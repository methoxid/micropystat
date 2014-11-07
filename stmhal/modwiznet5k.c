/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "stm32f4xx_hal.h"

#include "mpconfig.h"
#include "nlr.h"
#include "misc.h"
#include "qstr.h"
#include "obj.h"
#include "objlist.h"
#include "runtime.h"
#include "modnetwork.h"
#include "pin.h"
#include "genhdr/pins.h"
#include "spi.h"
#include MICROPY_HAL_H

#include "ethernet/wizchip_conf.h"
#include "ethernet/socket.h"
#include "internet/dns/dns.h"

/// \moduleref network

#define IPADDR_BUF_SIZE (4)

STATIC mp_obj_t wiznet5k_socket_new(uint8_t sn, mp_uint_t type);

typedef struct _wiznet5k_obj_t {
    mp_obj_base_t base;
    mp_uint_t cris_state;
    SPI_HandleTypeDef *spi;
    const pin_obj_t *cs;
    const pin_obj_t *rst;
    uint8_t socket_used;
} wiznet5k_obj_t;

STATIC wiznet5k_obj_t wiznet5k_obj;

STATIC void wiz_cris_enter(void) {
    wiznet5k_obj.cris_state = MICROPY_BEGIN_ATOMIC_SECTION();
}

STATIC void wiz_cris_exit(void) {
    MICROPY_END_ATOMIC_SECTION(wiznet5k_obj.cris_state);
}

STATIC void wiz_cs_select(void) {
    GPIO_clear_pin(wiznet5k_obj.cs->gpio, wiznet5k_obj.cs->pin_mask);
}

STATIC void wiz_cs_deselect(void) {
    GPIO_set_pin(wiznet5k_obj.cs->gpio, wiznet5k_obj.cs->pin_mask);
}

STATIC void wiz_spi_read(uint8_t *buf, uint32_t len) {
    HAL_StatusTypeDef status = HAL_SPI_Receive(wiznet5k_obj.spi, buf, len, 5000);
    (void)status;
}

STATIC void wiz_spi_write(const uint8_t *buf, uint32_t len) {
    HAL_StatusTypeDef status = HAL_SPI_Transmit(wiznet5k_obj.spi, (uint8_t*)buf, len, 5000);
    (void)status;
}

// Check the return value from Wiz socket calls:
//  - on error (<0) an exception is raised
//  - SOCK_OK or SOCK_BUSY does nothing
//  - anything positive does nothing
STATIC void check_sock_return_value(int8_t ret) {
    // TODO convert Wiz errno's to POSIX ones
    if (ret < 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_OSError, "socket error %d", ret));
    }
}

STATIC mp_obj_t wiznet5k_socket(mp_obj_t self_in, int domain, int type, int fileno, int *_errno) {
    if (domain != MOD_NETWORK_AF_INET) {
        *_errno = EAFNOSUPPORT;
        return MP_OBJ_NULL;
    }

    switch (type) {
        case MOD_NETWORK_SOCK_STREAM: type = Sn_MR_TCP; break;
        case MOD_NETWORK_SOCK_DGRAM: type = Sn_MR_UDP; break;
        default: *_errno = EINVAL; return MP_OBJ_NULL;
    }

    if (fileno < 0) {
        // get first unused socket number
        for (mp_uint_t sn = 0; sn < _WIZCHIP_SOCK_NUM_; sn++) {
            if ((wiznet5k_obj.socket_used & (1 << sn)) == 0) {
                fileno = sn;
                break;
            }
        }
        if (fileno < 0) {
            // too many open sockets
            *_errno = EMFILE;
            return MP_OBJ_NULL;
        }
    }

    return wiznet5k_socket_new(fileno, type);
}

STATIC int wiznet5k_gethostbyname(mp_obj_t nic, const char *name, mp_uint_t len, uint8_t *out_ip) {
    uint8_t dns_ip[IPADDR_BUF_SIZE] = {8, 8, 8, 8};
    uint8_t *buf = m_new(uint8_t, MAX_DNS_BUF_SIZE);
    DNS_init(0, buf);
    mp_int_t ret = DNS_run(dns_ip, (uint8_t*)name, out_ip);
    m_del(uint8_t, buf, MAX_DNS_BUF_SIZE);
    if (ret == 1) {
        // success
        return 0;
    } else {
        // failure
        return ENOENT;
    }
}
/******************************************************************************/
// Micro Python bindings

/// \class WIZnet5k - driver for WIZnet5x00 Ethernet modules
///
/// This class allows you to control WIZnet5x00 Ethernet adaptors based on
/// the W5200 and W5500 chipsets (only W5200 tested).
///
/// Example usage:
///
///     import wiznet5k
///     w = wiznet5k.WIZnet5k()
///     print(w.ipaddr())
///     w.gethostbyname('micropython.org')
///     s = w.socket()
///     s.connect(('192.168.0.2', 8080))
///     s.send('hello')
///     print(s.recv(10))

STATIC void wiznet5k_print(void (*print)(void *env, const char *fmt, ...), void *env, mp_obj_t self_in, mp_print_kind_t kind) {
    print(env, "WIZnet5k()");
}

/// \classmethod \constructor(spi, pin_cs, pin_rst)
/// Create and return a WIZnet5k object.
STATIC mp_obj_t wiznet5k_make_new(mp_obj_t type_in, mp_uint_t n_args, mp_uint_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 3, 3, false);

    // init the wiznet5k object
    wiznet5k_obj.base.type = (mp_obj_type_t*)&mod_network_nic_type_wiznet5k;
    wiznet5k_obj.cris_state = 0;
    wiznet5k_obj.spi = spi_get_handle(args[0]);
    wiznet5k_obj.cs = pin_find(args[1]);
    wiznet5k_obj.rst = pin_find(args[2]);
    wiznet5k_obj.socket_used = 0;

    /*!< SPI configuration */
    wiznet5k_obj.spi->Init.Mode = SPI_MODE_MASTER;
    wiznet5k_obj.spi->Init.Direction = SPI_DIRECTION_2LINES;
    wiznet5k_obj.spi->Init.DataSize = SPI_DATASIZE_8BIT;
    wiznet5k_obj.spi->Init.CLKPolarity = SPI_POLARITY_LOW; // clock is low when idle
    wiznet5k_obj.spi->Init.CLKPhase = SPI_PHASE_1EDGE; // data latched on first edge, which is rising edge for low-idle
    wiznet5k_obj.spi->Init.NSS = SPI_NSS_SOFT;
    wiznet5k_obj.spi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; // clock freq = f_PCLK / this_prescale_value; Wiz820i can do up to 80MHz
    wiznet5k_obj.spi->Init.FirstBit = SPI_FIRSTBIT_MSB;
    wiznet5k_obj.spi->Init.TIMode = SPI_TIMODE_DISABLED;
    wiznet5k_obj.spi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    wiznet5k_obj.spi->Init.CRCPolynomial = 7; // unused
    spi_init(wiznet5k_obj.spi, false);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = wiznet5k_obj.cs->pin_mask;
    HAL_GPIO_Init(wiznet5k_obj.cs->gpio, &GPIO_InitStructure);

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = wiznet5k_obj.rst->pin_mask;
    HAL_GPIO_Init(wiznet5k_obj.rst->gpio, &GPIO_InitStructure);

    GPIO_clear_pin(wiznet5k_obj.rst->gpio, wiznet5k_obj.rst->pin_mask);
    HAL_Delay(1); // datasheet says 2us
    GPIO_set_pin(wiznet5k_obj.rst->gpio, wiznet5k_obj.rst->pin_mask);
    HAL_Delay(160); // datasheet says 150ms

    reg_wizchip_cris_cbfunc(wiz_cris_enter, wiz_cris_exit);
    reg_wizchip_cs_cbfunc(wiz_cs_select, wiz_cs_deselect);
    reg_wizchip_spi_cbfunc(wiz_spi_read, wiz_spi_write);

    uint8_t sn_size[16] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 2k buffer for each socket
    ctlwizchip(CW_INIT_WIZCHIP, sn_size);

    // TODO make this configurable!
    wiz_NetInfo netinfo = {
        .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},
        .ip = {192, 168, 0, 18},
        .sn = {255, 255, 255, 0},
        .gw = {192, 168, 0, 1},
        .dns = {8, 8, 8, 8}, // Google public DNS
        .dhcp = NETINFO_STATIC,
    };
    ctlnetwork(CN_SET_NETINFO, (void*)&netinfo);

    // register with network module
    mod_network_register_nic(&wiznet5k_obj);

    // return wiznet5k object
    return &wiznet5k_obj;
}

/// \method regs()
/// Dump WIZnet5k registers.
STATIC mp_obj_t wiznet5k_regs(mp_obj_t self_in) {
    //wiznet5k_obj_t *self = self_in;
    printf("Wiz CREG:");
    for (int i = 0; i < 0x50; ++i) {
        if (i % 16 == 0) {
            printf("\n  %04x:", i);
        }
        printf(" %02x", WIZCHIP_READ(i));
    }
    for (int sn = 0; sn < 4; ++sn) {
        printf("\nWiz SREG[%d]:", sn);
        for (int i = 0; i < 0x30; ++i) {
            if (i % 16 == 0) {
                printf("\n  %04x:", i);
            }
            printf(" %02x", WIZCHIP_READ(WIZCHIP_SREG_ADDR(sn, i)));
        }
    }
    printf("\n");
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(wiznet5k_regs_obj, wiznet5k_regs);

/// \method ipaddr([(ip, subnet, gateway, dns)])
/// Get/set IP address, subnet mask, gateway and DNS.
STATIC mp_obj_t wiznet5k_ipaddr(mp_uint_t n_args, const mp_obj_t *args) {
    wiz_NetInfo netinfo;
    ctlnetwork(CN_GET_NETINFO, &netinfo);
    if (n_args == 1) {
        // get
        mp_obj_t tuple[4] = {
            mod_network_format_ipv4_addr(netinfo.ip),
            mod_network_format_ipv4_addr(netinfo.sn),
            mod_network_format_ipv4_addr(netinfo.gw),
            mod_network_format_ipv4_addr(netinfo.dns),
        };
        return mp_obj_new_tuple(4, tuple);
    } else {
        // set
        mp_obj_t *items;
        mp_obj_get_array_fixed_n(args[1], 4, &items);
        mod_network_parse_ipv4_addr(items[0], netinfo.ip);
        mod_network_parse_ipv4_addr(items[1], netinfo.sn);
        mod_network_parse_ipv4_addr(items[2], netinfo.gw);
        mod_network_parse_ipv4_addr(items[3], netinfo.dns);
        ctlnetwork(CN_SET_NETINFO, &netinfo);
        return mp_const_none;
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(wiznet5k_ipaddr_obj, 1, 2, wiznet5k_ipaddr);

STATIC const mp_map_elem_t wiznet5k_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_regs), (mp_obj_t)&wiznet5k_regs_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ipaddr), (mp_obj_t)&wiznet5k_ipaddr_obj },
};

STATIC MP_DEFINE_CONST_DICT(wiznet5k_locals_dict, wiznet5k_locals_dict_table);

const mod_network_nic_type_t mod_network_nic_type_wiznet5k = {
    .base = {
        { &mp_type_type },
        .name = MP_QSTR_WIZnet5k,
        .print = wiznet5k_print,
        .make_new = wiznet5k_make_new,
        .locals_dict = (mp_obj_t)&wiznet5k_locals_dict,
    },
    .socket = wiznet5k_socket,
    .gethostbyname = wiznet5k_gethostbyname,
};

/******************************************************************************/
// Micro Python bindings; WIZnet5x00 socket class

typedef struct _wiznet5k_socket_obj_t {
    mp_obj_base_t base;
    uint8_t sn;
    uint8_t type;
} wiznet5k_socket_obj_t;

STATIC const mp_obj_type_t wiznet5k_socket_type;

STATIC mp_obj_t wiznet5k_socket_new(uint8_t sn, mp_uint_t type) {
    wiznet5k_socket_obj_t *s = m_new_obj(wiznet5k_socket_obj_t);
    s->base.type = &wiznet5k_socket_type;
    s->sn = sn;
    s->type = type;
    return s;
}

STATIC void wiznet5k_socket_print(void (*print)(void *env, const char *fmt, ...), void *env, mp_obj_t self_in, mp_print_kind_t kind) {
    wiznet5k_socket_obj_t *self = self_in;
    print(env, "<WIZnet5k.socket sn=%u MR=0x%02x>", self->sn, getSn_MR(self->sn));
}

STATIC mp_obj_t wiznet5k_socket_close(mp_obj_t self_in) {
    wiznet5k_socket_obj_t *self = self_in;
    wiznet5k_obj.socket_used &= ~(1 << self->sn);
    mp_int_t ret = WIZCHIP_EXPORT(close)(self->sn);
    check_sock_return_value(ret);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(wiznet5k_socket_close_obj, wiznet5k_socket_close);

STATIC mp_obj_t wiznet5k_socket_bind(mp_obj_t self_in, mp_obj_t addr_in) {
    wiznet5k_socket_obj_t *self = self_in;

    uint8_t ip[IPADDR_BUF_SIZE];
    mp_uint_t port = mod_network_parse_inet_addr(addr_in, ip);

    // open the socket in server mode
    mp_int_t ret = WIZCHIP_EXPORT(socket)(self->sn, self->type, port, 0);
    check_sock_return_value(ret);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(wiznet5k_socket_bind_obj, wiznet5k_socket_bind);

STATIC mp_obj_t wiznet5k_socket_listen(mp_obj_t self_in, mp_obj_t backlog) {
    wiznet5k_socket_obj_t *self = self_in;
    mp_int_t ret = WIZCHIP_EXPORT(listen)(self->sn);
    check_sock_return_value(ret);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(wiznet5k_socket_listen_obj, wiznet5k_socket_listen);

STATIC mp_obj_t wiznet5k_socket_accept(mp_obj_t self_in) {
    //wiznet5k_socket_obj_t *self = self_in;

    // TODO what to do here exactly?

    mp_obj_t tuple[2] = {self_in, mp_const_none};
    return mp_obj_new_tuple(2, tuple);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(wiznet5k_socket_accept_obj, wiznet5k_socket_accept);

STATIC mp_obj_t wiznet5k_socket_connect(mp_obj_t self_in, mp_obj_t addr_in) {
    wiznet5k_socket_obj_t *self = self_in;

    // first open the socket in client mode
    mp_int_t ret = WIZCHIP_EXPORT(socket)(self->sn, self->type, 0, 0);
    check_sock_return_value(ret);

    // now connect
    uint8_t ip[IPADDR_BUF_SIZE];
    mp_uint_t port = mod_network_parse_inet_addr(addr_in, ip);
    ret = WIZCHIP_EXPORT(connect)(self->sn, ip, port);
    check_sock_return_value(ret);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(wiznet5k_socket_connect_obj, wiznet5k_socket_connect);

STATIC mp_obj_t wiznet5k_socket_disconnect(mp_obj_t self_in) {
    wiznet5k_socket_obj_t *self = self_in;
    mp_int_t ret = WIZCHIP_EXPORT(disconnect)(self->sn);
    check_sock_return_value(ret);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(wiznet5k_socket_disconnect_obj, wiznet5k_socket_disconnect);

STATIC mp_obj_t wiznet5k_socket_send(mp_obj_t self_in, mp_obj_t data_in) {
    wiznet5k_socket_obj_t *self = self_in;
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_in, &bufinfo, MP_BUFFER_READ);
    mp_int_t ret = WIZCHIP_EXPORT(send)(self->sn, bufinfo.buf, bufinfo.len);
    check_sock_return_value(ret);
    return mp_obj_new_int(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(wiznet5k_socket_send_obj, wiznet5k_socket_send);

STATIC mp_obj_t wiznet5k_socket_recv(mp_obj_t self_in, mp_obj_t len_in) {
    wiznet5k_socket_obj_t *self = self_in;
    mp_int_t len = mp_obj_get_int(len_in);
    byte *buf;
    mp_obj_t ret_obj = mp_obj_str_builder_start(&mp_type_bytes, len, &buf);
    mp_int_t ret = WIZCHIP_EXPORT(recv)(self->sn, buf, len);
    check_sock_return_value(ret);
    return mp_obj_str_builder_end_with_len(ret_obj, len);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(wiznet5k_socket_recv_obj, wiznet5k_socket_recv);

STATIC mp_obj_t wiznet5k_socket_sendto(mp_obj_t self_in, mp_obj_t data_in, mp_obj_t addr_in) {
    wiznet5k_socket_obj_t *self = self_in;
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data_in, &bufinfo, MP_BUFFER_READ);
    uint8_t ip[IPADDR_BUF_SIZE];
    mp_uint_t port = mod_network_parse_inet_addr(addr_in, ip);
    mp_int_t ret = WIZCHIP_EXPORT(sendto)(self->sn, bufinfo.buf, bufinfo.len, ip, port);
    check_sock_return_value(ret);
    return mp_obj_new_int(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(wiznet5k_socket_sendto_obj, wiznet5k_socket_sendto);

STATIC mp_obj_t wiznet5k_socket_recvfrom(mp_obj_t self_in, mp_obj_t len_in) {
    wiznet5k_socket_obj_t *self = self_in;
    mp_int_t len = mp_obj_get_int(len_in);
    uint8_t *buf = m_new(uint8_t, len);
    uint8_t ip[4];
    uint16_t port;
    mp_int_t ret = WIZCHIP_EXPORT(recvfrom)(self->sn, buf, len, ip, &port);
    check_sock_return_value(ret);
    mp_obj_t tuple[2] = {
        mp_obj_new_bytes(buf, ret),
        mod_network_format_inet_addr(ip, port),
    };
    return mp_obj_new_tuple(2, tuple);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(wiznet5k_socket_recvfrom_obj, wiznet5k_socket_recvfrom);

STATIC const mp_map_elem_t wiznet5k_socket_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_close), (mp_obj_t)&wiznet5k_socket_close_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_bind), (mp_obj_t)&wiznet5k_socket_bind_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_listen), (mp_obj_t)&wiznet5k_socket_listen_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_accept), (mp_obj_t)&wiznet5k_socket_accept_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_connect), (mp_obj_t)&wiznet5k_socket_connect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_disconnect), (mp_obj_t)&wiznet5k_socket_disconnect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_send), (mp_obj_t)&wiznet5k_socket_send_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_recv), (mp_obj_t)&wiznet5k_socket_recv_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_sendto), (mp_obj_t)&wiznet5k_socket_sendto_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_recvfrom), (mp_obj_t)&wiznet5k_socket_recvfrom_obj },
};

STATIC MP_DEFINE_CONST_DICT(wiznet5k_socket_locals_dict, wiznet5k_socket_locals_dict_table);

STATIC const mp_obj_type_t wiznet5k_socket_type = {
    { &mp_type_type },
    .name = MP_QSTR_socket,
    .print = wiznet5k_socket_print,
    .locals_dict = (mp_obj_t)&wiznet5k_socket_locals_dict,
};

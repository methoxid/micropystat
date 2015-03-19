// This file was automatically generated by make-pins.py
//
// --af boards/stm32f4xx_af.csv
// --board boards/BIPOT20/pins.csv
// --prefix boards/stm32f4xx_prefix.c

// stm32f4xx_prefix.c becomes the initial portion of the generated pins file.

#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"

#include "mpconfig.h"
#include "misc.h"
#include "qstr.h"
#include "obj.h"
#include "pin.h"

#define AF(af_idx, af_fn, af_unit, af_type, af_ptr) \
{ \
    { &pin_af_type }, \
    .name = MP_QSTR_AF ## af_idx ## _ ## af_fn ## af_unit, \
    .idx = (af_idx), \
    .fn = AF_FN_ ## af_fn, \
    .unit = (af_unit), \
    .type = AF_PIN_TYPE_ ## af_fn ## _ ## af_type, \
    .af_fn = (af_ptr) \
}

#define PIN(p_port, p_pin, p_num_af, p_af, p_adc_num, p_adc_channel) \
{ \
    { &pin_type }, \
    .name = MP_QSTR_ ## p_port ## p_pin, \
    .port = PORT_ ## p_port, \
    .pin = (p_pin), \
    .num_af = (p_num_af), \
    .pin_mask = (1 << ((p_pin) & 0x0f)), \
    .gpio = GPIO ## p_port, \
    .af = p_af, \
    .adc_num = p_adc_num, \
    .adc_channel = p_adc_channel, \
}

const pin_af_obj_t pin_A0_af[] = {
  AF( 1, TIM     ,  2, CH1       , TIM2    ), // TIM2_CH1
  AF( 1, TIM     ,  2, ETR       , TIM2    ), // TIM2_ETR
  AF( 2, TIM     ,  5, CH1       , TIM5    ), // TIM5_CH1
  AF( 3, TIM     ,  8, ETR       , TIM8    ), // TIM8_ETR
  AF( 7, USART   ,  2, CTS       , USART2  ), // USART2_CTS
  AF( 8, UART    ,  4, TX        , UART4   ), // UART4_TX
  //(11, ETH     ,  0, MII_CRS   , ETH     ), // ETH_MII_CRS
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A0 = PIN(A, 0, 6, pin_A0_af, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 0);

const pin_af_obj_t pin_A1_af[] = {
  AF( 1, TIM     ,  2, CH2       , TIM2    ), // TIM2_CH2
  AF( 2, TIM     ,  5, CH2       , TIM5    ), // TIM5_CH2
  AF( 7, USART   ,  2, RTS       , USART2  ), // USART2_RTS
  AF( 8, UART    ,  4, RX        , UART4   ), // UART4_RX
  //(11, ETH     ,  0, MII_RX_CLK, ETH     ), // ETH_MII_RX_CLK
  //(11, ETH     ,  0, RMII__REF_CLK, ETH     ), // ETH_RMII__REF_CLK
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A1 = PIN(A, 1, 4, pin_A1_af, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 1);

const pin_af_obj_t pin_A2_af[] = {
  AF( 1, TIM     ,  2, CH3       , TIM2    ), // TIM2_CH3
  AF( 2, TIM     ,  5, CH3       , TIM5    ), // TIM5_CH3
  AF( 3, TIM     ,  9, CH1       , TIM9    ), // TIM9_CH1
  AF( 7, USART   ,  2, TX        , USART2  ), // USART2_TX
  //(11, ETH     ,  0, MDIO      , ETH     ), // ETH_MDIO
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A2 = PIN(A, 2, 4, pin_A2_af, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 2);

const pin_af_obj_t pin_A3_af[] = {
  AF( 1, TIM     ,  2, CH4       , TIM2    ), // TIM2_CH4
  AF( 2, TIM     ,  5, CH4       , TIM5    ), // TIM5_CH4
  AF( 3, TIM     ,  9, CH2       , TIM9    ), // TIM9_CH2
  AF( 7, USART   ,  2, RX        , USART2  ), // USART2_RX
  //(10, OTG     ,  0, HS_ULPI_D0, OTG     ), // OTG_HS_ULPI_D0
  //(11, ETH     ,  0, MII_COL   , ETH     ), // ETH_MII_COL
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A3 = PIN(A, 3, 4, pin_A3_af, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 3);

const pin_af_obj_t pin_A4_af[] = {
  AF( 5, SPI     ,  1, NSS       , SPI1    ), // SPI1_NSS
  AF( 6, SPI     ,  3, NSS       , SPI3    ), // SPI3_NSS
  //( 6, I2S     ,  3, WS        , I2S3    ), // I2S3_WS
  AF( 7, USART   ,  2, CK        , USART2  ), // USART2_CK
  //(12, OTG     ,  0, HS_SOF    , OTG     ), // OTG_HS_SOF
  //(13, DCMI    ,  0, HSYNC     , DCMI    ), // DCMI_HSYNC
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A4 = PIN(A, 4, 3, pin_A4_af, PIN_ADC1 | PIN_ADC2, 4);

const pin_af_obj_t pin_A5_af[] = {
  AF( 1, TIM     ,  2, CH1       , TIM2    ), // TIM2_CH1
  AF( 1, TIM     ,  2, ETR       , TIM2    ), // TIM2_ETR
  AF( 3, TIM     ,  8, CH1N      , TIM8    ), // TIM8_CH1N
  AF( 5, SPI     ,  1, SCK       , SPI1    ), // SPI1_SCK
  //(10, OTG     ,  0, HS_ULPI_CK, OTG     ), // OTG_HS_ULPI_CK
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A5 = PIN(A, 5, 4, pin_A5_af, PIN_ADC1 | PIN_ADC2, 5);

const pin_af_obj_t pin_A6_af[] = {
  AF( 1, TIM     ,  1, BKIN      , TIM1    ), // TIM1_BKIN
  AF( 2, TIM     ,  3, CH1       , TIM3    ), // TIM3_CH1
  AF( 3, TIM     ,  8, BKIN      , TIM8    ), // TIM8_BKIN
  AF( 5, SPI     ,  1, MISO      , SPI1    ), // SPI1_MISO
  AF( 9, TIM     , 13, CH1       , TIM13   ), // TIM13_CH1
  //(13, DCMI    ,  0, PIXCK     , DCMI    ), // DCMI_PIXCK
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A6 = PIN(A, 6, 5, pin_A6_af, PIN_ADC1 | PIN_ADC2, 6);

const pin_af_obj_t pin_A7_af[] = {
  AF( 1, TIM     ,  1, CH1N      , TIM1    ), // TIM1_CH1N
  AF( 2, TIM     ,  3, CH2       , TIM3    ), // TIM3_CH2
  AF( 3, TIM     ,  8, CH1N      , TIM8    ), // TIM8_CH1N
  AF( 5, SPI     ,  1, MOSI      , SPI1    ), // SPI1_MOSI
  AF( 9, TIM     , 14, CH1       , TIM14   ), // TIM14_CH1
  //(11, ETH     ,  0, MII_RX_DV , ETH     ), // ETH_MII_RX_DV
  //(11, ETH     ,  0, RMII_CRS_DV, ETH     ), // ETH_RMII_CRS_DV
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A7 = PIN(A, 7, 5, pin_A7_af, PIN_ADC1 | PIN_ADC2, 7);

const pin_af_obj_t pin_A8_af[] = {
  //( 0, MCO     ,  1,           , MCO1    ), // MCO1
  AF( 1, TIM     ,  1, CH1       , TIM1    ), // TIM1_CH1
  AF( 4, I2C     ,  3, SCL       , I2C3    ), // I2C3_SCL
  AF( 7, USART   ,  1, CK        , USART1  ), // USART1_CK
  //(10, OTG     ,  0, FS_SOF    , OTG     ), // OTG_FS_SOF
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A8 = PIN(A, 8, 3, pin_A8_af, 0, 0);

const pin_af_obj_t pin_A9_af[] = {
  AF( 1, TIM     ,  1, CH2       , TIM1    ), // TIM1_CH2
  //( 4, I2C     ,  3, SMBA      , I2C3    ), // I2C3_SMBA
  AF( 7, USART   ,  1, TX        , USART1  ), // USART1_TX
  //(13, DCMI    ,  0, D0        , DCMI    ), // DCMI_D0
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A9 = PIN(A, 9, 2, pin_A9_af, 0, 0);

const pin_af_obj_t pin_A10_af[] = {
  AF( 1, TIM     ,  1, CH3       , TIM1    ), // TIM1_CH3
  AF( 7, USART   ,  1, RX        , USART1  ), // USART1_RX
  //(10, OTG     ,  0, FS_ID     , OTG     ), // OTG_FS_ID
  //(13, DCMI    ,  0, D1        , DCMI    ), // DCMI_D1
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A10 = PIN(A, 10, 2, pin_A10_af, 0, 0);

// const pin_af_obj_t pin_A13_af[] = {
  //( 0, JTMS-SWDIO,  0,           , JTMS-SWDIO), // JTMS-SWDIO
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_A13 = PIN(A, 13, 0, NULL, 0, 0);

// const pin_af_obj_t pin_A14_af[] = {
  //( 0, JTCK-SWCLK,  0,           , JTCK-SWCLK), // JTCK-SWCLK
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_A14 = PIN(A, 14, 0, NULL, 0, 0);

const pin_af_obj_t pin_A15_af[] = {
  //( 0, JTDI    ,  0,           , JTDI    ), // JTDI
  AF( 1, TIM     ,  2, CH1       , TIM2    ), // TIM2_CH1
  AF( 1, TIM     ,  2, ETR       , TIM2    ), // TIM2_ETR
  AF( 5, SPI     ,  1, NSS       , SPI1    ), // SPI1_NSS
  AF( 6, SPI     ,  3, NSS       , SPI3    ), // SPI3_NSS
  //( 6, I2S     ,  3, WS        , I2S3    ), // I2S3_WS
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_A15 = PIN(A, 15, 4, pin_A15_af, 0, 0);

const pin_af_obj_t pin_B0_af[] = {
  AF( 1, TIM     ,  1, CH2N      , TIM1    ), // TIM1_CH2N
  AF( 2, TIM     ,  3, CH3       , TIM3    ), // TIM3_CH3
  AF( 3, TIM     ,  8, CH2N      , TIM8    ), // TIM8_CH2N
  //(10, OTG     ,  0, HS_ULPI_D1, OTG     ), // OTG_HS_ULPI_D1
  //(11, ETH     ,  0, MII_RXD2  , ETH     ), // ETH_MII_RXD2
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B0 = PIN(B, 0, 3, pin_B0_af, PIN_ADC1 | PIN_ADC2, 8);

const pin_af_obj_t pin_B1_af[] = {
  AF( 1, TIM     ,  1, CH3N      , TIM1    ), // TIM1_CH3N
  AF( 2, TIM     ,  3, CH4       , TIM3    ), // TIM3_CH4
  AF( 3, TIM     ,  8, CH3N      , TIM8    ), // TIM8_CH3N
  //(10, OTG     ,  0, HS_ULPI_D2, OTG     ), // OTG_HS_ULPI_D2
  //(11, ETH     ,  0, MII_RXD3  , ETH     ), // ETH_MII_RXD3
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B1 = PIN(B, 1, 3, pin_B1_af, PIN_ADC1 | PIN_ADC2, 9);

const pin_af_obj_t pin_B3_af[] = {
  //( 0, JTDO    ,  0,           , JTDO    ), // JTDO
  //( 0, TRACESWO,  0,           , TRACESWO), // TRACESWO
  AF( 1, TIM     ,  2, CH2       , TIM2    ), // TIM2_CH2
  AF( 5, SPI     ,  1, SCK       , SPI1    ), // SPI1_SCK
  AF( 6, SPI     ,  3, SCK       , SPI3    ), // SPI3_SCK
  //( 6, I2S     ,  3, CK        , I2S3    ), // I2S3_CK
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B3 = PIN(B, 3, 3, pin_B3_af, 0, 0);

const pin_af_obj_t pin_B4_af[] = {
  //( 0, NJTRST  ,  0,           , NJTRST  ), // NJTRST
  AF( 2, TIM     ,  3, CH1       , TIM3    ), // TIM3_CH1
  AF( 5, SPI     ,  1, MISO      , SPI1    ), // SPI1_MISO
  AF( 6, SPI     ,  3, MISO      , SPI3    ), // SPI3_MISO
  //( 7, I2S3ext ,  0, SD        , I2S3ext ), // I2S3ext_SD
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B4 = PIN(B, 4, 3, pin_B4_af, 0, 0);

const pin_af_obj_t pin_B5_af[] = {
  AF( 2, TIM     ,  3, CH2       , TIM3    ), // TIM3_CH2
  //( 4, I2C     ,  1, SMBA      , I2C1    ), // I2C1_SMBA
  AF( 5, SPI     ,  1, MOSI      , SPI1    ), // SPI1_MOSI
  AF( 6, SPI     ,  3, MOSI      , SPI3    ), // SPI3_MOSI
  //( 6, I2S     ,  3, SD        , I2S3    ), // I2S3_SD
  //( 9, CAN     ,  2, RX        , CAN2    ), // CAN2_RX
  //(10, OTG     ,  0, HS_ULPI_D7, OTG     ), // OTG_HS_ULPI_D7
  //(11, ETH     ,  0, PPS_OUT   , ETH     ), // ETH_PPS_OUT
  //(13, DCMI    ,  0, D10       , DCMI    ), // DCMI_D10
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B5 = PIN(B, 5, 3, pin_B5_af, 0, 0);

const pin_af_obj_t pin_B6_af[] = {
  AF( 2, TIM     ,  4, CH1       , TIM4    ), // TIM4_CH1
  AF( 4, I2C     ,  1, SCL       , I2C1    ), // I2C1_SCL
  AF( 7, USART   ,  1, TX        , USART1  ), // USART1_TX
  //( 9, CAN     ,  2, TX        , CAN2    ), // CAN2_TX
  //(13, DCMI    ,  0, D5        , DCMI    ), // DCMI_D5
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B6 = PIN(B, 6, 3, pin_B6_af, 0, 0);

const pin_af_obj_t pin_B7_af[] = {
  AF( 2, TIM     ,  4, CH2       , TIM4    ), // TIM4_CH2
  AF( 4, I2C     ,  1, SDA       , I2C1    ), // I2C1_SDA
  AF( 7, USART   ,  1, RX        , USART1  ), // USART1_RX
  //(12, FSMC    ,  0, NL        , FSMC    ), // FSMC_NL
  //(13, DCMI    ,  0, VSYNC     , DCMI    ), // DCMI_VSYNC
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B7 = PIN(B, 7, 3, pin_B7_af, 0, 0);

const pin_af_obj_t pin_B8_af[] = {
  AF( 2, TIM     ,  4, CH3       , TIM4    ), // TIM4_CH3
  AF( 3, TIM     , 10, CH1       , TIM10   ), // TIM10_CH1
  AF( 4, I2C     ,  1, SCL       , I2C1    ), // I2C1_SCL
  //( 9, CAN     ,  1, RX        , CAN1    ), // CAN1_RX
  //(11, ETH     ,  0, MII_TXD3  , ETH     ), // ETH_MII_TXD3
  //(12, SDIO    ,  0, D4        , SDIO    ), // SDIO_D4
  //(13, DCMI    ,  0, D6        , DCMI    ), // DCMI_D6
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B8 = PIN(B, 8, 3, pin_B8_af, 0, 0);

const pin_af_obj_t pin_B9_af[] = {
  AF( 2, TIM     ,  4, CH4       , TIM4    ), // TIM4_CH4
  AF( 3, TIM     , 11, CH1       , TIM11   ), // TIM11_CH1
  AF( 4, I2C     ,  1, SDA       , I2C1    ), // I2C1_SDA
  AF( 5, SPI     ,  2, NSS       , SPI2    ), // SPI2_NSS
  //( 5, I2S     ,  2, WS        , I2S2    ), // I2S2_WS
  //( 9, CAN     ,  1, TX        , CAN1    ), // CAN1_TX
  //(12, SDIO    ,  0, D5        , SDIO    ), // SDIO_D5
  //(13, DCMI    ,  0, D7        , DCMI    ), // DCMI_D7
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B9 = PIN(B, 9, 4, pin_B9_af, 0, 0);

const pin_af_obj_t pin_B10_af[] = {
  AF( 1, TIM     ,  2, CH3       , TIM2    ), // TIM2_CH3
  AF( 4, I2C     ,  2, SCL       , I2C2    ), // I2C2_SCL
  AF( 5, SPI     ,  2, SCK       , SPI2    ), // SPI2_SCK
  //( 5, I2S     ,  2, CK        , I2S2    ), // I2S2_CK
  AF( 7, USART   ,  3, TX        , USART3  ), // USART3_TX
  //(10, OTG     ,  0, HS_ULPI_D3, OTG     ), // OTG_HS_ULPI_D3
  //(11, ETH     ,  0, MII_RX_ER , ETH     ), // ETH_MII_RX_ER
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B10 = PIN(B, 10, 4, pin_B10_af, 0, 0);

const pin_af_obj_t pin_B11_af[] = {
  AF( 1, TIM     ,  2, CH4       , TIM2    ), // TIM2_CH4
  AF( 4, I2C     ,  2, SDA       , I2C2    ), // I2C2_SDA
  AF( 7, USART   ,  3, RX        , USART3  ), // USART3_RX
  //(10, OTG     ,  0, HS_ULPI_D4, OTG     ), // OTG_HS_ULPI_D4
  //(11, ETH     ,  0, MII_TX_EN , ETH     ), // ETH_MII_TX_EN
  //(11, ETH     ,  0, RMII_TX_EN, ETH     ), // ETH_RMII_TX_EN
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B11 = PIN(B, 11, 3, pin_B11_af, 0, 0);

const pin_af_obj_t pin_B12_af[] = {
  AF( 1, TIM     ,  1, BKIN      , TIM1    ), // TIM1_BKIN
  //( 4, I2C     ,  2, SMBA      , I2C2    ), // I2C2_SMBA
  AF( 5, SPI     ,  2, NSS       , SPI2    ), // SPI2_NSS
  //( 5, I2S     ,  2, WS        , I2S2    ), // I2S2_WS
  AF( 7, USART   ,  3, CK        , USART3  ), // USART3_CK
  //( 9, CAN     ,  2, RX        , CAN2    ), // CAN2_RX
  //(10, OTG     ,  0, HS_ULPI_D5, OTG     ), // OTG_HS_ULPI_D5
  //(11, ETH     ,  0, MII_TXD0  , ETH     ), // ETH_MII_TXD0
  //(11, ETH     ,  0, RMII_TXD0 , ETH     ), // ETH_RMII_TXD0
  //(12, OTG     ,  0, HS_ID     , OTG     ), // OTG_HS_ID
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B12 = PIN(B, 12, 3, pin_B12_af, 0, 0);

const pin_af_obj_t pin_B13_af[] = {
  AF( 1, TIM     ,  1, CH1N      , TIM1    ), // TIM1_CH1N
  AF( 5, SPI     ,  2, SCK       , SPI2    ), // SPI2_SCK
  //( 5, I2S     ,  2, CK        , I2S2    ), // I2S2_CK
  AF( 7, USART   ,  3, CTS       , USART3  ), // USART3_CTS
  //( 9, CAN     ,  2, TX        , CAN2    ), // CAN2_TX
  //(10, OTG     ,  0, HS_ULPI_D6, OTG     ), // OTG_HS_ULPI_D6
  //(11, ETH     ,  0, MII_TXD1  , ETH     ), // ETH_MII_TXD1
  //(11, ETH     ,  0, RMII_TXD1 , ETH     ), // ETH_RMII_TXD1
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B13 = PIN(B, 13, 3, pin_B13_af, 0, 0);

const pin_af_obj_t pin_B14_af[] = {
  AF( 1, TIM     ,  1, CH2N      , TIM1    ), // TIM1_CH2N
  AF( 3, TIM     ,  8, CH2N      , TIM8    ), // TIM8_CH2N
  AF( 5, SPI     ,  2, MISO      , SPI2    ), // SPI2_MISO
  //( 6, I2S2ext ,  0, SD        , I2S2ext ), // I2S2ext_SD
  AF( 7, USART   ,  3, RTS       , USART3  ), // USART3_RTS
  AF( 9, TIM     , 12, CH1       , TIM12   ), // TIM12_CH1
  //(12, OTG     ,  0, HS_DM     , OTG     ), // OTG_HS_DM
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B14 = PIN(B, 14, 5, pin_B14_af, 0, 0);

const pin_af_obj_t pin_B15_af[] = {
  //( 0, RTC     ,  0, REFIN     , RTC     ), // RTC_REFIN
  AF( 1, TIM     ,  1, CH3N      , TIM1    ), // TIM1_CH3N
  AF( 3, TIM     ,  8, CH3N      , TIM8    ), // TIM8_CH3N
  AF( 5, SPI     ,  2, MOSI      , SPI2    ), // SPI2_MOSI
  //( 5, I2S     ,  2, SD        , I2S2    ), // I2S2_SD
  AF( 9, TIM     , 12, CH2       , TIM12   ), // TIM12_CH2
  //(12, OTG     ,  0, HS_DP     , OTG     ), // OTG_HS_DP
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_B15 = PIN(B, 15, 4, pin_B15_af, 0, 0);

// const pin_af_obj_t pin_C0_af[] = {
  //(10, OTG     ,  0, HS_ULPI_STP, OTG     ), // OTG_HS_ULPI_STP
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_C0 = PIN(C, 0, 0, NULL, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 10);

// const pin_af_obj_t pin_C1_af[] = {
  //(11, ETH     ,  0, MDC       , ETH     ), // ETH_MDC
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_C1 = PIN(C, 1, 0, NULL, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 11);

const pin_af_obj_t pin_C2_af[] = {
  AF( 5, SPI     ,  2, MISO      , SPI2    ), // SPI2_MISO
  //( 6, I2S2ext ,  0, SD        , I2S2ext ), // I2S2ext_SD
  //(10, OTG     ,  0, HS_ULPI_DIR, OTG     ), // OTG_HS_ULPI_DIR
  //(11, ETH     ,  0, MII_TXD2  , ETH     ), // ETH_MII_TXD2
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_C2 = PIN(C, 2, 1, pin_C2_af, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 12);

const pin_af_obj_t pin_C3_af[] = {
  AF( 5, SPI     ,  2, MOSI      , SPI2    ), // SPI2_MOSI
  //( 5, I2S     ,  2, SD        , I2S2    ), // I2S2_SD
  //(10, OTG     ,  0, HS_ULPI_NXT, OTG     ), // OTG_HS_ULPI_NXT
  //(11, ETH     ,  0, MII_TX_CLK, ETH     ), // ETH_MII_TX_CLK
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
};

const pin_obj_t pin_C3 = PIN(C, 3, 1, pin_C3_af, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 13);

// const pin_af_obj_t pin_C4_af[] = {
  //(11, ETH     ,  0, MII_RXD0  , ETH     ), // ETH_MII_RXD0
  //(11, ETH     ,  0, RMII_RXD0 , ETH     ), // ETH_RMII_RXD0
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_C4 = PIN(C, 4, 0, NULL, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 14);

// const pin_af_obj_t pin_C5_af[] = {
  //(11, ETH     ,  0, MII_RXD1  , ETH     ), // ETH_MII_RXD1
  //(11, ETH     ,  0, RMII_RXD1 , ETH     ), // ETH_RMII_RXD1
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_C5 = PIN(C, 5, 0, NULL, PIN_ADC1 | PIN_ADC2 | PIN_ADC3, 15);

// const pin_af_obj_t pin_C13_af[] = {
  //(15, EVENTOUT,  0,           , EVENTOUT), // EVENTOUT
// };

const pin_obj_t pin_C13 = PIN(C, 13, 0, NULL, 0, 0);

STATIC const mp_map_elem_t pin_cpu_pins_locals_dict_table[] = {
  { MP_OBJ_NEW_QSTR(MP_QSTR_A0), (mp_obj_t)&pin_A0 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A1), (mp_obj_t)&pin_A1 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A2), (mp_obj_t)&pin_A2 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A3), (mp_obj_t)&pin_A3 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A4), (mp_obj_t)&pin_A4 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A5), (mp_obj_t)&pin_A5 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A6), (mp_obj_t)&pin_A6 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A7), (mp_obj_t)&pin_A7 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A8), (mp_obj_t)&pin_A8 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A9), (mp_obj_t)&pin_A9 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A10), (mp_obj_t)&pin_A10 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A13), (mp_obj_t)&pin_A13 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A14), (mp_obj_t)&pin_A14 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A15), (mp_obj_t)&pin_A15 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B0), (mp_obj_t)&pin_B0 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B1), (mp_obj_t)&pin_B1 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B3), (mp_obj_t)&pin_B3 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B4), (mp_obj_t)&pin_B4 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B5), (mp_obj_t)&pin_B5 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B6), (mp_obj_t)&pin_B6 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B7), (mp_obj_t)&pin_B7 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B8), (mp_obj_t)&pin_B8 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B9), (mp_obj_t)&pin_B9 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B10), (mp_obj_t)&pin_B10 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B11), (mp_obj_t)&pin_B11 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B12), (mp_obj_t)&pin_B12 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B13), (mp_obj_t)&pin_B13 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B14), (mp_obj_t)&pin_B14 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B15), (mp_obj_t)&pin_B15 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C0), (mp_obj_t)&pin_C0 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C1), (mp_obj_t)&pin_C1 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C2), (mp_obj_t)&pin_C2 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C3), (mp_obj_t)&pin_C3 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C4), (mp_obj_t)&pin_C4 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C5), (mp_obj_t)&pin_C5 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C13), (mp_obj_t)&pin_C13 },
};
MP_DEFINE_CONST_DICT(pin_cpu_pins_locals_dict, pin_cpu_pins_locals_dict_table);

STATIC const mp_map_elem_t pin_board_pins_locals_dict_table[] = {
  { MP_OBJ_NEW_QSTR(MP_QSTR_LED_G), (mp_obj_t)&pin_A1 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_LED_R), (mp_obj_t)&pin_A2 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_LED_B), (mp_obj_t)&pin_A3 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A4), (mp_obj_t)&pin_A4 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A5), (mp_obj_t)&pin_A5 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX2A1), (mp_obj_t)&pin_A6 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX2A0), (mp_obj_t)&pin_A7 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_WIFIFCAH), (mp_obj_t)&pin_B6 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B7), (mp_obj_t)&pin_B7 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX2EN), (mp_obj_t)&pin_C4 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_PIN_BOOTSET), (mp_obj_t)&pin_C5 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_ASCK), (mp_obj_t)&pin_B3 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_C13), (mp_obj_t)&pin_C13 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_CHR_PG), (mp_obj_t)&pin_C0 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_CHR_CHG), (mp_obj_t)&pin_C1 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_PWR_ANALOG), (mp_obj_t)&pin_C2 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_BATT_ADC), (mp_obj_t)&pin_C3 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX3A1), (mp_obj_t)&pin_A10 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX3A0), (mp_obj_t)&pin_A9 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_BTRST), (mp_obj_t)&pin_B8 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_WIFIRST), (mp_obj_t)&pin_B9 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX1_A1), (mp_obj_t)&pin_B12 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX1_A0), (mp_obj_t)&pin_B13 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_MUX1_EN), (mp_obj_t)&pin_B14 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_CS_DAC), (mp_obj_t)&pin_B15 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B10), (mp_obj_t)&pin_B10 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_B11), (mp_obj_t)&pin_B11 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_PIN_RESET), (mp_obj_t)&pin_B0 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_PIN_OFF), (mp_obj_t)&pin_B1 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_AMISO), (mp_obj_t)&pin_B4 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A13), (mp_obj_t)&pin_A13 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_A14), (mp_obj_t)&pin_A14 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_BTPIN), (mp_obj_t)&pin_A15 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_SW), (mp_obj_t)&pin_A0 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_CS_ADC), (mp_obj_t)&pin_A8 },
  { MP_OBJ_NEW_QSTR(MP_QSTR_AMOSI), (mp_obj_t)&pin_B5 },
};
MP_DEFINE_CONST_DICT(pin_board_pins_locals_dict, pin_board_pins_locals_dict_table);

const pin_obj_t * const pin_adc1[] = {
  &pin_A0, // 0
  &pin_A1, // 1
  &pin_A2, // 2
  &pin_A3, // 3
  &pin_A4, // 4
  &pin_A5, // 5
  &pin_A6, // 6
  &pin_A7, // 7
  &pin_B0, // 8
  &pin_B1, // 9
  &pin_C0, // 10
  &pin_C1, // 11
  &pin_C2, // 12
  &pin_C3, // 13
  &pin_C4, // 14
  &pin_C5, // 15
};

const pin_obj_t * const pin_adc2[] = {
  &pin_A0, // 0
  &pin_A1, // 1
  &pin_A2, // 2
  &pin_A3, // 3
  &pin_A4, // 4
  &pin_A5, // 5
  &pin_A6, // 6
  &pin_A7, // 7
  &pin_B0, // 8
  &pin_B1, // 9
  &pin_C0, // 10
  &pin_C1, // 11
  &pin_C2, // 12
  &pin_C3, // 13
  &pin_C4, // 14
  &pin_C5, // 15
};

const pin_obj_t * const pin_adc3[] = {
  &pin_A0, // 0
  &pin_A1, // 1
  &pin_A2, // 2
  &pin_A3, // 3
  NULL,    // 4
  NULL,    // 5
  NULL,    // 6
  NULL,    // 7
  NULL,    // 8
  NULL,    // 9
  &pin_C0, // 10
  &pin_C1, // 11
  &pin_C2, // 12
  &pin_C3, // 13
  &pin_C4, // 14
  &pin_C5, // 15
};

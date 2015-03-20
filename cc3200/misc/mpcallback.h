/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Daniel Campora
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

#ifndef MPCALLBACK_H_
#define MPCALLBACK_H_

/******************************************************************************
 DEFINE CONSTANTS
 ******************************************************************************/
#define mpcallback_INIT_NUM_ARGS                  5

/******************************************************************************
 DEFINE TYPES
 ******************************************************************************/
typedef void (*mp_cb_method_t) (mp_obj_t self);
typedef mp_obj_t (*mp_cb_init_t) (mp_uint_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args);

typedef struct {
    mp_cb_init_t init;
    mp_cb_method_t enable;
    mp_cb_method_t disable;
} mp_cb_methods_t;

typedef struct {
    mp_obj_base_t base;
    mp_obj_t parent;
    mp_obj_t handler;
    mp_cb_methods_t *methods;
} mpcallback_obj_t;

/******************************************************************************
 DECLARE EXPORTED DATA
 ******************************************************************************/
extern const mp_arg_t mpcallback_init_args[];
extern const mp_obj_type_t pyb_callback_type;

/******************************************************************************
 DECLARE PUBLIC FUNCTIONS
 ******************************************************************************/
void mpcallback_init0 (void);
mp_obj_t mpcallback_new (mp_obj_t parent, mp_obj_t handler, const mp_cb_methods_t *methods);
mpcallback_obj_t *mpcallback_find (mp_obj_t parent);
void mpcallback_remove (const mp_obj_t parent);
void mpcallback_handler (mp_obj_t self_in);
uint mpcallback_translate_priority (uint priority);
mp_obj_t mpcallback_new (mp_obj_t parent, mp_obj_t handler, const mp_cb_methods_t *methods);

#endif /* MPCALLBACK_H_ */

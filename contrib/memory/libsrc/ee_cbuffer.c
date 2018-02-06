/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
    @file ee_cbuffer.c
    @brief Cicular Buffers library source file.
    @brief Buffer library source file.
    @author Errico Guidieri
    @date 2011
**/

#include "ee_cbuffer.h"

#include <string.h>

/*===========================================================
            Static Functions (Private Implementation)
===========================================================*/

static void * EE_cbuffer_push_and_get_write_addr(EE_CBuffer *cbuffer, EE_UINT16 data_length)
{
    /* Circular arithmetic to evaluate "push index" */
    EE_UINT16 write_index = (cbuffer->head + cbuffer->counter) % cbuffer->buffer_length;
    /* Increment Count (new element added)*/
    cbuffer->counter += data_length;
    /* evaluate the addres where write to */
    return (char *)cbuffer->memory + write_index;
}

static void * EE_cbuffer_pop_and_get_read_addr(EE_CBuffer *cbuffer, EE_UINT16 data_length)
{
    /* evaluate the address where read to */
    void * read_addr = (char *)cbuffer->memory + cbuffer->head;
    /* Circular arithmetic to evaluate new head */
    cbuffer->head = (cbuffer->head + data_length) % cbuffer->buffer_length;
    /* Decrement count (element removed) */
    cbuffer->counter -= data_length;
    return read_addr;
}

static EE_CBufferError EE_cbuffer_access_impl(const EE_CBuffer *cbuffer, EE_UINT16 index, void * ele, EE_UINT16 data_length)
{
    EE_CBufferError error = EE_CBUFF_OK;

    if((cbuffer == EE_NULL_CBUFF) || (ele == NULL) || (data_length == 0))
        error =  EE_CBUFF_ERR_NULL;

    if(!error){
        if(!EE_cbuffer_contains(cbuffer, data_length)){
            error = EE_CBUFF_ERR_TOO_FEW;
        } else if (index >= cbuffer->counter) {
            /* Out of Bounds condition */
            error = EE_CBUFF_ERR_OOB;
        } else {
            /* Circular arithmetic to evaluate "access index" */
            EE_UINT16 access_index = (cbuffer->head + index) % cbuffer->buffer_length;
            void * access_addr = (char *)cbuffer->memory + access_index;
            if(data_length > 1){
                const int offset = (char *)access_addr - (char *)cbuffer->memory;

                /* read in array boundaries */
                if((offset + data_length) <= cbuffer->buffer_length){
                    memcpy(ele, access_addr, data_length);
                } else { /* read outside array boundaries */
                    const int bytes_before_the_end = cbuffer->buffer_length - offset;
                    const int remaining_bytes      = data_length - bytes_before_the_end;

                    memcpy(ele, access_addr, bytes_before_the_end);
                    memcpy((char *)ele + bytes_before_the_end, cbuffer->memory, remaining_bytes);
                }
            } else {
                ((char *)ele)[0] = ((char *)access_addr)[0];
            }
        }
    }

    return error;
}

/*===========================================================
            Global Functions (Public Interface)
===========================================================*/

EE_CBufferError EE_cbuffer_init(EE_CBuffer * cbuffer, EE_UINT16 buffer_length, void * memory)
{
    EE_CBufferError error = EE_CBUFF_OK;

    if(cbuffer == EE_NULL_CBUFF)
        error =  EE_CBUFF_ERR_NULL;

    if(!error){
        cbuffer->head           = 0;
        cbuffer->counter        = 0;
        cbuffer->buffer_length  = buffer_length;
        cbuffer->memory         = memory;
    }

    return error;
}

/* This functions puts a message in the buffer (push in queue) */
EE_CBufferError EE_cbuffer_push(EE_CBuffer * cbuffer, const void * ele, EE_UINT16 data_length)
{
    EE_CBufferError error = EE_CBUFF_OK;

    if((cbuffer == EE_NULL_CBUFF) || (ele == NULL) || (data_length == 0))
        error = EE_CBUFF_ERR_NULL;

    if(!error){
        if(!EE_cbuffer_available(cbuffer, data_length)){
            error = EE_CBUFF_ERR_TOO_MANY;
        } else {
            void * write_addr = EE_cbuffer_push_and_get_write_addr(cbuffer, data_length);
            if(data_length > 1) {
                const int offset = (char *)write_addr - (char *)cbuffer->memory;

                /* write in array boundaries */
                if((offset + data_length) <= cbuffer->buffer_length){
                    memcpy(write_addr, ele, data_length);
                } else { /* write outside array boundaries */
                    const int bytes_before_the_end = cbuffer->buffer_length - offset;
                    const int remaining_bytes      = data_length - bytes_before_the_end;

                    memcpy(write_addr, ele, bytes_before_the_end);
                    memcpy(cbuffer->memory, (char *)ele + bytes_before_the_end, remaining_bytes);
                }
            } else {
                ((char *)write_addr)[0] = ((char *)ele)[0];
            }
        }
    }

    return error;
}

EE_CBufferError EE_cbuffer_pop(EE_CBuffer *cbuffer, void * ele, EE_UINT16 data_length)
{
    EE_CBufferError error = EE_CBUFF_OK;

    if((cbuffer == EE_NULL_CBUFF) || (ele == NULL) || (data_length == 0))
        error =  EE_CBUFF_ERR_NULL;

    if(!error){
        if(!EE_cbuffer_contains(cbuffer, data_length)){
            error = EE_CBUFF_ERR_TOO_FEW;
        } else {
            void * read_addr = EE_cbuffer_pop_and_get_read_addr(cbuffer, data_length);
            if(data_length > 1){
                const int offset = (char *)read_addr - (char *)cbuffer->memory;

                /* read in array boundaries */
                if((offset + data_length) <= cbuffer->buffer_length){
                    memcpy(ele, read_addr, data_length);
                } else { /* read outside array boundaries */
                    const int bytes_before_the_end = cbuffer->buffer_length - offset;
                    const int remaining_bytes      = data_length - bytes_before_the_end;

                    memcpy(ele, read_addr, bytes_before_the_end);
                    memcpy((char *)ele + bytes_before_the_end, cbuffer->memory, remaining_bytes);
                }
            } else {
                ((char *)ele)[0] = ((char *)read_addr)[0];
            }
        }
    }

    return error;
}

EE_CBufferError EE_cbuffer_first(const EE_CBuffer *cbuffer, void * ele, EE_UINT16 data_length)
{
    return EE_cbuffer_access_impl(cbuffer, 0, ele, data_length);
}

EE_CBufferError EE_cbuffer_last(const EE_CBuffer *cbuffer, void * ele, EE_UINT16 data_length)
{
    return EE_cbuffer_access_impl(cbuffer, (cbuffer->counter - data_length), ele, data_length);
}

EE_CBufferError EE_cbuffer_access(const EE_CBuffer *cbuffer, EE_UINT16 index, void * ele, EE_UINT16 data_length)
{
    return EE_cbuffer_access_impl(cbuffer, index, ele, data_length);
}

EE_CBufferError EE_cbuffer_skip(EE_CBuffer *cbuffer, EE_UINT16 bytes_to_skip)
{
    EE_CBufferError error = EE_CBUFF_OK;

    if(cbuffer == EE_NULL_CBUFF)
        error =  EE_CBUFF_ERR_NULL;

    if(!error && (bytes_to_skip > 0)){
        if(!EE_cbuffer_contains(cbuffer, bytes_to_skip)){
            error = EE_CBUFF_ERR_TOO_FEW;
        } else {
            EE_cbuffer_pop_and_get_read_addr(cbuffer, bytes_to_skip);
        }
    }

    return error;
}

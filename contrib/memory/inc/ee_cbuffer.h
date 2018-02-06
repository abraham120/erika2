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
    @file ee_cbuffer.h
    @brief Cicular Buffers library header file.
    
    The implementation of the circular queue make use of the 
    <it>fill counter</it>  mechanism to solve the Full/Empty condition and 
    particulary the case with one index and a fill counter
    (no additional variable required).
    @author Errico Guidieri
    @date 2011
**/

#ifndef __INCLUDE_MEMORY_CBUFFER_H__
#define __INCLUDE_MEMORY_CBUFFER_H__

#include <ee.h>

/** 
    @brief Cicular Buffers Type

    The implementation of the circular queue make use of the 
    <it>fill counter</it>  mechanism to solve the Full/Empty condition and 
    particulary the case with one index and a fill counter
    (no additional variable required).
**/
typedef struct EE_CBuffer{
    EE_UINT16   head;               /**<  head: points to first byte to be extracted **/
    EE_UINT16   counter;            /**<  counter: number of byte filled in buffer **/
    EE_UINT16   buffer_length;      /**<  buffer_length: size of array **/
    void *      memory;             /**<  memory: points to the buffer memory (supposed allocated byte dimension: buffer_length) **/
} EE_CBuffer;

typedef EE_INT8 EE_CBufferError;

/*================================================= 
          Symbols and macros definition
==================================================*/
/**
 @brief error codes
 @{
**/
#define EE_CBUFF_OK             (0x00)
#define EE_CBUFF_ERR_NULL       (-1)
#define EE_CBUFF_ERR_TOO_MANY   (-2)
#define EE_CBUFF_ERR_TOO_FEW    (-3)
#define EE_CBUFF_ERR_OOB        (-4) /** Out of Bounds **/
/** @} **/

/** @brief CBuffer NULL pointer **/
#define EE_NULL_CBUFF         ((EE_CBuffer *)0)


/*=================================================
              Functions declarations
==================================================*/
/**
    @brief This function is used to initialize a C-buffer. 
    
    Reset counters and indexes

    @param cbuffer: c-buffer struct pointer
    @param buffer_length: size of array  
    @param memory: points to the buffer memory (supposed allocated byte dimension: buffer_length)
    
    @return EE_CBUFF_OK if no errors found
*/
EE_CBufferError EE_cbuffer_init(EE_CBuffer * cbuffer, EE_UINT16 buffer_length, void * memory);

/**
    @brief Puts an element in the buffer.

    Puts a new element message in the buffer if there is a free location

    @param cbuffer: c-buffer struct pointer
    @param ele: element to add address 
    @param ele_length: new element's dimension in byte 
    
    @return EE_CBUFF_OK if no errors found
            EE_CBUFF_ERR_TOO_MANY if there's not enough space in the buffer    
**/
EE_CBufferError EE_cbuffer_push(EE_CBuffer *cbuffer, const void * ele, EE_UINT16 ele_length);

/**
    @brief Extracts first element from the buffer.

    Extracts first element from the buffer if buffer is not empty
    
    @param cbuffer: c-buffer struct pointer
    @param ele: address to be written with the extracted element
    @param ele_length: element's dimension in byte
    
    @return EE_CBUFF_OK if no errors found
            EE_CBUFF_ERR_FEW if the bites in buffer are not enough to fill the element    
**/
EE_CBufferError EE_cbuffer_pop(EE_CBuffer *cbuffer, void * ele, EE_UINT16 ele_length);

/**
    @brief Read first element in the buffer.

    Read first element from the buffer if buffer is not empty, without removing from it

    @param cbuffer: c-buffer struct pointer
    @param ele: address to be written with the read elements
    @param ele_length: element's dimension in byte

    @return EE_CBUFF_OK if no errors found
            EE_CBUFF_ERR_FEW if the bites in buffer are not enough to fill the element   
**/
EE_CBufferError EE_cbuffer_first(const EE_CBuffer *cbuffer, void * ele, EE_UINT16 ele_length);

/**
    @brief Read last element in the buffer.

    Read last element from the buffer if buffer is not empty, without removing from it
    
    @param cbuffer: c-buffer struct pointer
    @param ele: address to be written with the read element
    @param ele_length: element's dimension in byte    
    
    @return EE_CBUFF_OK if no errors found
            EE_CBUFF_ERR_FEW if the bites in buffer are not enough to fill the element    
**/
EE_CBufferError EE_cbuffer_last(const EE_CBuffer *cbuffer, void * ele, EE_UINT16 ele_length);

/**
    @brief Read last element in the buffer.

    Read last element from the buffer if buffer is not empty, without removing from it
    
    @param cbuffer: c-buffer struct pointer
    @param index: index where access at
    @param ele: address to be written with the read element
    @param ele_length: element's dimension in byte    
    
    @return EE_CBUFF_OK if no errors found
            EE_CBUFF_ERR_FEW if the bites in buffer are not enough to fill the element
            EE_CBUFF_ERR_OOB if index is >= C-buffer number of actual elements (counter)
**/
EE_CBufferError EE_cbuffer_access(const EE_CBuffer *cbuffer, EE_UINT16 index, void * ele, EE_UINT16 ele_length);


/**
    @brief Remove without read n bytes from the head of C-Buffer.

    Remove without read n bytes from the head of C-Buffer    
    
    @param cbuffer: c-buffer struct pointer
    @param bytes_to_skip: number of bytes to be skipped;
    
    @return EE_CBUFF_OK if no errors found
            EE_CBUFF_ERR_FEW if the bites in buffer are not enough to be skipped
**/
EE_CBufferError EE_cbuffer_skip(EE_CBuffer *cbuffer, EE_UINT16 bytes_to_skip);

/**
    @brief Check if the buffer is empty.

    Checks the counter of the buffer is equal to zero.
    
    @param cbuffer: c-buffer struct pointer
    @param num_bytes: number of bytes that buffer should contains at least
    
    @return 1 if buffer contains more or equal bytes of num_bytes
            0 otherwise    
**/
__INLINE__ EE_BIT EE_cbuffer_contains(const EE_CBuffer *cbuffer, EE_UINT16 num_bytes){
    return (cbuffer->counter >= num_bytes);
}

/**
    @brief Check if the buffer is full.
    
    Compare the counter of the buffer with the max size.
    
    @param cbuffer: c-buffer struct pointer
    @return 1 if in buffer are available more or equal bytes of num_bytes
            0 otherwise     
**/
__INLINE__ EE_BIT EE_cbuffer_available(const EE_CBuffer *cbuffer, EE_UINT16 num_bytes){
    return ((cbuffer->buffer_length - cbuffer->counter) >= num_bytes);
}

#endif /* __INCLUDE_MEMORY_CBUFFER_H__ */



/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file ee_buffer.h
	@brief Buffers library header file. 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __INCLUDE_EEMCUMICO32_BUFFER_H__
#define __INCLUDE_EEMCUMICO32_BUFFER_H__

#include "cpu/mico32/inc/ee_internal.h"

typedef struct {
    int g;							// get index: points to the first packet to be extracted
	int p;							// put index: points to the next empty location
	int counter;					// counter: to make difference between full queue and empty queue...
	int msg_size;					// size of a single message
	int buf_size;					// size of the buffer (vector of messages)
	EE_UINT8 *data;						// buffer vector (dimension: msg_size * buf_size)
} EE_buffer;


/*************************************************** 
* Symbols and macros definition
****************************************************/
#define EE_BUF_OK			(0x00)
#define EE_BUF_ERR_SIZE 	(-1)
#define EE_BUF_ERR_FULL 	(-2)
#define EE_BUF_ERR_EMPTY 	(-3)
#define EE_BUF_ERR_NULL 	(-4) 

#define EE_NULL_BUF			((EE_buffer *)0)

#define buf(i,j) buf->data[(i) * buf->msg_size + (j)]


/*************************************************** 
* Functions declarations
****************************************************/
/*
	This function is used to initialize a buffer. 
		Arguments:
			- EE_buffer *buf: buffer pointer
			- int msgsize: size of a message
			- int bufsize: size of the buffer   
			- EE_UINT8 *vet: vector used for buffering (vector size: msgsize*bufsize)
		Actions: 
			- reset counters and indexes (this function works with interrupts disabled...)
		Return values:
			- the function return the result: EE_BUF_OK if no errors found
*/
int EE_buffer_init(EE_buffer *buf, int msgsize, int bufsize, EE_UINT8 *vet);	// vet must be: EE_UINT8 vet[msgsize*bufsize]


/*
	This function puts a new message in the buffer.
		Arguments:
			- EE_buffer *buf: buffer pointer
			- EE_UINT8 *msg: address of first location of the message to be loaded 
		Actions: 
			- puts a message in the buffer if there is a free location (this function works with interrupts disabled...)
		Return values:
			- the function return the result: EE_BUF_OK if no errors found
											  EE_BUF_ERR_FULL if buffer is full	
*/
int EE_buffer_putmsg(EE_buffer *buf, EE_UINT8* msg);


/*
	This function extracts a message from the buffer.
		Arguments:
			- EE_buffer *buf: buffer pointer
			- EE_UINT8 *msg: address of first location of the message to be written with the extracted message 
		Actions: 
			- extracts a message from the buffer if buffer is not empty (this function works with interrupts disabled...)
		Return values:
			- the function return the result: EE_BUF_OK if no errors found
											  EE_BUF_ERR_EMPTY if buffer is empty	
*/
int EE_buffer_getmsg(EE_buffer *buf, EE_UINT8* msg);

/*
	This function can be used to check if the buffer is empty.
		Arguments:
			- EE_buffer *buf: buffer pointer
		Actions: 
			- this function checks the counter of the buffer (this function works with interrupts disabled...)
		Return values:
			- the function return the result: 1 if buffer is empty
											  0 if buffer is not empty	
*/
int EE_buffer_isempty(EE_buffer *buf);

/*
	This function can be used to check if the buffer is full.
		Arguments:
			- EE_buffer *buf: buffer pointer
		Actions: 
			- this function compare the counter of the buffer with the max size (this function works with interrupts disabled...)
		Return values:
			- the function return the result: 1 if buffer is full
											  0 if buffer is not full	
*/
int EE_buffer_isfull(EE_buffer *buf);

#endif // __INCLUDE_EEMCUMICO32_BUFFER_H__



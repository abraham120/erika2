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
    @file     ee_ring_buffer.c
    @brief    Static ring buffer implementation.
    @author   Alessandro Biondi
    @date     2013
    @example

*/

#ifndef __EE_RING_BUFFER_H__
#define __EE_RING_BUFFER_H__

#include <ee.h>

#define EE_RING_BUFFER_ALLOC(mem_area,size) EE_UINT8 mem_area[size+1]

/* Private - do not access directly */
typedef struct
{
  EE_UINT8 front;
  EE_UINT8 rear;
  EE_UINT16 size;
} EE_type_ring_buffer_info;

typedef struct
{
  EE_type_ring_buffer_info 	info;
  EE_UINT8     				*data;
} EE_type_ring_buffer;


__INLINE__ void __ALWAYS_INLINE__ EE_ring_buffer_init(EE_type_ring_buffer *buff, EE_UINT8 *mem_area, EE_UINT16 size)
{
	buff->info.front = buff->info.rear = 0; 
	buff->info.size  = size+1;
	buff->data		 = mem_area;
}

__INLINE__ void __ALWAYS_INLINE__ EE_ring_buffer_put(EE_type_ring_buffer *buff, EE_UINT8 item)
{
	buff->data[buff->info.rear] = item;
	buff->info.rear = (buff->info.rear+1) % buff->info.size;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_ring_buffer_get(EE_type_ring_buffer *buff)
{
	EE_UINT8 item;
	item = buff->data[buff->info.front];
	buff->info.front = (buff->info.front+1) % buff->info.size;
	return item;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_ring_buffer_isempty(EE_type_ring_buffer buff)
{
	return (buff.info.front==buff.info.rear);
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_ring_buffer_isfull(EE_type_ring_buffer buff)
{
	return (((buff.info.rear+1)%buff.info.size)==buff.info.front);
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_ring_buffer_head(EE_type_ring_buffer buff)
{
	return buff.data[buff.info.front];
}


#endif

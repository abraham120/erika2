/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/*
 * A simple FIFO queue.
 * 
 * more than one reader task and more than one writer task can respectively 
 * read and write on the FIFO.
 * 
 * The hypothesis here is that reads and writes on integers are atomic on the 
 * Nios II architecture.
 */

#ifndef __FIFO_H__
#define __FIFO_H__

#include "alt_types.h"
#include "ee.h"


/* The shared FIFO data structure */
typedef struct {
    int n_max;              /* Maximum number of elements in the FIFO */
    alt_u32 *fifo_data;     /* a pointer to the array of data */
   
    /* writers part */
    int data_written;       /* number of writes on the FIFO */
    int head;               /* the current head */
    
    /* readers part */
    int data_read;          /* number of reads on the FIFO */
    int tail;
} fifo_t;


/* 
 * FIFO initialization
 * Parameters:
 * 1) (in) pointer to a fifo structure
 * 2) (in) maximum number of items inside the FIFO
 * 3) (in) pointer to the data written/read
 */
void fifo_init(fifo_t *f, int n_max, alt_u32 *data);

/*
 * Non-blocking write on the FIFO
 * 
 * Parameters:
 * 1) (in) pointer to a fifo structure
 * 2) (in) resource to be used for mutual exclusion among writers
 * 3) (in) data to be written
 * 
 * Result:
 * 0 if success, 1 otherwise (FIFO full)
 */ 
int fifo_write(fifo_t *f, ResourceType wm, alt_u32 data);

/*
 * Non-blocking read on the FIFO
 * 
 * Parameters:
 * 1) (in) pointer to a fifo structure
 * 2) (in) resource to be used for mutual exclusion among readers
 * 3) (out) pointer to the data read (data to be written)
 * 
 * Result:
 * 0 if success, 1 otherwise (FIFO empty)
 */ 
int fifo_read(fifo_t *f, ResourceType rm, alt_u32 *data);

#endif

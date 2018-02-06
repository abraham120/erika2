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
 * Author: 2004 Antonio Fiaschi
 * CVS: $Id: inithal.c,v 1.10 2006/01/24 11:05:02 pj Exp $
 */

#include "ee.h"
#include "code.h"
#include "cfg_evb.h"

//extern void EE_IRQ_epilogue(void);

const EE_ADDR EE_mpc5_system_stack = (EE_ADDR)(__SYS_STACK_ADDRESS);

EE_ADDR EE_mpc5_IRQ_tos = (EE_ADDR)(__IRQ_STACK_ADDRESS);

struct EE_TOS EE_mpc5_system_tos[THREAD_MAX+1] =
{
    {(EE_ADDR)(__THREAD_STACK_ADDRESS        ),0}, /* main. MANDATORY! */
    {(EE_ADDR)(__THREAD_STACK_ADDRESS-512 -32),0}, /* thread0 */
    {(EE_ADDR)(__THREAD_STACK_ADDRESS-1024-32),0}, /* thread1 */
    {(EE_ADDR)(__THREAD_STACK_ADDRESS-1536-32),0}, /* thread2 */
    {(EE_ADDR)(__THREAD_STACK_ADDRESS-2048-32),0} /* thread3 */
};

#define __HANDLER_STACK_ADDRESS (__THREAD_STACK_ADDRESS-(512*(THREAD_MAX+1))-32)

struct EE_TOS EE_mpc5_handler_tos[16] = 
{
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS        ),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-512 -32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-1024-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-1536-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-2048-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-2560-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-3072-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-3584-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-4096-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-4608-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-5120-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-5632-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-6144-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-6656-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-7168-32),0},
    {(EE_ADDR)(__HANDLER_STACK_ADDRESS-7680-32),0}
};


const struct EE_THREAD_TOC EE_mpc5_thread_toc[THREAD_MAX+1] =
{
    {(EE_AID)0,(EE_ADDR)main,0,0,0},
    {(EE_AID)1,(EE_ADDR)thread0, 1,0,0},
    {(EE_AID)1,(EE_ADDR)thread1, 2,0,0},
    {(EE_AID)2,(EE_ADDR)thread2, 3,0,0},
    {(EE_AID)2,(EE_ADDR)thread3, 4,0,0}
};

EE_UREG EE_mpc5_thread_tos[THREAD_MAX+1] =
{
    0,				/* main */
    1,				/* thread0 */
    2,				/* thread1 */
    3,				/* thread2 */
    4				/* thread3 */
};


EE_UREG EE_mpc5_active_tos = 0; 
EE_TID EE_mpc5_active_thread = 0;
EE_AID EE_mpc5_active_application = 0; /* kernel */

EE_ADDR EE_mpc5_thread_epilogue[THREAD_MAX+1];

//struct EE_CONTEXT EE_mpc5_thread_context[THREAD_MAX+1];

#ifdef __ALLOW_NESTED_IRQ__
#ifndef __ENHANCED_IRQ__
const EE_UINT32 EE_mpc5_irq_mask[16] = {
	0x00000000,
	0x80000000,
	0xC0000000,
	0xE0000000,
	0xF0000000,
	0xF8000000,
	0xFC000000,
	0xFE000000,
	0xFF000000,
	0xFF800000,
	0xFFC00000,
	0xFFE00000,
	0xFFF00000,
	0xFFF80000,
	0xFFFC0000,
	0xFFFE0000
};
#endif
#endif

/* IRQ handlers installation */
#ifndef __ENHANCED_IRQ_
const struct EE_HANDLER_TOC EE_hal_IRQ_handler[16] = {
	{(EE_ADDR) handler_not_defined,0}, /* IRQ0 handler*/
	{(EE_ADDR) handler_not_defined,0}, /* LVL0 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* IRQ1 handler*/
#ifdef __RT_CLOCK_USED__
        {(EE_ADDR) rt_clock_handler,1},    /* LVL1 handler*/
#else
	{(EE_ADDR) handler_not_defined,0},
#endif
        {(EE_ADDR) handler_not_defined,0}, /* IRQ2 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* LVL2 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* IRQ3 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* LVL3 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* IRQ4 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* LVL4 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* IRQ5 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* LVL5 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* IRQ6 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* LVL6 handler*/
        {(EE_ADDR) handler_not_defined,0}, /* IRQ7 handler*/
        {(EE_ADDR) handler_not_defined,0}  /* LVL7 handler*/
};
#endif


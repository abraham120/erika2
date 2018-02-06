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
 * Author: 2002 Paolo Gai
 * CVS: $Id: initst10.c,v 1.3 2006/01/17 13:18:22 pj Exp $
 */

#include "ee.h"
#include "code.h"

#ifdef __MULTI__

#ifdef __ST10__
// user stack for the application...
EE_UINT16 EE_st10_user_stack[__USR_STK_SIZE__];



// 0xFCC0 used by the monitor, 
// 0xFC00 used by the main(), 
// 0xFC20 used by the interrupts
// ------------------------------------------------------------------
// WARNING: All interrupts must fire AFTER the call to st10_start!!!!
// ------------------------------------------------------------------

// 0xFC40, 0xFC60, 0xFC80, 0xFCa0, 0xFCe0 free for the threads!!!
// (ROM)
iram EE_UINT16 EE_st10_thread_cp[THREAD_MAX] = 
{ 0xFC40, 0xFC60, 0xFC80, 0xFCa0};

iram EE_ADDR EE_hal_thread_body[THREAD_MAX] = 
{ (EE_ADDR)thread0, (EE_ADDR)thread1, (EE_ADDR)thread2, (EE_ADDR)thread3};


// ROM TOS structures
// 256 bytes of system stack --> addresses = fa00 - fbff
// We give the main the first bytes of the TOS, since the boot sequence starts from the main task!
iram struct EE_struct_tos EE_stack_tos[THREAD_MAX+1] = 
{ 
  {0,0},                            // main --> st10_start loads user and system TOS!!!
  {0xfb90, (EE_ADDR)(EE_st10_user_stack+10)},  // Threads
  {0xfb30, (EE_ADDR)(EE_st10_user_stack+20)},
  {0xfad0, (EE_ADDR)(EE_st10_user_stack+30)},
  {0xfb10, (EE_ADDR)(EE_st10_user_stack+40)}
  // Interrupts: Remember that interrupts should have their own stack that have to be passed
  // when initializing the handlers using hal_set_handler!!!
  // In this example, We reserved {0xfa70, (ADDR)(user_stack+50)} for interrupt handlers
};
  
 
// ROM
// do not put any declaration here!!! This configuration only works because
// main_tos is allocated just before stack_tos!!

iram EE_UINT16 EE_st10_thread_tos[THREAD_MAX+1] =
{
  (EE_UINT16)(EE_stack_tos),   
  (EE_UINT16)(EE_stack_tos+1),
  (EE_UINT16)(EE_stack_tos+2),
  (EE_UINT16)(EE_stack_tos+3),
  (EE_UINT16)(EE_stack_tos+4)
};


// RAM
iram EE_UREG EE_st10_active_tos = (EE_UREG)EE_stack_tos;

// ROM
iram EE_UREG EE_st10_IRQ_user_tos = (EE_UREG)(EE_st10_user_stack+100);
iram EE_UREG EE_st10_IRQ_sys_tos	= 0xfa70;

#endif

#ifdef __ST10SEGM__

// user stack for the application...
EE_UINT16 EE_st10_user_stack[__USR_STK_SIZE__];



// 0xFCC0 used by the monitor, 
// 0xFC00 used by the main(), 
// 0xFC20 used by the interrupts
// ------------------------------------------------------------------
// WARNING: All interrupts must fire AFTER the call to st10_start!!!!
// ------------------------------------------------------------------

// 0xFC40, 0xFC60, 0xFC80, 0xFCa0, 0xFCe0 free for the threads!!!
// (ROM)
iram EE_UINT16 EE_st10_thread_cp[THREAD_MAX] = 
{ 0xFC40, 0xFC60, 0xFC80, 0xFCa0};

iram EE_ADDR EE_hal_thread_body[THREAD_MAX] = 
{ (EE_ADDR)thread0, (EE_ADDR)thread1, (EE_ADDR)thread2, (EE_ADDR)thread3};

// ROM TOS structures
// 256 bytes of system stack --> addresses = fa00 - fbff
// We give the main the first bytes of the TOS, since the boot sequence starts from the main task!
iram EE_ADDR EE_st10_tos[THREAD_MAX+1] = 
{ 
  NULL,                                  // main  --> st10_start loads user and system TOS!!!
  (EE_ADDR)(EE_st10_user_stack+100),            // Threads
  (EE_ADDR)(EE_st10_user_stack+200),
  (EE_ADDR)(EE_st10_user_stack+300),
  (EE_ADDR)(EE_st10_user_stack+400)
  // Interrupts: Remember that interrupts should have their own stack that have to be passed
  // when initializing the handlers using hal_set_handler!!!
  // In this example, We reserved {0xfa70, (ADDR)(user_stack+45)} for interrupt handlers
};
 
// ROM
// do not put any declaration here!!! This configuration only works because
// main_tos is allocated just before stack_tos!!

iram EE_UINT16 EE_st10_thread_tos[THREAD_MAX+1] =
{
  0,   // main
  1,
  2,
  3,
  4
};


// RAM
iram EE_TID EE_st10_active_tid = 0xFFFF;

// ROM
iram EE_ADDR EE_st10_IRQ_tos   = (EE_ADDR)(EE_st10_user_stack+500);

#endif

#endif

void my_init(void);

void my_init(void)
{
  #pragma asm
 	MOV T6IC,ZEROS                                                             
 	MOV T6CON,ZEROS                                                               
 	MOV T6,ZEROS                                                             
 	BSET T6R
	MOV T6IC, #00044h
  #pragma endasm
}



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
 * Author: 2000 Paolo Gai, Enico Bini
 * CVS: $Id: code.c,v 1.4 2006/01/05 14:38:25 pj Exp $
 */

#include "ee.h"
#include "code.h"

/* Do NOT use these in combination with __ST10SEGM__ */
//#define UNLOCK_WITH_PREEMPTION
//#define UNLOCK_WITHOUT_PREEMPTION
//#define ENDCYCLE_POP
//#define ENDCYCLE_READY
//#define ACTIVATE_NACT
//#define ACTIVATE_READY
//#define ACTIVATE_PREEMPT
// for the time tests look into timer.c

iram EE_UINT16 pre;
iram EE_UINT16 post;

void thread0(void)
{
      #ifdef UNLOCK_WITH_PREEMPTION
      #pragma asm
                                                 
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // UNLOCK_WITH_PREEMPTION breakpoint
  EE_mutex_lock(0);
      #ifdef UNLOCK_WITHOUT_PREEMPTION
      #pragma asm
                                                          
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
  EE_mutex_unlock(0);
      #ifdef UNLOCK_WITHOUT_PREEMPTION
      #pragma asm
                                                 
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // UNLOCK_WITHOUT_PREEMPTION breakpoint
  EE_thread_activate(2);
  EE_sys_scheduler();
      #ifdef ENDCYCLE_READY
      #pragma asm
                                                                                                     
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
}

void thread1(void)
{
      #ifdef ENDCYCLE_READY
      #pragma asm
                                        
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // ENDCYCLE_READY breakpoint   (it works only the at the first activation)

      #ifdef ACTIVATE_PREEMPT
      #pragma asm
                                                                 
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // ACTIVATE_PREEMPT breakpoint

      #ifdef ACTIVATE_NACT
      #pragma asm
                                               
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
  EE_thread_activate(2);
  EE_sys_scheduler();
      #ifdef ACTIVATE_NACT
      #pragma asm
                                                   
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // ACTIVATE_NACT breakpoint
      #ifdef ENDCYCLE_POP
      #pragma asm	       
                                            
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
}

void thread2(void)
{
      #ifdef ACTIVATE_PREEMPT
      #pragma asm
                                                                 
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
  EE_thread_activate(1);
  EE_sys_scheduler();
      #ifdef ENDCYCLE_POP
      #pragma asm
                                                
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // ENDCYCLE_POP breakpoint
  EE_mutex_lock(0);
      #ifdef ACTIVATE_READY
      #pragma asm
                                                                       
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
  EE_thread_activate(0);
  EE_sys_scheduler();
      #ifdef ACTIVATE_READY
      #pragma asm
      EXTERN _post:WORD
      MOV _post,T6
      #pragma endasm
      #endif
      // ACTIVATE_READY breakpoint
      #ifdef UNLOCK_WITH_PREEMPTION
      #pragma asm
                                                                        
      EXTERN _pre:WORD
      MOV _pre,T6
      #pragma endasm
      #endif
  EE_mutex_unlock(0);
}


void main(void)
{
  #pragma asm
                                                                
 	MOV T6IC,ZEROS                                                             
 	MOV T6CON,ZEROS                                                               
 	MOV T6,ZEROS                                                             
 	BSET T6R
	MOV T6IC, #00044h
  #pragma endasm

  /* test for nested primitives and interrupt disabling...
     Note that these function will be never called in this order, 
     however it is useful to see if interrupts are handled correctly */
  /* removed because no more visible in this file! */
  //EE_hal_begin_nested_primitive();
  //	EE_hal_begin_nested_primitive();
  //	EE_hal_end_nested_primitive();
  //EE_hal_end_nested_primitive();

	  for (;;) {}
}


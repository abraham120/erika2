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
 * Author: 2000-2004 Paolo Gai
 * CVS: $Id: ee_internal.h,v 1.6 2006/04/08 21:08:54 pj Exp $
 */


#include "st10mono/arch.h"

#ifndef __INCLUDE_ST10MONO_INTERNAL_H__
#define __INCLUDE_ST10MONO_INTERNAL_H__


/*
 * Generic Primitives
 */

/* critical section for generic primitive called into an ISR or into a task */

__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
  register EE_FREG temp;

  #pragma asm
	MOV @w1, PSW
	BCLR IEN
  #pragma endasm(temp=@w1)

  return temp;
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
    #pragma asm (@w1=f)
	MOV PSW, @w1
    #pragma endasm
}



/* 
 * Context Handling  
 */

extern EE_UREG EE_aux1, EE_aux2, EE_aux3, EE_aux4;

#ifdef __MONO__

/* These functions are implemented in assembly */
void EE_st10_ready2stacked (EE_ADDR cp, EE_ADDR body);

#ifdef __ST10_OPTIMIZED__
void EE_st10_endcycle_ready(EE_ADDR cp, EE_ADDR body);
void EE_st10_IRQ_ready     (EE_ADDR cp, EE_ADDR body);
#endif


__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID t)
{
  EE_st10_ready2stacked(EE_st10_thread_cp[t], EE_hal_thread_body[t]);
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  EE_st10_endcycle_ready(EE_st10_thread_cp[t], EE_hal_thread_body[t]);
#else
  EE_aux1 = (EE_UREG)EE_st10_thread_cp[t];
  EE_aux2 = (EE_UREG)EE_hal_thread_body[t];
#endif
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  EE_st10_IRQ_ready(EE_st10_thread_cp[t], EE_hal_thread_body[t]);
#else                       
			               
  EE_aux1 = (EE_UREG)EE_st10_thread_cp[t];
  EE_aux2 = (EE_UREG)EE_hal_thread_body[t];
#endif
} 



// - This function is called when a task has finished an instance, and
// a preempted thread (whose stack frame is already on the top of the
// system stack) is reactivated - there is no need to save and reload
// the user stack pointer because if an instance of the function is
// finished the user stack used by this function is clean!

/* This function is used by EE_hal_IRQ_stacked and by EE_hal_endcycle_stacked */
__INLINE__ void __ALWAYS_INLINE__ EE_st10_endcycle_stacked(void)
// The t parameter is ignored. Introduced only for interface compatibility
{
#ifdef __ST10_OPTIMIZED__
  #pragma asm()
	POP CP				; reload R0-R15

	POP MDH				; reload multiply registers
	POP MDL
	POP MDC

	RETI				; and wake up the thread!!!
  #pragma endasm()
#else
  EE_aux1 = 0;
#endif
}

#endif /* __MONO__ */

#ifdef __MULTI__

/* These functions are implemented in assembly */
void EE_st10_ready2stacked   (EE_UINT16 currtos, EE_UINT16 newtos, EE_ADDR cp, EE_ADDR body);
void EE_st10_endcycle_ready  (EE_UINT16 currtos, EE_UINT16 newtos, EE_ADDR cp, EE_ADDR body);
void EE_st10_endcycle_stacked(EE_UINT16 currtos, EE_UINT16 newtos);
void EE_st10_IRQ_ready       (EE_UINT16 newtos, EE_ADDR cp, EE_ADDR body);
void EE_st10_IRQ_stacked     (EE_UINT16 newtos);
void EE_st10_stkchange       (EE_UINT16 currtos, EE_UINT16 newtos);	 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  EE_st10_endcycle_ready(EE_hal_active_tos, 
                      EE_st10_thread_tos[t+1],     // thread_tos[0] is reserved for the main!!!
                      EE_st10_thread_cp[t], 
                      EE_hal_thread_body[t]);
#else
  EE_aux1 = (EE_UREG)EE_hal_active_tos;
  EE_aux2 = (EE_UREG)EE_st10_thread_tos[t+1];
  EE_aux3 = (EE_UREG)EE_st10_thread_cp[t];
  EE_aux4 = (EE_UREG)EE_hal_thread_body[t];
#endif
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  EE_st10_endcycle_stacked(EE_hal_active_tos,	 	 
  			EE_st10_thread_tos[t+1]);  // thread_tos[0] is reserved for the main!!!
#else
  EE_aux1 = (EE_UREG)EE_hal_active_tos;
  EE_aux2 = (EE_UREG)EE_st10_thread_tos[t+1];
  EE_aux4 = 0;
#endif
}	 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID t)
{
  EE_st10_ready2stacked(EE_hal_active_tos,
                     EE_st10_thread_tos[t+1],    // thread_tos[0] is reserved for the main!!!
		     EE_st10_thread_cp[t],
		     EE_hal_thread_body[t]);
} 


__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  EE_st10_IRQ_ready(EE_st10_thread_tos[t+1],          // thread_tos[0] is reserved for the main!!!
		 EE_st10_thread_cp[t],
		 EE_hal_thread_body[t]);
#else
  EE_aux2 = (EE_UREG)EE_st10_thread_tos[t+1];
  EE_aux3 = (EE_UREG)EE_st10_thread_cp[t];
  EE_aux4 = (EE_UREG)EE_hal_thread_body[t];
#endif
} 


__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  EE_st10_IRQ_stacked(EE_st10_thread_tos[t+1]);       // thread_tos[0] is reserved for the main!!!
#else
  EE_aux2 = (EE_UREG)EE_st10_thread_tos[t+1];
  EE_aux4 = 0;
#endif
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID t)
{
  EE_st10_stkchange(EE_hal_active_tos,	 	 
                 EE_st10_thread_tos[t+1]);	 
}

#endif /* __MULTI__ */


#ifdef __MONO__
  #define EE_hal_endcycle_stacked(x) EE_st10_endcycle_stacked()

  #define EE_hal_IRQ_stacked(x) EE_st10_endcycle_stacked()
#else
  __INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked  (EE_TID t);
  __INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked       (EE_TID t);

  /* called to change the active stack, typically used with locking semaphores */
  __INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange         (EE_TID t);
#endif


/*
 * Nested Interrupts Handling
 */

/* can be called with interrupt enabled */
#ifdef __ALLOW_NESTED_IRQ__
/* Note: EE_IRQ_nesting_level is defined into src/st10mono/main.c */
/* can be called with interrupt enabled */
extern EE_UREG EE_IRQ_nesting_level;

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
  return EE_IRQ_nesting_level;
}
#endif


/* 
 * OO related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* we have only to save SP and R0, because
   - The other registers are no more used (see tstub.c)
   - we used a CP bank for each task that can preempt another one
   - DPPx (I hope) do not need to be saved
*/

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{
  register EE_UINT16 t1, t2;

  #pragma asm
    MOV @w1, SP
    MOV @w2, R0
  #pragma endasm(t1=@w1, t2=@w2)
  
  EE_terminate_data_sys[t]= t1-2; /* to save the right SP */
  EE_terminate_data_usr[t]= t2;

  ((void (*)(void))EE_terminate_real_th_body[t])();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
  register EE_UINT16 t1, t2;

  t1 = EE_terminate_data_sys[t];
  t2 = EE_terminate_data_usr[t];

  #pragma asm(@w1=t1, @w2=t2)
    MOV SP, @w1
    MOV R0, @w2
    RET
  #pragma endasm()
}

#endif

/* 
 * Hard timers related stuffs
 */
#ifdef __HARD_ALARMS__

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_read_timer (EE_SREG timer)
{
  if (timer & 0xF0)
    /* second timer group, linked to T7 */
    return *(EE_UREG *)0xF050;
  else
    /* first timer group, linked to T0 */
    return *(EE_UREG *)0xFE50;
}

/* This function have to set next capcom trigger
 * if there isn't an already set interrupt flag
 */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_timer (EE_SREG timer, EE_UREG value)
{
  register EE_UREG inf, sup;
  
  if (timer & 0xF0)
  { /* second timer group, linked to T7 
     */
    if ((*(EE_UREG *)(0xF160 + (timer << 1)) & 0x0080) == 0x0080)
      /* There is a raised interrupt flag 
       */
      return; 
  
    /* the value 25 is the estimated maximum time
     * to execute the EE_hal_set_timer function 
     */
    inf = *(EE_UREG *)0xF050 - 25;
    sup = *(EE_UREG *)0xF050 + 25;
    if (inf < sup)
      if ((value > sup) || (value < inf))
        *(EE_UREG *)(0xFE60 + (timer << 1)) =  value;
      else
        *(EE_UREG *)(0xFE60 + (timer << 1)) =  sup;  
    else
      if ((value > sup) && (value < inf))
        *(EE_UREG *)(0xFE60 + (timer << 1)) =  value;
      else
        *(EE_UREG *)(0xFE60 + (timer << 1)) =  sup;  
      
    /* enable interrupt and reset interrupt request flag 
     */
    *(EE_UREG *)(0xF160 + (timer << 1)) |= 0x0040;
    *(EE_UREG *)(0xF160 + (timer << 1)) &= 0xFF7F;
  } 
  else
  { /* second timer group, linked to T0 
     */
    if ((*(EE_UREG *)(0xFF78 + (timer << 1)) & 0x0080) == 0x0080)
      /* There is a raised interrupt flag 
       */
      return; 
  
    /* the value 25 is the estimated maximum time
     * to execute the EE_hal_set_timer function 
     */
    inf = *(EE_UREG *)0xFE50 - 25;
    sup = *(EE_UREG *)0xFE50 + 25;
    if (inf < sup)
      if ((value > sup) || (value < inf))
        *(EE_UREG *)(0xFE80 + (timer << 1)) =  value;
      else
        *(EE_UREG *)(0xFE80 + (timer << 1)) =  sup;  
    else
      if ((value > sup) && (value < inf))
        *(EE_UREG *)(0xFE80 + (timer << 1)) =  value;
      else
        *(EE_UREG *)(0xFE80 + (timer << 1)) =  sup;  
      
    /* enable interrupt and reset interrupt request flag 
     */
    *(EE_UREG *)(0xFF78 + (timer << 1)) |= 0x0040;
    *(EE_UREG *)(0xFF78 + (timer << 1)) &= 0xFF7F;
  } 
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_timer (EE_SREG timer)
{
  if (timer & 0xF0)
  { /* second timer group, linked to T7 */
  
    /* reset any raised interrupt and interrupt flag*/
    *(EE_UREG *)(0xF160 + (timer << 1)) &= 0xFF3F;
  } 
  else
  { /* first timer group, linked to T0 */
  
    /* reset any raised interrupt */
    *(EE_UREG *)(0xFF78 + (timer << 1)) &= 0xFF3F;
  }  
}

#endif

#endif

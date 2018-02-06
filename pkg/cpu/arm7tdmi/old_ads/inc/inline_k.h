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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: inline_k.h,v 1.6 2006/04/08 21:05:47 pj Exp $
 */

#ifndef __INCLUDE_ARM7ADS_INLINE_K_H__
#define __INCLUDE_ARM7ADS_INLINE_K_H__

#include "eecfg.h"
#include "arm7ads/arch.h"
#include "arm7ads/drivers.h"	/* timer_0_get() */
#include "arm7ads/inline_d.h"	/* timer_0_get() */



/*********************************************************************
 HAL OPTIMIZED FUNCTIONS
 *********************************************************************/

/*
 * Enable interrupts
 */
#ifdef __thumb
void EE_arm7_enableIRQ(void);
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
#ifdef __thumb
    /* if we are in thumb_mode, we have to switch to ARM-mode to use
     * MSR and MRS instructions */
    EE_arm7_enableIRQ();		/* defined in hal.s in ARM-mode */
#else
    register int temp;
    __asm{MRS temp, CPSR};
    __asm{BIC temp, temp, #0x80};
    __asm{MSR CPSR_c, temp};
#endif /* __thumb */
}



/*
 * Disable interrupts
 */
#ifdef __thumb
void EE_arm7_disableIRQ(void);
#endif
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    /* ditto */
#ifdef __thumb
    EE_arm7_disableIRQ();
#else
    register int temp;
    __asm{MRS temp, CPSR};
    __asm{ORR temp, temp, #0x80};
    __asm{MSR CPSR_c, temp};
#endif /* __thumb */
}



/*
 * Generic Primitives
 */

/*
 * NOTE: We have to disable interrupts *before* calling the primitives
 *       (that is, before saving the registers) so begin_primitive()
 *       does nothing.
 */

/* 
 * Context Handling  
 */

/* NOTE: arm7_thread_tos[0]=main, arm7_thread_tos[1]=thread0, ... */

#ifdef __MONO__
void EE_arm7_hal_ready2stacked(EE_ADDR thread_addr); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
    EE_arm7_hal_ready2stacked(EE_hal_thread_body[thread]);
}
#endif
#ifdef __MULTI__
void EE_arm7_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
    EE_arm7_hal_ready2stacked(EE_hal_thread_body[thread],
			   EE_arm7_thread_tos[thread+1]);
}
#endif



#ifdef __MONO__
void EE_arm7_hal_endcycle_stacked(void); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
    EE_arm7_hal_endcycle_stacked(); /* TID is useless */
}
#endif
#ifdef __MULTI__
void EE_arm7_hal_endcycle_stacked(EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
    EE_arm7_hal_endcycle_stacked(EE_arm7_thread_tos[thread+1]);
}
#endif



#ifdef __MONO__
void EE_arm7_hal_endcycle_ready(EE_ADDR thread_addr); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
    EE_arm7_hal_endcycle_ready(EE_hal_thread_body[thread]);
}
#endif
#ifdef __MULTI__
void EE_arm7_hal_endcycle_ready(EE_ADDR thread_addr, EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
    EE_arm7_hal_endcycle_ready(EE_hal_thread_body[thread],
			    EE_arm7_thread_tos[thread+1]);
}
#endif


#if defined (__MULTI__) || defined (__MONO__)
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID thread)
{
    /* do nothing! (return to the preempted thread) */
}
#endif



#ifdef __MONO__
void EE_arm7_hal_IRQ_ready(EE_ADDR thread_addr); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID thread)
{
    EE_arm7_hal_IRQ_ready(EE_hal_thread_body[thread]);
}
#endif
#ifdef __MULTI__
void EE_arm7_hal_IRQ_ready(EE_ADDR thread_addr, EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID thread)
{
    EE_arm7_hal_IRQ_ready(EE_hal_thread_body[thread],
		       EE_arm7_thread_tos[thread+1]);
}
#endif



/* there is no mono version for this primitive...*/
#ifdef __MULTI__
void EE_arm7_hal_stkchange(EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread)
{
    EE_arm7_hal_stkchange(EE_arm7_thread_tos[thread+1]);
}
#endif




/*
 * Time Handling
 */

#ifdef __TIME_SUPPORT__
#if defined (__MULTI__) || defined (__MONO__)
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
    return 0xffffffff - EE_timer_0_get();
}
#endif
#endif


#endif /* __INCLUDE_ARM7ADS_INLINE_K_H__ */

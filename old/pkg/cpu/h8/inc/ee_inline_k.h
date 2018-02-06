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
 * Author: 2002 Davide Cantini
 * CVS: $Id: ee_inline_k.h,v 1.6 2006/04/08 21:07:06 pj Exp $
 */

#include "eecfg.h"
#include "h8/arch.h"
#include "h8/drivers.h"

/*******************************
 * H8 hal variables declaration
 *******************************/ 

extern EE_UINT16 EE_nested_primitive_counter;
extern EE_UREG EE_IRQ_nesting_level;

/*******************************
 * H8 hal functions declaration
 *******************************/ 

/*
 * Context handling
 */

void EE_h8_hal_endcycle_ready(EE_TID t);

void EE_h8_hal_endcycle_stacked(EE_TID t);

void EE_h8_hal_ready2stacked(EE_TID t);

void EE_h8_hal_IRQ_ready(EE_TID t);

void EE_h8_hal_IRQ_stacked(EE_TID t);

#ifdef __MULTI__
    void EE_h8_hal_stkchange(EE_TID t);
#endif


/*********************
 * Inline functions
 *********************/

/*
 * Context handling
 */

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID t)
{
    EE_h8_hal_endcycle_ready(t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID t)
{
    EE_h8_hal_endcycle_stacked(t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID t)
{
    EE_h8_hal_ready2stacked(t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID t)
{
    EE_h8_hal_IRQ_ready(t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID t)
{
    EE_h8_hal_IRQ_stacked(t);
}

#ifdef __MULTI__
    __INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID t)
    {
	EE_h8_hal_stkchange(t);
    }
#endif


/*
 * Primitive definition
 */

__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
  register EE_UINT8 f;
  __asm__(".align 1");
  __asm__("stc	ccr, %0l" :  "=r"(f));
  __asm__("orc 	#0x80, ccr");
  return f;
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
  __asm__(".align 1");
  __asm__("ldc	%0l, ccr" : : "r"(f));
}


/*
 * Interrupt handling
 */

__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    /* enable IRQ (I=0) */  
    __asm__(".align 1");
    __asm__("andc #0x7F, ccr");
            
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    /* disable IRQ (I=1) */
    __asm__(".align 1");
    __asm__("orc #0x80, ccr");
            
}

/*
 * Utility function
 */

#ifdef __TIME_SUPPORT__
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
    return T16FRC;  
}
#endif

/* can be called with interrupt enabled */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
    return EE_IRQ_nesting_level;
}

/* 
 * OO related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

//void EE_h8_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
//void EE_h8_terminate_task(EE_ADDR sp);

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{	
    __asm__("mov.w	%0, r1" : : "r" (t));
    __asm__("add.w	r1, r1");
    __asm__("push	r6");
    __asm__("push	r5");    
    __asm__("push	r4");    
    __asm__("mov.w	sp, @(_EE_terminate_data, r1)");   
    __asm__("mov.w	@(_EE_terminate_real_th_body,r1), r2");
    __asm__("jmp	@r2");
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
    __asm__("mov.w	%0, r1" : : "r" (t));   
    __asm__("add.w	r1, r1");    
    __asm__("mov.w	@(_EE_terminate_data, r1), sp");
    __asm__("pop	r4");   
    __asm__("pop	r5");
    __asm__("pop	r6");    
    __asm__("jmp	@_EE_thread_end_instance");        
}

#endif

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
	@file ee_irq.h
	@brief IRQ-related stuff for Lattice Mico32; userland declarations
	@author Bernardo  Dal Seno
	@date 2009-2010
*/  

#ifndef __INCLUDE_MICO32_IRQ_H__
#define __INCLUDE_MICO32_IRQ_H__

#include <cpu/mico32/inc/ee_cpu.h>
#include <cpu/mico32/inc/ee_irq_internal.h>


#ifndef __STATIC_ISR_TABLE__

/** Register a handler with a given interrupt number; also enable the given
 * interrupt.  If `fun' is 0, disable the given interrupt.
 * When interrupt nesting is enabled, it is safe to call this function from
 * interrupt handlers only for interrupts of higher level.
 */
void EE_mico32_register_ISR(int level, EE_mico32_ISR_handler fun);

/** Unregister the IRQ handler for the given interrupt and disable the given
 * interrupt. */
__INLINE__ void EE_mico32_unregister_ISR(int level)
{
    EE_mico32_register_ISR((level), 0);
}

#endif /* __STATIC_ISR_TABLE__ */


/** Enable the interrupts specified by the `mask' parameter. */
__INLINE__ void mico32_enable_irq_mask(int mask)
{
    int im = mico32_get_reg_im();
    mico32_set_reg_im(im | mask);
}


/** Disable the interrupts specified by the `mask' parameter. */
__INLINE__ void mico32_disable_irq_mask(int mask)
{
    int im = mico32_get_reg_im();
    mico32_set_reg_im(im & ~mask);
}


/** Enable the interrupt whose number is specified by the `irq' parameter. */
__INLINE__ void __ALWAYS_INLINE__ mico32_enable_irq(int irq)
{
    mico32_enable_irq_mask(1 << irq);
}


/** Disable the interrupt whose number is specified by the `irq' parameter. */
__INLINE__ void __ALWAYS_INLINE__ mico32_disable_irq(int irq)
{
    mico32_disable_irq_mask(1 << irq);
}


#endif /*  __INCLUDE_MICO32_IRQ_H__ */

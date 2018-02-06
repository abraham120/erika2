/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, TU Dortmund University, Faculty of Computer Science 12
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

/* Author: Jan C. Kleinsorge, TU Dortmund University, 2010-
 *
 */
#ifndef __INLCUDE_TRICORE1_EE_PRIMITIVES_H__
#define __INLCUDE_TRICORE1_EE_PRIMITIVES_H__

// #undef DEBUG

#include "ee.h"
#include "cpu/tricore1/inc/ee_debug.h"
#include "cpu/tricore1/inc/ee_cpu.h"
#include "cpu/tricore1/inc/ee_hal.h"


/*******************************************************************************
 * Generic Primitives
 */


/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task.
 *
 * We can safely store the entire ICR. Saves us instructions here and
 * a branch in end_nested_primitive.
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
    EE_ICR icr = EE_tc1_get_ICR();
    EE_hal_disableIRQ();
    return (EE_FREG)icr.reg;
}


/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
    EE_tc1_set_ICR((EE_ICR)f);
}


/* Nested Interrupts Handling */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
    return EE_IRQ_nesting_level;
}


#endif /* __INLCUDE_TRICORE1_EE_INTERNAL_H__ */

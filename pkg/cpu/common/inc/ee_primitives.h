/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2009  Evidence Srl
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
 * Functions used in HAL implementations, to be included by a specific
 * ee_internal.h header.
 * Derived from pkg/cpu/pic30/inc/ee_internal.h
 * Author: 2009 Bernardo Dal Seno
 */


#ifndef PKG_CPU_COMMON_INC_EE_PRIMITIVES_H
#define PKG_CPU_COMMON_INC_EE_PRIMITIVES_H

/*
 * Nested Interrupts Handling
 */

/* If MemMap.h support is enabled (i.e. because memory protection): use it */
#ifdef EE_SUPPORT_MEMMAP_H
/* The following variables belong to ERIKA OS section: ee_kernel_bss */
#define OS_START_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

extern EE_UREG EE_IRQ_nesting_level;

/* If MemMap.h support is enabled (i.e. because memory protection): use it */
#ifdef EE_SUPPORT_MEMMAP_H
#define OS_STOP_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

/* can be called with interrupt enabled */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
    return EE_IRQ_nesting_level;
}


#endif /* PKG_CPU_COMMON_INC_EE_PRIMITIVES_H */

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

/*
 * CPU-dependent part of HAL; defines used both by C and assembly
 * Author: 2011 Bernardo  Dal Seno
 */

#ifndef PKG_CPU_E200ZX_INC_EE_CPU_ASM_H
#define PKG_CPU_E200ZX_INC_EE_CPU_ASM_H

/* Needed for EE_SYS_STACK_SIZE */
#include "eecfg.h"

/* Stack alignment and default size */
#define EE_STACK_ALIGN 16
#ifndef EE_SYS_STACK_SIZE
#define EE_SYS_STACK_SIZE	512
#endif

/* Number of CPU exceptions */
#define EE_E200ZX_MAX_CPU_EXCP 16
#define EE_E200ZX_MAX_CPU_EXCP_C 16U

/* TCR register bits */
#define TCR_DIE		26
#define TCR_FIE		23
#define TCR_ARE		22
#define TCR_FP		24
#define TCR_FPEXT	13
#define TCR_FPALL_MASK	(((EE_UREG)0x3 << TCR_FP) | ((EE_UREG)0xf << TCR_FPEXT))

/* TSR register bits */
#define TSR_DIS		27
#define TSR_FIS		26

/* HID0 register bits */
#define HID0_TBEN	14

#endif /* __INCLUDE_E200ZX_EE_CPU_ASM_H__ */

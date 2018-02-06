/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * MCU register map
 * Author: 2011 Bernardo  Dal Seno
 *         2012 Francesco Esposito
 *         2013 Eugen Kleinschmidt
 */

#ifndef PKG_CPU_E200ZX_INC_EE_MCU_REGS_ASM_H
#define PKG_CPU_E200ZX_INC_EE_MCU_REGS_ASM_H

/* Include the appropriate file according to the target MCU */

/* This file should be used only for Assembly.  For C, "ee_mcu_regs.h" is a
 * better choice */

#ifdef __MPC5668__
#include <mcu/freescale_mpc5668/inc/ee_regs_asm.h>
#elif defined __MPC5674F__
#include <mcu/freescale_mpc5674f/inc/ee_regs_asm.h>
#elif defined EE_MPC5643L
#include <mcu/freescale_mpc5643l/inc/ee_regs_asm.h>
#elif defined EE_MPC5644A
#include <mcu/freescale_mpc5644a/inc/ee_regs_asm.h>
#else
#error "No known MCU found"
#endif

#endif /* EE_E200ZX_MCU_REGS_ASM_H */

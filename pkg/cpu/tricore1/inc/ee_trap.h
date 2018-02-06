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
#ifndef __INCLUDE_TRICORE1_EE_TRAP_H__
#define __INCLUDE_TRICORE1_EE_TRAP_H__

#include "ee_compiler.h"


/* Number of entries within trap table */
#define EE_MAX_TSR 8

#ifndef  __EECFG_THIS_IS_ASSEMBLER__

#include "cpu/tricore1/inc/ee_debug.h"

/* Initialization routine */
void EE_init_trap_vector(void);

/* Define a trap handler */
#define TSR(fn) __attribute__((interrupt)) \
    void EE_tsr_ ## fn (EE_TIN EE_tin)


/* Set a trap handler */
#define SetTSR(fn,t) \
    do { EE_tsr_table[t] = EE_tsr_ ## fn; } while(0)


/* Trap vector initialization */
#define EE_TSR_DEFAULT EE_trap_default_tsr


/* Trap Identification Number */
typedef EE_UINT8 EE_TIN;


/* Trap handler */
typedef void (*EE_TSR)(EE_TIN);


#endif /* __EECFG_THIS_IS_ASSEMBLER__ */

#endif /* __INCLUDE_TRICORE1_EE_TRAP_H__ */

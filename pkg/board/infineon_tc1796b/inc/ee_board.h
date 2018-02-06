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
#ifndef __INCLUDE_EE_BOARD_TC1796_H__
#define __INCLUDE_EE_BOARD_TC1796_H__


/*** Setup below runs the CPU in PLL mode at 150MHz. ***/


/* TriBoard 1796 default clock frequency (20MHz) */
#define EE_TRIBOARD1796_OSC_FREQ_HZ 20000000


/* Errata sheet: PLL_TC.H005
 *
 * The PLL robustness to system noise on the PLL supply voltage can be
 * improved significantly by increasing NDIV to a value greater than
 * NDIV = 32.
 * 
 * In PLL mode (set by EE_tc179x_init_clock), the CPU frequency is:
 * CPU_f = N / (P * K)  [N = 19..99, P = 0..7, K = 0..15]
 * (Refer to the manual)
 *
 * System frequency accordingly: 
 * SYS_f = CPU_f / (PLL_CLC.SYSFS + 1) [SYSFS = 0,1]
 *
 * System timer frequency accordingly:
 * STM_f = SYS_f / STM_CLC.RMC [RMC = 1..7; 0 means 'off']
 */

/* PLL K Divisor */
#define EE_TRIBOARD1796_PLL_KDIV 6

/* PLL N Divisor */
#define EE_TRIBOARD1796_PLL_NDIV 45

/* PLL P Divisor */
#define EE_TRIBOARD1796_PLL_PDIV 1

/* VCO Operating range */
#define EE_TRIBOARD1796_PLL_VCOSEL 2


#endif

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013 Bruno Morelli
 */

#ifndef EE_GIC_PRIO_TABLE_H__
#define EE_GIC_PRIO_TABLE_H__

#define EE_GIC_PRIO_LEVELS       256
/*
 * GIC can have 256, 128, 64, 32 or 16
 * differents interrupts priority levels.
 * All cortex-aX based mcu supports at least 16
 * priority levels, so we use the conservative 16 priority levels.
 * (0 is the higher priority) */
#define EE_GIC_PRIO_STEPS        (EE_GIC_PRIO_LEVELS >> 4)
#define EE_GIC_MIN_PRIO          (EE_GIC_PRIO_LEVELS - EE_GIC_PRIO_STEPS)
#define EE_GIC_MAX_PRIO          0
#define EE_GIC_ISR2_MIN_PRIO     (EE_GIC_MIN_PRIO)
#define EE_GIC_ISR2_MAX_PRIO     (EE_GIC_PRIO_LEVELS / 2)
#define EE_GIC_ISR1_MIN_PRIO     (EE_GIC_ISR2_MAX_PRIO - (EE_GIC_PRIO_STEPS))
#define EE_GIC_ISR1_MAX_PRIO     EE_GIC_MAX_PRIO

#define EE_CAX_ISR1_INT_PRI(x)   (EE_GIC_ISR1_MIN_PRIO - (x * EE_GIC_PRIO_STEPS))
#define EE_CAX_ISR2_INT_PRI(x)   (EE_GIC_ISR2_MIN_PRIO - (x * EE_GIC_PRIO_STEPS))

#define EE_CAX_BOUNDS(x,l,u)     ((x < l) ? l : (x > u) ? u : x)

#include "cpu/cortex_ax_xenpv/src/gic_internal_prio_map.h"

#if 0
#define EE_CAX_ISR1_PRI(x) ((EE_CAX_ISR1_INT_PRI(x) < EE_GIC_ISR1_MAX_PRIO) ? EE_GIC_ISR1_MAX_PRIO : ((EE_CAX_ISR1_INT_PRI(x) > EE_GIC_ISR1_MIN_PRIO) ? EE_GIC_ISR1_MIN_PRIO : EE_CAX_ISR1_INT_PRI(x)))

#define EE_CAX_ISR2_PRI(x) ((EE_CAX_ISR2_INT_PRI(x) < EE_GIC_ISR2_MAX_PRIO) ? EE_GIC_ISR2_MAX_PRIO : ((EE_CAX_ISR2_INT_PRI(x) > EE_GIC_ISR2_MIN_PRIO) ? EE_GIC_ISR2_MIN_PRIO : EE_CAX_ISR2_INT_PRI(x)))
#endif

#define EE_CAX_ISR1_PRI(x) EE_CAX_BOUNDS(EE_CAX_ISR1_INT_PRI(x),EE_GIC_ISR1_MAX_PRIO,EE_GIC_ISR1_MIN_PRIO)
#define EE_CAX_ISR2_PRI(x) EE_CAX_BOUNDS(EE_CAX_ISR2_INT_PRI(x),EE_GIC_ISR2_MAX_PRIO,EE_GIC_ISR2_MIN_PRIO)

struct {
  unsigned int intID;
  unsigned char prio;
} ip_table[] = {
#if (defined(EE_CAX_0_ISR) && (EE_CAX_MAX_ISR_ID >= 0) && (EE_CAX_MAX_ARCH_ISR_ID >= 0))
#if (EE_CAX_0_ISR_CAT == 2)
 { 0, EE_CAX_ISR2_PRI(EE_CAX_0_ISR_PRI) },
#else
 { 0, EE_CAX_ISR1_PRI(EE_CAX_0_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1_ISR) && (EE_CAX_MAX_ISR_ID >= 1) && (EE_CAX_MAX_ARCH_ISR_ID >= 1))
#if (EE_CAX_1_ISR_CAT == 2)
 { 1, EE_CAX_ISR2_PRI(EE_CAX_1_ISR_PRI) },
#else
 { 1, EE_CAX_ISR1_PRI(EE_CAX_1_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_2_ISR) && (EE_CAX_MAX_ISR_ID >= 2) && (EE_CAX_MAX_ARCH_ISR_ID >= 2))
#if (EE_CAX_2_ISR_CAT == 2)
 { 2, EE_CAX_ISR2_PRI(EE_CAX_2_ISR_PRI) },
#else
 { 2, EE_CAX_ISR1_PRI(EE_CAX_2_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_3_ISR) && (EE_CAX_MAX_ISR_ID >= 3) && (EE_CAX_MAX_ARCH_ISR_ID >= 3))
#if (EE_CAX_3_ISR_CAT == 2)
 { 3, EE_CAX_ISR2_PRI(EE_CAX_3_ISR_PRI) },
#else
 { 3, EE_CAX_ISR1_PRI(EE_CAX_3_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_4_ISR) && (EE_CAX_MAX_ISR_ID >= 4) && (EE_CAX_MAX_ARCH_ISR_ID >= 4))
#if (EE_CAX_4_ISR_CAT == 2)
 { 4, EE_CAX_ISR2_PRI(EE_CAX_4_ISR_PRI) },
#else
 { 4, EE_CAX_ISR1_PRI(EE_CAX_4_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_5_ISR) && (EE_CAX_MAX_ISR_ID >= 5) && (EE_CAX_MAX_ARCH_ISR_ID >= 5))
#if (EE_CAX_5_ISR_CAT == 2)
 { 5, EE_CAX_ISR2_PRI(EE_CAX_5_ISR_PRI) },
#else
 { 5, EE_CAX_ISR1_PRI(EE_CAX_5_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_6_ISR) && (EE_CAX_MAX_ISR_ID >= 6) && (EE_CAX_MAX_ARCH_ISR_ID >= 6))
#if (EE_CAX_6_ISR_CAT == 2)
 { 6, EE_CAX_ISR2_PRI(EE_CAX_6_ISR_PRI) },
#else
 { 6, EE_CAX_ISR1_PRI(EE_CAX_6_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_7_ISR) && (EE_CAX_MAX_ISR_ID >= 7) && (EE_CAX_MAX_ARCH_ISR_ID >= 7))
#if (EE_CAX_7_ISR_CAT == 2)
 { 7, EE_CAX_ISR2_PRI(EE_CAX_7_ISR_PRI) },
#else
 { 7, EE_CAX_ISR1_PRI(EE_CAX_7_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_8_ISR) && (EE_CAX_MAX_ISR_ID >= 8) && (EE_CAX_MAX_ARCH_ISR_ID >= 8))
#if (EE_CAX_8_ISR_CAT == 2)
 { 8, EE_CAX_ISR2_PRI(EE_CAX_8_ISR_PRI) },
#else
 { 8, EE_CAX_ISR1_PRI(EE_CAX_8_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_9_ISR) && (EE_CAX_MAX_ISR_ID >= 9) && (EE_CAX_MAX_ARCH_ISR_ID >= 9))
#if (EE_CAX_9_ISR_CAT == 2)
 { 9, EE_CAX_ISR2_PRI(EE_CAX_9_ISR_PRI) },
#else
 { 9, EE_CAX_ISR1_PRI(EE_CAX_9_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_10_ISR) && (EE_CAX_MAX_ISR_ID >= 10) && (EE_CAX_MAX_ARCH_ISR_ID >= 10))
#if (EE_CAX_10_ISR_CAT == 2)
 { 10, EE_CAX_ISR2_PRI(EE_CAX_10_ISR_PRI) },
#else
 { 10, EE_CAX_ISR1_PRI(EE_CAX_10_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_11_ISR) && (EE_CAX_MAX_ISR_ID >= 11) && (EE_CAX_MAX_ARCH_ISR_ID >= 11))
#if (EE_CAX_11_ISR_CAT == 2)
 { 11, EE_CAX_ISR2_PRI(EE_CAX_11_ISR_PRI) },
#else
 { 11, EE_CAX_ISR1_PRI(EE_CAX_11_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_12_ISR) && (EE_CAX_MAX_ISR_ID >= 12) && (EE_CAX_MAX_ARCH_ISR_ID >= 12))
#if (EE_CAX_12_ISR_CAT == 2)
 { 12, EE_CAX_ISR2_PRI(EE_CAX_12_ISR_PRI) },
#else
 { 12, EE_CAX_ISR1_PRI(EE_CAX_12_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_13_ISR) && (EE_CAX_MAX_ISR_ID >= 13) && (EE_CAX_MAX_ARCH_ISR_ID >= 13))
#if (EE_CAX_13_ISR_CAT == 2)
 { 13, EE_CAX_ISR2_PRI(EE_CAX_13_ISR_PRI) },
#else
 { 13, EE_CAX_ISR1_PRI(EE_CAX_13_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_14_ISR) && (EE_CAX_MAX_ISR_ID >= 14) && (EE_CAX_MAX_ARCH_ISR_ID >= 14))
#if (EE_CAX_14_ISR_CAT == 2)
 { 14, EE_CAX_ISR2_PRI(EE_CAX_14_ISR_PRI) },
#else
 { 14, EE_CAX_ISR1_PRI(EE_CAX_14_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_15_ISR) && (EE_CAX_MAX_ISR_ID >= 15) && (EE_CAX_MAX_ARCH_ISR_ID >= 15))
#if (EE_CAX_15_ISR_CAT == 2)
 { 15, EE_CAX_ISR2_PRI(EE_CAX_15_ISR_PRI) },
#else
 { 15, EE_CAX_ISR1_PRI(EE_CAX_15_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_16_ISR) && (EE_CAX_MAX_ISR_ID >= 16) && (EE_CAX_MAX_ARCH_ISR_ID >= 16))
#if (EE_CAX_16_ISR_CAT == 2)
 { 16, EE_CAX_ISR2_PRI(EE_CAX_16_ISR_PRI) },
#else
 { 16, EE_CAX_ISR1_PRI(EE_CAX_16_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_17_ISR) && (EE_CAX_MAX_ISR_ID >= 17) && (EE_CAX_MAX_ARCH_ISR_ID >= 17))
#if (EE_CAX_17_ISR_CAT == 2)
 { 17, EE_CAX_ISR2_PRI(EE_CAX_17_ISR_PRI) },
#else
 { 17, EE_CAX_ISR1_PRI(EE_CAX_17_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_18_ISR) && (EE_CAX_MAX_ISR_ID >= 18) && (EE_CAX_MAX_ARCH_ISR_ID >= 18))
#if (EE_CAX_18_ISR_CAT == 2)
 { 18, EE_CAX_ISR2_PRI(EE_CAX_18_ISR_PRI) },
#else
 { 18, EE_CAX_ISR1_PRI(EE_CAX_18_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_19_ISR) && (EE_CAX_MAX_ISR_ID >= 19) && (EE_CAX_MAX_ARCH_ISR_ID >= 19))
#if (EE_CAX_19_ISR_CAT == 2)
 { 19, EE_CAX_ISR2_PRI(EE_CAX_19_ISR_PRI) },
#else
 { 19, EE_CAX_ISR1_PRI(EE_CAX_19_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_20_ISR) && (EE_CAX_MAX_ISR_ID >= 20) && (EE_CAX_MAX_ARCH_ISR_ID >= 20))
#if (EE_CAX_20_ISR_CAT == 2)
 { 20, EE_CAX_ISR2_PRI(EE_CAX_20_ISR_PRI) },
#else
 { 20, EE_CAX_ISR1_PRI(EE_CAX_20_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_21_ISR) && (EE_CAX_MAX_ISR_ID >= 21) && (EE_CAX_MAX_ARCH_ISR_ID >= 21))
#if (EE_CAX_21_ISR_CAT == 2)
 { 21, EE_CAX_ISR2_PRI(EE_CAX_21_ISR_PRI) },
#else
 { 21, EE_CAX_ISR1_PRI(EE_CAX_21_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_22_ISR) && (EE_CAX_MAX_ISR_ID >= 22) && (EE_CAX_MAX_ARCH_ISR_ID >= 22))
#if (EE_CAX_22_ISR_CAT == 2)
 { 22, EE_CAX_ISR2_PRI(EE_CAX_22_ISR_PRI) },
#else
 { 22, EE_CAX_ISR1_PRI(EE_CAX_22_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_23_ISR) && (EE_CAX_MAX_ISR_ID >= 23) && (EE_CAX_MAX_ARCH_ISR_ID >= 23))
#if (EE_CAX_23_ISR_CAT == 2)
 { 23, EE_CAX_ISR2_PRI(EE_CAX_23_ISR_PRI) },
#else
 { 23, EE_CAX_ISR1_PRI(EE_CAX_23_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_24_ISR) && (EE_CAX_MAX_ISR_ID >= 24) && (EE_CAX_MAX_ARCH_ISR_ID >= 24))
#if (EE_CAX_24_ISR_CAT == 2)
 { 24, EE_CAX_ISR2_PRI(EE_CAX_24_ISR_PRI) },
#else
 { 24, EE_CAX_ISR1_PRI(EE_CAX_24_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_25_ISR) && (EE_CAX_MAX_ISR_ID >= 25) && (EE_CAX_MAX_ARCH_ISR_ID >= 25))
#if (EE_CAX_25_ISR_CAT == 2)
 { 25, EE_CAX_ISR2_PRI(EE_CAX_25_ISR_PRI) },
#else
 { 25, EE_CAX_ISR1_PRI(EE_CAX_25_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_26_ISR) && (EE_CAX_MAX_ISR_ID >= 26) && (EE_CAX_MAX_ARCH_ISR_ID >= 26))
#if (EE_CAX_26_ISR_CAT == 2)
 { 26, EE_CAX_ISR2_PRI(EE_CAX_26_ISR_PRI) },
#else
 { 26, EE_CAX_ISR1_PRI(EE_CAX_26_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_27_ISR) && (EE_CAX_MAX_ISR_ID >= 27) && (EE_CAX_MAX_ARCH_ISR_ID >= 27))
#if (EE_CAX_27_ISR_CAT == 2)
 { 27, EE_CAX_ISR2_PRI(EE_CAX_27_ISR_PRI) },
#else
 { 27, EE_CAX_ISR1_PRI(EE_CAX_27_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_28_ISR) && (EE_CAX_MAX_ISR_ID >= 28) && (EE_CAX_MAX_ARCH_ISR_ID >= 28))
#if (EE_CAX_28_ISR_CAT == 2)
 { 28, EE_CAX_ISR2_PRI(EE_CAX_28_ISR_PRI) },
#else
 { 28, EE_CAX_ISR1_PRI(EE_CAX_28_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_29_ISR) && (EE_CAX_MAX_ISR_ID >= 29) && (EE_CAX_MAX_ARCH_ISR_ID >= 29))
#if (EE_CAX_29_ISR_CAT == 2)
 { 29, EE_CAX_ISR2_PRI(EE_CAX_29_ISR_PRI) },
#else
 { 29, EE_CAX_ISR1_PRI(EE_CAX_29_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_30_ISR) && (EE_CAX_MAX_ISR_ID >= 30) && (EE_CAX_MAX_ARCH_ISR_ID >= 30))
#if (EE_CAX_30_ISR_CAT == 2)
 { 30, EE_CAX_ISR2_PRI(EE_CAX_30_ISR_PRI) },
#else
 { 30, EE_CAX_ISR1_PRI(EE_CAX_30_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_31_ISR) && (EE_CAX_MAX_ISR_ID >= 31) && (EE_CAX_MAX_ARCH_ISR_ID >= 31))
#if (EE_CAX_31_ISR_CAT == 2)
 { 31, EE_CAX_ISR2_PRI(EE_CAX_31_ISR_PRI) },
#else
 { 31, EE_CAX_ISR1_PRI(EE_CAX_31_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_32_ISR) && (EE_CAX_MAX_ISR_ID >= 32) && (EE_CAX_MAX_ARCH_ISR_ID >= 32))
#if (EE_CAX_32_ISR_CAT == 2)
 { 32, EE_CAX_ISR2_PRI(EE_CAX_32_ISR_PRI) },
#else
 { 32, EE_CAX_ISR1_PRI(EE_CAX_32_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_33_ISR) && (EE_CAX_MAX_ISR_ID >= 33) && (EE_CAX_MAX_ARCH_ISR_ID >= 33))
#if (EE_CAX_33_ISR_CAT == 2)
 { 33, EE_CAX_ISR2_PRI(EE_CAX_33_ISR_PRI) },
#else
 { 33, EE_CAX_ISR1_PRI(EE_CAX_33_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_34_ISR) && (EE_CAX_MAX_ISR_ID >= 34) && (EE_CAX_MAX_ARCH_ISR_ID >= 34))
#if (EE_CAX_34_ISR_CAT == 2)
 { 34, EE_CAX_ISR2_PRI(EE_CAX_34_ISR_PRI) },
#else
 { 34, EE_CAX_ISR1_PRI(EE_CAX_34_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_35_ISR) && (EE_CAX_MAX_ISR_ID >= 35) && (EE_CAX_MAX_ARCH_ISR_ID >= 35))
#if (EE_CAX_35_ISR_CAT == 2)
 { 35, EE_CAX_ISR2_PRI(EE_CAX_35_ISR_PRI) },
#else
 { 35, EE_CAX_ISR1_PRI(EE_CAX_35_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_36_ISR) && (EE_CAX_MAX_ISR_ID >= 36) && (EE_CAX_MAX_ARCH_ISR_ID >= 36))
#if (EE_CAX_36_ISR_CAT == 2)
 { 36, EE_CAX_ISR2_PRI(EE_CAX_36_ISR_PRI) },
#else
 { 36, EE_CAX_ISR1_PRI(EE_CAX_36_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_37_ISR) && (EE_CAX_MAX_ISR_ID >= 37) && (EE_CAX_MAX_ARCH_ISR_ID >= 37))
#if (EE_CAX_37_ISR_CAT == 2)
 { 37, EE_CAX_ISR2_PRI(EE_CAX_37_ISR_PRI) },
#else
 { 37, EE_CAX_ISR1_PRI(EE_CAX_37_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_38_ISR) && (EE_CAX_MAX_ISR_ID >= 38) && (EE_CAX_MAX_ARCH_ISR_ID >= 38))
#if (EE_CAX_38_ISR_CAT == 2)
 { 38, EE_CAX_ISR2_PRI(EE_CAX_38_ISR_PRI) },
#else
 { 38, EE_CAX_ISR1_PRI(EE_CAX_38_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_39_ISR) && (EE_CAX_MAX_ISR_ID >= 39) && (EE_CAX_MAX_ARCH_ISR_ID >= 39))
#if (EE_CAX_39_ISR_CAT == 2)
 { 39, EE_CAX_ISR2_PRI(EE_CAX_39_ISR_PRI) },
#else
 { 39, EE_CAX_ISR1_PRI(EE_CAX_39_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_40_ISR) && (EE_CAX_MAX_ISR_ID >= 40) && (EE_CAX_MAX_ARCH_ISR_ID >= 40))
#if (EE_CAX_40_ISR_CAT == 2)
 { 40, EE_CAX_ISR2_PRI(EE_CAX_40_ISR_PRI) },
#else
 { 40, EE_CAX_ISR1_PRI(EE_CAX_40_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_41_ISR) && (EE_CAX_MAX_ISR_ID >= 41) && (EE_CAX_MAX_ARCH_ISR_ID >= 41))
#if (EE_CAX_41_ISR_CAT == 2)
 { 41, EE_CAX_ISR2_PRI(EE_CAX_41_ISR_PRI) },
#else
 { 41, EE_CAX_ISR1_PRI(EE_CAX_41_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_42_ISR) && (EE_CAX_MAX_ISR_ID >= 42) && (EE_CAX_MAX_ARCH_ISR_ID >= 42))
#if (EE_CAX_42_ISR_CAT == 2)
 { 42, EE_CAX_ISR2_PRI(EE_CAX_42_ISR_PRI) },
#else
 { 42, EE_CAX_ISR1_PRI(EE_CAX_42_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_43_ISR) && (EE_CAX_MAX_ISR_ID >= 43) && (EE_CAX_MAX_ARCH_ISR_ID >= 43))
#if (EE_CAX_43_ISR_CAT == 2)
 { 43, EE_CAX_ISR2_PRI(EE_CAX_43_ISR_PRI) },
#else
 { 43, EE_CAX_ISR1_PRI(EE_CAX_43_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_44_ISR) && (EE_CAX_MAX_ISR_ID >= 44) && (EE_CAX_MAX_ARCH_ISR_ID >= 44))
#if (EE_CAX_44_ISR_CAT == 2)
 { 44, EE_CAX_ISR2_PRI(EE_CAX_44_ISR_PRI) },
#else
 { 44, EE_CAX_ISR1_PRI(EE_CAX_44_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_45_ISR) && (EE_CAX_MAX_ISR_ID >= 45) && (EE_CAX_MAX_ARCH_ISR_ID >= 45))
#if (EE_CAX_45_ISR_CAT == 2)
 { 45, EE_CAX_ISR2_PRI(EE_CAX_45_ISR_PRI) },
#else
 { 45, EE_CAX_ISR1_PRI(EE_CAX_45_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_46_ISR) && (EE_CAX_MAX_ISR_ID >= 46) && (EE_CAX_MAX_ARCH_ISR_ID >= 46))
#if (EE_CAX_46_ISR_CAT == 2)
 { 46, EE_CAX_ISR2_PRI(EE_CAX_46_ISR_PRI) },
#else
 { 46, EE_CAX_ISR1_PRI(EE_CAX_46_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_47_ISR) && (EE_CAX_MAX_ISR_ID >= 47) && (EE_CAX_MAX_ARCH_ISR_ID >= 47))
#if (EE_CAX_47_ISR_CAT == 2)
 { 47, EE_CAX_ISR2_PRI(EE_CAX_47_ISR_PRI) },
#else
 { 47, EE_CAX_ISR1_PRI(EE_CAX_47_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_48_ISR) && (EE_CAX_MAX_ISR_ID >= 48) && (EE_CAX_MAX_ARCH_ISR_ID >= 48))
#if (EE_CAX_48_ISR_CAT == 2)
 { 48, EE_CAX_ISR2_PRI(EE_CAX_48_ISR_PRI) },
#else
 { 48, EE_CAX_ISR1_PRI(EE_CAX_48_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_49_ISR) && (EE_CAX_MAX_ISR_ID >= 49) && (EE_CAX_MAX_ARCH_ISR_ID >= 49))
#if (EE_CAX_49_ISR_CAT == 2)
 { 49, EE_CAX_ISR2_PRI(EE_CAX_49_ISR_PRI) },
#else
 { 49, EE_CAX_ISR1_PRI(EE_CAX_49_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_50_ISR) && (EE_CAX_MAX_ISR_ID >= 50) && (EE_CAX_MAX_ARCH_ISR_ID >= 50))
#if (EE_CAX_50_ISR_CAT == 2)
 { 50, EE_CAX_ISR2_PRI(EE_CAX_50_ISR_PRI) },
#else
 { 50, EE_CAX_ISR1_PRI(EE_CAX_50_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_51_ISR) && (EE_CAX_MAX_ISR_ID >= 51) && (EE_CAX_MAX_ARCH_ISR_ID >= 51))
#if (EE_CAX_51_ISR_CAT == 2)
 { 51, EE_CAX_ISR2_PRI(EE_CAX_51_ISR_PRI) },
#else
 { 51, EE_CAX_ISR1_PRI(EE_CAX_51_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_52_ISR) && (EE_CAX_MAX_ISR_ID >= 52) && (EE_CAX_MAX_ARCH_ISR_ID >= 52))
#if (EE_CAX_52_ISR_CAT == 2)
 { 52, EE_CAX_ISR2_PRI(EE_CAX_52_ISR_PRI) },
#else
 { 52, EE_CAX_ISR1_PRI(EE_CAX_52_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_53_ISR) && (EE_CAX_MAX_ISR_ID >= 53) && (EE_CAX_MAX_ARCH_ISR_ID >= 53))
#if (EE_CAX_53_ISR_CAT == 2)
 { 53, EE_CAX_ISR2_PRI(EE_CAX_53_ISR_PRI) },
#else
 { 53, EE_CAX_ISR1_PRI(EE_CAX_53_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_54_ISR) && (EE_CAX_MAX_ISR_ID >= 54) && (EE_CAX_MAX_ARCH_ISR_ID >= 54))
#if (EE_CAX_54_ISR_CAT == 2)
 { 54, EE_CAX_ISR2_PRI(EE_CAX_54_ISR_PRI) },
#else
 { 54, EE_CAX_ISR1_PRI(EE_CAX_54_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_55_ISR) && (EE_CAX_MAX_ISR_ID >= 55) && (EE_CAX_MAX_ARCH_ISR_ID >= 55))
#if (EE_CAX_55_ISR_CAT == 2)
 { 55, EE_CAX_ISR2_PRI(EE_CAX_55_ISR_PRI) },
#else
 { 55, EE_CAX_ISR1_PRI(EE_CAX_55_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_56_ISR) && (EE_CAX_MAX_ISR_ID >= 56) && (EE_CAX_MAX_ARCH_ISR_ID >= 56))
#if (EE_CAX_56_ISR_CAT == 2)
 { 56, EE_CAX_ISR2_PRI(EE_CAX_56_ISR_PRI) },
#else
 { 56, EE_CAX_ISR1_PRI(EE_CAX_56_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_57_ISR) && (EE_CAX_MAX_ISR_ID >= 57) && (EE_CAX_MAX_ARCH_ISR_ID >= 57))
#if (EE_CAX_57_ISR_CAT == 2)
 { 57, EE_CAX_ISR2_PRI(EE_CAX_57_ISR_PRI) },
#else
 { 57, EE_CAX_ISR1_PRI(EE_CAX_57_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_58_ISR) && (EE_CAX_MAX_ISR_ID >= 58) && (EE_CAX_MAX_ARCH_ISR_ID >= 58))
#if (EE_CAX_58_ISR_CAT == 2)
 { 58, EE_CAX_ISR2_PRI(EE_CAX_58_ISR_PRI) },
#else
 { 58, EE_CAX_ISR1_PRI(EE_CAX_58_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_59_ISR) && (EE_CAX_MAX_ISR_ID >= 59) && (EE_CAX_MAX_ARCH_ISR_ID >= 59))
#if (EE_CAX_59_ISR_CAT == 2)
 { 59, EE_CAX_ISR2_PRI(EE_CAX_59_ISR_PRI) },
#else
 { 59, EE_CAX_ISR1_PRI(EE_CAX_59_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_60_ISR) && (EE_CAX_MAX_ISR_ID >= 60) && (EE_CAX_MAX_ARCH_ISR_ID >= 60))
#if (EE_CAX_60_ISR_CAT == 2)
 { 60, EE_CAX_ISR2_PRI(EE_CAX_60_ISR_PRI) },
#else
 { 60, EE_CAX_ISR1_PRI(EE_CAX_60_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_61_ISR) && (EE_CAX_MAX_ISR_ID >= 61) && (EE_CAX_MAX_ARCH_ISR_ID >= 61))
#if (EE_CAX_61_ISR_CAT == 2)
 { 61, EE_CAX_ISR2_PRI(EE_CAX_61_ISR_PRI) },
#else
 { 61, EE_CAX_ISR1_PRI(EE_CAX_61_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_62_ISR) && (EE_CAX_MAX_ISR_ID >= 62) && (EE_CAX_MAX_ARCH_ISR_ID >= 62))
#if (EE_CAX_62_ISR_CAT == 2)
 { 62, EE_CAX_ISR2_PRI(EE_CAX_62_ISR_PRI) },
#else
 { 62, EE_CAX_ISR1_PRI(EE_CAX_62_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_63_ISR) && (EE_CAX_MAX_ISR_ID >= 63) && (EE_CAX_MAX_ARCH_ISR_ID >= 63))
#if (EE_CAX_63_ISR_CAT == 2)
 { 63, EE_CAX_ISR2_PRI(EE_CAX_63_ISR_PRI) },
#else
 { 63, EE_CAX_ISR1_PRI(EE_CAX_63_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_64_ISR) && (EE_CAX_MAX_ISR_ID >= 64) && (EE_CAX_MAX_ARCH_ISR_ID >= 64))
#if (EE_CAX_64_ISR_CAT == 2)
 { 64, EE_CAX_ISR2_PRI(EE_CAX_64_ISR_PRI) },
#else
 { 64, EE_CAX_ISR1_PRI(EE_CAX_64_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_65_ISR) && (EE_CAX_MAX_ISR_ID >= 65) && (EE_CAX_MAX_ARCH_ISR_ID >= 65))
#if (EE_CAX_65_ISR_CAT == 2)
 { 65, EE_CAX_ISR2_PRI(EE_CAX_65_ISR_PRI) },
#else
 { 65, EE_CAX_ISR1_PRI(EE_CAX_65_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_66_ISR) && (EE_CAX_MAX_ISR_ID >= 66) && (EE_CAX_MAX_ARCH_ISR_ID >= 66))
#if (EE_CAX_66_ISR_CAT == 2)
 { 66, EE_CAX_ISR2_PRI(EE_CAX_66_ISR_PRI) },
#else
 { 66, EE_CAX_ISR1_PRI(EE_CAX_66_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_67_ISR) && (EE_CAX_MAX_ISR_ID >= 67) && (EE_CAX_MAX_ARCH_ISR_ID >= 67))
#if (EE_CAX_67_ISR_CAT == 2)
 { 67, EE_CAX_ISR2_PRI(EE_CAX_67_ISR_PRI) },
#else
 { 67, EE_CAX_ISR1_PRI(EE_CAX_67_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_68_ISR) && (EE_CAX_MAX_ISR_ID >= 68) && (EE_CAX_MAX_ARCH_ISR_ID >= 68))
#if (EE_CAX_68_ISR_CAT == 2)
 { 68, EE_CAX_ISR2_PRI(EE_CAX_68_ISR_PRI) },
#else
 { 68, EE_CAX_ISR1_PRI(EE_CAX_68_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_69_ISR) && (EE_CAX_MAX_ISR_ID >= 69) && (EE_CAX_MAX_ARCH_ISR_ID >= 69))
#if (EE_CAX_69_ISR_CAT == 2)
 { 69, EE_CAX_ISR2_PRI(EE_CAX_69_ISR_PRI) },
#else
 { 69, EE_CAX_ISR1_PRI(EE_CAX_69_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_70_ISR) && (EE_CAX_MAX_ISR_ID >= 70) && (EE_CAX_MAX_ARCH_ISR_ID >= 70))
#if (EE_CAX_70_ISR_CAT == 2)
 { 70, EE_CAX_ISR2_PRI(EE_CAX_70_ISR_PRI) },
#else
 { 70, EE_CAX_ISR1_PRI(EE_CAX_70_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_71_ISR) && (EE_CAX_MAX_ISR_ID >= 71) && (EE_CAX_MAX_ARCH_ISR_ID >= 71))
#if (EE_CAX_71_ISR_CAT == 2)
 { 71, EE_CAX_ISR2_PRI(EE_CAX_71_ISR_PRI) },
#else
 { 71, EE_CAX_ISR1_PRI(EE_CAX_71_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_72_ISR) && (EE_CAX_MAX_ISR_ID >= 72) && (EE_CAX_MAX_ARCH_ISR_ID >= 72))
#if (EE_CAX_72_ISR_CAT == 2)
 { 72, EE_CAX_ISR2_PRI(EE_CAX_72_ISR_PRI) },
#else
 { 72, EE_CAX_ISR1_PRI(EE_CAX_72_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_73_ISR) && (EE_CAX_MAX_ISR_ID >= 73) && (EE_CAX_MAX_ARCH_ISR_ID >= 73))
#if (EE_CAX_73_ISR_CAT == 2)
 { 73, EE_CAX_ISR2_PRI(EE_CAX_73_ISR_PRI) },
#else
 { 73, EE_CAX_ISR1_PRI(EE_CAX_73_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_74_ISR) && (EE_CAX_MAX_ISR_ID >= 74) && (EE_CAX_MAX_ARCH_ISR_ID >= 74))
#if (EE_CAX_74_ISR_CAT == 2)
 { 74, EE_CAX_ISR2_PRI(EE_CAX_74_ISR_PRI) },
#else
 { 74, EE_CAX_ISR1_PRI(EE_CAX_74_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_75_ISR) && (EE_CAX_MAX_ISR_ID >= 75) && (EE_CAX_MAX_ARCH_ISR_ID >= 75))
#if (EE_CAX_75_ISR_CAT == 2)
 { 75, EE_CAX_ISR2_PRI(EE_CAX_75_ISR_PRI) },
#else
 { 75, EE_CAX_ISR1_PRI(EE_CAX_75_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_76_ISR) && (EE_CAX_MAX_ISR_ID >= 76) && (EE_CAX_MAX_ARCH_ISR_ID >= 76))
#if (EE_CAX_76_ISR_CAT == 2)
 { 76, EE_CAX_ISR2_PRI(EE_CAX_76_ISR_PRI) },
#else
 { 76, EE_CAX_ISR1_PRI(EE_CAX_76_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_77_ISR) && (EE_CAX_MAX_ISR_ID >= 77) && (EE_CAX_MAX_ARCH_ISR_ID >= 77))
#if (EE_CAX_77_ISR_CAT == 2)
 { 77, EE_CAX_ISR2_PRI(EE_CAX_77_ISR_PRI) },
#else
 { 77, EE_CAX_ISR1_PRI(EE_CAX_77_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_78_ISR) && (EE_CAX_MAX_ISR_ID >= 78) && (EE_CAX_MAX_ARCH_ISR_ID >= 78))
#if (EE_CAX_78_ISR_CAT == 2)
 { 78, EE_CAX_ISR2_PRI(EE_CAX_78_ISR_PRI) },
#else
 { 78, EE_CAX_ISR1_PRI(EE_CAX_78_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_79_ISR) && (EE_CAX_MAX_ISR_ID >= 79) && (EE_CAX_MAX_ARCH_ISR_ID >= 79))
#if (EE_CAX_79_ISR_CAT == 2)
 { 79, EE_CAX_ISR2_PRI(EE_CAX_79_ISR_PRI) },
#else
 { 79, EE_CAX_ISR1_PRI(EE_CAX_79_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_80_ISR) && (EE_CAX_MAX_ISR_ID >= 80) && (EE_CAX_MAX_ARCH_ISR_ID >= 80))
#if (EE_CAX_80_ISR_CAT == 2)
 { 80, EE_CAX_ISR2_PRI(EE_CAX_80_ISR_PRI) },
#else
 { 80, EE_CAX_ISR1_PRI(EE_CAX_80_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_81_ISR) && (EE_CAX_MAX_ISR_ID >= 81) && (EE_CAX_MAX_ARCH_ISR_ID >= 81))
#if (EE_CAX_81_ISR_CAT == 2)
 { 81, EE_CAX_ISR2_PRI(EE_CAX_81_ISR_PRI) },
#else
 { 81, EE_CAX_ISR1_PRI(EE_CAX_81_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_82_ISR) && (EE_CAX_MAX_ISR_ID >= 82) && (EE_CAX_MAX_ARCH_ISR_ID >= 82))
#if (EE_CAX_82_ISR_CAT == 2)
 { 82, EE_CAX_ISR2_PRI(EE_CAX_82_ISR_PRI) },
#else
 { 82, EE_CAX_ISR1_PRI(EE_CAX_82_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_83_ISR) && (EE_CAX_MAX_ISR_ID >= 83) && (EE_CAX_MAX_ARCH_ISR_ID >= 83))
#if (EE_CAX_83_ISR_CAT == 2)
 { 83, EE_CAX_ISR2_PRI(EE_CAX_83_ISR_PRI) },
#else
 { 83, EE_CAX_ISR1_PRI(EE_CAX_83_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_84_ISR) && (EE_CAX_MAX_ISR_ID >= 84) && (EE_CAX_MAX_ARCH_ISR_ID >= 84))
#if (EE_CAX_84_ISR_CAT == 2)
 { 84, EE_CAX_ISR2_PRI(EE_CAX_84_ISR_PRI) },
#else
 { 84, EE_CAX_ISR1_PRI(EE_CAX_84_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_85_ISR) && (EE_CAX_MAX_ISR_ID >= 85) && (EE_CAX_MAX_ARCH_ISR_ID >= 85))
#if (EE_CAX_85_ISR_CAT == 2)
 { 85, EE_CAX_ISR2_PRI(EE_CAX_85_ISR_PRI) },
#else
 { 85, EE_CAX_ISR1_PRI(EE_CAX_85_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_86_ISR) && (EE_CAX_MAX_ISR_ID >= 86) && (EE_CAX_MAX_ARCH_ISR_ID >= 86))
#if (EE_CAX_86_ISR_CAT == 2)
 { 86, EE_CAX_ISR2_PRI(EE_CAX_86_ISR_PRI) },
#else
 { 86, EE_CAX_ISR1_PRI(EE_CAX_86_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_87_ISR) && (EE_CAX_MAX_ISR_ID >= 87) && (EE_CAX_MAX_ARCH_ISR_ID >= 87))
#if (EE_CAX_87_ISR_CAT == 2)
 { 87, EE_CAX_ISR2_PRI(EE_CAX_87_ISR_PRI) },
#else
 { 87, EE_CAX_ISR1_PRI(EE_CAX_87_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_88_ISR) && (EE_CAX_MAX_ISR_ID >= 88) && (EE_CAX_MAX_ARCH_ISR_ID >= 88))
#if (EE_CAX_88_ISR_CAT == 2)
 { 88, EE_CAX_ISR2_PRI(EE_CAX_88_ISR_PRI) },
#else
 { 88, EE_CAX_ISR1_PRI(EE_CAX_88_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_89_ISR) && (EE_CAX_MAX_ISR_ID >= 89) && (EE_CAX_MAX_ARCH_ISR_ID >= 89))
#if (EE_CAX_89_ISR_CAT == 2)
 { 89, EE_CAX_ISR2_PRI(EE_CAX_89_ISR_PRI) },
#else
 { 89, EE_CAX_ISR1_PRI(EE_CAX_89_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_90_ISR) && (EE_CAX_MAX_ISR_ID >= 90) && (EE_CAX_MAX_ARCH_ISR_ID >= 90))
#if (EE_CAX_90_ISR_CAT == 2)
 { 90, EE_CAX_ISR2_PRI(EE_CAX_90_ISR_PRI) },
#else
 { 90, EE_CAX_ISR1_PRI(EE_CAX_90_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_91_ISR) && (EE_CAX_MAX_ISR_ID >= 91) && (EE_CAX_MAX_ARCH_ISR_ID >= 91))
#if (EE_CAX_91_ISR_CAT == 2)
 { 91, EE_CAX_ISR2_PRI(EE_CAX_91_ISR_PRI) },
#else
 { 91, EE_CAX_ISR1_PRI(EE_CAX_91_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_92_ISR) && (EE_CAX_MAX_ISR_ID >= 92) && (EE_CAX_MAX_ARCH_ISR_ID >= 92))
#if (EE_CAX_92_ISR_CAT == 2)
 { 92, EE_CAX_ISR2_PRI(EE_CAX_92_ISR_PRI) },
#else
 { 92, EE_CAX_ISR1_PRI(EE_CAX_92_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_93_ISR) && (EE_CAX_MAX_ISR_ID >= 93) && (EE_CAX_MAX_ARCH_ISR_ID >= 93))
#if (EE_CAX_93_ISR_CAT == 2)
 { 93, EE_CAX_ISR2_PRI(EE_CAX_93_ISR_PRI) },
#else
 { 93, EE_CAX_ISR1_PRI(EE_CAX_93_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_94_ISR) && (EE_CAX_MAX_ISR_ID >= 94) && (EE_CAX_MAX_ARCH_ISR_ID >= 94))
#if (EE_CAX_94_ISR_CAT == 2)
 { 94, EE_CAX_ISR2_PRI(EE_CAX_94_ISR_PRI) },
#else
 { 94, EE_CAX_ISR1_PRI(EE_CAX_94_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_95_ISR) && (EE_CAX_MAX_ISR_ID >= 95) && (EE_CAX_MAX_ARCH_ISR_ID >= 95))
#if (EE_CAX_95_ISR_CAT == 2)
 { 95, EE_CAX_ISR2_PRI(EE_CAX_95_ISR_PRI) },
#else
 { 95, EE_CAX_ISR1_PRI(EE_CAX_95_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_96_ISR) && (EE_CAX_MAX_ISR_ID >= 96) && (EE_CAX_MAX_ARCH_ISR_ID >= 96))
#if (EE_CAX_96_ISR_CAT == 2)
 { 96, EE_CAX_ISR2_PRI(EE_CAX_96_ISR_PRI) },
#else
 { 96, EE_CAX_ISR1_PRI(EE_CAX_96_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_97_ISR) && (EE_CAX_MAX_ISR_ID >= 97) && (EE_CAX_MAX_ARCH_ISR_ID >= 97))
#if (EE_CAX_97_ISR_CAT == 2)
 { 97, EE_CAX_ISR2_PRI(EE_CAX_97_ISR_PRI) },
#else
 { 97, EE_CAX_ISR1_PRI(EE_CAX_97_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_98_ISR) && (EE_CAX_MAX_ISR_ID >= 98) && (EE_CAX_MAX_ARCH_ISR_ID >= 98))
#if (EE_CAX_98_ISR_CAT == 2)
 { 98, EE_CAX_ISR2_PRI(EE_CAX_98_ISR_PRI) },
#else
 { 98, EE_CAX_ISR1_PRI(EE_CAX_98_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_99_ISR) && (EE_CAX_MAX_ISR_ID >= 99) && (EE_CAX_MAX_ARCH_ISR_ID >= 99))
#if (EE_CAX_99_ISR_CAT == 2)
 { 99, EE_CAX_ISR2_PRI(EE_CAX_99_ISR_PRI) },
#else
 { 99, EE_CAX_ISR1_PRI(EE_CAX_99_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_100_ISR) && (EE_CAX_MAX_ISR_ID >= 100) && (EE_CAX_MAX_ARCH_ISR_ID >= 100))
#if (EE_CAX_100_ISR_CAT == 2)
 { 100, EE_CAX_ISR2_PRI(EE_CAX_100_ISR_PRI) },
#else
 { 100, EE_CAX_ISR1_PRI(EE_CAX_100_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_101_ISR) && (EE_CAX_MAX_ISR_ID >= 101) && (EE_CAX_MAX_ARCH_ISR_ID >= 101))
#if (EE_CAX_101_ISR_CAT == 2)
 { 101, EE_CAX_ISR2_PRI(EE_CAX_101_ISR_PRI) },
#else
 { 101, EE_CAX_ISR1_PRI(EE_CAX_101_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_102_ISR) && (EE_CAX_MAX_ISR_ID >= 102) && (EE_CAX_MAX_ARCH_ISR_ID >= 102))
#if (EE_CAX_102_ISR_CAT == 2)
 { 102, EE_CAX_ISR2_PRI(EE_CAX_102_ISR_PRI) },
#else
 { 102, EE_CAX_ISR1_PRI(EE_CAX_102_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_103_ISR) && (EE_CAX_MAX_ISR_ID >= 103) && (EE_CAX_MAX_ARCH_ISR_ID >= 103))
#if (EE_CAX_103_ISR_CAT == 2)
 { 103, EE_CAX_ISR2_PRI(EE_CAX_103_ISR_PRI) },
#else
 { 103, EE_CAX_ISR1_PRI(EE_CAX_103_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_104_ISR) && (EE_CAX_MAX_ISR_ID >= 104) && (EE_CAX_MAX_ARCH_ISR_ID >= 104))
#if (EE_CAX_104_ISR_CAT == 2)
 { 104, EE_CAX_ISR2_PRI(EE_CAX_104_ISR_PRI) },
#else
 { 104, EE_CAX_ISR1_PRI(EE_CAX_104_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_105_ISR) && (EE_CAX_MAX_ISR_ID >= 105) && (EE_CAX_MAX_ARCH_ISR_ID >= 105))
#if (EE_CAX_105_ISR_CAT == 2)
 { 105, EE_CAX_ISR2_PRI(EE_CAX_105_ISR_PRI) },
#else
 { 105, EE_CAX_ISR1_PRI(EE_CAX_105_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_106_ISR) && (EE_CAX_MAX_ISR_ID >= 106) && (EE_CAX_MAX_ARCH_ISR_ID >= 106))
#if (EE_CAX_106_ISR_CAT == 2)
 { 106, EE_CAX_ISR2_PRI(EE_CAX_106_ISR_PRI) },
#else
 { 106, EE_CAX_ISR1_PRI(EE_CAX_106_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_107_ISR) && (EE_CAX_MAX_ISR_ID >= 107) && (EE_CAX_MAX_ARCH_ISR_ID >= 107))
#if (EE_CAX_107_ISR_CAT == 2)
 { 107, EE_CAX_ISR2_PRI(EE_CAX_107_ISR_PRI) },
#else
 { 107, EE_CAX_ISR1_PRI(EE_CAX_107_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_108_ISR) && (EE_CAX_MAX_ISR_ID >= 108) && (EE_CAX_MAX_ARCH_ISR_ID >= 108))
#if (EE_CAX_108_ISR_CAT == 2)
 { 108, EE_CAX_ISR2_PRI(EE_CAX_108_ISR_PRI) },
#else
 { 108, EE_CAX_ISR1_PRI(EE_CAX_108_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_109_ISR) && (EE_CAX_MAX_ISR_ID >= 109) && (EE_CAX_MAX_ARCH_ISR_ID >= 109))
#if (EE_CAX_109_ISR_CAT == 2)
 { 109, EE_CAX_ISR2_PRI(EE_CAX_109_ISR_PRI) },
#else
 { 109, EE_CAX_ISR1_PRI(EE_CAX_109_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_110_ISR) && (EE_CAX_MAX_ISR_ID >= 110) && (EE_CAX_MAX_ARCH_ISR_ID >= 110))
#if (EE_CAX_110_ISR_CAT == 2)
 { 110, EE_CAX_ISR2_PRI(EE_CAX_110_ISR_PRI) },
#else
 { 110, EE_CAX_ISR1_PRI(EE_CAX_110_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_111_ISR) && (EE_CAX_MAX_ISR_ID >= 111) && (EE_CAX_MAX_ARCH_ISR_ID >= 111))
#if (EE_CAX_111_ISR_CAT == 2)
 { 111, EE_CAX_ISR2_PRI(EE_CAX_111_ISR_PRI) },
#else
 { 111, EE_CAX_ISR1_PRI(EE_CAX_111_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_112_ISR) && (EE_CAX_MAX_ISR_ID >= 112) && (EE_CAX_MAX_ARCH_ISR_ID >= 112))
#if (EE_CAX_112_ISR_CAT == 2)
 { 112, EE_CAX_ISR2_PRI(EE_CAX_112_ISR_PRI) },
#else
 { 112, EE_CAX_ISR1_PRI(EE_CAX_112_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_113_ISR) && (EE_CAX_MAX_ISR_ID >= 113) && (EE_CAX_MAX_ARCH_ISR_ID >= 113))
#if (EE_CAX_113_ISR_CAT == 2)
 { 113, EE_CAX_ISR2_PRI(EE_CAX_113_ISR_PRI) },
#else
 { 113, EE_CAX_ISR1_PRI(EE_CAX_113_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_114_ISR) && (EE_CAX_MAX_ISR_ID >= 114) && (EE_CAX_MAX_ARCH_ISR_ID >= 114))
#if (EE_CAX_114_ISR_CAT == 2)
 { 114, EE_CAX_ISR2_PRI(EE_CAX_114_ISR_PRI) },
#else
 { 114, EE_CAX_ISR1_PRI(EE_CAX_114_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_115_ISR) && (EE_CAX_MAX_ISR_ID >= 115) && (EE_CAX_MAX_ARCH_ISR_ID >= 115))
#if (EE_CAX_115_ISR_CAT == 2)
 { 115, EE_CAX_ISR2_PRI(EE_CAX_115_ISR_PRI) },
#else
 { 115, EE_CAX_ISR1_PRI(EE_CAX_115_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_116_ISR) && (EE_CAX_MAX_ISR_ID >= 116) && (EE_CAX_MAX_ARCH_ISR_ID >= 116))
#if (EE_CAX_116_ISR_CAT == 2)
 { 116, EE_CAX_ISR2_PRI(EE_CAX_116_ISR_PRI) },
#else
 { 116, EE_CAX_ISR1_PRI(EE_CAX_116_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_117_ISR) && (EE_CAX_MAX_ISR_ID >= 117) && (EE_CAX_MAX_ARCH_ISR_ID >= 117))
#if (EE_CAX_117_ISR_CAT == 2)
 { 117, EE_CAX_ISR2_PRI(EE_CAX_117_ISR_PRI) },
#else
 { 117, EE_CAX_ISR1_PRI(EE_CAX_117_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_118_ISR) && (EE_CAX_MAX_ISR_ID >= 118) && (EE_CAX_MAX_ARCH_ISR_ID >= 118))
#if (EE_CAX_118_ISR_CAT == 2)
 { 118, EE_CAX_ISR2_PRI(EE_CAX_118_ISR_PRI) },
#else
 { 118, EE_CAX_ISR1_PRI(EE_CAX_118_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_119_ISR) && (EE_CAX_MAX_ISR_ID >= 119) && (EE_CAX_MAX_ARCH_ISR_ID >= 119))
#if (EE_CAX_119_ISR_CAT == 2)
 { 119, EE_CAX_ISR2_PRI(EE_CAX_119_ISR_PRI) },
#else
 { 119, EE_CAX_ISR1_PRI(EE_CAX_119_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_120_ISR) && (EE_CAX_MAX_ISR_ID >= 120) && (EE_CAX_MAX_ARCH_ISR_ID >= 120))
#if (EE_CAX_120_ISR_CAT == 2)
 { 120, EE_CAX_ISR2_PRI(EE_CAX_120_ISR_PRI) },
#else
 { 120, EE_CAX_ISR1_PRI(EE_CAX_120_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_121_ISR) && (EE_CAX_MAX_ISR_ID >= 121) && (EE_CAX_MAX_ARCH_ISR_ID >= 121))
#if (EE_CAX_121_ISR_CAT == 2)
 { 121, EE_CAX_ISR2_PRI(EE_CAX_121_ISR_PRI) },
#else
 { 121, EE_CAX_ISR1_PRI(EE_CAX_121_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_122_ISR) && (EE_CAX_MAX_ISR_ID >= 122) && (EE_CAX_MAX_ARCH_ISR_ID >= 122))
#if (EE_CAX_122_ISR_CAT == 2)
 { 122, EE_CAX_ISR2_PRI(EE_CAX_122_ISR_PRI) },
#else
 { 122, EE_CAX_ISR1_PRI(EE_CAX_122_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_123_ISR) && (EE_CAX_MAX_ISR_ID >= 123) && (EE_CAX_MAX_ARCH_ISR_ID >= 123))
#if (EE_CAX_123_ISR_CAT == 2)
 { 123, EE_CAX_ISR2_PRI(EE_CAX_123_ISR_PRI) },
#else
 { 123, EE_CAX_ISR1_PRI(EE_CAX_123_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_124_ISR) && (EE_CAX_MAX_ISR_ID >= 124) && (EE_CAX_MAX_ARCH_ISR_ID >= 124))
#if (EE_CAX_124_ISR_CAT == 2)
 { 124, EE_CAX_ISR2_PRI(EE_CAX_124_ISR_PRI) },
#else
 { 124, EE_CAX_ISR1_PRI(EE_CAX_124_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_125_ISR) && (EE_CAX_MAX_ISR_ID >= 125) && (EE_CAX_MAX_ARCH_ISR_ID >= 125))
#if (EE_CAX_125_ISR_CAT == 2)
 { 125, EE_CAX_ISR2_PRI(EE_CAX_125_ISR_PRI) },
#else
 { 125, EE_CAX_ISR1_PRI(EE_CAX_125_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_126_ISR) && (EE_CAX_MAX_ISR_ID >= 126) && (EE_CAX_MAX_ARCH_ISR_ID >= 126))
#if (EE_CAX_126_ISR_CAT == 2)
 { 126, EE_CAX_ISR2_PRI(EE_CAX_126_ISR_PRI) },
#else
 { 126, EE_CAX_ISR1_PRI(EE_CAX_126_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_127_ISR) && (EE_CAX_MAX_ISR_ID >= 127) && (EE_CAX_MAX_ARCH_ISR_ID >= 127))
#if (EE_CAX_127_ISR_CAT == 2)
 { 127, EE_CAX_ISR2_PRI(EE_CAX_127_ISR_PRI) },
#else
 { 127, EE_CAX_ISR1_PRI(EE_CAX_127_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_128_ISR) && (EE_CAX_MAX_ISR_ID >= 128) && (EE_CAX_MAX_ARCH_ISR_ID >= 128))
#if (EE_CAX_128_ISR_CAT == 2)
 { 128, EE_CAX_ISR2_PRI(EE_CAX_128_ISR_PRI) },
#else
 { 128, EE_CAX_ISR1_PRI(EE_CAX_128_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_129_ISR) && (EE_CAX_MAX_ISR_ID >= 129) && (EE_CAX_MAX_ARCH_ISR_ID >= 129))
#if (EE_CAX_129_ISR_CAT == 2)
 { 129, EE_CAX_ISR2_PRI(EE_CAX_129_ISR_PRI) },
#else
 { 129, EE_CAX_ISR1_PRI(EE_CAX_129_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_130_ISR) && (EE_CAX_MAX_ISR_ID >= 130) && (EE_CAX_MAX_ARCH_ISR_ID >= 130))
#if (EE_CAX_130_ISR_CAT == 2)
 { 130, EE_CAX_ISR2_PRI(EE_CAX_130_ISR_PRI) },
#else
 { 130, EE_CAX_ISR1_PRI(EE_CAX_130_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_131_ISR) && (EE_CAX_MAX_ISR_ID >= 131) && (EE_CAX_MAX_ARCH_ISR_ID >= 131))
#if (EE_CAX_131_ISR_CAT == 2)
 { 131, EE_CAX_ISR2_PRI(EE_CAX_131_ISR_PRI) },
#else
 { 131, EE_CAX_ISR1_PRI(EE_CAX_131_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_132_ISR) && (EE_CAX_MAX_ISR_ID >= 132) && (EE_CAX_MAX_ARCH_ISR_ID >= 132))
#if (EE_CAX_132_ISR_CAT == 2)
 { 132, EE_CAX_ISR2_PRI(EE_CAX_132_ISR_PRI) },
#else
 { 132, EE_CAX_ISR1_PRI(EE_CAX_132_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_133_ISR) && (EE_CAX_MAX_ISR_ID >= 133) && (EE_CAX_MAX_ARCH_ISR_ID >= 133))
#if (EE_CAX_133_ISR_CAT == 2)
 { 133, EE_CAX_ISR2_PRI(EE_CAX_133_ISR_PRI) },
#else
 { 133, EE_CAX_ISR1_PRI(EE_CAX_133_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_134_ISR) && (EE_CAX_MAX_ISR_ID >= 134) && (EE_CAX_MAX_ARCH_ISR_ID >= 134))
#if (EE_CAX_134_ISR_CAT == 2)
 { 134, EE_CAX_ISR2_PRI(EE_CAX_134_ISR_PRI) },
#else
 { 134, EE_CAX_ISR1_PRI(EE_CAX_134_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_135_ISR) && (EE_CAX_MAX_ISR_ID >= 135) && (EE_CAX_MAX_ARCH_ISR_ID >= 135))
#if (EE_CAX_135_ISR_CAT == 2)
 { 135, EE_CAX_ISR2_PRI(EE_CAX_135_ISR_PRI) },
#else
 { 135, EE_CAX_ISR1_PRI(EE_CAX_135_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_136_ISR) && (EE_CAX_MAX_ISR_ID >= 136) && (EE_CAX_MAX_ARCH_ISR_ID >= 136))
#if (EE_CAX_136_ISR_CAT == 2)
 { 136, EE_CAX_ISR2_PRI(EE_CAX_136_ISR_PRI) },
#else
 { 136, EE_CAX_ISR1_PRI(EE_CAX_136_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_137_ISR) && (EE_CAX_MAX_ISR_ID >= 137) && (EE_CAX_MAX_ARCH_ISR_ID >= 137))
#if (EE_CAX_137_ISR_CAT == 2)
 { 137, EE_CAX_ISR2_PRI(EE_CAX_137_ISR_PRI) },
#else
 { 137, EE_CAX_ISR1_PRI(EE_CAX_137_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_138_ISR) && (EE_CAX_MAX_ISR_ID >= 138) && (EE_CAX_MAX_ARCH_ISR_ID >= 138))
#if (EE_CAX_138_ISR_CAT == 2)
 { 138, EE_CAX_ISR2_PRI(EE_CAX_138_ISR_PRI) },
#else
 { 138, EE_CAX_ISR1_PRI(EE_CAX_138_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_139_ISR) && (EE_CAX_MAX_ISR_ID >= 139) && (EE_CAX_MAX_ARCH_ISR_ID >= 139))
#if (EE_CAX_139_ISR_CAT == 2)
 { 139, EE_CAX_ISR2_PRI(EE_CAX_139_ISR_PRI) },
#else
 { 139, EE_CAX_ISR1_PRI(EE_CAX_139_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_140_ISR) && (EE_CAX_MAX_ISR_ID >= 140) && (EE_CAX_MAX_ARCH_ISR_ID >= 140))
#if (EE_CAX_140_ISR_CAT == 2)
 { 140, EE_CAX_ISR2_PRI(EE_CAX_140_ISR_PRI) },
#else
 { 140, EE_CAX_ISR1_PRI(EE_CAX_140_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_141_ISR) && (EE_CAX_MAX_ISR_ID >= 141) && (EE_CAX_MAX_ARCH_ISR_ID >= 141))
#if (EE_CAX_141_ISR_CAT == 2)
 { 141, EE_CAX_ISR2_PRI(EE_CAX_141_ISR_PRI) },
#else
 { 141, EE_CAX_ISR1_PRI(EE_CAX_141_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_142_ISR) && (EE_CAX_MAX_ISR_ID >= 142) && (EE_CAX_MAX_ARCH_ISR_ID >= 142))
#if (EE_CAX_142_ISR_CAT == 2)
 { 142, EE_CAX_ISR2_PRI(EE_CAX_142_ISR_PRI) },
#else
 { 142, EE_CAX_ISR1_PRI(EE_CAX_142_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_143_ISR) && (EE_CAX_MAX_ISR_ID >= 143) && (EE_CAX_MAX_ARCH_ISR_ID >= 143))
#if (EE_CAX_143_ISR_CAT == 2)
 { 143, EE_CAX_ISR2_PRI(EE_CAX_143_ISR_PRI) },
#else
 { 143, EE_CAX_ISR1_PRI(EE_CAX_143_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_144_ISR) && (EE_CAX_MAX_ISR_ID >= 144) && (EE_CAX_MAX_ARCH_ISR_ID >= 144))
#if (EE_CAX_144_ISR_CAT == 2)
 { 144, EE_CAX_ISR2_PRI(EE_CAX_144_ISR_PRI) },
#else
 { 144, EE_CAX_ISR1_PRI(EE_CAX_144_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_145_ISR) && (EE_CAX_MAX_ISR_ID >= 145) && (EE_CAX_MAX_ARCH_ISR_ID >= 145))
#if (EE_CAX_145_ISR_CAT == 2)
 { 145, EE_CAX_ISR2_PRI(EE_CAX_145_ISR_PRI) },
#else
 { 145, EE_CAX_ISR1_PRI(EE_CAX_145_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_146_ISR) && (EE_CAX_MAX_ISR_ID >= 146) && (EE_CAX_MAX_ARCH_ISR_ID >= 146))
#if (EE_CAX_146_ISR_CAT == 2)
 { 146, EE_CAX_ISR2_PRI(EE_CAX_146_ISR_PRI) },
#else
 { 146, EE_CAX_ISR1_PRI(EE_CAX_146_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_147_ISR) && (EE_CAX_MAX_ISR_ID >= 147) && (EE_CAX_MAX_ARCH_ISR_ID >= 147))
#if (EE_CAX_147_ISR_CAT == 2)
 { 147, EE_CAX_ISR2_PRI(EE_CAX_147_ISR_PRI) },
#else
 { 147, EE_CAX_ISR1_PRI(EE_CAX_147_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_148_ISR) && (EE_CAX_MAX_ISR_ID >= 148) && (EE_CAX_MAX_ARCH_ISR_ID >= 148))
#if (EE_CAX_148_ISR_CAT == 2)
 { 148, EE_CAX_ISR2_PRI(EE_CAX_148_ISR_PRI) },
#else
 { 148, EE_CAX_ISR1_PRI(EE_CAX_148_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_149_ISR) && (EE_CAX_MAX_ISR_ID >= 149) && (EE_CAX_MAX_ARCH_ISR_ID >= 149))
#if (EE_CAX_149_ISR_CAT == 2)
 { 149, EE_CAX_ISR2_PRI(EE_CAX_149_ISR_PRI) },
#else
 { 149, EE_CAX_ISR1_PRI(EE_CAX_149_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_150_ISR) && (EE_CAX_MAX_ISR_ID >= 150) && (EE_CAX_MAX_ARCH_ISR_ID >= 150))
#if (EE_CAX_150_ISR_CAT == 2)
 { 150, EE_CAX_ISR2_PRI(EE_CAX_150_ISR_PRI) },
#else
 { 150, EE_CAX_ISR1_PRI(EE_CAX_150_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_151_ISR) && (EE_CAX_MAX_ISR_ID >= 151) && (EE_CAX_MAX_ARCH_ISR_ID >= 151))
#if (EE_CAX_151_ISR_CAT == 2)
 { 151, EE_CAX_ISR2_PRI(EE_CAX_151_ISR_PRI) },
#else
 { 151, EE_CAX_ISR1_PRI(EE_CAX_151_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_152_ISR) && (EE_CAX_MAX_ISR_ID >= 152) && (EE_CAX_MAX_ARCH_ISR_ID >= 152))
#if (EE_CAX_152_ISR_CAT == 2)
 { 152, EE_CAX_ISR2_PRI(EE_CAX_152_ISR_PRI) },
#else
 { 152, EE_CAX_ISR1_PRI(EE_CAX_152_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_153_ISR) && (EE_CAX_MAX_ISR_ID >= 153) && (EE_CAX_MAX_ARCH_ISR_ID >= 153))
#if (EE_CAX_153_ISR_CAT == 2)
 { 153, EE_CAX_ISR2_PRI(EE_CAX_153_ISR_PRI) },
#else
 { 153, EE_CAX_ISR1_PRI(EE_CAX_153_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_154_ISR) && (EE_CAX_MAX_ISR_ID >= 154) && (EE_CAX_MAX_ARCH_ISR_ID >= 154))
#if (EE_CAX_154_ISR_CAT == 2)
 { 154, EE_CAX_ISR2_PRI(EE_CAX_154_ISR_PRI) },
#else
 { 154, EE_CAX_ISR1_PRI(EE_CAX_154_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_155_ISR) && (EE_CAX_MAX_ISR_ID >= 155) && (EE_CAX_MAX_ARCH_ISR_ID >= 155))
#if (EE_CAX_155_ISR_CAT == 2)
 { 155, EE_CAX_ISR2_PRI(EE_CAX_155_ISR_PRI) },
#else
 { 155, EE_CAX_ISR1_PRI(EE_CAX_155_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_156_ISR) && (EE_CAX_MAX_ISR_ID >= 156) && (EE_CAX_MAX_ARCH_ISR_ID >= 156))
#if (EE_CAX_156_ISR_CAT == 2)
 { 156, EE_CAX_ISR2_PRI(EE_CAX_156_ISR_PRI) },
#else
 { 156, EE_CAX_ISR1_PRI(EE_CAX_156_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_157_ISR) && (EE_CAX_MAX_ISR_ID >= 157) && (EE_CAX_MAX_ARCH_ISR_ID >= 157))
#if (EE_CAX_157_ISR_CAT == 2)
 { 157, EE_CAX_ISR2_PRI(EE_CAX_157_ISR_PRI) },
#else
 { 157, EE_CAX_ISR1_PRI(EE_CAX_157_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_158_ISR) && (EE_CAX_MAX_ISR_ID >= 158) && (EE_CAX_MAX_ARCH_ISR_ID >= 158))
#if (EE_CAX_158_ISR_CAT == 2)
 { 158, EE_CAX_ISR2_PRI(EE_CAX_158_ISR_PRI) },
#else
 { 158, EE_CAX_ISR1_PRI(EE_CAX_158_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_159_ISR) && (EE_CAX_MAX_ISR_ID >= 159) && (EE_CAX_MAX_ARCH_ISR_ID >= 159))
#if (EE_CAX_159_ISR_CAT == 2)
 { 159, EE_CAX_ISR2_PRI(EE_CAX_159_ISR_PRI) },
#else
 { 159, EE_CAX_ISR1_PRI(EE_CAX_159_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_160_ISR) && (EE_CAX_MAX_ISR_ID >= 160) && (EE_CAX_MAX_ARCH_ISR_ID >= 160))
#if (EE_CAX_160_ISR_CAT == 2)
 { 160, EE_CAX_ISR2_PRI(EE_CAX_160_ISR_PRI) },
#else
 { 160, EE_CAX_ISR1_PRI(EE_CAX_160_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_161_ISR) && (EE_CAX_MAX_ISR_ID >= 161) && (EE_CAX_MAX_ARCH_ISR_ID >= 161))
#if (EE_CAX_161_ISR_CAT == 2)
 { 161, EE_CAX_ISR2_PRI(EE_CAX_161_ISR_PRI) },
#else
 { 161, EE_CAX_ISR1_PRI(EE_CAX_161_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_162_ISR) && (EE_CAX_MAX_ISR_ID >= 162) && (EE_CAX_MAX_ARCH_ISR_ID >= 162))
#if (EE_CAX_162_ISR_CAT == 2)
 { 162, EE_CAX_ISR2_PRI(EE_CAX_162_ISR_PRI) },
#else
 { 162, EE_CAX_ISR1_PRI(EE_CAX_162_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_163_ISR) && (EE_CAX_MAX_ISR_ID >= 163) && (EE_CAX_MAX_ARCH_ISR_ID >= 163))
#if (EE_CAX_163_ISR_CAT == 2)
 { 163, EE_CAX_ISR2_PRI(EE_CAX_163_ISR_PRI) },
#else
 { 163, EE_CAX_ISR1_PRI(EE_CAX_163_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_164_ISR) && (EE_CAX_MAX_ISR_ID >= 164) && (EE_CAX_MAX_ARCH_ISR_ID >= 164))
#if (EE_CAX_164_ISR_CAT == 2)
 { 164, EE_CAX_ISR2_PRI(EE_CAX_164_ISR_PRI) },
#else
 { 164, EE_CAX_ISR1_PRI(EE_CAX_164_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_165_ISR) && (EE_CAX_MAX_ISR_ID >= 165) && (EE_CAX_MAX_ARCH_ISR_ID >= 165))
#if (EE_CAX_165_ISR_CAT == 2)
 { 165, EE_CAX_ISR2_PRI(EE_CAX_165_ISR_PRI) },
#else
 { 165, EE_CAX_ISR1_PRI(EE_CAX_165_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_166_ISR) && (EE_CAX_MAX_ISR_ID >= 166) && (EE_CAX_MAX_ARCH_ISR_ID >= 166))
#if (EE_CAX_166_ISR_CAT == 2)
 { 166, EE_CAX_ISR2_PRI(EE_CAX_166_ISR_PRI) },
#else
 { 166, EE_CAX_ISR1_PRI(EE_CAX_166_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_167_ISR) && (EE_CAX_MAX_ISR_ID >= 167) && (EE_CAX_MAX_ARCH_ISR_ID >= 167))
#if (EE_CAX_167_ISR_CAT == 2)
 { 167, EE_CAX_ISR2_PRI(EE_CAX_167_ISR_PRI) },
#else
 { 167, EE_CAX_ISR1_PRI(EE_CAX_167_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_168_ISR) && (EE_CAX_MAX_ISR_ID >= 168) && (EE_CAX_MAX_ARCH_ISR_ID >= 168))
#if (EE_CAX_168_ISR_CAT == 2)
 { 168, EE_CAX_ISR2_PRI(EE_CAX_168_ISR_PRI) },
#else
 { 168, EE_CAX_ISR1_PRI(EE_CAX_168_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_169_ISR) && (EE_CAX_MAX_ISR_ID >= 169) && (EE_CAX_MAX_ARCH_ISR_ID >= 169))
#if (EE_CAX_169_ISR_CAT == 2)
 { 169, EE_CAX_ISR2_PRI(EE_CAX_169_ISR_PRI) },
#else
 { 169, EE_CAX_ISR1_PRI(EE_CAX_169_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_170_ISR) && (EE_CAX_MAX_ISR_ID >= 170) && (EE_CAX_MAX_ARCH_ISR_ID >= 170))
#if (EE_CAX_170_ISR_CAT == 2)
 { 170, EE_CAX_ISR2_PRI(EE_CAX_170_ISR_PRI) },
#else
 { 170, EE_CAX_ISR1_PRI(EE_CAX_170_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_171_ISR) && (EE_CAX_MAX_ISR_ID >= 171) && (EE_CAX_MAX_ARCH_ISR_ID >= 171))
#if (EE_CAX_171_ISR_CAT == 2)
 { 171, EE_CAX_ISR2_PRI(EE_CAX_171_ISR_PRI) },
#else
 { 171, EE_CAX_ISR1_PRI(EE_CAX_171_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_172_ISR) && (EE_CAX_MAX_ISR_ID >= 172) && (EE_CAX_MAX_ARCH_ISR_ID >= 172))
#if (EE_CAX_172_ISR_CAT == 2)
 { 172, EE_CAX_ISR2_PRI(EE_CAX_172_ISR_PRI) },
#else
 { 172, EE_CAX_ISR1_PRI(EE_CAX_172_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_173_ISR) && (EE_CAX_MAX_ISR_ID >= 173) && (EE_CAX_MAX_ARCH_ISR_ID >= 173))
#if (EE_CAX_173_ISR_CAT == 2)
 { 173, EE_CAX_ISR2_PRI(EE_CAX_173_ISR_PRI) },
#else
 { 173, EE_CAX_ISR1_PRI(EE_CAX_173_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_174_ISR) && (EE_CAX_MAX_ISR_ID >= 174) && (EE_CAX_MAX_ARCH_ISR_ID >= 174))
#if (EE_CAX_174_ISR_CAT == 2)
 { 174, EE_CAX_ISR2_PRI(EE_CAX_174_ISR_PRI) },
#else
 { 174, EE_CAX_ISR1_PRI(EE_CAX_174_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_175_ISR) && (EE_CAX_MAX_ISR_ID >= 175) && (EE_CAX_MAX_ARCH_ISR_ID >= 175))
#if (EE_CAX_175_ISR_CAT == 2)
 { 175, EE_CAX_ISR2_PRI(EE_CAX_175_ISR_PRI) },
#else
 { 175, EE_CAX_ISR1_PRI(EE_CAX_175_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_176_ISR) && (EE_CAX_MAX_ISR_ID >= 176) && (EE_CAX_MAX_ARCH_ISR_ID >= 176))
#if (EE_CAX_176_ISR_CAT == 2)
 { 176, EE_CAX_ISR2_PRI(EE_CAX_176_ISR_PRI) },
#else
 { 176, EE_CAX_ISR1_PRI(EE_CAX_176_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_177_ISR) && (EE_CAX_MAX_ISR_ID >= 177) && (EE_CAX_MAX_ARCH_ISR_ID >= 177))
#if (EE_CAX_177_ISR_CAT == 2)
 { 177, EE_CAX_ISR2_PRI(EE_CAX_177_ISR_PRI) },
#else
 { 177, EE_CAX_ISR1_PRI(EE_CAX_177_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_178_ISR) && (EE_CAX_MAX_ISR_ID >= 178) && (EE_CAX_MAX_ARCH_ISR_ID >= 178))
#if (EE_CAX_178_ISR_CAT == 2)
 { 178, EE_CAX_ISR2_PRI(EE_CAX_178_ISR_PRI) },
#else
 { 178, EE_CAX_ISR1_PRI(EE_CAX_178_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_179_ISR) && (EE_CAX_MAX_ISR_ID >= 179) && (EE_CAX_MAX_ARCH_ISR_ID >= 179))
#if (EE_CAX_179_ISR_CAT == 2)
 { 179, EE_CAX_ISR2_PRI(EE_CAX_179_ISR_PRI) },
#else
 { 179, EE_CAX_ISR1_PRI(EE_CAX_179_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_180_ISR) && (EE_CAX_MAX_ISR_ID >= 180) && (EE_CAX_MAX_ARCH_ISR_ID >= 180))
#if (EE_CAX_180_ISR_CAT == 2)
 { 180, EE_CAX_ISR2_PRI(EE_CAX_180_ISR_PRI) },
#else
 { 180, EE_CAX_ISR1_PRI(EE_CAX_180_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_181_ISR) && (EE_CAX_MAX_ISR_ID >= 181) && (EE_CAX_MAX_ARCH_ISR_ID >= 181))
#if (EE_CAX_181_ISR_CAT == 2)
 { 181, EE_CAX_ISR2_PRI(EE_CAX_181_ISR_PRI) },
#else
 { 181, EE_CAX_ISR1_PRI(EE_CAX_181_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_182_ISR) && (EE_CAX_MAX_ISR_ID >= 182) && (EE_CAX_MAX_ARCH_ISR_ID >= 182))
#if (EE_CAX_182_ISR_CAT == 2)
 { 182, EE_CAX_ISR2_PRI(EE_CAX_182_ISR_PRI) },
#else
 { 182, EE_CAX_ISR1_PRI(EE_CAX_182_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_183_ISR) && (EE_CAX_MAX_ISR_ID >= 183) && (EE_CAX_MAX_ARCH_ISR_ID >= 183))
#if (EE_CAX_183_ISR_CAT == 2)
 { 183, EE_CAX_ISR2_PRI(EE_CAX_183_ISR_PRI) },
#else
 { 183, EE_CAX_ISR1_PRI(EE_CAX_183_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_184_ISR) && (EE_CAX_MAX_ISR_ID >= 184) && (EE_CAX_MAX_ARCH_ISR_ID >= 184))
#if (EE_CAX_184_ISR_CAT == 2)
 { 184, EE_CAX_ISR2_PRI(EE_CAX_184_ISR_PRI) },
#else
 { 184, EE_CAX_ISR1_PRI(EE_CAX_184_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_185_ISR) && (EE_CAX_MAX_ISR_ID >= 185) && (EE_CAX_MAX_ARCH_ISR_ID >= 185))
#if (EE_CAX_185_ISR_CAT == 2)
 { 185, EE_CAX_ISR2_PRI(EE_CAX_185_ISR_PRI) },
#else
 { 185, EE_CAX_ISR1_PRI(EE_CAX_185_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_186_ISR) && (EE_CAX_MAX_ISR_ID >= 186) && (EE_CAX_MAX_ARCH_ISR_ID >= 186))
#if (EE_CAX_186_ISR_CAT == 2)
 { 186, EE_CAX_ISR2_PRI(EE_CAX_186_ISR_PRI) },
#else
 { 186, EE_CAX_ISR1_PRI(EE_CAX_186_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_187_ISR) && (EE_CAX_MAX_ISR_ID >= 187) && (EE_CAX_MAX_ARCH_ISR_ID >= 187))
#if (EE_CAX_187_ISR_CAT == 2)
 { 187, EE_CAX_ISR2_PRI(EE_CAX_187_ISR_PRI) },
#else
 { 187, EE_CAX_ISR1_PRI(EE_CAX_187_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_188_ISR) && (EE_CAX_MAX_ISR_ID >= 188) && (EE_CAX_MAX_ARCH_ISR_ID >= 188))
#if (EE_CAX_188_ISR_CAT == 2)
 { 188, EE_CAX_ISR2_PRI(EE_CAX_188_ISR_PRI) },
#else
 { 188, EE_CAX_ISR1_PRI(EE_CAX_188_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_189_ISR) && (EE_CAX_MAX_ISR_ID >= 189) && (EE_CAX_MAX_ARCH_ISR_ID >= 189))
#if (EE_CAX_189_ISR_CAT == 2)
 { 189, EE_CAX_ISR2_PRI(EE_CAX_189_ISR_PRI) },
#else
 { 189, EE_CAX_ISR1_PRI(EE_CAX_189_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_190_ISR) && (EE_CAX_MAX_ISR_ID >= 190) && (EE_CAX_MAX_ARCH_ISR_ID >= 190))
#if (EE_CAX_190_ISR_CAT == 2)
 { 190, EE_CAX_ISR2_PRI(EE_CAX_190_ISR_PRI) },
#else
 { 190, EE_CAX_ISR1_PRI(EE_CAX_190_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_191_ISR) && (EE_CAX_MAX_ISR_ID >= 191) && (EE_CAX_MAX_ARCH_ISR_ID >= 191))
#if (EE_CAX_191_ISR_CAT == 2)
 { 191, EE_CAX_ISR2_PRI(EE_CAX_191_ISR_PRI) },
#else
 { 191, EE_CAX_ISR1_PRI(EE_CAX_191_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_192_ISR) && (EE_CAX_MAX_ISR_ID >= 192) && (EE_CAX_MAX_ARCH_ISR_ID >= 192))
#if (EE_CAX_192_ISR_CAT == 2)
 { 192, EE_CAX_ISR2_PRI(EE_CAX_192_ISR_PRI) },
#else
 { 192, EE_CAX_ISR1_PRI(EE_CAX_192_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_193_ISR) && (EE_CAX_MAX_ISR_ID >= 193) && (EE_CAX_MAX_ARCH_ISR_ID >= 193))
#if (EE_CAX_193_ISR_CAT == 2)
 { 193, EE_CAX_ISR2_PRI(EE_CAX_193_ISR_PRI) },
#else
 { 193, EE_CAX_ISR1_PRI(EE_CAX_193_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_194_ISR) && (EE_CAX_MAX_ISR_ID >= 194) && (EE_CAX_MAX_ARCH_ISR_ID >= 194))
#if (EE_CAX_194_ISR_CAT == 2)
 { 194, EE_CAX_ISR2_PRI(EE_CAX_194_ISR_PRI) },
#else
 { 194, EE_CAX_ISR1_PRI(EE_CAX_194_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_195_ISR) && (EE_CAX_MAX_ISR_ID >= 195) && (EE_CAX_MAX_ARCH_ISR_ID >= 195))
#if (EE_CAX_195_ISR_CAT == 2)
 { 195, EE_CAX_ISR2_PRI(EE_CAX_195_ISR_PRI) },
#else
 { 195, EE_CAX_ISR1_PRI(EE_CAX_195_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_196_ISR) && (EE_CAX_MAX_ISR_ID >= 196) && (EE_CAX_MAX_ARCH_ISR_ID >= 196))
#if (EE_CAX_196_ISR_CAT == 2)
 { 196, EE_CAX_ISR2_PRI(EE_CAX_196_ISR_PRI) },
#else
 { 196, EE_CAX_ISR1_PRI(EE_CAX_196_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_197_ISR) && (EE_CAX_MAX_ISR_ID >= 197) && (EE_CAX_MAX_ARCH_ISR_ID >= 197))
#if (EE_CAX_197_ISR_CAT == 2)
 { 197, EE_CAX_ISR2_PRI(EE_CAX_197_ISR_PRI) },
#else
 { 197, EE_CAX_ISR1_PRI(EE_CAX_197_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_198_ISR) && (EE_CAX_MAX_ISR_ID >= 198) && (EE_CAX_MAX_ARCH_ISR_ID >= 198))
#if (EE_CAX_198_ISR_CAT == 2)
 { 198, EE_CAX_ISR2_PRI(EE_CAX_198_ISR_PRI) },
#else
 { 198, EE_CAX_ISR1_PRI(EE_CAX_198_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_199_ISR) && (EE_CAX_MAX_ISR_ID >= 199) && (EE_CAX_MAX_ARCH_ISR_ID >= 199))
#if (EE_CAX_199_ISR_CAT == 2)
 { 199, EE_CAX_ISR2_PRI(EE_CAX_199_ISR_PRI) },
#else
 { 199, EE_CAX_ISR1_PRI(EE_CAX_199_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_200_ISR) && (EE_CAX_MAX_ISR_ID >= 200) && (EE_CAX_MAX_ARCH_ISR_ID >= 200))
#if (EE_CAX_200_ISR_CAT == 2)
 { 200, EE_CAX_ISR2_PRI(EE_CAX_200_ISR_PRI) },
#else
 { 200, EE_CAX_ISR1_PRI(EE_CAX_200_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_201_ISR) && (EE_CAX_MAX_ISR_ID >= 201) && (EE_CAX_MAX_ARCH_ISR_ID >= 201))
#if (EE_CAX_201_ISR_CAT == 2)
 { 201, EE_CAX_ISR2_PRI(EE_CAX_201_ISR_PRI) },
#else
 { 201, EE_CAX_ISR1_PRI(EE_CAX_201_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_202_ISR) && (EE_CAX_MAX_ISR_ID >= 202) && (EE_CAX_MAX_ARCH_ISR_ID >= 202))
#if (EE_CAX_202_ISR_CAT == 2)
 { 202, EE_CAX_ISR2_PRI(EE_CAX_202_ISR_PRI) },
#else
 { 202, EE_CAX_ISR1_PRI(EE_CAX_202_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_203_ISR) && (EE_CAX_MAX_ISR_ID >= 203) && (EE_CAX_MAX_ARCH_ISR_ID >= 203))
#if (EE_CAX_203_ISR_CAT == 2)
 { 203, EE_CAX_ISR2_PRI(EE_CAX_203_ISR_PRI) },
#else
 { 203, EE_CAX_ISR1_PRI(EE_CAX_203_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_204_ISR) && (EE_CAX_MAX_ISR_ID >= 204) && (EE_CAX_MAX_ARCH_ISR_ID >= 204))
#if (EE_CAX_204_ISR_CAT == 2)
 { 204, EE_CAX_ISR2_PRI(EE_CAX_204_ISR_PRI) },
#else
 { 204, EE_CAX_ISR1_PRI(EE_CAX_204_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_205_ISR) && (EE_CAX_MAX_ISR_ID >= 205) && (EE_CAX_MAX_ARCH_ISR_ID >= 205))
#if (EE_CAX_205_ISR_CAT == 2)
 { 205, EE_CAX_ISR2_PRI(EE_CAX_205_ISR_PRI) },
#else
 { 205, EE_CAX_ISR1_PRI(EE_CAX_205_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_206_ISR) && (EE_CAX_MAX_ISR_ID >= 206) && (EE_CAX_MAX_ARCH_ISR_ID >= 206))
#if (EE_CAX_206_ISR_CAT == 2)
 { 206, EE_CAX_ISR2_PRI(EE_CAX_206_ISR_PRI) },
#else
 { 206, EE_CAX_ISR1_PRI(EE_CAX_206_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_207_ISR) && (EE_CAX_MAX_ISR_ID >= 207) && (EE_CAX_MAX_ARCH_ISR_ID >= 207))
#if (EE_CAX_207_ISR_CAT == 2)
 { 207, EE_CAX_ISR2_PRI(EE_CAX_207_ISR_PRI) },
#else
 { 207, EE_CAX_ISR1_PRI(EE_CAX_207_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_208_ISR) && (EE_CAX_MAX_ISR_ID >= 208) && (EE_CAX_MAX_ARCH_ISR_ID >= 208))
#if (EE_CAX_208_ISR_CAT == 2)
 { 208, EE_CAX_ISR2_PRI(EE_CAX_208_ISR_PRI) },
#else
 { 208, EE_CAX_ISR1_PRI(EE_CAX_208_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_209_ISR) && (EE_CAX_MAX_ISR_ID >= 209) && (EE_CAX_MAX_ARCH_ISR_ID >= 209))
#if (EE_CAX_209_ISR_CAT == 2)
 { 209, EE_CAX_ISR2_PRI(EE_CAX_209_ISR_PRI) },
#else
 { 209, EE_CAX_ISR1_PRI(EE_CAX_209_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_210_ISR) && (EE_CAX_MAX_ISR_ID >= 210) && (EE_CAX_MAX_ARCH_ISR_ID >= 210))
#if (EE_CAX_210_ISR_CAT == 2)
 { 210, EE_CAX_ISR2_PRI(EE_CAX_210_ISR_PRI) },
#else
 { 210, EE_CAX_ISR1_PRI(EE_CAX_210_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_211_ISR) && (EE_CAX_MAX_ISR_ID >= 211) && (EE_CAX_MAX_ARCH_ISR_ID >= 211))
#if (EE_CAX_211_ISR_CAT == 2)
 { 211, EE_CAX_ISR2_PRI(EE_CAX_211_ISR_PRI) },
#else
 { 211, EE_CAX_ISR1_PRI(EE_CAX_211_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_212_ISR) && (EE_CAX_MAX_ISR_ID >= 212) && (EE_CAX_MAX_ARCH_ISR_ID >= 212))
#if (EE_CAX_212_ISR_CAT == 2)
 { 212, EE_CAX_ISR2_PRI(EE_CAX_212_ISR_PRI) },
#else
 { 212, EE_CAX_ISR1_PRI(EE_CAX_212_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_213_ISR) && (EE_CAX_MAX_ISR_ID >= 213) && (EE_CAX_MAX_ARCH_ISR_ID >= 213))
#if (EE_CAX_213_ISR_CAT == 2)
 { 213, EE_CAX_ISR2_PRI(EE_CAX_213_ISR_PRI) },
#else
 { 213, EE_CAX_ISR1_PRI(EE_CAX_213_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_214_ISR) && (EE_CAX_MAX_ISR_ID >= 214) && (EE_CAX_MAX_ARCH_ISR_ID >= 214))
#if (EE_CAX_214_ISR_CAT == 2)
 { 214, EE_CAX_ISR2_PRI(EE_CAX_214_ISR_PRI) },
#else
 { 214, EE_CAX_ISR1_PRI(EE_CAX_214_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_215_ISR) && (EE_CAX_MAX_ISR_ID >= 215) && (EE_CAX_MAX_ARCH_ISR_ID >= 215))
#if (EE_CAX_215_ISR_CAT == 2)
 { 215, EE_CAX_ISR2_PRI(EE_CAX_215_ISR_PRI) },
#else
 { 215, EE_CAX_ISR1_PRI(EE_CAX_215_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_216_ISR) && (EE_CAX_MAX_ISR_ID >= 216) && (EE_CAX_MAX_ARCH_ISR_ID >= 216))
#if (EE_CAX_216_ISR_CAT == 2)
 { 216, EE_CAX_ISR2_PRI(EE_CAX_216_ISR_PRI) },
#else
 { 216, EE_CAX_ISR1_PRI(EE_CAX_216_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_217_ISR) && (EE_CAX_MAX_ISR_ID >= 217) && (EE_CAX_MAX_ARCH_ISR_ID >= 217))
#if (EE_CAX_217_ISR_CAT == 2)
 { 217, EE_CAX_ISR2_PRI(EE_CAX_217_ISR_PRI) },
#else
 { 217, EE_CAX_ISR1_PRI(EE_CAX_217_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_218_ISR) && (EE_CAX_MAX_ISR_ID >= 218) && (EE_CAX_MAX_ARCH_ISR_ID >= 218))
#if (EE_CAX_218_ISR_CAT == 2)
 { 218, EE_CAX_ISR2_PRI(EE_CAX_218_ISR_PRI) },
#else
 { 218, EE_CAX_ISR1_PRI(EE_CAX_218_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_219_ISR) && (EE_CAX_MAX_ISR_ID >= 219) && (EE_CAX_MAX_ARCH_ISR_ID >= 219))
#if (EE_CAX_219_ISR_CAT == 2)
 { 219, EE_CAX_ISR2_PRI(EE_CAX_219_ISR_PRI) },
#else
 { 219, EE_CAX_ISR1_PRI(EE_CAX_219_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_220_ISR) && (EE_CAX_MAX_ISR_ID >= 220) && (EE_CAX_MAX_ARCH_ISR_ID >= 220))
#if (EE_CAX_220_ISR_CAT == 2)
 { 220, EE_CAX_ISR2_PRI(EE_CAX_220_ISR_PRI) },
#else
 { 220, EE_CAX_ISR1_PRI(EE_CAX_220_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_221_ISR) && (EE_CAX_MAX_ISR_ID >= 221) && (EE_CAX_MAX_ARCH_ISR_ID >= 221))
#if (EE_CAX_221_ISR_CAT == 2)
 { 221, EE_CAX_ISR2_PRI(EE_CAX_221_ISR_PRI) },
#else
 { 221, EE_CAX_ISR1_PRI(EE_CAX_221_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_222_ISR) && (EE_CAX_MAX_ISR_ID >= 222) && (EE_CAX_MAX_ARCH_ISR_ID >= 222))
#if (EE_CAX_222_ISR_CAT == 2)
 { 222, EE_CAX_ISR2_PRI(EE_CAX_222_ISR_PRI) },
#else
 { 222, EE_CAX_ISR1_PRI(EE_CAX_222_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_223_ISR) && (EE_CAX_MAX_ISR_ID >= 223) && (EE_CAX_MAX_ARCH_ISR_ID >= 223))
#if (EE_CAX_223_ISR_CAT == 2)
 { 223, EE_CAX_ISR2_PRI(EE_CAX_223_ISR_PRI) },
#else
 { 223, EE_CAX_ISR1_PRI(EE_CAX_223_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_224_ISR) && (EE_CAX_MAX_ISR_ID >= 224) && (EE_CAX_MAX_ARCH_ISR_ID >= 224))
#if (EE_CAX_224_ISR_CAT == 2)
 { 224, EE_CAX_ISR2_PRI(EE_CAX_224_ISR_PRI) },
#else
 { 224, EE_CAX_ISR1_PRI(EE_CAX_224_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_225_ISR) && (EE_CAX_MAX_ISR_ID >= 225) && (EE_CAX_MAX_ARCH_ISR_ID >= 225))
#if (EE_CAX_225_ISR_CAT == 2)
 { 225, EE_CAX_ISR2_PRI(EE_CAX_225_ISR_PRI) },
#else
 { 225, EE_CAX_ISR1_PRI(EE_CAX_225_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_226_ISR) && (EE_CAX_MAX_ISR_ID >= 226) && (EE_CAX_MAX_ARCH_ISR_ID >= 226))
#if (EE_CAX_226_ISR_CAT == 2)
 { 226, EE_CAX_ISR2_PRI(EE_CAX_226_ISR_PRI) },
#else
 { 226, EE_CAX_ISR1_PRI(EE_CAX_226_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_227_ISR) && (EE_CAX_MAX_ISR_ID >= 227) && (EE_CAX_MAX_ARCH_ISR_ID >= 227))
#if (EE_CAX_227_ISR_CAT == 2)
 { 227, EE_CAX_ISR2_PRI(EE_CAX_227_ISR_PRI) },
#else
 { 227, EE_CAX_ISR1_PRI(EE_CAX_227_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_228_ISR) && (EE_CAX_MAX_ISR_ID >= 228) && (EE_CAX_MAX_ARCH_ISR_ID >= 228))
#if (EE_CAX_228_ISR_CAT == 2)
 { 228, EE_CAX_ISR2_PRI(EE_CAX_228_ISR_PRI) },
#else
 { 228, EE_CAX_ISR1_PRI(EE_CAX_228_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_229_ISR) && (EE_CAX_MAX_ISR_ID >= 229) && (EE_CAX_MAX_ARCH_ISR_ID >= 229))
#if (EE_CAX_229_ISR_CAT == 2)
 { 229, EE_CAX_ISR2_PRI(EE_CAX_229_ISR_PRI) },
#else
 { 229, EE_CAX_ISR1_PRI(EE_CAX_229_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_230_ISR) && (EE_CAX_MAX_ISR_ID >= 230) && (EE_CAX_MAX_ARCH_ISR_ID >= 230))
#if (EE_CAX_230_ISR_CAT == 2)
 { 230, EE_CAX_ISR2_PRI(EE_CAX_230_ISR_PRI) },
#else
 { 230, EE_CAX_ISR1_PRI(EE_CAX_230_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_231_ISR) && (EE_CAX_MAX_ISR_ID >= 231) && (EE_CAX_MAX_ARCH_ISR_ID >= 231))
#if (EE_CAX_231_ISR_CAT == 2)
 { 231, EE_CAX_ISR2_PRI(EE_CAX_231_ISR_PRI) },
#else
 { 231, EE_CAX_ISR1_PRI(EE_CAX_231_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_232_ISR) && (EE_CAX_MAX_ISR_ID >= 232) && (EE_CAX_MAX_ARCH_ISR_ID >= 232))
#if (EE_CAX_232_ISR_CAT == 2)
 { 232, EE_CAX_ISR2_PRI(EE_CAX_232_ISR_PRI) },
#else
 { 232, EE_CAX_ISR1_PRI(EE_CAX_232_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_233_ISR) && (EE_CAX_MAX_ISR_ID >= 233) && (EE_CAX_MAX_ARCH_ISR_ID >= 233))
#if (EE_CAX_233_ISR_CAT == 2)
 { 233, EE_CAX_ISR2_PRI(EE_CAX_233_ISR_PRI) },
#else
 { 233, EE_CAX_ISR1_PRI(EE_CAX_233_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_234_ISR) && (EE_CAX_MAX_ISR_ID >= 234) && (EE_CAX_MAX_ARCH_ISR_ID >= 234))
#if (EE_CAX_234_ISR_CAT == 2)
 { 234, EE_CAX_ISR2_PRI(EE_CAX_234_ISR_PRI) },
#else
 { 234, EE_CAX_ISR1_PRI(EE_CAX_234_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_235_ISR) && (EE_CAX_MAX_ISR_ID >= 235) && (EE_CAX_MAX_ARCH_ISR_ID >= 235))
#if (EE_CAX_235_ISR_CAT == 2)
 { 235, EE_CAX_ISR2_PRI(EE_CAX_235_ISR_PRI) },
#else
 { 235, EE_CAX_ISR1_PRI(EE_CAX_235_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_236_ISR) && (EE_CAX_MAX_ISR_ID >= 236) && (EE_CAX_MAX_ARCH_ISR_ID >= 236))
#if (EE_CAX_236_ISR_CAT == 2)
 { 236, EE_CAX_ISR2_PRI(EE_CAX_236_ISR_PRI) },
#else
 { 236, EE_CAX_ISR1_PRI(EE_CAX_236_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_237_ISR) && (EE_CAX_MAX_ISR_ID >= 237) && (EE_CAX_MAX_ARCH_ISR_ID >= 237))
#if (EE_CAX_237_ISR_CAT == 2)
 { 237, EE_CAX_ISR2_PRI(EE_CAX_237_ISR_PRI) },
#else
 { 237, EE_CAX_ISR1_PRI(EE_CAX_237_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_238_ISR) && (EE_CAX_MAX_ISR_ID >= 238) && (EE_CAX_MAX_ARCH_ISR_ID >= 238))
#if (EE_CAX_238_ISR_CAT == 2)
 { 238, EE_CAX_ISR2_PRI(EE_CAX_238_ISR_PRI) },
#else
 { 238, EE_CAX_ISR1_PRI(EE_CAX_238_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_239_ISR) && (EE_CAX_MAX_ISR_ID >= 239) && (EE_CAX_MAX_ARCH_ISR_ID >= 239))
#if (EE_CAX_239_ISR_CAT == 2)
 { 239, EE_CAX_ISR2_PRI(EE_CAX_239_ISR_PRI) },
#else
 { 239, EE_CAX_ISR1_PRI(EE_CAX_239_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_240_ISR) && (EE_CAX_MAX_ISR_ID >= 240) && (EE_CAX_MAX_ARCH_ISR_ID >= 240))
#if (EE_CAX_240_ISR_CAT == 2)
 { 240, EE_CAX_ISR2_PRI(EE_CAX_240_ISR_PRI) },
#else
 { 240, EE_CAX_ISR1_PRI(EE_CAX_240_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_241_ISR) && (EE_CAX_MAX_ISR_ID >= 241) && (EE_CAX_MAX_ARCH_ISR_ID >= 241))
#if (EE_CAX_241_ISR_CAT == 2)
 { 241, EE_CAX_ISR2_PRI(EE_CAX_241_ISR_PRI) },
#else
 { 241, EE_CAX_ISR1_PRI(EE_CAX_241_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_242_ISR) && (EE_CAX_MAX_ISR_ID >= 242) && (EE_CAX_MAX_ARCH_ISR_ID >= 242))
#if (EE_CAX_242_ISR_CAT == 2)
 { 242, EE_CAX_ISR2_PRI(EE_CAX_242_ISR_PRI) },
#else
 { 242, EE_CAX_ISR1_PRI(EE_CAX_242_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_243_ISR) && (EE_CAX_MAX_ISR_ID >= 243) && (EE_CAX_MAX_ARCH_ISR_ID >= 243))
#if (EE_CAX_243_ISR_CAT == 2)
 { 243, EE_CAX_ISR2_PRI(EE_CAX_243_ISR_PRI) },
#else
 { 243, EE_CAX_ISR1_PRI(EE_CAX_243_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_244_ISR) && (EE_CAX_MAX_ISR_ID >= 244) && (EE_CAX_MAX_ARCH_ISR_ID >= 244))
#if (EE_CAX_244_ISR_CAT == 2)
 { 244, EE_CAX_ISR2_PRI(EE_CAX_244_ISR_PRI) },
#else
 { 244, EE_CAX_ISR1_PRI(EE_CAX_244_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_245_ISR) && (EE_CAX_MAX_ISR_ID >= 245) && (EE_CAX_MAX_ARCH_ISR_ID >= 245))
#if (EE_CAX_245_ISR_CAT == 2)
 { 245, EE_CAX_ISR2_PRI(EE_CAX_245_ISR_PRI) },
#else
 { 245, EE_CAX_ISR1_PRI(EE_CAX_245_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_246_ISR) && (EE_CAX_MAX_ISR_ID >= 246) && (EE_CAX_MAX_ARCH_ISR_ID >= 246))
#if (EE_CAX_246_ISR_CAT == 2)
 { 246, EE_CAX_ISR2_PRI(EE_CAX_246_ISR_PRI) },
#else
 { 246, EE_CAX_ISR1_PRI(EE_CAX_246_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_247_ISR) && (EE_CAX_MAX_ISR_ID >= 247) && (EE_CAX_MAX_ARCH_ISR_ID >= 247))
#if (EE_CAX_247_ISR_CAT == 2)
 { 247, EE_CAX_ISR2_PRI(EE_CAX_247_ISR_PRI) },
#else
 { 247, EE_CAX_ISR1_PRI(EE_CAX_247_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_248_ISR) && (EE_CAX_MAX_ISR_ID >= 248) && (EE_CAX_MAX_ARCH_ISR_ID >= 248))
#if (EE_CAX_248_ISR_CAT == 2)
 { 248, EE_CAX_ISR2_PRI(EE_CAX_248_ISR_PRI) },
#else
 { 248, EE_CAX_ISR1_PRI(EE_CAX_248_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_249_ISR) && (EE_CAX_MAX_ISR_ID >= 249) && (EE_CAX_MAX_ARCH_ISR_ID >= 249))
#if (EE_CAX_249_ISR_CAT == 2)
 { 249, EE_CAX_ISR2_PRI(EE_CAX_249_ISR_PRI) },
#else
 { 249, EE_CAX_ISR1_PRI(EE_CAX_249_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_250_ISR) && (EE_CAX_MAX_ISR_ID >= 250) && (EE_CAX_MAX_ARCH_ISR_ID >= 250))
#if (EE_CAX_250_ISR_CAT == 2)
 { 250, EE_CAX_ISR2_PRI(EE_CAX_250_ISR_PRI) },
#else
 { 250, EE_CAX_ISR1_PRI(EE_CAX_250_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_251_ISR) && (EE_CAX_MAX_ISR_ID >= 251) && (EE_CAX_MAX_ARCH_ISR_ID >= 251))
#if (EE_CAX_251_ISR_CAT == 2)
 { 251, EE_CAX_ISR2_PRI(EE_CAX_251_ISR_PRI) },
#else
 { 251, EE_CAX_ISR1_PRI(EE_CAX_251_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_252_ISR) && (EE_CAX_MAX_ISR_ID >= 252) && (EE_CAX_MAX_ARCH_ISR_ID >= 252))
#if (EE_CAX_252_ISR_CAT == 2)
 { 252, EE_CAX_ISR2_PRI(EE_CAX_252_ISR_PRI) },
#else
 { 252, EE_CAX_ISR1_PRI(EE_CAX_252_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_253_ISR) && (EE_CAX_MAX_ISR_ID >= 253) && (EE_CAX_MAX_ARCH_ISR_ID >= 253))
#if (EE_CAX_253_ISR_CAT == 2)
 { 253, EE_CAX_ISR2_PRI(EE_CAX_253_ISR_PRI) },
#else
 { 253, EE_CAX_ISR1_PRI(EE_CAX_253_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_254_ISR) && (EE_CAX_MAX_ISR_ID >= 254) && (EE_CAX_MAX_ARCH_ISR_ID >= 254))
#if (EE_CAX_254_ISR_CAT == 2)
 { 254, EE_CAX_ISR2_PRI(EE_CAX_254_ISR_PRI) },
#else
 { 254, EE_CAX_ISR1_PRI(EE_CAX_254_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_255_ISR) && (EE_CAX_MAX_ISR_ID >= 255) && (EE_CAX_MAX_ARCH_ISR_ID >= 255))
#if (EE_CAX_255_ISR_CAT == 2)
 { 255, EE_CAX_ISR2_PRI(EE_CAX_255_ISR_PRI) },
#else
 { 255, EE_CAX_ISR1_PRI(EE_CAX_255_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_256_ISR) && (EE_CAX_MAX_ISR_ID >= 256) && (EE_CAX_MAX_ARCH_ISR_ID >= 256))
#if (EE_CAX_256_ISR_CAT == 2)
 { 256, EE_CAX_ISR2_PRI(EE_CAX_256_ISR_PRI) },
#else
 { 256, EE_CAX_ISR1_PRI(EE_CAX_256_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_257_ISR) && (EE_CAX_MAX_ISR_ID >= 257) && (EE_CAX_MAX_ARCH_ISR_ID >= 257))
#if (EE_CAX_257_ISR_CAT == 2)
 { 257, EE_CAX_ISR2_PRI(EE_CAX_257_ISR_PRI) },
#else
 { 257, EE_CAX_ISR1_PRI(EE_CAX_257_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_258_ISR) && (EE_CAX_MAX_ISR_ID >= 258) && (EE_CAX_MAX_ARCH_ISR_ID >= 258))
#if (EE_CAX_258_ISR_CAT == 2)
 { 258, EE_CAX_ISR2_PRI(EE_CAX_258_ISR_PRI) },
#else
 { 258, EE_CAX_ISR1_PRI(EE_CAX_258_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_259_ISR) && (EE_CAX_MAX_ISR_ID >= 259) && (EE_CAX_MAX_ARCH_ISR_ID >= 259))
#if (EE_CAX_259_ISR_CAT == 2)
 { 259, EE_CAX_ISR2_PRI(EE_CAX_259_ISR_PRI) },
#else
 { 259, EE_CAX_ISR1_PRI(EE_CAX_259_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_260_ISR) && (EE_CAX_MAX_ISR_ID >= 260) && (EE_CAX_MAX_ARCH_ISR_ID >= 260))
#if (EE_CAX_260_ISR_CAT == 2)
 { 260, EE_CAX_ISR2_PRI(EE_CAX_260_ISR_PRI) },
#else
 { 260, EE_CAX_ISR1_PRI(EE_CAX_260_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_261_ISR) && (EE_CAX_MAX_ISR_ID >= 261) && (EE_CAX_MAX_ARCH_ISR_ID >= 261))
#if (EE_CAX_261_ISR_CAT == 2)
 { 261, EE_CAX_ISR2_PRI(EE_CAX_261_ISR_PRI) },
#else
 { 261, EE_CAX_ISR1_PRI(EE_CAX_261_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_262_ISR) && (EE_CAX_MAX_ISR_ID >= 262) && (EE_CAX_MAX_ARCH_ISR_ID >= 262))
#if (EE_CAX_262_ISR_CAT == 2)
 { 262, EE_CAX_ISR2_PRI(EE_CAX_262_ISR_PRI) },
#else
 { 262, EE_CAX_ISR1_PRI(EE_CAX_262_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_263_ISR) && (EE_CAX_MAX_ISR_ID >= 263) && (EE_CAX_MAX_ARCH_ISR_ID >= 263))
#if (EE_CAX_263_ISR_CAT == 2)
 { 263, EE_CAX_ISR2_PRI(EE_CAX_263_ISR_PRI) },
#else
 { 263, EE_CAX_ISR1_PRI(EE_CAX_263_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_264_ISR) && (EE_CAX_MAX_ISR_ID >= 264) && (EE_CAX_MAX_ARCH_ISR_ID >= 264))
#if (EE_CAX_264_ISR_CAT == 2)
 { 264, EE_CAX_ISR2_PRI(EE_CAX_264_ISR_PRI) },
#else
 { 264, EE_CAX_ISR1_PRI(EE_CAX_264_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_265_ISR) && (EE_CAX_MAX_ISR_ID >= 265) && (EE_CAX_MAX_ARCH_ISR_ID >= 265))
#if (EE_CAX_265_ISR_CAT == 2)
 { 265, EE_CAX_ISR2_PRI(EE_CAX_265_ISR_PRI) },
#else
 { 265, EE_CAX_ISR1_PRI(EE_CAX_265_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_266_ISR) && (EE_CAX_MAX_ISR_ID >= 266) && (EE_CAX_MAX_ARCH_ISR_ID >= 266))
#if (EE_CAX_266_ISR_CAT == 2)
 { 266, EE_CAX_ISR2_PRI(EE_CAX_266_ISR_PRI) },
#else
 { 266, EE_CAX_ISR1_PRI(EE_CAX_266_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_267_ISR) && (EE_CAX_MAX_ISR_ID >= 267) && (EE_CAX_MAX_ARCH_ISR_ID >= 267))
#if (EE_CAX_267_ISR_CAT == 2)
 { 267, EE_CAX_ISR2_PRI(EE_CAX_267_ISR_PRI) },
#else
 { 267, EE_CAX_ISR1_PRI(EE_CAX_267_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_268_ISR) && (EE_CAX_MAX_ISR_ID >= 268) && (EE_CAX_MAX_ARCH_ISR_ID >= 268))
#if (EE_CAX_268_ISR_CAT == 2)
 { 268, EE_CAX_ISR2_PRI(EE_CAX_268_ISR_PRI) },
#else
 { 268, EE_CAX_ISR1_PRI(EE_CAX_268_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_269_ISR) && (EE_CAX_MAX_ISR_ID >= 269) && (EE_CAX_MAX_ARCH_ISR_ID >= 269))
#if (EE_CAX_269_ISR_CAT == 2)
 { 269, EE_CAX_ISR2_PRI(EE_CAX_269_ISR_PRI) },
#else
 { 269, EE_CAX_ISR1_PRI(EE_CAX_269_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_270_ISR) && (EE_CAX_MAX_ISR_ID >= 270) && (EE_CAX_MAX_ARCH_ISR_ID >= 270))
#if (EE_CAX_270_ISR_CAT == 2)
 { 270, EE_CAX_ISR2_PRI(EE_CAX_270_ISR_PRI) },
#else
 { 270, EE_CAX_ISR1_PRI(EE_CAX_270_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_271_ISR) && (EE_CAX_MAX_ISR_ID >= 271) && (EE_CAX_MAX_ARCH_ISR_ID >= 271))
#if (EE_CAX_271_ISR_CAT == 2)
 { 271, EE_CAX_ISR2_PRI(EE_CAX_271_ISR_PRI) },
#else
 { 271, EE_CAX_ISR1_PRI(EE_CAX_271_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_272_ISR) && (EE_CAX_MAX_ISR_ID >= 272) && (EE_CAX_MAX_ARCH_ISR_ID >= 272))
#if (EE_CAX_272_ISR_CAT == 2)
 { 272, EE_CAX_ISR2_PRI(EE_CAX_272_ISR_PRI) },
#else
 { 272, EE_CAX_ISR1_PRI(EE_CAX_272_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_273_ISR) && (EE_CAX_MAX_ISR_ID >= 273) && (EE_CAX_MAX_ARCH_ISR_ID >= 273))
#if (EE_CAX_273_ISR_CAT == 2)
 { 273, EE_CAX_ISR2_PRI(EE_CAX_273_ISR_PRI) },
#else
 { 273, EE_CAX_ISR1_PRI(EE_CAX_273_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_274_ISR) && (EE_CAX_MAX_ISR_ID >= 274) && (EE_CAX_MAX_ARCH_ISR_ID >= 274))
#if (EE_CAX_274_ISR_CAT == 2)
 { 274, EE_CAX_ISR2_PRI(EE_CAX_274_ISR_PRI) },
#else
 { 274, EE_CAX_ISR1_PRI(EE_CAX_274_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_275_ISR) && (EE_CAX_MAX_ISR_ID >= 275) && (EE_CAX_MAX_ARCH_ISR_ID >= 275))
#if (EE_CAX_275_ISR_CAT == 2)
 { 275, EE_CAX_ISR2_PRI(EE_CAX_275_ISR_PRI) },
#else
 { 275, EE_CAX_ISR1_PRI(EE_CAX_275_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_276_ISR) && (EE_CAX_MAX_ISR_ID >= 276) && (EE_CAX_MAX_ARCH_ISR_ID >= 276))
#if (EE_CAX_276_ISR_CAT == 2)
 { 276, EE_CAX_ISR2_PRI(EE_CAX_276_ISR_PRI) },
#else
 { 276, EE_CAX_ISR1_PRI(EE_CAX_276_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_277_ISR) && (EE_CAX_MAX_ISR_ID >= 277) && (EE_CAX_MAX_ARCH_ISR_ID >= 277))
#if (EE_CAX_277_ISR_CAT == 2)
 { 277, EE_CAX_ISR2_PRI(EE_CAX_277_ISR_PRI) },
#else
 { 277, EE_CAX_ISR1_PRI(EE_CAX_277_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_278_ISR) && (EE_CAX_MAX_ISR_ID >= 278) && (EE_CAX_MAX_ARCH_ISR_ID >= 278))
#if (EE_CAX_278_ISR_CAT == 2)
 { 278, EE_CAX_ISR2_PRI(EE_CAX_278_ISR_PRI) },
#else
 { 278, EE_CAX_ISR1_PRI(EE_CAX_278_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_279_ISR) && (EE_CAX_MAX_ISR_ID >= 279) && (EE_CAX_MAX_ARCH_ISR_ID >= 279))
#if (EE_CAX_279_ISR_CAT == 2)
 { 279, EE_CAX_ISR2_PRI(EE_CAX_279_ISR_PRI) },
#else
 { 279, EE_CAX_ISR1_PRI(EE_CAX_279_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_280_ISR) && (EE_CAX_MAX_ISR_ID >= 280) && (EE_CAX_MAX_ARCH_ISR_ID >= 280))
#if (EE_CAX_280_ISR_CAT == 2)
 { 280, EE_CAX_ISR2_PRI(EE_CAX_280_ISR_PRI) },
#else
 { 280, EE_CAX_ISR1_PRI(EE_CAX_280_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_281_ISR) && (EE_CAX_MAX_ISR_ID >= 281) && (EE_CAX_MAX_ARCH_ISR_ID >= 281))
#if (EE_CAX_281_ISR_CAT == 2)
 { 281, EE_CAX_ISR2_PRI(EE_CAX_281_ISR_PRI) },
#else
 { 281, EE_CAX_ISR1_PRI(EE_CAX_281_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_282_ISR) && (EE_CAX_MAX_ISR_ID >= 282) && (EE_CAX_MAX_ARCH_ISR_ID >= 282))
#if (EE_CAX_282_ISR_CAT == 2)
 { 282, EE_CAX_ISR2_PRI(EE_CAX_282_ISR_PRI) },
#else
 { 282, EE_CAX_ISR1_PRI(EE_CAX_282_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_283_ISR) && (EE_CAX_MAX_ISR_ID >= 283) && (EE_CAX_MAX_ARCH_ISR_ID >= 283))
#if (EE_CAX_283_ISR_CAT == 2)
 { 283, EE_CAX_ISR2_PRI(EE_CAX_283_ISR_PRI) },
#else
 { 283, EE_CAX_ISR1_PRI(EE_CAX_283_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_284_ISR) && (EE_CAX_MAX_ISR_ID >= 284) && (EE_CAX_MAX_ARCH_ISR_ID >= 284))
#if (EE_CAX_284_ISR_CAT == 2)
 { 284, EE_CAX_ISR2_PRI(EE_CAX_284_ISR_PRI) },
#else
 { 284, EE_CAX_ISR1_PRI(EE_CAX_284_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_285_ISR) && (EE_CAX_MAX_ISR_ID >= 285) && (EE_CAX_MAX_ARCH_ISR_ID >= 285))
#if (EE_CAX_285_ISR_CAT == 2)
 { 285, EE_CAX_ISR2_PRI(EE_CAX_285_ISR_PRI) },
#else
 { 285, EE_CAX_ISR1_PRI(EE_CAX_285_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_286_ISR) && (EE_CAX_MAX_ISR_ID >= 286) && (EE_CAX_MAX_ARCH_ISR_ID >= 286))
#if (EE_CAX_286_ISR_CAT == 2)
 { 286, EE_CAX_ISR2_PRI(EE_CAX_286_ISR_PRI) },
#else
 { 286, EE_CAX_ISR1_PRI(EE_CAX_286_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_287_ISR) && (EE_CAX_MAX_ISR_ID >= 287) && (EE_CAX_MAX_ARCH_ISR_ID >= 287))
#if (EE_CAX_287_ISR_CAT == 2)
 { 287, EE_CAX_ISR2_PRI(EE_CAX_287_ISR_PRI) },
#else
 { 287, EE_CAX_ISR1_PRI(EE_CAX_287_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_288_ISR) && (EE_CAX_MAX_ISR_ID >= 288) && (EE_CAX_MAX_ARCH_ISR_ID >= 288))
#if (EE_CAX_288_ISR_CAT == 2)
 { 288, EE_CAX_ISR2_PRI(EE_CAX_288_ISR_PRI) },
#else
 { 288, EE_CAX_ISR1_PRI(EE_CAX_288_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_289_ISR) && (EE_CAX_MAX_ISR_ID >= 289) && (EE_CAX_MAX_ARCH_ISR_ID >= 289))
#if (EE_CAX_289_ISR_CAT == 2)
 { 289, EE_CAX_ISR2_PRI(EE_CAX_289_ISR_PRI) },
#else
 { 289, EE_CAX_ISR1_PRI(EE_CAX_289_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_290_ISR) && (EE_CAX_MAX_ISR_ID >= 290) && (EE_CAX_MAX_ARCH_ISR_ID >= 290))
#if (EE_CAX_290_ISR_CAT == 2)
 { 290, EE_CAX_ISR2_PRI(EE_CAX_290_ISR_PRI) },
#else
 { 290, EE_CAX_ISR1_PRI(EE_CAX_290_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_291_ISR) && (EE_CAX_MAX_ISR_ID >= 291) && (EE_CAX_MAX_ARCH_ISR_ID >= 291))
#if (EE_CAX_291_ISR_CAT == 2)
 { 291, EE_CAX_ISR2_PRI(EE_CAX_291_ISR_PRI) },
#else
 { 291, EE_CAX_ISR1_PRI(EE_CAX_291_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_292_ISR) && (EE_CAX_MAX_ISR_ID >= 292) && (EE_CAX_MAX_ARCH_ISR_ID >= 292))
#if (EE_CAX_292_ISR_CAT == 2)
 { 292, EE_CAX_ISR2_PRI(EE_CAX_292_ISR_PRI) },
#else
 { 292, EE_CAX_ISR1_PRI(EE_CAX_292_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_293_ISR) && (EE_CAX_MAX_ISR_ID >= 293) && (EE_CAX_MAX_ARCH_ISR_ID >= 293))
#if (EE_CAX_293_ISR_CAT == 2)
 { 293, EE_CAX_ISR2_PRI(EE_CAX_293_ISR_PRI) },
#else
 { 293, EE_CAX_ISR1_PRI(EE_CAX_293_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_294_ISR) && (EE_CAX_MAX_ISR_ID >= 294) && (EE_CAX_MAX_ARCH_ISR_ID >= 294))
#if (EE_CAX_294_ISR_CAT == 2)
 { 294, EE_CAX_ISR2_PRI(EE_CAX_294_ISR_PRI) },
#else
 { 294, EE_CAX_ISR1_PRI(EE_CAX_294_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_295_ISR) && (EE_CAX_MAX_ISR_ID >= 295) && (EE_CAX_MAX_ARCH_ISR_ID >= 295))
#if (EE_CAX_295_ISR_CAT == 2)
 { 295, EE_CAX_ISR2_PRI(EE_CAX_295_ISR_PRI) },
#else
 { 295, EE_CAX_ISR1_PRI(EE_CAX_295_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_296_ISR) && (EE_CAX_MAX_ISR_ID >= 296) && (EE_CAX_MAX_ARCH_ISR_ID >= 296))
#if (EE_CAX_296_ISR_CAT == 2)
 { 296, EE_CAX_ISR2_PRI(EE_CAX_296_ISR_PRI) },
#else
 { 296, EE_CAX_ISR1_PRI(EE_CAX_296_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_297_ISR) && (EE_CAX_MAX_ISR_ID >= 297) && (EE_CAX_MAX_ARCH_ISR_ID >= 297))
#if (EE_CAX_297_ISR_CAT == 2)
 { 297, EE_CAX_ISR2_PRI(EE_CAX_297_ISR_PRI) },
#else
 { 297, EE_CAX_ISR1_PRI(EE_CAX_297_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_298_ISR) && (EE_CAX_MAX_ISR_ID >= 298) && (EE_CAX_MAX_ARCH_ISR_ID >= 298))
#if (EE_CAX_298_ISR_CAT == 2)
 { 298, EE_CAX_ISR2_PRI(EE_CAX_298_ISR_PRI) },
#else
 { 298, EE_CAX_ISR1_PRI(EE_CAX_298_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_299_ISR) && (EE_CAX_MAX_ISR_ID >= 299) && (EE_CAX_MAX_ARCH_ISR_ID >= 299))
#if (EE_CAX_299_ISR_CAT == 2)
 { 299, EE_CAX_ISR2_PRI(EE_CAX_299_ISR_PRI) },
#else
 { 299, EE_CAX_ISR1_PRI(EE_CAX_299_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_300_ISR) && (EE_CAX_MAX_ISR_ID >= 300) && (EE_CAX_MAX_ARCH_ISR_ID >= 300))
#if (EE_CAX_300_ISR_CAT == 2)
 { 300, EE_CAX_ISR2_PRI(EE_CAX_300_ISR_PRI) },
#else
 { 300, EE_CAX_ISR1_PRI(EE_CAX_300_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_301_ISR) && (EE_CAX_MAX_ISR_ID >= 301) && (EE_CAX_MAX_ARCH_ISR_ID >= 301))
#if (EE_CAX_301_ISR_CAT == 2)
 { 301, EE_CAX_ISR2_PRI(EE_CAX_301_ISR_PRI) },
#else
 { 301, EE_CAX_ISR1_PRI(EE_CAX_301_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_302_ISR) && (EE_CAX_MAX_ISR_ID >= 302) && (EE_CAX_MAX_ARCH_ISR_ID >= 302))
#if (EE_CAX_302_ISR_CAT == 2)
 { 302, EE_CAX_ISR2_PRI(EE_CAX_302_ISR_PRI) },
#else
 { 302, EE_CAX_ISR1_PRI(EE_CAX_302_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_303_ISR) && (EE_CAX_MAX_ISR_ID >= 303) && (EE_CAX_MAX_ARCH_ISR_ID >= 303))
#if (EE_CAX_303_ISR_CAT == 2)
 { 303, EE_CAX_ISR2_PRI(EE_CAX_303_ISR_PRI) },
#else
 { 303, EE_CAX_ISR1_PRI(EE_CAX_303_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_304_ISR) && (EE_CAX_MAX_ISR_ID >= 304) && (EE_CAX_MAX_ARCH_ISR_ID >= 304))
#if (EE_CAX_304_ISR_CAT == 2)
 { 304, EE_CAX_ISR2_PRI(EE_CAX_304_ISR_PRI) },
#else
 { 304, EE_CAX_ISR1_PRI(EE_CAX_304_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_305_ISR) && (EE_CAX_MAX_ISR_ID >= 305) && (EE_CAX_MAX_ARCH_ISR_ID >= 305))
#if (EE_CAX_305_ISR_CAT == 2)
 { 305, EE_CAX_ISR2_PRI(EE_CAX_305_ISR_PRI) },
#else
 { 305, EE_CAX_ISR1_PRI(EE_CAX_305_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_306_ISR) && (EE_CAX_MAX_ISR_ID >= 306) && (EE_CAX_MAX_ARCH_ISR_ID >= 306))
#if (EE_CAX_306_ISR_CAT == 2)
 { 306, EE_CAX_ISR2_PRI(EE_CAX_306_ISR_PRI) },
#else
 { 306, EE_CAX_ISR1_PRI(EE_CAX_306_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_307_ISR) && (EE_CAX_MAX_ISR_ID >= 307) && (EE_CAX_MAX_ARCH_ISR_ID >= 307))
#if (EE_CAX_307_ISR_CAT == 2)
 { 307, EE_CAX_ISR2_PRI(EE_CAX_307_ISR_PRI) },
#else
 { 307, EE_CAX_ISR1_PRI(EE_CAX_307_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_308_ISR) && (EE_CAX_MAX_ISR_ID >= 308) && (EE_CAX_MAX_ARCH_ISR_ID >= 308))
#if (EE_CAX_308_ISR_CAT == 2)
 { 308, EE_CAX_ISR2_PRI(EE_CAX_308_ISR_PRI) },
#else
 { 308, EE_CAX_ISR1_PRI(EE_CAX_308_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_309_ISR) && (EE_CAX_MAX_ISR_ID >= 309) && (EE_CAX_MAX_ARCH_ISR_ID >= 309))
#if (EE_CAX_309_ISR_CAT == 2)
 { 309, EE_CAX_ISR2_PRI(EE_CAX_309_ISR_PRI) },
#else
 { 309, EE_CAX_ISR1_PRI(EE_CAX_309_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_310_ISR) && (EE_CAX_MAX_ISR_ID >= 310) && (EE_CAX_MAX_ARCH_ISR_ID >= 310))
#if (EE_CAX_310_ISR_CAT == 2)
 { 310, EE_CAX_ISR2_PRI(EE_CAX_310_ISR_PRI) },
#else
 { 310, EE_CAX_ISR1_PRI(EE_CAX_310_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_311_ISR) && (EE_CAX_MAX_ISR_ID >= 311) && (EE_CAX_MAX_ARCH_ISR_ID >= 311))
#if (EE_CAX_311_ISR_CAT == 2)
 { 311, EE_CAX_ISR2_PRI(EE_CAX_311_ISR_PRI) },
#else
 { 311, EE_CAX_ISR1_PRI(EE_CAX_311_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_312_ISR) && (EE_CAX_MAX_ISR_ID >= 312) && (EE_CAX_MAX_ARCH_ISR_ID >= 312))
#if (EE_CAX_312_ISR_CAT == 2)
 { 312, EE_CAX_ISR2_PRI(EE_CAX_312_ISR_PRI) },
#else
 { 312, EE_CAX_ISR1_PRI(EE_CAX_312_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_313_ISR) && (EE_CAX_MAX_ISR_ID >= 313) && (EE_CAX_MAX_ARCH_ISR_ID >= 313))
#if (EE_CAX_313_ISR_CAT == 2)
 { 313, EE_CAX_ISR2_PRI(EE_CAX_313_ISR_PRI) },
#else
 { 313, EE_CAX_ISR1_PRI(EE_CAX_313_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_314_ISR) && (EE_CAX_MAX_ISR_ID >= 314) && (EE_CAX_MAX_ARCH_ISR_ID >= 314))
#if (EE_CAX_314_ISR_CAT == 2)
 { 314, EE_CAX_ISR2_PRI(EE_CAX_314_ISR_PRI) },
#else
 { 314, EE_CAX_ISR1_PRI(EE_CAX_314_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_315_ISR) && (EE_CAX_MAX_ISR_ID >= 315) && (EE_CAX_MAX_ARCH_ISR_ID >= 315))
#if (EE_CAX_315_ISR_CAT == 2)
 { 315, EE_CAX_ISR2_PRI(EE_CAX_315_ISR_PRI) },
#else
 { 315, EE_CAX_ISR1_PRI(EE_CAX_315_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_316_ISR) && (EE_CAX_MAX_ISR_ID >= 316) && (EE_CAX_MAX_ARCH_ISR_ID >= 316))
#if (EE_CAX_316_ISR_CAT == 2)
 { 316, EE_CAX_ISR2_PRI(EE_CAX_316_ISR_PRI) },
#else
 { 316, EE_CAX_ISR1_PRI(EE_CAX_316_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_317_ISR) && (EE_CAX_MAX_ISR_ID >= 317) && (EE_CAX_MAX_ARCH_ISR_ID >= 317))
#if (EE_CAX_317_ISR_CAT == 2)
 { 317, EE_CAX_ISR2_PRI(EE_CAX_317_ISR_PRI) },
#else
 { 317, EE_CAX_ISR1_PRI(EE_CAX_317_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_318_ISR) && (EE_CAX_MAX_ISR_ID >= 318) && (EE_CAX_MAX_ARCH_ISR_ID >= 318))
#if (EE_CAX_318_ISR_CAT == 2)
 { 318, EE_CAX_ISR2_PRI(EE_CAX_318_ISR_PRI) },
#else
 { 318, EE_CAX_ISR1_PRI(EE_CAX_318_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_319_ISR) && (EE_CAX_MAX_ISR_ID >= 319) && (EE_CAX_MAX_ARCH_ISR_ID >= 319))
#if (EE_CAX_319_ISR_CAT == 2)
 { 319, EE_CAX_ISR2_PRI(EE_CAX_319_ISR_PRI) },
#else
 { 319, EE_CAX_ISR1_PRI(EE_CAX_319_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_320_ISR) && (EE_CAX_MAX_ISR_ID >= 320) && (EE_CAX_MAX_ARCH_ISR_ID >= 320))
#if (EE_CAX_320_ISR_CAT == 2)
 { 320, EE_CAX_ISR2_PRI(EE_CAX_320_ISR_PRI) },
#else
 { 320, EE_CAX_ISR1_PRI(EE_CAX_320_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_321_ISR) && (EE_CAX_MAX_ISR_ID >= 321) && (EE_CAX_MAX_ARCH_ISR_ID >= 321))
#if (EE_CAX_321_ISR_CAT == 2)
 { 321, EE_CAX_ISR2_PRI(EE_CAX_321_ISR_PRI) },
#else
 { 321, EE_CAX_ISR1_PRI(EE_CAX_321_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_322_ISR) && (EE_CAX_MAX_ISR_ID >= 322) && (EE_CAX_MAX_ARCH_ISR_ID >= 322))
#if (EE_CAX_322_ISR_CAT == 2)
 { 322, EE_CAX_ISR2_PRI(EE_CAX_322_ISR_PRI) },
#else
 { 322, EE_CAX_ISR1_PRI(EE_CAX_322_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_323_ISR) && (EE_CAX_MAX_ISR_ID >= 323) && (EE_CAX_MAX_ARCH_ISR_ID >= 323))
#if (EE_CAX_323_ISR_CAT == 2)
 { 323, EE_CAX_ISR2_PRI(EE_CAX_323_ISR_PRI) },
#else
 { 323, EE_CAX_ISR1_PRI(EE_CAX_323_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_324_ISR) && (EE_CAX_MAX_ISR_ID >= 324) && (EE_CAX_MAX_ARCH_ISR_ID >= 324))
#if (EE_CAX_324_ISR_CAT == 2)
 { 324, EE_CAX_ISR2_PRI(EE_CAX_324_ISR_PRI) },
#else
 { 324, EE_CAX_ISR1_PRI(EE_CAX_324_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_325_ISR) && (EE_CAX_MAX_ISR_ID >= 325) && (EE_CAX_MAX_ARCH_ISR_ID >= 325))
#if (EE_CAX_325_ISR_CAT == 2)
 { 325, EE_CAX_ISR2_PRI(EE_CAX_325_ISR_PRI) },
#else
 { 325, EE_CAX_ISR1_PRI(EE_CAX_325_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_326_ISR) && (EE_CAX_MAX_ISR_ID >= 326) && (EE_CAX_MAX_ARCH_ISR_ID >= 326))
#if (EE_CAX_326_ISR_CAT == 2)
 { 326, EE_CAX_ISR2_PRI(EE_CAX_326_ISR_PRI) },
#else
 { 326, EE_CAX_ISR1_PRI(EE_CAX_326_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_327_ISR) && (EE_CAX_MAX_ISR_ID >= 327) && (EE_CAX_MAX_ARCH_ISR_ID >= 327))
#if (EE_CAX_327_ISR_CAT == 2)
 { 327, EE_CAX_ISR2_PRI(EE_CAX_327_ISR_PRI) },
#else
 { 327, EE_CAX_ISR1_PRI(EE_CAX_327_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_328_ISR) && (EE_CAX_MAX_ISR_ID >= 328) && (EE_CAX_MAX_ARCH_ISR_ID >= 328))
#if (EE_CAX_328_ISR_CAT == 2)
 { 328, EE_CAX_ISR2_PRI(EE_CAX_328_ISR_PRI) },
#else
 { 328, EE_CAX_ISR1_PRI(EE_CAX_328_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_329_ISR) && (EE_CAX_MAX_ISR_ID >= 329) && (EE_CAX_MAX_ARCH_ISR_ID >= 329))
#if (EE_CAX_329_ISR_CAT == 2)
 { 329, EE_CAX_ISR2_PRI(EE_CAX_329_ISR_PRI) },
#else
 { 329, EE_CAX_ISR1_PRI(EE_CAX_329_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_330_ISR) && (EE_CAX_MAX_ISR_ID >= 330) && (EE_CAX_MAX_ARCH_ISR_ID >= 330))
#if (EE_CAX_330_ISR_CAT == 2)
 { 330, EE_CAX_ISR2_PRI(EE_CAX_330_ISR_PRI) },
#else
 { 330, EE_CAX_ISR1_PRI(EE_CAX_330_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_331_ISR) && (EE_CAX_MAX_ISR_ID >= 331) && (EE_CAX_MAX_ARCH_ISR_ID >= 331))
#if (EE_CAX_331_ISR_CAT == 2)
 { 331, EE_CAX_ISR2_PRI(EE_CAX_331_ISR_PRI) },
#else
 { 331, EE_CAX_ISR1_PRI(EE_CAX_331_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_332_ISR) && (EE_CAX_MAX_ISR_ID >= 332) && (EE_CAX_MAX_ARCH_ISR_ID >= 332))
#if (EE_CAX_332_ISR_CAT == 2)
 { 332, EE_CAX_ISR2_PRI(EE_CAX_332_ISR_PRI) },
#else
 { 332, EE_CAX_ISR1_PRI(EE_CAX_332_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_333_ISR) && (EE_CAX_MAX_ISR_ID >= 333) && (EE_CAX_MAX_ARCH_ISR_ID >= 333))
#if (EE_CAX_333_ISR_CAT == 2)
 { 333, EE_CAX_ISR2_PRI(EE_CAX_333_ISR_PRI) },
#else
 { 333, EE_CAX_ISR1_PRI(EE_CAX_333_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_334_ISR) && (EE_CAX_MAX_ISR_ID >= 334) && (EE_CAX_MAX_ARCH_ISR_ID >= 334))
#if (EE_CAX_334_ISR_CAT == 2)
 { 334, EE_CAX_ISR2_PRI(EE_CAX_334_ISR_PRI) },
#else
 { 334, EE_CAX_ISR1_PRI(EE_CAX_334_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_335_ISR) && (EE_CAX_MAX_ISR_ID >= 335) && (EE_CAX_MAX_ARCH_ISR_ID >= 335))
#if (EE_CAX_335_ISR_CAT == 2)
 { 335, EE_CAX_ISR2_PRI(EE_CAX_335_ISR_PRI) },
#else
 { 335, EE_CAX_ISR1_PRI(EE_CAX_335_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_336_ISR) && (EE_CAX_MAX_ISR_ID >= 336) && (EE_CAX_MAX_ARCH_ISR_ID >= 336))
#if (EE_CAX_336_ISR_CAT == 2)
 { 336, EE_CAX_ISR2_PRI(EE_CAX_336_ISR_PRI) },
#else
 { 336, EE_CAX_ISR1_PRI(EE_CAX_336_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_337_ISR) && (EE_CAX_MAX_ISR_ID >= 337) && (EE_CAX_MAX_ARCH_ISR_ID >= 337))
#if (EE_CAX_337_ISR_CAT == 2)
 { 337, EE_CAX_ISR2_PRI(EE_CAX_337_ISR_PRI) },
#else
 { 337, EE_CAX_ISR1_PRI(EE_CAX_337_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_338_ISR) && (EE_CAX_MAX_ISR_ID >= 338) && (EE_CAX_MAX_ARCH_ISR_ID >= 338))
#if (EE_CAX_338_ISR_CAT == 2)
 { 338, EE_CAX_ISR2_PRI(EE_CAX_338_ISR_PRI) },
#else
 { 338, EE_CAX_ISR1_PRI(EE_CAX_338_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_339_ISR) && (EE_CAX_MAX_ISR_ID >= 339) && (EE_CAX_MAX_ARCH_ISR_ID >= 339))
#if (EE_CAX_339_ISR_CAT == 2)
 { 339, EE_CAX_ISR2_PRI(EE_CAX_339_ISR_PRI) },
#else
 { 339, EE_CAX_ISR1_PRI(EE_CAX_339_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_340_ISR) && (EE_CAX_MAX_ISR_ID >= 340) && (EE_CAX_MAX_ARCH_ISR_ID >= 340))
#if (EE_CAX_340_ISR_CAT == 2)
 { 340, EE_CAX_ISR2_PRI(EE_CAX_340_ISR_PRI) },
#else
 { 340, EE_CAX_ISR1_PRI(EE_CAX_340_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_341_ISR) && (EE_CAX_MAX_ISR_ID >= 341) && (EE_CAX_MAX_ARCH_ISR_ID >= 341))
#if (EE_CAX_341_ISR_CAT == 2)
 { 341, EE_CAX_ISR2_PRI(EE_CAX_341_ISR_PRI) },
#else
 { 341, EE_CAX_ISR1_PRI(EE_CAX_341_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_342_ISR) && (EE_CAX_MAX_ISR_ID >= 342) && (EE_CAX_MAX_ARCH_ISR_ID >= 342))
#if (EE_CAX_342_ISR_CAT == 2)
 { 342, EE_CAX_ISR2_PRI(EE_CAX_342_ISR_PRI) },
#else
 { 342, EE_CAX_ISR1_PRI(EE_CAX_342_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_343_ISR) && (EE_CAX_MAX_ISR_ID >= 343) && (EE_CAX_MAX_ARCH_ISR_ID >= 343))
#if (EE_CAX_343_ISR_CAT == 2)
 { 343, EE_CAX_ISR2_PRI(EE_CAX_343_ISR_PRI) },
#else
 { 343, EE_CAX_ISR1_PRI(EE_CAX_343_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_344_ISR) && (EE_CAX_MAX_ISR_ID >= 344) && (EE_CAX_MAX_ARCH_ISR_ID >= 344))
#if (EE_CAX_344_ISR_CAT == 2)
 { 344, EE_CAX_ISR2_PRI(EE_CAX_344_ISR_PRI) },
#else
 { 344, EE_CAX_ISR1_PRI(EE_CAX_344_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_345_ISR) && (EE_CAX_MAX_ISR_ID >= 345) && (EE_CAX_MAX_ARCH_ISR_ID >= 345))
#if (EE_CAX_345_ISR_CAT == 2)
 { 345, EE_CAX_ISR2_PRI(EE_CAX_345_ISR_PRI) },
#else
 { 345, EE_CAX_ISR1_PRI(EE_CAX_345_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_346_ISR) && (EE_CAX_MAX_ISR_ID >= 346) && (EE_CAX_MAX_ARCH_ISR_ID >= 346))
#if (EE_CAX_346_ISR_CAT == 2)
 { 346, EE_CAX_ISR2_PRI(EE_CAX_346_ISR_PRI) },
#else
 { 346, EE_CAX_ISR1_PRI(EE_CAX_346_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_347_ISR) && (EE_CAX_MAX_ISR_ID >= 347) && (EE_CAX_MAX_ARCH_ISR_ID >= 347))
#if (EE_CAX_347_ISR_CAT == 2)
 { 347, EE_CAX_ISR2_PRI(EE_CAX_347_ISR_PRI) },
#else
 { 347, EE_CAX_ISR1_PRI(EE_CAX_347_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_348_ISR) && (EE_CAX_MAX_ISR_ID >= 348) && (EE_CAX_MAX_ARCH_ISR_ID >= 348))
#if (EE_CAX_348_ISR_CAT == 2)
 { 348, EE_CAX_ISR2_PRI(EE_CAX_348_ISR_PRI) },
#else
 { 348, EE_CAX_ISR1_PRI(EE_CAX_348_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_349_ISR) && (EE_CAX_MAX_ISR_ID >= 349) && (EE_CAX_MAX_ARCH_ISR_ID >= 349))
#if (EE_CAX_349_ISR_CAT == 2)
 { 349, EE_CAX_ISR2_PRI(EE_CAX_349_ISR_PRI) },
#else
 { 349, EE_CAX_ISR1_PRI(EE_CAX_349_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_350_ISR) && (EE_CAX_MAX_ISR_ID >= 350) && (EE_CAX_MAX_ARCH_ISR_ID >= 350))
#if (EE_CAX_350_ISR_CAT == 2)
 { 350, EE_CAX_ISR2_PRI(EE_CAX_350_ISR_PRI) },
#else
 { 350, EE_CAX_ISR1_PRI(EE_CAX_350_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_351_ISR) && (EE_CAX_MAX_ISR_ID >= 351) && (EE_CAX_MAX_ARCH_ISR_ID >= 351))
#if (EE_CAX_351_ISR_CAT == 2)
 { 351, EE_CAX_ISR2_PRI(EE_CAX_351_ISR_PRI) },
#else
 { 351, EE_CAX_ISR1_PRI(EE_CAX_351_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_352_ISR) && (EE_CAX_MAX_ISR_ID >= 352) && (EE_CAX_MAX_ARCH_ISR_ID >= 352))
#if (EE_CAX_352_ISR_CAT == 2)
 { 352, EE_CAX_ISR2_PRI(EE_CAX_352_ISR_PRI) },
#else
 { 352, EE_CAX_ISR1_PRI(EE_CAX_352_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_353_ISR) && (EE_CAX_MAX_ISR_ID >= 353) && (EE_CAX_MAX_ARCH_ISR_ID >= 353))
#if (EE_CAX_353_ISR_CAT == 2)
 { 353, EE_CAX_ISR2_PRI(EE_CAX_353_ISR_PRI) },
#else
 { 353, EE_CAX_ISR1_PRI(EE_CAX_353_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_354_ISR) && (EE_CAX_MAX_ISR_ID >= 354) && (EE_CAX_MAX_ARCH_ISR_ID >= 354))
#if (EE_CAX_354_ISR_CAT == 2)
 { 354, EE_CAX_ISR2_PRI(EE_CAX_354_ISR_PRI) },
#else
 { 354, EE_CAX_ISR1_PRI(EE_CAX_354_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_355_ISR) && (EE_CAX_MAX_ISR_ID >= 355) && (EE_CAX_MAX_ARCH_ISR_ID >= 355))
#if (EE_CAX_355_ISR_CAT == 2)
 { 355, EE_CAX_ISR2_PRI(EE_CAX_355_ISR_PRI) },
#else
 { 355, EE_CAX_ISR1_PRI(EE_CAX_355_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_356_ISR) && (EE_CAX_MAX_ISR_ID >= 356) && (EE_CAX_MAX_ARCH_ISR_ID >= 356))
#if (EE_CAX_356_ISR_CAT == 2)
 { 356, EE_CAX_ISR2_PRI(EE_CAX_356_ISR_PRI) },
#else
 { 356, EE_CAX_ISR1_PRI(EE_CAX_356_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_357_ISR) && (EE_CAX_MAX_ISR_ID >= 357) && (EE_CAX_MAX_ARCH_ISR_ID >= 357))
#if (EE_CAX_357_ISR_CAT == 2)
 { 357, EE_CAX_ISR2_PRI(EE_CAX_357_ISR_PRI) },
#else
 { 357, EE_CAX_ISR1_PRI(EE_CAX_357_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_358_ISR) && (EE_CAX_MAX_ISR_ID >= 358) && (EE_CAX_MAX_ARCH_ISR_ID >= 358))
#if (EE_CAX_358_ISR_CAT == 2)
 { 358, EE_CAX_ISR2_PRI(EE_CAX_358_ISR_PRI) },
#else
 { 358, EE_CAX_ISR1_PRI(EE_CAX_358_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_359_ISR) && (EE_CAX_MAX_ISR_ID >= 359) && (EE_CAX_MAX_ARCH_ISR_ID >= 359))
#if (EE_CAX_359_ISR_CAT == 2)
 { 359, EE_CAX_ISR2_PRI(EE_CAX_359_ISR_PRI) },
#else
 { 359, EE_CAX_ISR1_PRI(EE_CAX_359_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_360_ISR) && (EE_CAX_MAX_ISR_ID >= 360) && (EE_CAX_MAX_ARCH_ISR_ID >= 360))
#if (EE_CAX_360_ISR_CAT == 2)
 { 360, EE_CAX_ISR2_PRI(EE_CAX_360_ISR_PRI) },
#else
 { 360, EE_CAX_ISR1_PRI(EE_CAX_360_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_361_ISR) && (EE_CAX_MAX_ISR_ID >= 361) && (EE_CAX_MAX_ARCH_ISR_ID >= 361))
#if (EE_CAX_361_ISR_CAT == 2)
 { 361, EE_CAX_ISR2_PRI(EE_CAX_361_ISR_PRI) },
#else
 { 361, EE_CAX_ISR1_PRI(EE_CAX_361_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_362_ISR) && (EE_CAX_MAX_ISR_ID >= 362) && (EE_CAX_MAX_ARCH_ISR_ID >= 362))
#if (EE_CAX_362_ISR_CAT == 2)
 { 362, EE_CAX_ISR2_PRI(EE_CAX_362_ISR_PRI) },
#else
 { 362, EE_CAX_ISR1_PRI(EE_CAX_362_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_363_ISR) && (EE_CAX_MAX_ISR_ID >= 363) && (EE_CAX_MAX_ARCH_ISR_ID >= 363))
#if (EE_CAX_363_ISR_CAT == 2)
 { 363, EE_CAX_ISR2_PRI(EE_CAX_363_ISR_PRI) },
#else
 { 363, EE_CAX_ISR1_PRI(EE_CAX_363_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_364_ISR) && (EE_CAX_MAX_ISR_ID >= 364) && (EE_CAX_MAX_ARCH_ISR_ID >= 364))
#if (EE_CAX_364_ISR_CAT == 2)
 { 364, EE_CAX_ISR2_PRI(EE_CAX_364_ISR_PRI) },
#else
 { 364, EE_CAX_ISR1_PRI(EE_CAX_364_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_365_ISR) && (EE_CAX_MAX_ISR_ID >= 365) && (EE_CAX_MAX_ARCH_ISR_ID >= 365))
#if (EE_CAX_365_ISR_CAT == 2)
 { 365, EE_CAX_ISR2_PRI(EE_CAX_365_ISR_PRI) },
#else
 { 365, EE_CAX_ISR1_PRI(EE_CAX_365_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_366_ISR) && (EE_CAX_MAX_ISR_ID >= 366) && (EE_CAX_MAX_ARCH_ISR_ID >= 366))
#if (EE_CAX_366_ISR_CAT == 2)
 { 366, EE_CAX_ISR2_PRI(EE_CAX_366_ISR_PRI) },
#else
 { 366, EE_CAX_ISR1_PRI(EE_CAX_366_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_367_ISR) && (EE_CAX_MAX_ISR_ID >= 367) && (EE_CAX_MAX_ARCH_ISR_ID >= 367))
#if (EE_CAX_367_ISR_CAT == 2)
 { 367, EE_CAX_ISR2_PRI(EE_CAX_367_ISR_PRI) },
#else
 { 367, EE_CAX_ISR1_PRI(EE_CAX_367_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_368_ISR) && (EE_CAX_MAX_ISR_ID >= 368) && (EE_CAX_MAX_ARCH_ISR_ID >= 368))
#if (EE_CAX_368_ISR_CAT == 2)
 { 368, EE_CAX_ISR2_PRI(EE_CAX_368_ISR_PRI) },
#else
 { 368, EE_CAX_ISR1_PRI(EE_CAX_368_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_369_ISR) && (EE_CAX_MAX_ISR_ID >= 369) && (EE_CAX_MAX_ARCH_ISR_ID >= 369))
#if (EE_CAX_369_ISR_CAT == 2)
 { 369, EE_CAX_ISR2_PRI(EE_CAX_369_ISR_PRI) },
#else
 { 369, EE_CAX_ISR1_PRI(EE_CAX_369_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_370_ISR) && (EE_CAX_MAX_ISR_ID >= 370) && (EE_CAX_MAX_ARCH_ISR_ID >= 370))
#if (EE_CAX_370_ISR_CAT == 2)
 { 370, EE_CAX_ISR2_PRI(EE_CAX_370_ISR_PRI) },
#else
 { 370, EE_CAX_ISR1_PRI(EE_CAX_370_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_371_ISR) && (EE_CAX_MAX_ISR_ID >= 371) && (EE_CAX_MAX_ARCH_ISR_ID >= 371))
#if (EE_CAX_371_ISR_CAT == 2)
 { 371, EE_CAX_ISR2_PRI(EE_CAX_371_ISR_PRI) },
#else
 { 371, EE_CAX_ISR1_PRI(EE_CAX_371_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_372_ISR) && (EE_CAX_MAX_ISR_ID >= 372) && (EE_CAX_MAX_ARCH_ISR_ID >= 372))
#if (EE_CAX_372_ISR_CAT == 2)
 { 372, EE_CAX_ISR2_PRI(EE_CAX_372_ISR_PRI) },
#else
 { 372, EE_CAX_ISR1_PRI(EE_CAX_372_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_373_ISR) && (EE_CAX_MAX_ISR_ID >= 373) && (EE_CAX_MAX_ARCH_ISR_ID >= 373))
#if (EE_CAX_373_ISR_CAT == 2)
 { 373, EE_CAX_ISR2_PRI(EE_CAX_373_ISR_PRI) },
#else
 { 373, EE_CAX_ISR1_PRI(EE_CAX_373_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_374_ISR) && (EE_CAX_MAX_ISR_ID >= 374) && (EE_CAX_MAX_ARCH_ISR_ID >= 374))
#if (EE_CAX_374_ISR_CAT == 2)
 { 374, EE_CAX_ISR2_PRI(EE_CAX_374_ISR_PRI) },
#else
 { 374, EE_CAX_ISR1_PRI(EE_CAX_374_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_375_ISR) && (EE_CAX_MAX_ISR_ID >= 375) && (EE_CAX_MAX_ARCH_ISR_ID >= 375))
#if (EE_CAX_375_ISR_CAT == 2)
 { 375, EE_CAX_ISR2_PRI(EE_CAX_375_ISR_PRI) },
#else
 { 375, EE_CAX_ISR1_PRI(EE_CAX_375_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_376_ISR) && (EE_CAX_MAX_ISR_ID >= 376) && (EE_CAX_MAX_ARCH_ISR_ID >= 376))
#if (EE_CAX_376_ISR_CAT == 2)
 { 376, EE_CAX_ISR2_PRI(EE_CAX_376_ISR_PRI) },
#else
 { 376, EE_CAX_ISR1_PRI(EE_CAX_376_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_377_ISR) && (EE_CAX_MAX_ISR_ID >= 377) && (EE_CAX_MAX_ARCH_ISR_ID >= 377))
#if (EE_CAX_377_ISR_CAT == 2)
 { 377, EE_CAX_ISR2_PRI(EE_CAX_377_ISR_PRI) },
#else
 { 377, EE_CAX_ISR1_PRI(EE_CAX_377_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_378_ISR) && (EE_CAX_MAX_ISR_ID >= 378) && (EE_CAX_MAX_ARCH_ISR_ID >= 378))
#if (EE_CAX_378_ISR_CAT == 2)
 { 378, EE_CAX_ISR2_PRI(EE_CAX_378_ISR_PRI) },
#else
 { 378, EE_CAX_ISR1_PRI(EE_CAX_378_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_379_ISR) && (EE_CAX_MAX_ISR_ID >= 379) && (EE_CAX_MAX_ARCH_ISR_ID >= 379))
#if (EE_CAX_379_ISR_CAT == 2)
 { 379, EE_CAX_ISR2_PRI(EE_CAX_379_ISR_PRI) },
#else
 { 379, EE_CAX_ISR1_PRI(EE_CAX_379_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_380_ISR) && (EE_CAX_MAX_ISR_ID >= 380) && (EE_CAX_MAX_ARCH_ISR_ID >= 380))
#if (EE_CAX_380_ISR_CAT == 2)
 { 380, EE_CAX_ISR2_PRI(EE_CAX_380_ISR_PRI) },
#else
 { 380, EE_CAX_ISR1_PRI(EE_CAX_380_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_381_ISR) && (EE_CAX_MAX_ISR_ID >= 381) && (EE_CAX_MAX_ARCH_ISR_ID >= 381))
#if (EE_CAX_381_ISR_CAT == 2)
 { 381, EE_CAX_ISR2_PRI(EE_CAX_381_ISR_PRI) },
#else
 { 381, EE_CAX_ISR1_PRI(EE_CAX_381_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_382_ISR) && (EE_CAX_MAX_ISR_ID >= 382) && (EE_CAX_MAX_ARCH_ISR_ID >= 382))
#if (EE_CAX_382_ISR_CAT == 2)
 { 382, EE_CAX_ISR2_PRI(EE_CAX_382_ISR_PRI) },
#else
 { 382, EE_CAX_ISR1_PRI(EE_CAX_382_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_383_ISR) && (EE_CAX_MAX_ISR_ID >= 383) && (EE_CAX_MAX_ARCH_ISR_ID >= 383))
#if (EE_CAX_383_ISR_CAT == 2)
 { 383, EE_CAX_ISR2_PRI(EE_CAX_383_ISR_PRI) },
#else
 { 383, EE_CAX_ISR1_PRI(EE_CAX_383_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_384_ISR) && (EE_CAX_MAX_ISR_ID >= 384) && (EE_CAX_MAX_ARCH_ISR_ID >= 384))
#if (EE_CAX_384_ISR_CAT == 2)
 { 384, EE_CAX_ISR2_PRI(EE_CAX_384_ISR_PRI) },
#else
 { 384, EE_CAX_ISR1_PRI(EE_CAX_384_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_385_ISR) && (EE_CAX_MAX_ISR_ID >= 385) && (EE_CAX_MAX_ARCH_ISR_ID >= 385))
#if (EE_CAX_385_ISR_CAT == 2)
 { 385, EE_CAX_ISR2_PRI(EE_CAX_385_ISR_PRI) },
#else
 { 385, EE_CAX_ISR1_PRI(EE_CAX_385_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_386_ISR) && (EE_CAX_MAX_ISR_ID >= 386) && (EE_CAX_MAX_ARCH_ISR_ID >= 386))
#if (EE_CAX_386_ISR_CAT == 2)
 { 386, EE_CAX_ISR2_PRI(EE_CAX_386_ISR_PRI) },
#else
 { 386, EE_CAX_ISR1_PRI(EE_CAX_386_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_387_ISR) && (EE_CAX_MAX_ISR_ID >= 387) && (EE_CAX_MAX_ARCH_ISR_ID >= 387))
#if (EE_CAX_387_ISR_CAT == 2)
 { 387, EE_CAX_ISR2_PRI(EE_CAX_387_ISR_PRI) },
#else
 { 387, EE_CAX_ISR1_PRI(EE_CAX_387_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_388_ISR) && (EE_CAX_MAX_ISR_ID >= 388) && (EE_CAX_MAX_ARCH_ISR_ID >= 388))
#if (EE_CAX_388_ISR_CAT == 2)
 { 388, EE_CAX_ISR2_PRI(EE_CAX_388_ISR_PRI) },
#else
 { 388, EE_CAX_ISR1_PRI(EE_CAX_388_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_389_ISR) && (EE_CAX_MAX_ISR_ID >= 389) && (EE_CAX_MAX_ARCH_ISR_ID >= 389))
#if (EE_CAX_389_ISR_CAT == 2)
 { 389, EE_CAX_ISR2_PRI(EE_CAX_389_ISR_PRI) },
#else
 { 389, EE_CAX_ISR1_PRI(EE_CAX_389_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_390_ISR) && (EE_CAX_MAX_ISR_ID >= 390) && (EE_CAX_MAX_ARCH_ISR_ID >= 390))
#if (EE_CAX_390_ISR_CAT == 2)
 { 390, EE_CAX_ISR2_PRI(EE_CAX_390_ISR_PRI) },
#else
 { 390, EE_CAX_ISR1_PRI(EE_CAX_390_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_391_ISR) && (EE_CAX_MAX_ISR_ID >= 391) && (EE_CAX_MAX_ARCH_ISR_ID >= 391))
#if (EE_CAX_391_ISR_CAT == 2)
 { 391, EE_CAX_ISR2_PRI(EE_CAX_391_ISR_PRI) },
#else
 { 391, EE_CAX_ISR1_PRI(EE_CAX_391_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_392_ISR) && (EE_CAX_MAX_ISR_ID >= 392) && (EE_CAX_MAX_ARCH_ISR_ID >= 392))
#if (EE_CAX_392_ISR_CAT == 2)
 { 392, EE_CAX_ISR2_PRI(EE_CAX_392_ISR_PRI) },
#else
 { 392, EE_CAX_ISR1_PRI(EE_CAX_392_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_393_ISR) && (EE_CAX_MAX_ISR_ID >= 393) && (EE_CAX_MAX_ARCH_ISR_ID >= 393))
#if (EE_CAX_393_ISR_CAT == 2)
 { 393, EE_CAX_ISR2_PRI(EE_CAX_393_ISR_PRI) },
#else
 { 393, EE_CAX_ISR1_PRI(EE_CAX_393_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_394_ISR) && (EE_CAX_MAX_ISR_ID >= 394) && (EE_CAX_MAX_ARCH_ISR_ID >= 394))
#if (EE_CAX_394_ISR_CAT == 2)
 { 394, EE_CAX_ISR2_PRI(EE_CAX_394_ISR_PRI) },
#else
 { 394, EE_CAX_ISR1_PRI(EE_CAX_394_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_395_ISR) && (EE_CAX_MAX_ISR_ID >= 395) && (EE_CAX_MAX_ARCH_ISR_ID >= 395))
#if (EE_CAX_395_ISR_CAT == 2)
 { 395, EE_CAX_ISR2_PRI(EE_CAX_395_ISR_PRI) },
#else
 { 395, EE_CAX_ISR1_PRI(EE_CAX_395_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_396_ISR) && (EE_CAX_MAX_ISR_ID >= 396) && (EE_CAX_MAX_ARCH_ISR_ID >= 396))
#if (EE_CAX_396_ISR_CAT == 2)
 { 396, EE_CAX_ISR2_PRI(EE_CAX_396_ISR_PRI) },
#else
 { 396, EE_CAX_ISR1_PRI(EE_CAX_396_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_397_ISR) && (EE_CAX_MAX_ISR_ID >= 397) && (EE_CAX_MAX_ARCH_ISR_ID >= 397))
#if (EE_CAX_397_ISR_CAT == 2)
 { 397, EE_CAX_ISR2_PRI(EE_CAX_397_ISR_PRI) },
#else
 { 397, EE_CAX_ISR1_PRI(EE_CAX_397_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_398_ISR) && (EE_CAX_MAX_ISR_ID >= 398) && (EE_CAX_MAX_ARCH_ISR_ID >= 398))
#if (EE_CAX_398_ISR_CAT == 2)
 { 398, EE_CAX_ISR2_PRI(EE_CAX_398_ISR_PRI) },
#else
 { 398, EE_CAX_ISR1_PRI(EE_CAX_398_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_399_ISR) && (EE_CAX_MAX_ISR_ID >= 399) && (EE_CAX_MAX_ARCH_ISR_ID >= 399))
#if (EE_CAX_399_ISR_CAT == 2)
 { 399, EE_CAX_ISR2_PRI(EE_CAX_399_ISR_PRI) },
#else
 { 399, EE_CAX_ISR1_PRI(EE_CAX_399_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_400_ISR) && (EE_CAX_MAX_ISR_ID >= 400) && (EE_CAX_MAX_ARCH_ISR_ID >= 400))
#if (EE_CAX_400_ISR_CAT == 2)
 { 400, EE_CAX_ISR2_PRI(EE_CAX_400_ISR_PRI) },
#else
 { 400, EE_CAX_ISR1_PRI(EE_CAX_400_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_401_ISR) && (EE_CAX_MAX_ISR_ID >= 401) && (EE_CAX_MAX_ARCH_ISR_ID >= 401))
#if (EE_CAX_401_ISR_CAT == 2)
 { 401, EE_CAX_ISR2_PRI(EE_CAX_401_ISR_PRI) },
#else
 { 401, EE_CAX_ISR1_PRI(EE_CAX_401_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_402_ISR) && (EE_CAX_MAX_ISR_ID >= 402) && (EE_CAX_MAX_ARCH_ISR_ID >= 402))
#if (EE_CAX_402_ISR_CAT == 2)
 { 402, EE_CAX_ISR2_PRI(EE_CAX_402_ISR_PRI) },
#else
 { 402, EE_CAX_ISR1_PRI(EE_CAX_402_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_403_ISR) && (EE_CAX_MAX_ISR_ID >= 403) && (EE_CAX_MAX_ARCH_ISR_ID >= 403))
#if (EE_CAX_403_ISR_CAT == 2)
 { 403, EE_CAX_ISR2_PRI(EE_CAX_403_ISR_PRI) },
#else
 { 403, EE_CAX_ISR1_PRI(EE_CAX_403_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_404_ISR) && (EE_CAX_MAX_ISR_ID >= 404) && (EE_CAX_MAX_ARCH_ISR_ID >= 404))
#if (EE_CAX_404_ISR_CAT == 2)
 { 404, EE_CAX_ISR2_PRI(EE_CAX_404_ISR_PRI) },
#else
 { 404, EE_CAX_ISR1_PRI(EE_CAX_404_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_405_ISR) && (EE_CAX_MAX_ISR_ID >= 405) && (EE_CAX_MAX_ARCH_ISR_ID >= 405))
#if (EE_CAX_405_ISR_CAT == 2)
 { 405, EE_CAX_ISR2_PRI(EE_CAX_405_ISR_PRI) },
#else
 { 405, EE_CAX_ISR1_PRI(EE_CAX_405_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_406_ISR) && (EE_CAX_MAX_ISR_ID >= 406) && (EE_CAX_MAX_ARCH_ISR_ID >= 406))
#if (EE_CAX_406_ISR_CAT == 2)
 { 406, EE_CAX_ISR2_PRI(EE_CAX_406_ISR_PRI) },
#else
 { 406, EE_CAX_ISR1_PRI(EE_CAX_406_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_407_ISR) && (EE_CAX_MAX_ISR_ID >= 407) && (EE_CAX_MAX_ARCH_ISR_ID >= 407))
#if (EE_CAX_407_ISR_CAT == 2)
 { 407, EE_CAX_ISR2_PRI(EE_CAX_407_ISR_PRI) },
#else
 { 407, EE_CAX_ISR1_PRI(EE_CAX_407_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_408_ISR) && (EE_CAX_MAX_ISR_ID >= 408) && (EE_CAX_MAX_ARCH_ISR_ID >= 408))
#if (EE_CAX_408_ISR_CAT == 2)
 { 408, EE_CAX_ISR2_PRI(EE_CAX_408_ISR_PRI) },
#else
 { 408, EE_CAX_ISR1_PRI(EE_CAX_408_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_409_ISR) && (EE_CAX_MAX_ISR_ID >= 409) && (EE_CAX_MAX_ARCH_ISR_ID >= 409))
#if (EE_CAX_409_ISR_CAT == 2)
 { 409, EE_CAX_ISR2_PRI(EE_CAX_409_ISR_PRI) },
#else
 { 409, EE_CAX_ISR1_PRI(EE_CAX_409_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_410_ISR) && (EE_CAX_MAX_ISR_ID >= 410) && (EE_CAX_MAX_ARCH_ISR_ID >= 410))
#if (EE_CAX_410_ISR_CAT == 2)
 { 410, EE_CAX_ISR2_PRI(EE_CAX_410_ISR_PRI) },
#else
 { 410, EE_CAX_ISR1_PRI(EE_CAX_410_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_411_ISR) && (EE_CAX_MAX_ISR_ID >= 411) && (EE_CAX_MAX_ARCH_ISR_ID >= 411))
#if (EE_CAX_411_ISR_CAT == 2)
 { 411, EE_CAX_ISR2_PRI(EE_CAX_411_ISR_PRI) },
#else
 { 411, EE_CAX_ISR1_PRI(EE_CAX_411_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_412_ISR) && (EE_CAX_MAX_ISR_ID >= 412) && (EE_CAX_MAX_ARCH_ISR_ID >= 412))
#if (EE_CAX_412_ISR_CAT == 2)
 { 412, EE_CAX_ISR2_PRI(EE_CAX_412_ISR_PRI) },
#else
 { 412, EE_CAX_ISR1_PRI(EE_CAX_412_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_413_ISR) && (EE_CAX_MAX_ISR_ID >= 413) && (EE_CAX_MAX_ARCH_ISR_ID >= 413))
#if (EE_CAX_413_ISR_CAT == 2)
 { 413, EE_CAX_ISR2_PRI(EE_CAX_413_ISR_PRI) },
#else
 { 413, EE_CAX_ISR1_PRI(EE_CAX_413_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_414_ISR) && (EE_CAX_MAX_ISR_ID >= 414) && (EE_CAX_MAX_ARCH_ISR_ID >= 414))
#if (EE_CAX_414_ISR_CAT == 2)
 { 414, EE_CAX_ISR2_PRI(EE_CAX_414_ISR_PRI) },
#else
 { 414, EE_CAX_ISR1_PRI(EE_CAX_414_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_415_ISR) && (EE_CAX_MAX_ISR_ID >= 415) && (EE_CAX_MAX_ARCH_ISR_ID >= 415))
#if (EE_CAX_415_ISR_CAT == 2)
 { 415, EE_CAX_ISR2_PRI(EE_CAX_415_ISR_PRI) },
#else
 { 415, EE_CAX_ISR1_PRI(EE_CAX_415_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_416_ISR) && (EE_CAX_MAX_ISR_ID >= 416) && (EE_CAX_MAX_ARCH_ISR_ID >= 416))
#if (EE_CAX_416_ISR_CAT == 2)
 { 416, EE_CAX_ISR2_PRI(EE_CAX_416_ISR_PRI) },
#else
 { 416, EE_CAX_ISR1_PRI(EE_CAX_416_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_417_ISR) && (EE_CAX_MAX_ISR_ID >= 417) && (EE_CAX_MAX_ARCH_ISR_ID >= 417))
#if (EE_CAX_417_ISR_CAT == 2)
 { 417, EE_CAX_ISR2_PRI(EE_CAX_417_ISR_PRI) },
#else
 { 417, EE_CAX_ISR1_PRI(EE_CAX_417_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_418_ISR) && (EE_CAX_MAX_ISR_ID >= 418) && (EE_CAX_MAX_ARCH_ISR_ID >= 418))
#if (EE_CAX_418_ISR_CAT == 2)
 { 418, EE_CAX_ISR2_PRI(EE_CAX_418_ISR_PRI) },
#else
 { 418, EE_CAX_ISR1_PRI(EE_CAX_418_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_419_ISR) && (EE_CAX_MAX_ISR_ID >= 419) && (EE_CAX_MAX_ARCH_ISR_ID >= 419))
#if (EE_CAX_419_ISR_CAT == 2)
 { 419, EE_CAX_ISR2_PRI(EE_CAX_419_ISR_PRI) },
#else
 { 419, EE_CAX_ISR1_PRI(EE_CAX_419_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_420_ISR) && (EE_CAX_MAX_ISR_ID >= 420) && (EE_CAX_MAX_ARCH_ISR_ID >= 420))
#if (EE_CAX_420_ISR_CAT == 2)
 { 420, EE_CAX_ISR2_PRI(EE_CAX_420_ISR_PRI) },
#else
 { 420, EE_CAX_ISR1_PRI(EE_CAX_420_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_421_ISR) && (EE_CAX_MAX_ISR_ID >= 421) && (EE_CAX_MAX_ARCH_ISR_ID >= 421))
#if (EE_CAX_421_ISR_CAT == 2)
 { 421, EE_CAX_ISR2_PRI(EE_CAX_421_ISR_PRI) },
#else
 { 421, EE_CAX_ISR1_PRI(EE_CAX_421_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_422_ISR) && (EE_CAX_MAX_ISR_ID >= 422) && (EE_CAX_MAX_ARCH_ISR_ID >= 422))
#if (EE_CAX_422_ISR_CAT == 2)
 { 422, EE_CAX_ISR2_PRI(EE_CAX_422_ISR_PRI) },
#else
 { 422, EE_CAX_ISR1_PRI(EE_CAX_422_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_423_ISR) && (EE_CAX_MAX_ISR_ID >= 423) && (EE_CAX_MAX_ARCH_ISR_ID >= 423))
#if (EE_CAX_423_ISR_CAT == 2)
 { 423, EE_CAX_ISR2_PRI(EE_CAX_423_ISR_PRI) },
#else
 { 423, EE_CAX_ISR1_PRI(EE_CAX_423_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_424_ISR) && (EE_CAX_MAX_ISR_ID >= 424) && (EE_CAX_MAX_ARCH_ISR_ID >= 424))
#if (EE_CAX_424_ISR_CAT == 2)
 { 424, EE_CAX_ISR2_PRI(EE_CAX_424_ISR_PRI) },
#else
 { 424, EE_CAX_ISR1_PRI(EE_CAX_424_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_425_ISR) && (EE_CAX_MAX_ISR_ID >= 425) && (EE_CAX_MAX_ARCH_ISR_ID >= 425))
#if (EE_CAX_425_ISR_CAT == 2)
 { 425, EE_CAX_ISR2_PRI(EE_CAX_425_ISR_PRI) },
#else
 { 425, EE_CAX_ISR1_PRI(EE_CAX_425_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_426_ISR) && (EE_CAX_MAX_ISR_ID >= 426) && (EE_CAX_MAX_ARCH_ISR_ID >= 426))
#if (EE_CAX_426_ISR_CAT == 2)
 { 426, EE_CAX_ISR2_PRI(EE_CAX_426_ISR_PRI) },
#else
 { 426, EE_CAX_ISR1_PRI(EE_CAX_426_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_427_ISR) && (EE_CAX_MAX_ISR_ID >= 427) && (EE_CAX_MAX_ARCH_ISR_ID >= 427))
#if (EE_CAX_427_ISR_CAT == 2)
 { 427, EE_CAX_ISR2_PRI(EE_CAX_427_ISR_PRI) },
#else
 { 427, EE_CAX_ISR1_PRI(EE_CAX_427_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_428_ISR) && (EE_CAX_MAX_ISR_ID >= 428) && (EE_CAX_MAX_ARCH_ISR_ID >= 428))
#if (EE_CAX_428_ISR_CAT == 2)
 { 428, EE_CAX_ISR2_PRI(EE_CAX_428_ISR_PRI) },
#else
 { 428, EE_CAX_ISR1_PRI(EE_CAX_428_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_429_ISR) && (EE_CAX_MAX_ISR_ID >= 429) && (EE_CAX_MAX_ARCH_ISR_ID >= 429))
#if (EE_CAX_429_ISR_CAT == 2)
 { 429, EE_CAX_ISR2_PRI(EE_CAX_429_ISR_PRI) },
#else
 { 429, EE_CAX_ISR1_PRI(EE_CAX_429_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_430_ISR) && (EE_CAX_MAX_ISR_ID >= 430) && (EE_CAX_MAX_ARCH_ISR_ID >= 430))
#if (EE_CAX_430_ISR_CAT == 2)
 { 430, EE_CAX_ISR2_PRI(EE_CAX_430_ISR_PRI) },
#else
 { 430, EE_CAX_ISR1_PRI(EE_CAX_430_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_431_ISR) && (EE_CAX_MAX_ISR_ID >= 431) && (EE_CAX_MAX_ARCH_ISR_ID >= 431))
#if (EE_CAX_431_ISR_CAT == 2)
 { 431, EE_CAX_ISR2_PRI(EE_CAX_431_ISR_PRI) },
#else
 { 431, EE_CAX_ISR1_PRI(EE_CAX_431_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_432_ISR) && (EE_CAX_MAX_ISR_ID >= 432) && (EE_CAX_MAX_ARCH_ISR_ID >= 432))
#if (EE_CAX_432_ISR_CAT == 2)
 { 432, EE_CAX_ISR2_PRI(EE_CAX_432_ISR_PRI) },
#else
 { 432, EE_CAX_ISR1_PRI(EE_CAX_432_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_433_ISR) && (EE_CAX_MAX_ISR_ID >= 433) && (EE_CAX_MAX_ARCH_ISR_ID >= 433))
#if (EE_CAX_433_ISR_CAT == 2)
 { 433, EE_CAX_ISR2_PRI(EE_CAX_433_ISR_PRI) },
#else
 { 433, EE_CAX_ISR1_PRI(EE_CAX_433_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_434_ISR) && (EE_CAX_MAX_ISR_ID >= 434) && (EE_CAX_MAX_ARCH_ISR_ID >= 434))
#if (EE_CAX_434_ISR_CAT == 2)
 { 434, EE_CAX_ISR2_PRI(EE_CAX_434_ISR_PRI) },
#else
 { 434, EE_CAX_ISR1_PRI(EE_CAX_434_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_435_ISR) && (EE_CAX_MAX_ISR_ID >= 435) && (EE_CAX_MAX_ARCH_ISR_ID >= 435))
#if (EE_CAX_435_ISR_CAT == 2)
 { 435, EE_CAX_ISR2_PRI(EE_CAX_435_ISR_PRI) },
#else
 { 435, EE_CAX_ISR1_PRI(EE_CAX_435_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_436_ISR) && (EE_CAX_MAX_ISR_ID >= 436) && (EE_CAX_MAX_ARCH_ISR_ID >= 436))
#if (EE_CAX_436_ISR_CAT == 2)
 { 436, EE_CAX_ISR2_PRI(EE_CAX_436_ISR_PRI) },
#else
 { 436, EE_CAX_ISR1_PRI(EE_CAX_436_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_437_ISR) && (EE_CAX_MAX_ISR_ID >= 437) && (EE_CAX_MAX_ARCH_ISR_ID >= 437))
#if (EE_CAX_437_ISR_CAT == 2)
 { 437, EE_CAX_ISR2_PRI(EE_CAX_437_ISR_PRI) },
#else
 { 437, EE_CAX_ISR1_PRI(EE_CAX_437_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_438_ISR) && (EE_CAX_MAX_ISR_ID >= 438) && (EE_CAX_MAX_ARCH_ISR_ID >= 438))
#if (EE_CAX_438_ISR_CAT == 2)
 { 438, EE_CAX_ISR2_PRI(EE_CAX_438_ISR_PRI) },
#else
 { 438, EE_CAX_ISR1_PRI(EE_CAX_438_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_439_ISR) && (EE_CAX_MAX_ISR_ID >= 439) && (EE_CAX_MAX_ARCH_ISR_ID >= 439))
#if (EE_CAX_439_ISR_CAT == 2)
 { 439, EE_CAX_ISR2_PRI(EE_CAX_439_ISR_PRI) },
#else
 { 439, EE_CAX_ISR1_PRI(EE_CAX_439_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_440_ISR) && (EE_CAX_MAX_ISR_ID >= 440) && (EE_CAX_MAX_ARCH_ISR_ID >= 440))
#if (EE_CAX_440_ISR_CAT == 2)
 { 440, EE_CAX_ISR2_PRI(EE_CAX_440_ISR_PRI) },
#else
 { 440, EE_CAX_ISR1_PRI(EE_CAX_440_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_441_ISR) && (EE_CAX_MAX_ISR_ID >= 441) && (EE_CAX_MAX_ARCH_ISR_ID >= 441))
#if (EE_CAX_441_ISR_CAT == 2)
 { 441, EE_CAX_ISR2_PRI(EE_CAX_441_ISR_PRI) },
#else
 { 441, EE_CAX_ISR1_PRI(EE_CAX_441_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_442_ISR) && (EE_CAX_MAX_ISR_ID >= 442) && (EE_CAX_MAX_ARCH_ISR_ID >= 442))
#if (EE_CAX_442_ISR_CAT == 2)
 { 442, EE_CAX_ISR2_PRI(EE_CAX_442_ISR_PRI) },
#else
 { 442, EE_CAX_ISR1_PRI(EE_CAX_442_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_443_ISR) && (EE_CAX_MAX_ISR_ID >= 443) && (EE_CAX_MAX_ARCH_ISR_ID >= 443))
#if (EE_CAX_443_ISR_CAT == 2)
 { 443, EE_CAX_ISR2_PRI(EE_CAX_443_ISR_PRI) },
#else
 { 443, EE_CAX_ISR1_PRI(EE_CAX_443_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_444_ISR) && (EE_CAX_MAX_ISR_ID >= 444) && (EE_CAX_MAX_ARCH_ISR_ID >= 444))
#if (EE_CAX_444_ISR_CAT == 2)
 { 444, EE_CAX_ISR2_PRI(EE_CAX_444_ISR_PRI) },
#else
 { 444, EE_CAX_ISR1_PRI(EE_CAX_444_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_445_ISR) && (EE_CAX_MAX_ISR_ID >= 445) && (EE_CAX_MAX_ARCH_ISR_ID >= 445))
#if (EE_CAX_445_ISR_CAT == 2)
 { 445, EE_CAX_ISR2_PRI(EE_CAX_445_ISR_PRI) },
#else
 { 445, EE_CAX_ISR1_PRI(EE_CAX_445_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_446_ISR) && (EE_CAX_MAX_ISR_ID >= 446) && (EE_CAX_MAX_ARCH_ISR_ID >= 446))
#if (EE_CAX_446_ISR_CAT == 2)
 { 446, EE_CAX_ISR2_PRI(EE_CAX_446_ISR_PRI) },
#else
 { 446, EE_CAX_ISR1_PRI(EE_CAX_446_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_447_ISR) && (EE_CAX_MAX_ISR_ID >= 447) && (EE_CAX_MAX_ARCH_ISR_ID >= 447))
#if (EE_CAX_447_ISR_CAT == 2)
 { 447, EE_CAX_ISR2_PRI(EE_CAX_447_ISR_PRI) },
#else
 { 447, EE_CAX_ISR1_PRI(EE_CAX_447_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_448_ISR) && (EE_CAX_MAX_ISR_ID >= 448) && (EE_CAX_MAX_ARCH_ISR_ID >= 448))
#if (EE_CAX_448_ISR_CAT == 2)
 { 448, EE_CAX_ISR2_PRI(EE_CAX_448_ISR_PRI) },
#else
 { 448, EE_CAX_ISR1_PRI(EE_CAX_448_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_449_ISR) && (EE_CAX_MAX_ISR_ID >= 449) && (EE_CAX_MAX_ARCH_ISR_ID >= 449))
#if (EE_CAX_449_ISR_CAT == 2)
 { 449, EE_CAX_ISR2_PRI(EE_CAX_449_ISR_PRI) },
#else
 { 449, EE_CAX_ISR1_PRI(EE_CAX_449_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_450_ISR) && (EE_CAX_MAX_ISR_ID >= 450) && (EE_CAX_MAX_ARCH_ISR_ID >= 450))
#if (EE_CAX_450_ISR_CAT == 2)
 { 450, EE_CAX_ISR2_PRI(EE_CAX_450_ISR_PRI) },
#else
 { 450, EE_CAX_ISR1_PRI(EE_CAX_450_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_451_ISR) && (EE_CAX_MAX_ISR_ID >= 451) && (EE_CAX_MAX_ARCH_ISR_ID >= 451))
#if (EE_CAX_451_ISR_CAT == 2)
 { 451, EE_CAX_ISR2_PRI(EE_CAX_451_ISR_PRI) },
#else
 { 451, EE_CAX_ISR1_PRI(EE_CAX_451_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_452_ISR) && (EE_CAX_MAX_ISR_ID >= 452) && (EE_CAX_MAX_ARCH_ISR_ID >= 452))
#if (EE_CAX_452_ISR_CAT == 2)
 { 452, EE_CAX_ISR2_PRI(EE_CAX_452_ISR_PRI) },
#else
 { 452, EE_CAX_ISR1_PRI(EE_CAX_452_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_453_ISR) && (EE_CAX_MAX_ISR_ID >= 453) && (EE_CAX_MAX_ARCH_ISR_ID >= 453))
#if (EE_CAX_453_ISR_CAT == 2)
 { 453, EE_CAX_ISR2_PRI(EE_CAX_453_ISR_PRI) },
#else
 { 453, EE_CAX_ISR1_PRI(EE_CAX_453_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_454_ISR) && (EE_CAX_MAX_ISR_ID >= 454) && (EE_CAX_MAX_ARCH_ISR_ID >= 454))
#if (EE_CAX_454_ISR_CAT == 2)
 { 454, EE_CAX_ISR2_PRI(EE_CAX_454_ISR_PRI) },
#else
 { 454, EE_CAX_ISR1_PRI(EE_CAX_454_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_455_ISR) && (EE_CAX_MAX_ISR_ID >= 455) && (EE_CAX_MAX_ARCH_ISR_ID >= 455))
#if (EE_CAX_455_ISR_CAT == 2)
 { 455, EE_CAX_ISR2_PRI(EE_CAX_455_ISR_PRI) },
#else
 { 455, EE_CAX_ISR1_PRI(EE_CAX_455_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_456_ISR) && (EE_CAX_MAX_ISR_ID >= 456) && (EE_CAX_MAX_ARCH_ISR_ID >= 456))
#if (EE_CAX_456_ISR_CAT == 2)
 { 456, EE_CAX_ISR2_PRI(EE_CAX_456_ISR_PRI) },
#else
 { 456, EE_CAX_ISR1_PRI(EE_CAX_456_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_457_ISR) && (EE_CAX_MAX_ISR_ID >= 457) && (EE_CAX_MAX_ARCH_ISR_ID >= 457))
#if (EE_CAX_457_ISR_CAT == 2)
 { 457, EE_CAX_ISR2_PRI(EE_CAX_457_ISR_PRI) },
#else
 { 457, EE_CAX_ISR1_PRI(EE_CAX_457_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_458_ISR) && (EE_CAX_MAX_ISR_ID >= 458) && (EE_CAX_MAX_ARCH_ISR_ID >= 458))
#if (EE_CAX_458_ISR_CAT == 2)
 { 458, EE_CAX_ISR2_PRI(EE_CAX_458_ISR_PRI) },
#else
 { 458, EE_CAX_ISR1_PRI(EE_CAX_458_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_459_ISR) && (EE_CAX_MAX_ISR_ID >= 459) && (EE_CAX_MAX_ARCH_ISR_ID >= 459))
#if (EE_CAX_459_ISR_CAT == 2)
 { 459, EE_CAX_ISR2_PRI(EE_CAX_459_ISR_PRI) },
#else
 { 459, EE_CAX_ISR1_PRI(EE_CAX_459_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_460_ISR) && (EE_CAX_MAX_ISR_ID >= 460) && (EE_CAX_MAX_ARCH_ISR_ID >= 460))
#if (EE_CAX_460_ISR_CAT == 2)
 { 460, EE_CAX_ISR2_PRI(EE_CAX_460_ISR_PRI) },
#else
 { 460, EE_CAX_ISR1_PRI(EE_CAX_460_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_461_ISR) && (EE_CAX_MAX_ISR_ID >= 461) && (EE_CAX_MAX_ARCH_ISR_ID >= 461))
#if (EE_CAX_461_ISR_CAT == 2)
 { 461, EE_CAX_ISR2_PRI(EE_CAX_461_ISR_PRI) },
#else
 { 461, EE_CAX_ISR1_PRI(EE_CAX_461_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_462_ISR) && (EE_CAX_MAX_ISR_ID >= 462) && (EE_CAX_MAX_ARCH_ISR_ID >= 462))
#if (EE_CAX_462_ISR_CAT == 2)
 { 462, EE_CAX_ISR2_PRI(EE_CAX_462_ISR_PRI) },
#else
 { 462, EE_CAX_ISR1_PRI(EE_CAX_462_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_463_ISR) && (EE_CAX_MAX_ISR_ID >= 463) && (EE_CAX_MAX_ARCH_ISR_ID >= 463))
#if (EE_CAX_463_ISR_CAT == 2)
 { 463, EE_CAX_ISR2_PRI(EE_CAX_463_ISR_PRI) },
#else
 { 463, EE_CAX_ISR1_PRI(EE_CAX_463_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_464_ISR) && (EE_CAX_MAX_ISR_ID >= 464) && (EE_CAX_MAX_ARCH_ISR_ID >= 464))
#if (EE_CAX_464_ISR_CAT == 2)
 { 464, EE_CAX_ISR2_PRI(EE_CAX_464_ISR_PRI) },
#else
 { 464, EE_CAX_ISR1_PRI(EE_CAX_464_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_465_ISR) && (EE_CAX_MAX_ISR_ID >= 465) && (EE_CAX_MAX_ARCH_ISR_ID >= 465))
#if (EE_CAX_465_ISR_CAT == 2)
 { 465, EE_CAX_ISR2_PRI(EE_CAX_465_ISR_PRI) },
#else
 { 465, EE_CAX_ISR1_PRI(EE_CAX_465_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_466_ISR) && (EE_CAX_MAX_ISR_ID >= 466) && (EE_CAX_MAX_ARCH_ISR_ID >= 466))
#if (EE_CAX_466_ISR_CAT == 2)
 { 466, EE_CAX_ISR2_PRI(EE_CAX_466_ISR_PRI) },
#else
 { 466, EE_CAX_ISR1_PRI(EE_CAX_466_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_467_ISR) && (EE_CAX_MAX_ISR_ID >= 467) && (EE_CAX_MAX_ARCH_ISR_ID >= 467))
#if (EE_CAX_467_ISR_CAT == 2)
 { 467, EE_CAX_ISR2_PRI(EE_CAX_467_ISR_PRI) },
#else
 { 467, EE_CAX_ISR1_PRI(EE_CAX_467_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_468_ISR) && (EE_CAX_MAX_ISR_ID >= 468) && (EE_CAX_MAX_ARCH_ISR_ID >= 468))
#if (EE_CAX_468_ISR_CAT == 2)
 { 468, EE_CAX_ISR2_PRI(EE_CAX_468_ISR_PRI) },
#else
 { 468, EE_CAX_ISR1_PRI(EE_CAX_468_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_469_ISR) && (EE_CAX_MAX_ISR_ID >= 469) && (EE_CAX_MAX_ARCH_ISR_ID >= 469))
#if (EE_CAX_469_ISR_CAT == 2)
 { 469, EE_CAX_ISR2_PRI(EE_CAX_469_ISR_PRI) },
#else
 { 469, EE_CAX_ISR1_PRI(EE_CAX_469_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_470_ISR) && (EE_CAX_MAX_ISR_ID >= 470) && (EE_CAX_MAX_ARCH_ISR_ID >= 470))
#if (EE_CAX_470_ISR_CAT == 2)
 { 470, EE_CAX_ISR2_PRI(EE_CAX_470_ISR_PRI) },
#else
 { 470, EE_CAX_ISR1_PRI(EE_CAX_470_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_471_ISR) && (EE_CAX_MAX_ISR_ID >= 471) && (EE_CAX_MAX_ARCH_ISR_ID >= 471))
#if (EE_CAX_471_ISR_CAT == 2)
 { 471, EE_CAX_ISR2_PRI(EE_CAX_471_ISR_PRI) },
#else
 { 471, EE_CAX_ISR1_PRI(EE_CAX_471_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_472_ISR) && (EE_CAX_MAX_ISR_ID >= 472) && (EE_CAX_MAX_ARCH_ISR_ID >= 472))
#if (EE_CAX_472_ISR_CAT == 2)
 { 472, EE_CAX_ISR2_PRI(EE_CAX_472_ISR_PRI) },
#else
 { 472, EE_CAX_ISR1_PRI(EE_CAX_472_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_473_ISR) && (EE_CAX_MAX_ISR_ID >= 473) && (EE_CAX_MAX_ARCH_ISR_ID >= 473))
#if (EE_CAX_473_ISR_CAT == 2)
 { 473, EE_CAX_ISR2_PRI(EE_CAX_473_ISR_PRI) },
#else
 { 473, EE_CAX_ISR1_PRI(EE_CAX_473_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_474_ISR) && (EE_CAX_MAX_ISR_ID >= 474) && (EE_CAX_MAX_ARCH_ISR_ID >= 474))
#if (EE_CAX_474_ISR_CAT == 2)
 { 474, EE_CAX_ISR2_PRI(EE_CAX_474_ISR_PRI) },
#else
 { 474, EE_CAX_ISR1_PRI(EE_CAX_474_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_475_ISR) && (EE_CAX_MAX_ISR_ID >= 475) && (EE_CAX_MAX_ARCH_ISR_ID >= 475))
#if (EE_CAX_475_ISR_CAT == 2)
 { 475, EE_CAX_ISR2_PRI(EE_CAX_475_ISR_PRI) },
#else
 { 475, EE_CAX_ISR1_PRI(EE_CAX_475_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_476_ISR) && (EE_CAX_MAX_ISR_ID >= 476) && (EE_CAX_MAX_ARCH_ISR_ID >= 476))
#if (EE_CAX_476_ISR_CAT == 2)
 { 476, EE_CAX_ISR2_PRI(EE_CAX_476_ISR_PRI) },
#else
 { 476, EE_CAX_ISR1_PRI(EE_CAX_476_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_477_ISR) && (EE_CAX_MAX_ISR_ID >= 477) && (EE_CAX_MAX_ARCH_ISR_ID >= 477))
#if (EE_CAX_477_ISR_CAT == 2)
 { 477, EE_CAX_ISR2_PRI(EE_CAX_477_ISR_PRI) },
#else
 { 477, EE_CAX_ISR1_PRI(EE_CAX_477_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_478_ISR) && (EE_CAX_MAX_ISR_ID >= 478) && (EE_CAX_MAX_ARCH_ISR_ID >= 478))
#if (EE_CAX_478_ISR_CAT == 2)
 { 478, EE_CAX_ISR2_PRI(EE_CAX_478_ISR_PRI) },
#else
 { 478, EE_CAX_ISR1_PRI(EE_CAX_478_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_479_ISR) && (EE_CAX_MAX_ISR_ID >= 479) && (EE_CAX_MAX_ARCH_ISR_ID >= 479))
#if (EE_CAX_479_ISR_CAT == 2)
 { 479, EE_CAX_ISR2_PRI(EE_CAX_479_ISR_PRI) },
#else
 { 479, EE_CAX_ISR1_PRI(EE_CAX_479_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_480_ISR) && (EE_CAX_MAX_ISR_ID >= 480) && (EE_CAX_MAX_ARCH_ISR_ID >= 480))
#if (EE_CAX_480_ISR_CAT == 2)
 { 480, EE_CAX_ISR2_PRI(EE_CAX_480_ISR_PRI) },
#else
 { 480, EE_CAX_ISR1_PRI(EE_CAX_480_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_481_ISR) && (EE_CAX_MAX_ISR_ID >= 481) && (EE_CAX_MAX_ARCH_ISR_ID >= 481))
#if (EE_CAX_481_ISR_CAT == 2)
 { 481, EE_CAX_ISR2_PRI(EE_CAX_481_ISR_PRI) },
#else
 { 481, EE_CAX_ISR1_PRI(EE_CAX_481_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_482_ISR) && (EE_CAX_MAX_ISR_ID >= 482) && (EE_CAX_MAX_ARCH_ISR_ID >= 482))
#if (EE_CAX_482_ISR_CAT == 2)
 { 482, EE_CAX_ISR2_PRI(EE_CAX_482_ISR_PRI) },
#else
 { 482, EE_CAX_ISR1_PRI(EE_CAX_482_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_483_ISR) && (EE_CAX_MAX_ISR_ID >= 483) && (EE_CAX_MAX_ARCH_ISR_ID >= 483))
#if (EE_CAX_483_ISR_CAT == 2)
 { 483, EE_CAX_ISR2_PRI(EE_CAX_483_ISR_PRI) },
#else
 { 483, EE_CAX_ISR1_PRI(EE_CAX_483_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_484_ISR) && (EE_CAX_MAX_ISR_ID >= 484) && (EE_CAX_MAX_ARCH_ISR_ID >= 484))
#if (EE_CAX_484_ISR_CAT == 2)
 { 484, EE_CAX_ISR2_PRI(EE_CAX_484_ISR_PRI) },
#else
 { 484, EE_CAX_ISR1_PRI(EE_CAX_484_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_485_ISR) && (EE_CAX_MAX_ISR_ID >= 485) && (EE_CAX_MAX_ARCH_ISR_ID >= 485))
#if (EE_CAX_485_ISR_CAT == 2)
 { 485, EE_CAX_ISR2_PRI(EE_CAX_485_ISR_PRI) },
#else
 { 485, EE_CAX_ISR1_PRI(EE_CAX_485_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_486_ISR) && (EE_CAX_MAX_ISR_ID >= 486) && (EE_CAX_MAX_ARCH_ISR_ID >= 486))
#if (EE_CAX_486_ISR_CAT == 2)
 { 486, EE_CAX_ISR2_PRI(EE_CAX_486_ISR_PRI) },
#else
 { 486, EE_CAX_ISR1_PRI(EE_CAX_486_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_487_ISR) && (EE_CAX_MAX_ISR_ID >= 487) && (EE_CAX_MAX_ARCH_ISR_ID >= 487))
#if (EE_CAX_487_ISR_CAT == 2)
 { 487, EE_CAX_ISR2_PRI(EE_CAX_487_ISR_PRI) },
#else
 { 487, EE_CAX_ISR1_PRI(EE_CAX_487_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_488_ISR) && (EE_CAX_MAX_ISR_ID >= 488) && (EE_CAX_MAX_ARCH_ISR_ID >= 488))
#if (EE_CAX_488_ISR_CAT == 2)
 { 488, EE_CAX_ISR2_PRI(EE_CAX_488_ISR_PRI) },
#else
 { 488, EE_CAX_ISR1_PRI(EE_CAX_488_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_489_ISR) && (EE_CAX_MAX_ISR_ID >= 489) && (EE_CAX_MAX_ARCH_ISR_ID >= 489))
#if (EE_CAX_489_ISR_CAT == 2)
 { 489, EE_CAX_ISR2_PRI(EE_CAX_489_ISR_PRI) },
#else
 { 489, EE_CAX_ISR1_PRI(EE_CAX_489_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_490_ISR) && (EE_CAX_MAX_ISR_ID >= 490) && (EE_CAX_MAX_ARCH_ISR_ID >= 490))
#if (EE_CAX_490_ISR_CAT == 2)
 { 490, EE_CAX_ISR2_PRI(EE_CAX_490_ISR_PRI) },
#else
 { 490, EE_CAX_ISR1_PRI(EE_CAX_490_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_491_ISR) && (EE_CAX_MAX_ISR_ID >= 491) && (EE_CAX_MAX_ARCH_ISR_ID >= 491))
#if (EE_CAX_491_ISR_CAT == 2)
 { 491, EE_CAX_ISR2_PRI(EE_CAX_491_ISR_PRI) },
#else
 { 491, EE_CAX_ISR1_PRI(EE_CAX_491_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_492_ISR) && (EE_CAX_MAX_ISR_ID >= 492) && (EE_CAX_MAX_ARCH_ISR_ID >= 492))
#if (EE_CAX_492_ISR_CAT == 2)
 { 492, EE_CAX_ISR2_PRI(EE_CAX_492_ISR_PRI) },
#else
 { 492, EE_CAX_ISR1_PRI(EE_CAX_492_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_493_ISR) && (EE_CAX_MAX_ISR_ID >= 493) && (EE_CAX_MAX_ARCH_ISR_ID >= 493))
#if (EE_CAX_493_ISR_CAT == 2)
 { 493, EE_CAX_ISR2_PRI(EE_CAX_493_ISR_PRI) },
#else
 { 493, EE_CAX_ISR1_PRI(EE_CAX_493_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_494_ISR) && (EE_CAX_MAX_ISR_ID >= 494) && (EE_CAX_MAX_ARCH_ISR_ID >= 494))
#if (EE_CAX_494_ISR_CAT == 2)
 { 494, EE_CAX_ISR2_PRI(EE_CAX_494_ISR_PRI) },
#else
 { 494, EE_CAX_ISR1_PRI(EE_CAX_494_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_495_ISR) && (EE_CAX_MAX_ISR_ID >= 495) && (EE_CAX_MAX_ARCH_ISR_ID >= 495))
#if (EE_CAX_495_ISR_CAT == 2)
 { 495, EE_CAX_ISR2_PRI(EE_CAX_495_ISR_PRI) },
#else
 { 495, EE_CAX_ISR1_PRI(EE_CAX_495_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_496_ISR) && (EE_CAX_MAX_ISR_ID >= 496) && (EE_CAX_MAX_ARCH_ISR_ID >= 496))
#if (EE_CAX_496_ISR_CAT == 2)
 { 496, EE_CAX_ISR2_PRI(EE_CAX_496_ISR_PRI) },
#else
 { 496, EE_CAX_ISR1_PRI(EE_CAX_496_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_497_ISR) && (EE_CAX_MAX_ISR_ID >= 497) && (EE_CAX_MAX_ARCH_ISR_ID >= 497))
#if (EE_CAX_497_ISR_CAT == 2)
 { 497, EE_CAX_ISR2_PRI(EE_CAX_497_ISR_PRI) },
#else
 { 497, EE_CAX_ISR1_PRI(EE_CAX_497_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_498_ISR) && (EE_CAX_MAX_ISR_ID >= 498) && (EE_CAX_MAX_ARCH_ISR_ID >= 498))
#if (EE_CAX_498_ISR_CAT == 2)
 { 498, EE_CAX_ISR2_PRI(EE_CAX_498_ISR_PRI) },
#else
 { 498, EE_CAX_ISR1_PRI(EE_CAX_498_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_499_ISR) && (EE_CAX_MAX_ISR_ID >= 499) && (EE_CAX_MAX_ARCH_ISR_ID >= 499))
#if (EE_CAX_499_ISR_CAT == 2)
 { 499, EE_CAX_ISR2_PRI(EE_CAX_499_ISR_PRI) },
#else
 { 499, EE_CAX_ISR1_PRI(EE_CAX_499_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_500_ISR) && (EE_CAX_MAX_ISR_ID >= 500) && (EE_CAX_MAX_ARCH_ISR_ID >= 500))
#if (EE_CAX_500_ISR_CAT == 2)
 { 500, EE_CAX_ISR2_PRI(EE_CAX_500_ISR_PRI) },
#else
 { 500, EE_CAX_ISR1_PRI(EE_CAX_500_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_501_ISR) && (EE_CAX_MAX_ISR_ID >= 501) && (EE_CAX_MAX_ARCH_ISR_ID >= 501))
#if (EE_CAX_501_ISR_CAT == 2)
 { 501, EE_CAX_ISR2_PRI(EE_CAX_501_ISR_PRI) },
#else
 { 501, EE_CAX_ISR1_PRI(EE_CAX_501_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_502_ISR) && (EE_CAX_MAX_ISR_ID >= 502) && (EE_CAX_MAX_ARCH_ISR_ID >= 502))
#if (EE_CAX_502_ISR_CAT == 2)
 { 502, EE_CAX_ISR2_PRI(EE_CAX_502_ISR_PRI) },
#else
 { 502, EE_CAX_ISR1_PRI(EE_CAX_502_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_503_ISR) && (EE_CAX_MAX_ISR_ID >= 503) && (EE_CAX_MAX_ARCH_ISR_ID >= 503))
#if (EE_CAX_503_ISR_CAT == 2)
 { 503, EE_CAX_ISR2_PRI(EE_CAX_503_ISR_PRI) },
#else
 { 503, EE_CAX_ISR1_PRI(EE_CAX_503_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_504_ISR) && (EE_CAX_MAX_ISR_ID >= 504) && (EE_CAX_MAX_ARCH_ISR_ID >= 504))
#if (EE_CAX_504_ISR_CAT == 2)
 { 504, EE_CAX_ISR2_PRI(EE_CAX_504_ISR_PRI) },
#else
 { 504, EE_CAX_ISR1_PRI(EE_CAX_504_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_505_ISR) && (EE_CAX_MAX_ISR_ID >= 505) && (EE_CAX_MAX_ARCH_ISR_ID >= 505))
#if (EE_CAX_505_ISR_CAT == 2)
 { 505, EE_CAX_ISR2_PRI(EE_CAX_505_ISR_PRI) },
#else
 { 505, EE_CAX_ISR1_PRI(EE_CAX_505_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_506_ISR) && (EE_CAX_MAX_ISR_ID >= 506) && (EE_CAX_MAX_ARCH_ISR_ID >= 506))
#if (EE_CAX_506_ISR_CAT == 2)
 { 506, EE_CAX_ISR2_PRI(EE_CAX_506_ISR_PRI) },
#else
 { 506, EE_CAX_ISR1_PRI(EE_CAX_506_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_507_ISR) && (EE_CAX_MAX_ISR_ID >= 507) && (EE_CAX_MAX_ARCH_ISR_ID >= 507))
#if (EE_CAX_507_ISR_CAT == 2)
 { 507, EE_CAX_ISR2_PRI(EE_CAX_507_ISR_PRI) },
#else
 { 507, EE_CAX_ISR1_PRI(EE_CAX_507_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_508_ISR) && (EE_CAX_MAX_ISR_ID >= 508) && (EE_CAX_MAX_ARCH_ISR_ID >= 508))
#if (EE_CAX_508_ISR_CAT == 2)
 { 508, EE_CAX_ISR2_PRI(EE_CAX_508_ISR_PRI) },
#else
 { 508, EE_CAX_ISR1_PRI(EE_CAX_508_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_509_ISR) && (EE_CAX_MAX_ISR_ID >= 509) && (EE_CAX_MAX_ARCH_ISR_ID >= 509))
#if (EE_CAX_509_ISR_CAT == 2)
 { 509, EE_CAX_ISR2_PRI(EE_CAX_509_ISR_PRI) },
#else
 { 509, EE_CAX_ISR1_PRI(EE_CAX_509_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_510_ISR) && (EE_CAX_MAX_ISR_ID >= 510) && (EE_CAX_MAX_ARCH_ISR_ID >= 510))
#if (EE_CAX_510_ISR_CAT == 2)
 { 510, EE_CAX_ISR2_PRI(EE_CAX_510_ISR_PRI) },
#else
 { 510, EE_CAX_ISR1_PRI(EE_CAX_510_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_511_ISR) && (EE_CAX_MAX_ISR_ID >= 511) && (EE_CAX_MAX_ARCH_ISR_ID >= 511))
#if (EE_CAX_511_ISR_CAT == 2)
 { 511, EE_CAX_ISR2_PRI(EE_CAX_511_ISR_PRI) },
#else
 { 511, EE_CAX_ISR1_PRI(EE_CAX_511_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_512_ISR) && (EE_CAX_MAX_ISR_ID >= 512) && (EE_CAX_MAX_ARCH_ISR_ID >= 512))
#if (EE_CAX_512_ISR_CAT == 2)
 { 512, EE_CAX_ISR2_PRI(EE_CAX_512_ISR_PRI) },
#else
 { 512, EE_CAX_ISR1_PRI(EE_CAX_512_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_513_ISR) && (EE_CAX_MAX_ISR_ID >= 513) && (EE_CAX_MAX_ARCH_ISR_ID >= 513))
#if (EE_CAX_513_ISR_CAT == 2)
 { 513, EE_CAX_ISR2_PRI(EE_CAX_513_ISR_PRI) },
#else
 { 513, EE_CAX_ISR1_PRI(EE_CAX_513_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_514_ISR) && (EE_CAX_MAX_ISR_ID >= 514) && (EE_CAX_MAX_ARCH_ISR_ID >= 514))
#if (EE_CAX_514_ISR_CAT == 2)
 { 514, EE_CAX_ISR2_PRI(EE_CAX_514_ISR_PRI) },
#else
 { 514, EE_CAX_ISR1_PRI(EE_CAX_514_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_515_ISR) && (EE_CAX_MAX_ISR_ID >= 515) && (EE_CAX_MAX_ARCH_ISR_ID >= 515))
#if (EE_CAX_515_ISR_CAT == 2)
 { 515, EE_CAX_ISR2_PRI(EE_CAX_515_ISR_PRI) },
#else
 { 515, EE_CAX_ISR1_PRI(EE_CAX_515_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_516_ISR) && (EE_CAX_MAX_ISR_ID >= 516) && (EE_CAX_MAX_ARCH_ISR_ID >= 516))
#if (EE_CAX_516_ISR_CAT == 2)
 { 516, EE_CAX_ISR2_PRI(EE_CAX_516_ISR_PRI) },
#else
 { 516, EE_CAX_ISR1_PRI(EE_CAX_516_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_517_ISR) && (EE_CAX_MAX_ISR_ID >= 517) && (EE_CAX_MAX_ARCH_ISR_ID >= 517))
#if (EE_CAX_517_ISR_CAT == 2)
 { 517, EE_CAX_ISR2_PRI(EE_CAX_517_ISR_PRI) },
#else
 { 517, EE_CAX_ISR1_PRI(EE_CAX_517_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_518_ISR) && (EE_CAX_MAX_ISR_ID >= 518) && (EE_CAX_MAX_ARCH_ISR_ID >= 518))
#if (EE_CAX_518_ISR_CAT == 2)
 { 518, EE_CAX_ISR2_PRI(EE_CAX_518_ISR_PRI) },
#else
 { 518, EE_CAX_ISR1_PRI(EE_CAX_518_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_519_ISR) && (EE_CAX_MAX_ISR_ID >= 519) && (EE_CAX_MAX_ARCH_ISR_ID >= 519))
#if (EE_CAX_519_ISR_CAT == 2)
 { 519, EE_CAX_ISR2_PRI(EE_CAX_519_ISR_PRI) },
#else
 { 519, EE_CAX_ISR1_PRI(EE_CAX_519_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_520_ISR) && (EE_CAX_MAX_ISR_ID >= 520) && (EE_CAX_MAX_ARCH_ISR_ID >= 520))
#if (EE_CAX_520_ISR_CAT == 2)
 { 520, EE_CAX_ISR2_PRI(EE_CAX_520_ISR_PRI) },
#else
 { 520, EE_CAX_ISR1_PRI(EE_CAX_520_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_521_ISR) && (EE_CAX_MAX_ISR_ID >= 521) && (EE_CAX_MAX_ARCH_ISR_ID >= 521))
#if (EE_CAX_521_ISR_CAT == 2)
 { 521, EE_CAX_ISR2_PRI(EE_CAX_521_ISR_PRI) },
#else
 { 521, EE_CAX_ISR1_PRI(EE_CAX_521_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_522_ISR) && (EE_CAX_MAX_ISR_ID >= 522) && (EE_CAX_MAX_ARCH_ISR_ID >= 522))
#if (EE_CAX_522_ISR_CAT == 2)
 { 522, EE_CAX_ISR2_PRI(EE_CAX_522_ISR_PRI) },
#else
 { 522, EE_CAX_ISR1_PRI(EE_CAX_522_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_523_ISR) && (EE_CAX_MAX_ISR_ID >= 523) && (EE_CAX_MAX_ARCH_ISR_ID >= 523))
#if (EE_CAX_523_ISR_CAT == 2)
 { 523, EE_CAX_ISR2_PRI(EE_CAX_523_ISR_PRI) },
#else
 { 523, EE_CAX_ISR1_PRI(EE_CAX_523_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_524_ISR) && (EE_CAX_MAX_ISR_ID >= 524) && (EE_CAX_MAX_ARCH_ISR_ID >= 524))
#if (EE_CAX_524_ISR_CAT == 2)
 { 524, EE_CAX_ISR2_PRI(EE_CAX_524_ISR_PRI) },
#else
 { 524, EE_CAX_ISR1_PRI(EE_CAX_524_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_525_ISR) && (EE_CAX_MAX_ISR_ID >= 525) && (EE_CAX_MAX_ARCH_ISR_ID >= 525))
#if (EE_CAX_525_ISR_CAT == 2)
 { 525, EE_CAX_ISR2_PRI(EE_CAX_525_ISR_PRI) },
#else
 { 525, EE_CAX_ISR1_PRI(EE_CAX_525_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_526_ISR) && (EE_CAX_MAX_ISR_ID >= 526) && (EE_CAX_MAX_ARCH_ISR_ID >= 526))
#if (EE_CAX_526_ISR_CAT == 2)
 { 526, EE_CAX_ISR2_PRI(EE_CAX_526_ISR_PRI) },
#else
 { 526, EE_CAX_ISR1_PRI(EE_CAX_526_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_527_ISR) && (EE_CAX_MAX_ISR_ID >= 527) && (EE_CAX_MAX_ARCH_ISR_ID >= 527))
#if (EE_CAX_527_ISR_CAT == 2)
 { 527, EE_CAX_ISR2_PRI(EE_CAX_527_ISR_PRI) },
#else
 { 527, EE_CAX_ISR1_PRI(EE_CAX_527_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_528_ISR) && (EE_CAX_MAX_ISR_ID >= 528) && (EE_CAX_MAX_ARCH_ISR_ID >= 528))
#if (EE_CAX_528_ISR_CAT == 2)
 { 528, EE_CAX_ISR2_PRI(EE_CAX_528_ISR_PRI) },
#else
 { 528, EE_CAX_ISR1_PRI(EE_CAX_528_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_529_ISR) && (EE_CAX_MAX_ISR_ID >= 529) && (EE_CAX_MAX_ARCH_ISR_ID >= 529))
#if (EE_CAX_529_ISR_CAT == 2)
 { 529, EE_CAX_ISR2_PRI(EE_CAX_529_ISR_PRI) },
#else
 { 529, EE_CAX_ISR1_PRI(EE_CAX_529_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_530_ISR) && (EE_CAX_MAX_ISR_ID >= 530) && (EE_CAX_MAX_ARCH_ISR_ID >= 530))
#if (EE_CAX_530_ISR_CAT == 2)
 { 530, EE_CAX_ISR2_PRI(EE_CAX_530_ISR_PRI) },
#else
 { 530, EE_CAX_ISR1_PRI(EE_CAX_530_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_531_ISR) && (EE_CAX_MAX_ISR_ID >= 531) && (EE_CAX_MAX_ARCH_ISR_ID >= 531))
#if (EE_CAX_531_ISR_CAT == 2)
 { 531, EE_CAX_ISR2_PRI(EE_CAX_531_ISR_PRI) },
#else
 { 531, EE_CAX_ISR1_PRI(EE_CAX_531_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_532_ISR) && (EE_CAX_MAX_ISR_ID >= 532) && (EE_CAX_MAX_ARCH_ISR_ID >= 532))
#if (EE_CAX_532_ISR_CAT == 2)
 { 532, EE_CAX_ISR2_PRI(EE_CAX_532_ISR_PRI) },
#else
 { 532, EE_CAX_ISR1_PRI(EE_CAX_532_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_533_ISR) && (EE_CAX_MAX_ISR_ID >= 533) && (EE_CAX_MAX_ARCH_ISR_ID >= 533))
#if (EE_CAX_533_ISR_CAT == 2)
 { 533, EE_CAX_ISR2_PRI(EE_CAX_533_ISR_PRI) },
#else
 { 533, EE_CAX_ISR1_PRI(EE_CAX_533_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_534_ISR) && (EE_CAX_MAX_ISR_ID >= 534) && (EE_CAX_MAX_ARCH_ISR_ID >= 534))
#if (EE_CAX_534_ISR_CAT == 2)
 { 534, EE_CAX_ISR2_PRI(EE_CAX_534_ISR_PRI) },
#else
 { 534, EE_CAX_ISR1_PRI(EE_CAX_534_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_535_ISR) && (EE_CAX_MAX_ISR_ID >= 535) && (EE_CAX_MAX_ARCH_ISR_ID >= 535))
#if (EE_CAX_535_ISR_CAT == 2)
 { 535, EE_CAX_ISR2_PRI(EE_CAX_535_ISR_PRI) },
#else
 { 535, EE_CAX_ISR1_PRI(EE_CAX_535_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_536_ISR) && (EE_CAX_MAX_ISR_ID >= 536) && (EE_CAX_MAX_ARCH_ISR_ID >= 536))
#if (EE_CAX_536_ISR_CAT == 2)
 { 536, EE_CAX_ISR2_PRI(EE_CAX_536_ISR_PRI) },
#else
 { 536, EE_CAX_ISR1_PRI(EE_CAX_536_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_537_ISR) && (EE_CAX_MAX_ISR_ID >= 537) && (EE_CAX_MAX_ARCH_ISR_ID >= 537))
#if (EE_CAX_537_ISR_CAT == 2)
 { 537, EE_CAX_ISR2_PRI(EE_CAX_537_ISR_PRI) },
#else
 { 537, EE_CAX_ISR1_PRI(EE_CAX_537_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_538_ISR) && (EE_CAX_MAX_ISR_ID >= 538) && (EE_CAX_MAX_ARCH_ISR_ID >= 538))
#if (EE_CAX_538_ISR_CAT == 2)
 { 538, EE_CAX_ISR2_PRI(EE_CAX_538_ISR_PRI) },
#else
 { 538, EE_CAX_ISR1_PRI(EE_CAX_538_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_539_ISR) && (EE_CAX_MAX_ISR_ID >= 539) && (EE_CAX_MAX_ARCH_ISR_ID >= 539))
#if (EE_CAX_539_ISR_CAT == 2)
 { 539, EE_CAX_ISR2_PRI(EE_CAX_539_ISR_PRI) },
#else
 { 539, EE_CAX_ISR1_PRI(EE_CAX_539_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_540_ISR) && (EE_CAX_MAX_ISR_ID >= 540) && (EE_CAX_MAX_ARCH_ISR_ID >= 540))
#if (EE_CAX_540_ISR_CAT == 2)
 { 540, EE_CAX_ISR2_PRI(EE_CAX_540_ISR_PRI) },
#else
 { 540, EE_CAX_ISR1_PRI(EE_CAX_540_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_541_ISR) && (EE_CAX_MAX_ISR_ID >= 541) && (EE_CAX_MAX_ARCH_ISR_ID >= 541))
#if (EE_CAX_541_ISR_CAT == 2)
 { 541, EE_CAX_ISR2_PRI(EE_CAX_541_ISR_PRI) },
#else
 { 541, EE_CAX_ISR1_PRI(EE_CAX_541_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_542_ISR) && (EE_CAX_MAX_ISR_ID >= 542) && (EE_CAX_MAX_ARCH_ISR_ID >= 542))
#if (EE_CAX_542_ISR_CAT == 2)
 { 542, EE_CAX_ISR2_PRI(EE_CAX_542_ISR_PRI) },
#else
 { 542, EE_CAX_ISR1_PRI(EE_CAX_542_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_543_ISR) && (EE_CAX_MAX_ISR_ID >= 543) && (EE_CAX_MAX_ARCH_ISR_ID >= 543))
#if (EE_CAX_543_ISR_CAT == 2)
 { 543, EE_CAX_ISR2_PRI(EE_CAX_543_ISR_PRI) },
#else
 { 543, EE_CAX_ISR1_PRI(EE_CAX_543_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_544_ISR) && (EE_CAX_MAX_ISR_ID >= 544) && (EE_CAX_MAX_ARCH_ISR_ID >= 544))
#if (EE_CAX_544_ISR_CAT == 2)
 { 544, EE_CAX_ISR2_PRI(EE_CAX_544_ISR_PRI) },
#else
 { 544, EE_CAX_ISR1_PRI(EE_CAX_544_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_545_ISR) && (EE_CAX_MAX_ISR_ID >= 545) && (EE_CAX_MAX_ARCH_ISR_ID >= 545))
#if (EE_CAX_545_ISR_CAT == 2)
 { 545, EE_CAX_ISR2_PRI(EE_CAX_545_ISR_PRI) },
#else
 { 545, EE_CAX_ISR1_PRI(EE_CAX_545_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_546_ISR) && (EE_CAX_MAX_ISR_ID >= 546) && (EE_CAX_MAX_ARCH_ISR_ID >= 546))
#if (EE_CAX_546_ISR_CAT == 2)
 { 546, EE_CAX_ISR2_PRI(EE_CAX_546_ISR_PRI) },
#else
 { 546, EE_CAX_ISR1_PRI(EE_CAX_546_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_547_ISR) && (EE_CAX_MAX_ISR_ID >= 547) && (EE_CAX_MAX_ARCH_ISR_ID >= 547))
#if (EE_CAX_547_ISR_CAT == 2)
 { 547, EE_CAX_ISR2_PRI(EE_CAX_547_ISR_PRI) },
#else
 { 547, EE_CAX_ISR1_PRI(EE_CAX_547_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_548_ISR) && (EE_CAX_MAX_ISR_ID >= 548) && (EE_CAX_MAX_ARCH_ISR_ID >= 548))
#if (EE_CAX_548_ISR_CAT == 2)
 { 548, EE_CAX_ISR2_PRI(EE_CAX_548_ISR_PRI) },
#else
 { 548, EE_CAX_ISR1_PRI(EE_CAX_548_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_549_ISR) && (EE_CAX_MAX_ISR_ID >= 549) && (EE_CAX_MAX_ARCH_ISR_ID >= 549))
#if (EE_CAX_549_ISR_CAT == 2)
 { 549, EE_CAX_ISR2_PRI(EE_CAX_549_ISR_PRI) },
#else
 { 549, EE_CAX_ISR1_PRI(EE_CAX_549_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_550_ISR) && (EE_CAX_MAX_ISR_ID >= 550) && (EE_CAX_MAX_ARCH_ISR_ID >= 550))
#if (EE_CAX_550_ISR_CAT == 2)
 { 550, EE_CAX_ISR2_PRI(EE_CAX_550_ISR_PRI) },
#else
 { 550, EE_CAX_ISR1_PRI(EE_CAX_550_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_551_ISR) && (EE_CAX_MAX_ISR_ID >= 551) && (EE_CAX_MAX_ARCH_ISR_ID >= 551))
#if (EE_CAX_551_ISR_CAT == 2)
 { 551, EE_CAX_ISR2_PRI(EE_CAX_551_ISR_PRI) },
#else
 { 551, EE_CAX_ISR1_PRI(EE_CAX_551_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_552_ISR) && (EE_CAX_MAX_ISR_ID >= 552) && (EE_CAX_MAX_ARCH_ISR_ID >= 552))
#if (EE_CAX_552_ISR_CAT == 2)
 { 552, EE_CAX_ISR2_PRI(EE_CAX_552_ISR_PRI) },
#else
 { 552, EE_CAX_ISR1_PRI(EE_CAX_552_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_553_ISR) && (EE_CAX_MAX_ISR_ID >= 553) && (EE_CAX_MAX_ARCH_ISR_ID >= 553))
#if (EE_CAX_553_ISR_CAT == 2)
 { 553, EE_CAX_ISR2_PRI(EE_CAX_553_ISR_PRI) },
#else
 { 553, EE_CAX_ISR1_PRI(EE_CAX_553_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_554_ISR) && (EE_CAX_MAX_ISR_ID >= 554) && (EE_CAX_MAX_ARCH_ISR_ID >= 554))
#if (EE_CAX_554_ISR_CAT == 2)
 { 554, EE_CAX_ISR2_PRI(EE_CAX_554_ISR_PRI) },
#else
 { 554, EE_CAX_ISR1_PRI(EE_CAX_554_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_555_ISR) && (EE_CAX_MAX_ISR_ID >= 555) && (EE_CAX_MAX_ARCH_ISR_ID >= 555))
#if (EE_CAX_555_ISR_CAT == 2)
 { 555, EE_CAX_ISR2_PRI(EE_CAX_555_ISR_PRI) },
#else
 { 555, EE_CAX_ISR1_PRI(EE_CAX_555_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_556_ISR) && (EE_CAX_MAX_ISR_ID >= 556) && (EE_CAX_MAX_ARCH_ISR_ID >= 556))
#if (EE_CAX_556_ISR_CAT == 2)
 { 556, EE_CAX_ISR2_PRI(EE_CAX_556_ISR_PRI) },
#else
 { 556, EE_CAX_ISR1_PRI(EE_CAX_556_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_557_ISR) && (EE_CAX_MAX_ISR_ID >= 557) && (EE_CAX_MAX_ARCH_ISR_ID >= 557))
#if (EE_CAX_557_ISR_CAT == 2)
 { 557, EE_CAX_ISR2_PRI(EE_CAX_557_ISR_PRI) },
#else
 { 557, EE_CAX_ISR1_PRI(EE_CAX_557_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_558_ISR) && (EE_CAX_MAX_ISR_ID >= 558) && (EE_CAX_MAX_ARCH_ISR_ID >= 558))
#if (EE_CAX_558_ISR_CAT == 2)
 { 558, EE_CAX_ISR2_PRI(EE_CAX_558_ISR_PRI) },
#else
 { 558, EE_CAX_ISR1_PRI(EE_CAX_558_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_559_ISR) && (EE_CAX_MAX_ISR_ID >= 559) && (EE_CAX_MAX_ARCH_ISR_ID >= 559))
#if (EE_CAX_559_ISR_CAT == 2)
 { 559, EE_CAX_ISR2_PRI(EE_CAX_559_ISR_PRI) },
#else
 { 559, EE_CAX_ISR1_PRI(EE_CAX_559_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_560_ISR) && (EE_CAX_MAX_ISR_ID >= 560) && (EE_CAX_MAX_ARCH_ISR_ID >= 560))
#if (EE_CAX_560_ISR_CAT == 2)
 { 560, EE_CAX_ISR2_PRI(EE_CAX_560_ISR_PRI) },
#else
 { 560, EE_CAX_ISR1_PRI(EE_CAX_560_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_561_ISR) && (EE_CAX_MAX_ISR_ID >= 561) && (EE_CAX_MAX_ARCH_ISR_ID >= 561))
#if (EE_CAX_561_ISR_CAT == 2)
 { 561, EE_CAX_ISR2_PRI(EE_CAX_561_ISR_PRI) },
#else
 { 561, EE_CAX_ISR1_PRI(EE_CAX_561_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_562_ISR) && (EE_CAX_MAX_ISR_ID >= 562) && (EE_CAX_MAX_ARCH_ISR_ID >= 562))
#if (EE_CAX_562_ISR_CAT == 2)
 { 562, EE_CAX_ISR2_PRI(EE_CAX_562_ISR_PRI) },
#else
 { 562, EE_CAX_ISR1_PRI(EE_CAX_562_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_563_ISR) && (EE_CAX_MAX_ISR_ID >= 563) && (EE_CAX_MAX_ARCH_ISR_ID >= 563))
#if (EE_CAX_563_ISR_CAT == 2)
 { 563, EE_CAX_ISR2_PRI(EE_CAX_563_ISR_PRI) },
#else
 { 563, EE_CAX_ISR1_PRI(EE_CAX_563_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_564_ISR) && (EE_CAX_MAX_ISR_ID >= 564) && (EE_CAX_MAX_ARCH_ISR_ID >= 564))
#if (EE_CAX_564_ISR_CAT == 2)
 { 564, EE_CAX_ISR2_PRI(EE_CAX_564_ISR_PRI) },
#else
 { 564, EE_CAX_ISR1_PRI(EE_CAX_564_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_565_ISR) && (EE_CAX_MAX_ISR_ID >= 565) && (EE_CAX_MAX_ARCH_ISR_ID >= 565))
#if (EE_CAX_565_ISR_CAT == 2)
 { 565, EE_CAX_ISR2_PRI(EE_CAX_565_ISR_PRI) },
#else
 { 565, EE_CAX_ISR1_PRI(EE_CAX_565_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_566_ISR) && (EE_CAX_MAX_ISR_ID >= 566) && (EE_CAX_MAX_ARCH_ISR_ID >= 566))
#if (EE_CAX_566_ISR_CAT == 2)
 { 566, EE_CAX_ISR2_PRI(EE_CAX_566_ISR_PRI) },
#else
 { 566, EE_CAX_ISR1_PRI(EE_CAX_566_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_567_ISR) && (EE_CAX_MAX_ISR_ID >= 567) && (EE_CAX_MAX_ARCH_ISR_ID >= 567))
#if (EE_CAX_567_ISR_CAT == 2)
 { 567, EE_CAX_ISR2_PRI(EE_CAX_567_ISR_PRI) },
#else
 { 567, EE_CAX_ISR1_PRI(EE_CAX_567_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_568_ISR) && (EE_CAX_MAX_ISR_ID >= 568) && (EE_CAX_MAX_ARCH_ISR_ID >= 568))
#if (EE_CAX_568_ISR_CAT == 2)
 { 568, EE_CAX_ISR2_PRI(EE_CAX_568_ISR_PRI) },
#else
 { 568, EE_CAX_ISR1_PRI(EE_CAX_568_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_569_ISR) && (EE_CAX_MAX_ISR_ID >= 569) && (EE_CAX_MAX_ARCH_ISR_ID >= 569))
#if (EE_CAX_569_ISR_CAT == 2)
 { 569, EE_CAX_ISR2_PRI(EE_CAX_569_ISR_PRI) },
#else
 { 569, EE_CAX_ISR1_PRI(EE_CAX_569_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_570_ISR) && (EE_CAX_MAX_ISR_ID >= 570) && (EE_CAX_MAX_ARCH_ISR_ID >= 570))
#if (EE_CAX_570_ISR_CAT == 2)
 { 570, EE_CAX_ISR2_PRI(EE_CAX_570_ISR_PRI) },
#else
 { 570, EE_CAX_ISR1_PRI(EE_CAX_570_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_571_ISR) && (EE_CAX_MAX_ISR_ID >= 571) && (EE_CAX_MAX_ARCH_ISR_ID >= 571))
#if (EE_CAX_571_ISR_CAT == 2)
 { 571, EE_CAX_ISR2_PRI(EE_CAX_571_ISR_PRI) },
#else
 { 571, EE_CAX_ISR1_PRI(EE_CAX_571_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_572_ISR) && (EE_CAX_MAX_ISR_ID >= 572) && (EE_CAX_MAX_ARCH_ISR_ID >= 572))
#if (EE_CAX_572_ISR_CAT == 2)
 { 572, EE_CAX_ISR2_PRI(EE_CAX_572_ISR_PRI) },
#else
 { 572, EE_CAX_ISR1_PRI(EE_CAX_572_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_573_ISR) && (EE_CAX_MAX_ISR_ID >= 573) && (EE_CAX_MAX_ARCH_ISR_ID >= 573))
#if (EE_CAX_573_ISR_CAT == 2)
 { 573, EE_CAX_ISR2_PRI(EE_CAX_573_ISR_PRI) },
#else
 { 573, EE_CAX_ISR1_PRI(EE_CAX_573_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_574_ISR) && (EE_CAX_MAX_ISR_ID >= 574) && (EE_CAX_MAX_ARCH_ISR_ID >= 574))
#if (EE_CAX_574_ISR_CAT == 2)
 { 574, EE_CAX_ISR2_PRI(EE_CAX_574_ISR_PRI) },
#else
 { 574, EE_CAX_ISR1_PRI(EE_CAX_574_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_575_ISR) && (EE_CAX_MAX_ISR_ID >= 575) && (EE_CAX_MAX_ARCH_ISR_ID >= 575))
#if (EE_CAX_575_ISR_CAT == 2)
 { 575, EE_CAX_ISR2_PRI(EE_CAX_575_ISR_PRI) },
#else
 { 575, EE_CAX_ISR1_PRI(EE_CAX_575_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_576_ISR) && (EE_CAX_MAX_ISR_ID >= 576) && (EE_CAX_MAX_ARCH_ISR_ID >= 576))
#if (EE_CAX_576_ISR_CAT == 2)
 { 576, EE_CAX_ISR2_PRI(EE_CAX_576_ISR_PRI) },
#else
 { 576, EE_CAX_ISR1_PRI(EE_CAX_576_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_577_ISR) && (EE_CAX_MAX_ISR_ID >= 577) && (EE_CAX_MAX_ARCH_ISR_ID >= 577))
#if (EE_CAX_577_ISR_CAT == 2)
 { 577, EE_CAX_ISR2_PRI(EE_CAX_577_ISR_PRI) },
#else
 { 577, EE_CAX_ISR1_PRI(EE_CAX_577_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_578_ISR) && (EE_CAX_MAX_ISR_ID >= 578) && (EE_CAX_MAX_ARCH_ISR_ID >= 578))
#if (EE_CAX_578_ISR_CAT == 2)
 { 578, EE_CAX_ISR2_PRI(EE_CAX_578_ISR_PRI) },
#else
 { 578, EE_CAX_ISR1_PRI(EE_CAX_578_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_579_ISR) && (EE_CAX_MAX_ISR_ID >= 579) && (EE_CAX_MAX_ARCH_ISR_ID >= 579))
#if (EE_CAX_579_ISR_CAT == 2)
 { 579, EE_CAX_ISR2_PRI(EE_CAX_579_ISR_PRI) },
#else
 { 579, EE_CAX_ISR1_PRI(EE_CAX_579_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_580_ISR) && (EE_CAX_MAX_ISR_ID >= 580) && (EE_CAX_MAX_ARCH_ISR_ID >= 580))
#if (EE_CAX_580_ISR_CAT == 2)
 { 580, EE_CAX_ISR2_PRI(EE_CAX_580_ISR_PRI) },
#else
 { 580, EE_CAX_ISR1_PRI(EE_CAX_580_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_581_ISR) && (EE_CAX_MAX_ISR_ID >= 581) && (EE_CAX_MAX_ARCH_ISR_ID >= 581))
#if (EE_CAX_581_ISR_CAT == 2)
 { 581, EE_CAX_ISR2_PRI(EE_CAX_581_ISR_PRI) },
#else
 { 581, EE_CAX_ISR1_PRI(EE_CAX_581_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_582_ISR) && (EE_CAX_MAX_ISR_ID >= 582) && (EE_CAX_MAX_ARCH_ISR_ID >= 582))
#if (EE_CAX_582_ISR_CAT == 2)
 { 582, EE_CAX_ISR2_PRI(EE_CAX_582_ISR_PRI) },
#else
 { 582, EE_CAX_ISR1_PRI(EE_CAX_582_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_583_ISR) && (EE_CAX_MAX_ISR_ID >= 583) && (EE_CAX_MAX_ARCH_ISR_ID >= 583))
#if (EE_CAX_583_ISR_CAT == 2)
 { 583, EE_CAX_ISR2_PRI(EE_CAX_583_ISR_PRI) },
#else
 { 583, EE_CAX_ISR1_PRI(EE_CAX_583_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_584_ISR) && (EE_CAX_MAX_ISR_ID >= 584) && (EE_CAX_MAX_ARCH_ISR_ID >= 584))
#if (EE_CAX_584_ISR_CAT == 2)
 { 584, EE_CAX_ISR2_PRI(EE_CAX_584_ISR_PRI) },
#else
 { 584, EE_CAX_ISR1_PRI(EE_CAX_584_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_585_ISR) && (EE_CAX_MAX_ISR_ID >= 585) && (EE_CAX_MAX_ARCH_ISR_ID >= 585))
#if (EE_CAX_585_ISR_CAT == 2)
 { 585, EE_CAX_ISR2_PRI(EE_CAX_585_ISR_PRI) },
#else
 { 585, EE_CAX_ISR1_PRI(EE_CAX_585_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_586_ISR) && (EE_CAX_MAX_ISR_ID >= 586) && (EE_CAX_MAX_ARCH_ISR_ID >= 586))
#if (EE_CAX_586_ISR_CAT == 2)
 { 586, EE_CAX_ISR2_PRI(EE_CAX_586_ISR_PRI) },
#else
 { 586, EE_CAX_ISR1_PRI(EE_CAX_586_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_587_ISR) && (EE_CAX_MAX_ISR_ID >= 587) && (EE_CAX_MAX_ARCH_ISR_ID >= 587))
#if (EE_CAX_587_ISR_CAT == 2)
 { 587, EE_CAX_ISR2_PRI(EE_CAX_587_ISR_PRI) },
#else
 { 587, EE_CAX_ISR1_PRI(EE_CAX_587_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_588_ISR) && (EE_CAX_MAX_ISR_ID >= 588) && (EE_CAX_MAX_ARCH_ISR_ID >= 588))
#if (EE_CAX_588_ISR_CAT == 2)
 { 588, EE_CAX_ISR2_PRI(EE_CAX_588_ISR_PRI) },
#else
 { 588, EE_CAX_ISR1_PRI(EE_CAX_588_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_589_ISR) && (EE_CAX_MAX_ISR_ID >= 589) && (EE_CAX_MAX_ARCH_ISR_ID >= 589))
#if (EE_CAX_589_ISR_CAT == 2)
 { 589, EE_CAX_ISR2_PRI(EE_CAX_589_ISR_PRI) },
#else
 { 589, EE_CAX_ISR1_PRI(EE_CAX_589_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_590_ISR) && (EE_CAX_MAX_ISR_ID >= 590) && (EE_CAX_MAX_ARCH_ISR_ID >= 590))
#if (EE_CAX_590_ISR_CAT == 2)
 { 590, EE_CAX_ISR2_PRI(EE_CAX_590_ISR_PRI) },
#else
 { 590, EE_CAX_ISR1_PRI(EE_CAX_590_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_591_ISR) && (EE_CAX_MAX_ISR_ID >= 591) && (EE_CAX_MAX_ARCH_ISR_ID >= 591))
#if (EE_CAX_591_ISR_CAT == 2)
 { 591, EE_CAX_ISR2_PRI(EE_CAX_591_ISR_PRI) },
#else
 { 591, EE_CAX_ISR1_PRI(EE_CAX_591_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_592_ISR) && (EE_CAX_MAX_ISR_ID >= 592) && (EE_CAX_MAX_ARCH_ISR_ID >= 592))
#if (EE_CAX_592_ISR_CAT == 2)
 { 592, EE_CAX_ISR2_PRI(EE_CAX_592_ISR_PRI) },
#else
 { 592, EE_CAX_ISR1_PRI(EE_CAX_592_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_593_ISR) && (EE_CAX_MAX_ISR_ID >= 593) && (EE_CAX_MAX_ARCH_ISR_ID >= 593))
#if (EE_CAX_593_ISR_CAT == 2)
 { 593, EE_CAX_ISR2_PRI(EE_CAX_593_ISR_PRI) },
#else
 { 593, EE_CAX_ISR1_PRI(EE_CAX_593_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_594_ISR) && (EE_CAX_MAX_ISR_ID >= 594) && (EE_CAX_MAX_ARCH_ISR_ID >= 594))
#if (EE_CAX_594_ISR_CAT == 2)
 { 594, EE_CAX_ISR2_PRI(EE_CAX_594_ISR_PRI) },
#else
 { 594, EE_CAX_ISR1_PRI(EE_CAX_594_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_595_ISR) && (EE_CAX_MAX_ISR_ID >= 595) && (EE_CAX_MAX_ARCH_ISR_ID >= 595))
#if (EE_CAX_595_ISR_CAT == 2)
 { 595, EE_CAX_ISR2_PRI(EE_CAX_595_ISR_PRI) },
#else
 { 595, EE_CAX_ISR1_PRI(EE_CAX_595_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_596_ISR) && (EE_CAX_MAX_ISR_ID >= 596) && (EE_CAX_MAX_ARCH_ISR_ID >= 596))
#if (EE_CAX_596_ISR_CAT == 2)
 { 596, EE_CAX_ISR2_PRI(EE_CAX_596_ISR_PRI) },
#else
 { 596, EE_CAX_ISR1_PRI(EE_CAX_596_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_597_ISR) && (EE_CAX_MAX_ISR_ID >= 597) && (EE_CAX_MAX_ARCH_ISR_ID >= 597))
#if (EE_CAX_597_ISR_CAT == 2)
 { 597, EE_CAX_ISR2_PRI(EE_CAX_597_ISR_PRI) },
#else
 { 597, EE_CAX_ISR1_PRI(EE_CAX_597_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_598_ISR) && (EE_CAX_MAX_ISR_ID >= 598) && (EE_CAX_MAX_ARCH_ISR_ID >= 598))
#if (EE_CAX_598_ISR_CAT == 2)
 { 598, EE_CAX_ISR2_PRI(EE_CAX_598_ISR_PRI) },
#else
 { 598, EE_CAX_ISR1_PRI(EE_CAX_598_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_599_ISR) && (EE_CAX_MAX_ISR_ID >= 599) && (EE_CAX_MAX_ARCH_ISR_ID >= 599))
#if (EE_CAX_599_ISR_CAT == 2)
 { 599, EE_CAX_ISR2_PRI(EE_CAX_599_ISR_PRI) },
#else
 { 599, EE_CAX_ISR1_PRI(EE_CAX_599_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_600_ISR) && (EE_CAX_MAX_ISR_ID >= 600) && (EE_CAX_MAX_ARCH_ISR_ID >= 600))
#if (EE_CAX_600_ISR_CAT == 2)
 { 600, EE_CAX_ISR2_PRI(EE_CAX_600_ISR_PRI) },
#else
 { 600, EE_CAX_ISR1_PRI(EE_CAX_600_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_601_ISR) && (EE_CAX_MAX_ISR_ID >= 601) && (EE_CAX_MAX_ARCH_ISR_ID >= 601))
#if (EE_CAX_601_ISR_CAT == 2)
 { 601, EE_CAX_ISR2_PRI(EE_CAX_601_ISR_PRI) },
#else
 { 601, EE_CAX_ISR1_PRI(EE_CAX_601_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_602_ISR) && (EE_CAX_MAX_ISR_ID >= 602) && (EE_CAX_MAX_ARCH_ISR_ID >= 602))
#if (EE_CAX_602_ISR_CAT == 2)
 { 602, EE_CAX_ISR2_PRI(EE_CAX_602_ISR_PRI) },
#else
 { 602, EE_CAX_ISR1_PRI(EE_CAX_602_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_603_ISR) && (EE_CAX_MAX_ISR_ID >= 603) && (EE_CAX_MAX_ARCH_ISR_ID >= 603))
#if (EE_CAX_603_ISR_CAT == 2)
 { 603, EE_CAX_ISR2_PRI(EE_CAX_603_ISR_PRI) },
#else
 { 603, EE_CAX_ISR1_PRI(EE_CAX_603_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_604_ISR) && (EE_CAX_MAX_ISR_ID >= 604) && (EE_CAX_MAX_ARCH_ISR_ID >= 604))
#if (EE_CAX_604_ISR_CAT == 2)
 { 604, EE_CAX_ISR2_PRI(EE_CAX_604_ISR_PRI) },
#else
 { 604, EE_CAX_ISR1_PRI(EE_CAX_604_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_605_ISR) && (EE_CAX_MAX_ISR_ID >= 605) && (EE_CAX_MAX_ARCH_ISR_ID >= 605))
#if (EE_CAX_605_ISR_CAT == 2)
 { 605, EE_CAX_ISR2_PRI(EE_CAX_605_ISR_PRI) },
#else
 { 605, EE_CAX_ISR1_PRI(EE_CAX_605_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_606_ISR) && (EE_CAX_MAX_ISR_ID >= 606) && (EE_CAX_MAX_ARCH_ISR_ID >= 606))
#if (EE_CAX_606_ISR_CAT == 2)
 { 606, EE_CAX_ISR2_PRI(EE_CAX_606_ISR_PRI) },
#else
 { 606, EE_CAX_ISR1_PRI(EE_CAX_606_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_607_ISR) && (EE_CAX_MAX_ISR_ID >= 607) && (EE_CAX_MAX_ARCH_ISR_ID >= 607))
#if (EE_CAX_607_ISR_CAT == 2)
 { 607, EE_CAX_ISR2_PRI(EE_CAX_607_ISR_PRI) },
#else
 { 607, EE_CAX_ISR1_PRI(EE_CAX_607_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_608_ISR) && (EE_CAX_MAX_ISR_ID >= 608) && (EE_CAX_MAX_ARCH_ISR_ID >= 608))
#if (EE_CAX_608_ISR_CAT == 2)
 { 608, EE_CAX_ISR2_PRI(EE_CAX_608_ISR_PRI) },
#else
 { 608, EE_CAX_ISR1_PRI(EE_CAX_608_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_609_ISR) && (EE_CAX_MAX_ISR_ID >= 609) && (EE_CAX_MAX_ARCH_ISR_ID >= 609))
#if (EE_CAX_609_ISR_CAT == 2)
 { 609, EE_CAX_ISR2_PRI(EE_CAX_609_ISR_PRI) },
#else
 { 609, EE_CAX_ISR1_PRI(EE_CAX_609_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_610_ISR) && (EE_CAX_MAX_ISR_ID >= 610) && (EE_CAX_MAX_ARCH_ISR_ID >= 610))
#if (EE_CAX_610_ISR_CAT == 2)
 { 610, EE_CAX_ISR2_PRI(EE_CAX_610_ISR_PRI) },
#else
 { 610, EE_CAX_ISR1_PRI(EE_CAX_610_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_611_ISR) && (EE_CAX_MAX_ISR_ID >= 611) && (EE_CAX_MAX_ARCH_ISR_ID >= 611))
#if (EE_CAX_611_ISR_CAT == 2)
 { 611, EE_CAX_ISR2_PRI(EE_CAX_611_ISR_PRI) },
#else
 { 611, EE_CAX_ISR1_PRI(EE_CAX_611_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_612_ISR) && (EE_CAX_MAX_ISR_ID >= 612) && (EE_CAX_MAX_ARCH_ISR_ID >= 612))
#if (EE_CAX_612_ISR_CAT == 2)
 { 612, EE_CAX_ISR2_PRI(EE_CAX_612_ISR_PRI) },
#else
 { 612, EE_CAX_ISR1_PRI(EE_CAX_612_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_613_ISR) && (EE_CAX_MAX_ISR_ID >= 613) && (EE_CAX_MAX_ARCH_ISR_ID >= 613))
#if (EE_CAX_613_ISR_CAT == 2)
 { 613, EE_CAX_ISR2_PRI(EE_CAX_613_ISR_PRI) },
#else
 { 613, EE_CAX_ISR1_PRI(EE_CAX_613_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_614_ISR) && (EE_CAX_MAX_ISR_ID >= 614) && (EE_CAX_MAX_ARCH_ISR_ID >= 614))
#if (EE_CAX_614_ISR_CAT == 2)
 { 614, EE_CAX_ISR2_PRI(EE_CAX_614_ISR_PRI) },
#else
 { 614, EE_CAX_ISR1_PRI(EE_CAX_614_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_615_ISR) && (EE_CAX_MAX_ISR_ID >= 615) && (EE_CAX_MAX_ARCH_ISR_ID >= 615))
#if (EE_CAX_615_ISR_CAT == 2)
 { 615, EE_CAX_ISR2_PRI(EE_CAX_615_ISR_PRI) },
#else
 { 615, EE_CAX_ISR1_PRI(EE_CAX_615_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_616_ISR) && (EE_CAX_MAX_ISR_ID >= 616) && (EE_CAX_MAX_ARCH_ISR_ID >= 616))
#if (EE_CAX_616_ISR_CAT == 2)
 { 616, EE_CAX_ISR2_PRI(EE_CAX_616_ISR_PRI) },
#else
 { 616, EE_CAX_ISR1_PRI(EE_CAX_616_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_617_ISR) && (EE_CAX_MAX_ISR_ID >= 617) && (EE_CAX_MAX_ARCH_ISR_ID >= 617))
#if (EE_CAX_617_ISR_CAT == 2)
 { 617, EE_CAX_ISR2_PRI(EE_CAX_617_ISR_PRI) },
#else
 { 617, EE_CAX_ISR1_PRI(EE_CAX_617_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_618_ISR) && (EE_CAX_MAX_ISR_ID >= 618) && (EE_CAX_MAX_ARCH_ISR_ID >= 618))
#if (EE_CAX_618_ISR_CAT == 2)
 { 618, EE_CAX_ISR2_PRI(EE_CAX_618_ISR_PRI) },
#else
 { 618, EE_CAX_ISR1_PRI(EE_CAX_618_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_619_ISR) && (EE_CAX_MAX_ISR_ID >= 619) && (EE_CAX_MAX_ARCH_ISR_ID >= 619))
#if (EE_CAX_619_ISR_CAT == 2)
 { 619, EE_CAX_ISR2_PRI(EE_CAX_619_ISR_PRI) },
#else
 { 619, EE_CAX_ISR1_PRI(EE_CAX_619_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_620_ISR) && (EE_CAX_MAX_ISR_ID >= 620) && (EE_CAX_MAX_ARCH_ISR_ID >= 620))
#if (EE_CAX_620_ISR_CAT == 2)
 { 620, EE_CAX_ISR2_PRI(EE_CAX_620_ISR_PRI) },
#else
 { 620, EE_CAX_ISR1_PRI(EE_CAX_620_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_621_ISR) && (EE_CAX_MAX_ISR_ID >= 621) && (EE_CAX_MAX_ARCH_ISR_ID >= 621))
#if (EE_CAX_621_ISR_CAT == 2)
 { 621, EE_CAX_ISR2_PRI(EE_CAX_621_ISR_PRI) },
#else
 { 621, EE_CAX_ISR1_PRI(EE_CAX_621_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_622_ISR) && (EE_CAX_MAX_ISR_ID >= 622) && (EE_CAX_MAX_ARCH_ISR_ID >= 622))
#if (EE_CAX_622_ISR_CAT == 2)
 { 622, EE_CAX_ISR2_PRI(EE_CAX_622_ISR_PRI) },
#else
 { 622, EE_CAX_ISR1_PRI(EE_CAX_622_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_623_ISR) && (EE_CAX_MAX_ISR_ID >= 623) && (EE_CAX_MAX_ARCH_ISR_ID >= 623))
#if (EE_CAX_623_ISR_CAT == 2)
 { 623, EE_CAX_ISR2_PRI(EE_CAX_623_ISR_PRI) },
#else
 { 623, EE_CAX_ISR1_PRI(EE_CAX_623_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_624_ISR) && (EE_CAX_MAX_ISR_ID >= 624) && (EE_CAX_MAX_ARCH_ISR_ID >= 624))
#if (EE_CAX_624_ISR_CAT == 2)
 { 624, EE_CAX_ISR2_PRI(EE_CAX_624_ISR_PRI) },
#else
 { 624, EE_CAX_ISR1_PRI(EE_CAX_624_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_625_ISR) && (EE_CAX_MAX_ISR_ID >= 625) && (EE_CAX_MAX_ARCH_ISR_ID >= 625))
#if (EE_CAX_625_ISR_CAT == 2)
 { 625, EE_CAX_ISR2_PRI(EE_CAX_625_ISR_PRI) },
#else
 { 625, EE_CAX_ISR1_PRI(EE_CAX_625_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_626_ISR) && (EE_CAX_MAX_ISR_ID >= 626) && (EE_CAX_MAX_ARCH_ISR_ID >= 626))
#if (EE_CAX_626_ISR_CAT == 2)
 { 626, EE_CAX_ISR2_PRI(EE_CAX_626_ISR_PRI) },
#else
 { 626, EE_CAX_ISR1_PRI(EE_CAX_626_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_627_ISR) && (EE_CAX_MAX_ISR_ID >= 627) && (EE_CAX_MAX_ARCH_ISR_ID >= 627))
#if (EE_CAX_627_ISR_CAT == 2)
 { 627, EE_CAX_ISR2_PRI(EE_CAX_627_ISR_PRI) },
#else
 { 627, EE_CAX_ISR1_PRI(EE_CAX_627_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_628_ISR) && (EE_CAX_MAX_ISR_ID >= 628) && (EE_CAX_MAX_ARCH_ISR_ID >= 628))
#if (EE_CAX_628_ISR_CAT == 2)
 { 628, EE_CAX_ISR2_PRI(EE_CAX_628_ISR_PRI) },
#else
 { 628, EE_CAX_ISR1_PRI(EE_CAX_628_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_629_ISR) && (EE_CAX_MAX_ISR_ID >= 629) && (EE_CAX_MAX_ARCH_ISR_ID >= 629))
#if (EE_CAX_629_ISR_CAT == 2)
 { 629, EE_CAX_ISR2_PRI(EE_CAX_629_ISR_PRI) },
#else
 { 629, EE_CAX_ISR1_PRI(EE_CAX_629_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_630_ISR) && (EE_CAX_MAX_ISR_ID >= 630) && (EE_CAX_MAX_ARCH_ISR_ID >= 630))
#if (EE_CAX_630_ISR_CAT == 2)
 { 630, EE_CAX_ISR2_PRI(EE_CAX_630_ISR_PRI) },
#else
 { 630, EE_CAX_ISR1_PRI(EE_CAX_630_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_631_ISR) && (EE_CAX_MAX_ISR_ID >= 631) && (EE_CAX_MAX_ARCH_ISR_ID >= 631))
#if (EE_CAX_631_ISR_CAT == 2)
 { 631, EE_CAX_ISR2_PRI(EE_CAX_631_ISR_PRI) },
#else
 { 631, EE_CAX_ISR1_PRI(EE_CAX_631_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_632_ISR) && (EE_CAX_MAX_ISR_ID >= 632) && (EE_CAX_MAX_ARCH_ISR_ID >= 632))
#if (EE_CAX_632_ISR_CAT == 2)
 { 632, EE_CAX_ISR2_PRI(EE_CAX_632_ISR_PRI) },
#else
 { 632, EE_CAX_ISR1_PRI(EE_CAX_632_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_633_ISR) && (EE_CAX_MAX_ISR_ID >= 633) && (EE_CAX_MAX_ARCH_ISR_ID >= 633))
#if (EE_CAX_633_ISR_CAT == 2)
 { 633, EE_CAX_ISR2_PRI(EE_CAX_633_ISR_PRI) },
#else
 { 633, EE_CAX_ISR1_PRI(EE_CAX_633_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_634_ISR) && (EE_CAX_MAX_ISR_ID >= 634) && (EE_CAX_MAX_ARCH_ISR_ID >= 634))
#if (EE_CAX_634_ISR_CAT == 2)
 { 634, EE_CAX_ISR2_PRI(EE_CAX_634_ISR_PRI) },
#else
 { 634, EE_CAX_ISR1_PRI(EE_CAX_634_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_635_ISR) && (EE_CAX_MAX_ISR_ID >= 635) && (EE_CAX_MAX_ARCH_ISR_ID >= 635))
#if (EE_CAX_635_ISR_CAT == 2)
 { 635, EE_CAX_ISR2_PRI(EE_CAX_635_ISR_PRI) },
#else
 { 635, EE_CAX_ISR1_PRI(EE_CAX_635_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_636_ISR) && (EE_CAX_MAX_ISR_ID >= 636) && (EE_CAX_MAX_ARCH_ISR_ID >= 636))
#if (EE_CAX_636_ISR_CAT == 2)
 { 636, EE_CAX_ISR2_PRI(EE_CAX_636_ISR_PRI) },
#else
 { 636, EE_CAX_ISR1_PRI(EE_CAX_636_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_637_ISR) && (EE_CAX_MAX_ISR_ID >= 637) && (EE_CAX_MAX_ARCH_ISR_ID >= 637))
#if (EE_CAX_637_ISR_CAT == 2)
 { 637, EE_CAX_ISR2_PRI(EE_CAX_637_ISR_PRI) },
#else
 { 637, EE_CAX_ISR1_PRI(EE_CAX_637_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_638_ISR) && (EE_CAX_MAX_ISR_ID >= 638) && (EE_CAX_MAX_ARCH_ISR_ID >= 638))
#if (EE_CAX_638_ISR_CAT == 2)
 { 638, EE_CAX_ISR2_PRI(EE_CAX_638_ISR_PRI) },
#else
 { 638, EE_CAX_ISR1_PRI(EE_CAX_638_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_639_ISR) && (EE_CAX_MAX_ISR_ID >= 639) && (EE_CAX_MAX_ARCH_ISR_ID >= 639))
#if (EE_CAX_639_ISR_CAT == 2)
 { 639, EE_CAX_ISR2_PRI(EE_CAX_639_ISR_PRI) },
#else
 { 639, EE_CAX_ISR1_PRI(EE_CAX_639_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_640_ISR) && (EE_CAX_MAX_ISR_ID >= 640) && (EE_CAX_MAX_ARCH_ISR_ID >= 640))
#if (EE_CAX_640_ISR_CAT == 2)
 { 640, EE_CAX_ISR2_PRI(EE_CAX_640_ISR_PRI) },
#else
 { 640, EE_CAX_ISR1_PRI(EE_CAX_640_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_641_ISR) && (EE_CAX_MAX_ISR_ID >= 641) && (EE_CAX_MAX_ARCH_ISR_ID >= 641))
#if (EE_CAX_641_ISR_CAT == 2)
 { 641, EE_CAX_ISR2_PRI(EE_CAX_641_ISR_PRI) },
#else
 { 641, EE_CAX_ISR1_PRI(EE_CAX_641_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_642_ISR) && (EE_CAX_MAX_ISR_ID >= 642) && (EE_CAX_MAX_ARCH_ISR_ID >= 642))
#if (EE_CAX_642_ISR_CAT == 2)
 { 642, EE_CAX_ISR2_PRI(EE_CAX_642_ISR_PRI) },
#else
 { 642, EE_CAX_ISR1_PRI(EE_CAX_642_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_643_ISR) && (EE_CAX_MAX_ISR_ID >= 643) && (EE_CAX_MAX_ARCH_ISR_ID >= 643))
#if (EE_CAX_643_ISR_CAT == 2)
 { 643, EE_CAX_ISR2_PRI(EE_CAX_643_ISR_PRI) },
#else
 { 643, EE_CAX_ISR1_PRI(EE_CAX_643_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_644_ISR) && (EE_CAX_MAX_ISR_ID >= 644) && (EE_CAX_MAX_ARCH_ISR_ID >= 644))
#if (EE_CAX_644_ISR_CAT == 2)
 { 644, EE_CAX_ISR2_PRI(EE_CAX_644_ISR_PRI) },
#else
 { 644, EE_CAX_ISR1_PRI(EE_CAX_644_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_645_ISR) && (EE_CAX_MAX_ISR_ID >= 645) && (EE_CAX_MAX_ARCH_ISR_ID >= 645))
#if (EE_CAX_645_ISR_CAT == 2)
 { 645, EE_CAX_ISR2_PRI(EE_CAX_645_ISR_PRI) },
#else
 { 645, EE_CAX_ISR1_PRI(EE_CAX_645_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_646_ISR) && (EE_CAX_MAX_ISR_ID >= 646) && (EE_CAX_MAX_ARCH_ISR_ID >= 646))
#if (EE_CAX_646_ISR_CAT == 2)
 { 646, EE_CAX_ISR2_PRI(EE_CAX_646_ISR_PRI) },
#else
 { 646, EE_CAX_ISR1_PRI(EE_CAX_646_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_647_ISR) && (EE_CAX_MAX_ISR_ID >= 647) && (EE_CAX_MAX_ARCH_ISR_ID >= 647))
#if (EE_CAX_647_ISR_CAT == 2)
 { 647, EE_CAX_ISR2_PRI(EE_CAX_647_ISR_PRI) },
#else
 { 647, EE_CAX_ISR1_PRI(EE_CAX_647_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_648_ISR) && (EE_CAX_MAX_ISR_ID >= 648) && (EE_CAX_MAX_ARCH_ISR_ID >= 648))
#if (EE_CAX_648_ISR_CAT == 2)
 { 648, EE_CAX_ISR2_PRI(EE_CAX_648_ISR_PRI) },
#else
 { 648, EE_CAX_ISR1_PRI(EE_CAX_648_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_649_ISR) && (EE_CAX_MAX_ISR_ID >= 649) && (EE_CAX_MAX_ARCH_ISR_ID >= 649))
#if (EE_CAX_649_ISR_CAT == 2)
 { 649, EE_CAX_ISR2_PRI(EE_CAX_649_ISR_PRI) },
#else
 { 649, EE_CAX_ISR1_PRI(EE_CAX_649_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_650_ISR) && (EE_CAX_MAX_ISR_ID >= 650) && (EE_CAX_MAX_ARCH_ISR_ID >= 650))
#if (EE_CAX_650_ISR_CAT == 2)
 { 650, EE_CAX_ISR2_PRI(EE_CAX_650_ISR_PRI) },
#else
 { 650, EE_CAX_ISR1_PRI(EE_CAX_650_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_651_ISR) && (EE_CAX_MAX_ISR_ID >= 651) && (EE_CAX_MAX_ARCH_ISR_ID >= 651))
#if (EE_CAX_651_ISR_CAT == 2)
 { 651, EE_CAX_ISR2_PRI(EE_CAX_651_ISR_PRI) },
#else
 { 651, EE_CAX_ISR1_PRI(EE_CAX_651_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_652_ISR) && (EE_CAX_MAX_ISR_ID >= 652) && (EE_CAX_MAX_ARCH_ISR_ID >= 652))
#if (EE_CAX_652_ISR_CAT == 2)
 { 652, EE_CAX_ISR2_PRI(EE_CAX_652_ISR_PRI) },
#else
 { 652, EE_CAX_ISR1_PRI(EE_CAX_652_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_653_ISR) && (EE_CAX_MAX_ISR_ID >= 653) && (EE_CAX_MAX_ARCH_ISR_ID >= 653))
#if (EE_CAX_653_ISR_CAT == 2)
 { 653, EE_CAX_ISR2_PRI(EE_CAX_653_ISR_PRI) },
#else
 { 653, EE_CAX_ISR1_PRI(EE_CAX_653_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_654_ISR) && (EE_CAX_MAX_ISR_ID >= 654) && (EE_CAX_MAX_ARCH_ISR_ID >= 654))
#if (EE_CAX_654_ISR_CAT == 2)
 { 654, EE_CAX_ISR2_PRI(EE_CAX_654_ISR_PRI) },
#else
 { 654, EE_CAX_ISR1_PRI(EE_CAX_654_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_655_ISR) && (EE_CAX_MAX_ISR_ID >= 655) && (EE_CAX_MAX_ARCH_ISR_ID >= 655))
#if (EE_CAX_655_ISR_CAT == 2)
 { 655, EE_CAX_ISR2_PRI(EE_CAX_655_ISR_PRI) },
#else
 { 655, EE_CAX_ISR1_PRI(EE_CAX_655_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_656_ISR) && (EE_CAX_MAX_ISR_ID >= 656) && (EE_CAX_MAX_ARCH_ISR_ID >= 656))
#if (EE_CAX_656_ISR_CAT == 2)
 { 656, EE_CAX_ISR2_PRI(EE_CAX_656_ISR_PRI) },
#else
 { 656, EE_CAX_ISR1_PRI(EE_CAX_656_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_657_ISR) && (EE_CAX_MAX_ISR_ID >= 657) && (EE_CAX_MAX_ARCH_ISR_ID >= 657))
#if (EE_CAX_657_ISR_CAT == 2)
 { 657, EE_CAX_ISR2_PRI(EE_CAX_657_ISR_PRI) },
#else
 { 657, EE_CAX_ISR1_PRI(EE_CAX_657_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_658_ISR) && (EE_CAX_MAX_ISR_ID >= 658) && (EE_CAX_MAX_ARCH_ISR_ID >= 658))
#if (EE_CAX_658_ISR_CAT == 2)
 { 658, EE_CAX_ISR2_PRI(EE_CAX_658_ISR_PRI) },
#else
 { 658, EE_CAX_ISR1_PRI(EE_CAX_658_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_659_ISR) && (EE_CAX_MAX_ISR_ID >= 659) && (EE_CAX_MAX_ARCH_ISR_ID >= 659))
#if (EE_CAX_659_ISR_CAT == 2)
 { 659, EE_CAX_ISR2_PRI(EE_CAX_659_ISR_PRI) },
#else
 { 659, EE_CAX_ISR1_PRI(EE_CAX_659_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_660_ISR) && (EE_CAX_MAX_ISR_ID >= 660) && (EE_CAX_MAX_ARCH_ISR_ID >= 660))
#if (EE_CAX_660_ISR_CAT == 2)
 { 660, EE_CAX_ISR2_PRI(EE_CAX_660_ISR_PRI) },
#else
 { 660, EE_CAX_ISR1_PRI(EE_CAX_660_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_661_ISR) && (EE_CAX_MAX_ISR_ID >= 661) && (EE_CAX_MAX_ARCH_ISR_ID >= 661))
#if (EE_CAX_661_ISR_CAT == 2)
 { 661, EE_CAX_ISR2_PRI(EE_CAX_661_ISR_PRI) },
#else
 { 661, EE_CAX_ISR1_PRI(EE_CAX_661_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_662_ISR) && (EE_CAX_MAX_ISR_ID >= 662) && (EE_CAX_MAX_ARCH_ISR_ID >= 662))
#if (EE_CAX_662_ISR_CAT == 2)
 { 662, EE_CAX_ISR2_PRI(EE_CAX_662_ISR_PRI) },
#else
 { 662, EE_CAX_ISR1_PRI(EE_CAX_662_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_663_ISR) && (EE_CAX_MAX_ISR_ID >= 663) && (EE_CAX_MAX_ARCH_ISR_ID >= 663))
#if (EE_CAX_663_ISR_CAT == 2)
 { 663, EE_CAX_ISR2_PRI(EE_CAX_663_ISR_PRI) },
#else
 { 663, EE_CAX_ISR1_PRI(EE_CAX_663_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_664_ISR) && (EE_CAX_MAX_ISR_ID >= 664) && (EE_CAX_MAX_ARCH_ISR_ID >= 664))
#if (EE_CAX_664_ISR_CAT == 2)
 { 664, EE_CAX_ISR2_PRI(EE_CAX_664_ISR_PRI) },
#else
 { 664, EE_CAX_ISR1_PRI(EE_CAX_664_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_665_ISR) && (EE_CAX_MAX_ISR_ID >= 665) && (EE_CAX_MAX_ARCH_ISR_ID >= 665))
#if (EE_CAX_665_ISR_CAT == 2)
 { 665, EE_CAX_ISR2_PRI(EE_CAX_665_ISR_PRI) },
#else
 { 665, EE_CAX_ISR1_PRI(EE_CAX_665_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_666_ISR) && (EE_CAX_MAX_ISR_ID >= 666) && (EE_CAX_MAX_ARCH_ISR_ID >= 666))
#if (EE_CAX_666_ISR_CAT == 2)
 { 666, EE_CAX_ISR2_PRI(EE_CAX_666_ISR_PRI) },
#else
 { 666, EE_CAX_ISR1_PRI(EE_CAX_666_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_667_ISR) && (EE_CAX_MAX_ISR_ID >= 667) && (EE_CAX_MAX_ARCH_ISR_ID >= 667))
#if (EE_CAX_667_ISR_CAT == 2)
 { 667, EE_CAX_ISR2_PRI(EE_CAX_667_ISR_PRI) },
#else
 { 667, EE_CAX_ISR1_PRI(EE_CAX_667_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_668_ISR) && (EE_CAX_MAX_ISR_ID >= 668) && (EE_CAX_MAX_ARCH_ISR_ID >= 668))
#if (EE_CAX_668_ISR_CAT == 2)
 { 668, EE_CAX_ISR2_PRI(EE_CAX_668_ISR_PRI) },
#else
 { 668, EE_CAX_ISR1_PRI(EE_CAX_668_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_669_ISR) && (EE_CAX_MAX_ISR_ID >= 669) && (EE_CAX_MAX_ARCH_ISR_ID >= 669))
#if (EE_CAX_669_ISR_CAT == 2)
 { 669, EE_CAX_ISR2_PRI(EE_CAX_669_ISR_PRI) },
#else
 { 669, EE_CAX_ISR1_PRI(EE_CAX_669_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_670_ISR) && (EE_CAX_MAX_ISR_ID >= 670) && (EE_CAX_MAX_ARCH_ISR_ID >= 670))
#if (EE_CAX_670_ISR_CAT == 2)
 { 670, EE_CAX_ISR2_PRI(EE_CAX_670_ISR_PRI) },
#else
 { 670, EE_CAX_ISR1_PRI(EE_CAX_670_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_671_ISR) && (EE_CAX_MAX_ISR_ID >= 671) && (EE_CAX_MAX_ARCH_ISR_ID >= 671))
#if (EE_CAX_671_ISR_CAT == 2)
 { 671, EE_CAX_ISR2_PRI(EE_CAX_671_ISR_PRI) },
#else
 { 671, EE_CAX_ISR1_PRI(EE_CAX_671_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_672_ISR) && (EE_CAX_MAX_ISR_ID >= 672) && (EE_CAX_MAX_ARCH_ISR_ID >= 672))
#if (EE_CAX_672_ISR_CAT == 2)
 { 672, EE_CAX_ISR2_PRI(EE_CAX_672_ISR_PRI) },
#else
 { 672, EE_CAX_ISR1_PRI(EE_CAX_672_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_673_ISR) && (EE_CAX_MAX_ISR_ID >= 673) && (EE_CAX_MAX_ARCH_ISR_ID >= 673))
#if (EE_CAX_673_ISR_CAT == 2)
 { 673, EE_CAX_ISR2_PRI(EE_CAX_673_ISR_PRI) },
#else
 { 673, EE_CAX_ISR1_PRI(EE_CAX_673_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_674_ISR) && (EE_CAX_MAX_ISR_ID >= 674) && (EE_CAX_MAX_ARCH_ISR_ID >= 674))
#if (EE_CAX_674_ISR_CAT == 2)
 { 674, EE_CAX_ISR2_PRI(EE_CAX_674_ISR_PRI) },
#else
 { 674, EE_CAX_ISR1_PRI(EE_CAX_674_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_675_ISR) && (EE_CAX_MAX_ISR_ID >= 675) && (EE_CAX_MAX_ARCH_ISR_ID >= 675))
#if (EE_CAX_675_ISR_CAT == 2)
 { 675, EE_CAX_ISR2_PRI(EE_CAX_675_ISR_PRI) },
#else
 { 675, EE_CAX_ISR1_PRI(EE_CAX_675_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_676_ISR) && (EE_CAX_MAX_ISR_ID >= 676) && (EE_CAX_MAX_ARCH_ISR_ID >= 676))
#if (EE_CAX_676_ISR_CAT == 2)
 { 676, EE_CAX_ISR2_PRI(EE_CAX_676_ISR_PRI) },
#else
 { 676, EE_CAX_ISR1_PRI(EE_CAX_676_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_677_ISR) && (EE_CAX_MAX_ISR_ID >= 677) && (EE_CAX_MAX_ARCH_ISR_ID >= 677))
#if (EE_CAX_677_ISR_CAT == 2)
 { 677, EE_CAX_ISR2_PRI(EE_CAX_677_ISR_PRI) },
#else
 { 677, EE_CAX_ISR1_PRI(EE_CAX_677_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_678_ISR) && (EE_CAX_MAX_ISR_ID >= 678) && (EE_CAX_MAX_ARCH_ISR_ID >= 678))
#if (EE_CAX_678_ISR_CAT == 2)
 { 678, EE_CAX_ISR2_PRI(EE_CAX_678_ISR_PRI) },
#else
 { 678, EE_CAX_ISR1_PRI(EE_CAX_678_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_679_ISR) && (EE_CAX_MAX_ISR_ID >= 679) && (EE_CAX_MAX_ARCH_ISR_ID >= 679))
#if (EE_CAX_679_ISR_CAT == 2)
 { 679, EE_CAX_ISR2_PRI(EE_CAX_679_ISR_PRI) },
#else
 { 679, EE_CAX_ISR1_PRI(EE_CAX_679_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_680_ISR) && (EE_CAX_MAX_ISR_ID >= 680) && (EE_CAX_MAX_ARCH_ISR_ID >= 680))
#if (EE_CAX_680_ISR_CAT == 2)
 { 680, EE_CAX_ISR2_PRI(EE_CAX_680_ISR_PRI) },
#else
 { 680, EE_CAX_ISR1_PRI(EE_CAX_680_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_681_ISR) && (EE_CAX_MAX_ISR_ID >= 681) && (EE_CAX_MAX_ARCH_ISR_ID >= 681))
#if (EE_CAX_681_ISR_CAT == 2)
 { 681, EE_CAX_ISR2_PRI(EE_CAX_681_ISR_PRI) },
#else
 { 681, EE_CAX_ISR1_PRI(EE_CAX_681_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_682_ISR) && (EE_CAX_MAX_ISR_ID >= 682) && (EE_CAX_MAX_ARCH_ISR_ID >= 682))
#if (EE_CAX_682_ISR_CAT == 2)
 { 682, EE_CAX_ISR2_PRI(EE_CAX_682_ISR_PRI) },
#else
 { 682, EE_CAX_ISR1_PRI(EE_CAX_682_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_683_ISR) && (EE_CAX_MAX_ISR_ID >= 683) && (EE_CAX_MAX_ARCH_ISR_ID >= 683))
#if (EE_CAX_683_ISR_CAT == 2)
 { 683, EE_CAX_ISR2_PRI(EE_CAX_683_ISR_PRI) },
#else
 { 683, EE_CAX_ISR1_PRI(EE_CAX_683_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_684_ISR) && (EE_CAX_MAX_ISR_ID >= 684) && (EE_CAX_MAX_ARCH_ISR_ID >= 684))
#if (EE_CAX_684_ISR_CAT == 2)
 { 684, EE_CAX_ISR2_PRI(EE_CAX_684_ISR_PRI) },
#else
 { 684, EE_CAX_ISR1_PRI(EE_CAX_684_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_685_ISR) && (EE_CAX_MAX_ISR_ID >= 685) && (EE_CAX_MAX_ARCH_ISR_ID >= 685))
#if (EE_CAX_685_ISR_CAT == 2)
 { 685, EE_CAX_ISR2_PRI(EE_CAX_685_ISR_PRI) },
#else
 { 685, EE_CAX_ISR1_PRI(EE_CAX_685_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_686_ISR) && (EE_CAX_MAX_ISR_ID >= 686) && (EE_CAX_MAX_ARCH_ISR_ID >= 686))
#if (EE_CAX_686_ISR_CAT == 2)
 { 686, EE_CAX_ISR2_PRI(EE_CAX_686_ISR_PRI) },
#else
 { 686, EE_CAX_ISR1_PRI(EE_CAX_686_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_687_ISR) && (EE_CAX_MAX_ISR_ID >= 687) && (EE_CAX_MAX_ARCH_ISR_ID >= 687))
#if (EE_CAX_687_ISR_CAT == 2)
 { 687, EE_CAX_ISR2_PRI(EE_CAX_687_ISR_PRI) },
#else
 { 687, EE_CAX_ISR1_PRI(EE_CAX_687_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_688_ISR) && (EE_CAX_MAX_ISR_ID >= 688) && (EE_CAX_MAX_ARCH_ISR_ID >= 688))
#if (EE_CAX_688_ISR_CAT == 2)
 { 688, EE_CAX_ISR2_PRI(EE_CAX_688_ISR_PRI) },
#else
 { 688, EE_CAX_ISR1_PRI(EE_CAX_688_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_689_ISR) && (EE_CAX_MAX_ISR_ID >= 689) && (EE_CAX_MAX_ARCH_ISR_ID >= 689))
#if (EE_CAX_689_ISR_CAT == 2)
 { 689, EE_CAX_ISR2_PRI(EE_CAX_689_ISR_PRI) },
#else
 { 689, EE_CAX_ISR1_PRI(EE_CAX_689_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_690_ISR) && (EE_CAX_MAX_ISR_ID >= 690) && (EE_CAX_MAX_ARCH_ISR_ID >= 690))
#if (EE_CAX_690_ISR_CAT == 2)
 { 690, EE_CAX_ISR2_PRI(EE_CAX_690_ISR_PRI) },
#else
 { 690, EE_CAX_ISR1_PRI(EE_CAX_690_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_691_ISR) && (EE_CAX_MAX_ISR_ID >= 691) && (EE_CAX_MAX_ARCH_ISR_ID >= 691))
#if (EE_CAX_691_ISR_CAT == 2)
 { 691, EE_CAX_ISR2_PRI(EE_CAX_691_ISR_PRI) },
#else
 { 691, EE_CAX_ISR1_PRI(EE_CAX_691_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_692_ISR) && (EE_CAX_MAX_ISR_ID >= 692) && (EE_CAX_MAX_ARCH_ISR_ID >= 692))
#if (EE_CAX_692_ISR_CAT == 2)
 { 692, EE_CAX_ISR2_PRI(EE_CAX_692_ISR_PRI) },
#else
 { 692, EE_CAX_ISR1_PRI(EE_CAX_692_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_693_ISR) && (EE_CAX_MAX_ISR_ID >= 693) && (EE_CAX_MAX_ARCH_ISR_ID >= 693))
#if (EE_CAX_693_ISR_CAT == 2)
 { 693, EE_CAX_ISR2_PRI(EE_CAX_693_ISR_PRI) },
#else
 { 693, EE_CAX_ISR1_PRI(EE_CAX_693_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_694_ISR) && (EE_CAX_MAX_ISR_ID >= 694) && (EE_CAX_MAX_ARCH_ISR_ID >= 694))
#if (EE_CAX_694_ISR_CAT == 2)
 { 694, EE_CAX_ISR2_PRI(EE_CAX_694_ISR_PRI) },
#else
 { 694, EE_CAX_ISR1_PRI(EE_CAX_694_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_695_ISR) && (EE_CAX_MAX_ISR_ID >= 695) && (EE_CAX_MAX_ARCH_ISR_ID >= 695))
#if (EE_CAX_695_ISR_CAT == 2)
 { 695, EE_CAX_ISR2_PRI(EE_CAX_695_ISR_PRI) },
#else
 { 695, EE_CAX_ISR1_PRI(EE_CAX_695_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_696_ISR) && (EE_CAX_MAX_ISR_ID >= 696) && (EE_CAX_MAX_ARCH_ISR_ID >= 696))
#if (EE_CAX_696_ISR_CAT == 2)
 { 696, EE_CAX_ISR2_PRI(EE_CAX_696_ISR_PRI) },
#else
 { 696, EE_CAX_ISR1_PRI(EE_CAX_696_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_697_ISR) && (EE_CAX_MAX_ISR_ID >= 697) && (EE_CAX_MAX_ARCH_ISR_ID >= 697))
#if (EE_CAX_697_ISR_CAT == 2)
 { 697, EE_CAX_ISR2_PRI(EE_CAX_697_ISR_PRI) },
#else
 { 697, EE_CAX_ISR1_PRI(EE_CAX_697_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_698_ISR) && (EE_CAX_MAX_ISR_ID >= 698) && (EE_CAX_MAX_ARCH_ISR_ID >= 698))
#if (EE_CAX_698_ISR_CAT == 2)
 { 698, EE_CAX_ISR2_PRI(EE_CAX_698_ISR_PRI) },
#else
 { 698, EE_CAX_ISR1_PRI(EE_CAX_698_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_699_ISR) && (EE_CAX_MAX_ISR_ID >= 699) && (EE_CAX_MAX_ARCH_ISR_ID >= 699))
#if (EE_CAX_699_ISR_CAT == 2)
 { 699, EE_CAX_ISR2_PRI(EE_CAX_699_ISR_PRI) },
#else
 { 699, EE_CAX_ISR1_PRI(EE_CAX_699_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_700_ISR) && (EE_CAX_MAX_ISR_ID >= 700) && (EE_CAX_MAX_ARCH_ISR_ID >= 700))
#if (EE_CAX_700_ISR_CAT == 2)
 { 700, EE_CAX_ISR2_PRI(EE_CAX_700_ISR_PRI) },
#else
 { 700, EE_CAX_ISR1_PRI(EE_CAX_700_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_701_ISR) && (EE_CAX_MAX_ISR_ID >= 701) && (EE_CAX_MAX_ARCH_ISR_ID >= 701))
#if (EE_CAX_701_ISR_CAT == 2)
 { 701, EE_CAX_ISR2_PRI(EE_CAX_701_ISR_PRI) },
#else
 { 701, EE_CAX_ISR1_PRI(EE_CAX_701_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_702_ISR) && (EE_CAX_MAX_ISR_ID >= 702) && (EE_CAX_MAX_ARCH_ISR_ID >= 702))
#if (EE_CAX_702_ISR_CAT == 2)
 { 702, EE_CAX_ISR2_PRI(EE_CAX_702_ISR_PRI) },
#else
 { 702, EE_CAX_ISR1_PRI(EE_CAX_702_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_703_ISR) && (EE_CAX_MAX_ISR_ID >= 703) && (EE_CAX_MAX_ARCH_ISR_ID >= 703))
#if (EE_CAX_703_ISR_CAT == 2)
 { 703, EE_CAX_ISR2_PRI(EE_CAX_703_ISR_PRI) },
#else
 { 703, EE_CAX_ISR1_PRI(EE_CAX_703_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_704_ISR) && (EE_CAX_MAX_ISR_ID >= 704) && (EE_CAX_MAX_ARCH_ISR_ID >= 704))
#if (EE_CAX_704_ISR_CAT == 2)
 { 704, EE_CAX_ISR2_PRI(EE_CAX_704_ISR_PRI) },
#else
 { 704, EE_CAX_ISR1_PRI(EE_CAX_704_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_705_ISR) && (EE_CAX_MAX_ISR_ID >= 705) && (EE_CAX_MAX_ARCH_ISR_ID >= 705))
#if (EE_CAX_705_ISR_CAT == 2)
 { 705, EE_CAX_ISR2_PRI(EE_CAX_705_ISR_PRI) },
#else
 { 705, EE_CAX_ISR1_PRI(EE_CAX_705_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_706_ISR) && (EE_CAX_MAX_ISR_ID >= 706) && (EE_CAX_MAX_ARCH_ISR_ID >= 706))
#if (EE_CAX_706_ISR_CAT == 2)
 { 706, EE_CAX_ISR2_PRI(EE_CAX_706_ISR_PRI) },
#else
 { 706, EE_CAX_ISR1_PRI(EE_CAX_706_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_707_ISR) && (EE_CAX_MAX_ISR_ID >= 707) && (EE_CAX_MAX_ARCH_ISR_ID >= 707))
#if (EE_CAX_707_ISR_CAT == 2)
 { 707, EE_CAX_ISR2_PRI(EE_CAX_707_ISR_PRI) },
#else
 { 707, EE_CAX_ISR1_PRI(EE_CAX_707_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_708_ISR) && (EE_CAX_MAX_ISR_ID >= 708) && (EE_CAX_MAX_ARCH_ISR_ID >= 708))
#if (EE_CAX_708_ISR_CAT == 2)
 { 708, EE_CAX_ISR2_PRI(EE_CAX_708_ISR_PRI) },
#else
 { 708, EE_CAX_ISR1_PRI(EE_CAX_708_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_709_ISR) && (EE_CAX_MAX_ISR_ID >= 709) && (EE_CAX_MAX_ARCH_ISR_ID >= 709))
#if (EE_CAX_709_ISR_CAT == 2)
 { 709, EE_CAX_ISR2_PRI(EE_CAX_709_ISR_PRI) },
#else
 { 709, EE_CAX_ISR1_PRI(EE_CAX_709_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_710_ISR) && (EE_CAX_MAX_ISR_ID >= 710) && (EE_CAX_MAX_ARCH_ISR_ID >= 710))
#if (EE_CAX_710_ISR_CAT == 2)
 { 710, EE_CAX_ISR2_PRI(EE_CAX_710_ISR_PRI) },
#else
 { 710, EE_CAX_ISR1_PRI(EE_CAX_710_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_711_ISR) && (EE_CAX_MAX_ISR_ID >= 711) && (EE_CAX_MAX_ARCH_ISR_ID >= 711))
#if (EE_CAX_711_ISR_CAT == 2)
 { 711, EE_CAX_ISR2_PRI(EE_CAX_711_ISR_PRI) },
#else
 { 711, EE_CAX_ISR1_PRI(EE_CAX_711_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_712_ISR) && (EE_CAX_MAX_ISR_ID >= 712) && (EE_CAX_MAX_ARCH_ISR_ID >= 712))
#if (EE_CAX_712_ISR_CAT == 2)
 { 712, EE_CAX_ISR2_PRI(EE_CAX_712_ISR_PRI) },
#else
 { 712, EE_CAX_ISR1_PRI(EE_CAX_712_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_713_ISR) && (EE_CAX_MAX_ISR_ID >= 713) && (EE_CAX_MAX_ARCH_ISR_ID >= 713))
#if (EE_CAX_713_ISR_CAT == 2)
 { 713, EE_CAX_ISR2_PRI(EE_CAX_713_ISR_PRI) },
#else
 { 713, EE_CAX_ISR1_PRI(EE_CAX_713_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_714_ISR) && (EE_CAX_MAX_ISR_ID >= 714) && (EE_CAX_MAX_ARCH_ISR_ID >= 714))
#if (EE_CAX_714_ISR_CAT == 2)
 { 714, EE_CAX_ISR2_PRI(EE_CAX_714_ISR_PRI) },
#else
 { 714, EE_CAX_ISR1_PRI(EE_CAX_714_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_715_ISR) && (EE_CAX_MAX_ISR_ID >= 715) && (EE_CAX_MAX_ARCH_ISR_ID >= 715))
#if (EE_CAX_715_ISR_CAT == 2)
 { 715, EE_CAX_ISR2_PRI(EE_CAX_715_ISR_PRI) },
#else
 { 715, EE_CAX_ISR1_PRI(EE_CAX_715_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_716_ISR) && (EE_CAX_MAX_ISR_ID >= 716) && (EE_CAX_MAX_ARCH_ISR_ID >= 716))
#if (EE_CAX_716_ISR_CAT == 2)
 { 716, EE_CAX_ISR2_PRI(EE_CAX_716_ISR_PRI) },
#else
 { 716, EE_CAX_ISR1_PRI(EE_CAX_716_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_717_ISR) && (EE_CAX_MAX_ISR_ID >= 717) && (EE_CAX_MAX_ARCH_ISR_ID >= 717))
#if (EE_CAX_717_ISR_CAT == 2)
 { 717, EE_CAX_ISR2_PRI(EE_CAX_717_ISR_PRI) },
#else
 { 717, EE_CAX_ISR1_PRI(EE_CAX_717_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_718_ISR) && (EE_CAX_MAX_ISR_ID >= 718) && (EE_CAX_MAX_ARCH_ISR_ID >= 718))
#if (EE_CAX_718_ISR_CAT == 2)
 { 718, EE_CAX_ISR2_PRI(EE_CAX_718_ISR_PRI) },
#else
 { 718, EE_CAX_ISR1_PRI(EE_CAX_718_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_719_ISR) && (EE_CAX_MAX_ISR_ID >= 719) && (EE_CAX_MAX_ARCH_ISR_ID >= 719))
#if (EE_CAX_719_ISR_CAT == 2)
 { 719, EE_CAX_ISR2_PRI(EE_CAX_719_ISR_PRI) },
#else
 { 719, EE_CAX_ISR1_PRI(EE_CAX_719_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_720_ISR) && (EE_CAX_MAX_ISR_ID >= 720) && (EE_CAX_MAX_ARCH_ISR_ID >= 720))
#if (EE_CAX_720_ISR_CAT == 2)
 { 720, EE_CAX_ISR2_PRI(EE_CAX_720_ISR_PRI) },
#else
 { 720, EE_CAX_ISR1_PRI(EE_CAX_720_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_721_ISR) && (EE_CAX_MAX_ISR_ID >= 721) && (EE_CAX_MAX_ARCH_ISR_ID >= 721))
#if (EE_CAX_721_ISR_CAT == 2)
 { 721, EE_CAX_ISR2_PRI(EE_CAX_721_ISR_PRI) },
#else
 { 721, EE_CAX_ISR1_PRI(EE_CAX_721_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_722_ISR) && (EE_CAX_MAX_ISR_ID >= 722) && (EE_CAX_MAX_ARCH_ISR_ID >= 722))
#if (EE_CAX_722_ISR_CAT == 2)
 { 722, EE_CAX_ISR2_PRI(EE_CAX_722_ISR_PRI) },
#else
 { 722, EE_CAX_ISR1_PRI(EE_CAX_722_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_723_ISR) && (EE_CAX_MAX_ISR_ID >= 723) && (EE_CAX_MAX_ARCH_ISR_ID >= 723))
#if (EE_CAX_723_ISR_CAT == 2)
 { 723, EE_CAX_ISR2_PRI(EE_CAX_723_ISR_PRI) },
#else
 { 723, EE_CAX_ISR1_PRI(EE_CAX_723_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_724_ISR) && (EE_CAX_MAX_ISR_ID >= 724) && (EE_CAX_MAX_ARCH_ISR_ID >= 724))
#if (EE_CAX_724_ISR_CAT == 2)
 { 724, EE_CAX_ISR2_PRI(EE_CAX_724_ISR_PRI) },
#else
 { 724, EE_CAX_ISR1_PRI(EE_CAX_724_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_725_ISR) && (EE_CAX_MAX_ISR_ID >= 725) && (EE_CAX_MAX_ARCH_ISR_ID >= 725))
#if (EE_CAX_725_ISR_CAT == 2)
 { 725, EE_CAX_ISR2_PRI(EE_CAX_725_ISR_PRI) },
#else
 { 725, EE_CAX_ISR1_PRI(EE_CAX_725_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_726_ISR) && (EE_CAX_MAX_ISR_ID >= 726) && (EE_CAX_MAX_ARCH_ISR_ID >= 726))
#if (EE_CAX_726_ISR_CAT == 2)
 { 726, EE_CAX_ISR2_PRI(EE_CAX_726_ISR_PRI) },
#else
 { 726, EE_CAX_ISR1_PRI(EE_CAX_726_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_727_ISR) && (EE_CAX_MAX_ISR_ID >= 727) && (EE_CAX_MAX_ARCH_ISR_ID >= 727))
#if (EE_CAX_727_ISR_CAT == 2)
 { 727, EE_CAX_ISR2_PRI(EE_CAX_727_ISR_PRI) },
#else
 { 727, EE_CAX_ISR1_PRI(EE_CAX_727_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_728_ISR) && (EE_CAX_MAX_ISR_ID >= 728) && (EE_CAX_MAX_ARCH_ISR_ID >= 728))
#if (EE_CAX_728_ISR_CAT == 2)
 { 728, EE_CAX_ISR2_PRI(EE_CAX_728_ISR_PRI) },
#else
 { 728, EE_CAX_ISR1_PRI(EE_CAX_728_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_729_ISR) && (EE_CAX_MAX_ISR_ID >= 729) && (EE_CAX_MAX_ARCH_ISR_ID >= 729))
#if (EE_CAX_729_ISR_CAT == 2)
 { 729, EE_CAX_ISR2_PRI(EE_CAX_729_ISR_PRI) },
#else
 { 729, EE_CAX_ISR1_PRI(EE_CAX_729_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_730_ISR) && (EE_CAX_MAX_ISR_ID >= 730) && (EE_CAX_MAX_ARCH_ISR_ID >= 730))
#if (EE_CAX_730_ISR_CAT == 2)
 { 730, EE_CAX_ISR2_PRI(EE_CAX_730_ISR_PRI) },
#else
 { 730, EE_CAX_ISR1_PRI(EE_CAX_730_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_731_ISR) && (EE_CAX_MAX_ISR_ID >= 731) && (EE_CAX_MAX_ARCH_ISR_ID >= 731))
#if (EE_CAX_731_ISR_CAT == 2)
 { 731, EE_CAX_ISR2_PRI(EE_CAX_731_ISR_PRI) },
#else
 { 731, EE_CAX_ISR1_PRI(EE_CAX_731_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_732_ISR) && (EE_CAX_MAX_ISR_ID >= 732) && (EE_CAX_MAX_ARCH_ISR_ID >= 732))
#if (EE_CAX_732_ISR_CAT == 2)
 { 732, EE_CAX_ISR2_PRI(EE_CAX_732_ISR_PRI) },
#else
 { 732, EE_CAX_ISR1_PRI(EE_CAX_732_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_733_ISR) && (EE_CAX_MAX_ISR_ID >= 733) && (EE_CAX_MAX_ARCH_ISR_ID >= 733))
#if (EE_CAX_733_ISR_CAT == 2)
 { 733, EE_CAX_ISR2_PRI(EE_CAX_733_ISR_PRI) },
#else
 { 733, EE_CAX_ISR1_PRI(EE_CAX_733_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_734_ISR) && (EE_CAX_MAX_ISR_ID >= 734) && (EE_CAX_MAX_ARCH_ISR_ID >= 734))
#if (EE_CAX_734_ISR_CAT == 2)
 { 734, EE_CAX_ISR2_PRI(EE_CAX_734_ISR_PRI) },
#else
 { 734, EE_CAX_ISR1_PRI(EE_CAX_734_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_735_ISR) && (EE_CAX_MAX_ISR_ID >= 735) && (EE_CAX_MAX_ARCH_ISR_ID >= 735))
#if (EE_CAX_735_ISR_CAT == 2)
 { 735, EE_CAX_ISR2_PRI(EE_CAX_735_ISR_PRI) },
#else
 { 735, EE_CAX_ISR1_PRI(EE_CAX_735_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_736_ISR) && (EE_CAX_MAX_ISR_ID >= 736) && (EE_CAX_MAX_ARCH_ISR_ID >= 736))
#if (EE_CAX_736_ISR_CAT == 2)
 { 736, EE_CAX_ISR2_PRI(EE_CAX_736_ISR_PRI) },
#else
 { 736, EE_CAX_ISR1_PRI(EE_CAX_736_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_737_ISR) && (EE_CAX_MAX_ISR_ID >= 737) && (EE_CAX_MAX_ARCH_ISR_ID >= 737))
#if (EE_CAX_737_ISR_CAT == 2)
 { 737, EE_CAX_ISR2_PRI(EE_CAX_737_ISR_PRI) },
#else
 { 737, EE_CAX_ISR1_PRI(EE_CAX_737_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_738_ISR) && (EE_CAX_MAX_ISR_ID >= 738) && (EE_CAX_MAX_ARCH_ISR_ID >= 738))
#if (EE_CAX_738_ISR_CAT == 2)
 { 738, EE_CAX_ISR2_PRI(EE_CAX_738_ISR_PRI) },
#else
 { 738, EE_CAX_ISR1_PRI(EE_CAX_738_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_739_ISR) && (EE_CAX_MAX_ISR_ID >= 739) && (EE_CAX_MAX_ARCH_ISR_ID >= 739))
#if (EE_CAX_739_ISR_CAT == 2)
 { 739, EE_CAX_ISR2_PRI(EE_CAX_739_ISR_PRI) },
#else
 { 739, EE_CAX_ISR1_PRI(EE_CAX_739_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_740_ISR) && (EE_CAX_MAX_ISR_ID >= 740) && (EE_CAX_MAX_ARCH_ISR_ID >= 740))
#if (EE_CAX_740_ISR_CAT == 2)
 { 740, EE_CAX_ISR2_PRI(EE_CAX_740_ISR_PRI) },
#else
 { 740, EE_CAX_ISR1_PRI(EE_CAX_740_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_741_ISR) && (EE_CAX_MAX_ISR_ID >= 741) && (EE_CAX_MAX_ARCH_ISR_ID >= 741))
#if (EE_CAX_741_ISR_CAT == 2)
 { 741, EE_CAX_ISR2_PRI(EE_CAX_741_ISR_PRI) },
#else
 { 741, EE_CAX_ISR1_PRI(EE_CAX_741_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_742_ISR) && (EE_CAX_MAX_ISR_ID >= 742) && (EE_CAX_MAX_ARCH_ISR_ID >= 742))
#if (EE_CAX_742_ISR_CAT == 2)
 { 742, EE_CAX_ISR2_PRI(EE_CAX_742_ISR_PRI) },
#else
 { 742, EE_CAX_ISR1_PRI(EE_CAX_742_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_743_ISR) && (EE_CAX_MAX_ISR_ID >= 743) && (EE_CAX_MAX_ARCH_ISR_ID >= 743))
#if (EE_CAX_743_ISR_CAT == 2)
 { 743, EE_CAX_ISR2_PRI(EE_CAX_743_ISR_PRI) },
#else
 { 743, EE_CAX_ISR1_PRI(EE_CAX_743_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_744_ISR) && (EE_CAX_MAX_ISR_ID >= 744) && (EE_CAX_MAX_ARCH_ISR_ID >= 744))
#if (EE_CAX_744_ISR_CAT == 2)
 { 744, EE_CAX_ISR2_PRI(EE_CAX_744_ISR_PRI) },
#else
 { 744, EE_CAX_ISR1_PRI(EE_CAX_744_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_745_ISR) && (EE_CAX_MAX_ISR_ID >= 745) && (EE_CAX_MAX_ARCH_ISR_ID >= 745))
#if (EE_CAX_745_ISR_CAT == 2)
 { 745, EE_CAX_ISR2_PRI(EE_CAX_745_ISR_PRI) },
#else
 { 745, EE_CAX_ISR1_PRI(EE_CAX_745_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_746_ISR) && (EE_CAX_MAX_ISR_ID >= 746) && (EE_CAX_MAX_ARCH_ISR_ID >= 746))
#if (EE_CAX_746_ISR_CAT == 2)
 { 746, EE_CAX_ISR2_PRI(EE_CAX_746_ISR_PRI) },
#else
 { 746, EE_CAX_ISR1_PRI(EE_CAX_746_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_747_ISR) && (EE_CAX_MAX_ISR_ID >= 747) && (EE_CAX_MAX_ARCH_ISR_ID >= 747))
#if (EE_CAX_747_ISR_CAT == 2)
 { 747, EE_CAX_ISR2_PRI(EE_CAX_747_ISR_PRI) },
#else
 { 747, EE_CAX_ISR1_PRI(EE_CAX_747_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_748_ISR) && (EE_CAX_MAX_ISR_ID >= 748) && (EE_CAX_MAX_ARCH_ISR_ID >= 748))
#if (EE_CAX_748_ISR_CAT == 2)
 { 748, EE_CAX_ISR2_PRI(EE_CAX_748_ISR_PRI) },
#else
 { 748, EE_CAX_ISR1_PRI(EE_CAX_748_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_749_ISR) && (EE_CAX_MAX_ISR_ID >= 749) && (EE_CAX_MAX_ARCH_ISR_ID >= 749))
#if (EE_CAX_749_ISR_CAT == 2)
 { 749, EE_CAX_ISR2_PRI(EE_CAX_749_ISR_PRI) },
#else
 { 749, EE_CAX_ISR1_PRI(EE_CAX_749_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_750_ISR) && (EE_CAX_MAX_ISR_ID >= 750) && (EE_CAX_MAX_ARCH_ISR_ID >= 750))
#if (EE_CAX_750_ISR_CAT == 2)
 { 750, EE_CAX_ISR2_PRI(EE_CAX_750_ISR_PRI) },
#else
 { 750, EE_CAX_ISR1_PRI(EE_CAX_750_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_751_ISR) && (EE_CAX_MAX_ISR_ID >= 751) && (EE_CAX_MAX_ARCH_ISR_ID >= 751))
#if (EE_CAX_751_ISR_CAT == 2)
 { 751, EE_CAX_ISR2_PRI(EE_CAX_751_ISR_PRI) },
#else
 { 751, EE_CAX_ISR1_PRI(EE_CAX_751_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_752_ISR) && (EE_CAX_MAX_ISR_ID >= 752) && (EE_CAX_MAX_ARCH_ISR_ID >= 752))
#if (EE_CAX_752_ISR_CAT == 2)
 { 752, EE_CAX_ISR2_PRI(EE_CAX_752_ISR_PRI) },
#else
 { 752, EE_CAX_ISR1_PRI(EE_CAX_752_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_753_ISR) && (EE_CAX_MAX_ISR_ID >= 753) && (EE_CAX_MAX_ARCH_ISR_ID >= 753))
#if (EE_CAX_753_ISR_CAT == 2)
 { 753, EE_CAX_ISR2_PRI(EE_CAX_753_ISR_PRI) },
#else
 { 753, EE_CAX_ISR1_PRI(EE_CAX_753_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_754_ISR) && (EE_CAX_MAX_ISR_ID >= 754) && (EE_CAX_MAX_ARCH_ISR_ID >= 754))
#if (EE_CAX_754_ISR_CAT == 2)
 { 754, EE_CAX_ISR2_PRI(EE_CAX_754_ISR_PRI) },
#else
 { 754, EE_CAX_ISR1_PRI(EE_CAX_754_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_755_ISR) && (EE_CAX_MAX_ISR_ID >= 755) && (EE_CAX_MAX_ARCH_ISR_ID >= 755))
#if (EE_CAX_755_ISR_CAT == 2)
 { 755, EE_CAX_ISR2_PRI(EE_CAX_755_ISR_PRI) },
#else
 { 755, EE_CAX_ISR1_PRI(EE_CAX_755_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_756_ISR) && (EE_CAX_MAX_ISR_ID >= 756) && (EE_CAX_MAX_ARCH_ISR_ID >= 756))
#if (EE_CAX_756_ISR_CAT == 2)
 { 756, EE_CAX_ISR2_PRI(EE_CAX_756_ISR_PRI) },
#else
 { 756, EE_CAX_ISR1_PRI(EE_CAX_756_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_757_ISR) && (EE_CAX_MAX_ISR_ID >= 757) && (EE_CAX_MAX_ARCH_ISR_ID >= 757))
#if (EE_CAX_757_ISR_CAT == 2)
 { 757, EE_CAX_ISR2_PRI(EE_CAX_757_ISR_PRI) },
#else
 { 757, EE_CAX_ISR1_PRI(EE_CAX_757_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_758_ISR) && (EE_CAX_MAX_ISR_ID >= 758) && (EE_CAX_MAX_ARCH_ISR_ID >= 758))
#if (EE_CAX_758_ISR_CAT == 2)
 { 758, EE_CAX_ISR2_PRI(EE_CAX_758_ISR_PRI) },
#else
 { 758, EE_CAX_ISR1_PRI(EE_CAX_758_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_759_ISR) && (EE_CAX_MAX_ISR_ID >= 759) && (EE_CAX_MAX_ARCH_ISR_ID >= 759))
#if (EE_CAX_759_ISR_CAT == 2)
 { 759, EE_CAX_ISR2_PRI(EE_CAX_759_ISR_PRI) },
#else
 { 759, EE_CAX_ISR1_PRI(EE_CAX_759_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_760_ISR) && (EE_CAX_MAX_ISR_ID >= 760) && (EE_CAX_MAX_ARCH_ISR_ID >= 760))
#if (EE_CAX_760_ISR_CAT == 2)
 { 760, EE_CAX_ISR2_PRI(EE_CAX_760_ISR_PRI) },
#else
 { 760, EE_CAX_ISR1_PRI(EE_CAX_760_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_761_ISR) && (EE_CAX_MAX_ISR_ID >= 761) && (EE_CAX_MAX_ARCH_ISR_ID >= 761))
#if (EE_CAX_761_ISR_CAT == 2)
 { 761, EE_CAX_ISR2_PRI(EE_CAX_761_ISR_PRI) },
#else
 { 761, EE_CAX_ISR1_PRI(EE_CAX_761_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_762_ISR) && (EE_CAX_MAX_ISR_ID >= 762) && (EE_CAX_MAX_ARCH_ISR_ID >= 762))
#if (EE_CAX_762_ISR_CAT == 2)
 { 762, EE_CAX_ISR2_PRI(EE_CAX_762_ISR_PRI) },
#else
 { 762, EE_CAX_ISR1_PRI(EE_CAX_762_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_763_ISR) && (EE_CAX_MAX_ISR_ID >= 763) && (EE_CAX_MAX_ARCH_ISR_ID >= 763))
#if (EE_CAX_763_ISR_CAT == 2)
 { 763, EE_CAX_ISR2_PRI(EE_CAX_763_ISR_PRI) },
#else
 { 763, EE_CAX_ISR1_PRI(EE_CAX_763_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_764_ISR) && (EE_CAX_MAX_ISR_ID >= 764) && (EE_CAX_MAX_ARCH_ISR_ID >= 764))
#if (EE_CAX_764_ISR_CAT == 2)
 { 764, EE_CAX_ISR2_PRI(EE_CAX_764_ISR_PRI) },
#else
 { 764, EE_CAX_ISR1_PRI(EE_CAX_764_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_765_ISR) && (EE_CAX_MAX_ISR_ID >= 765) && (EE_CAX_MAX_ARCH_ISR_ID >= 765))
#if (EE_CAX_765_ISR_CAT == 2)
 { 765, EE_CAX_ISR2_PRI(EE_CAX_765_ISR_PRI) },
#else
 { 765, EE_CAX_ISR1_PRI(EE_CAX_765_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_766_ISR) && (EE_CAX_MAX_ISR_ID >= 766) && (EE_CAX_MAX_ARCH_ISR_ID >= 766))
#if (EE_CAX_766_ISR_CAT == 2)
 { 766, EE_CAX_ISR2_PRI(EE_CAX_766_ISR_PRI) },
#else
 { 766, EE_CAX_ISR1_PRI(EE_CAX_766_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_767_ISR) && (EE_CAX_MAX_ISR_ID >= 767) && (EE_CAX_MAX_ARCH_ISR_ID >= 767))
#if (EE_CAX_767_ISR_CAT == 2)
 { 767, EE_CAX_ISR2_PRI(EE_CAX_767_ISR_PRI) },
#else
 { 767, EE_CAX_ISR1_PRI(EE_CAX_767_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_768_ISR) && (EE_CAX_MAX_ISR_ID >= 768) && (EE_CAX_MAX_ARCH_ISR_ID >= 768))
#if (EE_CAX_768_ISR_CAT == 2)
 { 768, EE_CAX_ISR2_PRI(EE_CAX_768_ISR_PRI) },
#else
 { 768, EE_CAX_ISR1_PRI(EE_CAX_768_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_769_ISR) && (EE_CAX_MAX_ISR_ID >= 769) && (EE_CAX_MAX_ARCH_ISR_ID >= 769))
#if (EE_CAX_769_ISR_CAT == 2)
 { 769, EE_CAX_ISR2_PRI(EE_CAX_769_ISR_PRI) },
#else
 { 769, EE_CAX_ISR1_PRI(EE_CAX_769_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_770_ISR) && (EE_CAX_MAX_ISR_ID >= 770) && (EE_CAX_MAX_ARCH_ISR_ID >= 770))
#if (EE_CAX_770_ISR_CAT == 2)
 { 770, EE_CAX_ISR2_PRI(EE_CAX_770_ISR_PRI) },
#else
 { 770, EE_CAX_ISR1_PRI(EE_CAX_770_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_771_ISR) && (EE_CAX_MAX_ISR_ID >= 771) && (EE_CAX_MAX_ARCH_ISR_ID >= 771))
#if (EE_CAX_771_ISR_CAT == 2)
 { 771, EE_CAX_ISR2_PRI(EE_CAX_771_ISR_PRI) },
#else
 { 771, EE_CAX_ISR1_PRI(EE_CAX_771_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_772_ISR) && (EE_CAX_MAX_ISR_ID >= 772) && (EE_CAX_MAX_ARCH_ISR_ID >= 772))
#if (EE_CAX_772_ISR_CAT == 2)
 { 772, EE_CAX_ISR2_PRI(EE_CAX_772_ISR_PRI) },
#else
 { 772, EE_CAX_ISR1_PRI(EE_CAX_772_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_773_ISR) && (EE_CAX_MAX_ISR_ID >= 773) && (EE_CAX_MAX_ARCH_ISR_ID >= 773))
#if (EE_CAX_773_ISR_CAT == 2)
 { 773, EE_CAX_ISR2_PRI(EE_CAX_773_ISR_PRI) },
#else
 { 773, EE_CAX_ISR1_PRI(EE_CAX_773_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_774_ISR) && (EE_CAX_MAX_ISR_ID >= 774) && (EE_CAX_MAX_ARCH_ISR_ID >= 774))
#if (EE_CAX_774_ISR_CAT == 2)
 { 774, EE_CAX_ISR2_PRI(EE_CAX_774_ISR_PRI) },
#else
 { 774, EE_CAX_ISR1_PRI(EE_CAX_774_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_775_ISR) && (EE_CAX_MAX_ISR_ID >= 775) && (EE_CAX_MAX_ARCH_ISR_ID >= 775))
#if (EE_CAX_775_ISR_CAT == 2)
 { 775, EE_CAX_ISR2_PRI(EE_CAX_775_ISR_PRI) },
#else
 { 775, EE_CAX_ISR1_PRI(EE_CAX_775_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_776_ISR) && (EE_CAX_MAX_ISR_ID >= 776) && (EE_CAX_MAX_ARCH_ISR_ID >= 776))
#if (EE_CAX_776_ISR_CAT == 2)
 { 776, EE_CAX_ISR2_PRI(EE_CAX_776_ISR_PRI) },
#else
 { 776, EE_CAX_ISR1_PRI(EE_CAX_776_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_777_ISR) && (EE_CAX_MAX_ISR_ID >= 777) && (EE_CAX_MAX_ARCH_ISR_ID >= 777))
#if (EE_CAX_777_ISR_CAT == 2)
 { 777, EE_CAX_ISR2_PRI(EE_CAX_777_ISR_PRI) },
#else
 { 777, EE_CAX_ISR1_PRI(EE_CAX_777_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_778_ISR) && (EE_CAX_MAX_ISR_ID >= 778) && (EE_CAX_MAX_ARCH_ISR_ID >= 778))
#if (EE_CAX_778_ISR_CAT == 2)
 { 778, EE_CAX_ISR2_PRI(EE_CAX_778_ISR_PRI) },
#else
 { 778, EE_CAX_ISR1_PRI(EE_CAX_778_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_779_ISR) && (EE_CAX_MAX_ISR_ID >= 779) && (EE_CAX_MAX_ARCH_ISR_ID >= 779))
#if (EE_CAX_779_ISR_CAT == 2)
 { 779, EE_CAX_ISR2_PRI(EE_CAX_779_ISR_PRI) },
#else
 { 779, EE_CAX_ISR1_PRI(EE_CAX_779_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_780_ISR) && (EE_CAX_MAX_ISR_ID >= 780) && (EE_CAX_MAX_ARCH_ISR_ID >= 780))
#if (EE_CAX_780_ISR_CAT == 2)
 { 780, EE_CAX_ISR2_PRI(EE_CAX_780_ISR_PRI) },
#else
 { 780, EE_CAX_ISR1_PRI(EE_CAX_780_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_781_ISR) && (EE_CAX_MAX_ISR_ID >= 781) && (EE_CAX_MAX_ARCH_ISR_ID >= 781))
#if (EE_CAX_781_ISR_CAT == 2)
 { 781, EE_CAX_ISR2_PRI(EE_CAX_781_ISR_PRI) },
#else
 { 781, EE_CAX_ISR1_PRI(EE_CAX_781_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_782_ISR) && (EE_CAX_MAX_ISR_ID >= 782) && (EE_CAX_MAX_ARCH_ISR_ID >= 782))
#if (EE_CAX_782_ISR_CAT == 2)
 { 782, EE_CAX_ISR2_PRI(EE_CAX_782_ISR_PRI) },
#else
 { 782, EE_CAX_ISR1_PRI(EE_CAX_782_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_783_ISR) && (EE_CAX_MAX_ISR_ID >= 783) && (EE_CAX_MAX_ARCH_ISR_ID >= 783))
#if (EE_CAX_783_ISR_CAT == 2)
 { 783, EE_CAX_ISR2_PRI(EE_CAX_783_ISR_PRI) },
#else
 { 783, EE_CAX_ISR1_PRI(EE_CAX_783_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_784_ISR) && (EE_CAX_MAX_ISR_ID >= 784) && (EE_CAX_MAX_ARCH_ISR_ID >= 784))
#if (EE_CAX_784_ISR_CAT == 2)
 { 784, EE_CAX_ISR2_PRI(EE_CAX_784_ISR_PRI) },
#else
 { 784, EE_CAX_ISR1_PRI(EE_CAX_784_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_785_ISR) && (EE_CAX_MAX_ISR_ID >= 785) && (EE_CAX_MAX_ARCH_ISR_ID >= 785))
#if (EE_CAX_785_ISR_CAT == 2)
 { 785, EE_CAX_ISR2_PRI(EE_CAX_785_ISR_PRI) },
#else
 { 785, EE_CAX_ISR1_PRI(EE_CAX_785_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_786_ISR) && (EE_CAX_MAX_ISR_ID >= 786) && (EE_CAX_MAX_ARCH_ISR_ID >= 786))
#if (EE_CAX_786_ISR_CAT == 2)
 { 786, EE_CAX_ISR2_PRI(EE_CAX_786_ISR_PRI) },
#else
 { 786, EE_CAX_ISR1_PRI(EE_CAX_786_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_787_ISR) && (EE_CAX_MAX_ISR_ID >= 787) && (EE_CAX_MAX_ARCH_ISR_ID >= 787))
#if (EE_CAX_787_ISR_CAT == 2)
 { 787, EE_CAX_ISR2_PRI(EE_CAX_787_ISR_PRI) },
#else
 { 787, EE_CAX_ISR1_PRI(EE_CAX_787_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_788_ISR) && (EE_CAX_MAX_ISR_ID >= 788) && (EE_CAX_MAX_ARCH_ISR_ID >= 788))
#if (EE_CAX_788_ISR_CAT == 2)
 { 788, EE_CAX_ISR2_PRI(EE_CAX_788_ISR_PRI) },
#else
 { 788, EE_CAX_ISR1_PRI(EE_CAX_788_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_789_ISR) && (EE_CAX_MAX_ISR_ID >= 789) && (EE_CAX_MAX_ARCH_ISR_ID >= 789))
#if (EE_CAX_789_ISR_CAT == 2)
 { 789, EE_CAX_ISR2_PRI(EE_CAX_789_ISR_PRI) },
#else
 { 789, EE_CAX_ISR1_PRI(EE_CAX_789_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_790_ISR) && (EE_CAX_MAX_ISR_ID >= 790) && (EE_CAX_MAX_ARCH_ISR_ID >= 790))
#if (EE_CAX_790_ISR_CAT == 2)
 { 790, EE_CAX_ISR2_PRI(EE_CAX_790_ISR_PRI) },
#else
 { 790, EE_CAX_ISR1_PRI(EE_CAX_790_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_791_ISR) && (EE_CAX_MAX_ISR_ID >= 791) && (EE_CAX_MAX_ARCH_ISR_ID >= 791))
#if (EE_CAX_791_ISR_CAT == 2)
 { 791, EE_CAX_ISR2_PRI(EE_CAX_791_ISR_PRI) },
#else
 { 791, EE_CAX_ISR1_PRI(EE_CAX_791_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_792_ISR) && (EE_CAX_MAX_ISR_ID >= 792) && (EE_CAX_MAX_ARCH_ISR_ID >= 792))
#if (EE_CAX_792_ISR_CAT == 2)
 { 792, EE_CAX_ISR2_PRI(EE_CAX_792_ISR_PRI) },
#else
 { 792, EE_CAX_ISR1_PRI(EE_CAX_792_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_793_ISR) && (EE_CAX_MAX_ISR_ID >= 793) && (EE_CAX_MAX_ARCH_ISR_ID >= 793))
#if (EE_CAX_793_ISR_CAT == 2)
 { 793, EE_CAX_ISR2_PRI(EE_CAX_793_ISR_PRI) },
#else
 { 793, EE_CAX_ISR1_PRI(EE_CAX_793_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_794_ISR) && (EE_CAX_MAX_ISR_ID >= 794) && (EE_CAX_MAX_ARCH_ISR_ID >= 794))
#if (EE_CAX_794_ISR_CAT == 2)
 { 794, EE_CAX_ISR2_PRI(EE_CAX_794_ISR_PRI) },
#else
 { 794, EE_CAX_ISR1_PRI(EE_CAX_794_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_795_ISR) && (EE_CAX_MAX_ISR_ID >= 795) && (EE_CAX_MAX_ARCH_ISR_ID >= 795))
#if (EE_CAX_795_ISR_CAT == 2)
 { 795, EE_CAX_ISR2_PRI(EE_CAX_795_ISR_PRI) },
#else
 { 795, EE_CAX_ISR1_PRI(EE_CAX_795_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_796_ISR) && (EE_CAX_MAX_ISR_ID >= 796) && (EE_CAX_MAX_ARCH_ISR_ID >= 796))
#if (EE_CAX_796_ISR_CAT == 2)
 { 796, EE_CAX_ISR2_PRI(EE_CAX_796_ISR_PRI) },
#else
 { 796, EE_CAX_ISR1_PRI(EE_CAX_796_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_797_ISR) && (EE_CAX_MAX_ISR_ID >= 797) && (EE_CAX_MAX_ARCH_ISR_ID >= 797))
#if (EE_CAX_797_ISR_CAT == 2)
 { 797, EE_CAX_ISR2_PRI(EE_CAX_797_ISR_PRI) },
#else
 { 797, EE_CAX_ISR1_PRI(EE_CAX_797_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_798_ISR) && (EE_CAX_MAX_ISR_ID >= 798) && (EE_CAX_MAX_ARCH_ISR_ID >= 798))
#if (EE_CAX_798_ISR_CAT == 2)
 { 798, EE_CAX_ISR2_PRI(EE_CAX_798_ISR_PRI) },
#else
 { 798, EE_CAX_ISR1_PRI(EE_CAX_798_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_799_ISR) && (EE_CAX_MAX_ISR_ID >= 799) && (EE_CAX_MAX_ARCH_ISR_ID >= 799))
#if (EE_CAX_799_ISR_CAT == 2)
 { 799, EE_CAX_ISR2_PRI(EE_CAX_799_ISR_PRI) },
#else
 { 799, EE_CAX_ISR1_PRI(EE_CAX_799_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_800_ISR) && (EE_CAX_MAX_ISR_ID >= 800) && (EE_CAX_MAX_ARCH_ISR_ID >= 800))
#if (EE_CAX_800_ISR_CAT == 2)
 { 800, EE_CAX_ISR2_PRI(EE_CAX_800_ISR_PRI) },
#else
 { 800, EE_CAX_ISR1_PRI(EE_CAX_800_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_801_ISR) && (EE_CAX_MAX_ISR_ID >= 801) && (EE_CAX_MAX_ARCH_ISR_ID >= 801))
#if (EE_CAX_801_ISR_CAT == 2)
 { 801, EE_CAX_ISR2_PRI(EE_CAX_801_ISR_PRI) },
#else
 { 801, EE_CAX_ISR1_PRI(EE_CAX_801_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_802_ISR) && (EE_CAX_MAX_ISR_ID >= 802) && (EE_CAX_MAX_ARCH_ISR_ID >= 802))
#if (EE_CAX_802_ISR_CAT == 2)
 { 802, EE_CAX_ISR2_PRI(EE_CAX_802_ISR_PRI) },
#else
 { 802, EE_CAX_ISR1_PRI(EE_CAX_802_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_803_ISR) && (EE_CAX_MAX_ISR_ID >= 803) && (EE_CAX_MAX_ARCH_ISR_ID >= 803))
#if (EE_CAX_803_ISR_CAT == 2)
 { 803, EE_CAX_ISR2_PRI(EE_CAX_803_ISR_PRI) },
#else
 { 803, EE_CAX_ISR1_PRI(EE_CAX_803_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_804_ISR) && (EE_CAX_MAX_ISR_ID >= 804) && (EE_CAX_MAX_ARCH_ISR_ID >= 804))
#if (EE_CAX_804_ISR_CAT == 2)
 { 804, EE_CAX_ISR2_PRI(EE_CAX_804_ISR_PRI) },
#else
 { 804, EE_CAX_ISR1_PRI(EE_CAX_804_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_805_ISR) && (EE_CAX_MAX_ISR_ID >= 805) && (EE_CAX_MAX_ARCH_ISR_ID >= 805))
#if (EE_CAX_805_ISR_CAT == 2)
 { 805, EE_CAX_ISR2_PRI(EE_CAX_805_ISR_PRI) },
#else
 { 805, EE_CAX_ISR1_PRI(EE_CAX_805_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_806_ISR) && (EE_CAX_MAX_ISR_ID >= 806) && (EE_CAX_MAX_ARCH_ISR_ID >= 806))
#if (EE_CAX_806_ISR_CAT == 2)
 { 806, EE_CAX_ISR2_PRI(EE_CAX_806_ISR_PRI) },
#else
 { 806, EE_CAX_ISR1_PRI(EE_CAX_806_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_807_ISR) && (EE_CAX_MAX_ISR_ID >= 807) && (EE_CAX_MAX_ARCH_ISR_ID >= 807))
#if (EE_CAX_807_ISR_CAT == 2)
 { 807, EE_CAX_ISR2_PRI(EE_CAX_807_ISR_PRI) },
#else
 { 807, EE_CAX_ISR1_PRI(EE_CAX_807_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_808_ISR) && (EE_CAX_MAX_ISR_ID >= 808) && (EE_CAX_MAX_ARCH_ISR_ID >= 808))
#if (EE_CAX_808_ISR_CAT == 2)
 { 808, EE_CAX_ISR2_PRI(EE_CAX_808_ISR_PRI) },
#else
 { 808, EE_CAX_ISR1_PRI(EE_CAX_808_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_809_ISR) && (EE_CAX_MAX_ISR_ID >= 809) && (EE_CAX_MAX_ARCH_ISR_ID >= 809))
#if (EE_CAX_809_ISR_CAT == 2)
 { 809, EE_CAX_ISR2_PRI(EE_CAX_809_ISR_PRI) },
#else
 { 809, EE_CAX_ISR1_PRI(EE_CAX_809_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_810_ISR) && (EE_CAX_MAX_ISR_ID >= 810) && (EE_CAX_MAX_ARCH_ISR_ID >= 810))
#if (EE_CAX_810_ISR_CAT == 2)
 { 810, EE_CAX_ISR2_PRI(EE_CAX_810_ISR_PRI) },
#else
 { 810, EE_CAX_ISR1_PRI(EE_CAX_810_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_811_ISR) && (EE_CAX_MAX_ISR_ID >= 811) && (EE_CAX_MAX_ARCH_ISR_ID >= 811))
#if (EE_CAX_811_ISR_CAT == 2)
 { 811, EE_CAX_ISR2_PRI(EE_CAX_811_ISR_PRI) },
#else
 { 811, EE_CAX_ISR1_PRI(EE_CAX_811_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_812_ISR) && (EE_CAX_MAX_ISR_ID >= 812) && (EE_CAX_MAX_ARCH_ISR_ID >= 812))
#if (EE_CAX_812_ISR_CAT == 2)
 { 812, EE_CAX_ISR2_PRI(EE_CAX_812_ISR_PRI) },
#else
 { 812, EE_CAX_ISR1_PRI(EE_CAX_812_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_813_ISR) && (EE_CAX_MAX_ISR_ID >= 813) && (EE_CAX_MAX_ARCH_ISR_ID >= 813))
#if (EE_CAX_813_ISR_CAT == 2)
 { 813, EE_CAX_ISR2_PRI(EE_CAX_813_ISR_PRI) },
#else
 { 813, EE_CAX_ISR1_PRI(EE_CAX_813_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_814_ISR) && (EE_CAX_MAX_ISR_ID >= 814) && (EE_CAX_MAX_ARCH_ISR_ID >= 814))
#if (EE_CAX_814_ISR_CAT == 2)
 { 814, EE_CAX_ISR2_PRI(EE_CAX_814_ISR_PRI) },
#else
 { 814, EE_CAX_ISR1_PRI(EE_CAX_814_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_815_ISR) && (EE_CAX_MAX_ISR_ID >= 815) && (EE_CAX_MAX_ARCH_ISR_ID >= 815))
#if (EE_CAX_815_ISR_CAT == 2)
 { 815, EE_CAX_ISR2_PRI(EE_CAX_815_ISR_PRI) },
#else
 { 815, EE_CAX_ISR1_PRI(EE_CAX_815_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_816_ISR) && (EE_CAX_MAX_ISR_ID >= 816) && (EE_CAX_MAX_ARCH_ISR_ID >= 816))
#if (EE_CAX_816_ISR_CAT == 2)
 { 816, EE_CAX_ISR2_PRI(EE_CAX_816_ISR_PRI) },
#else
 { 816, EE_CAX_ISR1_PRI(EE_CAX_816_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_817_ISR) && (EE_CAX_MAX_ISR_ID >= 817) && (EE_CAX_MAX_ARCH_ISR_ID >= 817))
#if (EE_CAX_817_ISR_CAT == 2)
 { 817, EE_CAX_ISR2_PRI(EE_CAX_817_ISR_PRI) },
#else
 { 817, EE_CAX_ISR1_PRI(EE_CAX_817_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_818_ISR) && (EE_CAX_MAX_ISR_ID >= 818) && (EE_CAX_MAX_ARCH_ISR_ID >= 818))
#if (EE_CAX_818_ISR_CAT == 2)
 { 818, EE_CAX_ISR2_PRI(EE_CAX_818_ISR_PRI) },
#else
 { 818, EE_CAX_ISR1_PRI(EE_CAX_818_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_819_ISR) && (EE_CAX_MAX_ISR_ID >= 819) && (EE_CAX_MAX_ARCH_ISR_ID >= 819))
#if (EE_CAX_819_ISR_CAT == 2)
 { 819, EE_CAX_ISR2_PRI(EE_CAX_819_ISR_PRI) },
#else
 { 819, EE_CAX_ISR1_PRI(EE_CAX_819_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_820_ISR) && (EE_CAX_MAX_ISR_ID >= 820) && (EE_CAX_MAX_ARCH_ISR_ID >= 820))
#if (EE_CAX_820_ISR_CAT == 2)
 { 820, EE_CAX_ISR2_PRI(EE_CAX_820_ISR_PRI) },
#else
 { 820, EE_CAX_ISR1_PRI(EE_CAX_820_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_821_ISR) && (EE_CAX_MAX_ISR_ID >= 821) && (EE_CAX_MAX_ARCH_ISR_ID >= 821))
#if (EE_CAX_821_ISR_CAT == 2)
 { 821, EE_CAX_ISR2_PRI(EE_CAX_821_ISR_PRI) },
#else
 { 821, EE_CAX_ISR1_PRI(EE_CAX_821_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_822_ISR) && (EE_CAX_MAX_ISR_ID >= 822) && (EE_CAX_MAX_ARCH_ISR_ID >= 822))
#if (EE_CAX_822_ISR_CAT == 2)
 { 822, EE_CAX_ISR2_PRI(EE_CAX_822_ISR_PRI) },
#else
 { 822, EE_CAX_ISR1_PRI(EE_CAX_822_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_823_ISR) && (EE_CAX_MAX_ISR_ID >= 823) && (EE_CAX_MAX_ARCH_ISR_ID >= 823))
#if (EE_CAX_823_ISR_CAT == 2)
 { 823, EE_CAX_ISR2_PRI(EE_CAX_823_ISR_PRI) },
#else
 { 823, EE_CAX_ISR1_PRI(EE_CAX_823_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_824_ISR) && (EE_CAX_MAX_ISR_ID >= 824) && (EE_CAX_MAX_ARCH_ISR_ID >= 824))
#if (EE_CAX_824_ISR_CAT == 2)
 { 824, EE_CAX_ISR2_PRI(EE_CAX_824_ISR_PRI) },
#else
 { 824, EE_CAX_ISR1_PRI(EE_CAX_824_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_825_ISR) && (EE_CAX_MAX_ISR_ID >= 825) && (EE_CAX_MAX_ARCH_ISR_ID >= 825))
#if (EE_CAX_825_ISR_CAT == 2)
 { 825, EE_CAX_ISR2_PRI(EE_CAX_825_ISR_PRI) },
#else
 { 825, EE_CAX_ISR1_PRI(EE_CAX_825_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_826_ISR) && (EE_CAX_MAX_ISR_ID >= 826) && (EE_CAX_MAX_ARCH_ISR_ID >= 826))
#if (EE_CAX_826_ISR_CAT == 2)
 { 826, EE_CAX_ISR2_PRI(EE_CAX_826_ISR_PRI) },
#else
 { 826, EE_CAX_ISR1_PRI(EE_CAX_826_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_827_ISR) && (EE_CAX_MAX_ISR_ID >= 827) && (EE_CAX_MAX_ARCH_ISR_ID >= 827))
#if (EE_CAX_827_ISR_CAT == 2)
 { 827, EE_CAX_ISR2_PRI(EE_CAX_827_ISR_PRI) },
#else
 { 827, EE_CAX_ISR1_PRI(EE_CAX_827_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_828_ISR) && (EE_CAX_MAX_ISR_ID >= 828) && (EE_CAX_MAX_ARCH_ISR_ID >= 828))
#if (EE_CAX_828_ISR_CAT == 2)
 { 828, EE_CAX_ISR2_PRI(EE_CAX_828_ISR_PRI) },
#else
 { 828, EE_CAX_ISR1_PRI(EE_CAX_828_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_829_ISR) && (EE_CAX_MAX_ISR_ID >= 829) && (EE_CAX_MAX_ARCH_ISR_ID >= 829))
#if (EE_CAX_829_ISR_CAT == 2)
 { 829, EE_CAX_ISR2_PRI(EE_CAX_829_ISR_PRI) },
#else
 { 829, EE_CAX_ISR1_PRI(EE_CAX_829_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_830_ISR) && (EE_CAX_MAX_ISR_ID >= 830) && (EE_CAX_MAX_ARCH_ISR_ID >= 830))
#if (EE_CAX_830_ISR_CAT == 2)
 { 830, EE_CAX_ISR2_PRI(EE_CAX_830_ISR_PRI) },
#else
 { 830, EE_CAX_ISR1_PRI(EE_CAX_830_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_831_ISR) && (EE_CAX_MAX_ISR_ID >= 831) && (EE_CAX_MAX_ARCH_ISR_ID >= 831))
#if (EE_CAX_831_ISR_CAT == 2)
 { 831, EE_CAX_ISR2_PRI(EE_CAX_831_ISR_PRI) },
#else
 { 831, EE_CAX_ISR1_PRI(EE_CAX_831_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_832_ISR) && (EE_CAX_MAX_ISR_ID >= 832) && (EE_CAX_MAX_ARCH_ISR_ID >= 832))
#if (EE_CAX_832_ISR_CAT == 2)
 { 832, EE_CAX_ISR2_PRI(EE_CAX_832_ISR_PRI) },
#else
 { 832, EE_CAX_ISR1_PRI(EE_CAX_832_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_833_ISR) && (EE_CAX_MAX_ISR_ID >= 833) && (EE_CAX_MAX_ARCH_ISR_ID >= 833))
#if (EE_CAX_833_ISR_CAT == 2)
 { 833, EE_CAX_ISR2_PRI(EE_CAX_833_ISR_PRI) },
#else
 { 833, EE_CAX_ISR1_PRI(EE_CAX_833_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_834_ISR) && (EE_CAX_MAX_ISR_ID >= 834) && (EE_CAX_MAX_ARCH_ISR_ID >= 834))
#if (EE_CAX_834_ISR_CAT == 2)
 { 834, EE_CAX_ISR2_PRI(EE_CAX_834_ISR_PRI) },
#else
 { 834, EE_CAX_ISR1_PRI(EE_CAX_834_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_835_ISR) && (EE_CAX_MAX_ISR_ID >= 835) && (EE_CAX_MAX_ARCH_ISR_ID >= 835))
#if (EE_CAX_835_ISR_CAT == 2)
 { 835, EE_CAX_ISR2_PRI(EE_CAX_835_ISR_PRI) },
#else
 { 835, EE_CAX_ISR1_PRI(EE_CAX_835_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_836_ISR) && (EE_CAX_MAX_ISR_ID >= 836) && (EE_CAX_MAX_ARCH_ISR_ID >= 836))
#if (EE_CAX_836_ISR_CAT == 2)
 { 836, EE_CAX_ISR2_PRI(EE_CAX_836_ISR_PRI) },
#else
 { 836, EE_CAX_ISR1_PRI(EE_CAX_836_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_837_ISR) && (EE_CAX_MAX_ISR_ID >= 837) && (EE_CAX_MAX_ARCH_ISR_ID >= 837))
#if (EE_CAX_837_ISR_CAT == 2)
 { 837, EE_CAX_ISR2_PRI(EE_CAX_837_ISR_PRI) },
#else
 { 837, EE_CAX_ISR1_PRI(EE_CAX_837_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_838_ISR) && (EE_CAX_MAX_ISR_ID >= 838) && (EE_CAX_MAX_ARCH_ISR_ID >= 838))
#if (EE_CAX_838_ISR_CAT == 2)
 { 838, EE_CAX_ISR2_PRI(EE_CAX_838_ISR_PRI) },
#else
 { 838, EE_CAX_ISR1_PRI(EE_CAX_838_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_839_ISR) && (EE_CAX_MAX_ISR_ID >= 839) && (EE_CAX_MAX_ARCH_ISR_ID >= 839))
#if (EE_CAX_839_ISR_CAT == 2)
 { 839, EE_CAX_ISR2_PRI(EE_CAX_839_ISR_PRI) },
#else
 { 839, EE_CAX_ISR1_PRI(EE_CAX_839_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_840_ISR) && (EE_CAX_MAX_ISR_ID >= 840) && (EE_CAX_MAX_ARCH_ISR_ID >= 840))
#if (EE_CAX_840_ISR_CAT == 2)
 { 840, EE_CAX_ISR2_PRI(EE_CAX_840_ISR_PRI) },
#else
 { 840, EE_CAX_ISR1_PRI(EE_CAX_840_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_841_ISR) && (EE_CAX_MAX_ISR_ID >= 841) && (EE_CAX_MAX_ARCH_ISR_ID >= 841))
#if (EE_CAX_841_ISR_CAT == 2)
 { 841, EE_CAX_ISR2_PRI(EE_CAX_841_ISR_PRI) },
#else
 { 841, EE_CAX_ISR1_PRI(EE_CAX_841_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_842_ISR) && (EE_CAX_MAX_ISR_ID >= 842) && (EE_CAX_MAX_ARCH_ISR_ID >= 842))
#if (EE_CAX_842_ISR_CAT == 2)
 { 842, EE_CAX_ISR2_PRI(EE_CAX_842_ISR_PRI) },
#else
 { 842, EE_CAX_ISR1_PRI(EE_CAX_842_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_843_ISR) && (EE_CAX_MAX_ISR_ID >= 843) && (EE_CAX_MAX_ARCH_ISR_ID >= 843))
#if (EE_CAX_843_ISR_CAT == 2)
 { 843, EE_CAX_ISR2_PRI(EE_CAX_843_ISR_PRI) },
#else
 { 843, EE_CAX_ISR1_PRI(EE_CAX_843_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_844_ISR) && (EE_CAX_MAX_ISR_ID >= 844) && (EE_CAX_MAX_ARCH_ISR_ID >= 844))
#if (EE_CAX_844_ISR_CAT == 2)
 { 844, EE_CAX_ISR2_PRI(EE_CAX_844_ISR_PRI) },
#else
 { 844, EE_CAX_ISR1_PRI(EE_CAX_844_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_845_ISR) && (EE_CAX_MAX_ISR_ID >= 845) && (EE_CAX_MAX_ARCH_ISR_ID >= 845))
#if (EE_CAX_845_ISR_CAT == 2)
 { 845, EE_CAX_ISR2_PRI(EE_CAX_845_ISR_PRI) },
#else
 { 845, EE_CAX_ISR1_PRI(EE_CAX_845_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_846_ISR) && (EE_CAX_MAX_ISR_ID >= 846) && (EE_CAX_MAX_ARCH_ISR_ID >= 846))
#if (EE_CAX_846_ISR_CAT == 2)
 { 846, EE_CAX_ISR2_PRI(EE_CAX_846_ISR_PRI) },
#else
 { 846, EE_CAX_ISR1_PRI(EE_CAX_846_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_847_ISR) && (EE_CAX_MAX_ISR_ID >= 847) && (EE_CAX_MAX_ARCH_ISR_ID >= 847))
#if (EE_CAX_847_ISR_CAT == 2)
 { 847, EE_CAX_ISR2_PRI(EE_CAX_847_ISR_PRI) },
#else
 { 847, EE_CAX_ISR1_PRI(EE_CAX_847_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_848_ISR) && (EE_CAX_MAX_ISR_ID >= 848) && (EE_CAX_MAX_ARCH_ISR_ID >= 848))
#if (EE_CAX_848_ISR_CAT == 2)
 { 848, EE_CAX_ISR2_PRI(EE_CAX_848_ISR_PRI) },
#else
 { 848, EE_CAX_ISR1_PRI(EE_CAX_848_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_849_ISR) && (EE_CAX_MAX_ISR_ID >= 849) && (EE_CAX_MAX_ARCH_ISR_ID >= 849))
#if (EE_CAX_849_ISR_CAT == 2)
 { 849, EE_CAX_ISR2_PRI(EE_CAX_849_ISR_PRI) },
#else
 { 849, EE_CAX_ISR1_PRI(EE_CAX_849_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_850_ISR) && (EE_CAX_MAX_ISR_ID >= 850) && (EE_CAX_MAX_ARCH_ISR_ID >= 850))
#if (EE_CAX_850_ISR_CAT == 2)
 { 850, EE_CAX_ISR2_PRI(EE_CAX_850_ISR_PRI) },
#else
 { 850, EE_CAX_ISR1_PRI(EE_CAX_850_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_851_ISR) && (EE_CAX_MAX_ISR_ID >= 851) && (EE_CAX_MAX_ARCH_ISR_ID >= 851))
#if (EE_CAX_851_ISR_CAT == 2)
 { 851, EE_CAX_ISR2_PRI(EE_CAX_851_ISR_PRI) },
#else
 { 851, EE_CAX_ISR1_PRI(EE_CAX_851_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_852_ISR) && (EE_CAX_MAX_ISR_ID >= 852) && (EE_CAX_MAX_ARCH_ISR_ID >= 852))
#if (EE_CAX_852_ISR_CAT == 2)
 { 852, EE_CAX_ISR2_PRI(EE_CAX_852_ISR_PRI) },
#else
 { 852, EE_CAX_ISR1_PRI(EE_CAX_852_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_853_ISR) && (EE_CAX_MAX_ISR_ID >= 853) && (EE_CAX_MAX_ARCH_ISR_ID >= 853))
#if (EE_CAX_853_ISR_CAT == 2)
 { 853, EE_CAX_ISR2_PRI(EE_CAX_853_ISR_PRI) },
#else
 { 853, EE_CAX_ISR1_PRI(EE_CAX_853_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_854_ISR) && (EE_CAX_MAX_ISR_ID >= 854) && (EE_CAX_MAX_ARCH_ISR_ID >= 854))
#if (EE_CAX_854_ISR_CAT == 2)
 { 854, EE_CAX_ISR2_PRI(EE_CAX_854_ISR_PRI) },
#else
 { 854, EE_CAX_ISR1_PRI(EE_CAX_854_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_855_ISR) && (EE_CAX_MAX_ISR_ID >= 855) && (EE_CAX_MAX_ARCH_ISR_ID >= 855))
#if (EE_CAX_855_ISR_CAT == 2)
 { 855, EE_CAX_ISR2_PRI(EE_CAX_855_ISR_PRI) },
#else
 { 855, EE_CAX_ISR1_PRI(EE_CAX_855_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_856_ISR) && (EE_CAX_MAX_ISR_ID >= 856) && (EE_CAX_MAX_ARCH_ISR_ID >= 856))
#if (EE_CAX_856_ISR_CAT == 2)
 { 856, EE_CAX_ISR2_PRI(EE_CAX_856_ISR_PRI) },
#else
 { 856, EE_CAX_ISR1_PRI(EE_CAX_856_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_857_ISR) && (EE_CAX_MAX_ISR_ID >= 857) && (EE_CAX_MAX_ARCH_ISR_ID >= 857))
#if (EE_CAX_857_ISR_CAT == 2)
 { 857, EE_CAX_ISR2_PRI(EE_CAX_857_ISR_PRI) },
#else
 { 857, EE_CAX_ISR1_PRI(EE_CAX_857_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_858_ISR) && (EE_CAX_MAX_ISR_ID >= 858) && (EE_CAX_MAX_ARCH_ISR_ID >= 858))
#if (EE_CAX_858_ISR_CAT == 2)
 { 858, EE_CAX_ISR2_PRI(EE_CAX_858_ISR_PRI) },
#else
 { 858, EE_CAX_ISR1_PRI(EE_CAX_858_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_859_ISR) && (EE_CAX_MAX_ISR_ID >= 859) && (EE_CAX_MAX_ARCH_ISR_ID >= 859))
#if (EE_CAX_859_ISR_CAT == 2)
 { 859, EE_CAX_ISR2_PRI(EE_CAX_859_ISR_PRI) },
#else
 { 859, EE_CAX_ISR1_PRI(EE_CAX_859_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_860_ISR) && (EE_CAX_MAX_ISR_ID >= 860) && (EE_CAX_MAX_ARCH_ISR_ID >= 860))
#if (EE_CAX_860_ISR_CAT == 2)
 { 860, EE_CAX_ISR2_PRI(EE_CAX_860_ISR_PRI) },
#else
 { 860, EE_CAX_ISR1_PRI(EE_CAX_860_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_861_ISR) && (EE_CAX_MAX_ISR_ID >= 861) && (EE_CAX_MAX_ARCH_ISR_ID >= 861))
#if (EE_CAX_861_ISR_CAT == 2)
 { 861, EE_CAX_ISR2_PRI(EE_CAX_861_ISR_PRI) },
#else
 { 861, EE_CAX_ISR1_PRI(EE_CAX_861_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_862_ISR) && (EE_CAX_MAX_ISR_ID >= 862) && (EE_CAX_MAX_ARCH_ISR_ID >= 862))
#if (EE_CAX_862_ISR_CAT == 2)
 { 862, EE_CAX_ISR2_PRI(EE_CAX_862_ISR_PRI) },
#else
 { 862, EE_CAX_ISR1_PRI(EE_CAX_862_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_863_ISR) && (EE_CAX_MAX_ISR_ID >= 863) && (EE_CAX_MAX_ARCH_ISR_ID >= 863))
#if (EE_CAX_863_ISR_CAT == 2)
 { 863, EE_CAX_ISR2_PRI(EE_CAX_863_ISR_PRI) },
#else
 { 863, EE_CAX_ISR1_PRI(EE_CAX_863_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_864_ISR) && (EE_CAX_MAX_ISR_ID >= 864) && (EE_CAX_MAX_ARCH_ISR_ID >= 864))
#if (EE_CAX_864_ISR_CAT == 2)
 { 864, EE_CAX_ISR2_PRI(EE_CAX_864_ISR_PRI) },
#else
 { 864, EE_CAX_ISR1_PRI(EE_CAX_864_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_865_ISR) && (EE_CAX_MAX_ISR_ID >= 865) && (EE_CAX_MAX_ARCH_ISR_ID >= 865))
#if (EE_CAX_865_ISR_CAT == 2)
 { 865, EE_CAX_ISR2_PRI(EE_CAX_865_ISR_PRI) },
#else
 { 865, EE_CAX_ISR1_PRI(EE_CAX_865_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_866_ISR) && (EE_CAX_MAX_ISR_ID >= 866) && (EE_CAX_MAX_ARCH_ISR_ID >= 866))
#if (EE_CAX_866_ISR_CAT == 2)
 { 866, EE_CAX_ISR2_PRI(EE_CAX_866_ISR_PRI) },
#else
 { 866, EE_CAX_ISR1_PRI(EE_CAX_866_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_867_ISR) && (EE_CAX_MAX_ISR_ID >= 867) && (EE_CAX_MAX_ARCH_ISR_ID >= 867))
#if (EE_CAX_867_ISR_CAT == 2)
 { 867, EE_CAX_ISR2_PRI(EE_CAX_867_ISR_PRI) },
#else
 { 867, EE_CAX_ISR1_PRI(EE_CAX_867_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_868_ISR) && (EE_CAX_MAX_ISR_ID >= 868) && (EE_CAX_MAX_ARCH_ISR_ID >= 868))
#if (EE_CAX_868_ISR_CAT == 2)
 { 868, EE_CAX_ISR2_PRI(EE_CAX_868_ISR_PRI) },
#else
 { 868, EE_CAX_ISR1_PRI(EE_CAX_868_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_869_ISR) && (EE_CAX_MAX_ISR_ID >= 869) && (EE_CAX_MAX_ARCH_ISR_ID >= 869))
#if (EE_CAX_869_ISR_CAT == 2)
 { 869, EE_CAX_ISR2_PRI(EE_CAX_869_ISR_PRI) },
#else
 { 869, EE_CAX_ISR1_PRI(EE_CAX_869_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_870_ISR) && (EE_CAX_MAX_ISR_ID >= 870) && (EE_CAX_MAX_ARCH_ISR_ID >= 870))
#if (EE_CAX_870_ISR_CAT == 2)
 { 870, EE_CAX_ISR2_PRI(EE_CAX_870_ISR_PRI) },
#else
 { 870, EE_CAX_ISR1_PRI(EE_CAX_870_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_871_ISR) && (EE_CAX_MAX_ISR_ID >= 871) && (EE_CAX_MAX_ARCH_ISR_ID >= 871))
#if (EE_CAX_871_ISR_CAT == 2)
 { 871, EE_CAX_ISR2_PRI(EE_CAX_871_ISR_PRI) },
#else
 { 871, EE_CAX_ISR1_PRI(EE_CAX_871_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_872_ISR) && (EE_CAX_MAX_ISR_ID >= 872) && (EE_CAX_MAX_ARCH_ISR_ID >= 872))
#if (EE_CAX_872_ISR_CAT == 2)
 { 872, EE_CAX_ISR2_PRI(EE_CAX_872_ISR_PRI) },
#else
 { 872, EE_CAX_ISR1_PRI(EE_CAX_872_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_873_ISR) && (EE_CAX_MAX_ISR_ID >= 873) && (EE_CAX_MAX_ARCH_ISR_ID >= 873))
#if (EE_CAX_873_ISR_CAT == 2)
 { 873, EE_CAX_ISR2_PRI(EE_CAX_873_ISR_PRI) },
#else
 { 873, EE_CAX_ISR1_PRI(EE_CAX_873_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_874_ISR) && (EE_CAX_MAX_ISR_ID >= 874) && (EE_CAX_MAX_ARCH_ISR_ID >= 874))
#if (EE_CAX_874_ISR_CAT == 2)
 { 874, EE_CAX_ISR2_PRI(EE_CAX_874_ISR_PRI) },
#else
 { 874, EE_CAX_ISR1_PRI(EE_CAX_874_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_875_ISR) && (EE_CAX_MAX_ISR_ID >= 875) && (EE_CAX_MAX_ARCH_ISR_ID >= 875))
#if (EE_CAX_875_ISR_CAT == 2)
 { 875, EE_CAX_ISR2_PRI(EE_CAX_875_ISR_PRI) },
#else
 { 875, EE_CAX_ISR1_PRI(EE_CAX_875_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_876_ISR) && (EE_CAX_MAX_ISR_ID >= 876) && (EE_CAX_MAX_ARCH_ISR_ID >= 876))
#if (EE_CAX_876_ISR_CAT == 2)
 { 876, EE_CAX_ISR2_PRI(EE_CAX_876_ISR_PRI) },
#else
 { 876, EE_CAX_ISR1_PRI(EE_CAX_876_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_877_ISR) && (EE_CAX_MAX_ISR_ID >= 877) && (EE_CAX_MAX_ARCH_ISR_ID >= 877))
#if (EE_CAX_877_ISR_CAT == 2)
 { 877, EE_CAX_ISR2_PRI(EE_CAX_877_ISR_PRI) },
#else
 { 877, EE_CAX_ISR1_PRI(EE_CAX_877_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_878_ISR) && (EE_CAX_MAX_ISR_ID >= 878) && (EE_CAX_MAX_ARCH_ISR_ID >= 878))
#if (EE_CAX_878_ISR_CAT == 2)
 { 878, EE_CAX_ISR2_PRI(EE_CAX_878_ISR_PRI) },
#else
 { 878, EE_CAX_ISR1_PRI(EE_CAX_878_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_879_ISR) && (EE_CAX_MAX_ISR_ID >= 879) && (EE_CAX_MAX_ARCH_ISR_ID >= 879))
#if (EE_CAX_879_ISR_CAT == 2)
 { 879, EE_CAX_ISR2_PRI(EE_CAX_879_ISR_PRI) },
#else
 { 879, EE_CAX_ISR1_PRI(EE_CAX_879_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_880_ISR) && (EE_CAX_MAX_ISR_ID >= 880) && (EE_CAX_MAX_ARCH_ISR_ID >= 880))
#if (EE_CAX_880_ISR_CAT == 2)
 { 880, EE_CAX_ISR2_PRI(EE_CAX_880_ISR_PRI) },
#else
 { 880, EE_CAX_ISR1_PRI(EE_CAX_880_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_881_ISR) && (EE_CAX_MAX_ISR_ID >= 881) && (EE_CAX_MAX_ARCH_ISR_ID >= 881))
#if (EE_CAX_881_ISR_CAT == 2)
 { 881, EE_CAX_ISR2_PRI(EE_CAX_881_ISR_PRI) },
#else
 { 881, EE_CAX_ISR1_PRI(EE_CAX_881_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_882_ISR) && (EE_CAX_MAX_ISR_ID >= 882) && (EE_CAX_MAX_ARCH_ISR_ID >= 882))
#if (EE_CAX_882_ISR_CAT == 2)
 { 882, EE_CAX_ISR2_PRI(EE_CAX_882_ISR_PRI) },
#else
 { 882, EE_CAX_ISR1_PRI(EE_CAX_882_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_883_ISR) && (EE_CAX_MAX_ISR_ID >= 883) && (EE_CAX_MAX_ARCH_ISR_ID >= 883))
#if (EE_CAX_883_ISR_CAT == 2)
 { 883, EE_CAX_ISR2_PRI(EE_CAX_883_ISR_PRI) },
#else
 { 883, EE_CAX_ISR1_PRI(EE_CAX_883_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_884_ISR) && (EE_CAX_MAX_ISR_ID >= 884) && (EE_CAX_MAX_ARCH_ISR_ID >= 884))
#if (EE_CAX_884_ISR_CAT == 2)
 { 884, EE_CAX_ISR2_PRI(EE_CAX_884_ISR_PRI) },
#else
 { 884, EE_CAX_ISR1_PRI(EE_CAX_884_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_885_ISR) && (EE_CAX_MAX_ISR_ID >= 885) && (EE_CAX_MAX_ARCH_ISR_ID >= 885))
#if (EE_CAX_885_ISR_CAT == 2)
 { 885, EE_CAX_ISR2_PRI(EE_CAX_885_ISR_PRI) },
#else
 { 885, EE_CAX_ISR1_PRI(EE_CAX_885_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_886_ISR) && (EE_CAX_MAX_ISR_ID >= 886) && (EE_CAX_MAX_ARCH_ISR_ID >= 886))
#if (EE_CAX_886_ISR_CAT == 2)
 { 886, EE_CAX_ISR2_PRI(EE_CAX_886_ISR_PRI) },
#else
 { 886, EE_CAX_ISR1_PRI(EE_CAX_886_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_887_ISR) && (EE_CAX_MAX_ISR_ID >= 887) && (EE_CAX_MAX_ARCH_ISR_ID >= 887))
#if (EE_CAX_887_ISR_CAT == 2)
 { 887, EE_CAX_ISR2_PRI(EE_CAX_887_ISR_PRI) },
#else
 { 887, EE_CAX_ISR1_PRI(EE_CAX_887_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_888_ISR) && (EE_CAX_MAX_ISR_ID >= 888) && (EE_CAX_MAX_ARCH_ISR_ID >= 888))
#if (EE_CAX_888_ISR_CAT == 2)
 { 888, EE_CAX_ISR2_PRI(EE_CAX_888_ISR_PRI) },
#else
 { 888, EE_CAX_ISR1_PRI(EE_CAX_888_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_889_ISR) && (EE_CAX_MAX_ISR_ID >= 889) && (EE_CAX_MAX_ARCH_ISR_ID >= 889))
#if (EE_CAX_889_ISR_CAT == 2)
 { 889, EE_CAX_ISR2_PRI(EE_CAX_889_ISR_PRI) },
#else
 { 889, EE_CAX_ISR1_PRI(EE_CAX_889_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_890_ISR) && (EE_CAX_MAX_ISR_ID >= 890) && (EE_CAX_MAX_ARCH_ISR_ID >= 890))
#if (EE_CAX_890_ISR_CAT == 2)
 { 890, EE_CAX_ISR2_PRI(EE_CAX_890_ISR_PRI) },
#else
 { 890, EE_CAX_ISR1_PRI(EE_CAX_890_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_891_ISR) && (EE_CAX_MAX_ISR_ID >= 891) && (EE_CAX_MAX_ARCH_ISR_ID >= 891))
#if (EE_CAX_891_ISR_CAT == 2)
 { 891, EE_CAX_ISR2_PRI(EE_CAX_891_ISR_PRI) },
#else
 { 891, EE_CAX_ISR1_PRI(EE_CAX_891_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_892_ISR) && (EE_CAX_MAX_ISR_ID >= 892) && (EE_CAX_MAX_ARCH_ISR_ID >= 892))
#if (EE_CAX_892_ISR_CAT == 2)
 { 892, EE_CAX_ISR2_PRI(EE_CAX_892_ISR_PRI) },
#else
 { 892, EE_CAX_ISR1_PRI(EE_CAX_892_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_893_ISR) && (EE_CAX_MAX_ISR_ID >= 893) && (EE_CAX_MAX_ARCH_ISR_ID >= 893))
#if (EE_CAX_893_ISR_CAT == 2)
 { 893, EE_CAX_ISR2_PRI(EE_CAX_893_ISR_PRI) },
#else
 { 893, EE_CAX_ISR1_PRI(EE_CAX_893_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_894_ISR) && (EE_CAX_MAX_ISR_ID >= 894) && (EE_CAX_MAX_ARCH_ISR_ID >= 894))
#if (EE_CAX_894_ISR_CAT == 2)
 { 894, EE_CAX_ISR2_PRI(EE_CAX_894_ISR_PRI) },
#else
 { 894, EE_CAX_ISR1_PRI(EE_CAX_894_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_895_ISR) && (EE_CAX_MAX_ISR_ID >= 895) && (EE_CAX_MAX_ARCH_ISR_ID >= 895))
#if (EE_CAX_895_ISR_CAT == 2)
 { 895, EE_CAX_ISR2_PRI(EE_CAX_895_ISR_PRI) },
#else
 { 895, EE_CAX_ISR1_PRI(EE_CAX_895_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_896_ISR) && (EE_CAX_MAX_ISR_ID >= 896) && (EE_CAX_MAX_ARCH_ISR_ID >= 896))
#if (EE_CAX_896_ISR_CAT == 2)
 { 896, EE_CAX_ISR2_PRI(EE_CAX_896_ISR_PRI) },
#else
 { 896, EE_CAX_ISR1_PRI(EE_CAX_896_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_897_ISR) && (EE_CAX_MAX_ISR_ID >= 897) && (EE_CAX_MAX_ARCH_ISR_ID >= 897))
#if (EE_CAX_897_ISR_CAT == 2)
 { 897, EE_CAX_ISR2_PRI(EE_CAX_897_ISR_PRI) },
#else
 { 897, EE_CAX_ISR1_PRI(EE_CAX_897_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_898_ISR) && (EE_CAX_MAX_ISR_ID >= 898) && (EE_CAX_MAX_ARCH_ISR_ID >= 898))
#if (EE_CAX_898_ISR_CAT == 2)
 { 898, EE_CAX_ISR2_PRI(EE_CAX_898_ISR_PRI) },
#else
 { 898, EE_CAX_ISR1_PRI(EE_CAX_898_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_899_ISR) && (EE_CAX_MAX_ISR_ID >= 899) && (EE_CAX_MAX_ARCH_ISR_ID >= 899))
#if (EE_CAX_899_ISR_CAT == 2)
 { 899, EE_CAX_ISR2_PRI(EE_CAX_899_ISR_PRI) },
#else
 { 899, EE_CAX_ISR1_PRI(EE_CAX_899_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_900_ISR) && (EE_CAX_MAX_ISR_ID >= 900) && (EE_CAX_MAX_ARCH_ISR_ID >= 900))
#if (EE_CAX_900_ISR_CAT == 2)
 { 900, EE_CAX_ISR2_PRI(EE_CAX_900_ISR_PRI) },
#else
 { 900, EE_CAX_ISR1_PRI(EE_CAX_900_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_901_ISR) && (EE_CAX_MAX_ISR_ID >= 901) && (EE_CAX_MAX_ARCH_ISR_ID >= 901))
#if (EE_CAX_901_ISR_CAT == 2)
 { 901, EE_CAX_ISR2_PRI(EE_CAX_901_ISR_PRI) },
#else
 { 901, EE_CAX_ISR1_PRI(EE_CAX_901_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_902_ISR) && (EE_CAX_MAX_ISR_ID >= 902) && (EE_CAX_MAX_ARCH_ISR_ID >= 902))
#if (EE_CAX_902_ISR_CAT == 2)
 { 902, EE_CAX_ISR2_PRI(EE_CAX_902_ISR_PRI) },
#else
 { 902, EE_CAX_ISR1_PRI(EE_CAX_902_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_903_ISR) && (EE_CAX_MAX_ISR_ID >= 903) && (EE_CAX_MAX_ARCH_ISR_ID >= 903))
#if (EE_CAX_903_ISR_CAT == 2)
 { 903, EE_CAX_ISR2_PRI(EE_CAX_903_ISR_PRI) },
#else
 { 903, EE_CAX_ISR1_PRI(EE_CAX_903_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_904_ISR) && (EE_CAX_MAX_ISR_ID >= 904) && (EE_CAX_MAX_ARCH_ISR_ID >= 904))
#if (EE_CAX_904_ISR_CAT == 2)
 { 904, EE_CAX_ISR2_PRI(EE_CAX_904_ISR_PRI) },
#else
 { 904, EE_CAX_ISR1_PRI(EE_CAX_904_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_905_ISR) && (EE_CAX_MAX_ISR_ID >= 905) && (EE_CAX_MAX_ARCH_ISR_ID >= 905))
#if (EE_CAX_905_ISR_CAT == 2)
 { 905, EE_CAX_ISR2_PRI(EE_CAX_905_ISR_PRI) },
#else
 { 905, EE_CAX_ISR1_PRI(EE_CAX_905_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_906_ISR) && (EE_CAX_MAX_ISR_ID >= 906) && (EE_CAX_MAX_ARCH_ISR_ID >= 906))
#if (EE_CAX_906_ISR_CAT == 2)
 { 906, EE_CAX_ISR2_PRI(EE_CAX_906_ISR_PRI) },
#else
 { 906, EE_CAX_ISR1_PRI(EE_CAX_906_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_907_ISR) && (EE_CAX_MAX_ISR_ID >= 907) && (EE_CAX_MAX_ARCH_ISR_ID >= 907))
#if (EE_CAX_907_ISR_CAT == 2)
 { 907, EE_CAX_ISR2_PRI(EE_CAX_907_ISR_PRI) },
#else
 { 907, EE_CAX_ISR1_PRI(EE_CAX_907_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_908_ISR) && (EE_CAX_MAX_ISR_ID >= 908) && (EE_CAX_MAX_ARCH_ISR_ID >= 908))
#if (EE_CAX_908_ISR_CAT == 2)
 { 908, EE_CAX_ISR2_PRI(EE_CAX_908_ISR_PRI) },
#else
 { 908, EE_CAX_ISR1_PRI(EE_CAX_908_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_909_ISR) && (EE_CAX_MAX_ISR_ID >= 909) && (EE_CAX_MAX_ARCH_ISR_ID >= 909))
#if (EE_CAX_909_ISR_CAT == 2)
 { 909, EE_CAX_ISR2_PRI(EE_CAX_909_ISR_PRI) },
#else
 { 909, EE_CAX_ISR1_PRI(EE_CAX_909_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_910_ISR) && (EE_CAX_MAX_ISR_ID >= 910) && (EE_CAX_MAX_ARCH_ISR_ID >= 910))
#if (EE_CAX_910_ISR_CAT == 2)
 { 910, EE_CAX_ISR2_PRI(EE_CAX_910_ISR_PRI) },
#else
 { 910, EE_CAX_ISR1_PRI(EE_CAX_910_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_911_ISR) && (EE_CAX_MAX_ISR_ID >= 911) && (EE_CAX_MAX_ARCH_ISR_ID >= 911))
#if (EE_CAX_911_ISR_CAT == 2)
 { 911, EE_CAX_ISR2_PRI(EE_CAX_911_ISR_PRI) },
#else
 { 911, EE_CAX_ISR1_PRI(EE_CAX_911_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_912_ISR) && (EE_CAX_MAX_ISR_ID >= 912) && (EE_CAX_MAX_ARCH_ISR_ID >= 912))
#if (EE_CAX_912_ISR_CAT == 2)
 { 912, EE_CAX_ISR2_PRI(EE_CAX_912_ISR_PRI) },
#else
 { 912, EE_CAX_ISR1_PRI(EE_CAX_912_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_913_ISR) && (EE_CAX_MAX_ISR_ID >= 913) && (EE_CAX_MAX_ARCH_ISR_ID >= 913))
#if (EE_CAX_913_ISR_CAT == 2)
 { 913, EE_CAX_ISR2_PRI(EE_CAX_913_ISR_PRI) },
#else
 { 913, EE_CAX_ISR1_PRI(EE_CAX_913_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_914_ISR) && (EE_CAX_MAX_ISR_ID >= 914) && (EE_CAX_MAX_ARCH_ISR_ID >= 914))
#if (EE_CAX_914_ISR_CAT == 2)
 { 914, EE_CAX_ISR2_PRI(EE_CAX_914_ISR_PRI) },
#else
 { 914, EE_CAX_ISR1_PRI(EE_CAX_914_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_915_ISR) && (EE_CAX_MAX_ISR_ID >= 915) && (EE_CAX_MAX_ARCH_ISR_ID >= 915))
#if (EE_CAX_915_ISR_CAT == 2)
 { 915, EE_CAX_ISR2_PRI(EE_CAX_915_ISR_PRI) },
#else
 { 915, EE_CAX_ISR1_PRI(EE_CAX_915_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_916_ISR) && (EE_CAX_MAX_ISR_ID >= 916) && (EE_CAX_MAX_ARCH_ISR_ID >= 916))
#if (EE_CAX_916_ISR_CAT == 2)
 { 916, EE_CAX_ISR2_PRI(EE_CAX_916_ISR_PRI) },
#else
 { 916, EE_CAX_ISR1_PRI(EE_CAX_916_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_917_ISR) && (EE_CAX_MAX_ISR_ID >= 917) && (EE_CAX_MAX_ARCH_ISR_ID >= 917))
#if (EE_CAX_917_ISR_CAT == 2)
 { 917, EE_CAX_ISR2_PRI(EE_CAX_917_ISR_PRI) },
#else
 { 917, EE_CAX_ISR1_PRI(EE_CAX_917_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_918_ISR) && (EE_CAX_MAX_ISR_ID >= 918) && (EE_CAX_MAX_ARCH_ISR_ID >= 918))
#if (EE_CAX_918_ISR_CAT == 2)
 { 918, EE_CAX_ISR2_PRI(EE_CAX_918_ISR_PRI) },
#else
 { 918, EE_CAX_ISR1_PRI(EE_CAX_918_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_919_ISR) && (EE_CAX_MAX_ISR_ID >= 919) && (EE_CAX_MAX_ARCH_ISR_ID >= 919))
#if (EE_CAX_919_ISR_CAT == 2)
 { 919, EE_CAX_ISR2_PRI(EE_CAX_919_ISR_PRI) },
#else
 { 919, EE_CAX_ISR1_PRI(EE_CAX_919_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_920_ISR) && (EE_CAX_MAX_ISR_ID >= 920) && (EE_CAX_MAX_ARCH_ISR_ID >= 920))
#if (EE_CAX_920_ISR_CAT == 2)
 { 920, EE_CAX_ISR2_PRI(EE_CAX_920_ISR_PRI) },
#else
 { 920, EE_CAX_ISR1_PRI(EE_CAX_920_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_921_ISR) && (EE_CAX_MAX_ISR_ID >= 921) && (EE_CAX_MAX_ARCH_ISR_ID >= 921))
#if (EE_CAX_921_ISR_CAT == 2)
 { 921, EE_CAX_ISR2_PRI(EE_CAX_921_ISR_PRI) },
#else
 { 921, EE_CAX_ISR1_PRI(EE_CAX_921_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_922_ISR) && (EE_CAX_MAX_ISR_ID >= 922) && (EE_CAX_MAX_ARCH_ISR_ID >= 922))
#if (EE_CAX_922_ISR_CAT == 2)
 { 922, EE_CAX_ISR2_PRI(EE_CAX_922_ISR_PRI) },
#else
 { 922, EE_CAX_ISR1_PRI(EE_CAX_922_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_923_ISR) && (EE_CAX_MAX_ISR_ID >= 923) && (EE_CAX_MAX_ARCH_ISR_ID >= 923))
#if (EE_CAX_923_ISR_CAT == 2)
 { 923, EE_CAX_ISR2_PRI(EE_CAX_923_ISR_PRI) },
#else
 { 923, EE_CAX_ISR1_PRI(EE_CAX_923_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_924_ISR) && (EE_CAX_MAX_ISR_ID >= 924) && (EE_CAX_MAX_ARCH_ISR_ID >= 924))
#if (EE_CAX_924_ISR_CAT == 2)
 { 924, EE_CAX_ISR2_PRI(EE_CAX_924_ISR_PRI) },
#else
 { 924, EE_CAX_ISR1_PRI(EE_CAX_924_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_925_ISR) && (EE_CAX_MAX_ISR_ID >= 925) && (EE_CAX_MAX_ARCH_ISR_ID >= 925))
#if (EE_CAX_925_ISR_CAT == 2)
 { 925, EE_CAX_ISR2_PRI(EE_CAX_925_ISR_PRI) },
#else
 { 925, EE_CAX_ISR1_PRI(EE_CAX_925_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_926_ISR) && (EE_CAX_MAX_ISR_ID >= 926) && (EE_CAX_MAX_ARCH_ISR_ID >= 926))
#if (EE_CAX_926_ISR_CAT == 2)
 { 926, EE_CAX_ISR2_PRI(EE_CAX_926_ISR_PRI) },
#else
 { 926, EE_CAX_ISR1_PRI(EE_CAX_926_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_927_ISR) && (EE_CAX_MAX_ISR_ID >= 927) && (EE_CAX_MAX_ARCH_ISR_ID >= 927))
#if (EE_CAX_927_ISR_CAT == 2)
 { 927, EE_CAX_ISR2_PRI(EE_CAX_927_ISR_PRI) },
#else
 { 927, EE_CAX_ISR1_PRI(EE_CAX_927_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_928_ISR) && (EE_CAX_MAX_ISR_ID >= 928) && (EE_CAX_MAX_ARCH_ISR_ID >= 928))
#if (EE_CAX_928_ISR_CAT == 2)
 { 928, EE_CAX_ISR2_PRI(EE_CAX_928_ISR_PRI) },
#else
 { 928, EE_CAX_ISR1_PRI(EE_CAX_928_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_929_ISR) && (EE_CAX_MAX_ISR_ID >= 929) && (EE_CAX_MAX_ARCH_ISR_ID >= 929))
#if (EE_CAX_929_ISR_CAT == 2)
 { 929, EE_CAX_ISR2_PRI(EE_CAX_929_ISR_PRI) },
#else
 { 929, EE_CAX_ISR1_PRI(EE_CAX_929_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_930_ISR) && (EE_CAX_MAX_ISR_ID >= 930) && (EE_CAX_MAX_ARCH_ISR_ID >= 930))
#if (EE_CAX_930_ISR_CAT == 2)
 { 930, EE_CAX_ISR2_PRI(EE_CAX_930_ISR_PRI) },
#else
 { 930, EE_CAX_ISR1_PRI(EE_CAX_930_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_931_ISR) && (EE_CAX_MAX_ISR_ID >= 931) && (EE_CAX_MAX_ARCH_ISR_ID >= 931))
#if (EE_CAX_931_ISR_CAT == 2)
 { 931, EE_CAX_ISR2_PRI(EE_CAX_931_ISR_PRI) },
#else
 { 931, EE_CAX_ISR1_PRI(EE_CAX_931_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_932_ISR) && (EE_CAX_MAX_ISR_ID >= 932) && (EE_CAX_MAX_ARCH_ISR_ID >= 932))
#if (EE_CAX_932_ISR_CAT == 2)
 { 932, EE_CAX_ISR2_PRI(EE_CAX_932_ISR_PRI) },
#else
 { 932, EE_CAX_ISR1_PRI(EE_CAX_932_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_933_ISR) && (EE_CAX_MAX_ISR_ID >= 933) && (EE_CAX_MAX_ARCH_ISR_ID >= 933))
#if (EE_CAX_933_ISR_CAT == 2)
 { 933, EE_CAX_ISR2_PRI(EE_CAX_933_ISR_PRI) },
#else
 { 933, EE_CAX_ISR1_PRI(EE_CAX_933_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_934_ISR) && (EE_CAX_MAX_ISR_ID >= 934) && (EE_CAX_MAX_ARCH_ISR_ID >= 934))
#if (EE_CAX_934_ISR_CAT == 2)
 { 934, EE_CAX_ISR2_PRI(EE_CAX_934_ISR_PRI) },
#else
 { 934, EE_CAX_ISR1_PRI(EE_CAX_934_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_935_ISR) && (EE_CAX_MAX_ISR_ID >= 935) && (EE_CAX_MAX_ARCH_ISR_ID >= 935))
#if (EE_CAX_935_ISR_CAT == 2)
 { 935, EE_CAX_ISR2_PRI(EE_CAX_935_ISR_PRI) },
#else
 { 935, EE_CAX_ISR1_PRI(EE_CAX_935_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_936_ISR) && (EE_CAX_MAX_ISR_ID >= 936) && (EE_CAX_MAX_ARCH_ISR_ID >= 936))
#if (EE_CAX_936_ISR_CAT == 2)
 { 936, EE_CAX_ISR2_PRI(EE_CAX_936_ISR_PRI) },
#else
 { 936, EE_CAX_ISR1_PRI(EE_CAX_936_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_937_ISR) && (EE_CAX_MAX_ISR_ID >= 937) && (EE_CAX_MAX_ARCH_ISR_ID >= 937))
#if (EE_CAX_937_ISR_CAT == 2)
 { 937, EE_CAX_ISR2_PRI(EE_CAX_937_ISR_PRI) },
#else
 { 937, EE_CAX_ISR1_PRI(EE_CAX_937_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_938_ISR) && (EE_CAX_MAX_ISR_ID >= 938) && (EE_CAX_MAX_ARCH_ISR_ID >= 938))
#if (EE_CAX_938_ISR_CAT == 2)
 { 938, EE_CAX_ISR2_PRI(EE_CAX_938_ISR_PRI) },
#else
 { 938, EE_CAX_ISR1_PRI(EE_CAX_938_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_939_ISR) && (EE_CAX_MAX_ISR_ID >= 939) && (EE_CAX_MAX_ARCH_ISR_ID >= 939))
#if (EE_CAX_939_ISR_CAT == 2)
 { 939, EE_CAX_ISR2_PRI(EE_CAX_939_ISR_PRI) },
#else
 { 939, EE_CAX_ISR1_PRI(EE_CAX_939_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_940_ISR) && (EE_CAX_MAX_ISR_ID >= 940) && (EE_CAX_MAX_ARCH_ISR_ID >= 940))
#if (EE_CAX_940_ISR_CAT == 2)
 { 940, EE_CAX_ISR2_PRI(EE_CAX_940_ISR_PRI) },
#else
 { 940, EE_CAX_ISR1_PRI(EE_CAX_940_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_941_ISR) && (EE_CAX_MAX_ISR_ID >= 941) && (EE_CAX_MAX_ARCH_ISR_ID >= 941))
#if (EE_CAX_941_ISR_CAT == 2)
 { 941, EE_CAX_ISR2_PRI(EE_CAX_941_ISR_PRI) },
#else
 { 941, EE_CAX_ISR1_PRI(EE_CAX_941_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_942_ISR) && (EE_CAX_MAX_ISR_ID >= 942) && (EE_CAX_MAX_ARCH_ISR_ID >= 942))
#if (EE_CAX_942_ISR_CAT == 2)
 { 942, EE_CAX_ISR2_PRI(EE_CAX_942_ISR_PRI) },
#else
 { 942, EE_CAX_ISR1_PRI(EE_CAX_942_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_943_ISR) && (EE_CAX_MAX_ISR_ID >= 943) && (EE_CAX_MAX_ARCH_ISR_ID >= 943))
#if (EE_CAX_943_ISR_CAT == 2)
 { 943, EE_CAX_ISR2_PRI(EE_CAX_943_ISR_PRI) },
#else
 { 943, EE_CAX_ISR1_PRI(EE_CAX_943_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_944_ISR) && (EE_CAX_MAX_ISR_ID >= 944) && (EE_CAX_MAX_ARCH_ISR_ID >= 944))
#if (EE_CAX_944_ISR_CAT == 2)
 { 944, EE_CAX_ISR2_PRI(EE_CAX_944_ISR_PRI) },
#else
 { 944, EE_CAX_ISR1_PRI(EE_CAX_944_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_945_ISR) && (EE_CAX_MAX_ISR_ID >= 945) && (EE_CAX_MAX_ARCH_ISR_ID >= 945))
#if (EE_CAX_945_ISR_CAT == 2)
 { 945, EE_CAX_ISR2_PRI(EE_CAX_945_ISR_PRI) },
#else
 { 945, EE_CAX_ISR1_PRI(EE_CAX_945_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_946_ISR) && (EE_CAX_MAX_ISR_ID >= 946) && (EE_CAX_MAX_ARCH_ISR_ID >= 946))
#if (EE_CAX_946_ISR_CAT == 2)
 { 946, EE_CAX_ISR2_PRI(EE_CAX_946_ISR_PRI) },
#else
 { 946, EE_CAX_ISR1_PRI(EE_CAX_946_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_947_ISR) && (EE_CAX_MAX_ISR_ID >= 947) && (EE_CAX_MAX_ARCH_ISR_ID >= 947))
#if (EE_CAX_947_ISR_CAT == 2)
 { 947, EE_CAX_ISR2_PRI(EE_CAX_947_ISR_PRI) },
#else
 { 947, EE_CAX_ISR1_PRI(EE_CAX_947_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_948_ISR) && (EE_CAX_MAX_ISR_ID >= 948) && (EE_CAX_MAX_ARCH_ISR_ID >= 948))
#if (EE_CAX_948_ISR_CAT == 2)
 { 948, EE_CAX_ISR2_PRI(EE_CAX_948_ISR_PRI) },
#else
 { 948, EE_CAX_ISR1_PRI(EE_CAX_948_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_949_ISR) && (EE_CAX_MAX_ISR_ID >= 949) && (EE_CAX_MAX_ARCH_ISR_ID >= 949))
#if (EE_CAX_949_ISR_CAT == 2)
 { 949, EE_CAX_ISR2_PRI(EE_CAX_949_ISR_PRI) },
#else
 { 949, EE_CAX_ISR1_PRI(EE_CAX_949_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_950_ISR) && (EE_CAX_MAX_ISR_ID >= 950) && (EE_CAX_MAX_ARCH_ISR_ID >= 950))
#if (EE_CAX_950_ISR_CAT == 2)
 { 950, EE_CAX_ISR2_PRI(EE_CAX_950_ISR_PRI) },
#else
 { 950, EE_CAX_ISR1_PRI(EE_CAX_950_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_951_ISR) && (EE_CAX_MAX_ISR_ID >= 951) && (EE_CAX_MAX_ARCH_ISR_ID >= 951))
#if (EE_CAX_951_ISR_CAT == 2)
 { 951, EE_CAX_ISR2_PRI(EE_CAX_951_ISR_PRI) },
#else
 { 951, EE_CAX_ISR1_PRI(EE_CAX_951_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_952_ISR) && (EE_CAX_MAX_ISR_ID >= 952) && (EE_CAX_MAX_ARCH_ISR_ID >= 952))
#if (EE_CAX_952_ISR_CAT == 2)
 { 952, EE_CAX_ISR2_PRI(EE_CAX_952_ISR_PRI) },
#else
 { 952, EE_CAX_ISR1_PRI(EE_CAX_952_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_953_ISR) && (EE_CAX_MAX_ISR_ID >= 953) && (EE_CAX_MAX_ARCH_ISR_ID >= 953))
#if (EE_CAX_953_ISR_CAT == 2)
 { 953, EE_CAX_ISR2_PRI(EE_CAX_953_ISR_PRI) },
#else
 { 953, EE_CAX_ISR1_PRI(EE_CAX_953_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_954_ISR) && (EE_CAX_MAX_ISR_ID >= 954) && (EE_CAX_MAX_ARCH_ISR_ID >= 954))
#if (EE_CAX_954_ISR_CAT == 2)
 { 954, EE_CAX_ISR2_PRI(EE_CAX_954_ISR_PRI) },
#else
 { 954, EE_CAX_ISR1_PRI(EE_CAX_954_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_955_ISR) && (EE_CAX_MAX_ISR_ID >= 955) && (EE_CAX_MAX_ARCH_ISR_ID >= 955))
#if (EE_CAX_955_ISR_CAT == 2)
 { 955, EE_CAX_ISR2_PRI(EE_CAX_955_ISR_PRI) },
#else
 { 955, EE_CAX_ISR1_PRI(EE_CAX_955_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_956_ISR) && (EE_CAX_MAX_ISR_ID >= 956) && (EE_CAX_MAX_ARCH_ISR_ID >= 956))
#if (EE_CAX_956_ISR_CAT == 2)
 { 956, EE_CAX_ISR2_PRI(EE_CAX_956_ISR_PRI) },
#else
 { 956, EE_CAX_ISR1_PRI(EE_CAX_956_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_957_ISR) && (EE_CAX_MAX_ISR_ID >= 957) && (EE_CAX_MAX_ARCH_ISR_ID >= 957))
#if (EE_CAX_957_ISR_CAT == 2)
 { 957, EE_CAX_ISR2_PRI(EE_CAX_957_ISR_PRI) },
#else
 { 957, EE_CAX_ISR1_PRI(EE_CAX_957_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_958_ISR) && (EE_CAX_MAX_ISR_ID >= 958) && (EE_CAX_MAX_ARCH_ISR_ID >= 958))
#if (EE_CAX_958_ISR_CAT == 2)
 { 958, EE_CAX_ISR2_PRI(EE_CAX_958_ISR_PRI) },
#else
 { 958, EE_CAX_ISR1_PRI(EE_CAX_958_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_959_ISR) && (EE_CAX_MAX_ISR_ID >= 959) && (EE_CAX_MAX_ARCH_ISR_ID >= 959))
#if (EE_CAX_959_ISR_CAT == 2)
 { 959, EE_CAX_ISR2_PRI(EE_CAX_959_ISR_PRI) },
#else
 { 959, EE_CAX_ISR1_PRI(EE_CAX_959_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_960_ISR) && (EE_CAX_MAX_ISR_ID >= 960) && (EE_CAX_MAX_ARCH_ISR_ID >= 960))
#if (EE_CAX_960_ISR_CAT == 2)
 { 960, EE_CAX_ISR2_PRI(EE_CAX_960_ISR_PRI) },
#else
 { 960, EE_CAX_ISR1_PRI(EE_CAX_960_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_961_ISR) && (EE_CAX_MAX_ISR_ID >= 961) && (EE_CAX_MAX_ARCH_ISR_ID >= 961))
#if (EE_CAX_961_ISR_CAT == 2)
 { 961, EE_CAX_ISR2_PRI(EE_CAX_961_ISR_PRI) },
#else
 { 961, EE_CAX_ISR1_PRI(EE_CAX_961_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_962_ISR) && (EE_CAX_MAX_ISR_ID >= 962) && (EE_CAX_MAX_ARCH_ISR_ID >= 962))
#if (EE_CAX_962_ISR_CAT == 2)
 { 962, EE_CAX_ISR2_PRI(EE_CAX_962_ISR_PRI) },
#else
 { 962, EE_CAX_ISR1_PRI(EE_CAX_962_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_963_ISR) && (EE_CAX_MAX_ISR_ID >= 963) && (EE_CAX_MAX_ARCH_ISR_ID >= 963))
#if (EE_CAX_963_ISR_CAT == 2)
 { 963, EE_CAX_ISR2_PRI(EE_CAX_963_ISR_PRI) },
#else
 { 963, EE_CAX_ISR1_PRI(EE_CAX_963_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_964_ISR) && (EE_CAX_MAX_ISR_ID >= 964) && (EE_CAX_MAX_ARCH_ISR_ID >= 964))
#if (EE_CAX_964_ISR_CAT == 2)
 { 964, EE_CAX_ISR2_PRI(EE_CAX_964_ISR_PRI) },
#else
 { 964, EE_CAX_ISR1_PRI(EE_CAX_964_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_965_ISR) && (EE_CAX_MAX_ISR_ID >= 965) && (EE_CAX_MAX_ARCH_ISR_ID >= 965))
#if (EE_CAX_965_ISR_CAT == 2)
 { 965, EE_CAX_ISR2_PRI(EE_CAX_965_ISR_PRI) },
#else
 { 965, EE_CAX_ISR1_PRI(EE_CAX_965_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_966_ISR) && (EE_CAX_MAX_ISR_ID >= 966) && (EE_CAX_MAX_ARCH_ISR_ID >= 966))
#if (EE_CAX_966_ISR_CAT == 2)
 { 966, EE_CAX_ISR2_PRI(EE_CAX_966_ISR_PRI) },
#else
 { 966, EE_CAX_ISR1_PRI(EE_CAX_966_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_967_ISR) && (EE_CAX_MAX_ISR_ID >= 967) && (EE_CAX_MAX_ARCH_ISR_ID >= 967))
#if (EE_CAX_967_ISR_CAT == 2)
 { 967, EE_CAX_ISR2_PRI(EE_CAX_967_ISR_PRI) },
#else
 { 967, EE_CAX_ISR1_PRI(EE_CAX_967_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_968_ISR) && (EE_CAX_MAX_ISR_ID >= 968) && (EE_CAX_MAX_ARCH_ISR_ID >= 968))
#if (EE_CAX_968_ISR_CAT == 2)
 { 968, EE_CAX_ISR2_PRI(EE_CAX_968_ISR_PRI) },
#else
 { 968, EE_CAX_ISR1_PRI(EE_CAX_968_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_969_ISR) && (EE_CAX_MAX_ISR_ID >= 969) && (EE_CAX_MAX_ARCH_ISR_ID >= 969))
#if (EE_CAX_969_ISR_CAT == 2)
 { 969, EE_CAX_ISR2_PRI(EE_CAX_969_ISR_PRI) },
#else
 { 969, EE_CAX_ISR1_PRI(EE_CAX_969_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_970_ISR) && (EE_CAX_MAX_ISR_ID >= 970) && (EE_CAX_MAX_ARCH_ISR_ID >= 970))
#if (EE_CAX_970_ISR_CAT == 2)
 { 970, EE_CAX_ISR2_PRI(EE_CAX_970_ISR_PRI) },
#else
 { 970, EE_CAX_ISR1_PRI(EE_CAX_970_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_971_ISR) && (EE_CAX_MAX_ISR_ID >= 971) && (EE_CAX_MAX_ARCH_ISR_ID >= 971))
#if (EE_CAX_971_ISR_CAT == 2)
 { 971, EE_CAX_ISR2_PRI(EE_CAX_971_ISR_PRI) },
#else
 { 971, EE_CAX_ISR1_PRI(EE_CAX_971_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_972_ISR) && (EE_CAX_MAX_ISR_ID >= 972) && (EE_CAX_MAX_ARCH_ISR_ID >= 972))
#if (EE_CAX_972_ISR_CAT == 2)
 { 972, EE_CAX_ISR2_PRI(EE_CAX_972_ISR_PRI) },
#else
 { 972, EE_CAX_ISR1_PRI(EE_CAX_972_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_973_ISR) && (EE_CAX_MAX_ISR_ID >= 973) && (EE_CAX_MAX_ARCH_ISR_ID >= 973))
#if (EE_CAX_973_ISR_CAT == 2)
 { 973, EE_CAX_ISR2_PRI(EE_CAX_973_ISR_PRI) },
#else
 { 973, EE_CAX_ISR1_PRI(EE_CAX_973_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_974_ISR) && (EE_CAX_MAX_ISR_ID >= 974) && (EE_CAX_MAX_ARCH_ISR_ID >= 974))
#if (EE_CAX_974_ISR_CAT == 2)
 { 974, EE_CAX_ISR2_PRI(EE_CAX_974_ISR_PRI) },
#else
 { 974, EE_CAX_ISR1_PRI(EE_CAX_974_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_975_ISR) && (EE_CAX_MAX_ISR_ID >= 975) && (EE_CAX_MAX_ARCH_ISR_ID >= 975))
#if (EE_CAX_975_ISR_CAT == 2)
 { 975, EE_CAX_ISR2_PRI(EE_CAX_975_ISR_PRI) },
#else
 { 975, EE_CAX_ISR1_PRI(EE_CAX_975_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_976_ISR) && (EE_CAX_MAX_ISR_ID >= 976) && (EE_CAX_MAX_ARCH_ISR_ID >= 976))
#if (EE_CAX_976_ISR_CAT == 2)
 { 976, EE_CAX_ISR2_PRI(EE_CAX_976_ISR_PRI) },
#else
 { 976, EE_CAX_ISR1_PRI(EE_CAX_976_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_977_ISR) && (EE_CAX_MAX_ISR_ID >= 977) && (EE_CAX_MAX_ARCH_ISR_ID >= 977))
#if (EE_CAX_977_ISR_CAT == 2)
 { 977, EE_CAX_ISR2_PRI(EE_CAX_977_ISR_PRI) },
#else
 { 977, EE_CAX_ISR1_PRI(EE_CAX_977_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_978_ISR) && (EE_CAX_MAX_ISR_ID >= 978) && (EE_CAX_MAX_ARCH_ISR_ID >= 978))
#if (EE_CAX_978_ISR_CAT == 2)
 { 978, EE_CAX_ISR2_PRI(EE_CAX_978_ISR_PRI) },
#else
 { 978, EE_CAX_ISR1_PRI(EE_CAX_978_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_979_ISR) && (EE_CAX_MAX_ISR_ID >= 979) && (EE_CAX_MAX_ARCH_ISR_ID >= 979))
#if (EE_CAX_979_ISR_CAT == 2)
 { 979, EE_CAX_ISR2_PRI(EE_CAX_979_ISR_PRI) },
#else
 { 979, EE_CAX_ISR1_PRI(EE_CAX_979_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_980_ISR) && (EE_CAX_MAX_ISR_ID >= 980) && (EE_CAX_MAX_ARCH_ISR_ID >= 980))
#if (EE_CAX_980_ISR_CAT == 2)
 { 980, EE_CAX_ISR2_PRI(EE_CAX_980_ISR_PRI) },
#else
 { 980, EE_CAX_ISR1_PRI(EE_CAX_980_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_981_ISR) && (EE_CAX_MAX_ISR_ID >= 981) && (EE_CAX_MAX_ARCH_ISR_ID >= 981))
#if (EE_CAX_981_ISR_CAT == 2)
 { 981, EE_CAX_ISR2_PRI(EE_CAX_981_ISR_PRI) },
#else
 { 981, EE_CAX_ISR1_PRI(EE_CAX_981_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_982_ISR) && (EE_CAX_MAX_ISR_ID >= 982) && (EE_CAX_MAX_ARCH_ISR_ID >= 982))
#if (EE_CAX_982_ISR_CAT == 2)
 { 982, EE_CAX_ISR2_PRI(EE_CAX_982_ISR_PRI) },
#else
 { 982, EE_CAX_ISR1_PRI(EE_CAX_982_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_983_ISR) && (EE_CAX_MAX_ISR_ID >= 983) && (EE_CAX_MAX_ARCH_ISR_ID >= 983))
#if (EE_CAX_983_ISR_CAT == 2)
 { 983, EE_CAX_ISR2_PRI(EE_CAX_983_ISR_PRI) },
#else
 { 983, EE_CAX_ISR1_PRI(EE_CAX_983_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_984_ISR) && (EE_CAX_MAX_ISR_ID >= 984) && (EE_CAX_MAX_ARCH_ISR_ID >= 984))
#if (EE_CAX_984_ISR_CAT == 2)
 { 984, EE_CAX_ISR2_PRI(EE_CAX_984_ISR_PRI) },
#else
 { 984, EE_CAX_ISR1_PRI(EE_CAX_984_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_985_ISR) && (EE_CAX_MAX_ISR_ID >= 985) && (EE_CAX_MAX_ARCH_ISR_ID >= 985))
#if (EE_CAX_985_ISR_CAT == 2)
 { 985, EE_CAX_ISR2_PRI(EE_CAX_985_ISR_PRI) },
#else
 { 985, EE_CAX_ISR1_PRI(EE_CAX_985_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_986_ISR) && (EE_CAX_MAX_ISR_ID >= 986) && (EE_CAX_MAX_ARCH_ISR_ID >= 986))
#if (EE_CAX_986_ISR_CAT == 2)
 { 986, EE_CAX_ISR2_PRI(EE_CAX_986_ISR_PRI) },
#else
 { 986, EE_CAX_ISR1_PRI(EE_CAX_986_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_987_ISR) && (EE_CAX_MAX_ISR_ID >= 987) && (EE_CAX_MAX_ARCH_ISR_ID >= 987))
#if (EE_CAX_987_ISR_CAT == 2)
 { 987, EE_CAX_ISR2_PRI(EE_CAX_987_ISR_PRI) },
#else
 { 987, EE_CAX_ISR1_PRI(EE_CAX_987_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_988_ISR) && (EE_CAX_MAX_ISR_ID >= 988) && (EE_CAX_MAX_ARCH_ISR_ID >= 988))
#if (EE_CAX_988_ISR_CAT == 2)
 { 988, EE_CAX_ISR2_PRI(EE_CAX_988_ISR_PRI) },
#else
 { 988, EE_CAX_ISR1_PRI(EE_CAX_988_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_989_ISR) && (EE_CAX_MAX_ISR_ID >= 989) && (EE_CAX_MAX_ARCH_ISR_ID >= 989))
#if (EE_CAX_989_ISR_CAT == 2)
 { 989, EE_CAX_ISR2_PRI(EE_CAX_989_ISR_PRI) },
#else
 { 989, EE_CAX_ISR1_PRI(EE_CAX_989_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_990_ISR) && (EE_CAX_MAX_ISR_ID >= 990) && (EE_CAX_MAX_ARCH_ISR_ID >= 990))
#if (EE_CAX_990_ISR_CAT == 2)
 { 990, EE_CAX_ISR2_PRI(EE_CAX_990_ISR_PRI) },
#else
 { 990, EE_CAX_ISR1_PRI(EE_CAX_990_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_991_ISR) && (EE_CAX_MAX_ISR_ID >= 991) && (EE_CAX_MAX_ARCH_ISR_ID >= 991))
#if (EE_CAX_991_ISR_CAT == 2)
 { 991, EE_CAX_ISR2_PRI(EE_CAX_991_ISR_PRI) },
#else
 { 991, EE_CAX_ISR1_PRI(EE_CAX_991_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_992_ISR) && (EE_CAX_MAX_ISR_ID >= 992) && (EE_CAX_MAX_ARCH_ISR_ID >= 992))
#if (EE_CAX_992_ISR_CAT == 2)
 { 992, EE_CAX_ISR2_PRI(EE_CAX_992_ISR_PRI) },
#else
 { 992, EE_CAX_ISR1_PRI(EE_CAX_992_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_993_ISR) && (EE_CAX_MAX_ISR_ID >= 993) && (EE_CAX_MAX_ARCH_ISR_ID >= 993))
#if (EE_CAX_993_ISR_CAT == 2)
 { 993, EE_CAX_ISR2_PRI(EE_CAX_993_ISR_PRI) },
#else
 { 993, EE_CAX_ISR1_PRI(EE_CAX_993_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_994_ISR) && (EE_CAX_MAX_ISR_ID >= 994) && (EE_CAX_MAX_ARCH_ISR_ID >= 994))
#if (EE_CAX_994_ISR_CAT == 2)
 { 994, EE_CAX_ISR2_PRI(EE_CAX_994_ISR_PRI) },
#else
 { 994, EE_CAX_ISR1_PRI(EE_CAX_994_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_995_ISR) && (EE_CAX_MAX_ISR_ID >= 995) && (EE_CAX_MAX_ARCH_ISR_ID >= 995))
#if (EE_CAX_995_ISR_CAT == 2)
 { 995, EE_CAX_ISR2_PRI(EE_CAX_995_ISR_PRI) },
#else
 { 995, EE_CAX_ISR1_PRI(EE_CAX_995_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_996_ISR) && (EE_CAX_MAX_ISR_ID >= 996) && (EE_CAX_MAX_ARCH_ISR_ID >= 996))
#if (EE_CAX_996_ISR_CAT == 2)
 { 996, EE_CAX_ISR2_PRI(EE_CAX_996_ISR_PRI) },
#else
 { 996, EE_CAX_ISR1_PRI(EE_CAX_996_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_997_ISR) && (EE_CAX_MAX_ISR_ID >= 997) && (EE_CAX_MAX_ARCH_ISR_ID >= 997))
#if (EE_CAX_997_ISR_CAT == 2)
 { 997, EE_CAX_ISR2_PRI(EE_CAX_997_ISR_PRI) },
#else
 { 997, EE_CAX_ISR1_PRI(EE_CAX_997_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_998_ISR) && (EE_CAX_MAX_ISR_ID >= 998) && (EE_CAX_MAX_ARCH_ISR_ID >= 998))
#if (EE_CAX_998_ISR_CAT == 2)
 { 998, EE_CAX_ISR2_PRI(EE_CAX_998_ISR_PRI) },
#else
 { 998, EE_CAX_ISR1_PRI(EE_CAX_998_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_999_ISR) && (EE_CAX_MAX_ISR_ID >= 999) && (EE_CAX_MAX_ARCH_ISR_ID >= 999))
#if (EE_CAX_999_ISR_CAT == 2)
 { 999, EE_CAX_ISR2_PRI(EE_CAX_999_ISR_PRI) },
#else
 { 999, EE_CAX_ISR1_PRI(EE_CAX_999_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1000_ISR) && (EE_CAX_MAX_ISR_ID >= 1000) && (EE_CAX_MAX_ARCH_ISR_ID >= 1000))
#if (EE_CAX_1000_ISR_CAT == 2)
 { 1000, EE_CAX_ISR2_PRI(EE_CAX_1000_ISR_PRI) },
#else
 { 1000, EE_CAX_ISR1_PRI(EE_CAX_1000_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1001_ISR) && (EE_CAX_MAX_ISR_ID >= 1001) && (EE_CAX_MAX_ARCH_ISR_ID >= 1001))
#if (EE_CAX_1001_ISR_CAT == 2)
 { 1001, EE_CAX_ISR2_PRI(EE_CAX_1001_ISR_PRI) },
#else
 { 1001, EE_CAX_ISR1_PRI(EE_CAX_1001_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1002_ISR) && (EE_CAX_MAX_ISR_ID >= 1002) && (EE_CAX_MAX_ARCH_ISR_ID >= 1002))
#if (EE_CAX_1002_ISR_CAT == 2)
 { 1002, EE_CAX_ISR2_PRI(EE_CAX_1002_ISR_PRI) },
#else
 { 1002, EE_CAX_ISR1_PRI(EE_CAX_1002_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1003_ISR) && (EE_CAX_MAX_ISR_ID >= 1003) && (EE_CAX_MAX_ARCH_ISR_ID >= 1003))
#if (EE_CAX_1003_ISR_CAT == 2)
 { 1003, EE_CAX_ISR2_PRI(EE_CAX_1003_ISR_PRI) },
#else
 { 1003, EE_CAX_ISR1_PRI(EE_CAX_1003_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1004_ISR) && (EE_CAX_MAX_ISR_ID >= 1004) && (EE_CAX_MAX_ARCH_ISR_ID >= 1004))
#if (EE_CAX_1004_ISR_CAT == 2)
 { 1004, EE_CAX_ISR2_PRI(EE_CAX_1004_ISR_PRI) },
#else
 { 1004, EE_CAX_ISR1_PRI(EE_CAX_1004_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1005_ISR) && (EE_CAX_MAX_ISR_ID >= 1005) && (EE_CAX_MAX_ARCH_ISR_ID >= 1005))
#if (EE_CAX_1005_ISR_CAT == 2)
 { 1005, EE_CAX_ISR2_PRI(EE_CAX_1005_ISR_PRI) },
#else
 { 1005, EE_CAX_ISR1_PRI(EE_CAX_1005_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1006_ISR) && (EE_CAX_MAX_ISR_ID >= 1006) && (EE_CAX_MAX_ARCH_ISR_ID >= 1006))
#if (EE_CAX_1006_ISR_CAT == 2)
 { 1006, EE_CAX_ISR2_PRI(EE_CAX_1006_ISR_PRI) },
#else
 { 1006, EE_CAX_ISR1_PRI(EE_CAX_1006_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1007_ISR) && (EE_CAX_MAX_ISR_ID >= 1007) && (EE_CAX_MAX_ARCH_ISR_ID >= 1007))
#if (EE_CAX_1007_ISR_CAT == 2)
 { 1007, EE_CAX_ISR2_PRI(EE_CAX_1007_ISR_PRI) },
#else
 { 1007, EE_CAX_ISR1_PRI(EE_CAX_1007_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1008_ISR) && (EE_CAX_MAX_ISR_ID >= 1008) && (EE_CAX_MAX_ARCH_ISR_ID >= 1008))
#if (EE_CAX_1008_ISR_CAT == 2)
 { 1008, EE_CAX_ISR2_PRI(EE_CAX_1008_ISR_PRI) },
#else
 { 1008, EE_CAX_ISR1_PRI(EE_CAX_1008_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1009_ISR) && (EE_CAX_MAX_ISR_ID >= 1009) && (EE_CAX_MAX_ARCH_ISR_ID >= 1009))
#if (EE_CAX_1009_ISR_CAT == 2)
 { 1009, EE_CAX_ISR2_PRI(EE_CAX_1009_ISR_PRI) },
#else
 { 1009, EE_CAX_ISR1_PRI(EE_CAX_1009_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1010_ISR) && (EE_CAX_MAX_ISR_ID >= 1010) && (EE_CAX_MAX_ARCH_ISR_ID >= 1010))
#if (EE_CAX_1010_ISR_CAT == 2)
 { 1010, EE_CAX_ISR2_PRI(EE_CAX_1010_ISR_PRI) },
#else
 { 1010, EE_CAX_ISR1_PRI(EE_CAX_1010_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1011_ISR) && (EE_CAX_MAX_ISR_ID >= 1011) && (EE_CAX_MAX_ARCH_ISR_ID >= 1011))
#if (EE_CAX_1011_ISR_CAT == 2)
 { 1011, EE_CAX_ISR2_PRI(EE_CAX_1011_ISR_PRI) },
#else
 { 1011, EE_CAX_ISR1_PRI(EE_CAX_1011_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1012_ISR) && (EE_CAX_MAX_ISR_ID >= 1012) && (EE_CAX_MAX_ARCH_ISR_ID >= 1012))
#if (EE_CAX_1012_ISR_CAT == 2)
 { 1012, EE_CAX_ISR2_PRI(EE_CAX_1012_ISR_PRI) },
#else
 { 1012, EE_CAX_ISR1_PRI(EE_CAX_1012_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1013_ISR) && (EE_CAX_MAX_ISR_ID >= 1013) && (EE_CAX_MAX_ARCH_ISR_ID >= 1013))
#if (EE_CAX_1013_ISR_CAT == 2)
 { 1013, EE_CAX_ISR2_PRI(EE_CAX_1013_ISR_PRI) },
#else
 { 1013, EE_CAX_ISR1_PRI(EE_CAX_1013_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1014_ISR) && (EE_CAX_MAX_ISR_ID >= 1014) && (EE_CAX_MAX_ARCH_ISR_ID >= 1014))
#if (EE_CAX_1014_ISR_CAT == 2)
 { 1014, EE_CAX_ISR2_PRI(EE_CAX_1014_ISR_PRI) },
#else
 { 1014, EE_CAX_ISR1_PRI(EE_CAX_1014_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1015_ISR) && (EE_CAX_MAX_ISR_ID >= 1015) && (EE_CAX_MAX_ARCH_ISR_ID >= 1015))
#if (EE_CAX_1015_ISR_CAT == 2)
 { 1015, EE_CAX_ISR2_PRI(EE_CAX_1015_ISR_PRI) },
#else
 { 1015, EE_CAX_ISR1_PRI(EE_CAX_1015_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1016_ISR) && (EE_CAX_MAX_ISR_ID >= 1016) && (EE_CAX_MAX_ARCH_ISR_ID >= 1016))
#if (EE_CAX_1016_ISR_CAT == 2)
 { 1016, EE_CAX_ISR2_PRI(EE_CAX_1016_ISR_PRI) },
#else
 { 1016, EE_CAX_ISR1_PRI(EE_CAX_1016_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1017_ISR) && (EE_CAX_MAX_ISR_ID >= 1017) && (EE_CAX_MAX_ARCH_ISR_ID >= 1017))
#if (EE_CAX_1017_ISR_CAT == 2)
 { 1017, EE_CAX_ISR2_PRI(EE_CAX_1017_ISR_PRI) },
#else
 { 1017, EE_CAX_ISR1_PRI(EE_CAX_1017_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1018_ISR) && (EE_CAX_MAX_ISR_ID >= 1018) && (EE_CAX_MAX_ARCH_ISR_ID >= 1018))
#if (EE_CAX_1018_ISR_CAT == 2)
 { 1018, EE_CAX_ISR2_PRI(EE_CAX_1018_ISR_PRI) },
#else
 { 1018, EE_CAX_ISR1_PRI(EE_CAX_1018_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1019_ISR) && (EE_CAX_MAX_ISR_ID >= 1019) && (EE_CAX_MAX_ARCH_ISR_ID >= 1019))
#if (EE_CAX_1019_ISR_CAT == 2)
 { 1019, EE_CAX_ISR2_PRI(EE_CAX_1019_ISR_PRI) },
#else
 { 1019, EE_CAX_ISR1_PRI(EE_CAX_1019_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1020_ISR) && (EE_CAX_MAX_ISR_ID >= 1020) && (EE_CAX_MAX_ARCH_ISR_ID >= 1020))
#if (EE_CAX_1020_ISR_CAT == 2)
 { 1020, EE_CAX_ISR2_PRI(EE_CAX_1020_ISR_PRI) },
#else
 { 1020, EE_CAX_ISR1_PRI(EE_CAX_1020_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1021_ISR) && (EE_CAX_MAX_ISR_ID >= 1021) && (EE_CAX_MAX_ARCH_ISR_ID >= 1021))
#if (EE_CAX_1021_ISR_CAT == 2)
 { 1021, EE_CAX_ISR2_PRI(EE_CAX_1021_ISR_PRI) },
#else
 { 1021, EE_CAX_ISR1_PRI(EE_CAX_1021_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1022_ISR) && (EE_CAX_MAX_ISR_ID >= 1022) && (EE_CAX_MAX_ARCH_ISR_ID >= 1022))
#if (EE_CAX_1022_ISR_CAT == 2)
 { 1022, EE_CAX_ISR2_PRI(EE_CAX_1022_ISR_PRI) },
#else
 { 1022, EE_CAX_ISR1_PRI(EE_CAX_1022_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1023_ISR) && (EE_CAX_MAX_ISR_ID >= 1023) && (EE_CAX_MAX_ARCH_ISR_ID >= 1023))
#if (EE_CAX_1023_ISR_CAT == 2)
 { 1023, EE_CAX_ISR2_PRI(EE_CAX_1023_ISR_PRI) },
#else
 { 1023, EE_CAX_ISR1_PRI(EE_CAX_1023_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1024_ISR) && (EE_CAX_MAX_ISR_ID >= 1024) && (EE_CAX_MAX_ARCH_ISR_ID >= 1024))
#if (EE_CAX_1024_ISR_CAT == 2)
 { 1024, EE_CAX_ISR2_PRI(EE_CAX_1024_ISR_PRI) },
#else
 { 1024, EE_CAX_ISR1_PRI(EE_CAX_1024_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1025_ISR) && (EE_CAX_MAX_ISR_ID >= 1025) && (EE_CAX_MAX_ARCH_ISR_ID >= 1025))
#if (EE_CAX_1025_ISR_CAT == 2)
 { 1025, EE_CAX_ISR2_PRI(EE_CAX_1025_ISR_PRI) },
#else
 { 1025, EE_CAX_ISR1_PRI(EE_CAX_1025_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1026_ISR) && (EE_CAX_MAX_ISR_ID >= 1026) && (EE_CAX_MAX_ARCH_ISR_ID >= 1026))
#if (EE_CAX_1026_ISR_CAT == 2)
 { 1026, EE_CAX_ISR2_PRI(EE_CAX_1026_ISR_PRI) },
#else
 { 1026, EE_CAX_ISR1_PRI(EE_CAX_1026_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1027_ISR) && (EE_CAX_MAX_ISR_ID >= 1027) && (EE_CAX_MAX_ARCH_ISR_ID >= 1027))
#if (EE_CAX_1027_ISR_CAT == 2)
 { 1027, EE_CAX_ISR2_PRI(EE_CAX_1027_ISR_PRI) },
#else
 { 1027, EE_CAX_ISR1_PRI(EE_CAX_1027_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1028_ISR) && (EE_CAX_MAX_ISR_ID >= 1028) && (EE_CAX_MAX_ARCH_ISR_ID >= 1028))
#if (EE_CAX_1028_ISR_CAT == 2)
 { 1028, EE_CAX_ISR2_PRI(EE_CAX_1028_ISR_PRI) },
#else
 { 1028, EE_CAX_ISR1_PRI(EE_CAX_1028_ISR_PRI) },
#endif
#endif
#if (defined(EE_CAX_1029_ISR) && (EE_CAX_MAX_ISR_ID >= 1029) && (EE_CAX_MAX_ARCH_ISR_ID >= 1029))
#if (EE_CAX_1029_ISR_CAT == 2)
 { 1029, EE_CAX_ISR2_PRI(EE_CAX_1029_ISR_PRI) },
#else
 { 1029, EE_CAX_ISR1_PRI(EE_CAX_1029_ISR_PRI) },
#endif
#endif
};

#define IP_TABLE_SIZE (sizeof(ip_table)/sizeof(ip_table[0]))

#endif /* EE_GIC_PRIO_TABLE_H__ */

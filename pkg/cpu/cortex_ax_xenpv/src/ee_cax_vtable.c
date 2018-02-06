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

#include "ee.h"
#include "eecfg.h"

#include "cpu/cortex_ax_xenpv/inc/ee_cax_irq.h"

static unsigned int forever_loop_counter;

void forever_loop_handler(void)
{
  for (;;)
        forever_loop_counter++;
}
#if 0
void private_timer()
{
  static unsigned int cnt = 0;
  unsigned int *i = 0x10802018;
  *i = *i + 1;
}
#endif

/*extern void Timer_isr2(void);*/

#define EE_ISR_DUMMY forever_loop_handler

/* externs ... */
#if ((EE_CAX_MAX_ISR_ID >= 0) && (EE_CAX_MAX_ARCH_ISR_ID >= 0) && defined(EE_CAX_0_ISR))
extern void EE_CAX_0_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1) && (EE_CAX_MAX_ARCH_ISR_ID >= 1) && defined(EE_CAX_1_ISR))
extern void EE_CAX_1_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 2) && (EE_CAX_MAX_ARCH_ISR_ID >= 2) && defined(EE_CAX_2_ISR))
extern void EE_CAX_2_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 3) && (EE_CAX_MAX_ARCH_ISR_ID >= 3) && defined(EE_CAX_3_ISR))
extern void EE_CAX_3_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 4) && (EE_CAX_MAX_ARCH_ISR_ID >= 4) && defined(EE_CAX_4_ISR))
extern void EE_CAX_4_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 5) && (EE_CAX_MAX_ARCH_ISR_ID >= 5) && defined(EE_CAX_5_ISR))
extern void EE_CAX_5_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 6) && (EE_CAX_MAX_ARCH_ISR_ID >= 6) && defined(EE_CAX_6_ISR))
extern void EE_CAX_6_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 7) && (EE_CAX_MAX_ARCH_ISR_ID >= 7) && defined(EE_CAX_7_ISR))
extern void EE_CAX_7_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 8) && (EE_CAX_MAX_ARCH_ISR_ID >= 8) && defined(EE_CAX_8_ISR))
extern void EE_CAX_8_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 9) && (EE_CAX_MAX_ARCH_ISR_ID >= 9) && defined(EE_CAX_9_ISR))
extern void EE_CAX_9_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 10) && (EE_CAX_MAX_ARCH_ISR_ID >= 10) && defined(EE_CAX_10_ISR))
extern void EE_CAX_10_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 11) && (EE_CAX_MAX_ARCH_ISR_ID >= 11) && defined(EE_CAX_11_ISR))
extern void EE_CAX_11_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 12) && (EE_CAX_MAX_ARCH_ISR_ID >= 12) && defined(EE_CAX_12_ISR))
extern void EE_CAX_12_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 13) && (EE_CAX_MAX_ARCH_ISR_ID >= 13) && defined(EE_CAX_13_ISR))
extern void EE_CAX_13_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 14) && (EE_CAX_MAX_ARCH_ISR_ID >= 14) && defined(EE_CAX_14_ISR))
extern void EE_CAX_14_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 15) && (EE_CAX_MAX_ARCH_ISR_ID >= 15) && defined(EE_CAX_15_ISR))
extern void EE_CAX_15_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 16) && (EE_CAX_MAX_ARCH_ISR_ID >= 16) && defined(EE_CAX_16_ISR))
extern void EE_CAX_16_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 17) && (EE_CAX_MAX_ARCH_ISR_ID >= 17) && defined(EE_CAX_17_ISR))
extern void EE_CAX_17_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 18) && (EE_CAX_MAX_ARCH_ISR_ID >= 18) && defined(EE_CAX_18_ISR))
extern void EE_CAX_18_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 19) && (EE_CAX_MAX_ARCH_ISR_ID >= 19) && defined(EE_CAX_19_ISR))
extern void EE_CAX_19_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 20) && (EE_CAX_MAX_ARCH_ISR_ID >= 20) && defined(EE_CAX_20_ISR))
extern void EE_CAX_20_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 21) && (EE_CAX_MAX_ARCH_ISR_ID >= 21) && defined(EE_CAX_21_ISR))
extern void EE_CAX_21_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 22) && (EE_CAX_MAX_ARCH_ISR_ID >= 22) && defined(EE_CAX_22_ISR))
extern void EE_CAX_22_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 23) && (EE_CAX_MAX_ARCH_ISR_ID >= 23) && defined(EE_CAX_23_ISR))
extern void EE_CAX_23_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 24) && (EE_CAX_MAX_ARCH_ISR_ID >= 24) && defined(EE_CAX_24_ISR))
extern void EE_CAX_24_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 25) && (EE_CAX_MAX_ARCH_ISR_ID >= 25) && defined(EE_CAX_25_ISR))
extern void EE_CAX_25_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 26) && (EE_CAX_MAX_ARCH_ISR_ID >= 26) && defined(EE_CAX_26_ISR))
extern void EE_CAX_26_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 27) && (EE_CAX_MAX_ARCH_ISR_ID >= 27) && defined(EE_CAX_27_ISR))
extern void EE_CAX_27_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 28) && (EE_CAX_MAX_ARCH_ISR_ID >= 28) && defined(EE_CAX_28_ISR))
extern void EE_CAX_28_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 29) && (EE_CAX_MAX_ARCH_ISR_ID >= 29) && defined(EE_CAX_29_ISR))
extern void EE_CAX_29_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 30) && (EE_CAX_MAX_ARCH_ISR_ID >= 30) && defined(EE_CAX_30_ISR))
extern void EE_CAX_30_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 31) && (EE_CAX_MAX_ARCH_ISR_ID >= 31) && defined(EE_CAX_31_ISR))
extern void EE_CAX_31_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 32) && (EE_CAX_MAX_ARCH_ISR_ID >= 32) && defined(EE_CAX_32_ISR))
extern void EE_CAX_32_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 33) && (EE_CAX_MAX_ARCH_ISR_ID >= 33) && defined(EE_CAX_33_ISR))
extern void EE_CAX_33_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 34) && (EE_CAX_MAX_ARCH_ISR_ID >= 34) && defined(EE_CAX_34_ISR))
extern void EE_CAX_34_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 35) && (EE_CAX_MAX_ARCH_ISR_ID >= 35) && defined(EE_CAX_35_ISR))
extern void EE_CAX_35_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 36) && (EE_CAX_MAX_ARCH_ISR_ID >= 36) && defined(EE_CAX_36_ISR))
extern void EE_CAX_36_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 37) && (EE_CAX_MAX_ARCH_ISR_ID >= 37) && defined(EE_CAX_37_ISR))
extern void EE_CAX_37_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 38) && (EE_CAX_MAX_ARCH_ISR_ID >= 38) && defined(EE_CAX_38_ISR))
extern void EE_CAX_38_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 39) && (EE_CAX_MAX_ARCH_ISR_ID >= 39) && defined(EE_CAX_39_ISR))
extern void EE_CAX_39_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 40) && (EE_CAX_MAX_ARCH_ISR_ID >= 40) && defined(EE_CAX_40_ISR))
extern void EE_CAX_40_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 41) && (EE_CAX_MAX_ARCH_ISR_ID >= 41) && defined(EE_CAX_41_ISR))
extern void EE_CAX_41_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 42) && (EE_CAX_MAX_ARCH_ISR_ID >= 42) && defined(EE_CAX_42_ISR))
extern void EE_CAX_42_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 43) && (EE_CAX_MAX_ARCH_ISR_ID >= 43) && defined(EE_CAX_43_ISR))
extern void EE_CAX_43_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 44) && (EE_CAX_MAX_ARCH_ISR_ID >= 44) && defined(EE_CAX_44_ISR))
extern void EE_CAX_44_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 45) && (EE_CAX_MAX_ARCH_ISR_ID >= 45) && defined(EE_CAX_45_ISR))
extern void EE_CAX_45_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 46) && (EE_CAX_MAX_ARCH_ISR_ID >= 46) && defined(EE_CAX_46_ISR))
extern void EE_CAX_46_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 47) && (EE_CAX_MAX_ARCH_ISR_ID >= 47) && defined(EE_CAX_47_ISR))
extern void EE_CAX_47_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 48) && (EE_CAX_MAX_ARCH_ISR_ID >= 48) && defined(EE_CAX_48_ISR))
extern void EE_CAX_48_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 49) && (EE_CAX_MAX_ARCH_ISR_ID >= 49) && defined(EE_CAX_49_ISR))
extern void EE_CAX_49_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 50) && (EE_CAX_MAX_ARCH_ISR_ID >= 50) && defined(EE_CAX_50_ISR))
extern void EE_CAX_50_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 51) && (EE_CAX_MAX_ARCH_ISR_ID >= 51) && defined(EE_CAX_51_ISR))
extern void EE_CAX_51_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 52) && (EE_CAX_MAX_ARCH_ISR_ID >= 52) && defined(EE_CAX_52_ISR))
extern void EE_CAX_52_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 53) && (EE_CAX_MAX_ARCH_ISR_ID >= 53) && defined(EE_CAX_53_ISR))
extern void EE_CAX_53_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 54) && (EE_CAX_MAX_ARCH_ISR_ID >= 54) && defined(EE_CAX_54_ISR))
extern void EE_CAX_54_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 55) && (EE_CAX_MAX_ARCH_ISR_ID >= 55) && defined(EE_CAX_55_ISR))
extern void EE_CAX_55_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 56) && (EE_CAX_MAX_ARCH_ISR_ID >= 56) && defined(EE_CAX_56_ISR))
extern void EE_CAX_56_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 57) && (EE_CAX_MAX_ARCH_ISR_ID >= 57) && defined(EE_CAX_57_ISR))
extern void EE_CAX_57_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 58) && (EE_CAX_MAX_ARCH_ISR_ID >= 58) && defined(EE_CAX_58_ISR))
extern void EE_CAX_58_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 59) && (EE_CAX_MAX_ARCH_ISR_ID >= 59) && defined(EE_CAX_59_ISR))
extern void EE_CAX_59_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 60) && (EE_CAX_MAX_ARCH_ISR_ID >= 60) && defined(EE_CAX_60_ISR))
extern void EE_CAX_60_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 61) && (EE_CAX_MAX_ARCH_ISR_ID >= 61) && defined(EE_CAX_61_ISR))
extern void EE_CAX_61_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 62) && (EE_CAX_MAX_ARCH_ISR_ID >= 62) && defined(EE_CAX_62_ISR))
extern void EE_CAX_62_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 63) && (EE_CAX_MAX_ARCH_ISR_ID >= 63) && defined(EE_CAX_63_ISR))
extern void EE_CAX_63_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 64) && (EE_CAX_MAX_ARCH_ISR_ID >= 64) && defined(EE_CAX_64_ISR))
extern void EE_CAX_64_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 65) && (EE_CAX_MAX_ARCH_ISR_ID >= 65) && defined(EE_CAX_65_ISR))
extern void EE_CAX_65_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 66) && (EE_CAX_MAX_ARCH_ISR_ID >= 66) && defined(EE_CAX_66_ISR))
extern void EE_CAX_66_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 67) && (EE_CAX_MAX_ARCH_ISR_ID >= 67) && defined(EE_CAX_67_ISR))
extern void EE_CAX_67_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 68) && (EE_CAX_MAX_ARCH_ISR_ID >= 68) && defined(EE_CAX_68_ISR))
extern void EE_CAX_68_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 69) && (EE_CAX_MAX_ARCH_ISR_ID >= 69) && defined(EE_CAX_69_ISR))
extern void EE_CAX_69_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 70) && (EE_CAX_MAX_ARCH_ISR_ID >= 70) && defined(EE_CAX_70_ISR))
extern void EE_CAX_70_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 71) && (EE_CAX_MAX_ARCH_ISR_ID >= 71) && defined(EE_CAX_71_ISR))
extern void EE_CAX_71_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 72) && (EE_CAX_MAX_ARCH_ISR_ID >= 72) && defined(EE_CAX_72_ISR))
extern void EE_CAX_72_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 73) && (EE_CAX_MAX_ARCH_ISR_ID >= 73) && defined(EE_CAX_73_ISR))
extern void EE_CAX_73_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 74) && (EE_CAX_MAX_ARCH_ISR_ID >= 74) && defined(EE_CAX_74_ISR))
extern void EE_CAX_74_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 75) && (EE_CAX_MAX_ARCH_ISR_ID >= 75) && defined(EE_CAX_75_ISR))
extern void EE_CAX_75_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 76) && (EE_CAX_MAX_ARCH_ISR_ID >= 76) && defined(EE_CAX_76_ISR))
extern void EE_CAX_76_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 77) && (EE_CAX_MAX_ARCH_ISR_ID >= 77) && defined(EE_CAX_77_ISR))
extern void EE_CAX_77_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 78) && (EE_CAX_MAX_ARCH_ISR_ID >= 78) && defined(EE_CAX_78_ISR))
extern void EE_CAX_78_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 79) && (EE_CAX_MAX_ARCH_ISR_ID >= 79) && defined(EE_CAX_79_ISR))
extern void EE_CAX_79_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 80) && (EE_CAX_MAX_ARCH_ISR_ID >= 80) && defined(EE_CAX_80_ISR))
extern void EE_CAX_80_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 81) && (EE_CAX_MAX_ARCH_ISR_ID >= 81) && defined(EE_CAX_81_ISR))
extern void EE_CAX_81_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 82) && (EE_CAX_MAX_ARCH_ISR_ID >= 82) && defined(EE_CAX_82_ISR))
extern void EE_CAX_82_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 83) && (EE_CAX_MAX_ARCH_ISR_ID >= 83) && defined(EE_CAX_83_ISR))
extern void EE_CAX_83_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 84) && (EE_CAX_MAX_ARCH_ISR_ID >= 84) && defined(EE_CAX_84_ISR))
extern void EE_CAX_84_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 85) && (EE_CAX_MAX_ARCH_ISR_ID >= 85) && defined(EE_CAX_85_ISR))
extern void EE_CAX_85_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 86) && (EE_CAX_MAX_ARCH_ISR_ID >= 86) && defined(EE_CAX_86_ISR))
extern void EE_CAX_86_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 87) && (EE_CAX_MAX_ARCH_ISR_ID >= 87) && defined(EE_CAX_87_ISR))
extern void EE_CAX_87_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 88) && (EE_CAX_MAX_ARCH_ISR_ID >= 88) && defined(EE_CAX_88_ISR))
extern void EE_CAX_88_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 89) && (EE_CAX_MAX_ARCH_ISR_ID >= 89) && defined(EE_CAX_89_ISR))
extern void EE_CAX_89_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 90) && (EE_CAX_MAX_ARCH_ISR_ID >= 90) && defined(EE_CAX_90_ISR))
extern void EE_CAX_90_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 91) && (EE_CAX_MAX_ARCH_ISR_ID >= 91) && defined(EE_CAX_91_ISR))
extern void EE_CAX_91_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 92) && (EE_CAX_MAX_ARCH_ISR_ID >= 92) && defined(EE_CAX_92_ISR))
extern void EE_CAX_92_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 93) && (EE_CAX_MAX_ARCH_ISR_ID >= 93) && defined(EE_CAX_93_ISR))
extern void EE_CAX_93_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 94) && (EE_CAX_MAX_ARCH_ISR_ID >= 94) && defined(EE_CAX_94_ISR))
extern void EE_CAX_94_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 95) && (EE_CAX_MAX_ARCH_ISR_ID >= 95) && defined(EE_CAX_95_ISR))
extern void EE_CAX_95_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 96) && (EE_CAX_MAX_ARCH_ISR_ID >= 96) && defined(EE_CAX_96_ISR))
extern void EE_CAX_96_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 97) && (EE_CAX_MAX_ARCH_ISR_ID >= 97) && defined(EE_CAX_97_ISR))
extern void EE_CAX_97_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 98) && (EE_CAX_MAX_ARCH_ISR_ID >= 98) && defined(EE_CAX_98_ISR))
extern void EE_CAX_98_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 99) && (EE_CAX_MAX_ARCH_ISR_ID >= 99) && defined(EE_CAX_99_ISR))
extern void EE_CAX_99_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 100) && (EE_CAX_MAX_ARCH_ISR_ID >= 100) && defined(EE_CAX_100_ISR))
extern void EE_CAX_100_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 101) && (EE_CAX_MAX_ARCH_ISR_ID >= 101) && defined(EE_CAX_101_ISR))
extern void EE_CAX_101_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 102) && (EE_CAX_MAX_ARCH_ISR_ID >= 102) && defined(EE_CAX_102_ISR))
extern void EE_CAX_102_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 103) && (EE_CAX_MAX_ARCH_ISR_ID >= 103) && defined(EE_CAX_103_ISR))
extern void EE_CAX_103_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 104) && (EE_CAX_MAX_ARCH_ISR_ID >= 104) && defined(EE_CAX_104_ISR))
extern void EE_CAX_104_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 105) && (EE_CAX_MAX_ARCH_ISR_ID >= 105) && defined(EE_CAX_105_ISR))
extern void EE_CAX_105_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 106) && (EE_CAX_MAX_ARCH_ISR_ID >= 106) && defined(EE_CAX_106_ISR))
extern void EE_CAX_106_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 107) && (EE_CAX_MAX_ARCH_ISR_ID >= 107) && defined(EE_CAX_107_ISR))
extern void EE_CAX_107_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 108) && (EE_CAX_MAX_ARCH_ISR_ID >= 108) && defined(EE_CAX_108_ISR))
extern void EE_CAX_108_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 109) && (EE_CAX_MAX_ARCH_ISR_ID >= 109) && defined(EE_CAX_109_ISR))
extern void EE_CAX_109_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 110) && (EE_CAX_MAX_ARCH_ISR_ID >= 110) && defined(EE_CAX_110_ISR))
extern void EE_CAX_110_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 111) && (EE_CAX_MAX_ARCH_ISR_ID >= 111) && defined(EE_CAX_111_ISR))
extern void EE_CAX_111_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 112) && (EE_CAX_MAX_ARCH_ISR_ID >= 112) && defined(EE_CAX_112_ISR))
extern void EE_CAX_112_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 113) && (EE_CAX_MAX_ARCH_ISR_ID >= 113) && defined(EE_CAX_113_ISR))
extern void EE_CAX_113_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 114) && (EE_CAX_MAX_ARCH_ISR_ID >= 114) && defined(EE_CAX_114_ISR))
extern void EE_CAX_114_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 115) && (EE_CAX_MAX_ARCH_ISR_ID >= 115) && defined(EE_CAX_115_ISR))
extern void EE_CAX_115_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 116) && (EE_CAX_MAX_ARCH_ISR_ID >= 116) && defined(EE_CAX_116_ISR))
extern void EE_CAX_116_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 117) && (EE_CAX_MAX_ARCH_ISR_ID >= 117) && defined(EE_CAX_117_ISR))
extern void EE_CAX_117_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 118) && (EE_CAX_MAX_ARCH_ISR_ID >= 118) && defined(EE_CAX_118_ISR))
extern void EE_CAX_118_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 119) && (EE_CAX_MAX_ARCH_ISR_ID >= 119) && defined(EE_CAX_119_ISR))
extern void EE_CAX_119_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 120) && (EE_CAX_MAX_ARCH_ISR_ID >= 120) && defined(EE_CAX_120_ISR))
extern void EE_CAX_120_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 121) && (EE_CAX_MAX_ARCH_ISR_ID >= 121) && defined(EE_CAX_121_ISR))
extern void EE_CAX_121_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 122) && (EE_CAX_MAX_ARCH_ISR_ID >= 122) && defined(EE_CAX_122_ISR))
extern void EE_CAX_122_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 123) && (EE_CAX_MAX_ARCH_ISR_ID >= 123) && defined(EE_CAX_123_ISR))
extern void EE_CAX_123_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 124) && (EE_CAX_MAX_ARCH_ISR_ID >= 124) && defined(EE_CAX_124_ISR))
extern void EE_CAX_124_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 125) && (EE_CAX_MAX_ARCH_ISR_ID >= 125) && defined(EE_CAX_125_ISR))
extern void EE_CAX_125_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 126) && (EE_CAX_MAX_ARCH_ISR_ID >= 126) && defined(EE_CAX_126_ISR))
extern void EE_CAX_126_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 127) && (EE_CAX_MAX_ARCH_ISR_ID >= 127) && defined(EE_CAX_127_ISR))
extern void EE_CAX_127_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 128) && (EE_CAX_MAX_ARCH_ISR_ID >= 128) && defined(EE_CAX_128_ISR))
extern void EE_CAX_128_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 129) && (EE_CAX_MAX_ARCH_ISR_ID >= 129) && defined(EE_CAX_129_ISR))
extern void EE_CAX_129_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 130) && (EE_CAX_MAX_ARCH_ISR_ID >= 130) && defined(EE_CAX_130_ISR))
extern void EE_CAX_130_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 131) && (EE_CAX_MAX_ARCH_ISR_ID >= 131) && defined(EE_CAX_131_ISR))
extern void EE_CAX_131_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 132) && (EE_CAX_MAX_ARCH_ISR_ID >= 132) && defined(EE_CAX_132_ISR))
extern void EE_CAX_132_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 133) && (EE_CAX_MAX_ARCH_ISR_ID >= 133) && defined(EE_CAX_133_ISR))
extern void EE_CAX_133_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 134) && (EE_CAX_MAX_ARCH_ISR_ID >= 134) && defined(EE_CAX_134_ISR))
extern void EE_CAX_134_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 135) && (EE_CAX_MAX_ARCH_ISR_ID >= 135) && defined(EE_CAX_135_ISR))
extern void EE_CAX_135_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 136) && (EE_CAX_MAX_ARCH_ISR_ID >= 136) && defined(EE_CAX_136_ISR))
extern void EE_CAX_136_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 137) && (EE_CAX_MAX_ARCH_ISR_ID >= 137) && defined(EE_CAX_137_ISR))
extern void EE_CAX_137_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 138) && (EE_CAX_MAX_ARCH_ISR_ID >= 138) && defined(EE_CAX_138_ISR))
extern void EE_CAX_138_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 139) && (EE_CAX_MAX_ARCH_ISR_ID >= 139) && defined(EE_CAX_139_ISR))
extern void EE_CAX_139_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 140) && (EE_CAX_MAX_ARCH_ISR_ID >= 140) && defined(EE_CAX_140_ISR))
extern void EE_CAX_140_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 141) && (EE_CAX_MAX_ARCH_ISR_ID >= 141) && defined(EE_CAX_141_ISR))
extern void EE_CAX_141_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 142) && (EE_CAX_MAX_ARCH_ISR_ID >= 142) && defined(EE_CAX_142_ISR))
extern void EE_CAX_142_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 143) && (EE_CAX_MAX_ARCH_ISR_ID >= 143) && defined(EE_CAX_143_ISR))
extern void EE_CAX_143_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 144) && (EE_CAX_MAX_ARCH_ISR_ID >= 144) && defined(EE_CAX_144_ISR))
extern void EE_CAX_144_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 145) && (EE_CAX_MAX_ARCH_ISR_ID >= 145) && defined(EE_CAX_145_ISR))
extern void EE_CAX_145_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 146) && (EE_CAX_MAX_ARCH_ISR_ID >= 146) && defined(EE_CAX_146_ISR))
extern void EE_CAX_146_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 147) && (EE_CAX_MAX_ARCH_ISR_ID >= 147) && defined(EE_CAX_147_ISR))
extern void EE_CAX_147_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 148) && (EE_CAX_MAX_ARCH_ISR_ID >= 148) && defined(EE_CAX_148_ISR))
extern void EE_CAX_148_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 149) && (EE_CAX_MAX_ARCH_ISR_ID >= 149) && defined(EE_CAX_149_ISR))
extern void EE_CAX_149_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 150) && (EE_CAX_MAX_ARCH_ISR_ID >= 150) && defined(EE_CAX_150_ISR))
extern void EE_CAX_150_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 151) && (EE_CAX_MAX_ARCH_ISR_ID >= 151) && defined(EE_CAX_151_ISR))
extern void EE_CAX_151_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 152) && (EE_CAX_MAX_ARCH_ISR_ID >= 152) && defined(EE_CAX_152_ISR))
extern void EE_CAX_152_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 153) && (EE_CAX_MAX_ARCH_ISR_ID >= 153) && defined(EE_CAX_153_ISR))
extern void EE_CAX_153_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 154) && (EE_CAX_MAX_ARCH_ISR_ID >= 154) && defined(EE_CAX_154_ISR))
extern void EE_CAX_154_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 155) && (EE_CAX_MAX_ARCH_ISR_ID >= 155) && defined(EE_CAX_155_ISR))
extern void EE_CAX_155_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 156) && (EE_CAX_MAX_ARCH_ISR_ID >= 156) && defined(EE_CAX_156_ISR))
extern void EE_CAX_156_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 157) && (EE_CAX_MAX_ARCH_ISR_ID >= 157) && defined(EE_CAX_157_ISR))
extern void EE_CAX_157_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 158) && (EE_CAX_MAX_ARCH_ISR_ID >= 158) && defined(EE_CAX_158_ISR))
extern void EE_CAX_158_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 159) && (EE_CAX_MAX_ARCH_ISR_ID >= 159) && defined(EE_CAX_159_ISR))
extern void EE_CAX_159_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 160) && (EE_CAX_MAX_ARCH_ISR_ID >= 160) && defined(EE_CAX_160_ISR))
extern void EE_CAX_160_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 161) && (EE_CAX_MAX_ARCH_ISR_ID >= 161) && defined(EE_CAX_161_ISR))
extern void EE_CAX_161_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 162) && (EE_CAX_MAX_ARCH_ISR_ID >= 162) && defined(EE_CAX_162_ISR))
extern void EE_CAX_162_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 163) && (EE_CAX_MAX_ARCH_ISR_ID >= 163) && defined(EE_CAX_163_ISR))
extern void EE_CAX_163_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 164) && (EE_CAX_MAX_ARCH_ISR_ID >= 164) && defined(EE_CAX_164_ISR))
extern void EE_CAX_164_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 165) && (EE_CAX_MAX_ARCH_ISR_ID >= 165) && defined(EE_CAX_165_ISR))
extern void EE_CAX_165_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 166) && (EE_CAX_MAX_ARCH_ISR_ID >= 166) && defined(EE_CAX_166_ISR))
extern void EE_CAX_166_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 167) && (EE_CAX_MAX_ARCH_ISR_ID >= 167) && defined(EE_CAX_167_ISR))
extern void EE_CAX_167_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 168) && (EE_CAX_MAX_ARCH_ISR_ID >= 168) && defined(EE_CAX_168_ISR))
extern void EE_CAX_168_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 169) && (EE_CAX_MAX_ARCH_ISR_ID >= 169) && defined(EE_CAX_169_ISR))
extern void EE_CAX_169_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 170) && (EE_CAX_MAX_ARCH_ISR_ID >= 170) && defined(EE_CAX_170_ISR))
extern void EE_CAX_170_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 171) && (EE_CAX_MAX_ARCH_ISR_ID >= 171) && defined(EE_CAX_171_ISR))
extern void EE_CAX_171_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 172) && (EE_CAX_MAX_ARCH_ISR_ID >= 172) && defined(EE_CAX_172_ISR))
extern void EE_CAX_172_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 173) && (EE_CAX_MAX_ARCH_ISR_ID >= 173) && defined(EE_CAX_173_ISR))
extern void EE_CAX_173_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 174) && (EE_CAX_MAX_ARCH_ISR_ID >= 174) && defined(EE_CAX_174_ISR))
extern void EE_CAX_174_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 175) && (EE_CAX_MAX_ARCH_ISR_ID >= 175) && defined(EE_CAX_175_ISR))
extern void EE_CAX_175_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 176) && (EE_CAX_MAX_ARCH_ISR_ID >= 176) && defined(EE_CAX_176_ISR))
extern void EE_CAX_176_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 177) && (EE_CAX_MAX_ARCH_ISR_ID >= 177) && defined(EE_CAX_177_ISR))
extern void EE_CAX_177_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 178) && (EE_CAX_MAX_ARCH_ISR_ID >= 178) && defined(EE_CAX_178_ISR))
extern void EE_CAX_178_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 179) && (EE_CAX_MAX_ARCH_ISR_ID >= 179) && defined(EE_CAX_179_ISR))
extern void EE_CAX_179_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 180) && (EE_CAX_MAX_ARCH_ISR_ID >= 180) && defined(EE_CAX_180_ISR))
extern void EE_CAX_180_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 181) && (EE_CAX_MAX_ARCH_ISR_ID >= 181) && defined(EE_CAX_181_ISR))
extern void EE_CAX_181_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 182) && (EE_CAX_MAX_ARCH_ISR_ID >= 182) && defined(EE_CAX_182_ISR))
extern void EE_CAX_182_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 183) && (EE_CAX_MAX_ARCH_ISR_ID >= 183) && defined(EE_CAX_183_ISR))
extern void EE_CAX_183_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 184) && (EE_CAX_MAX_ARCH_ISR_ID >= 184) && defined(EE_CAX_184_ISR))
extern void EE_CAX_184_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 185) && (EE_CAX_MAX_ARCH_ISR_ID >= 185) && defined(EE_CAX_185_ISR))
extern void EE_CAX_185_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 186) && (EE_CAX_MAX_ARCH_ISR_ID >= 186) && defined(EE_CAX_186_ISR))
extern void EE_CAX_186_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 187) && (EE_CAX_MAX_ARCH_ISR_ID >= 187) && defined(EE_CAX_187_ISR))
extern void EE_CAX_187_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 188) && (EE_CAX_MAX_ARCH_ISR_ID >= 188) && defined(EE_CAX_188_ISR))
extern void EE_CAX_188_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 189) && (EE_CAX_MAX_ARCH_ISR_ID >= 189) && defined(EE_CAX_189_ISR))
extern void EE_CAX_189_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 190) && (EE_CAX_MAX_ARCH_ISR_ID >= 190) && defined(EE_CAX_190_ISR))
extern void EE_CAX_190_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 191) && (EE_CAX_MAX_ARCH_ISR_ID >= 191) && defined(EE_CAX_191_ISR))
extern void EE_CAX_191_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 192) && (EE_CAX_MAX_ARCH_ISR_ID >= 192) && defined(EE_CAX_192_ISR))
extern void EE_CAX_192_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 193) && (EE_CAX_MAX_ARCH_ISR_ID >= 193) && defined(EE_CAX_193_ISR))
extern void EE_CAX_193_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 194) && (EE_CAX_MAX_ARCH_ISR_ID >= 194) && defined(EE_CAX_194_ISR))
extern void EE_CAX_194_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 195) && (EE_CAX_MAX_ARCH_ISR_ID >= 195) && defined(EE_CAX_195_ISR))
extern void EE_CAX_195_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 196) && (EE_CAX_MAX_ARCH_ISR_ID >= 196) && defined(EE_CAX_196_ISR))
extern void EE_CAX_196_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 197) && (EE_CAX_MAX_ARCH_ISR_ID >= 197) && defined(EE_CAX_197_ISR))
extern void EE_CAX_197_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 198) && (EE_CAX_MAX_ARCH_ISR_ID >= 198) && defined(EE_CAX_198_ISR))
extern void EE_CAX_198_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 199) && (EE_CAX_MAX_ARCH_ISR_ID >= 199) && defined(EE_CAX_199_ISR))
extern void EE_CAX_199_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 200) && (EE_CAX_MAX_ARCH_ISR_ID >= 200) && defined(EE_CAX_200_ISR))
extern void EE_CAX_200_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 201) && (EE_CAX_MAX_ARCH_ISR_ID >= 201) && defined(EE_CAX_201_ISR))
extern void EE_CAX_201_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 202) && (EE_CAX_MAX_ARCH_ISR_ID >= 202) && defined(EE_CAX_202_ISR))
extern void EE_CAX_202_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 203) && (EE_CAX_MAX_ARCH_ISR_ID >= 203) && defined(EE_CAX_203_ISR))
extern void EE_CAX_203_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 204) && (EE_CAX_MAX_ARCH_ISR_ID >= 204) && defined(EE_CAX_204_ISR))
extern void EE_CAX_204_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 205) && (EE_CAX_MAX_ARCH_ISR_ID >= 205) && defined(EE_CAX_205_ISR))
extern void EE_CAX_205_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 206) && (EE_CAX_MAX_ARCH_ISR_ID >= 206) && defined(EE_CAX_206_ISR))
extern void EE_CAX_206_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 207) && (EE_CAX_MAX_ARCH_ISR_ID >= 207) && defined(EE_CAX_207_ISR))
extern void EE_CAX_207_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 208) && (EE_CAX_MAX_ARCH_ISR_ID >= 208) && defined(EE_CAX_208_ISR))
extern void EE_CAX_208_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 209) && (EE_CAX_MAX_ARCH_ISR_ID >= 209) && defined(EE_CAX_209_ISR))
extern void EE_CAX_209_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 210) && (EE_CAX_MAX_ARCH_ISR_ID >= 210) && defined(EE_CAX_210_ISR))
extern void EE_CAX_210_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 211) && (EE_CAX_MAX_ARCH_ISR_ID >= 211) && defined(EE_CAX_211_ISR))
extern void EE_CAX_211_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 212) && (EE_CAX_MAX_ARCH_ISR_ID >= 212) && defined(EE_CAX_212_ISR))
extern void EE_CAX_212_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 213) && (EE_CAX_MAX_ARCH_ISR_ID >= 213) && defined(EE_CAX_213_ISR))
extern void EE_CAX_213_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 214) && (EE_CAX_MAX_ARCH_ISR_ID >= 214) && defined(EE_CAX_214_ISR))
extern void EE_CAX_214_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 215) && (EE_CAX_MAX_ARCH_ISR_ID >= 215) && defined(EE_CAX_215_ISR))
extern void EE_CAX_215_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 216) && (EE_CAX_MAX_ARCH_ISR_ID >= 216) && defined(EE_CAX_216_ISR))
extern void EE_CAX_216_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 217) && (EE_CAX_MAX_ARCH_ISR_ID >= 217) && defined(EE_CAX_217_ISR))
extern void EE_CAX_217_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 218) && (EE_CAX_MAX_ARCH_ISR_ID >= 218) && defined(EE_CAX_218_ISR))
extern void EE_CAX_218_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 219) && (EE_CAX_MAX_ARCH_ISR_ID >= 219) && defined(EE_CAX_219_ISR))
extern void EE_CAX_219_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 220) && (EE_CAX_MAX_ARCH_ISR_ID >= 220) && defined(EE_CAX_220_ISR))
extern void EE_CAX_220_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 221) && (EE_CAX_MAX_ARCH_ISR_ID >= 221) && defined(EE_CAX_221_ISR))
extern void EE_CAX_221_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 222) && (EE_CAX_MAX_ARCH_ISR_ID >= 222) && defined(EE_CAX_222_ISR))
extern void EE_CAX_222_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 223) && (EE_CAX_MAX_ARCH_ISR_ID >= 223) && defined(EE_CAX_223_ISR))
extern void EE_CAX_223_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 224) && (EE_CAX_MAX_ARCH_ISR_ID >= 224) && defined(EE_CAX_224_ISR))
extern void EE_CAX_224_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 225) && (EE_CAX_MAX_ARCH_ISR_ID >= 225) && defined(EE_CAX_225_ISR))
extern void EE_CAX_225_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 226) && (EE_CAX_MAX_ARCH_ISR_ID >= 226) && defined(EE_CAX_226_ISR))
extern void EE_CAX_226_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 227) && (EE_CAX_MAX_ARCH_ISR_ID >= 227) && defined(EE_CAX_227_ISR))
extern void EE_CAX_227_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 228) && (EE_CAX_MAX_ARCH_ISR_ID >= 228) && defined(EE_CAX_228_ISR))
extern void EE_CAX_228_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 229) && (EE_CAX_MAX_ARCH_ISR_ID >= 229) && defined(EE_CAX_229_ISR))
extern void EE_CAX_229_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 230) && (EE_CAX_MAX_ARCH_ISR_ID >= 230) && defined(EE_CAX_230_ISR))
extern void EE_CAX_230_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 231) && (EE_CAX_MAX_ARCH_ISR_ID >= 231) && defined(EE_CAX_231_ISR))
extern void EE_CAX_231_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 232) && (EE_CAX_MAX_ARCH_ISR_ID >= 232) && defined(EE_CAX_232_ISR))
extern void EE_CAX_232_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 233) && (EE_CAX_MAX_ARCH_ISR_ID >= 233) && defined(EE_CAX_233_ISR))
extern void EE_CAX_233_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 234) && (EE_CAX_MAX_ARCH_ISR_ID >= 234) && defined(EE_CAX_234_ISR))
extern void EE_CAX_234_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 235) && (EE_CAX_MAX_ARCH_ISR_ID >= 235) && defined(EE_CAX_235_ISR))
extern void EE_CAX_235_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 236) && (EE_CAX_MAX_ARCH_ISR_ID >= 236) && defined(EE_CAX_236_ISR))
extern void EE_CAX_236_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 237) && (EE_CAX_MAX_ARCH_ISR_ID >= 237) && defined(EE_CAX_237_ISR))
extern void EE_CAX_237_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 238) && (EE_CAX_MAX_ARCH_ISR_ID >= 238) && defined(EE_CAX_238_ISR))
extern void EE_CAX_238_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 239) && (EE_CAX_MAX_ARCH_ISR_ID >= 239) && defined(EE_CAX_239_ISR))
extern void EE_CAX_239_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 240) && (EE_CAX_MAX_ARCH_ISR_ID >= 240) && defined(EE_CAX_240_ISR))
extern void EE_CAX_240_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 241) && (EE_CAX_MAX_ARCH_ISR_ID >= 241) && defined(EE_CAX_241_ISR))
extern void EE_CAX_241_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 242) && (EE_CAX_MAX_ARCH_ISR_ID >= 242) && defined(EE_CAX_242_ISR))
extern void EE_CAX_242_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 243) && (EE_CAX_MAX_ARCH_ISR_ID >= 243) && defined(EE_CAX_243_ISR))
extern void EE_CAX_243_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 244) && (EE_CAX_MAX_ARCH_ISR_ID >= 244) && defined(EE_CAX_244_ISR))
extern void EE_CAX_244_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 245) && (EE_CAX_MAX_ARCH_ISR_ID >= 245) && defined(EE_CAX_245_ISR))
extern void EE_CAX_245_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 246) && (EE_CAX_MAX_ARCH_ISR_ID >= 246) && defined(EE_CAX_246_ISR))
extern void EE_CAX_246_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 247) && (EE_CAX_MAX_ARCH_ISR_ID >= 247) && defined(EE_CAX_247_ISR))
extern void EE_CAX_247_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 248) && (EE_CAX_MAX_ARCH_ISR_ID >= 248) && defined(EE_CAX_248_ISR))
extern void EE_CAX_248_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 249) && (EE_CAX_MAX_ARCH_ISR_ID >= 249) && defined(EE_CAX_249_ISR))
extern void EE_CAX_249_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 250) && (EE_CAX_MAX_ARCH_ISR_ID >= 250) && defined(EE_CAX_250_ISR))
extern void EE_CAX_250_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 251) && (EE_CAX_MAX_ARCH_ISR_ID >= 251) && defined(EE_CAX_251_ISR))
extern void EE_CAX_251_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 252) && (EE_CAX_MAX_ARCH_ISR_ID >= 252) && defined(EE_CAX_252_ISR))
extern void EE_CAX_252_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 253) && (EE_CAX_MAX_ARCH_ISR_ID >= 253) && defined(EE_CAX_253_ISR))
extern void EE_CAX_253_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 254) && (EE_CAX_MAX_ARCH_ISR_ID >= 254) && defined(EE_CAX_254_ISR))
extern void EE_CAX_254_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 255) && (EE_CAX_MAX_ARCH_ISR_ID >= 255) && defined(EE_CAX_255_ISR))
extern void EE_CAX_255_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 256) && (EE_CAX_MAX_ARCH_ISR_ID >= 256) && defined(EE_CAX_256_ISR))
extern void EE_CAX_256_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 257) && (EE_CAX_MAX_ARCH_ISR_ID >= 257) && defined(EE_CAX_257_ISR))
extern void EE_CAX_257_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 258) && (EE_CAX_MAX_ARCH_ISR_ID >= 258) && defined(EE_CAX_258_ISR))
extern void EE_CAX_258_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 259) && (EE_CAX_MAX_ARCH_ISR_ID >= 259) && defined(EE_CAX_259_ISR))
extern void EE_CAX_259_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 260) && (EE_CAX_MAX_ARCH_ISR_ID >= 260) && defined(EE_CAX_260_ISR))
extern void EE_CAX_260_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 261) && (EE_CAX_MAX_ARCH_ISR_ID >= 261) && defined(EE_CAX_261_ISR))
extern void EE_CAX_261_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 262) && (EE_CAX_MAX_ARCH_ISR_ID >= 262) && defined(EE_CAX_262_ISR))
extern void EE_CAX_262_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 263) && (EE_CAX_MAX_ARCH_ISR_ID >= 263) && defined(EE_CAX_263_ISR))
extern void EE_CAX_263_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 264) && (EE_CAX_MAX_ARCH_ISR_ID >= 264) && defined(EE_CAX_264_ISR))
extern void EE_CAX_264_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 265) && (EE_CAX_MAX_ARCH_ISR_ID >= 265) && defined(EE_CAX_265_ISR))
extern void EE_CAX_265_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 266) && (EE_CAX_MAX_ARCH_ISR_ID >= 266) && defined(EE_CAX_266_ISR))
extern void EE_CAX_266_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 267) && (EE_CAX_MAX_ARCH_ISR_ID >= 267) && defined(EE_CAX_267_ISR))
extern void EE_CAX_267_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 268) && (EE_CAX_MAX_ARCH_ISR_ID >= 268) && defined(EE_CAX_268_ISR))
extern void EE_CAX_268_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 269) && (EE_CAX_MAX_ARCH_ISR_ID >= 269) && defined(EE_CAX_269_ISR))
extern void EE_CAX_269_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 270) && (EE_CAX_MAX_ARCH_ISR_ID >= 270) && defined(EE_CAX_270_ISR))
extern void EE_CAX_270_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 271) && (EE_CAX_MAX_ARCH_ISR_ID >= 271) && defined(EE_CAX_271_ISR))
extern void EE_CAX_271_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 272) && (EE_CAX_MAX_ARCH_ISR_ID >= 272) && defined(EE_CAX_272_ISR))
extern void EE_CAX_272_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 273) && (EE_CAX_MAX_ARCH_ISR_ID >= 273) && defined(EE_CAX_273_ISR))
extern void EE_CAX_273_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 274) && (EE_CAX_MAX_ARCH_ISR_ID >= 274) && defined(EE_CAX_274_ISR))
extern void EE_CAX_274_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 275) && (EE_CAX_MAX_ARCH_ISR_ID >= 275) && defined(EE_CAX_275_ISR))
extern void EE_CAX_275_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 276) && (EE_CAX_MAX_ARCH_ISR_ID >= 276) && defined(EE_CAX_276_ISR))
extern void EE_CAX_276_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 277) && (EE_CAX_MAX_ARCH_ISR_ID >= 277) && defined(EE_CAX_277_ISR))
extern void EE_CAX_277_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 278) && (EE_CAX_MAX_ARCH_ISR_ID >= 278) && defined(EE_CAX_278_ISR))
extern void EE_CAX_278_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 279) && (EE_CAX_MAX_ARCH_ISR_ID >= 279) && defined(EE_CAX_279_ISR))
extern void EE_CAX_279_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 280) && (EE_CAX_MAX_ARCH_ISR_ID >= 280) && defined(EE_CAX_280_ISR))
extern void EE_CAX_280_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 281) && (EE_CAX_MAX_ARCH_ISR_ID >= 281) && defined(EE_CAX_281_ISR))
extern void EE_CAX_281_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 282) && (EE_CAX_MAX_ARCH_ISR_ID >= 282) && defined(EE_CAX_282_ISR))
extern void EE_CAX_282_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 283) && (EE_CAX_MAX_ARCH_ISR_ID >= 283) && defined(EE_CAX_283_ISR))
extern void EE_CAX_283_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 284) && (EE_CAX_MAX_ARCH_ISR_ID >= 284) && defined(EE_CAX_284_ISR))
extern void EE_CAX_284_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 285) && (EE_CAX_MAX_ARCH_ISR_ID >= 285) && defined(EE_CAX_285_ISR))
extern void EE_CAX_285_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 286) && (EE_CAX_MAX_ARCH_ISR_ID >= 286) && defined(EE_CAX_286_ISR))
extern void EE_CAX_286_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 287) && (EE_CAX_MAX_ARCH_ISR_ID >= 287) && defined(EE_CAX_287_ISR))
extern void EE_CAX_287_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 288) && (EE_CAX_MAX_ARCH_ISR_ID >= 288) && defined(EE_CAX_288_ISR))
extern void EE_CAX_288_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 289) && (EE_CAX_MAX_ARCH_ISR_ID >= 289) && defined(EE_CAX_289_ISR))
extern void EE_CAX_289_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 290) && (EE_CAX_MAX_ARCH_ISR_ID >= 290) && defined(EE_CAX_290_ISR))
extern void EE_CAX_290_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 291) && (EE_CAX_MAX_ARCH_ISR_ID >= 291) && defined(EE_CAX_291_ISR))
extern void EE_CAX_291_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 292) && (EE_CAX_MAX_ARCH_ISR_ID >= 292) && defined(EE_CAX_292_ISR))
extern void EE_CAX_292_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 293) && (EE_CAX_MAX_ARCH_ISR_ID >= 293) && defined(EE_CAX_293_ISR))
extern void EE_CAX_293_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 294) && (EE_CAX_MAX_ARCH_ISR_ID >= 294) && defined(EE_CAX_294_ISR))
extern void EE_CAX_294_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 295) && (EE_CAX_MAX_ARCH_ISR_ID >= 295) && defined(EE_CAX_295_ISR))
extern void EE_CAX_295_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 296) && (EE_CAX_MAX_ARCH_ISR_ID >= 296) && defined(EE_CAX_296_ISR))
extern void EE_CAX_296_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 297) && (EE_CAX_MAX_ARCH_ISR_ID >= 297) && defined(EE_CAX_297_ISR))
extern void EE_CAX_297_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 298) && (EE_CAX_MAX_ARCH_ISR_ID >= 298) && defined(EE_CAX_298_ISR))
extern void EE_CAX_298_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 299) && (EE_CAX_MAX_ARCH_ISR_ID >= 299) && defined(EE_CAX_299_ISR))
extern void EE_CAX_299_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 300) && (EE_CAX_MAX_ARCH_ISR_ID >= 300) && defined(EE_CAX_300_ISR))
extern void EE_CAX_300_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 301) && (EE_CAX_MAX_ARCH_ISR_ID >= 301) && defined(EE_CAX_301_ISR))
extern void EE_CAX_301_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 302) && (EE_CAX_MAX_ARCH_ISR_ID >= 302) && defined(EE_CAX_302_ISR))
extern void EE_CAX_302_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 303) && (EE_CAX_MAX_ARCH_ISR_ID >= 303) && defined(EE_CAX_303_ISR))
extern void EE_CAX_303_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 304) && (EE_CAX_MAX_ARCH_ISR_ID >= 304) && defined(EE_CAX_304_ISR))
extern void EE_CAX_304_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 305) && (EE_CAX_MAX_ARCH_ISR_ID >= 305) && defined(EE_CAX_305_ISR))
extern void EE_CAX_305_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 306) && (EE_CAX_MAX_ARCH_ISR_ID >= 306) && defined(EE_CAX_306_ISR))
extern void EE_CAX_306_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 307) && (EE_CAX_MAX_ARCH_ISR_ID >= 307) && defined(EE_CAX_307_ISR))
extern void EE_CAX_307_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 308) && (EE_CAX_MAX_ARCH_ISR_ID >= 308) && defined(EE_CAX_308_ISR))
extern void EE_CAX_308_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 309) && (EE_CAX_MAX_ARCH_ISR_ID >= 309) && defined(EE_CAX_309_ISR))
extern void EE_CAX_309_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 310) && (EE_CAX_MAX_ARCH_ISR_ID >= 310) && defined(EE_CAX_310_ISR))
extern void EE_CAX_310_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 311) && (EE_CAX_MAX_ARCH_ISR_ID >= 311) && defined(EE_CAX_311_ISR))
extern void EE_CAX_311_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 312) && (EE_CAX_MAX_ARCH_ISR_ID >= 312) && defined(EE_CAX_312_ISR))
extern void EE_CAX_312_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 313) && (EE_CAX_MAX_ARCH_ISR_ID >= 313) && defined(EE_CAX_313_ISR))
extern void EE_CAX_313_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 314) && (EE_CAX_MAX_ARCH_ISR_ID >= 314) && defined(EE_CAX_314_ISR))
extern void EE_CAX_314_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 315) && (EE_CAX_MAX_ARCH_ISR_ID >= 315) && defined(EE_CAX_315_ISR))
extern void EE_CAX_315_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 316) && (EE_CAX_MAX_ARCH_ISR_ID >= 316) && defined(EE_CAX_316_ISR))
extern void EE_CAX_316_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 317) && (EE_CAX_MAX_ARCH_ISR_ID >= 317) && defined(EE_CAX_317_ISR))
extern void EE_CAX_317_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 318) && (EE_CAX_MAX_ARCH_ISR_ID >= 318) && defined(EE_CAX_318_ISR))
extern void EE_CAX_318_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 319) && (EE_CAX_MAX_ARCH_ISR_ID >= 319) && defined(EE_CAX_319_ISR))
extern void EE_CAX_319_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 320) && (EE_CAX_MAX_ARCH_ISR_ID >= 320) && defined(EE_CAX_320_ISR))
extern void EE_CAX_320_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 321) && (EE_CAX_MAX_ARCH_ISR_ID >= 321) && defined(EE_CAX_321_ISR))
extern void EE_CAX_321_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 322) && (EE_CAX_MAX_ARCH_ISR_ID >= 322) && defined(EE_CAX_322_ISR))
extern void EE_CAX_322_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 323) && (EE_CAX_MAX_ARCH_ISR_ID >= 323) && defined(EE_CAX_323_ISR))
extern void EE_CAX_323_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 324) && (EE_CAX_MAX_ARCH_ISR_ID >= 324) && defined(EE_CAX_324_ISR))
extern void EE_CAX_324_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 325) && (EE_CAX_MAX_ARCH_ISR_ID >= 325) && defined(EE_CAX_325_ISR))
extern void EE_CAX_325_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 326) && (EE_CAX_MAX_ARCH_ISR_ID >= 326) && defined(EE_CAX_326_ISR))
extern void EE_CAX_326_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 327) && (EE_CAX_MAX_ARCH_ISR_ID >= 327) && defined(EE_CAX_327_ISR))
extern void EE_CAX_327_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 328) && (EE_CAX_MAX_ARCH_ISR_ID >= 328) && defined(EE_CAX_328_ISR))
extern void EE_CAX_328_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 329) && (EE_CAX_MAX_ARCH_ISR_ID >= 329) && defined(EE_CAX_329_ISR))
extern void EE_CAX_329_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 330) && (EE_CAX_MAX_ARCH_ISR_ID >= 330) && defined(EE_CAX_330_ISR))
extern void EE_CAX_330_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 331) && (EE_CAX_MAX_ARCH_ISR_ID >= 331) && defined(EE_CAX_331_ISR))
extern void EE_CAX_331_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 332) && (EE_CAX_MAX_ARCH_ISR_ID >= 332) && defined(EE_CAX_332_ISR))
extern void EE_CAX_332_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 333) && (EE_CAX_MAX_ARCH_ISR_ID >= 333) && defined(EE_CAX_333_ISR))
extern void EE_CAX_333_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 334) && (EE_CAX_MAX_ARCH_ISR_ID >= 334) && defined(EE_CAX_334_ISR))
extern void EE_CAX_334_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 335) && (EE_CAX_MAX_ARCH_ISR_ID >= 335) && defined(EE_CAX_335_ISR))
extern void EE_CAX_335_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 336) && (EE_CAX_MAX_ARCH_ISR_ID >= 336) && defined(EE_CAX_336_ISR))
extern void EE_CAX_336_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 337) && (EE_CAX_MAX_ARCH_ISR_ID >= 337) && defined(EE_CAX_337_ISR))
extern void EE_CAX_337_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 338) && (EE_CAX_MAX_ARCH_ISR_ID >= 338) && defined(EE_CAX_338_ISR))
extern void EE_CAX_338_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 339) && (EE_CAX_MAX_ARCH_ISR_ID >= 339) && defined(EE_CAX_339_ISR))
extern void EE_CAX_339_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 340) && (EE_CAX_MAX_ARCH_ISR_ID >= 340) && defined(EE_CAX_340_ISR))
extern void EE_CAX_340_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 341) && (EE_CAX_MAX_ARCH_ISR_ID >= 341) && defined(EE_CAX_341_ISR))
extern void EE_CAX_341_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 342) && (EE_CAX_MAX_ARCH_ISR_ID >= 342) && defined(EE_CAX_342_ISR))
extern void EE_CAX_342_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 343) && (EE_CAX_MAX_ARCH_ISR_ID >= 343) && defined(EE_CAX_343_ISR))
extern void EE_CAX_343_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 344) && (EE_CAX_MAX_ARCH_ISR_ID >= 344) && defined(EE_CAX_344_ISR))
extern void EE_CAX_344_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 345) && (EE_CAX_MAX_ARCH_ISR_ID >= 345) && defined(EE_CAX_345_ISR))
extern void EE_CAX_345_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 346) && (EE_CAX_MAX_ARCH_ISR_ID >= 346) && defined(EE_CAX_346_ISR))
extern void EE_CAX_346_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 347) && (EE_CAX_MAX_ARCH_ISR_ID >= 347) && defined(EE_CAX_347_ISR))
extern void EE_CAX_347_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 348) && (EE_CAX_MAX_ARCH_ISR_ID >= 348) && defined(EE_CAX_348_ISR))
extern void EE_CAX_348_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 349) && (EE_CAX_MAX_ARCH_ISR_ID >= 349) && defined(EE_CAX_349_ISR))
extern void EE_CAX_349_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 350) && (EE_CAX_MAX_ARCH_ISR_ID >= 350) && defined(EE_CAX_350_ISR))
extern void EE_CAX_350_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 351) && (EE_CAX_MAX_ARCH_ISR_ID >= 351) && defined(EE_CAX_351_ISR))
extern void EE_CAX_351_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 352) && (EE_CAX_MAX_ARCH_ISR_ID >= 352) && defined(EE_CAX_352_ISR))
extern void EE_CAX_352_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 353) && (EE_CAX_MAX_ARCH_ISR_ID >= 353) && defined(EE_CAX_353_ISR))
extern void EE_CAX_353_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 354) && (EE_CAX_MAX_ARCH_ISR_ID >= 354) && defined(EE_CAX_354_ISR))
extern void EE_CAX_354_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 355) && (EE_CAX_MAX_ARCH_ISR_ID >= 355) && defined(EE_CAX_355_ISR))
extern void EE_CAX_355_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 356) && (EE_CAX_MAX_ARCH_ISR_ID >= 356) && defined(EE_CAX_356_ISR))
extern void EE_CAX_356_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 357) && (EE_CAX_MAX_ARCH_ISR_ID >= 357) && defined(EE_CAX_357_ISR))
extern void EE_CAX_357_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 358) && (EE_CAX_MAX_ARCH_ISR_ID >= 358) && defined(EE_CAX_358_ISR))
extern void EE_CAX_358_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 359) && (EE_CAX_MAX_ARCH_ISR_ID >= 359) && defined(EE_CAX_359_ISR))
extern void EE_CAX_359_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 360) && (EE_CAX_MAX_ARCH_ISR_ID >= 360) && defined(EE_CAX_360_ISR))
extern void EE_CAX_360_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 361) && (EE_CAX_MAX_ARCH_ISR_ID >= 361) && defined(EE_CAX_361_ISR))
extern void EE_CAX_361_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 362) && (EE_CAX_MAX_ARCH_ISR_ID >= 362) && defined(EE_CAX_362_ISR))
extern void EE_CAX_362_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 363) && (EE_CAX_MAX_ARCH_ISR_ID >= 363) && defined(EE_CAX_363_ISR))
extern void EE_CAX_363_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 364) && (EE_CAX_MAX_ARCH_ISR_ID >= 364) && defined(EE_CAX_364_ISR))
extern void EE_CAX_364_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 365) && (EE_CAX_MAX_ARCH_ISR_ID >= 365) && defined(EE_CAX_365_ISR))
extern void EE_CAX_365_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 366) && (EE_CAX_MAX_ARCH_ISR_ID >= 366) && defined(EE_CAX_366_ISR))
extern void EE_CAX_366_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 367) && (EE_CAX_MAX_ARCH_ISR_ID >= 367) && defined(EE_CAX_367_ISR))
extern void EE_CAX_367_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 368) && (EE_CAX_MAX_ARCH_ISR_ID >= 368) && defined(EE_CAX_368_ISR))
extern void EE_CAX_368_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 369) && (EE_CAX_MAX_ARCH_ISR_ID >= 369) && defined(EE_CAX_369_ISR))
extern void EE_CAX_369_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 370) && (EE_CAX_MAX_ARCH_ISR_ID >= 370) && defined(EE_CAX_370_ISR))
extern void EE_CAX_370_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 371) && (EE_CAX_MAX_ARCH_ISR_ID >= 371) && defined(EE_CAX_371_ISR))
extern void EE_CAX_371_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 372) && (EE_CAX_MAX_ARCH_ISR_ID >= 372) && defined(EE_CAX_372_ISR))
extern void EE_CAX_372_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 373) && (EE_CAX_MAX_ARCH_ISR_ID >= 373) && defined(EE_CAX_373_ISR))
extern void EE_CAX_373_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 374) && (EE_CAX_MAX_ARCH_ISR_ID >= 374) && defined(EE_CAX_374_ISR))
extern void EE_CAX_374_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 375) && (EE_CAX_MAX_ARCH_ISR_ID >= 375) && defined(EE_CAX_375_ISR))
extern void EE_CAX_375_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 376) && (EE_CAX_MAX_ARCH_ISR_ID >= 376) && defined(EE_CAX_376_ISR))
extern void EE_CAX_376_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 377) && (EE_CAX_MAX_ARCH_ISR_ID >= 377) && defined(EE_CAX_377_ISR))
extern void EE_CAX_377_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 378) && (EE_CAX_MAX_ARCH_ISR_ID >= 378) && defined(EE_CAX_378_ISR))
extern void EE_CAX_378_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 379) && (EE_CAX_MAX_ARCH_ISR_ID >= 379) && defined(EE_CAX_379_ISR))
extern void EE_CAX_379_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 380) && (EE_CAX_MAX_ARCH_ISR_ID >= 380) && defined(EE_CAX_380_ISR))
extern void EE_CAX_380_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 381) && (EE_CAX_MAX_ARCH_ISR_ID >= 381) && defined(EE_CAX_381_ISR))
extern void EE_CAX_381_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 382) && (EE_CAX_MAX_ARCH_ISR_ID >= 382) && defined(EE_CAX_382_ISR))
extern void EE_CAX_382_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 383) && (EE_CAX_MAX_ARCH_ISR_ID >= 383) && defined(EE_CAX_383_ISR))
extern void EE_CAX_383_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 384) && (EE_CAX_MAX_ARCH_ISR_ID >= 384) && defined(EE_CAX_384_ISR))
extern void EE_CAX_384_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 385) && (EE_CAX_MAX_ARCH_ISR_ID >= 385) && defined(EE_CAX_385_ISR))
extern void EE_CAX_385_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 386) && (EE_CAX_MAX_ARCH_ISR_ID >= 386) && defined(EE_CAX_386_ISR))
extern void EE_CAX_386_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 387) && (EE_CAX_MAX_ARCH_ISR_ID >= 387) && defined(EE_CAX_387_ISR))
extern void EE_CAX_387_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 388) && (EE_CAX_MAX_ARCH_ISR_ID >= 388) && defined(EE_CAX_388_ISR))
extern void EE_CAX_388_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 389) && (EE_CAX_MAX_ARCH_ISR_ID >= 389) && defined(EE_CAX_389_ISR))
extern void EE_CAX_389_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 390) && (EE_CAX_MAX_ARCH_ISR_ID >= 390) && defined(EE_CAX_390_ISR))
extern void EE_CAX_390_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 391) && (EE_CAX_MAX_ARCH_ISR_ID >= 391) && defined(EE_CAX_391_ISR))
extern void EE_CAX_391_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 392) && (EE_CAX_MAX_ARCH_ISR_ID >= 392) && defined(EE_CAX_392_ISR))
extern void EE_CAX_392_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 393) && (EE_CAX_MAX_ARCH_ISR_ID >= 393) && defined(EE_CAX_393_ISR))
extern void EE_CAX_393_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 394) && (EE_CAX_MAX_ARCH_ISR_ID >= 394) && defined(EE_CAX_394_ISR))
extern void EE_CAX_394_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 395) && (EE_CAX_MAX_ARCH_ISR_ID >= 395) && defined(EE_CAX_395_ISR))
extern void EE_CAX_395_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 396) && (EE_CAX_MAX_ARCH_ISR_ID >= 396) && defined(EE_CAX_396_ISR))
extern void EE_CAX_396_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 397) && (EE_CAX_MAX_ARCH_ISR_ID >= 397) && defined(EE_CAX_397_ISR))
extern void EE_CAX_397_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 398) && (EE_CAX_MAX_ARCH_ISR_ID >= 398) && defined(EE_CAX_398_ISR))
extern void EE_CAX_398_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 399) && (EE_CAX_MAX_ARCH_ISR_ID >= 399) && defined(EE_CAX_399_ISR))
extern void EE_CAX_399_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 400) && (EE_CAX_MAX_ARCH_ISR_ID >= 400) && defined(EE_CAX_400_ISR))
extern void EE_CAX_400_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 401) && (EE_CAX_MAX_ARCH_ISR_ID >= 401) && defined(EE_CAX_401_ISR))
extern void EE_CAX_401_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 402) && (EE_CAX_MAX_ARCH_ISR_ID >= 402) && defined(EE_CAX_402_ISR))
extern void EE_CAX_402_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 403) && (EE_CAX_MAX_ARCH_ISR_ID >= 403) && defined(EE_CAX_403_ISR))
extern void EE_CAX_403_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 404) && (EE_CAX_MAX_ARCH_ISR_ID >= 404) && defined(EE_CAX_404_ISR))
extern void EE_CAX_404_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 405) && (EE_CAX_MAX_ARCH_ISR_ID >= 405) && defined(EE_CAX_405_ISR))
extern void EE_CAX_405_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 406) && (EE_CAX_MAX_ARCH_ISR_ID >= 406) && defined(EE_CAX_406_ISR))
extern void EE_CAX_406_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 407) && (EE_CAX_MAX_ARCH_ISR_ID >= 407) && defined(EE_CAX_407_ISR))
extern void EE_CAX_407_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 408) && (EE_CAX_MAX_ARCH_ISR_ID >= 408) && defined(EE_CAX_408_ISR))
extern void EE_CAX_408_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 409) && (EE_CAX_MAX_ARCH_ISR_ID >= 409) && defined(EE_CAX_409_ISR))
extern void EE_CAX_409_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 410) && (EE_CAX_MAX_ARCH_ISR_ID >= 410) && defined(EE_CAX_410_ISR))
extern void EE_CAX_410_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 411) && (EE_CAX_MAX_ARCH_ISR_ID >= 411) && defined(EE_CAX_411_ISR))
extern void EE_CAX_411_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 412) && (EE_CAX_MAX_ARCH_ISR_ID >= 412) && defined(EE_CAX_412_ISR))
extern void EE_CAX_412_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 413) && (EE_CAX_MAX_ARCH_ISR_ID >= 413) && defined(EE_CAX_413_ISR))
extern void EE_CAX_413_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 414) && (EE_CAX_MAX_ARCH_ISR_ID >= 414) && defined(EE_CAX_414_ISR))
extern void EE_CAX_414_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 415) && (EE_CAX_MAX_ARCH_ISR_ID >= 415) && defined(EE_CAX_415_ISR))
extern void EE_CAX_415_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 416) && (EE_CAX_MAX_ARCH_ISR_ID >= 416) && defined(EE_CAX_416_ISR))
extern void EE_CAX_416_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 417) && (EE_CAX_MAX_ARCH_ISR_ID >= 417) && defined(EE_CAX_417_ISR))
extern void EE_CAX_417_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 418) && (EE_CAX_MAX_ARCH_ISR_ID >= 418) && defined(EE_CAX_418_ISR))
extern void EE_CAX_418_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 419) && (EE_CAX_MAX_ARCH_ISR_ID >= 419) && defined(EE_CAX_419_ISR))
extern void EE_CAX_419_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 420) && (EE_CAX_MAX_ARCH_ISR_ID >= 420) && defined(EE_CAX_420_ISR))
extern void EE_CAX_420_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 421) && (EE_CAX_MAX_ARCH_ISR_ID >= 421) && defined(EE_CAX_421_ISR))
extern void EE_CAX_421_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 422) && (EE_CAX_MAX_ARCH_ISR_ID >= 422) && defined(EE_CAX_422_ISR))
extern void EE_CAX_422_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 423) && (EE_CAX_MAX_ARCH_ISR_ID >= 423) && defined(EE_CAX_423_ISR))
extern void EE_CAX_423_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 424) && (EE_CAX_MAX_ARCH_ISR_ID >= 424) && defined(EE_CAX_424_ISR))
extern void EE_CAX_424_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 425) && (EE_CAX_MAX_ARCH_ISR_ID >= 425) && defined(EE_CAX_425_ISR))
extern void EE_CAX_425_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 426) && (EE_CAX_MAX_ARCH_ISR_ID >= 426) && defined(EE_CAX_426_ISR))
extern void EE_CAX_426_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 427) && (EE_CAX_MAX_ARCH_ISR_ID >= 427) && defined(EE_CAX_427_ISR))
extern void EE_CAX_427_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 428) && (EE_CAX_MAX_ARCH_ISR_ID >= 428) && defined(EE_CAX_428_ISR))
extern void EE_CAX_428_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 429) && (EE_CAX_MAX_ARCH_ISR_ID >= 429) && defined(EE_CAX_429_ISR))
extern void EE_CAX_429_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 430) && (EE_CAX_MAX_ARCH_ISR_ID >= 430) && defined(EE_CAX_430_ISR))
extern void EE_CAX_430_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 431) && (EE_CAX_MAX_ARCH_ISR_ID >= 431) && defined(EE_CAX_431_ISR))
extern void EE_CAX_431_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 432) && (EE_CAX_MAX_ARCH_ISR_ID >= 432) && defined(EE_CAX_432_ISR))
extern void EE_CAX_432_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 433) && (EE_CAX_MAX_ARCH_ISR_ID >= 433) && defined(EE_CAX_433_ISR))
extern void EE_CAX_433_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 434) && (EE_CAX_MAX_ARCH_ISR_ID >= 434) && defined(EE_CAX_434_ISR))
extern void EE_CAX_434_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 435) && (EE_CAX_MAX_ARCH_ISR_ID >= 435) && defined(EE_CAX_435_ISR))
extern void EE_CAX_435_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 436) && (EE_CAX_MAX_ARCH_ISR_ID >= 436) && defined(EE_CAX_436_ISR))
extern void EE_CAX_436_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 437) && (EE_CAX_MAX_ARCH_ISR_ID >= 437) && defined(EE_CAX_437_ISR))
extern void EE_CAX_437_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 438) && (EE_CAX_MAX_ARCH_ISR_ID >= 438) && defined(EE_CAX_438_ISR))
extern void EE_CAX_438_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 439) && (EE_CAX_MAX_ARCH_ISR_ID >= 439) && defined(EE_CAX_439_ISR))
extern void EE_CAX_439_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 440) && (EE_CAX_MAX_ARCH_ISR_ID >= 440) && defined(EE_CAX_440_ISR))
extern void EE_CAX_440_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 441) && (EE_CAX_MAX_ARCH_ISR_ID >= 441) && defined(EE_CAX_441_ISR))
extern void EE_CAX_441_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 442) && (EE_CAX_MAX_ARCH_ISR_ID >= 442) && defined(EE_CAX_442_ISR))
extern void EE_CAX_442_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 443) && (EE_CAX_MAX_ARCH_ISR_ID >= 443) && defined(EE_CAX_443_ISR))
extern void EE_CAX_443_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 444) && (EE_CAX_MAX_ARCH_ISR_ID >= 444) && defined(EE_CAX_444_ISR))
extern void EE_CAX_444_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 445) && (EE_CAX_MAX_ARCH_ISR_ID >= 445) && defined(EE_CAX_445_ISR))
extern void EE_CAX_445_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 446) && (EE_CAX_MAX_ARCH_ISR_ID >= 446) && defined(EE_CAX_446_ISR))
extern void EE_CAX_446_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 447) && (EE_CAX_MAX_ARCH_ISR_ID >= 447) && defined(EE_CAX_447_ISR))
extern void EE_CAX_447_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 448) && (EE_CAX_MAX_ARCH_ISR_ID >= 448) && defined(EE_CAX_448_ISR))
extern void EE_CAX_448_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 449) && (EE_CAX_MAX_ARCH_ISR_ID >= 449) && defined(EE_CAX_449_ISR))
extern void EE_CAX_449_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 450) && (EE_CAX_MAX_ARCH_ISR_ID >= 450) && defined(EE_CAX_450_ISR))
extern void EE_CAX_450_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 451) && (EE_CAX_MAX_ARCH_ISR_ID >= 451) && defined(EE_CAX_451_ISR))
extern void EE_CAX_451_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 452) && (EE_CAX_MAX_ARCH_ISR_ID >= 452) && defined(EE_CAX_452_ISR))
extern void EE_CAX_452_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 453) && (EE_CAX_MAX_ARCH_ISR_ID >= 453) && defined(EE_CAX_453_ISR))
extern void EE_CAX_453_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 454) && (EE_CAX_MAX_ARCH_ISR_ID >= 454) && defined(EE_CAX_454_ISR))
extern void EE_CAX_454_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 455) && (EE_CAX_MAX_ARCH_ISR_ID >= 455) && defined(EE_CAX_455_ISR))
extern void EE_CAX_455_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 456) && (EE_CAX_MAX_ARCH_ISR_ID >= 456) && defined(EE_CAX_456_ISR))
extern void EE_CAX_456_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 457) && (EE_CAX_MAX_ARCH_ISR_ID >= 457) && defined(EE_CAX_457_ISR))
extern void EE_CAX_457_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 458) && (EE_CAX_MAX_ARCH_ISR_ID >= 458) && defined(EE_CAX_458_ISR))
extern void EE_CAX_458_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 459) && (EE_CAX_MAX_ARCH_ISR_ID >= 459) && defined(EE_CAX_459_ISR))
extern void EE_CAX_459_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 460) && (EE_CAX_MAX_ARCH_ISR_ID >= 460) && defined(EE_CAX_460_ISR))
extern void EE_CAX_460_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 461) && (EE_CAX_MAX_ARCH_ISR_ID >= 461) && defined(EE_CAX_461_ISR))
extern void EE_CAX_461_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 462) && (EE_CAX_MAX_ARCH_ISR_ID >= 462) && defined(EE_CAX_462_ISR))
extern void EE_CAX_462_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 463) && (EE_CAX_MAX_ARCH_ISR_ID >= 463) && defined(EE_CAX_463_ISR))
extern void EE_CAX_463_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 464) && (EE_CAX_MAX_ARCH_ISR_ID >= 464) && defined(EE_CAX_464_ISR))
extern void EE_CAX_464_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 465) && (EE_CAX_MAX_ARCH_ISR_ID >= 465) && defined(EE_CAX_465_ISR))
extern void EE_CAX_465_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 466) && (EE_CAX_MAX_ARCH_ISR_ID >= 466) && defined(EE_CAX_466_ISR))
extern void EE_CAX_466_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 467) && (EE_CAX_MAX_ARCH_ISR_ID >= 467) && defined(EE_CAX_467_ISR))
extern void EE_CAX_467_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 468) && (EE_CAX_MAX_ARCH_ISR_ID >= 468) && defined(EE_CAX_468_ISR))
extern void EE_CAX_468_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 469) && (EE_CAX_MAX_ARCH_ISR_ID >= 469) && defined(EE_CAX_469_ISR))
extern void EE_CAX_469_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 470) && (EE_CAX_MAX_ARCH_ISR_ID >= 470) && defined(EE_CAX_470_ISR))
extern void EE_CAX_470_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 471) && (EE_CAX_MAX_ARCH_ISR_ID >= 471) && defined(EE_CAX_471_ISR))
extern void EE_CAX_471_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 472) && (EE_CAX_MAX_ARCH_ISR_ID >= 472) && defined(EE_CAX_472_ISR))
extern void EE_CAX_472_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 473) && (EE_CAX_MAX_ARCH_ISR_ID >= 473) && defined(EE_CAX_473_ISR))
extern void EE_CAX_473_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 474) && (EE_CAX_MAX_ARCH_ISR_ID >= 474) && defined(EE_CAX_474_ISR))
extern void EE_CAX_474_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 475) && (EE_CAX_MAX_ARCH_ISR_ID >= 475) && defined(EE_CAX_475_ISR))
extern void EE_CAX_475_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 476) && (EE_CAX_MAX_ARCH_ISR_ID >= 476) && defined(EE_CAX_476_ISR))
extern void EE_CAX_476_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 477) && (EE_CAX_MAX_ARCH_ISR_ID >= 477) && defined(EE_CAX_477_ISR))
extern void EE_CAX_477_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 478) && (EE_CAX_MAX_ARCH_ISR_ID >= 478) && defined(EE_CAX_478_ISR))
extern void EE_CAX_478_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 479) && (EE_CAX_MAX_ARCH_ISR_ID >= 479) && defined(EE_CAX_479_ISR))
extern void EE_CAX_479_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 480) && (EE_CAX_MAX_ARCH_ISR_ID >= 480) && defined(EE_CAX_480_ISR))
extern void EE_CAX_480_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 481) && (EE_CAX_MAX_ARCH_ISR_ID >= 481) && defined(EE_CAX_481_ISR))
extern void EE_CAX_481_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 482) && (EE_CAX_MAX_ARCH_ISR_ID >= 482) && defined(EE_CAX_482_ISR))
extern void EE_CAX_482_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 483) && (EE_CAX_MAX_ARCH_ISR_ID >= 483) && defined(EE_CAX_483_ISR))
extern void EE_CAX_483_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 484) && (EE_CAX_MAX_ARCH_ISR_ID >= 484) && defined(EE_CAX_484_ISR))
extern void EE_CAX_484_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 485) && (EE_CAX_MAX_ARCH_ISR_ID >= 485) && defined(EE_CAX_485_ISR))
extern void EE_CAX_485_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 486) && (EE_CAX_MAX_ARCH_ISR_ID >= 486) && defined(EE_CAX_486_ISR))
extern void EE_CAX_486_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 487) && (EE_CAX_MAX_ARCH_ISR_ID >= 487) && defined(EE_CAX_487_ISR))
extern void EE_CAX_487_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 488) && (EE_CAX_MAX_ARCH_ISR_ID >= 488) && defined(EE_CAX_488_ISR))
extern void EE_CAX_488_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 489) && (EE_CAX_MAX_ARCH_ISR_ID >= 489) && defined(EE_CAX_489_ISR))
extern void EE_CAX_489_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 490) && (EE_CAX_MAX_ARCH_ISR_ID >= 490) && defined(EE_CAX_490_ISR))
extern void EE_CAX_490_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 491) && (EE_CAX_MAX_ARCH_ISR_ID >= 491) && defined(EE_CAX_491_ISR))
extern void EE_CAX_491_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 492) && (EE_CAX_MAX_ARCH_ISR_ID >= 492) && defined(EE_CAX_492_ISR))
extern void EE_CAX_492_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 493) && (EE_CAX_MAX_ARCH_ISR_ID >= 493) && defined(EE_CAX_493_ISR))
extern void EE_CAX_493_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 494) && (EE_CAX_MAX_ARCH_ISR_ID >= 494) && defined(EE_CAX_494_ISR))
extern void EE_CAX_494_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 495) && (EE_CAX_MAX_ARCH_ISR_ID >= 495) && defined(EE_CAX_495_ISR))
extern void EE_CAX_495_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 496) && (EE_CAX_MAX_ARCH_ISR_ID >= 496) && defined(EE_CAX_496_ISR))
extern void EE_CAX_496_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 497) && (EE_CAX_MAX_ARCH_ISR_ID >= 497) && defined(EE_CAX_497_ISR))
extern void EE_CAX_497_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 498) && (EE_CAX_MAX_ARCH_ISR_ID >= 498) && defined(EE_CAX_498_ISR))
extern void EE_CAX_498_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 499) && (EE_CAX_MAX_ARCH_ISR_ID >= 499) && defined(EE_CAX_499_ISR))
extern void EE_CAX_499_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 500) && (EE_CAX_MAX_ARCH_ISR_ID >= 500) && defined(EE_CAX_500_ISR))
extern void EE_CAX_500_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 501) && (EE_CAX_MAX_ARCH_ISR_ID >= 501) && defined(EE_CAX_501_ISR))
extern void EE_CAX_501_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 502) && (EE_CAX_MAX_ARCH_ISR_ID >= 502) && defined(EE_CAX_502_ISR))
extern void EE_CAX_502_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 503) && (EE_CAX_MAX_ARCH_ISR_ID >= 503) && defined(EE_CAX_503_ISR))
extern void EE_CAX_503_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 504) && (EE_CAX_MAX_ARCH_ISR_ID >= 504) && defined(EE_CAX_504_ISR))
extern void EE_CAX_504_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 505) && (EE_CAX_MAX_ARCH_ISR_ID >= 505) && defined(EE_CAX_505_ISR))
extern void EE_CAX_505_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 506) && (EE_CAX_MAX_ARCH_ISR_ID >= 506) && defined(EE_CAX_506_ISR))
extern void EE_CAX_506_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 507) && (EE_CAX_MAX_ARCH_ISR_ID >= 507) && defined(EE_CAX_507_ISR))
extern void EE_CAX_507_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 508) && (EE_CAX_MAX_ARCH_ISR_ID >= 508) && defined(EE_CAX_508_ISR))
extern void EE_CAX_508_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 509) && (EE_CAX_MAX_ARCH_ISR_ID >= 509) && defined(EE_CAX_509_ISR))
extern void EE_CAX_509_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 510) && (EE_CAX_MAX_ARCH_ISR_ID >= 510) && defined(EE_CAX_510_ISR))
extern void EE_CAX_510_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 511) && (EE_CAX_MAX_ARCH_ISR_ID >= 511) && defined(EE_CAX_511_ISR))
extern void EE_CAX_511_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 512) && (EE_CAX_MAX_ARCH_ISR_ID >= 512) && defined(EE_CAX_512_ISR))
extern void EE_CAX_512_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 513) && (EE_CAX_MAX_ARCH_ISR_ID >= 513) && defined(EE_CAX_513_ISR))
extern void EE_CAX_513_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 514) && (EE_CAX_MAX_ARCH_ISR_ID >= 514) && defined(EE_CAX_514_ISR))
extern void EE_CAX_514_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 515) && (EE_CAX_MAX_ARCH_ISR_ID >= 515) && defined(EE_CAX_515_ISR))
extern void EE_CAX_515_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 516) && (EE_CAX_MAX_ARCH_ISR_ID >= 516) && defined(EE_CAX_516_ISR))
extern void EE_CAX_516_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 517) && (EE_CAX_MAX_ARCH_ISR_ID >= 517) && defined(EE_CAX_517_ISR))
extern void EE_CAX_517_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 518) && (EE_CAX_MAX_ARCH_ISR_ID >= 518) && defined(EE_CAX_518_ISR))
extern void EE_CAX_518_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 519) && (EE_CAX_MAX_ARCH_ISR_ID >= 519) && defined(EE_CAX_519_ISR))
extern void EE_CAX_519_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 520) && (EE_CAX_MAX_ARCH_ISR_ID >= 520) && defined(EE_CAX_520_ISR))
extern void EE_CAX_520_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 521) && (EE_CAX_MAX_ARCH_ISR_ID >= 521) && defined(EE_CAX_521_ISR))
extern void EE_CAX_521_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 522) && (EE_CAX_MAX_ARCH_ISR_ID >= 522) && defined(EE_CAX_522_ISR))
extern void EE_CAX_522_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 523) && (EE_CAX_MAX_ARCH_ISR_ID >= 523) && defined(EE_CAX_523_ISR))
extern void EE_CAX_523_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 524) && (EE_CAX_MAX_ARCH_ISR_ID >= 524) && defined(EE_CAX_524_ISR))
extern void EE_CAX_524_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 525) && (EE_CAX_MAX_ARCH_ISR_ID >= 525) && defined(EE_CAX_525_ISR))
extern void EE_CAX_525_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 526) && (EE_CAX_MAX_ARCH_ISR_ID >= 526) && defined(EE_CAX_526_ISR))
extern void EE_CAX_526_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 527) && (EE_CAX_MAX_ARCH_ISR_ID >= 527) && defined(EE_CAX_527_ISR))
extern void EE_CAX_527_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 528) && (EE_CAX_MAX_ARCH_ISR_ID >= 528) && defined(EE_CAX_528_ISR))
extern void EE_CAX_528_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 529) && (EE_CAX_MAX_ARCH_ISR_ID >= 529) && defined(EE_CAX_529_ISR))
extern void EE_CAX_529_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 530) && (EE_CAX_MAX_ARCH_ISR_ID >= 530) && defined(EE_CAX_530_ISR))
extern void EE_CAX_530_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 531) && (EE_CAX_MAX_ARCH_ISR_ID >= 531) && defined(EE_CAX_531_ISR))
extern void EE_CAX_531_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 532) && (EE_CAX_MAX_ARCH_ISR_ID >= 532) && defined(EE_CAX_532_ISR))
extern void EE_CAX_532_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 533) && (EE_CAX_MAX_ARCH_ISR_ID >= 533) && defined(EE_CAX_533_ISR))
extern void EE_CAX_533_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 534) && (EE_CAX_MAX_ARCH_ISR_ID >= 534) && defined(EE_CAX_534_ISR))
extern void EE_CAX_534_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 535) && (EE_CAX_MAX_ARCH_ISR_ID >= 535) && defined(EE_CAX_535_ISR))
extern void EE_CAX_535_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 536) && (EE_CAX_MAX_ARCH_ISR_ID >= 536) && defined(EE_CAX_536_ISR))
extern void EE_CAX_536_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 537) && (EE_CAX_MAX_ARCH_ISR_ID >= 537) && defined(EE_CAX_537_ISR))
extern void EE_CAX_537_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 538) && (EE_CAX_MAX_ARCH_ISR_ID >= 538) && defined(EE_CAX_538_ISR))
extern void EE_CAX_538_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 539) && (EE_CAX_MAX_ARCH_ISR_ID >= 539) && defined(EE_CAX_539_ISR))
extern void EE_CAX_539_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 540) && (EE_CAX_MAX_ARCH_ISR_ID >= 540) && defined(EE_CAX_540_ISR))
extern void EE_CAX_540_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 541) && (EE_CAX_MAX_ARCH_ISR_ID >= 541) && defined(EE_CAX_541_ISR))
extern void EE_CAX_541_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 542) && (EE_CAX_MAX_ARCH_ISR_ID >= 542) && defined(EE_CAX_542_ISR))
extern void EE_CAX_542_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 543) && (EE_CAX_MAX_ARCH_ISR_ID >= 543) && defined(EE_CAX_543_ISR))
extern void EE_CAX_543_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 544) && (EE_CAX_MAX_ARCH_ISR_ID >= 544) && defined(EE_CAX_544_ISR))
extern void EE_CAX_544_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 545) && (EE_CAX_MAX_ARCH_ISR_ID >= 545) && defined(EE_CAX_545_ISR))
extern void EE_CAX_545_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 546) && (EE_CAX_MAX_ARCH_ISR_ID >= 546) && defined(EE_CAX_546_ISR))
extern void EE_CAX_546_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 547) && (EE_CAX_MAX_ARCH_ISR_ID >= 547) && defined(EE_CAX_547_ISR))
extern void EE_CAX_547_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 548) && (EE_CAX_MAX_ARCH_ISR_ID >= 548) && defined(EE_CAX_548_ISR))
extern void EE_CAX_548_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 549) && (EE_CAX_MAX_ARCH_ISR_ID >= 549) && defined(EE_CAX_549_ISR))
extern void EE_CAX_549_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 550) && (EE_CAX_MAX_ARCH_ISR_ID >= 550) && defined(EE_CAX_550_ISR))
extern void EE_CAX_550_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 551) && (EE_CAX_MAX_ARCH_ISR_ID >= 551) && defined(EE_CAX_551_ISR))
extern void EE_CAX_551_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 552) && (EE_CAX_MAX_ARCH_ISR_ID >= 552) && defined(EE_CAX_552_ISR))
extern void EE_CAX_552_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 553) && (EE_CAX_MAX_ARCH_ISR_ID >= 553) && defined(EE_CAX_553_ISR))
extern void EE_CAX_553_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 554) && (EE_CAX_MAX_ARCH_ISR_ID >= 554) && defined(EE_CAX_554_ISR))
extern void EE_CAX_554_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 555) && (EE_CAX_MAX_ARCH_ISR_ID >= 555) && defined(EE_CAX_555_ISR))
extern void EE_CAX_555_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 556) && (EE_CAX_MAX_ARCH_ISR_ID >= 556) && defined(EE_CAX_556_ISR))
extern void EE_CAX_556_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 557) && (EE_CAX_MAX_ARCH_ISR_ID >= 557) && defined(EE_CAX_557_ISR))
extern void EE_CAX_557_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 558) && (EE_CAX_MAX_ARCH_ISR_ID >= 558) && defined(EE_CAX_558_ISR))
extern void EE_CAX_558_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 559) && (EE_CAX_MAX_ARCH_ISR_ID >= 559) && defined(EE_CAX_559_ISR))
extern void EE_CAX_559_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 560) && (EE_CAX_MAX_ARCH_ISR_ID >= 560) && defined(EE_CAX_560_ISR))
extern void EE_CAX_560_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 561) && (EE_CAX_MAX_ARCH_ISR_ID >= 561) && defined(EE_CAX_561_ISR))
extern void EE_CAX_561_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 562) && (EE_CAX_MAX_ARCH_ISR_ID >= 562) && defined(EE_CAX_562_ISR))
extern void EE_CAX_562_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 563) && (EE_CAX_MAX_ARCH_ISR_ID >= 563) && defined(EE_CAX_563_ISR))
extern void EE_CAX_563_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 564) && (EE_CAX_MAX_ARCH_ISR_ID >= 564) && defined(EE_CAX_564_ISR))
extern void EE_CAX_564_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 565) && (EE_CAX_MAX_ARCH_ISR_ID >= 565) && defined(EE_CAX_565_ISR))
extern void EE_CAX_565_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 566) && (EE_CAX_MAX_ARCH_ISR_ID >= 566) && defined(EE_CAX_566_ISR))
extern void EE_CAX_566_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 567) && (EE_CAX_MAX_ARCH_ISR_ID >= 567) && defined(EE_CAX_567_ISR))
extern void EE_CAX_567_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 568) && (EE_CAX_MAX_ARCH_ISR_ID >= 568) && defined(EE_CAX_568_ISR))
extern void EE_CAX_568_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 569) && (EE_CAX_MAX_ARCH_ISR_ID >= 569) && defined(EE_CAX_569_ISR))
extern void EE_CAX_569_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 570) && (EE_CAX_MAX_ARCH_ISR_ID >= 570) && defined(EE_CAX_570_ISR))
extern void EE_CAX_570_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 571) && (EE_CAX_MAX_ARCH_ISR_ID >= 571) && defined(EE_CAX_571_ISR))
extern void EE_CAX_571_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 572) && (EE_CAX_MAX_ARCH_ISR_ID >= 572) && defined(EE_CAX_572_ISR))
extern void EE_CAX_572_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 573) && (EE_CAX_MAX_ARCH_ISR_ID >= 573) && defined(EE_CAX_573_ISR))
extern void EE_CAX_573_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 574) && (EE_CAX_MAX_ARCH_ISR_ID >= 574) && defined(EE_CAX_574_ISR))
extern void EE_CAX_574_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 575) && (EE_CAX_MAX_ARCH_ISR_ID >= 575) && defined(EE_CAX_575_ISR))
extern void EE_CAX_575_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 576) && (EE_CAX_MAX_ARCH_ISR_ID >= 576) && defined(EE_CAX_576_ISR))
extern void EE_CAX_576_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 577) && (EE_CAX_MAX_ARCH_ISR_ID >= 577) && defined(EE_CAX_577_ISR))
extern void EE_CAX_577_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 578) && (EE_CAX_MAX_ARCH_ISR_ID >= 578) && defined(EE_CAX_578_ISR))
extern void EE_CAX_578_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 579) && (EE_CAX_MAX_ARCH_ISR_ID >= 579) && defined(EE_CAX_579_ISR))
extern void EE_CAX_579_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 580) && (EE_CAX_MAX_ARCH_ISR_ID >= 580) && defined(EE_CAX_580_ISR))
extern void EE_CAX_580_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 581) && (EE_CAX_MAX_ARCH_ISR_ID >= 581) && defined(EE_CAX_581_ISR))
extern void EE_CAX_581_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 582) && (EE_CAX_MAX_ARCH_ISR_ID >= 582) && defined(EE_CAX_582_ISR))
extern void EE_CAX_582_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 583) && (EE_CAX_MAX_ARCH_ISR_ID >= 583) && defined(EE_CAX_583_ISR))
extern void EE_CAX_583_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 584) && (EE_CAX_MAX_ARCH_ISR_ID >= 584) && defined(EE_CAX_584_ISR))
extern void EE_CAX_584_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 585) && (EE_CAX_MAX_ARCH_ISR_ID >= 585) && defined(EE_CAX_585_ISR))
extern void EE_CAX_585_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 586) && (EE_CAX_MAX_ARCH_ISR_ID >= 586) && defined(EE_CAX_586_ISR))
extern void EE_CAX_586_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 587) && (EE_CAX_MAX_ARCH_ISR_ID >= 587) && defined(EE_CAX_587_ISR))
extern void EE_CAX_587_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 588) && (EE_CAX_MAX_ARCH_ISR_ID >= 588) && defined(EE_CAX_588_ISR))
extern void EE_CAX_588_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 589) && (EE_CAX_MAX_ARCH_ISR_ID >= 589) && defined(EE_CAX_589_ISR))
extern void EE_CAX_589_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 590) && (EE_CAX_MAX_ARCH_ISR_ID >= 590) && defined(EE_CAX_590_ISR))
extern void EE_CAX_590_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 591) && (EE_CAX_MAX_ARCH_ISR_ID >= 591) && defined(EE_CAX_591_ISR))
extern void EE_CAX_591_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 592) && (EE_CAX_MAX_ARCH_ISR_ID >= 592) && defined(EE_CAX_592_ISR))
extern void EE_CAX_592_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 593) && (EE_CAX_MAX_ARCH_ISR_ID >= 593) && defined(EE_CAX_593_ISR))
extern void EE_CAX_593_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 594) && (EE_CAX_MAX_ARCH_ISR_ID >= 594) && defined(EE_CAX_594_ISR))
extern void EE_CAX_594_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 595) && (EE_CAX_MAX_ARCH_ISR_ID >= 595) && defined(EE_CAX_595_ISR))
extern void EE_CAX_595_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 596) && (EE_CAX_MAX_ARCH_ISR_ID >= 596) && defined(EE_CAX_596_ISR))
extern void EE_CAX_596_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 597) && (EE_CAX_MAX_ARCH_ISR_ID >= 597) && defined(EE_CAX_597_ISR))
extern void EE_CAX_597_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 598) && (EE_CAX_MAX_ARCH_ISR_ID >= 598) && defined(EE_CAX_598_ISR))
extern void EE_CAX_598_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 599) && (EE_CAX_MAX_ARCH_ISR_ID >= 599) && defined(EE_CAX_599_ISR))
extern void EE_CAX_599_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 600) && (EE_CAX_MAX_ARCH_ISR_ID >= 600) && defined(EE_CAX_600_ISR))
extern void EE_CAX_600_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 601) && (EE_CAX_MAX_ARCH_ISR_ID >= 601) && defined(EE_CAX_601_ISR))
extern void EE_CAX_601_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 602) && (EE_CAX_MAX_ARCH_ISR_ID >= 602) && defined(EE_CAX_602_ISR))
extern void EE_CAX_602_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 603) && (EE_CAX_MAX_ARCH_ISR_ID >= 603) && defined(EE_CAX_603_ISR))
extern void EE_CAX_603_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 604) && (EE_CAX_MAX_ARCH_ISR_ID >= 604) && defined(EE_CAX_604_ISR))
extern void EE_CAX_604_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 605) && (EE_CAX_MAX_ARCH_ISR_ID >= 605) && defined(EE_CAX_605_ISR))
extern void EE_CAX_605_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 606) && (EE_CAX_MAX_ARCH_ISR_ID >= 606) && defined(EE_CAX_606_ISR))
extern void EE_CAX_606_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 607) && (EE_CAX_MAX_ARCH_ISR_ID >= 607) && defined(EE_CAX_607_ISR))
extern void EE_CAX_607_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 608) && (EE_CAX_MAX_ARCH_ISR_ID >= 608) && defined(EE_CAX_608_ISR))
extern void EE_CAX_608_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 609) && (EE_CAX_MAX_ARCH_ISR_ID >= 609) && defined(EE_CAX_609_ISR))
extern void EE_CAX_609_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 610) && (EE_CAX_MAX_ARCH_ISR_ID >= 610) && defined(EE_CAX_610_ISR))
extern void EE_CAX_610_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 611) && (EE_CAX_MAX_ARCH_ISR_ID >= 611) && defined(EE_CAX_611_ISR))
extern void EE_CAX_611_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 612) && (EE_CAX_MAX_ARCH_ISR_ID >= 612) && defined(EE_CAX_612_ISR))
extern void EE_CAX_612_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 613) && (EE_CAX_MAX_ARCH_ISR_ID >= 613) && defined(EE_CAX_613_ISR))
extern void EE_CAX_613_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 614) && (EE_CAX_MAX_ARCH_ISR_ID >= 614) && defined(EE_CAX_614_ISR))
extern void EE_CAX_614_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 615) && (EE_CAX_MAX_ARCH_ISR_ID >= 615) && defined(EE_CAX_615_ISR))
extern void EE_CAX_615_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 616) && (EE_CAX_MAX_ARCH_ISR_ID >= 616) && defined(EE_CAX_616_ISR))
extern void EE_CAX_616_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 617) && (EE_CAX_MAX_ARCH_ISR_ID >= 617) && defined(EE_CAX_617_ISR))
extern void EE_CAX_617_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 618) && (EE_CAX_MAX_ARCH_ISR_ID >= 618) && defined(EE_CAX_618_ISR))
extern void EE_CAX_618_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 619) && (EE_CAX_MAX_ARCH_ISR_ID >= 619) && defined(EE_CAX_619_ISR))
extern void EE_CAX_619_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 620) && (EE_CAX_MAX_ARCH_ISR_ID >= 620) && defined(EE_CAX_620_ISR))
extern void EE_CAX_620_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 621) && (EE_CAX_MAX_ARCH_ISR_ID >= 621) && defined(EE_CAX_621_ISR))
extern void EE_CAX_621_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 622) && (EE_CAX_MAX_ARCH_ISR_ID >= 622) && defined(EE_CAX_622_ISR))
extern void EE_CAX_622_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 623) && (EE_CAX_MAX_ARCH_ISR_ID >= 623) && defined(EE_CAX_623_ISR))
extern void EE_CAX_623_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 624) && (EE_CAX_MAX_ARCH_ISR_ID >= 624) && defined(EE_CAX_624_ISR))
extern void EE_CAX_624_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 625) && (EE_CAX_MAX_ARCH_ISR_ID >= 625) && defined(EE_CAX_625_ISR))
extern void EE_CAX_625_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 626) && (EE_CAX_MAX_ARCH_ISR_ID >= 626) && defined(EE_CAX_626_ISR))
extern void EE_CAX_626_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 627) && (EE_CAX_MAX_ARCH_ISR_ID >= 627) && defined(EE_CAX_627_ISR))
extern void EE_CAX_627_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 628) && (EE_CAX_MAX_ARCH_ISR_ID >= 628) && defined(EE_CAX_628_ISR))
extern void EE_CAX_628_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 629) && (EE_CAX_MAX_ARCH_ISR_ID >= 629) && defined(EE_CAX_629_ISR))
extern void EE_CAX_629_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 630) && (EE_CAX_MAX_ARCH_ISR_ID >= 630) && defined(EE_CAX_630_ISR))
extern void EE_CAX_630_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 631) && (EE_CAX_MAX_ARCH_ISR_ID >= 631) && defined(EE_CAX_631_ISR))
extern void EE_CAX_631_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 632) && (EE_CAX_MAX_ARCH_ISR_ID >= 632) && defined(EE_CAX_632_ISR))
extern void EE_CAX_632_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 633) && (EE_CAX_MAX_ARCH_ISR_ID >= 633) && defined(EE_CAX_633_ISR))
extern void EE_CAX_633_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 634) && (EE_CAX_MAX_ARCH_ISR_ID >= 634) && defined(EE_CAX_634_ISR))
extern void EE_CAX_634_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 635) && (EE_CAX_MAX_ARCH_ISR_ID >= 635) && defined(EE_CAX_635_ISR))
extern void EE_CAX_635_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 636) && (EE_CAX_MAX_ARCH_ISR_ID >= 636) && defined(EE_CAX_636_ISR))
extern void EE_CAX_636_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 637) && (EE_CAX_MAX_ARCH_ISR_ID >= 637) && defined(EE_CAX_637_ISR))
extern void EE_CAX_637_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 638) && (EE_CAX_MAX_ARCH_ISR_ID >= 638) && defined(EE_CAX_638_ISR))
extern void EE_CAX_638_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 639) && (EE_CAX_MAX_ARCH_ISR_ID >= 639) && defined(EE_CAX_639_ISR))
extern void EE_CAX_639_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 640) && (EE_CAX_MAX_ARCH_ISR_ID >= 640) && defined(EE_CAX_640_ISR))
extern void EE_CAX_640_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 641) && (EE_CAX_MAX_ARCH_ISR_ID >= 641) && defined(EE_CAX_641_ISR))
extern void EE_CAX_641_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 642) && (EE_CAX_MAX_ARCH_ISR_ID >= 642) && defined(EE_CAX_642_ISR))
extern void EE_CAX_642_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 643) && (EE_CAX_MAX_ARCH_ISR_ID >= 643) && defined(EE_CAX_643_ISR))
extern void EE_CAX_643_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 644) && (EE_CAX_MAX_ARCH_ISR_ID >= 644) && defined(EE_CAX_644_ISR))
extern void EE_CAX_644_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 645) && (EE_CAX_MAX_ARCH_ISR_ID >= 645) && defined(EE_CAX_645_ISR))
extern void EE_CAX_645_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 646) && (EE_CAX_MAX_ARCH_ISR_ID >= 646) && defined(EE_CAX_646_ISR))
extern void EE_CAX_646_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 647) && (EE_CAX_MAX_ARCH_ISR_ID >= 647) && defined(EE_CAX_647_ISR))
extern void EE_CAX_647_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 648) && (EE_CAX_MAX_ARCH_ISR_ID >= 648) && defined(EE_CAX_648_ISR))
extern void EE_CAX_648_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 649) && (EE_CAX_MAX_ARCH_ISR_ID >= 649) && defined(EE_CAX_649_ISR))
extern void EE_CAX_649_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 650) && (EE_CAX_MAX_ARCH_ISR_ID >= 650) && defined(EE_CAX_650_ISR))
extern void EE_CAX_650_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 651) && (EE_CAX_MAX_ARCH_ISR_ID >= 651) && defined(EE_CAX_651_ISR))
extern void EE_CAX_651_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 652) && (EE_CAX_MAX_ARCH_ISR_ID >= 652) && defined(EE_CAX_652_ISR))
extern void EE_CAX_652_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 653) && (EE_CAX_MAX_ARCH_ISR_ID >= 653) && defined(EE_CAX_653_ISR))
extern void EE_CAX_653_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 654) && (EE_CAX_MAX_ARCH_ISR_ID >= 654) && defined(EE_CAX_654_ISR))
extern void EE_CAX_654_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 655) && (EE_CAX_MAX_ARCH_ISR_ID >= 655) && defined(EE_CAX_655_ISR))
extern void EE_CAX_655_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 656) && (EE_CAX_MAX_ARCH_ISR_ID >= 656) && defined(EE_CAX_656_ISR))
extern void EE_CAX_656_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 657) && (EE_CAX_MAX_ARCH_ISR_ID >= 657) && defined(EE_CAX_657_ISR))
extern void EE_CAX_657_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 658) && (EE_CAX_MAX_ARCH_ISR_ID >= 658) && defined(EE_CAX_658_ISR))
extern void EE_CAX_658_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 659) && (EE_CAX_MAX_ARCH_ISR_ID >= 659) && defined(EE_CAX_659_ISR))
extern void EE_CAX_659_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 660) && (EE_CAX_MAX_ARCH_ISR_ID >= 660) && defined(EE_CAX_660_ISR))
extern void EE_CAX_660_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 661) && (EE_CAX_MAX_ARCH_ISR_ID >= 661) && defined(EE_CAX_661_ISR))
extern void EE_CAX_661_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 662) && (EE_CAX_MAX_ARCH_ISR_ID >= 662) && defined(EE_CAX_662_ISR))
extern void EE_CAX_662_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 663) && (EE_CAX_MAX_ARCH_ISR_ID >= 663) && defined(EE_CAX_663_ISR))
extern void EE_CAX_663_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 664) && (EE_CAX_MAX_ARCH_ISR_ID >= 664) && defined(EE_CAX_664_ISR))
extern void EE_CAX_664_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 665) && (EE_CAX_MAX_ARCH_ISR_ID >= 665) && defined(EE_CAX_665_ISR))
extern void EE_CAX_665_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 666) && (EE_CAX_MAX_ARCH_ISR_ID >= 666) && defined(EE_CAX_666_ISR))
extern void EE_CAX_666_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 667) && (EE_CAX_MAX_ARCH_ISR_ID >= 667) && defined(EE_CAX_667_ISR))
extern void EE_CAX_667_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 668) && (EE_CAX_MAX_ARCH_ISR_ID >= 668) && defined(EE_CAX_668_ISR))
extern void EE_CAX_668_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 669) && (EE_CAX_MAX_ARCH_ISR_ID >= 669) && defined(EE_CAX_669_ISR))
extern void EE_CAX_669_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 670) && (EE_CAX_MAX_ARCH_ISR_ID >= 670) && defined(EE_CAX_670_ISR))
extern void EE_CAX_670_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 671) && (EE_CAX_MAX_ARCH_ISR_ID >= 671) && defined(EE_CAX_671_ISR))
extern void EE_CAX_671_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 672) && (EE_CAX_MAX_ARCH_ISR_ID >= 672) && defined(EE_CAX_672_ISR))
extern void EE_CAX_672_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 673) && (EE_CAX_MAX_ARCH_ISR_ID >= 673) && defined(EE_CAX_673_ISR))
extern void EE_CAX_673_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 674) && (EE_CAX_MAX_ARCH_ISR_ID >= 674) && defined(EE_CAX_674_ISR))
extern void EE_CAX_674_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 675) && (EE_CAX_MAX_ARCH_ISR_ID >= 675) && defined(EE_CAX_675_ISR))
extern void EE_CAX_675_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 676) && (EE_CAX_MAX_ARCH_ISR_ID >= 676) && defined(EE_CAX_676_ISR))
extern void EE_CAX_676_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 677) && (EE_CAX_MAX_ARCH_ISR_ID >= 677) && defined(EE_CAX_677_ISR))
extern void EE_CAX_677_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 678) && (EE_CAX_MAX_ARCH_ISR_ID >= 678) && defined(EE_CAX_678_ISR))
extern void EE_CAX_678_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 679) && (EE_CAX_MAX_ARCH_ISR_ID >= 679) && defined(EE_CAX_679_ISR))
extern void EE_CAX_679_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 680) && (EE_CAX_MAX_ARCH_ISR_ID >= 680) && defined(EE_CAX_680_ISR))
extern void EE_CAX_680_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 681) && (EE_CAX_MAX_ARCH_ISR_ID >= 681) && defined(EE_CAX_681_ISR))
extern void EE_CAX_681_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 682) && (EE_CAX_MAX_ARCH_ISR_ID >= 682) && defined(EE_CAX_682_ISR))
extern void EE_CAX_682_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 683) && (EE_CAX_MAX_ARCH_ISR_ID >= 683) && defined(EE_CAX_683_ISR))
extern void EE_CAX_683_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 684) && (EE_CAX_MAX_ARCH_ISR_ID >= 684) && defined(EE_CAX_684_ISR))
extern void EE_CAX_684_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 685) && (EE_CAX_MAX_ARCH_ISR_ID >= 685) && defined(EE_CAX_685_ISR))
extern void EE_CAX_685_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 686) && (EE_CAX_MAX_ARCH_ISR_ID >= 686) && defined(EE_CAX_686_ISR))
extern void EE_CAX_686_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 687) && (EE_CAX_MAX_ARCH_ISR_ID >= 687) && defined(EE_CAX_687_ISR))
extern void EE_CAX_687_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 688) && (EE_CAX_MAX_ARCH_ISR_ID >= 688) && defined(EE_CAX_688_ISR))
extern void EE_CAX_688_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 689) && (EE_CAX_MAX_ARCH_ISR_ID >= 689) && defined(EE_CAX_689_ISR))
extern void EE_CAX_689_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 690) && (EE_CAX_MAX_ARCH_ISR_ID >= 690) && defined(EE_CAX_690_ISR))
extern void EE_CAX_690_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 691) && (EE_CAX_MAX_ARCH_ISR_ID >= 691) && defined(EE_CAX_691_ISR))
extern void EE_CAX_691_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 692) && (EE_CAX_MAX_ARCH_ISR_ID >= 692) && defined(EE_CAX_692_ISR))
extern void EE_CAX_692_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 693) && (EE_CAX_MAX_ARCH_ISR_ID >= 693) && defined(EE_CAX_693_ISR))
extern void EE_CAX_693_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 694) && (EE_CAX_MAX_ARCH_ISR_ID >= 694) && defined(EE_CAX_694_ISR))
extern void EE_CAX_694_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 695) && (EE_CAX_MAX_ARCH_ISR_ID >= 695) && defined(EE_CAX_695_ISR))
extern void EE_CAX_695_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 696) && (EE_CAX_MAX_ARCH_ISR_ID >= 696) && defined(EE_CAX_696_ISR))
extern void EE_CAX_696_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 697) && (EE_CAX_MAX_ARCH_ISR_ID >= 697) && defined(EE_CAX_697_ISR))
extern void EE_CAX_697_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 698) && (EE_CAX_MAX_ARCH_ISR_ID >= 698) && defined(EE_CAX_698_ISR))
extern void EE_CAX_698_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 699) && (EE_CAX_MAX_ARCH_ISR_ID >= 699) && defined(EE_CAX_699_ISR))
extern void EE_CAX_699_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 700) && (EE_CAX_MAX_ARCH_ISR_ID >= 700) && defined(EE_CAX_700_ISR))
extern void EE_CAX_700_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 701) && (EE_CAX_MAX_ARCH_ISR_ID >= 701) && defined(EE_CAX_701_ISR))
extern void EE_CAX_701_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 702) && (EE_CAX_MAX_ARCH_ISR_ID >= 702) && defined(EE_CAX_702_ISR))
extern void EE_CAX_702_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 703) && (EE_CAX_MAX_ARCH_ISR_ID >= 703) && defined(EE_CAX_703_ISR))
extern void EE_CAX_703_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 704) && (EE_CAX_MAX_ARCH_ISR_ID >= 704) && defined(EE_CAX_704_ISR))
extern void EE_CAX_704_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 705) && (EE_CAX_MAX_ARCH_ISR_ID >= 705) && defined(EE_CAX_705_ISR))
extern void EE_CAX_705_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 706) && (EE_CAX_MAX_ARCH_ISR_ID >= 706) && defined(EE_CAX_706_ISR))
extern void EE_CAX_706_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 707) && (EE_CAX_MAX_ARCH_ISR_ID >= 707) && defined(EE_CAX_707_ISR))
extern void EE_CAX_707_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 708) && (EE_CAX_MAX_ARCH_ISR_ID >= 708) && defined(EE_CAX_708_ISR))
extern void EE_CAX_708_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 709) && (EE_CAX_MAX_ARCH_ISR_ID >= 709) && defined(EE_CAX_709_ISR))
extern void EE_CAX_709_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 710) && (EE_CAX_MAX_ARCH_ISR_ID >= 710) && defined(EE_CAX_710_ISR))
extern void EE_CAX_710_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 711) && (EE_CAX_MAX_ARCH_ISR_ID >= 711) && defined(EE_CAX_711_ISR))
extern void EE_CAX_711_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 712) && (EE_CAX_MAX_ARCH_ISR_ID >= 712) && defined(EE_CAX_712_ISR))
extern void EE_CAX_712_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 713) && (EE_CAX_MAX_ARCH_ISR_ID >= 713) && defined(EE_CAX_713_ISR))
extern void EE_CAX_713_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 714) && (EE_CAX_MAX_ARCH_ISR_ID >= 714) && defined(EE_CAX_714_ISR))
extern void EE_CAX_714_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 715) && (EE_CAX_MAX_ARCH_ISR_ID >= 715) && defined(EE_CAX_715_ISR))
extern void EE_CAX_715_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 716) && (EE_CAX_MAX_ARCH_ISR_ID >= 716) && defined(EE_CAX_716_ISR))
extern void EE_CAX_716_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 717) && (EE_CAX_MAX_ARCH_ISR_ID >= 717) && defined(EE_CAX_717_ISR))
extern void EE_CAX_717_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 718) && (EE_CAX_MAX_ARCH_ISR_ID >= 718) && defined(EE_CAX_718_ISR))
extern void EE_CAX_718_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 719) && (EE_CAX_MAX_ARCH_ISR_ID >= 719) && defined(EE_CAX_719_ISR))
extern void EE_CAX_719_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 720) && (EE_CAX_MAX_ARCH_ISR_ID >= 720) && defined(EE_CAX_720_ISR))
extern void EE_CAX_720_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 721) && (EE_CAX_MAX_ARCH_ISR_ID >= 721) && defined(EE_CAX_721_ISR))
extern void EE_CAX_721_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 722) && (EE_CAX_MAX_ARCH_ISR_ID >= 722) && defined(EE_CAX_722_ISR))
extern void EE_CAX_722_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 723) && (EE_CAX_MAX_ARCH_ISR_ID >= 723) && defined(EE_CAX_723_ISR))
extern void EE_CAX_723_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 724) && (EE_CAX_MAX_ARCH_ISR_ID >= 724) && defined(EE_CAX_724_ISR))
extern void EE_CAX_724_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 725) && (EE_CAX_MAX_ARCH_ISR_ID >= 725) && defined(EE_CAX_725_ISR))
extern void EE_CAX_725_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 726) && (EE_CAX_MAX_ARCH_ISR_ID >= 726) && defined(EE_CAX_726_ISR))
extern void EE_CAX_726_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 727) && (EE_CAX_MAX_ARCH_ISR_ID >= 727) && defined(EE_CAX_727_ISR))
extern void EE_CAX_727_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 728) && (EE_CAX_MAX_ARCH_ISR_ID >= 728) && defined(EE_CAX_728_ISR))
extern void EE_CAX_728_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 729) && (EE_CAX_MAX_ARCH_ISR_ID >= 729) && defined(EE_CAX_729_ISR))
extern void EE_CAX_729_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 730) && (EE_CAX_MAX_ARCH_ISR_ID >= 730) && defined(EE_CAX_730_ISR))
extern void EE_CAX_730_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 731) && (EE_CAX_MAX_ARCH_ISR_ID >= 731) && defined(EE_CAX_731_ISR))
extern void EE_CAX_731_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 732) && (EE_CAX_MAX_ARCH_ISR_ID >= 732) && defined(EE_CAX_732_ISR))
extern void EE_CAX_732_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 733) && (EE_CAX_MAX_ARCH_ISR_ID >= 733) && defined(EE_CAX_733_ISR))
extern void EE_CAX_733_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 734) && (EE_CAX_MAX_ARCH_ISR_ID >= 734) && defined(EE_CAX_734_ISR))
extern void EE_CAX_734_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 735) && (EE_CAX_MAX_ARCH_ISR_ID >= 735) && defined(EE_CAX_735_ISR))
extern void EE_CAX_735_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 736) && (EE_CAX_MAX_ARCH_ISR_ID >= 736) && defined(EE_CAX_736_ISR))
extern void EE_CAX_736_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 737) && (EE_CAX_MAX_ARCH_ISR_ID >= 737) && defined(EE_CAX_737_ISR))
extern void EE_CAX_737_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 738) && (EE_CAX_MAX_ARCH_ISR_ID >= 738) && defined(EE_CAX_738_ISR))
extern void EE_CAX_738_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 739) && (EE_CAX_MAX_ARCH_ISR_ID >= 739) && defined(EE_CAX_739_ISR))
extern void EE_CAX_739_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 740) && (EE_CAX_MAX_ARCH_ISR_ID >= 740) && defined(EE_CAX_740_ISR))
extern void EE_CAX_740_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 741) && (EE_CAX_MAX_ARCH_ISR_ID >= 741) && defined(EE_CAX_741_ISR))
extern void EE_CAX_741_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 742) && (EE_CAX_MAX_ARCH_ISR_ID >= 742) && defined(EE_CAX_742_ISR))
extern void EE_CAX_742_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 743) && (EE_CAX_MAX_ARCH_ISR_ID >= 743) && defined(EE_CAX_743_ISR))
extern void EE_CAX_743_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 744) && (EE_CAX_MAX_ARCH_ISR_ID >= 744) && defined(EE_CAX_744_ISR))
extern void EE_CAX_744_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 745) && (EE_CAX_MAX_ARCH_ISR_ID >= 745) && defined(EE_CAX_745_ISR))
extern void EE_CAX_745_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 746) && (EE_CAX_MAX_ARCH_ISR_ID >= 746) && defined(EE_CAX_746_ISR))
extern void EE_CAX_746_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 747) && (EE_CAX_MAX_ARCH_ISR_ID >= 747) && defined(EE_CAX_747_ISR))
extern void EE_CAX_747_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 748) && (EE_CAX_MAX_ARCH_ISR_ID >= 748) && defined(EE_CAX_748_ISR))
extern void EE_CAX_748_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 749) && (EE_CAX_MAX_ARCH_ISR_ID >= 749) && defined(EE_CAX_749_ISR))
extern void EE_CAX_749_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 750) && (EE_CAX_MAX_ARCH_ISR_ID >= 750) && defined(EE_CAX_750_ISR))
extern void EE_CAX_750_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 751) && (EE_CAX_MAX_ARCH_ISR_ID >= 751) && defined(EE_CAX_751_ISR))
extern void EE_CAX_751_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 752) && (EE_CAX_MAX_ARCH_ISR_ID >= 752) && defined(EE_CAX_752_ISR))
extern void EE_CAX_752_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 753) && (EE_CAX_MAX_ARCH_ISR_ID >= 753) && defined(EE_CAX_753_ISR))
extern void EE_CAX_753_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 754) && (EE_CAX_MAX_ARCH_ISR_ID >= 754) && defined(EE_CAX_754_ISR))
extern void EE_CAX_754_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 755) && (EE_CAX_MAX_ARCH_ISR_ID >= 755) && defined(EE_CAX_755_ISR))
extern void EE_CAX_755_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 756) && (EE_CAX_MAX_ARCH_ISR_ID >= 756) && defined(EE_CAX_756_ISR))
extern void EE_CAX_756_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 757) && (EE_CAX_MAX_ARCH_ISR_ID >= 757) && defined(EE_CAX_757_ISR))
extern void EE_CAX_757_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 758) && (EE_CAX_MAX_ARCH_ISR_ID >= 758) && defined(EE_CAX_758_ISR))
extern void EE_CAX_758_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 759) && (EE_CAX_MAX_ARCH_ISR_ID >= 759) && defined(EE_CAX_759_ISR))
extern void EE_CAX_759_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 760) && (EE_CAX_MAX_ARCH_ISR_ID >= 760) && defined(EE_CAX_760_ISR))
extern void EE_CAX_760_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 761) && (EE_CAX_MAX_ARCH_ISR_ID >= 761) && defined(EE_CAX_761_ISR))
extern void EE_CAX_761_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 762) && (EE_CAX_MAX_ARCH_ISR_ID >= 762) && defined(EE_CAX_762_ISR))
extern void EE_CAX_762_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 763) && (EE_CAX_MAX_ARCH_ISR_ID >= 763) && defined(EE_CAX_763_ISR))
extern void EE_CAX_763_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 764) && (EE_CAX_MAX_ARCH_ISR_ID >= 764) && defined(EE_CAX_764_ISR))
extern void EE_CAX_764_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 765) && (EE_CAX_MAX_ARCH_ISR_ID >= 765) && defined(EE_CAX_765_ISR))
extern void EE_CAX_765_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 766) && (EE_CAX_MAX_ARCH_ISR_ID >= 766) && defined(EE_CAX_766_ISR))
extern void EE_CAX_766_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 767) && (EE_CAX_MAX_ARCH_ISR_ID >= 767) && defined(EE_CAX_767_ISR))
extern void EE_CAX_767_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 768) && (EE_CAX_MAX_ARCH_ISR_ID >= 768) && defined(EE_CAX_768_ISR))
extern void EE_CAX_768_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 769) && (EE_CAX_MAX_ARCH_ISR_ID >= 769) && defined(EE_CAX_769_ISR))
extern void EE_CAX_769_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 770) && (EE_CAX_MAX_ARCH_ISR_ID >= 770) && defined(EE_CAX_770_ISR))
extern void EE_CAX_770_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 771) && (EE_CAX_MAX_ARCH_ISR_ID >= 771) && defined(EE_CAX_771_ISR))
extern void EE_CAX_771_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 772) && (EE_CAX_MAX_ARCH_ISR_ID >= 772) && defined(EE_CAX_772_ISR))
extern void EE_CAX_772_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 773) && (EE_CAX_MAX_ARCH_ISR_ID >= 773) && defined(EE_CAX_773_ISR))
extern void EE_CAX_773_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 774) && (EE_CAX_MAX_ARCH_ISR_ID >= 774) && defined(EE_CAX_774_ISR))
extern void EE_CAX_774_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 775) && (EE_CAX_MAX_ARCH_ISR_ID >= 775) && defined(EE_CAX_775_ISR))
extern void EE_CAX_775_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 776) && (EE_CAX_MAX_ARCH_ISR_ID >= 776) && defined(EE_CAX_776_ISR))
extern void EE_CAX_776_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 777) && (EE_CAX_MAX_ARCH_ISR_ID >= 777) && defined(EE_CAX_777_ISR))
extern void EE_CAX_777_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 778) && (EE_CAX_MAX_ARCH_ISR_ID >= 778) && defined(EE_CAX_778_ISR))
extern void EE_CAX_778_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 779) && (EE_CAX_MAX_ARCH_ISR_ID >= 779) && defined(EE_CAX_779_ISR))
extern void EE_CAX_779_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 780) && (EE_CAX_MAX_ARCH_ISR_ID >= 780) && defined(EE_CAX_780_ISR))
extern void EE_CAX_780_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 781) && (EE_CAX_MAX_ARCH_ISR_ID >= 781) && defined(EE_CAX_781_ISR))
extern void EE_CAX_781_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 782) && (EE_CAX_MAX_ARCH_ISR_ID >= 782) && defined(EE_CAX_782_ISR))
extern void EE_CAX_782_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 783) && (EE_CAX_MAX_ARCH_ISR_ID >= 783) && defined(EE_CAX_783_ISR))
extern void EE_CAX_783_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 784) && (EE_CAX_MAX_ARCH_ISR_ID >= 784) && defined(EE_CAX_784_ISR))
extern void EE_CAX_784_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 785) && (EE_CAX_MAX_ARCH_ISR_ID >= 785) && defined(EE_CAX_785_ISR))
extern void EE_CAX_785_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 786) && (EE_CAX_MAX_ARCH_ISR_ID >= 786) && defined(EE_CAX_786_ISR))
extern void EE_CAX_786_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 787) && (EE_CAX_MAX_ARCH_ISR_ID >= 787) && defined(EE_CAX_787_ISR))
extern void EE_CAX_787_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 788) && (EE_CAX_MAX_ARCH_ISR_ID >= 788) && defined(EE_CAX_788_ISR))
extern void EE_CAX_788_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 789) && (EE_CAX_MAX_ARCH_ISR_ID >= 789) && defined(EE_CAX_789_ISR))
extern void EE_CAX_789_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 790) && (EE_CAX_MAX_ARCH_ISR_ID >= 790) && defined(EE_CAX_790_ISR))
extern void EE_CAX_790_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 791) && (EE_CAX_MAX_ARCH_ISR_ID >= 791) && defined(EE_CAX_791_ISR))
extern void EE_CAX_791_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 792) && (EE_CAX_MAX_ARCH_ISR_ID >= 792) && defined(EE_CAX_792_ISR))
extern void EE_CAX_792_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 793) && (EE_CAX_MAX_ARCH_ISR_ID >= 793) && defined(EE_CAX_793_ISR))
extern void EE_CAX_793_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 794) && (EE_CAX_MAX_ARCH_ISR_ID >= 794) && defined(EE_CAX_794_ISR))
extern void EE_CAX_794_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 795) && (EE_CAX_MAX_ARCH_ISR_ID >= 795) && defined(EE_CAX_795_ISR))
extern void EE_CAX_795_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 796) && (EE_CAX_MAX_ARCH_ISR_ID >= 796) && defined(EE_CAX_796_ISR))
extern void EE_CAX_796_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 797) && (EE_CAX_MAX_ARCH_ISR_ID >= 797) && defined(EE_CAX_797_ISR))
extern void EE_CAX_797_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 798) && (EE_CAX_MAX_ARCH_ISR_ID >= 798) && defined(EE_CAX_798_ISR))
extern void EE_CAX_798_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 799) && (EE_CAX_MAX_ARCH_ISR_ID >= 799) && defined(EE_CAX_799_ISR))
extern void EE_CAX_799_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 800) && (EE_CAX_MAX_ARCH_ISR_ID >= 800) && defined(EE_CAX_800_ISR))
extern void EE_CAX_800_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 801) && (EE_CAX_MAX_ARCH_ISR_ID >= 801) && defined(EE_CAX_801_ISR))
extern void EE_CAX_801_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 802) && (EE_CAX_MAX_ARCH_ISR_ID >= 802) && defined(EE_CAX_802_ISR))
extern void EE_CAX_802_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 803) && (EE_CAX_MAX_ARCH_ISR_ID >= 803) && defined(EE_CAX_803_ISR))
extern void EE_CAX_803_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 804) && (EE_CAX_MAX_ARCH_ISR_ID >= 804) && defined(EE_CAX_804_ISR))
extern void EE_CAX_804_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 805) && (EE_CAX_MAX_ARCH_ISR_ID >= 805) && defined(EE_CAX_805_ISR))
extern void EE_CAX_805_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 806) && (EE_CAX_MAX_ARCH_ISR_ID >= 806) && defined(EE_CAX_806_ISR))
extern void EE_CAX_806_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 807) && (EE_CAX_MAX_ARCH_ISR_ID >= 807) && defined(EE_CAX_807_ISR))
extern void EE_CAX_807_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 808) && (EE_CAX_MAX_ARCH_ISR_ID >= 808) && defined(EE_CAX_808_ISR))
extern void EE_CAX_808_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 809) && (EE_CAX_MAX_ARCH_ISR_ID >= 809) && defined(EE_CAX_809_ISR))
extern void EE_CAX_809_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 810) && (EE_CAX_MAX_ARCH_ISR_ID >= 810) && defined(EE_CAX_810_ISR))
extern void EE_CAX_810_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 811) && (EE_CAX_MAX_ARCH_ISR_ID >= 811) && defined(EE_CAX_811_ISR))
extern void EE_CAX_811_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 812) && (EE_CAX_MAX_ARCH_ISR_ID >= 812) && defined(EE_CAX_812_ISR))
extern void EE_CAX_812_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 813) && (EE_CAX_MAX_ARCH_ISR_ID >= 813) && defined(EE_CAX_813_ISR))
extern void EE_CAX_813_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 814) && (EE_CAX_MAX_ARCH_ISR_ID >= 814) && defined(EE_CAX_814_ISR))
extern void EE_CAX_814_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 815) && (EE_CAX_MAX_ARCH_ISR_ID >= 815) && defined(EE_CAX_815_ISR))
extern void EE_CAX_815_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 816) && (EE_CAX_MAX_ARCH_ISR_ID >= 816) && defined(EE_CAX_816_ISR))
extern void EE_CAX_816_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 817) && (EE_CAX_MAX_ARCH_ISR_ID >= 817) && defined(EE_CAX_817_ISR))
extern void EE_CAX_817_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 818) && (EE_CAX_MAX_ARCH_ISR_ID >= 818) && defined(EE_CAX_818_ISR))
extern void EE_CAX_818_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 819) && (EE_CAX_MAX_ARCH_ISR_ID >= 819) && defined(EE_CAX_819_ISR))
extern void EE_CAX_819_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 820) && (EE_CAX_MAX_ARCH_ISR_ID >= 820) && defined(EE_CAX_820_ISR))
extern void EE_CAX_820_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 821) && (EE_CAX_MAX_ARCH_ISR_ID >= 821) && defined(EE_CAX_821_ISR))
extern void EE_CAX_821_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 822) && (EE_CAX_MAX_ARCH_ISR_ID >= 822) && defined(EE_CAX_822_ISR))
extern void EE_CAX_822_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 823) && (EE_CAX_MAX_ARCH_ISR_ID >= 823) && defined(EE_CAX_823_ISR))
extern void EE_CAX_823_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 824) && (EE_CAX_MAX_ARCH_ISR_ID >= 824) && defined(EE_CAX_824_ISR))
extern void EE_CAX_824_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 825) && (EE_CAX_MAX_ARCH_ISR_ID >= 825) && defined(EE_CAX_825_ISR))
extern void EE_CAX_825_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 826) && (EE_CAX_MAX_ARCH_ISR_ID >= 826) && defined(EE_CAX_826_ISR))
extern void EE_CAX_826_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 827) && (EE_CAX_MAX_ARCH_ISR_ID >= 827) && defined(EE_CAX_827_ISR))
extern void EE_CAX_827_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 828) && (EE_CAX_MAX_ARCH_ISR_ID >= 828) && defined(EE_CAX_828_ISR))
extern void EE_CAX_828_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 829) && (EE_CAX_MAX_ARCH_ISR_ID >= 829) && defined(EE_CAX_829_ISR))
extern void EE_CAX_829_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 830) && (EE_CAX_MAX_ARCH_ISR_ID >= 830) && defined(EE_CAX_830_ISR))
extern void EE_CAX_830_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 831) && (EE_CAX_MAX_ARCH_ISR_ID >= 831) && defined(EE_CAX_831_ISR))
extern void EE_CAX_831_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 832) && (EE_CAX_MAX_ARCH_ISR_ID >= 832) && defined(EE_CAX_832_ISR))
extern void EE_CAX_832_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 833) && (EE_CAX_MAX_ARCH_ISR_ID >= 833) && defined(EE_CAX_833_ISR))
extern void EE_CAX_833_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 834) && (EE_CAX_MAX_ARCH_ISR_ID >= 834) && defined(EE_CAX_834_ISR))
extern void EE_CAX_834_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 835) && (EE_CAX_MAX_ARCH_ISR_ID >= 835) && defined(EE_CAX_835_ISR))
extern void EE_CAX_835_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 836) && (EE_CAX_MAX_ARCH_ISR_ID >= 836) && defined(EE_CAX_836_ISR))
extern void EE_CAX_836_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 837) && (EE_CAX_MAX_ARCH_ISR_ID >= 837) && defined(EE_CAX_837_ISR))
extern void EE_CAX_837_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 838) && (EE_CAX_MAX_ARCH_ISR_ID >= 838) && defined(EE_CAX_838_ISR))
extern void EE_CAX_838_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 839) && (EE_CAX_MAX_ARCH_ISR_ID >= 839) && defined(EE_CAX_839_ISR))
extern void EE_CAX_839_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 840) && (EE_CAX_MAX_ARCH_ISR_ID >= 840) && defined(EE_CAX_840_ISR))
extern void EE_CAX_840_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 841) && (EE_CAX_MAX_ARCH_ISR_ID >= 841) && defined(EE_CAX_841_ISR))
extern void EE_CAX_841_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 842) && (EE_CAX_MAX_ARCH_ISR_ID >= 842) && defined(EE_CAX_842_ISR))
extern void EE_CAX_842_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 843) && (EE_CAX_MAX_ARCH_ISR_ID >= 843) && defined(EE_CAX_843_ISR))
extern void EE_CAX_843_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 844) && (EE_CAX_MAX_ARCH_ISR_ID >= 844) && defined(EE_CAX_844_ISR))
extern void EE_CAX_844_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 845) && (EE_CAX_MAX_ARCH_ISR_ID >= 845) && defined(EE_CAX_845_ISR))
extern void EE_CAX_845_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 846) && (EE_CAX_MAX_ARCH_ISR_ID >= 846) && defined(EE_CAX_846_ISR))
extern void EE_CAX_846_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 847) && (EE_CAX_MAX_ARCH_ISR_ID >= 847) && defined(EE_CAX_847_ISR))
extern void EE_CAX_847_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 848) && (EE_CAX_MAX_ARCH_ISR_ID >= 848) && defined(EE_CAX_848_ISR))
extern void EE_CAX_848_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 849) && (EE_CAX_MAX_ARCH_ISR_ID >= 849) && defined(EE_CAX_849_ISR))
extern void EE_CAX_849_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 850) && (EE_CAX_MAX_ARCH_ISR_ID >= 850) && defined(EE_CAX_850_ISR))
extern void EE_CAX_850_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 851) && (EE_CAX_MAX_ARCH_ISR_ID >= 851) && defined(EE_CAX_851_ISR))
extern void EE_CAX_851_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 852) && (EE_CAX_MAX_ARCH_ISR_ID >= 852) && defined(EE_CAX_852_ISR))
extern void EE_CAX_852_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 853) && (EE_CAX_MAX_ARCH_ISR_ID >= 853) && defined(EE_CAX_853_ISR))
extern void EE_CAX_853_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 854) && (EE_CAX_MAX_ARCH_ISR_ID >= 854) && defined(EE_CAX_854_ISR))
extern void EE_CAX_854_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 855) && (EE_CAX_MAX_ARCH_ISR_ID >= 855) && defined(EE_CAX_855_ISR))
extern void EE_CAX_855_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 856) && (EE_CAX_MAX_ARCH_ISR_ID >= 856) && defined(EE_CAX_856_ISR))
extern void EE_CAX_856_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 857) && (EE_CAX_MAX_ARCH_ISR_ID >= 857) && defined(EE_CAX_857_ISR))
extern void EE_CAX_857_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 858) && (EE_CAX_MAX_ARCH_ISR_ID >= 858) && defined(EE_CAX_858_ISR))
extern void EE_CAX_858_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 859) && (EE_CAX_MAX_ARCH_ISR_ID >= 859) && defined(EE_CAX_859_ISR))
extern void EE_CAX_859_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 860) && (EE_CAX_MAX_ARCH_ISR_ID >= 860) && defined(EE_CAX_860_ISR))
extern void EE_CAX_860_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 861) && (EE_CAX_MAX_ARCH_ISR_ID >= 861) && defined(EE_CAX_861_ISR))
extern void EE_CAX_861_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 862) && (EE_CAX_MAX_ARCH_ISR_ID >= 862) && defined(EE_CAX_862_ISR))
extern void EE_CAX_862_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 863) && (EE_CAX_MAX_ARCH_ISR_ID >= 863) && defined(EE_CAX_863_ISR))
extern void EE_CAX_863_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 864) && (EE_CAX_MAX_ARCH_ISR_ID >= 864) && defined(EE_CAX_864_ISR))
extern void EE_CAX_864_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 865) && (EE_CAX_MAX_ARCH_ISR_ID >= 865) && defined(EE_CAX_865_ISR))
extern void EE_CAX_865_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 866) && (EE_CAX_MAX_ARCH_ISR_ID >= 866) && defined(EE_CAX_866_ISR))
extern void EE_CAX_866_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 867) && (EE_CAX_MAX_ARCH_ISR_ID >= 867) && defined(EE_CAX_867_ISR))
extern void EE_CAX_867_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 868) && (EE_CAX_MAX_ARCH_ISR_ID >= 868) && defined(EE_CAX_868_ISR))
extern void EE_CAX_868_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 869) && (EE_CAX_MAX_ARCH_ISR_ID >= 869) && defined(EE_CAX_869_ISR))
extern void EE_CAX_869_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 870) && (EE_CAX_MAX_ARCH_ISR_ID >= 870) && defined(EE_CAX_870_ISR))
extern void EE_CAX_870_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 871) && (EE_CAX_MAX_ARCH_ISR_ID >= 871) && defined(EE_CAX_871_ISR))
extern void EE_CAX_871_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 872) && (EE_CAX_MAX_ARCH_ISR_ID >= 872) && defined(EE_CAX_872_ISR))
extern void EE_CAX_872_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 873) && (EE_CAX_MAX_ARCH_ISR_ID >= 873) && defined(EE_CAX_873_ISR))
extern void EE_CAX_873_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 874) && (EE_CAX_MAX_ARCH_ISR_ID >= 874) && defined(EE_CAX_874_ISR))
extern void EE_CAX_874_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 875) && (EE_CAX_MAX_ARCH_ISR_ID >= 875) && defined(EE_CAX_875_ISR))
extern void EE_CAX_875_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 876) && (EE_CAX_MAX_ARCH_ISR_ID >= 876) && defined(EE_CAX_876_ISR))
extern void EE_CAX_876_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 877) && (EE_CAX_MAX_ARCH_ISR_ID >= 877) && defined(EE_CAX_877_ISR))
extern void EE_CAX_877_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 878) && (EE_CAX_MAX_ARCH_ISR_ID >= 878) && defined(EE_CAX_878_ISR))
extern void EE_CAX_878_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 879) && (EE_CAX_MAX_ARCH_ISR_ID >= 879) && defined(EE_CAX_879_ISR))
extern void EE_CAX_879_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 880) && (EE_CAX_MAX_ARCH_ISR_ID >= 880) && defined(EE_CAX_880_ISR))
extern void EE_CAX_880_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 881) && (EE_CAX_MAX_ARCH_ISR_ID >= 881) && defined(EE_CAX_881_ISR))
extern void EE_CAX_881_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 882) && (EE_CAX_MAX_ARCH_ISR_ID >= 882) && defined(EE_CAX_882_ISR))
extern void EE_CAX_882_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 883) && (EE_CAX_MAX_ARCH_ISR_ID >= 883) && defined(EE_CAX_883_ISR))
extern void EE_CAX_883_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 884) && (EE_CAX_MAX_ARCH_ISR_ID >= 884) && defined(EE_CAX_884_ISR))
extern void EE_CAX_884_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 885) && (EE_CAX_MAX_ARCH_ISR_ID >= 885) && defined(EE_CAX_885_ISR))
extern void EE_CAX_885_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 886) && (EE_CAX_MAX_ARCH_ISR_ID >= 886) && defined(EE_CAX_886_ISR))
extern void EE_CAX_886_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 887) && (EE_CAX_MAX_ARCH_ISR_ID >= 887) && defined(EE_CAX_887_ISR))
extern void EE_CAX_887_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 888) && (EE_CAX_MAX_ARCH_ISR_ID >= 888) && defined(EE_CAX_888_ISR))
extern void EE_CAX_888_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 889) && (EE_CAX_MAX_ARCH_ISR_ID >= 889) && defined(EE_CAX_889_ISR))
extern void EE_CAX_889_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 890) && (EE_CAX_MAX_ARCH_ISR_ID >= 890) && defined(EE_CAX_890_ISR))
extern void EE_CAX_890_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 891) && (EE_CAX_MAX_ARCH_ISR_ID >= 891) && defined(EE_CAX_891_ISR))
extern void EE_CAX_891_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 892) && (EE_CAX_MAX_ARCH_ISR_ID >= 892) && defined(EE_CAX_892_ISR))
extern void EE_CAX_892_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 893) && (EE_CAX_MAX_ARCH_ISR_ID >= 893) && defined(EE_CAX_893_ISR))
extern void EE_CAX_893_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 894) && (EE_CAX_MAX_ARCH_ISR_ID >= 894) && defined(EE_CAX_894_ISR))
extern void EE_CAX_894_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 895) && (EE_CAX_MAX_ARCH_ISR_ID >= 895) && defined(EE_CAX_895_ISR))
extern void EE_CAX_895_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 896) && (EE_CAX_MAX_ARCH_ISR_ID >= 896) && defined(EE_CAX_896_ISR))
extern void EE_CAX_896_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 897) && (EE_CAX_MAX_ARCH_ISR_ID >= 897) && defined(EE_CAX_897_ISR))
extern void EE_CAX_897_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 898) && (EE_CAX_MAX_ARCH_ISR_ID >= 898) && defined(EE_CAX_898_ISR))
extern void EE_CAX_898_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 899) && (EE_CAX_MAX_ARCH_ISR_ID >= 899) && defined(EE_CAX_899_ISR))
extern void EE_CAX_899_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 900) && (EE_CAX_MAX_ARCH_ISR_ID >= 900) && defined(EE_CAX_900_ISR))
extern void EE_CAX_900_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 901) && (EE_CAX_MAX_ARCH_ISR_ID >= 901) && defined(EE_CAX_901_ISR))
extern void EE_CAX_901_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 902) && (EE_CAX_MAX_ARCH_ISR_ID >= 902) && defined(EE_CAX_902_ISR))
extern void EE_CAX_902_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 903) && (EE_CAX_MAX_ARCH_ISR_ID >= 903) && defined(EE_CAX_903_ISR))
extern void EE_CAX_903_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 904) && (EE_CAX_MAX_ARCH_ISR_ID >= 904) && defined(EE_CAX_904_ISR))
extern void EE_CAX_904_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 905) && (EE_CAX_MAX_ARCH_ISR_ID >= 905) && defined(EE_CAX_905_ISR))
extern void EE_CAX_905_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 906) && (EE_CAX_MAX_ARCH_ISR_ID >= 906) && defined(EE_CAX_906_ISR))
extern void EE_CAX_906_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 907) && (EE_CAX_MAX_ARCH_ISR_ID >= 907) && defined(EE_CAX_907_ISR))
extern void EE_CAX_907_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 908) && (EE_CAX_MAX_ARCH_ISR_ID >= 908) && defined(EE_CAX_908_ISR))
extern void EE_CAX_908_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 909) && (EE_CAX_MAX_ARCH_ISR_ID >= 909) && defined(EE_CAX_909_ISR))
extern void EE_CAX_909_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 910) && (EE_CAX_MAX_ARCH_ISR_ID >= 910) && defined(EE_CAX_910_ISR))
extern void EE_CAX_910_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 911) && (EE_CAX_MAX_ARCH_ISR_ID >= 911) && defined(EE_CAX_911_ISR))
extern void EE_CAX_911_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 912) && (EE_CAX_MAX_ARCH_ISR_ID >= 912) && defined(EE_CAX_912_ISR))
extern void EE_CAX_912_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 913) && (EE_CAX_MAX_ARCH_ISR_ID >= 913) && defined(EE_CAX_913_ISR))
extern void EE_CAX_913_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 914) && (EE_CAX_MAX_ARCH_ISR_ID >= 914) && defined(EE_CAX_914_ISR))
extern void EE_CAX_914_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 915) && (EE_CAX_MAX_ARCH_ISR_ID >= 915) && defined(EE_CAX_915_ISR))
extern void EE_CAX_915_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 916) && (EE_CAX_MAX_ARCH_ISR_ID >= 916) && defined(EE_CAX_916_ISR))
extern void EE_CAX_916_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 917) && (EE_CAX_MAX_ARCH_ISR_ID >= 917) && defined(EE_CAX_917_ISR))
extern void EE_CAX_917_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 918) && (EE_CAX_MAX_ARCH_ISR_ID >= 918) && defined(EE_CAX_918_ISR))
extern void EE_CAX_918_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 919) && (EE_CAX_MAX_ARCH_ISR_ID >= 919) && defined(EE_CAX_919_ISR))
extern void EE_CAX_919_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 920) && (EE_CAX_MAX_ARCH_ISR_ID >= 920) && defined(EE_CAX_920_ISR))
extern void EE_CAX_920_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 921) && (EE_CAX_MAX_ARCH_ISR_ID >= 921) && defined(EE_CAX_921_ISR))
extern void EE_CAX_921_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 922) && (EE_CAX_MAX_ARCH_ISR_ID >= 922) && defined(EE_CAX_922_ISR))
extern void EE_CAX_922_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 923) && (EE_CAX_MAX_ARCH_ISR_ID >= 923) && defined(EE_CAX_923_ISR))
extern void EE_CAX_923_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 924) && (EE_CAX_MAX_ARCH_ISR_ID >= 924) && defined(EE_CAX_924_ISR))
extern void EE_CAX_924_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 925) && (EE_CAX_MAX_ARCH_ISR_ID >= 925) && defined(EE_CAX_925_ISR))
extern void EE_CAX_925_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 926) && (EE_CAX_MAX_ARCH_ISR_ID >= 926) && defined(EE_CAX_926_ISR))
extern void EE_CAX_926_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 927) && (EE_CAX_MAX_ARCH_ISR_ID >= 927) && defined(EE_CAX_927_ISR))
extern void EE_CAX_927_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 928) && (EE_CAX_MAX_ARCH_ISR_ID >= 928) && defined(EE_CAX_928_ISR))
extern void EE_CAX_928_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 929) && (EE_CAX_MAX_ARCH_ISR_ID >= 929) && defined(EE_CAX_929_ISR))
extern void EE_CAX_929_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 930) && (EE_CAX_MAX_ARCH_ISR_ID >= 930) && defined(EE_CAX_930_ISR))
extern void EE_CAX_930_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 931) && (EE_CAX_MAX_ARCH_ISR_ID >= 931) && defined(EE_CAX_931_ISR))
extern void EE_CAX_931_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 932) && (EE_CAX_MAX_ARCH_ISR_ID >= 932) && defined(EE_CAX_932_ISR))
extern void EE_CAX_932_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 933) && (EE_CAX_MAX_ARCH_ISR_ID >= 933) && defined(EE_CAX_933_ISR))
extern void EE_CAX_933_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 934) && (EE_CAX_MAX_ARCH_ISR_ID >= 934) && defined(EE_CAX_934_ISR))
extern void EE_CAX_934_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 935) && (EE_CAX_MAX_ARCH_ISR_ID >= 935) && defined(EE_CAX_935_ISR))
extern void EE_CAX_935_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 936) && (EE_CAX_MAX_ARCH_ISR_ID >= 936) && defined(EE_CAX_936_ISR))
extern void EE_CAX_936_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 937) && (EE_CAX_MAX_ARCH_ISR_ID >= 937) && defined(EE_CAX_937_ISR))
extern void EE_CAX_937_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 938) && (EE_CAX_MAX_ARCH_ISR_ID >= 938) && defined(EE_CAX_938_ISR))
extern void EE_CAX_938_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 939) && (EE_CAX_MAX_ARCH_ISR_ID >= 939) && defined(EE_CAX_939_ISR))
extern void EE_CAX_939_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 940) && (EE_CAX_MAX_ARCH_ISR_ID >= 940) && defined(EE_CAX_940_ISR))
extern void EE_CAX_940_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 941) && (EE_CAX_MAX_ARCH_ISR_ID >= 941) && defined(EE_CAX_941_ISR))
extern void EE_CAX_941_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 942) && (EE_CAX_MAX_ARCH_ISR_ID >= 942) && defined(EE_CAX_942_ISR))
extern void EE_CAX_942_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 943) && (EE_CAX_MAX_ARCH_ISR_ID >= 943) && defined(EE_CAX_943_ISR))
extern void EE_CAX_943_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 944) && (EE_CAX_MAX_ARCH_ISR_ID >= 944) && defined(EE_CAX_944_ISR))
extern void EE_CAX_944_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 945) && (EE_CAX_MAX_ARCH_ISR_ID >= 945) && defined(EE_CAX_945_ISR))
extern void EE_CAX_945_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 946) && (EE_CAX_MAX_ARCH_ISR_ID >= 946) && defined(EE_CAX_946_ISR))
extern void EE_CAX_946_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 947) && (EE_CAX_MAX_ARCH_ISR_ID >= 947) && defined(EE_CAX_947_ISR))
extern void EE_CAX_947_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 948) && (EE_CAX_MAX_ARCH_ISR_ID >= 948) && defined(EE_CAX_948_ISR))
extern void EE_CAX_948_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 949) && (EE_CAX_MAX_ARCH_ISR_ID >= 949) && defined(EE_CAX_949_ISR))
extern void EE_CAX_949_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 950) && (EE_CAX_MAX_ARCH_ISR_ID >= 950) && defined(EE_CAX_950_ISR))
extern void EE_CAX_950_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 951) && (EE_CAX_MAX_ARCH_ISR_ID >= 951) && defined(EE_CAX_951_ISR))
extern void EE_CAX_951_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 952) && (EE_CAX_MAX_ARCH_ISR_ID >= 952) && defined(EE_CAX_952_ISR))
extern void EE_CAX_952_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 953) && (EE_CAX_MAX_ARCH_ISR_ID >= 953) && defined(EE_CAX_953_ISR))
extern void EE_CAX_953_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 954) && (EE_CAX_MAX_ARCH_ISR_ID >= 954) && defined(EE_CAX_954_ISR))
extern void EE_CAX_954_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 955) && (EE_CAX_MAX_ARCH_ISR_ID >= 955) && defined(EE_CAX_955_ISR))
extern void EE_CAX_955_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 956) && (EE_CAX_MAX_ARCH_ISR_ID >= 956) && defined(EE_CAX_956_ISR))
extern void EE_CAX_956_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 957) && (EE_CAX_MAX_ARCH_ISR_ID >= 957) && defined(EE_CAX_957_ISR))
extern void EE_CAX_957_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 958) && (EE_CAX_MAX_ARCH_ISR_ID >= 958) && defined(EE_CAX_958_ISR))
extern void EE_CAX_958_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 959) && (EE_CAX_MAX_ARCH_ISR_ID >= 959) && defined(EE_CAX_959_ISR))
extern void EE_CAX_959_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 960) && (EE_CAX_MAX_ARCH_ISR_ID >= 960) && defined(EE_CAX_960_ISR))
extern void EE_CAX_960_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 961) && (EE_CAX_MAX_ARCH_ISR_ID >= 961) && defined(EE_CAX_961_ISR))
extern void EE_CAX_961_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 962) && (EE_CAX_MAX_ARCH_ISR_ID >= 962) && defined(EE_CAX_962_ISR))
extern void EE_CAX_962_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 963) && (EE_CAX_MAX_ARCH_ISR_ID >= 963) && defined(EE_CAX_963_ISR))
extern void EE_CAX_963_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 964) && (EE_CAX_MAX_ARCH_ISR_ID >= 964) && defined(EE_CAX_964_ISR))
extern void EE_CAX_964_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 965) && (EE_CAX_MAX_ARCH_ISR_ID >= 965) && defined(EE_CAX_965_ISR))
extern void EE_CAX_965_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 966) && (EE_CAX_MAX_ARCH_ISR_ID >= 966) && defined(EE_CAX_966_ISR))
extern void EE_CAX_966_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 967) && (EE_CAX_MAX_ARCH_ISR_ID >= 967) && defined(EE_CAX_967_ISR))
extern void EE_CAX_967_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 968) && (EE_CAX_MAX_ARCH_ISR_ID >= 968) && defined(EE_CAX_968_ISR))
extern void EE_CAX_968_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 969) && (EE_CAX_MAX_ARCH_ISR_ID >= 969) && defined(EE_CAX_969_ISR))
extern void EE_CAX_969_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 970) && (EE_CAX_MAX_ARCH_ISR_ID >= 970) && defined(EE_CAX_970_ISR))
extern void EE_CAX_970_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 971) && (EE_CAX_MAX_ARCH_ISR_ID >= 971) && defined(EE_CAX_971_ISR))
extern void EE_CAX_971_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 972) && (EE_CAX_MAX_ARCH_ISR_ID >= 972) && defined(EE_CAX_972_ISR))
extern void EE_CAX_972_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 973) && (EE_CAX_MAX_ARCH_ISR_ID >= 973) && defined(EE_CAX_973_ISR))
extern void EE_CAX_973_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 974) && (EE_CAX_MAX_ARCH_ISR_ID >= 974) && defined(EE_CAX_974_ISR))
extern void EE_CAX_974_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 975) && (EE_CAX_MAX_ARCH_ISR_ID >= 975) && defined(EE_CAX_975_ISR))
extern void EE_CAX_975_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 976) && (EE_CAX_MAX_ARCH_ISR_ID >= 976) && defined(EE_CAX_976_ISR))
extern void EE_CAX_976_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 977) && (EE_CAX_MAX_ARCH_ISR_ID >= 977) && defined(EE_CAX_977_ISR))
extern void EE_CAX_977_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 978) && (EE_CAX_MAX_ARCH_ISR_ID >= 978) && defined(EE_CAX_978_ISR))
extern void EE_CAX_978_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 979) && (EE_CAX_MAX_ARCH_ISR_ID >= 979) && defined(EE_CAX_979_ISR))
extern void EE_CAX_979_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 980) && (EE_CAX_MAX_ARCH_ISR_ID >= 980) && defined(EE_CAX_980_ISR))
extern void EE_CAX_980_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 981) && (EE_CAX_MAX_ARCH_ISR_ID >= 981) && defined(EE_CAX_981_ISR))
extern void EE_CAX_981_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 982) && (EE_CAX_MAX_ARCH_ISR_ID >= 982) && defined(EE_CAX_982_ISR))
extern void EE_CAX_982_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 983) && (EE_CAX_MAX_ARCH_ISR_ID >= 983) && defined(EE_CAX_983_ISR))
extern void EE_CAX_983_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 984) && (EE_CAX_MAX_ARCH_ISR_ID >= 984) && defined(EE_CAX_984_ISR))
extern void EE_CAX_984_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 985) && (EE_CAX_MAX_ARCH_ISR_ID >= 985) && defined(EE_CAX_985_ISR))
extern void EE_CAX_985_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 986) && (EE_CAX_MAX_ARCH_ISR_ID >= 986) && defined(EE_CAX_986_ISR))
extern void EE_CAX_986_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 987) && (EE_CAX_MAX_ARCH_ISR_ID >= 987) && defined(EE_CAX_987_ISR))
extern void EE_CAX_987_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 988) && (EE_CAX_MAX_ARCH_ISR_ID >= 988) && defined(EE_CAX_988_ISR))
extern void EE_CAX_988_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 989) && (EE_CAX_MAX_ARCH_ISR_ID >= 989) && defined(EE_CAX_989_ISR))
extern void EE_CAX_989_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 990) && (EE_CAX_MAX_ARCH_ISR_ID >= 990) && defined(EE_CAX_990_ISR))
extern void EE_CAX_990_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 991) && (EE_CAX_MAX_ARCH_ISR_ID >= 991) && defined(EE_CAX_991_ISR))
extern void EE_CAX_991_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 992) && (EE_CAX_MAX_ARCH_ISR_ID >= 992) && defined(EE_CAX_992_ISR))
extern void EE_CAX_992_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 993) && (EE_CAX_MAX_ARCH_ISR_ID >= 993) && defined(EE_CAX_993_ISR))
extern void EE_CAX_993_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 994) && (EE_CAX_MAX_ARCH_ISR_ID >= 994) && defined(EE_CAX_994_ISR))
extern void EE_CAX_994_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 995) && (EE_CAX_MAX_ARCH_ISR_ID >= 995) && defined(EE_CAX_995_ISR))
extern void EE_CAX_995_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 996) && (EE_CAX_MAX_ARCH_ISR_ID >= 996) && defined(EE_CAX_996_ISR))
extern void EE_CAX_996_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 997) && (EE_CAX_MAX_ARCH_ISR_ID >= 997) && defined(EE_CAX_997_ISR))
extern void EE_CAX_997_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 998) && (EE_CAX_MAX_ARCH_ISR_ID >= 998) && defined(EE_CAX_998_ISR))
extern void EE_CAX_998_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 999) && (EE_CAX_MAX_ARCH_ISR_ID >= 999) && defined(EE_CAX_999_ISR))
extern void EE_CAX_999_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1000) && (EE_CAX_MAX_ARCH_ISR_ID >= 1000) && defined(EE_CAX_1000_ISR))
extern void EE_CAX_1000_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1001) && (EE_CAX_MAX_ARCH_ISR_ID >= 1001) && defined(EE_CAX_1001_ISR))
extern void EE_CAX_1001_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1002) && (EE_CAX_MAX_ARCH_ISR_ID >= 1002) && defined(EE_CAX_1002_ISR))
extern void EE_CAX_1002_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1003) && (EE_CAX_MAX_ARCH_ISR_ID >= 1003) && defined(EE_CAX_1003_ISR))
extern void EE_CAX_1003_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1004) && (EE_CAX_MAX_ARCH_ISR_ID >= 1004) && defined(EE_CAX_1004_ISR))
extern void EE_CAX_1004_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1005) && (EE_CAX_MAX_ARCH_ISR_ID >= 1005) && defined(EE_CAX_1005_ISR))
extern void EE_CAX_1005_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1006) && (EE_CAX_MAX_ARCH_ISR_ID >= 1006) && defined(EE_CAX_1006_ISR))
extern void EE_CAX_1006_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1007) && (EE_CAX_MAX_ARCH_ISR_ID >= 1007) && defined(EE_CAX_1007_ISR))
extern void EE_CAX_1007_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1008) && (EE_CAX_MAX_ARCH_ISR_ID >= 1008) && defined(EE_CAX_1008_ISR))
extern void EE_CAX_1008_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1009) && (EE_CAX_MAX_ARCH_ISR_ID >= 1009) && defined(EE_CAX_1009_ISR))
extern void EE_CAX_1009_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1010) && (EE_CAX_MAX_ARCH_ISR_ID >= 1010) && defined(EE_CAX_1010_ISR))
extern void EE_CAX_1010_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1011) && (EE_CAX_MAX_ARCH_ISR_ID >= 1011) && defined(EE_CAX_1011_ISR))
extern void EE_CAX_1011_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1012) && (EE_CAX_MAX_ARCH_ISR_ID >= 1012) && defined(EE_CAX_1012_ISR))
extern void EE_CAX_1012_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1013) && (EE_CAX_MAX_ARCH_ISR_ID >= 1013) && defined(EE_CAX_1013_ISR))
extern void EE_CAX_1013_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1014) && (EE_CAX_MAX_ARCH_ISR_ID >= 1014) && defined(EE_CAX_1014_ISR))
extern void EE_CAX_1014_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1015) && (EE_CAX_MAX_ARCH_ISR_ID >= 1015) && defined(EE_CAX_1015_ISR))
extern void EE_CAX_1015_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1016) && (EE_CAX_MAX_ARCH_ISR_ID >= 1016) && defined(EE_CAX_1016_ISR))
extern void EE_CAX_1016_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1017) && (EE_CAX_MAX_ARCH_ISR_ID >= 1017) && defined(EE_CAX_1017_ISR))
extern void EE_CAX_1017_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1018) && (EE_CAX_MAX_ARCH_ISR_ID >= 1018) && defined(EE_CAX_1018_ISR))
extern void EE_CAX_1018_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1019) && (EE_CAX_MAX_ARCH_ISR_ID >= 1019) && defined(EE_CAX_1019_ISR))
extern void EE_CAX_1019_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1020) && (EE_CAX_MAX_ARCH_ISR_ID >= 1020) && defined(EE_CAX_1020_ISR))
extern void EE_CAX_1020_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1021) && (EE_CAX_MAX_ARCH_ISR_ID >= 1021) && defined(EE_CAX_1021_ISR))
extern void EE_CAX_1021_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1022) && (EE_CAX_MAX_ARCH_ISR_ID >= 1022) && defined(EE_CAX_1022_ISR))
extern void EE_CAX_1022_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1023) && (EE_CAX_MAX_ARCH_ISR_ID >= 1023) && defined(EE_CAX_1023_ISR))
extern void EE_CAX_1023_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1024) && (EE_CAX_MAX_ARCH_ISR_ID >= 1024) && defined(EE_CAX_1024_ISR))
extern void EE_CAX_1024_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1025) && (EE_CAX_MAX_ARCH_ISR_ID >= 1025) && defined(EE_CAX_1025_ISR))
extern void EE_CAX_1025_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1026) && (EE_CAX_MAX_ARCH_ISR_ID >= 1026) && defined(EE_CAX_1026_ISR))
extern void EE_CAX_1026_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1027) && (EE_CAX_MAX_ARCH_ISR_ID >= 1027) && defined(EE_CAX_1027_ISR))
extern void EE_CAX_1027_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1028) && (EE_CAX_MAX_ARCH_ISR_ID >= 1028) && defined(EE_CAX_1028_ISR))
extern void EE_CAX_1028_ISR (void);
#endif
#if ((EE_CAX_MAX_ISR_ID >= 1029) && (EE_CAX_MAX_ARCH_ISR_ID >= 1029) && defined(EE_CAX_1029_ISR))
extern void EE_CAX_1029_ISR (void);
#endif


EE_ADDR EE_IRQ_HANDLER_TABLE[] = {
#if ((EE_CAX_MAX_ISR_ID >= 0) && (EE_CAX_MAX_ARCH_ISR_ID >= 0))
#if defined(EE_CAX_0_ISR)
EE_CAX_0_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1) && (EE_CAX_MAX_ARCH_ISR_ID >= 1))
#if defined(EE_CAX_1_ISR)
EE_CAX_1_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 2) && (EE_CAX_MAX_ARCH_ISR_ID >= 2))
#if defined(EE_CAX_2_ISR)
EE_CAX_2_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 3) && (EE_CAX_MAX_ARCH_ISR_ID >= 3))
#if defined(EE_CAX_3_ISR)
EE_CAX_3_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 4) && (EE_CAX_MAX_ARCH_ISR_ID >= 4))
#if defined(EE_CAX_4_ISR)
EE_CAX_4_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 5) && (EE_CAX_MAX_ARCH_ISR_ID >= 5))
#if defined(EE_CAX_5_ISR)
EE_CAX_5_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 6) && (EE_CAX_MAX_ARCH_ISR_ID >= 6))
#if defined(EE_CAX_6_ISR)
EE_CAX_6_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 7) && (EE_CAX_MAX_ARCH_ISR_ID >= 7))
#if defined(EE_CAX_7_ISR)
EE_CAX_7_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 8) && (EE_CAX_MAX_ARCH_ISR_ID >= 8))
#if defined(EE_CAX_8_ISR)
EE_CAX_8_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 9) && (EE_CAX_MAX_ARCH_ISR_ID >= 9))
#if defined(EE_CAX_9_ISR)
EE_CAX_9_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 10) && (EE_CAX_MAX_ARCH_ISR_ID >= 10))
#if defined(EE_CAX_10_ISR)
EE_CAX_10_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 11) && (EE_CAX_MAX_ARCH_ISR_ID >= 11))
#if defined(EE_CAX_11_ISR)
EE_CAX_11_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 12) && (EE_CAX_MAX_ARCH_ISR_ID >= 12))
#if defined(EE_CAX_12_ISR)
EE_CAX_12_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 13) && (EE_CAX_MAX_ARCH_ISR_ID >= 13))
#if defined(EE_CAX_13_ISR)
EE_CAX_13_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 14) && (EE_CAX_MAX_ARCH_ISR_ID >= 14))
#if defined(EE_CAX_14_ISR)
EE_CAX_14_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 15) && (EE_CAX_MAX_ARCH_ISR_ID >= 15))
#if defined(EE_CAX_15_ISR)
EE_CAX_15_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 16) && (EE_CAX_MAX_ARCH_ISR_ID >= 16))
#if defined(EE_CAX_16_ISR)
EE_CAX_16_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 17) && (EE_CAX_MAX_ARCH_ISR_ID >= 17))
#if defined(EE_CAX_17_ISR)
EE_CAX_17_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 18) && (EE_CAX_MAX_ARCH_ISR_ID >= 18))
#if defined(EE_CAX_18_ISR)
EE_CAX_18_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 19) && (EE_CAX_MAX_ARCH_ISR_ID >= 19))
#if defined(EE_CAX_19_ISR)
EE_CAX_19_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 20) && (EE_CAX_MAX_ARCH_ISR_ID >= 20))
#if defined(EE_CAX_20_ISR)
EE_CAX_20_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 21) && (EE_CAX_MAX_ARCH_ISR_ID >= 21))
#if defined(EE_CAX_21_ISR)
EE_CAX_21_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 22) && (EE_CAX_MAX_ARCH_ISR_ID >= 22))
#if defined(EE_CAX_22_ISR)
EE_CAX_22_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 23) && (EE_CAX_MAX_ARCH_ISR_ID >= 23))
#if defined(EE_CAX_23_ISR)
EE_CAX_23_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 24) && (EE_CAX_MAX_ARCH_ISR_ID >= 24))
#if defined(EE_CAX_24_ISR)
EE_CAX_24_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 25) && (EE_CAX_MAX_ARCH_ISR_ID >= 25))
#if defined(EE_CAX_25_ISR)
EE_CAX_25_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 26) && (EE_CAX_MAX_ARCH_ISR_ID >= 26))
#if defined(EE_CAX_26_ISR)
EE_CAX_26_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 27) && (EE_CAX_MAX_ARCH_ISR_ID >= 27))
#if defined(EE_CAX_27_ISR)
EE_CAX_27_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 28) && (EE_CAX_MAX_ARCH_ISR_ID >= 28))
#if defined(EE_CAX_28_ISR)
EE_CAX_28_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 29) && (EE_CAX_MAX_ARCH_ISR_ID >= 29))
#if defined(EE_CAX_29_ISR)
EE_CAX_29_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 30) && (EE_CAX_MAX_ARCH_ISR_ID >= 30))
#if defined(EE_CAX_30_ISR)
EE_CAX_30_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 31) && (EE_CAX_MAX_ARCH_ISR_ID >= 31))
#if defined(EE_CAX_31_ISR)
EE_CAX_31_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 32) && (EE_CAX_MAX_ARCH_ISR_ID >= 32))
#if defined(EE_CAX_32_ISR)
EE_CAX_32_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 33) && (EE_CAX_MAX_ARCH_ISR_ID >= 33))
#if defined(EE_CAX_33_ISR)
EE_CAX_33_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 34) && (EE_CAX_MAX_ARCH_ISR_ID >= 34))
#if defined(EE_CAX_34_ISR)
EE_CAX_34_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 35) && (EE_CAX_MAX_ARCH_ISR_ID >= 35))
#if defined(EE_CAX_35_ISR)
EE_CAX_35_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 36) && (EE_CAX_MAX_ARCH_ISR_ID >= 36))
#if defined(EE_CAX_36_ISR)
EE_CAX_36_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 37) && (EE_CAX_MAX_ARCH_ISR_ID >= 37))
#if defined(EE_CAX_37_ISR)
EE_CAX_37_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 38) && (EE_CAX_MAX_ARCH_ISR_ID >= 38))
#if defined(EE_CAX_38_ISR)
EE_CAX_38_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 39) && (EE_CAX_MAX_ARCH_ISR_ID >= 39))
#if defined(EE_CAX_39_ISR)
EE_CAX_39_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 40) && (EE_CAX_MAX_ARCH_ISR_ID >= 40))
#if defined(EE_CAX_40_ISR)
EE_CAX_40_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 41) && (EE_CAX_MAX_ARCH_ISR_ID >= 41))
#if defined(EE_CAX_41_ISR)
EE_CAX_41_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 42) && (EE_CAX_MAX_ARCH_ISR_ID >= 42))
#if defined(EE_CAX_42_ISR)
EE_CAX_42_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 43) && (EE_CAX_MAX_ARCH_ISR_ID >= 43))
#if defined(EE_CAX_43_ISR)
EE_CAX_43_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 44) && (EE_CAX_MAX_ARCH_ISR_ID >= 44))
#if defined(EE_CAX_44_ISR)
EE_CAX_44_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 45) && (EE_CAX_MAX_ARCH_ISR_ID >= 45))
#if defined(EE_CAX_45_ISR)
EE_CAX_45_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 46) && (EE_CAX_MAX_ARCH_ISR_ID >= 46))
#if defined(EE_CAX_46_ISR)
EE_CAX_46_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 47) && (EE_CAX_MAX_ARCH_ISR_ID >= 47))
#if defined(EE_CAX_47_ISR)
EE_CAX_47_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 48) && (EE_CAX_MAX_ARCH_ISR_ID >= 48))
#if defined(EE_CAX_48_ISR)
EE_CAX_48_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 49) && (EE_CAX_MAX_ARCH_ISR_ID >= 49))
#if defined(EE_CAX_49_ISR)
EE_CAX_49_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 50) && (EE_CAX_MAX_ARCH_ISR_ID >= 50))
#if defined(EE_CAX_50_ISR)
EE_CAX_50_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 51) && (EE_CAX_MAX_ARCH_ISR_ID >= 51))
#if defined(EE_CAX_51_ISR)
EE_CAX_51_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 52) && (EE_CAX_MAX_ARCH_ISR_ID >= 52))
#if defined(EE_CAX_52_ISR)
EE_CAX_52_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 53) && (EE_CAX_MAX_ARCH_ISR_ID >= 53))
#if defined(EE_CAX_53_ISR)
EE_CAX_53_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 54) && (EE_CAX_MAX_ARCH_ISR_ID >= 54))
#if defined(EE_CAX_54_ISR)
EE_CAX_54_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 55) && (EE_CAX_MAX_ARCH_ISR_ID >= 55))
#if defined(EE_CAX_55_ISR)
EE_CAX_55_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 56) && (EE_CAX_MAX_ARCH_ISR_ID >= 56))
#if defined(EE_CAX_56_ISR)
EE_CAX_56_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 57) && (EE_CAX_MAX_ARCH_ISR_ID >= 57))
#if defined(EE_CAX_57_ISR)
EE_CAX_57_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 58) && (EE_CAX_MAX_ARCH_ISR_ID >= 58))
#if defined(EE_CAX_58_ISR)
EE_CAX_58_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 59) && (EE_CAX_MAX_ARCH_ISR_ID >= 59))
#if defined(EE_CAX_59_ISR)
EE_CAX_59_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 60) && (EE_CAX_MAX_ARCH_ISR_ID >= 60))
#if defined(EE_CAX_60_ISR)
EE_CAX_60_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 61) && (EE_CAX_MAX_ARCH_ISR_ID >= 61))
#if defined(EE_CAX_61_ISR)
EE_CAX_61_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 62) && (EE_CAX_MAX_ARCH_ISR_ID >= 62))
#if defined(EE_CAX_62_ISR)
EE_CAX_62_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 63) && (EE_CAX_MAX_ARCH_ISR_ID >= 63))
#if defined(EE_CAX_63_ISR)
EE_CAX_63_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 64) && (EE_CAX_MAX_ARCH_ISR_ID >= 64))
#if defined(EE_CAX_64_ISR)
EE_CAX_64_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 65) && (EE_CAX_MAX_ARCH_ISR_ID >= 65))
#if defined(EE_CAX_65_ISR)
EE_CAX_65_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 66) && (EE_CAX_MAX_ARCH_ISR_ID >= 66))
#if defined(EE_CAX_66_ISR)
EE_CAX_66_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 67) && (EE_CAX_MAX_ARCH_ISR_ID >= 67))
#if defined(EE_CAX_67_ISR)
EE_CAX_67_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 68) && (EE_CAX_MAX_ARCH_ISR_ID >= 68))
#if defined(EE_CAX_68_ISR)
EE_CAX_68_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 69) && (EE_CAX_MAX_ARCH_ISR_ID >= 69))
#if defined(EE_CAX_69_ISR)
EE_CAX_69_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 70) && (EE_CAX_MAX_ARCH_ISR_ID >= 70))
#if defined(EE_CAX_70_ISR)
EE_CAX_70_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 71) && (EE_CAX_MAX_ARCH_ISR_ID >= 71))
#if defined(EE_CAX_71_ISR)
EE_CAX_71_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 72) && (EE_CAX_MAX_ARCH_ISR_ID >= 72))
#if defined(EE_CAX_72_ISR)
EE_CAX_72_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 73) && (EE_CAX_MAX_ARCH_ISR_ID >= 73))
#if defined(EE_CAX_73_ISR)
EE_CAX_73_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 74) && (EE_CAX_MAX_ARCH_ISR_ID >= 74))
#if defined(EE_CAX_74_ISR)
EE_CAX_74_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 75) && (EE_CAX_MAX_ARCH_ISR_ID >= 75))
#if defined(EE_CAX_75_ISR)
EE_CAX_75_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 76) && (EE_CAX_MAX_ARCH_ISR_ID >= 76))
#if defined(EE_CAX_76_ISR)
EE_CAX_76_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 77) && (EE_CAX_MAX_ARCH_ISR_ID >= 77))
#if defined(EE_CAX_77_ISR)
EE_CAX_77_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 78) && (EE_CAX_MAX_ARCH_ISR_ID >= 78))
#if defined(EE_CAX_78_ISR)
EE_CAX_78_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 79) && (EE_CAX_MAX_ARCH_ISR_ID >= 79))
#if defined(EE_CAX_79_ISR)
EE_CAX_79_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 80) && (EE_CAX_MAX_ARCH_ISR_ID >= 80))
#if defined(EE_CAX_80_ISR)
EE_CAX_80_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 81) && (EE_CAX_MAX_ARCH_ISR_ID >= 81))
#if defined(EE_CAX_81_ISR)
EE_CAX_81_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 82) && (EE_CAX_MAX_ARCH_ISR_ID >= 82))
#if defined(EE_CAX_82_ISR)
EE_CAX_82_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 83) && (EE_CAX_MAX_ARCH_ISR_ID >= 83))
#if defined(EE_CAX_83_ISR)
EE_CAX_83_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 84) && (EE_CAX_MAX_ARCH_ISR_ID >= 84))
#if defined(EE_CAX_84_ISR)
EE_CAX_84_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 85) && (EE_CAX_MAX_ARCH_ISR_ID >= 85))
#if defined(EE_CAX_85_ISR)
EE_CAX_85_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 86) && (EE_CAX_MAX_ARCH_ISR_ID >= 86))
#if defined(EE_CAX_86_ISR)
EE_CAX_86_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 87) && (EE_CAX_MAX_ARCH_ISR_ID >= 87))
#if defined(EE_CAX_87_ISR)
EE_CAX_87_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 88) && (EE_CAX_MAX_ARCH_ISR_ID >= 88))
#if defined(EE_CAX_88_ISR)
EE_CAX_88_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 89) && (EE_CAX_MAX_ARCH_ISR_ID >= 89))
#if defined(EE_CAX_89_ISR)
EE_CAX_89_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 90) && (EE_CAX_MAX_ARCH_ISR_ID >= 90))
#if defined(EE_CAX_90_ISR)
EE_CAX_90_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 91) && (EE_CAX_MAX_ARCH_ISR_ID >= 91))
#if defined(EE_CAX_91_ISR)
EE_CAX_91_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 92) && (EE_CAX_MAX_ARCH_ISR_ID >= 92))
#if defined(EE_CAX_92_ISR)
EE_CAX_92_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 93) && (EE_CAX_MAX_ARCH_ISR_ID >= 93))
#if defined(EE_CAX_93_ISR)
EE_CAX_93_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 94) && (EE_CAX_MAX_ARCH_ISR_ID >= 94))
#if defined(EE_CAX_94_ISR)
EE_CAX_94_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 95) && (EE_CAX_MAX_ARCH_ISR_ID >= 95))
#if defined(EE_CAX_95_ISR)
EE_CAX_95_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 96) && (EE_CAX_MAX_ARCH_ISR_ID >= 96))
#if defined(EE_CAX_96_ISR)
EE_CAX_96_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 97) && (EE_CAX_MAX_ARCH_ISR_ID >= 97))
#if defined(EE_CAX_97_ISR)
EE_CAX_97_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 98) && (EE_CAX_MAX_ARCH_ISR_ID >= 98))
#if defined(EE_CAX_98_ISR)
EE_CAX_98_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 99) && (EE_CAX_MAX_ARCH_ISR_ID >= 99))
#if defined(EE_CAX_99_ISR)
EE_CAX_99_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 100) && (EE_CAX_MAX_ARCH_ISR_ID >= 100))
#if defined(EE_CAX_100_ISR)
EE_CAX_100_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 101) && (EE_CAX_MAX_ARCH_ISR_ID >= 101))
#if defined(EE_CAX_101_ISR)
EE_CAX_101_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 102) && (EE_CAX_MAX_ARCH_ISR_ID >= 102))
#if defined(EE_CAX_102_ISR)
EE_CAX_102_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 103) && (EE_CAX_MAX_ARCH_ISR_ID >= 103))
#if defined(EE_CAX_103_ISR)
EE_CAX_103_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 104) && (EE_CAX_MAX_ARCH_ISR_ID >= 104))
#if defined(EE_CAX_104_ISR)
EE_CAX_104_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 105) && (EE_CAX_MAX_ARCH_ISR_ID >= 105))
#if defined(EE_CAX_105_ISR)
EE_CAX_105_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 106) && (EE_CAX_MAX_ARCH_ISR_ID >= 106))
#if defined(EE_CAX_106_ISR)
EE_CAX_106_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 107) && (EE_CAX_MAX_ARCH_ISR_ID >= 107))
#if defined(EE_CAX_107_ISR)
EE_CAX_107_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 108) && (EE_CAX_MAX_ARCH_ISR_ID >= 108))
#if defined(EE_CAX_108_ISR)
EE_CAX_108_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 109) && (EE_CAX_MAX_ARCH_ISR_ID >= 109))
#if defined(EE_CAX_109_ISR)
EE_CAX_109_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 110) && (EE_CAX_MAX_ARCH_ISR_ID >= 110))
#if defined(EE_CAX_110_ISR)
EE_CAX_110_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 111) && (EE_CAX_MAX_ARCH_ISR_ID >= 111))
#if defined(EE_CAX_111_ISR)
EE_CAX_111_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 112) && (EE_CAX_MAX_ARCH_ISR_ID >= 112))
#if defined(EE_CAX_112_ISR)
EE_CAX_112_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 113) && (EE_CAX_MAX_ARCH_ISR_ID >= 113))
#if defined(EE_CAX_113_ISR)
EE_CAX_113_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 114) && (EE_CAX_MAX_ARCH_ISR_ID >= 114))
#if defined(EE_CAX_114_ISR)
EE_CAX_114_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 115) && (EE_CAX_MAX_ARCH_ISR_ID >= 115))
#if defined(EE_CAX_115_ISR)
EE_CAX_115_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 116) && (EE_CAX_MAX_ARCH_ISR_ID >= 116))
#if defined(EE_CAX_116_ISR)
EE_CAX_116_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 117) && (EE_CAX_MAX_ARCH_ISR_ID >= 117))
#if defined(EE_CAX_117_ISR)
EE_CAX_117_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 118) && (EE_CAX_MAX_ARCH_ISR_ID >= 118))
#if defined(EE_CAX_118_ISR)
EE_CAX_118_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 119) && (EE_CAX_MAX_ARCH_ISR_ID >= 119))
#if defined(EE_CAX_119_ISR)
EE_CAX_119_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 120) && (EE_CAX_MAX_ARCH_ISR_ID >= 120))
#if defined(EE_CAX_120_ISR)
EE_CAX_120_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 121) && (EE_CAX_MAX_ARCH_ISR_ID >= 121))
#if defined(EE_CAX_121_ISR)
EE_CAX_121_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 122) && (EE_CAX_MAX_ARCH_ISR_ID >= 122))
#if defined(EE_CAX_122_ISR)
EE_CAX_122_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 123) && (EE_CAX_MAX_ARCH_ISR_ID >= 123))
#if defined(EE_CAX_123_ISR)
EE_CAX_123_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 124) && (EE_CAX_MAX_ARCH_ISR_ID >= 124))
#if defined(EE_CAX_124_ISR)
EE_CAX_124_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 125) && (EE_CAX_MAX_ARCH_ISR_ID >= 125))
#if defined(EE_CAX_125_ISR)
EE_CAX_125_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 126) && (EE_CAX_MAX_ARCH_ISR_ID >= 126))
#if defined(EE_CAX_126_ISR)
EE_CAX_126_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 127) && (EE_CAX_MAX_ARCH_ISR_ID >= 127))
#if defined(EE_CAX_127_ISR)
EE_CAX_127_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 128) && (EE_CAX_MAX_ARCH_ISR_ID >= 128))
#if defined(EE_CAX_128_ISR)
EE_CAX_128_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 129) && (EE_CAX_MAX_ARCH_ISR_ID >= 129))
#if defined(EE_CAX_129_ISR)
EE_CAX_129_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 130) && (EE_CAX_MAX_ARCH_ISR_ID >= 130))
#if defined(EE_CAX_130_ISR)
EE_CAX_130_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 131) && (EE_CAX_MAX_ARCH_ISR_ID >= 131))
#if defined(EE_CAX_131_ISR)
EE_CAX_131_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 132) && (EE_CAX_MAX_ARCH_ISR_ID >= 132))
#if defined(EE_CAX_132_ISR)
EE_CAX_132_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 133) && (EE_CAX_MAX_ARCH_ISR_ID >= 133))
#if defined(EE_CAX_133_ISR)
EE_CAX_133_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 134) && (EE_CAX_MAX_ARCH_ISR_ID >= 134))
#if defined(EE_CAX_134_ISR)
EE_CAX_134_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 135) && (EE_CAX_MAX_ARCH_ISR_ID >= 135))
#if defined(EE_CAX_135_ISR)
EE_CAX_135_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 136) && (EE_CAX_MAX_ARCH_ISR_ID >= 136))
#if defined(EE_CAX_136_ISR)
EE_CAX_136_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 137) && (EE_CAX_MAX_ARCH_ISR_ID >= 137))
#if defined(EE_CAX_137_ISR)
EE_CAX_137_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 138) && (EE_CAX_MAX_ARCH_ISR_ID >= 138))
#if defined(EE_CAX_138_ISR)
EE_CAX_138_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 139) && (EE_CAX_MAX_ARCH_ISR_ID >= 139))
#if defined(EE_CAX_139_ISR)
EE_CAX_139_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 140) && (EE_CAX_MAX_ARCH_ISR_ID >= 140))
#if defined(EE_CAX_140_ISR)
EE_CAX_140_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 141) && (EE_CAX_MAX_ARCH_ISR_ID >= 141))
#if defined(EE_CAX_141_ISR)
EE_CAX_141_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 142) && (EE_CAX_MAX_ARCH_ISR_ID >= 142))
#if defined(EE_CAX_142_ISR)
EE_CAX_142_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 143) && (EE_CAX_MAX_ARCH_ISR_ID >= 143))
#if defined(EE_CAX_143_ISR)
EE_CAX_143_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 144) && (EE_CAX_MAX_ARCH_ISR_ID >= 144))
#if defined(EE_CAX_144_ISR)
EE_CAX_144_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 145) && (EE_CAX_MAX_ARCH_ISR_ID >= 145))
#if defined(EE_CAX_145_ISR)
EE_CAX_145_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 146) && (EE_CAX_MAX_ARCH_ISR_ID >= 146))
#if defined(EE_CAX_146_ISR)
EE_CAX_146_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 147) && (EE_CAX_MAX_ARCH_ISR_ID >= 147))
#if defined(EE_CAX_147_ISR)
EE_CAX_147_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 148) && (EE_CAX_MAX_ARCH_ISR_ID >= 148))
#if defined(EE_CAX_148_ISR)
EE_CAX_148_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 149) && (EE_CAX_MAX_ARCH_ISR_ID >= 149))
#if defined(EE_CAX_149_ISR)
EE_CAX_149_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 150) && (EE_CAX_MAX_ARCH_ISR_ID >= 150))
#if defined(EE_CAX_150_ISR)
EE_CAX_150_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 151) && (EE_CAX_MAX_ARCH_ISR_ID >= 151))
#if defined(EE_CAX_151_ISR)
EE_CAX_151_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 152) && (EE_CAX_MAX_ARCH_ISR_ID >= 152))
#if defined(EE_CAX_152_ISR)
EE_CAX_152_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 153) && (EE_CAX_MAX_ARCH_ISR_ID >= 153))
#if defined(EE_CAX_153_ISR)
EE_CAX_153_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 154) && (EE_CAX_MAX_ARCH_ISR_ID >= 154))
#if defined(EE_CAX_154_ISR)
EE_CAX_154_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 155) && (EE_CAX_MAX_ARCH_ISR_ID >= 155))
#if defined(EE_CAX_155_ISR)
EE_CAX_155_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 156) && (EE_CAX_MAX_ARCH_ISR_ID >= 156))
#if defined(EE_CAX_156_ISR)
EE_CAX_156_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 157) && (EE_CAX_MAX_ARCH_ISR_ID >= 157))
#if defined(EE_CAX_157_ISR)
EE_CAX_157_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 158) && (EE_CAX_MAX_ARCH_ISR_ID >= 158))
#if defined(EE_CAX_158_ISR)
EE_CAX_158_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 159) && (EE_CAX_MAX_ARCH_ISR_ID >= 159))
#if defined(EE_CAX_159_ISR)
EE_CAX_159_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 160) && (EE_CAX_MAX_ARCH_ISR_ID >= 160))
#if defined(EE_CAX_160_ISR)
EE_CAX_160_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 161) && (EE_CAX_MAX_ARCH_ISR_ID >= 161))
#if defined(EE_CAX_161_ISR)
EE_CAX_161_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 162) && (EE_CAX_MAX_ARCH_ISR_ID >= 162))
#if defined(EE_CAX_162_ISR)
EE_CAX_162_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 163) && (EE_CAX_MAX_ARCH_ISR_ID >= 163))
#if defined(EE_CAX_163_ISR)
EE_CAX_163_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 164) && (EE_CAX_MAX_ARCH_ISR_ID >= 164))
#if defined(EE_CAX_164_ISR)
EE_CAX_164_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 165) && (EE_CAX_MAX_ARCH_ISR_ID >= 165))
#if defined(EE_CAX_165_ISR)
EE_CAX_165_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 166) && (EE_CAX_MAX_ARCH_ISR_ID >= 166))
#if defined(EE_CAX_166_ISR)
EE_CAX_166_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 167) && (EE_CAX_MAX_ARCH_ISR_ID >= 167))
#if defined(EE_CAX_167_ISR)
EE_CAX_167_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 168) && (EE_CAX_MAX_ARCH_ISR_ID >= 168))
#if defined(EE_CAX_168_ISR)
EE_CAX_168_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 169) && (EE_CAX_MAX_ARCH_ISR_ID >= 169))
#if defined(EE_CAX_169_ISR)
EE_CAX_169_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 170) && (EE_CAX_MAX_ARCH_ISR_ID >= 170))
#if defined(EE_CAX_170_ISR)
EE_CAX_170_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 171) && (EE_CAX_MAX_ARCH_ISR_ID >= 171))
#if defined(EE_CAX_171_ISR)
EE_CAX_171_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 172) && (EE_CAX_MAX_ARCH_ISR_ID >= 172))
#if defined(EE_CAX_172_ISR)
EE_CAX_172_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 173) && (EE_CAX_MAX_ARCH_ISR_ID >= 173))
#if defined(EE_CAX_173_ISR)
EE_CAX_173_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 174) && (EE_CAX_MAX_ARCH_ISR_ID >= 174))
#if defined(EE_CAX_174_ISR)
EE_CAX_174_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 175) && (EE_CAX_MAX_ARCH_ISR_ID >= 175))
#if defined(EE_CAX_175_ISR)
EE_CAX_175_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 176) && (EE_CAX_MAX_ARCH_ISR_ID >= 176))
#if defined(EE_CAX_176_ISR)
EE_CAX_176_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 177) && (EE_CAX_MAX_ARCH_ISR_ID >= 177))
#if defined(EE_CAX_177_ISR)
EE_CAX_177_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 178) && (EE_CAX_MAX_ARCH_ISR_ID >= 178))
#if defined(EE_CAX_178_ISR)
EE_CAX_178_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 179) && (EE_CAX_MAX_ARCH_ISR_ID >= 179))
#if defined(EE_CAX_179_ISR)
EE_CAX_179_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 180) && (EE_CAX_MAX_ARCH_ISR_ID >= 180))
#if defined(EE_CAX_180_ISR)
EE_CAX_180_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 181) && (EE_CAX_MAX_ARCH_ISR_ID >= 181))
#if defined(EE_CAX_181_ISR)
EE_CAX_181_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 182) && (EE_CAX_MAX_ARCH_ISR_ID >= 182))
#if defined(EE_CAX_182_ISR)
EE_CAX_182_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 183) && (EE_CAX_MAX_ARCH_ISR_ID >= 183))
#if defined(EE_CAX_183_ISR)
EE_CAX_183_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 184) && (EE_CAX_MAX_ARCH_ISR_ID >= 184))
#if defined(EE_CAX_184_ISR)
EE_CAX_184_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 185) && (EE_CAX_MAX_ARCH_ISR_ID >= 185))
#if defined(EE_CAX_185_ISR)
EE_CAX_185_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 186) && (EE_CAX_MAX_ARCH_ISR_ID >= 186))
#if defined(EE_CAX_186_ISR)
EE_CAX_186_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 187) && (EE_CAX_MAX_ARCH_ISR_ID >= 187))
#if defined(EE_CAX_187_ISR)
EE_CAX_187_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 188) && (EE_CAX_MAX_ARCH_ISR_ID >= 188))
#if defined(EE_CAX_188_ISR)
EE_CAX_188_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 189) && (EE_CAX_MAX_ARCH_ISR_ID >= 189))
#if defined(EE_CAX_189_ISR)
EE_CAX_189_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 190) && (EE_CAX_MAX_ARCH_ISR_ID >= 190))
#if defined(EE_CAX_190_ISR)
EE_CAX_190_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 191) && (EE_CAX_MAX_ARCH_ISR_ID >= 191))
#if defined(EE_CAX_191_ISR)
EE_CAX_191_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 192) && (EE_CAX_MAX_ARCH_ISR_ID >= 192))
#if defined(EE_CAX_192_ISR)
EE_CAX_192_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 193) && (EE_CAX_MAX_ARCH_ISR_ID >= 193))
#if defined(EE_CAX_193_ISR)
EE_CAX_193_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 194) && (EE_CAX_MAX_ARCH_ISR_ID >= 194))
#if defined(EE_CAX_194_ISR)
EE_CAX_194_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 195) && (EE_CAX_MAX_ARCH_ISR_ID >= 195))
#if defined(EE_CAX_195_ISR)
EE_CAX_195_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 196) && (EE_CAX_MAX_ARCH_ISR_ID >= 196))
#if defined(EE_CAX_196_ISR)
EE_CAX_196_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 197) && (EE_CAX_MAX_ARCH_ISR_ID >= 197))
#if defined(EE_CAX_197_ISR)
EE_CAX_197_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 198) && (EE_CAX_MAX_ARCH_ISR_ID >= 198))
#if defined(EE_CAX_198_ISR)
EE_CAX_198_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 199) && (EE_CAX_MAX_ARCH_ISR_ID >= 199))
#if defined(EE_CAX_199_ISR)
EE_CAX_199_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 200) && (EE_CAX_MAX_ARCH_ISR_ID >= 200))
#if defined(EE_CAX_200_ISR)
EE_CAX_200_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 201) && (EE_CAX_MAX_ARCH_ISR_ID >= 201))
#if defined(EE_CAX_201_ISR)
EE_CAX_201_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 202) && (EE_CAX_MAX_ARCH_ISR_ID >= 202))
#if defined(EE_CAX_202_ISR)
EE_CAX_202_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 203) && (EE_CAX_MAX_ARCH_ISR_ID >= 203))
#if defined(EE_CAX_203_ISR)
EE_CAX_203_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 204) && (EE_CAX_MAX_ARCH_ISR_ID >= 204))
#if defined(EE_CAX_204_ISR)
EE_CAX_204_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 205) && (EE_CAX_MAX_ARCH_ISR_ID >= 205))
#if defined(EE_CAX_205_ISR)
EE_CAX_205_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 206) && (EE_CAX_MAX_ARCH_ISR_ID >= 206))
#if defined(EE_CAX_206_ISR)
EE_CAX_206_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 207) && (EE_CAX_MAX_ARCH_ISR_ID >= 207))
#if defined(EE_CAX_207_ISR)
EE_CAX_207_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 208) && (EE_CAX_MAX_ARCH_ISR_ID >= 208))
#if defined(EE_CAX_208_ISR)
EE_CAX_208_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 209) && (EE_CAX_MAX_ARCH_ISR_ID >= 209))
#if defined(EE_CAX_209_ISR)
EE_CAX_209_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 210) && (EE_CAX_MAX_ARCH_ISR_ID >= 210))
#if defined(EE_CAX_210_ISR)
EE_CAX_210_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 211) && (EE_CAX_MAX_ARCH_ISR_ID >= 211))
#if defined(EE_CAX_211_ISR)
EE_CAX_211_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 212) && (EE_CAX_MAX_ARCH_ISR_ID >= 212))
#if defined(EE_CAX_212_ISR)
EE_CAX_212_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 213) && (EE_CAX_MAX_ARCH_ISR_ID >= 213))
#if defined(EE_CAX_213_ISR)
EE_CAX_213_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 214) && (EE_CAX_MAX_ARCH_ISR_ID >= 214))
#if defined(EE_CAX_214_ISR)
EE_CAX_214_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 215) && (EE_CAX_MAX_ARCH_ISR_ID >= 215))
#if defined(EE_CAX_215_ISR)
EE_CAX_215_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 216) && (EE_CAX_MAX_ARCH_ISR_ID >= 216))
#if defined(EE_CAX_216_ISR)
EE_CAX_216_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 217) && (EE_CAX_MAX_ARCH_ISR_ID >= 217))
#if defined(EE_CAX_217_ISR)
EE_CAX_217_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 218) && (EE_CAX_MAX_ARCH_ISR_ID >= 218))
#if defined(EE_CAX_218_ISR)
EE_CAX_218_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 219) && (EE_CAX_MAX_ARCH_ISR_ID >= 219))
#if defined(EE_CAX_219_ISR)
EE_CAX_219_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 220) && (EE_CAX_MAX_ARCH_ISR_ID >= 220))
#if defined(EE_CAX_220_ISR)
EE_CAX_220_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 221) && (EE_CAX_MAX_ARCH_ISR_ID >= 221))
#if defined(EE_CAX_221_ISR)
EE_CAX_221_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 222) && (EE_CAX_MAX_ARCH_ISR_ID >= 222))
#if defined(EE_CAX_222_ISR)
EE_CAX_222_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 223) && (EE_CAX_MAX_ARCH_ISR_ID >= 223))
#if defined(EE_CAX_223_ISR)
EE_CAX_223_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 224) && (EE_CAX_MAX_ARCH_ISR_ID >= 224))
#if defined(EE_CAX_224_ISR)
EE_CAX_224_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 225) && (EE_CAX_MAX_ARCH_ISR_ID >= 225))
#if defined(EE_CAX_225_ISR)
EE_CAX_225_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 226) && (EE_CAX_MAX_ARCH_ISR_ID >= 226))
#if defined(EE_CAX_226_ISR)
EE_CAX_226_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 227) && (EE_CAX_MAX_ARCH_ISR_ID >= 227))
#if defined(EE_CAX_227_ISR)
EE_CAX_227_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 228) && (EE_CAX_MAX_ARCH_ISR_ID >= 228))
#if defined(EE_CAX_228_ISR)
EE_CAX_228_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 229) && (EE_CAX_MAX_ARCH_ISR_ID >= 229))
#if defined(EE_CAX_229_ISR)
EE_CAX_229_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 230) && (EE_CAX_MAX_ARCH_ISR_ID >= 230))
#if defined(EE_CAX_230_ISR)
EE_CAX_230_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 231) && (EE_CAX_MAX_ARCH_ISR_ID >= 231))
#if defined(EE_CAX_231_ISR)
EE_CAX_231_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 232) && (EE_CAX_MAX_ARCH_ISR_ID >= 232))
#if defined(EE_CAX_232_ISR)
EE_CAX_232_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 233) && (EE_CAX_MAX_ARCH_ISR_ID >= 233))
#if defined(EE_CAX_233_ISR)
EE_CAX_233_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 234) && (EE_CAX_MAX_ARCH_ISR_ID >= 234))
#if defined(EE_CAX_234_ISR)
EE_CAX_234_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 235) && (EE_CAX_MAX_ARCH_ISR_ID >= 235))
#if defined(EE_CAX_235_ISR)
EE_CAX_235_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 236) && (EE_CAX_MAX_ARCH_ISR_ID >= 236))
#if defined(EE_CAX_236_ISR)
EE_CAX_236_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 237) && (EE_CAX_MAX_ARCH_ISR_ID >= 237))
#if defined(EE_CAX_237_ISR)
EE_CAX_237_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 238) && (EE_CAX_MAX_ARCH_ISR_ID >= 238))
#if defined(EE_CAX_238_ISR)
EE_CAX_238_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 239) && (EE_CAX_MAX_ARCH_ISR_ID >= 239))
#if defined(EE_CAX_239_ISR)
EE_CAX_239_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 240) && (EE_CAX_MAX_ARCH_ISR_ID >= 240))
#if defined(EE_CAX_240_ISR)
EE_CAX_240_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 241) && (EE_CAX_MAX_ARCH_ISR_ID >= 241))
#if defined(EE_CAX_241_ISR)
EE_CAX_241_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 242) && (EE_CAX_MAX_ARCH_ISR_ID >= 242))
#if defined(EE_CAX_242_ISR)
EE_CAX_242_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 243) && (EE_CAX_MAX_ARCH_ISR_ID >= 243))
#if defined(EE_CAX_243_ISR)
EE_CAX_243_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 244) && (EE_CAX_MAX_ARCH_ISR_ID >= 244))
#if defined(EE_CAX_244_ISR)
EE_CAX_244_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 245) && (EE_CAX_MAX_ARCH_ISR_ID >= 245))
#if defined(EE_CAX_245_ISR)
EE_CAX_245_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 246) && (EE_CAX_MAX_ARCH_ISR_ID >= 246))
#if defined(EE_CAX_246_ISR)
EE_CAX_246_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 247) && (EE_CAX_MAX_ARCH_ISR_ID >= 247))
#if defined(EE_CAX_247_ISR)
EE_CAX_247_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 248) && (EE_CAX_MAX_ARCH_ISR_ID >= 248))
#if defined(EE_CAX_248_ISR)
EE_CAX_248_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 249) && (EE_CAX_MAX_ARCH_ISR_ID >= 249))
#if defined(EE_CAX_249_ISR)
EE_CAX_249_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 250) && (EE_CAX_MAX_ARCH_ISR_ID >= 250))
#if defined(EE_CAX_250_ISR)
EE_CAX_250_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 251) && (EE_CAX_MAX_ARCH_ISR_ID >= 251))
#if defined(EE_CAX_251_ISR)
EE_CAX_251_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 252) && (EE_CAX_MAX_ARCH_ISR_ID >= 252))
#if defined(EE_CAX_252_ISR)
EE_CAX_252_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 253) && (EE_CAX_MAX_ARCH_ISR_ID >= 253))
#if defined(EE_CAX_253_ISR)
EE_CAX_253_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 254) && (EE_CAX_MAX_ARCH_ISR_ID >= 254))
#if defined(EE_CAX_254_ISR)
EE_CAX_254_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 255) && (EE_CAX_MAX_ARCH_ISR_ID >= 255))
#if defined(EE_CAX_255_ISR)
EE_CAX_255_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 256) && (EE_CAX_MAX_ARCH_ISR_ID >= 256))
#if defined(EE_CAX_256_ISR)
EE_CAX_256_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 257) && (EE_CAX_MAX_ARCH_ISR_ID >= 257))
#if defined(EE_CAX_257_ISR)
EE_CAX_257_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 258) && (EE_CAX_MAX_ARCH_ISR_ID >= 258))
#if defined(EE_CAX_258_ISR)
EE_CAX_258_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 259) && (EE_CAX_MAX_ARCH_ISR_ID >= 259))
#if defined(EE_CAX_259_ISR)
EE_CAX_259_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 260) && (EE_CAX_MAX_ARCH_ISR_ID >= 260))
#if defined(EE_CAX_260_ISR)
EE_CAX_260_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 261) && (EE_CAX_MAX_ARCH_ISR_ID >= 261))
#if defined(EE_CAX_261_ISR)
EE_CAX_261_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 262) && (EE_CAX_MAX_ARCH_ISR_ID >= 262))
#if defined(EE_CAX_262_ISR)
EE_CAX_262_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 263) && (EE_CAX_MAX_ARCH_ISR_ID >= 263))
#if defined(EE_CAX_263_ISR)
EE_CAX_263_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 264) && (EE_CAX_MAX_ARCH_ISR_ID >= 264))
#if defined(EE_CAX_264_ISR)
EE_CAX_264_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 265) && (EE_CAX_MAX_ARCH_ISR_ID >= 265))
#if defined(EE_CAX_265_ISR)
EE_CAX_265_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 266) && (EE_CAX_MAX_ARCH_ISR_ID >= 266))
#if defined(EE_CAX_266_ISR)
EE_CAX_266_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 267) && (EE_CAX_MAX_ARCH_ISR_ID >= 267))
#if defined(EE_CAX_267_ISR)
EE_CAX_267_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 268) && (EE_CAX_MAX_ARCH_ISR_ID >= 268))
#if defined(EE_CAX_268_ISR)
EE_CAX_268_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 269) && (EE_CAX_MAX_ARCH_ISR_ID >= 269))
#if defined(EE_CAX_269_ISR)
EE_CAX_269_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 270) && (EE_CAX_MAX_ARCH_ISR_ID >= 270))
#if defined(EE_CAX_270_ISR)
EE_CAX_270_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 271) && (EE_CAX_MAX_ARCH_ISR_ID >= 271))
#if defined(EE_CAX_271_ISR)
EE_CAX_271_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 272) && (EE_CAX_MAX_ARCH_ISR_ID >= 272))
#if defined(EE_CAX_272_ISR)
EE_CAX_272_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 273) && (EE_CAX_MAX_ARCH_ISR_ID >= 273))
#if defined(EE_CAX_273_ISR)
EE_CAX_273_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 274) && (EE_CAX_MAX_ARCH_ISR_ID >= 274))
#if defined(EE_CAX_274_ISR)
EE_CAX_274_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 275) && (EE_CAX_MAX_ARCH_ISR_ID >= 275))
#if defined(EE_CAX_275_ISR)
EE_CAX_275_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 276) && (EE_CAX_MAX_ARCH_ISR_ID >= 276))
#if defined(EE_CAX_276_ISR)
EE_CAX_276_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 277) && (EE_CAX_MAX_ARCH_ISR_ID >= 277))
#if defined(EE_CAX_277_ISR)
EE_CAX_277_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 278) && (EE_CAX_MAX_ARCH_ISR_ID >= 278))
#if defined(EE_CAX_278_ISR)
EE_CAX_278_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 279) && (EE_CAX_MAX_ARCH_ISR_ID >= 279))
#if defined(EE_CAX_279_ISR)
EE_CAX_279_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 280) && (EE_CAX_MAX_ARCH_ISR_ID >= 280))
#if defined(EE_CAX_280_ISR)
EE_CAX_280_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 281) && (EE_CAX_MAX_ARCH_ISR_ID >= 281))
#if defined(EE_CAX_281_ISR)
EE_CAX_281_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 282) && (EE_CAX_MAX_ARCH_ISR_ID >= 282))
#if defined(EE_CAX_282_ISR)
EE_CAX_282_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 283) && (EE_CAX_MAX_ARCH_ISR_ID >= 283))
#if defined(EE_CAX_283_ISR)
EE_CAX_283_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 284) && (EE_CAX_MAX_ARCH_ISR_ID >= 284))
#if defined(EE_CAX_284_ISR)
EE_CAX_284_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 285) && (EE_CAX_MAX_ARCH_ISR_ID >= 285))
#if defined(EE_CAX_285_ISR)
EE_CAX_285_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 286) && (EE_CAX_MAX_ARCH_ISR_ID >= 286))
#if defined(EE_CAX_286_ISR)
EE_CAX_286_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 287) && (EE_CAX_MAX_ARCH_ISR_ID >= 287))
#if defined(EE_CAX_287_ISR)
EE_CAX_287_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 288) && (EE_CAX_MAX_ARCH_ISR_ID >= 288))
#if defined(EE_CAX_288_ISR)
EE_CAX_288_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 289) && (EE_CAX_MAX_ARCH_ISR_ID >= 289))
#if defined(EE_CAX_289_ISR)
EE_CAX_289_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 290) && (EE_CAX_MAX_ARCH_ISR_ID >= 290))
#if defined(EE_CAX_290_ISR)
EE_CAX_290_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 291) && (EE_CAX_MAX_ARCH_ISR_ID >= 291))
#if defined(EE_CAX_291_ISR)
EE_CAX_291_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 292) && (EE_CAX_MAX_ARCH_ISR_ID >= 292))
#if defined(EE_CAX_292_ISR)
EE_CAX_292_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 293) && (EE_CAX_MAX_ARCH_ISR_ID >= 293))
#if defined(EE_CAX_293_ISR)
EE_CAX_293_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 294) && (EE_CAX_MAX_ARCH_ISR_ID >= 294))
#if defined(EE_CAX_294_ISR)
EE_CAX_294_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 295) && (EE_CAX_MAX_ARCH_ISR_ID >= 295))
#if defined(EE_CAX_295_ISR)
EE_CAX_295_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 296) && (EE_CAX_MAX_ARCH_ISR_ID >= 296))
#if defined(EE_CAX_296_ISR)
EE_CAX_296_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 297) && (EE_CAX_MAX_ARCH_ISR_ID >= 297))
#if defined(EE_CAX_297_ISR)
EE_CAX_297_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 298) && (EE_CAX_MAX_ARCH_ISR_ID >= 298))
#if defined(EE_CAX_298_ISR)
EE_CAX_298_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 299) && (EE_CAX_MAX_ARCH_ISR_ID >= 299))
#if defined(EE_CAX_299_ISR)
EE_CAX_299_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 300) && (EE_CAX_MAX_ARCH_ISR_ID >= 300))
#if defined(EE_CAX_300_ISR)
EE_CAX_300_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 301) && (EE_CAX_MAX_ARCH_ISR_ID >= 301))
#if defined(EE_CAX_301_ISR)
EE_CAX_301_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 302) && (EE_CAX_MAX_ARCH_ISR_ID >= 302))
#if defined(EE_CAX_302_ISR)
EE_CAX_302_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 303) && (EE_CAX_MAX_ARCH_ISR_ID >= 303))
#if defined(EE_CAX_303_ISR)
EE_CAX_303_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 304) && (EE_CAX_MAX_ARCH_ISR_ID >= 304))
#if defined(EE_CAX_304_ISR)
EE_CAX_304_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 305) && (EE_CAX_MAX_ARCH_ISR_ID >= 305))
#if defined(EE_CAX_305_ISR)
EE_CAX_305_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 306) && (EE_CAX_MAX_ARCH_ISR_ID >= 306))
#if defined(EE_CAX_306_ISR)
EE_CAX_306_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 307) && (EE_CAX_MAX_ARCH_ISR_ID >= 307))
#if defined(EE_CAX_307_ISR)
EE_CAX_307_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 308) && (EE_CAX_MAX_ARCH_ISR_ID >= 308))
#if defined(EE_CAX_308_ISR)
EE_CAX_308_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 309) && (EE_CAX_MAX_ARCH_ISR_ID >= 309))
#if defined(EE_CAX_309_ISR)
EE_CAX_309_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 310) && (EE_CAX_MAX_ARCH_ISR_ID >= 310))
#if defined(EE_CAX_310_ISR)
EE_CAX_310_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 311) && (EE_CAX_MAX_ARCH_ISR_ID >= 311))
#if defined(EE_CAX_311_ISR)
EE_CAX_311_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 312) && (EE_CAX_MAX_ARCH_ISR_ID >= 312))
#if defined(EE_CAX_312_ISR)
EE_CAX_312_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 313) && (EE_CAX_MAX_ARCH_ISR_ID >= 313))
#if defined(EE_CAX_313_ISR)
EE_CAX_313_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 314) && (EE_CAX_MAX_ARCH_ISR_ID >= 314))
#if defined(EE_CAX_314_ISR)
EE_CAX_314_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 315) && (EE_CAX_MAX_ARCH_ISR_ID >= 315))
#if defined(EE_CAX_315_ISR)
EE_CAX_315_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 316) && (EE_CAX_MAX_ARCH_ISR_ID >= 316))
#if defined(EE_CAX_316_ISR)
EE_CAX_316_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 317) && (EE_CAX_MAX_ARCH_ISR_ID >= 317))
#if defined(EE_CAX_317_ISR)
EE_CAX_317_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 318) && (EE_CAX_MAX_ARCH_ISR_ID >= 318))
#if defined(EE_CAX_318_ISR)
EE_CAX_318_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 319) && (EE_CAX_MAX_ARCH_ISR_ID >= 319))
#if defined(EE_CAX_319_ISR)
EE_CAX_319_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 320) && (EE_CAX_MAX_ARCH_ISR_ID >= 320))
#if defined(EE_CAX_320_ISR)
EE_CAX_320_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 321) && (EE_CAX_MAX_ARCH_ISR_ID >= 321))
#if defined(EE_CAX_321_ISR)
EE_CAX_321_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 322) && (EE_CAX_MAX_ARCH_ISR_ID >= 322))
#if defined(EE_CAX_322_ISR)
EE_CAX_322_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 323) && (EE_CAX_MAX_ARCH_ISR_ID >= 323))
#if defined(EE_CAX_323_ISR)
EE_CAX_323_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 324) && (EE_CAX_MAX_ARCH_ISR_ID >= 324))
#if defined(EE_CAX_324_ISR)
EE_CAX_324_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 325) && (EE_CAX_MAX_ARCH_ISR_ID >= 325))
#if defined(EE_CAX_325_ISR)
EE_CAX_325_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 326) && (EE_CAX_MAX_ARCH_ISR_ID >= 326))
#if defined(EE_CAX_326_ISR)
EE_CAX_326_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 327) && (EE_CAX_MAX_ARCH_ISR_ID >= 327))
#if defined(EE_CAX_327_ISR)
EE_CAX_327_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 328) && (EE_CAX_MAX_ARCH_ISR_ID >= 328))
#if defined(EE_CAX_328_ISR)
EE_CAX_328_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 329) && (EE_CAX_MAX_ARCH_ISR_ID >= 329))
#if defined(EE_CAX_329_ISR)
EE_CAX_329_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 330) && (EE_CAX_MAX_ARCH_ISR_ID >= 330))
#if defined(EE_CAX_330_ISR)
EE_CAX_330_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 331) && (EE_CAX_MAX_ARCH_ISR_ID >= 331))
#if defined(EE_CAX_331_ISR)
EE_CAX_331_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 332) && (EE_CAX_MAX_ARCH_ISR_ID >= 332))
#if defined(EE_CAX_332_ISR)
EE_CAX_332_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 333) && (EE_CAX_MAX_ARCH_ISR_ID >= 333))
#if defined(EE_CAX_333_ISR)
EE_CAX_333_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 334) && (EE_CAX_MAX_ARCH_ISR_ID >= 334))
#if defined(EE_CAX_334_ISR)
EE_CAX_334_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 335) && (EE_CAX_MAX_ARCH_ISR_ID >= 335))
#if defined(EE_CAX_335_ISR)
EE_CAX_335_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 336) && (EE_CAX_MAX_ARCH_ISR_ID >= 336))
#if defined(EE_CAX_336_ISR)
EE_CAX_336_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 337) && (EE_CAX_MAX_ARCH_ISR_ID >= 337))
#if defined(EE_CAX_337_ISR)
EE_CAX_337_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 338) && (EE_CAX_MAX_ARCH_ISR_ID >= 338))
#if defined(EE_CAX_338_ISR)
EE_CAX_338_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 339) && (EE_CAX_MAX_ARCH_ISR_ID >= 339))
#if defined(EE_CAX_339_ISR)
EE_CAX_339_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 340) && (EE_CAX_MAX_ARCH_ISR_ID >= 340))
#if defined(EE_CAX_340_ISR)
EE_CAX_340_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 341) && (EE_CAX_MAX_ARCH_ISR_ID >= 341))
#if defined(EE_CAX_341_ISR)
EE_CAX_341_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 342) && (EE_CAX_MAX_ARCH_ISR_ID >= 342))
#if defined(EE_CAX_342_ISR)
EE_CAX_342_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 343) && (EE_CAX_MAX_ARCH_ISR_ID >= 343))
#if defined(EE_CAX_343_ISR)
EE_CAX_343_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 344) && (EE_CAX_MAX_ARCH_ISR_ID >= 344))
#if defined(EE_CAX_344_ISR)
EE_CAX_344_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 345) && (EE_CAX_MAX_ARCH_ISR_ID >= 345))
#if defined(EE_CAX_345_ISR)
EE_CAX_345_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 346) && (EE_CAX_MAX_ARCH_ISR_ID >= 346))
#if defined(EE_CAX_346_ISR)
EE_CAX_346_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 347) && (EE_CAX_MAX_ARCH_ISR_ID >= 347))
#if defined(EE_CAX_347_ISR)
EE_CAX_347_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 348) && (EE_CAX_MAX_ARCH_ISR_ID >= 348))
#if defined(EE_CAX_348_ISR)
EE_CAX_348_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 349) && (EE_CAX_MAX_ARCH_ISR_ID >= 349))
#if defined(EE_CAX_349_ISR)
EE_CAX_349_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 350) && (EE_CAX_MAX_ARCH_ISR_ID >= 350))
#if defined(EE_CAX_350_ISR)
EE_CAX_350_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 351) && (EE_CAX_MAX_ARCH_ISR_ID >= 351))
#if defined(EE_CAX_351_ISR)
EE_CAX_351_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 352) && (EE_CAX_MAX_ARCH_ISR_ID >= 352))
#if defined(EE_CAX_352_ISR)
EE_CAX_352_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 353) && (EE_CAX_MAX_ARCH_ISR_ID >= 353))
#if defined(EE_CAX_353_ISR)
EE_CAX_353_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 354) && (EE_CAX_MAX_ARCH_ISR_ID >= 354))
#if defined(EE_CAX_354_ISR)
EE_CAX_354_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 355) && (EE_CAX_MAX_ARCH_ISR_ID >= 355))
#if defined(EE_CAX_355_ISR)
EE_CAX_355_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 356) && (EE_CAX_MAX_ARCH_ISR_ID >= 356))
#if defined(EE_CAX_356_ISR)
EE_CAX_356_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 357) && (EE_CAX_MAX_ARCH_ISR_ID >= 357))
#if defined(EE_CAX_357_ISR)
EE_CAX_357_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 358) && (EE_CAX_MAX_ARCH_ISR_ID >= 358))
#if defined(EE_CAX_358_ISR)
EE_CAX_358_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 359) && (EE_CAX_MAX_ARCH_ISR_ID >= 359))
#if defined(EE_CAX_359_ISR)
EE_CAX_359_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 360) && (EE_CAX_MAX_ARCH_ISR_ID >= 360))
#if defined(EE_CAX_360_ISR)
EE_CAX_360_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 361) && (EE_CAX_MAX_ARCH_ISR_ID >= 361))
#if defined(EE_CAX_361_ISR)
EE_CAX_361_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 362) && (EE_CAX_MAX_ARCH_ISR_ID >= 362))
#if defined(EE_CAX_362_ISR)
EE_CAX_362_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 363) && (EE_CAX_MAX_ARCH_ISR_ID >= 363))
#if defined(EE_CAX_363_ISR)
EE_CAX_363_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 364) && (EE_CAX_MAX_ARCH_ISR_ID >= 364))
#if defined(EE_CAX_364_ISR)
EE_CAX_364_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 365) && (EE_CAX_MAX_ARCH_ISR_ID >= 365))
#if defined(EE_CAX_365_ISR)
EE_CAX_365_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 366) && (EE_CAX_MAX_ARCH_ISR_ID >= 366))
#if defined(EE_CAX_366_ISR)
EE_CAX_366_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 367) && (EE_CAX_MAX_ARCH_ISR_ID >= 367))
#if defined(EE_CAX_367_ISR)
EE_CAX_367_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 368) && (EE_CAX_MAX_ARCH_ISR_ID >= 368))
#if defined(EE_CAX_368_ISR)
EE_CAX_368_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 369) && (EE_CAX_MAX_ARCH_ISR_ID >= 369))
#if defined(EE_CAX_369_ISR)
EE_CAX_369_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 370) && (EE_CAX_MAX_ARCH_ISR_ID >= 370))
#if defined(EE_CAX_370_ISR)
EE_CAX_370_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 371) && (EE_CAX_MAX_ARCH_ISR_ID >= 371))
#if defined(EE_CAX_371_ISR)
EE_CAX_371_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 372) && (EE_CAX_MAX_ARCH_ISR_ID >= 372))
#if defined(EE_CAX_372_ISR)
EE_CAX_372_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 373) && (EE_CAX_MAX_ARCH_ISR_ID >= 373))
#if defined(EE_CAX_373_ISR)
EE_CAX_373_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 374) && (EE_CAX_MAX_ARCH_ISR_ID >= 374))
#if defined(EE_CAX_374_ISR)
EE_CAX_374_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 375) && (EE_CAX_MAX_ARCH_ISR_ID >= 375))
#if defined(EE_CAX_375_ISR)
EE_CAX_375_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 376) && (EE_CAX_MAX_ARCH_ISR_ID >= 376))
#if defined(EE_CAX_376_ISR)
EE_CAX_376_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 377) && (EE_CAX_MAX_ARCH_ISR_ID >= 377))
#if defined(EE_CAX_377_ISR)
EE_CAX_377_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 378) && (EE_CAX_MAX_ARCH_ISR_ID >= 378))
#if defined(EE_CAX_378_ISR)
EE_CAX_378_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 379) && (EE_CAX_MAX_ARCH_ISR_ID >= 379))
#if defined(EE_CAX_379_ISR)
EE_CAX_379_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 380) && (EE_CAX_MAX_ARCH_ISR_ID >= 380))
#if defined(EE_CAX_380_ISR)
EE_CAX_380_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 381) && (EE_CAX_MAX_ARCH_ISR_ID >= 381))
#if defined(EE_CAX_381_ISR)
EE_CAX_381_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 382) && (EE_CAX_MAX_ARCH_ISR_ID >= 382))
#if defined(EE_CAX_382_ISR)
EE_CAX_382_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 383) && (EE_CAX_MAX_ARCH_ISR_ID >= 383))
#if defined(EE_CAX_383_ISR)
EE_CAX_383_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 384) && (EE_CAX_MAX_ARCH_ISR_ID >= 384))
#if defined(EE_CAX_384_ISR)
EE_CAX_384_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 385) && (EE_CAX_MAX_ARCH_ISR_ID >= 385))
#if defined(EE_CAX_385_ISR)
EE_CAX_385_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 386) && (EE_CAX_MAX_ARCH_ISR_ID >= 386))
#if defined(EE_CAX_386_ISR)
EE_CAX_386_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 387) && (EE_CAX_MAX_ARCH_ISR_ID >= 387))
#if defined(EE_CAX_387_ISR)
EE_CAX_387_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 388) && (EE_CAX_MAX_ARCH_ISR_ID >= 388))
#if defined(EE_CAX_388_ISR)
EE_CAX_388_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 389) && (EE_CAX_MAX_ARCH_ISR_ID >= 389))
#if defined(EE_CAX_389_ISR)
EE_CAX_389_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 390) && (EE_CAX_MAX_ARCH_ISR_ID >= 390))
#if defined(EE_CAX_390_ISR)
EE_CAX_390_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 391) && (EE_CAX_MAX_ARCH_ISR_ID >= 391))
#if defined(EE_CAX_391_ISR)
EE_CAX_391_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 392) && (EE_CAX_MAX_ARCH_ISR_ID >= 392))
#if defined(EE_CAX_392_ISR)
EE_CAX_392_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 393) && (EE_CAX_MAX_ARCH_ISR_ID >= 393))
#if defined(EE_CAX_393_ISR)
EE_CAX_393_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 394) && (EE_CAX_MAX_ARCH_ISR_ID >= 394))
#if defined(EE_CAX_394_ISR)
EE_CAX_394_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 395) && (EE_CAX_MAX_ARCH_ISR_ID >= 395))
#if defined(EE_CAX_395_ISR)
EE_CAX_395_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 396) && (EE_CAX_MAX_ARCH_ISR_ID >= 396))
#if defined(EE_CAX_396_ISR)
EE_CAX_396_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 397) && (EE_CAX_MAX_ARCH_ISR_ID >= 397))
#if defined(EE_CAX_397_ISR)
EE_CAX_397_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 398) && (EE_CAX_MAX_ARCH_ISR_ID >= 398))
#if defined(EE_CAX_398_ISR)
EE_CAX_398_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 399) && (EE_CAX_MAX_ARCH_ISR_ID >= 399))
#if defined(EE_CAX_399_ISR)
EE_CAX_399_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 400) && (EE_CAX_MAX_ARCH_ISR_ID >= 400))
#if defined(EE_CAX_400_ISR)
EE_CAX_400_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 401) && (EE_CAX_MAX_ARCH_ISR_ID >= 401))
#if defined(EE_CAX_401_ISR)
EE_CAX_401_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 402) && (EE_CAX_MAX_ARCH_ISR_ID >= 402))
#if defined(EE_CAX_402_ISR)
EE_CAX_402_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 403) && (EE_CAX_MAX_ARCH_ISR_ID >= 403))
#if defined(EE_CAX_403_ISR)
EE_CAX_403_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 404) && (EE_CAX_MAX_ARCH_ISR_ID >= 404))
#if defined(EE_CAX_404_ISR)
EE_CAX_404_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 405) && (EE_CAX_MAX_ARCH_ISR_ID >= 405))
#if defined(EE_CAX_405_ISR)
EE_CAX_405_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 406) && (EE_CAX_MAX_ARCH_ISR_ID >= 406))
#if defined(EE_CAX_406_ISR)
EE_CAX_406_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 407) && (EE_CAX_MAX_ARCH_ISR_ID >= 407))
#if defined(EE_CAX_407_ISR)
EE_CAX_407_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 408) && (EE_CAX_MAX_ARCH_ISR_ID >= 408))
#if defined(EE_CAX_408_ISR)
EE_CAX_408_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 409) && (EE_CAX_MAX_ARCH_ISR_ID >= 409))
#if defined(EE_CAX_409_ISR)
EE_CAX_409_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 410) && (EE_CAX_MAX_ARCH_ISR_ID >= 410))
#if defined(EE_CAX_410_ISR)
EE_CAX_410_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 411) && (EE_CAX_MAX_ARCH_ISR_ID >= 411))
#if defined(EE_CAX_411_ISR)
EE_CAX_411_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 412) && (EE_CAX_MAX_ARCH_ISR_ID >= 412))
#if defined(EE_CAX_412_ISR)
EE_CAX_412_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 413) && (EE_CAX_MAX_ARCH_ISR_ID >= 413))
#if defined(EE_CAX_413_ISR)
EE_CAX_413_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 414) && (EE_CAX_MAX_ARCH_ISR_ID >= 414))
#if defined(EE_CAX_414_ISR)
EE_CAX_414_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 415) && (EE_CAX_MAX_ARCH_ISR_ID >= 415))
#if defined(EE_CAX_415_ISR)
EE_CAX_415_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 416) && (EE_CAX_MAX_ARCH_ISR_ID >= 416))
#if defined(EE_CAX_416_ISR)
EE_CAX_416_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 417) && (EE_CAX_MAX_ARCH_ISR_ID >= 417))
#if defined(EE_CAX_417_ISR)
EE_CAX_417_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 418) && (EE_CAX_MAX_ARCH_ISR_ID >= 418))
#if defined(EE_CAX_418_ISR)
EE_CAX_418_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 419) && (EE_CAX_MAX_ARCH_ISR_ID >= 419))
#if defined(EE_CAX_419_ISR)
EE_CAX_419_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 420) && (EE_CAX_MAX_ARCH_ISR_ID >= 420))
#if defined(EE_CAX_420_ISR)
EE_CAX_420_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 421) && (EE_CAX_MAX_ARCH_ISR_ID >= 421))
#if defined(EE_CAX_421_ISR)
EE_CAX_421_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 422) && (EE_CAX_MAX_ARCH_ISR_ID >= 422))
#if defined(EE_CAX_422_ISR)
EE_CAX_422_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 423) && (EE_CAX_MAX_ARCH_ISR_ID >= 423))
#if defined(EE_CAX_423_ISR)
EE_CAX_423_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 424) && (EE_CAX_MAX_ARCH_ISR_ID >= 424))
#if defined(EE_CAX_424_ISR)
EE_CAX_424_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 425) && (EE_CAX_MAX_ARCH_ISR_ID >= 425))
#if defined(EE_CAX_425_ISR)
EE_CAX_425_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 426) && (EE_CAX_MAX_ARCH_ISR_ID >= 426))
#if defined(EE_CAX_426_ISR)
EE_CAX_426_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 427) && (EE_CAX_MAX_ARCH_ISR_ID >= 427))
#if defined(EE_CAX_427_ISR)
EE_CAX_427_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 428) && (EE_CAX_MAX_ARCH_ISR_ID >= 428))
#if defined(EE_CAX_428_ISR)
EE_CAX_428_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 429) && (EE_CAX_MAX_ARCH_ISR_ID >= 429))
#if defined(EE_CAX_429_ISR)
EE_CAX_429_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 430) && (EE_CAX_MAX_ARCH_ISR_ID >= 430))
#if defined(EE_CAX_430_ISR)
EE_CAX_430_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 431) && (EE_CAX_MAX_ARCH_ISR_ID >= 431))
#if defined(EE_CAX_431_ISR)
EE_CAX_431_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 432) && (EE_CAX_MAX_ARCH_ISR_ID >= 432))
#if defined(EE_CAX_432_ISR)
EE_CAX_432_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 433) && (EE_CAX_MAX_ARCH_ISR_ID >= 433))
#if defined(EE_CAX_433_ISR)
EE_CAX_433_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 434) && (EE_CAX_MAX_ARCH_ISR_ID >= 434))
#if defined(EE_CAX_434_ISR)
EE_CAX_434_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 435) && (EE_CAX_MAX_ARCH_ISR_ID >= 435))
#if defined(EE_CAX_435_ISR)
EE_CAX_435_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 436) && (EE_CAX_MAX_ARCH_ISR_ID >= 436))
#if defined(EE_CAX_436_ISR)
EE_CAX_436_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 437) && (EE_CAX_MAX_ARCH_ISR_ID >= 437))
#if defined(EE_CAX_437_ISR)
EE_CAX_437_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 438) && (EE_CAX_MAX_ARCH_ISR_ID >= 438))
#if defined(EE_CAX_438_ISR)
EE_CAX_438_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 439) && (EE_CAX_MAX_ARCH_ISR_ID >= 439))
#if defined(EE_CAX_439_ISR)
EE_CAX_439_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 440) && (EE_CAX_MAX_ARCH_ISR_ID >= 440))
#if defined(EE_CAX_440_ISR)
EE_CAX_440_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 441) && (EE_CAX_MAX_ARCH_ISR_ID >= 441))
#if defined(EE_CAX_441_ISR)
EE_CAX_441_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 442) && (EE_CAX_MAX_ARCH_ISR_ID >= 442))
#if defined(EE_CAX_442_ISR)
EE_CAX_442_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 443) && (EE_CAX_MAX_ARCH_ISR_ID >= 443))
#if defined(EE_CAX_443_ISR)
EE_CAX_443_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 444) && (EE_CAX_MAX_ARCH_ISR_ID >= 444))
#if defined(EE_CAX_444_ISR)
EE_CAX_444_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 445) && (EE_CAX_MAX_ARCH_ISR_ID >= 445))
#if defined(EE_CAX_445_ISR)
EE_CAX_445_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 446) && (EE_CAX_MAX_ARCH_ISR_ID >= 446))
#if defined(EE_CAX_446_ISR)
EE_CAX_446_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 447) && (EE_CAX_MAX_ARCH_ISR_ID >= 447))
#if defined(EE_CAX_447_ISR)
EE_CAX_447_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 448) && (EE_CAX_MAX_ARCH_ISR_ID >= 448))
#if defined(EE_CAX_448_ISR)
EE_CAX_448_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 449) && (EE_CAX_MAX_ARCH_ISR_ID >= 449))
#if defined(EE_CAX_449_ISR)
EE_CAX_449_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 450) && (EE_CAX_MAX_ARCH_ISR_ID >= 450))
#if defined(EE_CAX_450_ISR)
EE_CAX_450_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 451) && (EE_CAX_MAX_ARCH_ISR_ID >= 451))
#if defined(EE_CAX_451_ISR)
EE_CAX_451_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 452) && (EE_CAX_MAX_ARCH_ISR_ID >= 452))
#if defined(EE_CAX_452_ISR)
EE_CAX_452_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 453) && (EE_CAX_MAX_ARCH_ISR_ID >= 453))
#if defined(EE_CAX_453_ISR)
EE_CAX_453_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 454) && (EE_CAX_MAX_ARCH_ISR_ID >= 454))
#if defined(EE_CAX_454_ISR)
EE_CAX_454_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 455) && (EE_CAX_MAX_ARCH_ISR_ID >= 455))
#if defined(EE_CAX_455_ISR)
EE_CAX_455_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 456) && (EE_CAX_MAX_ARCH_ISR_ID >= 456))
#if defined(EE_CAX_456_ISR)
EE_CAX_456_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 457) && (EE_CAX_MAX_ARCH_ISR_ID >= 457))
#if defined(EE_CAX_457_ISR)
EE_CAX_457_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 458) && (EE_CAX_MAX_ARCH_ISR_ID >= 458))
#if defined(EE_CAX_458_ISR)
EE_CAX_458_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 459) && (EE_CAX_MAX_ARCH_ISR_ID >= 459))
#if defined(EE_CAX_459_ISR)
EE_CAX_459_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 460) && (EE_CAX_MAX_ARCH_ISR_ID >= 460))
#if defined(EE_CAX_460_ISR)
EE_CAX_460_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 461) && (EE_CAX_MAX_ARCH_ISR_ID >= 461))
#if defined(EE_CAX_461_ISR)
EE_CAX_461_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 462) && (EE_CAX_MAX_ARCH_ISR_ID >= 462))
#if defined(EE_CAX_462_ISR)
EE_CAX_462_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 463) && (EE_CAX_MAX_ARCH_ISR_ID >= 463))
#if defined(EE_CAX_463_ISR)
EE_CAX_463_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 464) && (EE_CAX_MAX_ARCH_ISR_ID >= 464))
#if defined(EE_CAX_464_ISR)
EE_CAX_464_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 465) && (EE_CAX_MAX_ARCH_ISR_ID >= 465))
#if defined(EE_CAX_465_ISR)
EE_CAX_465_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 466) && (EE_CAX_MAX_ARCH_ISR_ID >= 466))
#if defined(EE_CAX_466_ISR)
EE_CAX_466_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 467) && (EE_CAX_MAX_ARCH_ISR_ID >= 467))
#if defined(EE_CAX_467_ISR)
EE_CAX_467_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 468) && (EE_CAX_MAX_ARCH_ISR_ID >= 468))
#if defined(EE_CAX_468_ISR)
EE_CAX_468_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 469) && (EE_CAX_MAX_ARCH_ISR_ID >= 469))
#if defined(EE_CAX_469_ISR)
EE_CAX_469_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 470) && (EE_CAX_MAX_ARCH_ISR_ID >= 470))
#if defined(EE_CAX_470_ISR)
EE_CAX_470_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 471) && (EE_CAX_MAX_ARCH_ISR_ID >= 471))
#if defined(EE_CAX_471_ISR)
EE_CAX_471_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 472) && (EE_CAX_MAX_ARCH_ISR_ID >= 472))
#if defined(EE_CAX_472_ISR)
EE_CAX_472_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 473) && (EE_CAX_MAX_ARCH_ISR_ID >= 473))
#if defined(EE_CAX_473_ISR)
EE_CAX_473_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 474) && (EE_CAX_MAX_ARCH_ISR_ID >= 474))
#if defined(EE_CAX_474_ISR)
EE_CAX_474_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 475) && (EE_CAX_MAX_ARCH_ISR_ID >= 475))
#if defined(EE_CAX_475_ISR)
EE_CAX_475_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 476) && (EE_CAX_MAX_ARCH_ISR_ID >= 476))
#if defined(EE_CAX_476_ISR)
EE_CAX_476_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 477) && (EE_CAX_MAX_ARCH_ISR_ID >= 477))
#if defined(EE_CAX_477_ISR)
EE_CAX_477_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 478) && (EE_CAX_MAX_ARCH_ISR_ID >= 478))
#if defined(EE_CAX_478_ISR)
EE_CAX_478_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 479) && (EE_CAX_MAX_ARCH_ISR_ID >= 479))
#if defined(EE_CAX_479_ISR)
EE_CAX_479_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 480) && (EE_CAX_MAX_ARCH_ISR_ID >= 480))
#if defined(EE_CAX_480_ISR)
EE_CAX_480_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 481) && (EE_CAX_MAX_ARCH_ISR_ID >= 481))
#if defined(EE_CAX_481_ISR)
EE_CAX_481_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 482) && (EE_CAX_MAX_ARCH_ISR_ID >= 482))
#if defined(EE_CAX_482_ISR)
EE_CAX_482_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 483) && (EE_CAX_MAX_ARCH_ISR_ID >= 483))
#if defined(EE_CAX_483_ISR)
EE_CAX_483_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 484) && (EE_CAX_MAX_ARCH_ISR_ID >= 484))
#if defined(EE_CAX_484_ISR)
EE_CAX_484_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 485) && (EE_CAX_MAX_ARCH_ISR_ID >= 485))
#if defined(EE_CAX_485_ISR)
EE_CAX_485_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 486) && (EE_CAX_MAX_ARCH_ISR_ID >= 486))
#if defined(EE_CAX_486_ISR)
EE_CAX_486_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 487) && (EE_CAX_MAX_ARCH_ISR_ID >= 487))
#if defined(EE_CAX_487_ISR)
EE_CAX_487_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 488) && (EE_CAX_MAX_ARCH_ISR_ID >= 488))
#if defined(EE_CAX_488_ISR)
EE_CAX_488_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 489) && (EE_CAX_MAX_ARCH_ISR_ID >= 489))
#if defined(EE_CAX_489_ISR)
EE_CAX_489_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 490) && (EE_CAX_MAX_ARCH_ISR_ID >= 490))
#if defined(EE_CAX_490_ISR)
EE_CAX_490_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 491) && (EE_CAX_MAX_ARCH_ISR_ID >= 491))
#if defined(EE_CAX_491_ISR)
EE_CAX_491_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 492) && (EE_CAX_MAX_ARCH_ISR_ID >= 492))
#if defined(EE_CAX_492_ISR)
EE_CAX_492_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 493) && (EE_CAX_MAX_ARCH_ISR_ID >= 493))
#if defined(EE_CAX_493_ISR)
EE_CAX_493_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 494) && (EE_CAX_MAX_ARCH_ISR_ID >= 494))
#if defined(EE_CAX_494_ISR)
EE_CAX_494_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 495) && (EE_CAX_MAX_ARCH_ISR_ID >= 495))
#if defined(EE_CAX_495_ISR)
EE_CAX_495_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 496) && (EE_CAX_MAX_ARCH_ISR_ID >= 496))
#if defined(EE_CAX_496_ISR)
EE_CAX_496_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 497) && (EE_CAX_MAX_ARCH_ISR_ID >= 497))
#if defined(EE_CAX_497_ISR)
EE_CAX_497_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 498) && (EE_CAX_MAX_ARCH_ISR_ID >= 498))
#if defined(EE_CAX_498_ISR)
EE_CAX_498_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 499) && (EE_CAX_MAX_ARCH_ISR_ID >= 499))
#if defined(EE_CAX_499_ISR)
EE_CAX_499_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 500) && (EE_CAX_MAX_ARCH_ISR_ID >= 500))
#if defined(EE_CAX_500_ISR)
EE_CAX_500_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 501) && (EE_CAX_MAX_ARCH_ISR_ID >= 501))
#if defined(EE_CAX_501_ISR)
EE_CAX_501_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 502) && (EE_CAX_MAX_ARCH_ISR_ID >= 502))
#if defined(EE_CAX_502_ISR)
EE_CAX_502_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 503) && (EE_CAX_MAX_ARCH_ISR_ID >= 503))
#if defined(EE_CAX_503_ISR)
EE_CAX_503_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 504) && (EE_CAX_MAX_ARCH_ISR_ID >= 504))
#if defined(EE_CAX_504_ISR)
EE_CAX_504_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 505) && (EE_CAX_MAX_ARCH_ISR_ID >= 505))
#if defined(EE_CAX_505_ISR)
EE_CAX_505_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 506) && (EE_CAX_MAX_ARCH_ISR_ID >= 506))
#if defined(EE_CAX_506_ISR)
EE_CAX_506_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 507) && (EE_CAX_MAX_ARCH_ISR_ID >= 507))
#if defined(EE_CAX_507_ISR)
EE_CAX_507_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 508) && (EE_CAX_MAX_ARCH_ISR_ID >= 508))
#if defined(EE_CAX_508_ISR)
EE_CAX_508_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 509) && (EE_CAX_MAX_ARCH_ISR_ID >= 509))
#if defined(EE_CAX_509_ISR)
EE_CAX_509_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 510) && (EE_CAX_MAX_ARCH_ISR_ID >= 510))
#if defined(EE_CAX_510_ISR)
EE_CAX_510_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 511) && (EE_CAX_MAX_ARCH_ISR_ID >= 511))
#if defined(EE_CAX_511_ISR)
EE_CAX_511_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 512) && (EE_CAX_MAX_ARCH_ISR_ID >= 512))
#if defined(EE_CAX_512_ISR)
EE_CAX_512_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 513) && (EE_CAX_MAX_ARCH_ISR_ID >= 513))
#if defined(EE_CAX_513_ISR)
EE_CAX_513_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 514) && (EE_CAX_MAX_ARCH_ISR_ID >= 514))
#if defined(EE_CAX_514_ISR)
EE_CAX_514_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 515) && (EE_CAX_MAX_ARCH_ISR_ID >= 515))
#if defined(EE_CAX_515_ISR)
EE_CAX_515_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 516) && (EE_CAX_MAX_ARCH_ISR_ID >= 516))
#if defined(EE_CAX_516_ISR)
EE_CAX_516_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 517) && (EE_CAX_MAX_ARCH_ISR_ID >= 517))
#if defined(EE_CAX_517_ISR)
EE_CAX_517_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 518) && (EE_CAX_MAX_ARCH_ISR_ID >= 518))
#if defined(EE_CAX_518_ISR)
EE_CAX_518_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 519) && (EE_CAX_MAX_ARCH_ISR_ID >= 519))
#if defined(EE_CAX_519_ISR)
EE_CAX_519_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 520) && (EE_CAX_MAX_ARCH_ISR_ID >= 520))
#if defined(EE_CAX_520_ISR)
EE_CAX_520_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 521) && (EE_CAX_MAX_ARCH_ISR_ID >= 521))
#if defined(EE_CAX_521_ISR)
EE_CAX_521_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 522) && (EE_CAX_MAX_ARCH_ISR_ID >= 522))
#if defined(EE_CAX_522_ISR)
EE_CAX_522_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 523) && (EE_CAX_MAX_ARCH_ISR_ID >= 523))
#if defined(EE_CAX_523_ISR)
EE_CAX_523_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 524) && (EE_CAX_MAX_ARCH_ISR_ID >= 524))
#if defined(EE_CAX_524_ISR)
EE_CAX_524_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 525) && (EE_CAX_MAX_ARCH_ISR_ID >= 525))
#if defined(EE_CAX_525_ISR)
EE_CAX_525_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 526) && (EE_CAX_MAX_ARCH_ISR_ID >= 526))
#if defined(EE_CAX_526_ISR)
EE_CAX_526_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 527) && (EE_CAX_MAX_ARCH_ISR_ID >= 527))
#if defined(EE_CAX_527_ISR)
EE_CAX_527_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 528) && (EE_CAX_MAX_ARCH_ISR_ID >= 528))
#if defined(EE_CAX_528_ISR)
EE_CAX_528_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 529) && (EE_CAX_MAX_ARCH_ISR_ID >= 529))
#if defined(EE_CAX_529_ISR)
EE_CAX_529_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 530) && (EE_CAX_MAX_ARCH_ISR_ID >= 530))
#if defined(EE_CAX_530_ISR)
EE_CAX_530_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 531) && (EE_CAX_MAX_ARCH_ISR_ID >= 531))
#if defined(EE_CAX_531_ISR)
EE_CAX_531_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 532) && (EE_CAX_MAX_ARCH_ISR_ID >= 532))
#if defined(EE_CAX_532_ISR)
EE_CAX_532_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 533) && (EE_CAX_MAX_ARCH_ISR_ID >= 533))
#if defined(EE_CAX_533_ISR)
EE_CAX_533_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 534) && (EE_CAX_MAX_ARCH_ISR_ID >= 534))
#if defined(EE_CAX_534_ISR)
EE_CAX_534_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 535) && (EE_CAX_MAX_ARCH_ISR_ID >= 535))
#if defined(EE_CAX_535_ISR)
EE_CAX_535_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 536) && (EE_CAX_MAX_ARCH_ISR_ID >= 536))
#if defined(EE_CAX_536_ISR)
EE_CAX_536_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 537) && (EE_CAX_MAX_ARCH_ISR_ID >= 537))
#if defined(EE_CAX_537_ISR)
EE_CAX_537_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 538) && (EE_CAX_MAX_ARCH_ISR_ID >= 538))
#if defined(EE_CAX_538_ISR)
EE_CAX_538_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 539) && (EE_CAX_MAX_ARCH_ISR_ID >= 539))
#if defined(EE_CAX_539_ISR)
EE_CAX_539_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 540) && (EE_CAX_MAX_ARCH_ISR_ID >= 540))
#if defined(EE_CAX_540_ISR)
EE_CAX_540_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 541) && (EE_CAX_MAX_ARCH_ISR_ID >= 541))
#if defined(EE_CAX_541_ISR)
EE_CAX_541_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 542) && (EE_CAX_MAX_ARCH_ISR_ID >= 542))
#if defined(EE_CAX_542_ISR)
EE_CAX_542_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 543) && (EE_CAX_MAX_ARCH_ISR_ID >= 543))
#if defined(EE_CAX_543_ISR)
EE_CAX_543_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 544) && (EE_CAX_MAX_ARCH_ISR_ID >= 544))
#if defined(EE_CAX_544_ISR)
EE_CAX_544_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 545) && (EE_CAX_MAX_ARCH_ISR_ID >= 545))
#if defined(EE_CAX_545_ISR)
EE_CAX_545_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 546) && (EE_CAX_MAX_ARCH_ISR_ID >= 546))
#if defined(EE_CAX_546_ISR)
EE_CAX_546_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 547) && (EE_CAX_MAX_ARCH_ISR_ID >= 547))
#if defined(EE_CAX_547_ISR)
EE_CAX_547_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 548) && (EE_CAX_MAX_ARCH_ISR_ID >= 548))
#if defined(EE_CAX_548_ISR)
EE_CAX_548_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 549) && (EE_CAX_MAX_ARCH_ISR_ID >= 549))
#if defined(EE_CAX_549_ISR)
EE_CAX_549_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 550) && (EE_CAX_MAX_ARCH_ISR_ID >= 550))
#if defined(EE_CAX_550_ISR)
EE_CAX_550_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 551) && (EE_CAX_MAX_ARCH_ISR_ID >= 551))
#if defined(EE_CAX_551_ISR)
EE_CAX_551_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 552) && (EE_CAX_MAX_ARCH_ISR_ID >= 552))
#if defined(EE_CAX_552_ISR)
EE_CAX_552_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 553) && (EE_CAX_MAX_ARCH_ISR_ID >= 553))
#if defined(EE_CAX_553_ISR)
EE_CAX_553_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 554) && (EE_CAX_MAX_ARCH_ISR_ID >= 554))
#if defined(EE_CAX_554_ISR)
EE_CAX_554_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 555) && (EE_CAX_MAX_ARCH_ISR_ID >= 555))
#if defined(EE_CAX_555_ISR)
EE_CAX_555_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 556) && (EE_CAX_MAX_ARCH_ISR_ID >= 556))
#if defined(EE_CAX_556_ISR)
EE_CAX_556_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 557) && (EE_CAX_MAX_ARCH_ISR_ID >= 557))
#if defined(EE_CAX_557_ISR)
EE_CAX_557_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 558) && (EE_CAX_MAX_ARCH_ISR_ID >= 558))
#if defined(EE_CAX_558_ISR)
EE_CAX_558_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 559) && (EE_CAX_MAX_ARCH_ISR_ID >= 559))
#if defined(EE_CAX_559_ISR)
EE_CAX_559_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 560) && (EE_CAX_MAX_ARCH_ISR_ID >= 560))
#if defined(EE_CAX_560_ISR)
EE_CAX_560_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 561) && (EE_CAX_MAX_ARCH_ISR_ID >= 561))
#if defined(EE_CAX_561_ISR)
EE_CAX_561_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 562) && (EE_CAX_MAX_ARCH_ISR_ID >= 562))
#if defined(EE_CAX_562_ISR)
EE_CAX_562_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 563) && (EE_CAX_MAX_ARCH_ISR_ID >= 563))
#if defined(EE_CAX_563_ISR)
EE_CAX_563_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 564) && (EE_CAX_MAX_ARCH_ISR_ID >= 564))
#if defined(EE_CAX_564_ISR)
EE_CAX_564_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 565) && (EE_CAX_MAX_ARCH_ISR_ID >= 565))
#if defined(EE_CAX_565_ISR)
EE_CAX_565_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 566) && (EE_CAX_MAX_ARCH_ISR_ID >= 566))
#if defined(EE_CAX_566_ISR)
EE_CAX_566_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 567) && (EE_CAX_MAX_ARCH_ISR_ID >= 567))
#if defined(EE_CAX_567_ISR)
EE_CAX_567_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 568) && (EE_CAX_MAX_ARCH_ISR_ID >= 568))
#if defined(EE_CAX_568_ISR)
EE_CAX_568_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 569) && (EE_CAX_MAX_ARCH_ISR_ID >= 569))
#if defined(EE_CAX_569_ISR)
EE_CAX_569_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 570) && (EE_CAX_MAX_ARCH_ISR_ID >= 570))
#if defined(EE_CAX_570_ISR)
EE_CAX_570_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 571) && (EE_CAX_MAX_ARCH_ISR_ID >= 571))
#if defined(EE_CAX_571_ISR)
EE_CAX_571_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 572) && (EE_CAX_MAX_ARCH_ISR_ID >= 572))
#if defined(EE_CAX_572_ISR)
EE_CAX_572_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 573) && (EE_CAX_MAX_ARCH_ISR_ID >= 573))
#if defined(EE_CAX_573_ISR)
EE_CAX_573_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 574) && (EE_CAX_MAX_ARCH_ISR_ID >= 574))
#if defined(EE_CAX_574_ISR)
EE_CAX_574_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 575) && (EE_CAX_MAX_ARCH_ISR_ID >= 575))
#if defined(EE_CAX_575_ISR)
EE_CAX_575_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 576) && (EE_CAX_MAX_ARCH_ISR_ID >= 576))
#if defined(EE_CAX_576_ISR)
EE_CAX_576_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 577) && (EE_CAX_MAX_ARCH_ISR_ID >= 577))
#if defined(EE_CAX_577_ISR)
EE_CAX_577_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 578) && (EE_CAX_MAX_ARCH_ISR_ID >= 578))
#if defined(EE_CAX_578_ISR)
EE_CAX_578_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 579) && (EE_CAX_MAX_ARCH_ISR_ID >= 579))
#if defined(EE_CAX_579_ISR)
EE_CAX_579_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 580) && (EE_CAX_MAX_ARCH_ISR_ID >= 580))
#if defined(EE_CAX_580_ISR)
EE_CAX_580_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 581) && (EE_CAX_MAX_ARCH_ISR_ID >= 581))
#if defined(EE_CAX_581_ISR)
EE_CAX_581_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 582) && (EE_CAX_MAX_ARCH_ISR_ID >= 582))
#if defined(EE_CAX_582_ISR)
EE_CAX_582_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 583) && (EE_CAX_MAX_ARCH_ISR_ID >= 583))
#if defined(EE_CAX_583_ISR)
EE_CAX_583_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 584) && (EE_CAX_MAX_ARCH_ISR_ID >= 584))
#if defined(EE_CAX_584_ISR)
EE_CAX_584_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 585) && (EE_CAX_MAX_ARCH_ISR_ID >= 585))
#if defined(EE_CAX_585_ISR)
EE_CAX_585_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 586) && (EE_CAX_MAX_ARCH_ISR_ID >= 586))
#if defined(EE_CAX_586_ISR)
EE_CAX_586_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 587) && (EE_CAX_MAX_ARCH_ISR_ID >= 587))
#if defined(EE_CAX_587_ISR)
EE_CAX_587_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 588) && (EE_CAX_MAX_ARCH_ISR_ID >= 588))
#if defined(EE_CAX_588_ISR)
EE_CAX_588_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 589) && (EE_CAX_MAX_ARCH_ISR_ID >= 589))
#if defined(EE_CAX_589_ISR)
EE_CAX_589_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 590) && (EE_CAX_MAX_ARCH_ISR_ID >= 590))
#if defined(EE_CAX_590_ISR)
EE_CAX_590_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 591) && (EE_CAX_MAX_ARCH_ISR_ID >= 591))
#if defined(EE_CAX_591_ISR)
EE_CAX_591_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 592) && (EE_CAX_MAX_ARCH_ISR_ID >= 592))
#if defined(EE_CAX_592_ISR)
EE_CAX_592_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 593) && (EE_CAX_MAX_ARCH_ISR_ID >= 593))
#if defined(EE_CAX_593_ISR)
EE_CAX_593_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 594) && (EE_CAX_MAX_ARCH_ISR_ID >= 594))
#if defined(EE_CAX_594_ISR)
EE_CAX_594_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 595) && (EE_CAX_MAX_ARCH_ISR_ID >= 595))
#if defined(EE_CAX_595_ISR)
EE_CAX_595_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 596) && (EE_CAX_MAX_ARCH_ISR_ID >= 596))
#if defined(EE_CAX_596_ISR)
EE_CAX_596_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 597) && (EE_CAX_MAX_ARCH_ISR_ID >= 597))
#if defined(EE_CAX_597_ISR)
EE_CAX_597_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 598) && (EE_CAX_MAX_ARCH_ISR_ID >= 598))
#if defined(EE_CAX_598_ISR)
EE_CAX_598_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 599) && (EE_CAX_MAX_ARCH_ISR_ID >= 599))
#if defined(EE_CAX_599_ISR)
EE_CAX_599_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 600) && (EE_CAX_MAX_ARCH_ISR_ID >= 600))
#if defined(EE_CAX_600_ISR)
EE_CAX_600_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 601) && (EE_CAX_MAX_ARCH_ISR_ID >= 601))
#if defined(EE_CAX_601_ISR)
EE_CAX_601_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 602) && (EE_CAX_MAX_ARCH_ISR_ID >= 602))
#if defined(EE_CAX_602_ISR)
EE_CAX_602_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 603) && (EE_CAX_MAX_ARCH_ISR_ID >= 603))
#if defined(EE_CAX_603_ISR)
EE_CAX_603_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 604) && (EE_CAX_MAX_ARCH_ISR_ID >= 604))
#if defined(EE_CAX_604_ISR)
EE_CAX_604_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 605) && (EE_CAX_MAX_ARCH_ISR_ID >= 605))
#if defined(EE_CAX_605_ISR)
EE_CAX_605_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 606) && (EE_CAX_MAX_ARCH_ISR_ID >= 606))
#if defined(EE_CAX_606_ISR)
EE_CAX_606_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 607) && (EE_CAX_MAX_ARCH_ISR_ID >= 607))
#if defined(EE_CAX_607_ISR)
EE_CAX_607_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 608) && (EE_CAX_MAX_ARCH_ISR_ID >= 608))
#if defined(EE_CAX_608_ISR)
EE_CAX_608_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 609) && (EE_CAX_MAX_ARCH_ISR_ID >= 609))
#if defined(EE_CAX_609_ISR)
EE_CAX_609_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 610) && (EE_CAX_MAX_ARCH_ISR_ID >= 610))
#if defined(EE_CAX_610_ISR)
EE_CAX_610_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 611) && (EE_CAX_MAX_ARCH_ISR_ID >= 611))
#if defined(EE_CAX_611_ISR)
EE_CAX_611_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 612) && (EE_CAX_MAX_ARCH_ISR_ID >= 612))
#if defined(EE_CAX_612_ISR)
EE_CAX_612_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 613) && (EE_CAX_MAX_ARCH_ISR_ID >= 613))
#if defined(EE_CAX_613_ISR)
EE_CAX_613_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 614) && (EE_CAX_MAX_ARCH_ISR_ID >= 614))
#if defined(EE_CAX_614_ISR)
EE_CAX_614_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 615) && (EE_CAX_MAX_ARCH_ISR_ID >= 615))
#if defined(EE_CAX_615_ISR)
EE_CAX_615_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 616) && (EE_CAX_MAX_ARCH_ISR_ID >= 616))
#if defined(EE_CAX_616_ISR)
EE_CAX_616_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 617) && (EE_CAX_MAX_ARCH_ISR_ID >= 617))
#if defined(EE_CAX_617_ISR)
EE_CAX_617_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 618) && (EE_CAX_MAX_ARCH_ISR_ID >= 618))
#if defined(EE_CAX_618_ISR)
EE_CAX_618_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 619) && (EE_CAX_MAX_ARCH_ISR_ID >= 619))
#if defined(EE_CAX_619_ISR)
EE_CAX_619_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 620) && (EE_CAX_MAX_ARCH_ISR_ID >= 620))
#if defined(EE_CAX_620_ISR)
EE_CAX_620_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 621) && (EE_CAX_MAX_ARCH_ISR_ID >= 621))
#if defined(EE_CAX_621_ISR)
EE_CAX_621_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 622) && (EE_CAX_MAX_ARCH_ISR_ID >= 622))
#if defined(EE_CAX_622_ISR)
EE_CAX_622_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 623) && (EE_CAX_MAX_ARCH_ISR_ID >= 623))
#if defined(EE_CAX_623_ISR)
EE_CAX_623_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 624) && (EE_CAX_MAX_ARCH_ISR_ID >= 624))
#if defined(EE_CAX_624_ISR)
EE_CAX_624_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 625) && (EE_CAX_MAX_ARCH_ISR_ID >= 625))
#if defined(EE_CAX_625_ISR)
EE_CAX_625_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 626) && (EE_CAX_MAX_ARCH_ISR_ID >= 626))
#if defined(EE_CAX_626_ISR)
EE_CAX_626_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 627) && (EE_CAX_MAX_ARCH_ISR_ID >= 627))
#if defined(EE_CAX_627_ISR)
EE_CAX_627_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 628) && (EE_CAX_MAX_ARCH_ISR_ID >= 628))
#if defined(EE_CAX_628_ISR)
EE_CAX_628_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 629) && (EE_CAX_MAX_ARCH_ISR_ID >= 629))
#if defined(EE_CAX_629_ISR)
EE_CAX_629_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 630) && (EE_CAX_MAX_ARCH_ISR_ID >= 630))
#if defined(EE_CAX_630_ISR)
EE_CAX_630_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 631) && (EE_CAX_MAX_ARCH_ISR_ID >= 631))
#if defined(EE_CAX_631_ISR)
EE_CAX_631_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 632) && (EE_CAX_MAX_ARCH_ISR_ID >= 632))
#if defined(EE_CAX_632_ISR)
EE_CAX_632_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 633) && (EE_CAX_MAX_ARCH_ISR_ID >= 633))
#if defined(EE_CAX_633_ISR)
EE_CAX_633_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 634) && (EE_CAX_MAX_ARCH_ISR_ID >= 634))
#if defined(EE_CAX_634_ISR)
EE_CAX_634_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 635) && (EE_CAX_MAX_ARCH_ISR_ID >= 635))
#if defined(EE_CAX_635_ISR)
EE_CAX_635_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 636) && (EE_CAX_MAX_ARCH_ISR_ID >= 636))
#if defined(EE_CAX_636_ISR)
EE_CAX_636_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 637) && (EE_CAX_MAX_ARCH_ISR_ID >= 637))
#if defined(EE_CAX_637_ISR)
EE_CAX_637_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 638) && (EE_CAX_MAX_ARCH_ISR_ID >= 638))
#if defined(EE_CAX_638_ISR)
EE_CAX_638_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 639) && (EE_CAX_MAX_ARCH_ISR_ID >= 639))
#if defined(EE_CAX_639_ISR)
EE_CAX_639_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 640) && (EE_CAX_MAX_ARCH_ISR_ID >= 640))
#if defined(EE_CAX_640_ISR)
EE_CAX_640_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 641) && (EE_CAX_MAX_ARCH_ISR_ID >= 641))
#if defined(EE_CAX_641_ISR)
EE_CAX_641_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 642) && (EE_CAX_MAX_ARCH_ISR_ID >= 642))
#if defined(EE_CAX_642_ISR)
EE_CAX_642_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 643) && (EE_CAX_MAX_ARCH_ISR_ID >= 643))
#if defined(EE_CAX_643_ISR)
EE_CAX_643_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 644) && (EE_CAX_MAX_ARCH_ISR_ID >= 644))
#if defined(EE_CAX_644_ISR)
EE_CAX_644_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 645) && (EE_CAX_MAX_ARCH_ISR_ID >= 645))
#if defined(EE_CAX_645_ISR)
EE_CAX_645_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 646) && (EE_CAX_MAX_ARCH_ISR_ID >= 646))
#if defined(EE_CAX_646_ISR)
EE_CAX_646_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 647) && (EE_CAX_MAX_ARCH_ISR_ID >= 647))
#if defined(EE_CAX_647_ISR)
EE_CAX_647_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 648) && (EE_CAX_MAX_ARCH_ISR_ID >= 648))
#if defined(EE_CAX_648_ISR)
EE_CAX_648_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 649) && (EE_CAX_MAX_ARCH_ISR_ID >= 649))
#if defined(EE_CAX_649_ISR)
EE_CAX_649_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 650) && (EE_CAX_MAX_ARCH_ISR_ID >= 650))
#if defined(EE_CAX_650_ISR)
EE_CAX_650_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 651) && (EE_CAX_MAX_ARCH_ISR_ID >= 651))
#if defined(EE_CAX_651_ISR)
EE_CAX_651_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 652) && (EE_CAX_MAX_ARCH_ISR_ID >= 652))
#if defined(EE_CAX_652_ISR)
EE_CAX_652_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 653) && (EE_CAX_MAX_ARCH_ISR_ID >= 653))
#if defined(EE_CAX_653_ISR)
EE_CAX_653_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 654) && (EE_CAX_MAX_ARCH_ISR_ID >= 654))
#if defined(EE_CAX_654_ISR)
EE_CAX_654_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 655) && (EE_CAX_MAX_ARCH_ISR_ID >= 655))
#if defined(EE_CAX_655_ISR)
EE_CAX_655_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 656) && (EE_CAX_MAX_ARCH_ISR_ID >= 656))
#if defined(EE_CAX_656_ISR)
EE_CAX_656_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 657) && (EE_CAX_MAX_ARCH_ISR_ID >= 657))
#if defined(EE_CAX_657_ISR)
EE_CAX_657_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 658) && (EE_CAX_MAX_ARCH_ISR_ID >= 658))
#if defined(EE_CAX_658_ISR)
EE_CAX_658_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 659) && (EE_CAX_MAX_ARCH_ISR_ID >= 659))
#if defined(EE_CAX_659_ISR)
EE_CAX_659_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 660) && (EE_CAX_MAX_ARCH_ISR_ID >= 660))
#if defined(EE_CAX_660_ISR)
EE_CAX_660_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 661) && (EE_CAX_MAX_ARCH_ISR_ID >= 661))
#if defined(EE_CAX_661_ISR)
EE_CAX_661_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 662) && (EE_CAX_MAX_ARCH_ISR_ID >= 662))
#if defined(EE_CAX_662_ISR)
EE_CAX_662_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 663) && (EE_CAX_MAX_ARCH_ISR_ID >= 663))
#if defined(EE_CAX_663_ISR)
EE_CAX_663_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 664) && (EE_CAX_MAX_ARCH_ISR_ID >= 664))
#if defined(EE_CAX_664_ISR)
EE_CAX_664_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 665) && (EE_CAX_MAX_ARCH_ISR_ID >= 665))
#if defined(EE_CAX_665_ISR)
EE_CAX_665_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 666) && (EE_CAX_MAX_ARCH_ISR_ID >= 666))
#if defined(EE_CAX_666_ISR)
EE_CAX_666_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 667) && (EE_CAX_MAX_ARCH_ISR_ID >= 667))
#if defined(EE_CAX_667_ISR)
EE_CAX_667_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 668) && (EE_CAX_MAX_ARCH_ISR_ID >= 668))
#if defined(EE_CAX_668_ISR)
EE_CAX_668_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 669) && (EE_CAX_MAX_ARCH_ISR_ID >= 669))
#if defined(EE_CAX_669_ISR)
EE_CAX_669_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 670) && (EE_CAX_MAX_ARCH_ISR_ID >= 670))
#if defined(EE_CAX_670_ISR)
EE_CAX_670_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 671) && (EE_CAX_MAX_ARCH_ISR_ID >= 671))
#if defined(EE_CAX_671_ISR)
EE_CAX_671_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 672) && (EE_CAX_MAX_ARCH_ISR_ID >= 672))
#if defined(EE_CAX_672_ISR)
EE_CAX_672_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 673) && (EE_CAX_MAX_ARCH_ISR_ID >= 673))
#if defined(EE_CAX_673_ISR)
EE_CAX_673_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 674) && (EE_CAX_MAX_ARCH_ISR_ID >= 674))
#if defined(EE_CAX_674_ISR)
EE_CAX_674_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 675) && (EE_CAX_MAX_ARCH_ISR_ID >= 675))
#if defined(EE_CAX_675_ISR)
EE_CAX_675_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 676) && (EE_CAX_MAX_ARCH_ISR_ID >= 676))
#if defined(EE_CAX_676_ISR)
EE_CAX_676_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 677) && (EE_CAX_MAX_ARCH_ISR_ID >= 677))
#if defined(EE_CAX_677_ISR)
EE_CAX_677_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 678) && (EE_CAX_MAX_ARCH_ISR_ID >= 678))
#if defined(EE_CAX_678_ISR)
EE_CAX_678_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 679) && (EE_CAX_MAX_ARCH_ISR_ID >= 679))
#if defined(EE_CAX_679_ISR)
EE_CAX_679_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 680) && (EE_CAX_MAX_ARCH_ISR_ID >= 680))
#if defined(EE_CAX_680_ISR)
EE_CAX_680_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 681) && (EE_CAX_MAX_ARCH_ISR_ID >= 681))
#if defined(EE_CAX_681_ISR)
EE_CAX_681_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 682) && (EE_CAX_MAX_ARCH_ISR_ID >= 682))
#if defined(EE_CAX_682_ISR)
EE_CAX_682_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 683) && (EE_CAX_MAX_ARCH_ISR_ID >= 683))
#if defined(EE_CAX_683_ISR)
EE_CAX_683_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 684) && (EE_CAX_MAX_ARCH_ISR_ID >= 684))
#if defined(EE_CAX_684_ISR)
EE_CAX_684_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 685) && (EE_CAX_MAX_ARCH_ISR_ID >= 685))
#if defined(EE_CAX_685_ISR)
EE_CAX_685_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 686) && (EE_CAX_MAX_ARCH_ISR_ID >= 686))
#if defined(EE_CAX_686_ISR)
EE_CAX_686_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 687) && (EE_CAX_MAX_ARCH_ISR_ID >= 687))
#if defined(EE_CAX_687_ISR)
EE_CAX_687_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 688) && (EE_CAX_MAX_ARCH_ISR_ID >= 688))
#if defined(EE_CAX_688_ISR)
EE_CAX_688_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 689) && (EE_CAX_MAX_ARCH_ISR_ID >= 689))
#if defined(EE_CAX_689_ISR)
EE_CAX_689_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 690) && (EE_CAX_MAX_ARCH_ISR_ID >= 690))
#if defined(EE_CAX_690_ISR)
EE_CAX_690_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 691) && (EE_CAX_MAX_ARCH_ISR_ID >= 691))
#if defined(EE_CAX_691_ISR)
EE_CAX_691_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 692) && (EE_CAX_MAX_ARCH_ISR_ID >= 692))
#if defined(EE_CAX_692_ISR)
EE_CAX_692_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 693) && (EE_CAX_MAX_ARCH_ISR_ID >= 693))
#if defined(EE_CAX_693_ISR)
EE_CAX_693_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 694) && (EE_CAX_MAX_ARCH_ISR_ID >= 694))
#if defined(EE_CAX_694_ISR)
EE_CAX_694_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 695) && (EE_CAX_MAX_ARCH_ISR_ID >= 695))
#if defined(EE_CAX_695_ISR)
EE_CAX_695_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 696) && (EE_CAX_MAX_ARCH_ISR_ID >= 696))
#if defined(EE_CAX_696_ISR)
EE_CAX_696_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 697) && (EE_CAX_MAX_ARCH_ISR_ID >= 697))
#if defined(EE_CAX_697_ISR)
EE_CAX_697_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 698) && (EE_CAX_MAX_ARCH_ISR_ID >= 698))
#if defined(EE_CAX_698_ISR)
EE_CAX_698_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 699) && (EE_CAX_MAX_ARCH_ISR_ID >= 699))
#if defined(EE_CAX_699_ISR)
EE_CAX_699_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 700) && (EE_CAX_MAX_ARCH_ISR_ID >= 700))
#if defined(EE_CAX_700_ISR)
EE_CAX_700_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 701) && (EE_CAX_MAX_ARCH_ISR_ID >= 701))
#if defined(EE_CAX_701_ISR)
EE_CAX_701_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 702) && (EE_CAX_MAX_ARCH_ISR_ID >= 702))
#if defined(EE_CAX_702_ISR)
EE_CAX_702_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 703) && (EE_CAX_MAX_ARCH_ISR_ID >= 703))
#if defined(EE_CAX_703_ISR)
EE_CAX_703_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 704) && (EE_CAX_MAX_ARCH_ISR_ID >= 704))
#if defined(EE_CAX_704_ISR)
EE_CAX_704_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 705) && (EE_CAX_MAX_ARCH_ISR_ID >= 705))
#if defined(EE_CAX_705_ISR)
EE_CAX_705_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 706) && (EE_CAX_MAX_ARCH_ISR_ID >= 706))
#if defined(EE_CAX_706_ISR)
EE_CAX_706_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 707) && (EE_CAX_MAX_ARCH_ISR_ID >= 707))
#if defined(EE_CAX_707_ISR)
EE_CAX_707_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 708) && (EE_CAX_MAX_ARCH_ISR_ID >= 708))
#if defined(EE_CAX_708_ISR)
EE_CAX_708_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 709) && (EE_CAX_MAX_ARCH_ISR_ID >= 709))
#if defined(EE_CAX_709_ISR)
EE_CAX_709_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 710) && (EE_CAX_MAX_ARCH_ISR_ID >= 710))
#if defined(EE_CAX_710_ISR)
EE_CAX_710_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 711) && (EE_CAX_MAX_ARCH_ISR_ID >= 711))
#if defined(EE_CAX_711_ISR)
EE_CAX_711_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 712) && (EE_CAX_MAX_ARCH_ISR_ID >= 712))
#if defined(EE_CAX_712_ISR)
EE_CAX_712_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 713) && (EE_CAX_MAX_ARCH_ISR_ID >= 713))
#if defined(EE_CAX_713_ISR)
EE_CAX_713_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 714) && (EE_CAX_MAX_ARCH_ISR_ID >= 714))
#if defined(EE_CAX_714_ISR)
EE_CAX_714_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 715) && (EE_CAX_MAX_ARCH_ISR_ID >= 715))
#if defined(EE_CAX_715_ISR)
EE_CAX_715_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 716) && (EE_CAX_MAX_ARCH_ISR_ID >= 716))
#if defined(EE_CAX_716_ISR)
EE_CAX_716_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 717) && (EE_CAX_MAX_ARCH_ISR_ID >= 717))
#if defined(EE_CAX_717_ISR)
EE_CAX_717_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 718) && (EE_CAX_MAX_ARCH_ISR_ID >= 718))
#if defined(EE_CAX_718_ISR)
EE_CAX_718_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 719) && (EE_CAX_MAX_ARCH_ISR_ID >= 719))
#if defined(EE_CAX_719_ISR)
EE_CAX_719_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 720) && (EE_CAX_MAX_ARCH_ISR_ID >= 720))
#if defined(EE_CAX_720_ISR)
EE_CAX_720_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 721) && (EE_CAX_MAX_ARCH_ISR_ID >= 721))
#if defined(EE_CAX_721_ISR)
EE_CAX_721_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 722) && (EE_CAX_MAX_ARCH_ISR_ID >= 722))
#if defined(EE_CAX_722_ISR)
EE_CAX_722_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 723) && (EE_CAX_MAX_ARCH_ISR_ID >= 723))
#if defined(EE_CAX_723_ISR)
EE_CAX_723_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 724) && (EE_CAX_MAX_ARCH_ISR_ID >= 724))
#if defined(EE_CAX_724_ISR)
EE_CAX_724_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 725) && (EE_CAX_MAX_ARCH_ISR_ID >= 725))
#if defined(EE_CAX_725_ISR)
EE_CAX_725_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 726) && (EE_CAX_MAX_ARCH_ISR_ID >= 726))
#if defined(EE_CAX_726_ISR)
EE_CAX_726_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 727) && (EE_CAX_MAX_ARCH_ISR_ID >= 727))
#if defined(EE_CAX_727_ISR)
EE_CAX_727_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 728) && (EE_CAX_MAX_ARCH_ISR_ID >= 728))
#if defined(EE_CAX_728_ISR)
EE_CAX_728_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 729) && (EE_CAX_MAX_ARCH_ISR_ID >= 729))
#if defined(EE_CAX_729_ISR)
EE_CAX_729_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 730) && (EE_CAX_MAX_ARCH_ISR_ID >= 730))
#if defined(EE_CAX_730_ISR)
EE_CAX_730_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 731) && (EE_CAX_MAX_ARCH_ISR_ID >= 731))
#if defined(EE_CAX_731_ISR)
EE_CAX_731_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 732) && (EE_CAX_MAX_ARCH_ISR_ID >= 732))
#if defined(EE_CAX_732_ISR)
EE_CAX_732_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 733) && (EE_CAX_MAX_ARCH_ISR_ID >= 733))
#if defined(EE_CAX_733_ISR)
EE_CAX_733_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 734) && (EE_CAX_MAX_ARCH_ISR_ID >= 734))
#if defined(EE_CAX_734_ISR)
EE_CAX_734_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 735) && (EE_CAX_MAX_ARCH_ISR_ID >= 735))
#if defined(EE_CAX_735_ISR)
EE_CAX_735_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 736) && (EE_CAX_MAX_ARCH_ISR_ID >= 736))
#if defined(EE_CAX_736_ISR)
EE_CAX_736_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 737) && (EE_CAX_MAX_ARCH_ISR_ID >= 737))
#if defined(EE_CAX_737_ISR)
EE_CAX_737_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 738) && (EE_CAX_MAX_ARCH_ISR_ID >= 738))
#if defined(EE_CAX_738_ISR)
EE_CAX_738_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 739) && (EE_CAX_MAX_ARCH_ISR_ID >= 739))
#if defined(EE_CAX_739_ISR)
EE_CAX_739_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 740) && (EE_CAX_MAX_ARCH_ISR_ID >= 740))
#if defined(EE_CAX_740_ISR)
EE_CAX_740_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 741) && (EE_CAX_MAX_ARCH_ISR_ID >= 741))
#if defined(EE_CAX_741_ISR)
EE_CAX_741_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 742) && (EE_CAX_MAX_ARCH_ISR_ID >= 742))
#if defined(EE_CAX_742_ISR)
EE_CAX_742_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 743) && (EE_CAX_MAX_ARCH_ISR_ID >= 743))
#if defined(EE_CAX_743_ISR)
EE_CAX_743_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 744) && (EE_CAX_MAX_ARCH_ISR_ID >= 744))
#if defined(EE_CAX_744_ISR)
EE_CAX_744_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 745) && (EE_CAX_MAX_ARCH_ISR_ID >= 745))
#if defined(EE_CAX_745_ISR)
EE_CAX_745_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 746) && (EE_CAX_MAX_ARCH_ISR_ID >= 746))
#if defined(EE_CAX_746_ISR)
EE_CAX_746_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 747) && (EE_CAX_MAX_ARCH_ISR_ID >= 747))
#if defined(EE_CAX_747_ISR)
EE_CAX_747_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 748) && (EE_CAX_MAX_ARCH_ISR_ID >= 748))
#if defined(EE_CAX_748_ISR)
EE_CAX_748_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 749) && (EE_CAX_MAX_ARCH_ISR_ID >= 749))
#if defined(EE_CAX_749_ISR)
EE_CAX_749_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 750) && (EE_CAX_MAX_ARCH_ISR_ID >= 750))
#if defined(EE_CAX_750_ISR)
EE_CAX_750_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 751) && (EE_CAX_MAX_ARCH_ISR_ID >= 751))
#if defined(EE_CAX_751_ISR)
EE_CAX_751_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 752) && (EE_CAX_MAX_ARCH_ISR_ID >= 752))
#if defined(EE_CAX_752_ISR)
EE_CAX_752_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 753) && (EE_CAX_MAX_ARCH_ISR_ID >= 753))
#if defined(EE_CAX_753_ISR)
EE_CAX_753_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 754) && (EE_CAX_MAX_ARCH_ISR_ID >= 754))
#if defined(EE_CAX_754_ISR)
EE_CAX_754_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 755) && (EE_CAX_MAX_ARCH_ISR_ID >= 755))
#if defined(EE_CAX_755_ISR)
EE_CAX_755_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 756) && (EE_CAX_MAX_ARCH_ISR_ID >= 756))
#if defined(EE_CAX_756_ISR)
EE_CAX_756_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 757) && (EE_CAX_MAX_ARCH_ISR_ID >= 757))
#if defined(EE_CAX_757_ISR)
EE_CAX_757_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 758) && (EE_CAX_MAX_ARCH_ISR_ID >= 758))
#if defined(EE_CAX_758_ISR)
EE_CAX_758_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 759) && (EE_CAX_MAX_ARCH_ISR_ID >= 759))
#if defined(EE_CAX_759_ISR)
EE_CAX_759_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 760) && (EE_CAX_MAX_ARCH_ISR_ID >= 760))
#if defined(EE_CAX_760_ISR)
EE_CAX_760_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 761) && (EE_CAX_MAX_ARCH_ISR_ID >= 761))
#if defined(EE_CAX_761_ISR)
EE_CAX_761_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 762) && (EE_CAX_MAX_ARCH_ISR_ID >= 762))
#if defined(EE_CAX_762_ISR)
EE_CAX_762_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 763) && (EE_CAX_MAX_ARCH_ISR_ID >= 763))
#if defined(EE_CAX_763_ISR)
EE_CAX_763_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 764) && (EE_CAX_MAX_ARCH_ISR_ID >= 764))
#if defined(EE_CAX_764_ISR)
EE_CAX_764_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 765) && (EE_CAX_MAX_ARCH_ISR_ID >= 765))
#if defined(EE_CAX_765_ISR)
EE_CAX_765_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 766) && (EE_CAX_MAX_ARCH_ISR_ID >= 766))
#if defined(EE_CAX_766_ISR)
EE_CAX_766_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 767) && (EE_CAX_MAX_ARCH_ISR_ID >= 767))
#if defined(EE_CAX_767_ISR)
EE_CAX_767_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 768) && (EE_CAX_MAX_ARCH_ISR_ID >= 768))
#if defined(EE_CAX_768_ISR)
EE_CAX_768_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 769) && (EE_CAX_MAX_ARCH_ISR_ID >= 769))
#if defined(EE_CAX_769_ISR)
EE_CAX_769_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 770) && (EE_CAX_MAX_ARCH_ISR_ID >= 770))
#if defined(EE_CAX_770_ISR)
EE_CAX_770_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 771) && (EE_CAX_MAX_ARCH_ISR_ID >= 771))
#if defined(EE_CAX_771_ISR)
EE_CAX_771_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 772) && (EE_CAX_MAX_ARCH_ISR_ID >= 772))
#if defined(EE_CAX_772_ISR)
EE_CAX_772_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 773) && (EE_CAX_MAX_ARCH_ISR_ID >= 773))
#if defined(EE_CAX_773_ISR)
EE_CAX_773_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 774) && (EE_CAX_MAX_ARCH_ISR_ID >= 774))
#if defined(EE_CAX_774_ISR)
EE_CAX_774_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 775) && (EE_CAX_MAX_ARCH_ISR_ID >= 775))
#if defined(EE_CAX_775_ISR)
EE_CAX_775_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 776) && (EE_CAX_MAX_ARCH_ISR_ID >= 776))
#if defined(EE_CAX_776_ISR)
EE_CAX_776_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 777) && (EE_CAX_MAX_ARCH_ISR_ID >= 777))
#if defined(EE_CAX_777_ISR)
EE_CAX_777_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 778) && (EE_CAX_MAX_ARCH_ISR_ID >= 778))
#if defined(EE_CAX_778_ISR)
EE_CAX_778_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 779) && (EE_CAX_MAX_ARCH_ISR_ID >= 779))
#if defined(EE_CAX_779_ISR)
EE_CAX_779_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 780) && (EE_CAX_MAX_ARCH_ISR_ID >= 780))
#if defined(EE_CAX_780_ISR)
EE_CAX_780_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 781) && (EE_CAX_MAX_ARCH_ISR_ID >= 781))
#if defined(EE_CAX_781_ISR)
EE_CAX_781_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 782) && (EE_CAX_MAX_ARCH_ISR_ID >= 782))
#if defined(EE_CAX_782_ISR)
EE_CAX_782_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 783) && (EE_CAX_MAX_ARCH_ISR_ID >= 783))
#if defined(EE_CAX_783_ISR)
EE_CAX_783_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 784) && (EE_CAX_MAX_ARCH_ISR_ID >= 784))
#if defined(EE_CAX_784_ISR)
EE_CAX_784_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 785) && (EE_CAX_MAX_ARCH_ISR_ID >= 785))
#if defined(EE_CAX_785_ISR)
EE_CAX_785_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 786) && (EE_CAX_MAX_ARCH_ISR_ID >= 786))
#if defined(EE_CAX_786_ISR)
EE_CAX_786_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 787) && (EE_CAX_MAX_ARCH_ISR_ID >= 787))
#if defined(EE_CAX_787_ISR)
EE_CAX_787_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 788) && (EE_CAX_MAX_ARCH_ISR_ID >= 788))
#if defined(EE_CAX_788_ISR)
EE_CAX_788_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 789) && (EE_CAX_MAX_ARCH_ISR_ID >= 789))
#if defined(EE_CAX_789_ISR)
EE_CAX_789_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 790) && (EE_CAX_MAX_ARCH_ISR_ID >= 790))
#if defined(EE_CAX_790_ISR)
EE_CAX_790_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 791) && (EE_CAX_MAX_ARCH_ISR_ID >= 791))
#if defined(EE_CAX_791_ISR)
EE_CAX_791_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 792) && (EE_CAX_MAX_ARCH_ISR_ID >= 792))
#if defined(EE_CAX_792_ISR)
EE_CAX_792_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 793) && (EE_CAX_MAX_ARCH_ISR_ID >= 793))
#if defined(EE_CAX_793_ISR)
EE_CAX_793_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 794) && (EE_CAX_MAX_ARCH_ISR_ID >= 794))
#if defined(EE_CAX_794_ISR)
EE_CAX_794_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 795) && (EE_CAX_MAX_ARCH_ISR_ID >= 795))
#if defined(EE_CAX_795_ISR)
EE_CAX_795_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 796) && (EE_CAX_MAX_ARCH_ISR_ID >= 796))
#if defined(EE_CAX_796_ISR)
EE_CAX_796_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 797) && (EE_CAX_MAX_ARCH_ISR_ID >= 797))
#if defined(EE_CAX_797_ISR)
EE_CAX_797_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 798) && (EE_CAX_MAX_ARCH_ISR_ID >= 798))
#if defined(EE_CAX_798_ISR)
EE_CAX_798_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 799) && (EE_CAX_MAX_ARCH_ISR_ID >= 799))
#if defined(EE_CAX_799_ISR)
EE_CAX_799_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 800) && (EE_CAX_MAX_ARCH_ISR_ID >= 800))
#if defined(EE_CAX_800_ISR)
EE_CAX_800_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 801) && (EE_CAX_MAX_ARCH_ISR_ID >= 801))
#if defined(EE_CAX_801_ISR)
EE_CAX_801_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 802) && (EE_CAX_MAX_ARCH_ISR_ID >= 802))
#if defined(EE_CAX_802_ISR)
EE_CAX_802_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 803) && (EE_CAX_MAX_ARCH_ISR_ID >= 803))
#if defined(EE_CAX_803_ISR)
EE_CAX_803_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 804) && (EE_CAX_MAX_ARCH_ISR_ID >= 804))
#if defined(EE_CAX_804_ISR)
EE_CAX_804_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 805) && (EE_CAX_MAX_ARCH_ISR_ID >= 805))
#if defined(EE_CAX_805_ISR)
EE_CAX_805_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 806) && (EE_CAX_MAX_ARCH_ISR_ID >= 806))
#if defined(EE_CAX_806_ISR)
EE_CAX_806_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 807) && (EE_CAX_MAX_ARCH_ISR_ID >= 807))
#if defined(EE_CAX_807_ISR)
EE_CAX_807_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 808) && (EE_CAX_MAX_ARCH_ISR_ID >= 808))
#if defined(EE_CAX_808_ISR)
EE_CAX_808_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 809) && (EE_CAX_MAX_ARCH_ISR_ID >= 809))
#if defined(EE_CAX_809_ISR)
EE_CAX_809_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 810) && (EE_CAX_MAX_ARCH_ISR_ID >= 810))
#if defined(EE_CAX_810_ISR)
EE_CAX_810_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 811) && (EE_CAX_MAX_ARCH_ISR_ID >= 811))
#if defined(EE_CAX_811_ISR)
EE_CAX_811_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 812) && (EE_CAX_MAX_ARCH_ISR_ID >= 812))
#if defined(EE_CAX_812_ISR)
EE_CAX_812_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 813) && (EE_CAX_MAX_ARCH_ISR_ID >= 813))
#if defined(EE_CAX_813_ISR)
EE_CAX_813_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 814) && (EE_CAX_MAX_ARCH_ISR_ID >= 814))
#if defined(EE_CAX_814_ISR)
EE_CAX_814_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 815) && (EE_CAX_MAX_ARCH_ISR_ID >= 815))
#if defined(EE_CAX_815_ISR)
EE_CAX_815_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 816) && (EE_CAX_MAX_ARCH_ISR_ID >= 816))
#if defined(EE_CAX_816_ISR)
EE_CAX_816_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 817) && (EE_CAX_MAX_ARCH_ISR_ID >= 817))
#if defined(EE_CAX_817_ISR)
EE_CAX_817_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 818) && (EE_CAX_MAX_ARCH_ISR_ID >= 818))
#if defined(EE_CAX_818_ISR)
EE_CAX_818_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 819) && (EE_CAX_MAX_ARCH_ISR_ID >= 819))
#if defined(EE_CAX_819_ISR)
EE_CAX_819_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 820) && (EE_CAX_MAX_ARCH_ISR_ID >= 820))
#if defined(EE_CAX_820_ISR)
EE_CAX_820_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 821) && (EE_CAX_MAX_ARCH_ISR_ID >= 821))
#if defined(EE_CAX_821_ISR)
EE_CAX_821_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 822) && (EE_CAX_MAX_ARCH_ISR_ID >= 822))
#if defined(EE_CAX_822_ISR)
EE_CAX_822_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 823) && (EE_CAX_MAX_ARCH_ISR_ID >= 823))
#if defined(EE_CAX_823_ISR)
EE_CAX_823_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 824) && (EE_CAX_MAX_ARCH_ISR_ID >= 824))
#if defined(EE_CAX_824_ISR)
EE_CAX_824_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 825) && (EE_CAX_MAX_ARCH_ISR_ID >= 825))
#if defined(EE_CAX_825_ISR)
EE_CAX_825_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 826) && (EE_CAX_MAX_ARCH_ISR_ID >= 826))
#if defined(EE_CAX_826_ISR)
EE_CAX_826_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 827) && (EE_CAX_MAX_ARCH_ISR_ID >= 827))
#if defined(EE_CAX_827_ISR)
EE_CAX_827_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 828) && (EE_CAX_MAX_ARCH_ISR_ID >= 828))
#if defined(EE_CAX_828_ISR)
EE_CAX_828_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 829) && (EE_CAX_MAX_ARCH_ISR_ID >= 829))
#if defined(EE_CAX_829_ISR)
EE_CAX_829_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 830) && (EE_CAX_MAX_ARCH_ISR_ID >= 830))
#if defined(EE_CAX_830_ISR)
EE_CAX_830_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 831) && (EE_CAX_MAX_ARCH_ISR_ID >= 831))
#if defined(EE_CAX_831_ISR)
EE_CAX_831_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 832) && (EE_CAX_MAX_ARCH_ISR_ID >= 832))
#if defined(EE_CAX_832_ISR)
EE_CAX_832_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 833) && (EE_CAX_MAX_ARCH_ISR_ID >= 833))
#if defined(EE_CAX_833_ISR)
EE_CAX_833_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 834) && (EE_CAX_MAX_ARCH_ISR_ID >= 834))
#if defined(EE_CAX_834_ISR)
EE_CAX_834_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 835) && (EE_CAX_MAX_ARCH_ISR_ID >= 835))
#if defined(EE_CAX_835_ISR)
EE_CAX_835_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 836) && (EE_CAX_MAX_ARCH_ISR_ID >= 836))
#if defined(EE_CAX_836_ISR)
EE_CAX_836_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 837) && (EE_CAX_MAX_ARCH_ISR_ID >= 837))
#if defined(EE_CAX_837_ISR)
EE_CAX_837_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 838) && (EE_CAX_MAX_ARCH_ISR_ID >= 838))
#if defined(EE_CAX_838_ISR)
EE_CAX_838_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 839) && (EE_CAX_MAX_ARCH_ISR_ID >= 839))
#if defined(EE_CAX_839_ISR)
EE_CAX_839_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 840) && (EE_CAX_MAX_ARCH_ISR_ID >= 840))
#if defined(EE_CAX_840_ISR)
EE_CAX_840_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 841) && (EE_CAX_MAX_ARCH_ISR_ID >= 841))
#if defined(EE_CAX_841_ISR)
EE_CAX_841_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 842) && (EE_CAX_MAX_ARCH_ISR_ID >= 842))
#if defined(EE_CAX_842_ISR)
EE_CAX_842_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 843) && (EE_CAX_MAX_ARCH_ISR_ID >= 843))
#if defined(EE_CAX_843_ISR)
EE_CAX_843_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 844) && (EE_CAX_MAX_ARCH_ISR_ID >= 844))
#if defined(EE_CAX_844_ISR)
EE_CAX_844_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 845) && (EE_CAX_MAX_ARCH_ISR_ID >= 845))
#if defined(EE_CAX_845_ISR)
EE_CAX_845_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 846) && (EE_CAX_MAX_ARCH_ISR_ID >= 846))
#if defined(EE_CAX_846_ISR)
EE_CAX_846_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 847) && (EE_CAX_MAX_ARCH_ISR_ID >= 847))
#if defined(EE_CAX_847_ISR)
EE_CAX_847_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 848) && (EE_CAX_MAX_ARCH_ISR_ID >= 848))
#if defined(EE_CAX_848_ISR)
EE_CAX_848_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 849) && (EE_CAX_MAX_ARCH_ISR_ID >= 849))
#if defined(EE_CAX_849_ISR)
EE_CAX_849_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 850) && (EE_CAX_MAX_ARCH_ISR_ID >= 850))
#if defined(EE_CAX_850_ISR)
EE_CAX_850_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 851) && (EE_CAX_MAX_ARCH_ISR_ID >= 851))
#if defined(EE_CAX_851_ISR)
EE_CAX_851_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 852) && (EE_CAX_MAX_ARCH_ISR_ID >= 852))
#if defined(EE_CAX_852_ISR)
EE_CAX_852_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 853) && (EE_CAX_MAX_ARCH_ISR_ID >= 853))
#if defined(EE_CAX_853_ISR)
EE_CAX_853_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 854) && (EE_CAX_MAX_ARCH_ISR_ID >= 854))
#if defined(EE_CAX_854_ISR)
EE_CAX_854_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 855) && (EE_CAX_MAX_ARCH_ISR_ID >= 855))
#if defined(EE_CAX_855_ISR)
EE_CAX_855_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 856) && (EE_CAX_MAX_ARCH_ISR_ID >= 856))
#if defined(EE_CAX_856_ISR)
EE_CAX_856_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 857) && (EE_CAX_MAX_ARCH_ISR_ID >= 857))
#if defined(EE_CAX_857_ISR)
EE_CAX_857_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 858) && (EE_CAX_MAX_ARCH_ISR_ID >= 858))
#if defined(EE_CAX_858_ISR)
EE_CAX_858_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 859) && (EE_CAX_MAX_ARCH_ISR_ID >= 859))
#if defined(EE_CAX_859_ISR)
EE_CAX_859_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 860) && (EE_CAX_MAX_ARCH_ISR_ID >= 860))
#if defined(EE_CAX_860_ISR)
EE_CAX_860_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 861) && (EE_CAX_MAX_ARCH_ISR_ID >= 861))
#if defined(EE_CAX_861_ISR)
EE_CAX_861_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 862) && (EE_CAX_MAX_ARCH_ISR_ID >= 862))
#if defined(EE_CAX_862_ISR)
EE_CAX_862_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 863) && (EE_CAX_MAX_ARCH_ISR_ID >= 863))
#if defined(EE_CAX_863_ISR)
EE_CAX_863_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 864) && (EE_CAX_MAX_ARCH_ISR_ID >= 864))
#if defined(EE_CAX_864_ISR)
EE_CAX_864_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 865) && (EE_CAX_MAX_ARCH_ISR_ID >= 865))
#if defined(EE_CAX_865_ISR)
EE_CAX_865_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 866) && (EE_CAX_MAX_ARCH_ISR_ID >= 866))
#if defined(EE_CAX_866_ISR)
EE_CAX_866_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 867) && (EE_CAX_MAX_ARCH_ISR_ID >= 867))
#if defined(EE_CAX_867_ISR)
EE_CAX_867_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 868) && (EE_CAX_MAX_ARCH_ISR_ID >= 868))
#if defined(EE_CAX_868_ISR)
EE_CAX_868_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 869) && (EE_CAX_MAX_ARCH_ISR_ID >= 869))
#if defined(EE_CAX_869_ISR)
EE_CAX_869_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 870) && (EE_CAX_MAX_ARCH_ISR_ID >= 870))
#if defined(EE_CAX_870_ISR)
EE_CAX_870_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 871) && (EE_CAX_MAX_ARCH_ISR_ID >= 871))
#if defined(EE_CAX_871_ISR)
EE_CAX_871_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 872) && (EE_CAX_MAX_ARCH_ISR_ID >= 872))
#if defined(EE_CAX_872_ISR)
EE_CAX_872_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 873) && (EE_CAX_MAX_ARCH_ISR_ID >= 873))
#if defined(EE_CAX_873_ISR)
EE_CAX_873_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 874) && (EE_CAX_MAX_ARCH_ISR_ID >= 874))
#if defined(EE_CAX_874_ISR)
EE_CAX_874_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 875) && (EE_CAX_MAX_ARCH_ISR_ID >= 875))
#if defined(EE_CAX_875_ISR)
EE_CAX_875_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 876) && (EE_CAX_MAX_ARCH_ISR_ID >= 876))
#if defined(EE_CAX_876_ISR)
EE_CAX_876_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 877) && (EE_CAX_MAX_ARCH_ISR_ID >= 877))
#if defined(EE_CAX_877_ISR)
EE_CAX_877_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 878) && (EE_CAX_MAX_ARCH_ISR_ID >= 878))
#if defined(EE_CAX_878_ISR)
EE_CAX_878_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 879) && (EE_CAX_MAX_ARCH_ISR_ID >= 879))
#if defined(EE_CAX_879_ISR)
EE_CAX_879_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 880) && (EE_CAX_MAX_ARCH_ISR_ID >= 880))
#if defined(EE_CAX_880_ISR)
EE_CAX_880_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 881) && (EE_CAX_MAX_ARCH_ISR_ID >= 881))
#if defined(EE_CAX_881_ISR)
EE_CAX_881_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 882) && (EE_CAX_MAX_ARCH_ISR_ID >= 882))
#if defined(EE_CAX_882_ISR)
EE_CAX_882_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 883) && (EE_CAX_MAX_ARCH_ISR_ID >= 883))
#if defined(EE_CAX_883_ISR)
EE_CAX_883_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 884) && (EE_CAX_MAX_ARCH_ISR_ID >= 884))
#if defined(EE_CAX_884_ISR)
EE_CAX_884_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 885) && (EE_CAX_MAX_ARCH_ISR_ID >= 885))
#if defined(EE_CAX_885_ISR)
EE_CAX_885_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 886) && (EE_CAX_MAX_ARCH_ISR_ID >= 886))
#if defined(EE_CAX_886_ISR)
EE_CAX_886_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 887) && (EE_CAX_MAX_ARCH_ISR_ID >= 887))
#if defined(EE_CAX_887_ISR)
EE_CAX_887_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 888) && (EE_CAX_MAX_ARCH_ISR_ID >= 888))
#if defined(EE_CAX_888_ISR)
EE_CAX_888_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 889) && (EE_CAX_MAX_ARCH_ISR_ID >= 889))
#if defined(EE_CAX_889_ISR)
EE_CAX_889_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 890) && (EE_CAX_MAX_ARCH_ISR_ID >= 890))
#if defined(EE_CAX_890_ISR)
EE_CAX_890_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 891) && (EE_CAX_MAX_ARCH_ISR_ID >= 891))
#if defined(EE_CAX_891_ISR)
EE_CAX_891_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 892) && (EE_CAX_MAX_ARCH_ISR_ID >= 892))
#if defined(EE_CAX_892_ISR)
EE_CAX_892_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 893) && (EE_CAX_MAX_ARCH_ISR_ID >= 893))
#if defined(EE_CAX_893_ISR)
EE_CAX_893_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 894) && (EE_CAX_MAX_ARCH_ISR_ID >= 894))
#if defined(EE_CAX_894_ISR)
EE_CAX_894_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 895) && (EE_CAX_MAX_ARCH_ISR_ID >= 895))
#if defined(EE_CAX_895_ISR)
EE_CAX_895_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 896) && (EE_CAX_MAX_ARCH_ISR_ID >= 896))
#if defined(EE_CAX_896_ISR)
EE_CAX_896_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 897) && (EE_CAX_MAX_ARCH_ISR_ID >= 897))
#if defined(EE_CAX_897_ISR)
EE_CAX_897_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 898) && (EE_CAX_MAX_ARCH_ISR_ID >= 898))
#if defined(EE_CAX_898_ISR)
EE_CAX_898_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 899) && (EE_CAX_MAX_ARCH_ISR_ID >= 899))
#if defined(EE_CAX_899_ISR)
EE_CAX_899_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 900) && (EE_CAX_MAX_ARCH_ISR_ID >= 900))
#if defined(EE_CAX_900_ISR)
EE_CAX_900_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 901) && (EE_CAX_MAX_ARCH_ISR_ID >= 901))
#if defined(EE_CAX_901_ISR)
EE_CAX_901_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 902) && (EE_CAX_MAX_ARCH_ISR_ID >= 902))
#if defined(EE_CAX_902_ISR)
EE_CAX_902_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 903) && (EE_CAX_MAX_ARCH_ISR_ID >= 903))
#if defined(EE_CAX_903_ISR)
EE_CAX_903_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 904) && (EE_CAX_MAX_ARCH_ISR_ID >= 904))
#if defined(EE_CAX_904_ISR)
EE_CAX_904_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 905) && (EE_CAX_MAX_ARCH_ISR_ID >= 905))
#if defined(EE_CAX_905_ISR)
EE_CAX_905_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 906) && (EE_CAX_MAX_ARCH_ISR_ID >= 906))
#if defined(EE_CAX_906_ISR)
EE_CAX_906_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 907) && (EE_CAX_MAX_ARCH_ISR_ID >= 907))
#if defined(EE_CAX_907_ISR)
EE_CAX_907_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 908) && (EE_CAX_MAX_ARCH_ISR_ID >= 908))
#if defined(EE_CAX_908_ISR)
EE_CAX_908_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 909) && (EE_CAX_MAX_ARCH_ISR_ID >= 909))
#if defined(EE_CAX_909_ISR)
EE_CAX_909_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 910) && (EE_CAX_MAX_ARCH_ISR_ID >= 910))
#if defined(EE_CAX_910_ISR)
EE_CAX_910_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 911) && (EE_CAX_MAX_ARCH_ISR_ID >= 911))
#if defined(EE_CAX_911_ISR)
EE_CAX_911_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 912) && (EE_CAX_MAX_ARCH_ISR_ID >= 912))
#if defined(EE_CAX_912_ISR)
EE_CAX_912_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 913) && (EE_CAX_MAX_ARCH_ISR_ID >= 913))
#if defined(EE_CAX_913_ISR)
EE_CAX_913_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 914) && (EE_CAX_MAX_ARCH_ISR_ID >= 914))
#if defined(EE_CAX_914_ISR)
EE_CAX_914_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 915) && (EE_CAX_MAX_ARCH_ISR_ID >= 915))
#if defined(EE_CAX_915_ISR)
EE_CAX_915_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 916) && (EE_CAX_MAX_ARCH_ISR_ID >= 916))
#if defined(EE_CAX_916_ISR)
EE_CAX_916_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 917) && (EE_CAX_MAX_ARCH_ISR_ID >= 917))
#if defined(EE_CAX_917_ISR)
EE_CAX_917_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 918) && (EE_CAX_MAX_ARCH_ISR_ID >= 918))
#if defined(EE_CAX_918_ISR)
EE_CAX_918_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 919) && (EE_CAX_MAX_ARCH_ISR_ID >= 919))
#if defined(EE_CAX_919_ISR)
EE_CAX_919_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 920) && (EE_CAX_MAX_ARCH_ISR_ID >= 920))
#if defined(EE_CAX_920_ISR)
EE_CAX_920_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 921) && (EE_CAX_MAX_ARCH_ISR_ID >= 921))
#if defined(EE_CAX_921_ISR)
EE_CAX_921_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 922) && (EE_CAX_MAX_ARCH_ISR_ID >= 922))
#if defined(EE_CAX_922_ISR)
EE_CAX_922_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 923) && (EE_CAX_MAX_ARCH_ISR_ID >= 923))
#if defined(EE_CAX_923_ISR)
EE_CAX_923_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 924) && (EE_CAX_MAX_ARCH_ISR_ID >= 924))
#if defined(EE_CAX_924_ISR)
EE_CAX_924_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 925) && (EE_CAX_MAX_ARCH_ISR_ID >= 925))
#if defined(EE_CAX_925_ISR)
EE_CAX_925_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 926) && (EE_CAX_MAX_ARCH_ISR_ID >= 926))
#if defined(EE_CAX_926_ISR)
EE_CAX_926_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 927) && (EE_CAX_MAX_ARCH_ISR_ID >= 927))
#if defined(EE_CAX_927_ISR)
EE_CAX_927_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 928) && (EE_CAX_MAX_ARCH_ISR_ID >= 928))
#if defined(EE_CAX_928_ISR)
EE_CAX_928_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 929) && (EE_CAX_MAX_ARCH_ISR_ID >= 929))
#if defined(EE_CAX_929_ISR)
EE_CAX_929_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 930) && (EE_CAX_MAX_ARCH_ISR_ID >= 930))
#if defined(EE_CAX_930_ISR)
EE_CAX_930_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 931) && (EE_CAX_MAX_ARCH_ISR_ID >= 931))
#if defined(EE_CAX_931_ISR)
EE_CAX_931_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 932) && (EE_CAX_MAX_ARCH_ISR_ID >= 932))
#if defined(EE_CAX_932_ISR)
EE_CAX_932_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 933) && (EE_CAX_MAX_ARCH_ISR_ID >= 933))
#if defined(EE_CAX_933_ISR)
EE_CAX_933_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 934) && (EE_CAX_MAX_ARCH_ISR_ID >= 934))
#if defined(EE_CAX_934_ISR)
EE_CAX_934_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 935) && (EE_CAX_MAX_ARCH_ISR_ID >= 935))
#if defined(EE_CAX_935_ISR)
EE_CAX_935_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 936) && (EE_CAX_MAX_ARCH_ISR_ID >= 936))
#if defined(EE_CAX_936_ISR)
EE_CAX_936_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 937) && (EE_CAX_MAX_ARCH_ISR_ID >= 937))
#if defined(EE_CAX_937_ISR)
EE_CAX_937_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 938) && (EE_CAX_MAX_ARCH_ISR_ID >= 938))
#if defined(EE_CAX_938_ISR)
EE_CAX_938_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 939) && (EE_CAX_MAX_ARCH_ISR_ID >= 939))
#if defined(EE_CAX_939_ISR)
EE_CAX_939_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 940) && (EE_CAX_MAX_ARCH_ISR_ID >= 940))
#if defined(EE_CAX_940_ISR)
EE_CAX_940_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 941) && (EE_CAX_MAX_ARCH_ISR_ID >= 941))
#if defined(EE_CAX_941_ISR)
EE_CAX_941_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 942) && (EE_CAX_MAX_ARCH_ISR_ID >= 942))
#if defined(EE_CAX_942_ISR)
EE_CAX_942_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 943) && (EE_CAX_MAX_ARCH_ISR_ID >= 943))
#if defined(EE_CAX_943_ISR)
EE_CAX_943_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 944) && (EE_CAX_MAX_ARCH_ISR_ID >= 944))
#if defined(EE_CAX_944_ISR)
EE_CAX_944_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 945) && (EE_CAX_MAX_ARCH_ISR_ID >= 945))
#if defined(EE_CAX_945_ISR)
EE_CAX_945_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 946) && (EE_CAX_MAX_ARCH_ISR_ID >= 946))
#if defined(EE_CAX_946_ISR)
EE_CAX_946_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 947) && (EE_CAX_MAX_ARCH_ISR_ID >= 947))
#if defined(EE_CAX_947_ISR)
EE_CAX_947_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 948) && (EE_CAX_MAX_ARCH_ISR_ID >= 948))
#if defined(EE_CAX_948_ISR)
EE_CAX_948_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 949) && (EE_CAX_MAX_ARCH_ISR_ID >= 949))
#if defined(EE_CAX_949_ISR)
EE_CAX_949_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 950) && (EE_CAX_MAX_ARCH_ISR_ID >= 950))
#if defined(EE_CAX_950_ISR)
EE_CAX_950_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 951) && (EE_CAX_MAX_ARCH_ISR_ID >= 951))
#if defined(EE_CAX_951_ISR)
EE_CAX_951_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 952) && (EE_CAX_MAX_ARCH_ISR_ID >= 952))
#if defined(EE_CAX_952_ISR)
EE_CAX_952_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 953) && (EE_CAX_MAX_ARCH_ISR_ID >= 953))
#if defined(EE_CAX_953_ISR)
EE_CAX_953_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 954) && (EE_CAX_MAX_ARCH_ISR_ID >= 954))
#if defined(EE_CAX_954_ISR)
EE_CAX_954_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 955) && (EE_CAX_MAX_ARCH_ISR_ID >= 955))
#if defined(EE_CAX_955_ISR)
EE_CAX_955_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 956) && (EE_CAX_MAX_ARCH_ISR_ID >= 956))
#if defined(EE_CAX_956_ISR)
EE_CAX_956_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 957) && (EE_CAX_MAX_ARCH_ISR_ID >= 957))
#if defined(EE_CAX_957_ISR)
EE_CAX_957_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 958) && (EE_CAX_MAX_ARCH_ISR_ID >= 958))
#if defined(EE_CAX_958_ISR)
EE_CAX_958_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 959) && (EE_CAX_MAX_ARCH_ISR_ID >= 959))
#if defined(EE_CAX_959_ISR)
EE_CAX_959_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 960) && (EE_CAX_MAX_ARCH_ISR_ID >= 960))
#if defined(EE_CAX_960_ISR)
EE_CAX_960_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 961) && (EE_CAX_MAX_ARCH_ISR_ID >= 961))
#if defined(EE_CAX_961_ISR)
EE_CAX_961_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 962) && (EE_CAX_MAX_ARCH_ISR_ID >= 962))
#if defined(EE_CAX_962_ISR)
EE_CAX_962_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 963) && (EE_CAX_MAX_ARCH_ISR_ID >= 963))
#if defined(EE_CAX_963_ISR)
EE_CAX_963_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 964) && (EE_CAX_MAX_ARCH_ISR_ID >= 964))
#if defined(EE_CAX_964_ISR)
EE_CAX_964_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 965) && (EE_CAX_MAX_ARCH_ISR_ID >= 965))
#if defined(EE_CAX_965_ISR)
EE_CAX_965_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 966) && (EE_CAX_MAX_ARCH_ISR_ID >= 966))
#if defined(EE_CAX_966_ISR)
EE_CAX_966_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 967) && (EE_CAX_MAX_ARCH_ISR_ID >= 967))
#if defined(EE_CAX_967_ISR)
EE_CAX_967_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 968) && (EE_CAX_MAX_ARCH_ISR_ID >= 968))
#if defined(EE_CAX_968_ISR)
EE_CAX_968_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 969) && (EE_CAX_MAX_ARCH_ISR_ID >= 969))
#if defined(EE_CAX_969_ISR)
EE_CAX_969_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 970) && (EE_CAX_MAX_ARCH_ISR_ID >= 970))
#if defined(EE_CAX_970_ISR)
EE_CAX_970_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 971) && (EE_CAX_MAX_ARCH_ISR_ID >= 971))
#if defined(EE_CAX_971_ISR)
EE_CAX_971_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 972) && (EE_CAX_MAX_ARCH_ISR_ID >= 972))
#if defined(EE_CAX_972_ISR)
EE_CAX_972_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 973) && (EE_CAX_MAX_ARCH_ISR_ID >= 973))
#if defined(EE_CAX_973_ISR)
EE_CAX_973_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 974) && (EE_CAX_MAX_ARCH_ISR_ID >= 974))
#if defined(EE_CAX_974_ISR)
EE_CAX_974_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 975) && (EE_CAX_MAX_ARCH_ISR_ID >= 975))
#if defined(EE_CAX_975_ISR)
EE_CAX_975_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 976) && (EE_CAX_MAX_ARCH_ISR_ID >= 976))
#if defined(EE_CAX_976_ISR)
EE_CAX_976_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 977) && (EE_CAX_MAX_ARCH_ISR_ID >= 977))
#if defined(EE_CAX_977_ISR)
EE_CAX_977_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 978) && (EE_CAX_MAX_ARCH_ISR_ID >= 978))
#if defined(EE_CAX_978_ISR)
EE_CAX_978_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 979) && (EE_CAX_MAX_ARCH_ISR_ID >= 979))
#if defined(EE_CAX_979_ISR)
EE_CAX_979_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 980) && (EE_CAX_MAX_ARCH_ISR_ID >= 980))
#if defined(EE_CAX_980_ISR)
EE_CAX_980_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 981) && (EE_CAX_MAX_ARCH_ISR_ID >= 981))
#if defined(EE_CAX_981_ISR)
EE_CAX_981_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 982) && (EE_CAX_MAX_ARCH_ISR_ID >= 982))
#if defined(EE_CAX_982_ISR)
EE_CAX_982_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 983) && (EE_CAX_MAX_ARCH_ISR_ID >= 983))
#if defined(EE_CAX_983_ISR)
EE_CAX_983_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 984) && (EE_CAX_MAX_ARCH_ISR_ID >= 984))
#if defined(EE_CAX_984_ISR)
EE_CAX_984_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 985) && (EE_CAX_MAX_ARCH_ISR_ID >= 985))
#if defined(EE_CAX_985_ISR)
EE_CAX_985_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 986) && (EE_CAX_MAX_ARCH_ISR_ID >= 986))
#if defined(EE_CAX_986_ISR)
EE_CAX_986_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 987) && (EE_CAX_MAX_ARCH_ISR_ID >= 987))
#if defined(EE_CAX_987_ISR)
EE_CAX_987_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 988) && (EE_CAX_MAX_ARCH_ISR_ID >= 988))
#if defined(EE_CAX_988_ISR)
EE_CAX_988_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 989) && (EE_CAX_MAX_ARCH_ISR_ID >= 989))
#if defined(EE_CAX_989_ISR)
EE_CAX_989_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 990) && (EE_CAX_MAX_ARCH_ISR_ID >= 990))
#if defined(EE_CAX_990_ISR)
EE_CAX_990_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 991) && (EE_CAX_MAX_ARCH_ISR_ID >= 991))
#if defined(EE_CAX_991_ISR)
EE_CAX_991_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 992) && (EE_CAX_MAX_ARCH_ISR_ID >= 992))
#if defined(EE_CAX_992_ISR)
EE_CAX_992_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 993) && (EE_CAX_MAX_ARCH_ISR_ID >= 993))
#if defined(EE_CAX_993_ISR)
EE_CAX_993_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 994) && (EE_CAX_MAX_ARCH_ISR_ID >= 994))
#if defined(EE_CAX_994_ISR)
EE_CAX_994_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 995) && (EE_CAX_MAX_ARCH_ISR_ID >= 995))
#if defined(EE_CAX_995_ISR)
EE_CAX_995_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 996) && (EE_CAX_MAX_ARCH_ISR_ID >= 996))
#if defined(EE_CAX_996_ISR)
EE_CAX_996_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 997) && (EE_CAX_MAX_ARCH_ISR_ID >= 997))
#if defined(EE_CAX_997_ISR)
EE_CAX_997_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 998) && (EE_CAX_MAX_ARCH_ISR_ID >= 998))
#if defined(EE_CAX_998_ISR)
EE_CAX_998_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 999) && (EE_CAX_MAX_ARCH_ISR_ID >= 999))
#if defined(EE_CAX_999_ISR)
EE_CAX_999_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1000) && (EE_CAX_MAX_ARCH_ISR_ID >= 1000))
#if defined(EE_CAX_1000_ISR)
EE_CAX_1000_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1001) && (EE_CAX_MAX_ARCH_ISR_ID >= 1001))
#if defined(EE_CAX_1001_ISR)
EE_CAX_1001_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1002) && (EE_CAX_MAX_ARCH_ISR_ID >= 1002))
#if defined(EE_CAX_1002_ISR)
EE_CAX_1002_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1003) && (EE_CAX_MAX_ARCH_ISR_ID >= 1003))
#if defined(EE_CAX_1003_ISR)
EE_CAX_1003_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1004) && (EE_CAX_MAX_ARCH_ISR_ID >= 1004))
#if defined(EE_CAX_1004_ISR)
EE_CAX_1004_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1005) && (EE_CAX_MAX_ARCH_ISR_ID >= 1005))
#if defined(EE_CAX_1005_ISR)
EE_CAX_1005_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1006) && (EE_CAX_MAX_ARCH_ISR_ID >= 1006))
#if defined(EE_CAX_1006_ISR)
EE_CAX_1006_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1007) && (EE_CAX_MAX_ARCH_ISR_ID >= 1007))
#if defined(EE_CAX_1007_ISR)
EE_CAX_1007_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1008) && (EE_CAX_MAX_ARCH_ISR_ID >= 1008))
#if defined(EE_CAX_1008_ISR)
EE_CAX_1008_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1009) && (EE_CAX_MAX_ARCH_ISR_ID >= 1009))
#if defined(EE_CAX_1009_ISR)
EE_CAX_1009_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1010) && (EE_CAX_MAX_ARCH_ISR_ID >= 1010))
#if defined(EE_CAX_1010_ISR)
EE_CAX_1010_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1011) && (EE_CAX_MAX_ARCH_ISR_ID >= 1011))
#if defined(EE_CAX_1011_ISR)
EE_CAX_1011_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1012) && (EE_CAX_MAX_ARCH_ISR_ID >= 1012))
#if defined(EE_CAX_1012_ISR)
EE_CAX_1012_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1013) && (EE_CAX_MAX_ARCH_ISR_ID >= 1013))
#if defined(EE_CAX_1013_ISR)
EE_CAX_1013_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1014) && (EE_CAX_MAX_ARCH_ISR_ID >= 1014))
#if defined(EE_CAX_1014_ISR)
EE_CAX_1014_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1015) && (EE_CAX_MAX_ARCH_ISR_ID >= 1015))
#if defined(EE_CAX_1015_ISR)
EE_CAX_1015_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1016) && (EE_CAX_MAX_ARCH_ISR_ID >= 1016))
#if defined(EE_CAX_1016_ISR)
EE_CAX_1016_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1017) && (EE_CAX_MAX_ARCH_ISR_ID >= 1017))
#if defined(EE_CAX_1017_ISR)
EE_CAX_1017_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1018) && (EE_CAX_MAX_ARCH_ISR_ID >= 1018))
#if defined(EE_CAX_1018_ISR)
EE_CAX_1018_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1019) && (EE_CAX_MAX_ARCH_ISR_ID >= 1019))
#if defined(EE_CAX_1019_ISR)
EE_CAX_1019_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1020) && (EE_CAX_MAX_ARCH_ISR_ID >= 1020))
#if defined(EE_CAX_1020_ISR)
EE_CAX_1020_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1021) && (EE_CAX_MAX_ARCH_ISR_ID >= 1021))
#if defined(EE_CAX_1021_ISR)
EE_CAX_1021_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1022) && (EE_CAX_MAX_ARCH_ISR_ID >= 1022))
#if defined(EE_CAX_1022_ISR)
EE_CAX_1022_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1023) && (EE_CAX_MAX_ARCH_ISR_ID >= 1023))
#if defined(EE_CAX_1023_ISR)
EE_CAX_1023_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1024) && (EE_CAX_MAX_ARCH_ISR_ID >= 1024))
#if defined(EE_CAX_1024_ISR)
EE_CAX_1024_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1025) && (EE_CAX_MAX_ARCH_ISR_ID >= 1025))
#if defined(EE_CAX_1025_ISR)
EE_CAX_1025_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1026) && (EE_CAX_MAX_ARCH_ISR_ID >= 1026))
#if defined(EE_CAX_1026_ISR)
EE_CAX_1026_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1027) && (EE_CAX_MAX_ARCH_ISR_ID >= 1027))
#if defined(EE_CAX_1027_ISR)
EE_CAX_1027_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1028) && (EE_CAX_MAX_ARCH_ISR_ID >= 1028))
#if defined(EE_CAX_1028_ISR)
EE_CAX_1028_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif

#if ((EE_CAX_MAX_ISR_ID >= 1029) && (EE_CAX_MAX_ARCH_ISR_ID >= 1029))
#if defined(EE_CAX_1029_ISR)
EE_CAX_1029_ISR,
#else
EE_ISR_DUMMY,
#endif
#endif
};

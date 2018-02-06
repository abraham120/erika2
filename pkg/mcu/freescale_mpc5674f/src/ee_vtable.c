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

/**
	@file ee_vtable.c
	@brief Static Interrupt Vector Table
	@author Errico Guidieri
	@date 2012
 **/

#include <ee_internal.h>
#include <ee_irq.h>

#ifndef DEFAULT_IRQ_ENTRY
#define DEFAULT_IRQ_ENTRY (EE_e200z7_ISR_handler)0
#endif

/* Special entry for internal decrementer */
#ifdef EE_PPCE200ZX_DECREMENTER_ISR
extern void EE_PPCE200ZX_DECREMENTER_ISR(void);
#else
#define EE_PPCE200ZX_DECREMENTER_ISR DEFAULT_IRQ_ENTRY
#endif

/* Special entry for fixed interval timer */
#ifdef EE_PPCE200ZX_FIXED_INTV_ISR
extern void EE_PPCE200ZX_FIXED_INTV_ISR(void);
#else
#define EE_PPCE200ZX_FIXED_INTV_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_0_ISR
extern void EE_PPCE200ZX_0_ISR(void);
#else
#define EE_PPCE200ZX_0_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_1_ISR
extern void EE_PPCE200ZX_1_ISR(void);
#else
#define EE_PPCE200ZX_1_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_2_ISR
extern void EE_PPCE200ZX_2_ISR(void);
#else
#define EE_PPCE200ZX_2_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_3_ISR
extern void EE_PPCE200ZX_3_ISR(void);
#else
#define EE_PPCE200ZX_3_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_4_ISR
extern void EE_PPCE200ZX_4_ISR(void);
#else
#define EE_PPCE200ZX_4_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_5_ISR
extern void EE_PPCE200ZX_5_ISR(void);
#else
#define EE_PPCE200ZX_5_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_6_ISR
extern void EE_PPCE200ZX_6_ISR(void);
#else
#define EE_PPCE200ZX_6_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_7_ISR
extern void EE_PPCE200ZX_7_ISR(void);
#else
#define EE_PPCE200ZX_7_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_8_ISR
extern void EE_PPCE200ZX_8_ISR(void);
#else
#define EE_PPCE200ZX_8_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_9_ISR
extern void EE_PPCE200ZX_9_ISR(void);
#else
#define EE_PPCE200ZX_9_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_10_ISR
extern void EE_PPCE200ZX_10_ISR(void);
#else
#define EE_PPCE200ZX_10_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_11_ISR
extern void EE_PPCE200ZX_11_ISR(void);
#else
#define EE_PPCE200ZX_11_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_12_ISR
extern void EE_PPCE200ZX_12_ISR(void);
#else
#define EE_PPCE200ZX_12_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_13_ISR
extern void EE_PPCE200ZX_13_ISR(void);
#else
#define EE_PPCE200ZX_13_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_14_ISR
extern void EE_PPCE200ZX_14_ISR(void);
#else
#define EE_PPCE200ZX_14_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_15_ISR
extern void EE_PPCE200ZX_15_ISR(void);
#else
#define EE_PPCE200ZX_15_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_16_ISR
extern void EE_PPCE200ZX_16_ISR(void);
#else
#define EE_PPCE200ZX_16_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_17_ISR
extern void EE_PPCE200ZX_17_ISR(void);
#else
#define EE_PPCE200ZX_17_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_18_ISR
extern void EE_PPCE200ZX_18_ISR(void);
#else
#define EE_PPCE200ZX_18_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_19_ISR
extern void EE_PPCE200ZX_19_ISR(void);
#else
#define EE_PPCE200ZX_19_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_20_ISR
extern void EE_PPCE200ZX_20_ISR(void);
#else
#define EE_PPCE200ZX_20_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_21_ISR
extern void EE_PPCE200ZX_21_ISR(void);
#else
#define EE_PPCE200ZX_21_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_22_ISR
extern void EE_PPCE200ZX_22_ISR(void);
#else
#define EE_PPCE200ZX_22_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_23_ISR
extern void EE_PPCE200ZX_23_ISR(void);
#else
#define EE_PPCE200ZX_23_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_24_ISR
extern void EE_PPCE200ZX_24_ISR(void);
#else
#define EE_PPCE200ZX_24_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_25_ISR
extern void EE_PPCE200ZX_25_ISR(void);
#else
#define EE_PPCE200ZX_25_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_26_ISR
extern void EE_PPCE200ZX_26_ISR(void);
#else
#define EE_PPCE200ZX_26_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_27_ISR
extern void EE_PPCE200ZX_27_ISR(void);
#else
#define EE_PPCE200ZX_27_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_28_ISR
extern void EE_PPCE200ZX_28_ISR(void);
#else
#define EE_PPCE200ZX_28_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_29_ISR
extern void EE_PPCE200ZX_29_ISR(void);
#else
#define EE_PPCE200ZX_29_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_30_ISR
extern void EE_PPCE200ZX_30_ISR(void);
#else
#define EE_PPCE200ZX_30_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_31_ISR
extern void EE_PPCE200ZX_31_ISR(void);
#else
#define EE_PPCE200ZX_31_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_32_ISR
extern void EE_PPCE200ZX_32_ISR(void);
#else
#define EE_PPCE200ZX_32_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_33_ISR
extern void EE_PPCE200ZX_33_ISR(void);
#else
#define EE_PPCE200ZX_33_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_34_ISR
extern void EE_PPCE200ZX_34_ISR(void);
#else
#define EE_PPCE200ZX_34_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_35_ISR
extern void EE_PPCE200ZX_35_ISR(void);
#else
#define EE_PPCE200ZX_35_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_36_ISR
extern void EE_PPCE200ZX_36_ISR(void);
#else
#define EE_PPCE200ZX_36_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_37_ISR
extern void EE_PPCE200ZX_37_ISR(void);
#else
#define EE_PPCE200ZX_37_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_38_ISR
extern void EE_PPCE200ZX_38_ISR(void);
#else
#define EE_PPCE200ZX_38_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_39_ISR
extern void EE_PPCE200ZX_39_ISR(void);
#else
#define EE_PPCE200ZX_39_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_40_ISR
extern void EE_PPCE200ZX_40_ISR(void);
#else
#define EE_PPCE200ZX_40_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_41_ISR
extern void EE_PPCE200ZX_41_ISR(void);
#else
#define EE_PPCE200ZX_41_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_42_ISR
extern void EE_PPCE200ZX_42_ISR(void);
#else
#define EE_PPCE200ZX_42_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_43_ISR
extern void EE_PPCE200ZX_43_ISR(void);
#else
#define EE_PPCE200ZX_43_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_44_ISR
extern void EE_PPCE200ZX_44_ISR(void);
#else
#define EE_PPCE200ZX_44_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_45_ISR
extern void EE_PPCE200ZX_45_ISR(void);
#else
#define EE_PPCE200ZX_45_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_46_ISR
extern void EE_PPCE200ZX_46_ISR(void);
#else
#define EE_PPCE200ZX_46_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_47_ISR
extern void EE_PPCE200ZX_47_ISR(void);
#else
#define EE_PPCE200ZX_47_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_48_ISR
extern void EE_PPCE200ZX_48_ISR(void);
#else
#define EE_PPCE200ZX_48_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_49_ISR
extern void EE_PPCE200ZX_49_ISR(void);
#else
#define EE_PPCE200ZX_49_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_50_ISR
extern void EE_PPCE200ZX_50_ISR(void);
#else
#define EE_PPCE200ZX_50_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_51_ISR
extern void EE_PPCE200ZX_51_ISR(void);
#else
#define EE_PPCE200ZX_51_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_52_ISR
extern void EE_PPCE200ZX_52_ISR(void);
#else
#define EE_PPCE200ZX_52_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_53_ISR
extern void EE_PPCE200ZX_53_ISR(void);
#else
#define EE_PPCE200ZX_53_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_54_ISR
extern void EE_PPCE200ZX_54_ISR(void);
#else
#define EE_PPCE200ZX_54_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_55_ISR
extern void EE_PPCE200ZX_55_ISR(void);
#else
#define EE_PPCE200ZX_55_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_56_ISR
extern void EE_PPCE200ZX_56_ISR(void);
#else
#define EE_PPCE200ZX_56_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_57_ISR
extern void EE_PPCE200ZX_57_ISR(void);
#else
#define EE_PPCE200ZX_57_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_58_ISR
extern void EE_PPCE200ZX_58_ISR(void);
#else
#define EE_PPCE200ZX_58_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_59_ISR
extern void EE_PPCE200ZX_59_ISR(void);
#else
#define EE_PPCE200ZX_59_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_60_ISR
extern void EE_PPCE200ZX_60_ISR(void);
#else
#define EE_PPCE200ZX_60_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_61_ISR
extern void EE_PPCE200ZX_61_ISR(void);
#else
#define EE_PPCE200ZX_61_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_62_ISR
extern void EE_PPCE200ZX_62_ISR(void);
#else
#define EE_PPCE200ZX_62_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_63_ISR
extern void EE_PPCE200ZX_63_ISR(void);
#else
#define EE_PPCE200ZX_63_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_64_ISR
extern void EE_PPCE200ZX_64_ISR(void);
#else
#define EE_PPCE200ZX_64_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_65_ISR
extern void EE_PPCE200ZX_65_ISR(void);
#else
#define EE_PPCE200ZX_65_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_66_ISR
extern void EE_PPCE200ZX_66_ISR(void);
#else
#define EE_PPCE200ZX_66_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_67_ISR
extern void EE_PPCE200ZX_67_ISR(void);
#else
#define EE_PPCE200ZX_67_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_68_ISR
extern void EE_PPCE200ZX_68_ISR(void);
#else
#define EE_PPCE200ZX_68_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_69_ISR
extern void EE_PPCE200ZX_69_ISR(void);
#else
#define EE_PPCE200ZX_69_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_70_ISR
extern void EE_PPCE200ZX_70_ISR(void);
#else
#define EE_PPCE200ZX_70_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_71_ISR
extern void EE_PPCE200ZX_71_ISR(void);
#else
#define EE_PPCE200ZX_71_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_72_ISR
extern void EE_PPCE200ZX_72_ISR(void);
#else
#define EE_PPCE200ZX_72_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_73_ISR
extern void EE_PPCE200ZX_73_ISR(void);
#else
#define EE_PPCE200ZX_73_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_74_ISR
extern void EE_PPCE200ZX_74_ISR(void);
#else
#define EE_PPCE200ZX_74_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_75_ISR
extern void EE_PPCE200ZX_75_ISR(void);
#else
#define EE_PPCE200ZX_75_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_76_ISR
extern void EE_PPCE200ZX_76_ISR(void);
#else
#define EE_PPCE200ZX_76_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_77_ISR
extern void EE_PPCE200ZX_77_ISR(void);
#else
#define EE_PPCE200ZX_77_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_78_ISR
extern void EE_PPCE200ZX_78_ISR(void);
#else
#define EE_PPCE200ZX_78_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_79_ISR
extern void EE_PPCE200ZX_79_ISR(void);
#else
#define EE_PPCE200ZX_79_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_80_ISR
extern void EE_PPCE200ZX_80_ISR(void);
#else
#define EE_PPCE200ZX_80_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_81_ISR
extern void EE_PPCE200ZX_81_ISR(void);
#else
#define EE_PPCE200ZX_81_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_82_ISR
extern void EE_PPCE200ZX_82_ISR(void);
#else
#define EE_PPCE200ZX_82_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_83_ISR
extern void EE_PPCE200ZX_83_ISR(void);
#else
#define EE_PPCE200ZX_83_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_84_ISR
extern void EE_PPCE200ZX_84_ISR(void);
#else
#define EE_PPCE200ZX_84_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_85_ISR
extern void EE_PPCE200ZX_85_ISR(void);
#else
#define EE_PPCE200ZX_85_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_86_ISR
extern void EE_PPCE200ZX_86_ISR(void);
#else
#define EE_PPCE200ZX_86_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_87_ISR
extern void EE_PPCE200ZX_87_ISR(void);
#else
#define EE_PPCE200ZX_87_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_88_ISR
extern void EE_PPCE200ZX_88_ISR(void);
#else
#define EE_PPCE200ZX_88_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_89_ISR
extern void EE_PPCE200ZX_89_ISR(void);
#else
#define EE_PPCE200ZX_89_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_90_ISR
extern void EE_PPCE200ZX_90_ISR(void);
#else
#define EE_PPCE200ZX_90_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_91_ISR
extern void EE_PPCE200ZX_91_ISR(void);
#else
#define EE_PPCE200ZX_91_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_92_ISR
extern void EE_PPCE200ZX_92_ISR(void);
#else
#define EE_PPCE200ZX_92_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_93_ISR
extern void EE_PPCE200ZX_93_ISR(void);
#else
#define EE_PPCE200ZX_93_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_94_ISR
extern void EE_PPCE200ZX_94_ISR(void);
#else
#define EE_PPCE200ZX_94_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_95_ISR
extern void EE_PPCE200ZX_95_ISR(void);
#else
#define EE_PPCE200ZX_95_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_96_ISR
extern void EE_PPCE200ZX_96_ISR(void);
#else
#define EE_PPCE200ZX_96_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_97_ISR
extern void EE_PPCE200ZX_97_ISR(void);
#else
#define EE_PPCE200ZX_97_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_98_ISR
extern void EE_PPCE200ZX_98_ISR(void);
#else
#define EE_PPCE200ZX_98_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_99_ISR
extern void EE_PPCE200ZX_99_ISR(void);
#else
#define EE_PPCE200ZX_99_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_100_ISR
extern void EE_PPCE200ZX_100_ISR(void);
#else
#define EE_PPCE200ZX_100_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_101_ISR
extern void EE_PPCE200ZX_101_ISR(void);
#else
#define EE_PPCE200ZX_101_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_102_ISR
extern void EE_PPCE200ZX_102_ISR(void);
#else
#define EE_PPCE200ZX_102_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_103_ISR
extern void EE_PPCE200ZX_103_ISR(void);
#else
#define EE_PPCE200ZX_103_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_104_ISR
extern void EE_PPCE200ZX_104_ISR(void);
#else
#define EE_PPCE200ZX_104_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_105_ISR
extern void EE_PPCE200ZX_105_ISR(void);
#else
#define EE_PPCE200ZX_105_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_106_ISR
extern void EE_PPCE200ZX_106_ISR(void);
#else
#define EE_PPCE200ZX_106_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_107_ISR
extern void EE_PPCE200ZX_107_ISR(void);
#else
#define EE_PPCE200ZX_107_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_108_ISR
extern void EE_PPCE200ZX_108_ISR(void);
#else
#define EE_PPCE200ZX_108_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_109_ISR
extern void EE_PPCE200ZX_109_ISR(void);
#else
#define EE_PPCE200ZX_109_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_110_ISR
extern void EE_PPCE200ZX_110_ISR(void);
#else
#define EE_PPCE200ZX_110_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_111_ISR
extern void EE_PPCE200ZX_111_ISR(void);
#else
#define EE_PPCE200ZX_111_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_112_ISR
extern void EE_PPCE200ZX_112_ISR(void);
#else
#define EE_PPCE200ZX_112_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_113_ISR
extern void EE_PPCE200ZX_113_ISR(void);
#else
#define EE_PPCE200ZX_113_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_114_ISR
extern void EE_PPCE200ZX_114_ISR(void);
#else
#define EE_PPCE200ZX_114_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_115_ISR
extern void EE_PPCE200ZX_115_ISR(void);
#else
#define EE_PPCE200ZX_115_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_116_ISR
extern void EE_PPCE200ZX_116_ISR(void);
#else
#define EE_PPCE200ZX_116_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_117_ISR
extern void EE_PPCE200ZX_117_ISR(void);
#else
#define EE_PPCE200ZX_117_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_118_ISR
extern void EE_PPCE200ZX_118_ISR(void);
#else
#define EE_PPCE200ZX_118_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_119_ISR
extern void EE_PPCE200ZX_119_ISR(void);
#else
#define EE_PPCE200ZX_119_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_120_ISR
extern void EE_PPCE200ZX_120_ISR(void);
#else
#define EE_PPCE200ZX_120_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_121_ISR
extern void EE_PPCE200ZX_121_ISR(void);
#else
#define EE_PPCE200ZX_121_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_122_ISR
extern void EE_PPCE200ZX_122_ISR(void);
#else
#define EE_PPCE200ZX_122_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_123_ISR
extern void EE_PPCE200ZX_123_ISR(void);
#else
#define EE_PPCE200ZX_123_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_124_ISR
extern void EE_PPCE200ZX_124_ISR(void);
#else
#define EE_PPCE200ZX_124_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_125_ISR
extern void EE_PPCE200ZX_125_ISR(void);
#else
#define EE_PPCE200ZX_125_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_126_ISR
extern void EE_PPCE200ZX_126_ISR(void);
#else
#define EE_PPCE200ZX_126_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_127_ISR
extern void EE_PPCE200ZX_127_ISR(void);
#else
#define EE_PPCE200ZX_127_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_128_ISR
extern void EE_PPCE200ZX_128_ISR(void);
#else
#define EE_PPCE200ZX_128_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_129_ISR
extern void EE_PPCE200ZX_129_ISR(void);
#else
#define EE_PPCE200ZX_129_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_130_ISR
extern void EE_PPCE200ZX_130_ISR(void);
#else
#define EE_PPCE200ZX_130_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_131_ISR
extern void EE_PPCE200ZX_131_ISR(void);
#else
#define EE_PPCE200ZX_131_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_132_ISR
extern void EE_PPCE200ZX_132_ISR(void);
#else
#define EE_PPCE200ZX_132_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_133_ISR
extern void EE_PPCE200ZX_133_ISR(void);
#else
#define EE_PPCE200ZX_133_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_134_ISR
extern void EE_PPCE200ZX_134_ISR(void);
#else
#define EE_PPCE200ZX_134_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_135_ISR
extern void EE_PPCE200ZX_135_ISR(void);
#else
#define EE_PPCE200ZX_135_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_136_ISR
extern void EE_PPCE200ZX_136_ISR(void);
#else
#define EE_PPCE200ZX_136_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_137_ISR
extern void EE_PPCE200ZX_137_ISR(void);
#else
#define EE_PPCE200ZX_137_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_138_ISR
extern void EE_PPCE200ZX_138_ISR(void);
#else
#define EE_PPCE200ZX_138_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_139_ISR
extern void EE_PPCE200ZX_139_ISR(void);
#else
#define EE_PPCE200ZX_139_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_140_ISR
extern void EE_PPCE200ZX_140_ISR(void);
#else
#define EE_PPCE200ZX_140_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_141_ISR
extern void EE_PPCE200ZX_141_ISR(void);
#else
#define EE_PPCE200ZX_141_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_142_ISR
extern void EE_PPCE200ZX_142_ISR(void);
#else
#define EE_PPCE200ZX_142_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_143_ISR
extern void EE_PPCE200ZX_143_ISR(void);
#else
#define EE_PPCE200ZX_143_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_144_ISR
extern void EE_PPCE200ZX_144_ISR(void);
#else
#define EE_PPCE200ZX_144_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_145_ISR
extern void EE_PPCE200ZX_145_ISR(void);
#else
#define EE_PPCE200ZX_145_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_146_ISR
extern void EE_PPCE200ZX_146_ISR(void);
#else
#define EE_PPCE200ZX_146_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_147_ISR
extern void EE_PPCE200ZX_147_ISR(void);
#else
#define EE_PPCE200ZX_147_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_148_ISR
extern void EE_PPCE200ZX_148_ISR(void);
#else
#define EE_PPCE200ZX_148_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_149_ISR
extern void EE_PPCE200ZX_149_ISR(void);
#else
#define EE_PPCE200ZX_149_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_150_ISR
extern void EE_PPCE200ZX_150_ISR(void);
#else
#define EE_PPCE200ZX_150_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_151_ISR
extern void EE_PPCE200ZX_151_ISR(void);
#else
#define EE_PPCE200ZX_151_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_152_ISR
extern void EE_PPCE200ZX_152_ISR(void);
#else
#define EE_PPCE200ZX_152_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_153_ISR
extern void EE_PPCE200ZX_153_ISR(void);
#else
#define EE_PPCE200ZX_153_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_154_ISR
extern void EE_PPCE200ZX_154_ISR(void);
#else
#define EE_PPCE200ZX_154_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_155_ISR
extern void EE_PPCE200ZX_155_ISR(void);
#else
#define EE_PPCE200ZX_155_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_156_ISR
extern void EE_PPCE200ZX_156_ISR(void);
#else
#define EE_PPCE200ZX_156_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_157_ISR
extern void EE_PPCE200ZX_157_ISR(void);
#else
#define EE_PPCE200ZX_157_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_158_ISR
extern void EE_PPCE200ZX_158_ISR(void);
#else
#define EE_PPCE200ZX_158_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_159_ISR
extern void EE_PPCE200ZX_159_ISR(void);
#else
#define EE_PPCE200ZX_159_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_160_ISR
extern void EE_PPCE200ZX_160_ISR(void);
#else
#define EE_PPCE200ZX_160_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_161_ISR
extern void EE_PPCE200ZX_161_ISR(void);
#else
#define EE_PPCE200ZX_161_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_162_ISR
extern void EE_PPCE200ZX_162_ISR(void);
#else
#define EE_PPCE200ZX_162_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_163_ISR
extern void EE_PPCE200ZX_163_ISR(void);
#else
#define EE_PPCE200ZX_163_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_164_ISR
extern void EE_PPCE200ZX_164_ISR(void);
#else
#define EE_PPCE200ZX_164_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_165_ISR
extern void EE_PPCE200ZX_165_ISR(void);
#else
#define EE_PPCE200ZX_165_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_166_ISR
extern void EE_PPCE200ZX_166_ISR(void);
#else
#define EE_PPCE200ZX_166_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_167_ISR
extern void EE_PPCE200ZX_167_ISR(void);
#else
#define EE_PPCE200ZX_167_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_168_ISR
extern void EE_PPCE200ZX_168_ISR(void);
#else
#define EE_PPCE200ZX_168_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_169_ISR
extern void EE_PPCE200ZX_169_ISR(void);
#else
#define EE_PPCE200ZX_169_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_170_ISR
extern void EE_PPCE200ZX_170_ISR(void);
#else
#define EE_PPCE200ZX_170_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_171_ISR
extern void EE_PPCE200ZX_171_ISR(void);
#else
#define EE_PPCE200ZX_171_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_172_ISR
extern void EE_PPCE200ZX_172_ISR(void);
#else
#define EE_PPCE200ZX_172_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_173_ISR
extern void EE_PPCE200ZX_173_ISR(void);
#else
#define EE_PPCE200ZX_173_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_174_ISR
extern void EE_PPCE200ZX_174_ISR(void);
#else
#define EE_PPCE200ZX_174_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_175_ISR
extern void EE_PPCE200ZX_175_ISR(void);
#else
#define EE_PPCE200ZX_175_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_176_ISR
extern void EE_PPCE200ZX_176_ISR(void);
#else
#define EE_PPCE200ZX_176_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_177_ISR
extern void EE_PPCE200ZX_177_ISR(void);
#else
#define EE_PPCE200ZX_177_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_178_ISR
extern void EE_PPCE200ZX_178_ISR(void);
#else
#define EE_PPCE200ZX_178_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_179_ISR
extern void EE_PPCE200ZX_179_ISR(void);
#else
#define EE_PPCE200ZX_179_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_180_ISR
extern void EE_PPCE200ZX_180_ISR(void);
#else
#define EE_PPCE200ZX_180_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_181_ISR
extern void EE_PPCE200ZX_181_ISR(void);
#else
#define EE_PPCE200ZX_181_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_182_ISR
extern void EE_PPCE200ZX_182_ISR(void);
#else
#define EE_PPCE200ZX_182_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_183_ISR
extern void EE_PPCE200ZX_183_ISR(void);
#else
#define EE_PPCE200ZX_183_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_184_ISR
extern void EE_PPCE200ZX_184_ISR(void);
#else
#define EE_PPCE200ZX_184_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_185_ISR
extern void EE_PPCE200ZX_185_ISR(void);
#else
#define EE_PPCE200ZX_185_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_186_ISR
extern void EE_PPCE200ZX_186_ISR(void);
#else
#define EE_PPCE200ZX_186_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_187_ISR
extern void EE_PPCE200ZX_187_ISR(void);
#else
#define EE_PPCE200ZX_187_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_188_ISR
extern void EE_PPCE200ZX_188_ISR(void);
#else
#define EE_PPCE200ZX_188_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_189_ISR
extern void EE_PPCE200ZX_189_ISR(void);
#else
#define EE_PPCE200ZX_189_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_190_ISR
extern void EE_PPCE200ZX_190_ISR(void);
#else
#define EE_PPCE200ZX_190_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_191_ISR
extern void EE_PPCE200ZX_191_ISR(void);
#else
#define EE_PPCE200ZX_191_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_192_ISR
extern void EE_PPCE200ZX_192_ISR(void);
#else
#define EE_PPCE200ZX_192_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_193_ISR
extern void EE_PPCE200ZX_193_ISR(void);
#else
#define EE_PPCE200ZX_193_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_194_ISR
extern void EE_PPCE200ZX_194_ISR(void);
#else
#define EE_PPCE200ZX_194_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_195_ISR
extern void EE_PPCE200ZX_195_ISR(void);
#else
#define EE_PPCE200ZX_195_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_196_ISR
extern void EE_PPCE200ZX_196_ISR(void);
#else
#define EE_PPCE200ZX_196_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_197_ISR
extern void EE_PPCE200ZX_197_ISR(void);
#else
#define EE_PPCE200ZX_197_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_198_ISR
extern void EE_PPCE200ZX_198_ISR(void);
#else
#define EE_PPCE200ZX_198_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_199_ISR
extern void EE_PPCE200ZX_199_ISR(void);
#else
#define EE_PPCE200ZX_199_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_200_ISR
extern void EE_PPCE200ZX_200_ISR(void);
#else
#define EE_PPCE200ZX_200_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_201_ISR
extern void EE_PPCE200ZX_201_ISR(void);
#else
#define EE_PPCE200ZX_201_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_202_ISR
extern void EE_PPCE200ZX_202_ISR(void);
#else
#define EE_PPCE200ZX_202_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_203_ISR
extern void EE_PPCE200ZX_203_ISR(void);
#else
#define EE_PPCE200ZX_203_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_204_ISR
extern void EE_PPCE200ZX_204_ISR(void);
#else
#define EE_PPCE200ZX_204_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_205_ISR
extern void EE_PPCE200ZX_205_ISR(void);
#else
#define EE_PPCE200ZX_205_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_206_ISR
extern void EE_PPCE200ZX_206_ISR(void);
#else
#define EE_PPCE200ZX_206_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_207_ISR
extern void EE_PPCE200ZX_207_ISR(void);
#else
#define EE_PPCE200ZX_207_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_208_ISR
extern void EE_PPCE200ZX_208_ISR(void);
#else
#define EE_PPCE200ZX_208_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_209_ISR
extern void EE_PPCE200ZX_209_ISR(void);
#else
#define EE_PPCE200ZX_209_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_210_ISR
extern void EE_PPCE200ZX_210_ISR(void);
#else
#define EE_PPCE200ZX_210_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_211_ISR
extern void EE_PPCE200ZX_211_ISR(void);
#else
#define EE_PPCE200ZX_211_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_212_ISR
extern void EE_PPCE200ZX_212_ISR(void);
#else
#define EE_PPCE200ZX_212_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_213_ISR
extern void EE_PPCE200ZX_213_ISR(void);
#else
#define EE_PPCE200ZX_213_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_214_ISR
extern void EE_PPCE200ZX_214_ISR(void);
#else
#define EE_PPCE200ZX_214_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_215_ISR
extern void EE_PPCE200ZX_215_ISR(void);
#else
#define EE_PPCE200ZX_215_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_216_ISR
extern void EE_PPCE200ZX_216_ISR(void);
#else
#define EE_PPCE200ZX_216_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_217_ISR
extern void EE_PPCE200ZX_217_ISR(void);
#else
#define EE_PPCE200ZX_217_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_218_ISR
extern void EE_PPCE200ZX_218_ISR(void);
#else
#define EE_PPCE200ZX_218_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_219_ISR
extern void EE_PPCE200ZX_219_ISR(void);
#else
#define EE_PPCE200ZX_219_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_220_ISR
extern void EE_PPCE200ZX_220_ISR(void);
#else
#define EE_PPCE200ZX_220_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_221_ISR
extern void EE_PPCE200ZX_221_ISR(void);
#else
#define EE_PPCE200ZX_221_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_222_ISR
extern void EE_PPCE200ZX_222_ISR(void);
#else
#define EE_PPCE200ZX_222_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_223_ISR
extern void EE_PPCE200ZX_223_ISR(void);
#else
#define EE_PPCE200ZX_223_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_224_ISR
extern void EE_PPCE200ZX_224_ISR(void);
#else
#define EE_PPCE200ZX_224_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_225_ISR
extern void EE_PPCE200ZX_225_ISR(void);
#else
#define EE_PPCE200ZX_225_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_226_ISR
extern void EE_PPCE200ZX_226_ISR(void);
#else
#define EE_PPCE200ZX_226_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_227_ISR
extern void EE_PPCE200ZX_227_ISR(void);
#else
#define EE_PPCE200ZX_227_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_228_ISR
extern void EE_PPCE200ZX_228_ISR(void);
#else
#define EE_PPCE200ZX_228_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_229_ISR
extern void EE_PPCE200ZX_229_ISR(void);
#else
#define EE_PPCE200ZX_229_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_230_ISR
extern void EE_PPCE200ZX_230_ISR(void);
#else
#define EE_PPCE200ZX_230_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_231_ISR
extern void EE_PPCE200ZX_231_ISR(void);
#else
#define EE_PPCE200ZX_231_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_232_ISR
extern void EE_PPCE200ZX_232_ISR(void);
#else
#define EE_PPCE200ZX_232_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_233_ISR
extern void EE_PPCE200ZX_233_ISR(void);
#else
#define EE_PPCE200ZX_233_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_234_ISR
extern void EE_PPCE200ZX_234_ISR(void);
#else
#define EE_PPCE200ZX_234_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_235_ISR
extern void EE_PPCE200ZX_235_ISR(void);
#else
#define EE_PPCE200ZX_235_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_236_ISR
extern void EE_PPCE200ZX_236_ISR(void);
#else
#define EE_PPCE200ZX_236_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_237_ISR
extern void EE_PPCE200ZX_237_ISR(void);
#else
#define EE_PPCE200ZX_237_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_238_ISR
extern void EE_PPCE200ZX_238_ISR(void);
#else
#define EE_PPCE200ZX_238_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_239_ISR
extern void EE_PPCE200ZX_239_ISR(void);
#else
#define EE_PPCE200ZX_239_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_240_ISR
extern void EE_PPCE200ZX_240_ISR(void);
#else
#define EE_PPCE200ZX_240_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_241_ISR
extern void EE_PPCE200ZX_241_ISR(void);
#else
#define EE_PPCE200ZX_241_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_242_ISR
extern void EE_PPCE200ZX_242_ISR(void);
#else
#define EE_PPCE200ZX_242_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_243_ISR
extern void EE_PPCE200ZX_243_ISR(void);
#else
#define EE_PPCE200ZX_243_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_244_ISR
extern void EE_PPCE200ZX_244_ISR(void);
#else
#define EE_PPCE200ZX_244_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_245_ISR
extern void EE_PPCE200ZX_245_ISR(void);
#else
#define EE_PPCE200ZX_245_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_246_ISR
extern void EE_PPCE200ZX_246_ISR(void);
#else
#define EE_PPCE200ZX_246_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_247_ISR
extern void EE_PPCE200ZX_247_ISR(void);
#else
#define EE_PPCE200ZX_247_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_248_ISR
extern void EE_PPCE200ZX_248_ISR(void);
#else
#define EE_PPCE200ZX_248_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_249_ISR
extern void EE_PPCE200ZX_249_ISR(void);
#else
#define EE_PPCE200ZX_249_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_250_ISR
extern void EE_PPCE200ZX_250_ISR(void);
#else
#define EE_PPCE200ZX_250_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_251_ISR
extern void EE_PPCE200ZX_251_ISR(void);
#else
#define EE_PPCE200ZX_251_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_252_ISR
extern void EE_PPCE200ZX_252_ISR(void);
#else
#define EE_PPCE200ZX_252_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_253_ISR
extern void EE_PPCE200ZX_253_ISR(void);
#else
#define EE_PPCE200ZX_253_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_254_ISR
extern void EE_PPCE200ZX_254_ISR(void);
#else
#define EE_PPCE200ZX_254_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_255_ISR
extern void EE_PPCE200ZX_255_ISR(void);
#else
#define EE_PPCE200ZX_255_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_256_ISR
extern void EE_PPCE200ZX_256_ISR(void);
#else
#define EE_PPCE200ZX_256_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_257_ISR
extern void EE_PPCE200ZX_257_ISR(void);
#else
#define EE_PPCE200ZX_257_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_258_ISR
extern void EE_PPCE200ZX_258_ISR(void);
#else
#define EE_PPCE200ZX_258_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_259_ISR
extern void EE_PPCE200ZX_259_ISR(void);
#else
#define EE_PPCE200ZX_259_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_260_ISR
extern void EE_PPCE200ZX_260_ISR(void);
#else
#define EE_PPCE200ZX_260_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_261_ISR
extern void EE_PPCE200ZX_261_ISR(void);
#else
#define EE_PPCE200ZX_261_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_262_ISR
extern void EE_PPCE200ZX_262_ISR(void);
#else
#define EE_PPCE200ZX_262_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_263_ISR
extern void EE_PPCE200ZX_263_ISR(void);
#else
#define EE_PPCE200ZX_263_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_264_ISR
extern void EE_PPCE200ZX_264_ISR(void);
#else
#define EE_PPCE200ZX_264_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_265_ISR
extern void EE_PPCE200ZX_265_ISR(void);
#else
#define EE_PPCE200ZX_265_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_266_ISR
extern void EE_PPCE200ZX_266_ISR(void);
#else
#define EE_PPCE200ZX_266_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_267_ISR
extern void EE_PPCE200ZX_267_ISR(void);
#else
#define EE_PPCE200ZX_267_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_268_ISR
extern void EE_PPCE200ZX_268_ISR(void);
#else
#define EE_PPCE200ZX_268_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_269_ISR
extern void EE_PPCE200ZX_269_ISR(void);
#else
#define EE_PPCE200ZX_269_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_270_ISR
extern void EE_PPCE200ZX_270_ISR(void);
#else
#define EE_PPCE200ZX_270_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_271_ISR
extern void EE_PPCE200ZX_271_ISR(void);
#else
#define EE_PPCE200ZX_271_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_272_ISR
extern void EE_PPCE200ZX_272_ISR(void);
#else
#define EE_PPCE200ZX_272_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_273_ISR
extern void EE_PPCE200ZX_273_ISR(void);
#else
#define EE_PPCE200ZX_273_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_274_ISR
extern void EE_PPCE200ZX_274_ISR(void);
#else
#define EE_PPCE200ZX_274_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_275_ISR
extern void EE_PPCE200ZX_275_ISR(void);
#else
#define EE_PPCE200ZX_275_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_276_ISR
extern void EE_PPCE200ZX_276_ISR(void);
#else
#define EE_PPCE200ZX_276_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_277_ISR
extern void EE_PPCE200ZX_277_ISR(void);
#else
#define EE_PPCE200ZX_277_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_278_ISR
extern void EE_PPCE200ZX_278_ISR(void);
#else
#define EE_PPCE200ZX_278_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_279_ISR
extern void EE_PPCE200ZX_279_ISR(void);
#else
#define EE_PPCE200ZX_279_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_280_ISR
extern void EE_PPCE200ZX_280_ISR(void);
#else
#define EE_PPCE200ZX_280_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_281_ISR
extern void EE_PPCE200ZX_281_ISR(void);
#else
#define EE_PPCE200ZX_281_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_282_ISR
extern void EE_PPCE200ZX_282_ISR(void);
#else
#define EE_PPCE200ZX_282_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_283_ISR
extern void EE_PPCE200ZX_283_ISR(void);
#else
#define EE_PPCE200ZX_283_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_284_ISR
extern void EE_PPCE200ZX_284_ISR(void);
#else
#define EE_PPCE200ZX_284_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_285_ISR
extern void EE_PPCE200ZX_285_ISR(void);
#else
#define EE_PPCE200ZX_285_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_286_ISR
extern void EE_PPCE200ZX_286_ISR(void);
#else
#define EE_PPCE200ZX_286_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_287_ISR
extern void EE_PPCE200ZX_287_ISR(void);
#else
#define EE_PPCE200ZX_287_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_288_ISR
extern void EE_PPCE200ZX_288_ISR(void);
#else
#define EE_PPCE200ZX_288_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_289_ISR
extern void EE_PPCE200ZX_289_ISR(void);
#else
#define EE_PPCE200ZX_289_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_290_ISR
extern void EE_PPCE200ZX_290_ISR(void);
#else
#define EE_PPCE200ZX_290_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_291_ISR
extern void EE_PPCE200ZX_291_ISR(void);
#else
#define EE_PPCE200ZX_291_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_292_ISR
extern void EE_PPCE200ZX_292_ISR(void);
#else
#define EE_PPCE200ZX_292_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_293_ISR
extern void EE_PPCE200ZX_293_ISR(void);
#else
#define EE_PPCE200ZX_293_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_294_ISR
extern void EE_PPCE200ZX_294_ISR(void);
#else
#define EE_PPCE200ZX_294_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_295_ISR
extern void EE_PPCE200ZX_295_ISR(void);
#else
#define EE_PPCE200ZX_295_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_296_ISR
extern void EE_PPCE200ZX_296_ISR(void);
#else
#define EE_PPCE200ZX_296_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_297_ISR
extern void EE_PPCE200ZX_297_ISR(void);
#else
#define EE_PPCE200ZX_297_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_298_ISR
extern void EE_PPCE200ZX_298_ISR(void);
#else
#define EE_PPCE200ZX_298_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_299_ISR
extern void EE_PPCE200ZX_299_ISR(void);
#else
#define EE_PPCE200ZX_299_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_300_ISR
extern void EE_PPCE200ZX_300_ISR(void);
#else
#define EE_PPCE200ZX_300_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_301_ISR
extern void EE_PPCE200ZX_301_ISR(void);
#else
#define EE_PPCE200ZX_301_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_302_ISR
extern void EE_PPCE200ZX_302_ISR(void);
#else
#define EE_PPCE200ZX_302_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_303_ISR
extern void EE_PPCE200ZX_303_ISR(void);
#else
#define EE_PPCE200ZX_303_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_304_ISR
extern void EE_PPCE200ZX_304_ISR(void);
#else
#define EE_PPCE200ZX_304_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_305_ISR
extern void EE_PPCE200ZX_305_ISR(void);
#else
#define EE_PPCE200ZX_305_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_306_ISR
extern void EE_PPCE200ZX_306_ISR(void);
#else
#define EE_PPCE200ZX_306_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_307_ISR
extern void EE_PPCE200ZX_307_ISR(void);
#else
#define EE_PPCE200ZX_307_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_308_ISR
extern void EE_PPCE200ZX_308_ISR(void);
#else
#define EE_PPCE200ZX_308_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_309_ISR
extern void EE_PPCE200ZX_309_ISR(void);
#else
#define EE_PPCE200ZX_309_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_310_ISR
extern void EE_PPCE200ZX_310_ISR(void);
#else
#define EE_PPCE200ZX_310_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_311_ISR
extern void EE_PPCE200ZX_311_ISR(void);
#else
#define EE_PPCE200ZX_311_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_312_ISR
extern void EE_PPCE200ZX_312_ISR(void);
#else
#define EE_PPCE200ZX_312_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_313_ISR
extern void EE_PPCE200ZX_313_ISR(void);
#else
#define EE_PPCE200ZX_313_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_314_ISR
extern void EE_PPCE200ZX_314_ISR(void);
#else
#define EE_PPCE200ZX_314_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_315_ISR
extern void EE_PPCE200ZX_315_ISR(void);
#else
#define EE_PPCE200ZX_315_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_316_ISR
extern void EE_PPCE200ZX_316_ISR(void);
#else
#define EE_PPCE200ZX_316_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_317_ISR
extern void EE_PPCE200ZX_317_ISR(void);
#else
#define EE_PPCE200ZX_317_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_318_ISR
extern void EE_PPCE200ZX_318_ISR(void);
#else
#define EE_PPCE200ZX_318_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_319_ISR
extern void EE_PPCE200ZX_319_ISR(void);
#else
#define EE_PPCE200ZX_319_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_320_ISR
extern void EE_PPCE200ZX_320_ISR(void);
#else
#define EE_PPCE200ZX_320_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_321_ISR
extern void EE_PPCE200ZX_321_ISR(void);
#else
#define EE_PPCE200ZX_321_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_322_ISR
extern void EE_PPCE200ZX_322_ISR(void);
#else
#define EE_PPCE200ZX_322_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_323_ISR
extern void EE_PPCE200ZX_323_ISR(void);
#else
#define EE_PPCE200ZX_323_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_324_ISR
extern void EE_PPCE200ZX_324_ISR(void);
#else
#define EE_PPCE200ZX_324_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_325_ISR
extern void EE_PPCE200ZX_325_ISR(void);
#else
#define EE_PPCE200ZX_325_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_326_ISR
extern void EE_PPCE200ZX_326_ISR(void);
#else
#define EE_PPCE200ZX_326_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_327_ISR
extern void EE_PPCE200ZX_327_ISR(void);
#else
#define EE_PPCE200ZX_327_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_328_ISR
extern void EE_PPCE200ZX_328_ISR(void);
#else
#define EE_PPCE200ZX_328_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_329_ISR
extern void EE_PPCE200ZX_329_ISR(void);
#else
#define EE_PPCE200ZX_329_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_330_ISR
extern void EE_PPCE200ZX_330_ISR(void);
#else
#define EE_PPCE200ZX_330_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_331_ISR
extern void EE_PPCE200ZX_331_ISR(void);
#else
#define EE_PPCE200ZX_331_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_332_ISR
extern void EE_PPCE200ZX_332_ISR(void);
#else
#define EE_PPCE200ZX_332_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_333_ISR
extern void EE_PPCE200ZX_333_ISR(void);
#else
#define EE_PPCE200ZX_333_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_334_ISR
extern void EE_PPCE200ZX_334_ISR(void);
#else
#define EE_PPCE200ZX_334_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_335_ISR
extern void EE_PPCE200ZX_335_ISR(void);
#else
#define EE_PPCE200ZX_335_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_336_ISR
extern void EE_PPCE200ZX_336_ISR(void);
#else
#define EE_PPCE200ZX_336_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_337_ISR
extern void EE_PPCE200ZX_337_ISR(void);
#else
#define EE_PPCE200ZX_337_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_338_ISR
extern void EE_PPCE200ZX_338_ISR(void);
#else
#define EE_PPCE200ZX_338_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_339_ISR
extern void EE_PPCE200ZX_339_ISR(void);
#else
#define EE_PPCE200ZX_339_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_340_ISR
extern void EE_PPCE200ZX_340_ISR(void);
#else
#define EE_PPCE200ZX_340_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_341_ISR
extern void EE_PPCE200ZX_341_ISR(void);
#else
#define EE_PPCE200ZX_341_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_342_ISR
extern void EE_PPCE200ZX_342_ISR(void);
#else
#define EE_PPCE200ZX_342_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_343_ISR
extern void EE_PPCE200ZX_343_ISR(void);
#else
#define EE_PPCE200ZX_343_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_344_ISR
extern void EE_PPCE200ZX_344_ISR(void);
#else
#define EE_PPCE200ZX_344_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_345_ISR
extern void EE_PPCE200ZX_345_ISR(void);
#else
#define EE_PPCE200ZX_345_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_346_ISR
extern void EE_PPCE200ZX_346_ISR(void);
#else
#define EE_PPCE200ZX_346_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_347_ISR
extern void EE_PPCE200ZX_347_ISR(void);
#else
#define EE_PPCE200ZX_347_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_348_ISR
extern void EE_PPCE200ZX_348_ISR(void);
#else
#define EE_PPCE200ZX_348_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_349_ISR
extern void EE_PPCE200ZX_349_ISR(void);
#else
#define EE_PPCE200ZX_349_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_350_ISR
extern void EE_PPCE200ZX_350_ISR(void);
#else
#define EE_PPCE200ZX_350_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_351_ISR
extern void EE_PPCE200ZX_351_ISR(void);
#else
#define EE_PPCE200ZX_351_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_352_ISR
extern void EE_PPCE200ZX_352_ISR(void);
#else
#define EE_PPCE200ZX_352_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_353_ISR
extern void EE_PPCE200ZX_353_ISR(void);
#else
#define EE_PPCE200ZX_353_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_354_ISR
extern void EE_PPCE200ZX_354_ISR(void);
#else
#define EE_PPCE200ZX_354_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_355_ISR
extern void EE_PPCE200ZX_355_ISR(void);
#else
#define EE_PPCE200ZX_355_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_356_ISR
extern void EE_PPCE200ZX_356_ISR(void);
#else
#define EE_PPCE200ZX_356_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_357_ISR
extern void EE_PPCE200ZX_357_ISR(void);
#else
#define EE_PPCE200ZX_357_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_358_ISR
extern void EE_PPCE200ZX_358_ISR(void);
#else
#define EE_PPCE200ZX_358_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_359_ISR
extern void EE_PPCE200ZX_359_ISR(void);
#else
#define EE_PPCE200ZX_359_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_360_ISR
extern void EE_PPCE200ZX_360_ISR(void);
#else
#define EE_PPCE200ZX_360_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_361_ISR
extern void EE_PPCE200ZX_361_ISR(void);
#else
#define EE_PPCE200ZX_361_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_362_ISR
extern void EE_PPCE200ZX_362_ISR(void);
#else
#define EE_PPCE200ZX_362_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_363_ISR
extern void EE_PPCE200ZX_363_ISR(void);
#else
#define EE_PPCE200ZX_363_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_364_ISR
extern void EE_PPCE200ZX_364_ISR(void);
#else
#define EE_PPCE200ZX_364_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_365_ISR
extern void EE_PPCE200ZX_365_ISR(void);
#else
#define EE_PPCE200ZX_365_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_366_ISR
extern void EE_PPCE200ZX_366_ISR(void);
#else
#define EE_PPCE200ZX_366_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_367_ISR
extern void EE_PPCE200ZX_367_ISR(void);
#else
#define EE_PPCE200ZX_367_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_368_ISR
extern void EE_PPCE200ZX_368_ISR(void);
#else
#define EE_PPCE200ZX_368_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_369_ISR
extern void EE_PPCE200ZX_369_ISR(void);
#else
#define EE_PPCE200ZX_369_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_370_ISR
extern void EE_PPCE200ZX_370_ISR(void);
#else
#define EE_PPCE200ZX_370_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_371_ISR
extern void EE_PPCE200ZX_371_ISR(void);
#else
#define EE_PPCE200ZX_371_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_372_ISR
extern void EE_PPCE200ZX_372_ISR(void);
#else
#define EE_PPCE200ZX_372_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_373_ISR
extern void EE_PPCE200ZX_373_ISR(void);
#else
#define EE_PPCE200ZX_373_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_374_ISR
extern void EE_PPCE200ZX_374_ISR(void);
#else
#define EE_PPCE200ZX_374_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_375_ISR
extern void EE_PPCE200ZX_375_ISR(void);
#else
#define EE_PPCE200ZX_375_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_376_ISR
extern void EE_PPCE200ZX_376_ISR(void);
#else
#define EE_PPCE200ZX_376_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_377_ISR
extern void EE_PPCE200ZX_377_ISR(void);
#else
#define EE_PPCE200ZX_377_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_378_ISR
extern void EE_PPCE200ZX_378_ISR(void);
#else
#define EE_PPCE200ZX_378_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_379_ISR
extern void EE_PPCE200ZX_379_ISR(void);
#else
#define EE_PPCE200ZX_379_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_380_ISR
extern void EE_PPCE200ZX_380_ISR(void);
#else
#define EE_PPCE200ZX_380_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_381_ISR
extern void EE_PPCE200ZX_381_ISR(void);
#else
#define EE_PPCE200ZX_381_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_382_ISR
extern void EE_PPCE200ZX_382_ISR(void);
#else
#define EE_PPCE200ZX_382_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_383_ISR
extern void EE_PPCE200ZX_383_ISR(void);
#else
#define EE_PPCE200ZX_383_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_384_ISR
extern void EE_PPCE200ZX_384_ISR(void);
#else
#define EE_PPCE200ZX_384_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_385_ISR
extern void EE_PPCE200ZX_385_ISR(void);
#else
#define EE_PPCE200ZX_385_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_386_ISR
extern void EE_PPCE200ZX_386_ISR(void);
#else
#define EE_PPCE200ZX_386_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_387_ISR
extern void EE_PPCE200ZX_387_ISR(void);
#else
#define EE_PPCE200ZX_387_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_388_ISR
extern void EE_PPCE200ZX_388_ISR(void);
#else
#define EE_PPCE200ZX_388_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_389_ISR
extern void EE_PPCE200ZX_389_ISR(void);
#else
#define EE_PPCE200ZX_389_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_390_ISR
extern void EE_PPCE200ZX_390_ISR(void);
#else
#define EE_PPCE200ZX_390_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_391_ISR
extern void EE_PPCE200ZX_391_ISR(void);
#else
#define EE_PPCE200ZX_391_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_392_ISR
extern void EE_PPCE200ZX_392_ISR(void);
#else
#define EE_PPCE200ZX_392_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_393_ISR
extern void EE_PPCE200ZX_393_ISR(void);
#else
#define EE_PPCE200ZX_393_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_394_ISR
extern void EE_PPCE200ZX_394_ISR(void);
#else
#define EE_PPCE200ZX_394_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_395_ISR
extern void EE_PPCE200ZX_395_ISR(void);
#else
#define EE_PPCE200ZX_395_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_396_ISR
extern void EE_PPCE200ZX_396_ISR(void);
#else
#define EE_PPCE200ZX_396_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_397_ISR
extern void EE_PPCE200ZX_397_ISR(void);
#else
#define EE_PPCE200ZX_397_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_398_ISR
extern void EE_PPCE200ZX_398_ISR(void);
#else
#define EE_PPCE200ZX_398_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_399_ISR
extern void EE_PPCE200ZX_399_ISR(void);
#else
#define EE_PPCE200ZX_399_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_400_ISR
extern void EE_PPCE200ZX_400_ISR(void);
#else
#define EE_PPCE200ZX_400_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_401_ISR
extern void EE_PPCE200ZX_401_ISR(void);
#else
#define EE_PPCE200ZX_401_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_402_ISR
extern void EE_PPCE200ZX_402_ISR(void);
#else
#define EE_PPCE200ZX_402_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_403_ISR
extern void EE_PPCE200ZX_403_ISR(void);
#else
#define EE_PPCE200ZX_403_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_404_ISR
extern void EE_PPCE200ZX_404_ISR(void);
#else
#define EE_PPCE200ZX_404_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_405_ISR
extern void EE_PPCE200ZX_405_ISR(void);
#else
#define EE_PPCE200ZX_405_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_406_ISR
extern void EE_PPCE200ZX_406_ISR(void);
#else
#define EE_PPCE200ZX_406_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_407_ISR
extern void EE_PPCE200ZX_407_ISR(void);
#else
#define EE_PPCE200ZX_407_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_408_ISR
extern void EE_PPCE200ZX_408_ISR(void);
#else
#define EE_PPCE200ZX_408_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_409_ISR
extern void EE_PPCE200ZX_409_ISR(void);
#else
#define EE_PPCE200ZX_409_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_410_ISR
extern void EE_PPCE200ZX_410_ISR(void);
#else
#define EE_PPCE200ZX_410_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_411_ISR
extern void EE_PPCE200ZX_411_ISR(void);
#else
#define EE_PPCE200ZX_411_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_412_ISR
extern void EE_PPCE200ZX_412_ISR(void);
#else
#define EE_PPCE200ZX_412_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_413_ISR
extern void EE_PPCE200ZX_413_ISR(void);
#else
#define EE_PPCE200ZX_413_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_414_ISR
extern void EE_PPCE200ZX_414_ISR(void);
#else
#define EE_PPCE200ZX_414_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_415_ISR
extern void EE_PPCE200ZX_415_ISR(void);
#else
#define EE_PPCE200ZX_415_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_416_ISR
extern void EE_PPCE200ZX_416_ISR(void);
#else
#define EE_PPCE200ZX_416_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_417_ISR
extern void EE_PPCE200ZX_417_ISR(void);
#else
#define EE_PPCE200ZX_417_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_418_ISR
extern void EE_PPCE200ZX_418_ISR(void);
#else
#define EE_PPCE200ZX_418_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_419_ISR
extern void EE_PPCE200ZX_419_ISR(void);
#else
#define EE_PPCE200ZX_419_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_420_ISR
extern void EE_PPCE200ZX_420_ISR(void);
#else
#define EE_PPCE200ZX_420_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_421_ISR
extern void EE_PPCE200ZX_421_ISR(void);
#else
#define EE_PPCE200ZX_421_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_422_ISR
extern void EE_PPCE200ZX_422_ISR(void);
#else
#define EE_PPCE200ZX_422_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_423_ISR
extern void EE_PPCE200ZX_423_ISR(void);
#else
#define EE_PPCE200ZX_423_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_424_ISR
extern void EE_PPCE200ZX_424_ISR(void);
#else
#define EE_PPCE200ZX_424_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_425_ISR
extern void EE_PPCE200ZX_425_ISR(void);
#else
#define EE_PPCE200ZX_425_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_426_ISR
extern void EE_PPCE200ZX_426_ISR(void);
#else
#define EE_PPCE200ZX_426_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_427_ISR
extern void EE_PPCE200ZX_427_ISR(void);
#else
#define EE_PPCE200ZX_427_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_428_ISR
extern void EE_PPCE200ZX_428_ISR(void);
#else
#define EE_PPCE200ZX_428_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_429_ISR
extern void EE_PPCE200ZX_429_ISR(void);
#else
#define EE_PPCE200ZX_429_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_430_ISR
extern void EE_PPCE200ZX_430_ISR(void);
#else
#define EE_PPCE200ZX_430_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_431_ISR
extern void EE_PPCE200ZX_431_ISR(void);
#else
#define EE_PPCE200ZX_431_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_432_ISR
extern void EE_PPCE200ZX_432_ISR(void);
#else
#define EE_PPCE200ZX_432_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_433_ISR
extern void EE_PPCE200ZX_433_ISR(void);
#else
#define EE_PPCE200ZX_433_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_434_ISR
extern void EE_PPCE200ZX_434_ISR(void);
#else
#define EE_PPCE200ZX_434_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_435_ISR
extern void EE_PPCE200ZX_435_ISR(void);
#else
#define EE_PPCE200ZX_435_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_436_ISR
extern void EE_PPCE200ZX_436_ISR(void);
#else
#define EE_PPCE200ZX_436_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_437_ISR
extern void EE_PPCE200ZX_437_ISR(void);
#else
#define EE_PPCE200ZX_437_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_438_ISR
extern void EE_PPCE200ZX_438_ISR(void);
#else
#define EE_PPCE200ZX_438_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_439_ISR
extern void EE_PPCE200ZX_439_ISR(void);
#else
#define EE_PPCE200ZX_439_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_440_ISR
extern void EE_PPCE200ZX_440_ISR(void);
#else
#define EE_PPCE200ZX_440_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_441_ISR
extern void EE_PPCE200ZX_441_ISR(void);
#else
#define EE_PPCE200ZX_441_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_442_ISR
extern void EE_PPCE200ZX_442_ISR(void);
#else
#define EE_PPCE200ZX_442_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_443_ISR
extern void EE_PPCE200ZX_443_ISR(void);
#else
#define EE_PPCE200ZX_443_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_444_ISR
extern void EE_PPCE200ZX_444_ISR(void);
#else
#define EE_PPCE200ZX_444_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_445_ISR
extern void EE_PPCE200ZX_445_ISR(void);
#else
#define EE_PPCE200ZX_445_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_446_ISR
extern void EE_PPCE200ZX_446_ISR(void);
#else
#define EE_PPCE200ZX_446_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_447_ISR
extern void EE_PPCE200ZX_447_ISR(void);
#else
#define EE_PPCE200ZX_447_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_448_ISR
extern void EE_PPCE200ZX_448_ISR(void);
#else
#define EE_PPCE200ZX_448_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_449_ISR
extern void EE_PPCE200ZX_449_ISR(void);
#else
#define EE_PPCE200ZX_449_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_450_ISR
extern void EE_PPCE200ZX_450_ISR(void);
#else
#define EE_PPCE200ZX_450_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_451_ISR
extern void EE_PPCE200ZX_451_ISR(void);
#else
#define EE_PPCE200ZX_451_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_452_ISR
extern void EE_PPCE200ZX_452_ISR(void);
#else
#define EE_PPCE200ZX_452_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_453_ISR
extern void EE_PPCE200ZX_453_ISR(void);
#else
#define EE_PPCE200ZX_453_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_454_ISR
extern void EE_PPCE200ZX_454_ISR(void);
#else
#define EE_PPCE200ZX_454_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_455_ISR
extern void EE_PPCE200ZX_455_ISR(void);
#else
#define EE_PPCE200ZX_455_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_456_ISR
extern void EE_PPCE200ZX_456_ISR(void);
#else
#define EE_PPCE200ZX_456_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_457_ISR
extern void EE_PPCE200ZX_457_ISR(void);
#else
#define EE_PPCE200ZX_457_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_458_ISR
extern void EE_PPCE200ZX_458_ISR(void);
#else
#define EE_PPCE200ZX_458_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_459_ISR
extern void EE_PPCE200ZX_459_ISR(void);
#else
#define EE_PPCE200ZX_459_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_460_ISR
extern void EE_PPCE200ZX_460_ISR(void);
#else
#define EE_PPCE200ZX_460_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_461_ISR
extern void EE_PPCE200ZX_461_ISR(void);
#else
#define EE_PPCE200ZX_461_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_462_ISR
extern void EE_PPCE200ZX_462_ISR(void);
#else
#define EE_PPCE200ZX_462_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_463_ISR
extern void EE_PPCE200ZX_463_ISR(void);
#else
#define EE_PPCE200ZX_463_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_464_ISR
extern void EE_PPCE200ZX_464_ISR(void);
#else
#define EE_PPCE200ZX_464_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_465_ISR
extern void EE_PPCE200ZX_465_ISR(void);
#else
#define EE_PPCE200ZX_465_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_466_ISR
extern void EE_PPCE200ZX_466_ISR(void);
#else
#define EE_PPCE200ZX_466_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_467_ISR
extern void EE_PPCE200ZX_467_ISR(void);
#else
#define EE_PPCE200ZX_467_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_468_ISR
extern void EE_PPCE200ZX_468_ISR(void);
#else
#define EE_PPCE200ZX_468_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_469_ISR
extern void EE_PPCE200ZX_469_ISR(void);
#else
#define EE_PPCE200ZX_469_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_470_ISR
extern void EE_PPCE200ZX_470_ISR(void);
#else
#define EE_PPCE200ZX_470_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_471_ISR
extern void EE_PPCE200ZX_471_ISR(void);
#else
#define EE_PPCE200ZX_471_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_472_ISR
extern void EE_PPCE200ZX_472_ISR(void);
#else
#define EE_PPCE200ZX_472_ISR DEFAULT_IRQ_ENTRY
#endif

#ifdef EE_PPCE200ZX_473_ISR
extern void EE_PPCE200ZX_473_ISR(void);
#else
#define EE_PPCE200ZX_473_ISR DEFAULT_IRQ_ENTRY
#endif

/*
  Number of internal CPU exceptions (in cpu/e200zx/inc/ee_cpu_asm.h)
  EE_E200ZX_MAX_CPU_EXCP 16 
  Max External IRQ (in mcu/freescale_mpc5674f/ee_mpc5674f.h)
  EE_E200ZX_MAX_EXT_IRQ 474U

  It has been made const so it can be put in flash
 */
const EE_e200z7_ISR_handler EE_e200z7_ISR_table[EE_E200ZX_MAX_CPU_EXCP +
  EE_E200ZX_MAX_EXT_IRQ] = 
{
  /* SOFTWARE HANDLER FOR INTERNAL CPU EXCEPTION TO ENABLE THOSE THAT POINT TO
     __empty_handler WE HAVE TO CHANGE e200zx/src/ee_ivor.S */
  /* Zen EE_e200zx_critical_input set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR0 */
  /* Zen EE_e200zx_machine_check set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR1 */
  /* Zen EE_e200zx_data_storage set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR2 */
  /* Zen EE_EE_e200zx_instruction_storage set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR3 */
  /* Zen vector EE_e200zx_external_input set to  
     EE_e200zx_external_input_handler because IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR4 */
  /* Zen EE_e200zx_alignment set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR5 */
  /* Zen EE_e200zx_program set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR6 */
  /* Zen EE_e200zx_float_unavailable set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR7 */
  /* Zen EE_e200zx_system_call set to  used for memory protection */
  (EE_e200z7_ISR_handler)0, /* IVOR8 */
  /* Zen EE_e200zx_auxiliary_unavailable set to __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR9 */
  /* Zen EE_e200zx_decrementer set to EE_e200zx_decrementer_handler by IVOR */
  /* Special Entry is used as ISR2 for System Timer */
  EE_PPCE200ZX_DECREMENTER_ISR, /* IVOR10 */
  /* Zen EE_e200zx_interval_timer set to EE_e200zx_fixed_intv_handler by IVOR */
  EE_PPCE200ZX_FIXED_INTV_ISR, /* IVOR11 */
  /* Zen EE_e200zx_watchdog_timer set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR12 */
  /* Zen EE_e200zx_data_tlb_error set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR13 */
  /* Zen EE_e200zx_instruction_tlb_error set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR14 */
  /* Zen EE_e200zx_debug_critical set to  __empty_handler by IVOR */
  (EE_e200z7_ISR_handler)0, /* IVOR15 */

  /*  FROM HEREUNDER ARE ALL EXTERNAL INTERRUPT SOURCES,
      Position equal EE_E200ZX_MAX_CPU_EXCP + Vector Number */
  EE_PPCE200ZX_0_ISR,
  EE_PPCE200ZX_1_ISR,
  EE_PPCE200ZX_2_ISR,
  EE_PPCE200ZX_3_ISR,
  EE_PPCE200ZX_4_ISR,
  EE_PPCE200ZX_5_ISR,
  EE_PPCE200ZX_6_ISR,
  EE_PPCE200ZX_7_ISR,
  EE_PPCE200ZX_8_ISR,
  EE_PPCE200ZX_9_ISR,
  EE_PPCE200ZX_10_ISR,
  EE_PPCE200ZX_11_ISR,
  EE_PPCE200ZX_12_ISR,
  EE_PPCE200ZX_13_ISR,
  EE_PPCE200ZX_14_ISR,
  EE_PPCE200ZX_15_ISR,
  EE_PPCE200ZX_16_ISR,
  EE_PPCE200ZX_17_ISR,
  EE_PPCE200ZX_18_ISR,
  EE_PPCE200ZX_19_ISR,
  EE_PPCE200ZX_20_ISR,
  EE_PPCE200ZX_21_ISR,
  EE_PPCE200ZX_22_ISR,
  EE_PPCE200ZX_23_ISR,
  EE_PPCE200ZX_24_ISR,
  EE_PPCE200ZX_25_ISR,
  EE_PPCE200ZX_26_ISR,
  EE_PPCE200ZX_27_ISR,
  EE_PPCE200ZX_28_ISR,
  EE_PPCE200ZX_29_ISR,
  EE_PPCE200ZX_30_ISR,
  EE_PPCE200ZX_31_ISR,
  EE_PPCE200ZX_32_ISR,
  EE_PPCE200ZX_33_ISR,
  EE_PPCE200ZX_34_ISR,
  EE_PPCE200ZX_35_ISR,
  EE_PPCE200ZX_36_ISR,
  EE_PPCE200ZX_37_ISR,
  EE_PPCE200ZX_38_ISR,
  EE_PPCE200ZX_39_ISR,
  EE_PPCE200ZX_40_ISR,
  EE_PPCE200ZX_41_ISR,
  EE_PPCE200ZX_42_ISR,
  EE_PPCE200ZX_43_ISR,
  EE_PPCE200ZX_44_ISR,
  EE_PPCE200ZX_45_ISR,
  EE_PPCE200ZX_46_ISR,
  EE_PPCE200ZX_47_ISR,
  EE_PPCE200ZX_48_ISR,
  EE_PPCE200ZX_49_ISR,
  EE_PPCE200ZX_50_ISR,
  EE_PPCE200ZX_51_ISR,
  EE_PPCE200ZX_52_ISR,
  EE_PPCE200ZX_53_ISR,
  EE_PPCE200ZX_54_ISR,
  EE_PPCE200ZX_55_ISR,
  EE_PPCE200ZX_56_ISR,
  EE_PPCE200ZX_57_ISR,
  EE_PPCE200ZX_58_ISR,
  EE_PPCE200ZX_59_ISR,
  EE_PPCE200ZX_60_ISR,
  EE_PPCE200ZX_61_ISR,
  EE_PPCE200ZX_62_ISR,
  EE_PPCE200ZX_63_ISR,
  EE_PPCE200ZX_64_ISR,
  EE_PPCE200ZX_65_ISR,
  EE_PPCE200ZX_66_ISR,
  EE_PPCE200ZX_67_ISR,
  EE_PPCE200ZX_68_ISR,
  EE_PPCE200ZX_69_ISR,
  EE_PPCE200ZX_70_ISR,
  EE_PPCE200ZX_71_ISR,
  EE_PPCE200ZX_72_ISR,
  EE_PPCE200ZX_73_ISR,
  EE_PPCE200ZX_74_ISR,
  EE_PPCE200ZX_75_ISR,
  EE_PPCE200ZX_76_ISR,
  EE_PPCE200ZX_77_ISR,
  EE_PPCE200ZX_78_ISR,
  EE_PPCE200ZX_79_ISR,
  EE_PPCE200ZX_80_ISR,
  EE_PPCE200ZX_81_ISR,
  EE_PPCE200ZX_82_ISR,
  EE_PPCE200ZX_83_ISR,
  EE_PPCE200ZX_84_ISR,
  EE_PPCE200ZX_85_ISR,
  EE_PPCE200ZX_86_ISR,
  EE_PPCE200ZX_87_ISR,
  EE_PPCE200ZX_88_ISR,
  EE_PPCE200ZX_89_ISR,
  EE_PPCE200ZX_90_ISR,
  EE_PPCE200ZX_91_ISR,
  EE_PPCE200ZX_92_ISR,
  EE_PPCE200ZX_93_ISR,
  EE_PPCE200ZX_94_ISR,
  EE_PPCE200ZX_95_ISR,
  EE_PPCE200ZX_96_ISR,
  EE_PPCE200ZX_97_ISR,
  EE_PPCE200ZX_98_ISR,
  EE_PPCE200ZX_99_ISR,
  EE_PPCE200ZX_100_ISR,
  EE_PPCE200ZX_101_ISR,
  EE_PPCE200ZX_102_ISR,
  EE_PPCE200ZX_103_ISR,
  EE_PPCE200ZX_104_ISR,
  EE_PPCE200ZX_105_ISR,
  EE_PPCE200ZX_106_ISR,
  EE_PPCE200ZX_107_ISR,
  EE_PPCE200ZX_108_ISR,
  EE_PPCE200ZX_109_ISR,
  EE_PPCE200ZX_110_ISR,
  EE_PPCE200ZX_111_ISR,
  EE_PPCE200ZX_112_ISR,
  EE_PPCE200ZX_113_ISR,
  EE_PPCE200ZX_114_ISR,
  EE_PPCE200ZX_115_ISR,
  EE_PPCE200ZX_116_ISR,
  EE_PPCE200ZX_117_ISR,
  EE_PPCE200ZX_118_ISR,
  EE_PPCE200ZX_119_ISR,
  EE_PPCE200ZX_120_ISR,
  EE_PPCE200ZX_121_ISR,
  EE_PPCE200ZX_122_ISR,
  EE_PPCE200ZX_123_ISR,
  EE_PPCE200ZX_124_ISR,
  EE_PPCE200ZX_125_ISR,
  EE_PPCE200ZX_126_ISR,
  EE_PPCE200ZX_127_ISR,
  EE_PPCE200ZX_128_ISR,
  EE_PPCE200ZX_129_ISR,
  EE_PPCE200ZX_130_ISR,
  EE_PPCE200ZX_131_ISR,
  EE_PPCE200ZX_132_ISR,
  EE_PPCE200ZX_133_ISR,
  EE_PPCE200ZX_134_ISR,
  EE_PPCE200ZX_135_ISR,
  EE_PPCE200ZX_136_ISR,
  EE_PPCE200ZX_137_ISR,
  EE_PPCE200ZX_138_ISR,
  EE_PPCE200ZX_139_ISR,
  EE_PPCE200ZX_140_ISR,
  EE_PPCE200ZX_141_ISR,
  EE_PPCE200ZX_142_ISR,
  EE_PPCE200ZX_143_ISR,
  EE_PPCE200ZX_144_ISR,
  EE_PPCE200ZX_145_ISR,
  EE_PPCE200ZX_146_ISR,
  EE_PPCE200ZX_147_ISR,
  EE_PPCE200ZX_148_ISR,
  EE_PPCE200ZX_149_ISR,
  EE_PPCE200ZX_150_ISR,
  EE_PPCE200ZX_151_ISR,
  EE_PPCE200ZX_152_ISR,
  EE_PPCE200ZX_153_ISR,
  EE_PPCE200ZX_154_ISR,
  EE_PPCE200ZX_155_ISR,
  EE_PPCE200ZX_156_ISR,
  EE_PPCE200ZX_157_ISR,
  EE_PPCE200ZX_158_ISR,
  EE_PPCE200ZX_159_ISR,
  EE_PPCE200ZX_160_ISR,
  EE_PPCE200ZX_161_ISR,
  EE_PPCE200ZX_162_ISR,
  EE_PPCE200ZX_163_ISR,
  EE_PPCE200ZX_164_ISR,
  EE_PPCE200ZX_165_ISR,
  EE_PPCE200ZX_166_ISR,
  EE_PPCE200ZX_167_ISR,
  EE_PPCE200ZX_168_ISR,
  EE_PPCE200ZX_169_ISR,
  EE_PPCE200ZX_170_ISR,
  EE_PPCE200ZX_171_ISR,
  EE_PPCE200ZX_172_ISR,
  EE_PPCE200ZX_173_ISR,
  EE_PPCE200ZX_174_ISR,
  EE_PPCE200ZX_175_ISR,
  EE_PPCE200ZX_176_ISR,
  EE_PPCE200ZX_177_ISR,
  EE_PPCE200ZX_178_ISR,
  EE_PPCE200ZX_179_ISR,
  EE_PPCE200ZX_180_ISR,
  EE_PPCE200ZX_181_ISR,
  EE_PPCE200ZX_182_ISR,
  EE_PPCE200ZX_183_ISR,
  EE_PPCE200ZX_184_ISR,
  EE_PPCE200ZX_185_ISR,
  EE_PPCE200ZX_186_ISR,
  EE_PPCE200ZX_187_ISR,
  EE_PPCE200ZX_188_ISR,
  EE_PPCE200ZX_189_ISR,
  EE_PPCE200ZX_190_ISR,
  EE_PPCE200ZX_191_ISR,
  EE_PPCE200ZX_192_ISR,
  EE_PPCE200ZX_193_ISR,
  EE_PPCE200ZX_194_ISR,
  EE_PPCE200ZX_195_ISR,
  EE_PPCE200ZX_196_ISR,
  EE_PPCE200ZX_197_ISR,
  EE_PPCE200ZX_198_ISR,
  EE_PPCE200ZX_199_ISR,
  EE_PPCE200ZX_200_ISR,
  EE_PPCE200ZX_201_ISR,
  EE_PPCE200ZX_202_ISR,
  EE_PPCE200ZX_203_ISR,
  EE_PPCE200ZX_204_ISR,
  EE_PPCE200ZX_205_ISR,
  EE_PPCE200ZX_206_ISR,
  EE_PPCE200ZX_207_ISR,
  EE_PPCE200ZX_208_ISR,
  EE_PPCE200ZX_209_ISR,
  EE_PPCE200ZX_210_ISR,
  EE_PPCE200ZX_211_ISR,
  EE_PPCE200ZX_212_ISR,
  EE_PPCE200ZX_213_ISR,
  EE_PPCE200ZX_214_ISR,
  EE_PPCE200ZX_215_ISR,
  EE_PPCE200ZX_216_ISR,
  EE_PPCE200ZX_217_ISR,
  EE_PPCE200ZX_218_ISR,
  EE_PPCE200ZX_219_ISR,
  EE_PPCE200ZX_220_ISR,
  EE_PPCE200ZX_221_ISR,
  EE_PPCE200ZX_222_ISR,
  EE_PPCE200ZX_223_ISR,
  EE_PPCE200ZX_224_ISR,
  EE_PPCE200ZX_225_ISR,
  EE_PPCE200ZX_226_ISR,
  EE_PPCE200ZX_227_ISR,
  EE_PPCE200ZX_228_ISR,
  EE_PPCE200ZX_229_ISR,
  EE_PPCE200ZX_230_ISR,
  EE_PPCE200ZX_231_ISR,
  EE_PPCE200ZX_232_ISR,
  EE_PPCE200ZX_233_ISR,
  EE_PPCE200ZX_234_ISR,
  EE_PPCE200ZX_235_ISR,
  EE_PPCE200ZX_236_ISR,
  EE_PPCE200ZX_237_ISR,
  EE_PPCE200ZX_238_ISR,
  EE_PPCE200ZX_239_ISR,
  EE_PPCE200ZX_240_ISR,
  EE_PPCE200ZX_241_ISR,
  EE_PPCE200ZX_242_ISR,
  EE_PPCE200ZX_243_ISR,
  EE_PPCE200ZX_244_ISR,
  EE_PPCE200ZX_245_ISR,
  EE_PPCE200ZX_246_ISR,
  EE_PPCE200ZX_247_ISR,
  EE_PPCE200ZX_248_ISR,
  EE_PPCE200ZX_249_ISR,
  EE_PPCE200ZX_250_ISR,
  EE_PPCE200ZX_251_ISR,
  EE_PPCE200ZX_252_ISR,
  EE_PPCE200ZX_253_ISR,
  EE_PPCE200ZX_254_ISR,
  EE_PPCE200ZX_255_ISR,
  EE_PPCE200ZX_256_ISR,
  EE_PPCE200ZX_257_ISR,
  EE_PPCE200ZX_258_ISR,
  EE_PPCE200ZX_259_ISR,
  EE_PPCE200ZX_260_ISR,
  EE_PPCE200ZX_261_ISR,
  EE_PPCE200ZX_262_ISR,
  EE_PPCE200ZX_263_ISR,
  EE_PPCE200ZX_264_ISR,
  EE_PPCE200ZX_265_ISR,
  EE_PPCE200ZX_266_ISR,
  EE_PPCE200ZX_267_ISR,
  EE_PPCE200ZX_268_ISR,
  EE_PPCE200ZX_269_ISR,
  EE_PPCE200ZX_270_ISR,
  EE_PPCE200ZX_271_ISR,
  EE_PPCE200ZX_272_ISR,
  EE_PPCE200ZX_273_ISR,
  EE_PPCE200ZX_274_ISR,
  EE_PPCE200ZX_275_ISR,
  EE_PPCE200ZX_276_ISR,
  EE_PPCE200ZX_277_ISR,
  EE_PPCE200ZX_278_ISR,
  EE_PPCE200ZX_279_ISR,
  EE_PPCE200ZX_280_ISR,
  EE_PPCE200ZX_281_ISR,
  EE_PPCE200ZX_282_ISR,
  EE_PPCE200ZX_283_ISR,
  EE_PPCE200ZX_284_ISR,
  EE_PPCE200ZX_285_ISR,
  EE_PPCE200ZX_286_ISR,
  EE_PPCE200ZX_287_ISR,
  EE_PPCE200ZX_288_ISR,
  EE_PPCE200ZX_289_ISR,
  EE_PPCE200ZX_290_ISR,
  EE_PPCE200ZX_291_ISR,
  EE_PPCE200ZX_292_ISR,
  EE_PPCE200ZX_293_ISR,
  EE_PPCE200ZX_294_ISR,
  EE_PPCE200ZX_295_ISR,
  EE_PPCE200ZX_296_ISR,
  EE_PPCE200ZX_297_ISR,
  EE_PPCE200ZX_298_ISR,
  EE_PPCE200ZX_299_ISR,
  EE_PPCE200ZX_300_ISR,
  EE_PPCE200ZX_301_ISR,
  EE_PPCE200ZX_302_ISR,
  EE_PPCE200ZX_303_ISR,
  EE_PPCE200ZX_304_ISR,
  EE_PPCE200ZX_305_ISR,
  EE_PPCE200ZX_306_ISR,
  EE_PPCE200ZX_307_ISR,
  EE_PPCE200ZX_308_ISR,
  EE_PPCE200ZX_309_ISR,
  EE_PPCE200ZX_310_ISR,
  EE_PPCE200ZX_311_ISR,
  EE_PPCE200ZX_312_ISR,
  EE_PPCE200ZX_313_ISR,
  EE_PPCE200ZX_314_ISR,
  EE_PPCE200ZX_315_ISR,
  EE_PPCE200ZX_316_ISR,
  EE_PPCE200ZX_317_ISR,
  EE_PPCE200ZX_318_ISR,
  EE_PPCE200ZX_319_ISR,
  EE_PPCE200ZX_320_ISR,
  EE_PPCE200ZX_321_ISR,
  EE_PPCE200ZX_322_ISR,
  EE_PPCE200ZX_323_ISR,
  EE_PPCE200ZX_324_ISR,
  EE_PPCE200ZX_325_ISR,
  EE_PPCE200ZX_326_ISR,
  EE_PPCE200ZX_327_ISR,
  EE_PPCE200ZX_328_ISR,
  EE_PPCE200ZX_329_ISR,
  EE_PPCE200ZX_330_ISR,
  EE_PPCE200ZX_331_ISR,
  EE_PPCE200ZX_332_ISR,
  EE_PPCE200ZX_333_ISR,
  EE_PPCE200ZX_334_ISR,
  EE_PPCE200ZX_335_ISR,
  EE_PPCE200ZX_336_ISR,
  EE_PPCE200ZX_337_ISR,
  EE_PPCE200ZX_338_ISR,
  EE_PPCE200ZX_339_ISR,
  EE_PPCE200ZX_340_ISR,
  EE_PPCE200ZX_341_ISR,
  EE_PPCE200ZX_342_ISR,
  EE_PPCE200ZX_343_ISR,
  EE_PPCE200ZX_344_ISR,
  EE_PPCE200ZX_345_ISR,
  EE_PPCE200ZX_346_ISR,
  EE_PPCE200ZX_347_ISR,
  EE_PPCE200ZX_348_ISR,
  EE_PPCE200ZX_349_ISR,
  EE_PPCE200ZX_350_ISR,
  EE_PPCE200ZX_351_ISR,
  EE_PPCE200ZX_352_ISR,
  EE_PPCE200ZX_353_ISR,
  EE_PPCE200ZX_354_ISR,
  EE_PPCE200ZX_355_ISR,
  EE_PPCE200ZX_356_ISR,
  EE_PPCE200ZX_357_ISR,
  EE_PPCE200ZX_358_ISR,
  EE_PPCE200ZX_359_ISR,
  EE_PPCE200ZX_360_ISR,
  EE_PPCE200ZX_361_ISR,
  EE_PPCE200ZX_362_ISR,
  EE_PPCE200ZX_363_ISR,
  EE_PPCE200ZX_364_ISR,
  EE_PPCE200ZX_365_ISR,
  EE_PPCE200ZX_366_ISR,
  EE_PPCE200ZX_367_ISR,
  EE_PPCE200ZX_368_ISR,
  EE_PPCE200ZX_369_ISR,
  EE_PPCE200ZX_370_ISR,
  EE_PPCE200ZX_371_ISR,
  EE_PPCE200ZX_372_ISR,
  EE_PPCE200ZX_373_ISR,
  EE_PPCE200ZX_374_ISR,
  EE_PPCE200ZX_375_ISR,
  EE_PPCE200ZX_376_ISR,
  EE_PPCE200ZX_377_ISR,
  EE_PPCE200ZX_378_ISR,
  EE_PPCE200ZX_379_ISR,
  EE_PPCE200ZX_380_ISR,
  EE_PPCE200ZX_381_ISR,
  EE_PPCE200ZX_382_ISR,
  EE_PPCE200ZX_383_ISR,
  EE_PPCE200ZX_384_ISR,
  EE_PPCE200ZX_385_ISR,
  EE_PPCE200ZX_386_ISR,
  EE_PPCE200ZX_387_ISR,
  EE_PPCE200ZX_388_ISR,
  EE_PPCE200ZX_389_ISR,
  EE_PPCE200ZX_390_ISR,
  EE_PPCE200ZX_391_ISR,
  EE_PPCE200ZX_392_ISR,
  EE_PPCE200ZX_393_ISR,
  EE_PPCE200ZX_394_ISR,
  EE_PPCE200ZX_395_ISR,
  EE_PPCE200ZX_396_ISR,
  EE_PPCE200ZX_397_ISR,
  EE_PPCE200ZX_398_ISR,
  EE_PPCE200ZX_399_ISR,
  EE_PPCE200ZX_400_ISR,
  EE_PPCE200ZX_401_ISR,
  EE_PPCE200ZX_402_ISR,
  EE_PPCE200ZX_403_ISR,
  EE_PPCE200ZX_404_ISR,
  EE_PPCE200ZX_405_ISR,
  EE_PPCE200ZX_406_ISR,
  EE_PPCE200ZX_407_ISR,
  EE_PPCE200ZX_408_ISR,
  EE_PPCE200ZX_409_ISR,
  EE_PPCE200ZX_410_ISR,
  EE_PPCE200ZX_411_ISR,
  EE_PPCE200ZX_412_ISR,
  EE_PPCE200ZX_413_ISR,
  EE_PPCE200ZX_414_ISR,
  EE_PPCE200ZX_415_ISR,
  EE_PPCE200ZX_416_ISR,
  EE_PPCE200ZX_417_ISR,
  EE_PPCE200ZX_418_ISR,
  EE_PPCE200ZX_419_ISR,
  EE_PPCE200ZX_420_ISR,
  EE_PPCE200ZX_421_ISR,
  EE_PPCE200ZX_422_ISR,
  EE_PPCE200ZX_423_ISR,
  EE_PPCE200ZX_424_ISR,
  EE_PPCE200ZX_425_ISR,
  EE_PPCE200ZX_426_ISR,
  EE_PPCE200ZX_427_ISR,
  EE_PPCE200ZX_428_ISR,
  EE_PPCE200ZX_429_ISR,
  EE_PPCE200ZX_430_ISR,
  EE_PPCE200ZX_431_ISR,
  EE_PPCE200ZX_432_ISR,
  EE_PPCE200ZX_433_ISR,
  EE_PPCE200ZX_434_ISR,
  EE_PPCE200ZX_435_ISR,
  EE_PPCE200ZX_436_ISR,
  EE_PPCE200ZX_437_ISR,
  EE_PPCE200ZX_438_ISR,
  EE_PPCE200ZX_439_ISR,
  EE_PPCE200ZX_440_ISR,
  EE_PPCE200ZX_441_ISR,
  EE_PPCE200ZX_442_ISR,
  EE_PPCE200ZX_443_ISR,
  EE_PPCE200ZX_444_ISR,
  EE_PPCE200ZX_445_ISR,
  EE_PPCE200ZX_446_ISR,
  EE_PPCE200ZX_447_ISR,
  EE_PPCE200ZX_448_ISR,
  EE_PPCE200ZX_449_ISR,
  EE_PPCE200ZX_450_ISR,
  EE_PPCE200ZX_451_ISR,
  EE_PPCE200ZX_452_ISR,
  EE_PPCE200ZX_453_ISR,
  EE_PPCE200ZX_454_ISR,
  EE_PPCE200ZX_455_ISR,
  EE_PPCE200ZX_456_ISR,
  EE_PPCE200ZX_457_ISR,
  EE_PPCE200ZX_458_ISR,
  EE_PPCE200ZX_459_ISR,
  EE_PPCE200ZX_460_ISR,
  EE_PPCE200ZX_461_ISR,
  EE_PPCE200ZX_462_ISR,
  EE_PPCE200ZX_463_ISR,
  EE_PPCE200ZX_464_ISR,
  EE_PPCE200ZX_465_ISR,
  EE_PPCE200ZX_466_ISR,
  EE_PPCE200ZX_467_ISR,
  EE_PPCE200ZX_468_ISR,
  EE_PPCE200ZX_469_ISR,
  EE_PPCE200ZX_470_ISR,
  EE_PPCE200ZX_471_ISR,
  EE_PPCE200ZX_472_ISR,
  EE_PPCE200ZX_473_ISR
};

/* For MM-PWT 2: MISRA 8.1 */
__INLINE__ void __ALWAYS_INLINE__
    EE_mpc5674_set_external_priority(EE_UREG psr, EE_BIT prio);
__INLINE__ void __ALWAYS_INLINE__
    EE_mpc5674_set_external_priority(EE_UREG psr, EE_BIT prio)
{
		INTC.PSR[psr].R	= prio;
}

void EE_mpc5674_initialize_external_IRQ_priorities(void) {
#ifdef EE_PPCE200ZX_0_ISR_PRI
  EE_mpc5674_set_external_priority(0U, EE_PPCE200ZX_0_ISR_PRI);
#endif /* EE_PPCE200ZX_0_ISR_PRI */

#ifdef EE_PPCE200ZX_1_ISR_PRI
  EE_mpc5674_set_external_priority(1U, EE_PPCE200ZX_1_ISR_PRI);
#endif /* EE_PPCE200ZX_1_ISR_PRI */

#ifdef EE_PPCE200ZX_2_ISR_PRI
  EE_mpc5674_set_external_priority(2U, EE_PPCE200ZX_2_ISR_PRI);
#endif /* EE_PPCE200ZX_2_ISR_PRI */

#ifdef EE_PPCE200ZX_3_ISR_PRI
  EE_mpc5674_set_external_priority(3U, EE_PPCE200ZX_3_ISR_PRI);
#endif /* EE_PPCE200ZX_3_ISR_PRI */

#ifdef EE_PPCE200ZX_4_ISR_PRI
  EE_mpc5674_set_external_priority(4U, EE_PPCE200ZX_4_ISR_PRI);
#endif /* EE_PPCE200ZX_4_ISR_PRI */

#ifdef EE_PPCE200ZX_5_ISR_PRI
  EE_mpc5674_set_external_priority(5U, EE_PPCE200ZX_5_ISR_PRI);
#endif /* EE_PPCE200ZX_5_ISR_PRI */

#ifdef EE_PPCE200ZX_6_ISR_PRI
  EE_mpc5674_set_external_priority(6U, EE_PPCE200ZX_6_ISR_PRI);
#endif /* EE_PPCE200ZX_6_ISR_PRI */

#ifdef EE_PPCE200ZX_7_ISR_PRI
  EE_mpc5674_set_external_priority(7U, EE_PPCE200ZX_7_ISR_PRI);
#endif /* EE_PPCE200ZX_7_ISR_PRI */

#ifdef EE_PPCE200ZX_8_ISR_PRI
  EE_mpc5674_set_external_priority(8U, EE_PPCE200ZX_8_ISR_PRI);
#endif /* EE_PPCE200ZX_8_ISR_PRI */

#ifdef EE_PPCE200ZX_9_ISR_PRI
  EE_mpc5674_set_external_priority(9U, EE_PPCE200ZX_9_ISR_PRI);
#endif /* EE_PPCE200ZX_9_ISR_PRI */

#ifdef EE_PPCE200ZX_10_ISR_PRI
  EE_mpc5674_set_external_priority(10U, EE_PPCE200ZX_10_ISR_PRI);
#endif /* EE_PPCE200ZX_10_ISR_PRI */

#ifdef EE_PPCE200ZX_11_ISR_PRI
  EE_mpc5674_set_external_priority(11U, EE_PPCE200ZX_11_ISR_PRI);
#endif /* EE_PPCE200ZX_11_ISR_PRI */

#ifdef EE_PPCE200ZX_12_ISR_PRI
  EE_mpc5674_set_external_priority(12U, EE_PPCE200ZX_12_ISR_PRI);
#endif /* EE_PPCE200ZX_12_ISR_PRI */

#ifdef EE_PPCE200ZX_13_ISR_PRI
  EE_mpc5674_set_external_priority(13U, EE_PPCE200ZX_13_ISR_PRI);
#endif /* EE_PPCE200ZX_13_ISR_PRI */

#ifdef EE_PPCE200ZX_14_ISR_PRI
  EE_mpc5674_set_external_priority(14U, EE_PPCE200ZX_14_ISR_PRI);
#endif /* EE_PPCE200ZX_14_ISR_PRI */

#ifdef EE_PPCE200ZX_15_ISR_PRI
  EE_mpc5674_set_external_priority(15U, EE_PPCE200ZX_15_ISR_PRI);
#endif /* EE_PPCE200ZX_15_ISR_PRI */

#ifdef EE_PPCE200ZX_16_ISR_PRI
  EE_mpc5674_set_external_priority(16U, EE_PPCE200ZX_16_ISR_PRI);
#endif /* EE_PPCE200ZX_16_ISR_PRI */

#ifdef EE_PPCE200ZX_17_ISR_PRI
  EE_mpc5674_set_external_priority(17U, EE_PPCE200ZX_17_ISR_PRI);
#endif /* EE_PPCE200ZX_17_ISR_PRI */

#ifdef EE_PPCE200ZX_18_ISR_PRI
  EE_mpc5674_set_external_priority(18U, EE_PPCE200ZX_18_ISR_PRI);
#endif /* EE_PPCE200ZX_18_ISR_PRI */

#ifdef EE_PPCE200ZX_19_ISR_PRI
  EE_mpc5674_set_external_priority(19U, EE_PPCE200ZX_19_ISR_PRI);
#endif /* EE_PPCE200ZX_19_ISR_PRI */

#ifdef EE_PPCE200ZX_20_ISR_PRI
  EE_mpc5674_set_external_priority(20U, EE_PPCE200ZX_20_ISR_PRI);
#endif /* EE_PPCE200ZX_20_ISR_PRI */

#ifdef EE_PPCE200ZX_21_ISR_PRI
  EE_mpc5674_set_external_priority(21U, EE_PPCE200ZX_21_ISR_PRI);
#endif /* EE_PPCE200ZX_21_ISR_PRI */

#ifdef EE_PPCE200ZX_22_ISR_PRI
  EE_mpc5674_set_external_priority(22U, EE_PPCE200ZX_22_ISR_PRI);
#endif /* EE_PPCE200ZX_22_ISR_PRI */

#ifdef EE_PPCE200ZX_23_ISR_PRI
  EE_mpc5674_set_external_priority(23U, EE_PPCE200ZX_23_ISR_PRI);
#endif /* EE_PPCE200ZX_23_ISR_PRI */

#ifdef EE_PPCE200ZX_24_ISR_PRI
  EE_mpc5674_set_external_priority(24U, EE_PPCE200ZX_24_ISR_PRI);
#endif /* EE_PPCE200ZX_24_ISR_PRI */

#ifdef EE_PPCE200ZX_25_ISR_PRI
  EE_mpc5674_set_external_priority(25U, EE_PPCE200ZX_25_ISR_PRI);
#endif /* EE_PPCE200ZX_25_ISR_PRI */

#ifdef EE_PPCE200ZX_26_ISR_PRI
  EE_mpc5674_set_external_priority(26U, EE_PPCE200ZX_26_ISR_PRI);
#endif /* EE_PPCE200ZX_26_ISR_PRI */

#ifdef EE_PPCE200ZX_27_ISR_PRI
  EE_mpc5674_set_external_priority(27U, EE_PPCE200ZX_27_ISR_PRI);
#endif /* EE_PPCE200ZX_27_ISR_PRI */

#ifdef EE_PPCE200ZX_28_ISR_PRI
  EE_mpc5674_set_external_priority(28U, EE_PPCE200ZX_28_ISR_PRI);
#endif /* EE_PPCE200ZX_28_ISR_PRI */

#ifdef EE_PPCE200ZX_29_ISR_PRI
  EE_mpc5674_set_external_priority(29U, EE_PPCE200ZX_29_ISR_PRI);
#endif /* EE_PPCE200ZX_29_ISR_PRI */

#ifdef EE_PPCE200ZX_30_ISR_PRI
  EE_mpc5674_set_external_priority(30U, EE_PPCE200ZX_30_ISR_PRI);
#endif /* EE_PPCE200ZX_30_ISR_PRI */

#ifdef EE_PPCE200ZX_31_ISR_PRI
  EE_mpc5674_set_external_priority(31U, EE_PPCE200ZX_31_ISR_PRI);
#endif /* EE_PPCE200ZX_31_ISR_PRI */

#ifdef EE_PPCE200ZX_32_ISR_PRI
  EE_mpc5674_set_external_priority(32U, EE_PPCE200ZX_32_ISR_PRI);
#endif /* EE_PPCE200ZX_32_ISR_PRI */

#ifdef EE_PPCE200ZX_33_ISR_PRI
  EE_mpc5674_set_external_priority(33U, EE_PPCE200ZX_33_ISR_PRI);
#endif /* EE_PPCE200ZX_33_ISR_PRI */

#ifdef EE_PPCE200ZX_34_ISR_PRI
  EE_mpc5674_set_external_priority(34U, EE_PPCE200ZX_34_ISR_PRI);
#endif /* EE_PPCE200ZX_34_ISR_PRI */

#ifdef EE_PPCE200ZX_35_ISR_PRI
  EE_mpc5674_set_external_priority(35U, EE_PPCE200ZX_35_ISR_PRI);
#endif /* EE_PPCE200ZX_35_ISR_PRI */

#ifdef EE_PPCE200ZX_36_ISR_PRI
  EE_mpc5674_set_external_priority(36U, EE_PPCE200ZX_36_ISR_PRI);
#endif /* EE_PPCE200ZX_36_ISR_PRI */

#ifdef EE_PPCE200ZX_37_ISR_PRI
  EE_mpc5674_set_external_priority(37U, EE_PPCE200ZX_37_ISR_PRI);
#endif /* EE_PPCE200ZX_37_ISR_PRI */

#ifdef EE_PPCE200ZX_38_ISR_PRI
  EE_mpc5674_set_external_priority(38U, EE_PPCE200ZX_38_ISR_PRI);
#endif /* EE_PPCE200ZX_38_ISR_PRI */

#ifdef EE_PPCE200ZX_39_ISR_PRI
  EE_mpc5674_set_external_priority(39U, EE_PPCE200ZX_39_ISR_PRI);
#endif /* EE_PPCE200ZX_39_ISR_PRI */

#ifdef EE_PPCE200ZX_40_ISR_PRI
  EE_mpc5674_set_external_priority(40U, EE_PPCE200ZX_40_ISR_PRI);
#endif /* EE_PPCE200ZX_40_ISR_PRI */

#ifdef EE_PPCE200ZX_41_ISR_PRI
  EE_mpc5674_set_external_priority(41U, EE_PPCE200ZX_41_ISR_PRI);
#endif /* EE_PPCE200ZX_41_ISR_PRI */

#ifdef EE_PPCE200ZX_42_ISR_PRI
  EE_mpc5674_set_external_priority(42U, EE_PPCE200ZX_42_ISR_PRI);
#endif /* EE_PPCE200ZX_42_ISR_PRI */

#ifdef EE_PPCE200ZX_43_ISR_PRI
  EE_mpc5674_set_external_priority(43U, EE_PPCE200ZX_43_ISR_PRI);
#endif /* EE_PPCE200ZX_43_ISR_PRI */

#ifdef EE_PPCE200ZX_44_ISR_PRI
  EE_mpc5674_set_external_priority(44U, EE_PPCE200ZX_44_ISR_PRI);
#endif /* EE_PPCE200ZX_44_ISR_PRI */

#ifdef EE_PPCE200ZX_45_ISR_PRI
  EE_mpc5674_set_external_priority(45U, EE_PPCE200ZX_45_ISR_PRI);
#endif /* EE_PPCE200ZX_45_ISR_PRI */

#ifdef EE_PPCE200ZX_46_ISR_PRI
  EE_mpc5674_set_external_priority(46U, EE_PPCE200ZX_46_ISR_PRI);
#endif /* EE_PPCE200ZX_46_ISR_PRI */

#ifdef EE_PPCE200ZX_47_ISR_PRI
  EE_mpc5674_set_external_priority(47U, EE_PPCE200ZX_47_ISR_PRI);
#endif /* EE_PPCE200ZX_47_ISR_PRI */

#ifdef EE_PPCE200ZX_48_ISR_PRI
  EE_mpc5674_set_external_priority(48U, EE_PPCE200ZX_48_ISR_PRI);
#endif /* EE_PPCE200ZX_48_ISR_PRI */

#ifdef EE_PPCE200ZX_49_ISR_PRI
  EE_mpc5674_set_external_priority(49U, EE_PPCE200ZX_49_ISR_PRI);
#endif /* EE_PPCE200ZX_49_ISR_PRI */

#ifdef EE_PPCE200ZX_50_ISR_PRI
  EE_mpc5674_set_external_priority(50U, EE_PPCE200ZX_50_ISR_PRI);
#endif /* EE_PPCE200ZX_50_ISR_PRI */

#ifdef EE_PPCE200ZX_51_ISR_PRI
  EE_mpc5674_set_external_priority(51U, EE_PPCE200ZX_51_ISR_PRI);
#endif /* EE_PPCE200ZX_51_ISR_PRI */

#ifdef EE_PPCE200ZX_52_ISR_PRI
  EE_mpc5674_set_external_priority(52U, EE_PPCE200ZX_52_ISR_PRI);
#endif /* EE_PPCE200ZX_52_ISR_PRI */

#ifdef EE_PPCE200ZX_53_ISR_PRI
  EE_mpc5674_set_external_priority(53U, EE_PPCE200ZX_53_ISR_PRI);
#endif /* EE_PPCE200ZX_53_ISR_PRI */

#ifdef EE_PPCE200ZX_54_ISR_PRI
  EE_mpc5674_set_external_priority(54U, EE_PPCE200ZX_54_ISR_PRI);
#endif /* EE_PPCE200ZX_54_ISR_PRI */

#ifdef EE_PPCE200ZX_55_ISR_PRI
  EE_mpc5674_set_external_priority(55U, EE_PPCE200ZX_55_ISR_PRI);
#endif /* EE_PPCE200ZX_55_ISR_PRI */

#ifdef EE_PPCE200ZX_56_ISR_PRI
  EE_mpc5674_set_external_priority(56U, EE_PPCE200ZX_56_ISR_PRI);
#endif /* EE_PPCE200ZX_56_ISR_PRI */

#ifdef EE_PPCE200ZX_57_ISR_PRI
  EE_mpc5674_set_external_priority(57U, EE_PPCE200ZX_57_ISR_PRI);
#endif /* EE_PPCE200ZX_57_ISR_PRI */

#ifdef EE_PPCE200ZX_58_ISR_PRI
  EE_mpc5674_set_external_priority(58U, EE_PPCE200ZX_58_ISR_PRI);
#endif /* EE_PPCE200ZX_58_ISR_PRI */

#ifdef EE_PPCE200ZX_59_ISR_PRI
  EE_mpc5674_set_external_priority(59U, EE_PPCE200ZX_59_ISR_PRI);
#endif /* EE_PPCE200ZX_59_ISR_PRI */

#ifdef EE_PPCE200ZX_60_ISR_PRI
  EE_mpc5674_set_external_priority(60U, EE_PPCE200ZX_60_ISR_PRI);
#endif /* EE_PPCE200ZX_60_ISR_PRI */

#ifdef EE_PPCE200ZX_61_ISR_PRI
  EE_mpc5674_set_external_priority(61U, EE_PPCE200ZX_61_ISR_PRI);
#endif /* EE_PPCE200ZX_61_ISR_PRI */

#ifdef EE_PPCE200ZX_62_ISR_PRI
  EE_mpc5674_set_external_priority(62U, EE_PPCE200ZX_62_ISR_PRI);
#endif /* EE_PPCE200ZX_62_ISR_PRI */

#ifdef EE_PPCE200ZX_63_ISR_PRI
  EE_mpc5674_set_external_priority(63U, EE_PPCE200ZX_63_ISR_PRI);
#endif /* EE_PPCE200ZX_63_ISR_PRI */

#ifdef EE_PPCE200ZX_64_ISR_PRI
  EE_mpc5674_set_external_priority(64U, EE_PPCE200ZX_64_ISR_PRI);
#endif /* EE_PPCE200ZX_64_ISR_PRI */

#ifdef EE_PPCE200ZX_65_ISR_PRI
  EE_mpc5674_set_external_priority(65U, EE_PPCE200ZX_65_ISR_PRI);
#endif /* EE_PPCE200ZX_65_ISR_PRI */

#ifdef EE_PPCE200ZX_66_ISR_PRI
  EE_mpc5674_set_external_priority(66U, EE_PPCE200ZX_66_ISR_PRI);
#endif /* EE_PPCE200ZX_66_ISR_PRI */

#ifdef EE_PPCE200ZX_67_ISR_PRI
  EE_mpc5674_set_external_priority(67U, EE_PPCE200ZX_67_ISR_PRI);
#endif /* EE_PPCE200ZX_67_ISR_PRI */

#ifdef EE_PPCE200ZX_68_ISR_PRI
  EE_mpc5674_set_external_priority(68U, EE_PPCE200ZX_68_ISR_PRI);
#endif /* EE_PPCE200ZX_68_ISR_PRI */

#ifdef EE_PPCE200ZX_69_ISR_PRI
  EE_mpc5674_set_external_priority(69U, EE_PPCE200ZX_69_ISR_PRI);
#endif /* EE_PPCE200ZX_69_ISR_PRI */

#ifdef EE_PPCE200ZX_70_ISR_PRI
  EE_mpc5674_set_external_priority(70U, EE_PPCE200ZX_70_ISR_PRI);
#endif /* EE_PPCE200ZX_70_ISR_PRI */

#ifdef EE_PPCE200ZX_71_ISR_PRI
  EE_mpc5674_set_external_priority(71U, EE_PPCE200ZX_71_ISR_PRI);
#endif /* EE_PPCE200ZX_71_ISR_PRI */

#ifdef EE_PPCE200ZX_72_ISR_PRI
  EE_mpc5674_set_external_priority(72U, EE_PPCE200ZX_72_ISR_PRI);
#endif /* EE_PPCE200ZX_72_ISR_PRI */

#ifdef EE_PPCE200ZX_73_ISR_PRI
  EE_mpc5674_set_external_priority(73U, EE_PPCE200ZX_73_ISR_PRI);
#endif /* EE_PPCE200ZX_73_ISR_PRI */

#ifdef EE_PPCE200ZX_74_ISR_PRI
  EE_mpc5674_set_external_priority(74U, EE_PPCE200ZX_74_ISR_PRI);
#endif /* EE_PPCE200ZX_74_ISR_PRI */

#ifdef EE_PPCE200ZX_75_ISR_PRI
  EE_mpc5674_set_external_priority(75U, EE_PPCE200ZX_75_ISR_PRI);
#endif /* EE_PPCE200ZX_75_ISR_PRI */

#ifdef EE_PPCE200ZX_76_ISR_PRI
  EE_mpc5674_set_external_priority(76U, EE_PPCE200ZX_76_ISR_PRI);
#endif /* EE_PPCE200ZX_76_ISR_PRI */

#ifdef EE_PPCE200ZX_77_ISR_PRI
  EE_mpc5674_set_external_priority(77U, EE_PPCE200ZX_77_ISR_PRI);
#endif /* EE_PPCE200ZX_77_ISR_PRI */

#ifdef EE_PPCE200ZX_78_ISR_PRI
  EE_mpc5674_set_external_priority(78U, EE_PPCE200ZX_78_ISR_PRI);
#endif /* EE_PPCE200ZX_78_ISR_PRI */

#ifdef EE_PPCE200ZX_79_ISR_PRI
  EE_mpc5674_set_external_priority(79U, EE_PPCE200ZX_79_ISR_PRI);
#endif /* EE_PPCE200ZX_79_ISR_PRI */

#ifdef EE_PPCE200ZX_80_ISR_PRI
  EE_mpc5674_set_external_priority(80U, EE_PPCE200ZX_80_ISR_PRI);
#endif /* EE_PPCE200ZX_80_ISR_PRI */

#ifdef EE_PPCE200ZX_81_ISR_PRI
  EE_mpc5674_set_external_priority(81U, EE_PPCE200ZX_81_ISR_PRI);
#endif /* EE_PPCE200ZX_81_ISR_PRI */

#ifdef EE_PPCE200ZX_82_ISR_PRI
  EE_mpc5674_set_external_priority(82U, EE_PPCE200ZX_82_ISR_PRI);
#endif /* EE_PPCE200ZX_82_ISR_PRI */

#ifdef EE_PPCE200ZX_83_ISR_PRI
  EE_mpc5674_set_external_priority(83U, EE_PPCE200ZX_83_ISR_PRI);
#endif /* EE_PPCE200ZX_83_ISR_PRI */

#ifdef EE_PPCE200ZX_84_ISR_PRI
  EE_mpc5674_set_external_priority(84U, EE_PPCE200ZX_84_ISR_PRI);
#endif /* EE_PPCE200ZX_84_ISR_PRI */

#ifdef EE_PPCE200ZX_85_ISR_PRI
  EE_mpc5674_set_external_priority(85U, EE_PPCE200ZX_85_ISR_PRI);
#endif /* EE_PPCE200ZX_85_ISR_PRI */

#ifdef EE_PPCE200ZX_86_ISR_PRI
  EE_mpc5674_set_external_priority(86U, EE_PPCE200ZX_86_ISR_PRI);
#endif /* EE_PPCE200ZX_86_ISR_PRI */

#ifdef EE_PPCE200ZX_87_ISR_PRI
  EE_mpc5674_set_external_priority(87U, EE_PPCE200ZX_87_ISR_PRI);
#endif /* EE_PPCE200ZX_87_ISR_PRI */

#ifdef EE_PPCE200ZX_88_ISR_PRI
  EE_mpc5674_set_external_priority(88U, EE_PPCE200ZX_88_ISR_PRI);
#endif /* EE_PPCE200ZX_88_ISR_PRI */

#ifdef EE_PPCE200ZX_89_ISR_PRI
  EE_mpc5674_set_external_priority(89U, EE_PPCE200ZX_89_ISR_PRI);
#endif /* EE_PPCE200ZX_89_ISR_PRI */

#ifdef EE_PPCE200ZX_90_ISR_PRI
  EE_mpc5674_set_external_priority(90U, EE_PPCE200ZX_90_ISR_PRI);
#endif /* EE_PPCE200ZX_90_ISR_PRI */

#ifdef EE_PPCE200ZX_91_ISR_PRI
  EE_mpc5674_set_external_priority(91U, EE_PPCE200ZX_91_ISR_PRI);
#endif /* EE_PPCE200ZX_91_ISR_PRI */

#ifdef EE_PPCE200ZX_92_ISR_PRI
  EE_mpc5674_set_external_priority(92U, EE_PPCE200ZX_92_ISR_PRI);
#endif /* EE_PPCE200ZX_92_ISR_PRI */

#ifdef EE_PPCE200ZX_93_ISR_PRI
  EE_mpc5674_set_external_priority(93U, EE_PPCE200ZX_93_ISR_PRI);
#endif /* EE_PPCE200ZX_93_ISR_PRI */

#ifdef EE_PPCE200ZX_94_ISR_PRI
  EE_mpc5674_set_external_priority(94U, EE_PPCE200ZX_94_ISR_PRI);
#endif /* EE_PPCE200ZX_94_ISR_PRI */

#ifdef EE_PPCE200ZX_95_ISR_PRI
  EE_mpc5674_set_external_priority(95U, EE_PPCE200ZX_95_ISR_PRI);
#endif /* EE_PPCE200ZX_95_ISR_PRI */

#ifdef EE_PPCE200ZX_96_ISR_PRI
  EE_mpc5674_set_external_priority(96U, EE_PPCE200ZX_96_ISR_PRI);
#endif /* EE_PPCE200ZX_96_ISR_PRI */

#ifdef EE_PPCE200ZX_97_ISR_PRI
  EE_mpc5674_set_external_priority(97U, EE_PPCE200ZX_97_ISR_PRI);
#endif /* EE_PPCE200ZX_97_ISR_PRI */

#ifdef EE_PPCE200ZX_98_ISR_PRI
  EE_mpc5674_set_external_priority(98U, EE_PPCE200ZX_98_ISR_PRI);
#endif /* EE_PPCE200ZX_98_ISR_PRI */

#ifdef EE_PPCE200ZX_99_ISR_PRI
  EE_mpc5674_set_external_priority(99U, EE_PPCE200ZX_99_ISR_PRI);
#endif /* EE_PPCE200ZX_99_ISR_PRI */

#ifdef EE_PPCE200ZX_100_ISR_PRI
  EE_mpc5674_set_external_priority(100U, EE_PPCE200ZX_100_ISR_PRI);
#endif /* EE_PPCE200ZX_100_ISR_PRI */

#ifdef EE_PPCE200ZX_101_ISR_PRI
  EE_mpc5674_set_external_priority(101U, EE_PPCE200ZX_101_ISR_PRI);
#endif /* EE_PPCE200ZX_101_ISR_PRI */

#ifdef EE_PPCE200ZX_102_ISR_PRI
  EE_mpc5674_set_external_priority(102U, EE_PPCE200ZX_102_ISR_PRI);
#endif /* EE_PPCE200ZX_102_ISR_PRI */

#ifdef EE_PPCE200ZX_103_ISR_PRI
  EE_mpc5674_set_external_priority(103U, EE_PPCE200ZX_103_ISR_PRI);
#endif /* EE_PPCE200ZX_103_ISR_PRI */

#ifdef EE_PPCE200ZX_104_ISR_PRI
  EE_mpc5674_set_external_priority(104U, EE_PPCE200ZX_104_ISR_PRI);
#endif /* EE_PPCE200ZX_104_ISR_PRI */

#ifdef EE_PPCE200ZX_105_ISR_PRI
  EE_mpc5674_set_external_priority(105U, EE_PPCE200ZX_105_ISR_PRI);
#endif /* EE_PPCE200ZX_105_ISR_PRI */

#ifdef EE_PPCE200ZX_106_ISR_PRI
  EE_mpc5674_set_external_priority(106U, EE_PPCE200ZX_106_ISR_PRI);
#endif /* EE_PPCE200ZX_106_ISR_PRI */

#ifdef EE_PPCE200ZX_107_ISR_PRI
  EE_mpc5674_set_external_priority(107U, EE_PPCE200ZX_107_ISR_PRI);
#endif /* EE_PPCE200ZX_107_ISR_PRI */

#ifdef EE_PPCE200ZX_108_ISR_PRI
  EE_mpc5674_set_external_priority(108U, EE_PPCE200ZX_108_ISR_PRI);
#endif /* EE_PPCE200ZX_108_ISR_PRI */

#ifdef EE_PPCE200ZX_109_ISR_PRI
  EE_mpc5674_set_external_priority(109U, EE_PPCE200ZX_109_ISR_PRI);
#endif /* EE_PPCE200ZX_109_ISR_PRI */

#ifdef EE_PPCE200ZX_110_ISR_PRI
  EE_mpc5674_set_external_priority(110U, EE_PPCE200ZX_110_ISR_PRI);
#endif /* EE_PPCE200ZX_110_ISR_PRI */

#ifdef EE_PPCE200ZX_111_ISR_PRI
  EE_mpc5674_set_external_priority(111U, EE_PPCE200ZX_111_ISR_PRI);
#endif /* EE_PPCE200ZX_111_ISR_PRI */

#ifdef EE_PPCE200ZX_112_ISR_PRI
  EE_mpc5674_set_external_priority(112U, EE_PPCE200ZX_112_ISR_PRI);
#endif /* EE_PPCE200ZX_112_ISR_PRI */

#ifdef EE_PPCE200ZX_113_ISR_PRI
  EE_mpc5674_set_external_priority(113U, EE_PPCE200ZX_113_ISR_PRI);
#endif /* EE_PPCE200ZX_113_ISR_PRI */

#ifdef EE_PPCE200ZX_114_ISR_PRI
  EE_mpc5674_set_external_priority(114U, EE_PPCE200ZX_114_ISR_PRI);
#endif /* EE_PPCE200ZX_114_ISR_PRI */

#ifdef EE_PPCE200ZX_115_ISR_PRI
  EE_mpc5674_set_external_priority(115U, EE_PPCE200ZX_115_ISR_PRI);
#endif /* EE_PPCE200ZX_115_ISR_PRI */

#ifdef EE_PPCE200ZX_116_ISR_PRI
  EE_mpc5674_set_external_priority(116U, EE_PPCE200ZX_116_ISR_PRI);
#endif /* EE_PPCE200ZX_116_ISR_PRI */

#ifdef EE_PPCE200ZX_117_ISR_PRI
  EE_mpc5674_set_external_priority(117U, EE_PPCE200ZX_117_ISR_PRI);
#endif /* EE_PPCE200ZX_117_ISR_PRI */

#ifdef EE_PPCE200ZX_118_ISR_PRI
  EE_mpc5674_set_external_priority(118U, EE_PPCE200ZX_118_ISR_PRI);
#endif /* EE_PPCE200ZX_118_ISR_PRI */

#ifdef EE_PPCE200ZX_119_ISR_PRI
  EE_mpc5674_set_external_priority(119U, EE_PPCE200ZX_119_ISR_PRI);
#endif /* EE_PPCE200ZX_119_ISR_PRI */

#ifdef EE_PPCE200ZX_120_ISR_PRI
  EE_mpc5674_set_external_priority(120U, EE_PPCE200ZX_120_ISR_PRI);
#endif /* EE_PPCE200ZX_120_ISR_PRI */

#ifdef EE_PPCE200ZX_121_ISR_PRI
  EE_mpc5674_set_external_priority(121U, EE_PPCE200ZX_121_ISR_PRI);
#endif /* EE_PPCE200ZX_121_ISR_PRI */

#ifdef EE_PPCE200ZX_122_ISR_PRI
  EE_mpc5674_set_external_priority(122U, EE_PPCE200ZX_122_ISR_PRI);
#endif /* EE_PPCE200ZX_122_ISR_PRI */

#ifdef EE_PPCE200ZX_123_ISR_PRI
  EE_mpc5674_set_external_priority(123U, EE_PPCE200ZX_123_ISR_PRI);
#endif /* EE_PPCE200ZX_123_ISR_PRI */

#ifdef EE_PPCE200ZX_124_ISR_PRI
  EE_mpc5674_set_external_priority(124U, EE_PPCE200ZX_124_ISR_PRI);
#endif /* EE_PPCE200ZX_124_ISR_PRI */

#ifdef EE_PPCE200ZX_125_ISR_PRI
  EE_mpc5674_set_external_priority(125U, EE_PPCE200ZX_125_ISR_PRI);
#endif /* EE_PPCE200ZX_125_ISR_PRI */

#ifdef EE_PPCE200ZX_126_ISR_PRI
  EE_mpc5674_set_external_priority(126U, EE_PPCE200ZX_126_ISR_PRI);
#endif /* EE_PPCE200ZX_126_ISR_PRI */

#ifdef EE_PPCE200ZX_127_ISR_PRI
  EE_mpc5674_set_external_priority(127U, EE_PPCE200ZX_127_ISR_PRI);
#endif /* EE_PPCE200ZX_127_ISR_PRI */

#ifdef EE_PPCE200ZX_128_ISR_PRI
  EE_mpc5674_set_external_priority(128U, EE_PPCE200ZX_128_ISR_PRI);
#endif /* EE_PPCE200ZX_128_ISR_PRI */

#ifdef EE_PPCE200ZX_129_ISR_PRI
  EE_mpc5674_set_external_priority(129U, EE_PPCE200ZX_129_ISR_PRI);
#endif /* EE_PPCE200ZX_129_ISR_PRI */

#ifdef EE_PPCE200ZX_130_ISR_PRI
  EE_mpc5674_set_external_priority(130U, EE_PPCE200ZX_130_ISR_PRI);
#endif /* EE_PPCE200ZX_130_ISR_PRI */

#ifdef EE_PPCE200ZX_131_ISR_PRI
  EE_mpc5674_set_external_priority(131U, EE_PPCE200ZX_131_ISR_PRI);
#endif /* EE_PPCE200ZX_131_ISR_PRI */

#ifdef EE_PPCE200ZX_132_ISR_PRI
  EE_mpc5674_set_external_priority(132U, EE_PPCE200ZX_132_ISR_PRI);
#endif /* EE_PPCE200ZX_132_ISR_PRI */

#ifdef EE_PPCE200ZX_133_ISR_PRI
  EE_mpc5674_set_external_priority(133U, EE_PPCE200ZX_133_ISR_PRI);
#endif /* EE_PPCE200ZX_133_ISR_PRI */

#ifdef EE_PPCE200ZX_134_ISR_PRI
  EE_mpc5674_set_external_priority(134U, EE_PPCE200ZX_134_ISR_PRI);
#endif /* EE_PPCE200ZX_134_ISR_PRI */

#ifdef EE_PPCE200ZX_135_ISR_PRI
  EE_mpc5674_set_external_priority(135U, EE_PPCE200ZX_135_ISR_PRI);
#endif /* EE_PPCE200ZX_135_ISR_PRI */

#ifdef EE_PPCE200ZX_136_ISR_PRI
  EE_mpc5674_set_external_priority(136U, EE_PPCE200ZX_136_ISR_PRI);
#endif /* EE_PPCE200ZX_136_ISR_PRI */

#ifdef EE_PPCE200ZX_137_ISR_PRI
  EE_mpc5674_set_external_priority(137U, EE_PPCE200ZX_137_ISR_PRI);
#endif /* EE_PPCE200ZX_137_ISR_PRI */

#ifdef EE_PPCE200ZX_138_ISR_PRI
  EE_mpc5674_set_external_priority(138U, EE_PPCE200ZX_138_ISR_PRI);
#endif /* EE_PPCE200ZX_138_ISR_PRI */

#ifdef EE_PPCE200ZX_139_ISR_PRI
  EE_mpc5674_set_external_priority(139U, EE_PPCE200ZX_139_ISR_PRI);
#endif /* EE_PPCE200ZX_139_ISR_PRI */

#ifdef EE_PPCE200ZX_140_ISR_PRI
  EE_mpc5674_set_external_priority(140U, EE_PPCE200ZX_140_ISR_PRI);
#endif /* EE_PPCE200ZX_140_ISR_PRI */

#ifdef EE_PPCE200ZX_141_ISR_PRI
  EE_mpc5674_set_external_priority(141U, EE_PPCE200ZX_141_ISR_PRI);
#endif /* EE_PPCE200ZX_141_ISR_PRI */

#ifdef EE_PPCE200ZX_142_ISR_PRI
  EE_mpc5674_set_external_priority(142U, EE_PPCE200ZX_142_ISR_PRI);
#endif /* EE_PPCE200ZX_142_ISR_PRI */

#ifdef EE_PPCE200ZX_143_ISR_PRI
  EE_mpc5674_set_external_priority(143U, EE_PPCE200ZX_143_ISR_PRI);
#endif /* EE_PPCE200ZX_143_ISR_PRI */

#ifdef EE_PPCE200ZX_144_ISR_PRI
  EE_mpc5674_set_external_priority(144U, EE_PPCE200ZX_144_ISR_PRI);
#endif /* EE_PPCE200ZX_144_ISR_PRI */

#ifdef EE_PPCE200ZX_145_ISR_PRI
  EE_mpc5674_set_external_priority(145U, EE_PPCE200ZX_145_ISR_PRI);
#endif /* EE_PPCE200ZX_145_ISR_PRI */

#ifdef EE_PPCE200ZX_146_ISR_PRI
  EE_mpc5674_set_external_priority(146U, EE_PPCE200ZX_146_ISR_PRI);
#endif /* EE_PPCE200ZX_146_ISR_PRI */

#ifdef EE_PPCE200ZX_147_ISR_PRI
  EE_mpc5674_set_external_priority(147U, EE_PPCE200ZX_147_ISR_PRI);
#endif /* EE_PPCE200ZX_147_ISR_PRI */

#ifdef EE_PPCE200ZX_148_ISR_PRI
  EE_mpc5674_set_external_priority(148U, EE_PPCE200ZX_148_ISR_PRI);
#endif /* EE_PPCE200ZX_148_ISR_PRI */

#ifdef EE_PPCE200ZX_149_ISR_PRI
  EE_mpc5674_set_external_priority(149U, EE_PPCE200ZX_149_ISR_PRI);
#endif /* EE_PPCE200ZX_149_ISR_PRI */

#ifdef EE_PPCE200ZX_150_ISR_PRI
  EE_mpc5674_set_external_priority(150U, EE_PPCE200ZX_150_ISR_PRI);
#endif /* EE_PPCE200ZX_150_ISR_PRI */

#ifdef EE_PPCE200ZX_151_ISR_PRI
  EE_mpc5674_set_external_priority(151U, EE_PPCE200ZX_151_ISR_PRI);
#endif /* EE_PPCE200ZX_151_ISR_PRI */

#ifdef EE_PPCE200ZX_152_ISR_PRI
  EE_mpc5674_set_external_priority(152U, EE_PPCE200ZX_152_ISR_PRI);
#endif /* EE_PPCE200ZX_152_ISR_PRI */

#ifdef EE_PPCE200ZX_153_ISR_PRI
  EE_mpc5674_set_external_priority(153U, EE_PPCE200ZX_153_ISR_PRI);
#endif /* EE_PPCE200ZX_153_ISR_PRI */

#ifdef EE_PPCE200ZX_154_ISR_PRI
  EE_mpc5674_set_external_priority(154U, EE_PPCE200ZX_154_ISR_PRI);
#endif /* EE_PPCE200ZX_154_ISR_PRI */

#ifdef EE_PPCE200ZX_155_ISR_PRI
  EE_mpc5674_set_external_priority(155U, EE_PPCE200ZX_155_ISR_PRI);
#endif /* EE_PPCE200ZX_155_ISR_PRI */

#ifdef EE_PPCE200ZX_156_ISR_PRI
  EE_mpc5674_set_external_priority(156U, EE_PPCE200ZX_156_ISR_PRI);
#endif /* EE_PPCE200ZX_156_ISR_PRI */

#ifdef EE_PPCE200ZX_157_ISR_PRI
  EE_mpc5674_set_external_priority(157U, EE_PPCE200ZX_157_ISR_PRI);
#endif /* EE_PPCE200ZX_157_ISR_PRI */

#ifdef EE_PPCE200ZX_158_ISR_PRI
  EE_mpc5674_set_external_priority(158U, EE_PPCE200ZX_158_ISR_PRI);
#endif /* EE_PPCE200ZX_158_ISR_PRI */

#ifdef EE_PPCE200ZX_159_ISR_PRI
  EE_mpc5674_set_external_priority(159U, EE_PPCE200ZX_159_ISR_PRI);
#endif /* EE_PPCE200ZX_159_ISR_PRI */

#ifdef EE_PPCE200ZX_160_ISR_PRI
  EE_mpc5674_set_external_priority(160U, EE_PPCE200ZX_160_ISR_PRI);
#endif /* EE_PPCE200ZX_160_ISR_PRI */

#ifdef EE_PPCE200ZX_161_ISR_PRI
  EE_mpc5674_set_external_priority(161U, EE_PPCE200ZX_161_ISR_PRI);
#endif /* EE_PPCE200ZX_161_ISR_PRI */

#ifdef EE_PPCE200ZX_162_ISR_PRI
  EE_mpc5674_set_external_priority(162U, EE_PPCE200ZX_162_ISR_PRI);
#endif /* EE_PPCE200ZX_162_ISR_PRI */

#ifdef EE_PPCE200ZX_163_ISR_PRI
  EE_mpc5674_set_external_priority(163U, EE_PPCE200ZX_163_ISR_PRI);
#endif /* EE_PPCE200ZX_163_ISR_PRI */

#ifdef EE_PPCE200ZX_164_ISR_PRI
  EE_mpc5674_set_external_priority(164U, EE_PPCE200ZX_164_ISR_PRI);
#endif /* EE_PPCE200ZX_164_ISR_PRI */

#ifdef EE_PPCE200ZX_165_ISR_PRI
  EE_mpc5674_set_external_priority(165U, EE_PPCE200ZX_165_ISR_PRI);
#endif /* EE_PPCE200ZX_165_ISR_PRI */

#ifdef EE_PPCE200ZX_166_ISR_PRI
  EE_mpc5674_set_external_priority(166U, EE_PPCE200ZX_166_ISR_PRI);
#endif /* EE_PPCE200ZX_166_ISR_PRI */

#ifdef EE_PPCE200ZX_167_ISR_PRI
  EE_mpc5674_set_external_priority(167U, EE_PPCE200ZX_167_ISR_PRI);
#endif /* EE_PPCE200ZX_167_ISR_PRI */

#ifdef EE_PPCE200ZX_168_ISR_PRI
  EE_mpc5674_set_external_priority(168U, EE_PPCE200ZX_168_ISR_PRI);
#endif /* EE_PPCE200ZX_168_ISR_PRI */

#ifdef EE_PPCE200ZX_169_ISR_PRI
  EE_mpc5674_set_external_priority(169U, EE_PPCE200ZX_169_ISR_PRI);
#endif /* EE_PPCE200ZX_169_ISR_PRI */

#ifdef EE_PPCE200ZX_170_ISR_PRI
  EE_mpc5674_set_external_priority(170U, EE_PPCE200ZX_170_ISR_PRI);
#endif /* EE_PPCE200ZX_170_ISR_PRI */

#ifdef EE_PPCE200ZX_171_ISR_PRI
  EE_mpc5674_set_external_priority(171U, EE_PPCE200ZX_171_ISR_PRI);
#endif /* EE_PPCE200ZX_171_ISR_PRI */

#ifdef EE_PPCE200ZX_172_ISR_PRI
  EE_mpc5674_set_external_priority(172U, EE_PPCE200ZX_172_ISR_PRI);
#endif /* EE_PPCE200ZX_172_ISR_PRI */

#ifdef EE_PPCE200ZX_173_ISR_PRI
  EE_mpc5674_set_external_priority(173U, EE_PPCE200ZX_173_ISR_PRI);
#endif /* EE_PPCE200ZX_173_ISR_PRI */

#ifdef EE_PPCE200ZX_174_ISR_PRI
  EE_mpc5674_set_external_priority(174U, EE_PPCE200ZX_174_ISR_PRI);
#endif /* EE_PPCE200ZX_174_ISR_PRI */

#ifdef EE_PPCE200ZX_175_ISR_PRI
  EE_mpc5674_set_external_priority(175U, EE_PPCE200ZX_175_ISR_PRI);
#endif /* EE_PPCE200ZX_175_ISR_PRI */

#ifdef EE_PPCE200ZX_176_ISR_PRI
  EE_mpc5674_set_external_priority(176U, EE_PPCE200ZX_176_ISR_PRI);
#endif /* EE_PPCE200ZX_176_ISR_PRI */

#ifdef EE_PPCE200ZX_177_ISR_PRI
  EE_mpc5674_set_external_priority(177U, EE_PPCE200ZX_177_ISR_PRI);
#endif /* EE_PPCE200ZX_177_ISR_PRI */

#ifdef EE_PPCE200ZX_178_ISR_PRI
  EE_mpc5674_set_external_priority(178U, EE_PPCE200ZX_178_ISR_PRI);
#endif /* EE_PPCE200ZX_178_ISR_PRI */

#ifdef EE_PPCE200ZX_179_ISR_PRI
  EE_mpc5674_set_external_priority(179U, EE_PPCE200ZX_179_ISR_PRI);
#endif /* EE_PPCE200ZX_179_ISR_PRI */

#ifdef EE_PPCE200ZX_180_ISR_PRI
  EE_mpc5674_set_external_priority(180U, EE_PPCE200ZX_180_ISR_PRI);
#endif /* EE_PPCE200ZX_180_ISR_PRI */

#ifdef EE_PPCE200ZX_181_ISR_PRI
  EE_mpc5674_set_external_priority(181U, EE_PPCE200ZX_181_ISR_PRI);
#endif /* EE_PPCE200ZX_181_ISR_PRI */

#ifdef EE_PPCE200ZX_182_ISR_PRI
  EE_mpc5674_set_external_priority(182U, EE_PPCE200ZX_182_ISR_PRI);
#endif /* EE_PPCE200ZX_182_ISR_PRI */

#ifdef EE_PPCE200ZX_183_ISR_PRI
  EE_mpc5674_set_external_priority(183U, EE_PPCE200ZX_183_ISR_PRI);
#endif /* EE_PPCE200ZX_183_ISR_PRI */

#ifdef EE_PPCE200ZX_184_ISR_PRI
  EE_mpc5674_set_external_priority(184U, EE_PPCE200ZX_184_ISR_PRI);
#endif /* EE_PPCE200ZX_184_ISR_PRI */

#ifdef EE_PPCE200ZX_185_ISR_PRI
  EE_mpc5674_set_external_priority(185U, EE_PPCE200ZX_185_ISR_PRI);
#endif /* EE_PPCE200ZX_185_ISR_PRI */

#ifdef EE_PPCE200ZX_186_ISR_PRI
  EE_mpc5674_set_external_priority(186U, EE_PPCE200ZX_186_ISR_PRI);
#endif /* EE_PPCE200ZX_186_ISR_PRI */

#ifdef EE_PPCE200ZX_187_ISR_PRI
  EE_mpc5674_set_external_priority(187U, EE_PPCE200ZX_187_ISR_PRI);
#endif /* EE_PPCE200ZX_187_ISR_PRI */

#ifdef EE_PPCE200ZX_188_ISR_PRI
  EE_mpc5674_set_external_priority(188U, EE_PPCE200ZX_188_ISR_PRI);
#endif /* EE_PPCE200ZX_188_ISR_PRI */

#ifdef EE_PPCE200ZX_189_ISR_PRI
  EE_mpc5674_set_external_priority(189U, EE_PPCE200ZX_189_ISR_PRI);
#endif /* EE_PPCE200ZX_189_ISR_PRI */

#ifdef EE_PPCE200ZX_190_ISR_PRI
  EE_mpc5674_set_external_priority(190U, EE_PPCE200ZX_190_ISR_PRI);
#endif /* EE_PPCE200ZX_190_ISR_PRI */

#ifdef EE_PPCE200ZX_191_ISR_PRI
  EE_mpc5674_set_external_priority(191U, EE_PPCE200ZX_191_ISR_PRI);
#endif /* EE_PPCE200ZX_191_ISR_PRI */

#ifdef EE_PPCE200ZX_192_ISR_PRI
  EE_mpc5674_set_external_priority(192U, EE_PPCE200ZX_192_ISR_PRI);
#endif /* EE_PPCE200ZX_192_ISR_PRI */

#ifdef EE_PPCE200ZX_193_ISR_PRI
  EE_mpc5674_set_external_priority(193U, EE_PPCE200ZX_193_ISR_PRI);
#endif /* EE_PPCE200ZX_193_ISR_PRI */

#ifdef EE_PPCE200ZX_194_ISR_PRI
  EE_mpc5674_set_external_priority(194U, EE_PPCE200ZX_194_ISR_PRI);
#endif /* EE_PPCE200ZX_194_ISR_PRI */

#ifdef EE_PPCE200ZX_195_ISR_PRI
  EE_mpc5674_set_external_priority(195U, EE_PPCE200ZX_195_ISR_PRI);
#endif /* EE_PPCE200ZX_195_ISR_PRI */

#ifdef EE_PPCE200ZX_196_ISR_PRI
  EE_mpc5674_set_external_priority(196U, EE_PPCE200ZX_196_ISR_PRI);
#endif /* EE_PPCE200ZX_196_ISR_PRI */

#ifdef EE_PPCE200ZX_197_ISR_PRI
  EE_mpc5674_set_external_priority(197U, EE_PPCE200ZX_197_ISR_PRI);
#endif /* EE_PPCE200ZX_197_ISR_PRI */

#ifdef EE_PPCE200ZX_198_ISR_PRI
  EE_mpc5674_set_external_priority(198U, EE_PPCE200ZX_198_ISR_PRI);
#endif /* EE_PPCE200ZX_198_ISR_PRI */

#ifdef EE_PPCE200ZX_199_ISR_PRI
  EE_mpc5674_set_external_priority(199U, EE_PPCE200ZX_199_ISR_PRI);
#endif /* EE_PPCE200ZX_199_ISR_PRI */

#ifdef EE_PPCE200ZX_200_ISR_PRI
  EE_mpc5674_set_external_priority(200U, EE_PPCE200ZX_200_ISR_PRI);
#endif /* EE_PPCE200ZX_200_ISR_PRI */

#ifdef EE_PPCE200ZX_201_ISR_PRI
  EE_mpc5674_set_external_priority(201U, EE_PPCE200ZX_201_ISR_PRI);
#endif /* EE_PPCE200ZX_201_ISR_PRI */

#ifdef EE_PPCE200ZX_202_ISR_PRI
  EE_mpc5674_set_external_priority(202U, EE_PPCE200ZX_202_ISR_PRI);
#endif /* EE_PPCE200ZX_202_ISR_PRI */

#ifdef EE_PPCE200ZX_203_ISR_PRI
  EE_mpc5674_set_external_priority(203U, EE_PPCE200ZX_203_ISR_PRI);
#endif /* EE_PPCE200ZX_203_ISR_PRI */

#ifdef EE_PPCE200ZX_204_ISR_PRI
  EE_mpc5674_set_external_priority(204U, EE_PPCE200ZX_204_ISR_PRI);
#endif /* EE_PPCE200ZX_204_ISR_PRI */

#ifdef EE_PPCE200ZX_205_ISR_PRI
  EE_mpc5674_set_external_priority(205U, EE_PPCE200ZX_205_ISR_PRI);
#endif /* EE_PPCE200ZX_205_ISR_PRI */

#ifdef EE_PPCE200ZX_206_ISR_PRI
  EE_mpc5674_set_external_priority(206U, EE_PPCE200ZX_206_ISR_PRI);
#endif /* EE_PPCE200ZX_206_ISR_PRI */

#ifdef EE_PPCE200ZX_207_ISR_PRI
  EE_mpc5674_set_external_priority(207U, EE_PPCE200ZX_207_ISR_PRI);
#endif /* EE_PPCE200ZX_207_ISR_PRI */

#ifdef EE_PPCE200ZX_208_ISR_PRI
  EE_mpc5674_set_external_priority(208U, EE_PPCE200ZX_208_ISR_PRI);
#endif /* EE_PPCE200ZX_208_ISR_PRI */

#ifdef EE_PPCE200ZX_209_ISR_PRI
  EE_mpc5674_set_external_priority(209U, EE_PPCE200ZX_209_ISR_PRI);
#endif /* EE_PPCE200ZX_209_ISR_PRI */

#ifdef EE_PPCE200ZX_210_ISR_PRI
  EE_mpc5674_set_external_priority(210U, EE_PPCE200ZX_210_ISR_PRI);
#endif /* EE_PPCE200ZX_210_ISR_PRI */

#ifdef EE_PPCE200ZX_211_ISR_PRI
  EE_mpc5674_set_external_priority(211U, EE_PPCE200ZX_211_ISR_PRI);
#endif /* EE_PPCE200ZX_211_ISR_PRI */

#ifdef EE_PPCE200ZX_212_ISR_PRI
  EE_mpc5674_set_external_priority(212U, EE_PPCE200ZX_212_ISR_PRI);
#endif /* EE_PPCE200ZX_212_ISR_PRI */

#ifdef EE_PPCE200ZX_213_ISR_PRI
  EE_mpc5674_set_external_priority(213U, EE_PPCE200ZX_213_ISR_PRI);
#endif /* EE_PPCE200ZX_213_ISR_PRI */

#ifdef EE_PPCE200ZX_214_ISR_PRI
  EE_mpc5674_set_external_priority(214U, EE_PPCE200ZX_214_ISR_PRI);
#endif /* EE_PPCE200ZX_214_ISR_PRI */

#ifdef EE_PPCE200ZX_215_ISR_PRI
  EE_mpc5674_set_external_priority(215U, EE_PPCE200ZX_215_ISR_PRI);
#endif /* EE_PPCE200ZX_215_ISR_PRI */

#ifdef EE_PPCE200ZX_216_ISR_PRI
  EE_mpc5674_set_external_priority(216U, EE_PPCE200ZX_216_ISR_PRI);
#endif /* EE_PPCE200ZX_216_ISR_PRI */

#ifdef EE_PPCE200ZX_217_ISR_PRI
  EE_mpc5674_set_external_priority(217U, EE_PPCE200ZX_217_ISR_PRI);
#endif /* EE_PPCE200ZX_217_ISR_PRI */

#ifdef EE_PPCE200ZX_218_ISR_PRI
  EE_mpc5674_set_external_priority(218U, EE_PPCE200ZX_218_ISR_PRI);
#endif /* EE_PPCE200ZX_218_ISR_PRI */

#ifdef EE_PPCE200ZX_219_ISR_PRI
  EE_mpc5674_set_external_priority(219U, EE_PPCE200ZX_219_ISR_PRI);
#endif /* EE_PPCE200ZX_219_ISR_PRI */

#ifdef EE_PPCE200ZX_220_ISR_PRI
  EE_mpc5674_set_external_priority(220U, EE_PPCE200ZX_220_ISR_PRI);
#endif /* EE_PPCE200ZX_220_ISR_PRI */

#ifdef EE_PPCE200ZX_221_ISR_PRI
  EE_mpc5674_set_external_priority(221U, EE_PPCE200ZX_221_ISR_PRI);
#endif /* EE_PPCE200ZX_221_ISR_PRI */

#ifdef EE_PPCE200ZX_222_ISR_PRI
  EE_mpc5674_set_external_priority(222U, EE_PPCE200ZX_222_ISR_PRI);
#endif /* EE_PPCE200ZX_222_ISR_PRI */

#ifdef EE_PPCE200ZX_223_ISR_PRI
  EE_mpc5674_set_external_priority(223U, EE_PPCE200ZX_223_ISR_PRI);
#endif /* EE_PPCE200ZX_223_ISR_PRI */

#ifdef EE_PPCE200ZX_224_ISR_PRI
  EE_mpc5674_set_external_priority(224U, EE_PPCE200ZX_224_ISR_PRI);
#endif /* EE_PPCE200ZX_224_ISR_PRI */

#ifdef EE_PPCE200ZX_225_ISR_PRI
  EE_mpc5674_set_external_priority(225U, EE_PPCE200ZX_225_ISR_PRI);
#endif /* EE_PPCE200ZX_225_ISR_PRI */

#ifdef EE_PPCE200ZX_226_ISR_PRI
  EE_mpc5674_set_external_priority(226U, EE_PPCE200ZX_226_ISR_PRI);
#endif /* EE_PPCE200ZX_226_ISR_PRI */

#ifdef EE_PPCE200ZX_227_ISR_PRI
  EE_mpc5674_set_external_priority(227U, EE_PPCE200ZX_227_ISR_PRI);
#endif /* EE_PPCE200ZX_227_ISR_PRI */

#ifdef EE_PPCE200ZX_228_ISR_PRI
  EE_mpc5674_set_external_priority(228U, EE_PPCE200ZX_228_ISR_PRI);
#endif /* EE_PPCE200ZX_228_ISR_PRI */

#ifdef EE_PPCE200ZX_229_ISR_PRI
  EE_mpc5674_set_external_priority(229U, EE_PPCE200ZX_229_ISR_PRI);
#endif /* EE_PPCE200ZX_229_ISR_PRI */

#ifdef EE_PPCE200ZX_230_ISR_PRI
  EE_mpc5674_set_external_priority(230U, EE_PPCE200ZX_230_ISR_PRI);
#endif /* EE_PPCE200ZX_230_ISR_PRI */

#ifdef EE_PPCE200ZX_231_ISR_PRI
  EE_mpc5674_set_external_priority(231U, EE_PPCE200ZX_231_ISR_PRI);
#endif /* EE_PPCE200ZX_231_ISR_PRI */

#ifdef EE_PPCE200ZX_232_ISR_PRI
  EE_mpc5674_set_external_priority(232U, EE_PPCE200ZX_232_ISR_PRI);
#endif /* EE_PPCE200ZX_232_ISR_PRI */

#ifdef EE_PPCE200ZX_233_ISR_PRI
  EE_mpc5674_set_external_priority(233U, EE_PPCE200ZX_233_ISR_PRI);
#endif /* EE_PPCE200ZX_233_ISR_PRI */

#ifdef EE_PPCE200ZX_234_ISR_PRI
  EE_mpc5674_set_external_priority(234U, EE_PPCE200ZX_234_ISR_PRI);
#endif /* EE_PPCE200ZX_234_ISR_PRI */

#ifdef EE_PPCE200ZX_235_ISR_PRI
  EE_mpc5674_set_external_priority(235U, EE_PPCE200ZX_235_ISR_PRI);
#endif /* EE_PPCE200ZX_235_ISR_PRI */

#ifdef EE_PPCE200ZX_236_ISR_PRI
  EE_mpc5674_set_external_priority(236U, EE_PPCE200ZX_236_ISR_PRI);
#endif /* EE_PPCE200ZX_236_ISR_PRI */

#ifdef EE_PPCE200ZX_237_ISR_PRI
  EE_mpc5674_set_external_priority(237U, EE_PPCE200ZX_237_ISR_PRI);
#endif /* EE_PPCE200ZX_237_ISR_PRI */

#ifdef EE_PPCE200ZX_238_ISR_PRI
  EE_mpc5674_set_external_priority(238U, EE_PPCE200ZX_238_ISR_PRI);
#endif /* EE_PPCE200ZX_238_ISR_PRI */

#ifdef EE_PPCE200ZX_239_ISR_PRI
  EE_mpc5674_set_external_priority(239U, EE_PPCE200ZX_239_ISR_PRI);
#endif /* EE_PPCE200ZX_239_ISR_PRI */

#ifdef EE_PPCE200ZX_240_ISR_PRI
  EE_mpc5674_set_external_priority(240U, EE_PPCE200ZX_240_ISR_PRI);
#endif /* EE_PPCE200ZX_240_ISR_PRI */

#ifdef EE_PPCE200ZX_241_ISR_PRI
  EE_mpc5674_set_external_priority(241U, EE_PPCE200ZX_241_ISR_PRI);
#endif /* EE_PPCE200ZX_241_ISR_PRI */

#ifdef EE_PPCE200ZX_242_ISR_PRI
  EE_mpc5674_set_external_priority(242U, EE_PPCE200ZX_242_ISR_PRI);
#endif /* EE_PPCE200ZX_242_ISR_PRI */

#ifdef EE_PPCE200ZX_243_ISR_PRI
  EE_mpc5674_set_external_priority(243U, EE_PPCE200ZX_243_ISR_PRI);
#endif /* EE_PPCE200ZX_243_ISR_PRI */

#ifdef EE_PPCE200ZX_244_ISR_PRI
  EE_mpc5674_set_external_priority(244U, EE_PPCE200ZX_244_ISR_PRI);
#endif /* EE_PPCE200ZX_244_ISR_PRI */

#ifdef EE_PPCE200ZX_245_ISR_PRI
  EE_mpc5674_set_external_priority(245U, EE_PPCE200ZX_245_ISR_PRI);
#endif /* EE_PPCE200ZX_245_ISR_PRI */

#ifdef EE_PPCE200ZX_246_ISR_PRI
  EE_mpc5674_set_external_priority(246U, EE_PPCE200ZX_246_ISR_PRI);
#endif /* EE_PPCE200ZX_246_ISR_PRI */

#ifdef EE_PPCE200ZX_247_ISR_PRI
  EE_mpc5674_set_external_priority(247U, EE_PPCE200ZX_247_ISR_PRI);
#endif /* EE_PPCE200ZX_247_ISR_PRI */

#ifdef EE_PPCE200ZX_248_ISR_PRI
  EE_mpc5674_set_external_priority(248U, EE_PPCE200ZX_248_ISR_PRI);
#endif /* EE_PPCE200ZX_248_ISR_PRI */

#ifdef EE_PPCE200ZX_249_ISR_PRI
  EE_mpc5674_set_external_priority(249U, EE_PPCE200ZX_249_ISR_PRI);
#endif /* EE_PPCE200ZX_249_ISR_PRI */

#ifdef EE_PPCE200ZX_250_ISR_PRI
  EE_mpc5674_set_external_priority(250U, EE_PPCE200ZX_250_ISR_PRI);
#endif /* EE_PPCE200ZX_250_ISR_PRI */

#ifdef EE_PPCE200ZX_251_ISR_PRI
  EE_mpc5674_set_external_priority(251U, EE_PPCE200ZX_251_ISR_PRI);
#endif /* EE_PPCE200ZX_251_ISR_PRI */

#ifdef EE_PPCE200ZX_252_ISR_PRI
  EE_mpc5674_set_external_priority(252U, EE_PPCE200ZX_252_ISR_PRI);
#endif /* EE_PPCE200ZX_252_ISR_PRI */

#ifdef EE_PPCE200ZX_253_ISR_PRI
  EE_mpc5674_set_external_priority(253U, EE_PPCE200ZX_253_ISR_PRI);
#endif /* EE_PPCE200ZX_253_ISR_PRI */

#ifdef EE_PPCE200ZX_254_ISR_PRI
  EE_mpc5674_set_external_priority(254U, EE_PPCE200ZX_254_ISR_PRI);
#endif /* EE_PPCE200ZX_254_ISR_PRI */

#ifdef EE_PPCE200ZX_255_ISR_PRI
  EE_mpc5674_set_external_priority(255U, EE_PPCE200ZX_255_ISR_PRI);
#endif /* EE_PPCE200ZX_255_ISR_PRI */

#ifdef EE_PPCE200ZX_256_ISR_PRI
  EE_mpc5674_set_external_priority(256U, EE_PPCE200ZX_256_ISR_PRI);
#endif /* EE_PPCE200ZX_256_ISR_PRI */

#ifdef EE_PPCE200ZX_257_ISR_PRI
  EE_mpc5674_set_external_priority(257U, EE_PPCE200ZX_257_ISR_PRI);
#endif /* EE_PPCE200ZX_257_ISR_PRI */

#ifdef EE_PPCE200ZX_258_ISR_PRI
  EE_mpc5674_set_external_priority(258U, EE_PPCE200ZX_258_ISR_PRI);
#endif /* EE_PPCE200ZX_258_ISR_PRI */

#ifdef EE_PPCE200ZX_259_ISR_PRI
  EE_mpc5674_set_external_priority(259U, EE_PPCE200ZX_259_ISR_PRI);
#endif /* EE_PPCE200ZX_259_ISR_PRI */

#ifdef EE_PPCE200ZX_260_ISR_PRI
  EE_mpc5674_set_external_priority(260U, EE_PPCE200ZX_260_ISR_PRI);
#endif /* EE_PPCE200ZX_260_ISR_PRI */

#ifdef EE_PPCE200ZX_261_ISR_PRI
  EE_mpc5674_set_external_priority(261U, EE_PPCE200ZX_261_ISR_PRI);
#endif /* EE_PPCE200ZX_261_ISR_PRI */

#ifdef EE_PPCE200ZX_262_ISR_PRI
  EE_mpc5674_set_external_priority(262U, EE_PPCE200ZX_262_ISR_PRI);
#endif /* EE_PPCE200ZX_262_ISR_PRI */

#ifdef EE_PPCE200ZX_263_ISR_PRI
  EE_mpc5674_set_external_priority(263U, EE_PPCE200ZX_263_ISR_PRI);
#endif /* EE_PPCE200ZX_263_ISR_PRI */

#ifdef EE_PPCE200ZX_264_ISR_PRI
  EE_mpc5674_set_external_priority(264U, EE_PPCE200ZX_264_ISR_PRI);
#endif /* EE_PPCE200ZX_264_ISR_PRI */

#ifdef EE_PPCE200ZX_265_ISR_PRI
  EE_mpc5674_set_external_priority(265U, EE_PPCE200ZX_265_ISR_PRI);
#endif /* EE_PPCE200ZX_265_ISR_PRI */

#ifdef EE_PPCE200ZX_266_ISR_PRI
  EE_mpc5674_set_external_priority(266U, EE_PPCE200ZX_266_ISR_PRI);
#endif /* EE_PPCE200ZX_266_ISR_PRI */

#ifdef EE_PPCE200ZX_267_ISR_PRI
  EE_mpc5674_set_external_priority(267U, EE_PPCE200ZX_267_ISR_PRI);
#endif /* EE_PPCE200ZX_267_ISR_PRI */

#ifdef EE_PPCE200ZX_268_ISR_PRI
  EE_mpc5674_set_external_priority(268U, EE_PPCE200ZX_268_ISR_PRI);
#endif /* EE_PPCE200ZX_268_ISR_PRI */

#ifdef EE_PPCE200ZX_269_ISR_PRI
  EE_mpc5674_set_external_priority(269U, EE_PPCE200ZX_269_ISR_PRI);
#endif /* EE_PPCE200ZX_269_ISR_PRI */

#ifdef EE_PPCE200ZX_270_ISR_PRI
  EE_mpc5674_set_external_priority(270U, EE_PPCE200ZX_270_ISR_PRI);
#endif /* EE_PPCE200ZX_270_ISR_PRI */

#ifdef EE_PPCE200ZX_271_ISR_PRI
  EE_mpc5674_set_external_priority(271U, EE_PPCE200ZX_271_ISR_PRI);
#endif /* EE_PPCE200ZX_271_ISR_PRI */

#ifdef EE_PPCE200ZX_272_ISR_PRI
  EE_mpc5674_set_external_priority(272U, EE_PPCE200ZX_272_ISR_PRI);
#endif /* EE_PPCE200ZX_272_ISR_PRI */

#ifdef EE_PPCE200ZX_273_ISR_PRI
  EE_mpc5674_set_external_priority(273U, EE_PPCE200ZX_273_ISR_PRI);
#endif /* EE_PPCE200ZX_273_ISR_PRI */

#ifdef EE_PPCE200ZX_274_ISR_PRI
  EE_mpc5674_set_external_priority(274U, EE_PPCE200ZX_274_ISR_PRI);
#endif /* EE_PPCE200ZX_274_ISR_PRI */

#ifdef EE_PPCE200ZX_275_ISR_PRI
  EE_mpc5674_set_external_priority(275U, EE_PPCE200ZX_275_ISR_PRI);
#endif /* EE_PPCE200ZX_275_ISR_PRI */

#ifdef EE_PPCE200ZX_276_ISR_PRI
  EE_mpc5674_set_external_priority(276U, EE_PPCE200ZX_276_ISR_PRI);
#endif /* EE_PPCE200ZX_276_ISR_PRI */

#ifdef EE_PPCE200ZX_277_ISR_PRI
  EE_mpc5674_set_external_priority(277U, EE_PPCE200ZX_277_ISR_PRI);
#endif /* EE_PPCE200ZX_277_ISR_PRI */

#ifdef EE_PPCE200ZX_278_ISR_PRI
  EE_mpc5674_set_external_priority(278U, EE_PPCE200ZX_278_ISR_PRI);
#endif /* EE_PPCE200ZX_278_ISR_PRI */

#ifdef EE_PPCE200ZX_279_ISR_PRI
  EE_mpc5674_set_external_priority(279U, EE_PPCE200ZX_279_ISR_PRI);
#endif /* EE_PPCE200ZX_279_ISR_PRI */

#ifdef EE_PPCE200ZX_280_ISR_PRI
  EE_mpc5674_set_external_priority(280U, EE_PPCE200ZX_280_ISR_PRI);
#endif /* EE_PPCE200ZX_280_ISR_PRI */

#ifdef EE_PPCE200ZX_281_ISR_PRI
  EE_mpc5674_set_external_priority(281U, EE_PPCE200ZX_281_ISR_PRI);
#endif /* EE_PPCE200ZX_281_ISR_PRI */

#ifdef EE_PPCE200ZX_282_ISR_PRI
  EE_mpc5674_set_external_priority(282U, EE_PPCE200ZX_282_ISR_PRI);
#endif /* EE_PPCE200ZX_282_ISR_PRI */

#ifdef EE_PPCE200ZX_283_ISR_PRI
  EE_mpc5674_set_external_priority(283U, EE_PPCE200ZX_283_ISR_PRI);
#endif /* EE_PPCE200ZX_283_ISR_PRI */

#ifdef EE_PPCE200ZX_284_ISR_PRI
  EE_mpc5674_set_external_priority(284U, EE_PPCE200ZX_284_ISR_PRI);
#endif /* EE_PPCE200ZX_284_ISR_PRI */

#ifdef EE_PPCE200ZX_285_ISR_PRI
  EE_mpc5674_set_external_priority(285U, EE_PPCE200ZX_285_ISR_PRI);
#endif /* EE_PPCE200ZX_285_ISR_PRI */

#ifdef EE_PPCE200ZX_286_ISR_PRI
  EE_mpc5674_set_external_priority(286U, EE_PPCE200ZX_286_ISR_PRI);
#endif /* EE_PPCE200ZX_286_ISR_PRI */

#ifdef EE_PPCE200ZX_287_ISR_PRI
  EE_mpc5674_set_external_priority(287U, EE_PPCE200ZX_287_ISR_PRI);
#endif /* EE_PPCE200ZX_287_ISR_PRI */

#ifdef EE_PPCE200ZX_288_ISR_PRI
  EE_mpc5674_set_external_priority(288U, EE_PPCE200ZX_288_ISR_PRI);
#endif /* EE_PPCE200ZX_288_ISR_PRI */

#ifdef EE_PPCE200ZX_289_ISR_PRI
  EE_mpc5674_set_external_priority(289U, EE_PPCE200ZX_289_ISR_PRI);
#endif /* EE_PPCE200ZX_289_ISR_PRI */

#ifdef EE_PPCE200ZX_290_ISR_PRI
  EE_mpc5674_set_external_priority(290U, EE_PPCE200ZX_290_ISR_PRI);
#endif /* EE_PPCE200ZX_290_ISR_PRI */

#ifdef EE_PPCE200ZX_291_ISR_PRI
  EE_mpc5674_set_external_priority(291U, EE_PPCE200ZX_291_ISR_PRI);
#endif /* EE_PPCE200ZX_291_ISR_PRI */

#ifdef EE_PPCE200ZX_292_ISR_PRI
  EE_mpc5674_set_external_priority(292U, EE_PPCE200ZX_292_ISR_PRI);
#endif /* EE_PPCE200ZX_292_ISR_PRI */

#ifdef EE_PPCE200ZX_293_ISR_PRI
  EE_mpc5674_set_external_priority(293U, EE_PPCE200ZX_293_ISR_PRI);
#endif /* EE_PPCE200ZX_293_ISR_PRI */

#ifdef EE_PPCE200ZX_294_ISR_PRI
  EE_mpc5674_set_external_priority(294U, EE_PPCE200ZX_294_ISR_PRI);
#endif /* EE_PPCE200ZX_294_ISR_PRI */

#ifdef EE_PPCE200ZX_295_ISR_PRI
  EE_mpc5674_set_external_priority(295U, EE_PPCE200ZX_295_ISR_PRI);
#endif /* EE_PPCE200ZX_295_ISR_PRI */

#ifdef EE_PPCE200ZX_296_ISR_PRI
  EE_mpc5674_set_external_priority(296U, EE_PPCE200ZX_296_ISR_PRI);
#endif /* EE_PPCE200ZX_296_ISR_PRI */

#ifdef EE_PPCE200ZX_297_ISR_PRI
  EE_mpc5674_set_external_priority(297U, EE_PPCE200ZX_297_ISR_PRI);
#endif /* EE_PPCE200ZX_297_ISR_PRI */

#ifdef EE_PPCE200ZX_298_ISR_PRI
  EE_mpc5674_set_external_priority(298U, EE_PPCE200ZX_298_ISR_PRI);
#endif /* EE_PPCE200ZX_298_ISR_PRI */

#ifdef EE_PPCE200ZX_299_ISR_PRI
  EE_mpc5674_set_external_priority(299U, EE_PPCE200ZX_299_ISR_PRI);
#endif /* EE_PPCE200ZX_299_ISR_PRI */

#ifdef EE_PPCE200ZX_300_ISR_PRI
  EE_mpc5674_set_external_priority(300U, EE_PPCE200ZX_300_ISR_PRI);
#endif /* EE_PPCE200ZX_300_ISR_PRI */

#ifdef EE_PPCE200ZX_301_ISR_PRI
  EE_mpc5674_set_external_priority(301U, EE_PPCE200ZX_301_ISR_PRI);
#endif /* EE_PPCE200ZX_301_ISR_PRI */

#ifdef EE_PPCE200ZX_302_ISR_PRI
  EE_mpc5674_set_external_priority(302U, EE_PPCE200ZX_302_ISR_PRI);
#endif /* EE_PPCE200ZX_302_ISR_PRI */

#ifdef EE_PPCE200ZX_303_ISR_PRI
  EE_mpc5674_set_external_priority(303U, EE_PPCE200ZX_303_ISR_PRI);
#endif /* EE_PPCE200ZX_303_ISR_PRI */

#ifdef EE_PPCE200ZX_304_ISR_PRI
  EE_mpc5674_set_external_priority(304U, EE_PPCE200ZX_304_ISR_PRI);
#endif /* EE_PPCE200ZX_304_ISR_PRI */

#ifdef EE_PPCE200ZX_305_ISR_PRI
  EE_mpc5674_set_external_priority(305U, EE_PPCE200ZX_305_ISR_PRI);
#endif /* EE_PPCE200ZX_305_ISR_PRI */

#ifdef EE_PPCE200ZX_306_ISR_PRI
  EE_mpc5674_set_external_priority(306U, EE_PPCE200ZX_306_ISR_PRI);
#endif /* EE_PPCE200ZX_306_ISR_PRI */

#ifdef EE_PPCE200ZX_307_ISR_PRI
  EE_mpc5674_set_external_priority(307U, EE_PPCE200ZX_307_ISR_PRI);
#endif /* EE_PPCE200ZX_307_ISR_PRI */

#ifdef EE_PPCE200ZX_308_ISR_PRI
  EE_mpc5674_set_external_priority(308U, EE_PPCE200ZX_308_ISR_PRI);
#endif /* EE_PPCE200ZX_308_ISR_PRI */

#ifdef EE_PPCE200ZX_309_ISR_PRI
  EE_mpc5674_set_external_priority(309U, EE_PPCE200ZX_309_ISR_PRI);
#endif /* EE_PPCE200ZX_309_ISR_PRI */

#ifdef EE_PPCE200ZX_310_ISR_PRI
  EE_mpc5674_set_external_priority(310U, EE_PPCE200ZX_310_ISR_PRI);
#endif /* EE_PPCE200ZX_310_ISR_PRI */

#ifdef EE_PPCE200ZX_311_ISR_PRI
  EE_mpc5674_set_external_priority(311U, EE_PPCE200ZX_311_ISR_PRI);
#endif /* EE_PPCE200ZX_311_ISR_PRI */

#ifdef EE_PPCE200ZX_312_ISR_PRI
  EE_mpc5674_set_external_priority(312U, EE_PPCE200ZX_312_ISR_PRI);
#endif /* EE_PPCE200ZX_312_ISR_PRI */

#ifdef EE_PPCE200ZX_313_ISR_PRI
  EE_mpc5674_set_external_priority(313U, EE_PPCE200ZX_313_ISR_PRI);
#endif /* EE_PPCE200ZX_313_ISR_PRI */

#ifdef EE_PPCE200ZX_314_ISR_PRI
  EE_mpc5674_set_external_priority(314U, EE_PPCE200ZX_314_ISR_PRI);
#endif /* EE_PPCE200ZX_314_ISR_PRI */

#ifdef EE_PPCE200ZX_315_ISR_PRI
  EE_mpc5674_set_external_priority(315U, EE_PPCE200ZX_315_ISR_PRI);
#endif /* EE_PPCE200ZX_315_ISR_PRI */

#ifdef EE_PPCE200ZX_316_ISR_PRI
  EE_mpc5674_set_external_priority(316U, EE_PPCE200ZX_316_ISR_PRI);
#endif /* EE_PPCE200ZX_316_ISR_PRI */

#ifdef EE_PPCE200ZX_317_ISR_PRI
  EE_mpc5674_set_external_priority(317U, EE_PPCE200ZX_317_ISR_PRI);
#endif /* EE_PPCE200ZX_317_ISR_PRI */

#ifdef EE_PPCE200ZX_318_ISR_PRI
  EE_mpc5674_set_external_priority(318U, EE_PPCE200ZX_318_ISR_PRI);
#endif /* EE_PPCE200ZX_318_ISR_PRI */

#ifdef EE_PPCE200ZX_319_ISR_PRI
  EE_mpc5674_set_external_priority(319U, EE_PPCE200ZX_319_ISR_PRI);
#endif /* EE_PPCE200ZX_319_ISR_PRI */

#ifdef EE_PPCE200ZX_320_ISR_PRI
  EE_mpc5674_set_external_priority(320U, EE_PPCE200ZX_320_ISR_PRI);
#endif /* EE_PPCE200ZX_320_ISR_PRI */

#ifdef EE_PPCE200ZX_321_ISR_PRI
  EE_mpc5674_set_external_priority(321U, EE_PPCE200ZX_321_ISR_PRI);
#endif /* EE_PPCE200ZX_321_ISR_PRI */

#ifdef EE_PPCE200ZX_322_ISR_PRI
  EE_mpc5674_set_external_priority(322U, EE_PPCE200ZX_322_ISR_PRI);
#endif /* EE_PPCE200ZX_322_ISR_PRI */

#ifdef EE_PPCE200ZX_323_ISR_PRI
  EE_mpc5674_set_external_priority(323U, EE_PPCE200ZX_323_ISR_PRI);
#endif /* EE_PPCE200ZX_323_ISR_PRI */

#ifdef EE_PPCE200ZX_324_ISR_PRI
  EE_mpc5674_set_external_priority(324U, EE_PPCE200ZX_324_ISR_PRI);
#endif /* EE_PPCE200ZX_324_ISR_PRI */

#ifdef EE_PPCE200ZX_325_ISR_PRI
  EE_mpc5674_set_external_priority(325U, EE_PPCE200ZX_325_ISR_PRI);
#endif /* EE_PPCE200ZX_325_ISR_PRI */

#ifdef EE_PPCE200ZX_326_ISR_PRI
  EE_mpc5674_set_external_priority(326U, EE_PPCE200ZX_326_ISR_PRI);
#endif /* EE_PPCE200ZX_326_ISR_PRI */

#ifdef EE_PPCE200ZX_327_ISR_PRI
  EE_mpc5674_set_external_priority(327U, EE_PPCE200ZX_327_ISR_PRI);
#endif /* EE_PPCE200ZX_327_ISR_PRI */

#ifdef EE_PPCE200ZX_328_ISR_PRI
  EE_mpc5674_set_external_priority(328U, EE_PPCE200ZX_328_ISR_PRI);
#endif /* EE_PPCE200ZX_328_ISR_PRI */

#ifdef EE_PPCE200ZX_329_ISR_PRI
  EE_mpc5674_set_external_priority(329U, EE_PPCE200ZX_329_ISR_PRI);
#endif /* EE_PPCE200ZX_329_ISR_PRI */

#ifdef EE_PPCE200ZX_330_ISR_PRI
  EE_mpc5674_set_external_priority(330U, EE_PPCE200ZX_330_ISR_PRI);
#endif /* EE_PPCE200ZX_330_ISR_PRI */

#ifdef EE_PPCE200ZX_331_ISR_PRI
  EE_mpc5674_set_external_priority(331U, EE_PPCE200ZX_331_ISR_PRI);
#endif /* EE_PPCE200ZX_331_ISR_PRI */

#ifdef EE_PPCE200ZX_332_ISR_PRI
  EE_mpc5674_set_external_priority(332U, EE_PPCE200ZX_332_ISR_PRI);
#endif /* EE_PPCE200ZX_332_ISR_PRI */

#ifdef EE_PPCE200ZX_333_ISR_PRI
  EE_mpc5674_set_external_priority(333U, EE_PPCE200ZX_333_ISR_PRI);
#endif /* EE_PPCE200ZX_333_ISR_PRI */

#ifdef EE_PPCE200ZX_334_ISR_PRI
  EE_mpc5674_set_external_priority(334U, EE_PPCE200ZX_334_ISR_PRI);
#endif /* EE_PPCE200ZX_334_ISR_PRI */

#ifdef EE_PPCE200ZX_335_ISR_PRI
  EE_mpc5674_set_external_priority(335U, EE_PPCE200ZX_335_ISR_PRI);
#endif /* EE_PPCE200ZX_335_ISR_PRI */

#ifdef EE_PPCE200ZX_336_ISR_PRI
  EE_mpc5674_set_external_priority(336U, EE_PPCE200ZX_336_ISR_PRI);
#endif /* EE_PPCE200ZX_336_ISR_PRI */

#ifdef EE_PPCE200ZX_337_ISR_PRI
  EE_mpc5674_set_external_priority(337U, EE_PPCE200ZX_337_ISR_PRI);
#endif /* EE_PPCE200ZX_337_ISR_PRI */

#ifdef EE_PPCE200ZX_338_ISR_PRI
  EE_mpc5674_set_external_priority(338U, EE_PPCE200ZX_338_ISR_PRI);
#endif /* EE_PPCE200ZX_338_ISR_PRI */

#ifdef EE_PPCE200ZX_339_ISR_PRI
  EE_mpc5674_set_external_priority(339U, EE_PPCE200ZX_339_ISR_PRI);
#endif /* EE_PPCE200ZX_339_ISR_PRI */

#ifdef EE_PPCE200ZX_340_ISR_PRI
  EE_mpc5674_set_external_priority(340U, EE_PPCE200ZX_340_ISR_PRI);
#endif /* EE_PPCE200ZX_340_ISR_PRI */

#ifdef EE_PPCE200ZX_341_ISR_PRI
  EE_mpc5674_set_external_priority(341U, EE_PPCE200ZX_341_ISR_PRI);
#endif /* EE_PPCE200ZX_341_ISR_PRI */

#ifdef EE_PPCE200ZX_342_ISR_PRI
  EE_mpc5674_set_external_priority(342U, EE_PPCE200ZX_342_ISR_PRI);
#endif /* EE_PPCE200ZX_342_ISR_PRI */

#ifdef EE_PPCE200ZX_343_ISR_PRI
  EE_mpc5674_set_external_priority(343U, EE_PPCE200ZX_343_ISR_PRI);
#endif /* EE_PPCE200ZX_343_ISR_PRI */

#ifdef EE_PPCE200ZX_344_ISR_PRI
  EE_mpc5674_set_external_priority(344U, EE_PPCE200ZX_344_ISR_PRI);
#endif /* EE_PPCE200ZX_344_ISR_PRI */

#ifdef EE_PPCE200ZX_345_ISR_PRI
  EE_mpc5674_set_external_priority(345U, EE_PPCE200ZX_345_ISR_PRI);
#endif /* EE_PPCE200ZX_345_ISR_PRI */

#ifdef EE_PPCE200ZX_346_ISR_PRI
  EE_mpc5674_set_external_priority(346U, EE_PPCE200ZX_346_ISR_PRI);
#endif /* EE_PPCE200ZX_346_ISR_PRI */

#ifdef EE_PPCE200ZX_347_ISR_PRI
  EE_mpc5674_set_external_priority(347U, EE_PPCE200ZX_347_ISR_PRI);
#endif /* EE_PPCE200ZX_347_ISR_PRI */

#ifdef EE_PPCE200ZX_348_ISR_PRI
  EE_mpc5674_set_external_priority(348U, EE_PPCE200ZX_348_ISR_PRI);
#endif /* EE_PPCE200ZX_348_ISR_PRI */

#ifdef EE_PPCE200ZX_349_ISR_PRI
  EE_mpc5674_set_external_priority(349U, EE_PPCE200ZX_349_ISR_PRI);
#endif /* EE_PPCE200ZX_349_ISR_PRI */

#ifdef EE_PPCE200ZX_350_ISR_PRI
  EE_mpc5674_set_external_priority(350U, EE_PPCE200ZX_350_ISR_PRI);
#endif /* EE_PPCE200ZX_350_ISR_PRI */

#ifdef EE_PPCE200ZX_351_ISR_PRI
  EE_mpc5674_set_external_priority(351U, EE_PPCE200ZX_351_ISR_PRI);
#endif /* EE_PPCE200ZX_351_ISR_PRI */

#ifdef EE_PPCE200ZX_352_ISR_PRI
  EE_mpc5674_set_external_priority(352U, EE_PPCE200ZX_352_ISR_PRI);
#endif /* EE_PPCE200ZX_352_ISR_PRI */

#ifdef EE_PPCE200ZX_353_ISR_PRI
  EE_mpc5674_set_external_priority(353U, EE_PPCE200ZX_353_ISR_PRI);
#endif /* EE_PPCE200ZX_353_ISR_PRI */

#ifdef EE_PPCE200ZX_354_ISR_PRI
  EE_mpc5674_set_external_priority(354U, EE_PPCE200ZX_354_ISR_PRI);
#endif /* EE_PPCE200ZX_354_ISR_PRI */

#ifdef EE_PPCE200ZX_355_ISR_PRI
  EE_mpc5674_set_external_priority(355U, EE_PPCE200ZX_355_ISR_PRI);
#endif /* EE_PPCE200ZX_355_ISR_PRI */

#ifdef EE_PPCE200ZX_356_ISR_PRI
  EE_mpc5674_set_external_priority(356U, EE_PPCE200ZX_356_ISR_PRI);
#endif /* EE_PPCE200ZX_356_ISR_PRI */

#ifdef EE_PPCE200ZX_357_ISR_PRI
  EE_mpc5674_set_external_priority(357U, EE_PPCE200ZX_357_ISR_PRI);
#endif /* EE_PPCE200ZX_357_ISR_PRI */

#ifdef EE_PPCE200ZX_358_ISR_PRI
  EE_mpc5674_set_external_priority(358U, EE_PPCE200ZX_358_ISR_PRI);
#endif /* EE_PPCE200ZX_358_ISR_PRI */

#ifdef EE_PPCE200ZX_359_ISR_PRI
  EE_mpc5674_set_external_priority(359U, EE_PPCE200ZX_359_ISR_PRI);
#endif /* EE_PPCE200ZX_359_ISR_PRI */

#ifdef EE_PPCE200ZX_360_ISR_PRI
  EE_mpc5674_set_external_priority(360U, EE_PPCE200ZX_360_ISR_PRI);
#endif /* EE_PPCE200ZX_360_ISR_PRI */

#ifdef EE_PPCE200ZX_361_ISR_PRI
  EE_mpc5674_set_external_priority(361U, EE_PPCE200ZX_361_ISR_PRI);
#endif /* EE_PPCE200ZX_361_ISR_PRI */

#ifdef EE_PPCE200ZX_362_ISR_PRI
  EE_mpc5674_set_external_priority(362U, EE_PPCE200ZX_362_ISR_PRI);
#endif /* EE_PPCE200ZX_362_ISR_PRI */

#ifdef EE_PPCE200ZX_363_ISR_PRI
  EE_mpc5674_set_external_priority(363U, EE_PPCE200ZX_363_ISR_PRI);
#endif /* EE_PPCE200ZX_363_ISR_PRI */

#ifdef EE_PPCE200ZX_364_ISR_PRI
  EE_mpc5674_set_external_priority(364U, EE_PPCE200ZX_364_ISR_PRI);
#endif /* EE_PPCE200ZX_364_ISR_PRI */

#ifdef EE_PPCE200ZX_365_ISR_PRI
  EE_mpc5674_set_external_priority(365U, EE_PPCE200ZX_365_ISR_PRI);
#endif /* EE_PPCE200ZX_365_ISR_PRI */

#ifdef EE_PPCE200ZX_366_ISR_PRI
  EE_mpc5674_set_external_priority(366U, EE_PPCE200ZX_366_ISR_PRI);
#endif /* EE_PPCE200ZX_366_ISR_PRI */

#ifdef EE_PPCE200ZX_367_ISR_PRI
  EE_mpc5674_set_external_priority(367U, EE_PPCE200ZX_367_ISR_PRI);
#endif /* EE_PPCE200ZX_367_ISR_PRI */

#ifdef EE_PPCE200ZX_368_ISR_PRI
  EE_mpc5674_set_external_priority(368U, EE_PPCE200ZX_368_ISR_PRI);
#endif /* EE_PPCE200ZX_368_ISR_PRI */

#ifdef EE_PPCE200ZX_369_ISR_PRI
  EE_mpc5674_set_external_priority(369U, EE_PPCE200ZX_369_ISR_PRI);
#endif /* EE_PPCE200ZX_369_ISR_PRI */

#ifdef EE_PPCE200ZX_370_ISR_PRI
  EE_mpc5674_set_external_priority(370U, EE_PPCE200ZX_370_ISR_PRI);
#endif /* EE_PPCE200ZX_370_ISR_PRI */

#ifdef EE_PPCE200ZX_371_ISR_PRI
  EE_mpc5674_set_external_priority(371U, EE_PPCE200ZX_371_ISR_PRI);
#endif /* EE_PPCE200ZX_371_ISR_PRI */

#ifdef EE_PPCE200ZX_372_ISR_PRI
  EE_mpc5674_set_external_priority(372U, EE_PPCE200ZX_372_ISR_PRI);
#endif /* EE_PPCE200ZX_372_ISR_PRI */

#ifdef EE_PPCE200ZX_373_ISR_PRI
  EE_mpc5674_set_external_priority(373U, EE_PPCE200ZX_373_ISR_PRI);
#endif /* EE_PPCE200ZX_373_ISR_PRI */

#ifdef EE_PPCE200ZX_374_ISR_PRI
  EE_mpc5674_set_external_priority(374U, EE_PPCE200ZX_374_ISR_PRI);
#endif /* EE_PPCE200ZX_374_ISR_PRI */

#ifdef EE_PPCE200ZX_375_ISR_PRI
  EE_mpc5674_set_external_priority(375U, EE_PPCE200ZX_375_ISR_PRI);
#endif /* EE_PPCE200ZX_375_ISR_PRI */

#ifdef EE_PPCE200ZX_376_ISR_PRI
  EE_mpc5674_set_external_priority(376U, EE_PPCE200ZX_376_ISR_PRI);
#endif /* EE_PPCE200ZX_376_ISR_PRI */

#ifdef EE_PPCE200ZX_377_ISR_PRI
  EE_mpc5674_set_external_priority(377U, EE_PPCE200ZX_377_ISR_PRI);
#endif /* EE_PPCE200ZX_377_ISR_PRI */

#ifdef EE_PPCE200ZX_378_ISR_PRI
  EE_mpc5674_set_external_priority(378U, EE_PPCE200ZX_378_ISR_PRI);
#endif /* EE_PPCE200ZX_378_ISR_PRI */

#ifdef EE_PPCE200ZX_379_ISR_PRI
  EE_mpc5674_set_external_priority(379U, EE_PPCE200ZX_379_ISR_PRI);
#endif /* EE_PPCE200ZX_379_ISR_PRI */

#ifdef EE_PPCE200ZX_380_ISR_PRI
  EE_mpc5674_set_external_priority(380U, EE_PPCE200ZX_380_ISR_PRI);
#endif /* EE_PPCE200ZX_380_ISR_PRI */

#ifdef EE_PPCE200ZX_381_ISR_PRI
  EE_mpc5674_set_external_priority(381U, EE_PPCE200ZX_381_ISR_PRI);
#endif /* EE_PPCE200ZX_381_ISR_PRI */

#ifdef EE_PPCE200ZX_382_ISR_PRI
  EE_mpc5674_set_external_priority(382U, EE_PPCE200ZX_382_ISR_PRI);
#endif /* EE_PPCE200ZX_382_ISR_PRI */

#ifdef EE_PPCE200ZX_383_ISR_PRI
  EE_mpc5674_set_external_priority(383U, EE_PPCE200ZX_383_ISR_PRI);
#endif /* EE_PPCE200ZX_383_ISR_PRI */

#ifdef EE_PPCE200ZX_384_ISR_PRI
  EE_mpc5674_set_external_priority(384U, EE_PPCE200ZX_384_ISR_PRI);
#endif /* EE_PPCE200ZX_384_ISR_PRI */

#ifdef EE_PPCE200ZX_385_ISR_PRI
  EE_mpc5674_set_external_priority(385U, EE_PPCE200ZX_385_ISR_PRI);
#endif /* EE_PPCE200ZX_385_ISR_PRI */

#ifdef EE_PPCE200ZX_386_ISR_PRI
  EE_mpc5674_set_external_priority(386U, EE_PPCE200ZX_386_ISR_PRI);
#endif /* EE_PPCE200ZX_386_ISR_PRI */

#ifdef EE_PPCE200ZX_387_ISR_PRI
  EE_mpc5674_set_external_priority(387U, EE_PPCE200ZX_387_ISR_PRI);
#endif /* EE_PPCE200ZX_387_ISR_PRI */

#ifdef EE_PPCE200ZX_388_ISR_PRI
  EE_mpc5674_set_external_priority(388U, EE_PPCE200ZX_388_ISR_PRI);
#endif /* EE_PPCE200ZX_388_ISR_PRI */

#ifdef EE_PPCE200ZX_389_ISR_PRI
  EE_mpc5674_set_external_priority(389U, EE_PPCE200ZX_389_ISR_PRI);
#endif /* EE_PPCE200ZX_389_ISR_PRI */

#ifdef EE_PPCE200ZX_390_ISR_PRI
  EE_mpc5674_set_external_priority(390U, EE_PPCE200ZX_390_ISR_PRI);
#endif /* EE_PPCE200ZX_390_ISR_PRI */

#ifdef EE_PPCE200ZX_391_ISR_PRI
  EE_mpc5674_set_external_priority(391U, EE_PPCE200ZX_391_ISR_PRI);
#endif /* EE_PPCE200ZX_391_ISR_PRI */

#ifdef EE_PPCE200ZX_392_ISR_PRI
  EE_mpc5674_set_external_priority(392U, EE_PPCE200ZX_392_ISR_PRI);
#endif /* EE_PPCE200ZX_392_ISR_PRI */

#ifdef EE_PPCE200ZX_393_ISR_PRI
  EE_mpc5674_set_external_priority(393U, EE_PPCE200ZX_393_ISR_PRI);
#endif /* EE_PPCE200ZX_393_ISR_PRI */

#ifdef EE_PPCE200ZX_394_ISR_PRI
  EE_mpc5674_set_external_priority(394U, EE_PPCE200ZX_394_ISR_PRI);
#endif /* EE_PPCE200ZX_394_ISR_PRI */

#ifdef EE_PPCE200ZX_395_ISR_PRI
  EE_mpc5674_set_external_priority(395U, EE_PPCE200ZX_395_ISR_PRI);
#endif /* EE_PPCE200ZX_395_ISR_PRI */

#ifdef EE_PPCE200ZX_396_ISR_PRI
  EE_mpc5674_set_external_priority(396U, EE_PPCE200ZX_396_ISR_PRI);
#endif /* EE_PPCE200ZX_396_ISR_PRI */

#ifdef EE_PPCE200ZX_397_ISR_PRI
  EE_mpc5674_set_external_priority(397U, EE_PPCE200ZX_397_ISR_PRI);
#endif /* EE_PPCE200ZX_397_ISR_PRI */

#ifdef EE_PPCE200ZX_398_ISR_PRI
  EE_mpc5674_set_external_priority(398U, EE_PPCE200ZX_398_ISR_PRI);
#endif /* EE_PPCE200ZX_398_ISR_PRI */

#ifdef EE_PPCE200ZX_399_ISR_PRI
  EE_mpc5674_set_external_priority(399U, EE_PPCE200ZX_399_ISR_PRI);
#endif /* EE_PPCE200ZX_399_ISR_PRI */

#ifdef EE_PPCE200ZX_400_ISR_PRI
  EE_mpc5674_set_external_priority(400U, EE_PPCE200ZX_400_ISR_PRI);
#endif /* EE_PPCE200ZX_400_ISR_PRI */

#ifdef EE_PPCE200ZX_401_ISR_PRI
  EE_mpc5674_set_external_priority(401U, EE_PPCE200ZX_401_ISR_PRI);
#endif /* EE_PPCE200ZX_401_ISR_PRI */

#ifdef EE_PPCE200ZX_402_ISR_PRI
  EE_mpc5674_set_external_priority(402U, EE_PPCE200ZX_402_ISR_PRI);
#endif /* EE_PPCE200ZX_402_ISR_PRI */

#ifdef EE_PPCE200ZX_403_ISR_PRI
  EE_mpc5674_set_external_priority(403U, EE_PPCE200ZX_403_ISR_PRI);
#endif /* EE_PPCE200ZX_403_ISR_PRI */

#ifdef EE_PPCE200ZX_404_ISR_PRI
  EE_mpc5674_set_external_priority(404U, EE_PPCE200ZX_404_ISR_PRI);
#endif /* EE_PPCE200ZX_404_ISR_PRI */

#ifdef EE_PPCE200ZX_405_ISR_PRI
  EE_mpc5674_set_external_priority(405U, EE_PPCE200ZX_405_ISR_PRI);
#endif /* EE_PPCE200ZX_405_ISR_PRI */

#ifdef EE_PPCE200ZX_406_ISR_PRI
  EE_mpc5674_set_external_priority(406U, EE_PPCE200ZX_406_ISR_PRI);
#endif /* EE_PPCE200ZX_406_ISR_PRI */

#ifdef EE_PPCE200ZX_407_ISR_PRI
  EE_mpc5674_set_external_priority(407U, EE_PPCE200ZX_407_ISR_PRI);
#endif /* EE_PPCE200ZX_407_ISR_PRI */

#ifdef EE_PPCE200ZX_408_ISR_PRI
  EE_mpc5674_set_external_priority(408U, EE_PPCE200ZX_408_ISR_PRI);
#endif /* EE_PPCE200ZX_408_ISR_PRI */

#ifdef EE_PPCE200ZX_409_ISR_PRI
  EE_mpc5674_set_external_priority(409U, EE_PPCE200ZX_409_ISR_PRI);
#endif /* EE_PPCE200ZX_409_ISR_PRI */

#ifdef EE_PPCE200ZX_410_ISR_PRI
  EE_mpc5674_set_external_priority(410U, EE_PPCE200ZX_410_ISR_PRI);
#endif /* EE_PPCE200ZX_410_ISR_PRI */

#ifdef EE_PPCE200ZX_411_ISR_PRI
  EE_mpc5674_set_external_priority(411U, EE_PPCE200ZX_411_ISR_PRI);
#endif /* EE_PPCE200ZX_411_ISR_PRI */

#ifdef EE_PPCE200ZX_412_ISR_PRI
  EE_mpc5674_set_external_priority(412U, EE_PPCE200ZX_412_ISR_PRI);
#endif /* EE_PPCE200ZX_412_ISR_PRI */

#ifdef EE_PPCE200ZX_413_ISR_PRI
  EE_mpc5674_set_external_priority(413U, EE_PPCE200ZX_413_ISR_PRI);
#endif /* EE_PPCE200ZX_413_ISR_PRI */

#ifdef EE_PPCE200ZX_414_ISR_PRI
  EE_mpc5674_set_external_priority(414U, EE_PPCE200ZX_414_ISR_PRI);
#endif /* EE_PPCE200ZX_414_ISR_PRI */

#ifdef EE_PPCE200ZX_415_ISR_PRI
  EE_mpc5674_set_external_priority(415U, EE_PPCE200ZX_415_ISR_PRI);
#endif /* EE_PPCE200ZX_415_ISR_PRI */

#ifdef EE_PPCE200ZX_416_ISR_PRI
  EE_mpc5674_set_external_priority(416U, EE_PPCE200ZX_416_ISR_PRI);
#endif /* EE_PPCE200ZX_416_ISR_PRI */

#ifdef EE_PPCE200ZX_417_ISR_PRI
  EE_mpc5674_set_external_priority(417U, EE_PPCE200ZX_417_ISR_PRI);
#endif /* EE_PPCE200ZX_417_ISR_PRI */

#ifdef EE_PPCE200ZX_418_ISR_PRI
  EE_mpc5674_set_external_priority(418U, EE_PPCE200ZX_418_ISR_PRI);
#endif /* EE_PPCE200ZX_418_ISR_PRI */

#ifdef EE_PPCE200ZX_419_ISR_PRI
  EE_mpc5674_set_external_priority(419U, EE_PPCE200ZX_419_ISR_PRI);
#endif /* EE_PPCE200ZX_419_ISR_PRI */

#ifdef EE_PPCE200ZX_420_ISR_PRI
  EE_mpc5674_set_external_priority(420U, EE_PPCE200ZX_420_ISR_PRI);
#endif /* EE_PPCE200ZX_420_ISR_PRI */

#ifdef EE_PPCE200ZX_421_ISR_PRI
  EE_mpc5674_set_external_priority(421U, EE_PPCE200ZX_421_ISR_PRI);
#endif /* EE_PPCE200ZX_421_ISR_PRI */

#ifdef EE_PPCE200ZX_422_ISR_PRI
  EE_mpc5674_set_external_priority(422U, EE_PPCE200ZX_422_ISR_PRI);
#endif /* EE_PPCE200ZX_422_ISR_PRI */

#ifdef EE_PPCE200ZX_423_ISR_PRI
  EE_mpc5674_set_external_priority(423U, EE_PPCE200ZX_423_ISR_PRI);
#endif /* EE_PPCE200ZX_423_ISR_PRI */

#ifdef EE_PPCE200ZX_424_ISR_PRI
  EE_mpc5674_set_external_priority(424U, EE_PPCE200ZX_424_ISR_PRI);
#endif /* EE_PPCE200ZX_424_ISR_PRI */

#ifdef EE_PPCE200ZX_425_ISR_PRI
  EE_mpc5674_set_external_priority(425U, EE_PPCE200ZX_425_ISR_PRI);
#endif /* EE_PPCE200ZX_425_ISR_PRI */

#ifdef EE_PPCE200ZX_426_ISR_PRI
  EE_mpc5674_set_external_priority(426U, EE_PPCE200ZX_426_ISR_PRI);
#endif /* EE_PPCE200ZX_426_ISR_PRI */

#ifdef EE_PPCE200ZX_427_ISR_PRI
  EE_mpc5674_set_external_priority(427U, EE_PPCE200ZX_427_ISR_PRI);
#endif /* EE_PPCE200ZX_427_ISR_PRI */

#ifdef EE_PPCE200ZX_428_ISR_PRI
  EE_mpc5674_set_external_priority(428U, EE_PPCE200ZX_428_ISR_PRI);
#endif /* EE_PPCE200ZX_428_ISR_PRI */

#ifdef EE_PPCE200ZX_429_ISR_PRI
  EE_mpc5674_set_external_priority(429U, EE_PPCE200ZX_429_ISR_PRI);
#endif /* EE_PPCE200ZX_429_ISR_PRI */

#ifdef EE_PPCE200ZX_430_ISR_PRI
  EE_mpc5674_set_external_priority(430U, EE_PPCE200ZX_430_ISR_PRI);
#endif /* EE_PPCE200ZX_430_ISR_PRI */

#ifdef EE_PPCE200ZX_431_ISR_PRI
  EE_mpc5674_set_external_priority(431U, EE_PPCE200ZX_431_ISR_PRI);
#endif /* EE_PPCE200ZX_431_ISR_PRI */

#ifdef EE_PPCE200ZX_432_ISR_PRI
  EE_mpc5674_set_external_priority(432U, EE_PPCE200ZX_432_ISR_PRI);
#endif /* EE_PPCE200ZX_432_ISR_PRI */

#ifdef EE_PPCE200ZX_433_ISR_PRI
  EE_mpc5674_set_external_priority(433U, EE_PPCE200ZX_433_ISR_PRI);
#endif /* EE_PPCE200ZX_433_ISR_PRI */

#ifdef EE_PPCE200ZX_434_ISR_PRI
  EE_mpc5674_set_external_priority(434U, EE_PPCE200ZX_434_ISR_PRI);
#endif /* EE_PPCE200ZX_434_ISR_PRI */

#ifdef EE_PPCE200ZX_435_ISR_PRI
  EE_mpc5674_set_external_priority(435U, EE_PPCE200ZX_435_ISR_PRI);
#endif /* EE_PPCE200ZX_435_ISR_PRI */

#ifdef EE_PPCE200ZX_436_ISR_PRI
  EE_mpc5674_set_external_priority(436U, EE_PPCE200ZX_436_ISR_PRI);
#endif /* EE_PPCE200ZX_436_ISR_PRI */

#ifdef EE_PPCE200ZX_437_ISR_PRI
  EE_mpc5674_set_external_priority(437U, EE_PPCE200ZX_437_ISR_PRI);
#endif /* EE_PPCE200ZX_437_ISR_PRI */

#ifdef EE_PPCE200ZX_438_ISR_PRI
  EE_mpc5674_set_external_priority(438U, EE_PPCE200ZX_438_ISR_PRI);
#endif /* EE_PPCE200ZX_438_ISR_PRI */

#ifdef EE_PPCE200ZX_439_ISR_PRI
  EE_mpc5674_set_external_priority(439U, EE_PPCE200ZX_439_ISR_PRI);
#endif /* EE_PPCE200ZX_439_ISR_PRI */

#ifdef EE_PPCE200ZX_440_ISR_PRI
  EE_mpc5674_set_external_priority(440U, EE_PPCE200ZX_440_ISR_PRI);
#endif /* EE_PPCE200ZX_440_ISR_PRI */

#ifdef EE_PPCE200ZX_441_ISR_PRI
  EE_mpc5674_set_external_priority(441U, EE_PPCE200ZX_441_ISR_PRI);
#endif /* EE_PPCE200ZX_441_ISR_PRI */

#ifdef EE_PPCE200ZX_442_ISR_PRI
  EE_mpc5674_set_external_priority(442U, EE_PPCE200ZX_442_ISR_PRI);
#endif /* EE_PPCE200ZX_442_ISR_PRI */

#ifdef EE_PPCE200ZX_443_ISR_PRI
  EE_mpc5674_set_external_priority(443U, EE_PPCE200ZX_443_ISR_PRI);
#endif /* EE_PPCE200ZX_443_ISR_PRI */

#ifdef EE_PPCE200ZX_444_ISR_PRI
  EE_mpc5674_set_external_priority(444U, EE_PPCE200ZX_444_ISR_PRI);
#endif /* EE_PPCE200ZX_444_ISR_PRI */

#ifdef EE_PPCE200ZX_445_ISR_PRI
  EE_mpc5674_set_external_priority(445U, EE_PPCE200ZX_445_ISR_PRI);
#endif /* EE_PPCE200ZX_445_ISR_PRI */

#ifdef EE_PPCE200ZX_446_ISR_PRI
  EE_mpc5674_set_external_priority(446U, EE_PPCE200ZX_446_ISR_PRI);
#endif /* EE_PPCE200ZX_446_ISR_PRI */

#ifdef EE_PPCE200ZX_447_ISR_PRI
  EE_mpc5674_set_external_priority(447U, EE_PPCE200ZX_447_ISR_PRI);
#endif /* EE_PPCE200ZX_447_ISR_PRI */

#ifdef EE_PPCE200ZX_448_ISR_PRI
  EE_mpc5674_set_external_priority(448U, EE_PPCE200ZX_448_ISR_PRI);
#endif /* EE_PPCE200ZX_448_ISR_PRI */

#ifdef EE_PPCE200ZX_449_ISR_PRI
  EE_mpc5674_set_external_priority(449U, EE_PPCE200ZX_449_ISR_PRI);
#endif /* EE_PPCE200ZX_449_ISR_PRI */

#ifdef EE_PPCE200ZX_450_ISR_PRI
  EE_mpc5674_set_external_priority(450U, EE_PPCE200ZX_450_ISR_PRI);
#endif /* EE_PPCE200ZX_450_ISR_PRI */

#ifdef EE_PPCE200ZX_451_ISR_PRI
  EE_mpc5674_set_external_priority(451U, EE_PPCE200ZX_451_ISR_PRI);
#endif /* EE_PPCE200ZX_451_ISR_PRI */

#ifdef EE_PPCE200ZX_452_ISR_PRI
  EE_mpc5674_set_external_priority(452U, EE_PPCE200ZX_452_ISR_PRI);
#endif /* EE_PPCE200ZX_452_ISR_PRI */

#ifdef EE_PPCE200ZX_453_ISR_PRI
  EE_mpc5674_set_external_priority(453U, EE_PPCE200ZX_453_ISR_PRI);
#endif /* EE_PPCE200ZX_453_ISR_PRI */

#ifdef EE_PPCE200ZX_454_ISR_PRI
  EE_mpc5674_set_external_priority(454U, EE_PPCE200ZX_454_ISR_PRI);
#endif /* EE_PPCE200ZX_454_ISR_PRI */

#ifdef EE_PPCE200ZX_455_ISR_PRI
  EE_mpc5674_set_external_priority(455U, EE_PPCE200ZX_455_ISR_PRI);
#endif /* EE_PPCE200ZX_455_ISR_PRI */

#ifdef EE_PPCE200ZX_456_ISR_PRI
  EE_mpc5674_set_external_priority(456U, EE_PPCE200ZX_456_ISR_PRI);
#endif /* EE_PPCE200ZX_456_ISR_PRI */

#ifdef EE_PPCE200ZX_457_ISR_PRI
  EE_mpc5674_set_external_priority(457U, EE_PPCE200ZX_457_ISR_PRI);
#endif /* EE_PPCE200ZX_457_ISR_PRI */

#ifdef EE_PPCE200ZX_458_ISR_PRI
  EE_mpc5674_set_external_priority(458U, EE_PPCE200ZX_458_ISR_PRI);
#endif /* EE_PPCE200ZX_458_ISR_PRI */

#ifdef EE_PPCE200ZX_459_ISR_PRI
  EE_mpc5674_set_external_priority(459U, EE_PPCE200ZX_459_ISR_PRI);
#endif /* EE_PPCE200ZX_459_ISR_PRI */

#ifdef EE_PPCE200ZX_460_ISR_PRI
  EE_mpc5674_set_external_priority(460U, EE_PPCE200ZX_460_ISR_PRI);
#endif /* EE_PPCE200ZX_460_ISR_PRI */

#ifdef EE_PPCE200ZX_461_ISR_PRI
  EE_mpc5674_set_external_priority(461U, EE_PPCE200ZX_461_ISR_PRI);
#endif /* EE_PPCE200ZX_461_ISR_PRI */

#ifdef EE_PPCE200ZX_462_ISR_PRI
  EE_mpc5674_set_external_priority(462U, EE_PPCE200ZX_462_ISR_PRI);
#endif /* EE_PPCE200ZX_462_ISR_PRI */

#ifdef EE_PPCE200ZX_463_ISR_PRI
  EE_mpc5674_set_external_priority(463U, EE_PPCE200ZX_463_ISR_PRI);
#endif /* EE_PPCE200ZX_463_ISR_PRI */

#ifdef EE_PPCE200ZX_464_ISR_PRI
  EE_mpc5674_set_external_priority(464U, EE_PPCE200ZX_464_ISR_PRI);
#endif /* EE_PPCE200ZX_464_ISR_PRI */

#ifdef EE_PPCE200ZX_465_ISR_PRI
  EE_mpc5674_set_external_priority(465U, EE_PPCE200ZX_465_ISR_PRI);
#endif /* EE_PPCE200ZX_465_ISR_PRI */

#ifdef EE_PPCE200ZX_466_ISR_PRI
  EE_mpc5674_set_external_priority(466U, EE_PPCE200ZX_466_ISR_PRI);
#endif /* EE_PPCE200ZX_466_ISR_PRI */

#ifdef EE_PPCE200ZX_467_ISR_PRI
  EE_mpc5674_set_external_priority(467U, EE_PPCE200ZX_467_ISR_PRI);
#endif /* EE_PPCE200ZX_467_ISR_PRI */

#ifdef EE_PPCE200ZX_468_ISR_PRI
  EE_mpc5674_set_external_priority(468U, EE_PPCE200ZX_468_ISR_PRI);
#endif /* EE_PPCE200ZX_468_ISR_PRI */

#ifdef EE_PPCE200ZX_469_ISR_PRI
  EE_mpc5674_set_external_priority(469U, EE_PPCE200ZX_469_ISR_PRI);
#endif /* EE_PPCE200ZX_469_ISR_PRI */

#ifdef EE_PPCE200ZX_470_ISR_PRI
  EE_mpc5674_set_external_priority(470U, EE_PPCE200ZX_470_ISR_PRI);
#endif /* EE_PPCE200ZX_470_ISR_PRI */

#ifdef EE_PPCE200ZX_471_ISR_PRI
  EE_mpc5674_set_external_priority(471U, EE_PPCE200ZX_471_ISR_PRI);
#endif /* EE_PPCE200ZX_471_ISR_PRI */

#ifdef EE_PPCE200ZX_472_ISR_PRI
  EE_mpc5674_set_external_priority(472U, EE_PPCE200ZX_472_ISR_PRI);
#endif /* EE_PPCE200ZX_472_ISR_PRI */

#ifdef EE_PPCE200ZX_473_ISR_PRI
  EE_mpc5674_set_external_priority(473U, EE_PPCE200ZX_473_ISR_PRI);
#endif /* EE_PPCE200ZX_473_ISR_PRI */

}


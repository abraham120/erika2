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

/** @file   Cfg.h
 *  @brief  Drivers Configuration Utilities
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#ifndef CFG_H
#define CFG_H

/* Macro for Big Endian Bit Remapping for 16/32 bit registers */

/* Big Endian Bit Remapping (for 8 bit register) */
#define   AS_8_BIT0         (1U << 7U)
#define   AS_8_BIT1         (1U << 6U)
#define   AS_8_BIT2         (1U << 5U)
#define   AS_8_BIT3         (1U << 4U)
#define   AS_8_BIT4         (1U << 3U)
#define   AS_8_BIT5         (1U << 2U)
#define   AS_8_BIT6         (1U << 1U)
#define   AS_8_BIT7         (1U)
#define   AS_8_NOBIT        0x00U


/* Big Endian Bit Remapping (for 16 bit register) */
#define   AS_16_BIT0        (1U << 15U)
#define   AS_16_BIT1        (1U << 14U)
#define   AS_16_BIT2        (1U << 13U)
#define   AS_16_BIT3        (1U << 12U)
#define   AS_16_BIT4        (1U << 11U)
#define   AS_16_BIT5        (1U << 10U)
#define   AS_16_BIT6        (1U << 9U)
#define   AS_16_BIT7        (1U << 8U)
#define   AS_16_BIT8        (1U << 7U)
#define   AS_16_BIT9        (1U << 6U)
#define   AS_16_BIT10       (1U << 5U)
#define   AS_16_BIT11       (1U << 4U)
#define   AS_16_BIT12       (1U << 3U)
#define   AS_16_BIT13       (1U << 2U)
#define   AS_16_BIT14       (1U << 1U)
#define   AS_16_BIT15       (1U)
#define   AS_16_NOBIT       0x0000U

/* Big Endian Bit Remapping (for 32 bit register) */
#define   AS_32_BIT0        (1U << 31U)
#define   AS_32_BIT1        (1U << 30U)
#define   AS_32_BIT2        (1U << 29U)
#define   AS_32_BIT3        (1U << 28U)
#define   AS_32_BIT4        (1U << 27U)
#define   AS_32_BIT5        (1U << 26U)
#define   AS_32_BIT6        (1U << 25U)
#define   AS_32_BIT7        (1U << 24U)
#define   AS_32_BIT8        (1U << 23U)
#define   AS_32_BIT9        (1U << 22U)
#define   AS_32_BIT10       (1U << 21U)
#define   AS_32_BIT11       (1U << 20U)
#define   AS_32_BIT12       (1U << 19U)
#define   AS_32_BIT13       (1U << 18U)
#define   AS_32_BIT14       (1U << 17U)
#define   AS_32_BIT15       (1U << 16U)
#define   AS_32_BIT16       (1U << 15U)
#define   AS_32_BIT17       (1U << 14U)
#define   AS_32_BIT18       (1U << 13U)
#define   AS_32_BIT19       (1U << 12U)
#define   AS_32_BIT20       (1U << 11U)
#define   AS_32_BIT21       (1U << 10U)
#define   AS_32_BIT22       (1U << 9U)
#define   AS_32_BIT23       (1U << 8U)
#define   AS_32_BIT24       (1U << 7U)
#define   AS_32_BIT25       (1U << 6U)
#define   AS_32_BIT26       (1U << 5U)
#define   AS_32_BIT27       (1U << 4U)
#define   AS_32_BIT28       (1U << 3U)
#define   AS_32_BIT29       (1U << 2U)
#define   AS_32_BIT30       (1U << 1U)
#define   AS_32_BIT31       (1U)
#define   AS_32_NOBIT       0x00000000U

/* Port IDs */
#define AS_PORT_A           0U  /**< Port A   */
#define AS_PORT_B           1U  /**< Port B   */
#define AS_PORT_C           2U  /**< Port C   */
#define AS_PORT_D           3U  /**< Port D   */
#define AS_PORT_E           4U  /**< Port E   */
#define AS_PORT_F           5U  /**< Port F   */
#define AS_PORT_G           6U  /**< Port G   */
#define AS_PORT_H           7U  /**< Port H   */
#define AS_PORT_I           8U  /**< Port I   */

/* At Each Pin Is Associated Corresponding PCR value as ID */

#define AS_PORT_A_PIN_0     0U    /**< Port A - Pin 0 */
#define AS_PORT_A_PIN_1     1U    /**< Port A - Pin 1 */
#define AS_PORT_A_PIN_2     2U    /**< Port A - Pin 2 */
#define AS_PORT_A_PIN_3     3U    /**< Port A - Pin 3 */
#define AS_PORT_A_PIN_4     4U    /**< Port A - Pin 4 */
#define AS_PORT_A_PIN_5     5U    /**< Port A - Pin 5 */
#define AS_PORT_A_PIN_6     6U    /**< Port A - Pin 6 */
#define AS_PORT_A_PIN_7     7U    /**< Port A - Pin 7 */
#define AS_PORT_A_PIN_8     8U    /**< Port A - Pin 8 */
#define AS_PORT_A_PIN_9     9U    /**< Port A - Pin 9 */
#define AS_PORT_A_PIN_10    10U   /**< Port A - Pin 10 */
#define AS_PORT_A_PIN_11    11U   /**< Port A - Pin 11 */
#define AS_PORT_A_PIN_12    12U   /**< Port A - Pin 12 */
#define AS_PORT_A_PIN_13    13U   /**< Port A - Pin 13 */
#define AS_PORT_A_PIN_14    14U   /**< Port A - Pin 14 */
#define AS_PORT_A_PIN_15    15U   /**< Port A - Pin 15 */

#define AS_PORT_B_PIN_0     16U   /**< Port B - Pin 0 */
#define AS_PORT_B_PIN_1     17U   /**< Port B - Pin 1 */
#define AS_PORT_B_PIN_2     18U   /**< Port B - Pin 2 */
#define AS_PORT_B_PIN_3     19U   /**< Port B - Pin 3 */
#define AS_PORT_B_PIN_4     20U   /**< Port B - Pin 4 */
#define AS_PORT_B_PIN_5     21U   /**< Port B - Pin 5 */
#define AS_PORT_B_PIN_6     22U   /**< Port B - Pin 6 */
#define AS_PORT_B_PIN_7     23U   /**< Port B - Pin 7 */
#define AS_PORT_B_PIN_8     24U   /**< Port B - Pin 8 */
#define AS_PORT_B_PIN_9     25U   /**< Port B - Pin 9 */
#define AS_PORT_B_PIN_10    26U   /**< Port B - Pin 10 */
#define AS_PORT_B_PIN_11    27U   /**< Port B - Pin 11 */
#define AS_PORT_B_PIN_12    28U   /**< Port B - Pin 12 */
#define AS_PORT_B_PIN_13    29U   /**< Port B - Pin 13 */
#define AS_PORT_B_PIN_14    30U   /**< Port B - Pin 14 */
#define AS_PORT_B_PIN_15    31U   /**< Port B - Pin 15 */

#define AS_PORT_C_PIN_0     32U   /**< Port C - Pin 0 */
#define AS_PORT_C_PIN_1     33U   /**< Port C - Pin 1 */
#define AS_PORT_C_PIN_2     34U   /**< Port C - Pin 2 */
#define AS_PORT_C_PIN_3     35U   /**< Port C - Pin 3 */
#define AS_PORT_C_PIN_4     36U   /**< Port C - Pin 4 */
#define AS_PORT_C_PIN_5     37U   /**< Port C - Pin 5 */
#define AS_PORT_C_PIN_6     38U   /**< Port C - Pin 6 */
#define AS_PORT_C_PIN_7     39U   /**< Port C - Pin 7 */
#define AS_PORT_C_PIN_8     40U   /**< Port C - Pin 8 */
#define AS_PORT_C_PIN_9     41U   /**< Port C - Pin 9 */
#define AS_PORT_C_PIN_10    42U   /**< Port C - Pin 10 */
#define AS_PORT_C_PIN_11    43U   /**< Port C - Pin 11 */
#define AS_PORT_C_PIN_12    44U   /**< Port C - Pin 12 */
#define AS_PORT_C_PIN_13    45U   /**< Port C - Pin 13 */
#define AS_PORT_C_PIN_14    46U   /**< Port C - Pin 14 */
#define AS_PORT_C_PIN_15    47U   /**< Port C - Pin 15 */

#define AS_PORT_D_PIN_0     48U   /**< Port D - Pin 0 */
#define AS_PORT_D_PIN_1     49U   /**< Port D - Pin 1 */
#define AS_PORT_D_PIN_2     50U   /**< Port D - Pin 2 */
#define AS_PORT_D_PIN_3     51U   /**< Port D - Pin 3 */
#define AS_PORT_D_PIN_4     52U   /**< Port D - Pin 4 */
#define AS_PORT_D_PIN_5     53U   /**< Port D - Pin 5 */
#define AS_PORT_D_PIN_6     54U   /**< Port D - Pin 6 */
#define AS_PORT_D_PIN_7     55U   /**< Port D - Pin 7 */
#define AS_PORT_D_PIN_8     56U   /**< Port D - Pin 8 */
#define AS_PORT_D_PIN_9     57U   /**< Port D - Pin 9 */
#define AS_PORT_D_PIN_10    58U   /**< Port D - Pin 10 */
#define AS_PORT_D_PIN_11    59U   /**< Port D - Pin 11 */
#define AS_PORT_D_PIN_12    60U   /**< Port D - Pin 12 */
#define AS_PORT_D_PIN_14    62U   /**< Port D - Pin 14 */

#define AS_PORT_E_PIN_0     64U   /**< Port E - Pin 0 */
#define AS_PORT_E_PIN_2     66U   /**< Port E - Pin 2 */
#define AS_PORT_E_PIN_4     68U   /**< Port E - Pin 4 */
#define AS_PORT_E_PIN_5     69U   /**< Port E - Pin 5 */
#define AS_PORT_E_PIN_6     70U   /**< Port E - Pin 6 */
#define AS_PORT_E_PIN_7     71U   /**< Port E - Pin 7 */
#define AS_PORT_E_PIN_9     73U   /**< Port E - Pin 9 */
#define AS_PORT_E_PIN_10    74U   /**< Port E - Pin 10 */
#define AS_PORT_E_PIN_11    75U   /**< Port E - Pin 11 */
#define AS_PORT_E_PIN_12    76U   /**< Port E - Pin 12 */
#define AS_PORT_E_PIN_13    77U   /**< Port E - Pin 13 */
#define AS_PORT_E_PIN_14    78U   /**< Port E - Pin 14 */
#define AS_PORT_E_PIN_15    79U   /**< Port E - Pin 15 */

#define AS_PORT_F_PIN_0     80U   /**< Port F - Pin 0 */
#define AS_PORT_F_PIN_3     83U   /**< Port F - Pin 3 */
#define AS_PORT_F_PIN_4     84U   /**< Port F - Pin 4 */
#define AS_PORT_F_PIN_5     85U   /**< Port F - Pin 5 */
#define AS_PORT_F_PIN_6     86U   /**< Port F - Pin 6 */
#define AS_PORT_F_PIN_7     87U   /**< Port F - Pin 7 */
#define AS_PORT_F_PIN_8     88U   /**< Port F - Pin 8 */
#define AS_PORT_F_PIN_9     89U   /**< Port F - Pin 9 */
#define AS_PORT_F_PIN_10    90U   /**< Port F - Pin 10 */
#define AS_PORT_F_PIN_11    91U   /**< Port F - Pin 11 */
#define AS_PORT_F_PIN_12    92U   /**< Port F - Pin 12 */
#define AS_PORT_F_PIN_13    93U   /**< Port F - Pin 13 */
#define AS_PORT_F_PIN_14    94U   /**< Port F - Pin 14 */
#define AS_PORT_F_PIN_15    95U   /**< Port F - Pin 15 */

#define AS_PORT_G_PIN_2     98U   /**< Port G - Pin 2 */
#define AS_PORT_G_PIN_3     99U   /**< Port G - Pin 3 */
#define AS_PORT_G_PIN_4     100U  /**< Port G - Pin 4 */
#define AS_PORT_G_PIN_5     101U  /**< Port G - Pin 5 */
#define AS_PORT_G_PIN_6     102U  /**< Port G - Pin 6 */
#define AS_PORT_G_PIN_7     103U  /**< Port G - Pin 7 */
#define AS_PORT_G_PIN_8     104U  /**< Port G - Pin 8 */
#define AS_PORT_G_PIN_9     105U  /**< Port G - Pin 9 */
#define AS_PORT_G_PIN_10    106U  /**< Port G - Pin 10 */
#define AS_PORT_G_PIN_11    107U  /**< Port G - Pin 11 */
#define AS_PORT_G_PIN_12    108U  /**< Port G - Pin 12 */
#define AS_PORT_G_PIN_13    109U  /**< Port G - Pin 13 */
#define AS_PORT_G_PIN_14    110U  /**< Port G - Pin 14 */
#define AS_PORT_G_PIN_15    111U  /**< Port G - Pin 15 */

#define AS_PORT_H_PIN_0     112U  /**< Port H - Pin 0 */
#define AS_PORT_H_PIN_1     113U  /**< Port H - Pin 1 */
#define AS_PORT_H_PIN_2     114U  /**< Port H - Pin 2 */
#define AS_PORT_H_PIN_3     115U  /**< Port H - Pin 3 */
#define AS_PORT_H_PIN_4     116U  /**< Port H - Pin 4 */
#define AS_PORT_H_PIN_5     117U  /**< Port H - Pin 5 */
#define AS_PORT_H_PIN_6     118U  /**< Port H - Pin 6 */
#define AS_PORT_H_PIN_7     119U  /**< Port H - Pin 7 */

#define AS_PORT_I_PIN_0     128U  /**< Port I - Pin 0 */
#define AS_PORT_I_PIN_1     129U  /**< Port I - Pin 1 */
#define AS_PORT_I_PIN_2     130U  /**< Port I - Pin 2 */
#define AS_PORT_I_PIN_3     131U  /**< Port I - Pin 3 */

#endif /* CFG_H */

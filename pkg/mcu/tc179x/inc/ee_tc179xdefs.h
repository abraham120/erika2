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
#ifndef __INCLUDE_EE_TC179x_DEFS_H__
#define __INCLUDE_EE_TC179x_DEFS_H__

#include "mcu/tc179x/inc/ee_scu.h"
#include "mcu/tc179x/inc/ee_stm.h"

/* Support macros for stringification*/
#undef __XS
#undef __SS
#define __XS(x) # x
#define __SS(x) __XS(x)


/* Used to access memory mapped peripheral registers. */
#ifdef __GNUC__

/* Define register mapped global variables.
 *
 * Example:
 * 
 * EE_TC179x_MAP_REGISTER(PLL_CLC, EE_UREG, 0xF0000044) becomes a global
 * variable of name 'EE_tc179x_pll_clc' and type 'volatile EE_UREG'
 * and a global variable 'EE_tc1_pll_clc_nv' of type 'EE_UREG'. */
#define EE_TC179x_MAP_REGISTER(name, type, addr)                        \
    asm (                                                               \
        ".section .sfr \n"                                              \
        ".globl EE_tc179x_" __SS(name) " \n"                            \
        ".set   EE_tc179x_" __SS(name) ", " __SS(addr) "\n"             \
        ".type  EE_tc179x_" __SS(name) ", @object \n"                   \
        "\n"                                                            \
        ".globl EE_tc179x_" __SS(name) "_nv \n"                         \
        ".set   EE_tc179x_" __SS(name) "_nv, " __SS(addr) "\n"          \
        ".type  EE_tc179x_" __SS(name) "_nv, @object \n"                \
        ".previous \n");                                                \
    extern volatile type EE_tc179x_ ## name;                            \
    extern type EE_tc179x_ ## name ## _nv;

#else

#error Compiler not supported.

#endif


/*

  FIXME:
  We only need a fraction of these registers to get the system going. 
  Therefore, any generically typed (EE_UREG) register mapped below 
  can be removed in fact. This also keeps the porting overhead for 
  other TriCore versions at a minimum. 

*/


/* SCU Register Address Map 
 *
 * NOTE: Only the registers we explicitly make use of are strictly
 *       typed. All others can still be accessed but could safely 
 *       be omitted.
 */

#ifdef __TC1796__

/* WDT and SCU registers */
EE_TC179x_MAP_REGISTER(scu_base,    EE_UREG,     0xF0000000);
EE_TC179x_MAP_REGISTER(scu_id,      EE_UREG,     0xF0000008);
EE_TC179x_MAP_REGISTER(scu_sclkfdr, EE_UREG,     0xF000000C);
EE_TC179x_MAP_REGISTER(rst_req,     EE_UREG,     0xF0000010);
EE_TC179x_MAP_REGISTER(rst_sr,      EE_UREG,     0xF0000014);
EE_TC179x_MAP_REGISTER(osc_con,     EE_OSC_CON,  0xF0000018);
EE_TC179x_MAP_REGISTER(wdt_con0,    EE_WDT_CON0, 0xF0000020);
EE_TC179x_MAP_REGISTER(wdt_con1,    EE_WDT_CON1, 0xF0000024);
EE_TC179x_MAP_REGISTER(wdt_sr,      EE_UREG,     0xF0000028);
EE_TC179x_MAP_REGISTER(nmi_sr,      EE_UREG,     0xF000002C);
EE_TC179x_MAP_REGISTER(pmg_scr,     EE_UREG,     0xF0000034);
EE_TC179x_MAP_REGISTER(scu_sclir,   EE_UREG,     0xF0000038);
EE_TC179x_MAP_REGISTER(pll_clc,     EE_PLL_CLC,  0xF0000040);
EE_TC179x_MAP_REGISTER(scu_emsr,    EE_UREG,     0xF0000044);
EE_TC179x_MAP_REGISTER(scu_tccon,   EE_UREG,     0xF0000048);
EE_TC179x_MAP_REGISTER(scu_con,     EE_UREG,     0xF0000050);
EE_TC179x_MAP_REGISTER(scu_stat,    EE_UREG,     0xF0000054);
EE_TC179x_MAP_REGISTER(scu_tclr0,   EE_UREG,     0xF0000058);
EE_TC179x_MAP_REGISTER(scu_tclr1,   EE_UREG,     0xF000005C);
EE_TC179x_MAP_REGISTER(scu_manid,   EE_UREG,     0xF0000070);
EE_TC179x_MAP_REGISTER(scu_chipid,  EE_UREG,     0xF0000074);
EE_TC179x_MAP_REGISTER(scu_rtid,    EE_UREG,     0xF0000078);
EE_TC179x_MAP_REGISTER(scu_eicr0,   EE_UREG,     0xF0000080);
EE_TC179x_MAP_REGISTER(scu_eicr1,   EE_UREG,     0xF0000084);
EE_TC179x_MAP_REGISTER(scu_eifr,    EE_UREG,     0xF0000088);
EE_TC179x_MAP_REGISTER(scu_fmr,     EE_UREG,     0xF000008C);
EE_TC179x_MAP_REGISTER(scu_pdrr,    EE_UREG,     0xF0000090);
EE_TC179x_MAP_REGISTER(scu_igcr0,   EE_UREG,     0xF0000094);
EE_TC179x_MAP_REGISTER(scu_igcr1,   EE_UREG,     0xF0000098);
EE_TC179x_MAP_REGISTER(scu_tgadc0,  EE_UREG,     0xF000009C);
EE_TC179x_MAP_REGISTER(scu_tgadc1,  EE_UREG,     0xF00000A0);
EE_TC179x_MAP_REGISTER(scu_ptcon,   EE_UREG,     0xF00000B0);
EE_TC179x_MAP_REGISTER(scu_ptdat0,  EE_UREG,     0xF00000B4);
EE_TC179x_MAP_REGISTER(scu_ptdat1,  EE_UREG,     0xF00000B8);
EE_TC179x_MAP_REGISTER(scu_ptdat2,  EE_UREG,     0xF00000BC);
EE_TC179x_MAP_REGISTER(scu_ptdat3,  EE_UREG,     0xF00000C0);
EE_TC179x_MAP_REGISTER(scu_petcr,   EE_UREG,     0xF00000D0);
EE_TC179x_MAP_REGISTER(scu_petsr,   EE_UREG,     0xF00000D4);

/* STM registers */
EE_TC179x_MAP_REGISTER(stm_base,    EE_UREG,     0xF0000200);
EE_TC179x_MAP_REGISTER(stm_clc,     EE_STM_CLC,  0xF0000200);
EE_TC179x_MAP_REGISTER(stm_tim0,    EE_STM_TIM0, 0xF0000210);
EE_TC179x_MAP_REGISTER(stm_tim1,    EE_UREG,     0xF0000214);
EE_TC179x_MAP_REGISTER(stm_tim2,    EE_UREG,     0xF0000218);
EE_TC179x_MAP_REGISTER(stm_tim3,    EE_UREG,     0xF000021C);
EE_TC179x_MAP_REGISTER(stm_tim4,    EE_UREG ,    0xF0000220);
EE_TC179x_MAP_REGISTER(stm_tim5,    EE_UREG,     0xF0000224);
EE_TC179x_MAP_REGISTER(stm_tim6,    EE_STM_TIM6, 0xF0000228);
EE_TC179x_MAP_REGISTER(stm_cap,     EE_STM_CAP,  0xF000022C);
EE_TC179x_MAP_REGISTER(stm_cmp0,    EE_STM_CMP0, 0xF0000230);
EE_TC179x_MAP_REGISTER(stm_cmp1,    EE_STM_CMP1, 0xF0000234);
EE_TC179x_MAP_REGISTER(stm_cmcon,   EE_STM_CMCON,0xF0000238);
EE_TC179x_MAP_REGISTER(stm_icr,     EE_STM_ICR,  0xF000023c);
EE_TC179x_MAP_REGISTER(stm_isrr,    EE_STM_ISRR, 0xF0000240);
EE_TC179x_MAP_REGISTER(stm_src1,    EE_STM_SRC1, 0xF00002F8); /* no mistake */
EE_TC179x_MAP_REGISTER(stm_src0,    EE_STM_SRC0, 0xF00002FC);

#else 

#error MCU not supported.

#endif  


#endif 

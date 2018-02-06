/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/** @file	Hardware.h
 *  @brief	Hardware Abstraction Header File.
 *
 *  This file contains all the functions and macros for abstraction of hardware
 *  for Renesas RX200 (r5f5210x) and CCRX compiler.
 *
 *  @author	Gianluca Franchino
 *  @date	2012
 */

#ifndef	__HARDWARE_H__
#define	__HARDWARE_H__

/*
 * MACROS
 */
#define	HW_REG_SZ	0x00000004			/**< Register Size in Bytes   */
#define	HW_REG_SZ_S	0x00000002			/**< Register Size Shift Bits */

/* I/O and PORT related registers. */
#define HW_PWPR_B0WI_SET	0x80		/**< Set B0WI bit in the PWPR reg.  */
#define HW_PWPR_B0WI_CLEAR	0x00		/**< Clear B0WI bit in the PWPR reg.*/
#define HW_PWPR_PFSWE_SET	0x40		/**< Set PFSWE bit in the PWPR reg. */
#define HW_PWPR_PFSWE_CLEAR	0x00		/**< Clear PFSWE bi in the PWPR reg.*/
#define HW_PFS_ASEL_SET		0x80		/**< Set ASEL bit in the PFS reg. 	*/
#define HW_PFS_ISEL_SET		0x40		/**< Set ISEL bit in the PFS reg. 	*/

#define HW_IO_PDR_OFFSET	0x00000000	/**< I/O PORT PDR registers offset  */
#define HW_IO_PODR_OFFSET	0x00000020	/**< I/O PORT PODR registers offset */
#define HW_IO_PIDR_OFFSET 	0x00000040	/**< I/O PORT PIDR registers offset */
#define HW_IO_PMR_OFFSET 	0x00000060	/**< I/O PORT PMR registers offset  */
#define HW_IO_PCR_OFFSET 	0x000000C0	/**< I/O PORT PCR registers offset  */
#define HW_IO_DSCR_OFFSET 	0x000000E0	/**< I/O PORT DSCR registers offset  */

/**< Protect Register Register (PRCR)
 register address */
#define HW_PRCR_ADDR	EE_HWREG16_ADDR(0x000803FE)

/**< IWDT-Dedicated Low-Speed Clock Oscillator Control Register (ILOCOCR)
 register address */
#define HW_ILOCOCR_ADDR	EE_HWREG8_ADDR(0x00080035)

/**< PORT0 PDR register address */
#define HW_PORT0_ADDR	EE_HWREG_ADDR(0x0008C000)

/**< PORT1 ODR register base address */
#define HW_ODR_BASE_ADDR		EE_HWREG_ADDR(0x0008C080)
/**< PORT Pin Function Select register base address. */
#define HW_PORT_PFS_BASE_ADDR	EE_HWREG8_ADDR(0x0008C140)
/**< Port Write Protect (PWPR) Register address. */
#define HW_PORT_PWPR_ADDR		EE_HWREG8_ADDR(0x0008C11F)
/* IO Hardware Base Address */
#define	HW_IO_BASE_ADDR			HW_PORT0_ADDR

/* Timers related registers. */
/**< TMR module Timer Counter Control Register address base. */
#define HW_TCCR_ADDR_BASE		EE_HWREG8_ADDR(0x0008820A)
/**< TMR module Timer Control Register address base. */
#define HW_TMR_TCR_ADDR_BASE	EE_HWREG8_ADDR(0x00088200)
/**< TMR module Timer Counter Register address base. */
#define HW_TCNT_ADDR_BASE		EE_HWREG8_ADDR(0x00088208)
/**< TMR01 module Timer Counter Register 16 bits address base. */
#define HW_TMR01_TCNT_ADDR_BASE	EE_HWREG16_ADDR(0x00088208)
/**< TMR23 module Timer Counter Register 16 bits address base. */
#define HW_TMR23_TCNT_ADDR_BASE	EE_HWREG16_ADDR(0x00088218)
/**< TMR0 Time Constant Register A (TCORA). */
#define HW_TMR0_TCORA_ADDR		EE_HWREG8_ADDR(0x00088204)
/**< TMR1 Time Constant Register A (TCORA). */
#define HW_TMR1_TCORA_ADDR		EE_HWREG8_ADDR(0x00088205)
/**< TMR2 Time Constant Register A (TCORA). */
#define HW_TMR2_TCORA_ADDR		EE_HWREG8_ADDR(0x00088214)
/**< TMR3 Time Constant Register A (TCORA). */
#define HW_TMR3_TCORA_ADDR		EE_HWREG8_ADDR(0x00088215)
/**< TMR0 Time Constant Register B (TCORB). */
#define HW_TMR0_TCORB_ADDR		EE_HWREG8_ADDR(0x00088206)
/**< TMR1 Time Constant Register B (TCORB). */
#define HW_TMR1_TCORB_ADDR		EE_HWREG8_ADDR(0x00088207)
/**< TMR2 Time Constant Register B (TCORB). */
#define HW_TMR2_TCORB_ADDR		EE_HWREG8_ADDR(0x00088216)
/**< TMR3 Time Constant Register B (TCORB). */
#define HW_TMR3_TCORB_ADDR		EE_HWREG8_ADDR(0x00088217)
/**< Compare Match Timer (CMT) Start Register 0 (CMSTR0) address. */
#define HW_CMSTR0_ADDR			EE_HWREG16_ADDR(0x00088000)
/**< Compare Match Timer (CMT) Start Register 1 (CMSTR1) address. */
#define HW_CMSTR1_ADDR			EE_HWREG16_ADDR(0x00088010)
/**< Compare Match Timer (CMT) Compare Match Counter (CMCNT) CMT0 address. */
#define HW_CMT0_CMCNT_ADDR		EE_HWREG16_ADDR(0x00088004)
/**< MTU0 Timer Control Register address. */
#define HW_MTU0_TCR_ADDR		EE_HWREG8_ADDR(0x00088700)
/**< MTU1 Timer Control Register address. */
#define HW_MTU1_TCR_ADDR		EE_HWREG8_ADDR(0x00088780)
/**< MTU2 Timer Control Register address. */
#define HW_MTU2_TCR_ADDR		EE_HWREG8_ADDR(0x00088800)
/**< MTU3 Timer Control Register address. */
#define HW_MTU3_TCR_ADDR		EE_HWREG8_ADDR(0x00088600)
/**< MTU4 Timer Control Register address. */
#define HW_MTU4_TCR_ADDR		EE_HWREG8_ADDR(0x00088601)
/**< MTU5U Timer Control Register address. */
#define HW_MTU5U_TCR_ADDR		EE_HWREG8_ADDR(0x00088884)
/**< MTU5V Timer Control Register address. */
#define HW_MTU5V_TCR_ADDR		EE_HWREG8_ADDR(0x00088894)
/**< MTU5W Timer Control Register address. */
#define HW_MTU5W_TCR_ADDR		EE_HWREG8_ADDR(0x000888A4)
/**< Timer Compare Match Clear Register (TCNTCMPCLR)*/
#define HW_MTU5_TCNTCMPCLR_ADDR	EE_HWREG8_ADDR(0x000888B6)
/**< MTU0 Timer Control Register address. */
#define HW_MTU0_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088701)
/**< MTU1 Timer Control Register address. */
#define HW_MTU1_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088781)
/**< MTU2 Timer Control Register address. */
#define HW_MTU2_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088801)
/**< MTU3 Timer Control Register address. */
#define HW_MTU3_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088602)
/**< MTU4 Timer Control Register address. */
#define HW_MTU4_TMDR_ADDR 		EE_HWREG8_ADDR(0x00088603)
/**< MTU0 Timer Status Register address. */
#define HW_MTU0_TSR_ADDR 		EE_HWREG8_ADDR(0x00088705)
/**< MTU1 Timer Status Register address. */
#define HW_MTU1_TSR_ADDR 		EE_HWREG8_ADDR(0x00088785)
/**< MTU2 Timer Status Register address. */
#define HW_MTU2_TSR_ADDR 		EE_HWREG8_ADDR(0x00088805)
/**< MTU3 Timer Status Register address. */
#define HW_MTU3_TSR_ADDR 		EE_HWREG8_ADDR(0x0008862C)
/**< MTU4 Timer Status Register address. */
#define HW_MTU4_TSR_ADDR 		EE_HWREG8_ADDR(0x0008862D)
/**< MTU0 Timer Status Register address. */
#define HW_MTU0_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088706)
/**< MTU1 Timer Status Register address. */
#define HW_MTU1_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088786)
/**< MTU2 Timer Status Register address. */
#define HW_MTU2_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088806)
/**< MTU3 Timer Status Register address. */
#define HW_MTU3_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088610)
/**< MTU4 Timer Status Register address. */
#define HW_MTU4_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088612)
/**< MTU5U Timer Status Register address. */
#define HW_MTU5U_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088880)
/**< MTU5V Timer Status Register address. */
#define HW_MTU5V_TCNT_ADDR 		EE_HWREG16_ADDR(0x00088890)
/**< MTU5W Timer Status Register address. */
#define HW_MTU5W_TCNT_ADDR 		EE_HWREG16_ADDR(0x000888A0)
/**< MTU3 and MTU4 Timer Read/Write Enable Registers (TRWER) address. */
#define HW_MTU34_TRWER_ADDR		EE_HWREG16_ADDR(0x00088684)
/**< MTU0 Timer General Register A (TGRA) address. */
#define HW_MTU0_TGRA_ADDR		EE_HWREG16_ADDR(0x00088708)
/**< MTU0 Timer General Register B (TGRB) address. */
#define HW_MTU0_TGRB_ADDR		EE_HWREG16_ADDR(0x0008870A)
/**< MTU0 Timer General Register C (TGRC) address. */
#define HW_MTU0_TGRC_ADDR		EE_HWREG16_ADDR(0x0008870C)
/**< MTU0 Timer General Register D (TGRD) address. */
#define HW_MTU0_TGRD_ADDR		EE_HWREG16_ADDR(0x0008870E)
/**< MTU0 Timer General Register E (TGRE) address. */
#define HW_MTU0_TGRE_ADDR		EE_HWREG16_ADDR(0x00088720)
/**< MTU0 Timer General Register F (TGRF) address. */
#define HW_MTU0_TGRF_ADDR		EE_HWREG16_ADDR(0x00088722)
/**< MTU1 Timer General Register A (TGRA) address. */
#define HW_MTU1_TGRA_ADDR		EE_HWREG16_ADDR(0x00088788)
/**< MTU1 Timer General Register B (TGRB) address. */
#define HW_MTU1_TGRB_ADDR		EE_HWREG16_ADDR(0x0008878A)
/**< MTU2 Timer General Register A (TGRA) address. */
#define HW_MTU2_TGRA_ADDR		EE_HWREG16_ADDR(0x00088808)
/**< MTU2 Timer General Register B (TGRB) address. */
#define HW_MTU2_TGRB_ADDR		EE_HWREG16_ADDR(0x0008880A)
/**< MTU3 Timer General Register A (TGRA) address. */
#define HW_MTU3_TGRA_ADDR		EE_HWREG16_ADDR(0x00088618)
/**< MTU3 Timer General Register B (TGRB) address. */
#define HW_MTU3_TGRB_ADDR		EE_HWREG16_ADDR(0x0008861A)
/**< MTU3 Timer General Register C (TGRC) address. */
#define HW_MTU3_TGRC_ADDR		EE_HWREG16_ADDR(0x00088624)
/**< MTU3 Timer General Register D (TGRD) address. */
#define HW_MTU3_TGRD_ADDR		EE_HWREG16_ADDR(0x00088626)
/**< MTU4 Timer General Register A (TGRA) address. */
#define HW_MTU4_TGRA_ADDR		EE_HWREG16_ADDR(0x0008861C)
/**< MTU4 Timer General Register B (TGRB) address. */
#define HW_MTU4_TGRB_ADDR		EE_HWREG16_ADDR(0x0008861E)
/**< MTU4 Timer General Register C (TGRC) address. */
#define HW_MTU4_TGRC_ADDR		EE_HWREG16_ADDR(0x00088628)
/**< MTU4 Timer General Register D (TGRD) address. */
#define HW_MTU4_TGRD_ADDR		EE_HWREG16_ADDR(0x0008862A)
/**< MTU4 Timer General Register U (TGRB) address. */
#define HW_MTU5_TGRU_ADDR		EE_HWREG16_ADDR(0x00088882)
/**< MTU4 Timer General Register V (TGRC) address. */
#define HW_MTU5_TGRV_ADDR		EE_HWREG16_ADDR(0x00088892)
/**< MTU4 Timer General Register W (TGRD) address. */
#define HW_MTU5_TGRW_ADDR		EE_HWREG16_ADDR(0x000888A2)
/**< MTU0 Timer Interrupt Enable Register (TIER) address. */
#define HW_MTU0_TIER_ADDR 		EE_HWREG8_ADDR(0x00088704)
/**< MTU1 Timer Interrupt Enable Register (TIER) address. */
#define HW_MTU1_TIER_ADDR 		EE_HWREG8_ADDR(0x00088784)
/**< MTU2 Timer Interrupt Enable Register (TIER) address. */
#define HW_MTU2_TIER_ADDR 		EE_HWREG8_ADDR(0x00088804)
/**< MTU3 Timer Interrupt Enable Register (TIER) address. */
#define HW_MTU3_TIER_ADDR 		EE_HWREG8_ADDR(0x00088608)
/**< MTU4 Timer Interrupt Enable Register (TIER) address. */
#define HW_MTU4_TIER_ADDR 		EE_HWREG8_ADDR(0x00088609)
/**< MTU5 Timer Interrupt Enable Register (TIER) address. */
#define HW_MTU5_TIER_ADDR 		EE_HWREG8_ADDR(0x000088B2)
/**< MTU2A Timer Synchronous Registers (TSYR) address. */
#define HW_MTU2A_TSYR_ADDR		EE_HWREG8_ADDR(0x00008681)

/**< MTU0 to MTU4 Timer Start Registers (TSTR) address. */
#define HW_TSTR_BASE_ADDR		EE_HWREG8_ADDR(0x00088680)
/**< MTU5 Timer Start Registers (TSTR) address. */
#define HW_TSTR5_ADDR			EE_HWREG8_ADDR(0x000888B4)

/* WDT timer related registers. */
/**< WDT refresh register (WDTRR) address. */
#define HW_WDTRR_ADDR			EE_HWREG8_ADDR(0x00088020)
/**< WDT control register (WDTCR) address. */
#define HW_WDTCR_ADDR			EE_HWREG16_ADDR(0x00088022)
/**< WDT status register (WDTSR) address. */
#define HW_WDTSR_ADDR			EE_HWREG16_ADDR(0x00088024)
/**< WDT reset control register (WDTRCR) address. */
#define HW_WDTRCR_ADDR			EE_HWREG8_ADDR(0x00088026)

/* IWDT timer related registers. */
/**< IWDT refresh register (IWDTRR) address. */
#define HW_IWDTRR_ADDR			EE_HWREG8_ADDR(0x00088030)
/**< IWDT control register (IWDTCR) address. */
#define HW_IWDTCR_ADDR			EE_HWREG16_ADDR(0x00088032)
/**< IWDT status register (IWDTSR) address. */
#define HW_IWDTSR_ADDR			EE_HWREG16_ADDR(0x00088034)
/**< IWDT reset control register (IWDTRCR) address. */
#define HW_IWDTRCR_ADDR			EE_HWREG8_ADDR(0x00088036)
/**< IWDT Count Stop Control Register (IWDTCSTPR) address. */
#define HW_IWDTCSTPR_ADDR		EE_HWREG8_ADDR(0x00088038)

/* Module Stop/Start related registers. */
/**< Module Stop Control Register A (MSTPCRA) address. */
#define HW_SYSTEM_MSTPCRA_ADDR	EE_HWREG_ADDR(0x00080010)
/**< Module Stop Control Register B (MSTPCRB) address. */
#define HW_SYSTEM_MSTPCRB_ADDR	EE_HWREG_ADDR(0x00080014)
/**< Module Stop Control Register C (MSTPCRC) address. */
#define HW_SYSTEM_MSTPCRC_ADDR	EE_HWREG_ADDR(0x00080018)

/**< CMT module registers base address. */
#define HW_CMT_BASE_ADDR HW_CMSTR0_ADDR

/*Serial Communication Interfaces (SCIc and SCId) registers base address*/
/**< Base Address of SCIc */
#define HW_SCI_C_BASE_ADDR		EE_HWREG8_ADDR(0x0008A000)
/**< Base Address of SCId */
#define HW_SCI_D_BASE_ADDR		EE_HWREG8_ADDR(0x0008B300)
/*Serial Communication Interfaces (SCIc and SCId) register addresse offsets */
#define HW_SCI_CH_OFFSET	0x00000020	/**< SCI SPMR register offset  */
#define HW_SCI_SMR_OFFSET	0x00000000	/**< SCI SMR register offset  */
#define HW_SCI_BRR_OFFSET	0x00000001	/**< SCI BRR register offset  */
#define HW_SCI_SCR_OFFSET	0x00000002	/**< SCI SCR register offset  */
#define HW_SCI_TDR_OFFSET	0x00000003	/**< SCI TDR register offset  */
#define HW_SCI_SSR_OFFSET	0x00000004	/**< SCI SSR register offset  */
#define HW_SCI_RDR_OFFSET	0x00000005	/**< SCI RDR register offset  */
#define HW_SCI_SCMR_OFFSET	0x00000006	/**< SCI SCMR register offset  */
#define HW_SCI_SEMR_OFFSET	0x00000007	/**< SCI SEMR register offset  */
#define HW_SCI_SNFR_OFFSET	0x00000008	/**< SCI SNFR register offset  */
#define HW_SCI_SIMR1_OFFSET	0x00000009	/**< SCI SIMR1 register offset  */
#define HW_SCI_SIMR2_OFFSET	0x0000000A	/**< SCI SIMR2 register offset  */
#define HW_SCI_SIMR3_OFFSET	0x0000000B	/**< SCI SIMR3 register offset  */
#define HW_SCI_SISR_OFFSET	0x0000000C	/**< SCI SISR register offset  */
#define HW_SCI_SPMR_OFFSET	0x0000000D	/**< SCI SPMR register offset  */

/*Serial Peripheral Interface (RSPI) register addresses*/
/**< Address of RSPI control register (SPCR) */
#define HW_RSPI_SPCR_ADDR		EE_HWREG8_ADDR(0x00088380)
/**< Address of RSPI slave select polarity register (SSLP) */
#define HW_RSPI_SSLP_ADDR		EE_HWREG8_ADDR(0x00088381)
/**< Address of RSPI pin control register (SPPCR) */
#define HW_RSPI_SPPCR_ADDR		EE_HWREG8_ADDR(0x00088382)
/**< Address of RSPI status register (SPSR) */
#define HW_RSPI_SPSR_ADDR		EE_HWREG8_ADDR(0x00088383)
/**< Address of RSPI  data register (SPDR) */
#define HW_RSPI_SPDR_ADDR		EE_HWREG_ADDR(0x00088384)
/**< Address of RSPI sequence control register (SPSCR) */
#define HW_RSPI_SPSCR_ADDR		EE_HWREG8_ADDR(0x00088388)
/**< Address of RSPI sequence status register (SPSSR) */
#define HW_RSPI_SPSSR_ADDR		EE_HWREG8_ADDR(0x00088389)
/**< Address of RSPI bit rate register (SPBR) */
#define HW_RSPI_SPBR_ADDR		EE_HWREG8_ADDR(0x0008838A)
/**< Address of RSPI data control register (SPDCR) */
#define HW_RSPI_SPDCR_ADDR		EE_HWREG8_ADDR(0x0008838B)
/**< Address of RSPI clock delay register (SPCKD) */
#define HW_RSPI_SPCKD_ADDR		EE_HWREG8_ADDR(0x0008838C)
/**< Address of RSPI slave select negation delay register (SSLND) */
#define HW_RSPI_SSLND_ADDR		EE_HWREG8_ADDR(0x0008838D)
/**< Address of RSPI next-access delay register (SPND) */
#define HW_RSPI_SPND_ADDR		EE_HWREG8_ADDR(0x0008838E)
/**< Address of RSPI control register 2 (SPCR2) */
#define HW_RSPI_SPCR2_ADDR		EE_HWREG8_ADDR(0x0008838F)
/**< Address of RSPI command register 0 (SPCMD0) */
#define HW_RSPI_SPCMD0_ADDR		EE_HWREG16_ADDR(0x00088390)
/**< Address of RSPI command register 1 (SPCMD1) */
#define HW_RSPI_SPCMD1_ADDR		EE_HWREG16_ADDR(0x00088392)
/**< Address of RSPI command register 2 (SPCMD2) */
#define HW_RSPI_SPCMD2_ADDR		EE_HWREG16_ADDR(0x00088394)
/**< Address of RSPI command register 3 (SPCMD3) */
#define HW_RSPI_SPCMD3_ADDR		EE_HWREG16_ADDR(0x00088396)
/**< Address of RSPI command register 4 (SPCMD4) */
#define HW_RSPI_SPCMD4_ADDR		EE_HWREG16_ADDR(0x00088398)
/**< Address of RSPI command register 5 (SPCMD5) */
#define HW_RSPI_SPCMD5_ADDR		EE_HWREG16_ADDR(0x0008839A)
/**< Address of RSPI command register 6 (SPCMD6) */
#define HW_RSPI_SPCMD6_ADDR		EE_HWREG16_ADDR(0x0008839C)
/**< Address of RSPI command register 7 (SPCMD7) */
#define HW_RSPI_SPCMD7_ADDR		EE_HWREG16_ADDR(0x0008839E)



/**< Base address of Interrupt Request Enable Registers (IERx) */
#define HW_ICU_IEN_BASE	EE_HWREG8_ADDR(0x00087200)

/**< Address of Interrupt Request Enable Register (IER) for TMR0 CMIA */
#define HW_ICU_IER_TMR0_CMIA	EE_HWREG8_ADDR(0x00087215)
/**< Address of Interrupt Request Enable Register (IER) for TMR0 CMIB.*/
#define HW_ICU_IER_TMR0_CMIB	EE_HWREG8_ADDR(0x00087215)
/**< Address of Interrupt Request Enable Register (IER) for TMR1 CMIA */
#define HW_ICU_IER_TMR1_CMIA	EE_HWREG8_ADDR(0x00087216)
/**< Address of Interrupt Request Enable Register (IER) for TMR1 CMIB.*/
#define HW_ICU_IER_TMR1_CMIB	EE_HWREG8_ADDR(0x00087216)
/**< Address of Interrupt Request Enable Register (IER) for TMR2 CMIA */
#define HW_ICU_IER_TMR2_CMIA	EE_HWREG8_ADDR(0x00087216)
/**< Address of Interrupt Request Enable Register (IER) for TMR2 CMIB.*/
#define HW_ICU_IER_TMR2_CMIB	EE_HWREG8_ADDR(0x00087216)
/**< Address of Interrupt Request Enable Register (IER) for TMR3 CMIA */
#define HW_ICU_IER_TMR3_CMIA	EE_HWREG8_ADDR(0x00087216)
/**< Address of Interrupt Request Enable Register (IER) for TMR3 CMIB.*/
#define HW_ICU_IER_TMR3_CMIB	EE_HWREG8_ADDR(0x00087217)
/**< Address of Interrupt Request Enable Register (IER) for CMT CMI. */
#define HW_ICU_IER_CMT_CMI		EE_HWREG8_ADDR(0x00087203)
/**< Address of Interrupt Request Enable Register (IER) for MTU0 TGIA */
#define HW_ICU_IER_MTU0_TGIA	EE_HWREG8_ADDR(0x0008720E)
/**< Address of Interrupt Request Enable Register (IER) for MTU0 TGIB.*/
#define HW_ICU_IER_MTU0_TGIB	EE_HWREG8_ADDR(0x0008720E)
/**< Address of Interrupt Request Enable Register (IER) for MTU0 TGIC */
#define HW_ICU_IER_MTU0_TGIC	EE_HWREG8_ADDR(0x0008720E)
/**< Address of Interrupt Request Enable Register (IER) for MTU0 TGID.*/
#define HW_ICU_IER_MTU0_TGID	EE_HWREG8_ADDR(0x0008720E)
/**< Address of Interrupt Request Enable Register (IER) for MTU1 TGIA */
#define HW_ICU_IER_MTU1_TGIA	EE_HWREG8_ADDR(0x0008720F)
/**< Address of Interrupt Request Enable Register (IER) for MTU1 TGIB.*/
#define HW_ICU_IER_MTU1_TGIB	EE_HWREG8_ADDR(0x0008720F)
/**< Address of Interrupt Request Enable Register (IER) for MTU2 TGIA */
#define HW_ICU_IER_MTU2_TGIA	EE_HWREG8_ADDR(0x0008720F)
/**< Address of Interrupt Request Enable Register (IER) for MTU2 TGIB.*/
#define HW_ICU_IER_MTU2_TGIB	EE_HWREG8_ADDR(0x0008720F)
/**< Address of Interrupt Request Enable Register (IER) for MTU3 TGIA */
#define HW_ICU_IER_MTU3_TGIA	EE_HWREG8_ADDR(0x00087210)
/**< Address of Interrupt Request Enable Register (IER) for MTU3 TGIB.*/
#define HW_ICU_IER_MTU3_TGIB	EE_HWREG8_ADDR(0x00087210)
/**< Address of Interrupt Request Enable Register (IER) for MTU3 TGIC */
#define HW_ICU_IER_MTU3_TGIC	EE_HWREG8_ADDR(0x00087210)
/**< Address of Interrupt Request Enable Register (IER) for MTU3 TGID.*/
#define HW_ICU_IER_MTU3_TGID	EE_HWREG8_ADDR(0x00087210)
/**< Address of Interrupt Request Enable Register (IER) for MTU4 TGIA */
#define HW_ICU_IER_MTU4_TGIA	EE_HWREG8_ADDR(0x00087210)
/**< Address of Interrupt Request Enable Register (IER) for MTU4 TGIB.*/
#define HW_ICU_IER_MTU4_TGIB	EE_HWREG8_ADDR(0x00087210)
/**< Address of Interrupt Request Enable Register (IER) for MTU4 TGIC */
#define HW_ICU_IER_MTU4_TGIC	EE_HWREG8_ADDR(0x00087211)
/**< Address of Interrupt Request Enable Register (IER) for MTU4 TGID.*/
#define HW_ICU_IER_MTU4_TGID	EE_HWREG8_ADDR(0x00087211)
/**< Address of Interrupt Request Enable Register (IER) for MTU5 TGIx.*/
#define HW_ICU_IER_MTU5_TGI		EE_HWREG8_ADDR(0x00087211)
/**< Address of Interrupt Request Enable Register (IER) of SCI0 ERX  */
#define HW_ICU_IER_SCI0_ERX		EE_HWREG8_ADDR(0x0008721A)
/**< Address of Interrupt Request Enable Register (IER) of SCI0 RX  */
#define HW_ICU_IER_SCI0_RX		EE_HWREG8_ADDR(0x0008721A)
/**< Address of Interrupt Request Enable Register (IER) of SCI0 TX  */
#define HW_ICU_IER_SCI0_TX		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI0 TE  */
#define HW_ICU_IER_SCI0_TE		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI1 ERX  */
#define HW_ICU_IER_SCI1_ERX		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI1 RX  */
#define HW_ICU_IER_SCI1_RX		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI1 TX  */
#define HW_ICU_IER_SCI1_TX		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI1 TE  */
#define HW_ICU_IER_SCI1_TE		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI5 ERX  */
#define HW_ICU_IER_SCI5_ERX		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI5 RX  */
#define HW_ICU_IER_SCI5_RX		EE_HWREG8_ADDR(0x0008721B)
/**< Address of Interrupt Request Enable Register (IER) of SCI5 TX  */
#define HW_ICU_IER_SCI5_TX		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI5 TE  */
#define HW_ICU_IER_SCI5_TE		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI6 ERX  */
#define HW_ICU_IER_SCI6_ERX		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI6 RX  */
#define HW_ICU_IER_SCI6_RX		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI6 TX  */
#define HW_ICU_IER_SCI6_TX		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI6 TE  */
#define HW_ICU_IER_SCI6_TE		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI6 TE  */
#define HW_ICU_IER_SCI6_TE		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI8 ERX  */
#define HW_ICU_IER_SCI8_ERX		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI8 RX  */
#define HW_ICU_IER_SCI8_RX		EE_HWREG8_ADDR(0x0008721C)
/**< Address of Interrupt Request Enable Register (IER) of SCI8 TX  */
#define HW_ICU_IER_SCI8_TX		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI8 TE  */
#define HW_ICU_IER_SCI8_TE		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI9 ERX  */
#define HW_ICU_IER_SCI9_ERX		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI9 RX  */
#define HW_ICU_IER_SCI9_RX		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI9 TX  */
#define HW_ICU_IER_SCI9_TX		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI9 TE  */
#define HW_ICU_IER_SCI9_TE		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI12 ERX  */
#define HW_ICU_IER_SCI12_ERX	EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI12 RX  */
#define HW_ICU_IER_SCI12_RX		EE_HWREG8_ADDR(0x0008721D)
/**< Address of Interrupt Request Enable Register (IER) of SCI12 TX  */
#define HW_ICU_IER_SCI12_TX		EE_HWREG8_ADDR(0x0008721E)
/**< Address of Interrupt Request Enable Register (IER) of SCI12 TE  */
#define HW_ICU_IER_SCI12_TE		EE_HWREG8_ADDR(0x0008721E)
/**< Address of Interrupt Request Enable Register (IER) of RSPI0 SPEI  */
#define HW_ICU_IER_RSPI_SPEI	EE_HWREG8_ADDR(0x00087205)
/**< Address of Interrupt Request Enable Register (IER) of RSPI0 SPRI  */
#define HW_ICU_IER_RSPI_SPRI	EE_HWREG8_ADDR(0x00087205)
/**< Address of Interrupt Request Enable Register (IER) of RSPI0 SPTI  */
#define HW_ICU_IER_RSPI_SPTI	EE_HWREG8_ADDR(0x00087205)
/**< Address of Interrupt Request Enable Register (IER) of RSPI0 SPII  */
#define HW_ICU_IER_RSPI_SPII	EE_HWREG8_ADDR(0x00087205)


/*Interrrupt Request Registers (IR) address.*/
/**< Address of Interrupt Request Register (IER) of SCI0 ERX  */
#define HW_ICU_IR_SCI0_ERX		EE_HWREG8_ADDR(0x000870D6)
/**< Address of Interrupt Request Register (IER) of SCI1 ERX  */
#define HW_ICU_IR_SCI1_ERX		EE_HWREG8_ADDR(0x000870DA)
/**< Address of Interrupt Request Register (IER) of SCI5 ERX  */
#define HW_ICU_IR_SCI5_ERX		EE_HWREG8_ADDR(0x000870DE)
/**< Address of Interrupt Request Register (IER) of SCI6 ERX  */
#define HW_ICU_IR_SCI6_ERX		EE_HWREG8_ADDR(0x000870E2)
/**< Address of Interrupt Request Register (IER) of SCI8 ERX  */
#define HW_ICU_IR_SCI8_ERX		EE_HWREG8_ADDR(0x000870E6)
/**< Address of Interrupt Request Register (IER) of SCI9 ERX  */
#define HW_ICU_IR_SCI9_ERX		EE_HWREG8_ADDR(0x000870EA)
/**< Address of Interrupt Request Register (IER) of SCI12 ERX  */
#define HW_ICU_IR_SCI12_ERX		EE_HWREG8_ADDR(0x000870EE)
/**< Address of Interrupt Request Register (IER) of RSPI SPEI  */
#define HW_ICU_IR_RSPI_SPEI		EE_HWREG8_ADDR(0x0008702C)
/**< Address of Interrupt Request Register (IER) of RSPI SPRI  */
#define HW_ICU_IR_RSPI_SPRI		EE_HWREG8_ADDR(0x0008702D)
/**< Address of Interrupt Request Register (IER) of RSPI SPTI  */
#define HW_ICU_IR_RSPI_SPTI		EE_HWREG8_ADDR(0x0008702E)
/**< Address of Interrupt Request Register (IER) of RSPI SPII  */
#define HW_ICU_IR_RSPI_SPII		EE_HWREG8_ADDR(0x0008702F)


/*Interrrupt Priority Registers (IPRs) address.*/
/**< Address of IPR of TMR0 CMIx. */
#define HW_ICU_IPR_TMR0_REG			EE_HWREG8_ADDR(0x000873AE)
/**< Address of IPR of TMR1 CMIx. */
#define HW_ICU_IPR_TMR1_REG			EE_HWREG8_ADDR(0x000873B1)
/**< Address of IPR of TMR2 CMIx. */
#define HW_ICU_IPR_TMR2_REG			EE_HWREG8_ADDR(0x000873B4)
/**< Address of IPR of TMR3 CMIx. */
#define HW_ICU_IPR_TMR3_REG			EE_HWREG8_ADDR(0x000873B7)
/**< Address of IPR of CMT0 CMI. */
#define HW_ICU_IPR_CMT0_REG			EE_HWREG8_ADDR(0x00087304)
/**< Address of IPR of CMT1 CMI. */
#define HW_ICU_IPR_CMT1_REG			EE_HWREG8_ADDR(0x00087305)
/**< Address of IPR of CMT2 CMI. */
#define HW_ICU_IPR_CMT2_REG			EE_HWREG8_ADDR(0x00087306)
/**< Address of IPR of CMT3 CMI. */
#define HW_ICU_IPR_CMT3_REG			EE_HWREG8_ADDR(0x00087307)
/**< Address of IPR of MTU0 TGIx. */
#define HW_ICU_IPR_MTU0_TGI_REG		EE_HWREG8_ADDR(0x00087372)
/**< Address of IPR of MTU1 TGIx. */
#define HW_ICU_IPR_MTU1_TGI_REG		EE_HWREG8_ADDR(0x00087379)
/**< Address of IPR of MTU2 TGIx. */
#define HW_ICU_IPR_MTU2_TGI_REG		EE_HWREG8_ADDR(0x0008737D)
/**< Address of IPR of MTU3 TGIx. */
#define HW_ICU_IPR_MTU3_TGI_REG		EE_HWREG8_ADDR(0x00087381)
/**< Address of IPR of MTU4 TGIx. */
#define HW_ICU_IPR_MTU4_TGI_REG		EE_HWREG8_ADDR(0x00087386)
/**< Address of IPR of MTU5 TGIx. */
#define HW_ICU_IPR_MTU5_TGI_REG		EE_HWREG8_ADDR(0x0008738B)
/**< Address of IPR of SCI0  */
#define HW_ICU_IPR_SCI0				EE_HWREG8_ADDR(0x000873D6)
/**< Address of IPR of SCI1  */
#define HW_ICU_IPR_SCI1				EE_HWREG8_ADDR(0x000873DA)
/**< Address of IPR of SCI5  */
#define HW_ICU_IPR_SCI5				EE_HWREG8_ADDR(0x000873DE)
/**< Address of IPR of SCI6  */
#define HW_ICU_IPR_SCI6				EE_HWREG8_ADDR(0x000873E2)
/**< Address of IPR of SCI8  */
#define HW_ICU_IPR_SCI8				EE_HWREG8_ADDR(0x000873E6)
/**< Address of IPR of SCI9  */
#define HW_ICU_IPR_SCI9				EE_HWREG8_ADDR(0x000873EA)
/**< Address of IPR of SCI12 */
#define HW_ICU_IPR_SCI12			EE_HWREG8_ADDR(0x000873EE)
/**< Address of IPR of RSPI */
#define HW_ICU_IPR_RSPI				EE_HWREG8_ADDR(0x0008732C)


/**< Address of Non-Maskable Interrupt Status Register (NMISR) */
#define HW_ICU_NMISR				EE_HWREG8_ADDR(0x00087580)
/**< Address of Non-Maskable Interrupt Enable Register (NMIER) */
#define HW_ICU_NMIER				EE_HWREG8_ADDR(0x00087581)
/**< Address of Non-Maskable Interrupt Status Clear Register (NMICLR) */
#define HW_ICU_NMICLR				EE_HWREG8_ADDR(0x00087582)
/**< Address of NMI Pin Interrupt Control Register (NMICR) */
#define HW_ICU_NMICR				EE_HWREG8_ADDR(0x00087583)
/**< Address of NMI Pin Digital Filter Enable Register (NMIFLTE) */
#define HW_ICU_NMIFLTE				EE_HWREG8_ADDR(0x00087590)

/*NMIER bits*/
#define HW_ICU_NMIER_WDTST_MASK		0x04
#define HW_ICU_NMIER_IWDTST_MASK	0x08
/*NMISR bits*/
#define HW_ICU_NMISR_WDTST_MASK		0x04
#define HW_ICU_NMISR_IWDTST_MASK	0x08
/*NMICLR bits*/
#define HW_ICU_NMICLR_WDTCLR_MASK	0x04
#define HW_ICU_NMICLR_IWDTCLR_MASK	0x08

/* IER bit mask.*/
/**< Bit mask for TMR0 CMIA .*/
#define HW_ICU_TMR0_IER_CMIA_MASK	0x40
/**< Bit mask for TMR0 CMIB .*/
#define HW_ICU_TMR0_IER_CMIB_MASK	0x80
/**< Bit mask for TMR1 CMIA .*/
#define HW_ICU_TMR1_IER_CMIA_MASK	0x02
/**< Bit mask for TMR1 CMIB .*/
#define HW_ICU_TMR1_IER_CMIB_MASK	0x04
/**< Bit mask for TMR2 CMIA .*/
#define HW_ICU_TMR2_IER_CMIA_MASK	0x10
/**< Bit mask for TMR2 CMIB .*/
#define HW_ICU_TMR2_IER_CMIB_MASK	0x20
/**< Bit mask for TMR3 CMIA .*/
#define HW_ICU_TMR3_IER_CMIA_MASK	0x80
/**< Bit mask for TMR3 CMIB .*/
#define HW_ICU_TMR3_IER_CMIB_MASK	0x01
/**< Bit mask for TMR0 CMIA .*/
#define HW_ICU_TMR0_IER_CMIA_MASK	0x40
/**< Bit mask for TMR0 CMIB .*/
#define HW_ICU_TMR0_IER_CMIB_MASK	0x80
/**< Bit mask for CMT0 CMI .*/
#define HW_ICU_CMT0_IER_CMI_MASK	0x10
/**< Bit mask for CMT1 CMI .*/
#define HW_ICU_CMT1_IER_CMI_MASK	0x20
/**< Bit mask for CMT2 CMI .*/
#define HW_ICU_CMT2_IER_CMI_MASK	0x40
/**< Bit mask for CMT3 CMI .*/
#define HW_ICU_CMT3_IER_CMI_MASK	0x80
/**< Bit mask for MTU0 TGIA .*/
#define HW_ICU_MTU0_IER_TGIA_MASK	0x04
/**< Bit mask for MTU0 TGIB .*/
#define HW_ICU_MTU0_IER_TGIB_MASK	0x08
/**< Bit mask for MTU0 TGIC .*/
#define HW_ICU_MTU0_IER_TGIC_MASK	0x10
/**< Bit mask for MTU0 TGID .*/
#define HW_ICU_MTU0_IER_TGID_MASK	0x20
/**< Bit mask for MTU1 TGIA .*/
#define HW_ICU_MTU1_IER_TGIA_MASK	0x02
/**< Bit mask for MTU1 TGIB .*/
#define HW_ICU_MTU1_IER_TGIB_MASK	0x04
/**< Bit mask for MTU2 TGIA .*/
#define HW_ICU_MTU2_IER_TGIA_MASK	0x20
/**< Bit mask for MTU2 TGIB .*/
#define HW_ICU_MTU2_IER_TGIB_MASK	0x40
/**< Bit mask for MTU3 TGIA .*/
#define HW_ICU_MTU3_IER_TGIA_MASK	0x02
/**< Bit mask for MTU3 TGIB .*/
#define HW_ICU_MTU3_IER_TGIB_MASK	0x04
/**< Bit mask for MTU3 TGIC .*/
#define HW_ICU_MTU3_IER_TGIC_MASK	0x08
/**< Bit mask for MTU3 TGID .*/
#define HW_ICU_MTU3_IER_TGID_MASK	0x10
/**< Bit mask for MTU4 TGIA .*/
#define HW_ICU_MTU4_IER_TGIA_MASK	0x40
/**< Bit mask for MTU4 TGIB .*/
#define HW_ICU_MTU4_IER_TGIB_MASK	0x80
/**< Bit mask for MTU4 TGIC .*/
#define HW_ICU_MTU4_IER_TGIC_MASK	0x01
/**< Bit mask for MTU4 TGID .*/
#define HW_ICU_MTU4_IER_TGID_MASK	0x02
/**< Bit mask for MTU5 TGIU .*/
#define HW_ICU_MTU5_IER_TGIU_MASK	0x08
/**< Bit mask for MTU5 TGIV .*/
#define HW_ICU_MTU5_IER_TGIV_MASK	0x10
/**< Bit mask for MTU5 TGIW .*/
#define HW_ICU_MTU5_IER_TGIW_MASK	0x20
/**< Bit mask for SCI0 ER .*/
#define HW_ICU_SCI0_IER_ER_MASK		0x40
/**< Bit mask for SCI0 RX .*/
#define HW_ICU_SCI0_IER_RX_MASK		0x80
/**< Bit mask for SCI0 TX .*/
#define HW_ICU_SCI0_IER_TX_MASK		0x01
/**< Bit mask for SCI0 TE .*/
#define HW_ICU_SCI0_IER_TE_MASK		0x02
/**< Bit mask for SCI1 ER .*/
#define HW_ICU_SCI1_IER_ER_MASK		0x04
/**< Bit mask for SCI1 RX .*/
#define HW_ICU_SCI1_IER_RX_MASK		0x08
/**< Bit mask for SCI1 TX .*/
#define HW_ICU_SCI1_IER_TX_MASK		0x10
/**< Bit mask for SCI1 TE .*/
#define HW_ICU_SCI1_IER_TE_MASK		0x20
/**< Bit mask for SCI5 ER .*/
#define HW_ICU_SCI5_IER_ER_MASK		0x40
/**< Bit mask for SCI5 RX .*/
#define HW_ICU_SCI5_IER_RX_MASK		0x80
/**< Bit mask for SCI5 TX .*/
#define HW_ICU_SCI5_IER_TX_MASK		0x01
/**< Bit mask for SCI5 TE .*/
#define HW_ICU_SCI5_IER_TE_MASK		0x02
/**< Bit mask for SCI6 ER .*/
#define HW_ICU_SCI6_IER_ER_MASK		0x04
/**< Bit mask for SCI6 RX .*/
#define HW_ICU_SCI6_IER_RX_MASK		0x08
/**< Bit mask for SCI6 TX .*/
#define HW_ICU_SCI6_IER_TX_MASK		0x10
/**< Bit mask for SCI6 TE .*/
#define HW_ICU_SCI6_IER_TE_MASK		0x20
/**< Bit mask for SCI8 ER .*/
#define HW_ICU_SCI8_IER_ER_MASK		0x40
/**< Bit mask for SCI8 RX .*/
#define HW_ICU_SCI8_IER_RX_MASK		0x80
/**< Bit mask for SCI8 TX .*/
#define HW_ICU_SCI8_IER_TX_MASK		0x01
/**< Bit mask for SCI8 TE .*/
#define HW_ICU_SCI8_IER_TE_MASK		0x02
/**< Bit mask for SCI9 ER .*/
#define HW_ICU_SCI9_IER_ER_MASK		0x04
/**< Bit mask for SCI9 RX .*/
#define HW_ICU_SCI9_IER_RX_MASK		0x08
/**< Bit mask for SCI9 TX .*/
#define HW_ICU_SCI9_IER_TX_MASK		0x10
/**< Bit mask for SCI9 TE .*/
#define HW_ICU_SCI9_IER_TE_MASK		0x20
/**< Bit mask for SCI12 ER .*/
#define HW_ICU_SCI12_IER_ER_MASK	0x40
/**< Bit mask for SCI12 RX .*/
#define HW_ICU_SCI12_IER_RX_MASK	0x80
/**< Bit mask for SCI12 TX .*/
#define HW_ICU_SCI12_IER_TX_MASK	0x01
/**< Bit mask for SCI12 TE .*/
#define HW_ICU_SCI12_IER_TE_MASK	0x02
/**< Bit mask for RSPI SPEI .*/
#define HW_ICU_RSPI_IER_SPEI_MASK	0x10
/**< Bit mask for RSPI SPRI .*/
#define HW_ICU_RSPI_IER_SPRI_MASK	0x20
/**< Bit mask for RSPI SPTI .*/
#define HW_ICU_RSPI_IER_SPTI_MASK	0x40
/**< Bit mask for RSPI SPII .*/
#define HW_ICU_RSPI_IER_SPII_MASK	0x80

/*Priority levels for IPR registers. */
#define HW_IPR_PRI_LEVEL_0	0
#define HW_IPR_PRI_LEVEL_1	1
#define HW_IPR_PRI_LEVEL_2	2
#define HW_IPR_PRI_LEVEL_3	3
#define HW_IPR_PRI_LEVEL_4	4
#define HW_IPR_PRI_LEVEL_5	5
#define HW_IPR_PRI_LEVEL_6	6
#define HW_IPR_PRI_LEVEL_7	7
#define HW_IPR_PRI_LEVEL_8	8
#define HW_IPR_PRI_LEVEL_9	9
#define HW_IPR_PRI_LEVEL_10	10
#define HW_IPR_PRI_LEVEL_11	11
#define HW_IPR_PRI_LEVEL_12	12
#define HW_IPR_PRI_LEVEL_13	13
#define HW_IPR_PRI_LEVEL_14	14
#define HW_IPR_PRI_LEVEL_15	15


/** @brief	Channel to Hardware Unit.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Numeric ID of Hardware Unit.
 *
 *  This macro function returns the numeric ID of the harware unit referred to
 *  numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_UNIT_MASK</tt> macro.
 */
#ifdef	HW_CH_UNIT_MASK
#define	HW_CH_2_UNIT(_ch)	(uint32)( \
  (uint32)_ch & (uint32)HW_CH_UNIT_MASK \
)
#else
#define	HW_CH_2_UNIT(_ch)	(uint32)( 0x00000000 )
#endif

/** @brief	Channel to Hardware Module.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Numeric ID of Hardware Module.
 *
 *  This macro function returns the numeric ID of the harware module referred to
 *  numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> macro.
 */
#ifdef	HW_CH_MOD_MASK
#ifdef	HW_CH_UNIT_MASK_SZ_S
#define	HW_CH_2_MOD(_ch)	(uint32)( \
  ( (uint32)_ch & (uint32)HW_CH_MOD_MASK ) >> (uint32)HW_CH_UNIT_MASK_SZ_S \
  )

#else	/* HW_CH_UNIT_MASK_SZ_S */

#define	HW_CH_2_MOD(_ch)	(uint32)( \
  (uint32)_ch & (uint32)HW_CH_MOD_MASK \
)
#endif	/* !HW_CH_UNIT_MASK_SZ_S */
#endif	/* HW_CH_MOD_MASK */

#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
/** @brief	Channel to Hardware Module Base Address 
 *  @param	ch	Channel Identifier.
 *  @return	Hardware Module Base Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD</tt> macro.
 */
#define  HW_CH_2_MOD_BASE_ADDR(_ch) \
	(uint32)((uint32)HW_IO_BASE_ADDR + HW_CH_2_MOD(_ch))


#endif /*( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )*/

#if	( defined(HW_CH_MOD_MASK) && defined(HW_ODR_BASE_ADDR) )
/** @brief	Channel to Hardware ODR Base Address 
 *  @param	ch	Channel Identifier.
 *  @return	Hardware ODR Base Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_ODR_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD</tt> macro.
 */
#define  HW_CH_2_ODR_BASE_ADDR(_ch) \
	(HW_ODR_BASE_ADDR + (HW_CH_2_MOD(_ch) << (uint32) 0x1))

#endif /*( defined(HW_CH_MOD_MASK) && defined(HW_ODR_BASE_ADDR) )*/


/** @brief	Channel to Hardware Module Register
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Module Register Offset.
 *  @return	Hardware Module Register.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_REG_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#define	HW_CH_2_MOD_REG(_ch, _ro)	EE_HWREG( \
  HW_CH_2_MOD_REG_ADDR(_ch, _ro) \
)
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */

/** @brief	Channel to Hardware Unit Register Address
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Unit Register Offset.
 *  @return	Hardware Unit Register Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_REG_ADDR</tt> and <tt>HW_CH_2_UNIT</tt> macros.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#ifdef	HW_CH_UNIT_MASK
#define	HW_CH_2_UNIT_REG_ADDR(_ch, _ro)	(uint32)( \
  HW_CH_2_MOD_REG_ADDR(_ch,_ro) + (uint32)( \
    HW_CH_2_UNIT(_ch) << (uint32)HW_REG_SZ_S \
  ) \
)
#else	/* HW_CH_UNIT_MASK */
#define	HW_CH_2_UNIT_REG_ADDR(_ch, _ro)	(uint32)( HW_CH_2_MOD_REG_ADDR(_ch) )
#endif	/* !HW_CH_UNIT_MASK */
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */

/** @brief	Channel to Hardware Unit Register
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Unit Register Offset.
 *  @return	Hardware Unit Register.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_IO_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_UNIT_REG_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_IO_BASE_ADDR) )
#define	HW_CH_2_UNIT_REG(_ch, _ro)	EE_HWREG( \
  HW_CH_2_UNIT_REG_ADDR(_ch, _ro) \
)
#endif	/* HW_CH_MOD_MASK && HW_IO_BASE_ADDR */

/** @brief Macros used to enable the writing to clock generation related 
 *  registers.
 */
#define HW_PRCR_W_EN() \
	( EE_HWREG16(HW_PRCR_ADDR) = 0xA503)
	
/** @brief Macros used to disable the writing to clock generation related 
 *  registers.
 */
#define HW_PRCR_W_DIS() \
	( EE_HWREG16(HW_PRCR_ADDR) = 0xA500)
	
	
#endif	/* HARDWARE_H */

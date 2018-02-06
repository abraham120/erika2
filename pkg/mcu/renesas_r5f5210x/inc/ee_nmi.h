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

 /** @file	ee_nmi.h
  *  @brief	NMI Services Routine
  *  @author	Giuseppe Serano
  *  @date	2013
  */ 

#ifndef __INCLUDE_RENESAS_R5F5210X_NMI_H__
#define __INCLUDE_RENESAS_R5F5210X_NMI_H__

#include "ee.h"

#ifdef __CCRX__
#include "cpu/common/inc/ee_compiler_ccrx.h"
#else
#error Unsupported compiler
#endif

#if	(					\
	defined(EE_RX200_NMI_PIN_TRAP)	||	\
	defined(EE_RX200_NMI_OST_TRAP)	||	\
	defined(EE_RX200_NMI_WDT_TRAP)	||	\
	defined(EE_RX200_NMI_IWDT_TRAP)	||	\
	defined(EE_RX200_NMI_LVD1_TRAP)	||	\
	defined(EE_RX200_NMI_LVD2_TRAP)		\
)

#define	EE_RX200_NMI_TRAP	EE_rx200_nmi_trap

/** @brief	NMI Initialization. */
void EE_rx200_init_nmi(void);

/** Non-Maskable Interrupt Status Register (NMISR) */
#define	EE_RX200_ICU_NMISR		EE_HWREG8(0x00087580U)
/** Non-Maskable Interrupt Enable Register (NMIER) */
#define	EE_RX200_ICU_NMIER		EE_HWREG8(0x00087581U)
/** Non-Maskable Interrupt Status Clear Register (NMICLR) */
#define	EE_RX200_ICU_NMICLR		EE_HWREG8(0x00087582U)
/** NMI Pin Interrupt Control Register (NMICR) */
#define	EE_RX200_ICU_NMICR		EE_HWREG8(0x00087583U)
/** NMI Pin Digital Filter Enable Register (NMIFLTE) */
#define	EE_RX200_ICU_NMIFLTE		EE_HWREG8(0x00087590U)

/*
 * NMI Pin.
 */
#ifdef	EE_RX200_NMI_PIN_TRAP
#define	EE_RX200_ICU_NMI_PIN_MASK	0x01U
#endif	/* EE_RX200_NMI_PIN_TRAP */

/*
 * Oscillation Stop Detection.
 */
#ifdef	EE_RX200_NMI_OST_TRAP
#define	EE_RX200_ICU_NMI_OST_MASK	0x02U
#endif	/* EE_RX200_NMI_OST_TRAP */

/*
 * WDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_WDT_TRAP
#define	EE_RX200_ICU_NMI_WDT_MASK	0x04U
#endif	/* EE_RX200_NMI_WDT_TRAP */

/*
 * IWDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_IWDT_TRAP
#define	EE_RX200_ICU_NMI_IWDT_MASK	0x08U
#endif	/* EE_RX200_NMI_IWDT_TRAP */

/*
 * Voltage Monitoring 1.
 */
#ifdef	EE_RX200_NMI_LVD1_TRAP
#define	EE_RX200_ICU_NMI_LVD1_MASK	0x10U
#endif	/* EE_RX200_NMI_LVD1_TRAP */

/*
 * Voltage Monitoring 2.
 */
#ifdef	EE_RX200_NMI_LVD2_TRAP
#define	EE_RX200_ICU_NMI_LVD2_MASK	0x20U
#endif	/* EE_RX200_NMI_LVD2_TRAP */

#endif	/*
	 * EE_RX200_NMI_PIN_TRAP  || EE_RX200_NMI_OST_TRAP  ||
	 * EE_RX200_NMI_WDT_TRAP  || EE_RX200_NMI_IWDT_TRAP ||
	 * EE_RX200_NMI_LVD1_TRAP || EE_RX200_NMI_LVD2_TRAP
	 */

#endif /* __INCLUDE_RENESAS_R5F5210X_NMI_H__ */

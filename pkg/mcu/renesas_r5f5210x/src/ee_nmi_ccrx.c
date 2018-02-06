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

/** @file	ee_nmi_ccrx.c
 *  @brief	NMI Services Routine for use with Renesas HEW.
 *  @author	Giuseppe Serano
 *  @date	2013
 */

#include "ee.h"
#include "mcu/renesas_r5f5210x/inc/ee_nmi.h"

/*
 * NMI Pin.
 */
#ifdef	EE_RX200_NMI_PIN_TRAP
extern void EE_RX200_NMI_PIN_TRAP(void);
#endif	/* EE_RX200_NMI_PIN_TRAP */

/*
 * Oscillation Stop Detection.
 */
#ifdef	EE_RX200_NMI_OST_TRAP
extern void EE_RX200_NMI_OST_TRAP(void);
#endif	/* EE_RX200_NMI_OST_TRAP */

/*
 * WDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_WDT_TRAP
extern void EE_RX200_NMI_WDT_TRAP(void);
#endif	/* EE_RX200_NMI_WDT_TRAP */

/*
 * IWDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_IWDT_TRAP
extern void EE_RX200_NMI_IWDT_TRAP(void);
#endif	/* EE_RX200_NMI_IWDT_TRAP */

/*
 * Voltage Monitoring 1.
 */
#ifdef	EE_RX200_NMI_LVD1_TRAP
extern void EE_RX200_NMI_LVD1_TRAP(void);
#endif	/* EE_RX200_NMI_LVD1_TRAP */

/*
 * Voltage Monitoring 1.
 */
#ifdef	EE_RX200_NMI_LVD2_TRAP
extern void EE_RX200_NMI_LVD2_TRAP(void);
#endif	/* EE_RX200_NMI_LVD2_TRAP */

#ifdef	EE_RX200_NMI_TRAP
#pragma interrupt (EE_RX200_NMI_TRAP)
void EE_RX200_NMI_TRAP(void)
{
/*
 * NMI Pin.
 */
#ifdef	EE_RX200_NMI_PIN_TRAP
  if ( EE_RX200_ICU_NMISR & EE_RX200_ICU_NMI_PIN_MASK ) {

    EE_RX200_NMI_PIN_TRAP();

  }
#endif	/* EE_RX200_NMI_PIN_TRAP */

/*
 * Oscillation Stop Detection.
 */
#ifdef	EE_RX200_NMI_OST_TRAP
  if ( EE_RX200_ICU_NMISR & EE_RX200_ICU_NMI_OST_MASK ) {

    EE_RX200_NMI_OST_TRAP();

  }
#endif	/* EE_RX200_NMI_OST_TRAP */

/*
 * WDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_WDT_TRAP
  if ( EE_RX200_ICU_NMISR & EE_RX200_ICU_NMI_WDT_MASK ) {

    EE_RX200_NMI_WDT_TRAP();

  }
#endif	/* EE_RX200_NMI_WDT_TRAP */

/*
 * IWDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_IWDT_TRAP
  if ( EE_RX200_ICU_NMISR & EE_RX200_ICU_NMI_IWDT_MASK ) {

    EE_RX200_NMI_IWDT_TRAP();

  }
#endif	/* EE_RX200_NMI_IWDT_TRAP */

/*
 * Voltage Monitoring 1.
 */
#ifdef	EE_RX200_NMI_LVD1_TRAP
  if ( EE_RX200_ICU_NMISR & EE_RX200_ICU_NMI_LVD1_MASK ) {

    EE_RX200_NMI_LVD1_TRAP();

  }
#endif	/* EE_RX200_NMI_LVD1_TRAP */

/*
 * Voltage Monitoring 1.
 */
#ifdef	EE_RX200_NMI_LVD2_TRAP
  if ( EE_RX200_ICU_NMISR & EE_RX200_ICU_NMI_LVD2_MASK ) {

    EE_RX200_NMI_LVD2_TRAP();

  }
#endif	/* EE_RX200_NMI_LVD2_TRAP */

  /* Go into an infinite loop.*/
  while(1)
  {
  }
}

void EE_rx200_init_nmi(void)
{

/*
 * NMI Pin.
 */
#ifdef	EE_RX200_NMI_PIN_TRAP
  EE_RX200_ICU_NMIER = EE_RX200_ICU_NMI_PIN_MASK;
#endif	/* EE_RX200_NMI_PIN_TRAP */

/*
 * Oscillation Stop Detection.
 */
#ifdef	EE_RX200_NMI_OST_TRAP
  EE_RX200_ICU_NMIER = EE_RX200_ICU_NMI_OST_MASK;
#endif	/* EE_RX200_NMI_OST_TRAP */

/*
 * WDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_WDT_TRAP
  EE_RX200_ICU_NMIER = EE_RX200_ICU_NMI_WDT_MASK;
#endif	/* EE_RX200_NMI_WDT_TRAP */

/*
 * IWDT Underflow/Refresh Error.
 */
#ifdef	EE_RX200_NMI_IWDT_TRAP
  EE_RX200_ICU_NMIER = EE_RX200_ICU_NMI_IWDT_MASK;
#endif	/* EE_RX200_NMI_IWDT_TRAP */

/*
 * Voltage Monitoring 1.
 */
#ifdef	EE_RX200_NMI_LVD1_TRAP
  EE_RX200_ICU_NMIER = EE_RX200_ICU_NMI_LVD1_MASK;
#endif	/* EE_RX200_NMI_LVD1_TRAP */

/*
 * Voltage Monitoring 2.
 */
#ifdef	EE_RX200_NMI_LVD2_TRAP
  EE_RX200_ICU_NMIER = EE_RX200_ICU_NMI_LVD2_MASK;
#endif	/* EE_RX200_NMI_LVD2_TRAP */

}	/* EE_rx220_init_nmi() */

#endif	/* EE_RX200_NMI_TRAP */

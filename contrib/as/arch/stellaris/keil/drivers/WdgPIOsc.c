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

/*
 * WdgPIOsc.c Module source file.
 *
 * Precision Internal Oscillator (PIOsc) AUTOSAR WDG (Watchdog) Driver Source
 * File.
 *
 * Author:  2012,  Giuseppe Serano
 */

/*
 * WdgPIOsc.c has implicit access to the Wdg_PIOscCfg.h through the WdgPIOsc.h
 * file.
 */
#include "WdgPIOsc.h"

/* 
 * WDG087:	The Wdg module shall avoid the integration of incompatible files
 * 		by the following pre-processor checks:
 * 		For included (external) header files:
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		shall be verified.
 * 		If the values are not identical to the values expected by the
 * 		Wdg module, an error shall be reported. (BSW167, BSW004)
 */
#define	WDG_PIOSC_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_PIOSC_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_PIOSC_AR_MAJOR_VERSION ) || \
    ( WDG_PIOSC_AR_MAJOR_VERSION != WDG_PIOSC_AR_RELEASE_MAJOR_VERSION )
#error	WdgPIOsc: version mismatch.
#endif

#include "ee.h"

#include "Wdg_PIOscInternal.h"

/*
 * Global config
 */
Wdg_PIOsc_GlobalType Wdg_PIOsc_Global =
{
  WDG_UNINIT,		/* State	*/
#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_ON )
  WDGIF_OFF_MODE,	/* Mode		*/
#else	/* ( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */
  WDGIF_SLOW_MODE,	/* Mode		*/
#endif	/* !( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */
  FALSE,		/* Expired	*/
  NULL_PTR,		/* ConfigPtr	*/
};

/*
 * Turn-Off Watchdog.
 */
static void Wdg_PIOsc_Off(
  void
) {

  if ( SYSCTL_RCGCWD_R & SYSCTL_RCGCWD_R1 ) {

    SYSCTL_SRWD_R |= SYSCTL_SRWD_R1;	/* Start Reset */
    SYSCTL_SRWD_R &= ~SYSCTL_SRWD_R1;	/* Stop  Reset */

    while ( !( SYSCTL_PRWD_R & SYSCTL_PRWD_R1 ) );	/* Wait Reset */

    SYSCTL_RCGCWD_R &= ~SYSCTL_RCGCWD_R1;	/* Watchdog Off. */

  }

}

/*
 * Watchdog Mode Internal Set-up.
 */
static Std_ReturnType Wdg_PIOsc_SetMode_Internal(
  WdgIf_ModeType	Mode
) 
{

  Std_ReturnType	ret = E_OK;

  Wdg_PIOsc_Off();

  if ( Mode != WDGIF_OFF_MODE ) {

    SYSCTL_RCGCWD_R |= SYSCTL_RCGCWD_R1;	/* Watchdog On. */

    while ( !( SYSCTL_PRWD_R & SYSCTL_PRWD_R1 ) );	/* Wait Reset */

    if ( Mode == WDGIF_FAST_MODE ) {

      if ( Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast != NULL_PTR ) {

	WATCHDOG1_LOAD_R = MS_TO_TICKS(
	  Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgTimeout,
	  WDG_PIOSC_CLK_FREQ
	);

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

#ifdef	DEBUG
	WATCHDOG1_TEST_R = 
	(Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgCtl & WDT_TEST_STALL);

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );
#endif

	WATCHDOG1_CTL_R = (
	  ( 
	    Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgCtl & 
	    ( WDG_PIOSC_CTL_NMI_INT | WDG_PIOSC_CTL_RST_EN ) 
	  ) | WDT_CTL_INTEN
	);

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

	WATCHDOG1_ICR_R = WDT_ICR_M;

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

      }
      else {

	ret = E_NOT_OK;

      }

    }
    else {

      if ( Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow != NULL_PTR ) {

	WATCHDOG1_LOAD_R = MS_TO_TICKS(
	  Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgTimeout,
	  WDG_PIOSC_CLK_FREQ
	);

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

#ifdef	DEBUG
	WATCHDOG1_TEST_R = 
	(Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgCtl & WDT_TEST_STALL);

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );
#endif

	WATCHDOG1_CTL_R = (
	  ( 
	    Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgCtl & 
	    ( WDG_PIOSC_CTL_NMI_INT | WDG_PIOSC_CTL_RST_EN ) 
	  ) | WDT_CTL_INTEN
	);

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

	WATCHDOG1_ICR_R = WDT_ICR_M;

	while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

      }
      else {

	ret = E_NOT_OK;

      }

    }

  }

  if ( ret == E_OK ) {

    Wdg_PIOsc_Global.Expired = FALSE;
    Wdg_PIOsc_Global.Mode = Mode;

  }

  return ret;

}

/*
 * Wdg_PIOsc_Init implementation. (Non Re-entrant)
 */
void Wdg_PIOsc_Init(
  const Wdg_PIOsc_ConfigType *	ConfigPtr
)
{

  register EE_FREG		flags;
  register Std_ReturnType	rv;

  VALIDATE( ( ConfigPtr != NULL ), WDG_INIT_SERVICE_ID, WDG_E_PARAM_POINTER );

  VALIDATE(
    ( Hw_CheckCore() == E_OK ), WDG_INIT_SERVICE_ID, WDG_E_DRIVER_STATE
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    ( Wdg_PIOsc_Global.State != WDG_BUSY ),
    WDG_INIT_SERVICE_ID,
    WDG_E_DRIVER_STATE,
    flags
  );

  Wdg_PIOsc_Global.State = WDG_BUSY;
  Wdg_PIOsc_Global.Expired = FALSE;
  Wdg_PIOsc_Global.ConfigPtr = ConfigPtr;

  EE_hal_resumeIRQ(flags);

  rv = Wdg_PIOsc_SetMode_Internal(ConfigPtr->WdgDefaultMode);

  flags = EE_hal_suspendIRQ();

  if ( rv == E_OK ) {

    Wdg_PIOsc_Global.State = WDG_IDLE;

  }
  else {

    Wdg_PIOsc_Global.State = WDG_UNINIT;
    Wdg_PIOsc_Global.ConfigPtr = NULL_PTR;

  }

  EE_hal_resumeIRQ(flags);

}

/*
 * Wdg_PIOsc_SetMode implementation. (Non Re-entrant)
 */
Std_ReturnType Wdg_PIOsc_SetMode(
  WdgIf_ModeType	Mode
)
{

  register EE_FREG		flags;
  register Std_ReturnType	rv;

#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_OFF )
  VALIDATE_W_RV(
    ( Mode == WDGIF_OFF_MODE ),
    WDG_SETMODE_SERVICE_ID,
    WDG_E_PARAM_MODE,
    E_NOT_OK
  );
#endif

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    ( Wdg_PIOsc_Global.State == WDG_IDLE ),
    WDG_SETMODE_SERVICE_ID,
    WDG_E_DRIVER_STATE,
    E_NOT_OK,
    flags
  );

  Wdg_PIOsc_Global.State = WDG_BUSY;

  EE_hal_resumeIRQ(flags);

  rv = Wdg_PIOsc_SetMode_Internal(Mode);

  flags = EE_hal_suspendIRQ();

  Wdg_PIOsc_Global.State = WDG_IDLE;

  EE_hal_resumeIRQ(flags);

  return rv;

}

/*
 * Wdg_PIOsc_SetTriggerCondition implementation. (Non Re-entrant)
 */
void Wdg_PIOsc_SetTriggerCondition(
  uint16	Timeout
)
{

  register EE_FREG	flags;

  VALIDATE(
    ( ((float32)Timeout / 1000) < WDG_PIOSC_MAX_TIMEOUT ),
    WDG_SETTRIGGERCONDITION_SERVICE_ID,
    WDG_E_PARAM_TIMEOUT
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    ( Wdg_PIOsc_Global.State == WDG_IDLE ),
    WDG_SETTRIGGERCONDITION_SERVICE_ID,
    WDG_E_DRIVER_STATE,
    flags
  );

  Wdg_PIOsc_Global.State = WDG_BUSY;

  EE_hal_resumeIRQ(flags);

  if ( Wdg_PIOsc_Global.Mode != WDGIF_OFF_MODE ) {

    Wdg_PIOsc_Off();

    SYSCTL_RCGCWD_R |= SYSCTL_RCGCWD_R1;	/* Watchdog On. */

    while ( !( SYSCTL_PRWD_R & SYSCTL_PRWD_R1 ) );	/* Wait Reset */

    WATCHDOG1_LOAD_R = MS_TO_TICKS(Timeout, WDG_PIOSC_CLK_FREQ);

    while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

    if ( Wdg_PIOsc_Global.Mode == WDGIF_FAST_MODE ) {

#ifdef	DEBUG
      WATCHDOG1_TEST_R = 
      (Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgCtl & WDT_TEST_STALL);

      while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );
#endif

      WATCHDOG1_CTL_R = (
	  ( 
	    Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgCtl & 
	    ( WDG_PIOSC_CTL_NMI_INT | WDG_PIOSC_CTL_RST_EN ) 
	  ) | WDT_CTL_INTEN
      );

      while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

    }
    else {

#ifdef	DEBUG
      WATCHDOG1_TEST_R = 
      (Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgCtl & WDT_TEST_STALL);

      while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );
#endif

      WATCHDOG1_CTL_R = (
	  ( 
	    Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgCtl & 
	    ( WDG_PIOSC_CTL_NMI_INT | WDG_PIOSC_CTL_RST_EN ) 
	  ) | WDT_CTL_INTEN
      );

      while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

    }

    WATCHDOG1_ICR_R = WDT_ICR_M;

    while ( !( WATCHDOG1_CTL_R & WDT_CTL_WRC ) );

  }	/* if ( Wdg_PIOsc_Global.Mode != WDGIF_OFF_MODE ) */

  Wdg_PIOsc_Global.Expired = FALSE;

  flags = EE_hal_suspendIRQ();

  Wdg_PIOsc_Global.State = WDG_IDLE;

  EE_hal_resumeIRQ(flags);

}

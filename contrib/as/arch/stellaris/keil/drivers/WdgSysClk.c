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
 * WdgSysClk.c Module source file.
 *
 * System Clock AUTOSAR WDG (Watchdog) Driver Source File.
 *
 * Author:  2012,  Giuseppe Serano
 */

/*
 * WdgSysClk.c has implicit access to the Wdg_SysClkCfg.h through the
 * WdgSysClk.h file.
 */
#include "WdgSysClk.h"

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
#define	WDG_SYSCLK_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_SYSCLK_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_SYSCLK_AR_MAJOR_VERSION ) || \
    ( WDG_SYSCLK_AR_MAJOR_VERSION != WDG_SYSCLK_AR_RELEASE_MAJOR_VERSION )
#error	WdgSysClk: version mismatch.
#endif

#include "ee.h"

#include "Wdg_SysClkInternal.h"

/*
 * Global config
 */
Wdg_SysClk_GlobalType Wdg_SysClk_Global =
{
  WDG_UNINIT,		/* State	*/
#if	( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON )
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
static void Wdg_SysClk_Off(
  void
) {

  if ( SYSCTL_RCGC0_R & SYSCTL_RCGC0_WDT0 ) {

    SYSCTL_SRWD_R |= SYSCTL_SRWD_R0;	/* Start Reset */
    SYSCTL_SRWD_R &= ~SYSCTL_SRWD_R0;	/* Stop  Reset */

    while ( !( SYSCTL_PRWD_R & SYSCTL_PRWD_R0 ) );	/* Wait Reset */

    SYSCTL_RCGCWD_R &= ~SYSCTL_RCGCWD_R0;	/* Watchdog Off. */

  }

}

/*
 * Watchdog Mode Internal Set-up.
 */
static Std_ReturnType Wdg_SysClk_SetMode_Internal(
  WdgIf_ModeType	Mode
) 
{

  Std_ReturnType	ret = E_OK;

  Wdg_SysClk_Off();

  if ( Mode != WDGIF_OFF_MODE ) {

    SYSCTL_RCGCWD_R |= SYSCTL_RCGCWD_R0;	/* Watchdog On. */

    while ( !( SYSCTL_PRWD_R & SYSCTL_PRWD_R0 ) );	/* Wait Reset */

    if ( Mode == WDGIF_FAST_MODE ) {

      if ( Wdg_SysClk_Global.ConfigPtr->WdgSettingsFast != NULL_PTR ) {

	WATCHDOG0_LOAD_R = MS_TO_TICKS(
	  Wdg_SysClk_Global.ConfigPtr->WdgSettingsFast->WdgTimeout,
	  Mcu_Global.ConfigPtr->McuClockSettingConfig[
	    Mcu_Global.ClockSetting
	  ].McuClockReferencePointFrequency
	);

#ifdef	DEBUG
	WATCHDOG0_TEST_R = 
	(Wdg_SysClk_Global.ConfigPtr->WdgSettingsFast->WdgCtl & WDT_TEST_STALL);
#endif

	WATCHDOG0_CTL_R = (
	  ( 
	    Wdg_SysClk_Global.ConfigPtr->WdgSettingsFast->WdgCtl & 
	    ( WDG_SYSCLK_CTL_NMI_INT | WDG_SYSCLK_CTL_RST_EN ) 
	  ) | WDT_CTL_INTEN
	);

	WATCHDOG0_ICR_R = WDT_ICR_M;

      }
      else {

	ret = E_NOT_OK;

      }

    }
    else {

      if ( Wdg_SysClk_Global.ConfigPtr->WdgSettingsSlow != NULL_PTR ) {

	WATCHDOG0_LOAD_R = MS_TO_TICKS(
	  Wdg_SysClk_Global.ConfigPtr->WdgSettingsSlow->WdgTimeout,
	  Mcu_Global.ConfigPtr->McuClockSettingConfig[
	    Mcu_Global.ClockSetting
	  ].McuClockReferencePointFrequency
	);

#ifdef	DEBUG
	WATCHDOG0_TEST_R = 
	(Wdg_SysClk_Global.ConfigPtr->WdgSettingsSlow->WdgCtl & WDT_TEST_STALL);
#endif

	WATCHDOG0_CTL_R = (
	  ( 
	    Wdg_SysClk_Global.ConfigPtr->WdgSettingsSlow->WdgCtl & 
	    ( WDG_SYSCLK_CTL_NMI_INT | WDG_SYSCLK_CTL_RST_EN ) 
	  ) | WDT_CTL_INTEN
	);

	WATCHDOG0_ICR_R = WDT_ICR_M;

      }
      else {

	ret = E_NOT_OK;

      }

    }

  }

  if ( ret == E_OK ) {

    Wdg_SysClk_Global.Expired = FALSE;
    Wdg_SysClk_Global.Mode = Mode;

  }

  return ret;

}

/*
 * Wdg_SysClk_Init implementation. (Non Re-entrant)
 */
void Wdg_SysClk_Init(
  const Wdg_SysClk_ConfigType *	ConfigPtr
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
    ( Wdg_SysClk_Global.State != WDG_BUSY ),
    WDG_INIT_SERVICE_ID,
    WDG_E_DRIVER_STATE,
    flags
  );

  Wdg_SysClk_Global.State = WDG_BUSY;
  Wdg_SysClk_Global.Expired = FALSE;
  Wdg_SysClk_Global.ConfigPtr = ConfigPtr;

  EE_hal_resumeIRQ(flags);

  rv = Wdg_SysClk_SetMode_Internal(ConfigPtr->WdgDefaultMode);

  flags = EE_hal_suspendIRQ();

  if ( rv == E_OK ) {

    Wdg_SysClk_Global.State = WDG_IDLE;

  }
  else {

    Wdg_SysClk_Global.State = WDG_UNINIT;
    Wdg_SysClk_Global.ConfigPtr = NULL_PTR;

  }

  EE_hal_resumeIRQ(flags);

}

/*
 * Wdg_SysClk_SetMode implementation. (Non Re-entrant)
 */
Std_ReturnType Wdg_SysClk_SetMode(
  WdgIf_ModeType	Mode
)
{

  register EE_FREG		flags;
  register Std_ReturnType	rv;

#if	( WDG_SYSCLK_DISABLE_ALLOWED == STD_OFF )
  VALIDATE_W_RV(
    ( Mode == WDGIF_OFF_MODE ),
    WDG_SETMODE_SERVICE_ID,
    WDG_E_PARAM_MODE,
    E_NOT_OK
  );
#endif

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    ( Wdg_SysClk_Global.State == WDG_IDLE ),
    WDG_SETMODE_SERVICE_ID,
    WDG_E_DRIVER_STATE,
    E_NOT_OK,
    flags
  );

  Wdg_SysClk_Global.State = WDG_BUSY;

  EE_hal_resumeIRQ(flags);

  rv = Wdg_SysClk_SetMode_Internal(Mode);

  flags = EE_hal_suspendIRQ();

  Wdg_SysClk_Global.State = WDG_IDLE;

  EE_hal_resumeIRQ(flags);

  return rv;

}

/*
 * Wdg_SysClk_SetTriggerCondition implementation. (Non Re-entrant)
 */
void Wdg_SysClk_SetTriggerCondition(
  uint16	Timeout
)
{

  register EE_FREG	flags;
  register float32	freq;

  VALIDATE(
    ( ((float32)Timeout / 1000) < WDG_SYSCLK_MAX_TIMEOUT ),
    WDG_SETTRIGGERCONDITION_SERVICE_ID,
    WDG_E_PARAM_TIMEOUT
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    ( Wdg_SysClk_Global.State == WDG_IDLE ),
    WDG_SETTRIGGERCONDITION_SERVICE_ID,
    WDG_E_DRIVER_STATE,
    flags
  );

  Wdg_SysClk_Global.State = WDG_BUSY;

  freq =	Mcu_Global.ConfigPtr->McuClockSettingConfig[
			Mcu_Global.ClockSetting
		].McuClockReferencePointFrequency;

  EE_hal_resumeIRQ(flags);

  VALIDATE(
    ( ((float32)Timeout / 1000) < (0xFFFFFFFFU / freq) ),
    WDG_SETTRIGGERCONDITION_SERVICE_ID,
    WDG_E_PARAM_TIMEOUT
  );

  WATCHDOG0_LOAD_R = MS_TO_TICKS(Timeout, freq);

  WATCHDOG0_ICR_R = WDT_ICR_M;

  Wdg_SysClk_Global.Expired = FALSE;

  flags = EE_hal_suspendIRQ();

  Wdg_SysClk_Global.State = WDG_IDLE;

  EE_hal_resumeIRQ(flags);

}

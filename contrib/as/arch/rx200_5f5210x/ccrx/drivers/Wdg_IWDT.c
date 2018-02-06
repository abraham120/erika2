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
 * Wdg_IWDT.c Module source file.
 *
 * Peripheral Clock  AUTOSAR WDG (Watchdog) Driver Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

/*
 * Wdg_IWDT.c has implicit access to the Wdg_IWDT_Cfg.h through the
 * Wdg_IWDT.h file.
 */
#include "Wdg_IWDT.h"

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
#define	WDG_IWDT_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_IWDT_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_IWDT_AR_MAJOR_VERSION ) || \
    ( WDG_IWDT_AR_MAJOR_VERSION != WDG_IWDT_AR_RELEASE_MAJOR_VERSION )
#error	Wdg_IWDT: version mismatch.
#endif

#include "ee.h"

#include "Wdg_IWDT_Internal.h"

/*
 * Global config
 */
Wdg_IWDT_GlobalType Wdg_IWDT_Global =
{
		WDG_UNINIT,		/* State	*/
#if	( WDG_IWDT_DISABLE_ALLOWED == STD_ON )
		WDGIF_OFF_MODE,	/* Mode		*/
#else	/* ( WDG_IWDT_DISABLE_ALLOWED == STD_ON ) */
		WDGIF_SLOW_MODE,	/* Mode		*/
#endif	/* !( WDG_IWDT_DISABLE_ALLOWED == STD_ON ) */
		FALSE,		/* Expired	*/
		NULL_PTR,		/* ConfigPtr	*/
};


/** @brief	Set IWDG WDTCR register. That is, set clock div, time-out and window.
 *	@param  tc Time-out counter.
 *	@param  wdtcr_bits Bits to configure clock division ratio and refresh window.
 *	
 */
static void Wdg_IWDT_SetWDTCR(uint32 tc, uint16 wdtcr_bits) 
{
	/*
	* wdtcr_bits: b12, b11 ->Window Start Position
 	* wdtcr_bits: b8, b9 ->Window End Position
	* wdtcr_bits: b4, b7 ->Clock Division Ratio
	*/

	if (tc <= WDG_IWDT_TOP0) {
		WDG_IWDT_SET_IWDTCR(wdtcr_bits | WDG_IWDT_TOP0_MASK);
	} else if (tc <= WDG_IWDT_TOP1 ) {
		WDG_IWDT_SET_IWDTCR(wdtcr_bits | WDG_IWDT_TOP1_MASK);
	} else if (tc <= WDG_IWDT_TOP2 ) {
		WDG_IWDT_SET_IWDTCR(wdtcr_bits | WDG_IWDT_TOP2_MASK);
	} else {
		WDG_IWDT_SET_IWDTCR(wdtcr_bits | WDG_IWDT_TOP3_MASK);
	}
	
}

/*
 * Watchdog Mode Internal Set-up.
 */
static Std_ReturnType Wdg_IWDT_SetMode_Internal(WdgIf_ModeType	Mode) 
{
	Std_ReturnType	ret = E_OK;
	register uint32	ticks; 		/*Number of ticks */
	

	if ( Mode != WDGIF_OFF_MODE ) {
					  
		if (Mode == WDGIF_FAST_MODE) {
			ticks = MS_TO_TICKS(
				Wdg_IWDT_Global.ConfigPtr->WdgSettingsFast->WdgTimeout);
			WDG_IWDT_SET_UN_ACT(Wdg_IWDT_Global.ConfigPtr->WdgSettingsFast->WdgCtl);
			
		} else {
			ticks = MS_TO_TICKS(
				Wdg_IWDT_Global.ConfigPtr->WdgSettingsSlow->WdgTimeout);
			WDG_IWDT_SET_UN_ACT(Wdg_IWDT_Global.ConfigPtr->WdgSettingsSlow->WdgCtl);
		}
		
		if (ticks < WDG_IWDTD1_MAX_TICKS) {
			
			Wdg_IWDT_SetWDTCR( ticks / WDG_IWDT_DIV1, WDG_IWDT_DIV1_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_IWDTD16_MAX_TICKS) {
			
			Wdg_IWDT_SetWDTCR( ticks / WDG_IWDT_DIV16, WDG_IWDT_DIV16_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_IWDTD32_MAX_TICKS) {
			
			Wdg_IWDT_SetWDTCR( ticks / WDG_IWDT_DIV32, WDG_IWDT_DIV32_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_IWDTD64_MAX_TICKS) {
			
			Wdg_IWDT_SetWDTCR( ticks / WDG_IWDT_DIV64, WDG_IWDT_DIV64_MASK | 
							WDG_WDTCR_WIND_MASK);
					
		} else if (ticks < WDG_IWDTD128_MAX_TICKS) {
			
			Wdg_IWDT_SetWDTCR( ticks / WDG_IWDT_DIV128, WDG_IWDT_DIV128_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_IWDTD256_MAX_TICKS) {
			
			Wdg_IWDT_SetWDTCR( ticks / WDG_IWDT_DIV256, WDG_IWDT_DIV256_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else {
			
			ret = E_NOT_OK;
		}
	}	
  
	if ( ret == E_OK ) {
		Wdg_IWDT_Global.Expired = FALSE;
		Wdg_IWDT_Global.Mode = Mode;
		/* Start the IWDT oscillator.*/
		WDG_IWDT_CLK_START();
		/*Start WDG */
		WDG_IWDT_REFRESH();
	}

	
	return ret;

}

/*
 * Wdg_IWDT_Init implementation. (Non Re-entrant)
 */
void Wdg_IWDT_Init(const Wdg_IWDT_ConfigType *	ConfigPtr)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;

	VALIDATE( ( ConfigPtr != NULL ), WDG_INIT_SERVICE_ID, WDG_E_PARAM_POINTER );

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(( Wdg_IWDT_Global.State != WDG_BUSY ), 
			WDG_INIT_SERVICE_ID,
			WDG_E_DRIVER_STATE,
			flags);

	Wdg_IWDT_Global.State = WDG_BUSY;
	Wdg_IWDT_Global.Expired = FALSE;
	Wdg_IWDT_Global.ConfigPtr = ConfigPtr;

	EE_hal_resumeIRQ(flags);
	/* Note that WDGIF_OFF_MODE must be the mode passed by Wdg_IWDT_Init(), 
	 * otherwise Wdg_IWDT_SetMode() will not have effects. 
	 * The Watchdog module can be configured only once after reset. 
	 * Thus, ConfigPtr->WdgDefaultMode must be WDGIF_OFF_MODE.
	 */
	rv = Wdg_IWDT_SetMode_Internal(ConfigPtr->WdgDefaultMode);

	flags = EE_hal_suspendIRQ();

	if ( rv == E_OK ) {
		Wdg_IWDT_Global.State = WDG_IDLE;

	} else {

		Wdg_IWDT_Global.State = WDG_UNINIT;
		Wdg_IWDT_Global.ConfigPtr = NULL_PTR;

	}

	EE_hal_resumeIRQ(flags);

}

/*
 * Wdg_IWDT_SetMode implementation. (Non Re-entrant)
 */
Std_ReturnType Wdg_IWDT_SetMode(WdgIf_ModeType	Mode)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;

#if	( WDG_IWDT_DISABLE_ALLOWED == STD_OFF )
	VALIDATE_W_RV(( Mode != WDGIF_OFF_MODE ), 
			WDG_SETMODE_SERVICE_ID,
			WDG_E_PARAM_MODE,
			E_NOT_OK);
#endif

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Wdg_IWDT_Global.State == WDG_IDLE ), 
			WDG_SETMODE_SERVICE_ID,
			WDG_E_DRIVER_STATE,
			E_NOT_OK,
			flags);

	Wdg_IWDT_Global.State = WDG_BUSY;

	EE_hal_resumeIRQ(flags);

	rv = Wdg_IWDT_SetMode_Internal(Mode);

	flags = EE_hal_suspendIRQ();

	Wdg_IWDT_Global.State = WDG_IDLE;

	EE_hal_resumeIRQ(flags);

	return rv;
}

/*
 * Wdg_IWDT_SetTriggerCondition implementation. (Non Re-entrant)
 */
void Wdg_IWDT_SetTriggerCondition(uint16	Timeout)
{

	register EE_FREG	flags;
	
	/* Note: with this MCU the WDG can only be configured once, therefore Timeout 
	 * is not used. Should we keep it for compatibility with the AS interface or
	 * can we eliminate it?
	 */  
	/*
	register float32	freq;

	VALIDATE(( ((float32)Timeout / 1000) < WDG_IWDT_MAX_TIMEOUT ),
			WDG_SETTRIGGERCONDITION_SERVICE_ID, 
			WDG_E_PARAM_TIMEOUT);
	*/
	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(( Wdg_IWDT_Global.State == WDG_IDLE ), 
			WDG_SETTRIGGERCONDITION_SERVICE_ID,
			WDG_E_DRIVER_STATE,
			flags);

	Wdg_IWDT_Global.State = WDG_BUSY;

	/*
	freq =	Mcu_Global.ConfigPtr->McuClockSettingConfig[
			Mcu_Global.ClockSetting].McuClockReferencePointFrequency;
	freq = freq / WDG_IWDT_GET_PCKB_DIV(
			Mcu_Global.ConfigPtr->McuClockSettingConfig[
			        Mcu_Global.ClockSetting].McuRunModeClockConfiguration2);
  */
	EE_hal_resumeIRQ(flags);
/*
	VALIDATE( ( ((float32)Timeout / 1000) < (0xFFFFFFFFU / freq) ), 
			WDG_SETTRIGGERCONDITION_SERVICE_ID,
			WDG_E_PARAM_TIMEOUT);
*/
	WDG_IWDT_REFRESH();
	
	Wdg_IWDT_Global.Expired = FALSE;

	flags = EE_hal_suspendIRQ();

	Wdg_IWDT_Global.State = WDG_IDLE;

	EE_hal_resumeIRQ(flags);

}

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
 * Wdg_PCLK.c Module source file.
 *
 * Peripheral Clock  AUTOSAR WDG (Watchdog) Driver Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

/*
 * Wdg_PCLK.c has implicit access to the Wdg_PCLK_Cfg.h through the
 * Wdg_PCLK.h file.
 */
#include "Wdg_PCLK.h"

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
#define	WDG_PCLK_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_PCLK_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_PCLK_AR_MAJOR_VERSION ) || \
    ( WDG_PCLK_AR_MAJOR_VERSION != WDG_PCLK_AR_RELEASE_MAJOR_VERSION )
#error	Wdg_PCLK: version mismatch.
#endif

#include "ee.h"

#include "Wdg_PCLK_Internal.h"

/*
 * Global config
 */
Wdg_PCLK_GlobalType Wdg_PCLK_Global =
{
		WDG_UNINIT,		/* State	*/
#if	( WDG_PCLK_DISABLE_ALLOWED == STD_ON )
		WDGIF_OFF_MODE,	/* Mode		*/
#else	/* ( WDG_PCLK_DISABLE_ALLOWED == STD_ON ) */
		WDGIF_SLOW_MODE,	/* Mode		*/
#endif	/* !( WDG_PCLK_DISABLE_ALLOWED == STD_ON ) */
		FALSE,		/* Expired	*/
		NULL_PTR,		/* ConfigPtr	*/
};


/** @brief	Set WDG WDTCR register. That is, set clock div, time-out and window.
 *	@param  tc Time-out counter.
 *	@param  wdtcr_bits Bits to configure clock division ratio and refresh window.
 *	
 */
static void Wdg_PCLK_SetWDTCR(uint32 tc, uint16 wdtcr_bits) 
{
	/*
	* wdtcr_bits: b12, b11 ->Window Start Position
 	* wdtcr_bits: b8, b9 ->Window End Position
	* wdtcr_bits: b4, b7 ->Clock Division Ratio
	*/

	if (tc <= WDG_PCLK_TOP0) {
		WDG_PCLK_SET_WDTCR(wdtcr_bits | WDG_PCLK_TOP0_MASK);
	} else if (tc <= WDG_PCLK_TOP1 ) {
		WDG_PCLK_SET_WDTCR(wdtcr_bits | WDG_PCLK_TOP1_MASK);
	} else if (tc <= WDG_PCLK_TOP2 ) {
		WDG_PCLK_SET_WDTCR(wdtcr_bits | WDG_PCLK_TOP2_MASK);
	} else {
		WDG_PCLK_SET_WDTCR(wdtcr_bits | WDG_PCLK_TOP3_MASK);
	}
	
}

/*
 * Watchdog Mode Internal Set-up.
 */
static Std_ReturnType Wdg_PCLK_SetMode_Internal(WdgIf_ModeType	Mode) 
{
	Std_ReturnType	ret = E_OK;
	register float32	pclk;	/* Clock Frequency	*/
	register uint32	ticks; 		/*Number of ticks */
	

	if ( Mode != WDGIF_OFF_MODE ) {

		pclk =	Mcu_Global.ConfigPtr->McuClockSettingConfig[
				      Mcu_Global.ClockSetting].McuClockReferencePointFrequency;
		pclk = pclk / 
				GET_PCLKB_DIV(Mcu_Global.ConfigPtr->McuClockSettingConfig[
						Mcu_Global.ClockSetting].McuRunModeClockConfiguration2);
		if (Mode == WDGIF_FAST_MODE) {
			ticks = MS_TO_TICKS(
				Wdg_PCLK_Global.ConfigPtr->WdgSettingsFast->WdgTimeout, pclk);
			WDG_PCLK_SET_UN_ACT(Wdg_PCLK_Global.ConfigPtr->WdgSettingsFast->WdgCtl);
			
		} else {
			ticks = MS_TO_TICKS(
				Wdg_PCLK_Global.ConfigPtr->WdgSettingsSlow->WdgTimeout, pclk);
			WDG_PCLK_SET_UN_ACT(Wdg_PCLK_Global.ConfigPtr->WdgSettingsSlow->WdgCtl);
		}
		
		if (ticks < WDG_PCLKD4_MAX_TICKS) {
			
			Wdg_PCLK_SetWDTCR( ticks / WDG_PCLK_DIV4, WDG_PCLK_DIV4_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_PCLKD64_MAX_TICKS) {
			
			Wdg_PCLK_SetWDTCR( ticks / WDG_PCLK_DIV64, WDG_PCLK_DIV64_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_PCLKD128_MAX_TICKS) {
			
			Wdg_PCLK_SetWDTCR( ticks / WDG_PCLK_DIV128, WDG_PCLK_DIV128_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_PCLKD512_MAX_TICKS) {
			
			Wdg_PCLK_SetWDTCR( ticks / WDG_PCLK_DIV512, WDG_PCLK_DIV512_MASK | 
							WDG_WDTCR_WIND_MASK);
					
		} else if (ticks < WDG_PCLKD2048_MAX_TICKS) {
			
			Wdg_PCLK_SetWDTCR( ticks / WDG_PCLK_DIV2048, WDG_PCLK_DIV2048_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else if (ticks < WDG_PCLKD8192_MAX_TICKS) {
			
			Wdg_PCLK_SetWDTCR( ticks / WDG_PCLK_DIV8192, WDG_PCLK_DIV8192_MASK | 
							WDG_WDTCR_WIND_MASK);
			
		} else {
			
			ret = E_NOT_OK;
		}
	}	
  
	if ( ret == E_OK ) {
		Wdg_PCLK_Global.Expired = FALSE;
		Wdg_PCLK_Global.Mode = Mode;
			/*Start WDG */
		WDG_PCLK_REFRESH();
	}
	
	return ret;

}

/*
 * Wdg_PCLK_Init implementation. (Non Re-entrant)
 */
void Wdg_PCLK_Init(const Wdg_PCLK_ConfigType *	ConfigPtr)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;

	VALIDATE( ( ConfigPtr != NULL ), WDG_INIT_SERVICE_ID, WDG_E_PARAM_POINTER );

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(( Wdg_PCLK_Global.State != WDG_BUSY ), 
			WDG_INIT_SERVICE_ID,
			WDG_E_DRIVER_STATE,
			flags);

	Wdg_PCLK_Global.State = WDG_BUSY;
	Wdg_PCLK_Global.Expired = FALSE;
	Wdg_PCLK_Global.ConfigPtr = ConfigPtr;

	EE_hal_resumeIRQ(flags);
	/* Note that WDGIF_OFF_MODE must be the mode passed by Wdg_PCLK_Init(), 
	 * otherwise Wdg_PCLK_SetMode() will not have effects. 
	 * The Watchdog module can be configured only once after reset. 
	 * Thus, ConfigPtr->WdgDefaultMode must be WDGIF_OFF_MODE.
	 */
	rv = Wdg_PCLK_SetMode_Internal(ConfigPtr->WdgDefaultMode);

	flags = EE_hal_suspendIRQ();

	if ( rv == E_OK ) {

		Wdg_PCLK_Global.State = WDG_IDLE;

	} else {

		Wdg_PCLK_Global.State = WDG_UNINIT;
		Wdg_PCLK_Global.ConfigPtr = NULL_PTR;

	}

	EE_hal_resumeIRQ(flags);

}

/*
 * Wdg_PCLK_SetMode implementation. (Non Re-entrant)
 */
Std_ReturnType Wdg_PCLK_SetMode(WdgIf_ModeType	Mode)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;

#if	( WDG_PCLK_DISABLE_ALLOWED == STD_OFF )
	VALIDATE_W_RV(( Mode != WDGIF_OFF_MODE ), 
			WDG_SETMODE_SERVICE_ID,
			WDG_E_PARAM_MODE,
			E_NOT_OK);
#endif

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Wdg_PCLK_Global.State == WDG_IDLE ), 
			WDG_SETMODE_SERVICE_ID,
			WDG_E_DRIVER_STATE,
			E_NOT_OK,
			flags);

	Wdg_PCLK_Global.State = WDG_BUSY;

	EE_hal_resumeIRQ(flags);

	rv = Wdg_PCLK_SetMode_Internal(Mode);

	flags = EE_hal_suspendIRQ();

	Wdg_PCLK_Global.State = WDG_IDLE;

	EE_hal_resumeIRQ(flags);

	return rv;
}

/*
 * Wdg_PCLK_SetTriggerCondition implementation. (Non Re-entrant)
 */
void Wdg_PCLK_SetTriggerCondition(uint16	Timeout)
{

	register EE_FREG	flags;
	
	/* Note: with this MCU the WDG can only be configured once, therefore Timeout 
	 * is not used. Should we keep it for compatibility with the AS interface or
	 * can we eliminate it?
	 */  
	/*
	register float32	freq;

	VALIDATE(( ((float32)Timeout / 1000) < WDG_PCLK_MAX_TIMEOUT ),
			WDG_SETTRIGGERCONDITION_SERVICE_ID, 
			WDG_E_PARAM_TIMEOUT);
	*/
	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(( Wdg_PCLK_Global.State == WDG_IDLE ), 
			WDG_SETTRIGGERCONDITION_SERVICE_ID,
			WDG_E_DRIVER_STATE,
			flags);

	Wdg_PCLK_Global.State = WDG_BUSY;

	/*
	freq =	Mcu_Global.ConfigPtr->McuClockSettingConfig[
			Mcu_Global.ClockSetting].McuClockReferencePointFrequency;
	freq = freq / WDG_PCLK_GET_PCKB_DIV(
			Mcu_Global.ConfigPtr->McuClockSettingConfig[
			        Mcu_Global.ClockSetting].McuRunModeClockConfiguration2);
  */
	EE_hal_resumeIRQ(flags);
/*
	VALIDATE( ( ((float32)Timeout / 1000) < (0xFFFFFFFFU / freq) ), 
			WDG_SETTRIGGERCONDITION_SERVICE_ID,
			WDG_E_PARAM_TIMEOUT);
*/
	WDG_PCLK_REFRESH();
	
	Wdg_PCLK_Global.Expired = FALSE;

	flags = EE_hal_suspendIRQ();

	Wdg_PCLK_Global.State = WDG_IDLE;

	EE_hal_resumeIRQ(flags);

}

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

/** @file	Wdg_PCLK_Internal.h
 *  @brief	AUTOSAR-"like" Peripher Clock WDG (Watchdog) Driver Internal Header
 *  		File.
 *
 *  <b>WDG148</b>:	Each variable that shall be accessible by AUTOSAR
 *  			Debugging shall be defined as global variable.
 *
 *  <b>WDG149</b>:	All type definitions of variables which shall be
 *  			debugged shall be accessible by the header file Wdg.h.
 *
 *  <b>WDG150</b>:	The declaration of variables in the header file shall be
 *  			such, that it is possible to calculate the size of the
 *  			variables by C-"sizeof".
 *
 *  <b>WDG151</b>:	Variables available for debugging shall be described in
 *  			the respective Basic Software Module Description.
 *
 *  <b>WDG152</b>:	The internal state of the module (which indicates
 *  			whether it is not initialized, idle or busy) shall be
 *  			available for debugging.
 *
 *  <b>WDG153</b>:	The internal variable for the watchdog timeout counter
 *  			shall be available for debugging.
 *
 *  <b>WDG154</b>:	The internal variable for the watchdog mode shall be
 *  			available for debugging.
 *
 *  @author	Gianluca Franchino
 *  @date	2013
 */

#if	( WDG_PCLK_DEV_ERROR_DETECT == STD_ON )
/*
 * WDG062:	The Wdg module shall take the values for production code Event
 * 		Ids from the file Dem_IntErrId.h which is included via Dem.h.
 * 		(BSW00409)
 *
 * WDG063:	Development error values are of type uint8.
 *
 * WDG010:	The Wdg module shall detect the following errors and exceptions
 * 		depending on its configuration (development/production mode):
 * 		- WDG_E_DRIVER_STATE	(0x10):	API service used in wrong
 * 						context (e.g. module not
 * 						initialized).
 * 		- WDG_E_PARAM_MODE	(0x11):
 * 		- WDG_E_PARAM_CONFIG	(0x12):	API service called with wrong /
 * 						inconsistent parameter(s).
 * 		- WDG_E_PARAM_TIMEOUT	(0x13):	The passed timeout value is
 * 						higher than the maximum timeout
 * 						value.
 * 		- WDG_E_PARAM_POINTER	(0x14):	API is called with wrong pointer
 * 						value (e.g. NULL pointer).
 * 		- WDG_E_MODE_FAILED:		Setting a watchdog mode failed
 * 						(during initialization or mode
 * 						switch).
 * 		- WDG_E_DISABLE_REJECTED:	Initialization or watchdog mode
 * 						switch failed because it would
 * 						disable the watchdog though this
 * 						is not allowed in this
 * 						configuration.
 *
 * WDG045:	The detection of development errors is configurable by the
 * 		parameter WdgDevErrorDetect. (BSW00386, BSW00350)
 *
 * WDG064:	If the WdgDevErrorDetect switch is enabled, API parameter
 * 		checking is enabled. (BSW00386)
 *
 * WDG065:	The detection of production code errors cannot be switched off.
 * 		(BSW00386)
 *
 * WDG066:	Detected evelopment errors shall be reported to the Development
 * 		Error Tracer (DET) if the pre-processor switch WdgDevErrorDetect
 * 		is set. The error codes shall not be used as return values of
 * 		the called function. (BSW00369)
 *
 * WDG013:	Additional errors that are detected because of specific
 * 		implementation and/or specific hardware properties shall be
 * 		added in the module's implementation documentation. The
 * 		classification and enumeration shall be compatible to the errors
 * 		listed above [WDG010]. (BSW00337, BSW00385, BSW00327, BSW00331)
 */

/** API service used in wrong context (e.g. module not initialized). */
#define	WDG_E_DRIVER_STATE	0x10
/** API service called with wrong / inconsistent parameter(s) */
#define	WDG_E_PARAM_MODE	0x11
/** API service called with wrong / inconsistent parameter(s) */
#define	WDG_E_PARAM_CONFIG	0x12
/** The passed timeout value is higher than the maximum timeout value. */
#define	WDG_E_PARAM_TIMEOUT	0x13
/** API is called with wrong pointer value (e.g. NULL pointer). */
#define	WDG_E_PARAM_POINTER	0x14

/*
 * Service ID's
 */
#define	WDG_INIT_SERVICE_ID			0x00
#define	WDG_SETMODE_SERVICE_ID			0x01
#define	WDG_SETTRIGGERCONDITION_SERVICE_ID	0x03
#define	WDG_GETVERSIONINFO_SERVICE_ID		0x04


/* Development error macros. */
#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PCLK_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PCLK_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PCLK_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PCLK_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* WDG_PIOSC_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#endif	/* ( WDG_PCLK_DEV_ERROR_DETECT == STD_ON ) */

#include "Hardware.h"

#include "Mcu.h"

/*Bit masks used to get the pckb (Peripheral Clock B) divisor. */
#define PCKB_BITS_SHIFT_MASK 0x08
#define PCKB_BITS_MASK 0x0F

/*Pclkb divisor values. */
#define WDG_PCLK_DIV4		4
#define WDG_PCLK_DIV64		64
#define WDG_PCLK_DIV128		128
#define WDG_PCLK_DIV512		512
#define WDG_PCLK_DIV2048	2048
#define WDG_PCLK_DIV8192	8192
/*Bit masks used to set the pclkb divisor. */
#define WDG_PCLK_DIV4_MASK		0x0010
#define WDG_PCLK_DIV64_MASK		0x0040
#define WDG_PCLK_DIV128_MASK	0x00F0
#define WDG_PCLK_DIV512_MASK	0x0060
#define WDG_PCLK_DIV2048_MASK	0x0070
#define WDG_PCLK_DIV8192_MASK	0x0080
/*Max Cycles of PCLK Clock for each pclk Divisor*/
#define WDG_PCLKD4_MAX_TICKS	65536
#define WDG_PCLKD64_MAX_TICKS	1048576
#define WDG_PCLKD128_MAX_TICKS	2097152
#define WDG_PCLKD512_MAX_TICKS	8388608
#define WDG_PCLKD2048_MAX_TICKS	33554432
#define WDG_PCLKD8192_MAX_TICKS	134217728

/*Time-Out Period values. */
#define	WDG_PCLK_TOP0	1024
#define WDG_PCLK_TOP1	4096
#define WDG_PCLK_TOP2	8192
#define WDG_PCLK_TOP3	16384
/*Bit masks used to set Time-Out Period. */
#define WDG_PCLK_TOP0_MASK		0x0000
#define WDG_PCLK_TOP1_MASK		0x0001
#define WDG_PCLK_TOP2_MASK		0x0002
#define WDG_PCLK_TOP3_MASK		0x0003
/*Bit masks used to set Window start and stop bits. */
#define WDG_WDTCR_WIND_MASK		0x3300

#define WDG_WDTAR_CLEAR_UNDFF_FLAG		0xBFFF
#define WDG_WDTAR_CLEAR_REFEF_FLAG		0x7FFF
#define WDG_WDTSR_UNDFF_FLAG_MASK 		0x4000


/*
 * Macros used to set the WDTCR register.
 */
#define WDG_PCLK_SET_WDTCR(_val) \
	(EE_HWREG16(HW_WDTCR_ADDR) = _val)

/*
 * Get the WDTCR register value.
 */
#define WDG_PCLK_GET_WDTSR() ( EE_HWREG16(HW_WDTSR_ADDR) )

/*
 * Clear the UNDFF flag in the WDTCR register.
 */
#define WDG_PCLK_RESET_WDTSR_UNDFF() \
	( EE_HWREG16(HW_WDTSR_ADDR) = WDG_WDTAR_CLEAR_UNDFF_FLAG)

/*
 * Clear the REFEF flag in the WDTCR register.
 */
#define WDG_PCLK_RESET_WDTSR_REFEF() \
	( EE_HWREG16(HW_WDTSR_ADDR) = WDG_WDTAR_CLEAR_REFEF_FLAG)

/*
 * Macros used to start/refresh the watchdog.
 */
#define WDG_PCLK_REFRESH() \
	do {\
		EE_HWREG8(HW_WDTRR_ADDR) = 0;\
		EE_HWREG8(HW_WDTRR_ADDR) = 0xFF;\
} while(0)

/** @brief	Set WDG refresh window and select WDG action: either NMI or reset.
 *	@param  _val Configuration value.
 */
#define WDG_PCLK_SET_UN_ACT(_val) \
	do {\
		EE_HWREG8(HW_WDTRCR_ADDR) = _val;\
		EE_HWREG8(HW_ICU_NMIER) = (~_val & 0x80) >> 0x05;\
} while(0)


/** @brief
 *
 *  Utility Macro that convert an amount of milli-seconds in number of ticks of
 *  a given frequency
 */
#define MS_TO_TICKS(MS, FREQ_HZ)	((uint32)((MS) * ((FREQ_HZ) / 1000U)))

/** @brief
 *
 *  Utility Macro that return PCLKB divisor.
 */
#define GET_PCLKB_DIV(_clk_conf) \
	( 0x1 << ((_clk_conf >> PCKB_BITS_SHIFT_MASK) & PCKB_BITS_MASK) )


/*
 * MCU Global Configuration Reference
 */
typedef struct
{
	boolean			Init;					/* MCU Driver Initialized?    */

	const Mcu_ConfigType *	ConfigPtr;		/* Actual Configuration	      */

	Mcu_ClockType			ClockSetting;	/* Actual Clock Setting	      */

} Mcu_GlobalType;

/*
 * MCU Global Configuration External Reference
 */
extern Mcu_GlobalType Mcu_Global;


/*
 * WDG Status Type
 */
typedef enum {
	WDG_UNINIT = 0,	/**< The Wdg Driver is not initialized or not usable. */
	WDG_IDLE,		/**< The Wdg Driver is currently not being triggered or
  			  	  	  *  switched.					      */
	WDG_BUSY		/**< The Wdg Driver is currently being triggered or
  			  	  	  *  switched.					     */
}	Wdg_PCLK_StatusType;

/*
 * Type that holds all global data for PCLK Wdg Driver.
 */
typedef struct {

	Wdg_PCLK_StatusType		State;			/* WDG State		      */

	WdgIf_ModeType		Mode;				/* WDG Mode		      */

	boolean			Expired;				/* WDG Timeout Expired	      */

	const Wdg_PCLK_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

} Wdg_PCLK_GlobalType;

/*
 * Global config
 */
extern	Wdg_PCLK_GlobalType	Wdg_PCLK_Global;

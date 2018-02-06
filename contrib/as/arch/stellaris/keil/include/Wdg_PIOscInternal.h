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

/** @file	Wdg_PIOscInternal.h
 *  @brief	AUTOSAR-"like" PIOsc WDG (Watchdog) Driver Internal Header File.
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
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#if	( WDG_PIOSC_DEV_ERROR_DETECT == STD_ON )
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
    Det_ReportError(WDG_PIOSC_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PIOSC_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PIOSC_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(WDG_PIOSC_MODULE_ID,0,_api,_err); \
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

#endif	/* ( WDG_PIOSC_DEV_ERROR_DETECT == STD_ON ) */

#include "Hardware.h"

/** @brief
 *
 *  Utility Macro that convert an amount of milli-seconds in number of ticks of
 *  a given frequency
 */
#define MS_TO_TICKS(MS, FREQ_HZ)	((uint32)((MS) * ((FREQ_HZ) / 1000U)))

/*
 * WDG Status Type
 */
typedef enum {
  WDG_UNINIT = 0,	/**< The Wdg Driver is not initialized or not usable. */
  WDG_IDLE,		/**< The Wdg Driver is currently not being triggered or
  			  *  switched.					      */
  WDG_BUSY		/**< The Wdg Driver is currently being triggered or
  			  *  switched.					     */
}	Wdg_PIOsc_StatusType;

/*
 * Type that holds all global data for PIOsc Wdg Driver.
 */
typedef struct {

  Wdg_PIOsc_StatusType		State;		/* WDG State		      */

  WdgIf_ModeType		Mode;		/* WDG Mode		      */

  boolean			Expired;	/* WDG Timeout Expired	      */

  const Wdg_PIOsc_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

}	Wdg_PIOsc_GlobalType;

/*
 * Global config
 */
extern	Wdg_PIOsc_GlobalType Wdg_PIOsc_Global;

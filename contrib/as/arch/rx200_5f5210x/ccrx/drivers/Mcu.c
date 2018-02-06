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
 * Author:  2012,  Gianluca Franchino
 */

#define	MCU_AR_RELEASE_MAJOR_VERSION	4
#define	MCU_AR_RELEASE_MINOR_VERSION	0

#include "Mcu.h"

/*
 * MCU110:	For included (external) header files:
 * 		- <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * 		shall be verified.
 */
#if !defined( MCU_AR_MAJOR_VERSION ) || \
    ( MCU_AR_MAJOR_VERSION != MCU_AR_RELEASE_MAJOR_VERSION )
#error	Mcu: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(MCU_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* MCU_DEV_ERROR_DETECT */

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

#endif	/* !MCU_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Mcu
 */
typedef struct
{
	boolean			Init;		/* MCU Driver Initialized? */

	const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration */

	Mcu_ClockType			ClockSetting;	/* Actual Clock Setting */

} Mcu_GlobalType;


/*
 * MCU Global Configuration
 */
Mcu_GlobalType Mcu_Global =
{
	FALSE,			/* Init		*/
	NULL_PTR,			/* ConfigPtr	*/
	MCU_CLOCK_MODE_NORMAL		/* ClockSetting	*/
};

#include "Hardware.h"	/* Hardware Abstraction Header File. */

/*
 * Mcu_Init implementation.
 */
void Mcu_Init( const Mcu_ConfigType * ConfigPtr)
{
	register EE_FREG	flags;

	VALIDATE( ( ConfigPtr != NULL ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

	//VALIDATE( ( Hw_CheckCore() == E_OK ), MCU_INIT_SERVICE_ID, MCU_E_UNINIT );

	flags = EE_hal_suspendIRQ();

	Mcu_Global.ConfigPtr = ConfigPtr;
	Mcu_Global.Init = TRUE;

	EE_hal_resumeIRQ(flags);

}

/*
 * Mcu_InitRamSection implementation
 */
Std_ReturnType Mcu_InitRamSection( Mcu_RamSectionType RamSection)
{

	register EE_FREG			flags;
#if	0
	register uint32			idx;
#endif

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(
					  Mcu_Global.Init,
					  MCU_INITRAMSECTION_SERVICE_ID,
					  MCU_E_UNINIT,
					  E_NOT_OK,
					  flags
					  );

	VALIDATE_IRQ_W_RV(
					  ( RamSection < Mcu_Global.ConfigPtr->McuRamSectors ),
					  MCU_INITRAMSECTION_SERVICE_ID,
					  MCU_E_PARAM_RAMSECTION,
					  E_NOT_OK,
					  flags
					  );

  /* NOT YET IMPLEMENTED, reason: no support for external RAM */
#if	0
	for (
		 idx = 0;
		 idx < cfg->McuRamSectorSettingConf[RamSection].McuRamSectionSize;
		 idx++
		 ) {
			(
			 (
			  (uint8 *)
			  cfg->McuRamSectorSettingConf[RamSection].McuRamSectionBaseAddress
			  ) + idx
			 ) = cfg->McuRamSectorSettingConf[RamSection].McuRamDefaultValue;

		}
#endif	/* 0 */

	EE_hal_resumeIRQ(flags);

	return E_NOT_OK;
}



/*
 * Mcu_InitSystemClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )
static Std_ReturnType Mcu_InitSystemClock( 
		const Mcu_ClockSettingConfigType *ConfigPtr)
{
	
	volatile uint16 i;
	
	/*
	 * If ROM (Flash Memory for Code Storage) is in P/E mode or a transition to 
	 * operating power is in progress, writing to clock registers is prohibited.
	 */
	if (FLASH.FENTRYR.BIT.FENTRY || SYSTEM.OPCCR.BIT.OPCMTSF) {
	
		return E_NOT_OK;
	}
	
	
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	
	/*
	 * If the Clock Setting ID specifies the LOCO clock do nothing, this is 
	 * the default setting. 
	 */
	if ( ConfigPtr->McuClockSettingId == MCU_CLK_MODE_LOCO_I1_B1 ) {
		
		return E_OK;
	}
	
	
	if ( ConfigPtr->McuRunModeClockConfiguration & MCU_SCKCR3_CKSEL_HOCO ) {
		
		/* High-Speed Clocl Oscillator wait control register    */
		/* 33792 cycles -> wait at least ~1 ms  (HOCO = 32MHz ) */
		SYSTEM.HOCOWTCR2.BYTE = 0x0F;
		/* Select the HOCO working freq.						*/
		SYSTEM.HOCOCR2.BYTE |=  (ConfigPtr->McuRunModeClockConfiguration & 
								0x18000000) >> 27;
		/* HOCO ON												*/
		SYSTEM.HOCOCR.BYTE = 0x00;
		
	} else if ( ConfigPtr->McuRunModeClockConfiguration & 
			   MCU_SCKCR3_CKSEL_MAIN ) {
		/* Main clock oscillator wait control register			*/
		/* 65536 cycles -> wait at least 2 ms  (XTAL = 20MHz )  */
		SYSTEM.MOSCWTCR.BYTE = 0x0C;
		/* XTAL ON */
		SYSTEM.MOSCCR.BYTE = 0x00;
		
	} else {
		
		/*If PLL is not stopped, stop it.*/
		if (SYSTEM.PLLCR2.BYTE != 0x01) {
			/* Unselect PLL and select LOCO						*/
			SYSTEM.SCKCR3.BIT.CKSEL = 0;
			/* Stop PLL											*/
			SYSTEM.PLLCR2.BYTE = 0x01;
			/* Delay a little to let PLL to stop.				*/
			for (i = 0; i < 100; i++) {	
			}
			
		}
		/* Main clock oscillator wait control register			*/
		/* 65536 cycles -> wait at least 2 ms  (XTAL = 20MHz )  */
		SYSTEM.MOSCWTCR.BYTE = 0x0C;
		/* PLL wait control register							*/
		/* 262144 cycles										*/
		SYSTEM.PLLWTCR.BYTE = 0x0B;
		
		/* Set DIV and MUL factors of PLL						*/
		SYSTEM.PLLCR.WORD = (ConfigPtr->McuRunModeClockConfiguration >> 11) & 
							0x3FFF;
		/* XTAL ON												*/
		SYSTEM.MOSCCR.BYTE = 0x00;				
		/* PLL ON												*/									
		SYSTEM.PLLCR2.BYTE = 0x00;
		
	}
	
	/* Delay a little to let the source clock to settle.		*/
	for (i = 0; i < 10000; i++) {	
	}
	
	/*
	 * Set Main Clock Oscillator Forced Oscillation Control Register (MOFCR)
	 */
	SYSTEM.MOFCR.BYTE |= ConfigPtr->McuRunModeClockConfiguration;
		
	/*
	 * Set system (ICLK) and peripheral module B (PCLKB) clocks
	 */
	SYSTEM.SCKCR.LONG  |= ConfigPtr->McuRunModeClockConfiguration2;		
 	
	/* Select the source for system clock (bits 8:10) */
	SYSTEM.SCKCR3.WORD |=  (ConfigPtr->McuRunModeClockConfiguration & 0x700);
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;
	
	return E_OK;

}
#endif

/*
 * Mcu_InitClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )
Std_ReturnType Mcu_InitClock( Mcu_ClockType ClockSetting )
{
	register EE_FREG			flags;
	register Std_ReturnType		ret;

	VALIDATE_W_RV(
				( ClockSetting <= MCU_CLOCK_MODES_NUMBER ),
				  MCU_INITCLOCK_SERVICE_ID,
				  MCU_E_PARAM_CLOCK,
				  E_NOT_OK
				  );

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(
					  Mcu_Global.Init,
					  MCU_INITCLOCK_SERVICE_ID,
					  MCU_E_UNINIT,
					  E_NOT_OK,
					  flags
					  );

	ret = Mcu_InitSystemClock(
					&Mcu_Global.ConfigPtr->McuClockSettingConfig[ClockSetting]
							  );

	if ( ret == E_OK ) {
	  
		Mcu_Global.ClockSetting = ClockSetting;
		
		//return E_OK;
	}

	EE_hal_resumeIRQ(flags);

	return ret;

}
#endif

/*
 * Mcu_DistributePllClock implementation
 */
#if ( MCU_NO_PLL == STD_OFF )
void Mcu_DistributePllClock(void)
{
	/* NOT IMPLEMENTED: meaningless in this hardware */
}
#endif

/*
 * Mcu_GetPllStatus implementation
 */
Mcu_PllStatusType Mcu_GetPllStatus(void)
{

	register EE_FREG	flags;
	register Mcu_PllStatusType	ret;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(
					  Mcu_Global.Init,
					  MCU_GETPLLSTATUS_SERVICE_ID,
					  MCU_E_UNINIT,
					  MCU_PLL_STATUS_UNDEFINED,
					  flags
					  );

#if ( MCU_NO_PLL == STD_ON )
	ret = MCU_PLL_STATUS_UNDEFINED;
#else
	if (SYSTEM.PLLCR2.BYTE)
		ret = MCU_PLL_UNLOCKED;
	else
		ret = MCU_PLL_LOCKED;
#endif

	EE_hal_resumeIRQ(flags);

	return ret;

}

/*
 * Mcu_GetResetReason implementation
 */
Mcu_ResetType Mcu_GetResetReason(void) 
{

	register EE_FREG	flags;

	register uint8		resc;
	register Mcu_ResetType	ret;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(
					  Mcu_Global.Init,
					  MCU_GETRESETREASON_SERVICE_ID,
					  MCU_E_UNINIT,
					  MCU_RESET_UNDEFINED,
					  flags
					  );

	/* Read reset reason							*/
	resc = (SYSTEM.RSTSR0.BYTE & 0x8F) | (SYSTEM.RSTSR2.BYTE << 4);
	/* Clear reset registers						*/
	SYSTEM.RSTSR0.BYTE = SYSTEM.RSTSR2.BYTE = 0x00;
	
	if ( resc & SYS_RESC_POR ) {
		ret = MCU_POWER_ON_RESET;
	} else if ( resc & (SYS_RESC_IWDT | SYS_RESC_WDT) ) {
		ret = MCU_WATCHDOG_RESET;
	} else if (resc & SYS_RESC_SW) {
		ret = MCU_SW_RESET;
	} else {
		ret = MCU_RESET_UNDEFINED;
	}

	EE_hal_resumeIRQ(flags);

	return ret;

}

/*
 * Mcu_GetResetRawValue implementation
 */
Mcu_RawResetType Mcu_GetResetRawValue(void)
{

	register EE_FREG		flags;
	register Mcu_RawResetType	ret;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(
					  Mcu_Global.Init,
					  MCU_GETRESETREASON_SERVICE_ID,
					  MCU_E_UNINIT,
					  0x00000000U,
					  flags
					  );

	/* Read reset reason								*/
	ret = (SYSTEM.RSTSR0.BYTE & 0x8F) | (SYSTEM.RSTSR2.BYTE << 4);
	/* Clear reset registers							*/
	SYSTEM.RSTSR0.BYTE = SYSTEM.RSTSR2.BYTE = 0x00;

	EE_hal_resumeIRQ(flags);

	return ret;

}

#if ( MCU_PERFORM_RESET_API == STD_ON )
/*
 * Mcu_PerformReset implementation
 */
void Mcu_PerformReset(void)
{

	register EE_FREG	flags;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(
				 Mcu_Global.Init,
				 MCU_PERFORMRESET_SERVICE_ID,
				 MCU_E_UNINIT,
				 flags
				 );
	
	/* Allow the writing to SWRR register 				*/
	SYSTEM.PRCR.WORD = 0xA502;
	
	/* Perform software reset							*/
	SYSTEM.SWRR.WORD = 0xA501;
	
	/* Protect the writing to SWRR register 			*/
	SYSTEM.PRCR.WORD = 0xA500;
	
	EE_hal_resumeIRQ(flags);
	
	while(TRUE);	/* Waiting for Reset to perform.	*/	


}
#endif

/*
 * Mcu_SetMode implementation
 */
void Mcu_SetMode(Mcu_ModeType McuMode)
{

  register EE_FREG			flags;

  flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ( 
				 Mcu_Global.Init, 
				 MCU_SETMODE_SERVICE_ID, 
				 MCU_E_UNINIT, 
				 flags );

	VALIDATE_IRQ( 
				 ( McuMode < Mcu_Global.ConfigPtr->McuNumberOfMcuModes ),
				 MCU_SETMODE_SERVICE_ID,
				 MCU_E_PARAM_MODE,
				 flags
				 );

  /* NOT YET IMPLEMENTED, reason: operational mode only */

  EE_hal_resumeIRQ(flags);

}

/*
 * Mcu_GetRamState implementation
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
Mcu_RamStateType Mcu_GetRamState(
  void
)
{

  register EE_FREG		flags;
  register Mcu_RamStateType	rv;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Mcu_Global.Init,
    MCU_GETRAMSTATE_SERVICE_ID,
    MCU_E_UNINIT,
    MCU_RAMSTATE_INVALID,
    flags
  );

  rv = MCU_RAMSTATE_INVALID;

  /* NOT YET IMPLEMENTED, reason: no support for external RAM */

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif

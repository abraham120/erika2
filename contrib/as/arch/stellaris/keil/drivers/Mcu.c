/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Author:  2011,  Giuseppe Serano
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
void Mcu_Init(
  const Mcu_ConfigType * ConfigPtr
)
{

  register EE_FREG	flags;

  VALIDATE( ( ConfigPtr != NULL ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );

  VALIDATE( ( Hw_CheckCore() == E_OK ), MCU_INIT_SERVICE_ID, MCU_E_UNINIT );

  flags = EE_hal_suspendIRQ();

#if ( \
  !( \
      defined(__OO_BCC1__) || defined(__OO_BCC2__) || \
      defined(__OO_ECC1__) || defined(__OO_ECC2__) \
  ) \
)
  if ( !Mcu_Global.Init ) {

    EE_system_init();

  }
#endif	/* 
	 * !(
	 *   defined(__OO_BCC1__) || defined(__OO_BCC2__) ||
	 *   defined(__OO_ECC1__) || defined(__OO_ECC2__)
	 * )
	 */

  Mcu_Global.ConfigPtr = ConfigPtr;
  Mcu_Global.Init = TRUE;

  EE_hal_resumeIRQ(flags);

}

/*
 * Mcu_InitRamSection implementation
 */
Std_ReturnType Mcu_InitRamSection(
  Mcu_RamSectionType RamSection
)
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
  const Mcu_ClockSettingConfigType *ConfigPtr
)
{
  register Std_ReturnType	ret = E_OK;
#ifdef	__AS_MCU_INTERNAL_OSCILLATOR_CALIBRATION__
  register uint32		attempt;
#endif	/* __AS_MCU_INTERNAL_OSCILLATOR_CALIBRATION__ */

  register uint32 rccsrc;	/* Run-Mode Clock Configuration Source        */
  register uint32 rcc2src;	/* Run-Mode Clock Configuration 2 Source      */
  register uint32 rccdst;	/* Run-Mode Clock Configuration Destination   */
  register uint32 rcc2dst;	/* Run-Mode Clock Configuration 2 Destination */

#ifdef	__AS_MCU_INTERNAL_OSCILLATOR_CALIBRATION__
  register uint32 rccorig;	/* Run-Mode Clock Configuration Original      */
  register uint32 rcc2orig;	/* Run-Mode Clock Configuration 2 Original    */

  rccorig = SYSCTL_RCC_R;
  rcc2orig = SYSCTL_RCC2_R;
#endif	/* __AS_MCU_INTERNAL_OSCILLATOR_CALIBRATION__ */

  rccsrc = ConfigPtr->McuRunModeClockConfiguration | SYSCTL_RCC_BYPASS;
  rcc2src = ConfigPtr->McuRunModeClockConfiguration2 | SYSCTL_RCC2_BYPASS2;

  /* Configuring the microcontroller to run of a "raw" clock source */
  rccdst =	SYSCTL_RCC_SYSDIV_M	| /* Reset System Clock Divisor.      */
		SYSCTL_RCC_PWMDIV_M	| /* Reset PWM Unit Clock Divisor.    */
		SYSCTL_RCC_PWRDN 	| /* PLL Power-Down		      */
		SYSCTL_RCC_BYPASS	| /* PLL Bypass			      */
		SYSCTL_RCC_XTAL_16MHZ	| /* 16MHz			      */
		SYSCTL_RCC_OSCSRC_INT	| /* Precision Internal Oscillator    */
		SYSCTL_RCC_MOSCDIS;	  /* Disable Main Oscillator	      */

  rcc2dst =	SYSCTL_RCC2_SYSDIV2_M	| /* Reset System Clock Divisor.      */
		SYSCTL_RCC2_SYSDIV2LSB	| /* Additional LSB for SYSDIV2.      */
		SYSCTL_RCC2_USBPWRDN	| /* Power-Down USB PLL.	      */
		SYSCTL_RCC2_PWRDN2	| /* PLL Power-Down		      */
		SYSCTL_RCC2_BYPASS2	| /* PLL Bypass			      */
		SYSCTL_RCC2_OSCSRC2_IO;	  /* Precision Internal Oscillator    */

  /* 
   * IMPORTANT:	Write the RCC register prior to writing the RCC2 register.
   */
  SYSCTL_RCC_R = rccdst;		/* Write RCC			      */
  SYSCTL_RCC2_R = rcc2dst;		/* Write RCC2			      */

#ifdef	__AS_MCU_INTERNAL_OSCILLATOR_CALIBRATION__
  /* PIOSC Automatic Calibration using Hibernation Module if present */
  if ( SYSCTL_PPHIB_R & SYSCTL_PPHIB_P0) {

    /* Hibernation Module Clock Gating */
    SYSCTL_RCGCHIB_R |= SYSCTL_RCGCHIB_R0;

    /* Hibernation Module 32.768-kHz Oscillator Enable. */
    HIB_CTL_R |= HIB_CTL_CLK32EN;

    /* Wait Hibenation Module 32.768-kHz Oscillator to Enable. */
    while ( !((HIB_RIS_R & HIB_RIS_WC) || (HIB_MIS_R & HIB_MIS_WC)) );

    /* Repeat Calibration Process until Pass or Max Attempt*/
    for (
      attempt = 0; 
      (
	(attempt < MCU_PIOSC_CAL_MAX_ATTEMPTS) &&
	!(SYSCTL_PIOSCSTAT_R & SYSCTL_PIOSCSTAT_CRPASS)
      );
      attempt++
    ) {

      SYSCTL_PIOSCCAL_R |= SYSCTL_PIOSCCAL_CAL;

    }

    /* Calibration Process Failure Check. */
    if ( attempt == MCU_PIOSC_CAL_MAX_ATTEMPTS ) {

      rccsrc = rccorig;
      rcc2src = rcc2orig;
      ret = E_NOT_OK;

    }

    /* Hibernation Module 32.768-kHz Oscillator Disable. */
    HIB_CTL_R &= ~HIB_CTL_CLK32EN;

    /* Hibernation Module Clock Gating Removal */
    SYSCTL_RCGCHIB_R &= ~SYSCTL_RCGCHIB_R0;

  }
#endif	/* __AS_MCU_INTERNAL_OSCILLATOR_CALIBRATION__ */

  /*
    * IMPORTANT:	If a subsequent write to the RCC register is required,
    * 			include another register access after writing the RCC
    * 			register and before writing the RCC2 register.
    */
  SYSCTL_RCC_R = rccsrc;		/* Write RCC			      */
  rccsrc = SYSCTL_RCC2_R;		/* Read RCC2			      */
  SYSCTL_RCC2_R = rcc2src;		/* Write RCC2			      */

  return ret;

}
#endif

/*
 * Mcu_InitClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )
Std_ReturnType Mcu_InitClock(
  Mcu_ClockType ClockSetting
)
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

  }

  EE_hal_resumeIRQ(flags);

  return ret;

}
#endif

/*
 * Mcu_DistributePllClock implementation
 */
#if ( MCU_NO_PLL == STD_OFF )
void Mcu_DistributePllClock(
  void
)
{

  register EE_FREG	flags;

  register uint32 rccdst;	/* Run-Mode Clock Configuration Destination   */
  register uint32 rcc2dst;	/* Run-Mode Clock Configuration 2 Destination */

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Mcu_Global.Init,
    MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID,
    MCU_E_UNINIT,
    flags
  );

  rccdst = SYSCTL_RCC_R;	/* Read RCC	*/
  rcc2dst = SYSCTL_RCC2_R;	/* Read RCC2	*/

  /* PLL undefined check */
  VALIDATE_IRQ(
    (
      (
	( rcc2dst & SYSCTL_RCC2_USERCC2 ) && 
	!( rcc2dst & SYSCTL_RCC2_PWRDN2 )
      ) ||
      !(
	( rcc2dst & SYSCTL_RCC2_USERCC2 ) ||
	( rcc2dst & SYSCTL_RCC_PWRDN )
      )
    ),
    MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID,
    MCU_E_PLL_NOT_LOCKED,
    flags
  );

  rccdst = SYSCTL_PLLSTAT_R;	/* Read PLLSTAT	*/

  /* PLL locked check */
  VALIDATE_IRQ(
    ( rccdst & SYSCTL_PLLSTAT_LOCK ),
    MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID,
    MCU_E_PLL_NOT_LOCKED,
    flags
  );

  rccdst = SYSCTL_RCC_R;		/* Read RCC		*/
  rccdst &= ~SYSCTL_RCC_BYPASS;		/* Remove PLL Bypass	*/
  SYSCTL_RCC_R = rccdst;		/* Write RCC		*/
  rcc2dst = SYSCTL_RCC2_R;		/* Read RCC2		*/
  rcc2dst &= ~SYSCTL_RCC2_BYPASS2;	/* Remove PLL Bypass	*/
  SYSCTL_RCC2_R = rcc2dst;		/* Write RCC2		*/

  EE_hal_resumeIRQ(flags);

}
#endif

/*
 * Mcu_GetPllStatus implementation
 */
Mcu_PllStatusType Mcu_GetPllStatus(
  void
)
{

  register EE_FREG	flags;

#if ( MCU_NO_PLL == STD_OFF )
  register uint32 rccsrc;	/* Run-Mode Clock Configuration Source	      */
  register uint32 rcc2src;	/* Run-Mode Clock Configuration 2 Source      */
  register uint32 pllstat;	/* PLL Status.				      */
#endif

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

  rccsrc = SYSCTL_RCC_R;
  rcc2src = SYSCTL_RCC2_R;
  pllstat = SYSCTL_PLLSTAT_R;

  /* PLL undefined check. */
  if ( 
    ( ( rcc2src & SYSCTL_RCC2_USERCC2 ) && ( rcc2src & SYSCTL_RCC2_PWRDN2 ) ) ||
    ( !( rcc2src & SYSCTL_RCC2_USERCC2 ) && ( rccsrc & SYSCTL_RCC_PWRDN ) )
  )
    ret = MCU_PLL_STATUS_UNDEFINED;
  else if ( pllstat & SYSCTL_PLLSTAT_LOCK )
    ret = MCU_PLL_LOCKED;
  else
    ret = MCU_PLL_UNLOCKED;
#endif

  EE_hal_resumeIRQ(flags);

  return ret;

}

/*
 * Mcu_GetResetReason implementation
 */
Mcu_ResetType Mcu_GetResetReason(
  void
) {

  register EE_FREG	flags;

  register uint32		resc;
  register Mcu_ResetType	ret;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Mcu_Global.Init,
    MCU_GETRESETREASON_SERVICE_ID,
    MCU_E_UNINIT,
    MCU_RESET_UNDEFINED,
    flags
  );

  resc = SYSCTL_RESC_R;		/* Read  RESC */
  SYSCTL_RESC_R = 0x00000000U;	/* Clear RESC */

  if ( (resc & SYSCTL_RESC_POR) ) {

    ret = MCU_POWER_ON_RESET;

  }
  else if ( (resc & (SYSCTL_RESC_WDT1 | SYSCTL_RESC_WDT0)) ) {

    ret = MCU_WATCHDOG_RESET;

  }
  else if ( (resc & SYSCTL_RESC_SW) ) {

    ret = MCU_SW_RESET;

  }
  else {

    ret = MCU_RESET_UNDEFINED;

  }

  EE_hal_resumeIRQ(flags);

  return ret;

}

/*
 * Mcu_GetResetRawValue implementation
 */
Mcu_RawResetType Mcu_GetResetRawValue(
  void
)
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

  ret = SYSCTL_RESC_R;		/* Read  RESC */
  SYSCTL_RESC_R = 0x000000000;	/* Clear RESC */

  EE_hal_resumeIRQ(flags);

  return ret;

}

#if ( MCU_PERFORM_RESET_API == STD_ON )
/*
 * Mcu_PerformReset implementation
 */
void Mcu_PerformReset(
  void
)
{


  register EE_FREG	flags;
  register uint32	apint;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Mcu_Global.Init,
    MCU_PERFORMRESET_SERVICE_ID,
    MCU_E_UNINIT,
    flags
  );

  /* 
   * Ensure all outstanding memory accesses included buffered write are
   * completed before reset
   */
  __dsb(0xF);

  apint = NVIC_APINT_R;
  NVIC_APINT_R = (
    NVIC_APINT_VECTKEY |		/* Vector key 			 */
    (apint & NVIC_APINT_PRIGROUP_M) |	/* Keep priority group unchanged */
    NVIC_APINT_SYSRESETREQ		/* System Reset Request		 */
  );

  __dsb(0xF);	/* Ensure completion of memory access */

  EE_hal_resumeIRQ(flags);

  while(TRUE);	/* Waiting for Reset to perform. */

}
#endif

/*
 * Mcu_SetMode implementation
 */
void Mcu_SetMode(
  Mcu_ModeType McuMode
)
{

  register EE_FREG			flags;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ( Mcu_Global.Init, MCU_SETMODE_SERVICE_ID, MCU_E_UNINIT, flags );

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

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

/** @file   Mcu.c
 *  @brief  AUTOSAR MCU Driver Source File.
 *
 *  This file contains AUTOSAR MCU Driver implementation
 *  for Freescale Leopard (MPC5643L) and Codewarrior compiler.
 *
 *  @author Errico Guidieri
 *  @date 2012
 */

#define MCU_AR_RELEASE_MAJOR_VERSION  4
#define MCU_AR_RELEASE_MINOR_VERSION  0

#include "Mcu.h"

/*
 * MCU110:  For included (external) header files:
 *    - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 *    - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 *    shall be verified.
 */
#if !defined( MCU_AR_MAJOR_VERSION ) || \
    ( MCU_AR_MAJOR_VERSION != MCU_AR_RELEASE_MAJOR_VERSION )
#error  Mcu: version mismatch.
#endif

/* In Order to use Validate Macros in Utility.h I define AS_MODULE_ID */
#define AS_MODULE_ID MCU_MODULE_ID

#include <ee.h>
#include "Hardware.h" /* Hardware Abstraction Header File. */
#include "Utility.h"

static struct Mcu_GlobalType {
  boolean               init;
  const Mcu_ConfigType  *config;
  Mcu_ModeType          mode;
  Mcu_ClockType         clock;
} Mcu_Global = {FALSE, NULL, MCU_MODE_INVALID, MCU_CLOCKS_INVALID};


#if (MCU_CLOCK_OUTPUT_ENABLE == 1U)
/* Configure Output Clock Source: PLL or RC */
static void EE_mcu_select_clock_output(uint32 mode_conf_bitmask) {
  if( HW_REG_BITMASK_CHECK(mode_conf_bitmask, MCU_MODE_SYSCLK_FMPLL) ) {
    /* Configure Output Clock Source: PLL */
    CGM.OCDS_SC.B.SELCTL = 2U;
  } else {
    /* Configure Output Clock Source: RC */
    CGM.OCDS_SC.B.SELCTL = 0U;
  }
}
#else
#define EE_mcu_select_clock_output(mode_conf_bitmask)   ((void)0)
#endif

/* Check if PLL source need to be changed */
static boolean EE_mcu_pll_source_changed(const Mcu_ClockSettingConfigType *
    const clockSettingsPtr)
{
  const Mcu_AuxClockSettingConfigType * const
    auxClockSettingsPtr = clockSettingsPtr->McuAuxClockSettingConfig;

  register boolean pll_changed = FALSE;
  register uint32 i;

  for(i = 0U; i < clockSettingsPtr->McuAuxClockNumber ; ++i) {
    const Mcu_AuxClockIdType mcu_aux_id = auxClockSettingsPtr[i].McuAuxClockId;
    const uint32 pll_source_mask = auxClockSettingsPtr[i].McuAuxClockSource;

    if( mcu_aux_id == MCU_AUX_CLOCK_3 ) {
      if( CGM.AC3_SC.R != pll_source_mask ) {
        pll_changed = TRUE;
        break;
      }
    }
    if ( mcu_aux_id == MCU_AUX_CLOCK_4 ) {
      if( CGM.AC4_SC.R != pll_source_mask ) {
        pll_changed = TRUE;
        break;
      }
    }
  }

  return pll_changed;
}

/* Configure Auxiliary Clocks */
static void EE_mcu_configure_auxiliary_clocks(const Mcu_ClockSettingConfigType *
    const clockSettingsPtr) {
  const Mcu_AuxClockSettingConfigType * const
    auxClockSettingsPtr = clockSettingsPtr->McuAuxClockSettingConfig;

  register uint32 i;

  for(i = 0U; i < clockSettingsPtr->McuAuxClockNumber ; ++i) {
    const Mcu_AuxClockSettingConfigType * const auxClockConfigPtr = 
      &auxClockSettingsPtr[i];

    switch(auxClockConfigPtr->McuAuxClockId) {
      case MCU_AUX_CLOCK_0:
        CGM.AC0SC.R = auxClockConfigPtr->McuAuxClockSource;
        if(auxClockConfigPtr->McuAuxClockDivisor0 != 0U) {
          CGM.AC0DC.B.DE0  = 1U;
          CGM.AC0DC.B.DIV0 = auxClockConfigPtr->McuAuxClockDivisor0 - 1U;
        }
        if(auxClockConfigPtr->McuAuxClockDivisor1 != 0U) {
          CGM.AC0DC.B.DE1 = 1;
          CGM.AC0DC.B.DIV1 = auxClockConfigPtr->McuAuxClockDivisor1 - 1U;
        }
      break;
      case MCU_AUX_CLOCK_1:
        CGM.AC1SC.R = auxClockConfigPtr->McuAuxClockSource;
        if(auxClockConfigPtr->McuAuxClockDivisor0 != 0U) {
          CGM.AC1DC.B.DE0  = 1U;
          CGM.AC1DC.B.DIV0 = auxClockConfigPtr->McuAuxClockDivisor0 - 1U;
        }
      break;
      case MCU_AUX_CLOCK_2:
        CGM.AC2SC.R = auxClockConfigPtr->McuAuxClockSource;
        if(auxClockConfigPtr->McuAuxClockDivisor0 != 0U) {
          CGM.AC2DC.B.DE0  = 1U;
          CGM.AC2DC.B.DIV0 = auxClockConfigPtr->McuAuxClockDivisor0 - 1U;
        }
      break;
      case MCU_AUX_CLOCK_3:
        CGM.AC3SC.R = auxClockConfigPtr->McuAuxClockSource;
      break;
      case MCU_AUX_CLOCK_4:
        CGM.AC4SC.R = auxClockConfigPtr->McuAuxClockSource;
      break;
      default:
        ; /* Configuration error TODO: notify DET/DEM ? */
    }
  }
}

/* Disable watchdog. Watchdog is enabled default after reset.*/
static EE_mcu_disable_watchdog(void) {
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}

/*  Mode switch implementation */
#define MCU_TARGET_MODE_SHIFT   28U
#define MCU_KEY_MASK            0x00005AF0U
#define MCU_INVERTED_KEY_MASK   0x0000A50FU

static void EE_mcu_perform_mode_switch(Mcu_HardwareModeIdType
    mode_hardware_id) {

  const uint32 target_mode_mask   = mode_hardware_id << MCU_TARGET_MODE_SHIFT;
  const uint32 mode_key           = target_mode_mask | MCU_KEY_MASK;
  const uint32 mode_inverted_key  = target_mode_mask | MCU_INVERTED_KEY_MASK;
 

  /* Write key and inverted key to start a  mode transition */
  /* Enter Mode & Key */
  ME.MCTL.R = mode_key;
  /* Enter Mode & Inverted Key */  
  ME.MCTL.R = mode_inverted_key;

  while (ME.GS.B.S_MTRANS != 0U) {
    ; /* Wait until the end of mode transition */
  }

#ifdef DEBUG
  while (ME.GS.B.S_CURRENT_MODE !=  mode_hardware_id)
  {
    ; /* Catch if the right transition didn't happened */
  }
#endif /* DEBUG */

  /* Clear Transition flag (w1c bit)*/
  ME.IS.R = 0x00000001U;
}

#define MCU_RESET_CLEAR_ALL_FLAGS     0xFFFFU

#define MCU_RESET_CLEAR_F_F_SOFT      0x0004U
#define MCU_RESET_CLEAR_F_F_CWD       0x0008U
#define MCU_RESET_CLEAR_F_F_FCCU_SAFE 0x0080U
#define MCU_RESET_CLEAR_F_F_SWT       0x0100U

static void EE_mcu_clear_functional_reset_flags(uint16 bitmask_to_clear) {
  /* Check if the any bits of the bitmask are set */
  while((RGM.FES.R & bitmask_to_clear) != 0U) {
    /* w1c bits */
    RGM.FES.R = bitmask_to_clear;
  }
}

#define MCU_RESET_CLEAR_D_F_SOFT      0x4000U
#define MCU_RESET_CLEAR_D_F_POR       0x8000U
static void EE_mcu_clear_destructive_reset_flags(uint16 bitmask_to_clear) {
  /* Check if the any bits of the bitmask are set */
  while((RGM.DES.R & bitmask_to_clear) != 0U) {
    /* w1c bits */
    RGM.DES.R = bitmask_to_clear;
  }
}

#define EE_MCU_FCCU_CFK_KEY 0x618B7A50U
static void EE_mcu_clear_critical_fault(void)
{
  uint32 i, a[4];
    for(i = 0U; i < 4U; ++i) {

    FCCU.CFK.R = EE_MCU_FCCU_CFK_KEY;
    /* w1c bits */
    FCCU.CF_S[i].R = 0xFFFFFFFFU;

    while(FCCU.CTRL.B.OPS != 0x3U){
      ; /* Wait until operation ends */
    };
    a[i]=FCCU.CF_S[i].R;
  }
}

#define EE_MCU_FCCU_NCFK_KEY  0xAB3498FEU
static void EE_mcu_clear_non_critical_fault(void)
{
  uint32_t i,b[4];
  for(i = 0U; i < 4U ;i++){
    FCCU.NCFK.R = EE_MCU_FCCU_NCFK_KEY;
    /* w1c bits */
    FCCU.NCF_S[i].R = 0xFFFFFFFFU;

    while(FCCU.CTRL.B.OPS != 0x3U){
        ; /* Wait until operation ends */
    };
    b[i]=FCCU.NCF_S[i].R;
  }
}


/* CTU Initialization */
#if ( MCU_CTU_SUPPORT == STD_ON )
#define EE_MCU_CTU_IFR_RESET_IRQ 0x0FFFU
void Mcu_InitCtu(void)
{
  /* Flags for Critical Section */
  register EE_FREG f;
  
  /* Configure CTU */
  Mcu_CrossTriggeringUnitSettingConfigType const * const
    mcu_ctu_conf = Mcu_Global.config->McuCtuSettingConf;

  /* Start Critical Section */
  f = EE_hal_suspendIRQ();

  /* Unizializated Condition Check */
  if((Mcu_Global.init == FALSE) || (Mcu_Global.mode == MCU_MODE_INVALID)) {
    AS_ERROR(MCU_INITCTU_SERVICE_ID, MCU_E_UNINIT);

    /* End Critical Section */
    EE_hal_resumeIRQ(f);
    return;
  }

  /* Clear CTUIFR */
  CTU.CTUIFR.R = EE_MCU_CTU_IFR_RESET_IRQ;

  /* Clear General Reload Enable (GRE) (So I can write double buffered
     registers) */
  CTU.CTUCR.R |= MCU_CTU_CR_CLEAR_GENERAL_RELOAD;

  /* Trigger Generation Subsystem Configuration */
  /* TGS Input Selection */
  CTU.TGSISR.R  = mcu_ctu_conf->McuCtuTgsConf->TriggerGeneratorSubsystemInput;
  /* TGS Subsystem Control */
  CTU.TGSCR.R   = mcu_ctu_conf->McuCtuTgsConf->TriggerGeneratorSubsystemControl;
  /* TGS Counter Compare */
  CTU.TGSCCR.R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemCounterCompare;
  /* TGS Counter Compare Reload */
  CTU.TGSCRR.R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemCounterReload;

  /* TGS Trigger Comparators */
  CTU.TCR[0].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger1Compare;
  CTU.TCR[1].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger2Compare;
  CTU.TCR[2].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger3Compare;
  CTU.TCR[3].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger4Compare;
  CTU.TCR[4].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger5Compare;
  CTU.TCR[5].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger6Compare;
  CTU.TCR[6].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger7Compare;
  CTU.TCR[7].R  = mcu_ctu_conf->McuCtuTgsConf->
    TriggerGeneratorSubsystemTrigger8Compare;

  /* CTU ADC Command List */
  {
    uint32 i;
    for(i = 0U; i < mcu_ctu_conf->McuCtuNumberOfCommand; ++i) {
      CTU.CLR[i].R = mcu_ctu_conf->McuCtuCommandList[i];
    }
  }

	/* CTU Configure Triggers Enable triggers */
  {
    uint32 i, thcr1 = 0U, thcr2 = 0U;
    /* THCRx can be write only as word */
    for(i = 0U; i < mcu_ctu_conf->McuCtuNumberOfTriggerHandler; ++i)
    {
        const Mcu_Ctu_TriggerType trigger_id = mcu_ctu_conf->
          McuTcuTriggerHandlersConf[i].McuCtuTriggerId;

        if(trigger_id <= MCT_CTU_TRIGGER_3) {
          thcr1 |= mcu_ctu_conf->McuTcuTriggerHandlersConf[i].
            McuCtuTriggerConf << (sizeof(uint8) * trigger_id);
        } else {
          thcr2 |= mcu_ctu_conf->McuTcuTriggerHandlersConf[i].
            McuCtuTriggerConf << (sizeof(uint8) * trigger_id);
        }
    }
    CTU.THCR1.R = thcr1;
    CTU.THCR2.R = thcr2;
  }

  /* Enable CTU Interrupts */
  CTU.CTUIR.R = mcu_ctu_conf->McuCtuInterruptDmaConf;

  /* End Critical Section */
  EE_hal_resumeIRQ(f);
  return;
}
#endif
/*
 * Mcu_Init implementation.
 */
void Mcu_Init(const Mcu_ConfigType * ConfigPtr)
{
  /* Flags for Critical Section */
  register EE_FREG f;

  /* Check Valid Configuration */
  AS_ASSERT( ( ConfigPtr != NULL ), MCU_INIT_SERVICE_ID, MCU_E_PARAM_CONFIG );
  /* Check if the MCU is supported */
  AS_ASSERT( ( Hw_ChipCheck() == E_OK ), MCU_INIT_SERVICE_ID, MCU_E_UNINIT );

  /* Start Critical Section */
  f = EE_hal_suspendIRQ();

  /* Disable watchdog. Watchdog could be enabled by default after reset. */
  EE_mcu_disable_watchdog();

  /* Enable modes */
  ME.MER.R = MCU_ENABLED_MODES;
  /* TODO: Maybe add some FLASH and CACHE optimization here */

  /* Only peripheral configuration 0 it's used so peripheral have to be
     enabled according to this */
  /* Enable peripherals to run in all modes not LP with
     (default configuration) */
  ME.RUNPC[0].R = 0x000000FEU;
  /* Disable peripherals in LP modes (already done at reset) */
  /* ME.LPPC[0].R = 0x00000000; */

  /* save the configuration in global status */
  Mcu_Global.config = ConfigPtr;

  /* Configure RESET */
  ME_SET_MC(MCU_MODE_ID_RESET, ConfigPtr->McuResetSetting);

  /* Now the MCU is initializated */
  Mcu_Global.init = TRUE;

  /* Configure and switch to default mode (it should be a DRUN mode, because
     sometime MCU starts in SAFE mode) */
  /* Reset start-up FCCU SAFE event (as work around needed to recover if a
     fccu complain with a hw fault (it happens)) */
  if(RGM.FES.B.F_FCCU_SAFE || RGM.FES.B.F_FCCU_HARD)
  {
      ME.IMTS.R = 0x00000001U;
      EE_mcu_clear_critical_fault();
      EE_mcu_clear_non_critical_fault();
      EE_mcu_clear_functional_reset_flags(MCU_RESET_CLEAR_F_F_FCCU_SAFE);
  }

  Mcu_SetMode(ConfigPtr->McuDefaultInitMode);

#if (MCU_CLOCK_OUTPUT_ENABLE == 1U)
  /* Configure Prescaler */
  CGM.OCDS_SC.B.SELDIV = MCU_CLOCK_PRESCALER_FACTOR;
  /* Enable Output Clock */
  CGM.OC_EN.R = MCU_CLOCK_OUTPUT_ENABLE;
#endif /* MCU_CLOCK_OUTPUT_ENABLE != 0U */

  /* End Critical Section */
  EE_hal_resumeIRQ(f);
}

/*
 * Mcu_InitRamSection implementation
 */
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
  /* NOT SUPPORTED, reason: no support for external RAM */

  return E_OK;
}

/*
 * Mcu_InitClock implementation
 */
#if ( MCU_INIT_CLOCK == STD_ON )


#ifdef MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT
/* 21 Error Correction Status Module */
#if (! defined EE_CURRENTCPU) || (EE_CURRENTCPU == 0)
#define ECSM_BASE_ADDR 0xFFF40000U /* equal to SPP_MCM of mpc5643l header */
#else
#define ECSM_BASE_ADDR 0x8FF40000U /* ECSM_1 */
#endif /* EE_CURRENTCPU */
/* 21.4.2.7 Miscellaneous User-Defined Control Register (MUDCR) */
#define EE_ECSM_MUDCR (*((volatile EE_UREG*)(ECSM_BASE_ADDR + 0x0024U)))
#endif /* MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT */

/* Bitmasks used to set value to CGM.FMPLL */
#define EE_UNLOCK_PLL                   0xFFFF0010U
#define EE_ENABLE_PROG_PLL_SWITCHING    0x00000100U

/* Bitmasks to clear mode configurations */
#define EE_MODE_CLEAR_CLK               0xFFFFFFF0U
#define EE_MODE_CLEAR_PLL0              0xFFFFFFBFU
#define EE_MODE_CLEAR_PLL1              0xFFFFFF7FU

Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
  /* Flags for Critical Section */
  register EE_FREG f;

  /* Clock Settings */
  const Mcu_ClockSettingConfigType * clockSettingsPtr;
  /* Flag if a PLL is locked */
  boolean pll_locked;
  /* Flag if PLLs sources need to be changed */
  boolean change_pll_source;
  /* Active Hardware Mode */
  Mcu_HardwareModeIdType active_hw_mode;
  /* Hardware Mode Configuration */
  uint32 mode_configuration;

  /* Start Critical Section */
  f = EE_hal_suspendIRQ();

  /* Unizializated Condition Check */
  if((Mcu_Global.init == FALSE) || (Mcu_Global.mode == MCU_MODE_INVALID)) {
    AS_ERROR(MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT);

    /* End Critical Section */
    EE_hal_resumeIRQ(f);
    return E_NOT_OK;
  }

  /* Get Clock Settings */
  clockSettingsPtr = &Mcu_Global.config->McuClockSettingConfig[ClockSetting];

  /* PLL is locked ? */
  pll_locked = (CGM.FMPLL[0].CR.B.S_LOCK || CGM.FMPLL[1].CR.B.S_LOCK);

  /* PLLs sources need to be changed ? */
  change_pll_source = EE_mcu_pll_source_changed(clockSettingsPtr);

  /* Active Hardware Mode */
  active_hw_mode = MCU_HARDWARE_MODE_ACTIVE();

  /* Hardware Mode Configuration */
  mode_configuration = ME_GET_MC(active_hw_mode);

  /*                          !!! WARNING !!!
    If pll is locked and I have to change pll source I have (maybe) to switch
    to RC internal OSC and (obligatorily) disable PLLs.
  */
  if(pll_locked && change_pll_source)
  {
    ME_SET_MC(active_hw_mode, mode_configuration &
      EE_MODE_CLEAR_CLK & EE_MODE_CLEAR_PLL0 & EE_MODE_CLEAR_PLL1);
    EE_mcu_perform_mode_switch(active_hw_mode);
  }

  /* Configure Auxiliary Clocks */
  EE_mcu_configure_auxiliary_clocks(clockSettingsPtr);

  /* TODO: check the following better */
  /* Monitor FXOSC > FIRC/1 (16MHz); no PLL monitor */
  /* CGM.CMU_0_CSR.R = 0x000000000; */

  /* fsys = (fcrystal * ndiv) / (idf * odf) */
  /* fvco must be from 256 MHz to 512 MHz and fvco = fsys * odf */
  /* E.G. we want fsys = 120 MHz. fvco = fsys*odf = 120 MHz * 4 = 480 MHz */
  /* fsys =  (40 * 96)/(8 * 4) = 120 MHz */

  /* For system clock configure PLLs */
  CGM.FMPLL[0].CR.R = (clockSettingsPtr->McuPll0Configuration |
    EE_ENABLE_PROG_PLL_SWITCHING );
  CGM.FMPLL[1].CR.R = (clockSettingsPtr->McuPll1Configuration |
    EE_ENABLE_PROG_PLL_SWITCHING );


  /* Configure Mode to change Clock frequency */
  if( !HW_REG_BITMASK_CHECK(mode_configuration, MCU_MODE_SYSCLK_FMPLL) ) {
    /* Actual Mode Configuration doesn't use FMPLL so I cannot change clock */
    /* I adjust mode configuration */
    mode_configuration = (mode_configuration & EE_MODE_CLEAR_CLK) |
      MCU_MODE_PLL1_ON | MCU_MODE_PLL0_ON | MCU_MODE_XOSC_ON |
      MCU_MODE_IRCOSC_ON | MCU_MODE_SYSCLK_FMPLL;
  }

  /* Mode Switch to change Clock frequency */
  ME_SET_MC(active_hw_mode, mode_configuration);
  EE_mcu_perform_mode_switch(active_hw_mode);

#ifdef MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT
  if (clockSettingsPtr->McuClockReferencePointFrequency >=
        MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT)
  {
      /* Add a wait state in RAM read */
      EE_ECSM_MUDCR = 0x40000000U;
  }
#endif /* MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT */

  /* Select Right Output Clock (if needed) */
  EE_mcu_select_clock_output(mode_configuration);

  /* Set new clock setting */
  Mcu_Global.clock = ClockSetting;

  /* End Critical Section */
  EE_hal_resumeIRQ(f);

  return E_OK;
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
  Mcu_PllStatusType pll_status;

  /* CGM.FMPLL[0] it's system pll */
  if (CGM.FMPLL[0].CR.B.S_LOCK ) {
    pll_status = MCU_PLL_LOCKED;
  } else {
    pll_status = MCU_PLL_UNLOCKED;
  }

  return pll_status;
}

/*
 * Mcu_GetResetReason implementation
 */
Mcu_ResetType Mcu_GetResetReason(void)
{
  Mcu_ResetType reset_reason;

  /* N.B Destructive software Reset is not supported yet by this driver */
  if( RGM.DES.B.F_POR ) {
    reset_reason = MCU_POWER_ON_RESET;
  } else if( RGM.FES.B.F_SOFT_FUNC || RGM.DES.B.F_SOFT_DEST ) {
    reset_reason = MCU_SW_RESET;
  } else if( RGM.FES.B.F_SWT || RGM.FES.B.F_CWD ) {
    /* SWT or Core Watchdog reset */
    reset_reason = MCU_WATCHDOG_RESET;
  } else {
    reset_reason = MCU_RESET_UNDEFINED;
  }
}

/*
 * Mcu_GetResetRawValue implementation
 */
Mcu_RawResetType Mcu_GetResetRawValue(void)
{
  Mcu_RawResetType reset_raw_value;
  if( RGM.DES.R ) {
    reset_raw_value = RGM.DES.R;
  } else {
    reset_raw_value = RGM.FES.R;
  }

  /* Reset start-up reset events */
  EE_mcu_clear_functional_reset_flags(MCU_RESET_CLEAR_ALL_FLAGS);
  EE_mcu_clear_destructive_reset_flags(MCU_RESET_CLEAR_ALL_FLAGS);

  return reset_raw_value;
}

#if ( MCU_PERFORM_RESET_API == STD_ON )
/*
 * Mcu_PerformReset implementation
 */
void Mcu_PerformReset(void)
{
  /* XXX: At this time only Software Functional Reset it's supported */
  EE_hal_disableIRQ();
  EE_mcu_perform_mode_switch(MCU_MODE_ID_RESET);
}
#endif

/*
 * Mcu_SetMode implementation
 */
void Mcu_SetMode(Mcu_ModeType McuMode)
{
  /* Flags for Critical Section */
  register EE_FREG f;
  /* Mode Settings */
  const Mcu_ModeSettingConfigType * modeSettingsPtr;
  /* Mode Hardware ID*/
  Mcu_HardwareModeIdType mode_hw_id;
  /* Mode Configuration */
  uint32 mode_conf;

  /* Start Critical Section */
  f = EE_hal_suspendIRQ();

  /* Unizializated Condition Check */
  if(Mcu_Global.init == FALSE) {
    AS_ERROR(MCU_INITCLOCK_SERVICE_ID, MCU_E_UNINIT);

    /* End Critical Section */
    EE_hal_resumeIRQ(f);
    return;
  }

  /* Get Mode Settings, HW mode ID & mode configuration */
  modeSettingsPtr = &Mcu_Global.config->McuModeSettingConf[McuMode];
  mode_hw_id      = modeSettingsPtr->McuHardwareModeId;
  mode_conf       = modeSettingsPtr->McuRunConfiguration;

  /* Set mode configuration */
  ME_SET_MC(mode_hw_id, mode_conf);

  /* Perform Switch */
  EE_mcu_perform_mode_switch(mode_hw_id);

  /* Select Right Output Clock (if needed) */
  EE_mcu_select_clock_output(mode_conf);

  /* Set Actual mode */
  Mcu_Global.mode = McuMode;

  /* End Critical Section */
  EE_hal_resumeIRQ(f);
}

/*
 * Mcu_GetRamState implementation
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
Mcu_RamStateType Mcu_GetRamState(void)
{
  /* NOT YET IMPLEMENTED, reason: no support for external RAM */

  return MCU_RAMSTATE_INVALID;
}
#endif


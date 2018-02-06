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

/** @file   Mcu_Cfg.c
 *  @brief  fake-druid AUTOSAR MCU Driver Configuration Source File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#define MCU_AR_RELEASE_MAJOR_VERSION  4
#define MCU_AR_RELEASE_MINOR_VERSION  0

#include "Mcu.h"
#include "Utility.h"

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

Mcu_AuxClockSettingConfigType const Mcu_DefaultAuxClockSetting[] = {
  {
    MCU_AUX_CLOCK_3,
    MCU_AUX_CLOCK_SOURCE_XOSC,
    0U,
    0U
  }
};

Mcu_AuxClockSettingConfigType const Mcu_DemoAuxClockSetting[] = {
  {
    MCU_AUX_CLOCK_0,
    MCU_AUX_CLOCK_SOURCE_SYSPLL,
    1U,
    4U
  },
  {
    MCU_AUX_CLOCK_3,
    MCU_AUX_CLOCK_SOURCE_XOSC,
    0U,
    0U
  },
  {
    MCU_AUX_CLOCK_4,
    MCU_AUX_CLOCK_SOURCE_XOSC,
    0U,
    0U
  }
};


/*
 * MCU124_Conf: This container contains the configuration (parameters) for the
 *    Clock settings of the MCU.
 *
 * Please see MCU031 for more information on the MCU clock settings.
 */
Mcu_ClockSettingConfigType const Mcu_ClockSettingConfigData[] =
{
  { 
    MCU_CLOCK_EXT_REF_64MHZ,      /* Clock Settings Identifier          */
    6.4E7,                        /* McuClockReferencePointFrequency    */
    MCU_FMPLL_IDF(5U) | MCU_FMPLL_ODF(8U) | MCU_FMPLL_NDIV(64U) |
    MCU_FMPLL_DEFAULT,
    MCU_FMPLL_IDF(5U) | MCU_FMPLL_ODF(8U) | MCU_FMPLL_NDIV(64U) |
    MCU_FMPLL_DEFAULT,
    /* 0x12400001U, */            /* 40 MHz xtal: Set PLL0 to 64 MHz    */
                                  /* IDF = 4: divide Fxtal by 5 (IDF+1) */
                                  /* NDIV = 64: multiply by 64 (NDIV)   */
                                  /* ODF = 2:  divide Fpll by 8 (2**(ODF+1)) */
    1U,                           /* Auxiliary Clock Settings */
    &Mcu_DefaultAuxClockSetting[0]
  },
  {
    MCU_CLOCK_EXT_REF_80MHZ,      /* Clock Settings Identifier          */
    8E7,                          /* McuClockReferencePointFrequency    */
    MCU_FMPLL_IDF(8U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(64U) |
    MCU_FMPLL_DEFAULT,
    MCU_FMPLL_IDF(8U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(64U) |
    MCU_FMPLL_DEFAULT,
    /* 0x1D400001U, */            /* 40 MHz xtal: Set PLL0 to 120 MHz   */
                                  /* IDF = 7: divide Fxtal by 8 (IDF+1) */
                                  /* NDIV = 64: multiply by 64 (NDIV)   */
                                  /* ODF = 1:  divide Fpll by 4 (2**(ODF+1)) */
    1U,                           /* Auxiliary Clock Settings */
    &Mcu_DefaultAuxClockSetting[0]
  },
  {
    MCU_CLOCK_EXT_REF_120MHZ,     /* Clock Settings Identifier          */
    1.2E8,                        /* McuClockReferencePointFrequency    */
    MCU_FMPLL_IDF(4U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(48U),
    MCU_FMPLL_IDF(2U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(64U),
    /* 0x0D300001U, */            /* 40 MHz xtal: Set PLL0 to 120 MHz */
                                  /* IDF = 3: divide Fxtal by 4 (IDF+1) */
                                  /* NDIV = 48: multiply by 48 (NDIV) */
                                  /* ODF = 1:  divide Fpll by 4 (2**(ODF+1)) */
    1U,                           /* Auxiliary Clock Settings */
    &Mcu_DefaultAuxClockSetting[0]
  },
  {
    MCU_CLOCK_RC_REF_80MHZ,       /* Clock Settings Identifier          */
    1.2E8,                        /* McuClockReferencePointFrequency    */
    MCU_FMPLL_IDF(2U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(40U) |
    MCU_FMPLL_DEFAULT,
    MCU_FMPLL_IDF(2U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(40U) |
    MCU_FMPLL_DEFAULT,
    /* 0x05480001U, */            /* 16 MHz RC: Set PLL0 to 80 MHz */
                                  /* IDF = 1: divide RC by 2 (IDF+1) */
                                  /* NDIV = 40: multiply by 40 (NDIV) */
                                  /* ODF = 1:  divide Fpll by 4 (2**(ODF+1)) */
    1U,                           /* Auxiliary Clock Settings */
    &Mcu_DefaultAuxClockSetting[0]
  },
  {
    MCU_CLOCK_RC_REF_120MHZ,      /* Clock Settings Identifier          */
    1.2E8,                        /* McuClockReferencePointFrequency    */
    MCU_FMPLL_IDF(4U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(90U) |
    MCU_FMPLL_DEFAULT,
    MCU_FMPLL_IDF(4U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(90U) |
    MCU_FMPLL_DEFAULT,
    /* 0x095A0001U, */            /* 16 MHz RC: Set PLL0 to 120 MHz */
                                  /* IDF = 2: divide RC by 4 (IDF+1) */
                                  /* NDIV = 90: multiply by 90 (NDIV) */
                                  /* ODF = 1:  divide Fpll by 4 (2**(ODF+1)) */
    1U,                           /* Auxiliary Clock Settings */
    &Mcu_DefaultAuxClockSetting[0]
  },
  {
    MCU_CLOCK_DEMO_EXT_120MHZ,    /* Clock Settings Identifier          */
    1.2E8,                        /* McuClockReferencePointFrequency    */
    MCU_FMPLL_IDF(6U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(72U),
    MCU_FMPLL_IDF(2U) | MCU_FMPLL_ODF(4U) | MCU_FMPLL_NDIV(64U),
    3U,                           /* Auxiliary Clock Settings */
    &Mcu_DemoAuxClockSetting[0]
  }

};


/*
 * MCU123_Conf: This container contains the configuration (parameters) for the
 *    Mode setting of the MCU.
 *
 * Please see MCU035 for more information on the MCU mode settings.
 */
Mcu_ModeSettingConfigType const Mcu_ModeSettingConfigData[] =
{
  {
    MCU_MODE_INIT,      /* Application Init Mode */
    MCU_MODE_ID_DRUN,   /* DRUN hardware ID */
    MCU_MODE_MAIN_VOLTAGE_REG_ON | MCU_MODE_RESERVED_NORM | MCU_MODE_FLAON_NORM
      | MCU_MODE_XOSC_ON | MCU_MODE_IRCOSC_ON | MCU_MODE_SYSCLK_RC
    /* 0x001F0030U */   /* DRUN cfg: 16MHzIRCON,OSC0ON,PLL0OFF,syclk=16MHzIRC */
  },
  {
    MCU_MODE_APPLICATION, /* Application Execution Mode */
    MCU_MODE_ID_RUN0,     /* RUN0 hardware ID */
    MCU_MODE_MAIN_VOLTAGE_REG_ON | MCU_MODE_RESERVED_NORM | MCU_MODE_FLAON_NORM
      | MCU_MODE_PLL0_ON | MCU_MODE_XOSC_ON | MCU_MODE_IRCOSC_ON |
      MCU_MODE_SYSCLK_FMPLL
    /* 0x001F0074U */     /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  },
  {
    MCU_MODE_SUPERVISOR,  /* Application Supervisor Mode */
    MCU_MODE_ID_DRUN,     /* DRUN hardware ID */
    MCU_MODE_MAIN_VOLTAGE_REG_ON | MCU_MODE_RESERVED_NORM | MCU_MODE_FLAON_NORM
      | MCU_MODE_PLL0_ON | MCU_MODE_XOSC_ON | MCU_MODE_IRCOSC_ON |
      MCU_MODE_SYSCLK_FMPLL
    /* 0x001F0074U */     /* DRUN cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  },
  {
    MCU_MODE_SAFE,    /* Application Safe Mode (for recovering from errors) */
    MCU_MODE_ID_SAFE, /* SAFE hardware ID */
    MCU_MODE_MAIN_VOLTAGE_REG_ON | MCU_MODE_RESERVED_NORM | MCU_MODE_FLAON_NORM
      | MCU_MODE_IRCOSC_ON | MCU_MODE_SYSCLK_RC
    /* 0x001F0010U */ /* SAFE cfg: 16MHzIRCON,OSC0OFF,PLL0OFF,syclk=16MHzIRC */
  }
};

/* CTU Trigger Generation Subsystem Configuration */
const Mcu_Ctu_TriggerGeneratorSubsistemConfigType McuCtuTgsDemo = {
  /* TGSISR register value */
  MCU_CTU_TGS_TI_EVEN_PWM_0_RAISING_EDGE,
  /* TGSCR register value */
  MCU_CTU_TGS_TC_SUBUNIT_MODE_TRIGGERED,
  /* TGSCCR register value */
  0x0BB8U,
  /* TGSCRR register value */
  0U,
  /* T1CR register value */
  0U,
  /* T2CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE,
  /* T3CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE,
  /* T4CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE,
  /* T5CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE,
  /* T6CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE,
  /* T7CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE,
  /* T8CR register value */
  MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE
};

/* Demo Trigger Handler Configuration List */
const Mcu_Ctu_TriggerControlHandlerConfigType McuCtuDemoTriggerList[] = {
  {
    MCT_CTU_TRIGGER_0,
    MCU_CTU_THCR_TRIGGER_ENABLE | MCU_CTU_THCR_TRIGGER_EXT_OUT_ENABLE |
      MCU_CTU_THCR_TRIGGER_ADC_OUT_ENABLE
  }
};

/* Demo Command List */
const Mcu_Ctu_CommandListType McuCtuDemoCommandList[] = {
  MCU_CTU_CLR_ADC_CHANNEL(0U),
  MCU_CTU_CLR_ADC_CHANNEL(1U),
  MCU_CTU_CLR_ADC_CHANNEL(2U),
  MCU_CTU_CLR_ADC_CHANNEL(3U),
  MCU_CTU_CLR_ADC_CHANNEL(4U),
  MCU_CTU_CLR_ADC_CHANNEL(5U),
  MCU_CTU_CLR_ADC_CHANNEL(6U),
  MCU_CTU_CLR_ADC_CHANNEL(7U) | MCU_CTU_CLR_INTERRUPT_REQUEST,
  MCU_CTU_CLR_LAST_COMMAND
};

/** @brief CTU Configuration */
const Mcu_CrossTriggeringUnitSettingConfigType McuCtuDemo = {
  /* CTUIR register value */
  MCU_CTU_IR_TRIGGER_0_ENABLED,
  /* TGS Configuration */
  &McuCtuTgsDemo,
  /* CTU Trigger Cofiguration List */
  ARRAY_LENGTH(McuCtuDemoTriggerList),
  &McuCtuDemoTriggerList[0],
  /* CTU ADC Command List */
  ARRAY_LENGTH(McuCtuDemoCommandList),
  &McuCtuDemoCommandList[0]
};

/*
 * MCU129_Conf: This container contains the configuration (parameters) for the
 *    RAM Sector setting.
 *
 * Please see MCU030 for more information on RAM sector settings.
 */
Mcu_RamSectorSettingConfType const Mcu_RamSectorSettingConfigData[] =
{
  {
    0U,           /* McuRamDefaultValue       */
    0x40000000U,  /* McuRamSectionBaseAddress */
    /* 64K (0x00008000U) of RAM in Lock Step Mode */
    0x00008000U   /* McuRamSectionSize        */
  }
};

/*
 * MCU131:  The structure Mcu_ConfigType is an external data structure (i.e.
 *    implementation specific) and shall contain the initialization
 *    data for the MCU module.
 *    It shall contain:
 *    - MCU dependent properties
 *    - Reset Configuration
 *    - Definition of MCU modes
 *    - Definition of Clock settings
 *    - Definition of RAM sections
 *
 * MCU054:  The structure Mcu_ConfigType shall provide a configurable
 *    (enable/disable) clock failure notification if the MCU provides
 *    an interrupt for such detection.
 *    If the clock failure is detected with other HW mechanisms e.g.,
 *    the generation of a trap, this notification shall be disabled
 *    and the failure reporting shall be done outside the MCU driver.
 *
 * MCU035:  The definitions for each MCU mode within the structure
 *    Mcu_ConfigType shall contain: (depending on MCU)
 *    - MCU specific properties
 *    - Change of CPU clock
 *    - Change of Peripheral clock
 *    - Change of PLL settings
 *    - Change of MCU power supply
 *
 * MCU031:  The definitions for each Clock setting within the structure
 *    Mcu_ConfigType shall contain:
 *    - MCU specific properties as, e.g., clock safety features and
 *      special clock distribution settings
 *    - PLL settings /start lock options
 *    - Internal oscillator setting
 *
 * MCU030:  The definitions for each RAM section within the structure
 *    Mcu_ConfigType shall contain:
 *    - RAM section base address
 *    - Section size
 *    - Data pre-setting to be initialized
 *    Usage of linker symbols instead of scalar values is allowed.
 */
const Mcu_ConfigType Mcu_Config[] =
{
  {
    /* McuClockSrcFailureNotification */
    FALSE,
    /* McuNumberOfMcuModes            */
    MCU_MODES_NUMBER,
    /* McuDefaultInitMode             */
    MCU_MODE_INIT,
    /* McuRamSectors                  */
    1U,
    /* McuResetSetting                */
    MCU_RESET_CONF,
    /* (Mcu_ClockSettingConfigType const * const) */
    &Mcu_ClockSettingConfigData[0],
    /* McuDemEventParametersRefs      */
    /*NULL_PTR,*/
    /* (Mcu_ModeSettingConfigType const * const) */
    &Mcu_ModeSettingConfigData[0],
    /* (Mcu_RamSectorSettingConfType const * const) */
    &Mcu_RamSectorSettingConfigData[0],
    /* (Mcu_CrossTriggeringUnitSettingConfigType const * const
        McuCtuSettingConf) */
    &McuCtuDemo,
    /* McuExternalOscillatorFrequency */
    40000000U
  }
};

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

/** @file   Mcu_Cfg_internal.h
 *  @brief  Static part (types definition) of AUTOSAR MCU Driver Configuration
 *     Header File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#ifndef MCU_CFG_INTERNAL_H
#define MCU_CFG_INTERNAL_H

#include "Cfg.h"

/* Bitmak to check & set mode enabled register */
#define MCU_MODE_ENABLED_RESET          AS_32_BIT31
#define MCU_MODE_ENABLED_TEST           AS_32_BIT30
#define MCU_MODE_ENABLED_SAFE           AS_32_BIT29
#define MCU_MODE_ENABLED_DRUN           AS_32_BIT28
#define MCU_MODE_ENABLED_RUN0           AS_32_BIT27
#define MCU_MODE_ENABLED_RUN1           AS_32_BIT26
#define MCU_MODE_ENABLED_RUN2           AS_32_BIT25
#define MCU_MODE_ENABLED_RUN3           AS_32_BIT24
#define MCU_MODE_ENABLED_HALT0          AS_32_BIT23
#define MCU_MODE_ENABLED_STOP0          AS_32_BIT21

#define MCU_MODE_ENABLED_DRESET         AS_32_BIT16

/* Bitmasks to check & set mode configurations */
#define MCU_MODE_SYSCLK_RC              0x00000000U
#define MCU_MODE_SYSCLK_FMPLL           0x00000004U
#define MCU_MODE_IRCOSC_ON              AS_32_BIT27
#define MCU_MODE_XOSC_ON                AS_32_BIT26
#define MCU_MODE_PLL0_ON                AS_32_BIT25
#define MCU_MODE_PLL1_ON                AS_32_BIT24

#define MCU_MODE_FLAON_NORM             (3U << 16U)
#define MCU_MODE_FLAON_HALT0            (2U << 16U)
#define MCU_MODE_FLAON_STOP0            (1U << 16U)

#define MCU_MODE_RESERVED_NORM          (3U << 18U)
#define MCU_MODE_RESERVED_HALT0         (2U << 18U)
#define MCU_MODE_RESERVED_STOP0         (1U << 18U)

#define MCU_MODE_MAIN_VOLTAGE_REG_ON    AS_32_BIT11
#define MCU_MODE_IO_POWER_DOWN          AS_32_BIT8

/* Macros to populate FMPLL register */
#define MCU_FMPLL_IDF(n)                ((0x00000FU & ((n) - 1U)) << 26U)
#define MCU_FMPLL_ODF(n)                ((0x000003U & ((n)/2U - 1U)) << 24U)
#define MCU_FMPLL_NDIV(n)               ((0x00007FU & (n)) << 16U)
#define MCU_FMPLL_DEFAULT               AS_32_BIT31

/* Bitmask to select Auxiliary Clock Source */
#define MCU_AUX_CLOCK_SOURCE_RC         0x00000000U
#define MCU_AUX_CLOCK_SOURCE_XOSC       AS_32_BIT7
#define MCU_AUX_CLOCK_SOURCE_SYSPLL     AS_32_BIT5

/* @brief Raw Reset Type
 *
 *  <b>MCU235:</b> The type Mcu_RawResetType specifies the reset reason in raw
 *  register format, read from a reset status register.
 *
 *  <b>MCU236:</b> The type shall be <tt>uint8</tt>, <tt>uint16</tt> or
 *  <tt>uint32</tt> based on best performance.
 */
typedef uint16_least  Mcu_RawResetType;

typedef enum {
  MCU_MODE_ID_RESET = 0x00U,
  MCU_MODE_ID_TEST  = 0x01U,
  MCU_MODE_ID_SAFE  = 0x02U,
  MCU_MODE_ID_DRUN  = 0x03U,
  MCU_MODE_ID_RUN0  = 0x04U,
  MCU_MODE_ID_RUN1  = 0x05U,
  MCU_MODE_ID_RUN2  = 0x06U,
  MCU_MODE_ID_RUN3  = 0x07U,
  MCU_MODE_ID_HALT0 = 0x08U,
  MCU_MODE_ID_STOP0 = 0x0AU,
  MCU_MODE_ID_INVALID = 0xFFU
} Mcu_HardwareModeIdType;

/** @brief  Mode Setting Configuration Paramaters
 *
 *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
 *  for the Mode setting of the MCU.
 *
 *  @see <b>MCU035</b> for more information on the MCU mode settings.
 */

typedef struct {
  const Mcu_ModeType            McuModeSettingId;
  const Mcu_HardwareModeIdType  McuHardwareModeId;
  const uint32                  McuRunConfiguration;
} Mcu_ModeSettingConfigType;

typedef enum {
  MCU_AUX_CLOCK_0,
  MCU_AUX_CLOCK_1,
  MCU_AUX_CLOCK_2,
  MCU_AUX_CLOCK_3,
  MCU_AUX_CLOCK_4
} Mcu_AuxClockIdType;

typedef struct {
  const Mcu_AuxClockIdType  McuAuxClockId;
  const uint32              McuAuxClockSource;
  const uint32              McuAuxClockDivisor0;
  const uint32              McuAuxClockDivisor1;
} Mcu_AuxClockSettingConfigType;

/** @brief  Clock Settings Configuration Parameters
 *
 *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
 *  for the Clock settings of the MCU.
 *
 *  @see <b>MCU031</b> for more information on the MCU clock settings.
 */
typedef struct {

  /** @brief  Clock Settings Identifier
   *
   *  <b>MCU183_Conf:</b> The Id of this <tt>McuClockSettingConfig</tt> to
   *          be used as argument for the API call
   *          <tt>Mcu_InitClock()</tt>.
   */
  const Mcu_ClockType McuClockSettingId;

  /** @brief  Clock Frequency
   *
   *  <b>MCU174_Conf:</b> This container defines a reference point in the Mcu
   *  Clock tree. It defines the frequency which then can be used by other
   *  modules as an input value. Lower multiplictiy is 1, as even in the
   *  simpliest case (only one frequency is used), there is one frequency to be
   *  defined.
   *
   *  <b>MCU175_Conf:</b> This is the frequency for the specific instance of the
   *  <tt>McuClockReferencePoint</tt> container. It shall be given in Hz.
   */
  const float32 McuClockReferencePointFrequency;

  /** @brief FMPLL0 Register value for desired clock frequency */
  const uint32 McuPll0Configuration;

  /** @brief FMPLL1 Register value for desired clock frequency */
  const uint32 McuPll1Configuration;

  /** @brief Number of Auxiliary Clock configuration */
  const uint32  McuAuxClockNumber;

  /** @brief Auxiliary Clock Setting Configuration Parameters */
  const Mcu_AuxClockSettingConfigType * const McuAuxClockSettingConfig;

} Mcu_ClockSettingConfigType;

/** @brief Invalid ID for mcu configuration */
#define MCU_MODE_INVALID           (Mcu_ModeType)-1
/** @brief Invalid ID for clock configuration */
#define MCU_CLOCKS_INVALID         (Mcu_ClockType)-1

/** @brief  Ram Sector Setting Configuration Parameters
 *
 *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
 *  for the RAM Sector setting.
 *
 *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
 */
typedef struct {

  /** @brief  Default Value
   *
   *  <b>MCU177_Conf:</b> This parameter shall represent the Data pre-setting to
   *  be initialized.
   */
  const uint8   McuRamDefaultValue;
  
  /** @brief  Base Address
   *
   *  <b>MCU178_Conf:</b> This parameter shall represent the MCU RAM section
   *  base address.
   */
  const uint32  McuRamSectionBaseAddress;

  /** @brief  Section Size
   *
   *  <b>MCU179_Conf:</b> This parameter shall represent the MCU RAM Section
   *  size.
   */
  const uint32  McuRamSectionSize;

} Mcu_RamSectorSettingConfType;

/* Mcu_Ctu_TriggerGeneratorSubsistem.TriggerGeneratorSubunitInput
   bitmasks */
#define MCU_CTU_TGS_TI_EXT_SIGNAL_FALLING_EDGE    AS_32_BIT0
#define MCU_CTU_TGS_TI_EXT_SIGNAL_RAISING_EDGE    AS_32_BIT1

#define MCU_CTU_TGS_TI_E_TIMERS_2_FALLING_EDGE    AS_32_BIT2
#define MCU_CTU_TGS_TI_E_TIMERS_2_RAISING_EDGE    AS_32_BIT3

#define MCU_CTU_TGS_TI_E_TIMERS_1_FALLING_EDGE    AS_32_BIT4
#define MCU_CTU_TGS_TI_E_TIMERS_1_RAISING_EDGE    AS_32_BIT5

#define MCU_CTU_TGS_TI_REAL_PWM_3_FALLING_EDGE    AS_32_BIT6
#define MCU_CTU_TGS_TI_REAL_PWM_3_RAISING_EDGE    AS_32_BIT7

#define MCU_CTU_TGS_TI_REAL_PWM_2_FALLING_EDGE    AS_32_BIT8
#define MCU_CTU_TGS_TI_REAL_PWM_2_RAISING_EDGE    AS_32_BIT9

#define MCU_CTU_TGS_TI_REAL_PWM_1_FALLING_EDGE    AS_32_BIT10
#define MCU_CTU_TGS_TI_REAL_PWM_1_RAISING_EDGE    AS_32_BIT11

#define MCU_CTU_TGS_TI_REAL_PWM_0_FALLING_EDGE    AS_32_BIT12
#define MCU_CTU_TGS_TI_REAL_PWM_0_RAISING_EDGE    AS_32_BIT13

#define MCU_CTU_TGS_TI_EVEN_PWM_3_FALLING_EDGE    AS_32_BIT14
#define MCU_CTU_TGS_TI_EVEN_PWM_3_RAISING_EDGE    AS_32_BIT15

#define MCU_CTU_TGS_TI_EVEN_PWM_2_FALLING_EDGE    AS_32_BIT16
#define MCU_CTU_TGS_TI_EVEN_PWM_2_RAISING_EDGE    AS_32_BIT17

#define MCU_CTU_TGS_TI_EVEN_PWM_1_FALLING_EDGE    AS_32_BIT18
#define MCU_CTU_TGS_TI_EVEN_PWM_1_RAISING_EDGE    AS_32_BIT19

#define MCU_CTU_TGS_TI_EVEN_PWM_0_FALLING_EDGE    AS_32_BIT20
#define MCU_CTU_TGS_TI_EVEN_PWM_0_RAISING_EDGE    AS_32_BIT21

#define MCU_CTU_TGS_TI_ODD_PWM_3_FALLING_EDGE     AS_32_BIT22
#define MCU_CTU_TGS_TI_ODD_PWM_3_RAISING_EDGE     AS_32_BIT23

#define MCU_CTU_TGS_TI_ODD_PWM_2_FALLING_EDGE     AS_32_BIT24
#define MCU_CTU_TGS_TI_ODD_PWM_2_RAISING_EDGE     AS_32_BIT25

#define MCU_CTU_TGS_TI_ODD_PWM_1_FALLING_EDGE     AS_32_BIT26
#define MCU_CTU_TGS_TI_ODD_PWM_1_RAISING_EDGE     AS_32_BIT27

#define MCU_CTU_TGS_TI_ODD_PWM_0_FALLING_EDGE     AS_32_BIT28
#define MCU_CTU_TGS_TI_ODD_PWM_0_RAISING_EDGE     AS_32_BIT29

#define MCU_CTU_TGS_TI_PWM_RELOAD_FALLING_EDGE    AS_32_BIT30
#define MCU_CTU_TGS_TI_PWM_RELOAD_RAISING_EDGE    AS_32_BIT31

/*Mcu_Ctu_TriggerGeneratorSubsistem.TriggerGeneratorSubunitControl
   bitmasks */
#define   MCU_CTU_TGS_TC_TOGGLE_MODE              AS_16_BIT7
#define   MCU_CTU_TGS_TC_PRESCALER(p)             ((0x0003U & (p)) << 6U)
#define   MCU_CTU_TGS_TC_MASTER_RELOAD_SIGNAL(m)  ((0x001FU & (m)) << 1U)
#define   MCU_CTU_TGS_TC_SUBUNIT_MODE_SEQUENTIAL  AS_16_BIT15
#define   MCU_CTU_TGS_TC_SUBUNIT_MODE_TRIGGERED   0x0000U

#define MCU_CTU_TGS_TRIGGER_COMPARE_OUT_OF_RANGE  0xFFFFU

/** @brief CTU TGS Subsystem Configuration Parameters */
typedef struct {
  /* TGSISR register value */
  const uint32 TriggerGeneratorSubsystemInput;
  /* TGSCR register value */
  const uint16 TriggerGeneratorSubsystemControl;
  /* TGSCCR register value */
  const uint16 TriggerGeneratorSubsystemCounterCompare;
  /* TGSCRR register value */
  const uint16 TriggerGeneratorSubsystemCounterReload;
  /* T1CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger1Compare;
  /* T2CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger2Compare;
  /* T3CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger3Compare;
  /* T4CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger4Compare;
  /* T5CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger5Compare;
  /* T6CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger6Compare;
  /* T7CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger7Compare;
  /* T8CR register value */
  const uint16 TriggerGeneratorSubsystemTrigger8Compare;
} Mcu_Ctu_TriggerGeneratorSubsistemConfigType;

/* Mcu_Ctu_CommandListType bitmasks */
#define MCU_CTU_CLR_INTERRUPT_REQUEST     AS_16_BIT0
#define MCU_CTU_CLR_LAST_COMMAND          AS_16_BIT1
#define MCU_CTU_CLR_CONVERSION_MODE       AS_16_BIT2
#define MCU_CTU_CLR_FIFO(f)               ((0x000FU & (f)) << 10U)
#define MCU_CTU_CLR_SELECTION_UNIT_ADC_B  AS_16_BIT10
#define MCU_CTU_CLR_ADC_CHANNEL(c)        (0x000FU & (c))

/** @brief Max number of commands for ADC */
#define MCU_CTU_CLR_MAX_NUMBER_OF_COMMAND 24

/** @brief CTU Command List Type */
typedef uint16 Mcu_Ctu_CommandListType;

typedef enum {
  MCT_CTU_TRIGGER_0       = 0U,
  MCT_CTU_TRIGGER_1       = 1U,
  MCT_CTU_TRIGGER_2       = 2U,
  MCT_CTU_TRIGGER_3       = 3U,
  MCT_CTU_TRIGGER_4       = 4U,
  MCT_CTU_TRIGGER_5       = 5U,
  MCT_CTU_TRIGGER_6       = 6U,
  MCT_CTU_TRIGGER_7       = 7U,
  MCT_CTU_NUM_OF_TRIGGER  = 8U
} Mcu_Ctu_TriggerType;

#define   MCU_CTU_THCR_TRIGGER_ENABLE             AS_8_BIT1
#define   MCU_CTU_THCR_TRIGGER_EXT_OUT_ENABLE     AS_8_BIT2
#define   MCU_CTU_THCR_TRIGGER_TIMER4_OUT_ENABLE  AS_8_BIT3
#define   MCU_CTU_THCR_TRIGGER_TIMER3_OUT_ENABLE  AS_8_BIT4
#define   MCU_CTU_THCR_TRIGGER_TIMER2_OUT_ENABLE  AS_8_BIT5
#define   MCU_CTU_THCR_TRIGGER_TIMER1_OUT_ENABLE  AS_8_BIT6
#define   MCU_CTU_THCR_TRIGGER_ADC_OUT_ENABLE     AS_8_BIT7

typedef struct {
  const Mcu_Ctu_TriggerType     McuCtuTriggerId;
  const uint8                   McuCtuTriggerConf;
} Mcu_Ctu_TriggerControlHandlerConfigType;

/** McuCtuControlConf bitmasks */
#define MCU_CTU_CR_TRIGGER_7_SOFT               AS_16_BIT0
#define MCU_CTU_CR_TRIGGER_6_SOFT               AS_16_BIT1
#define MCU_CTU_CR_TRIGGER_5_SOFT               AS_16_BIT2
#define MCU_CTU_CR_TRIGGER_4_SOFT               AS_16_BIT3
#define MCU_CTU_CR_TRIGGER_3_SOFT               AS_16_BIT4
#define MCU_CTU_CR_TRIGGER_2_SOFT               AS_16_BIT5
#define MCU_CTU_CR_TRIGGER_1_SOFT               AS_16_BIT6
#define MCU_CTU_CR_TRIGGER_0_SOFT               AS_16_BIT7

#define MCU_CTU_CR_STATE_MACHINE_RESET          AS_16_BIT8
#define MCU_CTU_CR_OUTPUT_DISABLE               AS_16_BIT9

#define MCU_CTU_CR_DIGITAL_FILTER_ENABLED       AS_16_BIT10
#define MCU_CTU_CR_CLEAR_GENERAL_RELOAD         AS_16_BIT11
#define MCU_CTU_CR_FLAG_GENERAL_RELOAD          AS_16_BIT12

#define MCU_CTU_CR_MSR_SOFT                     AS_16_BIT13
#define MCU_CTU_CR_GENERAL_RELOAD_ENABLED       AS_16_BIT14

#define MCU_CTU_CR_TGS_IS_RELOAD_ENABLED        AS_16_BIT15

/** McuCtuInterruptDmaConf bitmasks */
#define MCU_CTU_IR_TRIGGER_7_ENABLED            AS_16_BIT0
#define MCU_CTU_IR_TRIGGER_6_ENABLED            AS_16_BIT1
#define MCU_CTU_IR_TRIGGER_5_ENABLED            AS_16_BIT2
#define MCU_CTU_IR_TRIGGER_4_ENABLED            AS_16_BIT3
#define MCU_CTU_IR_TRIGGER_3_ENABLED            AS_16_BIT4
#define MCU_CTU_IR_TRIGGER_2_ENABLED            AS_16_BIT5
#define MCU_CTU_IR_TRIGGER_1_ENABLED            AS_16_BIT6
#define MCU_CTU_IR_TRIGGER_0_ENABLED            AS_16_BIT7

#define MCU_CTU_IR_SAFE_COUNTER_B_ENABLED       AS_16_BIT10
#define MCU_CTU_IR_SAFE_COUNTER_A_ENABLED       AS_16_BIT11

#define MCU_CTU_IR_DMA_DE                       AS_16_BIT12
#define MCU_CTU_IR_MSR_DMA_ENABLED              AS_16_BIT13
#define MCU_CTU_IR_MSR_INTERRUPT_ENABLED        AS_16_BIT14
#define MCU_CTU_IR_ERROR_INTERRUPT_ENABLED      AS_16_BIT15

/** @brief CTU Configuration Parameters */
typedef struct {
  /* CTUIR register value */
  const uint32    McuCtuInterruptDmaConf;
  /* CTU TGS Configuration */
  Mcu_Ctu_TriggerGeneratorSubsistemConfigType const * const
      McuCtuTgsConf;
  /* THCR configuration */
  const uint32    McuCtuNumberOfTriggerHandler;
  Mcu_Ctu_TriggerControlHandlerConfigType const * const
      McuTcuTriggerHandlersConf;
  const uint32 McuCtuNumberOfCommand;
  Mcu_Ctu_CommandListType const * const McuCtuCommandList;

} Mcu_CrossTriggeringUnitSettingConfigType;

/** @brief  MCU Configuration Parameters
 *
 *  <b>MCU131:</b> The structure <tt>Mcu_ConfigType</tt> is an external data
 *  structure (i.e. implementation specific) and shall contain the
 *  initialization data for the MCU module. It shall contain:
 *  - MCU dependent properties
 *  - Reset Configuration
 *  - Definition of MCU modes
 *  - Definition of Clock settings
 *  - Definition of RAM sections
 *
 *  <b>MCU054:</b> The structure <tt>Mcu_ConfigType</tt> shall provide a
 *  configurable (enable/disable) clock failure notification if the MCU provides
 *  an interrupt for such detection. If the clock failure is detected with other
 *  HW mechanisms e.g., the generation of a trap, this notification shall be
 *  disabled and the failure reporting shall be done outside the MCU driver.
 *
 *  <b>MCU035:</b> The definitions for each MCU mode within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain: (depending on MCU)
 *  - MCU specific properties
 *  - Change of CPU clock
 *  - Change of Peripheral clock
 *  - Change of PLL settings
 *  - Change of MCU power supply
 *
 *  <b>MCU031:</b> The definitions for each Clock setting within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain:
 *  - MCU specific properties as, e.g., clock safety features and special clock
 *  distribution settings
 *  - PLL settings /start lock options
 *  - Internal oscillator setting
 *
 *  <b>MCU030:</b> The definitions for each RAM section within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain:
 *  - RAM section base address
 *  - Section size
 *  - Data pre-setting to be initialized
 * Usage of linker symbols instead of scalar values is allowed.
 */
typedef struct {

  /** @brief  Clock Source Failure Notification
   *
   *  <b>MCU170_Conf:</b> Enables/Disables clock failure notification. In case
   *  this feature is not supported by HW the setting should be disabled.
   */
  const boolean McuClockSrcFailureNotification;

  /** @brief  MCU Modes Number
   *
   *  <b>MCU171_Conf:</b> This parameter shall represent the number of Modes
   *  available for the MCU. calculationFormula = Number of configured
   *  <tt>McuModeSettingConf</tt>.
   */
  const uint8   McuNumberOfMcuModes;

  /** @brief Mcu Default Initial Mode
   *
   *  Used in MCU Init to configure the default mode before return
   */
  const Mcu_ModeType  McuDefaultInitMode;

  /** @brief  RAM Sectors Number
   *
   *  <b>MCU172_Conf:</b> This parameter shall represent the number of RAM
   *  sectors available for the MCU. calculationFormula = Number of configured
   *  <tt>McuRamSectorSettingConf</tt>
   */
  const uint32  McuRamSectors;

  /** @brief  Reset Setting Configuration Parameters
   *
   *  <b>MCU173_Conf:</b> This parameter relates to the MCU specific reset
   *  configuration. This applies to the function <tt>Mcu_PerformReset()</tt>,
   *  which performs a microcontroller reset using the hardware feature of the
   *  microcontroller.
   */
  const uint32 McuResetSetting;

  /** @brief  Clock Setting Configuration Parameters
   *
   *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
   *  for the Clock settings of the MCU.
   *
   *  @see <b>MCU031</b> for more information on the MCU clock settings.
   */
  Mcu_ClockSettingConfigType const * const McuClockSettingConfig;

#if ( MCU_DEV_ERROR_DETECT == STD_ON )
  /** @brief  DEM Event Configuration Parameters
   *
   *  <b>MCU187_Conf:</b> Container for the references to
   *  <tt>DemEventParameter</tt> elements which shall be invoked using the API
   *  <tt>Dem_ReportErrorStatus()</tt> API in case the corresponding error
   *  occurs. The EventId is taken from the referenced DemEventParameter's
   *  DemEventId value. The standardized errors are provided in the container
   *  and can be extended by vendor specific error references. */
  Mcu_DemEventParametersTypeRefs const * const McuDemEventParametersRefs;
#endif

  /** @brief  Mode Setting Configuration Parameters
   *
   *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
   *  for the Mode setting of the MCU.
   *
   *  @see <b>MCU035</b> for more information on the MCU mode settings.
   */
  Mcu_ModeSettingConfigType const * const  McuModeSettingConf;

  /** @brief  Ram Sector Setting  Configuration Parameters
   *
   *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
   *  for the RAM Sector setting.
   *
   *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
   */
  Mcu_RamSectorSettingConfType const * const McuRamSectorSettingConf;

  /** @brief  CTU Configuration Parameters */
  Mcu_CrossTriggeringUnitSettingConfigType const * const McuCtuSettingConf;

  /** @brief  External Oscillator Frequency parameter */
  const uint32 McuExternalOscillatorFrequency;

} Mcu_ConfigType;


/* Implementation Custom Functions */
#define MCU_INITCTU_SERVICE_ID MCU_LAST_SERVICE_ID + 1U
#if ( MCU_CTU_SUPPORT == STD_ON )
void Mcu_InitCtu(void);
/* Global CTU configuration (GRE + TGSISR_RE). TGS Input Selection Reload
   Enable CTU */
#define  Mcu_ReloadCtu() (CTU.CTUCR.R |= MCU_CTU_CR_GENERAL_RELOAD_ENABLED |\
    MCU_CTU_CR_TGS_IS_RELOAD_ENABLED)
#endif

#endif  /* MCU_CFG_H */

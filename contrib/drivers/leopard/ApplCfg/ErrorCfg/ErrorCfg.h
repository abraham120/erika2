/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef _ERRORCFG_H_
#define _ERRORCFG_H_

#include "BswCommon.h"

#define SIZE_OF_DETAILS_ARRAY_HP    (12)
#define SIZE_OF_DETAILS_ARRAY_LP    (12)
#define ERROR_ERASE_THRESHOLD       (40)    ///< A not-present error is erased from memory after ERROR_ERASE_THRESHOLD key cycles.

/// List of error identifiers.
typedef enum
{
    ERR_ID_GENERIC,
    DIAG_HW_I_BPACK,
    DIAG_HW_PHASE_CURR,
    DIAG_HW_I_CAP,
    DIAG_HW_V_CAP,
    DIAG_HW_I_SEC,
    DIAG_HW_V_CLAMP,
    DIAG_HW_V_AUX,
    DIAG_HW_V_CAP_DIG,
    DIAG_HW_DSP_GENERIC,
    DIAG_HW_PRECHARGE,
    DIAG_HW_WATCHDOG,
    DIAG_HW_SPI_DSP_CPLD,
    DIAG_SOC_INDICATOR,
    DIAG_OP_MODE,
    DIAG_VCAP,
    DIAG_SENS_1,
    DIAG_V_BPACK36,
    DIAG_I_BPACK36,
    DIAG_TEMP_MACHINE,
    DIAG_SENS_TEMP_MACHINE,
    DIAG_RECHARGE_LAMP,
    DIAG_BMS_POW_ENABLE,
    DIAG_V_BPACK_12,
    DIAG_SPI_DSP_PPC,
    DIAG_BMS,
    DIAG_RELAY_FAN,
    DIAG_HV_BR_TEMP,
    DIAG_3PH_BR_TEMP,
    DIAG_EN_DCDC_12V,
    DIAG_BUZZER,
    DIAG_VEHICLE_CAN,
    DIAG_FAN,
    DIAG_I_SENS_BPACK36,
    DIAG_V_SENS_BPACK36,
    DIAG_I_PHASE_V,
    DIAG_I_PHASE_W,
    DIAG_V_ALIM,
    DIAG_BMS_ABSENT,
    DIAG_NTS_ABSENT,
    DIAG_ECU_ABSENT,
    DIAG_COH_I_BPACK_36,
    DIAG_COH_V_BPACK_36,
    DIAG_SAFETY_2,
    DIAG_SAFETY_3,
    DIAG_CPU,
    DIAG_RAM,
    DIAG_SUPPLY_FAN,
    DIAG_RAPID_DISCHARGE,
    DIAG_PRESENCE_SWITCH,
    DIAG_BMS_DANGER_BPACK36,
    DIAG_SOFTWARE_VERSION,
    DIAG_GEN_BMS,
    DIAG_INTERNAL_FAN,
    DIAG_KUBO_SW_VER,
    DIAG_V_STARTER,
    ERR_ID_DEVELOPMENT,
    NR_OF_ERRORS
} ErrorIdType;

/// List of recovery identifiers.
typedef enum
{
    REC_FAN_ON,
    REC_SOFT_STOP,
    REC_TOR_0,
    REC_LIM_TOR,
    REC_CC_PHASES,
    REC_FIX_HYBRID_MODE,
    REC_NO_REVERSE,
    REC_USE_B12,
    REC_LIM_TORQUE_ICE,
    REC_LIM_VSPEED_ICE,
    REC_DCDC_12_OFF  ,
    REC_SAFETY_LAMP,
    REC_FAN_OFF,
    REC_HV_BR_TEMP,
    REC_3PH_BR_TEMP,
    REC_WARNING_LAMP,    
    NR_OF_RECOVERIES
} RecoveryIdType;

/// Type of confirmation of an error
typedef enum
{
    ERROR_CONFIRMATION_NOT_VALID,
    ERROR_CONFIRMATION_IMMEDIATE,           ///< Debouncing not applied: the error is set immediatly.
    ERROR_CONFIRMATION_UP_DOWN_COUNTER,     ///< Counter is incremented when the fault is detected and it's decremented when the fault is not detected. This method is similar to an average value, and it's more suitable for noisy signals.
    ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,   ///< Counter is incremented when the fault is detected and it's reset when the fault is not detected. This method is harder to trigger and it's more suitable for severe errors that must be detected quickly.
    NR_OF_CONFIRMATION_TYPES
} ErrorConfirmationType;

/// Configuration of the errors
typedef struct
{
    uint16 dtc;                     ///< Number of the related DTC (0x0000 if no DTC is associated to this error/event)
    uint8 confirmationThreshold;                ///< If confirmationCounter==confirmationThreshold then the error is present. Unit: the period by which SetError() is called. Range [1..0x7FFF]. If '1' the error is 'confirmed' as soon as it's 'reported'.
    ErrorConfirmationType confirmationType;     ///< Type of confirmation of an error
    boolean persistent;             ///< If TRUE, the error status must be saved to flash. 
    boolean detailsPriority;        ///< If TRUE, the error is saved in the high priority array detailsHP[].
    boolean fatal;                  ///< If TRUE, the confirmation of the error causes the stop of the application. Uses MainStateSafe().
    /* Following fields are managed only by external tools (i.e. PProget)
    boolean development;            ///< If TRUE, the error used only during system development
    ErrorSeverityType severity;     ///< Type of severity of an error (INFO, WARNING, ALARM, FATAL, DEVELOP).
    */
    void (*confirmedCallback)(ErrorIdType errId);       ///< Called when 'confirmed' changes to TRUE. If NULL the callback is ignored.
    void (*notConfirmedCallback)(ErrorIdType errId);    ///< Called when 'confirmed' changes to FALSE. If NULL the callback is ignored.
} ErrorConfigType;

extern const ErrorConfigType errorConfig[];

#endif      // _ERRORCFG_H_

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

#include "BswCommon.h"
#include "ErrorCfg.h"
#include "ErrorHandlers.h"

#define MODULE_ID   (29)

////////////////////////////////////////////////////////////////////////////////
// Start of auto-generated section
// ...
// ...

/// Configuration of errors
const ErrorConfigType errorConfig[NR_OF_ERRORS] = {
    // name                      dtc   confirmationThreshold   confirmationType     persistent  detailsPriority fatal     confirmedCallback                  notConfirmedCallback
    /* ERR_ID_GENERIC */       { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_I_BPACK */      { 0x9002, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_PHASE_CURR */   { 0x9003, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_I_CAP */        { 0x9004, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_V_CAP */        { 0x9005, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_I_SEC */        { 0x9006, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_V_CLAMP */      { 0x9007, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_V_AUX */        { 0x9008, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_V_CAP_DIG */    { 0x9009, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_DSP_GENERIC */  { 0x900A, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_PRECHARGE */    { 0x900B, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_WATCHDOG */     { 0x900C, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HW_SPI_DSP_CPLD */ { 0x900D, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SOC_INDICATOR */   { 0x900E, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_OP_MODE */         { 0x900F, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_VCAP */            { 0x9011, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SENS_1 */          { 0x9012, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_V_BPACK36 */       { 0x9013, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_I_BPACK36 */       { 0x9014, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_TEMP_MACHINE */    { 0x9015, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SENS_TEMP_MACHINE */ { 0x9016, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,   TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_RECHARGE_LAMP */   { 0x9017, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_BMS_POW_ENABLE */  { 0x9018, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_V_BPACK_12 */      { 0x9019, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SPI_DSP_PPC */     { 0x901A, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_BMS */             { 0x901B, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_RELAY_FAN */       { 0x901C, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_HV_BR_TEMP */      { 0x901D, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_3PH_BR_TEMP */     { 0x901E, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_EN_DCDC_12V */     { 0x901F, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_BUZZER */          { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_VEHICLE_CAN */     { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_FAN */             { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_I_SENS_BPACK36 */  { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_V_SENS_BPACK36 */  { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_I_PHASE_V */       { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_I_PHASE_W */       { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_V_ALIM */          { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_BMS_ABSENT */      { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_NTS_ABSENT */      { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_ECU_ABSENT */      { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_COH_I_BPACK_36 */  { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_COH_V_BPACK_36 */  { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SAFETY_2 */        { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SAFETY_3 */        { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_CPU */             { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_RAM */             { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SUPPLY_FAN */      { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_RAPID_DISCHARGE */ { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_PRESENCE_SWITCH */ { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_BMS_DANGER_BPACK36 */ { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,  TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_SOFTWARE_VERSION */ { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,    TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_GEN_BMS */         { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_INTERNAL_FAN */    { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_KUBO_SW_VER */     { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* DIAG_V_STARTER */       { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
    /* ERR_ID_DEVELOPMENT */   { 0x9001, 1, ERROR_CONFIRMATION_SAW_TOOTH_COUNTER,     TRUE,       TRUE,           FALSE,    confirmedCallback_DIAG_HW_I_BPACK, notConfirmedCallback_DIAG_HW_I_BPACK },
};

// End of auto-generated section
////////////////////////////////////////////////////////////////////////////////

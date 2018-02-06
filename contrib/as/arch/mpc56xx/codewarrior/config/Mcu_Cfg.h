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

/** @file   Mcu_Cfg.h
 *  @brief  fake-druid AUTOSAR MCU Driver Configuration Header File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 */


#if !(\
 ((MCU_SW_MAJOR_VERSION == 1) && \
  (MCU_SW_MINOR_VERSION == 0) && \
  (MCU_SW_PATCH_VERSION == 0))\
)
#error Mcu: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef MCU_CFG_H
#define MCU_CFG_H

/*
 * MCU118_Conf: This container contains the configuration (parameters) of the
 *    MCU driver.
 */
/* McuGeneralConfiguration */

/** @brief  Development Error Detection
 *
 *  <b>MCU166_Conf:</b> Pre-processor switch for enabling the development error
 *  detection and reporting.
 */
#define MCU_DEV_ERROR_DETECT  STD_OFF

/** @brief  Ram State Retrieval API
 *
 *  <b>MCU181_Conf:</b> Pre-processor switch to enable/disable the API
 *  <tt>Mcu_GetRamState()</tt>. (e.g. If the H/W does not support the
 *  functionality, this parameter can be used to disable the Api).
 */
#define MCU_GET_RAM_STATE_API STD_OFF

/** @brief  Clock Initialization API
 *
 *  <b>MCU182_Conf:</b> If this parameter is set to FALSE, the clock
 *  initialization has to be disabled from the MCU driver. This concept applies
 *  when there are some write once clock registers and a bootloader is present.
 *  If this parameter is set to TRUE, the MCU driver is responsible of the clock
 +  initialization.
 */
#define MCU_INIT_CLOCK    STD_ON

/** @brief  Hardware PLL
 *
 *  <b>MCU180_Conf:</b> This parameter shall be set True, if the H/W does not
 *  have a PLL or the PLL circuitry is enabled after the power on without S/W
 *  intervention. In this case <tt>MCU_DistributePllClock()</tt> has to be
 *  disabled and <tt>MCU_GetPllStatus()</tt> has to return
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt>. Otherwise this parameters has to be set
 *  False.
 */
#define MCU_NO_PLL    STD_OFF

/** @brief  Microcontroller Reset API
 *
 *  <b>MCU167_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Mcu_PerformReset()</tt>.
 */
#define MCU_PERFORM_RESET_API STD_ON

/** @brief  Version Informations Retrieval API
 *
 *  <b>MCU168_Conf:</b> Pre-processor switch to enable / disable the API to read
 *  out the modules version information.
 */
#define MCU_VERSION_INFO_API  STD_ON

/** @brief  Enable Custom CTU Support Functions */
#define MCU_CTU_SUPPORT STD_ON

/* Add this define to introduce wait states in RAM from a treeshold and beyond */
/* #define MCU_CLOCK_MAX_FREQ_WITHOUT_RAM_WAIT 120000000UL/

/*
 * MCU183_Conf: The Id of this McuClockSettingConfig to be used as argument for
 *    the API call "Mcu_InitClock".
 */

/* Define all clock configurated */
#define MCU_CLOCK_EXT_REF_64MHZ     0U
#define MCU_CLOCK_EXT_REF_80MHZ     1U
#define MCU_CLOCK_EXT_REF_120MHZ    2U
#define MCU_CLOCK_RC_REF_80MHZ      3U
#define MCU_CLOCK_RC_REF_120MHZ     4U
#define MCU_CLOCK_DEMO_EXT_120MHZ   5U

/* Actual number of supported clock configurations */
#define MCU_CLOCKS_NUMBER           6U

/*
 * MCU176_Conf: The parameter represents the MCU Mode settings.
 */

/* Bit mask to configure MC_ME register with */
/* Enable DRUN, RUN0, SAFE, RESET modes */
#define MCU_ENABLED_MODES MCU_MODE_ENABLED_RESET | MCU_MODE_ENABLED_SAFE |\
  MCU_MODE_ENABLED_DRUN | MCU_MODE_ENABLED_RUN0

/* A DRUN configuration */
#define MCU_MODE_INIT         0U
/* A RUN0 configuration */
#define MCU_MODE_APPLICATION  1U
/* A DRUN configuration */
#define MCU_MODE_SUPERVISOR   2U
/* A SAFE configuration */
#define MCU_MODE_SAFE         3U

/* Actual number of supported modes */
#define MCU_MODES_NUMBER      4U

/*  Reset Configuration (Default):
    I/O output power-down control:          OFF (No auto I/O safe gating),
    Main Voltage Regulator:                 ON, 
    Flash:                                  Normal,
    Secondary FMPLL control (PLL1):         OFF,
    System FMPLL control    (PLL0):         OFF,
    External Oscillator (XOSC):             OFF,
    Internal RC Oscillator 16MHz (IRCOSC):  ON,
    System Clock (SYSLK):                   16 MHZ int. RC osc.
*/
#define MCU_RESET_CONF      MCU_MODE_MAIN_VOLTAGE_REG_ON |\
  MCU_MODE_RESERVED_NORM | MCU_MODE_FLAON_NORM | MCU_MODE_IRCOSC_ON |\
  MCU_MODE_SYSCLK_RC

/* Clock Output Enbled */
#define MCU_CLOCK_OUTPUT_ENABLE     1U
/* Clock Output Prescaler Factor */
#define MCU_CLOCK_PRESCALER_FACTOR  2U /* Prescaler 4x */

/* Demo Configuration Macros*/

/* Demo Configuration ID */
#define MCU_CONFIG_DEMO 0U
/* Demo Configuration Pointer */
#define MCU_CONFIG_DEMO_PTR &Mcu_Config[MCU_CONFIG_DEMO]

/* Include Static Configuration (Type Declarations) */
#include <Mcu_Cfg_internal.h>

#endif  /* MCU_CFG_H */

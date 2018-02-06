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

/** @file   Port_Cfg.h
 *  @brief  fake-druid AUTOSAR MCU Driver Configuration Header File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 *
 */


#if !(\
 ((PORT_SW_MAJOR_VERSION == 1) && \
  (PORT_SW_MINOR_VERSION == 0) && \
  (PORT_SW_PATCH_VERSION == 0))\
)
#error Port: Configuration file expected BSW module version to be 1.0.0.*
#endif

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * PORT117_Conf:  Module wide configuration parameters of the PORT driver.
 */
/* PortGeneral */

/** @brief  Development Error Detection
 *
 *  <b>PORT123_Conf:</b> Switches the Development Error Detection and 
 *  Notification on or off.<br>
 *  - <tt>TRUE</tt>: Enabled.
 *  - <tt>FALSE</tt>: Disabled.
 */
#define PORT_DEV_ERROR_DETECT   STD_OFF

/** @brief  Pin Direction Setting API
 *
 *  <b>PORT131_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Port_SetPinDirection()</tt>.<br>
 *  - <tt>TRUE</tt>: Enabled, Function <tt>Port_SetPinDirection()</tt> is
 *  available.
 *  - <tt>FALSE</tt>: Disabled, Function <tt>Port_SetPinDirection()</tt> is not
 *  available.
 */
#define PORT_SET_PIN_DIRECTION_API  STD_ON

/** @brief  Pin Mode Setting API
 *
 *  <b>PORT132_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Port_SetPinMode()</tt>.<br>
 *  - <tt>TRUE</tt>: Enabled, Function <tt>Port_SetPinMode()</tt> is available.
 *  - <tt>FALSE</tt>: Disabled, Function <tt>Port_SetPinMode()</tt> is not
 *  available.
 */
#define PORT_SET_PIN_MODE_API   STD_ON

/** @brief  Version Informations Retrieval API
 *
 *  <b>PORT133_Conf:</b> Pre-processor switch to enable / disable the API to
 *  read out the modules version information.
 *  - <tt>TRUE</tt>: Version info API enabled.
 *  - <tt>FALSE</tt>: Version info API disabled.
 */
#define PORT_VERSION_INFO_API   STD_ON


/** @brief  Port Pins DIO Configuration
 *
 *  Identifier for Port Pins as DIO Configuration.
 */

#define PORT_CONFIG_DEMO   0U

/** @brief  Port Pins DIO Configuration Pointer
 *
 *  Pointer of Port Pins as DIO Port Driver Configuration
 */
#define PORT_CONFIG_DEMO_PTR &Port_Config[PORT_CONFIG_DEMO]


/** @brief  Default Configuration
 *
 *  Identifier for Default Port Driver Configuration.
 */
#define PORT_CONFIG_DEFAULT PORT_CONFIG_DEMO

/** @brief  Default Configuration Pointer
 *
 *  Pointer of Default Port Driver Configuration
 */
#define PORT_CONFIG_DEFAULT_PTR &Port_Config[PORT_CONFIG_DEFAULT]

/* Include Static Configuration (Type Declarations) */
#include <Port_Cfg_internal.h>

#endif  /* PORT_CFG_H */

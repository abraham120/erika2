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

/** @file	Compiler_Cfg.h
 *  @brief	fake-druid AUTOSAR Compiler Configuration Header File.
 *
 *  <b>COMPILER055:</b> This file contains all the module/component specific
 *  parameters (<tt>ptrclass</tt> and <tt>memclass</tt>) that are passed to the
 *  macros defined in Compiler.h for Texas Instruments Stellaris LM4F232XXXX and
 *  Keil compiler.
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#ifndef	COMPILER_CFG_H
#define	COMPILER_CFG_H

/*
 * COMPILER040:	Each AUTOSAR software module and application software component
 * 		shall support the distinction of at least the following
 * 		different memory classes and pointer classes.
 */

/*
 * <MSN>_CODE:			To be used for code.
 * <MSN>_CONST:			To be used for global or static constants.
 * <MSN>_APPL_DATA:		To be used for references on application data
 * 				(expected to be in RAM or ROM) passed via API.
 * <MSN>_APPL_CONST:		To be used for references on application
 * 				constants (expected to be certainly in ROM,
 * 				for instance pointer of Init-function) passed
 * 				via API.
 * <MSN>_APPL_CODE:		To be used for references on application
 * 				functions (e.g. call back function pointers)
 * <MSN>_CALLOUT_CODE:		To be used for references on application
 * 				functions (e.g. callout function pointers)
 * <MSN>_VAR_NOINIT:		To be used for all global or static variables
 * 				that are never initialized
 * <MSN>_VAR_POWER_ON_INIT:	To be used for all global or static variables
 * 				that are initialized only after power on reset.
 * <MSN>_VAR_FAST:		To be used for all global or static variables
 * 				that have at least on of the following
 * 				properties:
 * 				- accessed bitwise
 * 				- frequently used
 * 				- high number of accesses in sources code
 * <MSN>_VAR:			To be used for all global or static variables
 * 				that are initialized after every reset.
 */

#define	DIO_CODE
#define	DIO_CONST
#define	DIO_APPL_DATA
#define	DIO_APPL_CONST
#define	DIO_APPL_CODE
#define	DIO_CALLOUT_CODE
#define	DIO_VAR_NOINIT
#define	DIO_VAR_POWER_ON_INIT
#define	DIO_VAR_FAST
#define	DIO_VAR

#define	GPT_CODE
#define	GPT_CONST
#define	GPT_APPL_DATA
#define	GPT_APPL_CONST
#define	GPT_APPL_CODE
#define	GPT_CALLOUT_CODE
#define	GPT_VAR_NOINIT
#define	GPT_VAR_POWER_ON_INIT
#define	GPT_VAR_FAST
#define	GPT_VAR

#define	MCU_CODE
#define	MCU_CONST
#define	MCU_APPL_DATA
#define	MCU_APPL_CONST
#define	MCU_APPL_CODE
#define	MCU_CALLOUT_CODE
#define	MCU_VAR_NOINIT
#define	MCU_VAR_POWER_ON_INIT
#define	MCU_VAR_FAST
#define	MCU_VAR

#define	PORT_CODE
#define	PORT_CONST
#define	PORT_APPL_DATA
#define	PORT_APPL_CONST
#define	PORT_APPL_CODE
#define	PORT_CALLOUT_CODE
#define	PORT_VAR_NOINIT
#define	PORT_VAR_POWER_ON_INIT
#define	PORT_VAR_FAST
#define	PORT_VAR

#endif	/* COMPILER_CFG_H */

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/** 
* \file ee_irqstub.h
* \brief Erika IRQ support, it is compiler dependent (common files for HAL have been integrated), Erika HCS12 cpu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/

#ifndef	__INCLUDE_HC12_EE_IRQSTUB_H__
#define	__INCLUDE_HC12_EE_IRQSTUB_H__

#include	"eecfg.h"
#include	"cpu/hs12xs/inc/ee_compiler.h"

#include	"cpu/common/inc/ee_context.h"

#include	"cpu/common/inc/ee_irqstub.h"

extern EE_DADD EE_s12_temp_tos;

#ifdef __CODEWARRIOR__
  #include "cpu/hs12xs/inc/ee_irqstub_cw.h"
#endif

#ifdef __COSMIC__
  #include "cpu/hs12xs/inc/ee_irqstub_cosmic.h"
#endif

/* ISR2 */
#define ISR2(f)\
static void ISR2_##f(void);\
EE_S12_ISR void f(void)\
{\
  EE_ISR2_prestub();\
  ISR2_##f();\
  EE_ISR2_poststub();\
}\
static void ISR2_##f(void)

#endif	/* __INCLUDE_HC12_EE_IRQSTUB_H__ */

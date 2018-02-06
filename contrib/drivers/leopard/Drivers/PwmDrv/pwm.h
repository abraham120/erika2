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

#ifndef EE_MCU_MPC5643L_PWM_H
#define EE_MCU_MPC5643L_PWM_H

#include <cpu/common/inc/ee_stdint.h>
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>

#define PWMA_RISING_EDGE	0xFFFFFA24U //-0x05DC
#define PWMA_FALLING_EDGE	0x05DCU

#define PWM_MODULO 0xBB8
//#define PWM_MODULO 0x1778 // PWM_Period 100 us
#define PWM_INIT -0xBB8
//#define PWM_INIT -0x1778	// PWM_Period 100 us

#define PWM0_A0_ENABLE 0x100
#define PWM0_A1_ENABLE 0x200
#define PWM0_A2_ENABLE 0x400
#define PWM0_B0_ENABLE 0x10
#define PWM0_B1_ENABLE 0x20
#define PWM0_B2_ENABLE 0x40

#define PWM0_A0_LOAD 0x1
#define PWM0_A1_LOAD 0x2
#define PWM0_A2_LOAD 0x4
#define PWM0_B0_LOAD 0x1
#define PWM0_B1_LOAD 0x2
#define PWM0_B2_LOAD 0x4

void InitFlexPWM0(void);
void InitFlexPWM0_AB(void);
void OffPWM (void);
void OnPWM (void);
void TestPWMOutputDrive(void);
void PWMOutputLow (void);
void PWM0_A0_load_new_rising_edge(unsigned int val);
void PWM0_A0_load_new_falling_edge(unsigned int val);

void PWM0_A1_load_new_rising_edge(unsigned int val);
void PWM0_A1_load_new_falling_edge(unsigned int val);

void PWM0_A2_load_new_rising_edge(unsigned int val);
void PWM0_A2_load_new_falling_edge(unsigned int val);

#endif

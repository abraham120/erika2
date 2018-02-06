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
 
/** 
    @file   ee_pwm.h
    @brief  This header contains a simple PWM driver. 
            Those API let you set a frequency and a duty cycle
    @author Dario di Stefano
    @date   2011
**/ 
 
#ifndef __INCLUDE_MICROCHIP_DSPIC_BOARD_H__
#define __INCLUDE_MICROCHIP_DSPIC_BOARD_H__

/********************************************/
/*              PWM                         */
/********************************************/
#ifdef __USE_PWM__

/******************************* 
Include device header
********************************/
#include "mcu/microchip_dspic/inc/ee_mcu.h"

/** Max duty cicle value **/
#define EE_PWM_DUTY_MAX    32768U

/** PWM channel IDs 
    @{
**/
#define EE_PWM_MC1  1
#define EE_PWM_MC2  2

/** @} **/

/** PWM Modes 
    @{
**/
#define EE_H_PWM_L_OVER     1
#define EE_H_OVER_L_PWM     2
#define EE_H_PWM_L_PWM      3  
#define EE_H_OVER_L_OVER    4
/** @} **/

/** 
    PWM API error codes
    @{
 **/
#define EE_PWM_NO_ERROR             0
#define EE_PWM_ERROR_INVALID_CH_ID  -1
#define EE_PWM_ERROR_INVALID_DUTY   -2
#define EE_PWM_ERROR_INVALID_FREQ   -3
/** @} **/

/** Type for PWM channel IDs **/
typedef EE_UINT8 EE_PwmId;
/** Type for PWM pin output configuration **/
typedef EE_UINT8 EE_PwmOutputMode; 

/**
    @brief Initialize PWM channel.
    
    @param pwm_ch (EE_PwmId): pwm channel's Id.
    @param pwm_freq (EE_UINT32): pwm frequency
    @param pwm_output_mode (EE_PwmOutputMode): pwm pin output mode
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_pwm_init(EE_PwmId pwm_ch, EE_UINT32 pwm_freq, EE_PwmOutputMode pwm_output_mode);

/**
    @brief Close a PWM channel.
    
    @param pwm_ch (EE_PwmId): pwm channel's Id.
    
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_pwm_close(EE_PwmId pwm_ch);

/**
    @brief Set PWM channel's duty cicle and if, this value is not 0, start it.
    
    @param pwm_ch (EE_PwmId): pwm channel's Id.
    @param duty (EE_UINT16): pwm duty cycle [0, EE_PWM_DUTY_MAX]
    
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_pwm_set_duty(EE_PwmId pwm_ch, EE_UINT16 duty);

/**
    @brief Set PWM channel's pins override.
    
    @param pwm_ch (EE_PwmId): pwm channel's Id.
    @param dir (char): pwm pins override to set motor direction 
    
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_pwm_set_direction(EE_PwmId pwm_ch, char dir);

#endif /* __USE_PWM__ */

#endif /* __INCLUDE_MICROCHIP_DSPIC_BOARD_H__ */

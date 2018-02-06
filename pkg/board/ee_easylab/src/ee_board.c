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
#include "board/ee_easylab/inc/ee_board.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"

#ifdef __dsPIC33FJ64MC802__

#ifdef __USE_BUZZER__

#include "mcu/microchip_dspic/inc/ee_timer.h"

void EE_buzzer_toggle(void)
{
    LATAbits.LATA2 = ~LATAbits.LATA2;
}

void EE_buzzer_start(EE_UINT16 freq)
{
    /*
     * period (us) = 1000000UL / freq (Hz);
     */
    if ((freq > EE_BUZZER_MIN_FREQ) && (freq <= EE_BUZZER_MAX_FREQ)) {
        TRISAbits.TRISA2 = 0; /* output */
        LATAbits.LATA2 = 0;
        /* to get the desired period I have to half the given 
         * value becauze the timer call back is a toggle function so 
         * a period is 2 * Tisr long (Tisr: Interrupt Period).
         */
        EE_UINT16 period = 1000000UL / (freq * 2);
        EE_timer_set_callback(EE_TIMER_2, EE_buzzer_toggle);
        EE_timer_soft_init(EE_TIMER_2, period);
        EE_timer_start(EE_TIMER_2);
    }
}

void EE_buzzer_stop(void)
{
    EE_timer_set_callback(EE_TIMER_2, NULL);
    EE_timer_stop(EE_TIMER_2);
}
#endif /* __USE_BUZZER__ */

#ifdef __USE_PWM__

EE_INT16 EE_easylab_pwm_init(EE_UINT8 pwm_pin, EE_UINT32 pwm_freq)
{
    EE_INT16 error;
    switch(pwm_pin)
    {
        case EE_EASYLAB_PWM1:
            error = EE_pwm_init(EE_PWM_MC1, pwm_freq, EE_H_OVER_L_PWM);
        break;
        case EE_EASYLAB_PWM2:
            error = EE_pwm_init(EE_PWM_MC1, pwm_freq, EE_H_PWM_L_OVER);
        break;
        case EE_EASYLAB_PWM3:
            error = EE_pwm_init(EE_PWM_MC2, pwm_freq, EE_H_OVER_L_PWM);
        break;
        case EE_EASYLAB_PWM4:
            error = EE_pwm_init(EE_PWM_MC2, pwm_freq, EE_H_PWM_L_OVER);
        break;
        case EE_EASYLAB_PWM12:
            error = EE_pwm_init(EE_PWM_MC1, pwm_freq, EE_H_PWM_L_PWM);
        break;
        case EE_EASYLAB_PWM34:
            error = EE_pwm_init(EE_PWM_MC2, pwm_freq, EE_H_PWM_L_PWM);
        break;
        default:
            error = EE_EASYLAB_PWM_ERROR_INVALID_PIN_ID;
    }
    return error;
}

EE_INT16 EE_easylab_pwm_close(EE_UINT8 pwm_pin)
{
    EE_INT16 error;
    switch(pwm_pin)
    {
        case EE_EASYLAB_PWM1:
            error = EE_pwm_close(EE_PWM_MC1);
        break;
        case EE_EASYLAB_PWM2:
            error = EE_pwm_close(EE_PWM_MC1);
        break;
        case EE_EASYLAB_PWM3:
            error = EE_pwm_close(EE_PWM_MC2);
        break;
        case EE_EASYLAB_PWM4:
            error = EE_pwm_close(EE_PWM_MC2);
        break;
        case EE_EASYLAB_PWM12:
            error = EE_pwm_close(EE_PWM_MC1);
        break;
        case EE_EASYLAB_PWM34:
            error = EE_pwm_close(EE_PWM_MC2);
        break;
        default:
            error = EE_EASYLAB_PWM_ERROR_INVALID_PIN_ID;
    }
    return error;
}

EE_INT16 EE_easylab_pwm_set_direction(EE_UINT8 pwm_pin)
{
    EE_INT16 error = 0;
    switch(pwm_pin)
    {
        case EE_EASYLAB_PWM1:
            EE_pwm_set_direction(EE_PWM_MC1, EE_H_OVER_L_PWM);
        break;
        case EE_EASYLAB_PWM2:
            EE_pwm_set_direction(EE_PWM_MC1, EE_H_PWM_L_OVER);
        break;
        case EE_EASYLAB_PWM3:
            EE_pwm_set_direction(EE_PWM_MC2, EE_H_OVER_L_PWM);
        break;
        case EE_EASYLAB_PWM4:
            EE_pwm_set_direction(EE_PWM_MC2, EE_H_PWM_L_OVER);
        break;
        case EE_EASYLAB_PWM12:
            EE_pwm_set_direction(EE_PWM_MC1, EE_H_PWM_L_PWM);
        break;
        case EE_EASYLAB_PWM34:
            EE_pwm_set_direction(EE_PWM_MC2, EE_H_PWM_L_PWM);
        break;
        default:
            error = EE_EASYLAB_PWM_ERROR_INVALID_PIN_ID;
    }
    return error;
}

EE_INT16 EE_easylab_pwm_set_duty(EE_UINT8 pwm_pin, EE_UINT16 duty){
    EE_INT16 error;
    switch(pwm_pin)
    {
        case EE_EASYLAB_PWM1:
            EE_easylab_pwm_set_direction(EE_EASYLAB_PWM1);
            error = EE_pwm_set_duty(EE_PWM_MC1, duty);
        break;
        case EE_EASYLAB_PWM2:
            EE_easylab_pwm_set_direction(EE_EASYLAB_PWM2);
            error = EE_pwm_set_duty(EE_PWM_MC1, duty);
        break;
        case EE_EASYLAB_PWM3:
            EE_easylab_pwm_set_direction(EE_EASYLAB_PWM3);
            error = EE_pwm_set_duty(EE_PWM_MC2, duty);
        break;
        case EE_EASYLAB_PWM4:
            EE_easylab_pwm_set_direction(EE_EASYLAB_PWM4);
            error = EE_pwm_set_duty(EE_PWM_MC2, duty);
        break;
        case EE_EASYLAB_PWM12:
            EE_easylab_pwm_set_direction(EE_EASYLAB_PWM12);
            error = EE_pwm_set_duty(EE_PWM_MC1, duty);
        break;
        case EE_EASYLAB_PWM34:
            EE_easylab_pwm_set_direction(EE_EASYLAB_PWM34);
            error = EE_pwm_set_duty(EE_PWM_MC2, duty);
        break;
        default:
            error = EE_EASYLAB_PWM_ERROR_INVALID_PIN_ID;
    }
    return error;

}
#endif /* __USE_PWM__ */ 

#endif /*__dsPIC33FJ64MC802__ */



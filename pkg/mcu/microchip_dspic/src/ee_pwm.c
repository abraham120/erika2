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

#include "mcu/microchip_dspic/inc/ee_pwm.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"

void EE_pwm1_set_duty(EE_UINT16 duty)
{
    /* please, note the shift operation... (used the round trick...) */
    P1DC1 = (((EE_UINT32)duty * (P1TPER + 1) + (EE_PWM_DUTY_MAX / 2)) / EE_PWM_DUTY_MAX) << 1;
}

/*
    Set MCPWM1 motor direction  
 */
void EE_pwm1_set_direction(char dir)
{
    switch(dir)
    {
        case EE_H_PWM_L_OVER:
            P1OVDCONbits.POVD1H = 1;      /* PWM */
            P1OVDCONbits.POVD1L = 0;      /* OVERRIDE */
            break;
        case EE_H_OVER_L_PWM:
            P1OVDCONbits.POVD1H = 0;      /* OVERRIDE */
            P1OVDCONbits.POVD1L = 1;      /* PWM */
            break;
        case EE_H_PWM_L_PWM:
            P1OVDCONbits.POVD1H = 1;      /* PWM */
            P1OVDCONbits.POVD1L = 1;      /* PWM */
            break;
        case EE_H_OVER_L_OVER:
            P1OVDCONbits.POVD1H = 0;      /* OVERRIDE */
            P1OVDCONbits.POVD1L = 0;      /* OVERRIDE */
            break;
        default:
            P1OVDCONbits.POVD1H = 1;      /* PWM */
            P1OVDCONbits.POVD1L = 1;      /* PWM */
    }
}

void EE_pwm1_close(void)
{
    P1TCONbits.PTEN = 0;
}

EE_INT16 EE_pwm1_init(EE_UINT32 pwm_freq, EE_UINT16 init_duty, char dir)
{
    if(P1TCONbits.PTEN == 0)
    {
        EE_UINT16 ptper = EE_get_peripheral_clock() / pwm_freq;    
        
        if(ptper <= 1)
            return EE_PWM_ERROR_INVALID_FREQ;
        
        if(init_duty > EE_PWM_DUTY_MAX)
            return EE_PWM_ERROR_INVALID_DUTY;

        P1TCONbits.PTEN =   0;
        P1TCONbits.PTSIDL = 0;          /*PWM time base runs in CPU Idle mode */
        P1TCONbits.PTOPS =  0b0000;     /*1:1 postscale */
        P1TCONbits.PTCKPS = 0b00;       /*PWM time base input clock period is TCY (1:1 prescale) */
        P1TCONbits.PTMOD =  0b00;       /*PWM time base operates in a Free-Running mode */
        P1TMRbits.PTMR =    0;
        P1TPER =            ptper - 1;  /* prescaler == 1 */
        P1SECMP =           0;
        
        PWM1CON1bits.PMOD1 = 1;         /*PWM I/O pin pair is in Independent PWM Output mode */
        PWM1CON1bits.PEN1H = 1;         /*PWMxy pin is enabled for PWM output */
        PWM1CON1bits.PEN1L = 1;         /*PWMxy pin is enabled for PWM output */
    
        PWM1CON2bits.SEVOPS = 0b0000;
        PWM1CON2bits.IUE    = 0;
        PWM1CON2bits.OSYNC  = 1;
        PWM1CON2bits.UDIS   = 0;

        P1DTCON1 =          0;
        P1FLTACON =         0;

        P1OVDCONbits.POUT1H = 0; 
        P1OVDCONbits.POUT1L = 0;
        EE_pwm1_set_direction(dir);
        
        P1DC1 = 0 << 1;    
        EE_pwm1_set_duty(init_duty);
        
#ifndef _FLTA1IE
#define _FLTA1IE _FLTAIE
#endif
#ifndef _PWM1IE
#define _PWM1IE _PWMIE
#endif
        _FLTA1IE =  0;
        _PWM1IE  =  0;
        P1TCONbits.PTEN  =  1;
    }
    else
    {
        EE_pwm1_set_direction(dir);
        EE_pwm1_set_duty(init_duty);
    }
    return EE_PWM_NO_ERROR;
}


#ifdef __dsPIC33FJ64MC802__


void EE_pwm2_set_duty(EE_UINT16 duty)
{
    /* please, note the shift operation... (used the round trick...) */
    P2DC1 = (((EE_UINT32)duty * (P2TPER + 1) + (EE_PWM_DUTY_MAX / 2)) / EE_PWM_DUTY_MAX) << 1;
}

/*
    Set MCPWM1 motor direction  
 */
void EE_pwm2_set_direction(char dir)
{
    switch(dir)
    {
        case EE_H_PWM_L_OVER:
            P2OVDCONbits.POVD1H = 1;      /* PWM */
            P2OVDCONbits.POVD1L = 0;      /* OVERRIDE */
            break;
        case EE_H_OVER_L_PWM:
            P2OVDCONbits.POVD1H = 0;      /* OVERRIDE */
            P2OVDCONbits.POVD1L = 1;      /* PWM */
            break;
        case EE_H_PWM_L_PWM:
            P2OVDCONbits.POVD1H = 1;      /* PWM */
            P2OVDCONbits.POVD1L = 1;      /* PWM */
            break;
        case EE_H_OVER_L_OVER:
            P2OVDCONbits.POVD1H = 0;      /* OVERRIDE */
            P2OVDCONbits.POVD1L = 0;      /* OVERRIDE */
            break;
        default:
            P2OVDCONbits.POVD1H = 1;      /* PWM */
            P2OVDCONbits.POVD1L = 1;      /* PWM */
    }
}

void EE_pwm2_close(void)
{
    P2TCONbits.PTEN = 0;
}

EE_INT16 EE_pwm2_init(EE_UINT32 pwm_freq, EE_UINT16 init_duty, char dir)
{
    if(P2TCONbits.PTEN == 0)
    {
        EE_UINT16 ptper = EE_get_peripheral_clock() / pwm_freq;    
        
        if( (ptper <= 1) || (init_duty > 100) )
            return EE_PWM_ERROR_INVALID_DUTY;

        P2TCONbits.PTEN =       0;
        P2TCONbits.PTSIDL =     0;          /*PWM time base runs in CPU Idle mode */
        P2TCONbits.PTOPS =      0b0000;     /*1:1 postscale */
        P2TCONbits.PTCKPS =     0b00;       /*PWM time base input clock period is TCY (1:1 prescale) */
        P2TCONbits.PTMOD =      0b00;       /*PWM time base operates in a Free-Running mode */
        P2TMRbits.PTMR =        0;
        P2TPER =                ptper - 1;  /* prescaler == 1 */
        P2SECMP =               0;
        
        PWM2CON1bits.PMOD1 = 1;             /*PWM I/O pin pair is in Independent PWM Output mode */
        PWM2CON1bits.PEN1H = 1;             /*PWMxy pin is enabled for PWM output */
        PWM2CON1bits.PEN1L = 1;             /*PWMxy pin is enabled for PWM output */
    
        PWM2CON2bits.SEVOPS = 0b0000;
        PWM2CON2bits.IUE    = 0;
        PWM2CON2bits.OSYNC  = 1;
        PWM2CON2bits.UDIS   = 0;

        P2DTCON1 =          0;
        P2FLTACON =         0;

        P2OVDCONbits.POUT1H = 0; 
        P2OVDCONbits.POUT1L = 0;
        EE_pwm2_set_direction(dir);
        
        P2DC1 = 0<<1;    
        EE_pwm2_set_duty(init_duty);
        
        IEC4bits.FLTA2IE =     0;
        IEC4bits.PWM2IE  =     0;
        P2TCONbits.PTEN  =     1;
    }
    else
    {
        EE_pwm2_set_direction(dir);
        EE_pwm2_set_duty(init_duty);
    }
    return EE_PWM_NO_ERROR;
}

#else /*__dsPIC33FJ64MC802__ */

void EE_pwm2_set_duty(EE_UINT16 duty) {
}

/*
    Set MCPWM1 motor direction  
 */
void EE_pwm2_set_direction(char dir) {
}

void EE_pwm2_close(void) {
}

EE_INT16 EE_pwm2_init(EE_UINT32 pwm_freq, EE_UINT16 init_duty, char dir)
{
    return EE_PWM_ERROR_INVALID_CH_ID;
}

#endif /*__dsPIC33FJ64MC802__ */

EE_INT16 EE_pwm_init(EE_PwmId pwm_ch, EE_UINT32 pwm_freq, EE_PwmOutputMode pwm_output_mode)
{
    EE_INT16 error;
    switch(pwm_ch)
    {
        case EE_PWM_MC1:
            error = EE_pwm1_init(pwm_freq, 0, pwm_output_mode);
        break;
        case EE_PWM_MC2:
            error = EE_pwm2_init(pwm_freq, 0, pwm_output_mode);
        break;
        default:
            error = EE_PWM_ERROR_INVALID_CH_ID;
    }
    return error;
}

EE_INT16 EE_pwm_close(EE_PwmId pwm_ch)
{
    EE_INT16 error = EE_PWM_NO_ERROR;
    switch(pwm_ch)
    {
        case EE_PWM_MC1:
            EE_pwm1_close();
        break;
        case EE_PWM_MC2:
            EE_pwm2_close();
        break;
        default:
            error = EE_PWM_ERROR_INVALID_CH_ID;        
    }
    return error;
}

EE_INT16 EE_pwm_set_duty(EE_PwmId pwm_ch, EE_UINT16 duty)
{
    EE_INT16 error = EE_PWM_NO_ERROR;
    switch(pwm_ch)
    {
        case EE_PWM_MC1:
            EE_pwm1_set_duty(duty);
        break;
        case EE_PWM_MC2:
            EE_pwm2_set_duty(duty);
        break;
        default:
            error = EE_PWM_ERROR_INVALID_CH_ID;        
    }
    return error;
}

EE_INT16 EE_pwm_set_direction(EE_PwmId pwm_ch, char dir)
{
    EE_INT16 error = EE_PWM_NO_ERROR;
    switch(pwm_ch)
    {
        case EE_PWM_MC1:
            EE_pwm1_set_direction(dir);
        break;
        case EE_PWM_MC2:
            EE_pwm2_set_direction(dir);
        break;
        default:
            error = EE_PWM_ERROR_INVALID_CH_ID;        
    }
    return error;
}



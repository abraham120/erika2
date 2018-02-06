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
    @file   ee_board.h
    @brief  easylab board header file.

    Header file taht contains board's API declaration, and defines
    for remap mcu drivers on board layout.

    @author Errico Guidieri
    @date   2011
  */

#ifndef __INCLUDE_EASYLAB_BOARD_H__
#define __INCLUDE_EASYLAB_BOARD_H__

/*******************************
Include device header
********************************/
#include "mcu/microchip_dspic/inc/ee_mcu.h"

#ifdef __USE_UART__
/** configure UART1_RX driver pin **/
#define EE_Board_Uart1_Rx EE_PIN_RP10
/** configure UART1_TX driver pin **/
#define EE_Board_Uart1_Tx EE_PIN_RP11
#endif /* __USE_UART__ */

#ifdef __USE_LEDS__

#ifdef __dsPIC33FJ64MC802__

/* DIO bit allocation

Board     dsPIC     LED
DIO1       RA3       7
DIO2       RB4       8
DIO3       RA4       9
DIO4       RB5       10
DIO5       RB12      1
DIO6       RB13      2
DIO7       RB7       3
DIO8       RB6       4
           RB15      sys
*/

/** @brief Initialize all LEDS **/
__INLINE__ void EE_leds_init(void){
    /* Inizializzione LED pins regA */
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;

    /* Inizializzione LED pins regB */
    TRISBbits.TRISB4  = 0;
    TRISBbits.TRISB5  = 0;
    TRISBbits.TRISB6  = 0;
    TRISBbits.TRISB7  = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;

    /* Inizializzazione system LED (the one on microstick) */
    TRISBbits.TRISB15 = 0;
}

/** @brief Enable all LEDS **/
__INLINE__ void EE_leds_enable(void){
    /* Abilitazione LED pins regA */
    LATAbits.LATA3 = 1;
    LATAbits.LATA4 = 1;

    /* Abilitazione LED pins regB */
    LATBbits.LATB4  = 1;
    LATBbits.LATB5  = 1;
    LATBbits.LATB6  = 1;
    LATBbits.LATB7  = 1;
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;

    /* system LED (the one on microstick) */
    LATBbits.LATB15 = 1;
}

/** @brief Disable all LEDS **/
__INLINE__ void EE_leds_disable(void){
    /* Disabilitazione LED pins regA */
    LATAbits.LATA3 = 0;
    LATAbits.LATA4 = 0;

    /* Disabilitazione LED pins regB */
    LATBbits.LATB4  = 0;
    LATBbits.LATB5  = 0;
    LATBbits.LATB6  = 0;
    LATBbits.LATB7  = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;

    /* system LED (the one on microstick) */
    LATBbits.LATB15 = 0;
}

/** @brief Inizializzazione system LED (the one on microstick) **/
__INLINE__ void EE_sys_led_init(void)
{
    TRISBbits.TRISB15 = 0;
}

/** @brief Enable system led (the one on microstick) **/
__INLINE__ void EE_sys_led_on(void){
    LATBbits.LATB15 = 1;
}

/** @brief Disable system led (the one on microstick) **/
__INLINE__ void EE_sys_led_off(void){
    LATBbits.LATB15 = 0;
}

/** @brief Toogle system led (the one on microstick) **/
__INLINE__ void EE_sys_led_toggle(void){
    LATBbits.LATB15 = ~LATBbits.LATB15;
}

/** @brief Initialize led 1 **/
__INLINE__ void EE_led1_init(void)
{
    TRISAbits.TRISA3 = 0;
}

/** @brief Enable led 1 **/
__INLINE__ void EE_led1_on(void){
    LATAbits.LATA3 = 1;
}

/** @brief Disable led 1 **/
__INLINE__ void EE_led1_off(void){
    LATAbits.LATA3 = 0;
}

/** @brief Toggle led 1 **/
__INLINE__ void EE_led1_toggle(void){
    LATAbits.LATA3 = ~LATAbits.LATA3;
}

/** @brief Initialize led 2 **/
__INLINE__ void EE_led2_init(void)
{
    TRISBbits.TRISB4 = 0;
}

/** @brief Enable led 2 **/
__INLINE__ void EE_led2_on(void){
    LATBbits.LATB4 = 1;
}

/** @brief Disable led 2 **/
__INLINE__ void EE_led2_off(void){
    LATBbits.LATB4 = 0;
}

/** @brief Toggle led 2 **/
__INLINE__ void EE_led2_toggle(void){
    LATBbits.LATB4 = ~LATBbits.LATB4;
}

/** @brief Initialize led 3 **/
__INLINE__ void EE_led3_init(void)
{
    TRISAbits.TRISA4 = 0;
}

/** @brief Enable led 3 **/
__INLINE__ void EE_led3_on(void){
    LATAbits.LATA4 = 1;
}

/** @brief Disable led 3 **/
__INLINE__ void EE_led3_off(void){
    LATAbits.LATA4 = 0;
}

/** @brief Toogle led 3 **/
__INLINE__ void EE_led3_toggle(void){
    LATAbits.LATA4 = ~LATAbits.LATA4;
}

/** @brief Initialize led 4 **/
__INLINE__ void EE_led4_init(void)
{
    TRISBbits.TRISB5 = 0;
}

/** @brief Enable led 4 **/
__INLINE__ void EE_led4_on(void){
    LATBbits.LATB5 = 1;
}

/** @brief Disable led 4 **/
__INLINE__ void EE_led4_off(void){
    LATBbits.LATB5 = 0;
}

/** @brief Toggle led 4 **/
__INLINE__ void EE_led4_toggle(void){
    LATBbits.LATB5 = ~LATBbits.LATB5;
}

/** @brief Initialize led 5 **/
__INLINE__ void EE_led5_init(void)
{
    TRISBbits.TRISB12 = 0;
}

/** @brief Enable led5 **/
__INLINE__ void EE_led5_on(void){
    LATBbits.LATB12 = 1;
}

/** @brief Disable led 5 **/
__INLINE__ void EE_led5_off(void){
    LATBbits.LATB12 = 0;
}

/** @brief Toogle led 5 **/
__INLINE__ void EE_led5_toggle(void){
    LATBbits.LATB12 = ~LATBbits.LATB12;
}

/** @brief Initialize led 6 **/
__INLINE__ void EE_led6_init(void)
{
    TRISBbits.TRISB13 = 0;
}

/** @brief Enable led 6 **/
__INLINE__ void EE_led6_on(void){
    LATBbits.LATB13 = 1;
}

/** @brief Disable led 6 **/
__INLINE__ void EE_led6_off(void){
    LATBbits.LATB13 = 0;
}

/** @brief Toggle led 6 **/
__INLINE__ void EE_led6_toggle(void){
    LATBbits.LATB13 = ~LATBbits.LATB13;
}

/** @brief Initialize led 7 **/
__INLINE__ void EE_led7_init(void)
{
    TRISBbits.TRISB7 = 0;
}

/** @brief Enable led 7 **/
__INLINE__ void EE_led7_on(void){
    LATBbits.LATB7 = 1;
}

/** @brief Disable led 7 **/
__INLINE__ void EE_led7_off(void){
    LATBbits.LATB7 = 0;
}

/** @brief Toggle led 7 **/
__INLINE__ void EE_led7_toggle(void){
    LATBbits.LATB7 = ~LATBbits.LATB7;
}

/** @brief Initialize led 8 **/
__INLINE__ void EE_led8_init(void)
{
    TRISBbits.TRISB6 = 0;
}

/** @brief Enable led 8 **/
__INLINE__ void EE_led8_on(void){
    LATBbits.LATB6 = 1;
}

/** @brief Disable led 8 **/
__INLINE__ void EE_led8_off(void){
    LATBbits.LATB6 = 0;
}

/** @brief Toggle led 8 **/
__INLINE__ void EE_led8_toggle(void){
    LATBbits.LATB6 = ~LATBbits.LATB6;
}


#define EE_LED0 0
#define EE_LED1 1
#define EE_LED2 2
#define EE_LED3 3
#define EE_LED4 4
#define EE_LED5 5
#define EE_LED6 6
#define EE_LED7 7
#define EE_LED8 8

/**
    @brief init LEDx
**/
__INLINE__ void EE_led_init(int led_id)
{
    switch (led_id){
	case EE_LED1:
	  EE_led1_init();
	  break;
	case EE_LED2:
	  EE_led2_init();
	  break;
	case EE_LED3:
	  EE_led3_init();
	  break;
	case EE_LED4:
	  EE_led4_init();
	  break;
	case EE_LED5:
	  EE_led5_init();
	  break;
	case EE_LED6:
	  EE_led6_init();
	  break;
	case EE_LED7:
	  EE_led7_init();
	  break;
	case EE_LED8:
	  EE_led8_init();
	  break;
    }
}

/**
    @brief write LEDx
**/
__INLINE__ void EE_led_write(int led_id, EE_BIT bit)
{
    switch (led_id){
	case EE_LED1:
	  if(bit)
	    EE_led1_on();
	  else
	    EE_led1_off();
	  break;
	case EE_LED2:
	  if(bit)
	    EE_led2_on();
	  else
	    EE_led2_off();
	  break;
	case EE_LED3:
	  if(bit)
	    EE_led3_on();
	  else
	    EE_led3_off();
	  break;
	case EE_LED4:
	  if(bit)
	    EE_led4_on();
	  else
	    EE_led4_off();
	  break;
	case EE_LED5:
	  if(bit)
	    EE_led5_on();
	  else
	    EE_led5_off();
	  break;
	case EE_LED6:
	  if(bit)
	    EE_led6_on();
	  else
	    EE_led6_off();
	  break;
	case EE_LED7:
	  if(bit)
	    EE_led7_on();
	  else
	    EE_led7_off();
	  break;
	case EE_LED8:
	  if(bit)
	    EE_led8_on();
	  else
	    EE_led8_off();
	  break;
    }
}

#endif /* __dsPIC33FJ64MC802__ */
#endif /* __USE_LEDS__ */

#ifdef __USE_DIO__
#ifdef __dsPIC33FJ64MC802__
/* DIO bit allocation

Board     dsPIC
DIO1       RA3
DIO2       RB4
DIO3       RA4
DIO4       RB5
DIO5       RB12
DIO6       RB13
DIO7       RB7
DIO8       RB6
*/

#endif /*__dsPIC33FJ64MC802__ */

/**
    @brief configure DIO1
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio1_configure(EE_BIT in)
{
    TRISAbits.TRISA3 = in;
}

/**
    @brief write on DIO1
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio1_write(EE_BIT bit)
{
    LATAbits.LATA3 = bit;
}

/**
    @brief read DIO1
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio1_read(void)
{
    return PORTAbits.RA3;
}

/**
    @brief configure DIO2
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio2_configure(EE_BIT in)
{
    TRISBbits.TRISB4 = in;
}

/**
    @brief write on DIO2
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio2_write(EE_BIT bit)
{
    LATBbits.LATB4 = bit;
}

/**
    @brief read DIO2
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio2_read(void)
{
    return PORTBbits.RB4;
}

/**
    @brief configure DIO3
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio3_configure(EE_BIT in)
{
    TRISAbits.TRISA4 = in;
}

/**
    @brief write on DIO3
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio3_write(EE_BIT bit)
{
    LATAbits.LATA4 = bit;
}

/**
    @brief read DIO3
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio3_read(void)
{
    return PORTAbits.RA4;
}

/**
    @brief configure DIO4
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio4_configure(EE_BIT in)
{
    TRISBbits.TRISB5 = in;
}

/**
    @brief write on DIO4
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio4_write(EE_BIT bit)
{
    LATBbits.LATB5 = bit;
}

/**
    @brief read DIO4
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio4_read(void)
{
    return PORTBbits.RB5;
}

/**
    @brief configure DIO5
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio5_configure(EE_BIT in)
{
    TRISBbits.TRISB12 = in;
}

/**
    @brief write on DIO5
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio5_write(EE_BIT bit)
{
    LATBbits.LATB12 = bit;
}

/**
    @brief read DIO5
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio5_read(void)
{
    return PORTBbits.RB12;
}

/**
    @brief configure DIO6
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio6_configure(EE_BIT in)
{
    TRISBbits.TRISB13 = in;
}

/**
    @brief write on DIO6
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio6_write(EE_BIT bit)
{
    LATBbits.LATB13 = bit;
}

/**
    @brief read DIO6
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio6_read(void)
{
    return PORTBbits.RB13;
}

/**
    @brief configure DIO7
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio7_configure(EE_BIT in)
{
    TRISBbits.TRISB7 = in;
}

/**
    @brief write on DIO7
    @param bit: value to set on pin
**/
__INLINE__ void EE_dio7_write(EE_BIT bit)
{
    LATBbits.LATB7 = bit;
}

/**
    @brief read DIO7
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio7_read(void)
{
    return PORTBbits.RB7;
}

/**
    @brief configure DIO7
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio8_configure(EE_BIT in)
{
    TRISBbits.TRISB6 = in;
}

/** 
    @brief write on DIO8 
    @param bit: value to set on pin 
**/
__INLINE__ void EE_dio8_write(EE_BIT bit)
{
    LATBbits.LATB6 = bit;
}

/**
    @brief read DIO8
    @return value set on pin
**/
__INLINE__ EE_BIT EE_dio8_read(void)
{
    return PORTBbits.RB6;
}


#define EE_DIO1 0
#define EE_DIO2 1
#define EE_DIO3 2
#define EE_DIO4 3
#define EE_DIO5 4
#define EE_DIO6 5
#define EE_DIO7 6
#define EE_DIO8 7

/**
    @brief configure DIOx
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio_configure(int dio_id, EE_BIT in)
{
    switch (dio_id){
	case EE_DIO1:
	  EE_dio1_configure(in);
	  break;
	case EE_DIO2:
	  EE_dio2_configure(in);
	  break;
	case EE_DIO3:
	  EE_dio3_configure(in);
	  break;
	case EE_DIO4:
	  EE_dio4_configure(in);
	  break;
	case EE_DIO5:
	  EE_dio5_configure(in);
	  break;
	case EE_DIO6:
	  EE_dio6_configure(in);
	  break;
	case EE_DIO7:
	  EE_dio7_configure(in);
	  break;
	case EE_DIO8:
	  EE_dio8_configure(in);
	  break;
    }
}

/**
    @brief write DIOx
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio_write(int dio_id, EE_BIT bit)
{
    switch (dio_id){
	case EE_DIO1:
	  EE_dio1_write(bit);
	  break;
	case EE_DIO2:
	  EE_dio2_write(bit);
	  break;
	case EE_DIO3:
	  EE_dio3_write(bit);
	  break;
	case EE_DIO4:
	  EE_dio4_write(bit);
	  break;
	case EE_DIO5:
	  EE_dio5_write(bit);
	  break;
	case EE_DIO6:
	  EE_dio6_write(bit);
	  break;
	case EE_DIO7:
	  EE_dio7_write(bit);
	  break;
	case EE_DIO8:
	  EE_dio8_write(bit);
	  break;
    }
}

/**
    @brief read DIOx
    @param in: TRUE if the pin is a IN, FALSE if it is an OUT
**/
__INLINE__ void EE_dio_read(int dio_id, EE_BIT *bit)
{
    switch (dio_id){
	case EE_DIO1:
	  *bit = EE_dio1_read();
	  break;
	case EE_DIO2:
	  *bit = EE_dio2_read();
	  break;
	case EE_DIO3:
	  *bit = EE_dio3_read();
	  break;
	case EE_DIO4:
	  *bit = EE_dio4_read();
	  break;
	case EE_DIO5:
	  *bit = EE_dio5_read();
	  break;
	case EE_DIO6:
	  *bit = EE_dio6_read();
	  break;
	case EE_DIO7:
	  *bit = EE_dio7_read();
	  break;
	case EE_DIO8:
	  *bit = EE_dio8_read();
	  break;
    }
}

#endif /*__USE_DIO__ */

#ifdef __USE_BUZZER__

#ifndef __USE_TIMER__
#error "You must define EE_OPT = __USE_TIMER__ easylab buzzer"
#endif

#define EE_BUZZER_MAX_FREQ 48000U
#define EE_BUZZER_MIN_FREQ 100U

/**
    @brief Init the pin for buzzer
**/
__INLINE__ void EE_buzzer_init(void){
    TRISAbits.TRISA2 = 0; /* output */
}

/**
    @brief Start the buzzer

    Start the buzzer. These Buzzer API use Timer2 of dspic mcu.

    @param freq (EE_UINT16): output square wave frequency, that drive the buzzer
        between [100, 48000] Hz
**/
void EE_buzzer_start(EE_UINT16 freq);

/**
    @brief Togle the status of the GPIO pin that driver the buzzer
        (used as callback for the timer handler)
**/
void EE_buzzer_toggle(void);

/**
    @brief Stop the buzzer
**/
void EE_buzzer_stop(void);

#endif /* __USE_BUZZER__ */

#ifdef __USE_ADC__

/**
    Remap ADC channels IDs on right pins
    @{
**/
#define EE_ADC_AN1   EE_ADC_PIN0
#define EE_ADC_AN2   EE_ADC_PIN1
#define EE_ADC_AN3   EE_ADC_PIN4
#define EE_ADC_AN4   EE_ADC_PIN5
/** @} */

#include "mcu/microchip_dspic/inc/ee_adc.h"

/** @brief Initialize ADC driver.

    @param adc_ch_id (EE_AdcChId): channel's ID to initialize
    @param volt_ref (EE_Adc_VoltageRef): a voltage reference pair enum values
    @param bit_res (EE_Adc_BitResolution): desired ADc bit resolution

    @return 0 if no errors happend.
        Otherwise appropriate error value (negative value).
**/
__INLINE__ EE_INT8 EE_easylab_adc_init_ch(EE_AdcChId adc_ch_id)
{
    return EE_adc_init_ch(EE_ADC_1, adc_ch_id);
}

/**
    @brief Get channel value as uint

    @param adc_ch_id (EE_AdcChId): channel's ID to acquire.
    @param value  (EE_UINT16 *): return value pointer.

    @return 0 if no errors happened.
        Otherwise appropriate error value (negative value).
**/
__INLINE__ EE_INT8 EE_easylab_adc_get_ch_uint(EE_AdcChId adc_ch_id, EE_UINT16 * value ){
    return EE_adc_get_ch_uint(EE_ADC_1, adc_ch_id, value);
}

/**
    @brief Start ADC sampling

    @return 0 if no errors happened.
        Otherwise appropriate error value (negative value).

 **/
__INLINE__ EE_INT8 EE_easylab_adc_start ( EE_Adc_VoltageRef volt_ref, EE_Adc_BitResolution bit_res ) {
    return EE_adc_start(EE_ADC_1, volt_ref, bit_res);
}

/**
    @brief Stop ADC sampling

    @return 0 if no errors happened.
        Otherwise appropriate error value (negative value).

 **/
__INLINE__ EE_INT8 EE_easylab_adc_stop (void){
    return EE_adc_stop(EE_ADC_1);
}


#endif /*__USE_ADC__ */

#ifdef __USE_PWM__

/**
    Easylab Pins define for PWM
    @{
**/
#define EE_EASYLAB_PWM1     1
#define EE_EASYLAB_PWM2     2
#define EE_EASYLAB_PWM3     3
#define EE_EASYLAB_PWM4     4
/* if you want activate PWM over both pins 1 e 2 you should use these pin's ID */
#define EE_EASYLAB_PWM12    5
/* if you want activate PWM over both pins 3 e 4 you should use these pin's ID */
#define EE_EASYLAB_PWM34    6
/** @} **/

#include "mcu/microchip_dspic/inc/ee_pwm.h"

/**
    Easylab PWM API error codes
    @{
 **/
#define EE_EASYLAB_PWM_ERROR_INVALID_PIN_ID     -1
/** @} **/

/**
    @brief Initialize PWM pin

    @param pwm_pin (EE_UINT8): Pin's Id where start a PWM
    @param pwm_freq (EE_UINT32): pwm frequency

    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_init(EE_UINT8 pwm_pin, EE_UINT32 pwm_freq);

/**
    @brief Close a PWM pin.

    @param pwm_ch (EE_UINT8): pwm pin's Id.

    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_close(EE_UINT8 pwm_pin);

/**
    @brief Set PWM pin duty cicle and if, this value is not 0, start it.

    @param pwm_pin (EE_UINT8): pwm pin's Id.
    @param pwm_freq (EE_UINT32): pwm duty cycle [0, EE_PWM_DUTY_MAX]

    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_set_duty(EE_UINT8 pwm_pin, EE_UINT16 duty);

/**
    @brief Set PWM pin onverride status.

    @param pwm_pin (EE_UINT8): pwm pin's Id.
    
    @return an error value (negative integer) if someting happened
**/
EE_INT16 EE_easylab_pwm_set_direction(EE_UINT8 pwm_pin);

#endif /* __USE_PWM__ */

#endif /*__INCLUDE_EASYLAB_BOARD_H__ */

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

/*
    This is the demo preloaded on the EasyLab board.

    The demo shows the usage of some features of the board like PWM, ADC, Buzzer, USB/Serial, and leds.

    At the beginning the User configure the PWM and the ADC channels, and the desired voltage value that
    analog input should match, through serial communication.
    Then, using a simple cable, you can connect the analogic output (AOx for PWM channel x) to the AD
    converter (ANx for ADC channel x).
    The value measured by the AD converter is then transmitted to the PC (tested with putty.exe).
        Step 1: Select the PWM channel.
        Step 2: Select the ADC channel.
        Step 3: Set the desired voltage value.
        Step 4: Connect the cable and measure the output voltage.
    You can send ESC char to restart the demo.

    Author: Dario Di Stefano & Errico Guidieri
    Date:   2011
*/

#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"
#include "mcu/microchip_dspic/inc/ee_timer.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"
#include "stdlib.h"

/* Oscillator selectione register set on internal Fast RC oscillator. */
_FOSCSEL(FNOSC_FRC);
/* Oscillator configuration register set with clock switch enabled & clock monitoring disabled (FCKSM_CSECMD),
 * OSC2 pin as GPIO (OSCIOFNC_ON) and
 * primary oscillator disabled (not external oscillator/clock source in the board) */
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
/* Watchdog Timer disabled */
_FWDT(FWDTEN_OFF);

/*******************************
Include libraries headers
********************************/

/* flag utilized by wait_ms routine to be notified for timer timeout */
volatile unsigned int wait_finished = 0;
/* hold PWM channel to drive, chosen by User */
volatile unsigned int pwm_channel = 0xFFFF;
/* hold ADC channel to read, chosen by User */
volatile unsigned int adc_channel = 0xFFFF;
/* actual PWM duty cycle value */
volatile unsigned int pwm_duty_cycle = 0;
/* desired voltage in IN to ADC */
volatile int dvolt = 0;

/* Forward declaration for application functions */
static void easylab_buzzer_demo(void);
static void easylab_led_demo(void);
static void easylab_demo(void);
static void wait_ms(int ms);
static void print_u16(unsigned int data, char *out, unsigned char fillc);
static void start_timer();
static void tick_routine();

/*********************************************
      Tasks Implementation
 ********************************************/

/*
 * Initialization Task (indeed activatad by autostart, when StartOS is called).
 * Set system clock, configure and start peripheral drivers,
 * Execute interaction with user to get execution parameters,
 * start application tasks and set ciclyc alarms
 */
TASK(TaskInit)
{
    /* Set the system clock frequency to 80 Mhz (means microcontroller instructions frequency 40 MIPS) */
    EE_set_system_clock(80000000UL);
    /* start Timer1 needed by all the periodic tasks */
    start_timer();

    /* One shot executions to have a rapid board feedback */
    ActivateTask(TaskLeds);
    ActivateTask(TaskBuzzer);

    /* real demo. Start with a blocking user interaction to get execution parameters */
    easylab_demo();

    /* Program cyclic alarms which will fire after an initial offset, and after that periodically */
    SetRelAlarm(AlarmLeds, 500, 5000);
}

/*
 * Console management task. It read control character from UART and send actual ADC value.
 */
TASK(TaskConsole)
{
    /* control character holder */
    unsigned char data;
    /* ADC read holder */
    unsigned int val;
    /* litteral ADC value holder */
    char str[8];

    /* get control character and execute accordingly */
    if( EE_uart_read_byte(EE_UART_PORT_1, &data ) > 0 )
    {
        EE_uart_write_byte(EE_UART_PORT_1, data);
        /* escape to reset */
        if(data == '\e')
            asm("reset");
    }
    /* read ADC channel */
    EE_easylab_adc_get_ch_uint(adc_channel, &val);
    /* Convert level to voltage */
    val = (val * EE_ADC_VDD_mV) / EE_ADC_RES_MAX;
    /* translation to litteral format */
    print_u16(val, str, ' ');
    /* notification */
    EE_uart_write_string(EE_UART_PORT_1, "ADC input: ");
    EE_uart_write_string(EE_UART_PORT_1, str);
    EE_uart_write_string(EE_UART_PORT_1, " mV\r\n");
    TerminateTask();
}

/*
 * Voltage control task. try to drive PWM output (or rather supposed ADC input)
 * at desidered value.
 */
TASK(TaskVoltageCtrl)
{
    unsigned int new_pwm_duty_cycle = 0;
    unsigned int val;
    /* ADC read and voltage translation */
    EE_easylab_adc_get_ch_uint(adc_channel, &val);
    val = (val * EE_ADC_VDD_mV) / EE_ADC_RES_MAX;

    /* Control logic. Increment/decrement by 1 PWM duty case if read voltage is less/greater than desired value */
    if(val < dvolt)
        new_pwm_duty_cycle = (pwm_duty_cycle < EE_PWM_DUTY_MAX)?((pwm_duty_cycle > 0)?(pwm_duty_cycle + 1):(0)):(EE_PWM_DUTY_MAX);
    else if(val > dvolt)
        new_pwm_duty_cycle = (pwm_duty_cycle < EE_PWM_DUTY_MAX)?((pwm_duty_cycle > 0)?(pwm_duty_cycle - 1):(0)):(EE_PWM_DUTY_MAX);
    else
        new_pwm_duty_cycle = pwm_duty_cycle;

    /* Eventually set new PWM duty cycle */
    if(new_pwm_duty_cycle != pwm_duty_cycle)
    {
        pwm_duty_cycle = new_pwm_duty_cycle;
        EE_easylab_pwm_set_duty(pwm_channel, pwm_duty_cycle);
    }
    TerminateTask();
}

/* Execute Kitt effect with board's leds */
TASK(TaskLeds)
{
    easylab_led_demo();
    TerminateTask();
}

/* Execute stadium choir with buzzer :) */
TASK(TaskBuzzer)
{
    easylab_buzzer_demo();
    TerminateTask();
}

/* Used by wait_ms (sleep like) function. to get timer
 * expired notification
 */
TASK(TaskWaitFinished)
{
    wait_finished = 1;
    TerminateTask();
}

/*********************************
main entry point
*********************************/

int main ( void )
{
    /* Start Erika Enterprise OSEK Kernel OS. Automatically  */
    StartOS(OSDEFAULTAPPMODE);
    /* IRQ enabling. Needed workaround for StartOS implementation bug  */
    EE_hal_enableIRQ();

    while (1) {
        /*  endless loop */
    }
}

/*********************************
Application functions
*********************************/

/*
 * Callback of Timer1. Used to increment OSEK counter "myCounter";
 */
static void tick_routine()
{
    CounterTick(myCounter);
}

/*
 * Configure and start Timer1. You get a call back every 1000 us (1 ms).
 */
static void start_timer(){
    EE_timer_set_callback(EE_TIMER_1, tick_routine);
    /* reset the counter */
    EE_timer_soft_init(EE_TIMER_1, 1000U);
    EE_timer_start(EE_TIMER_1);
}

/*
 * print_u16(data, out)
 * Function used to convert an integer to array.
 * data: integer
 * out: output array (lenght supposed at least = to 6)
 */
static void print_u16(unsigned int data, char *out, unsigned char fillc)
{
    out[5] = '\0';
    out[4] = '0' + (data % 10);
    out[3] = '0' + ((data / 10) % 10);
    out[2] = '0' + ((data / 100) % 10);
    out[1] = '0' + ((data / 1000) % 10);
    out[0] = '0' + ((data / 10000) % 10);

    /* fill array with given fill character */
    if(fillc!='0')
    {
        int i;
        for(i=0; i<6; i++) {
            if(out[i]=='0')
                out[i]=fillc;
            else
                break;
        }
    }
}

/*
 * easylab_official_demo()
 * Function used to start the serial demo.
 */
static void easylab_demo(void) {
    /* UART initialization */
    EE_uart_init(EE_UART_PORT_1, 115200, EE_UART_BIT_STOP_1 | EE_UART_BIT8_NO, EE_UART_CTRL_SIMPLE);
    /* Application Blocking UI */
    EE_uart_write_string(EE_UART_PORT_1, "************* EasyLab board *************\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "***    A small board, a lot of fun!   ***\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "***  Copyright(c) 2011, Evidence Srl  ***\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "*****************************************\r\n\r\n");

    EE_uart_write_string(EE_UART_PORT_1, "= = = = = = = = = = = = = = =\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "PWM Demo (v1.0)\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "Description: This is the demo preloaded on the EasyLab board.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  The demo shows the usage of some features of the board like PWM,\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  ADC, Buzzer, USB/Serial, and leds.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  In the initial configuration you select the PWM and the ADC channels\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  to be used and set the desired voltage value.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  Then, using a simple cable, you can connect the analogic output\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  (AOx for PWM channel x) to the AD converter (ANx for ADC channel x).\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "  The value measured by the AD converter is then transmitted to the PC (tested with putty.exe).\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "Step 1: Select the PWM channel.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "Step 2: Select the ADC channel.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "Step 3: Set the desired voltage value.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "Step 4: Connect the cable and measure the output voltage.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "Then you can press ESC to restart the demo.\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "= = = = = = = = = = = = = = =\r\n\r\n");

    EE_uart_write_string(EE_UART_PORT_1, "Starting demo...\r\n");

    /*Used to read User answer characters */
    unsigned char data = 0;

    /* PWM channel selection */
    EE_uart_write_string(EE_UART_PORT_1, "Select the pwm channel (possible values are 1,2,3,4): ");

    while(1) {
        while( EE_uart_read_byte(EE_UART_PORT_1, &data)<=0 )
            ;
        EE_uart_write_byte(EE_UART_PORT_1, data);
        EE_uart_write_string(EE_UART_PORT_1, "\r\n");

        switch(data) {
            case '1':
                EE_easylab_pwm_init(EE_EASYLAB_PWM1, 20000);
                pwm_channel = EE_EASYLAB_PWM1;
                EE_uart_write_string(EE_UART_PORT_1, "PWM channel selected: 1\r\n");
                break;
            case '2':
                EE_easylab_pwm_init(EE_EASYLAB_PWM2, 20000);
                pwm_channel = EE_EASYLAB_PWM2;
                EE_uart_write_string(EE_UART_PORT_1, "PWM channel selected: 2\r\n");
                break;
            case '3':
                EE_easylab_pwm_init(EE_EASYLAB_PWM3, 20000);
                pwm_channel = EE_EASYLAB_PWM3;
                EE_uart_write_string(EE_UART_PORT_1, "PWM channel selected: 3\r\n");
                break;
            case '4':
                EE_easylab_pwm_init(EE_EASYLAB_PWM4, 20000);
                pwm_channel = EE_EASYLAB_PWM4;
                EE_uart_write_string(EE_UART_PORT_1, "PWM channel selected: 4\r\n");
                break;
            default:
                if(data == '\e') /* escape to reset */
                    asm("reset");
                EE_uart_write_string(EE_UART_PORT_1, ":-( Bad value!\r\n");
                EE_uart_write_string(EE_UART_PORT_1, "Select the pwm channel (possible values are 1,2,3,4): ");
        }
        if(pwm_channel < 0xFFFF)
            break;
    }

    /* ADC channel selection */
    EE_uart_write_string(EE_UART_PORT_1, "Select the adc channel (possible values are 1,2,3,4): ");

    while(1) {
        while( EE_uart_read_byte(EE_UART_PORT_1, &data)<=0 )
            ;
        EE_uart_write_byte(EE_UART_PORT_1, data);
        EE_uart_write_string(EE_UART_PORT_1, "\r\n");

        switch(data) {
            case '1':
                EE_easylab_adc_init_ch(EE_ADC_AN1);
                adc_channel = EE_ADC_AN1;
                EE_uart_write_string(EE_UART_PORT_1, "ADC channel selected: 1\r\n");
                break;
            case '2':
                EE_easylab_adc_init_ch(EE_ADC_AN2);
                adc_channel = EE_ADC_AN2;
                EE_uart_write_string(EE_UART_PORT_1, "ADC channel selected: 2\r\n");
                break;
            case '3':
                EE_easylab_adc_init_ch(EE_ADC_AN3);
                adc_channel = EE_ADC_AN3;
                EE_uart_write_string(EE_UART_PORT_1, "ADC channel selected: 3\r\n");
                break;
            case '4':
                EE_easylab_adc_init_ch(EE_ADC_AN4);
                adc_channel = EE_ADC_AN4;
                EE_uart_write_string(EE_UART_PORT_1, "ADC channel selected: 4\r\n");
                break;
            default:
                if(data == '\e') /* escape to reset */
                    asm("reset");
                EE_uart_write_string(EE_UART_PORT_1, ":-( Bad value!\r\n");
                EE_uart_write_string(EE_UART_PORT_1, "Select the adc channel (possible values are 1,2,3,4): ");
        }
        if(adc_channel < 0xFFFF) {
            EE_easylab_adc_start(EE_ADC_VDD_VSS, EE_ADC_12_BIT);
            break;
        }
    }

    /* Enter the voltage */
    unsigned char vet[32];
    EE_uart_write_string(EE_UART_PORT_1, "Enter the desired voltage, in mV (a number in the range 0 ... 3300):\r\n");
    EE_uart_write_string(EE_UART_PORT_1, "(in case of 3 digits or less, press enter to start)\r\n");
    data = 0;
    while(1) {
        dvolt = 0;
        while( EE_uart_read_byte(EE_UART_PORT_1, &(vet[data]) ) <= 0 )
            ;
        EE_uart_write_byte(EE_UART_PORT_1, vet[data]);
        if(vet[data] == '\e') /* escape to reset */
            asm ("reset");
        data++;

        if((data == 4) || (vet[data-1] == '\r') || (vet[data-1] == '\n'))
        {
            vet[data] = '\0';
            dvolt = atoi((const char*)vet);
            if( dvolt < 0 )
            {
                EE_uart_write_string(EE_UART_PORT_1, "\r\n#warning: input value < 0!\r\n");
                EE_uart_write_string(EE_UART_PORT_1, "Voltage = 0mV will be performed!\r\n");
                dvolt = 0;
                EE_easylab_pwm_set_duty(pwm_channel, 0);
                pwm_duty_cycle = 0;
                break;
            }
            else if( dvolt > EE_ADC_VDD_mV )
            {
                EE_uart_write_string(EE_UART_PORT_1, "\r\n#warning: input value > 3300!\r\n");
                EE_uart_write_string(EE_UART_PORT_1, "Voltage = 3300mV will be performed!\r\n");
                dvolt = EE_ADC_VDD_mV;
                EE_easylab_pwm_set_duty(pwm_channel, EE_PWM_DUTY_MAX);
                pwm_duty_cycle = EE_PWM_DUTY_MAX;
                break;
            }
            else if( dvolt == 0 )
            {
                EE_uart_write_string(EE_UART_PORT_1, "\r\nVoltage = 0mV will be performed!\r\n");
                EE_easylab_pwm_set_duty(pwm_channel, 0);
                pwm_duty_cycle = 0;
                break;
            }
            else
            {
                char str[8];
                EE_uart_write_string(EE_UART_PORT_1, "\r\nVoltage = ");
                print_u16(dvolt, str, ' ');
                EE_uart_write_string(EE_UART_PORT_1, str);
                EE_uart_write_string(EE_UART_PORT_1, "mV\r\n");
                pwm_duty_cycle = ((unsigned long) dvolt * EE_PWM_DUTY_MAX) / EE_ADC_VDD_mV;
                EE_easylab_pwm_set_duty(pwm_channel, pwm_duty_cycle);
                break;
            }
        }
    }
    /* Choose if control or not the output */
    /* ADC channel selection */
    EE_uart_write_string(EE_UART_PORT_1, "Do you want activate voltage output control routine (That will try to maintain the output at desired voltage)?\r\n"
        "(values: [y,n])\r\n");

    while(1) {
        while( EE_uart_read_byte(EE_UART_PORT_1, &data) <=0 )
            ;
        EE_uart_write_byte(EE_UART_PORT_1, data);
        EE_uart_write_string(EE_UART_PORT_1, "\r\n");

        switch(data) {
            case 'y':
                /* Schedule Voltage Control Alarm, that activate periodically  the Voltage
                 * Control task. */
                EE_uart_write_string(EE_UART_PORT_1, "Scheduling Voltage Control task\r\n");
                SetRelAlarm(AlarmVoltageCtrl, 10U, 10U);
                EE_uart_write_string(EE_UART_PORT_1, "Voltage Control task enabled\r\n");
                goto ctrl_loop_out;
            case 'n':
                EE_uart_write_string(EE_UART_PORT_1, "Voltage Control task NOT enabled\r\n");
                goto ctrl_loop_out;
            case '\e':
                asm("reset");
            default:
                EE_uart_write_string(EE_UART_PORT_1, ":-( Bad value! (values: [y,n])\r\n");
        }
    }
    ctrl_loop_out:


    /* Start the task that notify the read ADC value  */
    SetRelAlarm(AlarmConsole, 100U, 1000U);
}

/*
 * wait_ms(ms)
 * Function used to implement a wait.
 * ms: milliseconds to wait
 */
static void wait_ms(int ms) {

    /* Program one shot alarm which will fire after an initial offset */
    wait_finished = 0;
    SetRelAlarm(AlarmWaitFinished, ms, 0);
    while(!wait_finished)
    {
        /* wait until delay ends */
    }
}

/*
 * easylab_led_demo()
 * Function used to start the led demo.
 */
static void easylab_led_demo(void)
{
    typedef void (*op)(void);
    op const operations[] = {EE_led1_toggle, EE_led2_toggle, EE_led3_toggle, EE_led4_toggle,
        EE_led5_toggle, EE_led6_toggle, EE_led7_toggle, EE_led8_toggle
    };
    unsigned const op_size = sizeof(operations)/sizeof(op);
    /*     Initialize Leds */
    EE_leds_init();
    EE_leds_enable();
    wait_ms(500);
    EE_leds_disable();

    /* Kitt effect loop */
    unsigned total_leds = 0;
    operations[op_size -1]();
    while (total_leds < 16)
    {
        unsigned turn_on_index;
        unsigned turn_off_index;
        turn_on_index  = total_leds++ % op_size;
        turn_off_index = (turn_on_index)?(turn_on_index-1):(op_size -1);
        operations[turn_on_index]();
        operations[turn_off_index]();
        wait_ms(100);
    }
    operations[op_size -1]();
}

/*
 * easylab_buzzer_demo()
 * Function used to start the buzzer demo.
 * The buzzer demo perform a stadium choir, with blinking leds. :)
 */
static void easylab_buzzer_demo(void)
{
    EE_leds_init();
    /* 1 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(200);
    /* 2 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(200);
    /* 3 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(100);
    /* 4 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(100);
    /* 5 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(200);
    /* 6 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(100);
    /* 7 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(100);
    /* 8 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(100);
    /* 9 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(200);
    /* 10 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
    wait_ms(100);
    /* 11 */
    EE_leds_enable();
    EE_buzzer_start(1000);
    wait_ms(100);
    EE_leds_disable();
    EE_buzzer_stop();
}

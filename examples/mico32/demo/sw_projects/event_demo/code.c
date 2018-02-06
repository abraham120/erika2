/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011 Evidence Srl
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
    Author: Dario Di Stefano, 2011
*/ 

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
#include <MicoUtils.h>

/* This function is used to send info by serial interface. */
#include <string.h>
void print_string(const char *str) {
    EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int timer_fired = 0;
volatile int button_fired = 0;
volatile int dummit_counter = 0;
volatile int led_status = 0;
volatile int myErrorCounter = 0;
volatile StatusType ERROR_FLAG;

/* just a dummy delay */ 
/*
void mydelay(EE_UINT32 ms)
{
    MicoSleepMilliSecs(ms);
}
*/

__INLINE__ EE_UINT32 get_time_stamp(void)
{
	MicoTimer_t* freetimerc = (MicoTimer_t*)(FREETIMER_BASE_ADDRESS);
	return freetimerc->Snapshot;
}

__INLINE__ EE_UINT32 elapsed(EE_UINT32 from, EE_UINT32 to)
{
	/* Timers are decrementing */
	return from - to;
}

void mydelay(EE_UINT32 ms)
{
	EE_UINT32 start, curr;
	start = get_time_stamp();
	do {
		curr = get_time_stamp();
	} while (elapsed(start, curr) < (ms * (EE_UINT32)(CPU_FREQUENCY / 1000)));
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged...
 */
void led_blink(unsigned char theled)
{
  unsigned int intst;
  
  /* Disable IRQ */
  intst = EE_mico32_disableIRQ();
  
  led_status |= theled;
  EE_led_set_all(led_status);
 
  /* Enable IRQ */
  if (EE_mico32_are_IRQs_enabled(intst))
  	EE_mico32_enableIRQ();

  mydelay(200);

  /* Disable IRQ */
  intst = EE_mico32_disableIRQ();
  
  led_status &= ~theled;
  EE_led_set_all(led_status);
  
  /* Enable IRQ */
  if (EE_mico32_are_IRQs_enabled(intst))
  	EE_mico32_enableIRQ();
}

/* Task for events management */
TASK(Task1)
{
  EventMaskType mask;
  
  task1_fired++;
  
  while (1) {
    WaitEvent(TimerEvent|ButtonEvent);
    GetEvent(Task1, &mask);

    if (mask & TimerEvent) {
      led_blink(0x01);
      ClearEvent(TimerEvent);
    }

    if (mask & ButtonEvent) {
      led_blink(0x02);
      ClearEvent(ButtonEvent);
    }
  }
  
  TerminateTask();
}

/*  */
TASK(Task2)
{
  /* count the number of Task2 activations */
  task2_fired++;
  led_blink(0x04);
  
  TerminateTask();
}

/* Button event set inside the callback */
#define button_pressed() (EE_serio_read() & 0x01)

void Button_Callback(void)
{
    button_fired++;
    /* arm an alarm that will activated Task2 */ 
    SetRelAlarm(AlarmTask2, EE_STATIC_ALARM_TIME, EE_STATIC_CYCLE_TIME);
    //ActivateTask(Task2);
    /* set an event to wake up Task1 */
    SetEvent(Task1, ButtonEvent);
}

/* Timer event is configured in the oil file with 
   an alarm based on Counter1. */
void Timer1_Callback(void)
{
	//print_string("*");
    CounterTick(Counter1);
    
    /* Button is managed in polling mode here for 
       compatibility with all the platforms. */
    static int button_divisor = 0;
    if ( button_divisor > 0 ) {
        button_divisor++;
        if( button_divisor > 100 )
            button_divisor = 0;
    }
    else if( button_pressed() ) {
        Button_Callback();
        button_divisor++;
    }
    /*
    button_divisor++;
    if ( button_divisor > 300 ) 
    {
        button_divisor = 0;
        Button_Callback();
    }
    */
}

void ErrorHook(StatusType Error)
{
    myErrorCounter++;
    ERROR_FLAG = Error;
    led_blink(0xFF);
}

/* 
 * The StartupHook in this case is used to initialize the uart and timer controllers
 */
void StartupHook(void)
{    
    /* Init leds */
    EE_led_init();
    
    /* Uart configuration         */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  

    /* Program Timer 1 to raise interrupts */
    EE_timer_set_ISR_callback(Timer1_Callback);
    EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
    
    /* just a nice subliminal welcome message :-) */
    print_string("I love FLEX & ERIKA Enterprise!\r\n");
    EE_timer_on();
}


/* MAIN ENTRY POINT */
int main(void)
{
    /* let's start the multiprogramming environment...*/
    StartOS(OSDEFAULTAPPMODE);
 	
 	/* Enable IRQ         */
    EE_mico32_enableIRQ();
 	   
    /* now the background activities: in this case, we do nothing. */
    while(1)
        ;
    
    return 0;
}






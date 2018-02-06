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
 * Author: Paolo Gai
 * Author: Dario Di Stefano
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

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__
__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void) {
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void) {
  EE_hal_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void) {
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i) {
}
#endif

#define TASK1_PERIOD_ms 4000
#define DELAY_ms 300

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired  = 0;
volatile int button_fired = 0;
volatile int task1_fired  = 0;
volatile int task2_fired  = 0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile int led_status = 0;

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);


/* just a dummy delay */ 
static void mydelay(void) {
    MicoSleepMilliSecs(DELAY_ms);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
void led_blink(int theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_led_set_all(led_status);
  EnableAllInterrupts();

  mydelay();

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_led_set_all(led_status);
  EnableAllInterrupts();
}

/*
 * Handle button_pio interrupts activates Task2.
 */
#define button_pressed() (EE_serio_read() & 0x01)
static void handle_button(void)
{
  /* count the number of button presses */
  button_fired++;
  
  ActivateTask(Task2);  
}

void _T1Callback(void)
{
    static int timer_divisor = 0;
    static int button_divisor = 0;
    
	timer_divisor++;
	if (timer_divisor == TASK1_PERIOD_ms) {
		timer_divisor = 0;
		timer_fired++;
        ActivateTask(Task1);
	}

    /* Button is managed in polling mode for 
       compatibility with all the platforms. */
    if ( button_divisor > 0 ) {
        button_divisor++;
        if( button_divisor > 100 )
            button_divisor = 0;
    }
    else if( button_pressed() ) {
        handle_button();
        button_divisor++;
    }
}


/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;
  
  /* First half of the christmas tree */
  led_blink(0x01);
  led_blink(0x02);
  led_blink(0x04);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(0x08);
  led_blink(0x10);
  led_blink(0x20);
  
  TerminateTask();
}


/* Task2: Print the counters using the serial interface */
TASK(Task2)
{
  static int which_led = 0;
  /* count the number of Task2 activations */
  task2_fired++;

  /* let blink leds 6 or 7 */
  if (which_led) {
    led_blink(0x80);
    which_led = 0;
  }
  else {
    led_blink(0x40);
    which_led = 1;
  }

    // prints on the serial bus...
  
  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  char *msg_tmr =  "ISR_Timer: ";
  char *msg_tsk1 = "Task_1: ";
  char *msg_btn =  "Button_0: ";
  char *msg_tsk2 = "Task_2: ";
  unsigned char byte = 0;
  
  print_string(msg_tmr);
  byte = ((timer_fired%1000)/100)+'0';
  EE_uart_send_byte(byte);
  byte = ((timer_fired%100)/10)+'0';
  EE_uart_send_byte(byte);
  byte = (timer_fired%10)+'0';
  EE_uart_send_byte(byte);
  EE_uart_send_byte(' ');

  print_string( msg_tsk1);
  byte = ((task1_fired%1000)/100)+'0';
  EE_uart_send_byte(byte);
  byte = ((task1_fired%100)/10)+'0';
  EE_uart_send_byte(byte);
  byte = (task1_fired%10)+'0';
  EE_uart_send_byte(byte);
  EE_uart_send_byte(' ');

  print_string( msg_btn);
  byte = ((button_fired%1000)/100)+'0';
  EE_uart_send_byte(byte);
  byte = ((button_fired%100)/10)+'0';
  EE_uart_send_byte(byte);
  byte = (button_fired%10)+'0';
  EE_uart_send_byte(byte);
  EE_uart_send_byte(' ');

  print_string( msg_tsk2);
  byte = ((task2_fired%1000)/100)+'0';
  EE_uart_send_byte(byte);
  byte = ((task2_fired%100)/10)+'0';
  EE_uart_send_byte(byte);
  byte = (task2_fired%10)+'0';
  EE_uart_send_byte(byte);

  EE_uart_send_byte('\r');
  EE_uart_send_byte('\n');

  TerminateTask();
}
  
/* main entry point */
int main()
{ 
    /* Disable IRQ         */
    EE_mico32_disableIRQ();
    
    /* let's start the multiprogramming environment...*/
    StartOS(OSDEFAULTAPPMODE);

    /* Init leds */
    EE_led_init();
    
    /* Uart configuration         */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  

    /* Program Timer 1 to raise interrupts */
    EE_timer_set_ISR_callback(_T1Callback);
    EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);

    /* Enable IRQ         */
    EE_mico32_enableIRQ();

    /* just a nice subliminal welcome message :-) */
    print_string("I love FLEX & ERIKA Enterprise!\r\n");
    EE_timer_on();
    
    /* now the background activities: in this case, we do nothing. */
    while(1)
        ;
    
    return 0;

}

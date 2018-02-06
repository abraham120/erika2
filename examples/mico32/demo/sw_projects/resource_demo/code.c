/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011  Evidence Srl
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

#define button_pressed() (EE_serio_read() & 0x01)

/* Let's declare the tasks identifiers */
//DeclareTask(Task1);
//DeclareTask(Task2);

volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;
volatile unsigned char led_status = 0;
volatile int mycounter=0;

/* just a dummy delay */ 
void mydelay(int end_ms) {
    MicoSleepMilliSecs(end_ms);
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
void led_blink(unsigned char theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_led_set_all(led_status);
  EnableAllInterrupts();

  mydelay(500);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_led_set_all(led_status);
  EnableAllInterrupts();
}

#define TASK1_PERIOD_ms 1000
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


TASK(Task1)
{
  task1_fired++;
 
  /* Lock the resource */
  GetResource(Resource);

  /* do a long loop, printing the numbers from 0 to 9 */
  EE_led_on(0);
  int i;
  for (i=0; i<10; i++) {
	mydelay(300);
	EE_uart_send_byte(i+'0');
	EE_uart_send_byte(' ');
  }
  EE_led_off(0);
  print_string("\r\n");
  
  /* Release the lock */
  ReleaseResource(Resource);
  
  TerminateTask();
}


/* High Priority Task.
 * This task simply changes the counter depending on the current
 * applicationmode, and prints it using a print function.
 */
TASK(Task2)
{
  AppModeType currentmode;
  char * msg = "My Counter: ";
  unsigned char byte = 0;
  
  task2_fired++;
  
  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  /* Lock the resource */
  GetResource(Resource);

  EE_led_on(1);
  mydelay(500);
  
  /* decrement or increment the counter depending on the application mode */
  if ( currentmode==ModeIncrement )
    mycounter++;
  else
    mycounter--;
  
  print_string(msg);
  byte = ((mycounter%1000)/100)+'0';
  EE_uart_send_byte(byte);
  byte = ((mycounter%100)/10)+'0';
  EE_uart_send_byte(byte);
  byte = (mycounter%10)+'0';
  EE_uart_send_byte(byte);
  EE_uart_send_byte('\r');
  EE_uart_send_byte('\n');

  EE_led_off(1);
  
  /* Release the lock */
  ReleaseResource(Resource);

  TerminateTask();
}

int main(void)
{
    AppModeType startupmode;
    char *inc = "Increment mode when Task2 runs!!!\r\n";
    char *dec = "Decrement mode when Task2 runs!!!\r\n";
    char *intro = "I Love OSEK and Erika Enterprise!!!\r\n";

    /* Disable IRQ         */
    EE_mico32_disableIRQ();
    
    /* Init leds */
    EE_led_init();
    
    /* Uart configuration         */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  
    print_string(intro);
    
    /* check if the first button is pressed or not */
    if ( button_pressed() ) {
        /* the button is not pressed */
        startupmode = ModeIncrement;
        print_string(inc);
    }
    else {
        /* the button is pressed */
        startupmode = ModeDecrement;
        mycounter = 1000;
        print_string(dec);
    }
    StartOS(startupmode);

    /* Program Timer 1 to raise interrupts */
    EE_timer_set_ISR_callback(_T1Callback);
    EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);

    /* Enable IRQ         */
    EE_mico32_enableIRQ();
    
    EE_timer_on();

    /* now the background activities: in this case, we do nothing. */
    while(1)
        ;
    
    return 0;
}





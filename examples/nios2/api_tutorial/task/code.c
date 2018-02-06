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

/*
 * Copyright (C) 2002-2006 Evidence Srl
 *
 * This program is not free software.
 *
 * Please see the "Evidence RT-Druid and ERIKA Enterprise for Nios II Demo 
 * License" for legal details.
 *
 * You should have received a copy of the license along with this
 * program; if not, write to the Evidence Srl, Via E. Fermi, 6, 56010
 * Vicopisano (PI), Italy, or send an e-mail to info@evidence.eu.com.
 *
 */
 
/* Altera includes */
#include <system.h>
#include <stdio.h>
#include <altera_avalon_pio_regs.h>
#include "sys/alt_alarm.h"

/* EE includes */
#include "ee.h"

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__
__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void)
{
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i)
{
}
#endif

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task2_fired=0;

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
#define ONEMILLION 1000000
static void mydelay(void)
{
  int i;
  for (i=0; i<ONEMILLION/2; i++);
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
  alt_irq_context c;
  
  c = alt_irq_disable_all();
  led_status |= theled;
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_status);
  alt_irq_enable_all(c);

  mydelay();

  c = alt_irq_disable_all();
  led_status &= ~theled;
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_status);
  alt_irq_enable_all(c);
}



/* This alarm callback is attached to the system timer, and is used to
 * activate Task1
 * The period in expressed in system timer ticks, each one typically 10ms 
 */
#define TASK1_TIMER_INTERVAL  400
alt_u32 Task1_alarm_callback (void* arg)
{
  /* Count the number of alarm expirations */
  timer_fired++;
  
  ActivateTask(Task1);
  
  return TASK1_TIMER_INTERVAL;
}


/* Task1: just call the ChristmasTree */
TASK(Task1)
{
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


/* Task2: Print the counters on the JTAG UART */
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

  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  
  printf("Task2 - Timer: %3d Button: %3d Task2: %3d\n", timer_fired, button_fired, task2_fired);

  TerminateTask();
}



/*
 * Handle button_pio interrupts activates Task2.
 */
static void handle_button_interrupts(void* context, alt_u32 id)
{
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);

  /* count the number of button presses */
  button_fired++;
  
  ActivateTask(Task2);  
}

/* Initialize the button_pio. */
static void init_button_pio()
{
  /* Enable the first two 2 button interrupts. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_PIO_BASE, 0x3);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0x0);
  /* Register the interrupt handler. */
  alt_irq_register( BUTTON_PIO_IRQ, NULL, handle_button_interrupts ); 
}

  
int main()
{ 
  alt_alarm myalarm;
  
  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */
  EE_trace32_stack_init();
  
  printf("Welcome to the ERIKA Enterprise Christmas Tree!\n\n");
  
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
 
  /* program the Button PIO */
  init_button_pio();

  /* start the periodic timers */
  alt_alarm_start (&myalarm, TASK1_TIMER_INTERVAL, 
                   Task1_alarm_callback, NULL);
  
  /* now the background activities: in this case, we do nothing. */
  for (;;);
  
  return 0;
}

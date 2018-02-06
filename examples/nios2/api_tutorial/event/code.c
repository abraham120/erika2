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
 * Author: Paolo Gai
 */

/* Altera Includes */ 
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "altera_avalon_timer_regs.h"

/* EE includes */
#include "ee.h"



DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);


/* just a dummy delay */ 
#define ONEMILLION 1000000
static void mydelay(void)
{
  int i;
  for (i=0; i<ONEMILLION/2; i++);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged. See also the osek_task example for a full explanation of the
 * function.
 */
volatile int led_status = 0;
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



TASK(Task1)
{
  EventMaskType mask;

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

TASK(Task2)
{
  led_blink(0x04);
  TerminateTask();
}


int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
  led_blink(0xFF);
}



/*
 * 
 * Timer
 * 
 */

/* We use the HIGH_RES_TIMER available in almost all the Altera example designs
 * to implement the periodic counter needed for ERIKA Enterprise Alarms.
 * 
 * Please remember to specify "null" as timestamp timer in the Altera HAL 
 * System Library: in this way, the init_timer() function can safely call the
 * alt_irq_register function.
 */
 
/* call the ERIKA Enterprise tick function for the Counter1 counter! */
static void handle_timer_interrupt(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (HIGH_RES_TIMER_BASE, 0);
 
  CounterTick(Counter1);
}

/* Initialize the timer. */
static void init_timer()
{
  /* set to free running mode */
  IOWR_ALTERA_AVALON_TIMER_CONTROL (HIGH_RES_TIMER_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);

  /* register the interrupt handler, and enable the interrupt */
    
  alt_irq_register (HIGH_RES_TIMER_IRQ, NULL, handle_timer_interrupt);    
}

/*
 * 
 * Button PIO
 * 
 */


/*
 * Handle button_pio interrupts activates Task2.
 */
static void handle_button_interrupts(void* context, alt_u32 id)
{
  int buttonstatus;
  
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);

  buttonstatus = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

  /* check if the first button is pressed or not */
  if (buttonstatus & 0x1) {
    /* the button is not pressed, do nothing */
  }
  else {
    /* the button is pressed */
    /* arm an alarm that will activated Task2 */ 
    SetRelAlarm(AlarmTask2, 1000, 0);

    /* set an event to wake up Task1 */
    SetEvent(Task1, ButtonEvent);
  }
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

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  /* program the Button PIO */
  init_button_pio();
  
  /* program the conter timer */
  init_timer();
}



int main(void)
{
  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */
  EE_trace32_stack_init();
 
  StartOS(OSDEFAULTAPPMODE);

  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}

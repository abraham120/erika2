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

/* EE includes */
#include "ee.h"

/* a constant used in the delay loops */
#define ONEMILLION 1000000

/* this counter will be printed on the console in ascending 
 * or decreasing order when the button is pressed
 */
volatile int mycounter=0;

/* This alarm callback is attached to the system timer, and is used to
 * activate LowTask
 * The period in expressed in system timer ticks, each one typically 10ms 
 */
#define LOWTASK_TIMER_INTERVAL  400
alt_u32 LowTask_alarm_callback (void* arg)
{
  ActivateTask(LowTask);
  return LOWTASK_TIMER_INTERVAL;
}

/*
 * This is the Low priority task.
 * When the task runs, it locks a resource for a -long- time, preventing 
 * HighTask to preempt.
 */

TASK(LowTask)
{
  int i,j;

  /* Lock the resource */
  GetResource(Resource);

  /* do a long loop, printing the numbers from 0 to 9 */
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, 0x01);
  for (j=0; j<10; j++) {
    for (i=0; i<ONEMILLION; i++);
    printf("%d", j);
  }
  printf("\n");
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, 0x00);
  
  /* Release the lock */
  ReleaseResource(Resource);
  
  TerminateTask();
}


/* High Priority Task.
 * This task simply decrements the counter depending on the current 
 * applicationmode, and prints it using printf.
 */
TASK(HighTask)
{
  int i;
  AppModeType currentmode;
  
  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  GetResource(Resource);

  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, 0x02);
  for (i=0; i<ONEMILLION; i++);
  
  /* decrement or increment the counter depending on the application mode */
  if ( currentmode==ModeIncrement )
    mycounter++;
  else
    mycounter--;
  printf("mycounter=%d\n", mycounter);
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, 0x00);

  ReleaseResource(Resource);

  TerminateTask();
}

/*
 * Handle button_pio interrupts activates HighTask.
 */
static void handle_button_interrupts(void* context, alt_u32 id)
{
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);

  ActivateTask(HighTask);  
}


/* Initialize the button_pio. */
static void init_button_pio()
{
  /* Enable the first button interrupt. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_PIO_BASE, 0x1);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0x0);
  /* Register the interrupt handler. */
  alt_irq_register( BUTTON_PIO_IRQ, NULL, handle_button_interrupts ); 
}


int main(void)
{
  AppModeType startupmode;
  alt_alarm myalarm;
  
  int buttonstatus;
  
  printf("Welcome to the ERIKA Enterprise Resource demo!\n\n");
  
  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */
  //EE_trace32_stack_init();
  
  /* read the button status */
  buttonstatus = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

  /* check if the first button is pressed or not */
  if (buttonstatus & 0x1) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
    printf("ModeIncrement selected.\n");
    printf("To select ModeDecrement, start the demo with the 1st button pressed!\n");
  }
  else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
    printf("ModeDecrement selected.\n");
    printf("To select ModeIncrement, start the demo with the 1st button not pressed!\n");
  }

  /* program the Button PIO interrupt*/
  init_button_pio();
  
  /* start the periodic timers */
  alt_alarm_start (&myalarm, LOWTASK_TIMER_INTERVAL, 
                   LowTask_alarm_callback, NULL);

  StartOS(startupmode);
    
  for (;;);
}

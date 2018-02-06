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

#include <stdio.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include "ee.h"
#include "myfifo.h"
#include "sys/alt_alarm.h"


/*
 * A few constants...
 */
 
/* FIFO size */
#define MYFIFO_SIZE 8

/* frequency of the read and write task
 * (in number of system ticks, typically 10ms each)
 */
#define TIMER_INTERVAL_READ  200
#define TIMER_INTERVAL_WRITE 100



/*
 * Let's create an instance of the FIFO!
 */

volatile fifo_t EE_SHARED_DATA(myfifo);
volatile alt_u32 EE_SHARED_DATA(myfifo_data)[MYFIFO_SIZE];

void myfifo_init(void)
{
  fifo_init(&myfifo, MYFIFO_SIZE, myfifo_data);
}


/*
 * These two callbacks are attached to the system timer, and are used to
 * activate the ReadTask and WriteTask tasks
 */


alt_u32 alarm_callback_read (void* arg)
{
  ActivateTask(ReadTask);
  return TIMER_INTERVAL_READ;
}

alt_u32 alarm_callback_write (void* arg)
{
  ActivateTask(WriteTask);
  return TIMER_INTERVAL_WRITE;
}


/*
 * Handle button_pio interrupts activates the ButtonReadTask.
 */
static void handle_button_interrupts_cpu0(void* context, alt_u32 id)
{
  /* used to acknowledge (using leds) that an interrupt arrived */
  static int led_counter=0;
  
  /* Activate the ButtonReadTask */
  ActivateTask(ButtonReadTask);  

  /* display the counter value on the leds */  
  led_counter = (led_counter+1)%256;
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_counter);
  
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);
}

/* Initialize the button_pio. */
static void init_button_pio()
{
  /* Enable the first two 2 button interrupts. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_PIO_BASE, 0x3);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0x0);
  /* Register the interrupt handler. */
  alt_irq_register( BUTTON_PIO_IRQ, NULL, handle_button_interrupts_cpu0 ); 
}

  
int main()
{ 
  alt_alarm alarm_read;
  alt_alarm alarm_write;
  
  printf("Hello from CPU 0!\n");
  
  /* let's start the multiprogramming environment on CPU 0 */
  StartOS(OSDEFAULTAPPMODE);

  /* FIFO initialization */
  myfifo_init();
  
  /* program the Button PIO */
  init_button_pio();

  /* start the periodic timers */
  alt_alarm_start (&alarm_read, TIMER_INTERVAL_READ, 
                   alarm_callback_read, NULL);
  alt_alarm_start (&alarm_write, TIMER_INTERVAL_WRITE, 
                   alarm_callback_write, NULL);
  
  /* now the background activities: in this case, we do nothing. */
  for (;;);
  
  return 0;
}

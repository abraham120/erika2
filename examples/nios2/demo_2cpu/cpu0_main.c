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


/* 
 * This data is local to cpu0. 
 * The scope of the symbol is cpu0 ONLY, which means:
 * - other cpus cannot access this data
 * - other cpus can have data having the same name
 * 
 * This variable is just an example, it is not used 
 * in the rest of the application
 */
int a_local_counter;


/*
 * Handle button_pio interrupts activates the three tasks in the system.
 * Note that the tasks are activated regardless of their placement
 * on a particular CPU.
 */
static void handle_button_interrupts_cpu0(void* context, alt_u32 id)
{
  /* used to acknowledge (using leds) that an interrupt arrived */
  static int led_counter=0;
  
  /* Activate the three tasks */
  ActivateTask(task0);  
  ActivateTask(task1);  
  ActivateTask(task2);  

  /* display the counter value on the leds */  
  led_counter = (led_counter+1)%256;
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_counter);
  
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);
}

/* Initialize the button_pio. */
static void init_button_pio_0()
{
  /* Enable all 2 button interrupts. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_PIO_BASE, 0x3);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0x0);
  /* Register the interrupt handler. */
  alt_irq_register( BUTTON_PIO_IRQ, NULL, handle_button_interrupts_cpu0 ); 
}

int main()
{ 
  /* 
   * CPU 0
   * Initialization part
   */
  
  printf("Hello from CPU 0!\n");
  printf("Press a button to activate the tasks\n");
  
  init_button_pio_0();
  
  /* let's start the multiprogramming environment on CPU 0 */
  StartOS(OSDEFAULTAPPMODE);
  
  /* this is the background task, more or less equal to all the other Altera
   * HAL applications. In this case, we do nothing.
   */
  for (;;);
  
  return 0;
}

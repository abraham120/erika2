/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * Author: 2012,  Giuseppe Serano
 */

#include "ee.h"
#include "ee_irq.h"

/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for ( i= 0; i < ONEMILLION; i++)
    for (j = 0; j < ONEMILLION; j++)
    {
      ;	/* NOP */
    }
}

/* this counter will be printed on the console in ascending 
 * or decreasing order when the button is pressed
 */
volatile int mycounter = 0;

/*
 * Program the SysTick to raise interrupts
 */
void systick_program(void)
{

  EE_systick_set_period(	/* Set the SysTick period to (1ms @ 16MHz)    */
    MILLISECONDS_TO_TICKS(1, 16000000)
  );
  EE_systick_enable_int();	/* Enable SysTick Interrupts		      */
  EE_systick_start();		/* Start SysTick			      */

}

/* This alarm callback is attached to the system timer, and is used to
 * activate LowTask
 * The period in expressed in system timer ticks, each one typically 10ms 
 */
volatile int timer_divisor = 0;
ISR2(systick_handler)
{
  timer_divisor++;
  if (timer_divisor==2000) {
    timer_divisor = 0;
    ActivateTask(LowTask);
  }
}


/*
 * This is the Low priority task.
 * When the task runs, it locks a resource for a -long- time, preventing 
 * HighTask to preempt.
 */

TASK(LowTask)
{
  char j;
  char str[17] = "                ";
  
  /* Lock the resource */
  GetResource(Resource);

  /* do a long loop, printing the numbers from 0 to 9 */
  EE_oled_display_leds(OLED_DISPLAY_LED_0);
  for (j = 0; j < 10; j++) {
    mydelay();
    str[j] = j + '0';
    EE_oled_display_line1(str);
  }
  EE_oled_display_leds(OLED_DISPLAY_LEDS_OFF);

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
  AppModeType currentmode;
  char str[17] = "mycounter: 00000";
  
  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  GetResource(Resource);

  EE_oled_display_leds(OLED_DISPLAY_LED_1);
  
  mydelay();
  
  /* decrement or increment the counter depending on the application mode */
  if ( currentmode == ModeIncrement )
    mycounter++;
  else
    mycounter--;
  
  str[11] = ((mycounter/10000)+'0');
  str[12] = (((mycounter%10000)/1000)+'0');;
  str[13] = (((mycounter%1000)/100)+'0');
  str[14] = (((mycounter%100)/10)+'0');
  str[15] = (mycounter%10)+'0';
  EE_oled_display_line2(str);
  EE_oled_display_leds(OLED_DISPLAY_LEDS_OFF);

  ReleaseResource(Resource);

  TerminateTask();
}

/*
 * Buttons Interrupts Handler.
 */
ISR2(buttons_handler)
{
  ActivateTask(HighTask); 

  /* Clear Interrupt Sources */
  EE_user_buttons_clear_int();
}

int main(void)
{
  AppModeType startupmode;

  EE_UREG buttonstatus;

  /*
   * System Initialization:
   * - Power-On Reset System Clock: PIOSC (16MHz) without PLL.
   * - Context Switch: PendSV Exception (Minimum Priority)
   * - Nested Vectored Interrupt Controller.
   */
  EE_system_init();

  /* initialize buttons so we can read button 1 value */
  EE_user_buttons_init();

  mydelay();

  /* OLED Display Initialization */
  EE_oled_display_init();

  /* read the button status */
  buttonstatus = EE_user_buttons_get_status();
  EE_oled_display_line1("Startup Mode:");

  /* check if the SELECT/WAKE button is pressed or not */
  if (buttonstatus & SELECT_BUTTON) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
    EE_oled_display_line2("Increment");
  }
  else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
    EE_oled_display_line2("Decrement");
  }

  mydelay();

  /* let's start the multiprogramming environment...*/
  StartOS(startupmode);
  
  /* Enable User Buttons Interrupts */
  EE_user_buttons_enable_int();
    
  /* Program SysTick Timer to raise interrupts */
  systick_program();

  /* Background activities, none in this demo! */
  for (;;)
  {
    ;	/* NOP */
  }

  /* Warning: statement is unreachable */
  /* return 0; */

}

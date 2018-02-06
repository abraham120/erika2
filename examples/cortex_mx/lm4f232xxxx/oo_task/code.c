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

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__
__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void)
{
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void)
{
  EE_hal_enableIRQ();
}

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
volatile int timer_fired = 0;
volatile int button_fired = 0;
volatile int task1_fired = 0;
volatile int task2_fired = 0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile EE_UINT8 led_status = 0;


/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);


/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for (i = 0; i < ONEMILLION; i++)
    for (j = 0; j < ONEMILLION; j++)
    {
      ;	/* NOP */
    }
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
void led_blink(EE_UINT8 theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_oled_display_leds(led_status);
  EnableAllInterrupts();

  mydelay();

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_oled_display_leds(led_status);
  EnableAllInterrupts();
}


/*
 * Program the SysTick to raise interrupts
 */
void systick_program(void)
{

  EE_systick_set_period(	/* Set the SysTick period to (1ms @ 16MHz)   */
    MILLISECONDS_TO_TICKS(1, 16000000)
  );
  EE_systick_enable_int();	/* Enable SysTick Interrupts		      */
  EE_systick_start();		/* Start SysTick			      */

}


/* This is an ISR Type 2 which is attached to the SysTick peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(systick_handler)
{
  static int timer_divisor = 0;

  timer_divisor++;
  if (timer_divisor == 4000) {
    timer_divisor = 0;
    timer_fired++;
    ActivateTask(Task1);
  }
}


/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;
  
  /* First half of the christmas tree */
  led_blink(OLED_DISPLAY_LED_0);
  led_blink(OLED_DISPLAY_LED_1);
  led_blink(OLED_DISPLAY_LED_2);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(OLED_DISPLAY_LED_3);
  led_blink(OLED_DISPLAY_LED_4);
  led_blink(OLED_DISPLAY_LED_5);
  
  TerminateTask();
}


/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  static int	which_led = 0;
  static char	line1[OLED_DISPLAY_LINE_SIZE + 1] = "Tmr:000 Tsk1:000";
  static char	line2[OLED_DISPLAY_LINE_SIZE + 1] = "Btn:000 Tsk2:000";

  /* count the number of Task2 activations */
  task2_fired++;

  /* let blink leds 6 or 7 */
  if (which_led) {
    led_blink(OLED_DISPLAY_LED_7);
    which_led = 0;
  }
  else {
    led_blink(OLED_DISPLAY_LED_6);
    which_led = 1;
  }

  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  line1[4] = (((timer_fired%1000)/100)+'0');
  line1[5] = (((timer_fired%100)/10)+'0');
  line1[6] = ((timer_fired%10)+'0');

  line1[13] = (((task1_fired%1000)/100)+'0');
  line1[14] = (((task1_fired%100)/10)+'0');
  line1[15] = ((task1_fired%10)+'0');
  EE_oled_display_line1(line1);

  line2[4] = (((button_fired%1000)/100)+'0');
  line2[5] = (((button_fired%100)/10)+'0');
  line2[6] = ((button_fired%10)+'0');

  line2[13] = (((task2_fired%1000)/100)+'0');
  line2[14] = (((task2_fired%100)/10)+'0');
  line2[15] = ((task2_fired%10)+'0');

  EE_oled_display_line2(line2);

  TerminateTask();
}


/*
 * Programs User Buttons to rais interrupts.
 */
void buttons_program(void)
{

  EE_user_buttons_init();	/* Initializes User Buttons.		      */
  EE_user_buttons_enable_int();	/* Enable user Buttons Interrupts.	      */

}


/*
 * User Buttons Interrupts Handler which activates Task2.
 */
ISR2(buttons_handler)
{

  /* Clear Interrupt Sources */
  EE_user_buttons_clear_int();

  /* count the number of button presses */
  button_fired++;
  
  ActivateTask(Task2); 

}


int main()
{ 

  /*
   * System Initialization:
   * - Power-On Reset System Clock: PIOSC (16MHz) without PLL.
   * - Context Switch: PendSV Exception (Minimum Priority)
   * - Nested Vectored Interrupt Controller.
   */
  EE_system_init();

  /* OLED Display Initialization */
  EE_oled_display_init();

  /* Programs SysTick to raise interrupts */
  systick_program();

  /* Programs User Buttons to raise interrupts */
  buttons_program();

  mydelay();

  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);

  /* now the background activities: in this case, we do nothing. */
  for (;;)
  {
    ;	/* NOP */
  }
  
  /* Warning: statement is unreachable */
  /* return 0; */

}

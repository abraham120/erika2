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
 * Author: 2002-2012 Paolo Gai
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
__INLINE__ void __ALWAYS_INLINE__ StartOS(EE_UINT32 i)
{
}
#endif

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile EE_UINT32 timer_fired=0;
volatile EE_UINT32 button_fired=0;
volatile EE_UINT32 task1_fired=0;
volatile EE_UINT32 task2_fired=0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile unsigned char led_status = 0;

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
#define LED_ON_TIME_DELTA 200000U
static void led_blink(enum EE_tc2x5_led_id theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_tc2x5_set_leds_mask(led_status);
  EnableAllInterrupts();

  EE_tc2Yx_delay(LED_ON_TIME_DELTA);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_tc2x5_set_leds_mask(led_status);
  EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;

  /* First half of the christmas tree */
  led_blink(EE_TRIBOARD_2X5_LED_1);
  led_blink(EE_TRIBOARD_2X5_LED_2);
  led_blink(EE_TRIBOARD_2X5_LED_3);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  /* we use led 4 5 and 6 because the board has two rows of 4 leds each */
  led_blink(EE_TRIBOARD_2X5_LED_4);
  led_blink(EE_TRIBOARD_2X5_LED_5);
  led_blink(EE_TRIBOARD_2X5_LED_6);
  
  TerminateTask();
}


/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  static int which_led = 0;
  /* count the number of Task2 activations */
  ++task2_fired;

  /* let blink leds 4 or 8 */
  if (which_led) {
    led_blink(EE_TRIBOARD_2X5_LED_7);
    which_led = 0;
  }
  else 
  {
    led_blink(EE_TRIBOARD_2X5_LED_8);
    which_led = 1;
  }

  TerminateTask();
}

ISR2(button_handler)
{
    EE_tc2x5_button_irq_clear_request();
    ++button_fired;
    ActivateTask(Task2);
}

/*
 * MAIN TASK
 */
#ifdef __TASKING__
/* The loop is OK */
EE_DO_PRAGMA(warning 557)
#endif /* __TASKING__ */

int main( void )
{
    /* Init button */
    EE_tc2x5_button_irq_init(EE_ISR2_ID_button_handler);
    /* Init leds */
    EE_tc2x5_leds_init();

    /* let's start the multiprogramming environment...*/
    StartOS(OSDEFAULTAPPMODE);

    /* now the background activities... Only for FP Kernel */
    for (;;)
        ;
    return 0;
}

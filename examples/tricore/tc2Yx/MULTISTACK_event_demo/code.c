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
 * Copyright (C) 2002-2012 Paolo Gai
 */

#include "ee.h"
#include "ee_irq.h"

volatile unsigned int ERROR_FLAG = 0;
volatile int led_status = 0;
volatile int myErrorCounter;

DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

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

ISR2(button_handler)
{
    EE_tc2x5_button_irq_clear_request();
    /* arm an alarm that will activate Task2 */
    SetRelAlarm(AlarmTask2, 750, 0);

    /* set an event to wake up Task1 */
    SetEvent(Task1, ButtonEvent);
}
#ifdef __TASKING__
EE_DO_PRAGMA(warning 544)
#endif /* __TASKING__ */

TASK(Task1)
{
  EventMaskType mask;
  
  while (1) {
    WaitEvent(TimerEvent | ButtonEvent);
    GetEvent(Task1, &mask);

    if (mask & TimerEvent) {
      led_blink(EE_TRIBOARD_2X5_LED_1);
      ClearEvent(TimerEvent);
    }

    if (mask & ButtonEvent) {
      led_blink(EE_TRIBOARD_2X5_LED_2);
      ClearEvent(ButtonEvent);
    }
  }
  TerminateTask();
}
#ifdef __TASKING__
EE_DO_PRAGMA(warning restore)
#endif /* __TASKING__ */

TASK(Task2)
{
  led_blink(EE_TRIBOARD_2X5_LED_3);
  TerminateTask();
}

void ErrorHook(StatusType Error)
{
  ++myErrorCounter;
  ERROR_FLAG = Error;
  led_blink(EE_TRIBOARD_2X5_ALL_LEDS);
}

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  /* Init IRQ button */
  EE_tc2x5_button_irq_init(EE_ISR2_ID_button_handler);
  /* Init leds */
  EE_tc2x5_leds_init();
}


/* MAIN */
int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

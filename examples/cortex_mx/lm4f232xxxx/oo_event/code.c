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

DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for ( i = 0; i < ONEMILLION; i++)
    for (j = 0; j < ONEMILLION; j++)
    {
      ;	/* NOP */
    }
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged. See also the osek_task example for a full explanation of the
 * function.
 */
volatile EE_UINT8 led_status = 0;
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
 * TASK 1
 */
TASK(Task1)
{
  EventMaskType mask;

  while (1) {

    WaitEvent(TimerEvent|ButtonEvent);
    GetEvent(Task1, &mask);

    if (mask & TimerEvent) {
      led_blink(OLED_DISPLAY_LED_0);
      ClearEvent(TimerEvent);
    }

    if (mask & ButtonEvent) {
      led_blink(OLED_DISPLAY_LED_1);
      ClearEvent(ButtonEvent);
    }

  }

  /* Warning:  #111-D: statement is unreachable */
  /* TerminateTask(); */
}

/*
 * TASK 2
 */
TASK(Task2)
{
  led_blink(OLED_DISPLAY_LED_2);
  TerminateTask();
}

/*
 * HerrorHook
 */
int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
  led_blink(OLED_DISPLAY_LEDS_ON);
}

/*
 * 
 * SysTick
 * 
 */

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

/*
 * SysTick Interrupts Handler.
 */
ISR2(systick_handler)
{

  /* call the ERIKA Enterprise tick function for the Counter1 counter! */
  CounterTick(Counter1);

}

/*
 *
 * Buttons
 *
 */
void buttons_program(void)
{

  EE_user_buttons_init();	/* Initializes User Buttons.		      */
  EE_user_buttons_enable_int();	/* Enable user Buttons Interrupts.	      */

}

/*
 * Buttons Interrupts Handler.
 */
ISR2(buttons_handler)
{

  int buttonstatus;
  
  buttonstatus = EE_user_buttons_get_status();

  /* check if the SELECT/WAKE button is pressed or not */
  if (buttonstatus & SELECT_BUTTON) {
    /* the button is not pressed, do nothing */
  }
  else {
    /* the button is pressed */
    /* arm an alarm that will activated Task2 */ 
    SetRelAlarm(AlarmTask2, 1000, 0);

    /* set an event to wake up Task1 */
    SetEvent(Task1, ButtonEvent);

  }

  /* Clear Interrupt Sources */
  EE_user_buttons_clear_int();

}

/* 
 * The StartupHook in this case is used to initialize the Buttons and SysTick
 * interrupts
 */
void StartupHook(void)
{
  buttons_program();
  systick_program();
}

/*
 * Main 
 */
int main(void)
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

  StartOS(OSDEFAULTAPPMODE);

  /* Background activities, none in this demo! */
  for (;;)
  {
    ;	/* NOP */
  }

  /* Warning: statement is unreachable */
  /* return 0; */

}

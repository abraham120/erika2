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
 * Copyright (C) 2002-2008 Paolo Gai
 */

#include "ee.h"
#include "ee_irq.h"

#define __USE_LEDS__
#define __USE_BUTTONS__
#include "board/freescale_xpc564xl/inc/ee_board.h"

volatile unsigned int ERROR_FLAG = 0;

extern void prova_leds(EE_UREG led);

DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

/* some prototypes... */
void mydelay(unsigned long int del);
void led_blink(unsigned char theled);


volatile int led_status = 0;
volatile int myErrorCounter;

/* just a dummy delay */ 
void mydelay(unsigned long int del)
{
  volatile long int i;
  for (i=0; i<del; i++);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged...
 */
void led_blink(unsigned char theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_leds(led_status);
  EnableAllInterrupts();

  mydelay((long int)1200000);   // about 2 sec at 120 Mhz clock

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
}

/* BUTTON_0 interrupts activate Task2. */
static void Buttons_Interrupt(void)
{
  /* arm an alarm that will activate Task2 */
  SetRelAlarm(AlarmTask2,750,0);

  /* set an event to wake up Task1 */
  SetEvent(Task1, ButtonEvent);

  EE_buttons_clear_ISRflag(BUTTON_0);
}

static void Counter_Interrupt(void)
{
  CounterTick(Counter1);

  /* reset the decrementer to fire again */
  EE_e200z7_setup_decrementer(120000);  // set to 120 Mhz
}

EE_UINT32 b0, b1, b2, b3;

TASK(Task1)
{
  EventMaskType mask;
  
  while (1) {
    EE_buttons_clear_ISRflag(BUTTON_0);	
    EE_buttons_enable_interrupts(BUTTON_0);	
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

void ErrorHook(StatusType Error)
{
  myErrorCounter++;
  ERROR_FLAG = Error;
  led_blink(0xFF);
}

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  /* Init devices */
  EE_buttons_init();
  EE_e200z7_register_ISR(41 + 16, Buttons_Interrupt, 1);

  EE_e200z7_register_ISR(10, Counter_Interrupt, 0);
  EE_e200z7_setup_decrementer(120000);  // set to 120 Mhz
}


/* MAIN */
int main(void)
{
  /* Init HW: PLLs, clock (120 Mhz), clear error flags, etc */
  InitHW();

  /* Init leds */
  EE_leds_init();

  StartOS(OSDEFAULTAPPMODE);
  EE_e200z7_enableIRQ();

  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}

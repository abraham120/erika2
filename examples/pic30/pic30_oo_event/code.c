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

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							


DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);


/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for (i=0; i<ONEMILLION; i++)
    for (j=0; j<1000; j++);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged. See also the osek_task example for a full explanation of the
 * function.
 */
volatile int led_status = 0;
void led_blink(int theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_leds(led_status);
  EnableAllInterrupts();

  mydelay();

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
}



/* Program the Timer1 peripheral to raise interrupts */

void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0x9c40;		/* Load the Period register wit the value 0x9c40 (1ms @ 40MIPS)	*/
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
				* and clock source set to the internal 
				* instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
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

/* call the ERIKA Enterprise tick function for the Counter1 counter! */
ISR2(_T1Interrupt)
{
  /* clear the interrupt source */
  T1_clear();
 
  CounterTick(Counter1);
}


/*
 * Handle button_pio interrupts activates Task2.
 */
static void handle_button_interrupts(void)
{
  int buttonstatus;
  
  buttonstatus = EE_button_get_S1();

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

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  EE_buttons_init(&handle_button_interrupts, 0x01);
  T1_program();
}



int main(void)
{
  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */
  // EE_trace32_stack_init(); not supported yet on PIC30

  /* Init leds */
  EE_leds_init();
  EE_demoboard_leds_init();
	
  /* Init LCD */
  EE_lcd_init();
  EE_lcd_clear();
	  
  /* just a nice subliminal welcome message :-) */
  mydelay();
  EE_lcd_puts("I love FLEX &");
  EE_lcd_line2();
  EE_lcd_puts("ERIKA Enterprise");
	
  StartOS(OSDEFAULTAPPMODE);

  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}

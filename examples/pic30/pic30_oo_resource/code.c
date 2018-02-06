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



/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for (i=0; i<ONEMILLION*2; i++)
    for (j=0; j<1000; j++);
}

/* this counter will be printed on the console in ascending 
 * or decreasing order when the button is pressed
 */
volatile int mycounter=0;

/* This alarm callback is attached to the system timer, and is used to
 * activate LowTask
 * The period in expressed in system timer ticks, each one typically 10ms 
 */
volatile int timer_divisor = 0;
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();
	
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
  int j;

  /* Lock the resource */
  GetResource(Resource);

  /* do a long loop, printing the numbers from 0 to 9 */
  EE_leds(0x01);
  EE_lcd_clear();
  for (j=0; j<10; j++) {
    mydelay();
    EE_lcd_goto(j,0);
    EE_lcd_putc(j+'0');
  }
  EE_leds(0x00);
  
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

  EE_leds(0x02);
  for (i=0; i<ONEMILLION; i++);
  
  /* decrement or increment the counter depending on the application mode */
  if ( currentmode==ModeIncrement )
    mycounter++;
  else
    mycounter--;
  
  EE_lcd_line2();
  EE_lcd_puts("mycounter:");
  EE_lcd_putc(((mycounter%1000)/100)+'0');
  EE_lcd_putc(((mycounter%100)/10)+'0');
  EE_lcd_putc((mycounter%10)+'0');
  EE_leds(0x00);

  ReleaseResource(Resource);

  TerminateTask();
}

/*
 * Handle button_pio interrupts activates HighTask.
 */
static void handle_button_interrupts(void)
{
  ActivateTask(HighTask);  
}

int main(void)
{
  AppModeType startupmode;
  
  int buttonstatus;

  /* initialize buttons so we can read button 1 value */
  EE_buttons_init(0, 0);

  EE_leds_init();
  EE_demoboard_leds_init();
  
  EE_lcd_init();
  EE_lcd_clear();
  

  /* just a nice subliminal welcome message :-) */
  mydelay();
  EE_lcd_puts("I love FLEX :");
  
  /* read the button status */
  buttonstatus = EE_button_get_S1();

  /* check if the first button is pressed or not */
  if (buttonstatus & 0x1) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
    EE_lcd_puts("Inc");
  }
  else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
    EE_lcd_puts("Dec");
  }
  EE_lcd_home();

  StartOS(startupmode);
  
  /* Init button interrupt */
  EE_buttons_init(&handle_button_interrupts, 0x01);
    
  /* Program Timer 1 to raise interrupts */
  T1_program();
 
  for (;;);
}

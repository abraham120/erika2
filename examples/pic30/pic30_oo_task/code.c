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
 * Author: 2002-2008 Paolo Gai
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
volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile int led_status = 0;



/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);



/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for (i=0; i<ONEMILLION*4; i++)
    for (j=0; j<1000; j++);
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


/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */

volatile int timer_divisor = 0;

ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();
	
	timer_divisor++;
	if (timer_divisor==4000) {
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
  led_blink(0x01);
  led_blink(0x02);
  led_blink(0x04);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(0x08);
  led_blink(0x10);
  led_blink(0x20);
  
  TerminateTask();
}


/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  static int which_led = 0;
  /* count the number of Task2 activations */
  task2_fired++;

  /* let blink leds 6 or 7 */
  if (which_led) {
    led_blink(0x80);
    which_led = 0;
  }
  else {
    led_blink(0x40);
    which_led = 1;
  }

  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  EE_lcd_puts("Tmr:");
  EE_lcd_putc(((timer_fired%1000)/100)+'0');
  EE_lcd_putc(((timer_fired%100)/10)+'0');
  EE_lcd_putc((timer_fired%10)+'0');

  EE_lcd_puts(" Tsk1:");
  EE_lcd_putc(((task1_fired%1000)/100)+'0');
  EE_lcd_putc(((task1_fired%100)/10)+'0');
  EE_lcd_putc((task1_fired%10)+'0');

  EE_lcd_line2();
  EE_lcd_puts("Btn:");
  EE_lcd_putc(((button_fired%1000)/100)+'0');
  EE_lcd_putc(((button_fired%100)/10)+'0');
  EE_lcd_putc((button_fired%10)+'0');
  
  EE_lcd_puts(" Tsk2:");
  EE_lcd_putc(((task2_fired%1000)/100)+'0');
  EE_lcd_putc(((task2_fired%100)/10)+'0');
  EE_lcd_putc((task2_fired%10)+'0');

  EE_lcd_home();
  
  TerminateTask();
}



/*
 * Handle button_pio interrupts activates Task2.
 */
static void handle_button_interrupts(void)
{
  /* count the number of button presses */
  button_fired++;
  
  ActivateTask(Task2);  
}
  
int main()
{ 
  /* Clock setup */
  CLKDIVbits.DOZEN   = 0;
  CLKDIVbits.PLLPRE  = 0;
  CLKDIVbits.PLLPOST = 0;
  PLLFBDbits.PLLDIV  = 78;
	
  /* Wait for PLL to lock */
  while(OSCCONbits.LOCK!=1);
	
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
 
  /* Program Timer 1 to raise interrupts */
  T1_program();
	
  /* Init devices */
  EE_buttons_init(&handle_button_interrupts, 0x01);
  
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
  EE_lcd_home();
  
  /* now the background activities: in this case, we do nothing. */
  for (;;);
  
  return 0;
}

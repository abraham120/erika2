/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2010  Evidence Srl
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
	Author: 2009-2010 Dario Di Stefano
*/ 

#include "ee.h"
#include "cpu/hs12xs/inc/ee_irqstub.h"
#include "ee_s12regs.h" 
#include "myapp.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];
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

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;
volatile unsigned char led_status = 0;
volatile int dummit_counter=0;


/* just a dummy delay */ 
void mydelay(long int end)
{
  	long int i;
  	for (i=0; i<end; i++);
    
  	return;  
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
void led_blink(unsigned char theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_leds(led_status);
  EnableAllInterrupts();

  //mydelay((long int)125000);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;
   if(task1_fired==1)
  	EE_assert(4, task1_fired==1, 3);
  /* First half of the christmas tree */
  led_blink(LED_0);
  led_blink(LED_1);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
  //#ifdef MYSCHEDULE
  //  Schedule();
  //#endif

  /* Second half of the christmas tree */
  led_blink(LED_2);
  if(timer_fired<10)
  	PIT_Program();
  TerminateTask();
}

/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  static int which_led = 0;
  /* count the number of Task2 activations */
  task2_fired++;
	if(task2_fired==1)
  	EE_assert(3, task2_fired==1, 2);
  /* let blink leds 6 or 7 */
  if (which_led) 
  {
	led_status &= (~LED_3);
    EE_led_3_off();
    which_led = 0;
  }
  else 
  {
	led_status |= LED_3;
	EE_led_3_on();
    which_led = 1;
  }
  
  TerminateTask();
}
  
//void s12xs_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index)
//{
//	if (tos_index == EE_s12xs_active_tos)
//	goto label_2;
//label_2:
//	_asm("cli");
//	return;
//}  
  
  
// MAIN function 
int main()
{ 
	EE_assert(1, TRUE, EE_ASSERT_NIL);
	// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
	//EE_s12xs_system_tos[EE_s12xs_active_tos].SYS_tos = (EE_DADD)_asm("tfr s,d");	
	//_asm("tfr d,s",EE_s12xs_system_tos[EE_s12xs_active_tos].SYS_tos);	

  ///* Program Timer 1 to raise interrupts */
  PIT_Program();
  
  /* Init leds */
  EE_leds_init();

  mydelay(10);
  
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  /* now the background activities... */
  for (;;)
  {
     // if(EE_button_get_B0())        			// PP0 pushed
//      {
//          handle_button_interrupts(); 
//      }   
  }
  return 0;
}

void Interrupt_Init(void)
{
	// IVBR = 0xff;      // 0xFF default value
	INT_CFADDR = 0x70;
	INT_CFDATA5 = 0x02;
	
	INT_CFADDR = 0x70;
	INT_CFDATA4 = 0x05;
	
	_asm("cli");
	return;
}

void PIT_Program(void)
{
	  /*	PIT Module
	 */
	  PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	  PITFLT        = 0x00;        //@0x341;	/* PIT force load timer register */
	  PITCE         = 0x03;        //@0x342;	/* PIT channel enable register */
	  PITMUX        = 0x00;        //@0x343;	/* PIT multiplex register */
	  PITINTE       = 0x03;        //@0x344;	/* PIT interrupt enable register */
	  PITTF         = 0x03;        //@0x345;	/* PIT time-out flag register */
	  PITMTLD0      = 0x63;        //@0x346;	/* PIT micro timer load reg. 0 */
	  PITMTLD1      = 0x00;        //@0x347;	/* PIT micro timer load reg. 1 */
	  PITLD0        = 0x04;        //@0x348;	/* PIT load register 0 */
	  PITCNT0       = 0x00;        //@0x34a;	/* PIT count register 0 */
	  PITLD1        = 0x05;        //@0x34c;	/* PIT load register 1 */
	  PITCNT1       = 0x00;        //@0x34e;	/* PIT count register 1 */
	  PITLD2        = 0x00;        //@0x350;	/* PIT load register 2 */
	  PITCNT2       = 0x00;        //@0x352;	/* PIT count register 2 */
	  PITLD3        = 0x00;        //@0x354;	/* PIT load register 3 */
	  PITCNT3       = 0x00;        //@0x356;	/* PIT count register 3 */
	  PITCFLMT      = 0x80;        //@0x340;	/* PIT control micro timer register */
		  
	  Interrupt_Init();	  
	  return;
}

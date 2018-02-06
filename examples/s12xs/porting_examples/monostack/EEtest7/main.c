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
#include "test/assert/inc/ee_assert.h"
#include "ee_s12regs.h" 
#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

void Interrupt_Init(void);
static void mydelay(int end);
void PIT0_program(void);
void Interrupt_Init(void);
void EE_leds_init(void);

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;

/* just a dummy delay */ 
static void mydelay(int end)
{
  	int i;
  	for (i=0; i<end; i++);
    
  	return;  
}
 
/* Program the Timer1 peripheral to raise interrupts */

void PIT0_program(void)
{
	/*	PIT Module
 	*/
	  PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	  PITFLT        = 0x00;        //@0x341;	/* PIT force load timer register */
	  PITCE         = 0x01;        //@0x342;	/* PIT channel enable register */
	  PITMUX        = 0x00;        //@0x343;	/* PIT multiplex register */
	  PITINTE       = 0x01;        //@0x344;	/* PIT interrupt enable register */
	  PITTF         = 0x01;        //@0x345;	/* PIT time-out flag register */
	  PITMTLD0      = 0x63;        //@0x346;	/* PIT micro timer load reg. 0 */
	  PITMTLD1      = 0x00;        //@0x347;	/* PIT micro timer load reg. 1 */
	  PITLD0        = 0x04;        //@0x348;	/* PIT load register 0 */
	  PITCNT0       = 0x03;        //@0x34a;	/* PIT count register 0 */
	  PITLD1        = 0x00;        //@0x34c;	/* PIT load register 1 */
	  PITCNT1       = 0x00;        //@0x34e;	/* PIT count register 1 */
	  PITLD2        = 0x00;        //@0x350;	/* PIT load register 2 */
	  PITCNT2       = 0x00;        //@0x352;	/* PIT count register 2 */
	  PITLD3        = 0x00;        //@0x354;	/* PIT load register 3 */
	  PITCNT3       = 0x00;        //@0x356;	/* PIT count register 3 */
	  PITCFLMT      = 0x80;        //@0x340;	/* PIT control micro timer register */
	  
	  Interrupt_Init();
	  return;
}

/*	INTERRUPT registers initialisation
 */
void Interrupt_Init(void)
{
	// IVBR = 0xff;      // 0xFF default value
	_asm("cli");
	INT_CFADDR = 0x7A;
	INT_CFDATA0 = 0x02;
	
	return;
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  	task1_fired++;
  	EE_assert(4, task1_fired==1, 3);
  	ActivateTask(Task2); 

	PORTA |= 0x03;
	mydelay(2000);
	PORTA &= 0xFC;
	
	 PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	 PITCE         = 0x00;        //@0x342;	/* PIT channel enable register */

  	//TerminateTask();
}


/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
	task2_fired++;
  	// static int which_led = 0;
	if(task2_fired==1)
	{
		ActivateTask(Task2);
		ActivateTask(Task2);
		ActivateTask(Task2);
		ActivateTask(Task2);
		ActivateTask(Task2);
		ActivateTask(Task2);
	}
	//  /* count the number of Task2 activations */
    if(task2_fired==1)
  		EE_assert(2, task2_fired==1, 1);
  	else
  		if(task2_fired==5)
  			EE_assert(5, task2_fired==5, 4);
  	PORTA |= 0x0C;
	mydelay(1000);
	PORTA &= 0xF3;
	
  	//TerminateTask();
 
}

/*
 * Peripherals configuration
 */  
void EE_leds_init(void)
{
  	PORTA = (unsigned char)0x00;	// values                                             
  	DDRA = (unsigned char)0x0F;		// configured in output mode
  
  	return; 
}  

  
// MAIN function 
int main()
{ 
	EE_assert(1, TRUE, EE_ASSERT_NIL);
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  ActivateTask(Task2);

  ///* Program Timer 1 to raise interrupts */
  PIT0_program();
	
  /* Init leds */
  EE_leds_init();

  mydelay(10);
	while(task2_fired<5);
  EE_assert(6, task2_fired==5, 5);
  
  
  EE_assert_range(0,1,6);
  	EE_assert_last();
  while(1);
  
  return 0;
}

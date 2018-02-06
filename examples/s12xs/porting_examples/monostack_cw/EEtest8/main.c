/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011  Evidence Srl
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
	Author: Dario Di Stefano, 2011
*/ 

#include "ee.h"
#include "cpu/hs12xs/inc/ee_irqstub.h"
#include "test/assert/inc/ee_assert.h"
#include "mc9s12xs128.h" 
#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

void Interrupt_Init(void);
static void mydelay(int end);
void EE_leds(unsigned char value);
void led_blink(int theled);
void PIT0_program(void);
void Interrupt_Init(void);
static void handle_button_interrupts(void);
void EE_leds_init(void);
void EE_buttons_init(void);

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int button_fired=0;
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

/* Program the Timer peripheral to raise interrupts */

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

/*	INTERRUPT registers initialization
 */
void Interrupt_Init(void)
{
	// IVBR = 0xff;      // 0xFF default value
	_asm("cli");
	INT_CFADDR = 0x7A;
	INT_CFDATA0 = 0x02;
	
	return;
}

/* Task1 */
TASK(Task1)
{
  	task1_fired++;
  	
  	PITCFLMT      = 0x00;        //@0x340;	/* PIT control micro timer register */
	PITCE         = 0x00;        //@0x342;	/* PIT channel enable register */
  	
	/* Lock the resource */
  	GetResource(Resource);
  	EE_assert(3, task1_fired==1, 2);
  	ActivateTask(Task2);
  	EE_assert(4, task1_fired==1, 3);
	PORTA |= 0x03;
	mydelay(2000);
	PORTA &= 0xFC;
  
  	/* Release the lock */
  	ReleaseResource(Resource);
	
  	//TerminateTask();
}

/* Task2 */
TASK(Task2)
{
  	task2_fired++;
  	EE_assert(5, task2_fired==1, 4);
  	GetResource(Resource);
  	EE_assert(6, task1_fired==1, 5);
  	PORTA |= 0x0C;
	mydelay(1000);
	PORTA &= 0xF3;

  	ReleaseResource(Resource);
  	
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

int main(void)
{
	EE_assert(1, TRUE, EE_ASSERT_NIL);
	
	/* Init leds */
	EE_leds_init();
	
	mydelay(10);
   
  	StartOS(OSDEFAULTAPPMODE);
  
  	///* Program Timer to raise interrupts */
  	PIT0_program();
  
  	while(task2_fired<1);
  	EE_assert_range(0,1,6);
  	result = EE_assert_last();
  
	while(1);
  
  	return 0;
}


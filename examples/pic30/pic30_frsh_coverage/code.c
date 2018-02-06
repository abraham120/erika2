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



#define ONEMILLION 100000


int test_current = 0;


/*
 * TEST 0
 * Four tasks with the same contracts.
 * Each one starts, ends the budget, got recharging.
 * When the fourth ends the slice, a few are removed from the recharging queue.
 * then the recharging IRQ arrives
 *
 * In the middle, task1 change VRES obtaining a different budget
 */

void Test0(void)
{
    test_current = 0;
    ActivateTask(Task1);
}
void test0_task1(void)
{
  long int i;
  ActivateTask(Task2);
  ActivateTask(Task3);
  ActivateTask(Task4);
  for (i=0; i<ONEMILLION/64; i++);
  frsh_thread_bind(c5, Task1);
  for (i=0; i<ONEMILLION/32+ONEMILLION/64; i++);
  frsh_thread_bind(c1, Task1);
}

void test0_task2(void)
{
  long int i;
  for (i=0; i<ONEMILLION/16; i++);
}

void test0_task3(void)
{
  long int i;
  for (i=0; i<ONEMILLION/16; i++);
}

void test0_task4(void)
{
  long int i;
  for (i=0; i<ONEMILLION/16; i++);
}

void test0_task5(void)
{
  long int i;
  for (i=0; i<ONEMILLION/64; i++);
}


/*
 * TEST 1
 * Four tasks, but two ends early. the recharging IRQ is not needed.
 * At the end of task4 a double activation of task4
 * At the end of the second activation, task3 is activated, and task4 unbinds himself
 * result: task3 runs, task4 not.
 * then task3 binds task4
 * task4 runs with task3 with a different budget
 */

void Test1(void)
{
    frsh_vres_id_t vres_id;
    frsh_contract_t contract;

    test_current = 1;
    ActivateTask(Task1);

    // at the end Task4 is unbound and ready.
    // we bind it so it can get executed preempting the current task
    frsh_thread_bind(c4, Task4);

    frsh_thread_get_vres_id(Task4, &vres_id);   // OK
    // then we unbind it
    frsh_thread_unbind(Task4);
    frsh_thread_get_vres_id(Task4, NULL);       // null parameter
    frsh_thread_get_vres_id(1000, &vres_id);    // wrong id
    frsh_thread_get_vres_id(-1000, &vres_id);   // wrong id
    frsh_thread_unbind(Task4);       // on an unbound task
    frsh_thread_get_vres_id(Task4, &vres_id);   // unbound task

    // and we activate it
    ActivateTask(Task4);
    // here Task4 ends  with 1 pending activation, but it is unbound

    frsh_vres_get_contract(c1, NULL);          // null parameter
    frsh_vres_get_contract(1000, &contract);   // wrong id
    frsh_vres_get_contract(-1000, &contract);  // wrong id
    frsh_vres_get_contract(c1, &contract);     // wrong id
}

int test1_step=0;

void test1_task1(void)
{
  long int i;
  ActivateTask(Task2);
  ActivateTask(Task3);
  ActivateTask(Task4);
  ActivateTask(Task5);
  for (i=0; i<ONEMILLION/64; i++);
}

void test1_task2(void)
{
  long int i;
  for (i=0; i<ONEMILLION/64; i++);
}

void test1_task3(void)
{
  long int i;

  switch (test1_step) {
    case 0:
        for (i=0; i<ONEMILLION/32; i++);
        break;
    case 1:
        for (i=0; i<ONEMILLION/32; i++);

        // some checks on values
        frsh_thread_bind(c1, Task4);  // already bound
        frsh_thread_bind(1000, Task4); // vres id wrong
        frsh_thread_bind(-1, Task4); // vres id wrong
        frsh_thread_bind(c7, 1000); // task id wrong
        frsh_thread_bind(c7, -1); // task id wrong

        frsh_thread_bind(c7, Task4);
        for (i=0; i<ONEMILLION/32; i++);
        break;
  };

}

void test1_task4(void)
{
  long int i;

  for (i=0; i<ONEMILLION/32; i++);

  switch (test1_step) {
    case 0:
        ActivateTask(Task4);
        test1_step = 1;
        break;
    case 1:
        ActivateTask(Task3);
        frsh_thread_unbind(1000); // wrong id
        frsh_thread_unbind(-1); // wrong id
        frsh_thread_unbind(Task4); // on the running thread!
        frsh_thread_unbind(Task4); // on the running thread!
        for (i=0; i<ONEMILLION/32; i++);
        break;
  }
}

/*
 * TEST 2
 */

volatile int firsttime=1;


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

  if (firsttime) {
	  CounterTick(Counter1);
  }
}



TASK(test2_callback)
{
  /* Count the number of alarm expirations */
  static int test2_fired=0;

  if (test2_fired)
    firsttime=0; // this way task 3 can make a preemption

  test2_fired++;

  ActivateTask(Task4);  // on an unbinded task --> never a preemption!
  ActivateTask(Task3);  // on an unbinded task

  if (test2_fired==3)
    CancelAlarm(test2alarm);
}


void Test2(void)
{
    test_current = 2;

    /* start the periodic timers */
    SetRelAlarm(test2alarm,1,1);

    ActivateTask(Task1);
}
void test2_task1(void)
{
  frsh_thread_bind(c5, Task1);  // bind on the running thread
  frsh_thread_bind(c6, Task2);  // bind on a non-ready thread
  frsh_thread_bind(c7, Task3);  // correct bind

  ActivateTask(Task2);          // activate task2
  frsh_thread_bind(c1, Task2);  // should make a preemption on Task1

  while (firsttime);
  frsh_thread_bind(c6, Task2);  // task3 activated by a callback should make a preemption
                                // on Task2 because the vres has a long period

  frsh_thread_bind(c4, Task4);  // rebind task4, it will be used later on. a few task4 activation will execute

}

void test2_task2(void)
{
  long int i;
  for (i=0; i<ONEMILLION/4; i++);
}

void test2_task3(void)
{
}

void test2_task4(void)
{
}

/*
 * TEST 3
 * Resources
 */

void Test3(void)
{
    test_current = 3;
    ActivateTask(Task1);
}
void test3_task1(void)
{
  long int i;

  // really short critical section
  GetResource(myRes);
  ReleaseResource(myRes);

  GetResource(myRes);
  ActivateTask(Task2);  // preemption is disabled
  for (i=0; i<ONEMILLION/32; i++);

  ReleaseResource(myRes);

  for (i=0; i<ONEMILLION/32; i++);

  /* deferred unbind */
  GetResource(myRes);
  frsh_thread_unbind(Task1);       // unbind is postponed
  frsh_thread_unbind(Task1);       // Error, the unbind has been postponed
  for (i=0; i<ONEMILLION/32; i++);
  ActivateTask(Task3);             // this will bind again task1
  ReleaseResource(myRes);

  /* task3 executes here after the unbind */

  /* deferred bind */
  GetResource(myRes);
  frsh_thread_bind(c2,Task1);       // bind is postponed
  for (i=0; i<ONEMILLION/32; i++);
  ReleaseResource(myRes);

  for (i=0; i<ONEMILLION/32; i++);

  /* nested resources */
  GetResource(myRes);
  GetResource(myRes2);
  ReleaseResource(myRes2);
  ReleaseResource(myRes);


}

void test3_task2(void)
{
  long int i;
  for (i=0; i<ONEMILLION/32; i++);
}

void test3_task3(void)
{
  long int i;
  for (i=0; i<ONEMILLION/32; i++);
  frsh_thread_bind(c5,Task1);          // this will bind again task1 (c5 was set in test4
}

void test3_task4(void)
{
}




/*
 * TEST 4
 * Alarms
 */

void Test4(void)
{
    test_current = 4;
    ActivateTask(Task1);
}
void test4_task1(void)
{
    CounterTick(Counter1);
    Schedule();

    /* test for alarm cancellation */
    CancelAlarm(AlarmTask2); // alarm not set

    SetRelAlarm(AlarmTask2,1,1);
    SetAbsAlarm(AlarmTask3,2,1);
    SetRelAlarm(AlarmTask4,3,0);
    CancelAlarm(AlarmTask3); // cancel not the first alarm but there is someone after
    CancelAlarm(AlarmTask2);
    CancelAlarm(AlarmTask4);


    SetRelAlarm(AlarmTask2,2,1);
    SetAbsAlarm(AlarmTask3,2,1);
    SetRelAlarm(AlarmTask4,1,0);
    CounterTick(Counter1);
    Schedule();
    CounterTick(Counter1);
    Schedule();
    CounterTick(Counter1);
    Schedule();
    CounterTick(Counter1);
    Schedule();
    CounterTick(Counter1);
    Schedule();
    CounterTick(Counter1);
    Schedule();
    CounterTick(Counter1);
    Schedule();
}

void test4_task2(void)
{
  static int i = 0;
  if (i==2)
    CancelAlarm(AlarmTask2);
  i++;
}

void test4_task3(void)
{
  static int i = 0;

  // Note: when task3 is activated by the counter, It does not preempt task1.
  // making the test i>2 as it was in the beginning is erroneous because it makes
  // a double call to cancelalarm
  if (i==2)
    CancelAlarm(AlarmTask3);
  i++;
}

void test4_task4(void)
{
}



/*
 * TEST 5
 * Synch Objs
 */

SynchObjType syncobj = SYNCHOBJINIT;
volatile int test5_done = 0;

void Test5(void)
{
    test_current = 5;
    ActivateTask(Task1);
    ActivateTask(Task2);
    ActivateTask(Task3);
    while (!test5_done);
}
void test5_task1(void)
{
    EE_TIME t;
    bool flag;

    frsh_synchobj_wait(&syncobj, NULL, NULL, NULL, NULL);
    t = EE_sys_gettime()+10000;
    frsh_synchobj_wait_with_timeout(&syncobj, &t, &flag, NULL, NULL, NULL, NULL);
    t = EE_sys_gettime()+10000;
    frsh_synchobj_wait_with_timeout(&syncobj, &t, &flag, NULL, NULL, NULL, NULL);
    frsh_synchobj_wait_with_timeout(&syncobj, &t, &flag, NULL, NULL, NULL, NULL); // in the past
    ActivateTask(Task4);
}

void test5_task2(void)
{
    frsh_synchobj_signal(&syncobj);
}

void test5_task3(void)
{
    frsh_synchobj_signal(&syncobj);
}

void test5_task4(void)
{
    EE_TIME t;
    int i=0;

    t = EE_sys_gettime();
    frsh_timed_wait(&t, NULL, NULL, NULL, NULL); // in the past

    do {
        t = EE_sys_gettime()+10000;
        frsh_timed_wait(&t, NULL, NULL, NULL, NULL);
    } while (++i<3);

    test5_done=1;
}

/*
 * TEST 6
 * Synch Objs part two
 */

SynchObjType syncobj6 = SYNCHOBJINIT;
volatile int test6_done = 0;

void Test6(void)
{
    test_current = 6;
    ActivateTask(Task1);
    ActivateTask(Task2);
    ActivateTask(Task3);
    ActivateTask(Task4);
    while (test6_done==0);
    ActivateTask(Task4);
    while (test6_done==1);

}
void test6_task1(void)
{
    EE_TIME t;
    bool flag;
    t = EE_sys_gettime()+20000;

    frsh_synchobj_wait(NULL, NULL, NULL, NULL, NULL); // synchobj null
    frsh_synchobj_wait_with_timeout(NULL, &t, &flag, NULL, NULL, NULL, NULL); // synchobj null
    frsh_timed_wait(NULL, NULL, NULL, NULL, NULL); // synchobj null

    frsh_synchobj_wait_with_timeout(&syncobj6, NULL, &flag, NULL, NULL, NULL, NULL); // time null

    frsh_synchobj_signal(&syncobj6);
    frsh_synchobj_wait_with_timeout(&syncobj6, NULL, &flag, NULL, NULL, NULL, NULL); // no wait

    frsh_synchobj_signal(&syncobj6);
    frsh_synchobj_wait(&syncobj6, NULL, NULL, NULL, NULL); // no wait

    frsh_synchobj_wait_with_timeout(&syncobj6, &t, &flag, NULL, NULL, NULL, NULL);
    frsh_synchobj_wait(&syncobj6, NULL, NULL, NULL, NULL);
}

void test6_task2(void)
{
    EE_TIME t;
    bool flag;
    t = EE_sys_gettime()+10000;
    frsh_synchobj_wait_with_timeout(&syncobj6, &t, &flag, NULL, NULL, NULL, NULL);
    frsh_synchobj_wait(&syncobj6, NULL, NULL, NULL, NULL);
}

void test6_task3(void)
{
    frsh_rel_time_t next_budget, next_period;
    bool was_deadline_missed, was_budget_overrun;
    EE_TIME t;
    bool flag;
    t = EE_sys_gettime()+30000;
    frsh_synchobj_wait_with_timeout(&syncobj6, &t, &flag, &next_budget, &next_period, &was_deadline_missed, &was_budget_overrun);
    frsh_synchobj_wait(&syncobj6, &next_budget, &next_period, &was_deadline_missed, &was_budget_overrun);
}

void test6_task4(void)
{
  EE_TIME t;
  frsh_rel_time_t next_budget, next_period;
  bool was_deadline_missed, was_budget_overrun;

  t = EE_sys_gettime()+10000;
  frsh_timed_wait(&t, &next_budget, &next_period, &was_deadline_missed, &was_budget_overrun);


  switch (test6_done) {
  case 0:
    frsh_synchobj_signal(&syncobj6);
    frsh_synchobj_signal(&syncobj6);
    frsh_synchobj_signal(&syncobj6);
    test6_done=1;
    break;
  default:
    frsh_synchobj_signal(&syncobj6);
    frsh_synchobj_signal(&syncobj6);
    frsh_synchobj_signal(&syncobj6);

    test6_done=2;
    break;

  }
}

/*
 * TEST 7
 * forever loops with different frequencies
 */

void Test7(void)
{
    test_current = 7;
    frsh_thread_unbind(Task1);
    frsh_thread_unbind(Task2);
    frsh_thread_unbind(Task3);
    frsh_thread_unbind(Task4);
    frsh_thread_bind(c1, Task1);
    frsh_thread_bind(c5, Task2);
    ActivateTask(Task1);
}



/* just a dummy delay */
static void mydelay(void)
{
  int i,j;
  for (i=0; i<1000; i++)
    for (j=0; j<1000; j++);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged. See also the osek_task example for a full explanation of the
 * function.
 */
volatile int led_status = 0;
void myblink(int theled)
{
  EE_hal_disableIRQ();
  led_status |= theled;
  EE_leds(led_status);
  EE_hal_enableIRQ();

  mydelay();

  EE_hal_disableIRQ();
  led_status &= ~theled;
  EE_leds(led_status);
  EE_hal_enableIRQ();

  mydelay();
}




void test7_task1(void)
{
   ActivateTask(Task2);
   for (;;) myblink(0x1);
}

void test7_task2(void)
{
	for (;;) myblink(0x2);
}

/* Task Bodies */

TASK(Task1)
{
    switch (test_current) {
        case 0: test0_task1(); break;
        case 1: test1_task1(); break;
        case 2: test2_task1(); break;
        case 3: test3_task1(); break;
        case 4: test4_task1(); break;
        case 5: test5_task1(); break;
        case 6: test6_task1(); break;
        default:test7_task1(); break;
    };
}

TASK(Task2)
{
    switch (test_current) {
        case 0: test0_task2(); break;
        case 1: test1_task2(); break;
        case 2: test2_task2(); break;
        case 3: test3_task2(); break;
        case 4: test4_task2(); break;
        case 5: test5_task2(); break;
        case 6: test6_task2(); break;
        default:test7_task2(); break;
    };
}

TASK(Task3)
{
    switch (test_current) {
        case 0: test0_task3(); break;
        case 1: test1_task3(); break;
        case 2: test2_task3(); break;
        case 3: test3_task3(); break;
        case 4: test4_task3(); break;
        case 5: test5_task3(); break;
        default:test6_task3(); break;
    };
}

TASK(Task4)
{
    switch (test_current) {
        case 0: test0_task4(); break;
        case 1: test1_task4(); break;
        case 2: test2_task4(); break;
        case 3: test3_task4(); break;
        case 4: test4_task4(); break;
        case 5: test5_task4(); break;
        default:test6_task4(); break;
    };
}

TASK(Task5)
{
    test0_task5();
}






int main(void)
{
  long int i;

  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */

  /* Init leds */
  EE_leds_init();
  EE_demoboard_leds_init();

  /* Init LCD */
  EE_lcd_init();
  EE_lcd_clear();

  /* just a nice subliminal welcome message :-) */
  EE_lcd_puts("I love FLEX &");
  EE_lcd_line2();
  EE_lcd_puts("ERIKA Enterprise");

  T1_program();

  /* program the conter timer */
  frsh_init();

  /* to test the error return */
  frsh_init();

  /* exectute the coverage tests */
  Test0();
  for (i=0; i<ONEMILLION/16; i++);
  Test1();
  for (i=0; i<ONEMILLION/16; i++);
  Test2();
  for (i=0; i<ONEMILLION/16; i++);
  Test3();
  for (i=0; i<ONEMILLION/16; i++);
  Test4();
  for (i=0; i<ONEMILLION/16; i++);
  Test5();
  for (i=0; i<ONEMILLION/16; i++);
  Test6();
  for (i=0; i<ONEMILLION/16; i++);
  Test7();

  /* Background activities, none in this demo! */
  for (;;);

  return 0;
}



/*
 * Copyright (C) 2002-2006 Evidence Srl
 * Author: Paolo Gai
 */

/* Altera Includes */ 
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "altera_avalon_timer_regs.h"

/* EE includes */
#include "ee.h"

DeclareTask(Task1);
DeclareTask(Task2);

#define ONEMILLION 1000000

/*
 * 
 * Button PIO
 * 
 */


/*
 * Handle button_pio interrupts activates Task2.
 */
static void handle_button_interrupts(void* context, alt_u32 id)
{
  int buttonstatus;
  
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);

  buttonstatus = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

  /* check if the first button is pressed or not */
  if (buttonstatus & 0x1) {
    /* the button is not pressed, do nothing */

    ActivateTask(Task2);
  }
  else {
    ActivateTask(Task3);


    /* the button is pressed */
    /* arm an alarm that will activated Task2 */ 
//    SetRelAlarm(AlarmTask2, 1000, 0);

    /* set an event to wake up Task1 */
//    SetEvent(Task1, ButtonEvent);
  }
}

/* Initialize the button_pio. */
static void init_button_pio()
{
  /* Enable the first two 2 button interrupts. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_PIO_BASE, 0x3);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0x0);
  /* Register the interrupt handler. */
  alt_irq_register( BUTTON_PIO_IRQ, NULL, handle_button_interrupts ); 
}




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
  int i;
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
  int i;
  for (i=0; i<ONEMILLION/16; i++);
}

void test0_task3(void)
{
  int i;
  for (i=0; i<ONEMILLION/16; i++);
}

void test0_task4(void)
{
  int i;
  for (i=0; i<ONEMILLION/16; i++);
}

void test0_task5(void)
{
  int i;
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
  int i;
  ActivateTask(Task2);
  ActivateTask(Task3);
  ActivateTask(Task4);
  ActivateTask(Task5);
  for (i=0; i<ONEMILLION/64; i++);
}

void test1_task2(void)
{
  int i;
  for (i=0; i<ONEMILLION/64; i++);
}

void test1_task3(void)
{
  int i;
  
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
  int i;
 
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

alt_u32 test2_callback (void* arg)
{
  /* Count the number of alarm expirations */
  static int test2_fired=0;
  int returnvalue;
  
  if (test2_fired)
    firsttime=0; // this way task 3 can make a preemption
    
  test2_fired++;
  
  ActivateTask(Task4);  // on an unbinded task --> never a preemption!
  ActivateTask(Task3);  // on an unbinded task
  
  if (test2_fired==3) 
    returnvalue = 0;
  else
    returnvalue = 1;
  
  return returnvalue;
}


alt_alarm myalarm;

void Test2(void)
{
    test_current = 2;

    /* start the periodic timers */
    alt_alarm_start (&myalarm, 1, 
                     test2_callback, NULL);
    
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
  int i;
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
  int i;

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
  int i;
  for (i=0; i<ONEMILLION/32; i++);
}

void test3_task3(void)
{
  int i;
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
        default:test6_task1(); break;
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
        default:test6_task2(); break;
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
  int i;
  
  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */
  EE_trace32_stack_init();
 
  //  StartOS(OSDEFAULTAPPMODE);

  /* program the Button PIO */
  init_button_pio();
  
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

  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}



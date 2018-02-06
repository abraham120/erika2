#include <ee_internal.h>
#include <ee.h>
#include "test_irq.h"

void error( void )
{
  /* Do nothing; you should add a breakpoint on this function to catch
   * errors */
  EE_tc_debug();
}

unsigned int priority_to_be_generated;

void call_stack3( void )
{
  if ( priority_to_be_generated > 0 )
  {
    test_fire_irq(priority_to_be_generated);
  } else {
    /* TODO: manca IDs of OS-Applications */
    TerminateApplication(1U, NO_RESTART);
  }
}

void call_stack2( void )
{
  __asm volatile ("call call_stack3");
}

void call_stack1( void )
{
  __asm volatile ("call call_stack2");
}

TASK(MainTask)
{
  test_setup_irq(EE_ISR2_ID_App1Isr1);
  test_setup_irq(EE_ISR2_ID_App2Isr2);
  test_setup_irq(EE_ISR2_ID_App2Isr3);

  ActivateTask(TaskApp1Prio2);
  ActivateTask(TaskApp2Prio3);
  ActivateTask(TaskApp1Prio4);

  TerminateTask();
}

TASK(TaskApp1Prio2)
{
  error();
}

TASK(TaskApp2Prio3)
{
  TerminateTask();
}

TASK(TaskApp1Prio4)
{
  ActivateTask(TaskApp1Prio5);
  error();
}

TASK(TaskApp1Prio5)
{
  ActivateTask(TaskApp2Prio6);
  error();
}

TASK(TaskApp2Prio6)
{
  ActivateTask(TaskApp1Prio7);
  TerminateTask();
}

TASK(TaskApp1Prio7)
{
  ActivateTask(TaskApp2Prio8);
  error();
}

TASK(TaskApp2Prio8)
{
  test_fire_irq(EE_ISR2_ID_App1Isr1);
  TerminateTask();
}


ISR2(App1Isr1)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App2Isr2;
  call_stack1();
  error();
}

ISR2(App2Isr2)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App2Isr3;
  call_stack1();
  /* Check auto TerminateISR2 */
}

ISR2(App2Isr3)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = 0;

  call_stack1();
  /* Check auto TerminateISR2 */
}

#include <ee_internal.h>
#include <ee.h>
#include "test/assert/inc/ee_assert.h"
#include "test_irq.h"

#define API_START_SEC_VAR_NOINIT
#define API_START_SEC_CODE
#include "MemMap.h"

void error( void )
{
  /* Do nothing; you should add a breakpoint on this function to catch
   * errors */
  EE_tc_debug();
}

unsigned int priority_to_be_generated;

EE_TYPEASSERTVALUE EE_assertions[5];

static int assert_count = EE_ASSERT_NIL;
static void assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}
#define API_STOP_SEC_VAR_NOINIT
#define API_STOP_SEC_CODE
#include "MemMap.h"

void TRUSTED_test_fire_irq( void ) {
  /* WORKAROUND: Postpone the IRQ at the end of TRUSTED function */
  EE_hal_disableIRQ();
  test_fire_irq(priority_to_be_generated);
}

void call_stack3( void )
{
  if ( priority_to_be_generated > 0 )
  {
    CallTrustedFunction(EE_ID_TRUSTED_test_fire_irq, 0);
  } else {
    TerminateApplication(UserApp1, NO_RESTART);
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
  test_setup_irq(EE_ISR2_ID_App1Isr2);
  test_setup_irq(EE_ISR2_ID_App2Isr3);

  ActivateTask(TaskApp1Prio2);
  ActivateTask(TaskApp2Prio3);
  ActivateTask(TaskApp1Prio4);

  TerminateTask();
}

TASK(TaskApp1Prio2)
{
  /* This should never be scheduled */
  error();
}

TASK(TaskApp1Prio4)
{
  ActivateTask(TaskApp2Prio5);
  WaitEvent(DummyEvent);
  /* This should not reach here */
  error();
}

TASK(TaskApp1Prio6)
{
  StatusType s;

  s = TerminateApplication(TrustedApp2, RESTART);
  assert( s == E_OS_ACCESS );
  ShutdownOS( E_OS_ACCESS ); /* ignored */

  priority_to_be_generated = EE_ISR2_ID_App1Isr1;
  CallTrustedFunction(EE_ID_TRUSTED_test_fire_irq, 0);
  error();
}

TASK(TaskApp2Prio3)
{
  StatusType s;
  TaskStateType status;
  s = SetEvent(TaskApp1Prio4, DummyEvent);
  assert ( s == E_OS_STATE );
  s = GetTaskState(TaskApp1Prio4, &status);
  assert ( status == SUSPENDED );
  /* This shall not never return */
  s = SetEvent(TaskApp2Prio5, DummyEvent);
  error();
}

TASK(TaskApp2Prio5)
{
  ActivateTask(TaskApp1Prio6);
  WaitEvent(DummyEvent);

  EE_assert_range(0, 1, assert_count); 
  EE_assert_last();

  /* This shall not never return */
  ShutdownOS( E_OK );
  error();

}

ISR2(App1Isr1)
{
  StatusType s;
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App1Isr2;
  /* TODO: manca IDs of OS-Applications */
  s = TerminateApplication(TrustedApp2, RESTART);
  assert( s == E_OS_ACCESS );

  call_stack1();
  error();
}

ISR2(App1Isr2)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App2Isr3;
  call_stack1();
  error();
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

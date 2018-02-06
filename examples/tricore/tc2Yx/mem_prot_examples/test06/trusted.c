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
    TerminateApplication(TrustedApp, NO_RESTART);
  }
  error();
}

void call_stack2( void )
{
  __asm volatile ("call call_stack3");
  error();
}

void call_stack1( void )
{
  __asm volatile ("call call_stack2");
  error();
}

TASK(MainTask)
{
  test_setup_irq(EE_ISR2_ID_TrustedIsr1);
  test_setup_irq(EE_ISR2_ID_TrustedIsr2);
  test_setup_irq(EE_ISR2_ID_TrustedIsr3);

  test_fire_irq(EE_ISR2_ID_TrustedIsr1);

  error();
  /* TerminateTask(); */
}

ISR2(TrustedIsr1)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_TrustedIsr2;
  call_stack1();
  error();
}

ISR2(TrustedIsr2)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_TrustedIsr3;
  call_stack1();
  error();
}

ISR2(TrustedIsr3)
{
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = 0;

  call_stack1();
  error();
}

#include <ee_internal.h>
#include <ee.h>
#include "test/assert/inc/ee_assert.h"
#include "test_irq.h"

#define API_START_SEC_VAR_NOINIT
#define API_START_SEC_CODE
#include "MemMap.h"

/* Just used to force the compilare to allocate stack */
extern void really_grab_the_stack ( char * );

void error( void )
{
  /* Do nothing; you should add a breakpoint on this function to catch
   * errors */
  EE_tc_debug();
}

unsigned int priority_to_be_generated;

EE_TYPEASSERTVALUE EE_assertions[20];

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

void EE_TC_CHANGE_STACK_POINTER TRUSTED_call_stack3( void )
{
  /* WORKAROUND: Disaling IRQ will postpone its generation at the end of the
                 CallTrustedFunction syscall. Because of that I won't need more
                 to change OS Kernel data structures here directly */
  EE_hal_disableIRQ();
  if ( priority_to_be_generated == 3 ) {
    extern EE_STACK_T EE_tc_stack_4[EE_STACK_WLEN(512)];
    EE_ADDR sp = EE_tc_get_SP();
    ApplicationType current_app = GetApplicationID();
    assert((EE_STACK_ENDP(EE_tc_stack_4) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_4)));
    assert( current_app == 2U );
    assert( EE_as_Application_RAM[current_app].TrustedFunctionCallsCounter != 0U );
    /* !!!! FOLLOWING INSTRUCTION IS CRIMINAL done only because 
            App1Isr3 will be filtered by EE_tc_isr2_global_wrapper for
            [OS563] !!!!   */
    /* EE_as_Application_RAM[1].TrustedFunctionCallsCounter = 0U;
        EG: Finally commented */
  }
  test_fire_irq(priority_to_be_generated);
}

void EE_TC_CHANGE_STACK_POINTER call_stack2( void )
{
  if ( priority_to_be_generated > 0 ) {
    CallTrustedFunction(EE_ID_TRUSTED_call_stack3, 0);
  } else {
    extern EE_STACK_T EE_tc_stack_3[EE_STACK_WLEN(512)];
    EE_ADDR sp = EE_tc_get_SP();
    ApplicationType current_app = GetApplicationID();
    assert((EE_STACK_ENDP(EE_tc_stack_3) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_3)));
    assert( current_app == 1U );
    assert( EE_as_Application_RAM[current_app].TrustedFunctionCallsCounter  == 0U );
    TerminateApplication(UserApp1, NO_RESTART);
    /* ISR self termination */
    error();
  }
}

void call_stack1( void )
{
  __asm volatile ("call call_stack2");
}

TASK(MainTask)
{
  test_setup_irq(EE_ISR2_ID_App1Isr1);
  test_setup_irq(EE_ISR2_ID_App2Isr2);
  test_setup_irq(EE_ISR2_ID_App1Isr3);

  ActivateTask(TaskApp1Prio2);
  ActivateTask(TaskApp2Prio2);
  ActivateTask(TaskApp1Prio2);
  ActivateTask(TaskApp1Prio2);
  ActivateTask(TaskApp2Prio2);

  ActivateTask(TaskApp1Prio5);
  ActivateTask(TaskApp2Prio5);
  ActivateTask(TaskApp1Prio5);
  ActivateTask(TaskApp2Prio5);
  ActivateTask(TaskApp1Prio5);
  ActivateTask(TaskApp2Prio5);
  ActivateTask(TaskApp2Prio5);

  TerminateTask();
}


#define APP_UserApp1_START_SEC_CODE
#define APP_UserApp1_START_SEC_VAR_NOINIT
#include "MemMap.h"
TASK(TaskApp1Prio2)
{
  /* it must be never activated */
  error();
}

TASK(TaskApp1Prio5)
{
  static EE_UREG count;
  if (count > 0) {
    error();
  }
  count++;
}
#define APP_UserApp1_STOP_SEC_CODE
#define APP_UserApp1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

TASK(TaskApp2Prio2)
{
  ActivateTask(TaskApp2Prio5);
  TerminateTask();
}

TASK(TaskApp2Prio3)
{
  /* Never activated */
  error();
}

void EE_TC_CHANGE_STACK_POINTER FuncTaskApp2Prio5( void )
{
  static EE_UINT32 count;
  static MemoryStartAddressType volatile UserApp1ISRTOS;
  static MemoryStartAddressType volatile TrustedApp2ISRTOS;
  static EE_ADDR volatile sp;

  if ( count == 0U ) {
    UserApp1ISRTOS    = EE_tc_system_tos[EE_as_Application_ROM[UserApp1].ISRTOS].ram_tos;
    TrustedApp2ISRTOS = EE_tc_system_tos[EE_as_Application_ROM[TrustedApp2].ISRTOS].ram_tos;
  }
  sp = EE_tc_get_SP();
  test_fire_irq(EE_ISR2_ID_App1Isr1);
  assert( sp == EE_tc_get_SP() );
  if ( count >= 5U ) {
    assert ( UserApp1ISRTOS == EE_tc_system_tos[EE_as_Application_ROM[UserApp1].ISRTOS].ram_tos );
    assert ( TrustedApp2ISRTOS == EE_tc_system_tos[EE_as_Application_ROM[TrustedApp2].ISRTOS].ram_tos );
    EE_assert_range(0, 1, assert_count); 
    EE_assert_last();
  }
  ++count;
  TerminateTask();
}

void EE_TC_CHANGE_STACK_POINTER App2Isr2( void )
{
  extern EE_STACK_T EE_tc_stack_4[EE_STACK_WLEN(512)];
  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_4) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_4)));
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App1Isr3;
  call_stack1();
  /* Check auto TerminateISR2 */
}

#define APP_UserApp1_START_SEC_CODE
#define APP_UserApp1_START_SEC_VAR_NOINIT
#include "MemMap.h"

EE_ADDR      stack_pointer_holder;

void EE_TC_CHANGE_STACK_POINTER App1Isr1( void )
{
  extern EE_STACK_T EE_tc_stack_3[EE_STACK_WLEN(512)];
  static EE_UREG count;
  char grab_stack[8];
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  if ( count > 0 ) {
    error();
  }
  ++count;
  stack_pointer_holder =  EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_3) < stack_pointer_holder) && (stack_pointer_holder <= EE_STACK_INITP(EE_tc_stack_3)));

  priority_to_be_generated = EE_ISR2_ID_App2Isr2;
  call_stack1();
  error();
  really_grab_the_stack(grab_stack);
  priority_to_be_generated = grab_stack[1];
}

void EE_TC_CHANGE_STACK_POINTER App1Isr3( void )
{
  extern EE_STACK_T EE_tc_stack_3[EE_STACK_WLEN(512)];
  char grab_stack[8];
  EE_ADDR sp = EE_tc_get_SP();
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = 0;
  assert((EE_STACK_ENDP(EE_tc_stack_3) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_3)));
  assert(sp <= stack_pointer_holder);
  call_stack1();
  error();
  really_grab_the_stack(grab_stack);
  priority_to_be_generated = grab_stack[1];
}
#define APP_UserApp1_STOP_SEC_CODE
#define APP_UserApp1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

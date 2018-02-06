#include <ee_internal.h>
#include <ee.h>
#include "test_irq.h"

  /* Just used to force the compilare to allocate stack */
extern void really_grab_the_stack ( char * stack_grabber );

/* Variable used to check privileges in Hooks */
int trusted_memory;

#define API_START_SEC_VAR_NOINIT
#define API_START_SEC_CODE
#include "MemMap.h"

/* Variable used to check privileges in Hooks */
int public_memory;

EE_ADDR      stack_pointer_holder;

void error( void )
{
  /* Do nothing; you should add a breakpoint on this function to catch
   * errors */
  EE_tc_debug();
}

unsigned int priority_to_be_generated;

EE_TYPEASSERTVALUE EE_assertions[33];

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
  /* TODO: manca IDs of OS-Applications */
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
  MemoryStartAddressType volatile UserApp1ISRTOS = EE_tc_system_tos[EE_as_Application_ROM[UserApp1].ISRTOS].ram_tos;
  MemoryStartAddressType volatile TrustedApp2ISRTOS = EE_tc_system_tos[EE_as_Application_ROM[TrustedApp2].ISRTOS].ram_tos;

  ActivateTask(TaskApp1Prio6);
  WaitEvent(DummyEvent);

  assert ( UserApp1ISRTOS == EE_tc_system_tos[EE_as_Application_ROM[UserApp1].ISRTOS].ram_tos );
  assert ( TrustedApp2ISRTOS == EE_tc_system_tos[EE_as_Application_ROM[TrustedApp2].ISRTOS].ram_tos );

  /* This shall not never return */
  ShutdownOS( E_OK );
  error( );

}

#ifdef __DCC__
void EE_TC_CHANGE_STACK_POINTER App1Isr1 ( void )
#else  /* __DCC__ */
ISR2(App1Isr1)
#endif /* __DCC__ */
{
  extern EE_STACK_T EE_tc_stack_5[EE_STACK_WLEN(256)];
  StatusType s;
  char grab_stack[8];
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App1Isr2;

  s = TerminateApplication(TrustedApp2, RESTART);
  assert( s == E_OS_ACCESS );
  stack_pointer_holder =  EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_5) < stack_pointer_holder) && (stack_pointer_holder <= EE_STACK_INITP(EE_tc_stack_5)));

  call_stack1();
  error();
  really_grab_the_stack(grab_stack);
  priority_to_be_generated = grab_stack[1];

}

#ifdef __DCC__
void EE_TC_CHANGE_STACK_POINTER App1Isr2 ( void )
#else  /* __DCC__ */
ISR2(App1Isr2)
#endif /* __DCC__ */
{
  EE_ADDR sp;
  extern EE_STACK_T EE_tc_stack_5[EE_STACK_WLEN(256)];
  char grab_stack[8];
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = EE_ISR2_ID_App2Isr3;
  sp =  EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_5) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_5)));
  assert ( sp < stack_pointer_holder );
  call_stack1();
  error();
  really_grab_the_stack(grab_stack);
  priority_to_be_generated = grab_stack[1];

}
#ifdef __DCC__
void EE_TC_CHANGE_STACK_POINTER App2Isr3 ( void )
#else  /* __DCC__ */
ISR2(App2Isr3)
#endif /* __DCC__ */
{
  extern EE_STACK_T EE_tc_stack_6[EE_STACK_WLEN(256)];
  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_6) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_6)));
  /* Software IRQ can be fired only by TRUSTED Code (Supervisor mode): It's a
     TriCore Architectural Costraint (Write Accesses to Interrupt Router
     registers is granted only in Suoervisormode). */
  priority_to_be_generated = 0;

  call_stack1();
  /* Check auto TerminateISR2 */
}

void EE_TC_CHANGE_STACK_POINTER StartupHook_UserApp1 ( void ) {
  extern EE_STACK_T EE_tc_stack_5[EE_STACK_WLEN(256)];

  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_5) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_5)));

  ApplicationType volatile app = EE_tc_get_psw();
  app &= ((EE_UREG)0x3U << 12U);
  app >>= 12U;
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 1 );
  assert( !OSMEMORY_IS_WRITEABLE(access) );

  ++public_memory;
}

void EE_TC_CHANGE_STACK_POINTER StartupHook_TrustedApp2 ( void ) {
  extern EE_STACK_T EE_tc_stack_6[EE_STACK_WLEN(256)];

  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_6) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_6)));

  ApplicationType app = EE_TC_READ_PSW_PSR(EE_tc_get_psw());
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 2 );
  assert( OSMEMORY_IS_WRITEABLE(access) );

  ++trusted_memory;
  ++public_memory;
}

void EE_TC_CHANGE_STACK_POINTER StartupHook ( void ) {
  /* User Stack end */
  extern EE_STACK_T EE_E_USTACK[];
  /* User Stack Base. */
  extern EE_STACK_T EE_B_USTACK[];

  EE_ADDR sp = EE_tc_get_SP();
  assert(((EE_ADDR)EE_B_USTACK < sp) && (sp <= (EE_ADDR)EE_E_USTACK));

  ApplicationType app = EE_TC_READ_PSW_PSR(EE_tc_get_psw());
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 0 );
  assert( OSMEMORY_IS_WRITEABLE(access) );

  ++trusted_memory;
  ++public_memory;
}

void EE_TC_CHANGE_STACK_POINTER ShutdownHook_TrustedApp2 ( StatusType Error ) {
  extern EE_STACK_T EE_tc_stack_6[EE_STACK_WLEN(256)];

  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_6) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_6)));

  ApplicationType app = EE_TC_READ_PSW_PSR(EE_tc_get_psw());
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 2 );
  assert( OSMEMORY_IS_WRITEABLE(access) );

  ++trusted_memory;
  ++public_memory;
}

void EE_TC_CHANGE_STACK_POINTER ShutdownHook_UserApp1 ( StatusType Error ) {
  extern EE_STACK_T EE_tc_stack_5[EE_STACK_WLEN(256)];

  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_5) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_5)));

  ApplicationType app = EE_TC_READ_PSW_PSR(EE_tc_get_psw());
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 1 );
  assert( !OSMEMORY_IS_WRITEABLE(access) );

  ++public_memory;
}

void EE_TC_CHANGE_STACK_POINTER ShutdownHook ( StatusType Error ) {
  extern EE_STACK_T EE_tc_stack_4[EE_STACK_WLEN(256)];

  EE_ADDR sp = EE_tc_get_SP();
  assert((EE_STACK_ENDP(EE_tc_stack_4) < sp) && (sp <= EE_STACK_INITP(EE_tc_stack_4)));

  ApplicationType app = EE_TC_READ_PSW_PSR(EE_tc_get_psw());
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 2 );
  assert( OSMEMORY_IS_WRITEABLE(access) );

  ++trusted_memory;
  ++public_memory;

  assert( public_memory == 6 );
  assert( trusted_memory == 4 );

  EE_assert_range(0, 1, assert_count); 
  EE_assert_last();
}

void ErrorHook ( StatusType Error ) {
  /* TODO */
}

void ErrorHook_UserApp1 ( StatusType Error ) {
  /* TODO */
}

void ErrorHook_TrustedApp2 ( StatusType Error ) {
  /* TODO */
}


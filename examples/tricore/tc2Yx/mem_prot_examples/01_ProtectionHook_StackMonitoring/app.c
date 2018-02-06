#include "ee_internal.h"
#include "test.h"

/* Just used to force the compiler to allocate stack */
extern void really_grab_the_stack ( char * stack_grabber );

/* Variable used to check privileges in Hooks */
int trusted_memory;

#define API_START_SEC_VAR_NOINIT
#define API_START_SEC_CODE
#include "MemMap.h"

/* Variable used to check privileges in Hooks */
int public_memory;

EE_ADDR      stack_pointer_holder;

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

void EE_TC_CHANGE_STACK_POINTER ShutdownHook ( StatusType Error ) {
  ApplicationType app = EE_TC_READ_PSW_PSR(EE_tc_get_psw());
  AccessType access = EE_hal_get_app_mem_access(app,
    &trusted_memory, sizeof(trusted_memory));
  assert ( app == 0 );
  assert( OSMEMORY_IS_WRITEABLE(access) );
#ifdef EE_TERMINATETASKISR_TEST
  assert( Error == E_OK);
#else /* EE_TERMINATETASKISR_TEST */
  assert( Error == E_OS_STACKFAULT);
#endif /* EE_TERMINATETASKISR_TEST */
  EE_assert_range(0, 1, assert_count); 
  EE_assert_last();
}

ProtectionReturnType ProtectionHook (StatusType FatalError) {
  assert( FatalError == E_OS_STACKFAULT );
#ifdef EE_TERMINATETASKISR_TEST
  return PRO_TERMINATETASKISR;
#else /* EE_TERMINATETASKISR_TEST */
  return PRO_IGNORE;
#endif /* EE_TERMINATETASKISR_TEST */
}

TASK(TaskApp1Prio1)
{
  /* Grab all the reserved stack */
  char grab_stack[257
#ifdef __DCC__
  /* Stupid DIAB compiler use 44 byte of RAM in ActiveTask primitive */
   - 44
#endif /* __DCC__ */
  ];
  StatusType s;
  s = ActivateTask(TaskApp1Prio2);
  error();
  really_grab_the_stack(grab_stack);
  TerminateTask();
}

TASK(TaskApp1Prio2)
{
#ifndef EE_TERMINATETASKISR_TEST
  error();
#endif /* EE_TERMINATETASKISR_TEST*/
  TerminateTask();
}

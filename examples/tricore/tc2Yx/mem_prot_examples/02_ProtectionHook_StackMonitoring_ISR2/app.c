#include "ee_internal.h"
#include "test.h"
#include "test_irq.h"

/* Just used to force the compiler to allocate stack */
extern void really_grab_the_stack ( char * stack_grabber );

#define APP_UserApp1_START_SEC_VAR_NOINIT
#include "MemMap.h"
/* ProtectionHook Counter. Put in these section to be read by UserApp1 */
unsigned int protection_counter;
#define APP_UserApp1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define API_START_SEC_VAR_NOINIT
#define API_START_SEC_CODE
#include "MemMap.h"

EE_TYPEASSERTVALUE EE_assertions[6];

static int assert_count = EE_ASSERT_NIL;
static void __NEVER_INLINE__ assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}
#define API_STOP_SEC_VAR_NOINIT
#define API_STOP_SEC_CODE
#include "MemMap.h"

ProtectionReturnType ProtectionHook (StatusType FatalError) {
  ++protection_counter;
  assert( FatalError == E_OS_STACKFAULT );
#ifdef EE_TERMINATETASKISR_TEST
  return PRO_TERMINATETASKISR;
#else /* EE_TERMINATETASKISR_TEST */
  return PRO_TERMINATEAPPL;
#endif /* EE_TERMINATETASKISR_TEST */
}

TASK(TaskApp2Prio1)
{
  MemoryStartAddressType volatile UserApp1ISRTOS = EE_tc_system_tos[EE_as_Application_ROM[UserApp1].ISRTOS].ram_tos;
  MemoryStartAddressType volatile UserApp2ISRTOS = EE_tc_system_tos[EE_as_Application_ROM[UserApp2].ISRTOS].ram_tos;

  ActivateTask(TaskApp1Prio2);

#ifdef EE_TERMINATETASKISR_TEST
  assert( protection_counter == 2U );
#else /* EE_TERMINATETASKISR_TEST */
  assert( protection_counter == 1U );
#endif /* EE_TERMINATETASKISR_TEST */

 assert ( UserApp1ISRTOS == EE_tc_system_tos[EE_as_Application_ROM[UserApp1].ISRTOS].ram_tos );
 assert ( UserApp2ISRTOS == EE_tc_system_tos[EE_as_Application_ROM[UserApp2].ISRTOS].ram_tos );

  EE_assert_range(0, 1, assert_count); 
  EE_assert_last();
  TerminateTask();
}

TASK(TaskApp1Prio2)
{

  test_fire_irq(EE_ISR2_ID_App1Isr1);
#ifndef EE_TERMINATETASKISR_TEST
  error();
#endif /* EE_TERMINATETASKISR_TEST */
  TerminateTask();
}

ISR(App1Isr1) {
  char stack_grabber[257];
  test_fire_irq(EE_ISR2_ID_App2Isr2);
  error();
  really_grab_the_stack(stack_grabber);
}

ISR(App2Isr2) {
  test_fire_irq(EE_ISR2_ID_App1Isr3);
};

ISR(App1Isr3) {
  error();
};

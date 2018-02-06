#include "test.h"

#ifdef __EE_MEMORY_PROTECTION__
#define APP_App1_START_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /*__EE_MEMORY_PROTECTION__ */
EE_TYPEASSERTVALUE EE_assertions[EE_MAX_ASSERTIONS];

unsigned char volatile  cycle_stop;
TickType      volatile  g_remaning_budget;
#ifdef __EE_MEMORY_PROTECTION__
#define APP_App1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /*__EE_MEMORY_PROTECTION__ */

#ifdef __EE_MEMORY_PROTECTION__
#define APP_App1_START_SEC_DATA
#include "MemMap.h"
#endif /*__EE_MEMORY_PROTECTION__ */
unsigned int volatile assert_count = EE_ASSERT_NIL;
#ifdef __EE_MEMORY_PROTECTION__
#define APP_App1_STOP_SEC_DATA
#include "MemMap.h"
#endif /*__EE_MEMORY_PROTECTION__ */

void __NEVER_INLINE__ test_assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

void ShutdownHook ( StatusType Error ) {
  TickType loc_remaining_budget =
    EE_as_tp_budget_data[EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->
      execution_budget_index].remaining_budget;

  test_assert( EE_as_tp_active.active_tp == INVALID_TIMING_PROTECTION );
  test_assert( loc_remaining_budget < g_remaning_budget );
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U);

#ifdef EE_TEST_FINISHED_WITH_TP_ERROR
  test_assert( Error == E_OS_PROTECTION_LOCKED );
#else /* EE_TEST_FINISHED_WITH_TP_ERROR */
  test_assert( Error == E_OK );
#endif /* EE_TEST_FINISHED_WITH_TP_ERROR */

  EE_assert_range(0, 1, assert_count);
  EE_assert_last();
}

TASK(TaskPrio2) {
  TickType loc_remaining_budget =
    EE_as_tp_budget_data[EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->
      execution_budget_index].remaining_budget;

  test_assert( EE_as_tp_active.active_tp == INVALID_TIMING_PROTECTION );
  test_assert( loc_remaining_budget < g_remaning_budget );
  /* If the Reclamation Time Frames Budget is active the TP timer is active in
     any case */
#ifndef EE_NO_RECLAMATION_TIME_FRAMES
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0U);
#else /* !EE_NO_RECLAMATION_TIME_FRAMES */
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U);
#endif /* !EE_NO_RECLAMATION_TIME_FRAMES */

  g_remaning_budget = loc_remaining_budget;

  /* Unlock TaskPrio1 */
  cycle_stop = 1;
  TerminateTask();
}

TASK(TaskPrio1) {
  BudgetType            volatile budget_id;
  TimingProtectionType  volatile tp_id;
  TickType              volatile loc_remaining_budget;

  tp_id = EE_as_tp_active.active_tp;
  budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;
  loc_remaining_budget = EE_as_tp_budget_data[EE_as_tp_ROM_refs[
    EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->execution_budget_index].remaining_budget;

  test_assert( tp_id == EE_AS_TP_ID_FROM_TASK(TaskPrio1) );
  test_assert( EE_as_tp_RAM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)] ==
    EE_as_tp_active.active_tp_RAM_ref );
  test_assert( EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)] ==
    EE_as_tp_active.active_tp_ROM_ref );
  test_assert( budget_id == EE_as_tp_active.
    active_tp_ROM_ref->execution_budget_index );

  test_assert( loc_remaining_budget == EE_as_tp_budget_data[EE_as_tp_active.
    active_tp_ROM_ref->execution_budget_index].remaining_budget );

  test_assert( loc_remaining_budget > EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0));
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

  g_remaning_budget = loc_remaining_budget;


  {
    TickType local_res_budget;
    /* Get the Res scheduler */
    GetResource(RES_SCHEDULER);

    budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;
    local_res_budget = EE_as_tp_budget_data[budget_id].remaining_budget;

    test_assert( (*EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->
      resources_lock_budgets_ref)[RES_SCHEDULER] == budget_id );
    test_assert( EE_as_tp_budget_confs[budget_id].budget_value >
      local_res_budget );
    test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) <
      local_res_budget);
    test_assert(EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

    /* OS interrupts doesn't exist */
    SuspendOSInterrupts();

    budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;

    test_assert( EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->
      all_isr_lock_budget_index == budget_id );
    test_assert( EE_as_tp_budget_confs[budget_id].budget_value == 
      EE_as_tp_budget_data[budget_id].remaining_budget);
    test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) <
      EE_as_tp_budget_data[budget_id].remaining_budget);
    test_assert(EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

    ResumeOSInterrupts();

    budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;

    test_assert( EE_as_tp_budget_data[budget_id].remaining_budget <
      local_res_budget );
    test_assert( (*EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->
      resources_lock_budgets_ref)[RES_SCHEDULER] == budget_id );
    test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) <
      EE_as_tp_budget_data[budget_id].remaining_budget);
    test_assert(EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

    ReleaseResource(RES_SCHEDULER);

    tp_id = EE_as_tp_active.active_tp;
    budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;
    loc_remaining_budget = EE_as_tp_budget_data[EE_as_tp_ROM_refs[
      EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->execution_budget_index].
        remaining_budget;

    test_assert( budget_id == EE_as_tp_active.
      active_tp_ROM_ref->execution_budget_index );

    test_assert( loc_remaining_budget == EE_as_tp_budget_data[budget_id].
      remaining_budget );

    test_assert( loc_remaining_budget > EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0));
    test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

    g_remaning_budget = loc_remaining_budget;
  }

  while ( !cycle_stop ) {
    ; /* Just wait... */
  }

  tp_id = EE_as_tp_active.active_tp;
  budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;
  loc_remaining_budget = EE_as_tp_budget_data[EE_as_tp_ROM_refs[
    EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->execution_budget_index].remaining_budget;

  test_assert( tp_id == EE_AS_TP_ID_FROM_TASK(TaskPrio1) );
  test_assert( EE_as_tp_RAM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)] ==
    EE_as_tp_active.active_tp_RAM_ref );
  test_assert( EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)] ==
    EE_as_tp_active.active_tp_ROM_ref );
  test_assert( budget_id == EE_as_tp_active.active_tp_ROM_ref->
    execution_budget_index );
#ifndef EE_AS_OSAPPLICATIONS__
  /* If OSApplication are not used after the tick interrupt the TASk is
     restored without get budget */
  test_assert( loc_remaining_budget == g_remaning_budget );
#else /* !EE_AS_OSAPPLICATIONS__ */
  /* If OSApplication are used EE_as_TerminateISR2 eat some budget! */
  test_assert( loc_remaining_budget < g_remaning_budget );
#endif /* !EE_AS_OSAPPLICATIONS__ */
  test_assert( loc_remaining_budget > EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0));
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

  g_remaning_budget = loc_remaining_budget;

  WaitEvent(EventTaskPrio1);

  tp_id = EE_as_tp_active.active_tp;
  budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;
  loc_remaining_budget = EE_as_tp_budget_data[EE_as_tp_ROM_refs[
    EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->execution_budget_index].remaining_budget;

  test_assert( tp_id == EE_AS_TP_ID_FROM_TASK(TaskPrio1) );
  test_assert( EE_as_tp_RAM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)] ==
    EE_as_tp_active.active_tp_RAM_ref );
  test_assert( EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)] ==
    EE_as_tp_active.active_tp_ROM_ref );
  test_assert( budget_id == EE_as_tp_active.active_tp_ROM_ref->
    execution_budget_index );

  test_assert( loc_remaining_budget > g_remaning_budget );
  test_assert( loc_remaining_budget > EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0));
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0);

  g_remaning_budget = loc_remaining_budget;

#ifdef EE_TEST_FINISHED_WITH_TP_ERROR
  /* Check that this can interrupt a TASK in a CriticalSection */
  DisableAllInterrupts();

  budget_id = EE_as_tp_active.active_tp_RAM_ref->first_expiring;

  test_assert( EE_as_tp_ROM_refs[EE_AS_TP_ID_FROM_TASK(TaskPrio1)]->
    all_isr_lock_budget_index == budget_id );
  test_assert( EE_as_tp_budget_confs[budget_id].budget_value == 
    EE_as_tp_budget_data[budget_id].remaining_budget);
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) <
    EE_as_tp_budget_data[budget_id].remaining_budget);

  while ( 1 ) {
    ;
  }
#else  /* EE_TEST_FINISHED_WITH_TP_ERROR */
  ShutdownOS(E_OK);
#endif /* EE_TEST_FINISHED_WITH_TP_ERROR */

  TerminateTask();
}


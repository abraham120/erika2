#include "test.h"

#if (!defined(EE_AS_OSAPPLICATIONS__)) && (!defined(EE_TEST_FINISHED_WITH_TP_ERROR))
#error If you OSApplications are not configured you need to terminate this test with a TP Error
#endif /* !EE_AS_OSAPPLICATIONS__ && !EE_TEST_FINISHED_WITH_TP_ERROR */

EE_TYPEASSERTVALUE EE_assertions[EE_MAX_ASSERTIONS];
unsigned int volatile assert_count = EE_ASSERT_NIL;

void __NEVER_INLINE__ test_assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

int main( void )
{
  /* Init IRQ button */
  EE_tc2x5_button_irq_init(EE_ISR2_ID_button_handler);
  /* Init leds */
  EE_tc2x5_leds_init();

  StartOS(OSDEFAULTAPPMODE);

#ifdef EE_AS_OSAPPLICATIONS__
  test_assert(EE_as_active_app == KERNEL_OSAPPLICATION);
#endif /* EE_AS_OSAPPLICATIONS__ */
  test_assert(EE_as_tp_active.active_tp == INVALID_TIMING_PROTECTION);

#ifndef EE_NO_RECLAMATION_TIME_FRAMES
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0U);
#else /* !EE_NO_RECLAMATION_TIME_FRAMES */
  test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U);
#endif /* !EE_NO_RECLAMATION_TIME_FRAMES */

#ifdef EE_AS_OSAPPLICATIONS__
  while ( EE_as_Application_RAM[App1].ApplState == APPLICATION_ACCESSIBLE )
  {
    if ( EE_as_active_app != KERNEL_OSAPPLICATION ) {
      error();
    }
    if (EE_as_tp_active.active_tp != INVALID_TIMING_PROTECTION) {
      error();
    }
#ifndef EE_NO_RECLAMATION_TIME_FRAMES
    /* To handle the case where the TP Trap is exactly after TPS read */
    if( (EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U) && (EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U) )
#else /* !EE_NO_RECLAMATION_TIME_FRAMES */
    if( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0U )
#endif /* !EE_NO_RECLAMATION_TIME_FRAMES */
    {
      error();
    }
  }
#else /* EE_AS_OSAPPLICATIONS__ */
  while ( 1 ) {
#ifndef EE_NO_RECLAMATION_TIME_FRAMES
    /* To handle the case where the TP Trap is exactly after TPS read */
    if( (EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U) && (EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U) )
#else /* !EE_NO_RECLAMATION_TIME_FRAMES */
    if( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0U )
#endif /* !EE_NO_RECLAMATION_TIME_FRAMES */
    {
      error();
    }
  }
#endif /* EE_AS_OSAPPLICATIONS__ */
  ShutdownOS(E_OK);
  return 0;
}

#ifdef EE_SUPPORT_MEMMAP_H
#define APP_App1_START_SEC_CODE
#define APP_App1_START_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

EE_UREG button_pressed_once;
EE_UREG interarrival_count;
EE_UREG activation_counter;
EE_UREG release_counter;

static void led_blink(enum EE_tc2x5_led_id theled, EE_UREG usec)
{
  //EE_UREG start, ticks;
  DisableAllInterrupts();
  EE_tc2x5_set_leds_mask(theled);
  EnableAllInterrupts();

  //ticks = usec * (EE_CPU_CLOCK / EE_MEGA);
  //start = EE_hal_swfrt_get_current_time();
  EE_tc2Yx_delay(usec);
  /* while ( ticks > EE_hal_swfrt_get_current_time() - start ) {
    ;
  }*/

  DisableAllInterrupts();
  EE_tc2x5_set_leds_mask(EE_TRIBOARD_2X5_NO_LEDS);
  EnableAllInterrupts();
}

ProtectionReturnType ProtectionHook ( StatusType FatalError ) {
  if ( FatalError == E_OS_PROTECTION_ARRIVAL )
  {
    ++interarrival_count;
    return PRO_IGNORE;
  } else {
    if ( button_pressed_once ) {
      test_assert(interarrival_count == 3);
      test_assert(release_counter == 3);
      test_assert(activation_counter == 3);
#ifdef EE_TEST_FINISHED_WITH_TP_ERROR
      return PRO_SHUTDOWN;
#else /* EE_TEST_FINISHED_WITH_TP_ERROR */
      return PRO_TERMINATEAPPL;
#endif /* EE_TEST_FINISHED_WITH_TP_ERROR */
    } else {
      test_assert(release_counter == 2);
      test_assert(activation_counter == 2);
      test_assert(interarrival_count == 2);
      return PRO_TERMINATETASKISR;
    }
  }
}

void ShutdownHook ( StatusType Error ) {

  test_assert(EE_as_tp_active.active_tp == INVALID_TIMING_PROTECTION);
  test_assert(EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U);

#ifdef EE_TEST_FINISHED_WITH_TP_ERROR
  test_assert( Error == E_OS_PROTECTION_TIME );
#else /* EE_TEST_FINISHED_WITH_TP_ERROR */
  test_assert( Error == E_OK );
#endif /* EE_TEST_FINISHED_WITH_TP_ERROR */

  EE_assert_range(0, 1, assert_count);
  EE_assert_last();
}

ISR(button_handler) {
  ActivateTask(TaskPrio2);
  if ( button_pressed_once ) {
    /* This will cause the execution budget to expire */
    led_blink(EE_TRIBOARD_2X5_ALL_LEDS, 5500);
  } else {
    led_blink(EE_TRIBOARD_2X5_ALL_LEDS, 4000);
    button_pressed_once = EE_TRUE;
  }
}

TASK(TaskPrio2) {
  ++activation_counter;
  if ( activation_counter == 1U) {
#ifdef EE_AS_OSAPPLICATIONS__
    test_assert(EE_as_active_app == App1);
#endif /* EE_AS_OSAPPLICATIONS__ */
    test_assert(EE_as_tp_active.active_tp == EE_AS_TP_ID_FROM_TASK(TaskPrio2));
    test_assert(EE_as_tp_active.active_tp_RAM_ref->first_expiring ==
      EE_as_tp_active.active_tp_ROM_ref->execution_budget_index);

    test_assert( EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0U);

  } else {
#ifdef EE_AS_OSAPPLICATIONS__
    if ( EE_as_active_app != App1 ) {
      error();
    }
#endif /* EE_AS_OSAPPLICATIONS__ */
    if (EE_as_tp_active.active_tp != EE_AS_TP_ID_FROM_TASK(TaskPrio2)) {
      error();
    }
    if ( EE_as_tp_active.active_tp_RAM_ref->first_expiring !=
      EE_as_tp_active.active_tp_ROM_ref->execution_budget_index )
    {
      error();
    }
#ifdef EE_AS_OSAPPLICATIONS__
    if (EE_as_Application_RAM[App1].ApplState != APPLICATION_ACCESSIBLE)
    {
      error();
    }
#endif /* EE_AS_OSAPPLICATIONS__ */
    if (EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U)
    {
      error();
    }
  }

  SetEvent(TaskPrio1,EventTaskPrio1);
  TerminateTask();
}

TASK(TaskPrio1) {
#ifdef EE_AS_OSAPPLICATIONS__
  test_assert(EE_as_active_app == App1);
#endif /* EE_AS_OSAPPLICATIONS__ */
  test_assert(EE_as_tp_active.active_tp == EE_AS_TP_ID_FROM_TASK(TaskPrio1));
  test_assert(EE_as_tp_active.active_tp_RAM_ref->first_expiring == 
    EE_as_tp_active.active_tp_ROM_ref->execution_budget_index);
  test_assert(EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) != 0U);

  while ( 1 ) {
    ++release_counter;
#ifdef EE_AS_OSAPPLICATIONS__
    if ( EE_as_active_app != App1 ) {
      error();
    }
#endif /* EE_AS_OSAPPLICATIONS__ */
    if (EE_as_tp_active.active_tp != EE_AS_TP_ID_FROM_TASK(TaskPrio1)) {
      error();
    }
    if ( EE_as_tp_active.active_tp_RAM_ref->first_expiring !=
      EE_as_tp_active.active_tp_ROM_ref->execution_budget_index )
    {
      error();
    }
#ifdef EE_AS_OSAPPLICATIONS__
    if (EE_as_Application_RAM[App1].ApplState != APPLICATION_ACCESSIBLE)
    {
      error();
    }
#endif /* EE_AS_OSAPPLICATIONS__ */
    if (EE_tc_get_csfr(EE_CPU_REG_TPS_TIMER0) == 0U)
    {
      error();
    }
    WaitEvent(EventTaskPrio1);
    ClearEvent(EventTaskPrio1);
  }

  TerminateTask();
}

#ifdef EE_SUPPORT_MEMMAP_H
#define APP_App1_STOP_SEC_CODE
#define APP_App1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */


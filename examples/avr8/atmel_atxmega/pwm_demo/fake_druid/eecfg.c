#include "ee.h"



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskL1);
    DeclareTask(TaskL2);
    DeclareTask(TaskL3);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &FuncTaskL1,		/* thread TaskL1 */
        &FuncTaskL2,		/* thread TaskL2 */
        &FuncTaskL3 		/* thread TaskL3 */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		/* thread TaskL1 */
        0x2U,		/* thread TaskL2 */
        0x4U 		/* thread TaskL3 */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		/* thread TaskL1 */
        0x2U,		/* thread TaskL2 */
        0x4U 		/* thread TaskL3 */
    };

    /* thread status */
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY,
            EE_READY
        };
    #endif

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL,
        EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* The first task into the ready queue */
    EE_TID EE_rqfirst  = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;



/***************************************************************************
 *
 * Counters
 *
 **************************************************************************/
    EE_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
        {0, -1},         /* Counter400us */
        {0, -1}          /* Counter1ms   */
    };



/***************************************************************************
 *
 * Alarms
 *
 **************************************************************************/
    const EE_alarm_ROM_type   EE_alarm_ROM[] = {
        {0, EE_ALARM_ACTION_TASK    , TaskL1, NULL},
        {0, EE_ALARM_ACTION_TASK    , TaskL2, NULL},
        {1, EE_ALARM_ACTION_TASK    , TaskL3, NULL}
    };

    EE_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];


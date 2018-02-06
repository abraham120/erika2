#include "ee.h"



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskTxOk);
    DeclareTask(TaskRxOk);
    DeclareTask(TaskRxErr);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &FuncTaskTxOk,		/* thread TaskTxOk */
        &FuncTaskRxOk,		/* thread TaskRxOk */
        &FuncTaskRxErr 		/* thread TaskRxErr */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		/* thread TaskTxOk */
        0x2U,		/* thread TaskRxOk */
        0x1U 		/* thread TaskRxErr */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		/* thread TaskTxOk */
        0x2U,		/* thread TaskRxOk */
        0x1U 		/* thread TaskRxErr */
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


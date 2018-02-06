
#include "ee.h"


#include "ee.h"


/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Sender);
    DeclareTask(LwipReceive);
    DeclareTask(LwipPeriodic);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncSender,		/* thread Sender */
        (EE_FADDR)FuncLwipReceive,		/* thread LwipReceive */
        (EE_FADDR)FuncLwipPeriodic 		/* thread LwipPeriodic */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		/* thread Sender */
        0x2U,		/* thread LwipReceive */
        0x4U 		/* thread LwipPeriodic */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		/* thread Sender */
        0x2U,		/* thread LwipReceive */
        0x4U 		/* thread LwipPeriodic */
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
 * Mutex
 *
 **************************************************************************/
    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
        0x4U,		/* resource LwipMutex */
        0x4U 		/* resource RES_SCHEDULER */
    };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];



/***************************************************************************
 *
 * Counters
 *
 **************************************************************************/
    EE_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
        {0, -1}         /* SenderCounter */
    };



/***************************************************************************
 *
 * Alarms
 *
 **************************************************************************/
    const EE_alarm_ROM_type   EE_alarm_ROM[] = {
        {0, EE_ALARM_ACTION_TASK    , Sender, NULL}
    };

    EE_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];


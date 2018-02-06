#include "ee.h"



/***************************************************************************
 *
 * Stack definition for CORTEX M0
 *
 **************************************************************************/


    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0U,	 /* dummy*/
        0U,	 /* Task1*/
        0U 	 /* Task2*/
    };

    struct EE_TOS EE_cortex_mx_system_tos[1] = {
        {0} 	/* Task   (dummy), Task 0 (Task1), Task 1 (Task2) */
    };

    EE_UREG EE_cortex_mx_active_tos = 0U; /* dummy */



// STACK configuration











struct EE_TOS EE_std_system_tos[1] = {
        {0}, /* shared */
};


EE_UREG EE_std_active_tos = 0U; /* dummy */


/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &FuncTask1,		/* thread Task1 */
        &FuncTask2 		/* thread Task2 */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		/* thread Task1 */
        0x2U 		/* thread Task2 */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		/* thread Task1 */
        0x2U 		/* thread Task2 */
    };

    /* thread status */
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY
        };
    #endif

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
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


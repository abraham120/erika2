#include "ee.h"



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &EE_oo_thread_stub,		 /* thread Task1 */
        &EE_oo_thread_stub 		 /* thread Task2 */

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_THREAD_PTR EE_terminate_real_th_body[EE_MAX_TASK] = {
        &FuncTask1,
        &FuncTask2
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread Task1 */
        0x2U 		 /* thread Task2 */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x2U,		 /* thread Task1 */
        0x2U 		 /* thread Task2 */
    };

    /* thread status */
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED
    };

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;

    /* The priority queues: (8 priorities maximum!) */
    EE_TYPEPAIR EE_rq_queues_head[EE_RQ_QUEUES_HEAD_SIZE] =
        { -1, -1, -1, -1, -1, -1, -1, -1};
    EE_TYPEPAIR EE_rq_queues_tail[EE_RQ_QUEUES_TAIL_SIZE] =
        { -1, -1, -1, -1, -1, -1, -1, -1};

    EE_TYPE_RQ_MASK  EE_rq_bitmask = 0U;

    /* remaining nact: init= maximum pending activations of a Task */
    EE_TYPENACT EE_th_rnact[EE_MAX_TASK] = {
        1U,		 /* thread Task1 */
        4U		 /* thread Task2 */
    };

    const EE_TYPENACT EE_th_rnact_max[EE_MAX_TASK] = {
        1U,		 /* thread Task1 */
        4U		 /* thread Task2 */
    };

    EE_TYPEPRIO EE_rq_link[EE_MAX_TASK] =
        { 0U, 1U};

    /* The pairs that are enqueued into the priority queues (5 is the total number of task activations) */
    EE_TYPEPAIR EE_rq_pairs_next[EE_RQ_PAIRS_NEXT_SIZE] =
        { 1, 2, 3, 4, -1};

    /* no need to be initialized */
    EE_TID EE_rq_pairs_tid[EE_RQ_PAIRS_TID_SIZE];

    /* a list of unused pairs */
    EE_TYPEPAIR EE_rq_free = 0; /* pointer to a free pair */

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL
        };
    #endif



/***************************************************************************
 *
 * AppMode
 *
 **************************************************************************/
    EE_TYPEAPPMODE EE_ApplicationMode;


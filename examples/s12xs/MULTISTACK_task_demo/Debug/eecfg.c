#include "ee.h"



/***************************************************************************
 *
 * Stack definition for Freescale S12
 *
 **************************************************************************/
    #define STACK_1_SIZE 64 // size = 128 bytes 
    #define STACK_2_SIZE 64 // size = 128 bytes 
    #define STACK_3_SIZE 64 // size = 128 bytes 

    int EE_s12xs_stack_1[STACK_1_SIZE];	// Task 0 (Task1)
    int EE_s12xs_stack_2[STACK_2_SIZE];	// Task 1 (Task2)
    int EE_s12xs_stack_3[STACK_3_SIZE];	// irq stack

    EE_UREG EE_s12xs_thread_tos[EE_MAX_TASK+1] = {
        0U,	// dummy
        1U,	// Task1
        2U 	// Task2
    };

    struct EE_TOS EE_s12xs_system_tos[3] = {
        {0},	// Task   (dummy)
        {(EE_DADD)(&EE_s12xs_stack_1[STACK_1_SIZE -3])},	// Task 0 (Task1)
        {(EE_DADD)(&EE_s12xs_stack_2[STACK_2_SIZE -3])} 	// Task 1 (Task2)
    };

    EE_UREG EE_s12xs_active_tos = 0U; // dummy

    // stack used only by IRQ handlers
    struct EE_TOS EE_s12xs_IRQ_tos = {
        (EE_DADD)(&EE_s12xs_stack_3[STACK_3_SIZE -3])
    };



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)EE_oo_thread_stub,		 /* thread Task1 */
        (EE_FADDR)EE_oo_thread_stub 		 /* thread Task2 */

    };

    EE_UINT16 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_FADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTask1,
        (EE_FADDR)FuncTask2
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread Task1 */
        0x2U 		 /* thread Task2 */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread Task1 */
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

    /* remaining nact: init= maximum pending activations of a Task */
    /* MUST BE 1 for BCC1 and ECC1 */
    EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] =
        { 1U, 1U};

    /* First task in the ready queue (initvalue = EE_NIL) */
    EE_TID EE_rq_first  = EE_NIL;

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL
        };
    #endif



/***************************************************************************
 *
 * Event handling
 *
 **************************************************************************/
    EE_TYPEEVENTMASK EE_th_event_active[EE_MAX_TASK] =
        { 0U, 0U};    /* thread event already active */

    EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
        { 0U, 0U};    /* thread wait mask */

    EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
        { 0U, 0U};

    EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
        { 0U, 0U};



/***************************************************************************
 *
 * AppMode
 *
 **************************************************************************/
    EE_TYPEAPPMODE EE_ApplicationMode;


/***************************************************************************
 *
 * Auto Start (TASK)
 *
 **************************************************************************/
    static const EE_TID EE_oo_autostart_task_mode_OSDEFAULTAPPMODE[1] = 
        { Task2 };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1U, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };


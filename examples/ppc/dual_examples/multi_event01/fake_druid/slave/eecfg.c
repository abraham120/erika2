#include "ee.h"



/***************************************************************************
 *
 * Stack definition for Freescale MPC5668G, PPC e200z0
 *
 **************************************************************************/
    #define STACK_1_SIZE 512 /* size = 512 bytes */
    #pragma section PRAGMA_SECTION_BEGIN_SYS_STACK
    static EE_STACK_T EE_stack_1[EE_STACK_WLEN(STACK_1_SIZE)];	/* Task 0 (TaskZ0Main) */
    #pragma section PRAGMA_SECTION_END_SYS_STACK

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0U,	 /* dummy*/
        1U,	 /* TaskZ0Main*/
        0U 	 /* TaskZ0Bkg*/
    };

    struct EE_TOS EE_e200z7_system_tos[2] = {
        {0},	/* Task  (dummy), Task 1 (TaskZ0Bkg) */
        {(EE_ADDR)(&EE_stack_1[EE_STACK_INITP(STACK_1_SIZE)])} 	/* Task 0 (TaskZ0Main) */
    };

    EE_UREG EE_e200z7_active_tos = 0U; /* dummy */



/***************************************************************************
 *
 * Kernel ( CPU 1 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskZ0Main);
    DeclareTask(TaskZ0Bkg);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &EE_oo_thread_stub,		 /* thread TaskZ0Main */
        &EE_oo_thread_stub 		 /* thread TaskZ0Bkg */

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_THREAD_PTR EE_terminate_real_th_body[EE_MAX_TASK] = {
        &FuncTaskZ0Main,
        &FuncTaskZ0Bkg
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x2U,		 /* thread TaskZ0Main */
        0x1U 		 /* thread TaskZ0Bkg */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x2U,		 /* thread TaskZ0Main */
        0x1U 		 /* thread TaskZ0Bkg */
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
        { 1U, 0U};



/***************************************************************************
 *
 * Mutex
 *
 **************************************************************************/
    /*
     * This is the last mutex that the task has locked. This array
     *    contains one entry for each task. Initvalue= all -1. at runtime,
     *    it points to the first item in the EE_resource_stack data structure.
    */
    EE_UREG EE_th_resource_last[EE_MAX_TASK] =
        { (EE_UREG) -1, (EE_UREG) -1};

    /*
     * This array is used to store a list of resources locked by a
     *    task. there is one entry for each resource, initvalue = -1. the
     *    list of resources locked by a task is ended by -1.
    */
    EE_UREG EE_resource_stack[EE_MAX_RESOURCE] =
        { (EE_UREG) -1};

    /*
     * Only in extended status or when using ORTI with resources; for
     *    each resource, a flag is allocated to see if the resource is locked or
     *    not.  Note that this information cannot be easily knew from the previous
     *    two data structures. initvalue=0
    */
    EE_TYPEBOOL EE_resource_locked[EE_MAX_RESOURCE] =
        { 0U};

    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
        0x2U 		/* resource RES_SCHEDULER */
    };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];



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
        { TaskZ0Main };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1U, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };



#include "ee.h"


/***************************************************************************
 *
 * Stack definition for Freescale MPC5668G, PPC e200z6
 *
 **************************************************************************/


    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0U,	 /* dummy*/
        0U 	 /* TaskZ6*/
    };

    struct EE_TOS EE_e200z7_system_tos[1] = {
        {0} 	/* Task  (dummy), Task 0 (TaskZ6) */
    };

    EE_UREG EE_e200z7_active_tos = 0U; /* dummy */



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskZ6);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)EE_oo_thread_stub 		 /* thread TaskZ6 */

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_FADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTaskZ6
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U 		 /* thread TaskZ6 */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U 		 /* thread TaskZ6 */
    };

    /* thread status */
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED
    };

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL
    };

    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;

    /* remaining nact: init= maximum pending activations of a Task */
    /* MUST BE 1 for BCC1 and ECC1 */
    EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] =
        { 1};

    /* First task in the ready queue (initvalue = EE_NIL) */
    EE_TID EE_rq_first  = EE_NIL;

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL
        };
    #endif



/***************************************************************************
 *
 * Event handling
 *
 **************************************************************************/
    EE_TYPEEVENTMASK EE_th_event_active[EE_MAX_TASK] =
        { 0U};    /* thread event already active */

    EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
        { 0U};    /* thread wait mask */

    EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
        { 0U};

    EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
        { 0U};



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
        { (EE_UREG) -1};

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
        0x1U 		/* resource RES_SCHEDULER */
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
 * ORTI
 *
 **************************************************************************/
    #include "ee.h"

    #ifdef __OO_ORTI_LASTERROR__
        StatusType EE_ORTI_lasterror = E_OK;
    #endif

    #ifdef __OO_ORTI_SERVICETRACE__
        volatile EE_UINT8 EE_ORTI_servicetrace;
    #endif

    EE_TYPEPRIO EE_ORTI_th_priority[1]; /* MAX_TASK = 1 */

    EE_TYPEPRIO EE_ORTI_resource_oldpriority[1]; /* MAX_RESOURCE = 1 */

    EE_UREG EE_ORTI_res_locker[1]; /* MAX_RESOURCE = 1 */


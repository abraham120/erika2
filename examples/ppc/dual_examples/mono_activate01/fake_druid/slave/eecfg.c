#include "ee.h"


/***************************************************************************
 *
 * Kernel ( CPU 1 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskZ0);
    DeclareTask(TaskZ0b);
    DeclareTask(TaskZ0c);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)EE_oo_thread_stub,		 /* thread TaskZ0 */
        (EE_FADDR)EE_oo_thread_stub,		 /* thread TaskZ0b */
        (EE_FADDR)EE_oo_thread_stub 		 /* thread TaskZ0c */

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_FADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTaskZ0,
        (EE_FADDR)FuncTaskZ0b,
        (EE_FADDR)FuncTaskZ0c
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread TaskZ0 */
        0x2U,		 /* thread TaskZ0b */
        0x4U 		 /* thread TaskZ0c */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread TaskZ0 */
        0x2U,		 /* thread TaskZ0b */
        0x4U 		 /* thread TaskZ0c */
    };

    /* thread status */
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED,
        SUSPENDED
    };

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
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
        { 1, 1, 1};

    /* First task in the ready queue (initvalue = EE_NIL) */
    EE_TID EE_rq_first  = EE_NIL;

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL,
            EE_NIL
        };
    #endif



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
        { (EE_UREG) -1, (EE_UREG) -1, (EE_UREG) -1};

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
        0x4U 		/* resource RES_SCHEDULER */
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
        { TaskZ0 };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1U, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };



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

    EE_TYPEPRIO EE_ORTI_th_priority[3]; /* MAX_TASK = 3 */

    EE_TYPEPRIO EE_ORTI_resource_oldpriority[1]; /* MAX_RESOURCE = 1 */

    EE_UREG EE_ORTI_res_locker[1]; /* MAX_RESOURCE = 1 */


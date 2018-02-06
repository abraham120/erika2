#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Kernel ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////
    // Definition of task's body
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_ADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_ADDR)EE_oo_thread_stub,		 // thread Task1
        (EE_ADDR)EE_oo_thread_stub 		 // thread Task2

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    // ip of each thread body (ROM)
    const EE_ADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_ADDR)FuncTask1,
        (EE_ADDR)FuncTask2
    };
    // ready priority
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1,		 // thread Task1
        0x2 		 // thread Task2
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1,		 // thread Task1
        0x2 		 // thread Task2
    };

    // thread status
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED
    };

    // next thread
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    // The first stacked task
    EE_TID EE_stkfirst = EE_NIL;

    // system ceiling
    EE_TYPEPRIO EE_sys_ceiling= 0x0000;

    // remaining nact: init= maximum pending activations of a Task
    // MUST BE 1 for BCC1 and ECC1
    EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] =
        { 1, 1};

    // First task in the ready queue (initvalue = EE_NIL)
    EE_TID EE_rq_first  = EE_NIL;

    #ifndef __OO_NO_CHAINTASK__
        // The next task to be activated after a ChainTask. initvalue=all EE_NIL
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL
        };
    #endif



//////////////////////////////////////////////////////////////////////////////
//  
//   Mutex
//  
/////////////////////////////////////////////////////////////////////////////
    // This is the last mutex that the task has locked. This array
    //    contains one entry for each task. Initvalue= all -1. at runtime,
    //    it points to the first item in the EE_resource_stack data structure.
    EE_UREG EE_th_resource_last[EE_MAX_TASK] =
        { (EE_UREG) -1, (EE_UREG) -1};

    // This array is used to store a list of resources locked by a
    //    task. there is one entry for each resource, initvalue = -1. the
    //    list of resources locked by a task is ended by -1.
    EE_UREG EE_resource_stack[EE_MAX_RESOURCE] =
        { (EE_UREG) -1};

    // Only in extended status or when using ORTI with resources; for
    //    each resource, a flag is allocated to see if the resource is locked or
    //    not.  Note that this information cannot be easily knew from the previous
    //    two data structures. initvalue=0
    EE_TYPEBOOL EE_resource_locked[EE_MAX_RESOURCE] =
        { 0};

    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
        0x2 		// resource Resource
    };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];



//////////////////////////////////////////////////////////////////////////////
//  
//   AppMode
//  
/////////////////////////////////////////////////////////////////////////////
    EE_TYPEAPPMODE EE_ApplicationMode;


#include "ee.h"



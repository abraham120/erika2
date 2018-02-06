
#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Kernel ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////
    // Definition of task's body
    DeclareTask(Task1);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTask1 		// thread Task1

    };

    // ready priority
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1 		// thread Task1
    };

    // dispatch priority
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1 		// thread Task1
    };

    // thread status
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY
        };
    #endif

    // next thread
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
    // The first stacked task
    EE_TID EE_stkfirst = EE_NIL;

    // The first task into the ready queue
    EE_TID EE_rqfirst  = EE_NIL;

    // system ceiling
    EE_TYPEPRIO EE_sys_ceiling= 0x0000;



//////////////////////////////////////////////////////////////////////////////
//  
//   Mutex
//  
/////////////////////////////////////////////////////////////////////////////
    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
     };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];



//////////////////////////////////////////////////////////////////////////////
//  
//   Counters
//  
/////////////////////////////////////////////////////////////////////////////
    EE_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {     };



//////////////////////////////////////////////////////////////////////////////
//  
//   Alarms
//  
/////////////////////////////////////////////////////////////////////////////
    const EE_alarm_ROM_type   EE_alarm_ROM[] = {

    };

    EE_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM];


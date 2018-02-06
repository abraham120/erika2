#include "ee.h"

    
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTask1,		
        (EE_FADDR)FuncTask2 		

    };

    
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		
        0x1U 		
    };

    
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		
        0x1U 		
    };

    
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY
        };
    #endif

    
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
    
    EE_TID EE_stkfirst = EE_NIL;

    
    EE_TID EE_rqfirst  = EE_NIL;

    
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;


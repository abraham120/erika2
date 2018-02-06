
#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Stack definition for Lattice mico 32
//  
/////////////////////////////////////////////////////////////////////////////
    #define STACK_1_SIZE 128 // size = 512 bytes 
    #define STACK_2_SIZE 128 // size = 512 bytes 

#ifndef DEBUG_STACK
    int EE_e200z7_stack_1[STACK_1_SIZE];	/* Task 0 (Task1) */
    int EE_e200z7_stack_2[STACK_2_SIZE];	/* irq stack */
#else
    int EE_me200z7_stack_1[STACK_1_SIZE + E200Z7_STACK_DEBUG_LEN] = 
            E200Z7_STACK_INIT(STACK_1_SIZE);	/* Task 0 (Task1) */
    int EE_e200z7_stack_2[STACK_2_SIZE + E200Z7_STACK_DEBUG_LEN] = 
            E200Z7_STACK_INIT(STACK_2_SIZE);	/* irq stack */
#endif

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0,	 /* dummy*/
        1 	 /* Task1*/
    };

    struct EE_TOS EE_e200z7_system_tos[2] = {
        {0},	/* Task   (dummy) */
        {(EE_ADDR)(&EE_e200z7_stack_1[STACK_1_SIZE - 2])} 	/* Task 0 (Task1) */
    };

    EE_UREG EE_e200z7_active_tos = 0; /* dummy */

    /* stack used only by IRQ handlers */
    struct EE_TOS EE_e200z7_IRQ_tos = {
        (EE_ADDR)(&EE_e200z7_stack_2[STACK_2_SIZE - 2])
    };

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

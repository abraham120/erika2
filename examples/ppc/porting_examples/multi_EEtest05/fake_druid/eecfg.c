
#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Stack definition for Lattice mico 32
//  
/////////////////////////////////////////////////////////////////////////////
    #define STACK_1_SIZE 128 // size = 512 bytes 
    #define STACK_2_SIZE 128 // size = 512 bytes 

#ifndef DEBUG_STACK
    int EE_e200z7_stack_1[STACK_1_SIZE];	/* Task 1 (Task2) */
    int EE_e200z7_stack_2[STACK_2_SIZE];	/* Task 2 (Task3) */
#else
    int EE_e200z7_stack_1[STACK_1_SIZE + E200Z7_STACK_DEBUG_LEN] = 
            E200Z7_STACK_INIT(STACK_1_SIZE);	/* Task 1 (Task2) */
    int EE_e200z7_stack_2[STACK_2_SIZE + E200Z7_STACK_DEBUG_LEN] = 
            E200Z7_STACK_INIT(STACK_2_SIZE);	/* Task 2 (Task3) */
#endif

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0,	 /* dummy*/
        0,	 /* Task1*/
        1,	 /* Task2*/
        2,	 /* Task3*/
        0,	 /* Task4*/
        0,	 /* Task5*/
        0 	 /* Task6*/
    };

    struct EE_TOS EE_e200z7_system_tos[3] = {
        {0},	/* Task   (dummy), Task 0 (Task1), Task 3 (Task4), Task 4 (Task5), Task 5 (Task6) */
        {(EE_ADDR)(&EE_e200z7_stack_1[STACK_1_SIZE - 2])},	/* Task 1 (Task2) */
        {(EE_ADDR)(&EE_e200z7_stack_2[STACK_2_SIZE - 2])} 	/* Task 2 (Task3) */
    };

    EE_UREG EE_e200z7_active_tos = 0; /* dummy */

#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Kernel ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////
    // Definition of task's body
    DeclareTask(Task1);
    DeclareTask(Task2);
    DeclareTask(Task3);
    DeclareTask(Task4);
    DeclareTask(Task5);
    DeclareTask(Task6);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTask1,		// thread Task1
        (EE_FADDR)FuncTask2,		// thread Task2
        (EE_FADDR)FuncTask3,		// thread Task3
        (EE_FADDR)FuncTask4,		// thread Task4
        (EE_FADDR)FuncTask5,		// thread Task5
        (EE_FADDR)FuncTask6 		// thread Task6

    };

    // ready priority
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1,		// thread Task1
        0x2,		// thread Task2
        0x4,		// thread Task3
        0x8,		// thread Task4
        0x10,		// thread Task5
        0x20 		// thread Task6
    };

    // dispatch priority
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1,		// thread Task1
        0x2,		// thread Task2
        0x4,		// thread Task3
        0x8,		// thread Task4
        0x10,		// thread Task5
        0x20 		// thread Task6
    };

    // thread status
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY
        };
    #endif

    // next thread
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
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
    const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= { 0 };

    EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE] = { 0 };



//////////////////////////////////////////////////////////////////////////////
//  
//   Counters
//  
/////////////////////////////////////////////////////////////////////////////
    EE_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = { 0 };



//////////////////////////////////////////////////////////////////////////////
//  
//   Alarms
//  
/////////////////////////////////////////////////////////////////////////////
    const EE_alarm_ROM_type   EE_alarm_ROM[] = { 0 };

    EE_alarm_RAM_type         EE_alarm_RAM[EE_MAX_ALARM] = { 0 };



#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Stack definition for MSP430
//  
/////////////////////////////////////////////////////////////////////////////
    #define STACK_1_SIZE 256 // size = 512 bytes 
    #define STACK_2_SIZE 256 // size = 512 bytes 
    //#define STACK_3_SIZE 256 // size = 512 bytes 

    int EE_msp430_stack_1[STACK_1_SIZE];	/* Task 0 (Task1) */
    int EE_msp430_stack_2[STACK_2_SIZE];	/* Task 1 (Task2) */
  //  int EE_msp430_stack_3[STACK_3_SIZE];	/* irq stack */

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0,	 /* dummy*/
        1,	 /* Task1*/
        2 	 /* Task2*/
    };

    struct EE_TOS EE_msp430_system_tos[3] = {
        {0},	/* Task   (dummy) */
        {(EE_ADDR)(&EE_msp430_stack_1[STACK_1_SIZE-MSP430_INIT_TOS_OFFSET])},	/* Task 0 (Task1) */
        {(EE_ADDR)(&EE_msp430_stack_2[STACK_2_SIZE-MSP430_INIT_TOS_OFFSET])} 	/* Task 1 (Task2) */
    };

    EE_UREG EE_msp430_active_tos = 0; /* dummy */
/* stack used only by IRQ handlers */
 /*  struct EE_TOS EE_msp430_IRQ_tos = {
        (EE_ADDR)(&EE_msp430_stack_3[7])
    };
*/

#include "ee.h"


//////////////////////////////////////////////////////////////////////////////
//  
//   Kernel ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////
    // Definition of task's body
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncTask1,		// thread Task1
        (EE_FADDR)FuncTask2 		// thread Task2

    };

    // ready priority
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1,		// thread Task1
        0x2 		// thread Task2
    };

    // dispatch priority
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1,		// thread Task1
        0x2 		// thread Task2
    };

    // thread status
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY
        };
    #endif

    // next thread
    EE_TID EE_th_next[EE_MAX_TASK] = {
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


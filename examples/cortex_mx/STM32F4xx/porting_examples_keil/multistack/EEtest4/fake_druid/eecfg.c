#include "ee.h"



/***************************************************************************
 *
 * Stack definition for CORTEX M0
 *
 **************************************************************************/
    #define STACK_1_SIZE 128 // size = 512 bytes 
    #define STACK_2_SIZE 128 // size = 512 bytes 
    #define STACK_3_SIZE 128 // size = 512 bytes 

    int EE_cortex_mx_stack_1[STACK_1_SIZE];	/* Task 0 (Task1) */
    int EE_cortex_mx_stack_2[STACK_2_SIZE];	/* Task 1 (Task2) */
    int EE_cortex_mx_stack_3[STACK_3_SIZE];	/* irq stack */

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0U,	 /* dummy*/
        1U,	 /* Task1*/
        2U 	 /* Task2*/
    };

    struct EE_TOS EE_cortex_mx_system_tos[3] = {
        {0},	/* Task   (dummy) */
        {(EE_ADDR)(&EE_cortex_mx_stack_1[STACK_1_SIZE - CORTEX_MX_INIT_TOS_OFFSET])},	/* Task 0 (Task1) */
        {(EE_ADDR)(&EE_cortex_mx_stack_2[STACK_2_SIZE - CORTEX_MX_INIT_TOS_OFFSET])} 	/* Task 1 (Task2) */
    };

    EE_UREG EE_cortex_mx_active_tos = 0U; /* dummy */

    /* stack used only by IRQ handlers */
    struct EE_TOS EE_cortex_mx_IRQ_tos = {
        (EE_ADDR)(&EE_cortex_mx_stack_3[STACK_3_SIZE])
    };



// STACK configuration

#define STACK_IRQ_SIZE 512 
int EE_stack_IRQ[STACK_IRQ_SIZE];

/* stack used only by IRQ handlers */
struct EE_TOS EE_std_IRQ_tos = {
    (EE_ADDR)(&EE_stack_IRQ[STACK_IRQ_SIZE - 1])
};


#define STACK_Task1_ID 1U
#define STACK_Task1_SIZE 512
int EE_stack_Task1[STACK_Task1_SIZE];

#define STACK_Task2_ID 2U
#define STACK_Task2_SIZE 512
int EE_stack_Task2[STACK_Task2_SIZE];











struct EE_TOS EE_std_system_tos[3] = {
        {0}, /* shared */
        {(EE_ADDR)(&EE_stack_Task1[STACK_Task1_SIZE - 1])},
        {(EE_ADDR)(&EE_stack_Task2[STACK_Task2_SIZE - 1])},
};


EE_UREG EE_std_active_tos = 0U; /* dummy */


/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &FuncTask1,		/* thread Task1 */
        &FuncTask2 		/* thread Task2 */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		/* thread Task1 */
        0x2U 		/* thread Task2 */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		/* thread Task1 */
        0x2U 		/* thread Task2 */
    };

    /* thread status */
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY
        };
    #endif

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* The first task into the ready queue */
    EE_TID EE_rqfirst  = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;


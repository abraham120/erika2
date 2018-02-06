#include "ee.h"



/***************************************************************************
 *
 * Stack definition for Freescale MPC5674F, PPC e200z7
 *
 **************************************************************************/
#ifndef USE_PRAGMAS

    #define STACK_1_SIZE 512 /* size = 512 bytes */
    #define STACK_2_SIZE 512 /* size = 512 bytes */
    #define STACK_3_SIZE 512 /* size = 512 bytes */
    #define STACK_4_SIZE 512 /* size = 512 bytes */
    #define STACK_5_SIZE 512 /* size = 512 bytes */
    #define STACK_6_SIZE 512 /* size = 512 bytes */
    #define STACK_7_SIZE 512 /* size = 512 bytes */

    static EE_STACK_T EE_STACK_ATTRIB_NAME(TrustedApp) EE_stack_1[EE_STACK_WLEN(STACK_1_SIZE)];	/* Task 0 (MainTask), Task 1 (TrustedTask1), shared stack TrustedApp */
    static EE_STACK_T EE_STACK_ATTRIB_NAME(App1) EE_stack_2[EE_STACK_WLEN(STACK_2_SIZE)];	/* Task 2 (App1Init), Task 3 (App1Task), shared stack App1 */
    static EE_STACK_T EE_STACK_ATTRIB_NAME(App2) EE_stack_3[EE_STACK_WLEN(STACK_3_SIZE)];	/* Task 4 (App2Init), shared stack App2 */
    static EE_STACK_T EE_STACK_ATTRIB_NAME(App2) EE_stack_4[EE_STACK_WLEN(STACK_4_SIZE)];	/* Task 5 (App2Task) */
    static EE_STACK_T EE_STACK_ATTRIB_NAME(TrustedApp) EE_stack_5[EE_STACK_WLEN(STACK_5_SIZE)];	/* ISR stack for TrustedApp */
    static EE_STACK_T EE_STACK_ATTRIB_NAME(App1) EE_stack_6[EE_STACK_WLEN(STACK_6_SIZE)];	/* ISR stack for App1 */
    static EE_STACK_T EE_STACK_ATTRIB_NAME(App2) EE_stack_7[EE_STACK_WLEN(STACK_7_SIZE)];	/* ISR stack for App2 */

#else

#define STACK_1_SIZE 512 /* size = 512 bytes */
#define STACK_2_SIZE 512 /* size = 512 bytes */
#define STACK_3_SIZE 512 /* size = 512 bytes */
#define STACK_4_SIZE 512 /* size = 512 bytes */
#define STACK_5_SIZE 512 /* size = 512 bytes */
#define STACK_6_SIZE 512 /* size = 512 bytes */
#define STACK_7_SIZE 512 /* size = 512 bytes */

#pragma section DATA "ee_stack_TrustedApp" "ee_stack_TrustedApp"
static EE_STACK_T EE_stack_1[EE_STACK_WLEN(STACK_1_SIZE)];
static EE_STACK_T EE_stack_5[EE_STACK_WLEN(STACK_5_SIZE)];
#pragma section DATA //EE_stack_1, EE_stack_5

#pragma section DATA "ee_stack_App1" "ee_stack_App1"
static EE_STACK_T EE_stack_2[EE_STACK_WLEN(STACK_2_SIZE)];
static EE_STACK_T EE_stack_6[EE_STACK_WLEN(STACK_6_SIZE)];
#pragma section DATA// APP1 EE_stack_2, EE_stack_6

#pragma section DATA "ee_stack_App2" "ee_stack_App2"
static EE_STACK_T EE_stack_3[EE_STACK_WLEN(STACK_3_SIZE)];
static EE_STACK_T EE_stack_4[EE_STACK_WLEN(STACK_4_SIZE)];
static EE_STACK_T EE_stack_7[EE_STACK_WLEN(STACK_7_SIZE)];
#pragma section DATA// EE_stack_3, EE_stack_4, EE_stack_7

#endif

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0U,	 /* dummy*/
        1U,	 /* MainTask*/
        1U,	 /* TrustedTask1*/
        2U,	 /* App1Init*/
        2U,	 /* App1Task*/
        3U,	 /* App2Init*/
        4U 	 /* App2Task*/
    };

    struct EE_TOS EE_e200z7_system_tos[5] = {
        {0},	/* Task  (dummy) */
        {(EE_ADDR)(&EE_stack_1[EE_STACK_INITP(STACK_1_SIZE)])},	/* Task 0 (MainTask), Task 1 (TrustedTask1), shared stack TrustedApp */
        {(EE_ADDR)(&EE_stack_2[EE_STACK_INITP(STACK_2_SIZE)])},	/* Task 2 (App1Init), Task 3 (App1Task), shared stack App1 */
        {(EE_ADDR)(&EE_stack_3[EE_STACK_INITP(STACK_3_SIZE)])},	/* Task 4 (App2Init), shared stack App2 */
        {(EE_ADDR)(&EE_stack_4[EE_STACK_INITP(STACK_4_SIZE)])} 	/* Task 5 (App2Task) */
    };

    EE_UREG EE_e200z7_active_tos = 0U; /* dummy */



/***************************************************************************
 *
 * OS APPLICATIONS definition
 *
 **************************************************************************/
    extern const int ee_load_data_TrustedApp;
    extern int ee_sstack_TrustedApp;
    extern int ee_sdata_TrustedApp;
    extern int ee_sbss_TrustedApp;
    extern int ee_ebss_TrustedApp;
    extern const int ee_load_data_App1;
    extern int ee_sstack_App1;
    extern int ee_sdata_App1;
    extern int ee_sbss_App1;
    extern int ee_ebss_App1;
    extern const int ee_load_data_App2;
    extern int ee_sstack_App2;
    extern int ee_sdata_App2;
    extern int ee_sbss_App2;
    extern int ee_ebss_App2;

    const EE_as_Application_ROM_type EE_as_Application_ROM[EE_MAX_APP] = {
	{{ &ee_load_data_TrustedApp, &ee_sstack_TrustedApp, &ee_sdata_TrustedApp, &ee_sbss_TrustedApp, &ee_ebss_TrustedApp }},
        {{ &ee_load_data_App1, &ee_sstack_App1, &ee_sdata_App1, &ee_sbss_App1, &ee_ebss_App1 }},
        {{ &ee_load_data_App2, &ee_sstack_App2, &ee_sdata_App2, &ee_sbss_App2, &ee_ebss_App2 }}
    };


    EE_as_Application_RAM_type EE_as_Application_RAM[EE_MAX_APP+1U] = {
        EE_APP_RAM_INIT(0,0U),
        EE_APP_RAM_INIT(&EE_stack_5[EE_STACK_INITP(STACK_5_SIZE)], EE_MEMPROT_TRUST_MODE),
        EE_APP_RAM_INIT(&EE_stack_6[EE_STACK_INITP(STACK_6_SIZE)], EE_MEMPROT_USR_MODE),
        EE_APP_RAM_INIT(&EE_stack_7[EE_STACK_INITP(STACK_7_SIZE)], EE_MEMPROT_USR_MODE)
    };

    const ApplicationType EE_th_app[EE_MAX_TASK+1] = {
        0,	/* dummy */
        1,	/* MainTask */
        1,	/* TrustedTask1 */
        2,	/* App1Init */
        2,	/* App1Task */
        3,	/* App2Init */
        3 	/* App2Task */
    };



/***************************************************************************
 *
 * Memory Partitions
 *
 **************************************************************************/
    const EE_MEMPROT_ENTRY_T EE_hal_memprot_entries[EE_HAL_MEMPROT_ENTRIES(EE_MAX_APP)] = {
        EE_MEMPROT_SYSTEM_ENTRY,
        EE_MEMPROT_USER_ENTRY(1U, 0x40010000U, 0x10000U, 16U, EE_MEMPROT_TRUST_DATA), /* TrustedApp */
        EE_MEMPROT_USER_ENTRY(2U, 0x40020000U, 0x10000U, 16U, EE_MEMPROT_USR_DATA), /* App1 */
        EE_MEMPROT_USER_ENTRY(3U, 0x40030000U, 0x4000U, 14U, EE_MEMPROT_USR_DATA) /* App2 */
    };



/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
    EE_as_ISR_RAM_type EE_as_ISR_stack[EE_MAX_NESTING_LEVEL];

    const EE_as_ISR_ROM_type EE_as_ISR_ROM[EE_MAX_ISR] = {
        { 1 },/* TrustedIsr */
        { 2 },/* App1Isr */
        { 3 } /* App2Isr */
    };



/***************************************************************************
 *
 * System Calls
 *
 **************************************************************************/
const EE_FADDR EE_syscall_table[EE_SYSCALL_NR] = {
    (EE_FADDR)EE_as_EnableAllInterrupts,
    (EE_FADDR)EE_as_DisableAllInterrupts,
    (EE_FADDR)EE_as_ResumeAllInterrupts,
    (EE_FADDR)EE_as_SuspendAllInterrupts,
    (EE_FADDR)EE_as_ResumeOSInterrupts,
    (EE_FADDR)EE_as_SuspendOSInterrupts,
    (EE_FADDR)EE_oo_ActivateTask,
    (EE_FADDR)EE_oo_TerminateTask,
    (EE_FADDR)EE_oo_ChainTask,
    (EE_FADDR)EE_oo_Schedule,
    (EE_FADDR)EE_oo_ForceSchedule,
    (EE_FADDR)EE_oo_GetTaskID,
    (EE_FADDR)EE_oo_GetTaskState,
    (EE_FADDR)EE_oo_GetActiveApplicationMode,
    (EE_FADDR)EE_oo_StartOS,
    (EE_FADDR)EE_oo_ShutdownOS,
    (EE_FADDR)EE_as_TerminateISR2,
    (EE_FADDR)EE_as_ORTI_set_service,
};



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(MainTask);
    DeclareTask(TrustedTask1);
    DeclareTask(App1Init);
    DeclareTask(App1Task);
    DeclareTask(App2Init);
    DeclareTask(App2Task);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
        (EE_FADDR)EE_oo_thread_stub,		 /* thread MainTask */
        (EE_FADDR)EE_oo_thread_stub,		 /* thread TrustedTask1 */
        (EE_FADDR)EE_oo_thread_stub,		 /* thread App1Init */
        (EE_FADDR)EE_oo_thread_stub,		 /* thread App1Task */
        (EE_FADDR)EE_oo_thread_stub,		 /* thread App2Init */
        (EE_FADDR)EE_oo_thread_stub 		 /* thread App2Task */

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_FADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
        (EE_FADDR)FuncMainTask,
        (EE_FADDR)FuncTrustedTask1,
        (EE_FADDR)FuncApp1Init,
        (EE_FADDR)FuncApp1Task,
        (EE_FADDR)FuncApp2Init,
        (EE_FADDR)FuncApp2Task
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x10U,		 /* thread MainTask */
        0x1U,		 /* thread TrustedTask1 */
        0x2U,		 /* thread App1Init */
        0x4U,		 /* thread App1Task */
        0x2U,		 /* thread App2Init */
        0x8U 		 /* thread App2Task */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x10U,		 /* thread MainTask */
        0x1U,		 /* thread TrustedTask1 */
        0x2U,		 /* thread App1Init */
        0x4U,		 /* thread App1Task */
        0x2U,		 /* thread App2Init */
        0x8U 		 /* thread App2Task */
    };

    /* thread status */
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED,
        SUSPENDED,
        SUSPENDED,
        SUSPENDED,
        SUSPENDED
    };

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL,
        EE_NIL
    };

    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;

    /* The priority queues: (16 priorities maximum!) */
    EE_TYPEPAIR EE_rq_queues_head[16] =
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    EE_TYPEPAIR EE_rq_queues_tail[16] =
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    EE_TYPE_RQ_MASK EE_rq_bitmask = 0U;

    /* remaining nact: init= maximum pending activations of a Task */
    EE_TYPEPRIO EE_th_rnact[EE_MAX_TASK] = {
        1U,		 /* thread MainTask */
        1U,		 /* thread TrustedTask1 */
        1U,		 /* thread App1Init */
        1U,		 /* thread App1Task */
        1U,		 /* thread App2Init */
        1U		 /* thread App2Task */
    };

    /* max number activations of a Task */
    const EE_TYPEPRIO EE_th_rnact_max[EE_MAX_TASK] = {
        1U,		 /* thread MainTask */
        1U,		 /* thread TrustedTask1 */
        1U,		 /* thread App1Init */
        1U,		 /* thread App1Task */
        1U,		 /* thread App2Init */
        1U		 /* thread App2Task */
    };

    EE_TYPEPRIO EE_rq_link[EE_MAX_TASK] =
        { 4U, 0U, 1U, 2U, 1U, 3U};

    /* The pairs that are enqueued into the priority queues (6 is the total number of task activations) */
    EE_TYPEPAIR EE_rq_pairs_next[] =
        { 1, 2, 3, 4, 5, -1};

    /* no need to be initialized */
    EE_TID EE_rq_pairs_tid[6];

    /* a list of unused pairs */
    EE_TYPEPAIR EE_rq_free = 0; /* pointer to a free pair */

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL,
            EE_NIL,
            EE_NIL,
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
        { 0U, 0U, 0U, 0U, 0U, 0U};    /* thread event already active */

    EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
        { 0U, 0U, 0U, 0U, 0U, 0U};    /* thread wait mask */

    EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
        { 0U, 0U, 0U, 0U, 0U, 0U};

    EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
        { 0U, 0U, 0U, 0U, 0U, 0U};



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
        { MainTask };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1U, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };


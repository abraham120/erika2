#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 4
    #define MainTask 0
    #define TrustedTask1 1
    #define App1Task 2
    #define App2Task 3

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

/***************************************************************************
 *
 * OS APPLICATIONS definition
 *
 **************************************************************************/
    #define EE_MAX_APP 3



/***************************************************************************
 *
 * System Calls
 *
 **************************************************************************/
#define EE_ID_ActivateTask                             0
#define EE_ID_TerminateTask                            1
#define EE_ID_ChainTask                                2
#define EE_ID_Schedule                                 3
#define EE_ID_ForceSchedule                            4
#define EE_ID_GetTaskID                                5
#define EE_ID_GetTaskState                             6
#define EE_ID_EnableAllInterrupts                      7
#define EE_ID_DisableAllInterrupts                     8
#define EE_ID_ResumeAllInterrupts                      9
#define EE_ID_SuspendAllInterrupts                    10
#define EE_ID_ResumeOSInterrupts                      11
#define EE_ID_SuspendOSInterrupts                     12
#define EE_ID_GetActiveApplicationMode                13
#define EE_ID_StartOS                                 14
#define EE_ID_ShutdownOS                              15
#define EE_ID_TerminateISR2                           16

#define EE_MAX_SYS_SERVICEID		17
#define EE_SYSCALL_NR			17


/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
    #define EE_MAX_NESTING_LEVEL     19
    #define EE_MAX_ISR               3

/* ISR to Application mapping (TO BE REMOVED; needed by ISR2 macro) */
    #define ISR2_APP_TrustedIsr 1
    #define ISR2_APP_App1Isr    2
    #define ISR2_APP_App2Isr    3

/* ISR id */
    #define ISR2_ID_TrustedIsr	0
    #define ISR2_ID_App1Isr	1
    #define ISR2_ID_App2Isr	2

#endif


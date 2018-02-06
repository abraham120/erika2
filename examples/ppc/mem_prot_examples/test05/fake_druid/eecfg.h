#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1275



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 6
    #define MainTask 0
    #define TrustedTask1 1
    #define App1Init 2
    #define App1Task 3
    #define App2Init 4
    #define App2Task 5

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* System stack size */
    #define EE_SYS_STACK_SIZE     4096



/***************************************************************************
 *
 * OS APPLICATIONS definition
 *
 **************************************************************************/
    #define EE_MAX_APP 3U

    #define EE_ISR_DYNAMIC_TABLE


/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
    #define EE_MAX_NESTING_LEVEL     19
    #define EE_MAX_ISR               3

/* ISR to Application mapping */
    #define ISR2_APP_TrustedIsr	1
    #define ISR2_APP_App1Isr	2
    #define ISR2_APP_App2Isr	3

/* ISR id */
    #define ISR2_ID_TrustedIsr	0
    #define ISR2_ID_App1Isr	1
    #define ISR2_ID_App2Isr	2



/***************************************************************************
 *
 * System Calls
 *
 **************************************************************************/
#define EE_ID_EnableAllInterrupts                      0
#define EE_ID_DisableAllInterrupts                     1
#define EE_ID_ResumeAllInterrupts                      2
#define EE_ID_SuspendAllInterrupts                     3
#define EE_ID_ResumeOSInterrupts                       4
#define EE_ID_SuspendOSInterrupts                      5
#define EE_ID_ActivateTask                             6
#define EE_ID_TerminateTask                            7
#define EE_ID_ChainTask                                8
#define EE_ID_Schedule                                 9
#define EE_ID_ForceSchedule                           10
#define EE_ID_GetTaskID                               11
#define EE_ID_GetTaskState                            12
#define EE_ID_GetActiveApplicationMode                13
#define EE_ID_StartOS                                 14
#define EE_ID_ShutdownOS                              15
#define EE_ID_TerminateISR2                           16
#ifdef __OO_ORTI_SERVICETRACE__
#define EE_ID_ORTI_ext_set_service                    17
#endif __OO_ORTI_SERVICETRACE__

#define EE_ID_interrupts_last                          5
#define EE_MAX_SYS_SERVICEID                          18
#define EE_SYSCALL_NR                                 18
#endif


#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 1
    #define TaskMaster 0

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 1U
    #define RES_SCHEDULER 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0

    /* CPUs */
    #define EE_MAX_CPU 2
    #define EE_CURRENTCPU 0



/***************************************************************************
 *
 * Remote Notification
 *
 **************************************************************************/
    #define EE_MAX_RN 3
    #define rn_TaskMaster 0
    #define rn_Task1 1
    #define rn_Task2 2

    /* remote threads */
    #define Task1 (rn_Task1|EE_REMOTE_TID)
    #define Task2 (rn_Task2|EE_REMOTE_TID)

#endif


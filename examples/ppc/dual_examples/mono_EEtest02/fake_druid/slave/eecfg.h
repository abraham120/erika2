#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 1 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 1
    #define Task1 0

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0

    /* CPUs */
    #define EE_MAX_CPU 2
    #define EE_CURRENTCPU 1



/***************************************************************************
 *
 * Remote Notification
 *
 **************************************************************************/
    #define EE_MAX_RN 2
    #define rn_TaskMaster 0
    #define rn_Task1 1

    /* remote threads */
    #define TaskMaster (rn_TaskMaster|EE_REMOTE_TID)

#endif


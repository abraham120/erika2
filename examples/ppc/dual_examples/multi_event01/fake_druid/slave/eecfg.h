#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 1 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 2
    #define TaskZ0Main 0
    #define TaskZ0Bkg 1

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 1U
    #define RES_SCHEDULER 0U

    /* EVENT definition */
    #define Event1 0x1U
    #define Event2 0x2U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1

    /* CPUs */
    #define EE_MAX_CPU 2
    #define EE_CURRENTCPU 1



/***************************************************************************
 *
 * Remote Notification
 *
 **************************************************************************/
    #define EE_MAX_RN 3
    #define rn_TaskZ6 0
    #define rn_TaskZ0Main 1
    #define rn_TaskZ0Bkg 2

    /* remote threads */
    #define TaskZ6 (rn_TaskZ6|EE_REMOTE_TID)

    /* System stack size */
    #define EE_SYS_STACK_SIZE     4096

#endif


#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 1 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 3
    #define TaskZ0 0
    #define TaskZ0b 1
    #define TaskZ0c 2

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 1U
    #define RES_SCHEDULER 0U

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
    #define EE_MAX_RN 6
    #define rn_TaskZ6 0
    #define rn_TaskZ6b 1
    #define rn_TaskZ6c 2
    #define rn_TaskZ0 3
    #define rn_TaskZ0b 4
    #define rn_TaskZ0c 5

    /* remote threads */
    #define TaskZ6 (rn_TaskZ6|EE_REMOTE_TID)
    #define TaskZ6b (rn_TaskZ6b|EE_REMOTE_TID)
    #define TaskZ6c (rn_TaskZ6c|EE_REMOTE_TID)

    /* System stack size */
    #define EE_SYS_STACK_SIZE     4096

#endif


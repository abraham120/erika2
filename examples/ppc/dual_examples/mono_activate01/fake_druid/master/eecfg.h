#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 3
    #define TaskZ6 0
    #define TaskZ6b 1
    #define TaskZ6c 2

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
    #define EE_MAX_RN 6
    #define rn_TaskZ6 0
    #define rn_TaskZ6b 1
    #define rn_TaskZ6c 2
    #define rn_TaskZ0 3
    #define rn_TaskZ0b 4
    #define rn_TaskZ0c 5

    /* remote threads */
    #define TaskZ0 (rn_TaskZ0|EE_REMOTE_TID)
    #define TaskZ0b (rn_TaskZ0b|EE_REMOTE_TID)
    #define TaskZ0c (rn_TaskZ0c|EE_REMOTE_TID)

    /* System stack size */
    #define EE_SYS_STACK_SIZE     4096

#endif


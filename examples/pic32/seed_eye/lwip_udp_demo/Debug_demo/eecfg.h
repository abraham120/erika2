#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 3
    #define Sender 0
    #define LwipReceive 1
    #define LwipPeriodic 2

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 2U
    #define LwipMutex 0U
    #define RES_SCHEDULER 1U

    /* ALARM definition */
    #define EE_MAX_ALARM 1
    #define SenderAlarm 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 1
    #define SenderCounter 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

#endif


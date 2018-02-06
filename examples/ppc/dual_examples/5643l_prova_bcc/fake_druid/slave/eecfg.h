#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1276



/***************************************************************************
 *
 * Common defines ( CPU 1 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 2
    #define disturbing_task 0
    #define CheckOK_task 1

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 1U
    #define RES_SCHEDULER 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 2
    #define EE_CURRENTCPU 1

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __E200ZX_EXECUTE_FROM_RAM__
#define __CODEWARRIOR__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_LINUX__
#define __MSRP__
#define __PPCE200ZX__
#define __MPC5668G__
#define __PPCE200Z0__
#define __VLE__
#define __DIAB__
#define __RN__
#define __RN_TASK__
#define __OO_BCC1__
#define __OO_EXTENDED_STATUS__
#define __MONO__
#define __OO_HAS_USERESSCHEDULER__
#define __OO_NO_ALARMS__

#endif



/***************************************************************************
 *
 * Remote Notification
 *
 **************************************************************************/
    #define EE_MAX_RN 6
    #define rn_TaskZ6_1 0
    #define rn_TaskZ6_2 1
    #define rn_TaskZ6_3 2
    #define rn_TaskZ6_4 3
    #define rn_disturbing_task 4
    #define rn_CheckOK_task 5

    /* remote threads */
    #define TaskZ6_1 ((EE_TID)rn_TaskZ6_1+(EE_TID)EE_REMOTE_TID)
    #define TaskZ6_2 ((EE_TID)rn_TaskZ6_2+(EE_TID)EE_REMOTE_TID)
    #define TaskZ6_3 ((EE_TID)rn_TaskZ6_3+(EE_TID)EE_REMOTE_TID)
    #define TaskZ6_4 ((EE_TID)rn_TaskZ6_4+(EE_TID)EE_REMOTE_TID)

    /* System stack size */
    #define EE_SYS_STACK_SIZE     4096

#endif


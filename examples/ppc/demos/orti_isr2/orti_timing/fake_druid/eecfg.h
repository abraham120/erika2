#ifndef __EECFG_H__
#define __EECFG_H__



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 3
    #define Task0 0
    #define Task1 1
    #define Task2 2

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

    /* System stack size */
    #define EE_SYS_STACK_SIZE     2048

#endif


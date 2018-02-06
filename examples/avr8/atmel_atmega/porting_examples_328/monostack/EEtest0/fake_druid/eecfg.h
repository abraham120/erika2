#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1277



/***************************************************************************
 *
 * Common defines ( CPU 0 )
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
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define DEBUG
#define __ASSERT__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/

#define __RTD_CYGWIN__
#if	0
#define __RTD_LINUX__
#endif	/* 0 */
#define __AVR8__
#define __ATMEGA__
#define __FP__
#define __MONO__
#define __FP_NO_RESOURCE__

#endif



#endif


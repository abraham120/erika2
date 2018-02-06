#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1278



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
    #define EE_MAX_ALARM 0U

    /* SCHEDULING TABLE definition */
    #define EE_MAX_SCHEDULETABLE 0U

    /* COUNTER OBJECTS definition */
    #define EE_MAX_COUNTER_OBJECTS (EE_MAX_ALARM + EE_MAX_SCHEDULETABLE)

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0U

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* Number of isr 2 */
    #define EE_MAX_ISR2   0
    #define EE_MAX_ISR_ID 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
//#define __RTD_CYGWIN__
//#define __RTD_LINUX__
#define __AVR8__
#define __ATTINY__
#define __FP__
#define __MONO__
#define __FP_NO_RESOURCE__

#endif



#endif


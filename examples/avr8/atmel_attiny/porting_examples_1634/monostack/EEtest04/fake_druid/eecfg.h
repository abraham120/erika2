#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1278



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 2
    #define Task1 0
    #define Task2 1

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
    #define EE_MAX_ISR2   1
    #define EE_MAX_ISR_ID 1

/***************************************************************************
 *
 * ISR
 *
 **************************************************************************/
#define EE_AVR8_TIMER0_COMPA_ISR	timer_handler
/* #define EE_AVR8_TIMER0_COMPA_ISR_PRI	EE_ISR_PRI_LOW */
#define EE_AVR8_TIMER0_COMPA_ISR_CAT	2

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
#define __TIMER_USED__
#define __TIMER_0_USED__
#define __TIMER0_CLK_DIV256__
#define __FP__
#define __MONO__
#define __FP_NO_RESOURCE__

#endif



#endif


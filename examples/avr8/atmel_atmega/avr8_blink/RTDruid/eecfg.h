#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1277



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 3
    #define TaskL1 0
    #define TaskL2 1
    #define TaskL3 2

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 3
    #define AlarmL1 0
    #define AlarmL2 1
    #define AlarmL3 2

    /* COUNTER definition */
    #define EE_MAX_COUNTER 2
    #define Counter320us 0
    #define Counter1ms 1

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* Number of isr 2 */
    #define EE_MAX_ISR2 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __LEDS_USED__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __AVR5__
#define __ATMEGA128__
#define __TIMER0_CLK_DIV64__
#define __TIMER_0_USED__
#define __TIMER1_CLK_DIV8__
#define __TIMER_1_USED__
#define __TIMER2_CLK_DIV1024__
#define __TIMER_2_USED__
#define __TIMER3_CLK_DIV1024__
#define __TIMER_3_USED__
#define __TIMER_USED__
#define __XBOW_MIB5X0__ 
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__

#endif



#endif


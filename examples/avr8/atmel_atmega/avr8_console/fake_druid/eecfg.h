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
    #define TaskSend 0

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 1U
    #define AlarmSend 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 1U
    #define myCounter 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

/***************************************************************************
 *
 * ISR
 *
 **************************************************************************/

#define EE_AVR8_TIMER1_COMPA_ISR	irq_1_f__type1
/* #define EE_AVR8_TIMER1_COMPA_ISR_PRI	EE_ISR_PRI_1 */
#define EE_AVR8_TIMER1_COMPA_ISR_CAT	2



#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define DEBUG
#define USE_CONSOLE
#define USE_CONSOLE_SERIAL

/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
/*
#define __RTD_CYGWIN__
#define __RTD_LINUX__
*/
#define __AVR8__
#define __ATMEGA__
#define __TIMER_USED__
#define __TIMER_1_USED__
#define __TIMER1_CLK_DIV256__
#define __USE_UART__
#define __XBOW_MIB5X0__ 
#define __LEDS_USED__
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__
/* #define __ALLOW_NESTED_IRQ__ */

#endif



#endif


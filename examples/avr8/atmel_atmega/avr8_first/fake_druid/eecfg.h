#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1277



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 2
    #define Task0 0
    #define Task1 1

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0U

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0U

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

#define EE_AVR8_TIMER0_COMP_ISR		irq_1_f__type0
/* #define EE_AVR8_TIMER0_COMP_ISR_PRI	EE_ISR_PRI_1 */
#define EE_AVR8_TIMER0_COMP_ISR_CAT	2

#define EE_AVR8_TIMER2_COMP_ISR		irq_1_f__type2
/* #define EE_AVR8_TIMER2_COMP_ISR_PRI	EE_ISR_PRI_1 */
#define EE_AVR8_TIMER2_COMP_ISR_CAT	2



#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define DEBUG


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
/*
#define __RTD_CYGWIN__
#define __RTD_LINUX__
*/
/* #define __HAS_TYPES_H__ */
/* #define __AVR_PGMSPACE__ */
#define __AVR8_GCC_C99__
#define __AVR8__
#define __ATMEGA__
#define __IC_USED__
#define __TIMER_USED__
#define __TIMER0_CLK_DIV64__
#define __TIMER_0_USED__
#define __TIMER1_CLK_DIV64__
#define __TIMER_1_USED__
#define __TIMER2_CLK_DIV64__
#define __TIMER_2_USED__
#define __TIMER3_CLK_DIV64__
#define __TIMER_3_USED__
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


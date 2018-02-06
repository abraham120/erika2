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
    #define EE_MAX_ALARM 3U
    #define AlarmL1 0
    #define AlarmL2 1
    #define AlarmL3 2

    /* COUNTER definition */
    #define EE_MAX_COUNTER 2U
    #define Counter1ms   0
    #define CounterTicks 1

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
#define EE_AVR8_TCC0_OVF_ISR		EE_Gpt_C_0_OVF_ISR
#define EE_AVR8_TCC0_OVF_ISR_PRI	EE_ISR_PRI_1
#define EE_AVR8_TCC0_OVF_ISR_CAT	2

#define EE_AVR8_TCD0_OVF_ISR		EE_Gpt_D_0_OVF_ISR
#define EE_AVR8_TCD0_OVF_ISR_PRI	EE_ISR_PRI_1
#define EE_AVR8_TCD0_OVF_ISR_CAT	2

#define EE_AVR8_PORTA_INT0_ISR		EE_Gpio_PortA_ISR
#define EE_AVR8_PORTA_INT0_ISR_PRI	EE_ISR_PRI_2
#define EE_AVR8_PORTA_INT0_ISR_CAT	2

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define DEBUG

/* TODO: Set correct #define. */

/* MCU */
#define __MCU_EXTENDED_STATUS__
#define __MCU_INITCLOCK_API__
#define __MCU_DEINITCLOCK_API__
#define __MCU_GETCLOCKSTATUS_API__
#define __MCU_DISTRIBUTECLOCK_API__

/* GPIO */
#define __GPIO_DRIVER__
#define __GPIO_EXTENDED_STATUS__
#define __GPIO_READCHANNEL_API__
#define __GPIO_WRITECHANNEL_API__
#define __GPIO_FLIPCHANNEL_API__
#define __GPIO_ENABLENOTIF_API__

/* GPT */
#define __GPT_DRIVER__
#define __GPT_CHANNEL_C_0__
#define __GPT_CHANNEL_D_0__
#define __GPT_EXTENDED_STATUS__
#define __GPT_STOPTIMER_API__
#define __GPT_ENABLENOTIF_API__

/* BOARD */
/*
#define __BOARD_EXTENDED_STATUS__
*/
/* LED */
/*
#define __LED_DRIVER__
#define __LED_PORT_D__
#define __LED_EXTENDED_STATUS__
*/


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
/*
#define __RTD_CYGWIN__
#define __RTD_LINUX__
*/
#define __HAS_TYPES_H__
#define __AVR8__
#define __ATXMEGA__
/* #define __ATMEL_STK600__ */
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__
#define __ALLOW_NESTED_IRQ__

#endif



#endif


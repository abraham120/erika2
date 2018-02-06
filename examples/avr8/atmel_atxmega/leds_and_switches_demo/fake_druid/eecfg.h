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
    #define Counter320us 0
    #define Counter1ms 1

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
#define EE_AVR8_TCC0_OVF_ISR		timer1_handler
#define EE_AVR8_TCC0_OVF_ISR_PRI	EE:ISR_PRI_1
#define EE_AVR8_TCC0_OVF_ISR_CAT	2

#define EE_AVR8_TCC1_OVF_ISR		timer2_handler
#define EE_AVR8_TCC1_OVF_ISR_PRI	EE_ISR_PRI_2
#define EE_AVR8_TCC1_OVF_ISR_CAT	2

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define	DEBUG

/* TODO: Set correct #define. */

/* MCU */
#define __MCU_EXTENDED_STATUS__

/* GPIO */
#define __GPIO_DRIVER__
#define __GPIO_EXTENDED_STATUS__
#define __GPIO_READCHANNEL_API__
#define __GPIO_WRITECHANNEL_API__
#define __GPIO_FLIPCHANNEL_API__

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
/* #define __RTD_CYGWIN__ */
/* #define __RTD_LINUX__ */
#define __HAS_TYPES_H__
#define __AVR8__
#define __ATXMEGA__
/* #define __ATMEL_STK600__ */
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__

#endif



#endif


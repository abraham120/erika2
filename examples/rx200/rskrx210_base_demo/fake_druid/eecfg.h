#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1277



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 5
    #define TaskLeds 0
    #define TaskDebounce1 1
    #define TaskDebounce2 2
    #define TaskDebounce3 3
    #define TaskLCD 4

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 5
    #define AlarmLeds 0
    #define AlarmDeb1 1
    #define AlarmDeb2 2
    #define AlarmDeb3 3
    #define AlarmLCD 4

    /* COUNTER definition */
    #define EE_MAX_COUNTER 1
    #define myCounter 0

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
#define __RSKRX210__
#define __USE_SYSTICK__
#define __USE_RSKRX120_USER_LED__
#define __USE_RSKRX120_BUTTONS__
#define __USE_RSKRX210_OP_FREQ_SETUP__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __R5F5210x__
#define __RX200__
#define __CCRX__
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__

#endif



/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
#define EE_RX200_CMIA0_ISR cmia0_handler
#define EE_RX200_IRQ1_ISR irq1_handler
#define EE_RX200_IRQ3_ISR irq3_handler
#define EE_RX200_IRQ4_ISR irq4_handler


#endif


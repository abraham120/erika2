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
    #define Task1 0
    #define Task2 1

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __OO_STARTOS_OLD__
#define __ADD_LIBS__
#define __USE_STM32F4XX_CMSIS__
#define __USE_STM32F4XX_SPD__
#define __USE_STM32F4XX_EVAL__
#define __USE_SYSTICK__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_LINUX__
#define __CORTEX_MX__
#define __CORTEX_M4__
#define __GNU__
#define __OO_BCC1__
#define __OO_EXTENDED_STATUS__
#define __MONO__
#define __OO_NO_ALARMS__
#define __OO_NO_RESOURCES__
#define __OO_AUTOSTART_TASK__
#define __ALLOW_NESTED_IRQ__

#endif



/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
#define EE_CORTEX_MX_SYSTICK_ISR systick_handler
#define EE_CORTEX_MX_SYSTICK_ISR_PRI EE_ISR_PRI_1


#endif


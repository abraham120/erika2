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
#define __ASSERT__
#define __ADD_LIBS__
#define __USE_STM32F4XX_CMSIS__
#define __USE_STM32F4XX_SPD__
#define __USE_STM32F4XX_EVAL__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __CORTEX_MX__
#define __CORTEX_M4__
#define __GNU__
#define __FP__
#define __MONO__
#define __FP_NO_RESOURCES__

#endif



#endif


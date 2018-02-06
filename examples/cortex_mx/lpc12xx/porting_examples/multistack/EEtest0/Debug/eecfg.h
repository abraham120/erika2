#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1276



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
#define __USE_LPC12XX_CMSIS_V2__
#define __USE_CMSIS_IOCON__
#define __USE_CMSIS_SYSCTRL__
#define __USE_CMSIS_GPIO__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __LPCXPRESSO__
#define __LPC12xx__
#define __CORTEX_MX__
#define __CORTEX_M0__
#define __C_M0_IAR_J_LINK__
#define __IAR__
#define __FP__
#define __MULTI__
#define __FP_NO_RESOURCE__

#endif



#endif


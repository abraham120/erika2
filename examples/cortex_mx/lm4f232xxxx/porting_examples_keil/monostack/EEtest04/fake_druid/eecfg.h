#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1275



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


/***************************************************************************
 *
 * ISR
 *
 **************************************************************************/

#define EE_CORTEX_MX_SYSTICK_ISR systick_handler

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __USE_USER_LED__
#define __USE_SYSTICK__

/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __CORTEX_MX__
#define __CORTEX_M4__
#define __KEIL__
#define __STELLARIS__
#define __LM4F232xxxx__
#define __FP__
#define __MONO__
#define __FP_NO_RESOURCE__


#endif

#endif


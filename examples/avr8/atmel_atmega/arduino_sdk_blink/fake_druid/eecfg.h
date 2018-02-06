#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1278



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 1
    #define TaskL1 0

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



#ifndef __DISABLE_EEOPT_DEFINES__

/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define DEBUG
#define __ADD_LIBS__

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
#define __ARDUINO_SDK__
#define __ARDUINO_SDK_CC__
#define __ARDUINO_SDK_CC_1_6_10__
#define __ARDUINO_UNO_328__
#define __FP__
#define __MONO__
#define __FP_NO_RESOURCE__

#endif



#endif


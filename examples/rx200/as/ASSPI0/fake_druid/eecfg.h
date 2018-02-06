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

    /* Number of isr 2 */
    #define EE_MAX_ISR2 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __AUTOSAR_R4_0__
#define __AS_MCU_DRIVER__
#define __AS_PORT_DRIVER__
#define __AS_DIO_DRIVER__
#define __AS_SPI_DRIVER__
#define __AS_CFG_SPI_VERSION_INFO_API__
#define __ADD_LIBS__


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
#define __FP_NO_RESOURCE__

#endif



#endif


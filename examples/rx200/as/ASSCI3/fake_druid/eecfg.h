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
    #define TaskTxOk 0
    #define TaskRxOk 1
    #define TaskRxErr 2

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
    #define EE_MAX_ISR2 3

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
#define __AS_SCI_DRIVER__
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



/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
#define EE_RX200_TXI0_ISR EE_RX200_TXI0_ISR
#define EE_RX200_TXI0_ISR_PRI EE_ISR_PRI_1
#define EE_RX200_ERI0_ISR EE_RX200_ERI0_ISR
#define EE_RX200_RXI0_ISR EE_RX200_RXI0_ISR


#endif


#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1277



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 4
    #define TaskJobError 0
    #define TaskJobOk 1
    #define TaskSeqError 2
    #define TaskSeqOk 3

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
    #define EE_MAX_ISR2 6

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
#define __AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__
#define __AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__
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
#define EE_RX200_SCI0_TXI0_ISR EE_RX200_SCI0_TXI0_ISR
#define EE_RX200_SCI0_TXI0_ISR_PRI EE_ISR_PRI_1
#define EE_RX200_SCI0_ERI0_ISR EE_RX200_SCI0_ERI0_ISR
#define EE_RX200_SCI0_RXI0_ISR EE_RX200_SCI0_RXI0_ISR
#define EE_RX200_SCI1_TXI1_ISR EE_RX200_SCI1_TXI1_ISR
#define EE_RX200_SCI1_TXI1_ISR_PRI EE_ISR_PRI_1
#define EE_RX200_SCI1_ERI1_ISR EE_RX200_SCI1_ERI1_ISR
#define EE_RX200_SCI1_RXI1_ISR EE_RX200_SCI1_RXI1_ISR
#define EE_RX200_SCI1_RXI1_ISR_PRI EE_ISR_PRI_2


#endif


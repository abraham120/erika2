#ifndef __INCLUDE_MICROCHIP_PIC32_UART_H__
#define __INCLUDE_MICROCHIP_PIC32_UART_H__
#include "ee.h"



/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif


/******************************************************************************/
/*			 Mode configuration bits - Byte Values		      */
/******************************************************************************/

// 	Associated with UxMODEbits.PDSEL 
#define EE_UART_BIT9		0x06
#define EE_UART_BIT8_ODD	0x04
#define EE_UART_BIT8_EVEN	0x02
#define EE_UART_BIT8_NO		0x00

//	 Associated with UxMODEbits.STSEL
#define EE_UART_BIT_STOP_1	0x00
#define EE_UART_BIT_STOP_2	0x01


/******************************************************************************/
/*			 Mode configuration bits - Mode	Values		      */
/******************************************************************************/

// Uart pins enable configuration bits
#define EE_UART_CTRL_SIMPLE		0x00
//#define EE_UART_CTRL_FLOW_BASIC		0x01

//TODO: remove
#define EE_UART_CTRL_FLOW		0x01

#define EE_UART_CTRL_FLOW_COMPLETE	0x02
#define EE_UART_CTRL_MASK		0x03

// High baudrate configuration bit
#define EE_UART_BRGH_NONE		0x00
#define EE_UART_BRGH_ON			0x08
#define EE_UART_BRGH_MASK		0x08


// Interrupt configuration bits - TX
#define EE_UART_TX_INT_SINGLE	0x8000
#define EE_UART_TX_INT_EMPTY	0x4000
#define EE_UART_TX_INT_LAST	0x2000	
#define EE_UART_TX_INT_MASK 	0xE000

// Interrupt configuration bits - RX
#define EE_UART_RX_INT_FULL	0x00C0
#define EE_UART_RX_INT_3OF4	0x0080
#define EE_UART_RX_INT_SINGLE	0x0000	


/******************************************************************************/
/*				 Available Ports			      */
/******************************************************************************/



#ifdef __32MX795F512L__
enum {
	EE_UART_PORT_1A  = 0,		//UART1A
	EE_UART_PORT_1B,		//UART1B
	EE_UART_PORT_2A,		//UART2A
	EE_UART_PORT_2B,		//UART2B
	EE_UART_PORT_3A,		//UART3A
	EE_UART_PORT_3B,		//UART3B
};

#else //not __32MX795F512L__
enum {
	EE_UART_PORT_1  = 0,		//UART1
	EE_UART_PORT_2,			//UART2
};

#endif


	


/******************************************************************************/
/*				 Returned Messages			      */
/******************************************************************************/
	
#define EE_UART_NO_ERROR			1	//Used as positive
#define EE_UART_ERR_BAD_PORT			1
#define EE_UART_ERR_NO_DATA			2
#define EE_UART_ERR_OVERFLOW			3
#define EE_UART_ERR_INT_MODE			4
#define EE_UART_ERR_INT_DISABLED		5
#define EE_UART_FUNCTION_NOT_IMPLEMENTED	10


/******************************************************************************/
/*				Interrupt Registers			      */
/******************************************************************************/

#ifdef __32MX795F512L__

/* 		Interrupt Enable      	*/

#define	EE_UART_PORT1A_RX_INT_ENABLE 		IEC0bits.U1ARXIE
#define	EE_UART_PORT1A_TX_INT_ENABLE 		IEC0bits.U1ATXIE
#define	EE_UART_PORT1A_ERR_INT_ENABLE 		IEC0bits.U1AEIE

#define	EE_UART_PORT1B_RX_INT_ENABLE 		IEC2bits.U1BRXIE
#define	EE_UART_PORT1B_TX_INT_ENABLE 		IEC2bits.U1BTXIE
#define	EE_UART_PORT1B_ERR_INT_ENABLE 		IEC2bits.U1BEIE

#define	EE_UART_PORT2A_RX_INT_ENABLE 		IEC1bits.U2ARXIE
#define	EE_UART_PORT2A_TX_INT_ENABLE 		IEC1bits.U2ATXIE
#define	EE_UART_PORT2A_ERR_INT_ENABLE 		IEC1bits.U2AEIE

#define	EE_UART_PORT2B_RX_INT_ENABLE 		IEC2bits.U2BRXIE
#define	EE_UART_PORT2B_TX_INT_ENABLE 		IEC2bits.U2BTXIE
#define	EE_UART_PORT2B_ERR_INT_ENABLE 		IEC2bits.U2BEIE

#define	EE_UART_PORT3A_RX_INT_ENABLE 		IEC1bits.U3ARXIE
#define	EE_UART_PORT3A_TX_INT_ENABLE 		IEC1bits.U3ATXIE
#define	EE_UART_PORT3A_ERR_INT_ENABLE 		IEC1bits.U3AEIE

#define	EE_UART_PORT3B_RX_INT_ENABLE 		IEC2bits.U3BRXIE
#define	EE_UART_PORT3B_TX_INT_ENABLE 		IEC2bits.U3BTXIE
#define	EE_UART_PORT3B_ERR_INT_ENABLE 		IEC2bits.U3BEIE


/* 		Interrupt Flag	 	*/

#define	EE_UART_PORT1A_RX_INT_FLAG 		IFS0bits.U1ARXIF
#define	EE_UART_PORT1A_TX_INT_FLAG 		IFS0bits.U1ATXIF
#define	EE_UART_PORT1A_ERR_INT_FLAG 		IFS0bits.U1AEIF

#define	EE_UART_PORT1B_RX_INT_FLAG 		IFS2bits.U1BRXIF
#define	EE_UART_PORT1B_TX_INT_FLAG 		IFS2bits.U1BTXIF
#define	EE_UART_PORT1B_ERR_INT_FLAG 		IFS2bits.U1BEIF

#define	EE_UART_PORT2A_RX_INT_FLAG 		IFS1bits.U2ARXIF
#define	EE_UART_PORT2A_TX_INT_FLAG 		IFS1bits.U2ATXIF 
#define	EE_UART_PORT2A_ERR_INT_FLAG 		IFS1bits.U2AEIF

#define	EE_UART_PORT2B_RX_INT_FLAG 		IFS2bits.U2BRXIF
#define	EE_UART_PORT2B_TX_INT_FLAG 		IFS2bits.U2BTXIF
#define	EE_UART_PORT2B_ERR_INT_FLAG 		IFS2bits.U2BEIF

#define	EE_UART_PORT3A_RX_INT_FLAG 		IFS1bits.U3ARXIF 
#define	EE_UART_PORT3A_TX_INT_FLAG 		IFS1bits.U3ATXIF
#define	EE_UART_PORT3A_ERR_INT_FLAG 		IFS1bits.U3AEIF

#define	EE_UART_PORT3B_RX_INT_FLAG 		IFS2bits.U3BRXIF
#define	EE_UART_PORT3B_TX_INT_FLAG 		IFS2bits.U3BTXIF
#define	EE_UART_PORT3B_ERR_INT_FLAG 		IFS2bits.U3BEIF

#else	//not __32MX795F512L__

/* 		Interrupt Enable      	*/

#define	EE_UART_PORT1_RX_INT_ENABLE 		IEC0bits.U1RXIE
#define	EE_UART_PORT1_TX_INT_ENABLE 		IEC0bits.U1TXIE
#define	EE_UART_PORT1_ERR_INT_ENABLE 		IEC0bits.U1EIE

#define	EE_UART_PORT2_RX_INT_ENABLE 		IEC1bits.U2RXIE 
#define	EE_UART_PORT2_TX_INT_ENABLE 		IEC1bits.U2TXIE
#define	EE_UART_PORT2_ERR_INT_ENABLE 		IEC1bits.U2EIE

/* 		Interrupt Flag	 	*/

#define	EE_UART_PORT1_RX_INT_FLAG 		IFS0bits.U1RXIF
#define	EE_UART_PORT1_TX_INT_FLAG 		IFS0bits.U1TXIF
#define	EE_UART_PORT1_ERR_INT_FLAG 		IFS0bits.U1EIF

#define	EE_UART_PORT2_RX_INT_FLAG 		IFS1bits.U2RXIF
#define	EE_UART_PORT2_TX_INT_FLAG 		IFS1bits.U2TXIF
#define	EE_UART_PORT2_ERR_INT_FLAG 		IFS1bits.U2EIF

#endif
	

/******************************************************************************/
/*				 Functions				      */
/******************************************************************************/


/**
* @brief Initialize the UART peripheral.
*
* This function initializes the UART peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @param[in] baudrate 	
* @param[in] byte_format
* @param[in] mode	
* @return EE_UART_NO_ERROR, if no errors occurred.
*
* @pre		None
*/

EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, 
		     EE_UINT16 mode);



/**
* @brief Closes the UART peripheral.
*
* This function closes the UART peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @return EE_UART_NO_ERROR, if no errors occurred.
*
* @pre		None
*/

EE_INT8 EE_uart_close(EE_UINT8 port);



/**
* @brief Write a byte on the UART peripheral.
*
* This function writes data on the UART peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @param[in] data 	
* @return EE_UART_NO_ERROR, if no errors occurred.
*
* @pre		None
*/


EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data);


/**
* @brief Read a byte from the UART peripheral.
*
* This function reads data from the UART peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @param[in] *data 	
* @return EE_UART_NO_ERROR, if no errors occurred.
*
* @pre		None
*/

EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data);



/**
* @brief Set the rx callback for the UART peripheral.
*
* This function reads data from the UART peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @param[in] (*RxFunc)	
* @param[in] rxmode
* @return EE_UART_NO_ERROR, if no errors occurred.
*
* @pre		None
*/

EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), 
				EE_UINT8 rxmode);



#endif

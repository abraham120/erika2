/** 
* @file ee_spi.h
* @brief SPI interface for PIC32MX
* @author Christian Nastasi
* @author Ghibaudi Marco
* @version 0.1
* @date 2010-14-07
*/
#ifndef __INCLUDE_MICROCHIP_PIC32_SPI_H__
#define __INCLUDE_MICROCHIP_PIC32_SPI_H__

#include "ee.h"


/******************************************************************************/
/*				 Port Definition			      */
/******************************************************************************/



#ifdef __32MX795F512L__
enum {
	EE_SPI_PORT_1 = 0,
	EE_SPI_PORT_1A,
	EE_SPI_PORT_2A,
	EE_SPI_PORT_3A,
	EE_SPI_PORT_N,
};


#else //not defined __32MX795F512L__

enum {
	EE_SPI_PORT_1  = 0,
	EE_SPI_PORT_2,
	EE_SPI_PORT_N,
};

#endif


/******************************************************************************/
/*				 Returned Messages			      */
/******************************************************************************/

#define EE_SPI_NO_ERRORS		1	//Used positive
#define EE_SPI_ERR_BAD_PORT		1
#define EE_SPI_ERR_BAD_ARGS		2
#define EE_SPI_ERR_BUSY			3
//#define EE_SPI_DMA_NOT_IMPLEMENTED	4
#define EE_SPI_ERR_UNIMPLEMENTED	10

#define EE_SPI_EVT_TX_DONE		1
#define EE_SPI_EVT_RX_DONE		2



/******************************************************************************/
/*				 Configuration Flags			      */
/******************************************************************************/

/** 
* @name SPI Configuration Flags
* @{ */
/* General Flags
*  NOTE: this work under the assumption that all the SPI ports have the same 
*  control register specification. See pic32mx family reference manual.
*/
#define EE_SPI_MASTER			0x0020
#define EE_SPI_CLOCK_IDLE_HIGH		0x0040	
#define EE_SPI_SDO_ON_CLOCK_TO_IDLE	0x0100
#define EE_SPI_SDI_ON_CLOCK_END		0x0200
/* Other Flags */
#define EE_SPI_DMA_TX			0x0001
#define EE_SPI_DMA_RX			0x0002
/* TODO: have more flags 
#define EE_SPI_SIZE	Use two bits of the flags to specify 8/16/32. This
has to be done for DMA accordingly.
*/

#define EE_SPI_DEFAULT	(EE_SPI_MASTER | EE_SPI_SDO_ON_CLOCK_TO_IDLE)
/**  @} */



/******************************************************************************/
/*				 Functions Prototypes			      */
/******************************************************************************/



/**
* @brief Initialize the SPI peripheral.
*
* This function initializes the SPI peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @param[in] baudrate 	
* @param[in] flags 	
* @return 	\todo
*
* @pre		None
*/
EE_INT8 EE_spi_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags); 

/**
* @brief Switch-off the SPI peripheral.
*
* This function switches-off the SPI peripheral defined by 
* the input parameter \p port.
*
* @param[in] port 	
* @return	EE_SPI_NO_ERRORS if no errors occurred. Otherwise a negative
*		number
*
* @pre		None
*/
EE_INT8 EE_spi_close(EE_UINT8 port); 

/** 
* @brief Set SPI event callback
* 
* \todo Say something more about callbacks. 
* 
* @param[in] port	The SPI port identifier.
* @param[in] event	The SPI event identifier.
* @param[in] f		The function pointer for the event callback.
* 
* @return 		\todo
*/
EE_INT8 EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void));

/** 
* @brief Write bytes through the SPI peripheral.
*
* \todo Say something more about this function. 
*
* @param[in] port	The SPI port identifier.
* @param[in] data	Bytes array to be transmitted.
* @param[in] len	Number of byte to be transmitted.
* 
* @return 	\todo
*/
EE_INT8 EE_spi_write(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len);

/** 
* @brief Read bytes through the SPI peripheral.
*
* \todo Say something more about this function. 
*
* @param[in] port	The SPI port identifier.
* @param[out] data	Bytes array to store received data.
* @param[in] len	Number of byte to be received.
* 
* @return 	\todo
*/
EE_INT8 EE_spi_read(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len);

/** 
* @brief Perform SPI write-and-read cycle
* 
* \todo This function is currently not implemented!
*
* @param[in] port	The SPI port identifier.
* @param[in] data_out
* @param[out] data_in
* @param[in] len
* 
* @return 
*/
EE_INT8 EE_spi_cycle(EE_UINT8 port, EE_UINT8 *data_out, EE_UINT8 *data_in, 
		     EE_UINT32 len);

#endif 

#ifndef __INCLUDE_MICROCHIP_DSPIC_SPI_H__
#define __INCLUDE_MICROCHIP_DSPIC_SPI_H__

#include "ee.h"

/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __PIC30_INCLUDE_REGS__
#include "ee_pic30regs.h"
#endif

//#include "P2PDefs.h"	// FIXME: chris: from gianluca's driver

#define EE_SPI_PORT_1 0
#define EE_SPI_PORT_2 1

#define EE_SPI_ERR_BAD_PORT		1
//#define EE_SPI_ERR_NO_DATA		2
//#define EE_SPI_ERR_OVERFLOW		3
//#define EE_SPI_ERR_INT_MODE		4
//#define EE_SPI_ERR_INT_DISABLED	5

/**
* @brief Initialize the SPI peripheral.
*
* This function initializes the SPI peripheral defined by 
* the input parameter \p port.
*
* @param[in] port 	The number of the SPI port to be initialized,
* 			it must be RADIO_SP1 or RADIO_SP2 defined in radio_spi.h.
* @return 	\todo
*
* @pre		None
*/
EE_INT8 EE_spi_init(EE_UINT8 port);

EE_INT8 EE_spi_close(EE_UINT8 port);

/**
* @brief Send a byte through  the SPI peripheral.
*
* This function send a character (8 bits) through the SPI 
* port controlling the radio.
*
* @param[in] data_in	The character to be sent
* @param[out] data_out	\todo
*
* @return 	\todo
*
* @pre		The SPI port must be correctly initialized.
*/
EE_INT8 EE_spi_rw_byte(EE_UINT8 port, EE_UINT8 data_in, EE_UINT8 *data_out);

/**
* @brief Send a byte through  the SPI peripheral.
*
* This function send a character (8 bits) through the SPI 
* port controlling the radio.
*
* @param[in] data	The character to be sent
*
* @return 	\todo
*
* @pre		The SPI port must be correctly initialized.
*/
EE_INT8 EE_spi_write_byte(EE_UINT8 port, EE_UINT8 data);

/**
* @brief Get a character through the SPI peripheral.
*
* This function send a character (8 bits) through the SPI 
* port controlling the radio.
*
* @return 	\todo
*
* @pre		The SPI port must be correctly initialized.
*/
EE_INT8 EE_spi_read_byte(EE_UINT8 port, EE_UINT8 *data);

#endif

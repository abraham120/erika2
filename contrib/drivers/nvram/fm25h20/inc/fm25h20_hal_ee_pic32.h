/** 
* @file fm25h20_hal_ee_pic32.h
* @brief FM25H20 Hw Abstraction Layer using Erika OS over Microchip pic32
* @author Christian Nastasi
* @author Marco Ghibaudi
* @date 2010-01-12
*
* This file is the definition of the hardware abstraction layer 
* used by all the module
* of the FM25H20 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/

#ifndef __fm25h20_hal_ee_pic32_h__
#define __fm25h20_hal_ee_pic32_h__

#ifndef __USE_SPI__
#error "FM25H20 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/microchip_pic32/inc/ee_spi.h>

/******************************************************************************/
/*			 	Inclusions				      */
/******************************************************************************/
#define FM25H20_SPI_PORT_1	EE_SPI_PORT_1
#define FM25H20_SPI_PORT_2	EE_SPI_PORT_2
#define FM25H20_SPI_FLAGS 	EE_SPI_MASTER | EE_SPI_SDO_ON_CLOCK_TO_IDLE  
#define FM25H20_SPI_CLOCK 	10000000 /*Clock frequency of the SPI Channel*/

#ifndef FM25H20_CSN
#define FM25H20_CSN		PORTGbits.RG9
#endif

#ifndef FM25H20_HOLD
#define FM25H20_HOLD		PORTCbits.RC2
#endif

#ifndef FM25H20_WPROTECT
#define FM25H20_WPROTECT	PORTCbits.RC3
#endif

#ifndef FM25H20_TRIS_CSN
#define FM25H20_TRIS_CSN	TRISGbits.TRISG9
#endif

#ifndef FM25H20_TRIS_HOLD
#define FM25H20_TRIS_HOLD	TRISCbits.TRISC2
#endif

#ifndef FM25H20_TRIS_WPROTECT
#define FM25H20_TRIS_WPROTECT	TRISCbits.TRISC3
#endif

#define fm25h20_cs_low()			FM25H20_CSN = 0 
#define fm25h20_cs_high()			FM25H20_CSN = 1 
#define fm25h20_hold_on() 			FM25H20_HOLD = 0 
#define fm25h20_hold_off() 			FM25H20_HOLD = 1 
#define fm25h20_write_protection_on()		FM25H20_WPROTECT = 0 
#define fm25h20_write_protection_off()		FM25H20_WPROTECT = 1 
#define fm25h20_set_cs_as_out() 		FM25H20_TRIS_CSN = 0
#define fm25h20_set_hold_as_out() 		FM25H20_TRIS_HOLD = 0
#define fm25h20_set_write_protection_as_out()	FM25H20_TRIS_WPROTECT = 0

/******************************************************************************/
/*			 Functions prototypes 				      */
/******************************************************************************/
/** 
* @brief  Add a delay. 
* 	
* This function adds a delay of \var delay_count us. Accuracy ~ 2% @ 80 Mhz.
*  	
* @ param[in]  delay_count number of us to be waited
* 
*/
COMPILER_INLINE void fm25h20_delay_us(uint16_t delay_count)
{
	EE_delay_us((uint32_t)delay_count);
}

/** 
* @brief  Init the hardware. 
* 	
* This function inits the pins used by the memory.
*  	
* @ param[in]  delay_count number of us to be waited
* 
*/
void fm25h20_hal_init();

/** 
* @brief Initializes SPI. 
* 	
* This function initializes the SPI.
*  	
* @ param[in]	port SPI port to be used.
* @ return	\todo 
*/
int8_t fm25h20_spi_init(uint8_t port, EE_UINT32 baudrate, EE_UINT16 flags );

/** 
* @brief Closes SPI. 
* 	
* This function closes the SPI.
*  	
* @ return	EE_SPI_PORT_CLOSED after closing the port. 
*/
int8_t fm25h20_spi_close(void);

/** 
* @brief Put on SPI. 
* 	
* This function puts data on the SPI.
*  	
* @ param[in]	in data to be transmitted.
* @ param[in]	*out address of data read-back
* @ return	\todo 
*/
int8_t	fm25h20_spi_write(uint8_t *data, uint32_t len);

/** 
* @brief Get from SPI. 
* 	
* This function acquires data from the SPI.
*  	
* @ param[in]	*out address of data read-back
* @ return	\todo 
*/
int8_t	fm25h20_spi_read(uint8_t *data, uint32_t len);

#endif /* Header Protection */

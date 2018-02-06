/** 
* @file fm25h20_compiler.h
* @brief FM25H20 Driver
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-25
*
* This file is the definition of the abstract compiler used by all the module
* of the FM25H20 library. 
*
* \todo Write something about the supported compilers.
*/

#ifndef _fm25h20_h_
#define _fm25h20_h_

#include "fm25h20_hal.h"

/** 
* @name Standard Commands
* @{ */
#define FM25H20_WRITE_ENABLE 		0x06	//Enables write operation
#define FM25H20_WRITE_DISABLE 		0x04	//Disables write operation
#define FM25H20_READ_STATUS_REG 	0x05	//Read the status register
#define FM25H20_WRITE_STATUS_REG 	0x01	//Writes the status register
#define FM25H20_READ_MEMORY	 	0x03	//Reads the memory
#define FM25H20_WRITE_MEMORY 		0x02	//Writes the memory
#define FM25H20_SLEEP 			0xB9	//Enters in the Sleep mode
/* @} */

/** 
* @name Device Specific characteristics
* @{ */
#define MEMORY_SIZE 	0x3FFFF		//Highest memory address
#define CHECK_MASK	0x40		//Standard value for Status register 
/* @} */

/** 
* @name Commands' arrays size
* @{ */
#define WRITE_ARRAY_SIZE 	4		
#define READ_ARRAY_SIZE 	4			
/* @} */

/** 
* @name Error Codes
* @{ */
#define FM25H20_ERR_NONE 			1 /* Returned as positive! */
#define FM25H20_WRONG_MEMORY_ADDRESS 		1 
#define FM25H20_SPI_INIT_FAILED 		2
#define FM25H20_FRAM_INIT_FAILED 		3
#define FM25H20_FRAM_WAKE_UP_FAILED 		4
#define FM25H20_DOUBLE_INIT	 		5
#define FM25H20_WRITE_FAILED	 		6
#define FM25H20_READ_FAILED	 		7
/* @} */

/* Functions prototypes */

/** 
* @brief  Initialize the memory 
* 	
* This function initializes the memory using the specified SPI channel.
*  	
* @ param[in] port spi channel used
* @ return  \ref FM25H20_ERR_NONE is returned on success, otherwise a negative
*		 error code is returned. 
*/
int8_t fm25h20_init(uint8_t port);

/** 
* @brief  Get data from the memory
* 	
* This function acquires data from the memory using the assigned SPI channel.
*  	
* @ param[in] address the address of the data to be gathered
* @ param[in] len the dimension in bytes of data to be extracted
* @ param[in] *data the location where the data are saved
* @ return  \ref FM25H20_ERR_NONE is returned on success, otherwise a negative
*		 error code is returned. 
*/
int8_t fm25h20_get(uint32_t address, uint32_t len, uint8_t *data);

/** 
* @brief  Store data in the memory
* 	
* This function stores data in the memory using the assigned SPI channel.
*  	
* @ param[in] address the address of the data to be written
* @ param[in] len the dimension in bytes of data to be written
* @ param[in] *buf the location of the data to be stored
* @ return  \ref FM25H20_ERR_NONE is returned on success, otherwise a negative
*		 error code is returned. 
*/
int8_t fm25h20_store(uint32_t address, uint32_t len, uint8_t* buf);

COMPILER_INLINE void fm25h20_sleep() 
{
	fm25h20_cs_low();
	uint8_t app = FM25H20_SLEEP;
	fm25h20_spi_write(&app, 1);
	fm25h20_cs_high();
}


COMPILER_INLINE uint8_t fm25h20_wake() 
{	
	/* select the device */
	fm25h20_cs_low();
	
	/* Perform a read to ensure that the device correctly woke up, 
	TODO: check this! */
	uint8_t app = FM25H20_READ_MEMORY;
	//fm25h20_spi_write(&app, 1);
	fm25h20_delay_us(450); // Wake-up time
	app = FM25H20_READ_STATUS_REG;
	fm25h20_spi_read(&app,1);
	
	/*Deselect the device */	
	fm25h20_cs_high();
	
	/* check the waking up */
	if ((app & CHECK_MASK) != 0)  
		return FM25H20_ERR_NONE; //woken-up correctly
	return FM25H20_FRAM_WAKE_UP_FAILED; //waking-up failed
}

#endif /* _fm25h20_h_*/

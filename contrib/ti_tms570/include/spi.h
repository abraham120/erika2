/** @file spi.h
*   @brief SPI Driver Definition File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*/



#ifndef __SPI_H__
#define __SPI_H__

#include "reg_spi.h"

/** @enum triggerEvent
*   @brief Transfer Group Trigger Event
*/
enum triggerEvent
{
    TRG_NEVER   = 0U,
    TRG_RISING  = 1U,
    TRG_FALLING = 2U,
    TRG_BOTH    = 3U,
    TRG_HIGH    = 5U,
    TRG_LOW     = 6U,
    TRG_ALWAYS  = 7U
};


/** @enum triggerSource
*   @brief Transfer Group Trigger Source
*/
enum triggerSource
{
    TRG_DISABLED,
    TRG_GIOA0,
    TRG_GIOA1,
    TRG_GIOA2,
    TRG_GIOA3,
    TRG_GIOA4,
    TRG_GIOA5,
    TRG_GIOA6,
    TRG_GIOA7,
    TRG_HET8,
    TRG_HET10,
    TRG_HET12,
    TRG_HET14,
    TRG_HET16,
    TRG_HET18,
    TRG_TICK
};


/** @enum chipSelect
*   @brief Transfer Group Chip Select
*/
enum chipSelect
{
    CS_NONE = 0xFFU,
    CS_0    = 0xFEU,
    CS_1    = 0xFDU,
    CS_2    = 0xFBU,
    CS_3    = 0xF7U,
    CS_4    = 0xEFU,
    CS_5    = 0xDFU,
    CS_6    = 0xBFU,
    CS_7    = 0x7FU
};
/** 
 *  @defgroup SPI SPI
 *  @brief Serial Peripheral Interface Module.
 *  
 *  SPI is a high-speed synchronous serial input/output port that allows a serial bit stream of
 *  programmed length (2 to 16 bits) to be shifted in and out of the device at a programmed bit-transfer rate.
 *
 *	Related Files
 *   - reg_spi.h
 *   - spi.h
 *   - spi.c
 *  @addtogroup SPI
 *  @{
 */

/* SPI Interface Functions */
void spiInit(void);
void spiSetFunctional(spiBASE_t *spi, uint32 port);
void spiSetData(spiBASE_t *spi, uint32 group, uint16 * data);
uint32 spiGetData(spiBASE_t *spi, uint32 group, uint16 * data);
void spiTransfer(spiBASE_t *spi, uint32 group);
uint32  spiIsTransferComplete(spiBASE_t *spi, uint32 group);
void spiEnableGroupNotification(spiBASE_t *spi, uint32 group, uint32 level);
void spiDisableGroupNotification(spiBASE_t *spi, uint32 group);


/** @fn void spiNotification(spiBASE_t *spi, uint32 flags)
*   @brief Error interrupt callback
*   @param[in] spi   - Spi module base address
*   @param[in] flags - Copy of error interrupt flags
*
* This is a error callback that is provided by the application and is call upon
* an error interrupt.  The parameter passed to the callback is a copy of the error
* interrupt flag register.
*/
void spiNotification(spiBASE_t *spi, uint32 flags);


/** @fn void spiGroupNotification(spiBASE_t *spi, uint32 group)
*   @brief Transfer complete notification callback
*   @param[in] spi   - Spi module base address
*   @param[in] group - Transfer group
*
* This is a callback function provided by the application.  It is call when
* a transfer is complete.  The paramter is the transfer group that triggered
* the interrupt.
*/
void spiGroupNotification(spiBASE_t *spi, uint32 group);
/**@}*/

#endif

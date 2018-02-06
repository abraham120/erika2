/** 
* @file mrf24j40_hal_ee_pic32.h
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over Microchip pic32
* @author Christian Nastasi
* @author Marco Ghibaudi
* @date 2010-01-12
*
* This file is the definition of the hardware abstraction layer 
* used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers. 
*
* \todo Write something about the hal support.
*/


#ifndef __mrf24j40_hal_ee_pic32_h__
#define __mrf24j40_hal_ee_pic32_h__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module from MCU is required!"
#endif
#include <ee.h>
#include <mcu/microchip_pic32/inc/ee_spi.h>

#ifdef  __32MX795F512L__
#define MRF24J40_SPI_PORT_1	EE_SPI_PORT_1
#define MRF24J40_SPI_PORT_1A	EE_SPI_PORT_1A
#define MRF24J40_SPI_PORT_2A	EE_SPI_PORT_2A
#define MRF24J40_SPI_PORT_3A	EE_SPI_PORT_3A
#else 
#define MRF24J40_SPI_PORT_1	EE_SPI_PORT_1
#define MRF24J40_SPI_PORT_2	EE_SPI_PORT_2
#endif

#ifdef __IPERMOB_BOARD_V2__
#include "board/ipermob_board_v2/inc/ee_mrf24j40_hal.h"

#else 
#include "board/ipermob_mb_pic32/inc/ee_mrf24j40_hal.h"

#endif /* Board Selection */

/* ------------------------------ HAL APIs ---------------------------------- */

int8_t	mrf24j40_hal_init(void);
int8_t	mrf24j40_hal_spi_init(uint8_t port);
int8_t	mrf24j40_hal_spi_close(void);
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

COMPILER_INLINE void mrf24j40_hal_delay_us(uint16_t delay_count)
{
	EE_delay_us((uint32_t)delay_count);
} 

COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	// chris: FIXME: This is due to the inverter of the elco v1 board!
	// markintosh: in the future it will be removed the elco v1 board bug
	// as well as the need for the two different implementations

	#ifdef MRF24J40MB_NOT_INVERTED_RESET	
	MRF24J40_RESETn = 1;
	#else	//not defined MRF24J40MB_NOT_INVERTED_RESET
	MRF24J40_RESETn = 0;
	#endif	
}

COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	// chris: FIXME: This is due to the inverter of the elco v1 board!
	// markintosh: in the future it will be removed the elco v1 board bug
	// as well as the need for the two different implementations
	
	#ifdef MRF24J40MB_NOT_INVERTED_RESET
		MRF24J40_RESETn = 0;
	#else	//not defined  MRF24J40MB_NOT_INVERTED_RESET
		MRF24J40_RESETn = 1;
	#endif
}

COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	MRF24J40_CSn = 1;
}

COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	MRF24J40_CSn = 0;
}

COMPILER_INLINE void mrf24j40_hal_irq_init(void)
{
	MRF24J40_INTERRUPT_INIT(6, 3);
}

COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
{
	MRF24J40_INTERRUPT_FLAG_CLR();
}

COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	MRF24J40_INTERRUPT_ENABLE_SET();
}

COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	MRF24J40_INTERRUPT_ENABLE_CLR();
}

COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return MRF24J40_INTERRUPT_ENABLE_STAT();
}

#endif /* Header Protection */

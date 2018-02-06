/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
/** 
* @file 	mrf24j40_hal_ee_mico32.h
* @brief 	MRF24J40 driver HAL for Mico32
			This file is part of Microchip MRF24J40 radio transceiver
			driver developed by Gianluca Franchino, Retis Lab. 
			Scuola Superiore Sant'Anna. Pisa (Italy), 02/27/2008.
			Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
* @author 	Dario Di Stefano
* @date 	2010
*/


#ifndef __mrf24j40_hal_ee_mico32_h__
#define __mrf24j40_hal_ee_mico32_h__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "board/fpg-eye/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
#include "mcu/mico32/inc/ee_spi.h"
#include "mcu/mico32/inc/ee_gpio.h"
#include "MicoUtils.h"

#ifdef __FPG_EYE__
#include "board/fpg-eye/inc/ee_zigbee_mrf24j40.h"
#else	/* NO board */
#error "MRF24J40_HAL: No board selected!"
#endif	//#ifdef __FPG_EYE__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module is required!"
#endif // __USE_SPI__

#ifndef ISR2
#define ISR2(f) void f(void)
#endif

/* ------------------------------------------------------------------------------- */
/* Structures and external variables */
/* ------------------------------------------------------------------------------- */
//MRF24J40 structure (used in ISR mode):
typedef struct {	
	int status;
	int mode;							// mrf24j40 operating mode (polling, isr, ...)
    MicoGPIO_t* base;					// GPIO controller base address
    int irqf;							// GPIO irq flag to register the handler
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
} EE_mrf24j40_st;

/* ZIGBEE driver functions list */
extern EE_mrf24j40_st ee_mrf24j40_st;

/* ------------------------------------------------------------------------------- */
/* Macros used into the Zigbee driver functions */
/* ------------------------------------------------------------------------------- */
#define MRF24J40_HAL_ISR() 		ISR2(MRF24J40_INTERRUPT_NAME)
#define MRF24J40_INTERRUPT_NAME	mrf24j40_isr		//_EXTERNAL_3_VECTOR
#define EE_MRF24J40_DEVICE_ID	(0x01)
#define MRF24J40_SPI_PORT_1		1
#define MRF24J40_SPI_PORT_2		2

/* Exit status for the EE_ZIGBEE driver */
#define	MRF24J40_SUCCESS 		(0)		/* no error */
#define	MRF24J40_FAILURE		(-19)	/* generic error */
#define	MRF24J40_ERR_SPI_INIT	(-20)	/* error in spi initialization */
#define	MRF24J40_ERR_SPI_READ	(-21)	/* spi read error */
#define	MRF24J40_ERR_SPI_WRITE	(-22)	/* spi write error */
#define	MRF24J40_ERR_DEV_NOINIT	(-23)	/* ZIGBEE device error */
#define	MRF24J40_ERR_MEM_NULL	(-24)	/* ZIGBEE null pointer error */

/* MRF24J40 operating modes */
#define EE_MRF24J40_POLLING		(0x00)
#define EE_MRF24J40_RX_ISR		(0x01)
#define EE_MRF24J40_TX_ISR		(0x02)	
#define EE_MRF24J40_RXTX_ISR	(0x03)
#define EE_MRF24J40_RX_BLOCK	(0x10)
#define EE_MRF24J40_TX_BLOCK	(0x20)
#define EE_MRF24J40_RXTX_BLOCK  (0x30)
#define EE_mrf24j40_need_enable_int(new)  	( ((new) & EE_MRF24J40_RX_ISR) || ((new) & EE_MRF24J40_TX_ISR) )

#define MRF24J40_SOFTRST_MASK 		(0x07)
#define MRF24J40_WAKE_ACTIVE()		EE_mrf24j40_gpio_wake_active()
#define MRF24J40_WAKE_INACTIVE()	EE_mrf24j40_gpio_wake_inactive()

#if(0) // not yet supported macros...
#define EE_MRF24J40_SHORT_ADDRESS_MASK		(0x3F)
#define EE_MRF24J40_LONG_ADDRESS_MASK		(0x3FF)
#define EE_MRF24J40_SRCR					(0x00)
#define EE_MRF24J40_SWCR					(0x01)
#define EE_MRF24J40_LRCR					(0x800)
#define EE_MRF24J40_LWCR					(0x801)
//#define EE_mrf24j40_need_init_rx_buf(old,new)		( !((old) & EE_MRF24J40_RX_ISR) && ((new) & EE_MRF24J40_RX_ISR) )
//#define EE_mrf24j40_need_init_tx_buf(old,new)  	( !((old) & EE_MRF24J40_TX_ISR) && ((new) & EE_MRF24J40_TX_ISR) )
//#define EE_mrf24j40_need_enable_rx_int(old, new)  ( (new) & EE_MRF24J40_RX_ISR )
//#define EE_mrf24j40_need_disable_rx_int(old, new) ( !((new) & EE_MRF24J40_RX_ISR) )
//#define EE_mrf24j40_enabled_rx_int(mode)  		( (mode) & EE_MRF24J40_RX_ISR )
#define EE_mrf24j40_tx_polling(mode) 				( !((mode) & EE_MRF24J40_TX_ISR) )
#define EE_mrf24j40_rx_polling(mode) 				( !((mode) & EE_MRF24J40_RX_ISR) )
#define EE_mrf24j40_rx_block(mode) 					( ((mode) & EE_MRF24J40_RX_BLOCK) )
#define EE_mrf24j40_tx_block(mode) 					( ((mode) & EE_MRF24J40_TX_BLOCK) )
#endif //#if(0) // not yet supported macros...

/* ------------------------------------------------------------------------------- */
/* ZIGBEE driver functions list */
/* ------------------------------------------------------------------------------- */
#define EE_ZIGBEE_SPI_NAME_UC NET_SPI
#define EE_ZIGBEE_SPI_NAME_LC net_spi

/* Macros for SPI-based ZIGBEE functions */  
#define DECLARE_FUNC_SPI_MRF24J40(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_spi_config(int settings, int mode){ \
	cat3(EE_, lc, _config)(settings); \
	return cat3(EE_, lc, _set_ISR_mode)(mode); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_write_byte(EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_write_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_read(void){ \
	return cat3(EE_, lc, _receive_byte)(); } \
__INLINE__ int __ALWAYS_INLINE__  EE_mrf24j40_spi_read_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(data, len); } \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_spi_set_SSO(void){ \
	EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_spi_clear_SSO(void){ \
	EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_spi_set_slave(unsigned int mask){ \
	EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), mask); } \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_spi_get_slave(unsigned int *pmask ){ \
	EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); } \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_spi_close(){ \
	EE_hal_spi_disable((MicoSPI_t*)EE_BASE_ADD(uc)); }
	
/* ZIGBEE API functions */

/* SPI functions */
DECLARE_FUNC_SPI_MRF24J40(EE_ZIGBEE_SPI_NAME_UC, EE_ZIGBEE_SPI_NAME_LC)

/**
	@brief This function contains a delay loop in micro-seconds. 
*/
void EE_mrf24j40_delay_us(unsigned int delay_count);

/**
	@brief This function sets ISR rx callback.
*/
int EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk);

/**
	@brief This function sets ISR tx callback.
*/
int EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk);

/**
	@brief This function sets the driver operating mode (polling, ISR).
*/
int EE_hal_mrf24j40_set_ISR_mode(int mode);

/**
	@brief This function reads the content of a short address register.
*/
int EE_mrf24j40_read_short_address_register(int address);

/**
	@brief This function reads the content of a long address register.
*/
int EE_mrf24j40_read_long_address_register(int address);

/**
	@brief This function writes on a short address register.
*/
int EE_mrf24j40_write_short_address_register(int address, EE_UINT8 data);

/**
	@brief This function writes on a long address register.
*/
int EE_mrf24j40_write_long_address_register(int address, EE_UINT8 data);

/**
	@brief This function resets the tranceiver via software.
*/
int EE_mrf24j40_software_reset(void);

/**
	@brief This function resets the tranceiver via hardware.
*/
int EE_mrf24j40_hardware_reset(void);

/**
	@brief This function turns on the tranceiver releasing reset.
*/
int EE_mrf24j40_enable(void);

/**
	@brief This function turns off the tranceiver holding reset.
*/
int EE_mrf24j40_disable(void);

/**
	@brief This function enables GPIO IRQ.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_enable_IRQ(void)
{
	EE_mrf24j40_gpio_enable_IRQ();
}

/**
	@brief This function disables GPIO IRQ.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_disable_IRQ(void)
{
	EE_mrf24j40_gpio_disable_IRQ();
}

/**
	@brief This function returns GPIO IRQ enabling status.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_IRQ_enabled(void)
{
	return EE_mrf24j40_gpio_IRQ_enabled();
}

/**
	@brief This function sets the driver operating mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_set_ISR_mode(int mode)
{ 
	return EE_hal_mrf24j40_set_ISR_mode(mode); 
} 

/**
	@brief This function turns off the tranceiver and resets Mico32 GPIO pins.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_init(void)
{ 
	EE_mrf24j40_gpio_write_output_pins(0);
	mico32_disable_irq(ee_mrf24j40_st.irqf);
	EE_mrf24j40_disable_IRQ();
	return MRF24J40_SUCCESS;
} 

/**
	@brief 	This function turns on the tranceiver, initializes Mico32 spi controller 
			and configures driver operating mode.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_config(void)
{ 
	EE_mrf24j40_init();		// init pins and disable gpio interrupt source.
	EE_mrf24j40_enable();	// set to 1 the _reset_ pin to turn on the mrf24j40 device.
	EE_mrf24j40_spi_config(0, EE_SPI_POLLING | EE_SPI_RXTX_BLOCK);
	
	#ifdef __USE_ZIGBEE_IRQ__
	return EE_mrf24j40_set_ISR_mode(EE_MRF24J40_RXTX_ISR); 
	#else // __USE_ZIGBEE_IRQ__
	return EE_mrf24j40_set_ISR_mode(EE_MRF24J40_POLLING | EE_MRF24J40_RXTX_BLOCK);
	#endif // __USE_ZIGBEE_IRQ__
} 

/**
	@brief 	This function is the MRF24j40 driver interrupt handler.
*/
void EE_mrf24j40_handler(int level);

#ifndef __STATIC_ISR_TABLE__
/**
	@brief 	This function registers the MRF24j40 driver interrupt handler.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_mrf24j40_handler_setup(void)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(ee_mrf24j40_st.irqf, EE_mrf24j40_handler);	 
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_mrf24j40_handler_setup()
#endif // __STATIC_ISR_TABLE__


/*
	HAL API functions for UWL
*/

/**
	@brief This function sets the rx ISR callback (for UWL).
*/
void mrf24j40_set_rx_callback(void (*func)(void));

/**
	@brief This function sets the tx-finished ISR callback (for UWL).
*/
void mrf24j40_set_tx_finished_callback(void (*tx_finished_func)(uint8_t tx_status));

/**
	@brief 	This function is the driver internal callback (for UWL).
			It's called by the true handler. 
			Note, it is not the registered handler function. 
*/
ISR2(MRF24J40_INTERRUPT_NAME);

/**
	@brief 	This function initializes and resets Mico32 GPIO pins (for UWL).
*/
int8_t	mrf24j40_hal_init(void);

/**
	@brief 	This function initializes Mico32 spi controller (for UWL).
*/
int8_t	mrf24j40_hal_spi_init(uint8_t port);

/**
	@brief 	This function closes Mico32 spi controller (for UWL).
*/
int8_t	mrf24j40_hal_spi_close(void);

/**
	@brief 	This function writes an array of bytes 
			using Mico32 spi controller (for UWL).
*/
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);

/**
	@brief 	This function reads an array of bytes 
			using Mico32 spi controller (for UWL).
*/
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

/**
	@brief 	This function implements a delay in micro-seconds.
*/
COMPILER_INLINE void mrf24j40_hal_delay_us(uint16_t delay_count)
{
	EE_mrf24j40_delay_us((unsigned int)delay_count);
}

/**
	@brief 	This function releases reset pin.
*/
COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	EE_mrf24j40_gpio_release_reset();
}

/**
	@brief 	This function holds reset.
*/
COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	EE_mrf24j40_gpio_hold_in_reset();
}

/**
	@brief 	This function terminates spi communication.
*/
COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	EE_mrf24j40_spi_clear_SSO();
}

/**
	@brief 	This function selects the slave and configures SS pin
			to have a data transfer longer than the transmit and receive registers.
*/
COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	EE_mrf24j40_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	EE_mrf24j40_spi_set_SSO(); // ss is low when transmission begins...
}

/**
	@brief 	This function is void. Kept for compatibility.
*/
COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
{
	return;
}

/**
	@brief 	This function enables Mico32 IRQ.
*/
COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	EE_mico32_enableIRQ(); 
}

/**
	@brief 	This function disables Mico32 IRQ.
*/
COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	EE_mico32_disableIRQ(); 
}

/**
	@brief 	This function returns Mico32 IRQ enabling status.
*/
COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return EE_mico32_get_IRQ_enabled(); 
}

/**
	@brief 	This function registers the GPIO interrupt handler 
			and enables MRF24J40 driver GPIO IRQ. 
*/
COMPILER_INLINE uint8_t mrf24j40_hal_int_enable(void)
{
	mico32_clear_ip_mask(1<<EE_MRF24J40_IRQ); 	
	EE_hal_mrf24j40_handler_setup(); 			
	mico32_enable_irq(ee_mrf24j40_st.irqf);
	EE_mrf24j40_enable_IRQ();	 				
	return MRF24J40_SUCCESS;
}

/**
	@brief 	This function disables MRF24J40 driver GPIO IRQ. 
*/
COMPILER_INLINE uint8_t mrf24j40_hal_int_disable(void)
{
	EE_mrf24j40_disable_IRQ();
	return MRF24J40_SUCCESS;
}

/**
	@brief 	This function returns MRF24J40 driver GPIO IRQ
			enabling status. 
*/
COMPILER_INLINE uint8_t mrf24j40_hal_int_status(void)
{
	return EE_mrf24j40_IRQ_enabled();
}

#endif /* Header Protection */

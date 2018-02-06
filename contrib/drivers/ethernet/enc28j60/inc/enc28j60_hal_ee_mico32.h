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
* @file 	enc28j60_hal_ee_mico32.h
* @brief 	ENC28J60 driver - HAL for Lattice Mico32.
* @author 	Dario Di Stefano
* @date 	2010
*/ 

#ifndef __ENC28J60_HAL_EE_MICO32_H__
#define __ENC28J60_HAL_EE_MICO32_H__

/* Needed header files */
//#include "cpu/mico32/inc/ee_internal.h"
//#include "cpu/mico32/inc/ee_irq.h"
#include <ee_irq.h>
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_spi.h"
#include "mcu/mico32/inc/ee_gpio.h"
/* Board header */
#ifdef __FPG_EYE__
#include "board/fpg-eye/inc/ee_internal.h"
#include "board/fpg-eye/inc/ee_ethernet_enc28j60.h"
#else	/* NO board */
#error "ENC28J60_HAL: No board selected!"
#endif	
/* Other used libraries */
#include "MicoUtils.h"
/* Check */
#ifndef __USE_SPI__
#error "ENC28J60 HAL EE : The SPI module from MCU is required!"
#endif
/* Types definition */
#include "enc28j60_reg.h"
#include "enc28j60_compiler.h"

/* ENC28J60 structure (used in ISR mode) */
typedef struct {	
    MicoGPIO_t* base;					// GPIO controller base address
    int irqf;							// GPIO irq flag to register the handler
    EE_TID task;						// task called inside the interrupt handler
} EE_enc28j60_st;

extern EE_enc28j60_st ee_enc28j60_st;

/* ------------------------------------------------------------------------------- */
/* Macros used into the Ethernet driver functions */
/* ------------------------------------------------------------------------------- */

/* Symbols and macros */
#define EE_ENC28J60_DEVICE_ID		(0x01)
#define EE_ENC28J60_ADDRESS_MASK	(0x1F)
#define ENC28J60_INTERRUPT_NAME()

/* Exit status for the EE_ETHERNET driver */
#define	ENC28J60_SUCCESS 			(0)		/* no error */
#define	ENC28J60_FAILURE			(-19)	/* generic error */
#define	ENC28J60_ERR_SPI_INIT		(-20)	/* error in spi initialization */
#define	ENC28J60_ERR_SPI_READ		(-21)	/* spi read error */
#define	ENC28J60_ERR_SPI_WRITE		(-22)	/* spi write error */
#define	ENC28J60_ERR_DEV_NOINIT		(-23)	/* eth device error */
#define	ENC28J60_ERR_MEM_NULL		(-24)	/* eth null pointer error */

/* Pseudo functions (Wrapper) */
#define ENC_CS_IO_f(p)				/* null definition */
#define ENC_CS_TRIS_f(p)			/* null definition */
#define DelayMs(ms)					EE_enc28j60_delay_ms(ms)
#define Reset()						EE_enc28j60_hardware_reset() // to do... asm("RESET")
#define ClearSPIDoneFlag()			/* null definition */					

/* ------------------------------------------------------------------------------- */
/* ETHERNET driver functions list */
/* ------------------------------------------------------------------------------- */

/* Macros for SPI-based ETHERNET functions */  
#define DECLARE_FUNC_SPI_ENC28J60(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_hal_spi_init(void){ \
	return cat3(EE_, lc, _config)(0); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_hal_write_byte(EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_hal_write_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_hal_read_byte(void){ \
	return cat3(EE_, lc, _receive_byte)(); } \
__INLINE__ int __ALWAYS_INLINE__  EE_enc28j60_hal_read_buffer(EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(data, len); } \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_set_SSO(void){ \
	EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_clear_SSO(void){ \
	EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_set_slave(unsigned int mask){ \
	EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), mask); } \
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_get_slave(unsigned int *pmask ){ \
	EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); }

/** 
	@brief	SPI functions 
*/
DECLARE_FUNC_SPI_ENC28J60(EE_ETHERNET_SPI_NAME_UC, EE_ETHERNET_SPI_NAME_LC)

/**
	@brief	ENC28J60 driver GPIO interrupt handler.
*/
void EE_enc28j60_hal_handler(int level);
#ifndef __STATIC_ISR_TABLE__
/** 
	@brief	This function registers GPIO ISR handler. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_handler_setup(void)
{
    EE_mico32_register_ISR(ee_enc28j60_st.irqf, EE_enc28j60_handler);	 
}
#else // __STATIC_ISR_TABLE__
#define EE_enc28j60_hal_handler_setup()
#endif // __STATIC_ISR_TABLE__

#define EE_enc28j60_hal_chip_select() 	EE_enc28j60_hal_set_SSO()
#define EE_enc28j60_hal_chip_unselect() EE_enc28j60_hal_clear_SSO()

/**
	@brief	This function sets the task should be called inside the interrupt handler.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_set_rx_task(EE_TID task)
{
	ee_enc28j60_st.task = task;
}

/**
	@brief	This function writes 2 bytes on spi bus. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_16(EE_UINT8 byte1, EE_UINT8 byte2)
{
	EE_enc28j60_hal_write_byte(byte1);
	EE_enc28j60_hal_write_byte(byte2);
}

/**
	@brief	This function contains a delay loop in micro-seconds. 
*/
void EE_enc28j60_hal_delay_us(unsigned int delay_count);

/**
	@brief	This function contains a delay loop in milli-seconds. . 
*/
void EE_enc28j60_hal_delay_ms(unsigned int delay_count);

/**
	@brief	This function reads an ETH register.
*/
REG EE_enc28j60_hal_read_ETH_register(BYTE Address);

/**
	@brief	This function reads a MAC/MII register.
*/
REG EE_enc28j60_hal_read_MAC_MII_register(BYTE Address);

/**
	@brief	This function reads a PHY register.
*/
PHYREG EE_enc28j60_hal_read_PHY_register(BYTE Register);

/**
	@brief	This function writes on a generic register.
*/
void EE_enc28j60_hal_write_register(BYTE Address, BYTE Data);

/**
	@brief	This function writes on a PHY register.
*/
void EE_enc28j60_hal_write_PHY_register(BYTE Register, WORD Data);

/**
	@brief	This function reads a byte from the ENC28J60 memory buffer.
*/
BYTE EE_enc28j60_hal_get();

/**
	@brief	This function reads an array of bytes from the ENC28J60 memory buffer.
*/
WORD EE_enc28j60_hal_get_array(BYTE *val, WORD len);

/**
	@brief	This function writes a byte to the ENC28J60 memory buffer.
*/
void EE_enc28j60_hal_put(BYTE val);

/**
	@brief	This function writes an array of bytes to the ENC28J60 memory buffer.
*/
void EE_enc28j60_hal_put_array(BYTE *val, WORD len);

/**
	@brief	This function implements a binary OR on a register.
*/
void EE_enc28j60_hal_bit_field_set_register(BYTE Address, BYTE Data);

/**
	@brief	This function implements a binary AND on a register.
*/
void EE_enc28j60_hal_bit_field_clear_register(BYTE Address, BYTE Data);

/**
	@brief	This function send a software reset command.
*/
void EE_enc28j60_hal_software_reset(void);

/**
	@brief	This function resets the device (HW reset).
*/
void EE_enc28j60_hal_hardware_reset(void);

/**
	@brief	This function selects the bank.
*/
void EE_enc28j60_hal_bank_select(WORD Register);


/* INLINE functions */

/**
	@brief	This function reads a MAC register.
*/
__INLINE__ REG __ALWAYS_INLINE__ EE_enc28j60_hal_read_MAC_register(BYTE address)
{
	return EE_enc28j60_hal_read_MAC_MII_register(address);
}

/**
	@brief	This function reads a MII register.
*/
__INLINE__ REG __ALWAYS_INLINE__ EE_enc28j60_hal_read_MII_register(BYTE address)
{
	return EE_enc28j60_hal_read_MAC_MII_register(address);
}

/**
	@brief	This function writes on a ETH register.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_ETH_register(BYTE address, BYTE data)
{
	return EE_enc28j60_hal_write_register(address, data);
}

/**
	@brief	This function writes on a MAC register.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_MAC_register(BYTE address, BYTE data)
{
	return EE_enc28j60_hal_write_register(address, data);
}

/**
	@brief	This function writes on a MII register.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_MII_register(BYTE address, BYTE data)
{
	return EE_enc28j60_hal_write_register(address, data);
}

/**
	@brief	This function enables device using reset pin (turn on). 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_enable(void)
{
	EE_enc28j60_gpio_release_reset();
}

/**
	@brief	This function disables device using reset pin (turn off). 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_disable(void)
{
	EE_enc28j60_gpio_hold_in_reset();
}

/**
	@brief	This function enables ENC28J60 reception interrupts. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_enable_IRQ(void)
{
	mico32_enable_irq(ee_enc28j60_st.irqf);
	EE_enc28j60_gpio_enable_IRQ();
}

/**
	@brief	This function disables ENC28J60 reception interrupts. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_disable_IRQ(void)
{
	EE_enc28j60_gpio_disable_IRQ();
}

/**
	@brief	This function returns ENC28J60 reception interrupts enabling status. 
*/
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_hal_IRQ_enabled(void)
{
	return EE_enc28j60_gpio_IRQ_enabled();
}

#endif //__ENC28J60_HAL_EE_MICO32_H__


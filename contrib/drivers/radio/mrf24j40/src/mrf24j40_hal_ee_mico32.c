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
* @file 	mrf24j40_hal_ee_mico32.c
* @brief 	MRF24J40 driver HAL for Mico32
			This file is part of Microchip MRF24J40 radio transceiver
			driver developed by Gianluca Franchino, Retis Lab. 
			Scuola Superiore Sant'Anna. Pisa (Italy), 02/27/2008.
			Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
* @author 	Dario Di Stefano
* @date 	2010
*/

#include "mrf24j40.h"

/* ---------------------- Global variables --------------------------------- */
EE_mrf24j40_st ee_mrf24j40_st = {
	.mode= EE_MRF24J40_POLLING, 
	.base= (MicoGPIO_t* )EE_MRF24J40_BASE_ADDRESS,
	.irqf= EE_MRF24J40_IRQ, 
	.rxcbk= EE_NULL_CBK, 
	.txcbk= EE_NULL_CBK };

/* MRF24J40 driver interrupt handler */
void EE_mrf24j40_handler(int level)
{
	MRF24J40_INTERRUPT_NAME();
	EE_gpio_common_handler(level);
}

/* This function sets MRF24J40 driver operating mode */
int EE_hal_mrf24j40_set_ISR_mode(int mode)
{
	int old_mode;
	unsigned int intst;
	
	old_mode = ee_mrf24j40_st.mode;
	if(old_mode == mode)
		return MRF24J40_SUCCESS;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	
	/* Register IRQ handler */
	EE_hal_mrf24j40_handler_setup();
	ee_mrf24j40_st.mode = mode; 	
	
	/* IRQ settings */
    if(EE_mrf24j40_need_enable_int(mode)){
		mico32_enable_irq(ee_mrf24j40_st.irqf);
		EE_mrf24j40_enable_IRQ();
	}
	else{
		mico32_disable_irq(ee_mrf24j40_st.irqf);
		EE_mrf24j40_disable_IRQ();
	}
	
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();
        
	return MRF24J40_SUCCESS;
}

/* This function sets MRF24J40 driver ISR rx callback. */
int EE_mrf24j40_set_rx_ISR_callback(EE_ISR_callback rxcbk)
{
	ee_mrf24j40_st.rxcbk = rxcbk;
	mrf24j40_set_rx_callback(rxcbk);
	
	return MRF24J40_SUCCESS;
}

/* This function sets MRF24J40 driver ISR tx callback (for UWL). */
void EE_mrf24j40_txfcbk(uint8_t tx_status)
{
	ee_mrf24j40_st.status = tx_status;
	ee_mrf24j40_st.txcbk();
}

/* This function sets MRF24J40 driver ISR tx callback. */
int EE_mrf24j40_set_tx_ISR_callback(EE_ISR_callback txcbk)
{
	ee_mrf24j40_st.txcbk = txcbk;
	mrf24j40_set_tx_finished_callback(EE_mrf24j40_txfcbk);
	
	return MRF24J40_SUCCESS;
}

/* This function reads MRF24J40 short address register. */
int EE_mrf24j40_read_short_address_register(int address)
{
	// int ret;
	// EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1);// | MRF24J40_SRCR;
	// EE_UINT8 rx_data[1];
	// EE_UINT8 tx_data[1];
	
	// tx_data[0] = add;
	// EE_mrf24j40_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_spi_set_SSO();
	// ret = EE_mrf24j40_spi_write_buffer(tx_data, 1);
	// ret = EE_mrf24j40_spi_read_buffer(rx_data, 1);
	// EE_mrf24j40_spi_clear_SSO();
	// if (ret >= 0)
		// ret = rx_data[0];
	
	// return ret;
	
	return mrf24j40_get_short_add_mem(address);
}

/* This function reads MRF24J40 long address register. */
int EE_mrf24j40_read_long_address_register(int address)
{
	// int ret;
	// EE_UINT32 add = ((address & EE_MRF24J40_LONG_ADDRESS_MASK) << 1) | EE_MRF24J40_LRCR;	// 1 a9 a8 a7 a6 a5 a4 a3 a2 a1 a0 0
	// EE_UINT8 rx_data[1];
	// EE_UINT8 tx_data[2];
	
	// EE_mrf24j40_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_spi_set_SSO();
	// tx_data[0] = (add >> 4) & 0x00FF;
	// tx_data[1] = (add << 4) & 0x00FF;
	// ret = EE_mrf24j40_spi_write_buffer(tx_data, 2);
	// ret = EE_mrf24j40_spi_read_buffer(rx_data, 1);
	// EE_mrf24j40_spi_clear_SSO();
	// if(ret >= 0)
		// ret = rx_data[0];
	
	// return ret;
	return mrf24j40_get_long_add_mem(address);
}

/* This function writes MRF24J40 short address register. */
int EE_mrf24j40_write_short_address_register(int address, EE_UINT8 data)
{
	// int ret;
	// EE_UINT8 add = ((address & EE_MRF24J40_SHORT_ADDRESS_MASK) << 1) | EE_MRF24J40_SWCR;
	// EE_UINT8 tx_data[2];
	
	// tx_data[0] = add;
	// tx_data[1] = data;
	// EE_mrf24j40_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_spi_set_SSO();
	// ret = EE_mrf24j40_spi_write_buffer(tx_data, 2);
	// EE_mrf24j40_spi_clear_SSO();
	
	// return ret;
	
	mrf24j40_set_short_add_mem(address, data);
	return MRF24J40_SUCCESS;
}

/* This function reads MRF24J40 long address register. */
int EE_mrf24j40_write_long_address_register(int address, EE_UINT8 data)
{
	// int ret;
	// EE_UINT32 add = ((address & EE_MRF24J40_LONG_ADDRESS_MASK) << 1) | EE_MRF24J40_LWCR;	// 1 a9 a8 a7 a6 a5 a4 a3 a2 a1 a0 1
	// EE_UINT8 tx_data[3];
	
	// EE_mrf24j40_spi_set_slave(EE_MRF24J40_DEVICE_ID);	
	// EE_mrf24j40_spi_set_SSO();
	// tx_data[0] = (add >> 4) & 0x00FF;
	// tx_data[1] = (add << 4) & 0x00FF;
	// tx_data[2] = data;
	// ret = EE_mrf24j40_spi_write_buffer(tx_data, 3);
	// EE_mrf24j40_spi_clear_SSO();
	
	// return ret;
	mrf24j40_set_long_add_mem(address, data);
	return MRF24J40_SUCCESS;
}

/* This function implements a delay in micro-seconds */
void EE_mrf24j40_delay_us(unsigned int delay_count)
{
	MicoSleepMicroSecs((unsigned int)delay_count);
}

/* This function resets the tranceiver via software */
int EE_mrf24j40_software_reset(void)
{
	EE_mrf24j40_write_short_address_register(MRF24J40_SOFTRST, MRF24J40_SOFTRST_MASK);
	
	return MRF24J40_SUCCESS;
}

/* This function resets the tranceiver via hardware */
int EE_mrf24j40_hardware_reset(void)
{
    EE_mrf24j40_disable();
	EE_mrf24j40_delay_us(100);
	EE_mrf24j40_enable();
	EE_mrf24j40_delay_us(100);
	
    return MRF24J40_SUCCESS;
}

/* This function enables the tranceiver releasing reset pin. */
int EE_mrf24j40_enable(void)
{
	EE_mrf24j40_gpio_release_reset();
	EE_mrf24j40_delay_us(1000);
	
    return MRF24J40_SUCCESS;
}

/* This function disables the tranceiver holding reset */
int EE_mrf24j40_disable(void)
{
	EE_mrf24j40_gpio_hold_in_reset();
	
    return MRF24J40_SUCCESS;
}


/* MRF24J40 driver functions used by UWL */

/* This function initializes Mico32 GPIO pins. */
int8_t	mrf24j40_hal_init(void)
{
    EE_mrf24j40_init();
	
	return 1;
} 

/* This function initializes Mico32 spi controller. */
int8_t	mrf24j40_hal_spi_init(uint8_t port)
{
    EE_mrf24j40_spi_config(0, EE_SPI_POLLING | EE_SPI_RXTX_BLOCK);

    return 1;
}

/* This function closes Mico32 spi controller. */
int8_t	mrf24j40_hal_spi_close(void)
{
    EE_mrf24j40_spi_close();
	
    return 1;
}

/* This function writes an array of bytes using spi interface. */
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len)
{
    EE_mrf24j40_spi_write_buffer(data, len);
	
    return 1;
}

/* This function reads an array of bytes using spi interface. */
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len)
{
    EE_mrf24j40_spi_read_buffer(data, len);
	
	return 1;
}



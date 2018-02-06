/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file ee_spi_pic32like_api.h
	@brief SPI adapted functions for compatibility with pic32 projects. 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __INCLUDE_EEMCUMICO32_SPI_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_SPI_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 SPI driver*/ 
/* ------------------------------------------------ */

#define EE_SPI_EVT_TX_DONE 					(0x01)
#define EE_SPI_EVT_RX_DONE 					(0x00)
#ifdef __USE_SPI_IRQ__
#define EE_mchp_spi_init(lc, flags)			EE_hal_spi_config(& EE_ST_NAME(lc), flags)
#else
#define EE_mchp_spi_init(uc, flags)			EE_hal_spi_config((MicoSPI_t *)EE_BASE_ADD(uc), flags)
#endif
#define EE_mchp_spi_set_tx_cbk(lc, cbk) 	EE_hal_spi_set_tx_ISR_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_spi_set_rx_cbk(lc, cbk) 	EE_hal_spi_set_rx_ISR_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_spi_write(uc, data, len)	EE_hal_spi_write_buffer_polling((MicoSPI_t *)EE_BASE_ADD(uc), data, len)
#define EE_mchp_spi_read(uc, data, len)		EE_hal_spi_read_buffer_polling((MicoSPI_t *)EE_BASE_ADD(uc), data, len)

/*
	This function is used to initialize the spi controller.
        Arguments:
            - EE_UINT8 port: port number of the spi controller
			- EE_UINT32 baudrate: operating rate of the spi interface
			- EE_UINT16 flags: special settings
        Actions: 
            - Initialize spi controller
		Return values:
			- the return value is: 	EE_SPI_OK if no errors found, 
									a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags)
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI1_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI1_NAME_UC, flags);
		#endif
	else
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI2_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI2_NAME_UC, flags);
		#endif
	#else
		#if defined(EE_SPI1_NAME_UC)
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI1_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI1_NAME_UC, flags);
		#endif
		#else
		#ifdef __USE_SPI_IRQ__
		ret = EE_mchp_spi_init(EE_SPI2_NAME_LC, flags);
		#else
		ret = EE_mchp_spi_init(EE_SPI2_NAME_UC, flags);
		#endif
		#endif
	#endif
		
	return ret;
}

/*
	This function is used to close spi controller (void for Lattice Mico32).
        Arguments:
            - EE_UINT8 port: port number of the spi controller
        Actions: 
            - Close spi controller
		Return values:
			- the return value is EE_SPI_OK.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_close(EE_UINT8 port)
{
	// not used on LM32 device...
	return EE_SPI_OK;
}

#ifdef __USE_SPI_IRQ__

/*
	This function is used to set the ISR callback (irq mode not supported).
        Arguments:
            - EE_UINT8 port: port number of the spi controller
			- EE_UINT8 event: event associated to the callback
			- void (*f)(void): pointer to the callback
        Actions: 
            - Set the ISR callback
		Return values:
			- the return value is: 	EE_SPI_OK if no errors found, 
									a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void))
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI1_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI1_NAME_LC, f);
	else
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI2_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI2_NAME_LC, f); 
	#else
		#if defined(EE_SPI1_NAME_UC)
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI1_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI1_NAME_LC, f);
		#else
		if(event == EE_SPI_EVT_RX_DONE)
			ret = EE_mchp_spi_set_rx_cbk(EE_SPI2_NAME_LC, f);
		else
			ret = EE_mchp_spi_set_tx_cbk(EE_SPI2_NAME_LC, f); 
		#endif
	#endif
		
	return ret;
}
#else	//#ifdef __USE_SPI_IRQ__

/*
	This function is used to set the ISR callback (void in polling mode).
        Arguments:
            - EE_UINT8 port: port number of the spi controller
			- EE_UINT8 event: event associated to the callback
			- void (*f)(void): pointer to the callback
        Actions: 
            - Set the ISR callback
		Return values:
			- the return value is EE_SPI_OK. 
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_set_callback(EE_UINT8 port, EE_UINT8 event, void (*f)(void))
{
	// not used in polling mode...
	return EE_SPI_OK;
}
#endif 	//#ifdef __USE_SPI_IRQ__

/*
	This function is used to transmit an array of bytes on the spi bus.
        Arguments:
            - EE_UINT8 port: port number of the spi controller
			- EE_UINT8 *data: array of bytes to be transmitted
			- EE_UINT32 len: number of bytes to transmit
        Actions: 
            - Transmit an array of bytes on the spi bus.
		Return values:
			- the return value is len when transmission is finished.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_write(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		ret = EE_mchp_spi_write(EE_SPI1_NAME_UC, data, len);
	else
		ret = EE_mchp_spi_write(EE_SPI2_NAME_UC, data, len);
	#else
		#if defined(EE_SPI1_NAME_UC)
		ret = EE_mchp_spi_write(EE_SPI1_NAME_UC, data, len);
		#else
		ret = EE_mchp_spi_write(EE_SPI2_NAME_UC, data, len);
		#endif
	#endif
		
	return ret;
}

/*
	This function is used to read an array of bytes.
        Arguments:
            - EE_UINT8 port: port number of the spi controller
			- EE_UINT8 *data: array of bytes for the received data
			- EE_UINT32 len: number of bytes to be read
        Actions: 
            - Read an array of bytes.
		Return values:
			- the return value is len when reception is finished.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_read(EE_UINT8 port, EE_UINT8 *data, EE_UINT32 len)
{
	EE_INT8 ret;
	
	#if defined(EE_SPI1_NAME_UC) && defined(EE_SPI2_NAME_UC)
	if(port==1)
		ret = EE_mchp_spi_read(EE_SPI1_NAME_UC, data, len);
	else
		ret = EE_mchp_spi_read(EE_SPI2_NAME_UC, data, len);
	#else
		#if defined(EE_SPI1_NAME_UC)
		ret = EE_mchp_spi_read(EE_SPI1_NAME_UC, data, len);
		#else
		ret = EE_mchp_spi_read(EE_SPI2_NAME_UC, data, len);
		#endif
	#endif
		
	return ret;
}

/*
	This function is used to transmit and receive a number of bytes (not implemented).
        Arguments:
            - EE_UINT8 port: port number of the spi controller
			- EE_UINT8 *data_out: array of bytes to be transmitted
			- EE_UINT8 *data_in: array of bytes for the received data
			- EE_UINT32 len: number of bytes to be read/transmitted
        Actions: 
            - Transmit and receive a number of bytes
		Return values:
			- the return value is len when reception/transmission is finished.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_spi_cycle(EE_UINT8 port, EE_UINT8 *data_out, EE_UINT8 *data_in, EE_UINT32 len)
{
	// not implemented...
	return 0;
}

#endif //__INCLUDE_EEMCUMICO32_SPI_PIC32LIKE_H__

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
	@file ee_uart_pic32like_api.h
	@brief Uart adapted functions for compatibility with pic32 projects. 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __INCLUDE_EEMCUMICO32_UART_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_UART_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 uart driver*/ 
/* ------------------------------------------------ */

#define EE_mchp_uart_init(lc, baud, bf, mode) EE_hal_uart_config(& EE_ST_NAME(lc), baud, bf)
#define EE_mchp_uart_write_byte(lc, data) EE_hal_uart_write_byte(& EE_ST_NAME(lc), data)            
#define EE_mchp_uart_read_byte(lc, data) EE_hal_uart_read_byte(& EE_ST_NAME(lc), data)  
#define EE_mchp_uart_set_rx_callback(lc, rxcbk) EE_hal_uart_set_rx_callback(& EE_ST_NAME(lc), rxcbk)

/*
	This function is used to initialize UART. 
        Arguments:
			- EE_UINT8 port: port number
            - EE_UINT32 baud: baud rate value in Hz
			- EE_UINT16 byte_format: byte format used by the uart controller
            - EE_UINT16 mode: operating mode  
        Actions: 
            - Initialize uart
        Return values:
            - the function returns the result: 	EE_UART_OK if no errors found,
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, EE_UINT16 mode)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
        ret = EE_mchp_uart_init(EE_UART1_NAME_LC, baud, byte_format, mode);
    else 
        ret = EE_mchp_uart_init(EE_UART2_NAME_LC, baud, byte_format, mode);
    #else
        #if defined(EE_UART1_NAME_LC)
        ret = EE_mchp_uart_init(EE_UART1_NAME_LC, baud, byte_format, mode);
        #else   
        ret = EE_mchp_uart_init(EE_UART2_NAME_LC, baud, byte_format, mode);
        #endif
    #endif
    
    return ret;
}


/*
	This function is used to close UART. (this function is void for Mico32 device)
        Arguments:
			- EE_UINT8 port: port number
        Actions: 
            - Nothing.
        Return values:
            - the function returns the result: 	EE_UART_OK.
												
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_close(EE_UINT8 port)
{
    return EE_UART_OK;
}

/*
	This function is used to write a byte.
        Arguments:
			- EE_UINT8 port: port number
            - EE_UINT8 data: character to be transmitted
        Actions: 
            - Write a byte
        Return values:
            - the function returns the result: 	EE_UART_OK if no errors found,
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
        ret = EE_mchp_uart_write_byte(EE_UART1_NAME_LC, data);
    else 
        ret = EE_mchp_uart_write_byte(EE_UART2_NAME_LC, data);
    #else
        #if defined(EE_UART1_NAME_LC)
        ret = EE_mchp_uart_write_byte(EE_UART1_NAME_LC, data);
        #else   
        ret = EE_mchp_uart_write_byte(EE_UART2_NAME_LC, data);
        #endif
    #endif
    
    return ret;

}

/*
	This function is used to read a byte.
        Arguments:
			- EE_UINT8 port: port number
            - EE_UINT8 *data: pointer to a character
        Actions: 
            - Read a byte
        Return values:
            - the function returns the result: 	EE_UART_OK if no errors found,
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
        ret = EE_mchp_uart_read_byte(EE_UART1_NAME_LC, data);
    else 
        ret = EE_mchp_uart_read_byte(EE_UART2_NAME_LC, data);
    #else
        #if defined(EE_UART1_NAME_LC)
        ret = EE_mchp_uart_read_byte(EE_UART1_NAME_LC, data);
        #else   
        ret = EE_mchp_uart_read_byte(EE_UART2_NAME_LC, data);
        #endif
    #endif
    
    return ret;

}

#ifdef __USE_UART_IRQ__
typedef void (*EE_mchp_ISR_callback)(EE_UINT8);
extern EE_mchp_ISR_callback ee_mchp_uart1_ISR_cbk;
extern EE_mchp_ISR_callback ee_mchp_uart2_ISR_cbk;
void ee_aux_uart1_ISR_cbk(void);
void ee_aux_uart2_ISR_cbk(void);

/*
	This function is used to set the ISR callback.
        Arguments:
			- EE_UINT8 port: port number
            - void (*RxFunc)(EE_UINT8 data): pointer of the callback
			- EE_UINT8 rxmode: operating mode (not used!)
        Actions: 
            - Set the ISR callback.
        Return values:
            - the function returns the result: 	EE_UART_OK if no errors found,
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), EE_UINT8 rxmode)
{
    EE_INT8 ret;
    
    #if defined(EE_UART1_NAME_LC) && defined(EE_UART2_NAME_LC)
    if(port==1)
    {
        ee_mchp_uart1_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART1_NAME_LC, ee_aux_uart1_ISR_cbk);
    }
    else 
    {
        ee_mchp_uart2_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART2_NAME_LC, ee_aux_uart2_ISR_cbk);
    }
    #else
        #if defined(EE_UART1_NAME_LC)
        ee_mchp_uart1_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART1_NAME_LC, ee_aux_uart1_ISR_cbk);
        #else   
        ee_mchp_uart2_ISR_cbk = RxFunc;
        ret = EE_mchp_uart_set_rx_callback(EE_UART2_NAME_LC, ee_aux_uart2_ISR_cbk);
        #endif
    #endif
    
    return ret;
}
#endif // #ifdef __USE_UART_IRQ__

#endif //__INCLUDE_EEMCUMICO32_UART_PIC32LIKE_H__

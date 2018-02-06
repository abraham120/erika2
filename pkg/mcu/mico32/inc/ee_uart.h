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
	@file 	ee_uart.h
	@brief 	Uart library header file.\n
			UART API explanation:\n
			API is generated with DECLARE_FUNC_UART(uc, lc) and only if the macros
			EE_UART1_NAME_UC, EE_UART2_NAME_UC are defined in "eecfg.h". 
	@author Dario Di Stefano
	@date 	2010
	@example
			The name of the UART module specified inside the platform and
			inside the conf.oil file is "User_Uart".
			
			The macros generated in "eecfg.h" are:\n
			\#define EE_UART1_NAME_LC user_uart\n
			\#define EE_UART1_NAME_UC USER_UART\n
			
			The user must use the lower case form of the name, "user_uart", 
			to call the functions of the UART API as shown in the following example list.
			
			Name: 				int EE_user_uart_config(int baudrate,int settings);\n
			Action:				This function configures UART controller (to change default parameters);\n
			Parameter baudrate:	operating rate;\n
			Parameter settings: flags to set byte format (see macros in ee_uart.h);\n
			Return:				EE_UART_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_uart_set_ISR_mode(int mode);\n
			Action: 			This function sets UART operating mode (to change default parameters);\n
			Parameter mode:		operating mode (see macros in ee_uart.h);\n
			Return:				EE_UART_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_uart_set_rx_ISR_callback(EE_ISR_callback rxcbk);\n
			Action: 			This function sets rx callback called inside the UART common handler (interrupt mode only);\n
			Parameter rxcbk:	pointer to the callback;\n
			Return:				EE_UART_OK.\n
			
			Name: 				int EE_user_uart_set_tx_ISR_callback(EE_ISR_callback txcbk);\n
			Action: 			This function sets tx callback called inside the UART common handler (interrupt mode only);\n
			Parameter rxcbk:	pointer to the callback;\n
			Return:				EE_UART_OK.\n
			
			Name: 				int EE_user_uart_send_byte(EE_UINT8 data);\n
			Action: 			This function writes a byte using uart interface;\n
			Parameter data:		character to be transmitted;\n
			Return:				1 if the operation is completed successfully, a negative number otherwise (see error codes in ee_uart.h).\n
			
			Name: 				int EE_user_uart_receive_byte(EE_UINT8 *data);\n
			Action: 			This function receives a byte using uart interface;\n
			Parameter data:		address of the variable to copy to;\n
			Return:				1 if the operation is completed successfully, a negative number otherwise (see error codes in ee_uart.h).\n
			
			Name: 				int EE_user_uart_send_buffer(const void *vet, int len);\n
			Action: 			This function writes a number of bytes using uart interface;\n
			Parameter vet:		array of bytes to be transmitted;\n
			Parameter len:		number of bytes to transmit;\n
			Return:				the number of bytes transmitted or a negative number in case of error (see error codes in ee_uart.h).\n
			
			Name: 				int EE_user_uart_receive_buffer(void *vet, int len);\n
			Action:				This function receives a number of bytes using uart interface;\n
			Parameter vet:		array to write to;\n
			Parameter len:		number of bytes to receive;\n
			Return:				the number of bytes received or a negative number in case of error (see error codes in ee_uart.h).\n
			
			Name: 				int EE_user_uart_enable_IRQ(int ier);\n
			Action:				This function enables UART IRQ (interrupt mode only);\n
			Parameter ier:		IER register desired;\n
			Return:				EE_UART_OK.\n
			
			Name: 				int EE_user_uart_disable_IRQ(void);\n
			Action:				This function disables UART IRQ (interrupt mode only);\n
			Return:				EE_UART_OK.\n
			
			Name: 				int EE_user_uart_return_error(void);\n
			Action:				This function returns the code of the last error condition occurred;\n
			Return:				an error code.\n
			
			Name: 				int EE_user_uart_is_rx_ready(void);\n
			Action: 			This function verifies if rx status is ready;\n
			Return: 			1 if rx is ready, 0 if rx is not ready.\n
*/

#ifndef __INCLUDE_EEMCUMICO32_UART_H__
#define __INCLUDE_EEMCUMICO32_UART_H__

//#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
//#include <cpu/mico32/inc/ee_irq.h>
#include <MicoUart.h>               // to use LATTICE data structures.

/* mico-uart register structure (defined in MicoUart.h) */
//    typedef struct st_MicoUart{
//        volatile unsigned int rxtx;
//        volatile unsigned int ier;
//        volatile unsigned int iir;
//        volatile unsigned int lcr;
//        volatile unsigned int mcr;
//        volatile unsigned int lsr;
//        volatile unsigned int msr;
//        volatile unsigned int div;
//    }MicoUart_t;

#define EE_UART_BIT8_ODD    (0x0B)  // 8 bit, odd parity
#define EE_UART_BIT8_EVEN   (0x1B)  // 8 bit, even parity
#define EE_UART_BIT8_NO     (0x03)  // 8 bit, no parity

#define EE_UART_BIT7_ODD    (0x0A)  // 7 bit, odd parity
#define EE_UART_BIT7_EVEN   (0x1A)  // 7 bit, even parity
#define EE_UART_BIT7_NO     (0x02)  // 7 bit, no parity

#define EE_UART_BIT6_ODD    (0x09)  // 6 bit, odd parity
#define EE_UART_BIT6_EVEN   (0x19)  // 6 bit, even parity
#define EE_UART_BIT6_NO     (0x01)  // 6 bit, no parity

#define EE_UART_BIT5_ODD    (0x08)  // 5 bit, odd parity
#define EE_UART_BIT5_EVEN   (0x18)  // 5 bit, even parity
#define EE_UART_BIT5_NO     (0x00)  // 5 bit, no parity

#define EE_UART_BIT_STOP_1  (0x00)  // 1 stop bit
#define EE_UART_BIT_STOP_2  (0x04)  // 2 stop bits

/* Uart operating modes */
#define EE_UART_POLLING     (0x00)  // polling mode
#define EE_UART_RX_ISR      (0x01)  // Reception IRQ enabled 
#define EE_UART_TX_ISR      (0x02)  // Transmission IRQ enabled 
#define EE_UART_RXTX_ISR    (0x03)  // Transmission/Reception IRQ enabled 
#define EE_UART_RX_BLOCK    (0x10)  // Blocking mode in reception
#define EE_UART_TX_BLOCK    (0x20)  // Blocking mode in transmission
#define EE_UART_RXTX_BLOCK  (0x30)  // Blocking mode in transmission/reception

/* Uart return values */
#define EE_UART_OK                  (0x00)
#define EE_UART_ERR_RX_BUF_FULL     (-20)
#define EE_UART_ERR_RX_BUF_EMPTY    (-21)
#define EE_UART_ERR_TX_BUF_FULL     (-22)
#define EE_UART_ERR_TX_BUF_EMPTY    (-23)
#define EE_UART_ERR_BAD_VALUE       (-24)
#define EE_UART_ERR_TX_NOT_READY    (-25)
#define EE_UART_ERR_RX_NOT_READY    (-26)

/* Macros for tests */
#define EE_uart_need_init_rx_buf(old,new)  ( !((old) & EE_UART_RX_ISR) && ((new) & EE_UART_RX_ISR) )
#define EE_uart_need_init_tx_buf(old,new)  ( !((old) & EE_UART_TX_ISR) && ((new) & EE_UART_TX_ISR) )
#define EE_uart_need_enable_rx_int(old, new)  ( (new) & EE_UART_RX_ISR )
#define EE_uart_need_disable_rx_int(old, new)  ( !((new) & EE_UART_RX_ISR) )
#define EE_uart_enabled_rx_int(mode)  ( (mode) & EE_UART_RX_ISR )
#define EE_uart_need_enable_int(new)  ( ((new) & EE_UART_RX_ISR) || ((new) & EE_UART_TX_ISR) )
#define EE_uart_tx_polling(mode) ( !((mode) & EE_UART_TX_ISR) )
#define EE_uart_rx_polling(mode) ( !((mode) & EE_UART_RX_ISR) )
#define EE_uart_rx_block(mode) ( ((mode) & EE_UART_RX_BLOCK) )
#define EE_uart_tx_block(mode) ( ((mode) & EE_UART_TX_BLOCK) )

/* Uart utils */
#define EE_UART_NULL_VET            ((EE_UINT8 *)0) // Used by buffer array

#ifdef __USE_UART_IRQ__
 
/* UART structure (used in ISR mode): */
typedef struct {
	int err;						// last error condition 					
	int mode;						// uart operating mode (polling, isr, ...)
    MicoUart_t* base;				// controller base address
    int irqf;						// irq flag to register the handler
    EE_ISR_callback rxcbk;			// rx callback
    EE_ISR_callback txcbk;			// tx callback
    EE_buffer rxbuf;				// rx buffer used in isr mode
    EE_buffer txbuf;				// tx buffer used in isr mode
} EE_uart_st;

#else // #ifdef __USE_UART_IRQ__

/* UART structure (used in polling mode): */
typedef struct {
	int err;							// last error condition 					
	int mode;							// uart operating mode (polling, isr, ...)
    MicoUart_t* base;					// controller base address
    int irqf;							// irq flag to register the handler
} EE_uart_st;

#endif // #ifdef __USE_UART_IRQ__


/********************** Internal functions **************************/

/**
	@brief 				This function configures UART controller 
	@param usp 			UART structure pointer
	@param baudrate 	rate value in Hz
	@param settings 	settings value (please, use macros defined in ee_uart.h)   
	@return 			EE_UART_OK if no errors found, a negative number in case of errors
*/
int EE_hal_uart_config(EE_uart_st* usp, int baudrate, int setttings);                   


/**
	@brief 			This function changes UART operating mode. 
    @param usp 		UART structure pointer
	@param mode 	UART desired operating mode (please, see macros in ee_uart.h)
	@return 		EE_UART_OK if no errors found, EE_UART_ERR_BAD_VALUE if bad argument passed 
*/
int EE_hal_uart_set_ISR_mode(EE_uart_st* usp, int mode);                                


/**
	@brief 					This function sets rx callback called after execution of the UART handler. 
    @param usp 				UART structure pointer
    @param isr_rx_callback	Name of the function to be called
    @return 				EE_UART_OK
*/
int EE_hal_uart_set_rx_callback(EE_uart_st* usp, EE_ISR_callback isr_rx_callback);      


/**
	@brief 					This function sets tx callback called after execution of the UART handler. 
	@param usp 				UART structure pointer
	@param isr_tx_callback 	Name of the function to be called
	@return 				EE_UART_OK
*/
int EE_hal_uart_set_tx_callback(EE_uart_st* usp, EE_ISR_callback isr_rx_callback);      


/**
	@brief 			This function sends one byte.
    @param usp 		UART structure pointer
    @param data 	Character to be transmitted 
    @return			1 if data is transmitted (tx polling mode) or 
					loaded in the tx buffer (tx isr mode), else the return value is < 0 
*/
int EE_hal_uart_write_byte(EE_uart_st* usp, EE_UINT8 data);                                


/**
	@brief 			This function reads one byte.
	@param usp 		UART structure pointer
    @param data 	Address of the location (variable) to be written 
	@return  		1 if data is read form the rx register (rx polling mode) or
					extracted from the rx buffer, else the return value is < 0 
*/
int EE_hal_uart_read_byte(EE_uart_st* usp, EE_UINT8 *data);                             


/**
	@brief 			This function reads an array of characters.
    @param usp		UART structure pointer
    @param vet		address of the first location to be written with the received characters
    @param len		number of characters to read
    @return			the number of characters read/extracted (polling/isr mode), else the return value is < 0        
*/
int EE_hal_uart_read_buffer(EE_uart_st* usp, void *vet, int len);                       


/**
	@brief 			This function writes an array of characters.
	@param usp 		UART structure pointer
    @param vet 		address of the first character to be transmitted
    @param len		number of characters to transmit
    @return			the number of characters transmitted/loaded (polling/isr mode), else the return value is < 0 
*/
int EE_hal_uart_write_buffer(EE_uart_st* usp, const void *vet, int len);                     


/**
	@brief  		This function enables UART IRQ.
    @param usp 		UART structure pointer
    @param ier		value to be loaded in the ier register (please, see MicoUart.h from Lattice)
    @return   		EE_UART_OK if no errors found     
*/
int EE_hal_uart_enable_IRQ(EE_uart_st* usp, int ier);                                   


/**
	@brief			This function disables UART IRQ.
    @param usp		UART structure pointer
	@return   		EE_UART_OK 
*/
int EE_hal_uart_disable_IRQ(EE_uart_st* usp);                                           

/**
	@brief			This function returns the error condition stored in the uart structure.
    @param usp		UART structure pointer
    @return			code of the last error condition (error code list reported in ee_uart.h)
*/
int EE_hal_uart_return_error(EE_uart_st* usp);                                         

/**
	@brief 			This function verifies if rx status is ready
	@param uartc	pointer to the uart registers structure
	@return 		1 if rx is ready, 0 if rx is not ready
*/
__INLINE__ int __ALWAYS_INLINE__ EE_hal_uart_is_rx_ready(MicoUart_t *uartc)
{
    return (uartc->lsr & MICOUART_LSR_RX_RDY_MASK) != 0;
}


#ifdef __USE_UART_IRQ__
 
/* Uart settings */
#define EE_UART_MSGSIZE     (1)		// Size (number of characters) of an UART message (for buffer usage in IRQ mode)
#define EE_UART_BUFSIZE     (16)	// Buffer size (number of messages)

/**
	The UART handler works for rx and tx interrupts. In case of rx interrupts
	push the received character in the rx queue, then calls the user callback. 
	In case of tx interrupts extracts and transmits the characters of the tx buffer,
	then calls the user callaback.
	
	@brief 			This function is UART IRQ handler.
	@param level 	IRQ number
*/
void EE_uart_common_handler(int level);                                                 //handler

#ifndef __STATIC_ISR_TABLE__
/**
	@brief 			This function sets the interrupt handler
	@param usp 		UART controller structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_uart_handler_setup(EE_uart_st* usp)
{
	/* Register IRQ handler */
    EE_mico32_register_ISR(usp->irqf, EE_uart_common_handler);	
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_uart_handler_setup(usp)
#endif // __STATIC_ISR_TABLE__

/* Macro for Structure declaration */
#define DECLARE_STRUCT_UART(uc, lc) \
  extern EE_uart_st EE_ST_NAME(lc);
  
/* Macro for structure definition */
#define DEFINE_STRUCT_UART(uc, lc) \
EE_uart_st cat3(ee_, lc, _st) = { \
    .err=EE_UART_OK, .mode= EE_UART_POLLING | EE_UART_RXTX_BLOCK, .base= (MicoUart_t* )cat2(uc, _BASE_ADDRESS),\
    .irqf= cat2(uc, _IRQ), .rxcbk= EE_NULL_CBK, .txcbk= EE_NULL_CBK,\
    .rxbuf.data= EE_VETRX_NAME(lc),.txbuf.data= EE_VETTX_NAME(lc)};
	
/* Macro for vectors (buffers) definition */  
#define DEFINE_VET_UART(uc, lc) \
EE_UINT8 EE_VETRX_NAME(lc)[EE_UART_BUFSIZE]; \
EE_UINT8 EE_VETTX_NAME(lc)[EE_UART_BUFSIZE];  

/* Interrupt mode API */	
#define DECLARE_FUNC_UART(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _is_rx_ready)(void){ \
    return EE_hal_uart_is_rx_ready((MicoUart_t* )cat2(uc, _BASE_ADDRESS)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
    return EE_hal_uart_config(& EE_ST_NAME(lc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_ISR_mode)(int mode){ \
    return EE_hal_uart_set_ISR_mode(& EE_ST_NAME(lc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_rx_ISR_callback)(EE_ISR_callback rxcbk){ \
    return EE_hal_uart_set_rx_callback(& EE_ST_NAME(lc), rxcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_tx_ISR_callback)(EE_ISR_callback txcbk){ \
    return EE_hal_uart_set_tx_callback(& EE_ST_NAME(lc), txcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_byte)(EE_UINT8 data){ \
    return EE_hal_uart_write_byte(& EE_ST_NAME(lc), data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_byte)(EE_UINT8 *data){ \
    return EE_hal_uart_read_byte(& EE_ST_NAME(lc), data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_buffer)(const void *vet, int len){ \
    return EE_hal_uart_write_buffer(& EE_ST_NAME(lc), vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_buffer)(void *vet, int len){ \
    return EE_hal_uart_read_buffer(& EE_ST_NAME(lc), vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(int ier){ \
    return EE_hal_uart_enable_IRQ(& EE_ST_NAME(lc), ier); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
    return EE_hal_uart_disable_IRQ(& EE_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _return_error)(void){ \
    return EE_hal_uart_return_error(& EE_ST_NAME(lc)); }
    
/* User functions (API): */  
#ifdef EE_UART1_NAME_UC
DECLARE_STRUCT_UART(EE_UART1_NAME_UC, EE_UART1_NAME_LC)
#endif  

#ifdef EE_UART2_NAME_UC
DECLARE_STRUCT_UART(EE_UART2_NAME_UC, EE_UART2_NAME_LC)
#endif  

/* Return the Uart structure for the component associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_uart_st *EE_get_uart_st_from_level(int level);


#ifndef EE_UART2_NAME_UC
/* If there is only one component of this kind, no test is done */
/**
	@brief 			This function is used inside the handler to get UART structure pointer
	@param level 	IRQ level
    @return 		the pointer of the structure associated to the IRQ number passed as argument
*/
__INLINE__ EE_uart_st * __ALWAYS_INLINE__ EE_get_uart_st_from_level(int level)
{
    return & EE_ST_NAME(EE_UART1_NAME_LC);
}
#else /* #ifndef EE_UART2_NAME_UC */
__INLINE__ EE_uart_st * __ALWAYS_INLINE__ EE_get_uart_st_from_level(int level)
{
    if (level == EE_IRQ_NAME(EE_UART1_NAME_UC))
        return & EE_ST_NAME(EE_UART1_NAME_LC);
    else
        return & EE_ST_NAME(EE_UART2_NAME_LC);
}
#endif /* #ifndef EE_UART_NAME2_UC */

#else // #ifdef __USE_UART_IRQ__

/* Macro for Structure declaration */
#define DECLARE_STRUCT_UART(uc, lc) \
  extern EE_uart_st EE_ST_NAME(lc);
  
/* Macro for structure definition */
#define DEFINE_STRUCT_UART(uc, lc) \
EE_uart_st cat3(ee_, lc, _st) = { \
    .err=EE_UART_OK, .mode= EE_UART_POLLING | EE_UART_RXTX_BLOCK, .base= (MicoUart_t* )cat2(uc, _BASE_ADDRESS),\
    .irqf= cat2(uc, _IRQ) };
	
/* Polling mode API */	
#define DECLARE_FUNC_UART(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _is_rx_ready)(void){ \
    return EE_hal_uart_is_rx_ready((MicoUart_t* )cat2(uc, _BASE_ADDRESS)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
    return EE_hal_uart_config(& EE_ST_NAME(lc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_ISR_mode)(int mode){ \
    return EE_hal_uart_set_ISR_mode(& EE_ST_NAME(lc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_byte)(EE_UINT8 data){ \
    return EE_hal_uart_write_byte(& EE_ST_NAME(lc), data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_byte)(EE_UINT8 *data){ \
    return EE_hal_uart_read_byte(& EE_ST_NAME(lc), data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_buffer)(const void *vet, int len){ \
    return EE_hal_uart_write_buffer(& EE_ST_NAME(lc), vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_buffer)(void *vet, int len){ \
    return EE_hal_uart_read_buffer(& EE_ST_NAME(lc), vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(int ier){ \
    return EE_hal_uart_enable_IRQ(& EE_ST_NAME(lc), ier); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
    return EE_hal_uart_disable_IRQ(& EE_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _return_error)(void){ \
    return EE_hal_uart_return_error(& EE_ST_NAME(lc)); }
    
/* User functions (API): */  
#ifdef EE_UART1_NAME_UC
DECLARE_STRUCT_UART(EE_UART1_NAME_UC, EE_UART1_NAME_LC)
#endif  

#ifdef EE_UART2_NAME_UC
DECLARE_STRUCT_UART(EE_UART2_NAME_UC, EE_UART2_NAME_LC)
#endif  

#endif // #ifdef __USE_UART_IRQ__

/* User functions (API): */  
#ifdef EE_UART1_NAME_UC
DECLARE_FUNC_UART(EE_UART1_NAME_UC, EE_UART1_NAME_LC)
#endif  

#ifdef EE_UART2_NAME_UC
DECLARE_FUNC_UART(EE_UART2_NAME_UC, EE_UART2_NAME_LC)
#endif

#ifdef __USE_MICO_PIC32LIKE_API__
#include "mcu/mico32/inc/ee_uart_pic32like_api.h"
#endif // #ifdef __USE_MICO_PIC32LIKE_API__

#endif // __INCLUDE_EEMCUMICO32_UART_H__



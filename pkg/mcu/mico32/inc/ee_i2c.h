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
	@file 	ee_i2c.h
	@brief 	I2C library header file.\n
			I2C API explanation:\n
			API is generated with DECLARE_FUNC_I2C(uc, lc) and only if the macros
			EE_I2C1_NAME_UC, EE_I2C2_NAME_UC are defined in "eecfg.h". 
	@author Dario Di Stefano
	@date 	2010
	@example 	
			The name of the I2C module specified inside the platform and
			inside the conf.oil file is "User_I2c".
			
			The macros generated in "eecfg.h" are:\n
			\#define EE_I2C1_NAME_LC user_i2c\n
			\#define EE_I2C1_NAME_UC USER_I2C\n
			
			The user must use the lower case form of the name, "user_i2c", 
			to call the functions of the I2C API as shown in the following example list.
				
			Name: 				int EE_user_i2c_config(int baudrate,int settings);\n
			Action:				This function configures I2C controller (to change default parameters);\n
			Parameter baudrate:	operating rate;\n
			Parameter settings: binary OR of flags for special settings (see macros in ee_i2c.h);\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_set_mode(int mode);\n
			Action:				This function configures I2C controller operating mode (to change default parameters);\n
			Parameter mode:		operating mode (see macros in ee_i2c.h);\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_set_rx_callback(EE_ISR_callback rxcbk);\n
			Action:				This function sets RX isr callback (interrupt mode only);\n
			Parameter rxcbk:	pointer to the callback;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_set_tx_callback(EE_ISR_callback txcbk);\n
			Action:				This function sets TX isr callback (interrupt mode only);\n
			Parameter txcbk:	pointer to the callback;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_send_byte(EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)\n
			Action:				This function sends a byte;\n
			Parameter device:	slave address;\n
			Parameter address:	memory address;\n
			Parameter data:		data to send;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_receive_byte(EE_UINT8 device, EE_UINT8 address);\n
			Action:				This function receives a byte;\n
			Parameter device:	slave address;\n
			Parameter address:	memory address;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_send_buffer(EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *vet, int len);\n
			Action:				This function sends an array of bytes;\n
			Parameter device:	slave address;\n
			Parameter address:	memory address;\n
			Parameter vet:		array of bytes to send;\n
			Parameter len:		number of bytes to send;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n

			Name: 				int EE_user_i2c_receive_buffer(EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *vet, int len);\n
			Action:				This function receives an array of bytes;\n
			Parameter device:	slave address;\n
			Parameter address:	memory address;\n
			Parameter vet:		array to load with the received data;\n
			Parameter len:		number of bytes to receive;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_enable_IRQ(void);\n
			Action:				This function enables I2C IRQ (interrupt mode only);\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_disable_IRQ(void);\n
			Action:				This function disables I2C IRQ (interrupt mode only);\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_enable(void);\n
			Action:				This function enables I2C driver control;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_disable(void);\n
			Action:				This function disables I2C driver control;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_start(void);\n
			Action:				This function sends an I2C start signal;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_stop(void);\n
			Action:				This function sends an I2C stop signal;\n
			Return:				EE_I2C_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_i2c_return_error(void);\n
			Action:				This function reads the code of the last error condition occurred;\n
			Return:				the code of the last error condition occurred.\n
			
			Name: 				int EE_user_i2c_is_idle(void);\n
			Action:				This function verifies the status of the I2C bus;\n
			Return:				1 if I2C bus is idle, else 0.\n
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_H__
#define __INCLUDE_EEMCUMICO32_I2C_H__

//#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
//#include <cpu/mico32/inc/ee_irq.h>
#include "OpenCoresI2CMaster.h"

/* mico-i2c register structure (defined in OpenCoresI2CMaster.h) */
//   typedef struct st_OCI2CMDev_t {
//        /* Prescale register: lower byte, R/W */
//        volatile unsigned int PrescaleLo;
//        /* Prescale register: upper byte, R/W */
//        volatile unsigned int PrescaleHi;
//        /* Control register: R/W */
//        volatile unsigned int Control;
//        /* Data register: read = rxdata, write = txdata */
//        volatile unsigned int Data;
//        /* Command/Status register: !!!read = status!!!, !!!write = command!!! */
//        volatile unsigned int StatusCommand;	
//    }OCI2CMDev_t;
 
/* i2c settings */
#define EE_I2C_MSGSIZE 				(1)		// Size (number of characters) of an I2C message (for buffer usage in IRQ mode)	
#define EE_I2C_BUFSIZE 				(12)	// Buffer size (number of messages)

/* i2c bit masks */
#define EE_I2C_RW_MASK              (0x01)	// 1=Read, 0=Write
#define EE_I2C_ADDR_MASK            (0xFE)
#define EE_I2C_STATUS_RX_RDY_MASK	(0x01)
#define EE_I2C_CTL_RX_INTR_EN_MASK	(0x02)
#define EE_I2C_STATUS_TX_RDY_MASK	(0x03)
#define EE_I2C_CTL_TX_INTR_EN_MASK	(0x04)

/* i2c return values */			
#define EE_I2C_OK					(0)
#define EE_I2C_ERR_RECEPTION   		(-30)
#define EE_I2C_ERR_TRANSMISSION		(-31)
#define EE_I2C_ERR_BAD_VALUE		(-32)
#define EE_I2C_ERR_ADD_ACK			(-33)
#define EE_I2C_ERR_DATA_ACK			(-34)
#define EE_I2C_ERR_ARB_LOST			(-35)
#define EE_I2C_ERR_DEV_ACK			(-36)

/* i2c operating modes */
#define EE_I2C_POLLING				(0x00)
#define EE_I2C_RX_ISR				(0x01)
#define EE_I2C_TX_ISR				(0x02)	
#define EE_I2C_RXTX_ISR				(0x03)	
#define EE_I2C_RX_BLOCK				(0x10)
#define EE_I2C_TX_BLOCK				(0x20)
#define EE_I2C_RXTX_BLOCK  			(0x30)	

/* Macro for tests */
#define EE_i2c_need_init_rx_buf(old,new)  (!((old) & EE_I2C_RX_ISR) && ((new) & EE_I2C_RX_ISR))
#define EE_i2c_need_init_tx_buf(old,new)  (!((old) & EE_I2C_TX_ISR) && ((new) & EE_I2C_TX_ISR))
#define EE_i2c_need_enable_int(new)  ( ((new) & EE_I2C_RX_ISR) || ((new) & EE_I2C_TX_ISR) )
#define EE_i2c_tx_polling(mode) ( !((mode) & EE_I2C_TX_ISR) )
#define EE_i2c_rx_polling(mode) ( !((mode) & EE_I2C_RX_ISR) )
#define EE_i2c_bus_idle(status) ( !((status) & OCI2CM_STATUS_BUS_BUSY) )
#define EE_i2c_pend_for_TIP_done(status) { while((status) & OCI2CM_STATUS_TRANSFER); }
 
/* Internal functions */

/**
	@brief 			This function writes one character on the i2c bus.
					Issue a start signal, transmit device address (write mode), 
					transmit slave memory address, tranmsit data, issue a stop signal. 
	@param i2cc 	I2C base address
	@param device 	slave address
	@param address 	slave memory address to be written
	@param data 	data to be transmitted
	@return			EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
					EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
					EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
					EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_write_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	

/**
	@brief			This function reads one character from the i2c bus.
					Issue a start signal, transmit device address (write mode), 
					transmit slave memory address, transmit device address (read mode), 
					read data and transmit NACK, issue a stop signal. 
	@param i2cc 	I2C base address
	@param device	slave address
	@param address	slave memory address to be read
	@return			EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
					EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
					EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
					data 				if all is ok
*/
int EE_hal_i2c_read_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address);



/**
	@brief			This function reads mote than one characters from the i2c bus.
					Issue a start signal, transmit device address (write mode), 
					transmit slave memory address, transmit device address (read mode), 
					read data and transmit ACK/NACK, issue a stop signal. 
	@param i2cc 	I2C base address
	@param device 	slave address
	@param address 	slave memory address to be read
	@param data 	array to be loaded with the read characters
	@param len 		number of characters to be read
	@return 		EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
					EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
					EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
					EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_read_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);		


/**
	@brief			This function writes more than one characters on the i2c bus.
					Issue a start signal, transmit device address (write mode), 
					transmit slave memory address, tranmsit all data, issue a stop signal. 
	@param i2cc 	I2C base address
	@param device 	slave address
	@param address	slave memory address to be written
	@param data		array of characters to be transmitted
	@param len		number of characters to be transmitted
	@return			EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
					EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
					EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
					EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_write_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *data, int len);	

/**
	@brief 			This function issues only a start signal on the i2c bus.
	@param i2cc		I2C base address
	@return			EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
					EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_start(OCI2CMDev_t* i2cc);

/**
	@brief 			This function issues only a stop signal on the i2c bus.
	@param i2cc		I2C base address
	@return			EE_I2C_OK 	
*/																	
int EE_hal_i2c_stop(OCI2CMDev_t* i2cc);


/**
	@brief			This function disables i2c core.
	@param i2cc		I2C base address
	@return			EE_I2C_OK 	
*/	
int EE_hal_i2c_disable(OCI2CMDev_t* i2cc);		
	
/**
	@brief			This function enables i2c core.
	@param i2cc		I2C base address
	@return			EE_I2C_OK 		
*/														
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_enable(OCI2CMDev_t* i2cc)
{
	i2cc->Control |= OCI2CM_CTL_CORE_ENABLE;  
	return EE_I2C_OK;
}

/**
	@brief			This function enables interrupts.
	@param i2cc		I2C base address
	@return			EE_I2C_OK 
*/																
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_enable_IRQ(OCI2CMDev_t* i2cc)
{
	i2cc->Control |= OCI2CM_CTL_INT_ENABLE;
	return EE_I2C_OK;	
}

/**
	@brief			This function disables interrupts.
	@param i2cc		I2C base address
	@return			EE_I2C_OK 
*/													
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_disable_IRQ(OCI2CMDev_t* i2cc)
{
	i2cc->Control &= ~OCI2CM_CTL_INT_ENABLE;
	return EE_I2C_OK;
}

/**
	@brief			This function checks if the i2c bus is idle.
	@param i2cc		I2C base address
	@return			1 if i2c bus is idle else 0	
*/	
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_idle(OCI2CMDev_t* i2cc)
{
	return EE_i2c_bus_idle(i2cc->StatusCommand);
}


#ifdef __USE_I2C_IRQ__ /* not yet supported */

/* I2C structure (used in ISR mode) */
typedef struct {
	int err;							// last error condition
	int mode;							// i2c operating mode (polling, isr, ...)
	int ir;								// flag to discriminate interrupt source (rx or tx)
    OCI2CMDev_t* base;					// controller base address
    int irqf;							// irq flag
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
    EE_buffer rxbuf;					// rx buffer used in isr mode
    EE_buffer txbuf;					// tx buffer used in isr mode
} EE_i2c_st;

/* Macro for Structure declaration */
#define DECLARE_STRUCT_I2C(uc, lc) \
  extern EE_i2c_st EE_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_I2C(uc, lc) \
EE_i2c_st cat3(ee_, lc, _st) = { \
	.err=EE_I2C_OK, .mode= EE_I2C_POLLING | EE_I2C_RXTX_BLOCK, .base= (OCI2CMDev_t* )cat2(uc, _BASE_ADDRESS),\
	.irqf= cat2(uc, _IRQ), .rxcbk= EE_NULL_CBK, .txcbk= EE_NULL_CBK,\
	.rxbuf.data= EE_VETRX_NAME(lc),.txbuf.data= EE_VETTX_NAME(lc)};
/* Macro for vectors (buffers) definition */  
#define DEFINE_VET_I2C(uc, lc) \
EE_UINT8 EE_VETRX_NAME(lc)[EE_I2C_BUFSIZE]; \
EE_UINT8 EE_VETTX_NAME(lc)[EE_I2C_BUFSIZE];  

/**
	@brief			This function configures i2c controller (not yet supported). 
	@param i2csp	I2C structure
	@param baudrate	transmission rate 
	@return			EE_I2C_OK 	
*/					
int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate);

/**
	@brief			This function sets i2c controller mode (not yet supported).
	@param i2csp	I2C structure
	@param mode		desired mode
	@return			EE_I2C_OK 	
*/	
int EE_hal_i2c_set_mode(EE_i2c_st* i2csp, int mode);	

/**
	@brief			This function sets rx callback (not yet supported).
	@param i2csp	I2C structure
	@param isr_rx_callback	rx callback pointer
	@return			EE_I2C_OK 	
*/	
int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback);	

/**
	@brief			This function sets tx callback (not yet supported).
	@param i2csp	I2C structure
	@param isr_tx_callback	tx callback pointer
	@return			EE_I2C_OK 	
*/					
int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback);			

/**
	@brief			This function returns the code of the last error condition occurred (not yet supported).
	@param i2csp	I2C structure
	@return			code of the last error condition occurred
*/																								
int EE_hal_i2c_return_error(EE_i2c_st* i2csp);			

/**
	@brief			This function writes a byte with I2C interface 
					configured in IRQ mode (not yet supported).
	@param i2csp	I2C structure
	@param device	slave address
	@param address	memory address
	@param data		data to be transmitted
	@return			EE_I2C_OK if no error occurs else an error code.	
*/	
int EE_hal_i2c_write_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	

/**
	@brief			This function reads a byte with I2C interface 
					configured in IRQ mode (not yet supported).
	@param i2csp	I2C structure
	@param device	slave address
	@param address	memory address
	@return			EE_I2C_OK if no error occurs else an error code.	
*/	
int EE_hal_i2c_read_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address);	

/**
	@brief			This function reads an array of bytes with I2C interface 
					configured in IRQ mode (not yet supported).
	@param i2csp	I2C structure
	@param device	slave address
	@param address	memory address
	@param data		array to be loaded with the received data
	@param len		number of bytes to be received
	@return			EE_I2C_OK if no error occurs else an error code.	
*/
int EE_hal_i2c_read_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);

/**
	@brief			This function writes an array of bytes with I2C interface 
					configured in IRQ mode (not yet supported).
	@param i2csp	I2C structure
	@param device	slave address
	@param address	memory address
	@param data		array of bytes to be transmitted
	@param len		number of bytes to be transmitted
	@return			EE_I2C_OK if no error occurs else an error code.	
*/
int EE_hal_i2c_write_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *data, int len);
	
/**
	@brief			This function is the I2C interrupt handler.
	@param level	IRQ level	
*/
void EE_i2c_common_handler(int level);		

#ifndef __STATIC_ISR_TABLE__
/**
	@brief 			This function sets the interrupt handler
	@param i2csp 	I2C driver structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_i2c_handler_setup(EE_i2c_st* i2csp)
{
	/* Register IRQ handler */
    EE_mico32_register_ISR(i2csp->irqf, EE_i2c_common_handler);	
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_i2c_handler_setup(i2csp)
#endif // __STATIC_ISR_TABLE__															
							
/* Interrupt mode API */
#define DECLARE_FUNC_I2C(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
	return EE_hal_i2c_config(& EE_ST_NAME(lc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_mode)(int mode){ \
	return EE_hal_i2c_set_mode(& EE_ST_NAME(lc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_rx_callback)(EE_ISR_callback rxcbk){ \
	return EE_hal_i2c_set_rx_callback(& EE_ST_NAME(lc), rxcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_tx_callback)(EE_ISR_callback txcbk){ \
	return EE_hal_i2c_set_tx_callback(& EE_ST_NAME(lc), txcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_byte)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 data){ \
	int ret; \
	if(EE_i2c_tx_polling(EE_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_write_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, data); \
	else \
		ret = EE_hal_i2c_write_byte_irq(& EE_ST_NAME(lc), device, address, data); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_byte)(EE_UINT8 device, EE_UINT8 address){ \
	int ret; \
	if(EE_i2c_rx_polling(EE_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_read_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address); \
	else \
		ret = EE_hal_i2c_read_byte_irq(& EE_ST_NAME(lc), device, address); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_buffer)(EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *vet, int len){ \
	int ret; \
	if(EE_i2c_tx_polling(EE_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_write_buffer_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, vet, len); \
	else \
		ret = EE_hal_i2c_write_buffer_irq(& EE_ST_NAME(lc), device, address, vet, len); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_buffer)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *vet, int len){ \
	int ret; \
	if(EE_i2c_rx_polling(EE_ST_NAME(lc).mode))\
		ret = EE_hal_i2c_read_buffer_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, vet, len); \
	else \
		ret = EE_hal_i2c_read_buffer_irq(& EE_ST_NAME(lc), device, address, vet, len); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(void){ \
	return EE_hal_i2c_enable_IRQ((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
	return EE_hal_i2c_disable_IRQ((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	return EE_hal_i2c_disable((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	return EE_hal_i2c_enable((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _stop)(void){ \
	return EE_hal_i2c_stop((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _start)(void){ \
	return EE_hal_i2c_start((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _return_error)(void){ \
	return EE_hal_i2c_return_error(& EE_ST_NAME(lc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _is_idle)(void){ \
	return EE_hal_i2c_idle((OCI2CMDev_t*)EE_BASE_ADD(uc)); }
	
/* User functions (API): */  
#ifdef EE_I2C1_NAME_UC
DECLARE_STRUCT_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif	//#ifdef EE_I2C1_NAME_UC

#ifdef EE_I2C2_NAME_UC
DECLARE_STRUCT_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif	//#ifdef EE_I2C2_NAME_UC
	
/* Return the I2C structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_i2c_st *EE_get_i2c_st_from_level(int level);

/**
	@brief 			This function is used inside the handler to get I2C structure pointer
	@param level 	IRQ level
    @return 		the pointer of the structure associated to the IRQ number passed as argument
*/
__INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
{
	#ifdef EE_I2C1_NAME_UC
	if (level == EE_IRQ_NAME(EE_I2C1_NAME_UC))
        return & EE_ST_NAME(EE_I2C1_NAME_LC);
	#endif
	#ifdef EE_I2C2_NAME_UC
	if (level == EE_IRQ_NAME(EE_I2C2_NAME_UC))
        return & EE_ST_NAME(EE_I2C2_NAME_LC);
	#endif
	return (EE_i2c_st *)0;
}

// #ifndef EE_I2C2_NAME_UC
// /* If there is only one component of this kind, no test is done */
// __INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
// {
    // return & EE_ST_NAME(EE_I2C1_NAME_LC);
// }
// #else /* #ifndef EE_I2C2_NAME_UC */
// __INLINE__ EE_i2c_st * __ALWAYS_INLINE__ EE_get_i2c_st_from_level(int level)
// {
    // if (level == EE_IRQ_NAME(EE_I2C1_NAME_UC))
        // return & EE_ST_NAME(EE_I2C1_NAME_LC);
    // else
        // return & EE_ST_NAME(EE_I2C2_NAME_LC);
// }
// #endif /* #ifndef EE_I2C2_NAME_UC */	
	
		
#else //#ifdef __USE_I2C_IRQ__

///*
//	I2C structure (used in polling mode):
//*/
//typedef struct {
//	int err;							// last error condition
//	int mode;							// i2c operating mode (polling, isr, ...)
//} EE_i2c_st;

/**
	@brief			This function configures i2c controller. 
	@param i2cc		address of the I2C registers structure
	@param baudrate	transmission rate 
	@param settings	special settings
	@return			EE_I2C_OK if no error occurs, else an error code.	
*/	
int EE_hal_i2c_config(OCI2CMDev_t* i2cc, int baudrate, int settings);

/**
	@brief			This function sets i2c controller mode.
	@param i2cc		address of the I2C registers structure
	@param mode 	desired operating mode
	@return			EE_I2C_OK if no error occurs, else an error code.	
*/	
int EE_hal_i2c_set_mode(OCI2CMDev_t* i2cc, int mode);	

/* Polling mode API */
#define DECLARE_FUNC_I2C(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int baudrate,int settings){ \
	return EE_hal_i2c_config((OCI2CMDev_t*)EE_BASE_ADD(uc), baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_mode)(int mode){ \
	return EE_hal_i2c_set_mode((OCI2CMDev_t*)EE_BASE_ADD(uc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_byte)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 data){ \
	return EE_hal_i2c_write_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_byte)(EE_UINT8 device, EE_UINT8 address){ \
	return EE_hal_i2c_read_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_buffer)(EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *vet, int len){ \
	return EE_hal_i2c_write_buffer_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_buffer)(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *vet, int len){ \
	return EE_hal_i2c_read_buffer_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	return EE_hal_i2c_disable((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	return EE_hal_i2c_enable((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _stop)(void){ \
	return EE_hal_i2c_stop((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _start)(void){ \
	return EE_hal_i2c_start((OCI2CMDev_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _is_idle)(void){ \
	return EE_hal_i2c_idle((OCI2CMDev_t*)EE_BASE_ADD(uc)); }
//__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(void){
//	return EE_hal_i2c_enable_IRQ((OCI2CMDev_t*)EE_BASE_ADD(uc)); }
//__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){
//	return EE_hal_i2c_disable_IRQ((OCI2CMDev_t*)EE_BASE_ADD(uc)); }
		
#endif //#ifdef __USE_I2C_IRQ__

/* User functions (API) declaration: */  
#ifdef EE_I2C1_NAME_UC
DECLARE_FUNC_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif	//#ifdef EE_I2C1_NAME_UC

#ifdef EE_I2C2_NAME_UC
DECLARE_FUNC_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif	//#ifdef EE_I2C2_NAME_UC


#ifdef __USE_MICO_PIC32LIKE_API__
#include "mcu/mico32/inc/ee_i2c_pic32like_api.h"
#endif // #ifdef __USE_MICO_PIC32LIKE_API__

#endif // __INCLUDE_EEMCUMICO32_I2C_H__


/*************************************************** 
* Notes
****************************************************/
// Interrupt works only byte-by-byte data transfers...
//	The interface defines 3 transmission speeds:
//	- Normal: 100Kbps
//	- Fast: 400Kbps
//	- High speed: 3.5Mbps
//	Only 100Kbps and 400Kbps modes are supported directly. For High speed special IOs
//	are needed. If these IOs are available and used, then High speed is also supported.

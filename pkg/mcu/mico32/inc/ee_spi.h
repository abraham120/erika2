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
	@file 	ee_spi.h
	@brief 	SPI library header file.\n
			SPI API explanation:\n
			API is generated with DECLARE_FUNC_SPI(uc, lc) and only if the macros
			EE_SPI1_NAME_UC, EE_SPI2_NAME_UC are defined in "eecfg.h". 
	@author Dario Di Stefano
	@date 	2010

	@example
			The name of the SPI module specified inside the platform and
			inside the conf.oil file is "User_Spi".
			
			The macros generated in "eecfg.h" are:\n
			\#define EE_SPI1_NAME_LC user_spi\n
			\#define EE_SPI1_NAME_UC USER_SPI\n
			
			The user must use the lower case form of the name, "user_spi", 
			to call the functions of the SPI API as shown in the following example list.
				
			Name: 				int EE_user_spi_config(int settings);\n
			Action:				This function configures spi controller (to change default parameters);\n
								Baudrate is specified in the platform file (see system_conf.h).\n
			Parameter settings: binary OR of flags for special settings (see macros in ee_spi.h);\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_spi_set_ISR_mode(int mode);\n
			Action:				This function sets spi controller operating mode (to change default parameters);\n
			Parameter mode:		operating mode (see macros in ee_spi.h);\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_spi_set_rx_ISR_callback(EE_ISR_callback rxcbk);\n
			Action:				This function sets RX isr callback (interrupt mode only);\n
			Parameter rxcbk:	pointer to the callback;\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_spi_set_tx_ISR_callback(EE_ISR_callback txcbk);\n
			Action:				This function sets TX isr callback (interrupt mode only);\n
			Parameter txcbk:	pointer to the callback;\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_spi_send_byte(EE_UINT8 data);\n
			Action:				This function sends a byte;\n
			Parameter data:		data to send;\n
			Return:				1 if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_spi_receive_byte(void);\n
			Action:				This function receives a byte;\n
			Return:				the received data, or a negative number in case of errors.\n
			
			Name: 				int EE_user_spi_send_buffer(const void* vet, int len);\n
			Action:				This function sends an array of bytes;\n
			Parameter vet:		array of bytes to send;\n
			Parameter len:		number of bytes to send;\n
			Return:				the number of transmitted bytes if no errors found, a negative number in case of errors.\n

			Name: 				int EE_user_spi_receive_buffer(void* vet, int len);\n
			Action:				This function receives an array of bytes;\n
			Parameter vet:		array to load with the received data;\n
			Parameter len:		number of bytes to receive;\n
			Return:				the number of received bytes if no errors found, a negative number in case of errors.\n
			
			Name: 				void EE_user_spi_get_slave(unsigned int *pmask);\n
			Action:				This function reads the sSelect register;\n
			Parameter pmask:	address of the variable to copy to;\n
			
			Name: 				void EE_user_spi_set_slave(unsigned int val)\n
			Action:				This function sets the sSelect register;\n
			Parameter val:		slave id to load;\n
			
			Name: 				void EE_user_spi_set_SSO(void);\n
			Action:				This function sets SSO bit in the control register;\n
			
			Name: 				void EE_user_spi_clear_SSO(void);\n
			Action:				This function clears SSO bit in the control register;\n
			
			Name: 				int EE_user_spi_return_error(void);\n
			Action:				This function returns the code of the last error condition occurred;\n
			Return:				the code of the last error condition occurred.\n
			
			Name: 				void EE_user_spi_enable_IRQ(void);\n
			Action:				This function enables SPI IRQ (interrupt mode only);\n
			
			Name: 				void EE_user_spi_disable_IRQ(void);\n
			Action:				This function disables SPI IRQ (interrupt mode only);\n
			
			Name: 				void EE_user_spi_enable(void);\n
			Action:				This function enables SPI driver control;\n
			
			Name: 				void EE_user_spi_disable(void);\n
			Action:				This function disables SPI driver control;\n
			
			Name: 				void EE_user_spi_is_wait_for_bus_idle(void);\n
			Action:				This function waits for SPI bus idle;\n
*/ 

#ifndef __INCLUDE_EEMCUMICO32_SPI_H__
#define __INCLUDE_EEMCUMICO32_SPI_H__

//#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
//#include <cpu/mico32/inc/ee_irq.h>
#include "MicoSPI.h"

/* mico-spi register structure (defined here because is not defined in MicoSPI.h ) */
typedef struct st_MicoSPI{
       volatile unsigned int rx;
       volatile unsigned int tx;
       volatile unsigned int status;
       volatile unsigned int control;
       volatile unsigned int sSelect;
}MicoSPI_t;
 
/* spi buffer settings */
#define EE_SPI_MSGSIZE 					(1)			// Size (number of characters) of an SPI message (for buffer usage in IRQ mode)
#define EE_SPI_BUFSIZE 					(12)		// Buffer size (number of messages)

/* status register masks */ 
#define EE_SPI_STATUS_RX_ERR_MASK      	(0x008)
#define EE_SPI_STATUS_TX_ERR_MASK      	(0x010)
#define EE_SPI_STATUS_TMT_RDY_MASK		(0x020)
#define EE_SPI_STATUS_TX_RDY_MASK      	(0x040)
#define EE_SPI_STATUS_RX_RDY_MASK      	(0x080)

/* control-register masks */ 
#define EE_SPI_CTL_RX_ERR_INTR_EN_MASK	(0x008)
#define EE_SPI_CTL_TX_ERR_INTR_EN_MASK 	(0x010)
#define EE_SPI_CTL_TX_INTR_EN_MASK     	(0x040)
#define EE_SPI_CTL_RX_INTR_EN_MASK     	(0x080)
#define EE_SPI_CTL_RXTX_ERR_INTR_EN_MASK (0x100)
#define EE_SPI_CTL_ALL_INTR_DIS_MASK	(0xFFFFFE00)
#define EE_SPI_CTL_SSO_MASK				(0x400)

/* spi return values */			
#define EE_SPI_OK					(0)
#define EE_SPI_ERR_RECEPTION   		(-40)
#define EE_SPI_ERR_TRANSMISSION		(-41)
#define EE_SPI_ERR_BAD_VALUE		(-42)
#define EE_SPI_ERR_TX_NOT_READY		(-43)
#define EE_SPI_ERR_RX_NOT_READY		(-44)

/* spi operating modes */
#define EE_SPI_POLLING				(0x00)
#define EE_SPI_RX_ISR				(0x01)
#define EE_SPI_TX_ISR				(0x02)	
#define EE_SPI_RXTX_ISR				(0x03)	
#define EE_SPI_RX_BLOCK				(0x10)
#define EE_SPI_TX_BLOCK				(0x20)
#define EE_SPI_RXTX_BLOCK  			(0x30)	

/* Macros for tests */
#define EE_spi_need_init_rx_buf(old,new)	(!((old) & EE_SPI_RX_ISR) && ((new) & EE_SPI_RX_ISR))
#define EE_spi_need_init_tx_buf(old,new)	(!((old) & EE_SPI_TX_ISR) && ((new) & EE_SPI_TX_ISR))
#define EE_spi_need_enable_int(new)			( ((new) & EE_SPI_RX_ISR) || ((new) & EE_SPI_TX_ISR) )
#define EE_spi_tx_polling(mode)				( !((mode) & EE_SPI_TX_ISR) )
#define EE_spi_rx_polling(mode)				( !((mode) & EE_SPI_RX_ISR) )
//#define EE_spi_bus_idle(status)
//#define EE_spi_pend_for_TIP_done(status)
#define EE_spi_clear_rx_overrun_error(status)	(status &= (~EE_SPI_STATUS_RX_ERR_MASK))
#define EE_spi_tx_ready(status)				(status & EE_SPI_STATUS_TX_RDY_MASK)
#define EE_spi_rx_ready(status)				(status & EE_SPI_STATUS_RX_RDY_MASK)
#define EE_spi_tmt_ready(status)			(status & EE_SPI_STATUS_TMT_RDY_MASK)
#define EE_spi_enable_tx_int(ctrl)			(ctrl |= EE_SPI_CTL_TX_INTR_EN_MASK)
#define EE_spi_enable_rx_int(ctrl)			(ctrl |= EE_SPI_CTL_RX_INTR_EN_MASK)
#define EE_spi_disable_tx_int(ctrl)			(ctrl &= (~EE_SPI_CTL_TX_INTR_EN_MASK))
#define EE_spi_disable_rx_int(ctrl)			(ctrl &= (~EE_SPI_CTL_RX_INTR_EN_MASK))
//#define EE_spi_is_master(set)				(set & EE_SPI_MASTER_MASK)

/**
	@brief 			This function waits for the spi bus idle. 
    @param spic		pointer of the controller registers structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_wait_for_bus_idle(MicoSPI_t* spic)
{
	while(!EE_spi_tmt_ready(spic->status))
		;
}

/**
	@brief			This function writes a byte in polling mode.
    @param spic		pointer of the controller registers structure
	@param data		data to be transmitted.
    @return 		1 when transmission is finished.	
*/
int EE_hal_spi_write_byte_polling(MicoSPI_t* spic, EE_UINT8 data);

/**
	@brief			This function reads a byte in polling mode.
    @param spic		pointer of the controller registers structure
    @return			the received data.
*/
int EE_hal_spi_read_byte_polling(MicoSPI_t *spic);

/**
	@brief			This function writes an array of bytes in polling mode.
    @param spic		pointer of the controller registers structure
	@param data		array of data to send
	@param len		number of bytes to send
    @return			len when transmission is finished.	
*/
int EE_hal_spi_write_buffer_polling(MicoSPI_t *spic, const void *data, int len);

/**
	@brief			This function reads an array of bytes in polling mode.
    @param spic		pointer of the controller registers structure
	@param data		array used for the received data
	@param len		number of bytes to receive
    @return			len when reception is finished.	
*/
int EE_hal_spi_read_buffer_polling(MicoSPI_t *spic, void *data, int len);

/**
	@brief			This function sets SSO bit in control register.
    @param spic		pointer of the controller registers structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_set_SSO(MicoSPI_t* spic)		
{
	spic->control |= EE_SPI_CTL_SSO_MASK;
}

/**
	@brief			This function clears SSO bit in control register.
	@param spic		pointer of the controller registers structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_clear_SSO(MicoSPI_t* spic)		
{
	/* wait the end of previous transmission */
	while(!EE_spi_tmt_ready(spic->status))		
		;
	spic->control &= (~EE_SPI_CTL_SSO_MASK);
}

/**
	@brief			This function writes on the slave select register 
    @param spic		pointer of the controller registers structure
	@param val		data to be written
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_set_slave(MicoSPI_t* spic, unsigned int val)		
{
	spic->sSelect = val;
}

/**
	@brief			This function reads the slave select register 
    @param spic 	pointer of the controller registers structure
	@param pval		pointer to a variable to copy to.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_get_slave(MicoSPI_t* spic, unsigned int *pval)		
{
	if(pval != 0)
        *pval = spic->sSelect;
}

#ifdef __USE_SPI_IRQ__ 
/*
	SPI structure (used in ISR mode) (not yet supported) :
*/
typedef struct {
	int err;							// last error condition
	int mode;							// spi operating mode (polling, isr, ...)
	int ir;								// flag to discriminate interrupt source (rx or tx)
    MicoSPI_t* base;					// controller base address
    int irqf;							// irq flag
    EE_ISR_callback rxcbk;				// rx callback
    EE_ISR_callback txcbk;				// tx callback
    EE_buffer rxbuf;					// rx buffer used in isr mode
    EE_buffer txbuf;					// tx buffer used in isr mode
} EE_spi_st;

/* Macro for Structure declaration */
#define DECLARE_STRUCT_SPI(uc, lc) \
  extern EE_spi_st EE_ST_NAME(lc);
  
/* Macro for structure definition */
#define DEFINE_STRUCT_SPI(uc, lc) \
EE_spi_st cat3(ee_, lc, _st) = { \
	.err=EE_SPI_OK, .mode= EE_SPI_POLLING | EE_SPI_RXTX_BLOCK, .base= (MicoSPI_t* )cat2(uc, _BASE_ADDRESS),\
	.irqf= cat2(uc, _IRQ), .rxcbk= EE_NULL_CBK, .txcbk= EE_NULL_CBK,\
	.rxbuf.data= EE_VETRX_NAME(lc),.txbuf.data= EE_VETTX_NAME(lc)};
	
/* Macro for vectors (buffers) definition */  
#define DEFINE_VET_SPI(uc, lc) \
EE_UINT8 EE_VETRX_NAME(lc)[EE_SPI_BUFSIZE]; \
EE_UINT8 EE_VETTX_NAME(lc)[EE_SPI_BUFSIZE];  

/**
	@brief			This function configures SPI controller (not yet supported).
    @param spisp	pointer of the spi driver structure
	@param settings	special settings
    @return			EE_SPI_OK if no errors found, else an error code.
*/
int EE_hal_spi_config(EE_spi_st* spisp, int settings);

/**
	@brief			This function sets a particular interrupt operating mode (not yet supported).
    @param spisp	pointer of the spi driver structure
	@param mode		desired operating mode
    @return			EE_SPI_OK if no errors found, else an error code.
*/
int EE_hal_spi_set_ISR_mode(EE_spi_st* spisp, int mode);

/**
	@brief			This function sets the RX isr callback (not yet supported).
    @param spisp	pointer of the spi driver structure
	@param isr_rx_callback	pointer to the rx callback 
    @return			EE_SPI_OK if no errors found, else an error code.
*/
int EE_hal_spi_set_rx_ISR_callback(EE_spi_st* spisp, EE_ISR_callback isr_rx_callback);

/**
	@brief 			This function sets the TX isr callback (not yet supported).
	@param spisp	pointer of the spi driver structure
	@param isr_tx_callback	pointer to the tx callback 
	@return			EE_SPI_OK if no errors found, else an error code.
*/
int EE_hal_spi_set_tx_ISR_callback(EE_spi_st* spisp, EE_ISR_callback isr_tx_callback);
	
/**
	@brief			This function writes a byte in irq mode (not yet supported).
    @param spisp	pointer of the spi driver structure
	@param data		data to be transmitted
    @return			1 when transmission is finished
*/												
int EE_hal_spi_write_byte_irq(EE_spi_st* spisp, EE_UINT8 data);

/**
	@brief			This function reads a byte in irq mode (not yet supported).
    @param spisp	pointer of the spi driver structure
	@return			the received data
*/
int EE_hal_spi_read_byte_irq(EE_spi_st* spisp);

/**
	@brief			This function writes an array of bytes in irq mode (not yet supported).
    @param spisp	pointer of the spi driver structure spisp	
	@param data		array of bytes to send
	@param len		number of bytes to send
    @return			len when transmission is finished
*/
int EE_hal_spi_write_buffer_irq(EE_spi_st* spisp, const void *data, int len);

/**
	@brief			This function reads an array of bytes in irq mode (not yet supported).
    @param spisp	pointer of the spi driver structure spisp
	@param data		array of bytes to receive
	@param len		number of bytes to receive
    @return			len when reception is finished
*/	
int EE_hal_spi_read_buffer_irq(EE_spi_st* spisp, void *data, int len);

/**
	@brief			This function reads the code of last error condition occurred (not yet supported).
    @param spisp	pointer of the spi driver structure spisp
    @return			the code of the last error condition occurred
*/
int EE_hal_spi_return_error(EE_spi_st* spisp);

/**
	@brief			This function enables IRQ (not yet supported).
    @param spisp	pointer of the spi driver structure spisp
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_enable_IRQ(EE_spi_st *spisp)
{
	MicoSPI_t* spic = spisp->base;
	spic->control = spisp->mode;
}

/**
	@brief			This function disables IRQ (not yet supported).
    @param spisp	pointer of the spi driver structure spisp
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_disable_IRQ(EE_spi_st *spisp)
{
	MicoSPI_t* spic = spisp->base;
	spic->control &= EE_SPI_CTL_ALL_INTR_DIS_MASK;
}

/**
	@brief			This function enables SPI controller (not yet supported).
    @param spisp	pointer of the spi driver structure spisp
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_enable(EE_spi_st *spisp)
{
	MicoSPI_t* spic = spisp->base;
	
	spic->control = spisp->mode;
}

/**
	@brief			This function disables SPI controller (not yet supported).
    @param spisp	pointer of the spi driver structure spisp
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_disable(EE_spi_st *spisp)
{
	MicoSPI_t* spic = spisp->base;
	
	while( !EE_spi_tmt_ready(spic->status) );
	spic->control = 0;
}

/*
	SPI Interrupt handler.
*/
void EE_spi_common_handler(int level);		

#ifndef __STATIC_ISR_TABLE__
/**
	@brief 			This function sets the interrupt handler
	@param spisp	pointer of the spi driver structure spisp
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_handler_setup(EE_spi_st* spisp)
{
	/* Register IRQ handler */
    EE_mico32_register_ISR(spisp->irqf, EE_spi_common_handler);	
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_spi_handler_setup(spisp)
#endif // __STATIC_ISR_TABLE__															
							
/* Interrupt mode API */
#define DECLARE_FUNC_SPI(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int settings){ \
	return EE_hal_spi_config(& EE_ST_NAME(lc), settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_ISR_mode)(int mode){ \
	return EE_hal_spi_set_ISR_mode(& EE_ST_NAME(lc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_rx_ISR_callback)(EE_ISR_callback rxcbk){ \
	return EE_hal_spi_set_rx_ISR_callback(& EE_ST_NAME(lc), rxcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_tx_ISR_callback)(EE_ISR_callback txcbk){ \
	return EE_hal_spi_set_tx_ISR_callback(& EE_ST_NAME(lc), txcbk); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_byte)(EE_UINT8 data){ \
	int ret; \
	if(EE_spi_tx_polling(EE_ST_NAME(lc).mode)) \
		ret = EE_hal_spi_write_byte_polling((MicoSPI_t*)EE_BASE_ADD(uc), data); \
	else \
		ret = EE_hal_spi_write_byte_irq(& EE_ST_NAME(lc), data); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_byte)(void){ \
	int ret; \
	if(EE_spi_rx_polling(EE_ST_NAME(lc).mode)) \
		ret = EE_hal_spi_read_byte_polling((MicoSPI_t*)EE_BASE_ADD(uc)); \
	else \
		ret = EE_hal_spi_read_byte_irq(& EE_ST_NAME(lc)); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_buffer)(const void* vet, int len){ \
	int ret; \
	if(EE_spi_tx_polling(EE_ST_NAME(lc).mode)) \
		ret = EE_hal_spi_write_buffer_polling((MicoSPI_t*)EE_BASE_ADD(uc), vet, len); \
	else \
		ret = EE_hal_spi_write_buffer_irq(& EE_ST_NAME(lc), vet, len); \
	return ret; } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_buffer)(void* vet, int len){ \
	int ret; \
	if(EE_spi_rx_polling(EE_ST_NAME(lc).mode)) \
		ret = EE_hal_spi_read_buffer_polling((MicoSPI_t*)EE_BASE_ADD(uc), vet, len); \
	else \
		ret = EE_hal_spi_read_buffer_irq(& EE_ST_NAME(lc), vet, len); \
	return ret; } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _get_slave)(unsigned int *pmask){ \
	EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _set_slave)(unsigned int val){ \
	EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), val); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _set_SSO)(void){ \
	EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _clear_SSO)(void){ \
	EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _return_error)(void){ \
	return EE_hal_spi_return_error(& EE_ST_NAME(lc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(void){ \
	EE_hal_spi_enable_IRQ(& EE_ST_NAME(lc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){ \
	EE_hal_spi_disable_IRQ(& EE_ST_NAME(lc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	EE_hal_spi_enable(& EE_ST_NAME(lc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	EE_hal_spi_disable(& EE_ST_NAME(lc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _wait_for_bus_idle)(void){ \
	EE_hal_spi_wait_for_bus_idle((MicoSPI_t*)EE_BASE_ADD(uc)); }
	
/* User functions (API): */  
#ifdef EE_SPI1_NAME_UC
DECLARE_STRUCT_SPI(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
#endif	//#ifdef EE_SPI1_NAME_UC

#ifdef EE_SPI2_NAME_UC
DECLARE_STRUCT_SPI(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
#endif	//#ifdef EE_SPI2_NAME_UC
	
/* Return the SPI structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_spi_st *EE_get_spi_st_from_level(int level);

/**
	@brief 			This function is used inside the handler to get SPI structure pointer
	@param level 	IRQ level
    @return 		the pointer of the structure associated to the IRQ number passed as argument
*/
__INLINE__ EE_spi_st * __ALWAYS_INLINE__ EE_get_spi_st_from_level(int level)
{
	#ifdef EE_SPI1_NAME_UC
	if (level == EE_IRQ_NAME(EE_SPI1_NAME_UC))
        return & EE_ST_NAME(EE_SPI1_NAME_LC);
	#endif
	#ifdef EE_SPI2_NAME_UC
	if (level == EE_IRQ_NAME(EE_SPI2_NAME_UC))
        return & EE_ST_NAME(EE_SPI2_NAME_LC);
	#endif
	return (EE_spi_st *)0;
}

// #ifndef EE_SPI2_NAME_UC
// /* If there is only one component of this kind, no test is done */
// __INLINE__ EE_spi_st * __ALWAYS_INLINE__ EE_get_spi_st_from_level(int level)
// {
    // return & EE_ST_NAME(EE_SPI1_NAME_LC);
// }
// #else /* #ifndef EE_SPI2_NAME_UC */
// __INLINE__ EE_spi_st * __ALWAYS_INLINE__ EE_get_spi_st_from_level(int level)
// {
    // if (level == EE_IRQ_NAME(EE_SPI1_NAME_UC))
        // return & EE_ST_NAME(EE_SPI1_NAME_LC);
    // else
        // return & EE_ST_NAME(EE_SPI2_NAME_LC);
// }
// #endif /* #ifndef EE_SPI2_NAME_UC */	
	
		
#else //#ifdef __USE_SPI_IRQ__

///*
//	SPI structure (used in polling mode):
//*/
//typedef struct {
//	int err;							// last error condition
//	int mode;							// spi operating mode (polling, isr, ...)
//} EE_spi_st;

/**
	@brief			This function configures SPI in polling mode.
    @param spic		pointer of the spi registers structure
	@param settings	special settings
	@return			EE_SPI_OK if no errors found, else an error code.
*/
int EE_hal_spi_config(MicoSPI_t* spic, int settings);

/**
	@brief			This function sets a particular polling operating mode. 
    @param spic		pointer of the spi registers structure
	@param irqf		IRQ number associated to the spi controller
	@param mode		desired operating mode
    @return			EE_SPI_OK if no errors found, else an error code.
*/
int EE_hal_spi_set_ISR_mode(MicoSPI_t* spic, int irqf, int mode);
	
/**
	@brief			This function enables SPI controller.
    @param spic		pointer of the spi registers structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_enable(MicoSPI_t* spic)
{
}

/**
	@brief			This function disables SPI controller.
    @param spic		pointer of the spi registers structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_spi_disable(MicoSPI_t* spic)
{
	while( !EE_spi_tmt_ready(spic->status) );
	spic->control = 0;
}

/* Polling mode API */
#define DECLARE_FUNC_SPI(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _config)(int settings){ \
	return EE_hal_spi_config((MicoSPI_t*)EE_BASE_ADD(uc), settings); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _set_ISR_mode)(int mode){ \
	return EE_hal_spi_set_ISR_mode((MicoSPI_t*)EE_BASE_ADD(uc), EE_IRQ_NAME(uc), mode); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_byte)(EE_UINT8 data){ \
	return EE_hal_spi_write_byte_polling((MicoSPI_t*)EE_BASE_ADD(uc), data); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_byte)(void){ \
	return EE_hal_spi_read_byte_polling((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _send_buffer)(const void* vet, int len){ \
	return EE_hal_spi_write_buffer_polling((MicoSPI_t*)EE_BASE_ADD(uc), vet, len); } \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _receive_buffer)( void* vet, int len){ \
	return EE_hal_spi_read_buffer_polling((MicoSPI_t*)EE_BASE_ADD(uc), vet, len); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _disable)(void){ \
	EE_hal_spi_disable((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _enable)(void){ \
	EE_hal_spi_enable((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _set_SSO)(void){ \
	EE_hal_spi_set_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _clear_SSO)(void){ \
	EE_hal_spi_clear_SSO((MicoSPI_t*)EE_BASE_ADD(uc)); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _set_slave)(unsigned int mask){ \
	EE_hal_spi_set_slave((MicoSPI_t*)EE_BASE_ADD(uc), mask); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _get_slave)(unsigned int *pmask ){ \
	EE_hal_spi_get_slave((MicoSPI_t*)EE_BASE_ADD(uc), pmask); } \
__INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _wait_for_bus_idle)(void){ \
	EE_hal_spi_wait_for_bus_idle((MicoSPI_t*)EE_BASE_ADD(uc)); }	
	
#endif //#ifdef __USE_SPI_IRQ__

/* User functions (API) declaration: */  
#ifdef EE_SPI1_NAME_UC
DECLARE_FUNC_SPI(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
#endif	//#ifdef EE_SPI1_NAME_UC

#ifdef EE_SPI2_NAME_UC
DECLARE_FUNC_SPI(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
#endif	//#ifdef EE_SPI2_NAME_UC

#ifdef __USE_MICO_PIC32LIKE_API__
#include "mcu/mico32/inc/ee_spi_pic32like_api.h"
#endif // #ifdef __USE_MICO_PIC32LIKE_API__

#endif // __INCLUDE_EEMCUMICO32_SPI_H__

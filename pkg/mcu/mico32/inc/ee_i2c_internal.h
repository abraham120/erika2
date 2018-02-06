/*
  Name: ee_i2c_internal.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.28
  Description: I2C internal header file. 
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_INTERNAL_H__
#define __INCLUDE_EEMCUMICO32_I2C_INTERNAL_H__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
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
/*
	int EE_hal_i2c_write_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	
		This function is used to write one character on the i2c bus.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
			- EE_UINT8 device: slave address
			- EE_UINT8 address: slave memory address to be written
			- EE_UINT8 data: data to be transmitted
		Actions: 
			- issue a start signal, transmit device address (write mode), transmit slave memory address, tranmsit data, issue a stop signal. 
		Return values:
			- the return values can be:	EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
										EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
										EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
										EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_write_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	

/*
	int EE_hal_i2c_read_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address);
		This function is used to read one character from the i2c bus.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
			- EE_UINT8 device: slave address
			- EE_UINT8 address: slave memory address to be read
		Actions: 
			- issue a start signal, transmit device address (write mode), transmit slave memory address, transmit device address (read mode), 
				read data and transmit NACK, issue a stop signal. 
		Return values:
			- the return values can be:	EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
										EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
										EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
										data 				if all is ok
*/
int EE_hal_i2c_read_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address);



/*
	int EE_hal_i2c_read_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);	
		This function is used to read mote than one characters from the i2c bus.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
			- EE_UINT8 device: slave address
			- EE_UINT8 address: slave memory address to be read
			- EE_UINT8 *data: array to be loaded with the read characters
			- int len: number of characters to be read
		Actions: 
			- issue a start signal, transmit device address (write mode), transmit slave memory address, transmit device address (read mode), 
				read data and transmit ACK/NACK, issue a stop signal. 
		Return values:
			- the return values can be:	EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
										EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
										EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
										EE_I2C_OK 				if all is ok
*/
int EE_hal_i2c_read_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);		


/*
	int EE_hal_i2c_write_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);	
		This function is used to write more than one characters on the i2c bus.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
			- EE_UINT8 device: slave address
			- EE_UINT8 address: slave memory address to be written
			- EE_UINT8 *data: array of characters to be transmitted
			- int len: number of characters to be transmitted
		Actions: 
			- issue a start signal, transmit device address (write mode), transmit slave memory address, tranmsit all data, issue a stop signal. 
		Return values:
			- the return values can be:	EE_I2C_ERR_DEV_ACK 	if ACK is not been received during device address transmission
										EE_I2C_ERR_ADD_ACK 	if ACK is not been received during memory address transmission
										EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
										EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_write_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *data, int len);	

/*
	int EE_hal_i2c_start(OCI2CMDev_t* i2cc);
		This function is used to issue only a start signal on the i2c bus.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- issue only a start signal on the i2c bus.
		Return values:
			- the return values can be:	EE_I2C_ERR_ARB_LOST if arbitration is been lost during transmission
										EE_I2C_OK 			if all is ok
*/
int EE_hal_i2c_start(OCI2CMDev_t* i2cc);

/*
	int EE_hal_i2c_stop(OCI2CMDev_t* i2cc);
		This function is used to issue only a stop signal on the i2c bus.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- issue only a stop signal on the i2c bus.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/																	
int EE_hal_i2c_stop(OCI2CMDev_t* i2cc);


/*
	int EE_hal_i2c_disable(OCI2CMDev_t* i2cc);	
		This function is used to disable i2c core.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- disable i2c core.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/	
int EE_hal_i2c_disable(OCI2CMDev_t* i2cc);		
	
/*
	__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_enable(OCI2CMDev_t* i2cc);
		This function is used to enable i2c core.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- enable i2c core.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/														
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_enable(OCI2CMDev_t* i2cc)
{
	i2cc->Control |= OCI2CM_CTL_CORE_ENABLE;  
	return EE_I2C_OK;
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_enable_IRQ(OCI2CMDev_t* i2cc)
		This function is used to enable interrupts.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- enable interrupts.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/																
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_enable_IRQ(OCI2CMDev_t* i2cc)
{
	i2cc->Control |= OCI2CM_CTL_INT_ENABLE;
	return EE_I2C_OK;	
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_disable_IRQ(OCI2CMDev_t* i2cc)
		This function is used to disable interrupts.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- disable interrupts.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/													
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_disable_IRQ(OCI2CMDev_t* i2cc)
{
	i2cc->Control &= ~OCI2CM_CTL_INT_ENABLE;
	return EE_I2C_OK;
}

/*
	__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_idle(OCI2CMDev_t* i2cc)
		This function is used to check if the i2c bus is idle.
		Arguments:
			- OCI2CMDev_t* i2cc: I2C base address
		Actions: 
			- check if the i2c bus is idle.
		Return values:
			- the return values can be:	1 if i2c bus is idle else 0	
*/	
__INLINE__ int __ALWAYS_INLINE__ EE_hal_i2c_idle(OCI2CMDev_t* i2cc)
{
	return EE_i2c_bus_idle(i2cc->StatusCommand);
}


#ifdef __USE_I2C_IRQ__

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

/*
	int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate);
		This function is used to configure i2c controller.
		Arguments:
			- EE_i2c_st* i2csp: I2C structure
			- int baudrate: transmission rate 
		Actions: 
			- configure i2c controller.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/					
int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate);

/*
	int EE_hal_i2c_set_mode(EE_i2c_st* i2csp, int mode);		
		This function is used to set i2c controller mode.
		Arguments:
			- EE_i2c_st* i2csp: I2C structure
			- int mode: desired mode
		Actions: 
			- set i2c controller mode.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/	
int EE_hal_i2c_set_mode(EE_i2c_st* i2csp, int mode);	

/*
	int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback);		
		This function is used to set rx callback.
		Arguments:
			- EE_i2c_st* i2csp: I2C structure
			- EE_ISR_callback isr_rx_callback: rx callback pointer
		Actions: 
			- set rx callback.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/	
int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback);	

/*
	int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback);			
		This function is used to set tx callback.
		Arguments:
			- EE_i2c_st* i2csp: I2C structure
			- EE_ISR_callback isr_tx_callback: tx callback pointer
		Actions: 
			- set tx callback.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/						
int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback);			

/*
	int EE_hal_i2c_return_error(EE_i2c_st* i2csp);				
		This function is used to know the last error condition
		Arguments:
			- EE_i2c_st* i2csp: I2C structure
		Actions: 
			- return the last error condition
		Return values:
			- the return value is the last error condition
*/																								
int EE_hal_i2c_return_error(EE_i2c_st* i2csp);			

/* to do */
int EE_hal_i2c_write_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data);	
/* to do */
int EE_hal_i2c_read_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address);	
/* to do */
int EE_hal_i2c_read_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len);
/* to do */	
int EE_hal_i2c_write_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *data, int len);
/* to do */		

/* Interrupt handler */
void EE_i2c_common_handler(int level);																	
							
/* 
	Macros for I2C driver API generation (irq mode)
*/ 
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

/*
	int EE_hal_i2c_config(OCI2CMDev_t* i2cc, int baudrate, int setttings);
		This function is used to configure i2c controller.
		Arguments:
			- OCI2CMDev_t* i2cc: i2c base address
			- int baudrate: transmission rate 
			- int settings: other i2c settings (to do...)
		Actions: 
			- configure i2c controller.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/		
int EE_hal_i2c_config(OCI2CMDev_t* i2cc, int baudrate, int setttings);

/*
	int EE_hal_i2c_set_mode(OCI2CMDev_t* i2cc, int mode);		
		This function is used to set i2c controller mode.
		Arguments:
			- OCI2CMDev_t* i2cc: i2c base address
			- int mode: desired mode
		Actions: 
			- set i2c controller mode.
		Return values:
			- the return values can be:	EE_I2C_OK 	
*/	
int EE_hal_i2c_set_mode(OCI2CMDev_t* i2cc, int mode);	

/* 
	Macros for I2C driver API generation (polling mode)
*/ 
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

/* ------------------------------------------------------------------------- */

#ifdef __USE_MICO_PIC_API__
/* Macros for compatibility with pic32 i2c driver*/ 
#define EE_mchp_i2c_init(uc, baud, flags) EE_hal_i2c_config((OCI2CMDev_t*)EE_BASE_ADD(uc), baud, flags)
#define EE_mchp_i2c_idle(uc) EE_hal_i2c_idle((OCI2CMDev_t*)EE_BASE_ADD(uc))
#define EE_mchp_i2c_read_byte(uc, device, address) EE_hal_i2c_read_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address)
#define EE_mchp_i2c_write_byte(uc, device, address, data) EE_hal_i2c_write_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, data)	

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_init(EE_UINT8 port, EE_UINT16 baudrate, EE_UINT16 flags)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_init(EE_I2C1_NAME_UC, baudrate, flags);
	else
		ret = EE_mchp_i2c_init(EE_I2C2_NAME_UC, baudrate, flags);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_init(EE_I2C1_NAME_UC, baudrate, flags);
		#else
		ret = EE_mchp_i2c_init(EE_I2C2_NAME_UC, baudrate, flags);
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_idle(EE_UINT8 port)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_idle(EE_I2C1_NAME_UC);
	else
		ret = EE_mchp_i2c_idle(EE_I2C2_NAME_UC);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_idle(EE_I2C1_NAME_UC);
		#else
		ret = EE_mchp_i2c_idle(EE_I2C2_NAME_UC);
		#endif
	#endif
		
	return ret;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_read_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_read_byte(EE_I2C1_NAME_UC, device, address);
	else
		ret = EE_mchp_i2c_read_byte(EE_I2C2_NAME_UC, device, address);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_read_byte(EE_I2C1_NAME_UC, device, address);
		#else
		ret = EE_mchp_i2c_read_byte(EE_I2C2_NAME_UC, device, address);
		#endif
	#endif
		
	*data = (EE_UINT8)ret;
		
	return ret;

}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_write_byte(EE_I2C1_NAME_UC, device, address, data);
	else
		ret = EE_mchp_i2c_write_byte(EE_I2C2_NAME_UC, device, address, data);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_write_byte(EE_I2C1_NAME_UC, device, address, data);
		#else
		ret = EE_mchp_i2c_write_byte(EE_I2C2_NAME_UC, device, address, data);
		#endif
	#endif
		
	return ret;

}

#endif // #ifdef __USE_MICO_PIC_API__

/* ------------------------------------------------------------------------- */

#endif //__INCLUDE_EEMCUMICO32_I2C_INTERNAL_H__

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

/*
 * Author: 2010,  Christian Grioli
 * Uart implementation.
 */

#include "mcu/msp430/inc/ee_uart_util.h"


#define __EE_UART_PORT_1_ISR_ENABLE__

/*Internal variables*/

static EE_UINT8 uart_mode1=0;
static EE_UINT8 uart_mode2=0;

static EE_INT8 error_1=0;
static EE_INT8 error_2=0;

#ifdef __EE_UART_PORT_1_ISR_ENABLE__

static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
static void (*Tx1IsrFunction)(volatile EE_UINT8* regs) = NULL;

#define setRX1Function(func) Rx1IsrFunction=func
#define setTX1Function(func) Tx1IsrFunction=func

#else
#define setRX1Function(func)
#define setTX1Function(func) 

#endif



#ifdef __EE_UART_PORT_2_ISR_ENABLE__
static void (*Rx2IsrFunction)(EE_UINT8 data) = NULL;
static void (*Tx2IsrFunction)(volatile EE_UINT8* regs) = NULL;

#define setRX2Function(func) Rx2IsrFunction=func
#define setTX2Function(func) Tx2IsrFunction=func

#else

#define setRX2Function(func)
#define setTX2Function(func) 


#endif




/********************** Internal function **************************/
/*This function controls the error during the reading, if the control is enable*/

EE_INT8 EE_uart_ctrl_error(EE_INT8 port){
EE_UINT8 mode;
EE_INT8* error; 
volatile EE_UINT8*regs;
if(port==EE_UART_PORT_1){
	mode=uart_mode1;
	error=&error_1;
	regs=&U0RCTL;
}
else if(port==EE_UART_PORT_2){
	mode=uart_mode2;
	error=&error_2;
	regs=&U1RCTL;
}
else
	return EE_UART_ERR_BAD_PORT;


*error=EE_UART_NO_ERROR;

if(mode & EE_UART_CTRL_ERROR)
{
	if(*regs & EE_UART_IS_ERROR)
	{
		if(U0RCTL & EE_UART_IS_FRAME_ERROR)
			*error=EE_UART_ERR_FRAME;
		if(U0RCTL & EE_UART_IS_PARITY_ERROR)
			*error=EE_UART_ERR_PARITY;
		if(U0RCTL & EE_UART_IS_OVERRUN_ERROR)
			*error=EE_UART_ERR_OVERRUN;
		if(U0RCTL & EE_UART_IS_BREAK_DETECT)
			*error=EE_UART_ERR_BREAK_CONDITION;


	}
}
return *error;



}


/********************** Library function **************************/

/*This function allow the setting baud information on the variables/parameter of the function ee_uart_init*/
EE_INT8 EE_uart_set_baud(EE_UINT32* baud, EE_UINT16 baud_value){
if(baud_value<3)
	return EE_UART_ERR_BAD_BAUD_VALUE;
*baud|=baud_value;
return EE_UART_NO_ERROR;

}


/*This function allow the setting modulation information on the variables/parameter of the function ee_uart_init*/
EE_INT8 EE_uart_set_modulation(EE_UINT32* baud, EE_UINT8 modulation_value){
EE_UINT32 value=modulation_value;
*baud|=(value <<16);
return EE_UART_NO_ERROR;
}




EE_INT8 EE_uart_print_error(EE_UINT8 port){


if(port==EE_UART_PORT_1){

	return error_1;

}
else if(port==EE_UART_PORT_2){
	
	return error_2;
}

return EE_UART_ERR_BAD_PORT;

}



EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, EE_UINT16 mode){

	if(port==EE_UART_PORT_1){
		/*Setting SWRTS bit*/
		U0CTL|=SWRST;
		/*Setting byte information*/
		U0CTL|=byte_format & EE_BYTE_FORMAT_INFO;
		/*Setting baud*/
		U0BR0=EE_UxBR0_value(baud);
		U0BR1=EE_UxBR1_value(baud);
		U0MCTL=EE_UxMCTL_value(baud);
		/*Enable module TX/RX*/
		ME1|=EE_UART_TX_RX_ENABLE_1;		
		/*Set the transmit mode information*/
		uart_mode1=mode;
		uart_mode1=uart_mode1>>8;		
		U0TCTL|=uart_mode1;
		uart_mode1=mode;

		/*Set the reading error control*/
		if(mode & EE_UART_CTRL_ERROR)
			U0RCTL|=EE_UART_SET_CTRL_ERROR;	
		/*Setting pins*/
		P3SEL|=EE_UART_SEL_TXD_RXD_1;
		P3DIR|=EE_UART_DIR_TXD_RXD_1;
		/*Resetting SWRTS bit*/
		U0CTL&=~SWRST;
		return EE_UART_NO_ERROR;
	}
	else if(port==EE_UART_PORT_2){
		/*Setting SWRTS bit*/
		U1CTL|=SWRST;
		/*Setting byte information*/
		U1CTL|=byte_format & EE_BYTE_FORMAT_INFO;
		/*Setting baud*/
		U1BR0=EE_UxBR0_value(baud);
		U1BR1=EE_UxBR1_value(baud);
		U1MCTL=EE_UxMCTL_value(baud);
		/*Enable module TX/RX*/
		ME2|=EE_UART_TX_RX_ENABLE_2;
		/*Set the transmit mode information*/
		uart_mode2=mode;
		uart_mode2=uart_mode2>>8;		
		U1TCTL|=uart_mode2;
		uart_mode2=mode;
		/*Set the reading error control*/
		if(mode & EE_UART_CTRL_ERROR)
			U1RCTL|=EE_UART_SET_CTRL_ERROR;
		
		/*Setting pins*/
		P3SEL|=EE_UART_SEL_TXD_RXD_2;
		P3DIR|=EE_UART_DIR_TXD_RXD_2;

		/*Resetting SWRTS bit*/
		U1CTL&=~SWRST;

		return EE_UART_NO_ERROR;
	}
	else 
		return EE_UART_ERR_BAD_PORT; 



}



EE_INT8 EE_uart_close(EE_UINT8 port){



if(port==EE_UART_PORT_1){
/*If data is on the buffer, wait for avoid wrong state*/
	while((U0CTL & TXEPT)==0);
	/*Disable Tx/Rx module*/
	ME1&=~EE_UART_TX_RX_ENABLE_1;
	/*Reset control TX/RX registers*/	
	if(uart_mode1  & EE_UART_CTRL_ERROR)
		U0RCTL&=~EE_UART_SET_CTRL_ERROR;
	/*Reset the control register and feature enabled*/
	uart_mode1=uart_mode1>>8;
	U0TCTL&=~uart_mode1;
	U0TCTL&=~EE_UART_START_EDGE;
	/*Reset ISR*/
	IE1&=~EE_UART_SET_RX_ISR_1;
	IE1&=~EE_UART_SET_TX_ISR_1;
	/*Reset pins*/
	P3SEL&=~EE_UART_SEL_TXD_RXD_1;
	P3DIR&=~EE_UART_DIR_TXD_RXD_1;
	return EE_UART_NO_ERROR;
}
else if(port==EE_UART_PORT_2){
/*If data is on the buffer, wait for avoid wrong state*/
	while((U1CTL & TXEPT)==0);
	/*Disable Tx/Rx module*/
	ME2&=~EE_UART_TX_RX_ENABLE_2;
	/*Reset control TX/RX registers*/
	if(uart_mode2 & EE_UART_CTRL_ERROR)
		U1RCTL&=~EE_UART_SET_CTRL_ERROR;
	/*Reset the control register and feature enabled*/
	uart_mode2=uart_mode2>>8;
	U1TCTL&=~uart_mode2;
	U1TCTL&=~EE_UART_START_EDGE;
	/*Reset ISR*/
	IE2&=~EE_UART_SET_RX_ISR_2;
	IE2&=~EE_UART_SET_TX_ISR_2;		
	/*Reset pins*/
	P3SEL&=~EE_UART_SEL_TXD_RXD_2;
	P3DIR&=~EE_UART_DIR_TXD_RXD_2;
	
	return EE_UART_NO_ERROR;

}
else
	return EE_UART_ERR_BAD_PORT;

}


EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data){


if(port==EE_UART_PORT_1){

	if(EE_UART_IS_POLLING(uart_mode1)){

		if(EE_UART_IS_TX_BLOCK(uart_mode1)){ 
		/*If polling blocking mode*/
			while((IFG1 & UTXIFG0)==0);
			U0TXBUF =data;
			return EE_UART_NO_ERROR;
			}
		else{
		 /*If only polling mode*/
		 if((IFG1 & UTXIFG0)==0)
				return EE_UART_ERR_TX_NOT_READY;
	                U0TXBUF =data;
			return EE_UART_NO_ERROR;
			
		}
	}
	/*If not polling mode*/
	return  EE_UART_ERR_INT_MODE;
}
else if(port==EE_UART_PORT_2){

	if(EE_UART_IS_POLLING(uart_mode2)){

		if(EE_UART_IS_TX_BLOCK(uart_mode2)){
		/*If polling blocking mode*/
			while((IFG2 & UTXIFG1)==0);
			U1TXBUF =data;
			return EE_UART_NO_ERROR;
		}
		else{
		/*If only polling mode*/
		 if((IFG2 & UTXIFG1)==0)
				return EE_UART_ERR_TX_NOT_READY;
	                U1TXBUF =data;
			return EE_UART_NO_ERROR;
			
		}
	}
	/*If not polling mode*/
	return  EE_UART_ERR_INT_MODE;
}
else
	return EE_UART_ERR_BAD_PORT;




}


EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data){

EE_INT8 ret;
if(port==EE_UART_PORT_1){
	
	if(EE_UART_IS_POLLING(uart_mode1)){

		if(EE_UART_IS_RX_BLOCK(uart_mode1)){
			/*If polling blocking mode*/
			while((IFG1 & URXIFG0)==0);
			ret=EE_uart_ctrl_error(EE_UART_PORT_1);	
			/*In this way, read the error,save information and then read the data and the error delete*/
			*data=U0RXBUF;
			return ret; 
		}
		else{
		/*If only blocking mode*/
		 if((IFG1 & URXIFG0)==0)
				return EE_UART_ERR_RX_NOT_READY;
	                ret=EE_uart_ctrl_error(EE_UART_PORT_1);	
			*data=U0RXBUF;
			return ret;
			
		}

	}
	/*If not polling mode*/
	return  EE_UART_ERR_INT_MODE;


}
else if(port==EE_UART_PORT_2){

	if(EE_UART_IS_POLLING(uart_mode2)){
	
		if(EE_UART_IS_RX_BLOCK(uart_mode2)){
			/*If polling blocking mode*/
			while((IFG2 & URXIFG1)==0);
			ret=EE_uart_ctrl_error(EE_UART_PORT_2);	
			/*In this way, read the error,save information and then read the data and the error delete*/
			*data=U1RXBUF;
			return ret;
		}

		else{
		/*If only blocking mode*/
		 if((IFG2 & URXIFG1)==0)
				return EE_UART_ERR_RX_NOT_READY;
			
			ret=EE_uart_ctrl_error(EE_UART_PORT_2);
	                *data=U1RXBUF;
			return ret;
			
		}

	}
	/*If not polling mode*/
	return  EE_UART_ERR_INT_MODE;
}
else
	return EE_UART_ERR_BAD_PORT;






}

EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data),EE_UINT8 rxmode){

	if (port == EE_UART_PORT_1) {	
		
		if(uart_mode1 & EE_UART_RX_ISR){
		/*If ISR mode*/			
			if (RxFunc) {
				/*Set function*/
				setRX1Function(RxFunc);
				/*Enable ISR and start edge*/
				IE1|=EE_UART_SET_RX_ISR_1;
				if(rxmode & EE_UART_START_EDGE)
					U0TCTL|=EE_UART_START_EDGE;
				return EE_UART_NO_ERROR;			
			}
		
			return EE_UART_ERR_FUNCTION_NULL;		

		}
		return EE_UART_ERR_INT_DISABLED;
		
	} else if (port == EE_UART_PORT_2) {

		if(uart_mode2 & EE_UART_RX_ISR){
			/*If ISR mode*/
			if (RxFunc) {
				/*Set the function*/
				setRX2Function(RxFunc);
				/*Enable ISR and start edge*/
				IE2|=EE_UART_SET_RX_ISR_2;				
				if(rxmode & EE_UART_START_EDGE)
					U1TCTL|=EE_UART_START_EDGE;
								
				
				return EE_UART_NO_ERROR;			
			}
		
			return EE_UART_ERR_FUNCTION_NULL;		

		}
		return EE_UART_ERR_INT_DISABLED;
		
	}
	return EE_UART_ERR_BAD_PORT;





}

EE_INT8 EE_uart_set_tx_callback(EE_UINT8 port, void (*TxFunc)(volatile EE_UINT8* regs),EE_UINT8 txmode){

	if (port == EE_UART_PORT_1) {	
		
		if(uart_mode1 & EE_UART_TX_ISR){
			/*If ISR function*/
			if (TxFunc) {
				/*Set the function*/
				setTX1Function(TxFunc);
				/*Enable ISR*/
				IE1|=EE_UART_SET_TX_ISR_1;
				return EE_UART_NO_ERROR;			
			}
		
			return EE_UART_ERR_FUNCTION_NULL;		

		}
		return EE_UART_ERR_INT_DISABLED;
		
	} else if (port == EE_UART_PORT_2) {

		if(uart_mode2 & EE_UART_TX_ISR){
			/*If ISR function*/

			if (TxFunc) {
				/*Set the function*/
				setTX2Function(TxFunc);
				/*Enable ISR*/
				IE2|=EE_UART_SET_TX_ISR_2;
				return EE_UART_NO_ERROR;			
			}
		
			return EE_UART_ERR_FUNCTION_NULL;		

		}
		return EE_UART_ERR_INT_DISABLED;
		
	}
	return EE_UART_ERR_BAD_PORT;


}


#ifdef __EE_UART_PORT_1_ISR_ENABLE__

ISR2(USART0RX_VECTOR )
{
/*TODO:If set CTRL_ERROR, in this way I lose error information
Now there is one function that save the error and print it*/

	if (Rx1IsrFunction != NULL) {
		if((IFG1 & EE_UART_IS_START_EDGE_1)==0)/*START-EDGE*/ 
			EE_msp430_change_LPM(NO_LPMODE);
		EE_uart_ctrl_error(EE_UART_PORT_1);
		/* Execute callback function */
		Rx1IsrFunction(U0RXBUF);
		}
	           
}

ISR2(USART1TX_VECTOR )
{
	if (Tx1IsrFunction != NULL) {
		/* Execute callback function */
		Tx1IsrFunction(&U0TXBUF);
		}	           
}


#endif


#ifdef __EE_UART_PORT_2_ISR_ENABLE__
ISR2(USART1RX_VECTOR )
{
/*TODO:If set CTRL_ERROR, in this way I lose error information
Now there is one function that save the error and print it*/
	if (Rx2IsrFunction != NULL) {
		/* Execute callback function */
		if((IFG2 & EE_UART_IS_START_EDGE_2)==0)/*START-EDGE*/ 
			EE_msp430_change_LPM(NO_LPMODE);
		EE_uart_ctrl_error(EE_UART_PORT_2);
		Rx2IsrFunction(U1RXBUF);

		}
	           
}

ISR2(USART1TX_VECTOR )
{
	if (Tx2IsrFunction != NULL) {
		/* Execute callback function */
		Tx2IsrFunction(&U1TXBUF);
		}
	           
}


#endif

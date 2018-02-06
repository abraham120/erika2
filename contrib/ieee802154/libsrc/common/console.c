/*
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */
 
#include "ee.h"
#include "common/console.h"

EE_UINT8 console_port;


/*******************************************************************************
 * Function:        void ee_console_init(EE_UINT8 console_port)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          none
 *
 * Side Effects:    None
 *
 * Overview:        This routine initializes the console.
 *                  
 * Note:            None
 ******************************************************************************/
 
void ee_console_init(EE_UINT8 port)
{ 	
	console_port = port;
	
	if (console_port == UART1)
  		EE_UART1_Init(115200, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);
  	else
  		EE_UART2_Init(115200, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);
  		
}

/*******************************************************************************
 * Function:        void ee_console_out(EE_UINT8 ch)
 *
 * PreCondition:    None
 *
 * Input:           the character to send out to the console.
 *
 * Output:          0 all right, -1 otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This routine send a character to the console.
 *                  
 * Note:            None
 ******************************************************************************/
 
void ee_console_out(EE_UINT8 ch)
{
	/*if (console_port == UART1)
		EE_UART1_Send(ch);
	else
		EE_UART2_Send(ch);*/
}

/*******************************************************************************
 * Function:        void ee_console_out_str(const char *ch)
 *
 * PreCondition:    None
 *
 * Input:           the string to send out to the console.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine send a string to the console.
 *                  
 * Note:            None
 ******************************************************************************/
 
void ee_console_out_str(const char *ch)
{

	while (*ch != '\0') {
		if (console_port == UART1)
			EE_UART1_Send(*ch++);
		else
			EE_UART2_Send(*ch++);
	}

}

char* itoa(EE_UINT8 val, int base){
		static char buf[32] = {0};
		int i = 30;
		for(; val && i ; --i, val /= base)
			buf[i] = "0123456789abcdef"[val % base];
		return &buf[i+1];
}
	
void ee_console_out16_radix(EE_UINT16 val, int radix){
	
	ee_console_out_radix((EE_UINT8)(val >> 8), radix);
	ee_console_out_radix((EE_UINT8)(val & 0x00FF), radix);	
		
}

void ee_console_out32_radix(EE_UINT32 val, int radix){
	ee_console_out_radix((EE_UINT8)(val >> 24), radix);
	ee_console_out_radix((EE_UINT8)(val >> 16), radix);
	ee_console_out_radix((EE_UINT8)(val >> 8), radix);
	ee_console_out_radix((EE_UINT8)(val & 0x000000FF), radix);	
}

void ee_console_out_radix(EE_UINT8 val, int radix)
{
	char *tp;	
	
	if(val == 0){
		if (console_port == UART1){
				EE_UART1_Send('0');
				EE_UART1_Send('0');
		} 
		else{
				EE_UART2_Send('0');
				EE_UART2_Send('0');
		}
		
	}
	else{
		tp = itoa(val, radix);
		if(!(val >> 4)){
			if (console_port == UART1){
				EE_UART1_Send('0');
				EE_UART1_Send(tp[0]);
			}
			else{
				EE_UART2_Send('0');
				EE_UART2_Send(tp[0]);
			}
		}else if( !(val | 0x0F)){
			if (console_port == UART1){
				EE_UART1_Send(tp[0]);
				EE_UART1_Send('0');
			}
			else{
				EE_UART2_Send(tp[0]);
				EE_UART2_Send('0');
			}
		}
		else{
			if (console_port == UART1){
				EE_UART1_Send(tp[0]);
				EE_UART1_Send(tp[1]);
			}
			else{
				EE_UART2_Send(tp[0]);
				EE_UART2_Send(tp[1]);
			}
		}
		
	}
}

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

#include "common/ee_radio_spi.h"


EE_UINT8 spi_port;

/*******************************************************************************
 * Function:        void ee_spi_init(EE_UINT8 spi_port)
 *
 * PreCondition:    None
 *
 * Input:           the spi port
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine initializes (opens) the spi selected by spi_port.
 *                  
 * Note:            None
 ******************************************************************************/

void ee_radio_spi_init(EE_UINT8 port)
{
		spi_port = port;
		
		if (spi_port == RADIO_SPI1) {
			
			SPI1STATbits.SPIEN = 0; /* Disable the SPI module */
		
			/*	Enable SPI internal clock 
			 *	Enable 8 bits communication mode
			 *	Enable Master Mode 
			 *	Primary Prescale 1:1
			 *	Secondary Prescale 8:1
			 *	Note: with these prescale values the port is working at 5 MHz. 
			 */
			// SPI1CON1 = 0x23;
			 SPI1CON1 = 0x3E; /* 10Mhz @ 40MIPS */
			 
			/* Note: because the chip select pin (SS1) does not work properly, we
			 * drive this pin directly setting it as a normal I/O pin.
			 */  
			 SPI1CON2 = 0;
			 SPI1STATbits.SPIEN = 1; /* Enable the SPI module */
			 
		} else {
			SPI2STATbits.SPIEN = 0; /* Disable the SPI module */

			/*	Enable SPI internal clock 
			 *	Enable 8 bits communication mode
			 *	Enable Master Mode 
			 *	Primary Prescale 1:1
			 *	Secondary Prescale 8:1
			 *	Note: with these prescale values the port is working at 5 MHz. 
			 */

			 //SPI2CON1 = 0x23;
			 SPI2CON1 = 0x3E; /* 10Mhz@40MIPS */
	
			/* Note: because the chip select pin (SS1) does not work properly, we
			 * drive this pin directly setting it as a normal I/O pin.
			 */  
			 
			 SPI2CON2 = 0;
			 
			 SPI2STATbits.SPIEN = 1; /* Enable the SPI module */
			 
			
		}				
}

/*******************************************************************************
 * Function:        EE_UINT8 ee_radio_spi_put(EE_UINT8 v)
 *
 * PreCondition:    None
 *
 * Input:           the EE_UINT8 to send
 *
 * Output:          the EE_UINT8 recived during the transmission
 *
 * Side Effects:    None
 *
 * Overview:        This routine sends a EE_UINT8 through the spi port.
 *                  
 * Note:            None
 ******************************************************************************/
extern void (*hal_console_out)(EE_UINT8); 

EE_UINT8 ee_radio_spi_put(EE_UINT8 v)
{
	if (spi_port == RADIO_SPI1) {
		IFS0bits.SPI1IF = 0;
   		SPI1STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while(SPI1STATbits.SPITBF);
   		SPI1BUF = v;
   		while(!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;
   		
   		return (SPI1BUF & 0xff);
	
	} else {
		IFS2bits.SPI2IF = 0;
   		SPI2STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while(SPI2STATbits.SPITBF);
   		SPI2BUF = v;
   		
   		while(!SPI2STATbits.SPIRBF);
   		SPI2STATbits.SPIROV = 0;
   	   
   		return (SPI2BUF & 0xff);
   		
   	}

	return 0;
}

/*******************************************************************************
 * Function:        EE_UINT8 ee_radio_spi_get(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the read EE_UINT8
 *
 * Side Effects:    None
 *
 * Overview:        This routine reads a EE_UINT8 from the radio spi port.
 *                  
 * Note:            None
 ******************************************************************************/

EE_UINT8 ee_radio_spi_get(void)
{
	EE_UINT8 count_while = 0;

	if (spi_port == RADIO_SPI1) {
   		/* wait until the tx buffer is empty */
   		while(SPI1STATbits.SPITBF);
   		SPI1BUF = 0x00;
   		while(!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;
   		
   		return (SPI1BUF & 0xff);
	
	} else {
   		/* wait until the tx buffer is empty */
   		while(SPI2STATbits.SPITBF);
   		SPI2BUF = 0x00;
   		while(!SPI2STATbits.SPIRBF) {
			/*TODO: TRY TO UNDERSTAND THE PROBLEM TOGETHER WITH GIANLUCA */
			count_while++;
			if(count_while > 100){
				SPI2STATbits.SPIROV = 0;
				return 0;
			}
		}
		SPI2STATbits.SPIROV = 0;

   		return (SPI2BUF & 0xff);

   	}   
	return 0; 
} 

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
* @file 	pcf8583.c
* @brief 	PCF8583 real time clock driver - main source file.
* @author 	Dario Di Stefano 
* @date 	2010-08-30
*/

#include "pcf8583.h"
#include "pcf8583_hal.h"

/*	This function updates rt-clock internal time.
	It sends i2c commands to: turn off the clock, write new time 
	and turn on the clock;
*/
int EE_rtc_write_time(const TTime *ttw)
{
	uint8_t tx_data[7];
	
	/* Turn off rt-clock and change the time */					
   	tx_data[0] = RTC_OFF;
   	tx_data[1] = ((ttw->hundredths/10)<<4) + (ttw->hundredths%10);
   	tx_data[2] = ((ttw->seconds/10)<<4) + (ttw->seconds%10);
   	tx_data[3] = ((ttw->minutes/10)<<4) + (ttw->minutes%10);
   	tx_data[4] = ((ttw->hours/10)<<4) + (ttw->hours%10);
   	tx_data[5] = ((ttw->year%4)<<6) + ((ttw->day/10)<<4) +(ttw->day%10);
   	tx_data[6] = ((ttw->month/10)<<4) + (ttw->month%10);
	
   	EE_rtc_write_buffer(RTC_CSR_ADD, tx_data, 7);
	
   	/* Save year in RAM */		
	EE_rtc_write_byte(RTC_YEAR_ADD, ttw->year);						
   	/* Turn on rt-clock */	
	EE_rtc_write_byte(RTC_CSR_ADD, RTC_ON);		
	
	return RTC_NO_ERROR;
}

/* This function reads the rt-clock internal time.  */
int EE_rtc_read_time(TTime *ttr) 
{
	uint8_t rx_data[7];
	int8_t yearmod4, diff;
	
	/* Read the time */			
   	EE_rtc_read_buffer(RTC_HSECONDS_ADD, rx_data, 6);	
   	
	ttr->hundredths = (rx_data[0] >> 4)*10 + (rx_data[0] & 0x0F); 
	ttr->seconds = (rx_data[1] >> 4)*10 + (rx_data[1] & 0x0F); 
	ttr->minutes = (rx_data[2] >> 4)*10 + (rx_data[2] & 0x0F); 
	ttr->hours = (rx_data[3] >> 4)*10 + (rx_data[3] & 0x0F); 
	ttr->day = ((rx_data[4] & 0b00110000) >> 4)*10 + (rx_data[4] & 0x0F); 
	yearmod4 = (rx_data[4] & 0b11000000) >> 6;        	
	ttr->month = ((rx_data[5] & 0b00010000) >> 4)*10 + (rx_data[5] & 0x0F);
 	
	/* Read the year stored in the rt-clock RAM */	
	rx_data[0] = EE_rtc_read_byte(RTC_YEAR_ADD);	
	if(rx_data[0] >= 0){
		diff = yearmod4 - (rx_data[0] & 0x03);	// Calculate the difference (3,2,1,0,-1,-2,-3)
		if (diff!=0 )  							// check if year is changed in RTC
		{										// in this case the new value should be written to RTC RAM at address 16(0x10)  	
			ttr->year = rx_data[0] + ((diff+4) & 0x03);			
			EE_rtc_write_byte(RTC_YEAR_ADD, ttr->year);	
		}
		else
		{
			ttr->year = rx_data[0];	
		}	
	}	
  		
   	return RTC_NO_ERROR;
}




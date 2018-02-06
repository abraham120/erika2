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

#include "sensors.h"

unsigned char angle8, angleH, angleL;
unsigned char light, distanceH, distanceL;
unsigned int  angle, distance;

void I2C_Init(void)
{
	/* Stop I2C port */
	I2C1CONbits.I2CEN = 0;

	/* Disable Interrupts */
	IEC1bits.SI2C1IE = 0;
	IEC1bits.MI2C1IE = 0;

	/* Clear Interrupt flag bits */
	IFS1bits.SI2C1IF = 0;
	IFS1bits.MI2C1IF = 0;

	/* Configre SCL/SDA pin as open-drain */
	ODCGbits.ODCG2=1;
	ODCGbits.ODCG3=1;

	/* Clear Address and mask */
	I2C1ADD=0;
	I2C1MSK=0;

	/* Set baudrate */
	I2C1BRG = 1363;	// With Fcy = 40MHz
	
	/* Configure I2C port */
	I2C1CON = 0;
	I2C1CONbits.ACKDT = 1;
	I2C1CONbits.DISSLW = 1;

	/* Start I2C port */
	I2C1CONbits.I2CEN = 1;
}

unsigned char I2C_ReadByte (unsigned char Device, unsigned char Address)
{
	unsigned char Data = 0;

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed 
	while(I2C1CONbits.SEN);

	// Write Slave address and set master for transmission  (R/W bit should be 0)
	I2C1TRN = Device;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;
	
	// Wait till address is transmitted 
	while(I2C1STATbits.TBF);

	// Test for ACK condition received           
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle 
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Write word address
	I2C1TRN = Address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted 
	while(I2C1STATbits.TBF);

	// Test for ACK condition received           
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Generate the I2C bus restart condition
	I2C1CONbits.RSEN = 1;		// initiate restart on SDA and SCL pins

	// Wait until re-start condition is over      
	while (I2C1CONbits.RSEN);

	// Write Slave address and set master for reception  (R/W bit should be 1)
	I2C1TRN = Device+1;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1 
		return -1;

	// Wait till address is transmitted 
	while(I2C1STATbits.TBF);

	// Test for ACK condition received           
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Read the data byte
	I2C1CONbits.RCEN = 1;
	while(I2C1CONbits.RCEN);
	I2C1STATbits.I2COV = 0;
	Data = I2C1RCV;

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// send NACK condition back to the I2C slave indicating master received the data byte
	I2C1CONbits.ACKDT = 1;
	I2C1CONbits.ACKEN = 1;

	// wait until NACK sequence is over
	while (I2C1CONbits.ACKEN); 

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// send STOP condition
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins 

	// Wait till Stop sequence is completed  
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return (Data);			// return with data
}

char I2C_WriteByte(unsigned char Device, unsigned char Address, unsigned char Data)
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed 
	while(I2C1CONbits.SEN);

	// Write Slave address and set master for transmission  (R/W bit should be 0)
	I2C1TRN = Device;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;
	
	// Wait till address is transmitted 
	while(I2C1STATbits.TBF);

	// Test for ACK condition received           
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle 
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Write word address
	I2C1TRN = Address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted 
	while(I2C1STATbits.TBF);

	// Test for ACK condition received           
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT); 

	// Write data byte to serial EEPROM  
	I2C1TRN = Data;
	if(I2C1STATbits.IWCOL)        /* If write collision occurs,return -1 */
		return -1;

	// Wait till address is transmitted 
	while(I2C1STATbits.TBF);

	// Test for ACK condition received           
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */  

	// Wait till Stop sequence is completed  
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
	
	return 0;
}

char Sensors_Acquire(void)
{
	unsigned char res;
	
	/* Acquire data from compass */
	angle8 = I2C_ReadByte(0xC0,0x01);
	angleH = I2C_ReadByte(0xC0,0x02);
	angleL = I2C_ReadByte(0xC0,0x03);

	angle = (angleH * 256) + angleL;
	
	/* Acquire data from US sensor */
	// Acquire US sensor version 
	res = I2C_ReadByte(0xE0,0x00);
	if (res != 0xFF) {
		light = I2C_ReadByte(0xE0,0x01);
		distanceH = I2C_ReadByte(0xE0,0x02);
		distanceL = I2C_ReadByte(0xE0,0x03);
	
		distance = ((distanceH * 256) + distanceL)*8;
		
	} else {
		light = 0;
		distanceH = 0;
		distanceL = 0;
		
		distance = 0;
		
		return -1;
	}
	
	// Send request
	I2C_WriteByte(0xE0,0x00,0x51);
	
	// Wait till ACK
	//unsigned long i = 0;
	//while((i<100000)&&(I2C_ReadByte(0xE0,0x00) == 0xFF)) i++;
	//while(I2C_ReadByte(0xE0,0x00) == 0xFF);
	//while(i<100000) i++;
	
	return 0;
}

/* ------------------------------------------------------------------------- */

void Serial_Init(void)
{
	/* Stop UART port */
	U1MODEbits.UARTEN = 0;
	
	/* Disable Interrupts */
	IEC0bits.U1RXIE = 0;
	IEC0bits.U1TXIE = 0;
	
	/* Clear Interrupt flag bits */
	IFS0bits.U1RXIF = 0;
	IFS0bits.U1TXIF = 0;
		
	/* Set IO pins */
	TRISDbits.TRISD14 = 0;
	TRISDbits.TRISD15 = 0;
	TRISFbits.TRISF3 = 0;
	TRISFbits.TRISF2 = 1;
	
	/* baud rate */
	U1BRG  = 21; // With Fcy = 40MHz
	
	/* Operation settings and start port */
	U1MODE = 0;
	U1MODEbits.UEN = 0; //2
	U1MODEbits.BRGH = 0;
	U1MODEbits.UARTEN = 1;

	/* TX & RX interrupt modes */
	U1STA = 0;
	U1STAbits.UTXEN=1;
}

int Serial_Send(unsigned char data)
{
	unsigned int i;
	
	while (U1STAbits.UTXBF);
	U1TXREG = data;
	while(!U1STAbits.TRMT);
	
	for(i=0; i<2000; i++);
	
	return 0;
}

int Serial_Receive(unsigned char* data)
{
	if (U1STAbits.OERR) {
		U1STAbits.OERR = 0;
		return -2;
	}
	
	if (U1STAbits.URXDA) {
		*data = U1RXREG & 0x00FF;
		return 0;
	} else {
		*data = 0;
		return -1;
	}
}

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
* \file ee_sci.h
* \brief SCI driver, Erika HCS12 mcu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/


#ifdef __USE_SCI__

#ifndef __INCLUDE_FREESCALE_S12XS_SCI_H__
#define __INCLUDE_FREESCALE_S12XS_SCI_H__

#include "mcu/hs12xs/inc/ee_mcu.h"
/* Include a file with the registers of the s12 micro-controller */ 
#include "mcu/hs12xs/inc/ee_mcuregs.h"


#if defined (__MC9S12G96__) || defined (__MC9S12G128__)
  #define SCI_0             0
  #define SCI_1             1
  #define SCI_2             2
#elif defined (__MC9S12XS64__) || defined (__MC9S12XS128__) || defined (__MC9S12XS256__)\
              || defined (__MC9S12G48__) || defined (__MC9S12GN48__)
  #define SCI_0             0
  #define SCI_1             1
#elif defined (__MC9S12GN16__) || defined (__MC9S12GN32__)
  #define SCI_0             0
#else
  #error SCI not supported for this derivative!
#endif

#define ALL               65000

#define SCIBDH            0x00
#define SCIBDL            0x01
#define SCICR1            0x02
#define SCIASR1           0x00
#define SCIACR1           0x01
#define SCIACR2           0x02
#define SCICR2            0x03
#define SCISR1            0x04
#define SCISR2            0x05
#define SCIDRH            0x06
#define SCIDRL            0x07

typedef struct EE_sci_peripheral_t {
	int ena;
	unsigned char *init_reg;
} EE_sci_peripheral;

extern volatile EE_sci_peripheral EE_sci[];

/**
 * \brief				This function is used to open the Serial Communication Interface.
 * \param sci_num		Number of the SCIx to be used.
 * \param baudrate		Serial communication baudrate (SCI BAUD RATE = BUSCLK/(16*BR)).
 * \return				-1 in case of error, 0 if it returns successfully.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_sci_open(unsigned char sci_num, unsigned long int baudrate) {

	unsigned int br = 0;
	unsigned char *sci_pt;
	unsigned long int busclock = EE_get_peripheral_frequency_mhz()*1000000ul;
	
	if(EE_get_peripheral_frequency_mhz()==0)
		return -1;

	EE_sci[sci_num].ena = 1;
	sci_pt = EE_sci[sci_num].init_reg;
	/* Set Baud Rate Modulo Divisor */
	br = (unsigned int)(busclock / (baudrate*((unsigned long int)16)));
	sci_pt[SCIBDH] = (unsigned char)(br >> 8);
	sci_pt[SCIBDL] = (unsigned char)(br&0x00FF);
	/* Trasmitter and Receiver Enable */
	sci_pt[SCICR2] = 0x0C;
	return 0;
}

/**
 * \brief				This function is used to close the Serial Communication Interface and
                        disable transmit and receive data.
 * \param sci_num		Number of the SCIx to be closed.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_sci_close(unsigned char sci_num) {

	unsigned char *sci_pt;
	unsigned char data;
	unsigned int i;

	EE_sci[sci_num].ena = -1;
	sci_pt = EE_sci[sci_num].init_reg;
	i = 0;
	/* Verify that Receive Data Register is FULL */
	while (i < 1000 && !(sci_pt[SCISR1]&0x20)) { 
		i++;
	}
	if (sci_pt[SCISR1]&0x20) {
		/* Clear RDRF Flag */
		data = sci_pt[SCIDRL];
	}
	sci_pt[SCIBDH] = 0;
	sci_pt[SCIBDL] = 0;
	/* Trasmitter and Receiver Disable */
	sci_pt[SCICR2] = 0;
}

/**
 * \brief				This function is used to transmit a byte through the Serial Communication Interface.
 * \param sci_num		Number of the SCIx to be used.
 * \param txbyte		Byte to transmit.
 * \return				True if the byte has been transmitted.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_sci_send_byte(unsigned char sci_num, unsigned char txbyte) {

	unsigned char *sci_pt;

	if (!EE_sci[sci_num].ena) {
		return -1;
	}
	sci_pt = EE_sci[sci_num].init_reg;
	/* Wait until Transmit Data Register is empty. */
	while (!(sci_pt[SCISR1] & 0x80))
		;
	/* Send byte and clear TDRE flag */
	sci_pt[SCIDRL] = txbyte;
	return 1;
}

/**
 * \brief				This function is used to transmit a string through the Serial Communication Interface.
 * \param sci_num		Number of the SCIx to be used.
 * \param s			String to transmit.
 * \param num			String length.
 * \return				True if the string has been transmitted.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_sci_send_string(unsigned char sci_num, const char* s, unsigned int num) {

	unsigned int i = 0;
	int res = 1;
	
	while ((s[i]!='\0') && (i<num)) {
		res = EE_sci_send_byte(sci_num,s[i]);
		i++;
		if (res==-1) {
			break;
		}
	}
	return res;
}

/**
 * \brief				This function is used to transmit an array of chars through the Serial Communication Interface.
 * \param sci_num		Number of the SCIx to be used.
 * \param v			Array to transmit.
 * \param num			Number of bytes.
 * \return				True if the array has been transmitted.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_sci_send_bytes(unsigned char sci_num, char* v, unsigned int num) {

	unsigned int i = 0;
	int res = 1;

	while ((v[i]!='\0') && (i<num)) {
		res = EE_sci_send_byte(sci_num,v[i]);
		i++;
		if (res==-1) {
			break;
		}
	}
	return res;
}

/**
 * \brief				This function is used to receive a byte through the Serial Communication Interface.
 * \param sci_num		Number of the SCIx to be used.
 * \param buffer		Address to save the received byte.
 * \return				True if the array has been received.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_sci_get_byte(unsigned char sci_num, unsigned char *buffer) {

	unsigned char *sci_pt;

	if (!EE_sci[sci_num].ena){
		return -1;
	}
	sci_pt = EE_sci[sci_num].init_reg;
	while (!(sci_pt[SCISR1]&0x20)) {
		;
	}
	/* Get Buffer and clear RDRF flag */
	*buffer = sci_pt[SCISR1];
	*buffer = sci_pt[SCIDRL];
	return 1;
}


/**
 * \brief				This function is used to check data receive through the Serial Communication Interface.
 * \param sci_num		Number of the SCIx to be used.
 * \return				True if receiver data register (SCIDR) is full.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_sci_getcheck(unsigned char sci_num) {

	unsigned char *sci_pt;

	if (!EE_sci[sci_num].ena) {
		return -1;
	}
	sci_pt = EE_sci[sci_num].init_reg;
	if (sci_pt[SCISR1]&0x20) {
		return 1;
	}
	return -1;
}

#endif

#endif

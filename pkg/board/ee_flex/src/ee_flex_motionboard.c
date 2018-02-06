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

/*
 * Author: 20065 Mauro Marinoni
 * CVS: $Id: ee_board.c,v 1.11 2008/08/29 11:21:08 francesco Exp $
 */
#ifdef __USE_MOTIONBOARD__

#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"


/******************************************************************************/
/*                              Buttons                                       */
/* Author: Gianluca Franchino                                                                */
/******************************************************************************/
#ifdef __USE_BUTTONS__

void (*EE_buttonS1_callback)(void);
void (*EE_buttonS2_callback)(void);

ISR2(_IC2Interrupt)
{
	IFS0bits.IC2IF = 0;

	if (EE_buttonS2_callback != NULL)
		EE_buttonS2_callback();
}

ISR2(_IC4Interrupt)
{
	IFS2bits.IC4IF = 0;

	if (EE_buttonS1_callback != NULL)
		EE_buttonS1_callback();
}
#endif

/************************************************************************* */
/*                                Analog input                             */
/************************************************************************* */

#if defined(__USE_ANALOG_SENSORS__) || defined(__USE_TRIMMER__) || defined(__USE_ACCELEROMETER__) || defined(__USE_ADC__)
EE_UINT8 ee_adc_init_flag = 0;
#endif

#ifdef __USE_ACCELEROMETER__
EE_UINT8 EE_accelerometer_g = 6;
#endif

/******************************************************************************/
/*                                   U S B                                    */
/******************************************************************************/
#if defined __USE_USB__

#include <string.h>

#define USB_PIC18_REQ 		LATDbits.LATD12
#define USB_PIC18_REQ_TRIS 	TRISDbits.TRISD12
#define FLEX_USB_HEADER_START 0x15	/**< The start header: 10101 */
#define FLEX_USB_PACKET_PAYLOAD_SIZE 60	/**< The packet payload size */
#ifndef FLEX_USB_RX_BUFFER_SIZE
#define FLEX_USB_RX_BUFFER_SIZE	240
#endif

struct flex_usb_packet_t {
	/*CHRIS: TODO: METTERE LA CRC IN FONDO!!!!! */
	unsigned crc : 8;       /**< The checksum, including header */
	unsigned start : 5;	/**< Commone header 10101 */
	unsigned type : 3;	/**< Packet type */
	unsigned more : 1; 	/**< Is last fragment */
	unsigned seq : 4; 	/**< Fragment sequence number */
	unsigned reserved1 : 3;	/**< Reserverd (seq, length) */
	unsigned reserved2 : 2;	/**< Reserverd (seq, length) */
	unsigned length : 6;	/**< Payload lenght */
	EE_UINT8 payload[FLEX_USB_PACKET_PAYLOAD_SIZE]; /**< Packet payload */
	//EE_UINT8 crc;		/**< The checksum, including header */
};

enum flex_usb_header_type_t {
	FLEX_USB_HEADER_NULL = 0x00,
	FLEX_USB_HEADER_COMMAND = 0x01,
	FLEX_USB_HEADER_DATA = 0x02,
	FLEX_USB_HEADER_ACK = 0x03,
};

enum flex_usb_command_type_t {
	FLEX_USB_COMMAND_CONNECT = 0x0001,
	FLEX_USB_COMMAND_DISCONNECT = 0x0002,
};

static struct flex_usb_packet_t dma_tx_pkt __attribute__((space(dma)));
static struct flex_usb_packet_t dma_rx_pkt __attribute__((space(dma)));
static EE_UINT8 rx_buffer[FLEX_USB_RX_BUFFER_SIZE] __attribute__((far));
static EE_UINT16 rx_first = 0;
static EE_UINT16 rx_last = 0;
static EE_UINT16 rx_held = 0;
static EE_INT8 usb_initialized = 0;
//static volatile char dummy_send_lock = 0;

void EE_usb_init(void)
{
	if(usb_initialized)
		return;
	/* dsPIC SPI communication busy */
	USB_PIC18_REQ_TRIS = 0;	/* Output: USB request by dsPIC (SPI Slave) */
	USB_PIC18_REQ = 0; 	/* No request at the beginning */
	/* Following code shows SPI register configuration for SLAVE Mode */
  	SPI1BUF = 0x00;
  	SPI1CON1bits.DISSCK = 0;/* Internal Serial Clock is Enabled. */
  	SPI1CON1bits.DISSDO = 0;/* SDOx pin is controlled by the module. */
  	SPI1CON1bits.MODE16 = 0;/* Communication is byte-wide (8 bits).*/
  	SPI1CON1bits.SMP = 0; 	/* Input Data is sampled at the middle of data
				   output time. */
	SPI1CON1bits.CKE = 0; 	/* Serial output data changes on transition from
				   Idle clock state to active clock state. */
  	SPI1CON1bits.CKP = 0; 	/* Idle state for clock is a low level; active
				   state is a high level. */
  	SPI1CON1bits.MSTEN = 0; /* Master Mode disabled. */
  	SPI1CON1bits.SSEN = 0; 	/* Slave Select pin NOT used by SPI. */
  	SPI1STATbits.SPIROV = 0;/* No Receive Overflow Has Occurred. */
  	SPI1STATbits.SPIEN = 1; /* Enable SPI Module. */
  	IFS0bits.SPI1IF = 0;
  	IEC0bits.SPI1IE = 0;
  	/* DMA0 configuration for SPI Tx */
  	DMA0CON = 0;		/* Restore Default */
	DMA0CONbits.SIZE = 1; 	/* Byte oriented */
	DMA0CONbits.DIR = 1; 	/* From DMA memory to peripheral */
	DMA0CONbits.MODE = 1; 	/* One shot, ping-pong disabled */
  	DMA0REQ = 0x00A;
  	DMA0PAD = (volatile EE_UINT16) &(SPI1BUF);
  	DMA0STA = __builtin_dmaoffset(&dma_tx_pkt);
  	DMA0CONbits.CHEN = 0;	/* Disable Tx DMA Channel. */
  	IFS0bits.DMA0IF = 0;
  	IEC0bits.DMA0IE = 0;
  	/* DMA1 configuration for SPI Rx; lower priority than DMA0 */
  	DMA1CON = 0;		/* Restore Default */
	DMA1CONbits.SIZE = 1; 	/* Byte oriented */
	//DMA1CONbits.MODE = 1; 	/* One shot, ping-pong disabled */
  	DMA1REQ = 0x00A;
  	DMA1PAD = (volatile EE_UINT16) &SPI1BUF;
  	DMA1STA = __builtin_dmaoffset(&dma_rx_pkt);
	DMA1CNT = 63;	/* NOTE 63 = sizeof(dma_tx_pkt) - 1 */
  	IFS0bits.DMA1IF = 0;
  	IEC0bits.DMA1IE = 1;
  	DMA1CONbits.CHEN = 1;	/* Enable Rx DMA Channel. */
	/* Init variables */
	memset(rx_buffer, 0, FLEX_USB_RX_BUFFER_SIZE);
	rx_first = 0;
	rx_last = 0;
	rx_held = 0;
	//dummy_send_lock = 0;
	usb_initialized = 1;
}

EE_INT16 EE_usb_write(EE_UINT8 *buf, EE_UINT16 len)
{
	EE_UINT16 i;
	EE_UINT8 sum;

	/* chris: current policy is: have no packet buffer, no fragmentation,
		  no ack and wait until the previous packet transmission ends.
	*/
	if (len == 0 || len > FLEX_USB_PACKET_PAYLOAD_SIZE)
		return -1;
	//while (USB_PIC18_REQ) ; /* Wait previous transfer to be completed. */
	if(USB_PIC18_REQ) 
		return -1; 
	memset((EE_UINT8 *) &dma_tx_pkt, 0x0, 64);
	dma_tx_pkt.start = FLEX_USB_HEADER_START;
	dma_tx_pkt.type = FLEX_USB_HEADER_DATA;
	dma_tx_pkt.more = 0;
	dma_tx_pkt.seq = 0;
	dma_tx_pkt.length = len;
	memcpy(dma_tx_pkt.payload, buf, len);
	/* NOTE 63 = sizeof(dma_tx_pkt) - sizeof(CRC) */
	//for (sum = 0, i = 0; i < 63; i++)
	for (sum = 0, i = 1; i < 64; i++) // COMPLIANT TO "HEADER" CRC
		sum += ((EE_UINT8 *) &dma_tx_pkt)[i];
	dma_tx_pkt.crc = sum;
	DMA0STA = __builtin_dmaoffset(&dma_tx_pkt);
	DMA0CNT = 63;	/* NOTE 63 = sizeof(dma_tx_pkt) - 1 */
	IFS0bits.DMA0IF  = 0;
	IEC0bits.DMA0IE  = 1;
	DMA0CONbits.CHEN = 1;
	DMA0REQbits.FORCE = 1;
	USB_PIC18_REQ = 1;	/* Request transmission */
	/* chris: TODO: non usare il bloccaggio attivo qui!!! */
	//dummy_send_lock = 1;
	//while (dummy_send_lock) ;
	return len;
}

EE_INT16 EE_usb_read(EE_UINT8 *buf, EE_UINT16 len)
{
	EE_UINT16 idx;

	if (len == 0 || len > FLEX_USB_RX_BUFFER_SIZE)
		return -1;
  	IEC0bits.DMA1IE = 0;	/* mutex: disable DMA SPI RX Interrupt */
	if (rx_held == 0) {
  		IEC0bits.DMA1IE = 1;	/* mutex: enable DMA SPI RX Interrupt */
		return 0;
	}
	if (len > rx_held)
		len = rx_held;
	idx = (rx_first + len) % FLEX_USB_RX_BUFFER_SIZE;
	/* NOTE: idx = new_first position for rx */
	if (idx > rx_first) {
		/* Message is located from rx_first to the end of the buffer. */
		memcpy(buf, rx_buffer + rx_first, len);
	} else {
		/* The first part of message is stored from rx_first to the end
		    of the buffer, the remaining part goes from the of the
		    begin buffer to idx index.  */
		memcpy(buf, rx_buffer + rx_first,
		       FLEX_USB_RX_BUFFER_SIZE - rx_first);
		memcpy(buf + (FLEX_USB_RX_BUFFER_SIZE - rx_first),
		       rx_buffer, idx + 1);
	}
	rx_held -= len;
	rx_first = idx;
  	IEC0bits.DMA1IE = 1;	/* mutex: enable DMA SPI RX Interrupt */
	/* chris: note: if len > 2^16 a wrong negative value is returned */
	return (EE_INT16) len;
}

/**
* @brief DMA ISR for SPI transmission
*/
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	IFS0bits.DMA0IF  = 0;
	IEC0bits.DMA0IE  = 0;
	DMA0CONbits.CHEN = 0;
	/* TODO: do something eventually here to start another transfer */
	/* chris: TODO: versione di test.... sblocca il dummy lock! */
	USB_PIC18_REQ = 0;
	//dummy_send_lock = 0;
}

/**
* @brief DMA ISR for SPI reception
*/
void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
	EE_UINT16 idx;
	IFS0bits.DMA1IF = 0;
	/* TODO: controllare header start, controllare CRC */
	if (dma_rx_pkt.type == FLEX_USB_HEADER_DATA) {
		/* If the read message is larger than the whole buffer,
		   write the last FLEX_USB_RX_BUFFER_SIZE bytes in the buffer.
		   TODO: is this a possible scenario?? */
		/* NOTE: idx as temp vari to silent compiler */
		idx = dma_rx_pkt.length; 
		if (idx >= FLEX_USB_RX_BUFFER_SIZE) {
			idx = dma_rx_pkt.length - FLEX_USB_RX_BUFFER_SIZE;
			memcpy(rx_buffer, dma_rx_pkt.payload + idx,
			       FLEX_USB_RX_BUFFER_SIZE);
			rx_last = 0;
			rx_first = 0;
			rx_held = FLEX_USB_RX_BUFFER_SIZE;
			return;
		}
		if (FLEX_USB_RX_BUFFER_SIZE - rx_held < dma_rx_pkt.length) {
			/* Overriding condition: implement shift policy
			   on the rx_first indec,  idx=amount of
			   overriding bytes. */
			idx = dma_rx_pkt.length -
			      (FLEX_USB_RX_BUFFER_SIZE - rx_held);
			rx_first = (rx_first + idx) % FLEX_USB_RX_BUFFER_SIZE;
		}
		/* NOTE: idx = new_last position for rx */
		idx = (rx_last + dma_rx_pkt.length) % FLEX_USB_RX_BUFFER_SIZE;
		if (idx > rx_last) {
			/* The message fits from rx_last to the
			   end of the buffer. */
			memcpy(rx_buffer + rx_last, dma_rx_pkt.payload,
			       dma_rx_pkt.length);
		} else {
			/* The first part of message must be stored
			   from rx_last to the end of the buffer, the
			   remaining part goes from begin buffer to
			   idx index.  */
			memcpy(rx_buffer + rx_last, dma_rx_pkt.payload,
			       (FLEX_USB_RX_BUFFER_SIZE - rx_last));
			memcpy(rx_buffer,
			       dma_rx_pkt.payload + FLEX_USB_RX_BUFFER_SIZE -
			       rx_last, idx+1);
		}
		rx_last = idx;
		rx_held += dma_rx_pkt.length;
	}
}

#endif /* __USE_USB__ */

/******************************************************************************/
/*                                   PWM Out                                  */
/******************************************************************************/
#ifdef __USE_PWM__

EE_UINT8 t_pre_scaler;

void EE_ocpwm_init(EE_UINT8 chan, EE_UINT32 pwm_period, EE_UINT32 init_pw)
{
	/* OutputCompare PWM constants
	*
	* pwm_timer2_period = (fcy/pre_scaler) x pwm_period - 1
	*     fcy [MHz]
	*     pwm_perdiod [microseconds]
	*
	* pwm_resolution = log_2((fcy/pre_scaler) x pwm_perdiod) [bits]
	*/
	EE_UINT8 pre_scaler=0;
	EE_UINT16 p=0;
	/* Check PW limits */
	if (init_pw > pwm_period)
		return;
	T2CON = 0; /* Stops the Timer2 and reset control reg */
	TMR2  = 0; /* Clear contents of the timer register */
	IFS0bits.T2IF = 0; /* Clear the Disable Timer2 interrupt status flag */
	IEC0bits.T2IE = 0;
	/* Calculate the best(minimum) pre-scaling factor */
	for (pre_scaler = 0; pre_scaler < 4; pre_scaler++) {
		p = (((40*pwm_period) -1) / 0xFFFE) + 1;
		if (pre_scaler < 3) {
			if (p <= (0x0001 << (pre_scaler*3))) {
				p = (pre_scaler*3);
				break;
			}
		} else {
			if (p <= 256) {
				p = 8;
				break;
			}
		}
	}
	if(pre_scaler > 3)
		return;
	 /* Set pre-scaler for Timer2 */
	T2CONbits.TCKPS = pre_scaler;	
	t_pre_scaler = p;
	PR2 = ((pwm_period * 40) >> p);
	if(PR2 > 0) 
		PR2 -= 1; /* Set period for Timer2 */
	p = (EE_UINT16)(( init_pw * 40) >> p );
	if(p>0) 
		p -= 1;	/* Compute the initial PulseWidth to set */
	p = PR2 - p;
	switch(chan)
	{
	case EE_PWM_PORT1:
		TRISDbits.TRISD7 = 0; /* Set OC8 as output */
		OC8R = p; /* Set the initial duty cycle */
		OC8RS = p; /* Load OCRS: current pwm duty cycle */
		OC8CON = 0x0006; /* Set OC8: PWM, no fault check, Timer2 */
		break;
	case EE_PWM_PORT2:
		TRISDbits.TRISD6 = 0; /* Set OC7 as output */
		OC7R = p; /* Set the initial duty cycle */
		OC7RS = p; /* Load OCRS: current pwm duty cycle */
		OC7CON = 0x0006; /* Set OC7: PWM, no fault check, Timer2 */
		break;
	}
	T2CONbits.TON = 1; 
	return;
}

void EE_ocpwm_set_duty_f( EE_UINT8 chan , float duty )
{
	float duty_out;/* The computed duty cycle*/
	/* Get period from Timer2 period register PR2 */
	EE_UINT16 period = PR2;

	if (duty <= 0.0)
		duty_out = 0; //** for negative values assume zero
	else if(duty >= 1.0)
		duty_out = 1; //** for exessive values assume one
	else
		duty_out = duty; //** for the correct values ...

	duty_out = 1.0 - duty_out;

	// Computer register valure
	switch (chan) {
	case EE_PWM_PORT1:
		OC8RS = duty_out * (period + 1);
		break;
	case EE_PWM_PORT2:
		OC7RS = duty_out * (period + 1);
		break;
	}
}
#endif // __USE_PWM__

/******************************************************************************/
/*                                   DC-Motor PWM Out                         */
/******************************************************************************/
#ifdef __USE_DCM_PWM__

int EE_dcm_pwm_init(EE_UINT8 chan, EE_UINT32 pwm_freq, EE_UINT16 init_duty, EE_INT8 dir)
{
	/* PWM tri-state */
	EE_DCM_EN_M1_TRIS = 	    0;		    // pwm enable pin configuration	(D7/OC8 for L293D, EN_M1)
	EE_DCM_EN_M2_TRIS = 	    0;		    // pwm enable pin configuration (D6/OC7 for L293D, EN_M2)

	if(PTCONbits.PTEN==0)
	{
		EE_UINT16 ptper = (EE_UINT32)(40000000) / pwm_freq;	
		
		if( (ptper <= 1) || (init_duty > 100) )
			return -1;

		PTCONbits.PTEN = 	0;
		PTCONbits.PTSIDL = 	0;		//PWM time base runs in CPU Idle mode
		PTCONbits.PTOPS = 	0b0000;	//1:1 postscale
		PTCONbits.PTCKPS = 	0b00;	//PWM time base input clock period is TCY (1:1 prescale)
		PTCONbits.PTMOD = 	0b00;	//PWM time base operates in a Free-Running mode
		PTMRbits.PTMR = 	0;
		PTPER = 			ptper - 1;	// prescaler == 1
		SEVTCMP = 			0;
		
		PWMCON1bits.PMOD4 = 1;	    //PWM I/O pin pair is in Independent PWM Output mode
		PWMCON1bits.PMOD3 = 1;	    //PWM I/O pin pair is in Independent PWM Output mode
		PWMCON1bits.PMOD2 = 1;	    //PWM I/O pin pair is in Independent PWM Output mode
		PWMCON1bits.PMOD1 = 1;	    //PWM I/O pin pair is in Independent PWM Output mode
		PWMCON1bits.PEN4H = 0;	    //PWMxy pin is disabled for PWM output
		PWMCON1bits.PEN4L = 0;	    //PWMxy pin is disabled for PWM output
		PWMCON1bits.PEN3H = 0;	    //PWMxy pin is disabled for PWM output
		PWMCON1bits.PEN3L = 0;	    //PWMxy pin is disabled for PWM output
		PWMCON1bits.PEN2H = 1;		//PWMxy pin is enabled for PWM output
		PWMCON1bits.PEN2L = 1;		//PWMxy pin is enabled for PWM output
		PWMCON1bits.PEN1H = 1;		//PWMxy pin is enabled for PWM output
		PWMCON1bits.PEN1L = 1;		//PWMxy pin is enabled for PWM output
	
		PWMCON2bits.SEVOPS = 0b0000;
		PWMCON2bits.IUE = 	0;
		PWMCON2bits.OSYNC = 1;
		PWMCON2bits.UDIS = 	0;

		DTCON1 = 			0;
		DTCON2 = 			0;	
		FLTACON = 			0;
		FLTBCON = 			0;

		OVDCONbits.POUT4H = 0;	 
		OVDCONbits.POUT4L = 0;	 
		OVDCONbits.POUT3H = 0; 
		OVDCONbits.POUT3L = 0; 
		OVDCONbits.POUT2H = 0; 
		OVDCONbits.POUT2L = 0; 
		OVDCONbits.POUT1H = 0; 
		OVDCONbits.POUT1L = 0;
		OVDCONbits.POVD4H = 0;	
		OVDCONbits.POVD4L = 0;	
		OVDCONbits.POVD3H = 0; 	
		OVDCONbits.POVD3L = 0;	
		OVDCONbits.POVD2H = 0;      // OVERRIDE
		OVDCONbits.POVD2L = 0; 	    // OVERRIDE
		OVDCONbits.POVD1H = 0; 	    // OVERRIDE
		OVDCONbits.POVD1L = 0;	    // OVERRIDE
		
		PDC1 = 0<<1;	
		PDC2 = 0<<1;
		PDC3 = 0<<1;
		PDC4 = 0<<1;
		
		EE_dcm_pwm_enable_chan(chan);
		EE_dcm_pwm_set_direction(chan, dir);
		EE_dcm_pwm_set_duty(chan, init_duty);
		
		IEC3bits.FLTAIE = 	0;
		IEC3bits.PWMIE = 	0;
		IEC4bits.FLTBIE = 	0; 
		PTCONbits.PTEN = 	1;
    }
	else
	{
		EE_dcm_pwm_enable_chan(chan);
		EE_dcm_pwm_set_direction(chan, dir);
		EE_dcm_pwm_set_duty(chan, init_duty);
	}
	return 1;
}

void EE_dcm_pwm_enable_chan(EE_UINT8 chan)
{
	switch (chan) {
		case EE_DCM_PORT1:
			EE_DCM_EN_M1 = 1;
			break;
		case EE_DCM_PORT2:
			EE_DCM_EN_M2 = 1;
			break;
	}
}

void EE_dcm_pwm_disable_chan(EE_UINT8 chan)
{
	switch (chan) {
		case EE_DCM_PORT1:
			EE_DCM_EN_M1 = 0;
			break;
		case EE_DCM_PORT2:
			EE_DCM_EN_M2 = 0;
			break;
	}
}

void EE_dcm_pwm_set_duty(EE_UINT8 chan, EE_UINT32 duty)
{
	switch (chan) {
		case EE_DCM_PORT1:
			PDC1 = (EE_UINT16)(((EE_UINT32)duty * (EE_UINT32)(PTPER+1))/((EE_UINT32)100)) << 1;	// please, note the shift operation...
			break;
		case EE_DCM_PORT2:
			PDC2 = (EE_UINT16)(((EE_UINT32)duty * (EE_UINT32)(PTPER+1))/((EE_UINT32)100)) << 1;	// please, note the shift operation...
			break;
	}
}

void EE_dcm_pwm_set_direction(EE_UINT8 chan , EE_INT8 dir)
{
	switch (chan) {
		case EE_DCM_PORT1:
			if(dir > 0){
				OVDCONbits.POVD1H = 1;      // PWM
				OVDCONbits.POVD1L = 0;      // OVERRIDE
			}
			else if(dir < 0){
				OVDCONbits.POVD1H = 0;      // OVERRIDE
				OVDCONbits.POVD1L = 1;      // PWM
			}
			else{ // dir==0 
				OVDCONbits.POVD1H = 0;      // OVERRIDE
				OVDCONbits.POVD1L = 0;      // OVERRIDE
			}
			break;
		case EE_DCM_PORT2:
			if(dir > 0)
			{
				OVDCONbits.POVD2H = 1;      // PWM
				OVDCONbits.POVD2L = 0;      // OVERRIDE
			}
			else if(dir < 0)
			{
				OVDCONbits.POVD2H = 0;      // OVERRIDE
				OVDCONbits.POVD2L = 1;      // PWM
			}
			else{ // dir==0 
				OVDCONbits.POVD2H = 0;      // OVERRIDE
				OVDCONbits.POVD2L = 0;      // OVERRIDE
			}
			break;
	}
}

void EE_dcm_pwm_close(void)
{
	PTCONbits.PTEN = 0;
}

#endif // __USE_DCM_PWM__

#ifdef __USE_ENCODER__

/* SW encoder */
EE_UINT16 ee_encsw_poscnts;
EE_INT16 ee_encsw_swapped;
EE_INT16 ee_encsw_maxcnt;
EE_UINT16 ee_encsw_encdir;
//EE_UINT16 ee_encsw_poscnts_h;
EE_INT8 ee_encsw_over_under_flow;
const EE_UINT16 ee_enc_poscnts_offset = 0x8000;

ISR2(_IC1Interrupt)
{
	IFS0bits.IC1IF = 0;
	
	EE_pic30_disableIRQ();
	if(ee_encsw_swapped)
		ee_encsw_encdir = (!(EE_ENCODER_SW_PINA ^ EE_ENCODER_SW_PINB))?  1: 0;
	else
		ee_encsw_encdir = (EE_ENCODER_SW_PINA ^ EE_ENCODER_SW_PINB)?     1: 0;
	if(ee_encsw_encdir) {
		EE_INT8 rflag1 = 0, rflag2 = 0;
		//ee_encsw_poscnts_h = EE_encoder_ISR_cbk(ee_encsw_encdir, ++ee_encsw_poscnts, ee_encsw_poscnts_h, &rflag1);
		//ee_encsw_poscnts_h = EE_encoder_ISR_cbk(ee_encsw_encdir, ++ee_encsw_poscnts, ee_encsw_poscnts_h, &rflag2);
		EE_encoder_ISR_cbk(ee_encsw_encdir, ++ee_encsw_poscnts, ee_enc_poscnts_offset, &rflag1);
		EE_encoder_ISR_cbk(ee_encsw_encdir, ++ee_encsw_poscnts, ee_enc_poscnts_offset, &rflag2);
		ee_encsw_over_under_flow = (rflag1)? rflag1 : rflag2;
	}
	else {
		EE_INT8 rflag1 = 0, rflag2 = 0;
		//ee_encsw_poscnts_h = EE_encoder_ISR_cbk(ee_encsw_encdir, --ee_encsw_poscnts, ee_encsw_poscnts_h, &rflag1);
		//ee_encsw_poscnts_h = EE_encoder_ISR_cbk(ee_encsw_encdir, --ee_encsw_poscnts, ee_encsw_poscnts_h, &rflag2);
		EE_encoder_ISR_cbk(ee_encsw_encdir, --ee_encsw_poscnts, ee_enc_poscnts_offset, &rflag1);
		EE_encoder_ISR_cbk(ee_encsw_encdir, --ee_encsw_poscnts, ee_enc_poscnts_offset, &rflag2);
		ee_encsw_over_under_flow = (rflag1)? rflag1 : rflag2;
	}
	EE_pic30_enableIRQ();
}

/* HW encoder */

void (*QEI_cbk)(void);
//EE_UINT16 ee_enchw_poscnts_h;
EE_INT8 ee_enchw_over_under_flow;

ISR2(_QEIInterrupt)	// High priority interrupt
{
	EE_pic30_disableIRQ();
	IFS3bits.QEIIF = 0;
	//ee_enchw_poscnts_h = EE_encoder_ISR_cbk(QEICONbits.UPDN, POSCNT, ee_enchw_poscnts_h, &ee_enchw_over_under_flow);
	EE_encoder_ISR_cbk(QEICONbits.UPDN, POSCNT, 0, &ee_enchw_over_under_flow);
	EE_pic30_enableIRQ();
	
	if(QEI_cbk!=0)
		QEI_cbk();
}

#endif // __USE_ENCODER__ 

#endif // __USE_MOTIONBOARD__


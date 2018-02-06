/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
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
	@file flex_can.c
	@brief www.scicos.org, www.scicoslab.org
	@author Dario Di Stefano, Evidence Srl
	@date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"
#include "pic30/communication/flex_can.h"

/* initializagtion flag, used inside EE_eCAN1_init */
volatile EE_UINT8 ee_ecan1_initialized = 0;

/* BLOCKS */
/* CAN1_tx_block CAN1_tx_blocks[CAN1_BLOCK_TX_NUM]; */
CAN1_rx_block CAN1_rx_blocks[CAN1_BLOCK_RX_NUM];

/* Rx and Tx buffers */
EE_UINT8 scicosCAN1_rx_buffer[CAN_DATA_LEN];
EE_UINT8 scicosCAN1_tx_buffer[CAN_DATA_LEN];
DEF_TEST_VARS();

int EESCI_eCAN1_get_rx_block(EE_UINT32 can_id)
{
	int i;
	for(i=0; i<CAN1_BLOCK_RX_NUM; i++)
		if(can_id == CAN1_rx_blocks[i].id)
			return i;
	return -1;
}

/* Called inside the task used for transmission */
void EESCI_eCAN1_send(EE_UINT8 *data, int len, int id)
{
	int i;
	ee_ecan_mID tx_ecan1message; /* TX Transmission message */
	
	EESCI_can_debug_print_string("can send start!\n");
	/* C1CTRL1bits.ABAT = 1; 
	   while(C1TR01CONbits.TXREQ0){}; 
	*/
	tx_ecan1message.buffer			=	0;   /* Buffer number */
	tx_ecan1message.frame_type		=	1;   /* 0->Std Id, 1->Ext Id */
	tx_ecan1message.id 				= 	id;  /* Identifier */
	tx_ecan1message.message_type	=	0;   /* 0->Normal, 1->Remote Transmit */
	tx_ecan1message.data_length		=	len; /*Length of data (0 to 8 EE_UINT8s) */
	for(i=0; i<CAN_DATA_LEN; i++) 
		tx_ecan1message.data[i] = data[i];
	EE_ecan1_SendMessage(&tx_ecan1message);
	while(C1TR01CONbits.TXREQ0) /* we use buffer0 to transmit */
        ;
	EESCI_can_debug_print_string("can send end!\n");
}

/* Called to initializa */
void EESCI_eCAN1_init(void)
{
	/* Callback initialization */
	EE_ecan1_set_ISR_callback(&EESCI_eCAN1_cbk);
	
	/* Buffers initialization */
	int i;
	for(i=0; i<sizeof(scicosCAN1_tx_buffer); i++) {
		scicosCAN1_tx_buffer[i] = 0;
		scicosCAN1_rx_buffer[i] = 0;
	}
	
	/* Can setup and initialization */
	EE_ecan1_Initialize();
	EE_ecan1_WriteRxAcptMask(0x0,0x1FFFFFFF, 0,0x1);
	EE_ecan1_WriteRxAcptFilter(0x0,CAN1_rx_blocks[0].id,0x1,0x1,0x0); /* id=1 to buffer 1 */
	EE_ecan1_WriteRxAcptFilter(0x1,CAN1_rx_blocks[1].id,0x1,0x2,0x0); /* id=2 to buffer 2 */
	EE_ecan1_WriteRxAcptFilter(0x2,CAN1_rx_blocks[2].id,0x1,0x3,0x0); /* id=3 to buffer 3 */
	EE_ecan1_WriteRxAcptFilter(0x4,CAN1_rx_blocks[3].id,0x1,0x4,0x0); /* id=4 to buffer 4 */
	EE_ecan1_WriteRxAcptFilter(0x5,CAN1_rx_blocks[4].id,0x1,0x5,0x0); /* id=5 to buffer 5 */
}

/* ------------------------------------------------------------------------------
    CAN1 interrupt handlers
   ------------------------------------------------------------------------------ */

/* CAN bus 1 Interrupt, ISR2 type */
void EESCI_eCAN1_cbk(void)
{
	EESCI_eCAN1_tx_service();
	EESCI_eCAN1_rx_service();
}

/* Tx callback */
void EESCI_eCAN1_tx_service(void)
{
	/* Transmission interrupt (nothing to be done but clear flag) */
	if(C1INTFbits.TBIF)
    	C1INTFbits.TBIF = 0;
}

volatile int eesci_can_debug_rx_service_flag = 0;

/* CAN bus 1 Interrupt, ISR2 type */
void EESCI_eCAN1_rx_service(void)
{
	ee_ecan_mID *rx_ecan1message_p = 0;
	
	/*Reception interrupt, different code for different filtered id's */
    if(C1INTFbits.RBIF)
    {
    	/* Filter 1(id=ID_PLANT): Sensor to controller message */
    	if(C1RXFUL1bits.RXFUL1==1) {
            /* Tells rxECAN1 the buffer to pass from DMA to RAM */
	    	rx_ecan1message_p = &(CAN1_rx_blocks[0].rx_ecan1message); 
			rx_ecan1message_p->buffer = 1; //rx_ecan1message1.buffer=1;
	    	C1RXFUL1bits.RXFUL1=0;
	    	EE_ecan1_Rx(rx_ecan1message_p);
			C1INTFbits.RBIF = 0;
        }

		/* Filter 2(id=ID_PLANT+1): Controller to Actuator message */
		if(C1RXFUL1bits.RXFUL2==1) {
            /*Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message_p = &(CAN1_rx_blocks[1].rx_ecan1message); 
	    	rx_ecan1message_p->buffer=2;
	    	C1RXFUL1bits.RXFUL2=0;
	    	EE_ecan1_Rx(rx_ecan1message_p);
			C1INTFbits.RBIF = 0;
	    }

		/* Filter 3(id=ID_PLANT+2): Controller updated reference (supervision) */
		if(C1RXFUL1bits.RXFUL3==1) {
            /*Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message_p = &(CAN1_rx_blocks[2].rx_ecan1message); 
	    	rx_ecan1message_p->buffer=3;
	    	C1RXFUL1bits.RXFUL3=0;
	    	EE_ecan1_Rx(rx_ecan1message_p);
			C1INTFbits.RBIF = 0;
			eesci_can_debug_rx_service_flag = 1;
	    }

		/* Filter 4(id=4): Reserved for future improvements */
		if(C1RXFUL1bits.RXFUL4==1) {
            /* Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message_p = &(CAN1_rx_blocks[3].rx_ecan1message); 
	    	rx_ecan1message_p->buffer=4;
	    	C1RXFUL1bits.RXFUL4=0;
	    	EE_ecan1_Rx(rx_ecan1message_p);
			C1INTFbits.RBIF = 0;
	    }
		
		/* Filter 5(id=5): Reserved for future improvements */
		if(C1RXFUL1bits.RXFUL5==1) {
            /* Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message_p = &(CAN1_rx_blocks[4].rx_ecan1message); 
	    	rx_ecan1message_p->buffer=5;
	    	C1RXFUL1bits.RXFUL5=0;
	    	EE_ecan1_Rx(rx_ecan1message_p);
			C1INTFbits.RBIF = 0;
	    }
	}
}



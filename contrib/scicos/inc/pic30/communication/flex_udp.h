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
	@file flex_udp.h
	@brief www.scicos.org, www.scicoslab.org
	@author Daniele Alessandrelli, RetisLab, Pisa
	@author Dario Di Stefano, Evidence Srl, Pisa
	@date 2006-2010
*/

#ifndef ETH_TASK_H_
#define ETH_TASK_H_

#include "TCPIP_Stack/TCPIP.h"

/* max number of i/o block lines */
#define SCICOS_UDP_CHANNELS 15
#define EESCI_UDP_BUFFER_LENGTH 16

/* size of a float variable on a scicos line */
#define UDP_SIZE_OF_ELEMENT (sizeof(float))

/* Length of a buffer */
#define EE_UDP_BUF_SIZE (SCICOS_UDP_CHANNELS*UDP_SIZE_OF_ELEMENT)

/* Macros to read input/output ports */
#define u(i,j) ((double *)block->inptr[i])[j]
#define y(i,j) ((double *)block->outptr[i])[j]

extern volatile unsigned long int UDP_flex_port;		/* FLEX SERVER PORT NUMBER */
extern volatile unsigned long int UDP_pc_port;			/* PC SERVER PORT NUMBER */
extern NODE_INFO UDP_remote;

extern BYTE scicosUDP_rx_buffer[UDP_SIZE_OF_ELEMENT];	/* buffer for UDP reception */
extern BYTE scicosUDP_tx_buffer[UDP_SIZE_OF_ELEMENT];	/* buffer for UDP transmission */

extern volatile int UDP_num_rx_channels;
extern volatile int UDP_num_tx_channels;

typedef char UDP_message[UDP_SIZE_OF_ELEMENT];
typedef struct {
    int g;			/* get index: points to the first packet to be extracted */
	int p;			/* put index: points to the next empty location */
	int counter;	/* counter: to make difference between full queue and empty queue... */
	UDP_message data[EESCI_UDP_BUFFER_LENGTH];
} UDP_buffer;
extern volatile UDP_message tx_msg[EESCI_UDP_BUFFER_LENGTH];
extern volatile UDP_message rx_msg[EESCI_UDP_BUFFER_LENGTH];

extern UDP_buffer UDP_rx_buffer;
extern UDP_buffer UDP_tx_buffer;
void UDP_Buffer_Init(UDP_buffer *buf, int dim);
int UDP_Buffer_Putmsg(UDP_buffer *buf, BYTE* msg);
int UDP_Buffer_Getmsg(UDP_buffer *buf, BYTE* msg);
void UDP_Buffer_Close(UDP_buffer *buf);
int UDP_Buffer_Isempty(UDP_buffer *buf);
int UDP_Buffer_Isfull(UDP_buffer *buf);
int UDP_Buffer_count(UDP_buffer *buf);

/*
TASKs
*/
DeclareTask(UDP_TASK);

#endif /* ETH_TASK_H_ */

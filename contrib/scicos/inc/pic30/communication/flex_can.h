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
	@file flex_can.h
	@brief www.scicos.org, www.scicoslab.org
	@author Dario Di Stefano, Evidence Srl
	@date 2006-2010
*/

#ifndef CAN_SCICOS_H_
#define CAN_SCICOS_H_

/* max number of i/o block lines */
#define SCICOS_CAN_CHANNELS  16
/* Length of a buffer */
#define EE_CAN_BUF_SIZE (SCICOS_CAN_CHANNELS*sizeof(float))
/* Size of the data field */
#define CAN_DATA_LEN 8
/* CAN buffer dimension */
#define CAN_BUF_SIZE 20
/* Debug print functions */
#define CAN_DEBUG_TEST_NUM 100

/* Macros to read input/output ports */
#define u(i,j) ((double *)block->inptr[i])[j]
#define y(i,j) ((double *)block->outptr[i])[j]

#ifndef CAN_DEBUG

#define EESCI_can_debug_print_string(a)
#define EESCI_can_debug_print_val(a,b)
#define EESCI_can_debug_print_vals(a,b,c)
#define EESCI_can_debug_insert_val(rx,cnt)
#define EESCI_can_debug_print_results()
#define DECL_EXT_TEST_VARS()
#define DEF_TEST_VARS()

#else /* CAN_DEBUG */

#include "mcu/microchip_dspic/inc/ee_uart.h"
#include "string.h"
#include "stdio.h"
#define DECL_EXT_TEST_VARS() extern volatile unsigned int eesci_can_debug_rx_test_vet[CAN_DEBUG_TEST_NUM]; \
                             extern volatile int eesci_can_debug_initialized
#define DEF_TEST_VARS()      volatile unsigned int eesci_can_debug_rx_test_vet[CAN_DEBUG_TEST_NUM]; \
                             volatile int eesci_can_debug_initialized = 0

/* Declaration of extern variables used in TEST mode */
DECL_EXT_TEST_VARS();

__INLINE__ void EESCI_can_debug_init()
{
	EE_uart_init(EE_UART_PORT_1, 115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1, EE_UART_CTRL_SIMPLE);
	eesci_can_debug_initialized = 1;
}

__INLINE__ void EESCI_can_debug_print_string(char *str)
{
	if(eesci_can_debug_initialized==0)
		EESCI_can_debug_init();
	int len, i;
	len = strlen(str);
	for(i=0; i<len; i++)
		EE_uart_write_byte(EE_UART_PORT_1, str[i]);
}
__INLINE__ void EESCI_can_debug_print_val(char *str, int val)
{
	if(eesci_can_debug_initialized==0)
		EESCI_can_debug_init();
	char str_val[64];
	sprintf(str_val,str,val);
	EESCI_can_debug_print_string(str_val);
}

__INLINE__ void EESCI_can_debug_print_vals(char *str, int val1, int val2)
{
	if(eesci_can_debug_initialized==0)
		EESCI_can_debug_init();
	char str_val[64];
	sprintf(str_val,str,val1,val2);
	EESCI_can_debug_print_string(str_val);
}

__INLINE__ void EESCI_can_debug_print_results(void)
{
	IEC2bits.C1IE = 0;
	int i;
	char str_val[64];
	for(i=0; i<CAN_DEBUG_TEST_NUM; i++ ) {
		sprintf(str_val, "rx_test_vet[%d]:%x\r\n", i, eesci_can_debug_rx_test_vet[i]);
		EESCI_can_debug_print_string(str_val);
	}
	while(1)
		;
}

__INLINE__ void EESCI_can_debug_insert_val(EE_UINT8* rx_data, int val_cnt)
{
	eesci_can_debug_rx_test_vet[val_cnt] =  ((unsigned int)rx_data[6])<<8 | ((unsigned int)rx_data[7]); 
}
#endif /* CAN_DEBUG */



/* -------------------------------------------- */
/* Global variables used in the CAN scicos code */
/* -------------------------------------------- */

/*
#define CAN1_BLOCK_TX_NUM 5
typedef struct {
    EE_UINT8 index;
    EE_UINT32 id;
    EE_UINT8 len;
} CAN1_tx_block;
extern CAN1_tx_block CAN1_tx_blocks[CAN1_BLOCK_TX_NUM];
*/

#define CAN1_BLOCK_RX_NUM 5
typedef struct {
    EE_UINT32 id;
    ee_ecan_mID rx_ecan1message;
} CAN1_rx_block;
extern CAN1_rx_block CAN1_rx_blocks[CAN1_BLOCK_RX_NUM];

/* buffer */
extern EE_UINT8 scicosCAN1_rx_buffer[CAN_DATA_LEN];
extern EE_UINT8 scicosCAN1_tx_buffer[CAN_DATA_LEN];
extern volatile EE_UINT8 ee_ecan1_initialized;

/* CAN scicos blocks library */
void EESCI_eCAN1_cbk(void);
void EESCI_eCAN1_init(void);
void EESCI_eCAN1_send(EE_UINT8 *data, int len, int id);
void EESCI_eCAN1_tx_service(void);
void EESCI_eCAN1_rx_service(void);
int EESCI_eCAN1_get_rx_block(EE_UINT32 can_id);

#endif /* CAN_SCICOS_H_ */

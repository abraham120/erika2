/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
* @file 	eth_api.h
* @brief 	MAC layer configuration header and external API.
*           MAC layer functions are not in this files as the implementation depends on
*           the configuration. For example, if you select PIC32 the MAC layer is in the file named "microhip/ETHPIC32IntMac.c".
* @author 	Dario Di Stefano
* @date 	2011
*/ 
 
#ifndef __EE_ETH_H__
#define __EE_ETH_H__

/* RT-OS */
#ifdef __ERIKA__		/* Erika OS */
  #include <ee.h>
#else			/* No OS */
  #error "ETH_H ERROR: OS not specified"
#endif	/* End OS Selection */
#include <eth_compiler.h>

/* Architecture */
#if defined __PIC32__
  #include <eth_hal_ee_pic32.h>
#else		/* NO Architecture */
  #error "ETH_H: Architecture not supported"
#endif

/* MAC/PHY headers */
#include "mac_extphy_debug.h"
#include "phy.h"

/* ETH INT registers */
#define EE_ETH_IRQ_MANAGED           0
#define EE_ETH_IRQ_PENDING           1

/* MAC address structure */
typedef struct __attribute__((__packed__))
{
    BYTE v[6];
} MAC_ADDR;

/* ETH structure (used in ISR mode) */
typedef struct {
  	int irqf;	
	EE_TID task;		// task called inside the interrupt handler
} EE_eth_st;

extern volatile EE_eth_st ee_eth_st;

/**
 * To store MAC address.
 */
extern MAC_ADDR ee_myMACaddress; 

/* MAC layer functions */
void MACInit(MAC_ADDR myMACaddress);
//void MACProcess(void);
//BOOL MACIsLinked(void);
BOOL MACGetHeader(MAC_ADDR *remote, BYTE* type);
//void MACSetReadPtrInRx(WORD offset);
PTR_BASE MACSetWritePtr(PTR_BASE address);
//PTR_BASE MACSetReadPtr(PTR_BASE address);
//BYTE MACGet(void);
int MACLink(void);
BOOL MACGetInfo(BYTE* PacketCount, WORD* length);
WORD MACGetArray(BYTE *val, WORD len);
void MACDiscardRx(void);
//WORD MACGetFreeRxSize(void);
//void MACMemCopyAsync(PTR_BASE destAddr, PTR_BASE sourceAddr, WORD len);
//BOOL MACIsMemCopyDone(void);
void MACPutHeader(MAC_ADDR *remote, BYTE type, WORD dataLen);
BOOL MACIsTxReady(void);
//void MACPut(BYTE val);
void MACSetCurrSize(WORD dataLen);
PTR_BASE MACGetTxBaseAddr(void);
void MACPutArray(BYTE *val, WORD len);
void MACFlush(void);

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to check link status.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_eth_link_check(void)
{
	return MACLink();
}

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to initialize the device and other modules.
*/
void EE_eth_init(MAC_ADDR myMACaddress);

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to initialize the transfer of a packet.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_transfer_init(void)
{
	while(!MACIsTxReady())
		;
	MACSetWritePtr(MACGetTxBaseAddr());
}

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to transmit a packet
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_write(BYTE* data, WORD len)
{
    MACPutArray(data, len);
}

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to signal the end of a packet transfer
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_signal(WORD dataLen)
{
	MACSetCurrSize(dataLen);
	MACFlush();
}

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to read the length of the receive packet
*/
__INLINE__ int __ALWAYS_INLINE__ EE_eth_read_info(BYTE* PacketCount, WORD* length)
{
	return MACGetInfo(PacketCount, length);
}

/** 
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to receive a packet.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_eth_read(BYTE* data, WORD len)
{
	return MACGetArray(data, len);
}

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack
			Function used to acknowledge a packet reception
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_ack(void)
{
	MACDiscardRx();
}

/**
	@brief 	MAC/PHY driver - MAC layer for TCPIP stack.
			Function used to drop a packet (not yet supported).
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_drop_packet(void)
{
}

/**
	This function sets the task should be called inside the interrupt handler.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_set_rx_task(EE_TID task)
{
	ee_eth_st.task = task;
}

/**
	This function write the internal interrupt request flag
*/
__INLINE__ void __ALWAYS_INLINE__ EE_eth_irq_int_write(int val) {
	ee_eth_st.irqf = val;
}

/**
	This function write the internal interrupt request flag
*/
__INLINE__ int __ALWAYS_INLINE__ EE_eth_irq_int_read() {
	return ee_eth_st.irqf;
}

/**
	This function enables ETHERNET reception interrupts. 
*/
int EE_eth_clear_irq_flag(void);

/**
	This function enables ETHERNET reception interrupts. 
*/
void EE_eth_init_IRQ(void);

/**
	This function enables ETHERNET reception interrupts. 
*/
void EE_eth_enable_IRQ(void);

/**
	This function disables ETHERNET reception interrupts. 
*/
void EE_eth_disable_IRQ(void);

/**
	This function provides, before resetting it, the status of the pending 
	interrupt flag
*/
int EE_eth_pending_interrupt(void);


#endif

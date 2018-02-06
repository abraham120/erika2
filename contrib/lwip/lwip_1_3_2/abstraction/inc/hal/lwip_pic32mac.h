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
* @file lwip_pic32mac.h
* @brief PIC32 mac abstraction layer for LWIP.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2011
*/

#ifndef __LWIP_PIC32_MAC_H__
#define __LWIP_PIC32_MAC_H__

#include "ee_lwip.h"
#include "eth_api.h"
#include <hal/lwip_compiler.h>

#ifndef EE_LWIP_PIC32MAC_INIT_DELAY
#define EE_LWIP_PIC32MAC_INIT_DELAY 3000
#endif

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif {
  /* Add whatever per-interface state that is needed here. */
  struct eth_addr *ethaddr;
  u8_t pkt_cnt;
  u16_t length;
};

/* Flag for pending irq status */
extern volatile int EE_lwip_irq_pending;

/**
 * @brief MAC initialization function in LWIP.
 *
 * This function allocates memory for ethernetif and configures the mac controller. 
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void EE_ethernetif_hal_init(struct netif *netif);

/**
 * This function sets the reception task activated by the mac driver handler. 
 * @param task identification number of the task should be called.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_set_Rx_task(EE_TID task)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_set_Rx_task\n"));
	EE_eth_set_rx_task(task);
}

/**
 * This function is called at the and of the reception task. 
 * In this version of the mac driver this function enables interrupts (disabled inside the handler). 
 */
__INLINE__ void __ALWAYS_INLINE__ EE_lwip_hal_rx_service(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_lwip_hal_rx_service\n"));
    #ifndef LWIP_RX_POLLING 
	EE_eth_enable_IRQ();
    #else
    EE_lwip_irq_pending = 1;
    #endif
}

/**
 * This function checks if there are pending packets. 
 * @return 1 if there are pending packets, 0 otherwise.  
 */
__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_pending_interrupt(void)
{
    LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_pending_interrupt\n"));
    #ifdef LWIP_RX_POLLING 
    int res = EE_lwip_irq_pending;
    EE_lwip_irq_pending = 0;
    return res;
    #else
    EE_lwip_irq_pending = EE_eth_irq_int_read();  /* check if an rx_isr is pending */
    EE_eth_irq_int_write(EE_ETH_IRQ_MANAGED);     /* clear irq pending flag  */
    if( EE_eth_pending_interrupt() )              /* check if an interrupt/packet is pending */
        EE_lwip_irq_pending = EE_ETH_IRQ_PENDING; /* there are pending packets (no pending interrupts because are disabled) */
    return EE_lwip_irq_pending;
    #endif
    
}

/**
 * This function calls the low level function used to configures 
 * the device tx addresses for the next transfer.  
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_initiate_transfer(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_initiate_transfer\n"));
	EE_eth_transfer_init();
}

/**
 * This function calls the low level function that puts the array to be transmitted into the device.  
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_write(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_write: %x, %d\n", data, len));
	EE_eth_write(data, len);
}

/**
 * This function calls the low level function that commands the transmission on the ethernet cable.  
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_signal(u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_signal: %d\n", len));
	EE_eth_signal(len);
}

/**
 * This function calls the low level function used to get info about the received packets to be read.  
 * @return 0 if there aren't pending packets, the length otherwise.  
 */
__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_get_info(struct netif *netif)
{
	struct ethernetif *ethernet_if = (struct ethernetif *)netif->state;
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_get_info: %x\n", ethernet_if));
	
	if(EE_eth_read_info(&ethernet_if->pkt_cnt, &ethernet_if->length) < 0)
		return 0;
	else
		return ethernet_if->length;
}

/**
 * This function calls the low level function used to get an array of bytes.  
 * @return the number of read bytes.  
 */
__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_read(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_read: %x, %d\n", data, len));
	return EE_eth_read(data, len);
}

/**
 * This function calls the low level function used to send an ack to the mac controller.   
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_ack(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_ack\n"));
	EE_eth_ack();
}

/**
 * This function calls the low level function used to drop a packet.   
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_drop_packet(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_drop_packet\n"));
	EE_eth_drop_packet();
}

#endif /* __LWIP_PIC32_MAC_H__ */

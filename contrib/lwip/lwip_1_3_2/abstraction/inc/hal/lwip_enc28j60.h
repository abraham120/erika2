/** 
* @file lwip_enc28j60.h
* @brief ENC28j60 abstraction layer for LWIP.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2010-07-12
*/

#ifndef __lwip_ethernet_enc28j60_h__
#define __lwip_ethernet_enc28j60_h__

#include "ee_lwip.h"
#include "enc28j60.h"
#include <hal/lwip_compiler.h>

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

/**
 * @brief ENC28J60 initialization function in LWIP.
 *
 * This function allocates memory for ethernetif and configures the ENC28J60 controller. 
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void EE_ethernetif_hal_init(struct netif *netif);

/**
 * This function sets the reception task activated by the ENC28J60 driver handler. 
 * @param task identification number of the task should be called.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_set_Rx_task(EE_TID task)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_set_Rx_task\n"));
	EE_enc28j60_set_rx_task(task);
}

/**
 * This function is called at the and of the reception task. 
 * In this version of the ENC28J60 driver this function enables interrupts (disabled inside the handler). 
 */
__INLINE__ void __ALWAYS_INLINE__ EE_lwip_hal_rx_service(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_lwip_hal_rx_service\n"));
	EE_enc28j60_enable_IRQ();
}

/**
 * This function checks if there are pending packets (ENC28J60 INT pin low). 
 * @return 1 if there are pending packets, 0 otherwise.  
 */
__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_pending_interrupt(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_pending_interrupt\n"));
	return EE_enc28j60_pending_interrupt();
}

/**
 * This function calls the low level function used to configures 
 * the device tx addresses for the next transfer.  
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_initiate_transfer(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_initiate_transfer\n"));
	EE_enc28j60_transfer_init();
}

/**
 * This function calls the low level function that puts the array to be transmitted into the device.  
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_write(u8_t* data, u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_write: %x, %d\n", data, len));
	EE_enc28j60_write(data, len);
}

/**
 * This function calls the low level function that commands the transmission on the ethernet cable.  
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_signal(u16_t len)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_signal: %d\n", len));
	EE_enc28j60_signal(len);
}

/**
 * This function calls the low level function used to get info about the received packets to be read.  
 * @return 0 if there aren't pending packets, the length otherwise.  
 */
__INLINE__ int __ALWAYS_INLINE__ EE_ethernetif_hal_get_info(struct netif *netif)
{
	struct ethernetif *ethernet_if = (struct ethernetif *)netif->state;
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_get_info: %x\n", ethernet_if));
	
	if(EE_enc28j60_read_info(&ethernet_if->pkt_cnt, &ethernet_if->length) < 0)
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
	return EE_enc28j60_read(data, len);
}

/**
 * This function calls the low level function used to send an ack to the ENC28J60 controller.   
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_ack(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_ack\n"));
	EE_enc28j60_ack();
}

/**
 * This function calls the low level function used to drop a packet.   
 */
__INLINE__ void __ALWAYS_INLINE__ EE_ethernetif_hal_drop_packet(void)
{
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_drop_packet\n"));
	EE_enc28j60_drop_packet();
}

#endif /* Header Protection */

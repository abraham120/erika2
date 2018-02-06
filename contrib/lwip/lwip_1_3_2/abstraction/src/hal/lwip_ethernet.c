/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 * Copyright (C) 2010  Evidence Srl
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 * Author: 2010,  Dario Di Stefano (generic driver interface).
 *
 */
 
/** 
* @file lwip_ethernet.c
* @brief LWIP ethernet interface library.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2010-07-12
*/
 
/**
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "ee_lwip.h"

/** 
 * Define those to better describe your network interface. 
 */
#define IFNAME0 'e'
#define IFNAME1 'n'

/**
 * Low level functions
 */
static struct pbuf *low_level_input(struct netif *netif);
static err_t low_level_init(struct netif *netif);
static err_t low_level_output(struct netif *netif, struct pbuf *p);

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static err_t low_level_init(struct netif *netif)
{
	EE_lwip_write_timestamp(LWIP_START_LOWLEV_INIT);
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("low_level_init ( %#x)\n",netif));

	/* Do whatever else is needed to initialize interface. */  
	EE_ethernetif_hal_init(netif);
	
	EE_lwip_write_timestamp(LWIP_END_LOWLEV_INIT);
	return ERR_OK;
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t EE_ethernet_init(struct netif *netif)
{
	LWIP_ASSERT("netif != NULL", (netif != NULL));
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("ethernetif_init ( %#x)\n",netif));
	
	EE_lwip_write_timestamp(LWIP_START_ETH_INIT);
	
	/**
	 * Initialize netif structure.
	 */
	 
	/* Initialize interface hostname */ 
	#if LWIP_NETIF_HOSTNAME
	netif->hostname = "lwip";
	#endif /* LWIP_NETIF_HOSTNAME */

	/*
	* Initialize the snmp variables and counters inside the struct netif.
	* The last argument should be replaced with your link speed, in units
	* of bits per second.
	*/
	// NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

	/* set MAC hardware address length */
	netif->hwaddr_len = ETHARP_HWADDR_LEN;

	/* set MAC hardware address */
	netif->hwaddr[0] = ETHERNETIF_MAC_BYTE1;
	netif->hwaddr[1] = ETHERNETIF_MAC_BYTE2;
	netif->hwaddr[2] = ETHERNETIF_MAC_BYTE3;
	netif->hwaddr[3] = ETHERNETIF_MAC_BYTE4;
	netif->hwaddr[4] = ETHERNETIF_MAC_BYTE5;
	netif->hwaddr[5] = ETHERNETIF_MAC_BYTE6;
	
	/* maximum transfer unit */
	netif->mtu = 1500;

	/* device capabilities */
	/* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	/* We directly use etharp_output() here to save a function call.
	* You can instead declare your own function an call etharp_output()
	* from it if you have to do some checks before sending (e.g. if link
	* is available...) */
	netif->output = etharp_output;
	netif->linkoutput = low_level_output;
	
	/* initialize the hardware */
	low_level_init(netif);

	EE_lwip_write_timestamp(LWIP_END_ETH_INIT);
	return ERR_OK;
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
	struct pbuf *q;
	EE_lwip_write_timestamp(LWIP_START_LOWLEV_OUT);
	
	u16_t length = p->tot_len;
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("low_level_output ( %#x)\n",p));

	EE_lwip_write_timestamp(LWIP_START_LOWLEV_INIT_TRANSFER);
	EE_ethernetif_hal_initiate_transfer();
	EE_lwip_write_timestamp(LWIP_END_LOWLEV_INIT_TRANSFER);
	
	#if ETH_PAD_SIZE
	pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
	#endif

	EE_lwip_write_timestamp(LWIP_START_LOWLEV_WRITE);
	for(q = p; q != NULL; q = q->next) {
		/* Send the data from the pbuf to the interface, one pbuf at a
		   time. The size of the data in each pbuf is kept in the ->len
		   variable. */
		EE_ethernetif_hal_write(q->payload, q->len);
	}
	EE_lwip_write_timestamp(LWIP_END_LOWLEV_WRITE);
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("low_level_output: signal length: %d\n", length));
	
	EE_lwip_write_timestamp(LWIP_START_LOWLEV_SIGNAL);
	EE_ethernetif_hal_signal(length);
	EE_lwip_write_timestamp(LWIP_END_LOWLEV_SIGNAL);
	
	#if ETH_PAD_SIZE
	pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
	#endif

	LINK_STATS_INC(link.xmit);
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("low_level_output: return OK\n"));
	EE_lwip_write_timestamp(LWIP_END_LOWLEV_OUT);
	
	return ERR_OK;
}

/**
 * This function should be called when a packet is ready to be transmittedd
 * to the interface. It uses the function low_level_output() that
 * should handle the actual transmission of bytes to the network
 * interface. 
 * @param netif the lwip network interface structure for this ethernetif.
 * @param p buffer to be transmitted.
 * @param ipaddr ip address.
 */
err_t EE_ethernet_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr)
{
#if	0
	err_t ret;
#endif
	EE_lwip_write_timestamp(LWIP_START_ETH_OUT);
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("ethernetif_output()\n"));

#if	0
	ret =
#endif
	etharp_output(netif, p, ipaddr);

	if (p != NULL) 
	{
		low_level_output(netif, p);
	}

	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("ethernetif_output() return OK\n"));
	EE_lwip_write_timestamp(LWIP_END_ETH_OUT);
	
	return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *low_level_input(struct netif *netif)
{
	struct pbuf *p, *q;
	u16_t len;

	EE_lwip_write_timestamp(LWIP_START_LOWLEV_INPUT);
	
	len = EE_ethernetif_hal_get_info(netif);
	if( len == 0)
	{
		EE_lwip_write_timestamp(LWIP_END_LOWLEV_INPUT);
		return (struct pbuf *)0;
	}

	#if ETH_PAD_SIZE
	len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
	#endif

	/* We allocate a pbuf chain of pbufs from the pool. */
	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  
	if (p != NULL) 
	{
		#if ETH_PAD_SIZE
		pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
		#endif

		/* We iterate over the pbuf chain until we have read the entire
		* packet into the pbuf. */
		for(q = p; q != NULL; q = q->next) {
		/* Read enough bytes to fill this pbuf in the chain. The
		* available data in the pbuf is given by the q->len
		* variable.
		* This does not necessarily have to be a memcpy, you can also preallocate
		* pbufs for a DMA-enabled MAC and after receiving truncate it to the
		* actually received size. In this case, ensure the tot_len member of the
		* pbuf is the sum of the chained pbuf len members.
		*/
			EE_ethernetif_hal_read(q->payload, q->len);
			LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("low_level_input: payload=0x%x, len=%d\n", q->payload, q->len));
		}
		EE_ethernetif_hal_ack();

		#if ETH_PAD_SIZE
		pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
		#endif

		LINK_STATS_INC(link.recv);
	} 
	else {
		EE_ethernetif_hal_drop_packet();
		LINK_STATS_INC(link.memerr);
		LINK_STATS_INC(link.drop);
	}

	EE_lwip_write_timestamp(LWIP_END_LOWLEV_INPUT);
	return p;  
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
err_t EE_ethernet_input(struct netif *netif)
{
	struct eth_hdr *ethhdr;
	struct pbuf *p;

	EE_lwip_write_timestamp(LWIP_START_ETH_INPUT);
	/* move received packet into a new pbuf */
	p = low_level_input(netif);
	/* no packet could be read, silently ignore this */
	if (p == NULL) 
	{
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: p == NULL!\n"));
		EE_lwip_write_timestamp(LWIP_END_ETH_INPUT);
		return ERR_OK;
	}
	/* points to packet payload, which starts with an Ethernet header */
	ethhdr = p->payload;

	switch (htons(ethhdr->type)) {
	/* IP or ARP packet? */
	case ETHTYPE_IP:
	case ETHTYPE_ARP:
#if PPPOE_SUPPORT
	/* PPPoE packet? */
	case ETHTYPE_PPPOEDISC:
	case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
		/* full packet send to tcpip_thread to process */
		if (netif->input(p, netif)!=ERR_OK)
		{ 
			LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error!\n"));
			pbuf_free(p);
			p = NULL;
		}
		break;

	default:
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: type unknown!\n"));
		pbuf_free(p);
		p = NULL;
		break;
	}
	
	EE_lwip_write_timestamp(LWIP_END_ETH_INPUT);
	return ERR_OK;
}


/** 
* @file lwip_pic32mac.c
* @brief PIC32 mac abstraction layer for LWIP.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2010-07-12
*/

#include "ee_lwip.h"

volatile int EE_lwip_irq_pending = 1;

/**
 * @brief PIC32 mac initialization function in LWIP.
 *
 * This function allocates memory for ethernetif and configures the mac controller. 
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void EE_ethernetif_hal_init(struct netif *netif)
{
	struct ethernetif *ethernet_if;
	MAC_ADDR myMACaddress;
	
	LWIP_DEBUGF(NETIF_DEBUG | LWIP_DBG_TRACE, ("EE_ethernetif_hal_init\n"));
	
	/* Allocate memory for ethernetif */
	ethernet_if = mem_malloc(sizeof(struct ethernetif));
	if (ethernet_if == NULL)
		LWIP_DEBUGF(NETIF_DEBUG, ("EE_ethernetif_hal_init: out of memory\n"));
	
	netif->state = ethernet_if;
	ethernet_if->ethaddr = 	(struct eth_addr *)&(netif->hwaddr[0]);
	ethernet_if->pkt_cnt = 	0; 
	ethernet_if->length = 	0;
	
	myMACaddress.v[0] = netif->hwaddr[0];
	myMACaddress.v[1] = netif->hwaddr[1];
	myMACaddress.v[2] = netif->hwaddr[2];
	myMACaddress.v[3] = netif->hwaddr[3];
	myMACaddress.v[4] = netif->hwaddr[4];
	myMACaddress.v[5] = netif->hwaddr[5];

	/* Disable IRQ */
	EE_eth_disable_IRQ();
	/* MAC and PHY layers initialization */
	EE_eth_init(myMACaddress);
	#ifndef LWIP_RX_POLLING
	/* Enable IRQ */ 
	EE_eth_init_IRQ();
	EE_eth_enable_IRQ();
	#endif
	/* Link status check */
	while( EE_eth_link_check()==0 )
		;
	/* Test shows that this wait is needed to send  
	   the initial gratitous ARP packet successfully... */
	//EE_lwip_sleep_ms(EE_LWIP_PIC32MAC_INIT_DELAY);
}


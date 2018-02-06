/** 
* @file lwip_enc28j60.c
* @brief ENC28j60 abstraction layer for LWIP.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2010-07-12
*/

#include "ee_lwip.h"


/**
 * @brief ENC28J60 initialization function in LWIP.
 *
 * This function allocates memory for ethernetif and configures the ENC28J60 controller. 
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void EE_ethernetif_hal_init(struct netif *netif)
{
	struct ethernetif *ethernet_if;
	mac_addr myMACaddress;
	
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

	EE_enc28j60_init(myMACaddress);
}

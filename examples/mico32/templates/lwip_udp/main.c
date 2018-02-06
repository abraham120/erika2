/*
  Name: main.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: LWIP template.
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
/* LWIP */
#include "ee_lwip.h"

/* ----------------------------------------------------------- */
/* Macros */
/* ----------------------------------------------------------- */
#define MY_PORT						...
#define MY_IPADDR_BYTE1 			...
#define MY_IPADDR_BYTE2 			...
#define MY_IPADDR_BYTE3 			...
#define MY_IPADDR_BYTE4 			...
#define MY_NETMASK_BYTE1 			...
#define MY_NETMASK_BYTE2 			...
#define MY_NETMASK_BYTE3 			...
#define MY_NETMASK_BYTE4 			...
#define MY_GATEWAY_ADDR_BYTE1 		...
#define MY_GATEWAY_ADDR_BYTE2 		...
#define MY_GATEWAY_ADDR_BYTE3 		...
#define MY_GATEWAY_ADDR_BYTE4 		...
#define MY_ETHERNETIF_MAC_BYTE1		...
#define MY_ETHERNETIF_MAC_BYTE2		...
#define MY_ETHERNETIF_MAC_BYTE3		...
#define MY_ETHERNETIF_MAC_BYTE4		...
#define MY_ETHERNETIF_MAC_BYTE5		...
#define MY_ETHERNETIF_MAC_BYTE6		...

/* ----------------------------------------------------------- */
/* Demo Variables */
/* ----------------------------------------------------------- */
/* UDP socket used in this demo */
struct udp_pcb* my_udp_socket;

/* ----------------------------------------------------------- */
/* Callbacks and tasks */
/* ----------------------------------------------------------- */
/* UDP rx handler */
void udp_rx_handler(void *arg, struct udp_pcb *upcb,
                    struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    /* connect to the remote host */
    udp_connect(upcb, addr, port);               
    /* Do something with the received packet */
    ... /* for example: ActivateTask(myTask) */
    /* don't leak the pbuf! */
    pbuf_free(p);	
}

/* Timer callback */
void system_timer_callback(void)
{
    /* count the interrupts, waking up expired alarms */
    CounterTick(myCounter);
}

/* myTask */
TASK(myTask)
{
	/* Transmission */
	GetResource(LwipMutex);        
    if (my_udp_socket->remote_port != (uint16_t)0)  /* if the udp socket is connected... */
    {
        struct pbuf* p = pbuf_alloc(PBUF_TRANSPORT, ..., PBUF_REF);
        p->payload = ...
        if (p != (struct pbuf *)0) 
        {
            /* Send the extracted packet */
            udp_send(my_udp_socket, p);
            pbuf_free(p); 
        }
    }
	ReleaseResource(LwipMutex);
}

/* MAIN (Background task) */
int main(void)
{
    /* Enable IRQ         */
    EE_mico32_enableIRQ();
    
    /* LWIP configuration  */
    struct ip_addr my_ipaddr, netmask, gw;
    struct eth_addr my_ethaddr;
	IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
	IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3, MY_NETMASK_BYTE4);
	IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2, MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
	ETH_ADDR(&my_ethaddr, MY_ETHERNETIF_MAC_BYTE1, MY_ETHERNETIF_MAC_BYTE2, MY_ETHERNETIF_MAC_BYTE3, 
				MY_ETHERNETIF_MAC_BYTE4, MY_ETHERNETIF_MAC_BYTE5, MY_ETHERNETIF_MAC_BYTE6);
    EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);
    
    /* Socket initialization   */
    my_udp_socket = udp_new();  						/* Create the udp socket */
    udp_bind(my_udp_socket, &my_ipaddr, MY_PORT); 		/* BInd the udp socket */
    udp_recv(my_udp_socket, &udp_rx_handler, 0);        /* Set the rx callback for udp packets */ 
         
    /* Background activity */
    while(1)
        ;
        
    return 0;
}



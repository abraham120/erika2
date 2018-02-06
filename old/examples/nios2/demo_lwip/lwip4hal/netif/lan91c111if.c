/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
*                                                                             *
* altera_avalon_lan91c111.c - LWIP ethernet interface for the the Lan91C111   *
* on the Nios boards.                                                         *
*                                                                             *
* Author PRR                                                                  *
*                                                                             *
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "system.h"
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "altera_avalon_lan91c111.h"
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "netif/etharp.h"
#include "arch/perf.h"

/* Unique descricption of the network interface. */
#define IFNAME0 'n'
#define IFNAME1 '9'

/*-----------------------------------------------------------------------------------* 
 *
 * low_level_output():
 *
 * Should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 *-----------------------------------------------------------------------------------*/

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  struct pbuf *q, *pq;
  alt_u32 length = p->tot_len;
  alt_avalon_lan91c111_if *dev = netif->state;

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("low_level_output ( %#x)\n",p));

  if(p->next == NULL)       /* pbuf is already contiguous */
  {
    pq = p;
  }
  else                      /* copy pbuf to contiguous mem */
  {
    char* ptr;
    if (length <= PBUF_POOL_BUFSIZE) {
      pq = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);
	 } else {
      pq = pbuf_alloc(PBUF_RAW, length, PBUF_RAM);
	 }
    if (!pq) {
      return ERR_MEM;
    }
    /* Copy each buffer of data to the contiguous memory */
    ptr = pq->payload;
    for(q = p; q != NULL; q = q->next) {
        memcpy(ptr, q->payload, q->len);
        ptr += q->len;
    }
  }

//  sys_sem_wait(dev->semaphore);
//  alt_avalon_lan91c111_output(dev, pq->payload, length);
  dev->ethernet_dev_list.dev.write_routine(dev, pq->payload, length);
//  sys_sem_signal(dev->semaphore);

  if (p != pq) {
    pbuf_free(pq);
  }
#if LINK_STATS
  lwip_stats.link.xmit++;
#endif /* LINK_STATS */      
  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("low_level_output () return OK\n"));

  return ERR_OK;
}


/*-----------------------------------------------------------------------------------* 
 *
 * lan91c111if_output():
 *
 * This function is called by the TCP/IP stack when an IP packet
 * should be sent. It calls the function called low_level_output() to
 * do the actuall transmission of the packet.
 *
 * 
 *-----------------------------------------------------------------------------------*/
err_t
lan91c111if_output(struct netif *netif, struct pbuf *p,
      struct ip_addr *ipaddr)
{
  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_output()\n"));

  p = etharp_output(netif, ipaddr, p);

  if (p != NULL) 
  {
    low_level_output(netif, p);
  }

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_output() return OK\n"));

  return ERR_OK;
}


/*-----------------------------------------------------------------------------------* 
 *
 * if_getbuf():
 *
 * Allocate a pbuf with a contiguous payload.
 *
 *-----------------------------------------------------------------------------------*/
static void* if_getbuf(alt_u32 length)
{
  struct pbuf *p;

  if (length <= PBUF_POOL_BUFSIZE) {
    p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);
  } else {
    p = pbuf_alloc(PBUF_RAW, length, PBUF_RAM);
  }

  if (!p)  return NULL;

  return p->payload;
}

/*-----------------------------------------------------------------------------------* 
 *
 * low_level_input():
 *
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 *
 *-----------------------------------------------------------------------------------*/
static struct pbuf*
low_level_input(struct netif *netif)
{
  struct pbuf *p = NULL;
  void *buf;
  alt_avalon_lan91c111_if *dev = netif->state;

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("low_level_input()\n"));

//  sys_sem_wait(dev->semaphore);
  buf = dev->ethernet_dev_list.dev.read_routine(dev, if_getbuf);
//  sys_sem_signal(dev->semaphore);

  if(buf) {      /* Reconstruct original pbuf ptr */
    (char*)p = (char*)buf - sizeof(struct pbuf);
#if LINK_STATS
    lwip_stats.link.recv++;
#endif /* LINK_STATS */      
  } 
  else 
  {
#if LINK_STATS
    lwip_stats.link.memerr++;
    lwip_stats.link.drop++;
#endif /* LINK_STATS */      
  }

  return p;  
}

/*-----------------------------------------------------------------------------------* 
 *
 * lan91c111if_input():
 *
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface.
 *
 * 
 *-----------------------------------------------------------------------------------*/
err_t lan91c111if_input(struct netif *netif)
{
  err_t           ret_code=0;
  struct eth_hdr  *ethhdr;
  struct pbuf     *p, *q;

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_input()\n"));
  p = low_level_input(netif);

  if (p != NULL) 
  {
    ethhdr = p->payload;
    q = NULL;

    switch (htons(ethhdr->type)) 
    {
    case ETHTYPE_IP:
      /* Update ARP Table obtain first queued packet */
      q = etharp_ip_input(netif, p);
      pbuf_header(p, -14);
      netif->input(p, netif);
      break;
    case ETHTYPE_ARP:
      /* Pass p to ARP, get ARP Reply or ARP queued packet */
      q = etharp_arp_input(netif, (struct eth_addr *)&netif->hwaddr, p);
      break;
    default:
      pbuf_free(p);
      break;
    }

    if (q != NULL) 
    {
      low_level_output(netif, q);
      pbuf_free(q);
      q = NULL;
    }
  }
  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("%d\n", ret_code));

  return ret_code;
}


/*-----------------------------------------------------------------------------------*
 *
 * lan91c111if_service():
 *
 * Should be called by the program to service the network interface.
 * It calls the function low_level_rx() to do the actual input.
 * 
 *-----------------------------------------------------------------------------------*/
err_t lan91c111if_service(struct netif *netif)
{
  err_t ret_code = 0;
  alt_avalon_lan91c111_if* dev = (alt_avalon_lan91c111_if*)netif->state;

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_service()\n"));

  /* Call the device input routine, passing the LWIP input handler */
//  /*ret_code =*/ dev->ethernet_dev_list.dev.rx_routine(dev);
  /*ret_code =*/ dev->ethernet_dev_list.dev.rx_routine(dev, lan91c111if_input);

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_service() exit = %d\n",ret_code));

  return ret_code;
}


/*-----------------------------------------------------------------------------------* 
 *
 * low_level_init():
 *
 * Calls the devices's low level initialization and translates
 * the returned error to the equivalant LWIP error code.
 * Cross-links the LWIP netif to the device structure.
 *
 *-----------------------------------------------------------------------------------*/
static err_t
low_level_init(struct netif *netif)
{
  int ret_code;
  alt_avalon_lan91c111_if* dev = (alt_avalon_lan91c111_if*)netif->state;

  dev->ethernet_dev_list.dev.network = (void*)netif;
  dev->hwaddr = netif->hwaddr;

  /*
  * Read the MAC address out of flash
  */
  ret_code = read_mac_address(netif);
  if (ret_code != 0) 
  {
    /* set default MAC hardware address */
    netif->hwaddr_len = 6;
    netif->hwaddr[0] = 0x00;
    netif->hwaddr[1] = 0x60;
    netif->hwaddr[2] = 0x80;
    netif->hwaddr[3] = 0xa1;
    netif->hwaddr[4] = 0xb2;
    netif->hwaddr[5] = 0xc3;
//    goto exit;
  }

  ret_code = dev->ethernet_dev_list.dev.init_routine(dev);
  switch (ret_code) 
  {
    case 0:
      return (err_t)ERR_OK;
    case -EIO:
      return (err_t)ERR_IF;
    case -ENOMEM:
      return (err_t)ERR_MEM;
    default:
      return (err_t)ERR_IF;
  }
}

/*-----------------------------------------------------------------------------------*
 *
 * lan91c111if_init():
 *
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * 
 *-----------------------------------------------------------------------------------*/
err_t lan91c111if_init(struct netif *netif)
{
  err_t ret_code;

  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_init()\n"));
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  netif->output = lan91c111if_output;
  netif->linkoutput = low_level_output;

  /* maximum transfer unit */
  netif->mtu = 1500;
  /* broadcast capability */
  netif->flags = NETIF_FLAG_BROADCAST;

  if (netif->state == NULL ) 
  {
    ret_code = ERR_IF;
    goto exit;
  }

  ret_code = low_level_init(netif);
  if (ret_code == ERR_OK)
  {
    etharp_init();
  }
  else
  {
    free(netif->state);
  }

exit:
  LWIP_DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111if_init() exit = %d\n",ret_code));

  return ret_code;
}


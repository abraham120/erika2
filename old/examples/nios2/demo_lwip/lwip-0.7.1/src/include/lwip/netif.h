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

/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
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
 *
 */
#ifndef __LWIP_NETIF_H__
#define __LWIP_NETIF_H__

#include "lwip/opt.h"

#include "lwip/err.h"

#include "lwip/ip_addr.h"

#include "lwip/inet.h"
#include "lwip/pbuf.h"
#include "lwip/dhcp.h"

/** must be the maximum of all used hardware address lengths
    across all types of interfaces in use */
#define NETIF_MAX_HWADDR_LEN 6U

/** TODO: define the use (where, when, whom) of netif flags */

/** whether the network interface is 'up'. this is
 * a software flag used to control whether this network
 * interface is enabled and processes traffic */
#define NETIF_FLAG_UP 0x1U
/** if set, the netif has broadcast capability */
#define NETIF_FLAG_BROADCAST 0x2U
/** if set, the netif is one end of a point-to-point connection */
#define NETIF_FLAG_POINTTOPOINT 0x4U
/** if set, the interface is configured using DHCP */
#define NETIF_FLAG_DHCP 0x08U
/** if set, the interface has an active link
 *  (set by the interface) */
#define NETIF_FLAG_LINK_UP 0x10U

/** generic data structure used for all lwIP network interfaces */
struct netif {
  /** pointer to next in linked list */
  struct netif *next;
  /** The following fields should be filled in by the
      initialization function for the device driver. */
  
  /** IP address configuration in network byte order */
  struct ip_addr ip_addr;
  struct ip_addr netmask;
  struct ip_addr gw;

  /** This function is called by the network device driver
      to pass a packet up the TCP/IP stack. */
  err_t (* input)(struct pbuf *p, struct netif *inp);
  /** This function is called by the IP module when it wants
      to send a packet on the interface. This function typically
      first resolves the hardware address, then sends the packet. */
  err_t (* output)(struct netif *netif, struct pbuf *p,
       struct ip_addr *ipaddr);
  /** This function is called by the ARP module when it wants
      to send a packet on the interface. This function outputs
      the pbuf as-is on the link medium. */
  err_t (* linkoutput)(struct netif *netif, struct pbuf *p);
  /** This field can be set by the device driver and could point
      to state information for the device. */
  void *state;
#if LWIP_DHCP
  /** the DHCP client state information for this netif */
  struct dhcp *dhcp;
#endif
  /** number of bytes used in hwaddr */
  unsigned char hwaddr_len;
  /** link level hardware address of this interface */
  unsigned char hwaddr[NETIF_MAX_HWADDR_LEN];
  /** maximum transfer unit (in bytes) */
  u16_t mtu;
  /** descriptive abbreviation */
  char name[2];
  /** number of this interface */
  u8_t num;
  /** NETIF_FLAG_* */
  u8_t flags;
};

/** The list of network interfaces. */
extern struct netif *netif_list;
/** The default network interface. */
extern struct netif *netif_default;

/* netif_init() must be called first. */
void netif_init(void);

struct netif *netif_add(struct netif *netif, struct ip_addr *ipaddr, struct ip_addr *netmask,
      struct ip_addr *gw,
      void *state,
      err_t (* init)(struct netif *netif),
      err_t (* input)(struct pbuf *p, struct netif *netif));

void
netif_set_addr(struct netif *netif,struct ip_addr *ipaddr, struct ip_addr *netmask,
    struct ip_addr *gw);
void netif_remove(struct netif * netif);

/* Returns a network interface given its name. The name is of the form
   "et0", where the first two letters are the "name" field in the
   netif structure, and the digit is in the num field in the same
   structure. */
struct netif *netif_find(char *name);

void netif_set_default(struct netif *netif);

void netif_set_ipaddr(struct netif *netif, struct ip_addr *ipaddr);
void netif_set_netmask(struct netif *netif, struct ip_addr *netmast);
void netif_set_gw(struct netif *netif, struct ip_addr *gw);

#endif /* __LWIP_NETIF_H__ */

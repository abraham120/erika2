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

#ifndef __NETIF_ETHARP_H__
#define __NETIF_ETHARP_H__

#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/ip.h"

#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct eth_addr {
  PACK_STRUCT_FIELD(u8_t addr[6]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

PACK_STRUCT_BEGIN
struct eth_hdr {
  PACK_STRUCT_FIELD(struct eth_addr dest);
  PACK_STRUCT_FIELD(struct eth_addr src);
  PACK_STRUCT_FIELD(u16_t type);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

PACK_STRUCT_BEGIN
/** the ARP message */
struct etharp_hdr {
  PACK_STRUCT_FIELD(struct eth_hdr ethhdr);
  PACK_STRUCT_FIELD(u16_t hwtype);
  PACK_STRUCT_FIELD(u16_t proto);
  PACK_STRUCT_FIELD(u16_t _hwlen_protolen);
  PACK_STRUCT_FIELD(u16_t opcode);
  PACK_STRUCT_FIELD(struct eth_addr shwaddr);
  PACK_STRUCT_FIELD(struct ip_addr sipaddr);
  PACK_STRUCT_FIELD(struct eth_addr dhwaddr);
  PACK_STRUCT_FIELD(struct ip_addr dipaddr);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END

PACK_STRUCT_BEGIN
struct ethip_hdr {
  PACK_STRUCT_FIELD(struct eth_hdr eth);
  PACK_STRUCT_FIELD(struct ip_hdr ip);
};
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

#define ARP_TMR_INTERVAL 10000

#define ETHTYPE_ARP 0x0806
#define ETHTYPE_IP  0x0800

void etharp_init(void);
void etharp_tmr(void);
struct pbuf *etharp_ip_input(struct netif *netif, struct pbuf *p);
struct pbuf *etharp_arp_input(struct netif *netif, struct eth_addr *ethaddr,
         struct pbuf *p);
struct pbuf *etharp_output(struct netif *netif, struct ip_addr *ipaddr,
         struct pbuf *q);
err_t etharp_query(struct netif *netif, struct ip_addr *ipaddr, struct pbuf *q);



#endif /* __NETIF_ARP_H__ */

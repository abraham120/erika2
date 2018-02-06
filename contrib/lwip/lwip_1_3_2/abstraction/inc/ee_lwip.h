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
 
/** 
* @file ee_lwip.h
* @brief LWIP main header file.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2010-07-12
*/

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "netif/ppp_oe.h"
#include "lwip/ip.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include <lwip/netif.h>

/** 
 * Headers used for LWIP porting into Erika 
 */
#include "hal/lwip_ethernet.h"
#include <util/lwip_debug.h>
#include <hal/lwip_timer.h>

#ifndef __EE_LWIP_H__
#define __EE_LWIP_H__

#define ETH_ADDR(ethp, a, b, c, d, e, f) \
	(ethp)->addr[0] = a; \
	(ethp)->addr[1] = b; \
	(ethp)->addr[2] = c; \
	(ethp)->addr[3] = d; \
	(ethp)->addr[4] = e; \
	(ethp)->addr[5] = f;

/**
 * Device ethernet address
 */
extern u8_t ETHERNETIF_MAC_BYTE1;
extern u8_t ETHERNETIF_MAC_BYTE2;
extern u8_t ETHERNETIF_MAC_BYTE3;
extern u8_t ETHERNETIF_MAC_BYTE4;
extern u8_t ETHERNETIF_MAC_BYTE5;
extern u8_t ETHERNETIF_MAC_BYTE6;	
	
/** 
 * Main network structure 
 */
extern struct netif EE_lwip_netif; 

/**
 * LWIP API for users 
 */
void EE_lwip_init(struct ip_addr *my_ipaddr, struct ip_addr *netmask, struct ip_addr *gw, struct eth_addr *my_ethaddr);

#endif /* __EE_LWIP_H__ */

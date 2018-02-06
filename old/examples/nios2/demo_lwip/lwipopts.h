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

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define NO_SYS                  1

/* ---------- Memory options ---------- */
#define MEM_ALIGNMENT           4
#define MEM_SIZE                64*1024
#define MEMP_NUM_PBUF           32
#define MEMP_NUM_SYS_TIMEOUT    0

/* The following four are used only with the sequential API and can be
   set to 0 if the application only will use the raw API. */
#define MEMP_NUM_NETBUF         0
#define MEMP_NUM_NETCONN        0
#define MEMP_NUM_API_MSG        0
#define MEMP_NUM_TCPIP_MSG      0

/* ---------- Pbuf options ---------- */
#define PBUF_POOL_SIZE          32
#define PBUF_POOL_BUFSIZE       1536
#define PBUF_LINK_HLEN          16

/* ---------- ARP options ---------- */
#define ARP_QUEUEING            0
#define ETHARP_ALWAYS_INSERT    0

/* ---------- IP options ---------- */

/* ---------- ICMP options ---------- */

/* ---------- DHCP options ---------- */
#define LWIP_DHCP               1

/* ---------- UDP options ---------- */
#define LWIP_UDP                1

/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_MSS                 1460
#define TCP_SND_BUF             4096


#define LWIP_CALLBACK_API       1

/* ---------- Statistics options ---------- */
#define LWIP_STATS              0

#endif /* __LWIPOPTS_H__ */

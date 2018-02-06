/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2011  Evidence Srl
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
    @file      lwip.h
    @author    Dario Di Stefano
    @date      2011
*/

/* Macros */
#define MY_ETHERNETIF_MAC_BYTE1     (0x00)
#define MY_ETHERNETIF_MAC_BYTE2     (0x04)
#define MY_ETHERNETIF_MAC_BYTE3     (0xA3)
#define MY_ETHERNETIF_MAC_BYTE4     (0x00)
#define MY_ETHERNETIF_MAC_BYTE5     (0x00)
#define MY_ETHERNETIF_MAC_BYTE6     (0x00)

#define MY_IPADDR_BYTE1             (192)
#define MY_IPADDR_BYTE2             (100)
#define MY_IPADDR_BYTE3             (100)
#define MY_IPADDR_BYTE4             (66)

#define MY_NETMASK_BYTE1            (255)
#define MY_NETMASK_BYTE2            (255)
#define MY_NETMASK_BYTE3            (255)
#define MY_NETMASK_BYTE4            (248)

#define MY_GATEWAY_ADDR_BYTE1       (192)
#define MY_GATEWAY_ADDR_BYTE2       (100)
#define MY_GATEWAY_ADDR_BYTE3       (100)
#define MY_GATEWAY_ADDR_BYTE4       (65)

#define MY_UDP_PORT                 (9760)
#define REMOTE_UDP_PORT             (9762)
#define UDP_SENDER_BUF_SIZE         (1408)
#define UDP_SENDER_INIT_SIZE        (11)
#define MY_UDP_BUFFER_LEN           UDP_SENDER_INIT_SIZE
#define UDP_NUM_PACKETS             (512)






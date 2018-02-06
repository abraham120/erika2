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
 * Copyright (c) 2001 Leon Woestenberg <leon.woestenberg@axon.nl>
 * Copyright (c) 2001 Axon Digital Design B.V., The Netherlands.
 * All rights reserved.
 *
 * This is a generic ethernet device driver used in combination with the lwIP stack.
 *
 * This is work under development. Please coordinate changes
 * and requests with Leon Woestenberg <leon.woestenberg@axon.nl>
 *
 * The Swedish Institute of Computer Science and Adam Dunkels
 * are specifically granted permission to redistribute this
 * source code under any conditions they seem fit.
 *
 */
#ifndef __LAN91C111IF_H__
#define __LAN91C111IF_H__

#include "altera_avalon_lan91c111.h"
#include "lwip/netif.h"

err_t lan91c111if_init(struct netif *);
err_t lan91c111if_service(struct netif *);
err_t lan91c111if_input(struct netif *);
err_t lan91c111if_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr);

#endif /* __LAN91C111IF_H__ */

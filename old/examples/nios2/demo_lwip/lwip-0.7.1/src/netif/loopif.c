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
#include "lwip/opt.h"

#if LWIP_HAVE_LOOPIF

#include "netif/loopif.h"
#include "lwip/mem.h"

#if defined(LWIP_DEBUG) && defined(LWIP_TCPDUMP)
#include "netif/tcpdump.h"
#endif /* LWIP_DEBUG && LWIP_TCPDUMP */

#include "lwip/tcp.h"
#include "lwip/ip.h"

static void
loopif_input( void * arg )
{
	struct netif *netif = (struct netif *)( ((void **)arg)[ 0 ] );
	struct pbuf *r = (struct pbuf *)( ((void **)arg)[ 1 ] );

	mem_free( arg );
	netif -> input( r, netif );
}

static err_t
loopif_output(struct netif *netif, struct pbuf *p,
       struct ip_addr *ipaddr)
{
  struct pbuf *q, *r;
  char *ptr;
  void **arg;

#if defined(LWIP_DEBUG) && defined(LWIP_TCPDUMP)
  tcpdump(p);
#endif /* LWIP_DEBUG && LWIP_TCPDUMP */
  
  r = pbuf_alloc(PBUF_RAW, p->tot_len, PBUF_RAM);
  if (r != NULL) {
    ptr = r->payload;
    
    for(q = p; q != NULL; q = q->next) {
      memcpy(ptr, q->payload, q->len);
      ptr += q->len;
    }

    arg = mem_malloc( sizeof( void *[2]));
	if( NULL == arg ) {
		return ERR_MEM;
	}
	
	arg[0] = netif;
	arg[1] = r;
	/**
	 * workaround (patch #1779) to try to prevent bug #2595:
	 * When connecting to "localhost" with the loopif interface,
	 * tcp_output doesn't get the opportunity to finnish sending the
	 * segment before tcp_process gets it, resulting in tcp_process
	 * referencing pcb->unacked-> which still is NULL.
	 * 
	 * TODO: Is there still a race condition here? Leon
	 */
	sys_timeout( 1, loopif_input, arg );
	
    return ERR_OK;    
  }
  return ERR_MEM;
}

err_t
loopif_init(struct netif *netif)
{
  netif->name[0] = 'l';
  netif->name[1] = 'o';
#if 0 /** TODO: I think this should be enabled, or not? Leon */
  netif->input = loopif_input;
#endif
  netif->output = loopif_output;
  return ERR_OK;
}

#endif /* LWIP_HAVE_LOOPIF */








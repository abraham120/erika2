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

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

struct echo_state {
  struct pbuf *p;
  u32_t  pos;    /* where to start in this pbuf */
  u32_t  left;   /* how many are left in this pbuf */
};

/*-----------------------------------------------------------------------------------*/
static void
echo_err(void *arg, err_t err)
{
  struct echo_state *es = arg;

  if (es) {
    if (es->p) {
      pbuf_free(es->p);
    }
    mem_free(es);
  }
}
/*-----------------------------------------------------------------------------------*/
static void
close_conn(struct tcp_pcb *pcb, struct echo_state *es)
{
  tcp_arg(pcb, NULL);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);
  if (es) {
    if (es->p) {
      pbuf_free(es->p);
    }
    mem_free(es);
  }
  tcp_close(pcb);
}
/*-----------------------------------------------------------------------------------*/
static void
send_data(struct tcp_pcb *pcb, struct echo_state *es)
{
  err_t err;
  u16_t len;

  if (es->p == NULL) 
    return;

  /* We cannot send more data than space avaliable in the send
     buffer. */    
  len = tcp_sndbuf(pcb); 
  if(len > es->left) {
    len = es->left;
  } 
  
  err = tcp_write(pcb, es->p->payload + es->pos, len, 1);
  
  if(err == ERR_OK) {
    es->pos  += len;
    es->left -= len;
  } else {
    printf("send_data: error %d len %d %d\n", err, len, tcp_sndbuf(pcb));
  }
}
/*-----------------------------------------------------------------------------------*/
static err_t
echo_poll(void *arg, struct tcp_pcb *pcb)
{
  struct echo_state *es = arg;

  /*  printf("Poll\n");*/
  if(es == NULL) {
    /*    printf("Null, close\n");*/
    tcp_close(pcb);
  } else {
    /* check to see if we need re-transmit */
  }

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
echo_sent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  struct pbuf *p;
  struct echo_state *es = arg;

  if (es->left > 0) {
    send_data(pcb, es);
  } else {
    if (es->p) {
      /* free the pbuf and send the next one */
      p = es->p;
      es->p = pbuf_dechain(p);
      es->pos = 0;
      if (es->p) es->left = es->p->len;
      else       es->left = 0;
      pbuf_free(p);
      if (es->left > 0) send_data(pcb, es);
    }
  }
  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
echo_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  struct echo_state *es = arg;

  if(err == ERR_OK && p != NULL) {

    /* Inform TCP that we have taken the data. */
    tcp_recved(pcb, p->tot_len);
    
    /* append this pbuf to the sending list */
    if (es->p) {
      pbuf_chain(es->p, p);
    }
    else {
      es->p    = p;
      es->left = p->len;
      es->pos  = 0;
    }
    send_data(pcb, es);

  } else {

    if (err != ERR_OK) 
      printf("error %d, connection closed \n", err);
    if (!p)
      printf("no data received, connection closed\n");
    close_conn(pcb, es);
  }

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
static err_t
echo_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
  struct echo_state *es;

//  tcp_setprio(pcb, TCP_PRIO_MIN);

  /* Allocate memory for the structure that holds the state of the
     connection. */
  es = mem_malloc(sizeof(struct echo_state));

  if(es == NULL) {
//    printf("echo_accept: Out of memory\n");
    return ERR_MEM;
  }

  /* Initialize the structure. */
  es->p    = NULL;
  es->left = 0;
  es->pos  = 0;

  /* Tell TCP that this is the structure we wish to be passed for our
     callbacks. */
  tcp_arg(pcb, es);

  /* Tell TCP that we wish to be informed of incoming data by a call
     to the echo_recv() function. */
  tcp_recv(pcb, echo_recv);

  /* Tell TCP that we wish be to informed of data that has been
     successfully sent by a call to the echo_sent() function. */
  tcp_sent(pcb, echo_sent);

  tcp_err(pcb, echo_err);
  
  tcp_poll(pcb, echo_poll, 10);

  return ERR_OK;
}
/*-----------------------------------------------------------------------------------*/
void
echo_init(void)
{
  struct tcp_pcb *pcb;

  pcb = tcp_new();
  tcp_bind(pcb, IP_ADDR_ANY, 7);
  pcb = tcp_listen(pcb);
  tcp_accept(pcb, echo_accept);
}
/*-----------------------------------------------------------------------------------*/

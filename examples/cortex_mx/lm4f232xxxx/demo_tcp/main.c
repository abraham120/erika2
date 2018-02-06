/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2012  Evidence Srl
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
 
/** @file	main.c
 *  @brief	LWIP TCP test (with ENC28J60, see oil files).
 *
 *  User can use this demo to learn how to write LWIP TCP based applications.
 *  The demo requires a RS232 serial connection with user PC.
 *  The demo requires a SPI bus to communicate with ENC28J60.
 *  The demo requires a Ethernet connection with user PC.
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */

/* RT-Kernel */
#include <ee.h>
/* Standard library */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
/* lwIP */
#include <ee_lwip.h>
#include "lwip.h"

/* AS MCAL */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#ifdef	DEBUG
#include "Sci.h"
#endif
#include "Spi.h"
#include "Icu.h"

#define	MY_TCP_PORT	9760
#define	REMOTE_TCP_PORT	50001

#define	TCP_SENDER_BUF_SIZE	1460
#define	TCP_SENDER_PKT_NUM	0

struct ip_addr	my_ipaddr, remote_ipaddr;
char		*msg = "LwIP Packet %d\n";

/*
 * Variables for TCP Server communication
 */
struct tcp_pcb	*srv_sender_tcp_pcb = NULL_PTR,
		*srv_listener_tcp_pcb = NULL_PTR,
		*srv_receiver_tcp_pcb = NULL_PTR;
struct my_pts	srv_sender_pts = { 0 };
EE_UINT8	srv_sender_buf[TCP_SENDER_BUF_SIZE];

/* 
 * Variables for TCP Client comunication
 */
struct tcp_pcb	*clt_sender_tcp_pcb = NULL_PTR;
struct my_pts	clt_sender_pts = { 0 };

#ifdef	DEBUG
#define	time_diff_ms(t1,t2)	\
	((EE_UINT32)((t1) - (t2)) / (EE_UINT32)(EE_CPU_CLOCK / 1000U))
#define	time_diff_us(t1,t2) 	\
	((EE_UINT32)((t1) - (t2)) / (EE_UINT32)(EE_CPU_CLOCK / 1000000U))

EE_UINT32 time1, time2, time3;

static void EE_uart_send_buffer(const char * const str, size_t len) {
  size_t i;
  uint8 rx;
  Sci_StatusType st;
  for(i = 0U; i < len; ++i) {
	/* To eventually handle errors in rx */
    st = Sci_GetStatus(SCI_CHANNEL_4);
    while ((st != SCI_OPERATIONAL) && (st != SCI_TX_OK)) {
	  Sci_ReadRxData(SCI_CHANNEL_4, &rx);
	  st = Sci_GetStatus(SCI_CHANNEL_4);
	}
    Sci_WriteTxData(SCI_CHANNEL_4, str[i]);
  }
}

#define	MAXCHARS	80

/* A printf-like function */
void myprintf(const char *format, ...)
{
  const char printf_trunc[] = "..[TRUNCATED]..\n";
  char str[MAXCHARS];
  int len;
  va_list args;

  va_start(args, format);
  len = vsnprintf(str, MAXCHARS, format, args);
  va_end(args);

  if (len > MAXCHARS - 1) {

    /* vsnptintf() returns the number of characters needed */
    EE_uart_send_buffer(str, MAXCHARS - 1 );
    EE_uart_send_buffer(printf_trunc, sizeof(printf_trunc) - 1);

  } else {

    EE_uart_send_buffer(str, len);

  }
}

/* This function is used to display received packets on serial terminal */
static void hex_dump(const void *base, int size)
{
  const unsigned char *p = base;
  char lbuf[16*3+4];
  int k, j;

  j = 0;
  for (k = 0; k < size; ++k) {

    sprintf(&lbuf[j], "%02x ", p[k]);

    j += 3;

    if (0 == ((k+1) % 16) || k == size-1) {

      lbuf[j++] = '\n';
      lbuf[j] = 0;
      EE_uart_send_buffer(lbuf, j);
      j = 0;

    } else if (0 == ((k+1) % 8)) {

      lbuf[j++] = ' ';

    }

  }
}
#endif	/* DEBUG */

void fill_buff(char *b, EE_UINT16 sz, EE_UINT32 pkt_num)
{
  register EE_UINT16 ofs = 0;
  register int n;
  while ( (ofs + 23) < sz ) {
    n = sprintf(&b[ofs], msg, pkt_num);
    ofs += n;
  }
}

/*
 * Sender Task: TCP Client.
 */
TASK(SenderTask)
{
  static EE_UINT8	buf[TCP_SENDER_BUF_SIZE];
  static EE_UINT16	size = 24;	/* strlen(msg) */
  static EE_UINT32	pn = 0;	/* Packet Number. */

#if	( TCP_SENDER_PKT_NUM != 0 )
  UINT32		i = 0;
#endif

  err_t ret;

  if ( clt_sender_tcp_pcb != NULL_PTR ) {

#if	( TCP_SENDER_PKT_NUM == 0 )
    if ( clt_sender_tcp_pcb->state == ESTABLISHED ) {
#else
    while (
      ( clt_sender_tcp_pcb->state == ESTABLISHED ) &&
      ( i++ < TCP_SENDER_PKT_NUM )
    ) {
#endif

      GetResource(LwipMutex);

      /* TCP packet setup */
#ifdef	DEBUG
      time1 = EE_systick_get_value();
#endif

      memset(buf, 0, TCP_SENDER_BUF_SIZE);
      fill_buff((char *)buf, size, pn++);
      clt_sender_pts.payload = buf;
      clt_sender_pts.left = size;
      clt_sender_pts.pos  = 0;

#ifdef	DEBUG
      time2 = EE_systick_get_value();
#endif

      /* Send the packet */
      ret = tcp_send_data(clt_sender_tcp_pcb, &clt_sender_pts);

      ReleaseResource(LwipMutex);

      if (ret == ERR_OK) {

	/* wait transmission end */
	while( 
	  (clt_sender_tcp_pcb->state == ESTABLISHED) &&
	  (clt_sender_pts.payload != NULL_PTR)
	) {
	    ;
	}

#ifdef	DEBUG
	if (
	  (clt_sender_tcp_pcb->state == ESTABLISHED) &&
	  (clt_sender_pts.payload == NULL_PTR)
	) {
	    GetResource(LwipMutex);
	    myprintf("Setup took %d us\n", time_diff_us(time1, time2));
	    myprintf(
	      "Transmission of %d B took %d ms (%d B/s)\n",
	      size,
	      time_diff_ms(time2, time3),
	      ( size * 1000 ) / time_diff_ms(time2, time3)
	    );
	    ReleaseResource(LwipMutex);
	}
#endif

	if ( (size << 1) <= TCP_SENDER_BUF_SIZE) {
	  size <<= 1;
	}
	else {
	  size = 24;
	}

      }
#ifdef	DEBUG
      else {

	GetResource(LwipMutex);
	myprintf("ERROR in sending a packet\n");
	ReleaseResource(LwipMutex);

      }
#endif

    }
#ifdef	DEBUG
    else {

      GetResource(LwipMutex);
      myprintf("ERROR: Client Sender TCP not connected\n");
      ReleaseResource(LwipMutex);

    }
#endif

  }
#ifdef	DEBUG
  else {

      GetResource(LwipMutex);
      myprintf("ERROR: Client Sender TCP PCB NULL\n");
      ReleaseResource(LwipMutex);

  }
#endif

}	/* TASK(SenderTask) */

TASK(InitTask)
{

  /* Initialize lwIP */
  struct ip_addr netmask, gw;
  struct eth_addr my_ethaddr;

#ifdef	DEBUG
  myprintf("\n\n\nLWIP configuration in progress...\n");
#endif

  IP4_ADDR(
    &my_ipaddr,
    MY_IPADDR_BYTE1,
    MY_IPADDR_BYTE2,
    MY_IPADDR_BYTE3,
    MY_IPADDR_BYTE4
  );

  IP4_ADDR(
    &netmask,
    MY_NETMASK_BYTE1,
    MY_NETMASK_BYTE2,
    MY_NETMASK_BYTE3,
    MY_NETMASK_BYTE4
  );

  IP4_ADDR(
    &gw,
    MY_GATEWAY_ADDR_BYTE1,
    MY_GATEWAY_ADDR_BYTE2,
    MY_GATEWAY_ADDR_BYTE3,
    MY_GATEWAY_ADDR_BYTE4
  );

  ETH_ADDR(
    &my_ethaddr,
    MY_ETHERNETIF_MAC_BYTE1,
    MY_ETHERNETIF_MAC_BYTE2,
    MY_ETHERNETIF_MAC_BYTE3,
    MY_ETHERNETIF_MAC_BYTE4,
    MY_ETHERNETIF_MAC_BYTE5,
    MY_ETHERNETIF_MAC_BYTE6
  );

  IP4_ADDR(
    &remote_ipaddr,
    REMOTE_IPADDR_BYTE1,
    REMOTE_IPADDR_BYTE2,
    REMOTE_IPADDR_BYTE3,
    REMOTE_IPADDR_BYTE4
  );

  EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);

#ifdef	DEBUG
  myprintf("Done!\n");
#endif

}	/* TASK(InitTask) */

TASK(BackgroundTask)
{
#ifdef	DEBUG
  err_t ret;
#endif

  GetResource(LwipMutex);

  /* Create Client Sender TCP Packet Control Block */
  clt_sender_tcp_pcb = tcp_new();

#ifdef	DEBUG
  myprintf("clt_sender_tcp_pcb: %p\n", clt_sender_tcp_pcb);
#endif

  /* Create Server Sender TCP Packet Control Block */
  srv_sender_tcp_pcb = tcp_new();

#ifdef	DEBUG
  myprintf("srv_sender_tcp_pcb: %p\n", srv_sender_tcp_pcb);
#endif

  /* Create Server Listener TCP Packet Control Block */
  srv_listener_tcp_pcb = tcp_new();

#ifdef	DEBUG
  myprintf("srv_listener_tcp_pcb: %p\n", srv_listener_tcp_pcb);
#endif

  ReleaseResource(LwipMutex);

  if (
    (clt_sender_tcp_pcb != NULL_PTR) &&
    (srv_sender_tcp_pcb != NULL_PTR) &&
    (srv_listener_tcp_pcb != NULL_PTR)
  ) {

    GetResource(LwipMutex);

    /* Client Sender Bind to a local port + 2 */
#ifdef	DEBUG
    ret =
#endif
    tcp_bind(clt_sender_tcp_pcb, &my_ipaddr, MY_TCP_PORT + 2);

#ifdef	DEBUG
    if (ret == ERR_OK) {
      myprintf("Client Sender Binds to TCP port %d\n", MY_TCP_PORT + 2);
    }
    else {
      myprintf("ERROR while binding to TCP port %d\n", MY_TCP_PORT + 2);
      myprintf("tcp_bind() return value: %d\n", ret);
    }
#endif

    /* Server Sender Bind to a local port + 1 */
#ifdef	DEBUG
    ret =
#endif
    tcp_bind(srv_sender_tcp_pcb, &my_ipaddr, MY_TCP_PORT + 1);

#ifdef	DEBUG
    if (ret == ERR_OK) {
      myprintf("Server Sender Binds to TCP port %d\n", MY_TCP_PORT + 1);
    }
    else {
      myprintf("ERROR while binding to TCP port %d\n", MY_TCP_PORT + 1);
      myprintf("tcp_bind() return value: %d\n", ret);
    }
#endif

    /* Server Listener Bind to a local port */
#ifdef	DEBUG
    ret =
#endif
    tcp_bind(srv_listener_tcp_pcb, &my_ipaddr, MY_TCP_PORT);

#ifdef	DEBUG
    if (ret == ERR_OK) {
      myprintf("Server Listener Binds to TCP port %d\n", MY_TCP_PORT);
    }
    else {
      myprintf("ERROR while binding to TCP port %d\n", MY_TCP_PORT);
      myprintf("tcp_bind() return value: %d\n", ret);
    }
#endif

    ReleaseResource(LwipMutex);

    for (;;) {

      if ( srv_listener_tcp_pcb->state == CLOSED ) {

	GetResource(LwipMutex);

	srv_listener_tcp_pcb = tcp_listen(srv_listener_tcp_pcb);

	if (
	  (srv_listener_tcp_pcb != NULL_PTR) &&
	  (srv_listener_tcp_pcb->state == LISTEN)
	) {
#ifdef	DEBUG
	  myprintf("srv_listener_tcp_pcb: %p\n", srv_listener_tcp_pcb);
	  myprintf(
	    "Server listening to TCP %d.%d.%d.%d:%d...\n",
	    ip4_addr1(&remote_ipaddr),
	    ip4_addr2(&remote_ipaddr),
	    ip4_addr3(&remote_ipaddr),
	    ip4_addr4(&remote_ipaddr),
	    REMOTE_TCP_PORT
	  );
#endif
	  tcp_accept(srv_listener_tcp_pcb, &tcp_accept_callback);
	}
#ifdef	DEBUG
	else {
	  myprintf(
	    "ERROR while Server listening to TCP %d.%d.%d.%d:%d\n",
	    ip4_addr1(&remote_ipaddr),
	    ip4_addr2(&remote_ipaddr),
	    ip4_addr3(&remote_ipaddr),
	    ip4_addr4(&remote_ipaddr),
	    REMOTE_TCP_PORT
	  );
	  myprintf("tcp_listen() return value: %p\n", srv_listener_tcp_pcb);
	  if (srv_listener_tcp_pcb != NULL_PTR) {
	    switch (srv_listener_tcp_pcb->state) {
	        case CLOSED:
		  myprintf("pcb state: CLOSED\n");
		  break;
		case LISTEN:
		  myprintf("pcb state: LISTEN\n");
		  break;
		case SYN_SENT:
		  myprintf("pcb state: SYN_SENT\n");
		  break;
		case SYN_RCVD:
		  myprintf("pcb state: SYN_RCVD\n");
		  break;
		case ESTABLISHED:
		  myprintf("pcb state: ESTABLISHED\n");
		  break;
		case FIN_WAIT_1:
		  myprintf("pcb state: FIN_WAIT_1\n");
		  break;
		case FIN_WAIT_2:
		  myprintf("pcb state: FIN_WAIT_2\n");
		  break;
		case CLOSE_WAIT:
		  myprintf("pcb state: CLOSE_WAIT\n");
		  break;
		case CLOSING:
		  myprintf("pcb state: CLOSING\n");
		  break;
		case LAST_ACK:
		  myprintf("pcb state: LAST_ACK\n");
		  break;
		case TIME_WAIT:
		  myprintf("pcb state: CLOSED\n");
		  break;
		default:
		  myprintf("pcb state: UNKNOWN\n");
	    }
	  }
	}
#endif

	ReleaseResource(LwipMutex);

      }

      if ( srv_sender_tcp_pcb->state == CLOSED ) {

	GetResource(LwipMutex);

#ifdef	DEBUG
	ret =
#endif
	tcp_connect(
	  srv_sender_tcp_pcb,
	  &remote_ipaddr,
	  REMOTE_TCP_PORT,
	  &tcp_connect_callback
	);

#ifdef	DEBUG
	if (ret == ERR_OK) {
	  myprintf(
	    "Server Sender connecting to TCP %d.%d.%d.%d:%d...\n",
	    ip4_addr1(&remote_ipaddr),
	    ip4_addr2(&remote_ipaddr),
	    ip4_addr3(&remote_ipaddr),
	    ip4_addr4(&remote_ipaddr),
	    REMOTE_TCP_PORT
	  );
	}
	else {
	  myprintf(
	    "ERROR while Server Sender connecting to TCP %d.%d.%d.%d:%d\n",
	    ip4_addr1(&remote_ipaddr),
	    ip4_addr2(&remote_ipaddr),
	    ip4_addr3(&remote_ipaddr),
	    ip4_addr4(&remote_ipaddr),
	    REMOTE_TCP_PORT
	  );
	  myprintf("tcp_connect() return value: %d\n", ret);
	}
#endif

	ReleaseResource(LwipMutex);

      }

      if ( clt_sender_tcp_pcb->state == CLOSED ) {

	GetResource(LwipMutex);

#ifdef	DEBUG
	ret =
#endif
	tcp_connect(
	  clt_sender_tcp_pcb,
	  &remote_ipaddr,
	  REMOTE_TCP_PORT,
	  &tcp_connect_callback
	);

#ifdef	DEBUG
	if (ret == ERR_OK) {
	  myprintf(
	    "Client Sender connecting to TCP %d.%d.%d.%d:%d...\n",
	    ip4_addr1(&remote_ipaddr),
	    ip4_addr2(&remote_ipaddr),
	    ip4_addr3(&remote_ipaddr),
	    ip4_addr4(&remote_ipaddr),
	    REMOTE_TCP_PORT
	  );
	}
	else {
	  myprintf(
	    "ERROR while Server Sender connecting to TCP %d.%d.%d.%d:%d\n",
	    ip4_addr1(&remote_ipaddr),
	    ip4_addr2(&remote_ipaddr),
	    ip4_addr3(&remote_ipaddr),
	    ip4_addr4(&remote_ipaddr),
	    REMOTE_TCP_PORT
	  );
	  myprintf("tcp_connect() return value: %d\n", ret);
	}
#endif

	ReleaseResource(LwipMutex);

      }

    }

  }
  else {

    Icu_DisableEdgeDetection(ICU_ENC28J60_CHANNEL);
    Icu_DisableNotification(ICU_ENC28J60_CHANNEL);

    for (;;) {

#ifdef	DEBUG
      GetResource(LwipMutex);
      myprintf("ERROR while creating TCP PCBs\n");
      ReleaseResource(LwipMutex);
#endif

    }

  }

}	/* TASK(BackGroundTask) */

/*
 * MAIN TASK
 */
int main (void) {
  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  /* 50 MHz Clock  */
  if ( Mcu_InitClock(MCU_CLOCK_MODE_MOSC_4_PLL) == E_NOT_OK ) {

    Mcu_PerformReset();

  }

  while ( Mcu_GetPllStatus() != MCU_PLL_LOCKED );

  Mcu_DistributePllClock();

  /* Initialize all AS MCAL */
  Port_Init(PORT_CONFIG_SPI_ENC28J60_PTR);
  Dio_Init(DIO_CONFIG_ENC28J60_PTR);
#ifdef	DEBUG
  Sci_Init(SCI_CONFIG_DEFAULT_PTR);
#endif
  Dma_Init(DMA_CONFIG_SPI_PTR);
  Spi_Init(SPI_CONFIG_ENC28J60_PTR);
  Icu_Init(ICU_CONFIG_ENC28J60_PTR);
  Icu_EnableNotification(ICU_ENC28J60_CHANNEL);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

/*
 * TCP connection closing
 */
err_t tcp_close_connection(struct tcp_pcb *pcb)
{
#ifdef	DEBUG
  myprintf("\ntcp_close_connection start!\n");
#endif

  tcp_arg(pcb, NULL);
  tcp_err(pcb, NULL);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);

  err_t err = tcp_close(pcb);

#ifdef	DEBUG
  myprintf("tcp_close_connection end!\n");
#endif

  return err;
}

/* TCP send data */
err_t tcp_send_data(struct tcp_pcb *pcb, struct my_pts *pts)
{
  err_t err;
  u16_t len;

#ifdef	DEBUG
  myprintf("\ntcp_send_data start!\n");
#endif

  if (pts->payload == NULL) {

#ifdef	DEBUG
    myprintf("payload NULL -> tcp_send_data end!\n");
#endif

    return ERR_OK;

  }

  /* We cannot send more data than space avaliable in the send buffer. */
  len = tcp_sndbuf(pcb);

#ifdef	DEBUG
  myprintf("tcp_send_data: max length available = %d\n", len);
#endif

  if(len > pts->left){

    len = pts->left;

  }

#ifdef	DEBUG
  myprintf("tcp_send_data: length required = %d\n", len);

  myprintf("\ntcp_send_data write...\n");
#endif

  /* Send the extracted packet */
  err = tcp_write(
    pcb,
    (const void *)((u8_t *)pts->payload + pts->pos),
    len,
    TCP_WRITE_FLAG_COPY
  );

  if(err == ERR_OK) {

    pts->pos += len;
    pts->left -= len;

#ifdef	DEBUG
    myprintf("done!\n");
#endif

  }
  else {

#ifdef	DEBUG
    myprintf(
      "tcp_write() error! code: %d, len: %d, space: %d\n",
      err,
      len,
      tcp_sndbuf(pcb)
    );
#endif

    tcp_close_connection(pcb);

  }

#ifdef	DEBUG
  myprintf("tcp_send_data end!\n");
#endif

  return err;
}

/* TCP tx handler */
err_t tcp_tx_callback(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  struct my_pts *pts = (struct my_pts *)arg;

#ifdef	DEBUG
  myprintf("\ntcp_tx_callback start!\n");
#endif

  if (pts->left > 0) {

    tcp_send_data(pcb, pts);

  }
  else {

    pts->payload = NULL_PTR;

#ifdef	DEBUG
    myprintf("tcp_tx_callback FINISHED!\n");

    if (pcb == clt_sender_tcp_pcb) {
      time3 = EE_systick_get_value();
    }
#endif

  }

#ifdef	DEBUG
  myprintf("tcp_tx_callback end!\n");
#endif

  return ERR_OK;
}

/*
 * TCP RX callback
 */
err_t tcp_rx_callback(
  void			*arg,
  struct tcp_pcb	*pcb,
  struct pbuf		*p,
  err_t			err
) {

#ifdef	DEBUG
  struct pbuf *q;
  int i;

  myprintf("\ntcp_rx_callback start!\n");
#endif

  /* Make the LED blink in RX */
  Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_HIGH);

    if(err != ERR_OK) {

#ifdef	DEBUG
      myprintf("tcp_rx_callback error %d, connection closed \n", err);
#endif

      tcp_close_connection(pcb);

    }
    else {

      if (p != NULL) {

#ifdef	DEBUG
	/* Print the received TCP packet */
	myprintf(
	  "\nReceived %d bytes from %d.%d.%d.%d, port %d\n",
	  p->tot_len,
	  ip4_addr1(&(pcb->remote_ip)),
	  ip4_addr2(&(pcb->remote_ip)), 
	  ip4_addr3(&(pcb->remote_ip)),
	  ip4_addr4(&(pcb->remote_ip)),
	  pcb->remote_port
	);

	for(i = 1, q = p; q != NULL; q = q->next, ++i) {
	  myprintf("Chunk #%d, %d byte long\n",i, q->len);
	  hex_dump(q->payload, q->len);
	}
#endif

	if ( pcb == srv_receiver_tcp_pcb ) {

	  if ( srv_sender_tcp_pcb->state == ESTABLISHED ) {

	    memset(srv_sender_buf, 0, TCP_SENDER_BUF_SIZE);
	    memcpy(srv_sender_buf, p->payload, p->len);

	    srv_sender_pts.payload = srv_sender_buf;
	    srv_sender_pts.left = p->len;
	    srv_sender_pts.pos  = 0;

	    /* Send the packet */
	    err = tcp_send_data(srv_sender_tcp_pcb, &srv_sender_pts);

#ifdef	DEBUG
	    if (err != ERR_OK) {

	      myprintf("ERROR in sending a packet\n");

	    }
#endif

	  }

	}
	else {

	  /* Unknown Connection!!! */
#ifdef	DEBUG
	  myprintf("\ntcp_rx_callback: connection unknown!\n");
#endif

	}

	/* Inform TCP that we have taken the data. */
	tcp_recved(pcb, p->tot_len);

      } 
      else {

#ifdef	DEBUG
	myprintf("tcp_rx_callback: no data received, connection closed\n");
#endif

	tcp_close_connection(pcb);

      }

    }

  /* Don't leak the pbuf! */
  pbuf_free(p);

  /* Make the LED blink in RX */
  Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_LOW);

#ifdef	DEBUG
  myprintf("tcp_rx_callback end!\n");
#endif

  return err;

}

/*
 * TCP accept callback
 */
err_t tcp_accept_callback(void *arg, struct tcp_pcb *pcb, err_t err)
{
#ifdef	DEBUG
  myprintf("\ntcp_accept_callback start!\n");
#endif

#if	0
  if ( pcb == srv_receiver_tcp_pcb ) {
#ifdef	DEBUG
    myprintf(
      "Server connection accepted from TCP %d.%d.%d.%d:%d\n",
      ip4_addr1(&(srv_receiver_tcp_pcb->remote_ip)),
      ip4_addr2(&(srv_receiver_tcp_pcb->remote_ip)),
      ip4_addr3(&(srv_receiver_tcp_pcb->remote_ip)),
      ip4_addr4(&(srv_receiver_tcp_pcb->remote_ip)),
      srv_receiver_tcp_pcb->remote_port
    );
#endif
#else
#ifdef	DEBUG
    myprintf(
      "Server connection accepted from TCP %d.%d.%d.%d:%d\n",
      ip4_addr1(&(pcb->remote_ip)),
      ip4_addr2(&(pcb->remote_ip)),
      ip4_addr3(&(pcb->remote_ip)),
      ip4_addr4(&(pcb->remote_ip)),
      pcb->remote_port
    );
#endif
#endif

    /* 
     * Tell TCP that this is the structure we wish to be passed for our
     * callbacks.
     */
#ifdef	DEBUG
    tcp_err(pcb, &tcp_error_callback);	/* Set the error callback */
#endif
    tcp_recv(pcb, &tcp_rx_callback);	/* Set the rx callback */
    srv_receiver_tcp_pcb = pcb;
    tcp_accepted(srv_listener_tcp_pcb);
#if	0
  }
  else {

    /* Unknown Connection!!! */
#ifdef	DEBUG
    myprintf("pcb: %p\n", pcb);
    myprintf("srv_receiver_tcp_pcb: %p\n", srv_receiver_tcp_pcb);
    myprintf("\ntcp_accept_callback: connection unknown!\n");
#endif
    tcp_close(pcb);
    return ERR_VAL;

  }
#endif

#ifdef	DEBUG
  myprintf("tcp_accect_callback end!\n");
#endif

  return ERR_OK;
}

/*
 * TCP connect callback
 */
err_t tcp_connect_callback(void *arg, struct tcp_pcb *pcb, err_t err)
{
#ifdef	DEBUG
  myprintf("\ntcp_connect_callback start!\n");
#endif

  if ( pcb == srv_sender_tcp_pcb ) {
#ifdef	DEBUG
    myprintf(
      "Server Sender connected to TCP %d.%d.%d.%d:%d\n",
      ip4_addr1(&remote_ipaddr),
      ip4_addr2(&remote_ipaddr),
      ip4_addr3(&remote_ipaddr),
      ip4_addr4(&remote_ipaddr),
      REMOTE_TCP_PORT
    );
#endif

    /* Server Sender Connected: Initialize the pts. */
    srv_sender_pts.payload = NULL;
    srv_sender_pts.left = 0;
    srv_sender_pts.pos  = 0;

    /* 
     * Tell TCP that this is the structure we wish to be passed for our
     * callbacks.
     */
    tcp_arg(pcb, &srv_sender_pts);	/* Set the argument that will be passed 
					 * to all callbacks for that connection
					 */
#ifdef	DEBUG
    tcp_err(pcb, &tcp_error_callback);	/* Set the error callback */
#endif
    tcp_sent(pcb, &tcp_tx_callback);	/* Set the tx callback */
  }
  else if ( pcb == clt_sender_tcp_pcb ) {
#ifdef	DEBUG
    myprintf(
      "Client Sender connected to TCP %d.%d.%d.%d:%d\n",
      ip4_addr1(&remote_ipaddr),
      ip4_addr2(&remote_ipaddr),
      ip4_addr3(&remote_ipaddr),
      ip4_addr4(&remote_ipaddr),
      REMOTE_TCP_PORT
    );
#endif

    /* Client Sender Connected: Initialize the pts. */
    clt_sender_pts.payload = NULL_PTR;
    clt_sender_pts.left = 0;
    clt_sender_pts.pos  = 0;

    /* 
     * Tell TCP that this is the structure we wish to be passed for our
     * callbacks.
     */
    tcp_arg(pcb, &clt_sender_pts);	/* Set the argument that will be passed 
					 * to all callbacks for that connection
					 */
#ifdef	DEBUG
    tcp_err(pcb, &tcp_error_callback);	/* Set the error callback */
#endif
    tcp_sent(pcb, &tcp_tx_callback);	/* Set the tx callback */
  }
  else {

    
    /* Unknown Connection!!! */
#ifdef	DEBUG
    myprintf("\ntcp_connect_callback: connection unknown!\n");
#endif
    tcp_close(pcb);
    return ERR_VAL;

  }

#ifdef	DEBUG
  myprintf("tcp_connect_callback end!\n");
#endif

  return ERR_OK;
}

#ifdef	DEBUG
/*
 * TCP error callback
 */
void  tcp_error_callback(void *arg, err_t err)
{
  myprintf("tcp_error_callback start!\n");
  myprintf("TCP Error Code: %d\n", err);
  myprintf("tcp_error_callback end!\n");
}
#endif

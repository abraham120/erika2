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
 
/** @file	tcp_clt.c
 *  @brief	TCP Client.
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

/* BUFLEN is 1460 bytes */
#define	BUFLEN		1460

/* Number of "packets" sent per connection. */
#define	NPACK		0

static int pkt_num = 0;

/* Server's IP Address. */
#define	SRV_IP		"192.168.0.2"

/* Server's port number */
#define	SRV_PORT	9760

int main(void)
{

  /* Variable and structure definitions. */
  struct sockaddr_in serveraddr;
  int s, i, rc;
  char buf[BUFLEN] = { 0 };

  memset(&serveraddr, 0x00U, sizeof(struct sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(SRV_PORT);
  if (
    (serveraddr.sin_addr.s_addr = inet_addr(SRV_IP)) ==
    (unsigned long)INADDR_NONE
  ) {

    perror("Server-address() error");

    exit(-1);

  }

  for (;;) {

    /* get a socket descriptor */
    if ( (s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {

      perror("Client-socket() error");
      exit(-1);

    }
  
    /* connect() to server. */
    if ( 
      (rc = connect(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0
    ) {

      perror("Client-connect() error");

    }

#if ( NPACK > 0 )
    for (i = 0; ( i < NPACK ) && ( rc >= 0 ); i++) {
#else
    while ( rc >= 0 ) {
#endif

      /* Write() some string to the server. */
      printf("Sending packet %d\n\n", pkt_num);
      sprintf(buf, "PC Packet %d\n", pkt_num);
      pkt_num++;
      rc = write(s, buf, BUFLEN);

      if (rc < 0) {

	perror("Client-write() error");
	/* Close socket descriptor from client side. */
	close(s);

      }

      usleep(5000000);

    }	/*
	 * for (i = 0; ( i < NPACK ) && ( rc >= 0 ); i++)
	 * while ( rc >= 0 )
	 */

#if ( NPACK > 0 )
    /* Close socket descriptor from client side. */
    close(s);
#endif

  }	/* for (;;) */

  return 0;

}

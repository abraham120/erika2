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
 
/** @file	udp_recv.c
 *  @brief	UDP receive packets.
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define	BUFLEN	1472

void diep(char *s)
{
  perror(s);
  exit(1);
}

#define MY_IP	"192.168.0.1"
#define	MY_PORT	8640

#define OTHER_IP	"192.168.0.2"
#define	OTHER_PORT	9760

int main(void)
{

  struct sockaddr_in si_me, si_other;
  int s, slen=sizeof(si_other);
  char buf[BUFLEN] = { 0 };

  if ( (s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {

    diep("socket() error!\n");

  }

  memset((char *) &si_me, sizeof(si_me), 0);

  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(MY_PORT);

  if ( inet_aton(MY_IP, &si_me.sin_addr) == 0 ) {

    diep("inet_aton() error!\n");

  }

  if ( bind(s, (const struct sockaddr *) &si_me, sizeof(si_me)) == -1 ) {

    diep("bind() error!\n");

  }

  while (1) {

    if ( 
      recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1
    ) {

      perror("revfrom() error!\n");

    }
    else {

      printf(
	"Received packet from %s:%d\n%s\n\n", 
	inet_ntoa(si_other.sin_addr),
	ntohs(si_other.sin_port),
	buf
      );

    }

  }

  close(s);

  return 0;

}

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
 
/** @file	udp_send.c
 *  @brief	UDP send packets.
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
#define	NPACK	0

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

  struct sockaddr_in si_other;
  int s, i;
  char buf[BUFLEN] = { 0 };

  if ( (s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {

    diep("socket() error!\n");

  }

  memset((char *) &si_other, 0, sizeof(si_other));

  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(OTHER_PORT);

  if ( inet_aton(OTHER_IP, &si_other.sin_addr) == 0 ) {

    diep("inet_aton() error!\n");

  }

#if ( NPACK > 0 )
  for (i = 0; i < NPACK; i++) {
#else
  for (i = 0; 1; i++) {
#endif

    printf("Sending packet %d\n\n", i);
    sprintf(buf, "PC Packet %d\n", i);

    if (
      sendto(
	s, buf, BUFLEN, 0, (const struct sockaddr *) &si_other, sizeof(si_other)
      ) == -1
    ) {

      diep("sendto() error!\n");

    }

    usleep(40000);

  }

  close(s);

  return 0;

}

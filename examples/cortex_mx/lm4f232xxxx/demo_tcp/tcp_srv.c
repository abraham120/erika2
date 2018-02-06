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
 
/** @file	tcp_srv.c
 *  @brief	TCP ECHO Server.
 *
 *  Using select() for I/O multiplexing.
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* port we're listening on */
#define	PORT	50001

int main(int argc, char *argv[])
{

  fd_set	master;		/* master file descriptor list */
  fd_set	read_fds;	/* temp file descriptor list for select() */

  struct sockaddr_in	serveraddr;	/* server address */
  struct sockaddr_in	clientaddr;	/* client address */

  int	fdmax;		/* maximum file descriptor number */

  int	listener;	/* listening socket descriptor */

  int	newfd;		/* newly accept()ed socket descriptor */

  char	buf[1024];	/* buffer for client data */

  int	nbytes;

  int	yes = 1;		/* for setsockopt() SO_REUSEADDR, below */

  int	addrlen;

  int	i, j;

  /* clear the master and temp sets */
  FD_ZERO(&master);
  FD_ZERO(&read_fds);

  if ( (listener = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {

    perror("Server-socket() error!");

    exit(1);

  }

  if ( 
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1
  ) {

    /* "address already in use" error message */
    perror("Server-setsockopt() error!");

    exit(1);

  }

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);
  memset(&(serveraddr.sin_zero), '\0', 8);

  if (
    bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1
  ) {

    perror("Server-bind() error!");

    exit(1);

  }

  if ( listen(listener, 10) == -1 ) {

    perror("Server-listen() error!");

    exit(1);

  }

  FD_SET(listener, &master);	/* add the listener to the master set */

  /* keep track of the biggest file descriptor */
  fdmax = listener; /* so far, it's this one*/

  /* main loop */
  for (;;) {

    read_fds = master;	/* copy it */

    if ( select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1 ) {

        perror("Server-select() error!");

        exit(1);

    }

    /* run through the existing connections looking for data to be read */
    for ( i = 0; i <= fdmax; i++ ) {

      if (  FD_ISSET(i, &read_fds)  ) { 

	/* we got one... */
	if ( i == listener ) {

	  /* handle new connections */
	  addrlen = sizeof(clientaddr);

	  if (
	    (
	      newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)
	    ) == -1
	  ) {

	    perror("Server-accept() error!");

	  }
	  else {

	    FD_SET(newfd, &master); /* add to master set */

	    if ( newfd > fdmax ) {

	      /* keep track of the maximum */
	      fdmax = newfd;

	    }

	    printf(
	      "%s: New connection from %s on socket %d\n",
	      argv[0],
	      inet_ntoa(clientaddr.sin_addr),
	      newfd
	    );

	  }

	}
	else {

	  /* handle data from a client */

	  if ( (nbytes = recv(i, buf, sizeof(buf), 0)) <= 0 ) {

	    /* got error or connection closed by client */
	    if ( nbytes == 0 ) {

	      /* connection closed */
	      printf("%s: socket %d hung up\n", argv[0], i);

	    }
	    else {

	      perror("recv() error!");

	    }

	    close(i);	/* close it... */

	    FD_CLR(i, &master);	/* remove from master set */

	  }
	  else {

	    /* we got some data from a client*/
	    for ( j = 0; j <= fdmax; j++ ) {

	      /* send to everyone! */
	      if ( FD_ISSET(j, &master) ) {

		/* except the listener and ourselves */
		if ( 
		  ( j != listener )
		  && ( j != i )
		) {

		  if ( send(j, buf, nbytes, 0) == -1 ) {

		    perror("send() error!");

		  }

		}

	      }

	    }

	  }

	}

      }

    }

  }

  return 0;

}

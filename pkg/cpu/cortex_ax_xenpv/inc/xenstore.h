/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2014 Arianna Avanzini
 */

#ifndef _XENSTORE_H_
#define _XENSTORE_H_

typedef EE_UINT32 XENSTORE_RING_IDX;

struct xsd_sockmsg
{
    EE_UINT32 type;  /* XS_??? */
    EE_UINT32 req_id;/* Request identifier, echoed in daemon's response.  */
    EE_UINT32 tx_id; /* Transaction id (0 if not related to a transaction). */
    EE_UINT32 len;   /* Length of data following this. */

    /* Generally followed by nul-terminated string(s). */
};


enum xsd_sockmsg_type
{
    XS_DEBUG,
    XS_DIRECTORY,
    XS_READ,
    XS_GET_PERMS,
    XS_WATCH,
    XS_UNWATCH,
    XS_TRANSACTION_START,
    XS_TRANSACTION_END,
    XS_INTRODUCE,
    XS_RELEASE,
    XS_GET_DOMAIN_PATH,
    XS_WRITE,
    XS_MKDIR,
    XS_RM,
    XS_SET_PERMS,
    XS_WATCH_EVENT,
    XS_ERROR,
    XS_IS_DOMAIN_INTRODUCED,
    XS_RESUME,
    XS_SET_TARGET,
    XS_RESTRICT,
    XS_RESET_WATCHES
};

struct evtchn_send {
    /* IN parameters. */
    evtchn_port_t port;
};
typedef struct evtchn_send evtchn_send_t;

#define XENSTORE_RING_SIZE 1024

struct xenstore_domain_interface {
    char req[XENSTORE_RING_SIZE]; /* Requests to xenstore daemon. */
    char rsp[XENSTORE_RING_SIZE]; /* Replies and async watch events. */
    XENSTORE_RING_IDX req_cons, req_prod;
    XENSTORE_RING_IDX rsp_cons, rsp_prod;
};

#define NOTIFY(store_evtchn)							\
	do {								\
		evtchn_send_t event;					\
		event.port = store_evtchn;				\
		if (HYPERVISOR_event_channel_op(EVTCHNOP_send, &event))	\
			printk("EE: ERROR: xenstore send\n");		\
	} while(0);

#define IGNORE(xenstore_buf, n)					\
	do {									\
		char buffer[XENSTORE_RING_SIZE];				\
		xenstore_read_response(xenstore_buf, buffer, n);	\
	} while(0);


void arch_init_xenbus(struct xenstore_domain_interface **xenstore_buf, EE_UINT32 *store_evtchn);
int xenstore_write_request(struct xenstore_domain_interface *xenstore_buf, char *message, int length);
int xenstore_read_response(struct xenstore_domain_interface *xenstore_buf, char *message, int length);
int strlnx(char *s);
int xenstore_write(struct xenstore_domain_interface *xenstore_buf, EE_UINT32 store_evtchn, char *key, char *value);
int xenstore_read(struct xenstore_domain_interface *xenstore_buf, EE_UINT32 store_evtchn, char *key, char *value, int value_length);

#endif /*_XENSTORE_H_*/

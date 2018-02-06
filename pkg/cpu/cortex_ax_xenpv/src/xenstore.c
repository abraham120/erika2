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

#include "cpu/common/inc/ee_types.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_cpu.h"
#include "cpu/cortex_ax_xenpv/inc/xenincludes.h"
#include "cpu/cortex_ax_xenpv/inc/xenstore.h"
#include "cpu/cortex_ax_xenpv/inc/xenevents.h"
#include "cpu/cortex_ax_xenpv/inc/xendebug.h"
#include "cpu/cortex_ax_xenpv/inc/hyper-calls.h"

#define HVMOP_set_param           0
#define HVMOP_get_param           1
struct xen_hvm_param {
    domid_t  domid;    /* IN */
    EE_UINT32 index;    /* IN */
    EE_UINT64 value;    /* IN/OUT */
};
typedef struct xen_hvm_param xen_hvm_param_t;

#define HVM_PARAM_STORE_PFN    1
#define HVM_PARAM_STORE_EVTCHN 2

typedef EE_UINT32 XENSTORE_RING_IDX;
#define MASK_XENSTORE_IDX(idx) ((idx) & (XENSTORE_RING_SIZE-1))

static volatile int req_id = 0;

extern int HYPERVISOR_hvm_op(int what, struct xen_hvm_param *xhv);

static inline int hvm_get_parameter(int idx, EE_UINT64 *value)
{
        struct xen_hvm_param xhv;
        int ret;

        xhv.domid = DOMID_SELF;
        xhv.index = idx;
        ret = HYPERVISOR_hvm_op(HVMOP_get_param, &xhv);
        if (ret < 0) {
		printk("EE: ERROR: cannot get parameter\n");
		goto out;
        }
        *value = xhv.value;
out:
        return ret;
}

void arch_init_xenbus(struct xenstore_domain_interface **xenstore_buf, EE_UINT32 *store_evtchn) {
        EE_UINT64 value;
        EE_UINT64 xenstore_pfn;

	if (hvm_get_parameter(HVM_PARAM_STORE_EVTCHN, &value)) {
		printk("EE: ERROR: cannot get xenstore evtchn\n");
		return;
	}

        *store_evtchn = (int)value;

        if (hvm_get_parameter(HVM_PARAM_STORE_PFN, &value)) {
		printk("EE: ERROR: cannot get xenstore pfn\n");
		return;
	}
        xenstore_pfn = value;

        *xenstore_buf = pfn_to_virt(xenstore_pfn);
}

int xenstore_write_request(struct xenstore_domain_interface *xenstore_buf, char *message, int length)
{
	int i;
	if (length > XENSTORE_RING_SIZE)
		return -1;
	for (i = xenstore_buf->req_prod ; length > 0 ; i++, length--) {
		XENSTORE_RING_IDX data;
		do {
			data = i - xenstore_buf->req_cons;
			mb();
		} while (data >= sizeof(xenstore_buf->req));
		xenstore_buf->req[MASK_XENSTORE_IDX(i)] = *message;
		message++;
	}
	wmb();
	xenstore_buf->req_prod = i;
	return 0;
}

int xenstore_read_response(struct xenstore_domain_interface *xenstore_buf, char *message, int length)
{
	int i;
	for (i = xenstore_buf->rsp_cons ; length > 0 ; i++, length--) {
		XENSTORE_RING_IDX data;
		do {
			data = xenstore_buf->rsp_prod - i;
			mb();
		} while (data == 0);
		*message = xenstore_buf->rsp[MASK_XENSTORE_IDX(i)];
		message++;
	}
	xenstore_buf->rsp_cons = i;
	return 0;
}

int strlnx(char *s)
{
        const char *sc;
        for (sc = s; *sc != '\0' && *sc != '\n' ; ++sc);
        return (int)(sc - s);
}


int xenstore_write(struct xenstore_domain_interface *xenstore_buf, EE_UINT32 store_evtchn, char *key, char *value)
{
	int key_length = strlnx(key);
	int value_length = strlnx(value);
	struct xsd_sockmsg msg;

	msg.type = XS_WRITE;
	msg.req_id = req_id;
	msg.tx_id = 0;
	msg.len = 1 + key_length + value_length;
	xenstore_write_request(xenstore_buf, (char *)&msg, sizeof(msg));
	/*
	 * NOTE: key must be null-terminated, but value
	 *       must NOT be null-terminated, or the
	 *       inserted value will include trailing
	 *       characters...
	 */
	xenstore_write_request(xenstore_buf, key, key_length + 1);
	xenstore_write_request(xenstore_buf, value, value_length);
	NOTIFY(store_evtchn);
	xenstore_read_response(xenstore_buf, (char *)&msg, sizeof(msg));
	IGNORE(xenstore_buf, msg.len);
	if (msg.req_id != req_id++)
		return -1;

	return 0;
}

int xenstore_read(struct xenstore_domain_interface *xenstore_buf, EE_UINT32 store_evtchn, char *key, char *value, int value_length)
{
	int key_length = strlnx(key);
	struct xsd_sockmsg msg;
	msg.type = XS_READ;
	msg.req_id = req_id;
	msg.tx_id = 0;
	msg.len = 1 + key_length;
	xenstore_write_request(xenstore_buf, (char *)&msg, sizeof(msg));
	xenstore_write_request(xenstore_buf, key, key_length + 1);
	NOTIFY(store_evtchn);
	xenstore_read_response(xenstore_buf, (char *)&msg, sizeof(msg));
	if (msg.req_id != req_id++) {
		IGNORE(xenstore_buf, msg.len);
		return -1;
	}
	if (value_length >= msg.len) {
		xenstore_read_response(xenstore_buf, value, msg.len);
		return 0;
	}
	xenstore_read_response(xenstore_buf, value, value_length);
	IGNORE(xenstore_buf, msg.len - value_length);
	return -2;
}

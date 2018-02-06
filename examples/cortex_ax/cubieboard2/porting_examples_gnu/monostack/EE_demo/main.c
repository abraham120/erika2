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

#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE 1
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

#define __EE_XEN_PV__
#ifdef __EE_XEN_PV__

#include "cpu/cortex_ax_xenpv/inc/xendebug.h"
#include "cpu/cortex_ax_xenpv/inc/xenincludes.h"
#include "cpu/cortex_ax_xenpv/inc/xenevents.h"
#include "cpu/cortex_ax_xenpv/inc/xengnttab.h"
#include "cpu/cortex_ax_xenpv/inc/hyper-calls.h"

void *dtb_global;
extern char _end;
shared_info_t *HYPERVISOR_shared_info;

void EE_Xen_map_shared(void)
{
	struct xen_add_to_physmap xatp;
	/* Map shared info page */
	xatp.domid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = virt_to_pfn(&shared_info);
	if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp) != 0)
		BUG();
	HYPERVISOR_shared_info = (struct shared_info *)&shared_info;
	printk("EE: shared info page mapped\n");
}

unsigned long start_pfn_p, max_pfn_p;

void EE_Xen_init_mm(void)
{
        start_pfn_p = (((unsigned long)&_end) >> PAGE_SHIFT) + 1000;
        max_pfn_p = ((unsigned long)&_end + PHYS_SIZE) >> PAGE_SHIFT;
	printk("EE: init mm\n");
}

#include "cpu/cortex_ax_xenpv/inc/gic.h"

static struct xenstore_domain_interface *xenstore_buf;
static uint32_t store_evtchn;

#include "cpu/cortex_ax_xenpv/inc/xenstore.h"

int task_state = 0;

void EE_xenbus_handler(evtchn_port_t port, struct pt_regs *regs, void *data)
{
	printk("EE: xenbus handler\n");
}

void EE_Xen_init_xenbus(void)
{
	arch_init_xenbus(&xenstore_buf, &store_evtchn);
	/*
	 * NOTE: evtchn must be unmasked even if we don't want to use it for
	 *       other than send operations.
	 */
	bind_evtchn(store_evtchn, EE_xenbus_handler, NULL);
	unmask_evtchn(store_evtchn);
	printk("EE: xenbus init\n");
}

#include "mcu/allwinner_a20/inc/gpio.h"

struct erika_idc_struct {
	int pin_number;
	int pin_value;
	int return_value;
};
extern char idc_page;
struct erika_idc_struct *idc_page_pointer;

int linux_idc_evtchn = 0;

int bind_to_interdomain_evtchn(int domid, int evtchn)
{
	struct evtchn_bind_interdomain op;
	int ret = 0;

	op.remote_dom = domid;
	op.remote_port = evtchn;
	ret = HYPERVISOR_event_channel_op(EVTCHNOP_bind_interdomain, &op);
	if (ret)
		return ret;
	linux_idc_evtchn = op.local_port;
	printk("EE: bound with Linux evtchn\n");

	return ret;
}

int notify_interdomain_evtchn(int port)
{
	struct evtchn_send send = { .port = port };
	return HYPERVISOR_event_channel_op(EVTCHNOP_send, &send);
}

int close_interdomain_evtchn(int port)
{
	struct evtchn_close op = { .port = port };
	int ret;

	ret = HYPERVISOR_event_channel_op(EVTCHNOP_close, &op);
	linux_idc_evtchn = 0;

	return ret;
}

void notify_back_Linux(void)
{
	char buffer[10];

	printk("EE: notifying back Linux\n");
	buffer[9] = '\0';

	xenstore_read(xenstore_buf, store_evtchn, "/local/linux_erika_evtchn", buffer, 9);
	if (bind_to_interdomain_evtchn(0, 7)) {
		printk("EE: error while binding to Linux\n");
		return;
	}
	unmask_evtchn(linux_idc_evtchn);
	notify_interdomain_evtchn(linux_idc_evtchn);
	close_interdomain_evtchn(linux_idc_evtchn);
}

void EE_Xen_idc_handler(evtchn_port_t port, struct pt_regs *regs, void *data)
{
	printk("EE: idc handler\n");
	print_number(idc_page_pointer->pin_number);
	print_number(idc_page_pointer->pin_value);
	gpio_cfg_pin(SUNXI_GPD(idc_page_pointer->pin_number), OUTPUT);
	if (idc_page_pointer->pin_value == 0) {
		printk("EE: setting pin to LOW\n");
		gpio_output(SUNXI_GPD(idc_page_pointer->pin_number), LOW);
	} else {
		printk("EE: setting pin to HIGH\n");
		gpio_output(SUNXI_GPD(idc_page_pointer->pin_number), HIGH);
	}
	idc_page_pointer->return_value = 0;

	notify_back_Linux();

	return;
}

#define IDC_REF			2

static evtchn_port_t erika_idc_port;

/* On how to bind channels: extras/mini-os/events.c */
void EE_Xen_init_idc(void)
{
	evtchn_alloc_unbound_t op;
	char port[10];

	op.dom = DOMID_SELF;
	op.remote_dom = 0;
	if (HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound, &op)) {
		printk("EE: ERROR: cannot alloc idc chan\n");
		return;
	}
	erika_idc_port = bind_evtchn(op.port, EE_Xen_idc_handler, &task_state);
	printk("EE: init idc\n");
	itoa(erika_idc_port, port);

	if (xenstore_write(xenstore_buf, store_evtchn, "/local/erika_task_evtchn", port) == -1)
		printk("EE: ERROR: xenstore_write\n");
	printk("EE: port advertised\n");

	/* Shared memory */
	gnttab_update_entry_v2(IDC_REF, 0, virt_to_pfn(&idc_page), 0);
	idc_page_pointer = (struct erika_idc_struct *)&idc_page;
	print_number(virt_to_pfn(&idc_page));

	printk("EE: memory page shared for idc\n");

	unmask_evtchn(erika_idc_port);
	printk("EE: unmask port\n");
}

void EE_Xen_Start(void)
{
	printk("EE: Xen start\n");
	EE_Xen_map_shared();
	EE_Xen_init_mm();
	gic_init();
	EE_Xen_init_xenbus();
	EE_Xen_init_gnttab();
	EE_Xen_init_idc();
}
#endif /*__EE_XEN_PV__*/

TASK(Hello_world_task)
{
#ifdef __EE_XEN_PV__
	printk("EE: task\n");
	gpio_cfg_pin(PD1, OUTPUT);
	printk("EE: task: GPIO configured\n");
	gpio_output(PD1, HIGH);
	printk("EE: task: GPIO pin high\n");
#endif /*__EE_XEN_PV__*/
}

/*
 * MAIN TASK
*/

/* The loop is OK */


void ErrorHook(StatusType Error)
{
    /*TODO*/
    return;
}

int main(void)
{
//    EE_serial_init();
#ifdef __EE_XEN_PV__
    printk("ERIKA Enterprise\n");
    EE_Xen_Start();
#endif /* __EE_XEN_PV__ */
    gpio_init();
#ifdef __EE_XEN_PV__
    printk("EE: GPIO initialized\n");
#endif /* __EE_XEN_PV__ */
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    StartOS(OSDEFAULTAPPMODE);

    ActivateTask(Hello_world_task);

    printk("EE: background activity\n");

    // Forever loop: background activities (if any) should go here
    for (;;);

    return 0;
}

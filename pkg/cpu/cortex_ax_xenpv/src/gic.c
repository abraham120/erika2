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
#include "cpu/cortex_ax_xenpv/inc/xendebug.h"
#include "cpu/cortex_ax_xenpv/inc/gic.h"

// ARM GIC implementation

extern unsigned long IRQ_handler;

struct gic {
	volatile char *gicd_base;
	volatile char *gicc_base;
};

static struct gic gic;

// Distributor Interface
#define GICD_CTLR		0x0
#define GICD_ISENABLER	0x100
#define GICD_PRIORITY	0x400
#define GICD_ITARGETSR	0x800
#define GICD_ICFGR		0xC00

// CPU Interface
#define GICC_CTLR	0x0
#define GICC_PMR	0x4
#define GICC_IAR	0xc
#define GICC_EOIR	0x10
#define GICC_HPPIR	0x18

#define gicd(gic, offset) ((gic)->gicd_base + (offset))
#define gicc(gic, offset) ((gic)->gicc_base + (offset))

#define REG(addr) ((EE_UINT32 *)(addr))

static inline EE_UINT32 REG_READ32(volatile EE_UINT32 *addr)
{
	EE_UINT32 value;
	__asm__ __volatile__("ldr %0, [%1]":"=&r"(value):"r"(addr));
	rmb();
	return value;
}

static inline void REG_WRITE32(volatile EE_UINT32 *addr, unsigned int value)
{
	__asm__ __volatile__("str %0, [%1]"::"r"(value), "r"(addr));
	wmb();
}

static void gic_set_priority(struct gic *gic, unsigned char irq_number, unsigned char priority)
{
	EE_UINT32 value;
	value = REG_READ32(REG(gicd(gic, GICD_PRIORITY)) + irq_number);
	value &= ~(0xff << (8 * (irq_number & 0x3))); // set priority to '0'
	value |= priority << (8 * (irq_number & 0x3)); // add our priority
	REG_WRITE32(REG(gicd(gic, GICD_PRIORITY)) + irq_number, value);
}

static void gic_route_interrupt(struct gic *gic, unsigned char irq_number, unsigned char cpu_set)
{
	EE_UINT32 value;
	value = REG_READ32(REG(gicd(gic, GICD_ITARGETSR)) + irq_number);
	value &= ~(0xff << (8 * (irq_number & 0x3))); // set priority to '0'
	value |= cpu_set << (8 * (irq_number & 0x3)); // add our priority
	REG_WRITE32(REG(gicd(gic, GICD_ITARGETSR)) + irq_number, value);
}

static void gic_enable_interrupt(struct gic *gic, unsigned char irq_number,
		unsigned char cpu_set, unsigned char level_sensitive, unsigned char ppi)
{
	void *set_enable_reg;
	void *cfg_reg;

	// set priority
	gic_set_priority(gic, irq_number, 0x0);

	// set target cpus for this interrupt
	gic_route_interrupt(gic, irq_number, cpu_set);

	// set level/edge triggered
	cfg_reg = (void *)gicd(gic, GICD_ICFGR);
	level_sensitive ? clear_bit((irq_number * 2) + 1, cfg_reg) : set_bit((irq_number * 2) + 1, cfg_reg);
	if(ppi)
		clear_bit((irq_number * 2), cfg_reg);

	wmb();

	// enable forwarding interrupt from distributor to cpu interface
	set_enable_reg = (void *)gicd(gic, GICD_ISENABLER);
	set_bit(irq_number, set_enable_reg);
	wmb();
}

static void gic_enable_interrupts(struct gic *gic)
{
	// Global enable forwarding interrupts from distributor to cpu interface
	REG_WRITE32(REG(gicd(gic, GICD_CTLR)), 0x00000001);

	// Global enable signalling of interrupt from the cpu interface
	REG_WRITE32(REG(gicc(gic, GICC_CTLR)), 0x00000001);
}

static void gic_disable_interrupts(struct gic *gic)
{
	// Global disable signalling of interrupt from the cpu interface
	REG_WRITE32(REG(gicc(gic, GICC_CTLR)), 0x00000000);

	// Global disable forwarding interrupts from distributor to cpu interface
	REG_WRITE32(REG(gicd(gic, GICD_CTLR)), 0x00000000);
}

static void gic_cpu_set_priority(struct gic *gic, char priority)
{
	REG_WRITE32(REG(gicc(gic, GICC_PMR)), priority & 0x000000FF);
}

static void gic_set_handler(unsigned long gic_handler) {
	IRQ_handler = gic_handler;
}

static unsigned long gic_readiar(struct gic *gic) {
	return REG_READ32(REG(gicc(gic, GICC_IAR))) & 0x000003FF; // Interrupt ID
}

static void gic_eoir(struct gic *gic, EE_UINT32 irq) {
	REG_WRITE32(REG(gicc(gic, GICC_EOIR)), irq & 0x000003FF);
}

#define EVENTS_IRQ 31
#define VIRTUALTIMER_IRQ 27
#define VTIMER_TICK 0x6000000
void timer_handler(evtchn_port_t port, struct pt_regs *regs, void *ign);
void increment_vtimer_compare(uint64_t inc);

int in_callback;

void do_hypervisor_callback(struct pt_regs *regs)
{
    unsigned long  l1, l2, l1i, l2i;
    unsigned int   port;
    int            cpu = 0;
    shared_info_t *s = HYPERVISOR_shared_info;
    vcpu_info_t   *vcpu_info = &s->vcpu_info[cpu];

    in_callback = 1;

    vcpu_info->evtchn_upcall_pending = 0;
    /* Clear master flag /before/ clearing selector flag. */
    wmb();
    l1 = xchg(&vcpu_info->evtchn_pending_sel, 0);
    while ( l1 != 0 )
    {
        l1i = __ffs(l1);
        l1 &= ~(1UL << l1i);

        while ( (l2 = active_evtchns(cpu, s, l1i)) != 0 )
        {
            l2i = __ffs(l2);
            l2 &= ~(1UL << l2i);

            port = (l1i * (sizeof(unsigned long) * 8)) + l2i;
			do_event(port, regs);
        }
    }

    in_callback = 0;
}

static void gic_handler(void) {
	unsigned int irq = gic_readiar(&gic);

	switch(irq) {
	case EVENTS_IRQ:
		do_hypervisor_callback(NULL);
		break;
	case VIRTUALTIMER_IRQ:
		timer_handler(0, NULL, 0);
		increment_vtimer_compare(VTIMER_TICK);
		break;
	default:
		printk("ERIKA: unknown GIC\n");
		break;
	}

	gic_eoir(&gic, irq);
}

void gic_init(void) {
	// FIXME Get from dt!
	gic.gicd_base = (char *)0x2c001000ULL;
	gic.gicc_base = (char *)0x2c002000ULL;
	wmb();

	gic_set_handler((unsigned long)gic_handler);

	gic_disable_interrupts(&gic);
	gic_cpu_set_priority(&gic, 0xff);
	gic_enable_interrupt(&gic, EVENTS_IRQ /* interrupt number */, 0x1 /*cpu_set*/, 1 /*level_sensitive*/, 0 /* ppi */);
	gic_enable_interrupt(&gic, VIRTUALTIMER_IRQ /* interrupt number */, 0x1 /*cpu_set*/, 1 /*level_sensitive*/, 1 /* ppi */);
	gic_enable_interrupts(&gic);

	printk("EE: GIC init\n");
}

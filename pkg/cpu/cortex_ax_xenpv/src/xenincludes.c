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

#include "cpu/cortex_ax_xenpv/inc/xenincludes.h"
#include "cpu/cortex_ax_xenpv/inc/xendebug.h"

static ev_action_t ev_actions[NR_EVS];
static unsigned long bound_ports[NR_EVS/(8*sizeof(unsigned long))];

int do_event(evtchn_port_t port, struct pt_regs *regs)
{
    ev_action_t  *action;

    clear_evtchn(port);

    if ( port >= NR_EVS ) {
        printk("EE: ERROR: do_event\n");
        return 1;
    }

    action = &ev_actions[port];
    action->count++;

    /* call the handler */
        action->handler(port, regs, action->data);

    return 1;
}

evtchn_port_t bind_evtchn(evtchn_port_t port, evtchn_handler_t handler,
                                                  void *data)
{
        ev_actions[port].data = data;
        wmb();
        ev_actions[port].handler = handler;
        set_bit(port, bound_ports);

        return port;
}

void timer_handler(evtchn_port_t port, struct pt_regs *regs, void *ign)
{
        printk("timer kick\n");
	/*get_time_values_from_xen();
        update_wallclock();*/
}

void increment_vtimer_compare(uint64_t inc) {
        uint32_t x, y;
        uint64_t value;
        __asm__ __volatile__("mrrc p15, 1, %0, %1, c14\n"
                        "isb":"=r"(x), "=r"(y));

        // CompareValue = Counter + VTIMER_TICK
        value = (0xFFFFFFFFFFFFFFFFULL & x) | ((0xFFFFFFFFFFFFFFFFULL & y) << 32);
        value += inc;
        x = 0xFFFFFFFFULL & value;
        y = (value >> 32) & 0xFFFFFFFF;

        __asm__ __volatile__("mcrr p15, 3, %0, %1, c14\n"
                        "isb"::"r"(x), "r"(y));

        __asm__ __volatile__("mov %0, #0x1\n"
                                "mcr p15, 0, %0, c14, c3, 1\n" /* Enable timer and unmask the output signal */
                                "isb":"=r"(x));
}

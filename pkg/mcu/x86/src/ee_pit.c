/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Author: 2014,  Martin Hoffmann
 * PIT (Programmable Interrupt Timer) implementation.
 */

#include "mcu/x86/inc/ee_pit.h"
#include "cpu/x86/inc/ee_irqstub.h"
#include "mcu/x86/inc/ee_ioport.h"
#include "mcu/x86/inc/ee_ioapic.h"

#ifdef DEBUG
#include "mcu/x86/inc/ee_uart.h"
#endif

/********************** Library function **************************/

#define PIT_RATE (1193180)
#define PIT_CHANNEL0_PORT (0x40)
#define PIT_COMMAND_PORT (0x43)

void EE_pit_set_periodic(EE_UINT16 rate){
    EE_UINT16 divisor = PIT_RATE / rate;

	// lo+hi byte, square wave generator mode
	outb(PIT_COMMAND_PORT, 0x36);
	io_wait();
	outb(PIT_CHANNEL0_PORT, divisor & 0xFF);
	io_wait();
	outb(PIT_CHANNEL0_PORT, divisor >> 8);

}

void EE_pit_init(void){
    EE_pit_set_periodic(1000); // generate interrupt @ 1 kHz

	// setup IRQ handler
	/* HACK:
	   The PIT is sometimes connected to pin 0 (Bochs),
	   and sometimes to pin 2 (QEMU) of the I/O APIC, so we setup both.
	   The real solution is to parse the multiprocessor tables for
	   redirection entries, but that would be *much* more work.

	   Alternative solution: unmask PIT interrupt (only!) in PIC and
	   use the LAPIC LINT0 handler.
	*/
    EE_ioapic_setup_irq(0, IRQ_PIT); // Bochs
    EE_ioapic_setup_irq(2, IRQ_PIT); // QEMU

}

__attribute__((weak)) void EE_pit_handler(void) {
#ifdef DEBUG
    printf("Timer!\n");
#endif
}

ISR2(IRQ_PIT) {
    EE_pit_handler();
}




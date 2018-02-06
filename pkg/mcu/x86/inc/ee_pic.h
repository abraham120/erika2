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
 * PIC (programmable interrupt controller) driver
 * Author: 2014,  Martin Hoffmann, FAU Erlangen
 */


#ifndef __INCLUDE__X86_PIC_H__
#define __INCLUDE__X86_PIC_H__

#include "ee.h"
#include "mcu/x86/inc/ee_ioport.h"

enum {
	PIC1 = 0x20, //!< IO base address for master PIC
	PIC2 = 0xA0, //!< IO base address for slave PIC
	PIC1_COMMAND = PIC1,
	PIC1_DATA = PIC1+1,
	PIC2_COMMAND = PIC2,
	PIC2_DATA = PIC2+1,
	PIC_EOI = 0x20, //!< End-of-interrupt command code
	PIC_OFFSET = 0x30 //!< Vector (offset) of first PIC interrupt
};


/** \brief Remap PIC interrupt vectors
 *
 * reinitialize the PIC controllers, giving them specified vector offsets
 * rather than 0x08 and 0x70, as configured by default
 *
 * \param offset1 vector offset for master PIC (offset1..offset1+7)
 * \param offset2 vector offset for for slave PIC (offset2..offset2+7)
 */
__INLINE__ void __ALWAYS_INLINE__ EE_pic_remap(EE_UINT8 offset1, EE_UINT8 offset2) {
	// save masks
	EE_UINT8 mask1 = inb(PIC1_DATA);
	EE_UINT8 mask2 = inb(PIC2_DATA);

	// start the initialization sequence (in cascade mode)
	outb(PIC1_COMMAND, 0x11);
	io_wait();
	outb(PIC2_COMMAND, 0x11);
	io_wait();

	// set vector offsets
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();

	// tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC1_DATA, 4);
	io_wait();
	// tell Slave PIC its cascade identity (0000 0010)
	outb(PIC2_DATA, 2);
	io_wait();

	// set 8086/88 (MCS-80/85) mode
	outb(PIC1_DATA, 0x01);
	io_wait();
	outb(PIC2_DATA, 0x01);
	io_wait();

	// restore masks
	outb(PIC1_DATA, mask1);
	outb(PIC2_DATA, mask2);

}

/** \brief Initialize the PIC */
__INLINE__ void __ALWAYS_INLINE__ EE_pic_init(void) {
	// remap interrupts to avoid conflicts
	EE_pic_remap(PIC_OFFSET, PIC_OFFSET+8);
}


/** \brief Disable interrupt delivery from PIC */
__INLINE__ void __ALWAYS_INLINE__ EE_pic_disable(void) {
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}

/** \brief Send end-of-interrupt signal
 *
 * \param irq Acknowledged IRQ number (original, not remapped value)
 */
__INLINE__ void __ALWAYS_INLINE__ EE_pic_sendEOI(EE_UINT8 irq) {
	if(irq >= 8)
		outb(PIC2_COMMAND, PIC_EOI); // PIC2 Command

	outb(PIC1_COMMAND, PIC_EOI); // PIC1 Command
}



#endif

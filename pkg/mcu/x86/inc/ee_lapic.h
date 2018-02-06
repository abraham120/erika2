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
 * LAPIC driver
 * Author: 2014,  Martin Hoffmann, FAU Erlangen
 */


#ifndef __INCLUDE__X86_LAPIC_H__
#define __INCLUDE__X86_LAPIC_H__

#include "ee.h"
#include "mcu/x86/inc/ee_ioport.h"

#include "mcu/x86/inc/ee_pic.h"

enum EE_x86_lapic_regs {
	BASE = 0xFEE00000, //!< base address for LAPIC
	ID = BASE + 0x020, //!< local APIC ID register
	SINT = BASE + 0x0F0, //!< spurious interrupt register
	TPR = BASE + 0x080, //!< task priority register
	PPR = BASE + 0x0A0, //!< processor priority register
	EOI = BASE + 0x0B0, //!< end-of-interrupt register
	IRR = BASE + 0x200,
	ISRREG = BASE + 0x100,
	ICR_LO = BASE + 0x0300, //!< interrupt control register, bits 0-31
	ICR_HI = BASE + 0x0310, //!< interrupt control register, bits 32-63
};


__INLINE__ void __ALWAYS_INLINE__ lapic_write_reg(EE_UINT32 reg, EE_UINT32 val) {
		*((volatile EE_UINT32*) reg) = val;
}

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ lapic_read_reg(EE_UINT32 reg) {
	return *((volatile EE_UINT32*) reg);
}


__INLINE__ void __ALWAYS_INLINE__ EE_lapic_enable(void) {
	EE_UINT32 val = lapic_read_reg(SINT);
	val |= 0x100; // enable APIC bit
	lapic_write_reg(SINT, val);
}

/** \brief Send end-of-interrupt signal */
__INLINE__ void __ALWAYS_INLINE__ EE_lapic_send_eoi(void) {
	lapic_write_reg(EOI, 0);
}

/** \brief Return local APIC ID */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_lapic_get_id(void) {
	return lapic_read_reg(ID);
}


/** \brief Return interrupt request register */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_lapic_get_irr(EE_UINT8 offset) {
	return lapic_read_reg((IRR + (offset)*0x10));
}


/** \brief Return interrupt service register */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_lapic_get_isr(EE_UINT8 offset) {
	return lapic_read_reg((ISRREG + (offset)*0x10));
}

/** \brief Set task priority
 *
 * This will block all IRQ vectors lower than the given priority.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_lapic_set_int_prio(EE_TYPEISR2PRIO prio) {
	lapic_write_reg(TPR, prio);
}


/** \brief Return task priority */
__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_lapic_get_int_prio(void) {
	return lapic_read_reg(TPR);
}

/** \brief Trigger interrupt vector */
__INLINE__ void __ALWAYS_INLINE__ EE_lapic_trigger(EE_UINT8 vector) {
	// write interrupt vector
	// fixed delivery mode
	// physical destination mode
	// assert level
	// destination shorthand: self
	lapic_write_reg(ICR_LO, (1 << 18) | (1<<14) | vector);
}

/** \brief Initialize the LAPIC and disable the PIC */
__INLINE__ void __ALWAYS_INLINE__ EE_lapic_init(void) {
    EE_lapic_enable();

    EE_pic_disable();
}



#endif

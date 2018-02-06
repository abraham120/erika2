
#include "mcu/x86/inc/ee_ioapic.h"

enum ioapic_regs {
    IOREGSEL = 0xFEC00000, // base address for IOAPIC
    IOWIN    = IOREGSEL + 0x10, // register select register
    IOREDTBL = 0x10 // start of I/O redirection table
};


static inline void ioapic_write_reg(EE_UINT8 reg, EE_UINT32 val) {
		*((volatile EE_UINT32*) IOREGSEL) = reg;
		*((volatile EE_UINT32*) IOWIN) = val;
}

static inline EE_UINT32 ioapic_read_reg(EE_UINT8 reg) {
	*((volatile EE_UINT32*) IOREGSEL) = reg;
	return *((volatile EE_UINT32*) IOWIN);
}


void EE_ioapic_init(void) {

}

void EE_ioapic_setup_irq(EE_UINT8 pin, EE_UINT8 vector) {
    EE_ioapic_setup_irq_extended(pin, vector, FIXED, 0);
}


void EE_ioapic_setup_irq_extended(EE_UINT8 pin, EE_UINT8 vector, enum ee_ioapic_delivery_mode delivery_mode, EE_UINT8 active_low) {
    EE_UINT8 reg_lo = IOREDTBL + pin*2;

    ioapic_write_reg(reg_lo, (active_low << 13) | (delivery_mode << 8) | vector);
}



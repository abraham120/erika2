//#include "mcu/x86/inc/ee_pic.h"

#if 0
void EE_pic_init(void) {
	// remap interrupts to avoid conflicts
	EE_pic_remap(PIC_OFFSET, PIC_OFFSET+8);
}

void EE_pic_remap(EE_UINT8 offset1, EE_UINT8 offset2) {
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

void EE_pic_disable() {
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}

#endif

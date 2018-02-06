#include "mcu/x86/inc/ee_mcu.h"


void EE_mcu_x86_init() {

    EE_gdt_init();
    EE_idt_init();

    EE_pic_init();

    EE_lapic_init();

    EE_ioapic_init();
//TODO reenable
//    EE_pit_init();
}

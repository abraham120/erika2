#ifndef _HYPER_ARM_32_H_
#define _HYPER_ARM_32_H_

#define __HYPERVISOR_set_callbacks			4
#define __HYPERVISOR_memory_op				12
#define __HYPERVISOR_console_io				18
#define __HYPERVISOR_grant_table_op			20
#define __HYPERVISOR_sched_op				29
#define __HYPERVISOR_event_channel_op			32
#define __HYPERVISOR_hvm_op				34

#define __HVC(imm16) .long ((0xE1400070 | (((imm16) & 0xFFF0) << 4) | ((imm16) & 0x000F)) & 0xFFFFFFFF)

#define XEN_IMM						0xEA1

#define HYPERCALL_SIMPLE(hypercall)			\
	.globl HYPERVISOR_##hypercall;			\
	.align 4,0x90;					\
	HYPERVISOR_##hypercall:				\
		mov r12, #__HYPERVISOR_##hypercall;	\
		__HVC(XEN_IMM);				\
		mov pc, lr;

#define _hypercall2 HYPERCALL_SIMPLE
#define _hypercall3 HYPERCALL_SIMPLE

_hypercall2(memory_op);
_hypercall2(hvm_op);
_hypercall2(event_channel_op);
_hypercall2(sched_op);
_hypercall3(console_io);
_hypercall3(set_callbacks);
_hypercall3(grant_table_op);

#endif /*_HYPER_ARM_32_H_*/

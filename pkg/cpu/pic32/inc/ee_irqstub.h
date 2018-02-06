#ifndef __INCLUDE_PIC32_EE_IRQSTUB_H__
#define __INCLUDE_PIC32_EE_IRQSTUB_H__

#include "eecfg.h"
#include "cpu/pic32/inc/ee_compiler.h"

/* from ee_internal.h */
extern EE_ADDR EE_hal_endcycle_next_thread;
extern EE_UREG EE_IRQ_nesting_level;
#ifdef __MULTI__
extern EE_UREG EE_hal_endcycle_next_tos;
#endif
#ifdef __IRQ_STACK_NEEDED__
extern EE_ADDR EE_pic32_temp_tos;
#endif

void EE_IRQ_end_instance(void);
#ifdef __MONO__
void EE_pic32_hal_ready2stacked(EE_ADDR thread_addr);
#endif
#ifdef __MULTI__
void EE_pic32_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index);
void EE_pic32_hal_stkchange(EE_UREG tos_index);
#endif

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_prestub(void)
{
	EE_pic32_disableIRQ();
	#ifdef __ALLOW_NESTED_IRQ__
	EE_IRQ_nesting_level++;
	#ifdef __MULTI__
	#ifdef __IRQ_STACK_NEEDED__
	if (EE_IRQ_nesting_level == 1) {
		asm volatile ("sw $sp,%gp_rel(EE_pic32_temp_tos)($gp)");
		/* chris: TODO: This leads to a 3 assembly instruction code to
		load the SP register: first load the value in a temporary
		register then move it in the SP. The code can be changed to a  
		two assembly instructions version where instead of using the
		temporary register the value is immediately loaded in SP. 
		This cannot be done in C, we need asm for that like the 
		following one where passing EE_PIC32_IRQ_TOS is invalid. */
		register EE_ADDR tmp = EE_PIC32_IRQ_TOS;
		asm volatile ("addu $sp,$zero,%0" : "+r"(tmp));
		//asm volatile ("lui $sp,%hi(EE_PIC32_IRQ_TOS)");
		//asm volatile ("addiu $sp,%lo(EE_PIC32_IRQ_TOS)");
	}
	#endif /* __IRQ_STACK_NEEDED__ */
	#endif /* __MULTI__ */
	EE_pic32_enableIRQ();
	#else /* not __ALLOW_NESTED_IRQ__ */
	EE_IRQ_nesting_level = 1;
	#endif /* __ALLOW_NESTED_IRQ__ */
}

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void)
{
	#ifdef __ALLOW_NESTED_IRQ__
	EE_pic32_disableIRQ();
	EE_IRQ_nesting_level--;
	if (EE_IRQ_nesting_level != 0) {
		EE_pic32_enableIRQ();
		return;
	}
	#ifdef __MULTI__
	#ifdef __IRQ_STACK_NEEDED__
	asm volatile ("lw $sp,%gp_rel(EE_pic32_temp_tos)($gp)");
	#endif /* __MULTI__ */
	#endif /* __IRQ_STACK_NEEDED__ */
	#else /* not __ALLOW_NESTED_IRQ__ */
	EE_IRQ_nesting_level = 0;
	#endif /* __ALLOW_NESTED_IRQ__ */
	EE_IRQ_end_instance();
	if (EE_hal_endcycle_next_thread) {
		/* enable interrupts and set the CPU priority level to 0
		 before calling the thread that MUST be interruptable.
		NOTE: the interrupt enable is performed in ready2stacked. */
		register EE_UREG tmp;
		asm volatile (	"mfc0 %0, $12\n\t"
				"ins %0, $zero, 10, 6\n\t" 
				"mtc0 %0, $12\n\t" 
				: "=r"(tmp));
		#ifdef __MONO__
		EE_pic32_hal_ready2stacked(EE_hal_endcycle_next_thread);
		#endif
		#ifdef __MULTI__
		EE_pic32_hal_ready2stacked(EE_hal_endcycle_next_thread, 
					   EE_hal_endcycle_next_tos);
		#endif
	#ifdef __MULTI__
	} else if (EE_hal_endcycle_next_tos != EE_pic32_active_tos) {
		/* Set the CPU priority level to 0 before calling the thread 
		that MUST be interruptable.
		NOTE: the interrupt MUST be disabled because this 
		function does not jump actually to the stacked thread
		but to a kernel section that has to run with disabled
		interrupt and that will manage to enable them before 
		jumping to the actual thread code. */
		register EE_UREG tmp;
		asm volatile (	"mfc0 %0, $12\n\t"
				"ins %0, $zero, 10, 6\n\t" 
				"mtc0 %0, $12\n\t" 
				: "=r"(tmp));
		EE_pic32_hal_stkchange(EE_hal_endcycle_next_tos);
	#endif /* __MULTI__ */
	}
	EE_pic32_enableIRQ();
}

/* chris: TODO: check this. Is the ISR installation valid? 
*               Is 'vector' ok? should be 'at_vector' ? */
#define ISR2(f) \
void ISR2_##f(void); \
void __attribute__((interrupt(ipl6))) \
     __attribute__((vector(f))) isr_##f(void) \
{ \
	EE_ISR2_prestub(); \
	ISR2_##f(); \
	EE_ISR2_poststub(); \
} \
void ISR2_##f(void)
  
/* chris: TODO: In future we may solve the problem of the private IRQ stack size
that happens when the compiler automatically save the current context (112Bytes)
of the interrupted thread. We can install the handler without the compiler 
stub (see code below) and use an assemply stub that switches to the common 
stack (or the ISR private) before saving the context of the interrupted 
thread. */
//void __attribute__((vector(f))) isr_##f(void)

/* The effect of this is: 
   - CPU with max priority and Interrupt Disable 
   - The Shadow Set usage is NOT driven by this, but we need regs IPCx = 7 
*/
#define ISR1(f) \
void __attribute__((interrupt(ipl7))) \
     __attribute__((vector(f))) isr1_##f(void) 
 

#endif

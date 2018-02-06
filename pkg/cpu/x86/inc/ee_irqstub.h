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
 * Interrupt descriptor table (IDT)
 * Author: 2014,  Martin Hoffmann, FAU Erlangen
 */


#ifndef __INCLUDE__X86_EE_IRQSTUB_H__
#define __INCLUDE__X86_EE_IRQSTUB_H__


/* Use angled parenthesis to include the main "ee_internal.h" */
//#include "cpu/x86/inc/ee_context.h"
#include "cpu/x86/inc/ee_cpu.h"
#include "cpu/common/inc/ee_context.h"
#include "cpu/common/inc/ee_irqstub.h"
#include "mcu/x86/inc/ee_lapic.h"

/** \brief Context saved by CPU on interrupt/trap/syscall */
struct cpu_context {
	EE_UINT32 error_code; //!< error code (dummy value if unused)

	EE_UINT32 eip; //!< source address
	EE_UINT32 cs; //!< source code segment selector

	EE_UINT32 eflags; //!< original flags

	// only pushed when coming from ring>0:
	EE_UINT32 user_esp; //!< userspace stack pointer
	EE_UINT32 ss; //!< userspace stack segment selector
} __attribute__((packed));

/** \brief Application (task) context (saved by IRQ handlers) */
struct task_context {
	EE_UINT32 edi, esi, ebp, esp, ebx;
	EE_UINT32 edx, ecx, eax;
} __attribute__((packed));


/* as placed by the isr handler entry */
struct irq_context  {
    struct task_context task;
    struct cpu_context  cpu;
} __attribute__((packed));


void EE_idt_init(void);

/**
 * @name IRQ numbers
 * @{
 */
#define IRQ_SYSCALL 34 //!< syscall software interrupt
#define IRQ_RESCHEDULE 33 //!< reschedule (AST) software interrupt
#define IRQ_DISPATCH 32 //!< dispatcher (AST) software interrupt
#define IRQ_PIT 48 //!< programmable interval timer interrupt
/**@}*/

#ifdef __ALLOW_NESTED_IRQ__

#define EE_std_enableIRQ_nested() EE_x86_enableIRQ()
#define EE_std_disableIRQ_nested() EE_x86_disableIRQ()

#else	/* else __ALLOW_NESTED_IRQ__*/

#define EE_std_enableIRQ_nested() ((void)0)
#define EE_std_disableIRQ_nested() ((void)0)

#endif /* end __ALLOW_NESTED_IRQ__*/

#if defined(__MULTI__) && defined(__IRQ_STACK_NEEDED__)

extern	void EE_x86_IRQ_change_stack( void );
extern	void EE_x86_IRQ_stack_back( void );

extern EE_UREG EE_x86_tmp_tos;
extern struct EE_TOS EE_x86_IRQ_tos;
/*save the stack pointer*/ /*Load new stack pointer*/
#define EE_std_change_stack()\
do {\
	if(EE_IRQ_nesting_level==1) {\
	 asm volatile ("mov %%esp,%0\r\n" \
                  "mov %1, %%esp\r\n" \
                    : "=m" (EE_x86_tmp_tos) \
                    : "m"  (EE_x86_IRQ_tos) ); \
	}\
} while(0)

#define EE_std_stack_back() asm volatile ("mov %0, %%esp\r\n" : : "m" \
                                                    (EE_x86_tmp_tos));

#else	/* else __MULTI__ && __IRQ_STACK_NEEDED__*/

#define EE_std_change_stack() ((void)0)
#define EE_std_stack_back() ((void)0)

#endif	/* end __MULTI__ && __IRQ_STACK_NEEDED__*/

extern EE_UREG	EE_x86_change_context_active;


__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_prestub(void) {

    /* Increment nesting level here, with IRQs are disabled */
    EE_increment_IRQ_nesting_level();

    /* if IRQ stack enabled */
    EE_std_change_stack();

    /* enable IRQ if nesting is allowed */
    EE_std_enableIRQ_nested();
}

__INLINE__ void __ALWAYS_INLINE__ EE_lapic_send_eoi(void) ;

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void) {

    EE_std_disableIRQ_nested();

    EE_std_end_IRQ_post_stub();

    EE_decrement_IRQ_nesting_level();

    if ( EE_IRQ_nesting_level == 0 ) {
      EE_std_stack_back();
      EE_std_after_IRQ_schedule();
    }

    EE_lapic_send_eoi();

    EE_hal_enableIRQ();
}

/**
 * @name IRQ handler macros
 *
 * To define an interrupt handler after the context has been saved use the
 * ISR2.
 * To define an interrupt handler without context saving or stack
 * adjustments use the ISR1 macro. Take care to save and restore
 * registers and stack before usage!
 * @{
 */

/** \brief Define a free-standing interrupt handler
 *
 * This code will be jumped to directly when the interrupt occurs.
 * No context saving or stack adjustment is performed!
 * Return from interrupt and other things have to be implemented manually.
 * This invokes just a naked function. Use this only if you really know what
 * you are doing.
 *
 * \param irqno IRQ number
 */
#define ISR1(f)			\
    IRQ_HANDLER(f)


/** ISR2 boilerplate code **/
#define ISR2IMPL(irqnum)			\
__INLINE__ void __ALWAYS_INLINE__ isr_impl_ ## irqnum(EE_UINT32 vector, struct irq_context ctx);		\
void isr_ ## irqnum(EE_UINT32 vector, struct irq_context ctx) \
{				\
	EE_ISR2_prestub();	\
    (void)vector; (void)ctx; \
	isr_impl_ ## irqnum(vector, ctx);		\
	EE_ISR2_poststub();	\
}				\
__INLINE__ void __ALWAYS_INLINE__ isr_impl_ ## irqnum(EE_UINT32 vector, struct irq_context ctx)

/* Standard Macro to declare an ISR2 */
#define ISR2(f) ISR2IMPL(f)

#define IRQ_HANDLER(irqno) IRQ_HNDLR(irqno)

/** \brief Define a free-standing interrupt handler
 *
 * This helper macro is needed to allow macro expansion for the argument
 * of the IRQ_HANDLER macro.
 * \see IRQ_HANDLER
 *
 * \internal
 */
#define IRQ_HNDLR(irqno) \
	extern  __attribute__((naked)) void irq_handler_ ## irqno (void)


#endif

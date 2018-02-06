#include "cpu/pic32/inc/ee_cpu.h"

#ifndef __INCLUDE_PIC32_INTERNAL_H__
#define __INCLUDE_PIC32_INTERNAL_H__

/*
 * Generic Primitives
 */

/* called as _first_ function of a primitive that can be called into
   an IRQ and into a task */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
	register EE_FREG irq_enabled;
	
	asm volatile (	"mfc0 %0, $12\n\t" : "=r"(irq_enabled));
	irq_enabled &= 0x1; /* chris: Do I need to check IE, EXL, ERL, DM? */
	EE_hal_disableIRQ();
	return !irq_enabled;
}

/* called as _last_ function of a primitive that can be called into
   an IRQ and into a task */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
	if (f) 
		EE_hal_disableIRQ();
	else
		EE_hal_enableIRQ();
}

/* 
 * Context Handling  
 */

extern EE_ADDR EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;

/* typically called into a generic primitive to implement preemption */
/* NOTE: pic32_thread_tos[0]=dummy, pic32_thread_tos[1]=thread0, ... */
#ifdef __MONO__
void EE_pic32_hal_ready2stacked(EE_ADDR thread_addr); /*ASM*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
	EE_pic32_hal_ready2stacked(EE_hal_thread_body[thread]);
}
#endif
#ifdef __MULTI__
void EE_pic32_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index); /*ASM*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
	EE_pic32_hal_ready2stacked(EE_hal_thread_body[thread],
				   EE_pic32_thread_tos[thread + 1]);
}
#endif


/* typically called at the end of a thread instance */
#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
	EE_hal_endcycle_next_thread = 0;
	/* TID is useless */
}
#endif
#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
	EE_hal_endcycle_next_tos = EE_pic32_thread_tos[thread + 1];
	EE_hal_endcycle_next_thread = 0;
}
#endif



#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
  EE_hal_endcycle_next_thread = EE_hal_thread_body[thread];
}
#endif
#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
	EE_hal_endcycle_next_tos = EE_pic32_thread_tos[thread+1];
	EE_hal_endcycle_next_thread = EE_hal_thread_body[thread];
}
#endif

/* typically called at the end of an interrupt */
#define EE_hal_IRQ_stacked EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready EE_hal_endcycle_ready

/* called to change the active stack, typically inside blocking primitives */
/* there is no mono version for this primitive...*/
#ifdef __MULTI__
void EE_pic32_hal_stkchange(EE_UREG tos_index); /* in ASM */

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread)
{
	EE_pic32_hal_stkchange(EE_pic32_thread_tos[thread+1]);
}
#endif

/*
 * Nested Interrupts Handling
 */

/* can be called with interrupt enabled */
extern EE_UREG EE_IRQ_nesting_level;

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
	return EE_IRQ_nesting_level;
}

/* 
 * OO TerminateTask related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)
void EE_pic32_terminate_savestk(EE_ADDR sp, EE_ADDR realbody); /*ASM*/
void EE_pic32_terminate_task(EE_ADDR sp) NORETURN; /*ASM*/

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{
	EE_pic32_terminate_savestk(&EE_terminate_data[t],
				   (EE_ADDR)EE_terminate_real_th_body[t]);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
	EE_pic32_terminate_task(&EE_terminate_data[t]);
}

#endif 
#endif

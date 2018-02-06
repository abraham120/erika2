/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, Pebble Bay Consulting Ltd.
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

/* Author: Steve Langstaff, Pebble Bay Consulting Ltd, 2010
 *
 */

#include "ee_internal.h"
#include "cpu/common/inc/ee_irqstub.h"

#ifdef  __MULTI__
extern void EE_esi_change_context(EE_TID tid);
#endif

#ifdef __IRQ_STACK_NEEDED__

/* EE_std_IRQ_tos is the top of stack structure defined in eecfg.c */
extern struct EE_TOS EE_std_IRQ_tos;

/* EE_isr_stack_temp holds the old stack pointer when using the ISR stack */
unsigned int EE_isr_stack_temp;

/* EE_isr_stack_swap_and_call() is implemented in assembler */
extern void EE_isr_stack_swap_and_call(void (*handler)(void), EE_ADDR isr_tos);

#endif

/* EE_isr_low_level_handler() is implemented in assembler */
extern void EE_isr_low_level_handler(void);

static void (*handler_table[__interrupts__])(void);

void install_irq_handler(int irq, void (*handler)(void))
{
    esi_exception_table_t *exception_table = esi_exception_get_exception_table();
    exception_table->interrupt[irq] = EE_isr_low_level_handler;
    handler_table[irq] = handler;
}

/* EE_isr_high_level_handler() is called by the EE_isr_low_level_handler() */
void EE_isr_high_level_handler(void)
{
	unsigned int pending = esi_interrupt_get_pending();
	unsigned int mask = esi_interrupt_get_mask();
	int irq;
	void (*handler)(void);

	/* look for the highest priority enabled pending interrupt */
#if	__ffs_enabled__
	irq = ffs(pending & mask);
	/* if irq is zero it means we have no enabled pending interrupts! */
	if (irq == 0)
	{
		//puts("ERROR: Spurious interrupt");
		return;
	}
	/* decrement irq because the handler_table is indexed from zero */
	--irq;
#else
	{
		unsigned int enabled = pending & mask;
		mask = 1;
		for (irq = 0; irq < __interrupts__; ++irq)
		{
			if (enabled & mask)
			{
				break;
			}
			mask = mask << 1;
		}
		/* if we have reached the end of the for loop without seeing the irq */
		if (irq == __interrupts__)
		{
			//puts("ERROR: Spurious interrupt");
			return;
		}
	}
#endif

	handler = handler_table[irq];

	/* call the ISR */
	if (handler)
	{
		int inside = EE_is_inside_ISR_call();
		EE_increment_IRQ_nesting_level();

#ifdef __IRQ_STACK_NEEDED__
		/* if this not nested, or is the outermost of a nested set of interrupts
		 * we should swap to the interrupt stack before calling the handler
		 */
		if (!inside)
		{
			EE_isr_stack_swap_and_call(handler, EE_std_IRQ_tos.SYS_tos);
		}
		else
		{
			(*handler)();
		}
#else
		(*handler)();
#endif
#ifdef __ALLOW_NESTED_IRQ__
		/* ISR may have enabled interrupts, so let's disable them before we fiddle
		 * with the nesting level
		 */
		esi_interrupt_disable();
#endif
		EE_decrement_IRQ_nesting_level();
		if (!inside)
		{
			EE_std_after_IRQ_schedule();
		}
	}
	else
	{
		//puts("ERROR: Missing ISR");
	}
}

#ifdef	__MULTI__
void EE_std_change_context(EE_TID tid)
{
#ifdef	DEBUG_TASK_SWITCH
	EE_UREG tos_index = EE_std_thread_tos[(tid&0x7FFFFFFF)+1];
	EE_ADDR				sp;

	iprintf("%s: tid=0x%08x tos_index=%d active_tos=%d stacked=%d\n",
			__FUNCTION__,
			tid,
			tos_index,
			EE_std_active_tos,
			(tid&0x80000000)?1:0);

	sp = EE_std_system_tos[EE_std_active_tos].SYS_tos;
	iprintf("%s: active sp=%x\n", __FUNCTION__, sp);

	sp = EE_std_system_tos[tos_index].SYS_tos;
	iprintf("%s: new    sp=%x\n", __FUNCTION__, sp);
#endif

	/* It is important to stop this function from being inlined,
	 * as the stack use has to be consistent between the different callers of
	 * EE_esi_change_context() - if this is not done then it has been observed
	 * that some calls to EE_std_change_context() are replaced by direct calls
	 * to EE_esi_change_context() and some are not. The stack is slightly
	 * different in these cases which leads to segmentation violations on
	 * context change.
	 */
	asm ("");	/* special magic to stop this function from being inlined */

	EE_esi_change_context(tid);
}

extern struct EE_TOS EE_std_system_tos[];

/* _user_init function is called before main */
void _user_init(void)
{
	int	i;
	int	max_stacks=0;

	/* find number of stacks in use */
	for (i=0;i<=EE_MAX_TASK;++i)
	{
		if (EE_std_thread_tos[i] > max_stacks)
		{
			max_stacks = EE_std_thread_tos[i];
		}
	}

	/* TODO: Here might be a good place to do any per-stack reentrancy
	 * structure manipulation.
	 */

	/* setup top of stacks according to our preferences for register saving */
	for (i=0;i<=max_stacks;++i)
	{
		if (EE_std_system_tos[i].SYS_tos != 0)
		{
			EE_std_system_tos[i].SYS_tos -= __registers__;
		}
	}
}
#endif



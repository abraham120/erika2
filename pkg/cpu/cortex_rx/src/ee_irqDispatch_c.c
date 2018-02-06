/** @file  irqDispatch_c.c
 *  @brief contains Second Level IRQ Dispatcher C routine
 *  @date  9/13/2012
 *  @note  
 */

#include "ee.h"
#include "../contrib/ti_tms570/include/sys_vim.h"


typedef volatile struct vimRam
{
    t_isrFuncPTR ISR[VIM_CHANNELS + 1];
} vimRAM_t;

#define vimRAM ((vimRAM_t *)0xFFF82000U)


/** @def   MAX_NESTING_LEVEL
 *  @brief Defines max nesting deep
 *  @note
 */

#define MAX_NESTING_LEVEL 4


/** @fn    void C_irqDispatch(void)
 *  @brief Second Level IRQ Dispatcher C routine
 *  @note  This implementation is limited to the use of the first 96 interrupt priority's.
 */

#pragma CODE_STATE(C_irqDispatch, 32);
#pragma FUNC_EXT_CALLED(C_irqDispatch);
void C_irqDispatch(void)
{
	EE_UINT32 u32IrqIndex                     = vimREG->IRQINDEX; /* Read IRQ Index Offset Vector */
	/** @NOTE IRQIVEC is zero if no interrupt is pending */

	t_isrFuncPTR irq_func_pnt              = vimRAM->ISR[u32IrqIndex]; /* Read IRQ Interrupt Vector */
	static volatile sint32 s32NestingLevel = 0;

	if (0U == u32IrqIndex)
	{
		/* Phantom Interrupt */

		/** @TODO Add custom fault handler, if necessary. */
		while(1);
	}
	else
	{
		/* Increment Nesting Level indicator */
		s32NestingLevel++;

		/* If Nesting Level indicator is less than the max level, enable IRQ to allow further preemption */
		if ((MAX_NESTING_LEVEL) > s32NestingLevel)
		{
			/* Stack VIM REQENASET[0,1,2] Registers for later restore */
			EE_UINT32 SaveREQMASKSET0 = vimREG->REQMASKSET0;
			EE_UINT32 SaveREQMASKSET1 = vimREG->REQMASKSET1;
			EE_UINT32 SaveREQMASKSET2 = vimREG->REQMASKSET2;
			/* t32 SaveREQMASKSET3 = vimREG->REQMASKSET3; Not applicable for RM48L */

			/* Mask out lower priority IRQ's and the current IRQ itself, keep FIQ's enabled */

			if (96U < u32IrqIndex) /* 96-...*/
			{
				/** @NOTE Current VIM implementations only support up to 96 channels. */
				/** @TODO Add custom fault handler, if necessary. */
				while (1); /* Fault */

				/* REG->REQMASKCLR0 = ( 0xFFFFFFFCU                         & (~vimREG->FIRQPR0)); Higher priority */
				/* REG->REQMASKCLR1 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR1)); Higher priority */
				/* REG->REQMASKCLR2 = ((0xFFFFFFFFU                         & (~vimREG->FIRQPR2)); Higher priority */
				/* REG->REQMASKCLR3 = ( 0xFFFFFFFFU << (u32IrqIndex - 97U)) & (~vimREG->FIRQPR3)); */

			}
			else if (64U < u32IrqIndex) /* 64-96 */
			{
				/* REG->REQMASKCLR0 = ( 0xFFFFFFFCU                         & (~vimREG->FIRQPR0)); Higher priority */
				/* REG->REQMASKCLR1 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR1)); Higher priority */
				vimREG->REQMASKCLR2 = ((0xFFFFFFFFU << (u32IrqIndex - 65U)) & (~vimREG->FIRQPR2));
				/* REG->REQMASKCLR3 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR3)); Not applicable for RM48L */

				vimREG->REQMASKCLR2; /* Readback Mask to ensure that the previous write was finished before enabling interrupts again */
			}
			else if (32U < u32IrqIndex) /* 32-63 */
			{
				/* REG->REQMASKCLR0 = ( 0xFFFFFFFCU                         & (~vimREG->FIRQPR0)); Higher priority */
				vimREG->REQMASKCLR1 = ((0xFFFFFFFFU << (u32IrqIndex - 33U)) & (~vimREG->FIRQPR1));
				vimREG->REQMASKCLR2 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR2));
				/* REG->REQMASKCLR3 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR3)); Not applicable for RM48L */

				vimREG->REQMASKCLR1; /* Readback Mask to ensure that the previous write was finished before enabling interrupts again */
			}
			else if ( 2U < u32IrqIndex) /*  2-31 */
			{

				vimREG->REQMASKCLR0 = ((0xFFFFFFFFU << (u32IrqIndex -  1U)) & (~vimREG->FIRQPR0));
				vimREG->REQMASKCLR1 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR1));
				vimREG->REQMASKCLR2 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR2));
				/* REG->REQMASKCLR3 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR3)); Not applicable for RM48L */

				vimREG->REQMASKCLR0; /* Readback Mask to ensure that the previous write was finished before enabling interrupts again */
			}
			else /* if (0U < u32IrqIndex) */ /* 0 and 1 */
			{
				/** @NOTE The lower two bits of the REQMASK are tied to 1 and can't be cleared. These vectors are furthermore tied to FIQ and this code is thus dead for IRQ. */
				vimREG->REQMASKCLR0 = ( 0xFFFFFFFCU                         & (~vimREG->FIRQPR0));
				vimREG->REQMASKCLR1 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR1));
				vimREG->REQMASKCLR2 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR2));
				/* REG->REQMASKCLR3 = ( 0xFFFFFFFFU                         & (~vimREG->FIRQPR3)); Not applicable for RM48L */

				vimREG->REQMASKCLR0; /* Readback Mask to ensure that the previous write was finished before enabling interrupts again */
			}

			//_enable_IRQ();    /* Enable IRQ, to allow preemption of IRQ routine */

			(*irq_func_pnt)(); /* Execute interrupt routine */

			_disable_IRQ();    /* Disable IRQ, to protect the remainder of the dispatcher from preemption */

			/* Restore VIM REQENASET[0,1,2] Registers from Stack */
			vimREG->REQMASKSET0 = SaveREQMASKSET0;
			vimREG->REQMASKSET1 = SaveREQMASKSET1;
			vimREG->REQMASKSET2 = SaveREQMASKSET2;
			/* REG->REQMASKSET3 = SaveREQMASKSET3; Not applicable for RM48L */
		}
		else
		{
			/* Do not enable IRQ, because max nesting level was reached */
			(*irq_func_pnt)(); /* Execute interrupt routine */
		}

		if (0 < s32NestingLevel)
		{
			s32NestingLevel--;
		}
	}

	return; /* Return to First Level IRQ Dispatcher Assembly routine */
}

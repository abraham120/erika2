/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/**
    @file ee_systick.h
    @brief SysTick system timer driver header file.
    @author Giuanluca Franchino
    @date 2012

**/

#ifndef	__INCLUDE_RENESAS_RSKRX210_SYSTICK_H__
#define	__INCLUDE_RENESAS_RSKRX210_SYSTICK_H__

#ifdef	__USE_SYSTICK__

__INLINE__ void __ALWAYS_INLINE__ EE_systick_set_period(EE_UINT8 tc, EE_UINT8 pre)
{
	/*Set prescaler for PCLK*/
	TMR0.TCCR.BYTE = pre;  
	TMR0.TCORA = tc;//tc -> match A reg
}


__INLINE__ void __ALWAYS_INLINE__ EE_systick_enable_int(void)
{
	/*
	 * Cleared by compare match A
	 * Enable Compare match A interrupt requests (CMIA0)
	 */
	TMR0.TCR.BYTE = 0x48;
	
	/*Enable TMR0_CMIA0 interrupt in ICU*/
	ICU.IER[IER_TMR0_CMIA0].BIT.IEN_TMR0_CMIA0 = 1;
	/*Set TMR0_CMIA0 interrupt priority to level 1 */
	ICU.IPR[IPR_TMR0_CMIA0].BIT.IPR=0x1;
	
}


/*Enable TIMER0 module*/
__INLINE__ void __ALWAYS_INLINE__ EE_systick_set_IRQ_pri(EE_UINT8 pri)
{
	/*Set TMR0_CMIA0 interrupt priority level*/
	if (pri > 15)
		ICU.IPR[IR_TMR0_CMIA0].BIT.IPR=0x1;
	else
		ICU.IPR[IR_TMR0_CMIA0].BIT.IPR=pri;
}



/*Enable TIMER0 module*/
__INLINE__ void __ALWAYS_INLINE__ EE_systick_start(void)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of MSTPCRA register. 
	 */
	SYSTEM.PRCR.WORD |= 0xA502;
	
	SYSTEM.MSTPCRA.BIT.MSTPA5 = 0;
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = (SYSTEM.PRCR.WORD & 0x0009) | 0xA502;
}

/*Stop TIMER0 module*/
__INLINE__ void __ALWAYS_INLINE__ EE_systick_stop(void)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of MSTPCRA register. 
	 */
	SYSTEM.PRCR.WORD |= 0xA502;

	SYSTEM.MSTPCRA.BIT.MSTPA5 = 1;
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = (SYSTEM.PRCR.WORD & 0x0009) | 0xA502;
}


#endif	/* __USE_SYSTICK__ */

#endif	/* _INCLUDE_RENESAS_RSKRX210_SYSTICK_H__*/

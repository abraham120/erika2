/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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

#if ( defined(__PPCE200ZX__ ) || defined(__STELLARIS__) || defined(EE_TRICORE__))

#ifdef __PPCE200ZX__
/* Ack the IRQ */
#define ISR_LOW 0
#if defined (EE_MPC5777C) || defined (EE_SPC574K)
/* Macros to access MPC5777C/SPC574K INTC properly */
#define INTC_SSCIR(n)   (*(EE_UINT8 volatile *)(INTC_SSCIR_BASE + (n)))
#define ACK_IRQ(x) (INTC_SSCIR(x) = 1)
#else
#define ACK_IRQ(x) (INTC.SSCIR[(x)].B.CLR = 1)
#endif
#else
/* Ack the IRQ */
#define ISR_LOW 0
#define ACK_IRQ(x)    ((void)0)
#endif  /* __PPCE200ZX__ */

typedef void (*SoftIRQHandler) (void);

/* Setup an IRQ source */
void test_setup_irq(unsigned int irq, SoftIRQHandler handler,
		unsigned int priority);

/* Fire an IRQ.  When this function returns, an IRQ is guaranteed to have fired
 * once. */
void test_fire_irq(unsigned int irq);
#else
void test_setup_irq(void);

/* Fire an IRQ.  When this function returns, an IRQ is guaranteed to have fired
 * once. */
void test_fire_irq(void);

/* Callback function, defined in the test code.  It must be called by the
* ISR. */
void isr_callback(void);
#endif

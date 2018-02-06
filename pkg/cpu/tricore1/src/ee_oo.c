/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, TU Dortmund University, Faculty of Computer Science 12
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

/* Author: Jan C. Kleinsorge, TU Dortmund University, 2010-
 *
 */


#include "cpu/tricore1/inc/ee_debug.h"
#include "cpu/tricore1/inc/ee_cpu.h"
#include "cpu/tricore1/inc/ee_compiler.h"

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) \
    || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* Restores the context which has been saved with
 * terminate_savestk. */
void EE_tc1_hal_terminate_task(EE_ADDR addr_stored_pcx)
{
    EE_tc1_dsync();      /* Flush shadow CSAs before access */

    EE_CSA_LINK fcx = EE_tc1_csa_get_fcx();        /* Obtain free-list head */
    EE_CSA_LINK pcx = EE_tc1_csa_get_pcxi();       /* Obtain CSA-list head  */
    EE_CSA_LINK cp = *((EE_PCXI*)addr_stored_pcx); /* Obtain "check point"  */
    EE_CSA_LINK next = EE_tc1_csa_get_next(cp); /* Link to context of savestk */
    EE_CSA* csa = EE_tc1_csa_make_addr(cp);     /* For direct access */
    EE_UREG a11 = csa->ucx.A11;                 /* Extract return address */

    EE_barrier();   /* Ensure compiler doesn't schedule beyond this point */

    EE_hal_disableIRQ(); /* Prevent interference while messing with CSAs */

    EE_tc1_csa_set_pcxi(next);    /* "Unwind" CSA list */
    EE_tc1_csa_set_next(cp, fcx); /* Link tail of dead CSAs to free-list */
    EE_tc1_csa_set_fcx(pcx);      /* Dead CSAs become head of free-list */
    EE_tc1_isync();               /* Ensure changes apply before returning */
    EE_tc1_set_RA((EE_ADDR)a11) ;          /* Return to the right place */

    /* Return into ready2stacked applies the newly reset context. */
    /* Interrupts will be disabled implicitly. */
}


/* Saves a context "check point" to which we can return to with
 * TerminateTask. */
void EE_tc1_hal_terminate_savestk(EE_ADDR addr_store_pcx,
	EE_THREAD_PTR realbody)
{

    /* FIXME: this can fairly well be done in plain C and functions
     *        from ee_cpu.h (except for the self-call) */

#ifdef __GNUC__

    /* Upper context has been saved implicitly and is pointed to by
     * PCX, lower context need not be saved by ABI definition. */

    asm("call 1f           \n\t" /* Create a dummy context. This will
                                  * allow us to have an O(1) recovery
                                  * instead of element-wise unwinding
                                  * the CSA list upon TerminateTask */
        "1:                \n\t"
        "isync             \n\t" /* Ensure state */
        "mfcr %%d8, $pcxi  \n\t" /* Obtain link to previous context of dummy. */
        "st.w [%%a4], %%d8 \n\t" /* Recall dummy's previous context */
        "jli %0            \n\t" /* We already created the target
                                  * CSA. Also reset A11.*/
        : : "a"(realbody) : "d8", "memory");

#else

#error Compiler not supported

#endif

    /* When TerminateTask wasn't invoked, we simply return here with
     * the initial context of this function. */

}


#endif /* __OO_BCC1__ || __OO_BCC2__ || __OO_ECC1__ || __OO_ECC2__  */

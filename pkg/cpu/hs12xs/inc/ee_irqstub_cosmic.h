/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
* \file ee_irqstub_cosmic.h
* \brief Erika IRQ support for Cosmic (common files for HAL have been integrated), Erika HCS12 cpu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/


#ifndef	__INCLUDE_HC12_EE_IRQSTUB_COSMIC_H__
#define	__INCLUDE_HC12_EE_IRQSTUB_COSMIC_H__

/* -------------------------------------------------------- */
/* ------------------ PRESTUB ----------------------------- */

/**
 * \brief				This function is the prestub of the IRQs.
                        Actions: If needed the function can call the context change and the
                        resume of IRQ.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_prestub(void) {
  //register EE_FREG flags;
  //flags = EE_s12_suspendIRQ();
  EE_increment_IRQ_nesting_level();
#ifdef	__ALLOW_NESTED_IRQ__
#ifdef	__MULTI__
#ifdef	__IRQ_STACK_NEEDED__
  if (EE_IRQ_nesting_level==1) {
    EE_s12_temp_tos =  EE_READ_SP();         /* save the stack pointer */
    EE_WRITE_SP( EE_s12_IRQ_tos.SYS_tos );   /* change the stack pointer */  
  }
#endif	// __IRQ_STACK_NEEDED__
#endif	// __MULTI__
#ifdef __MC9S12XS128__
  EE_s12_enableIRQ(); //EE_s12_resumeIRQ(flags);
#endif
#endif	// __ALLOW_NESTED_IRQ__
}

/*
	__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_prestub(void)
	{
	#ifdef __ALLOW_NESTED_IRQ__
	  EE_IRQ_nesting_level++;

	#ifdef __MULTI__
	#ifdef __IRQ_STACK_NEEDED__
	  if (EE_IRQ_nesting_level==1) {
		EE_s12_temp_tos =  EE_READ_SP();         // save the stack pointer 
		EE_WRITE_SP( EE_s12xs_IRQ_tos.SYS_tos );   // change the stack pointer 
	  }
	#endif
	#endif
	  EE_s12xs_enableIRQ();
	#else
	  EE_IRQ_nesting_level=1;
	#endif
	}
*/

/* -------------------------------------------------------- */


/* -------------------------------------------------------- */
/* ------------------ POSTSTUB ---------------------------- */

/**
 * \brief				This function is the poststub of the IRQs.
                        Actions: If needed this function can call the context change and the
                        scheduler.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void) {
#ifdef	__ALLOW_NESTED_IRQ__
  EE_s12_disableIRQ();
  EE_decrement_IRQ_nesting_level();
  if (EE_is_inside_ISR_call()) return;
#ifdef	__MULTI__
#ifdef	__IRQ_STACK_NEEDED__
  EE_WRITE_SP( EE_s12_temp_tos );    // change the stack pointer
#endif	// __IRQ_STACK_NEEDED__
#endif	// __MULTI__
#endif	// __ALLOW_NESTED_IRQ__
  EE_std_after_IRQ_schedule();
}


/*
__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void) 
{
#ifdef __ALLOW_NESTED_IRQ__
  EE_s12_disableIRQ();
  EE_IRQ_nesting_level--;

  if (EE_IRQ_nesting_level!=0) 
      return;

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
  EE_WRITE_SP( EE_s12_temp_tos );        // change the stack pointer
#endif
#endif

#else // not __ALLOW_NESTED_IRQ__
  EE_IRQ_nesting_level=0;
#endif // __ALLOW_NESTED_IRQ__

  EE_IRQ_end_instance();
  
  if (EE_hal_endcycle_next_thread) {
    // enable interrupt and CPU priority to 0
    EE_WRITE_CCRH(0x0000);
#ifdef __MONO__
    EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread);
#endif
#ifdef __MULTI__
	 EE_s12xs_hal_ready2stacked(EE_hal_endcycle_next_thread, EE_hal_endcycle_next_tos);
#endif
  }
  else {
#ifdef __MULTI__
    if (EE_hal_endcycle_next_tos != EE_s12xs_active_tos) {
        // enable interrupt and CPU priority to 0
        EE_WRITE_CCRH(0x0000);
        EE_s12xs_hal_stkchange(EE_hal_endcycle_next_tos);
        //EE_s12xs_hal_stkchange(EE_hal_endcycle_next_thread, EE_hal_endcycle_next_tos);
    }
#endif
  }

  //  Set CPU priority to 6 and enable interrupt with disi
  //  retfie will restore the right priority level
  EE_WRITE_CCRH(0x0600);
  EE_s12xs_enableIRQ();
}
*/

/* -------------------------------------------------------- */

#define EE_S12_ISR @interrupt @near

#endif	/* __INCLUDE_HC12_EE_IRQSTUB_H__ */

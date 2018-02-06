// /* ###*B*###
// * ERIKA Enterprise - a tiny RTOS for small microcontrollers
// *
// * Copyright (C) 2002-2008  Evidence Srl
// *
// * This file is part of ERIKA Enterprise.
// *
// * ERIKA Enterprise is free software; you can redistribute it
// * and/or modify it under the terms of the GNU General Public License
// * version 2 as published by the Free Software Foundation,
// * (with a special exception described below).
// *
// * Linking this code statically or dynamically with other modules is
// * making a combined work based on this code.  Thus, the terms and
// * conditions of the GNU General Public License cover the whole
// * combination.
// *
// * As a special exception, the copyright holders of this library give you
// * permission to link this code with independent modules to produce an
// * executable, regardless of the license terms of these independent
// * modules, and to copy and distribute the resulting executable under
// * terms of your choice, provided that you also meet, for each linked
// * independent module, the terms and conditions of the license of that
// * module.  An independent module is a module which is not derived from
// * or based on this library.  If you modify this code, you may extend
// * this exception to your version of the code, but you are not
// * obligated to do so.  If you do not wish to do so, delete this
// * exception statement from your version.
// *
// * ERIKA Enterprise is distributed in the hope that it will be
// * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU General Public License version 2 for more details.
// *
// * You should have received a copy of the GNU General Public License
// * version 2 along with ERIKA Enterprise; if not, write to the
// * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// * Boston, MA 02110-1301 USA.
// * ###*E*### */

//! 
//! \file ee_cpu_cw_utils.h
//! \brief Utils for Codewarrior (macros and inline assembly), Erika HCS12 cpu.
//| This file is also included by the .S files.
//! \author Dario Di Stefano
//! \version 0.1
//! \date 2011-01-12
//!

#ifndef	__INCLUDE_HC12_EE_CPU_CW_H__
#define	__INCLUDE_HC12_EE_CPU_CW_H__

#ifndef __EECFG_THIS_IS_ASSEMBLER__

// save CCR register (I bit)
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_READ_CCR() {
    EE_FREG rvar;
    __asm tfr ccr,b;
    __asm std rvar;
    return rvar;
}
 
// save the stack pointer
__INLINE__ EE_DADD __ALWAYS_INLINE__ EE_READ_SP() {
    EE_DADD tos;
    __asm tfr SP,d;
    __asm addd #5;
    __asm std tos;
    return tos;
}
 
// change the stack pointer
#define EE_WRITE_SP(tos) {__asm ldd tos;\
                          __asm tfr d,SP;}
  
// Macro for interrupts disabling
#define ASM_DIS_INT __asm sei
  
// Macro for interrupts enabling  
#define ASM_EN_INT  __asm cli

// write CCRH register
#if defined (__MC9S12XS64__) || defined (__MC9S12XS128__) || defined (__MC9S12XS256__)
  #define EE_WRITE_CCRH(rvar)    do {\
     EE_UINT16 var = rvar;\
     __asm ldd var;\
     __asm tfr a,CCRH;\
   }while(0)
#endif
#if defined (__MC9S12G96__) || defined (__MC9S12G128__) || defined (__MC9S12GN16__) || defined (__MC9S12GN32__)\
            || defined (__MC9S12G48__) || defined (__MC9S12GN48__)
  #define EE_WRITE_CCRH(rvar)    do {\
   }while(0)
#endif

#else // __EECFG_THIS_IS_ASSEMBLER__

// Macro for ASM files:
#define EE_THREAD_END_INSTANCE        EE_thread_end_instance
#define EE_HAL_ENDCYCLE_NEXT_THREAD   EE_hal_endcycle_next_thread
#define EE_STD_CHANGE_CONTEXT         EE_std_change_context

#define EE_S12_SYSTEM_TOS             EE_s12_system_tos
#define EE_S12_ACTIVE_TOS             EE_s12_active_tos 
#define EE_S12_THREAD_TOS             EE_s12_thread_tos 
#define EE_CHANGE_CONTEXT_TID_PAR     ee_change_context_tid_par
#define EE_STD_RUN_TASK_CODE          EE_std_run_task_code

#define _EE_hal_endcycle_next_tos     EE_hal_endcycle_next_tos
#define _EE_s12xs_change_to_irq_tos   EE_s12xs_change_to_irq_tos
#define _EE_s12xs_change_from_irq_tos EE_s12xs_change_from_irq_tos
#define _EE_s12xs_temp_tos            EE_s12xs_temp_tos

#define PPAGE_NAME                    PPAGE
#define STACK_POINTER                 SP

#endif

#endif // __INCLUDE_HC12_EE_CPU_CW_H__

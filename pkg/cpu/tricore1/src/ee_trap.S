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
#ifdef __GNUC__

        .extern EE_trap_vector, STT_FUNC, 0
        .extern EE_wdt_lock, STT_FUNC, 0
        .extern EE_wdt_unlock, STT_FUNC, 0

/* Default trap handler
 * 
 */       
        .section .text
        .type EE_trap_default_tsr, @function
        .globl EE_trap_default_tsr                                    
EE_trap_default_tsr:        
        debug 
        ji %a11
        
        .size EE_trap_default_tsr, . - EE_trap_default_tsr
        .previous

        
/* Sets this table as the trap vector.
 * 
 * NOTE: On GNU invoked automatically (see ee_init.S)
 */       
        .section .text
        .globl EE_init_trap_vector
        .type EE_init_trap_vector, @function
EE_init_trap_vector:
        
        call EE_wdt_unlock
#if defined (__TRAP__)
        movh %d8, HI:EE_trap_vector
        addi %d8, %d8, LO:EE_trap_vector
        mtcr $btv, %d8 /* Table must be properly aligned */
        isync
#endif
        call EE_wdt_lock
        ret
        
        .size EE_init_trap_vector, . - EE_init_trap_vector
        .previous

#else

#error Compiler not supported.
        
#endif /* __GNUC__ */

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

/*
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: insthand.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

/* for generic primitive definitions */
#include "ee.h"

/* Standard ARM vector locations for IRQ & SWI handlers */
#define EE_IRQVector (EE_ADDR) 0x18
#define EE_SWIVector (EE_ADDR) 0x08

#ifdef DEBUG
/* Backup address of Angel interrupt handlers */
EE_ADDR Angel_IRQ_addr;
EE_ADDR Angel_SWI_addr;
#endif

/* Implemented in assembly (see arm7/inthand.s) */
extern void EE_SWI_handler(void);
extern void EE_IRQ_handler(void);



/*********************************************************************
 SWI & IRQ interrupt handler installer
 *********************************************************************/

/* NOTE: This function returns the address of the old handler so that
 * the new handler is able to call the old handler if it discovers
 * that the source of the exception is not a source it can deal
 * with. */
#ifdef DEBUG
static EE_ADDR EE_install_SWI_IRQ_handler(EE_ADDR routine_addr, EE_ADDR vector_addr)
#else
static void EE_install_SWI_IRQ_handler(EE_ADDR routine_addr, EE_ADDR vector_addr)
#endif
{
    EE_UREG old_vector_content;
    EE_ADDR absolute_routine_addr;
#ifdef DEBUG
    EE_ADDR Angel_addr;
#endif

    /*
     * Take the address of the old exception handler (Angel Debugger)
     */
    
    /* get the old content = branch instruction */
    old_vector_content = (EE_UREG)(*vector_addr); 

    /* mask off the instruction to get the offset.
     * 0xe59ff000 is the opcode for the single data transfer, used as
     * branch instruction (LDR pc, [pc, #offset]) */
    old_vector_content ^= 0xe59ff000; 

    /* calculate the absolute address of the exception handler, by:
     * - adding the address of the corresponding vector;
     * - adding 0x8 to allow for prefetching. */
    absolute_routine_addr = (EE_ADDR)((EE_UREG)vector_addr + (EE_UREG)old_vector_content + 0x8); 

    /*
     * Chain Angel handler
     */
#ifdef DEBUG
    Angel_addr = (EE_ADDR)(*absolute_routine_addr);
#endif
    *absolute_routine_addr = (EE_UREG)routine_addr;

#ifdef DEBUG
    return Angel_addr;
#endif
}

void EE_install_handlers(void)
{
#ifdef DEBUG
    Angel_SWI_addr = EE_install_SWI_IRQ_handler((EE_ADDR)EE_SWI_handler, EE_SWIVector);
    Angel_IRQ_addr = EE_install_SWI_IRQ_handler((EE_ADDR)EE_IRQ_handler, EE_IRQVector);
#else
    EE_install_SWI_IRQ_handler((EE_ADDR)EE_SWI_handler, EE_SWIVector);
    EE_install_SWI_IRQ_handler((EE_ADDR)EE_IRQ_handler, EE_IRQVector);
#endif
}


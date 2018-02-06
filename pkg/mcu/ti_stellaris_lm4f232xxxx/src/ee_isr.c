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

/*
 * Context Interrupt Services Routines
 * Author: 2011 Giuseppe Serano
 */

#include "mcu/ti_stellaris_lm4f232xxxx/inc/ee_isr.h"

/*
 * This is the code that gets called when the processor receives an unexpected
 * interrupt.  This simply enters an infinite loop, preserving the system state
 * for examination by a debugger.
 */
void EE_cortex_mx_default_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

#ifndef EE_CORTEX_MX_NMI_ISR
void EE_cortex_mx_nmi_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif

#ifndef EE_CORTEX_MX_HARD_FAULT_ISR
void EE_cortex_mx_hard_fault_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif

#ifndef EE_CORTEX_MX_MPU_FAULT_ISR
void EE_cortex_mx_mpu_fault_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif

#ifndef EE_CORTEX_MX_BUS_FAULT_ISR
void EE_cortex_mx_bus_fault_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif

#ifndef EE_CORTEX_MX_USAGE_FAULT_ISR
void EE_cortex_mx_usage_fault_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif

#ifndef EE_CORTEX_MX_DEBUG_MONITOR_ISR
void EE_cortex_mx_debug_monitor_ISR(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
#endif

/*
 * This is the code that gets called when the processor first starts execution
 * following a reset event.  Only the absolutely necessary set is performed,
 * after which the application supplied entry() routine is called.  Any fancy
 * actions (such as making decisions based on the reset cause register, and
 * resetting the bits in that register) are left solely in the hands of the
 * application.
 */
void EE_cortex_mx_default_reset_ISR(void)
{
#ifdef __CCS__
    //
    // Jump to the CCS C Initialization Routine.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
#else
    EE_cortex_mx_default_ISR();
#endif
}

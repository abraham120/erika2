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

#ifndef __SHAREDDATA_H__
#define __SHAREDDATA_H__

/* 
 * Data structures shared among all processors
 * 
 * The simbol declared below will be shared among all the processors in the 
 * system.
 * 
 * Please note that the source code that use this symbol does not need to know 
 * that the data it is referencing is global or local to a particular cpu.
 * 
 * The actual status of the data (either global to all CPUs or local to a 
 * particular CPU is specified at the DEFINITION of the variable.
 * 
 * We need to use the EE_DISABLE_GP_ADDRESSING keyword to disable GP addressing
 * to avoid the compiler using GP-relative addressing that will not work if the
 * data is shared among all the processors. If you try to remove it, the 
 * compilation will fail.
 * 
 * The use of EE_DISABLE_GP_ADDRESSING is only required for small RAM data.
 * Add it when the compiler gives you errors like the following one:
 * --------------
 * filename:line: Unable to reach this_is_shared (at 0x82012120) from the 
 * global pointer (at 0x0201a064) because the offset (2147451068) is out 
 * of the allowed range, -32678 to 32767.
 * --------------
 *  
 * See shareddata.c for the definition of this variable.
 */

extern int this_is_shared EE_DISABLE_GP_ADDRESSING;

#endif

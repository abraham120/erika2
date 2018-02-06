/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Asm functions that dirty all registers and check for unexepcted changes
 * Author: 2010,  Bernardo  Dal Seno
 */


/*
 * Save all the callee-saved registers, dirty all user registers (except for sp)
 * using values computed from `base_dirt', call `func' (cannot be null), check
 * the value of the callee-saved registers, restore the callee-saved registers,
 * and return.  Return 0 if no register has changed, or the number X of the
 * changed register rX.
 */
int dirty_regs(void (*func)(void), short base_dirt);


/*
 * Save all the callee-saved registers, dirty all user registers (except for sp)
 * using values computed from `base_dirt', and enter a loop to check for any
 * change in the value of any register.  If a change is detected, return the
 * number X of the changed register rX.
 */
static inline int check_regs(short base_dirt);


static inline int check_regs(short base_dirt)
{
    return dirty_regs((void (*)(void))0, base_dirt);
}


void dirty_caller_saved_regs(short base_dirt);

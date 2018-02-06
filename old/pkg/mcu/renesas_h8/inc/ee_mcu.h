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

(to be rewritten)

__INLINE__ void __ALWAYS_INLINE__ EE_hal_idle(void)
{
  /* cpu enters in power down state.								*
   * Two possible states are possible, depending on the bit 7 of SYSCR:				*
   * - 0: go in sleep mode;									*
   * - 1: go in software standby mode.         							*
   * In software standby mode clock system is halted and settling time (~8ms) is needed 	*
   * to recover from: this can happen only with an external interrupt (ON/OFF,RUN button).   	* 
   * Sleep mode is less power saving but exit from it is possible also with internal		*
   * interrupt and no settling time is needed.  						*
   * So be sure about the value of that bit before calling this primitive.	             	*/

    SYSCR &= 0x7F;    // sleep mode   
    __asm__(".align 1");
    __asm__("andc #0x7F, ccr  ;; enable interrupt before sleep or... sleep forever!!!! ");
    __asm__("sleep");	    
}

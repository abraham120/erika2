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
 * Managament LPM Header.
 * Author: 2010,Christian Grioli
*/

#ifndef __INCLUDE_MSP430_EE_UTILS_H__
#define __INCLUDE_MSP430_EE_UTILS_H__

#include<iomacros.h>
#define NUM_LPM 5
#define EE_LPM_info(x) x & 0x00F0

#define LPMODE_0 0
#define LPMODE_1 1
#define LPMODE_2 2
#define LPMODE_3 3
#define LPMODE_4 4
#define LPMODE_DEFAULT NUM_LPM
#define NO_LPMODE NUM_LPM+1

#ifdef __LPMODE__

extern EE_UINT16* EE_sr_on_stack;
extern EE_UINT16* EE_sr_nested;
extern EE_UINT16 EE_msp430_choose_LPM(EE_UINT8 lpm);

/*This function allows to modify R2 and set the lpm bits. 
Usable in the task and in the interrupt*/
__INLINE__ void EE_msp430_enter_LPM(EE_UINT8 lpm){

_BIS_SR(EE_msp430_choose_LPM(lpm));
}


/*This function allows to modify R2 and reset the lpm bits of the one task. 
Usable in the interrupt, but modify R2 of task. 
After that the mode lpm is deleting from R2 of task*/

__INLINE__ void EE_msp430_exit_LPM(EE_UINT8 lpm){

(*EE_sr_on_stack)&=~EE_msp430_choose_LPM(lpm);



}

/*This function allows to modify R2 and modify the lpm bits. 
Usable in the interrupt  but modify R2 of task. 
After that the mode lpm is changing from R2 of task*/

__INLINE__ void EE_msp430_change_LPM(EE_UINT8 lpm){
(*EE_sr_on_stack)|=EE_msp430_choose_LPM(lpm);
}



#else

__INLINE__ void EE_msp430_enter_LPM(EE_UINT8 lpm){
	return;

}

__INLINE__  void EE_msp430_exit_LPM(EE_UINT8 lpm){
	return;

}


__INLINE__  void EE_msp430_change_LPM(EE_UINT8 lpm){
	return;
}
#endif
#endif

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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_ic.c,v 1.1 2004/11/18 11:19:31 pj Exp $
 */

#include "mcu/unibo_mparm/inc/ee_mcuregs.h"
#include "mcu/unibo_mparm/inc/ee_ic.h"
/*
void EE_IC_compute_masks(EE_TYPEIRQMASK *result, EE_TYPEIRQMASK masked)
{
  EE_TYPEIRQ i, j, currentmask, currentprio;
  EE_UREG priorities[6];
  EE_UREG counters[6];

  priorities[0] = *INTPRI0;
  priorities[1] = *INTPRI1;
  priorities[2] = *INTPRI2;
  priorities[3] = *INTPRI3;
  priorities[4] = *INTPRI4;
  priorities[5] = *INTPRI5;

  counters[0] = 4;
  counters[1] = 4;
  counters[2] = 4;
  counters[3] = 4;
  counters[4] = 4;
  counters[5] = 1;

  for (i=0, j=0, currentmask=masked; i<21; i++) {
    // change the current priority position
    if (!counters[j]) j++;
    counters[j]--;

    // read the priority field
    currentprio = priorities[j] & 0xFF;

    // set its mask
    result[currentprio] = currentmask;

    // update the mask
    currentmask |= 1 << currentprio;

    // update the priorities
    priorities[j] = priorities[j] >> 8;
  }
}
*/

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
 * Author: 2003 Francesco Bertozzi
 * CVS: $Id: ee_dispatcher.c,v 1.2 2004/11/30 14:38:06 pj Exp $
 */
 
#include "com/com.h"
void EE_psa_dispatcher (void)
{
  // cut - from here
  #ifdef CUT_OFF
  if ((EE_psa_tm.value[1] & EE_MASK_PSA_POVL) == EE_PSA_POVL)
  { /* there is an overload on periodic messages */
    EE_psa_tm.id[0] = (EE_psa_tm.id[0] & 0xF8) | 
                         (EE_psa_tm.lp_per >> 3);
    EE_psa_tm.id[1] = (EE_psa_tm.id[1] & 0x1F) | 
                         (EE_UINT8)(EE_psa_sys.lp_per << 5);
  }
  else if ((EE_psa_tm.value[1] & EE_MASK_PSA_SOVL) == EE_PSA_SOVL)
  { /* there is an overload on sporadic messages  */
    EE_psa_tm.id[0] = (EE_psa_tm.id[0] & 0xF8) | 
                         (EE_psa_tm.lp_spor >> 3);
    EE_psa_tm.id[1] = (EE_psa_tm.id[1] & 0x1F) | 
                         (EE_UINT8)(EE_psa_sys.lp_spor << 5);
  }
  else
  #endif
  // cut - till here
  {
    if (++EE_psa_sys.node == EE_psa_sys.node_max)
      EE_psa_sys.node = 0;
    EE_psa_tm.id[0] = (EE_psa_tm.id[0] & 0xF8) | 
                         (EE_psa_sys.node >> 3);
    EE_psa_tm.id[1] = (EE_psa_tm.id[1] & 0x1F) | 
                         (EE_UINT8)(EE_psa_sys.node<< 5);
  }   
    
  EE_psa_tm.value[1] += 0x40;     
                          
  EE_L_Data.request(EE_psa_tm.id, EE_psa_tm.size, EE_psa_tm.value);
  
  EE_thread_activate(EE_PSA_SCHEDULER_TID);
}
  

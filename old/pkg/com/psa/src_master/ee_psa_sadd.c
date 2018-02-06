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
 * CVS: $Id: ee_psa_sadd.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "com/com.h"
#ifdef EE_PSA_SPORADIC
void EE_psa_sporadic_add(EE_UINT8 msg_id, EE_UINT8 *data)
{
  EE_UINT8 i;
  EE_UINT16 available_bw,
               val, val_const1, val_const2,
               val_up, val_down;
  register struct EE_psa_periodic_TYPE * msg_ptr = &EE_psa_sporadic[msg_id];;
  
  available_bw = EE_PSA_EC - 2*EE_PSA_X 
                 - EE_PSA_TM - EE_PSA_CTRL 
                 #ifdef EE_PSA_PERIODIC
                 - EE_psa_sys.LPW_act
                 #endif
                 ;     
  
  EE_mutex_lock (EE_MUTEX_PSA_SPORADIC);
  
  msg_ptr->status |= EE_SET_PSA_ACTIVE;
  msg_ptr->Unorm = (data[0] << 8) | data[1];
  msg_ptr->dline = (data[2] << 8) | data[3];
  msg_ptr->tx_time = (data[4] << 8) | data[5];
  
  t = ((msg_ptr->dline - EE_PSA_TM - msg_ptr->tx_time) / EE_PSA_EC) * EE_PSA_EC;
  val_const1 = t + 2*EE_PSA_X + EE_PSA_EC;
  val_const2 = (t / EE_PSA_EC) - 1;
  
  /* reset the sporadic overload condition */
  EE_psa_tm.value[1] |= EE_RESET_PSA_SOVL; 
  EE_psa_sys.LAW_act = 0;   
  
  for (i=msg_id; i<EE_PSA_N_SPORADIC; i++)
  {
    val_up = val_down = 0;
    for (j=0; j<i; j++)
    {
      msg_ptr = &EE_psa_sporadic[j];
      if ((msg_ptr->status & EE_MASK_PSA_ACTIVE) == EE_PSA_ACTIVE)
      {
        msg_ptr = &EE_psa_sporadic[j];
        val_up += (val_const1 + msg_ptr->mit) / msg_ptr->mit * msg_ptr->tx_time; 
        
        val_down += msg_ptr->Unorm;
      }
    }
    
    val = val_up / (val_down + val_const2);
    if (EE_psa_sys.LAW_act < val)
    /* I have to update the length of the assigned AW */
      EE_psa_sys.LAW_act = val;
      
    if (val > available_bw)
      if (val <= EE_PSA_LAW)
      { /* overload  on periodic messages */
        EE_psa_tm.value[1] |= EE_SET_PSA_POVL;
        return;
      } 
      else 
      { /* overload on sporadic messages */
        EE_psa_tm.value[1] |= EE_SET_PSA_SOVL;
        return;
      }
  }
  
  EE_mutex_unlock (EE_MUTEX_PSA_SPORADIC);
}
#endif
    

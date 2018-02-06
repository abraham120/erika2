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
 * CVS: $Id: ee_psa_padd.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "com/com.h"
#ifdef EE_PSA_PERIODIC
void EE_psa_periodic_add(EE_UINT8 msg_id, EE_UINT8 *data)
{
  EE_UINT16 available_bw;
  register struct EE_psa_periodic_TYPE * msg_ptr;
        
  available_bw = EE_PSA_EC - 2*EE_PSA_X 
                 - EE_PSA_TM - EE_PSA_CTRL 
                 #ifdef EE_PSA_SPORADIC
                 - EE_psa_sys.LAW_act
                 #endif
                 ;                
  
  EE_mutex_lock (EE_MUTEX_PSA_PERIODIC);
  
  msg_ptr = &EE_psa_periodic[msg_id & EE_MASK_PSA_REAL_ID];
  
  if ((msg_ptr->status & EE_MASK_PSA_QUEUE) == EE_PSA_ACTRD)
    /* the message is activated and in ready queue */
    EE_psa_remove_ready(msg_id);
  else if ((msg_ptr->status & EE_MASK_PSA_QUEUE) == EE_PSA_ACTPD)
    /* the message is activated and in pending queue */
    EE_psa_remove_pending(msg_id);
    
  msg_ptr->status = (msg_ptr->status & EE_PSA_RESET_STATUS) | EE_PSA_ACTRD;
  msg_ptr->count = data[0];
  msg_ptr->period = (data[1] << 8) | data[2];
  msg_ptr->tx_time = (data[3] << 8) | data[4];  
  msg_ptr->Unorm = (data[5] << 8) | data[6];  
  if ((msg_id & EE_MASK_PSA_PTYPE) == EE_PSA_PHARD)
    msg_ptr->status |= EE_SET_PSA_PHARD;
  else 
    msg_ptr->status &= EE_RESET_PSA_PHARD;
  
  EE_psa_insert_ready(msg_id);
  
  /* I have to know the used bandwidth */
  EE_psa_sys.LPW_act += (EE_PSA_EC * msg_ptr->Unorm);
  
  if (available_bw > EE_psa_sys.LPW_act)
    EE_psa_tm.value[1] |= EE_RESET_PSA_POVL;
  else if (EE_psa_sys.LPW_act <= EE_PSA_LPW)
    EE_psa_tm.value[1] |= EE_SET_PSA_SOVL;
  else
    EE_psa_tm.value[1] |= EE_SET_PSA_POVL;    
    
  EE_mutex_unlock (EE_MUTEX_PSA_PERIODIC);
}
#endif

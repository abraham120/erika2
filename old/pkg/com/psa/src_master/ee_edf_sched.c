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
 * CVS: $Id: ee_edf_sched.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */
 
#include "com/com.h" 
#ifdef EE_PSA_PERIODIC
void EE_psa_time_control (void)
{
  EE_UINT8 p, q;
  EE_UINT16 time_count;
  register struct EE_psa_periodic_TYPE * msg_ptr;

  EE_mutex_lock (EE_MUTEX_PSA_PERIODIC);
  
  if (EE_psa_sys.pending_head == EE_COM_NULL)
    /* There are no scheduled messages */
    EE_psa_tm.size = 0;
  else
  { /* EDF scheduling algorithm */
    EE_psa_tm.size = 8;
    
    q = EE_psa_sys.pending_head;
    msg_ptr = &EE_psa_periodic[q];
    msg_ptr->count--;
    time_count = 0;
    
    if ((EE_psa_tm.value[1] & EE_MASK_PSA_POVL) == EE_PSA_POVL)
      /* I have to handle a periodic message overload */
      while ((time_count < EE_PSA_LPW) && (q != EE_COM_NULL))
      {
        msg_ptr = &EE_psa_periodic[q];
        if ((msg_ptr->status & EE_MASK_PSA_PTYPE) == EE_PSA_PHARD)
        { /* It's a periodic hard deadline message and must be scheduled */
          time_count += msg_ptr->tx_time;
          EE_psa_periodic[msg_ptr->next].count+= msg_ptr->count;
          
          if (EE_psa_sys.pending_head == q)
          { /* It's an head removal */
            EE_psa_sys.pending_head = msg_ptr->next;
            msg_ptr->status &= EE_RESET_PSA_PENDING;
            EE_psa_insert_ready(q);
            q = EE_psa_sys.pending_head;
          }
          else
          {
            EE_psa_periodic[p].next = msg_ptr->next;
            msg_ptr->status &= EE_RESET_PSA_PENDING;
            EE_psa_insert_ready(q);
            q = EE_psa_periodic[p].next;
          }
        }
        else
        { /* It's a periodic soft deadline message and it must not be scheduled */
          if (msg_ptr->count == 0)
          { /* I'm in first position */
            EE_psa_sys.pending_head = msg_ptr->next;
            msg_ptr->status &= EE_RESET_PSA_PENDING;
            EE_psa_insert_ready(q);
            q = EE_psa_sys.pending_head;
          }
          else
          {
            p = q;
            q = msg_ptr->next;
          }
        }
      }
    else
      /* no overload to handle */
      while ((time_count < EE_PSA_LPW) && (q != EE_COM_NULL))
      {
        msg_ptr = &EE_psa_periodic[q];
        time_count += msg_ptr->tx_time;
        EE_psa_periodic[msg_ptr->next].count+= msg_ptr->count;
          
        EE_psa_sys.pending_head = msg_ptr->next;
        msg_ptr->status &= EE_RESET_PSA_PENDING;
        EE_psa_insert_ready(q);
        q = EE_psa_sys.pending_head;
      }
  }
  
  EE_mutex_unlock (EE_MUTEX_PSA_PERIODIC);
}
#endif
  

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
 * CVS: $Id: ee_psa_indication.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */
 
#include "com/com.h"
void EE_psa_indication (EE_UINT8 *can_msg_id, EE_UINT8 size, EE_UINT8 *data)
{
  EE_UINT8 temp_id;
  
  switch (can_msg_id[0] & EE_MASK_PSA_CAN_TYPE)
  { 
    case EE_PSA_CAN_POVL:
    #ifdef EE_PSA_PERIODIC    
      /* Periodic overload control message */
      temp_id = ~((can_msg_id[0] & 0x0F) << 2) | (can_msg_id[1] >> 6);
      switch (data[0] & EE_MASK_PSA_CAN_OP)
      {
        case EE_PSA_CAN_ADD:
          EE_psa_periodic_add(temp_id, &data[1]);
          break;
          
        case EE_PSA_CAN_REMOVE:
          EE_psa_periodic_remove(temp_id);
          break;
      }; 
    #endif 
    break;
      
    case EE_PSA_CAN_SOVL:
    #ifdef EE_PSA_SPORADIC
      /* Sporadic overload control message */
      temp_id = ~((can_msg_id[0] & 0x0F) << 2) | (can_msg_id[1] >> 6);
      switch (data[0] & EE_MASK_PSA_CAN_OP)
      {
        case EE_PSA_CAN_ADD:
          EE_psa_sporadic_add(temp_id, &data[1]);
          break;
          
        case EE_PSA_CAN_REMOVE:
          EE_psa_sporadic_remove(temp_id);
          break;
      }; 
    #endif
    break;
      
    case EE_PSA_CAN_PER:
    #ifdef EE_PSA_PERIODIC
      /* Periodic control message */
      switch (data[0] & EE_MASK_PSA_CAN_OP)
      {
        case EE_PSA_CAN_ADD_HARD:
          /* add or change hard periodic messages from master table */
          EE_psa_periodic_add(0x80 | (data[0] & 0x3F), &data[1]);
          break;
            
        case EE_PSA_CAN_ADD_SOFT:
          /* add or change soft periodic messages from master table */
          EE_psa_periodic_add(data[0] & 0x3F, &data[1]);
          break;
            
        case EE_PSA_CAN_REMOVE:
          /* remove periodic messages from master table */
          EE_psa_periodic_remove(data[0] & 0x3F);
          break;
          
      }; 
    #endif
    break;
      
    case EE_PSA_CAN_SPOR:
    #ifdef EE_PSA_SPORADIC
      /* Sporadic control message */
      switch (data[0] & EE_MASK_PSA_CAN_OP)
      {
        case EE_PSA_CAN_ADD:
          EE_psa_sporadic_add(data[0] & 0x3F, &data[1]);
          break;
          
        case EE_PSA_CAN_REMOVE:
          EE_psa_sporadic_remove(data[0] & 0x3F);
          break;
      }; 
    #endif
    break;
  }
}        
  

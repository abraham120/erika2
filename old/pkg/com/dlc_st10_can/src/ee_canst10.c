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

#include "com/com.h"
/* 
 *  All this functions are used to configure CAN controller and its messages 
 *  The ST10 uP has only a CAN controller so the lower 2 bits of mask are not useful
 */

 /* 
 * This function is used to set the global mask for incoming messages
 * 
 * Input parameters
 *    mask : the mask to use in message property (see documentation for more detail)
 *
 * Output parameters
 *    none
 */
void EE_L_set_global_mask (EE_UINT8 mask[])
{
   switch (mask[0] & EE_MASK_L_ID_TYPE)
   {
      case EE_L_STANDARD:
         *EE_DLC_GMS_BASE = mask[1]; 
         *(EE_DLC_GMS_BASE+1) = mask[0];
         break;
         
      case EE_L_EXTENDED:
         *EE_DLC_UGML_BASE = mask[3];
         *(EE_DLC_UGML_BASE+1) = mask[2];
         *EE_DLC_LGML_BASE = mask[1];
         *(EE_DLC_LGML_BASE+1) = mask[0];
         break;
   }
}

 /* 
 * This function is used to set the global mask of last message for incoming messages
 * 
 * Input parameters
 *    mask : the mask to use in message property (see documentation for more detail)
 *
 * Output parameters
 *    none
 */
void EE_L_set_last_mask (EE_UINT8 mask[])
{
   switch (mask[0] & EE_MASK_L_ID_TYPE)
   {
      case EE_L_STANDARD:
         *EE_DLC_ULML_BASE = mask[1]; 
         *(EE_DLC_ULML_BASE+1) = mask[0];
         break;
         
      case EE_L_EXTENDED:
         *EE_DLC_ULML_BASE = mask[3];
         *(EE_DLC_ULML_BASE+1) = mask[2];
         *EE_DLC_LLML_BASE = mask[1];
         *(EE_DLC_LLML_BASE+1) = mask[0];
         break;               
   }     
}

/* 
 * This function is used to reserve a message slot in reception 
 * 
 * Input parameters
 *    mask : the mask to use in message property (see documentation for more detail)
 *
 * Output parameters
 *    The assigned message slot
 *
 * Local parameters
 *    i : used in cycles
 *    temp_addr : used like displacement in message register access
 */
EE_UINT8 EE_L_set_message_receive (EE_UINT8 mask[])
{
  EE_UINT16 disp;
  EE_UINT8 n_slot;
  
  EE_mutex_lock(EE_MUTEX_DLC);
  
  if (EE_L_info.tot_free == 0)
  {
    /* There aren't free messages */
    EE_mutex_unlock(EE_MUTEX_DLC);     
    return EE_L_NULL_MSG;
  }
  
  /* There are free messages */
  n_slot = 0; 
  disp = 1;
  while ((EE_L_info.msg_free & disp) != disp)
  {
    n_slot++;  
    disp = 1 << n_slot;
  }
  
  /* Set message to busy */
  EE_L_info.msg_free &= ~disp;
  EE_L_info.tot_free--;   
  
  EE_mutex_unlock(EE_MUTEX_DLC);     
  
  /* Calculating the displacement */
  disp = n_slot << 4;  
  
  switch (mask[0] & EE_MASK_L_ID_TYPE)
  {
     case EE_L_STANDARD:
        *(EE_DLC_UAR_BASE + disp) = mask[1];
        *(EE_DLC_UAR_BASE + disp + 1) = mask[0];
        
        *(EE_DLC_CNF_BASE + disp) = EE_DLC_SET_RX_STD;
        
        break;
        
     case EE_L_EXTENDED:
        *(EE_DLC_UAR_BASE + disp) = mask[3];
        *(EE_DLC_UAR_BASE + disp + 1) = mask[2];
        *(EE_DLC_LAR_BASE + disp) = mask[1];
        *(EE_DLC_LAR_BASE + disp + 1) = mask[0];
        
        *(EE_DLC_CNF_BASE + disp) = EE_DLC_SET_RX_XTD;
        
        break;
  }
  
  *(EE_UINT16 *)(EE_DLC_CTR_BASE + disp) = 0x5599;
  return n_slot;
}
      
/* 
 * This function is used to set a message in transmission; it's used to make a 
 * previous receive message free.
 * 
 * Input parameters
 *    message : the number of message to set (see documentation for more detail)
 *
 * Output parameters
 *    none
 *
 * Local parameters
 *    temp_addr : used like displacement in message register access
 */
void EE_L_set_message_free (EE_UINT8 message)
{
   EE_UINT16 temp_addr = message << 4;
   
   EE_mutex_lock(EE_MUTEX_DLC);     
    
   EE_L_info.tot_free++;
   EE_L_info.msg_free |= 1 << message;
   
   EE_mutex_unlock(EE_MUTEX_DLC);     
    
   *(EE_DLC_CNF_BASE + temp_addr) = EE_DLC_SET_TX_STD; /* identifier type not usefull */
        
   *(EE_UINT16 *)(EE_DLC_CTR_BASE + temp_addr) = 0x5555;
}

/* 
 * This function is used to change the message mask for a "receive message"
 * 
 * Input parameters
 *    message : the number of message to set (see documentation for more detail)
 *    mask : the mask that must be used
 *
 * Output parameters
 *    none
 *
 * Local parameters
 *    temp_addr : used like displacement in message register access
 */
void EE_L_set_message_mask (EE_UINT8 message, EE_UINT8 mask[])
{
   EE_UINT16 temp_addr = message << 4;

   *(EE_UINT16 *)(EE_DLC_CTR_BASE + temp_addr) = 0x5559;  /* set MSGVAL and RXIE */          
   
   switch (mask[0] & EE_MASK_L_ID_TYPE)
   {
      case EE_L_STANDARD:
         *(EE_DLC_UAR_BASE + temp_addr) = mask[1];
         *(EE_DLC_UAR_BASE + temp_addr + 1) = mask[0];
         
         *(EE_DLC_CNF_BASE + temp_addr) = EE_DLC_SET_RX_STD;
         break;
         
      case EE_L_EXTENDED:
         *(EE_DLC_UAR_BASE + temp_addr) = mask[3];
         *(EE_DLC_UAR_BASE + temp_addr + 1) = mask[2];
         *(EE_DLC_LAR_BASE + temp_addr) = mask[1];
         *(EE_DLC_LAR_BASE + temp_addr + 1) = mask[0];
         
         *(EE_DLC_CNF_BASE + temp_addr) = EE_DLC_SET_RX_XTD;
         break;
   }   
   
   *(EE_UINT16 *)(EE_DLC_CTR_BASE + temp_addr) = 0x5599;  /* set MSGVAL and RXIE */          
}

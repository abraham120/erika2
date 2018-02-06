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

/* This function is made for ST10 a uP with only a CAN controller so no useful info are 
 * carried by the controller field in identifier.
 *
 * This is called by the upper network layer when they want to send new data into bus.
 * If there are no empty slots, no send is accomplished and an immediate call to L_Data.confirm 
 * is made.
 *
 * Input parameter:
 *    msg_id : identifier to be used in CAN frame (in a identifier-syntax dependent):
 *
 *       STANDARD : id(11) xx(2) controller(2) type(1)
 *       EXTENDED : id(29) controller(2) type(1)
 * 
 *       where:  xx is not used, controller is used to identify the controller, 
 *               type is used to select the identifier type (standard or extended)
 *                 
 *    msg_length : length of the message to send
 *    msg_data : data to be sent
 */
void EE_L_request (EE_UINT8 msg_id[], EE_UINT8 msg_length, EE_UINT8 msg_data[])
{
  EE_UINT16 disp;
  EE_UINT8 n_slot,
              i;
  
  if (EE_L_info.tot_free == 0)
  {
     EE_L_Data.confirm(msg_id, EE_COM_OVFL);
     return;
  }
  
  EE_hal_begin_nested_primitive();
  
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
  EE_L_last_send = n_slot;
  
  /* Calculating the displacement */
  disp = n_slot << 4;  
  
      
  /* Invio i dati: 
   * Resetto TXOK in quanto questo viene settato dal controller appena ha inviato il dato
   * setto CPUUPD per dire che i dati sono inconsistenti in quanto li sto modificando
   * setto NEWDAT perchè sto immettendo nuovi dati (NEWDAT verrà resettato dalla cpu quando 
   * invierà i dati nel messaggio

   * aggiorno i dati

   * resetto CPUUPD in quanto il messaggio ora é consistente
   * setto TXREQ in quanto voglio trasmettere il dato 
   */
  
  /* 
   * I have to set the status message to busy
   */
  
  EE_DLC_SR &= 0xF7;   /*reset TXOK */
  *(EE_UINT16 *)(EE_DLC_CTR_BASE + disp) = 0x5AA5; /* set CPUUPD, NEWDAT, MSGVAL and TXIE in message control reg. */

  switch (msg_id[0] & EE_MASK_L_ID_TYPE)
     {
        case EE_L_STANDARD:           
           *(EE_DLC_CNF_BASE + disp) = (EE_UINT8)((msg_length << 4) | 0x08);  /* DIR=1, XTD=0 and DLC = msg_length */
           
           /* setting id */
           *(EE_DLC_UAR_BASE + disp) = msg_id[1];
           *(EE_DLC_UAR_BASE + disp + 1) = msg_id[0];
           break;
          
        case EE_L_EXTENDED:
           *(EE_DLC_CNF_BASE + disp) = (EE_UINT8)((msg_length << 4) | 0x0C);  /* DIR=1, XTD=1 and DLC = msg_length */
           
           /* setting id */
           *(EE_DLC_UAR_BASE + disp) = msg_id[3];
           *(EE_DLC_UAR_BASE + disp + 1) = msg_id[2];
           *(EE_DLC_LAR_BASE + disp) = msg_id[1];
           *(EE_DLC_LAR_BASE + disp + 1) = msg_id[0];
           break;
     }
           
  
  /* I'm storing new data */
  for (i=0; i<msg_length; i++)
     *(EE_DLC_DATA_BASE + disp +i) = msg_data[i];
       
  *(EE_UINT16 *)(EE_DLC_CTR_BASE + disp) = 0x67FF; /* set TXRQ and reset CPUUPD in message control reg. */
  
  EE_hal_end_nested_primitive();
}

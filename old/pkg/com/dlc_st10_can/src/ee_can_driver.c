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
 * L_CAN_MANAGEMENT 
 * 
 * The transmission or reception error aren't managed by the data link layer at the moment
 */

void EE_L_can_driver (void)
{  EE_UINT8 control_reg, status_reg, intid,
               disp;
   EE_UINT8 msg_id[4];
   
   control_reg = EE_DLC_CR;
   status_reg = EE_DLC_SR;
   EE_DLC_SR = 0;
      
   while (intid = (EE_DLC_INT_ID))
      switch (intid)
      {
         case 1:  /* errore causato da una condizione di BUSOFF */
         if (status_reg & 0x80) 
         {
            EE_DLC_CR = (EE_DLC_CR & 0xFE); /* reset INIT */
            /* ERRORE di BUSOFF, il bus viene fermato */
         } 
         break;
         
         case 2:  /* ricezione di un messaggio (slot 15)*/
            if (((*(EE_UINT8 *)0xEFF6) & EE_MASK_DLC_ID_TYPE) 
                  == EE_DLC_EXTENDED)
               {  /* A long identifier message was received */
                  msg_id[3] = *(EE_UINT8 *)0xEFF2;
                  msg_id[2] = *(EE_UINT8 *)0xEFF3;
                  msg_id[1] = *(EE_UINT8 *)0xEFF4;
                  msg_id[0] = *(EE_UINT8 *)0xEFF5;
                  
                  msg_id[0] |= 0x04;   /* set EXTENDED in message identifier */
               }
               else
               {  /* A standard identifier message was received*/
                  msg_id[1] = *(EE_UINT8 *)0xEFF2;
                  msg_id[0] = *(EE_UINT8 *)0xEFF3;
               }            
            
            EE_L_Data.indication(msg_id, 
                              *(EE_UINT8 *)0xEFF6 >> 4, 
                              (EE_UINT8 *)0xEFF7);
         
            /*
             * !!! Warning !!! 
             * Don't change the order of the next two code lines, if you change it 
             * CAN controller stop working properly
             */
             
            *(EE_UINT8 *)0xEFF0 = 0xFD; /* reset INTPND */
            
            *(EE_UINT16 *)0xEFF0 = 0x55DF;
            
            /*
             ************************************************
             */
         
            break;
         
         default: /* a message was send or received (message 1-14) */
         
            disp = (intid-3) << 4;
            
            if ((*(EE_DLC_CNF_BASE + disp) & EE_MASK_DLC_ID_TYPE) 
                  == EE_DLC_EXTENDED)
               {  /* Long identifier message */
                  msg_id[3] = *(EE_DLC_UAR_BASE + disp);
                  msg_id[2] = *(EE_DLC_UAR_BASE + disp + 1);
                  msg_id[1] = *(EE_DLC_LAR_BASE + disp);
                  msg_id[0] = *(EE_DLC_LAR_BASE + disp + 1);
                  
                  msg_id[0] |= 0x04;   /* set EXTENDED in message identifier */
               }
               else
               {  /* Standard identifier message */
                  msg_id[1] = *(EE_DLC_UAR_BASE + disp);
                  msg_id[0] = *(EE_DLC_UAR_BASE + disp + 1);
               }
         
            if ((*(EE_DLC_CNF_BASE + disp) & EE_MASK_DLC_MESSAGE_DIR) 
                  == EE_DLC_MESSAGE_TRANSMIT)
            {   /* transmission message or remote received */
               if ((*(EE_DLC_CTR_BASE + disp + 1) & EE_MASK_DLC_MESSAGE_REMOTE) 
                    == EE_DLC_MESSAGE_REMOTE)
               { 
                  /* remote message received */
               }
               else
               { 
                  /* simple message transmit */
                  EE_L_info.tot_free++;
                  EE_L_info.msg_free |= 1 << (intid-3);
                  
                  EE_L_Data.confirm(msg_id, EE_COM_OK);  /* confermo l'invio */                  
               }
            } /* if - tx message */
            else
            {  /* received message or remote sent */
               if ((*(EE_DLC_CTR_BASE + disp + 1) & EE_MASK_DLC_MESSAGE_NEW) == EE_DLC_MESSAGE_NEW)
               { 
                  /* new frame received */
                  EE_L_Data.indication(msg_id, *(EE_DLC_CNF_BASE + disp) >> 4, EE_DLC_CNF_BASE + disp + 1);
               }
               else
               { 
                  /* remote frame sent */
               }
            }
           
            *(EE_UINT16 *)(EE_DLC_CTR_BASE + disp) = 0xFFFD;   /* reset INTPND */
            break;
         
   }  /*switch*/
}

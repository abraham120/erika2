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

#ifndef EE_DLC_INIT_C
#define EE_DLC_INIT_C
#include "com/com.h"

struct EE_L_info_TYPE EE_L_info;
EE_UINT8 EE_L_last_send;
/*
 * This function is called at the initialization of the can controller by the 
 * upper network level. It start the can controller with all messages in transmission 
 * and no valid message.
 * The CAN speed is set according with the value of the symbol EE_DLC_CAN_RATE that 
 * rappresent the content of the BTR register
 * 
 * Input parameter
 *    EE_DLC_CAN_RATE (symbol)
 *
 * Output parameter
 *    none
 *
 * Local parameter
 *    i : used in cycles
 */

void EE_L_init (void)
{  
   EE_UINT8 i,
               disp;
   
   /* 
    * I'm going to disable the CAN controller 
    */
   EE_DLC_SR = 0x00;
   EE_DLC_CR = 0x41;
   
   /* 
    * Bit rate of the CAN 
    */
   EE_DLC_BTR = EE_DLC_CAN_RATE;
   
   *EE_DLC_UGML_BASE = 0xFF;
   *(EE_DLC_UGML_BASE+1) = 0xFF;
   *EE_DLC_LGML_BASE = 0xFF;
   *(EE_DLC_LGML_BASE+1) = 0xFF;
    
   /* 
    * Set all messages to not valid
    */
   for (i=0; i < 15; i++) 
   {   disp = i << 4;
       *(EE_DLC_CNF_BASE + disp) = 0x88;  /* DIR = 1 (trasmit) */
       *(EE_UINT16 *)(EE_DLC_CTR_BASE + disp) = 0x5555;  /* MSGVAL = 0 (message not valid) */       
   }
   
   EE_L_info.tot_free = 14;
   EE_L_info.msg_free = 0x7FFF;
    
   EE_DLC_CANIC = EE_DLC_CAN_PRIORITY; /* set CAN controller interrupt priority group 2 priority 11 */
   EE_DLC_DP4 &= 0x9F;
   EE_DLC_DP4 |= 0x40;
   
   /* 
    * And finally, start the CAN controller 
    */
   EE_DLC_SR = 0x00;
   EE_DLC_CR = 0x0A;
   
}
#endif
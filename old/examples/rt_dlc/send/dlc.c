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
 * CVS: $Id: dlc.c,v 1.3 2006/01/05 14:38:25 pj Exp $
 */

#include "ee.h"
#include "com/com.h"

EE_UINT8 length = 8;
EE_UINT8 tx_id[2] = {0x40, 0x44};
EE_UINT8 rx_id[2] = {0x40, 0x54};
EE_UINT8 data[8] = {0,0,0,0,0,0,0,0};

EE_UINT8 i = 0;

void confirm (EE_UINT8 msg_id[], EE_UINT8 result)
{  
  i++;
  if (i==2)
    i = 0;
  EE_L_Data_request_exclusive(tx_id, length, data);  
}

void indication (EE_UINT8 msg_id[], EE_UINT8 msg_length, EE_UINT8 msg_data[])
{

}

void main(void)
{    
  EE_L_init();
  EE_L_set_message_receive(rx_id); // request for a receiving slot
  
  EE_L_Data.request(tx_id, length, data);
        
  for (;;) {}
}

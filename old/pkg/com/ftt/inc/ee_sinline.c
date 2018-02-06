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
 * CVS: $Id: ee_sinline.c,v 1.3 2006/04/08 21:15:23 pj Exp $
 */
 
#ifndef __INLINE_H__
#define __INLINE_H__

#include "com/com.h"

/* EE_FTT_Snotify
 * 
 * Used after a Synch. message reception/transmission to notify the event 
 * Input params:
 *    msg_pos : The message index.
 *    type    : The notification result
 */
#ifdef EE_FTT_N_SYNCH
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_Snotify (EE_UINT8 msg_pos, EE_UINT8 type)
{
   if ((EE_FTT_SYNCH_MSG_RAM[msg_pos]->status & EE_MASK_FTT_ACTION_TYPE) == EE_FTT_ACTION_CALLBACK)
      ((void (*)(EE_UINT8))EE_FTT_SYNCH_MSG_ROM[msg_pos]->call)(type);
   else 
      EE_thread_activate(*(EE_UINT8 *)EE_FTT_SYNCH_MSG_ROM[msg_pos]->call);
}   
#endif

/* EE_FTT_Anotify
 * 
 * Used after an Asynch. message reception/transmission to notify the event 
 * Input params:
 *    msg_pos : The message index.
 *    type    : The notification result
 */
#ifdef EE_FTT_N_RT
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_Anotify (EE_UINT8 msg_pos, EE_UINT8 type)
{
   if ((EE_FTT_RT_RAM[msg_pos]->status & EE_MASK_FTT_ACTION_TYPE) == EE_FTT_ACTION_CALLBACK)
      ((void (*)(EE_UINT8))EE_FTT_RT_ROM[msg_pos]->call)(type);
   else 
      EE_thread_activate(*(EE_UINT8 *)EE_FTT_RT_ROM[msg_pos]->call);
}   
#endif

/* EE_FTT_NRTTnotify
 * 
 * Used after a non real-time (transmission) message reception/transmission 
 * to notify the event 
 * Input params:
 *    msg_pos : The message index.
 *    type    : The notification result
 */
#ifdef EE_FTT_NRTT
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_NRTTnotify (EE_UINT8 msg_pos, EE_UINT8 type)
{
   if ((EE_FTT_NRTT_RAM[msg_pos] & EE_MASK_FTT_ACTION_TYPE) == EE_FTT_ACTION_CALLBACK)
      ((void (*)(EE_UINT8))EE_FTT_NRTT_ROM[msg_pos]->call)(type);
   else 
      EE_thread_activate(*(EE_UINT8 *)EE_FTT_NRTT_ROM[msg_pos]->call);
}
#endif
      
/* EE_FTT_NRTRnotify
 * 
 * Used after a non real-time (transmission) message reception/transmission 
 * to notify the event 
 * Input params:
 *    msg_pos : The message index.
 *    type    : The notification result
 */
#ifdef EE_FTT_NRTR
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_NRTRnotify (EE_UINT8 msg_pos, EE_UINT8 type)
{
   if ((EE_FTT_NRTR_RAM[msg_pos]->status & EE_MASK_FTT_ACTION_TYPE) == EE_FTT_ACTION_CALLBACK)
      ((void (*)(EE_UINT8))EE_FTT_NRTR_ROM[msg_pos]->call)(type);
   else 
      EE_thread_activate(*(EE_UINT8 *)EE_FTT_NRTR_ROM[msg_pos]->call);
}
#endif
#endif
   

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

#ifndef __DLC_H__
#define __DLC_H__

#include "ee.h"

/* internal API structure */
struct EE_L_Data_TYPE {
   void (*start) (void);
   void (*request)(EE_UINT8 msg_id[], EE_UINT8 msg_length, EE_UINT8 msg_data[]);
   void (*confirm)(EE_UINT8 msg_id[], EE_UINT8 result);
   void (*indication)(EE_UINT8 msg_id[], EE_UINT8 msg_length, EE_UINT8 msg_data[]);
};

extern const struct EE_L_Data_TYPE EE_L_Data;

/* 
 * This structure is used to store info about busy and free slots.
 *  msg_free bit explication
 *    0 : busy
 *    1 : free
 *  tot_free : Then number of free slots
 */
struct EE_L_info_TYPE {
  EE_UINT16 msg_free;
  EE_UINT8 tot_free;  
};

extern EE_UINT8 EE_L_last_send;

extern struct EE_L_info_TYPE EE_L_info;

/* FUNCTION DECLARATION section
 */
void EE_L_init (void);
void EE_L_set_global_mask (EE_UINT8 mask[]);
void EE_L_set_last_mask (EE_UINT8 mask[]);
EE_UINT8 EE_L_set_message_receive (EE_UINT8 mask[]);
void EE_L_set_message_free (EE_UINT8 message);
void EE_L_set_message_mask (EE_UINT8 message, EE_UINT8 mask[]);
void EE_L_disable_last (void);
void EE_L_can_handler (void);
void EE_L_can_driver (void);
void EE_L_init (void);
void EE_L_request (EE_UINT8 msg_id[], EE_UINT8 msg_length, EE_UINT8 msg_data[]);
__INLINE__ void __ALWAYS_INLINE__ EE_L_Data_request_exclusive (EE_UINT8 msg_id[], EE_UINT8 msg_length, EE_UINT8 msg_data[]);

/*********/
/* MACRO */
/*********/
#define EE_L_SET_CALLOUT(confirm,indication) \
  const struct EE_L_Data_TYPE EE_L_Data = {EE_L_init,EE_L_request,(confirm),(indication)}

#define EE_DLC_CAN_DRIVER EE_L_can_driver

/* 
 * Various constant 
 *
 * Syntax 
 *    L means symbol defined and used in this layer
 *    DLC means a symbol used directly on CAN controller
 *
*/

#define EE_L_NULL_MSG 255
#define EE_L_NUM_MSG 15

#define EE_MASK_L_MSG_STATUS 0x03
#define EE_L_MSG_ACTIVE_FREE 0x00

#define EE_DLC_SET_RX_STD 0x00  /* macro used to set a receive standard message */
#define EE_DLC_SET_RX_XTD 0x04  /* macro used to set a receive extended message */
#define EE_DLC_SET_TX_STD 0x08  /* macro used to set a transmite standard message */
#define EE_DLC_SET_TX_XTD 0x0C  /* macro used to set a transmit extended message */

#define EE_MASK_L_MESSAGE_DIR 0x04
#define EE_L_MESSAGE_TRANSMIT 0x00
#define EE_L_MESSAGE_RECEIVE 0x04

#define EE_MASK_DLC_MESSAGE_DIR 0x08
#define EE_DLC_MESSAGE_TRANSMIT 0x08
#define EE_DLC_MESSAGE_RECEIVE 0x00

#define EE_MASK_DLC_ID_TYPE 0x04
#define EE_DLC_STANDARD 0x00
#define EE_DLC_EXTENDED 0x04

#define EE_MASK_DLC_MESSAGE_REMOTE 0xC0
#define EE_DLC_MESSAGE_REMOTE 0x80

#define EE_MASK_L_ID_TYPE 0x04
#define EE_L_STANDARD 0x00
#define EE_L_EXTENDED 0x04

#define EE_MASK_DLC_MESSAGE_NEW 0x03
#define EE_DLC_MESSAGE_NEW 0x02

#define EE_DLC_INTERRUPT_DISABLE 0xFD
#define EE_DLC_INTERRUPT_ENABLE 0x02
/* 
 * usefull CAN register
 */
#define EE_DLC_SYSCON *(EE_UINT16*) 0xFF12
#define EE_DLC_CR *(EE_UINT8*) 0xEF00
#define EE_DLC_SR *(EE_UINT8*) 0xEF01
#define EE_DLC_BTR *(EE_UINT16*) 0xEF04
              
#define EE_DLC_GMS_BASE (EE_UINT8*) 0xEF06   /* Global Mask short */
#define EE_DLC_UGML_BASE (EE_UINT8*) 0xEF08   /* Upper Global Mask Long */
#define EE_DLC_LGML_BASE (EE_UINT8*) 0xEF0A   /* Lower Global Mask Long */
#define EE_DLC_ULML_BASE (EE_UINT8*) 0xEF0C   /* Upper Mask of Last Message */
#define EE_DLC_LLML_BASE (EE_UINT8*) 0xEF0E   /* Lower Mask of Last Message */
              
#define EE_DLC_CNF_BASE  (EE_UINT8*) 0xEF16   /* Message configuration register base in displacement operation */
#define EE_DLC_CTR_BASE (EE_UINT8*) 0xEF10   /* Message control register base in displacement operation */
#define EE_DLC_UAR_BASE (EE_UINT8*) 0xEF12   /* Message upper arbitration register base in displacement operation */
#define EE_DLC_LAR_BASE (EE_UINT8*) 0xEF14   /* Message lower arbitration register base in displacement operation */
#define EE_DLC_DATA_BASE (EE_UINT8 *) 0xEF17   /* Message data base in displacement operation */
              
#define EE_DLC_INT_ID *(EE_UINT8 *) 0xEF02
#define EE_DLC_CANIC *(EE_UINT16 *) 0xF186   /* Can interrupt controller register */
#define EE_DLC_DP4 *(EE_UINT8 *) 0xFFCA   /* Data port 4 register */

#endif
	

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
 * CVS: $Id: ee_master.h,v 1.2 2006/04/08 21:15:23 pj Exp $
 */
 
/* SRT section
 */
#ifdef EE_FTT_SRT_LENGTH
#ifndef __PRIVATE_SRT__
/* This structure is the Synchronous Requirement Table used to
 * store all informations on synch. messages of the net
 */
/* Status explication : 
 * -------x : 0 not active
 *            1 active
 * ------x- : 0 not pending transmission request
 *            1 pending transmission request
 */ 
struct EE_FTT_SRT_TYPE {
   EE_UINT16 tx_time;
   EE_UINT8 phase,
               per,
               dline,
               status;
                
   EE_UINT8 prev,
               next;
};
#endif

extern struct EE_FTT_SRT_TYPE EE_FTT_SRT[EE_FTT_SRT_LENGTH];
extern EE_UINT8 EE_FTT_SRT_head,
                   EE_FTT_SRT_tail;
#endif


/* ART section
 */
#ifdef EE_FTT_ART_LENGTH
#ifndef __PRIVATE_ART__
/* This structure is the Asynchronous Requirement Table used to
 * store all informations on sporadic guaranteed messages of the net
 */
/* Status explication : 
 * -------x : 0 not active
 *            1 active
 */
struct EE_FTT_ART_TYPE {
   EE_UINT16 tx_time,
                dline,
                mit;              
                
   EE_UINT8 status;  
                               
};
#endif

extern struct EE_FTT_ART_TYPE EE_FTT_ART[EE_FTT_ART_LENGTH];

/* ASYNCH "HURRY DATA" DB section
 *
 * This DB is used to insert new control data exiting from master node
 */
struct EE_FTT_HURRY_BUFF_TYPE {
   EE_UINT16 msg_id;   
   EE_UINT8 size;               
   EE_UINT8 data[8];  
};
               
struct EE_FTT_HURRY_RAM_TYPE {
   EE_UINT8 first,
               last,
               tot,
               status;
};

extern struct EE_FTT_HURRY_BUFF_TYPE EE_FTT_HURRY_BUFF[EE_FTT_N_HURRY];
extern struct EE_FTT_HURRY_RAM_TYPE EE_FTT_HURRY_RAM;
/* EE_FTT_law : contains the size of every asynch. window
 */
extern EE_UINT16 EE_FTT_law[EE_FTT_MAX_DLINE];
#endif

/* ASYNCH CONTROL LP DB section
 */

struct EE_FTT_LP_RAM_TYPE { 
   EE_UINT8 first, 
               last,
               tot;
};               

struct EE_FTT_LP_BUFF_TYPE {
   EE_UINT16 msg_id;
   EE_UINT8 size;
   EE_UINT8 data[8];
};

extern struct EE_FTT_LP_RAM_TYPE EE_FTT_LP_RAM;
extern struct EE_FTT_LP_BUFF_TYPE EE_FTT_LP_BUFF[EE_FTT_N_ASYNCH_LP];

/* TRIGGER MESSAGE section
 * EE_FTT_tm : the trigger message
 * EE_FTT_tm_sn : The sequence number of the trigger message
 */
extern EE_UINT8 EE_FTT_tm[EE_FTT_TM_LENGTH];
extern EE_UINT8 EE_FTT_tm_sn;

/* GLOBAL variable section
 * EE_FTT_lsw : is used to store the length of every synchronous window
 * EE_FTT_law : is used to store the length of every asynchronous window, 
 */
extern EE_UINT8 EE_FTT_system_status;
extern EE_UINT16 EE_FTT_actual_lsw;

/* FUNCTION DECLARATION section
 */
void EE_FTT_transmitter (void);
#define EE_FTT_TRANSMITTER EE_FTT_transmitter

void EE_FTT_stop_asynch(void);
#define EE_FTT_STOP_ASYNCH EE_FTT_stop_asynch

void EE_FTT_dispatcher (void);
#define EE_FTT_DISPATCHER EE_FTT_dispatcher

void EE_FTT_indication(EE_UINT8 msg_id[], EE_UINT8 length, EE_UINT8 msg_data[]);
void EE_FTT_confirm(EE_UINT8 msg_id[], EE_UINT8 result);
void EE_FTT_start (void);
extern void EE_FTT_PROTO_set_handler(EE_UINT16 rel_dline);
extern void EE_FTT_PROTO_reset_handler(void);   
extern void EE_FTT_PROTO_init_handler(void);  
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_PROTO_read_timer(void);
extern EE_UINT16 EE_FTT_PROTO_timer;

#ifdef EE_FTT_SRT_LENGTH
void EE_FTT_SRT_add (EE_UINT8 msg_id, EE_UINT8 * data);
void EE_FTT_SRT_change (EE_UINT8 msg_id, EE_UINT8 * data);
void EE_FTT_SRT_remove (EE_UINT8 msg_id);

void EE_FTT_SRT_insert (EE_UINT8 id);
void EE_FTT_SRT_delete (EE_UINT8 id);
#ifdef EE_FTT_SYNCH_AC
EE_UINT8 EE_FTT_SRT_check (void);
#endif

void EE_FTT_scheduler (void);
#define EE_FTT_SCHEDULER EE_FTT_scheduler
#endif

#ifdef EE_FTT_ART_LENGTH
void EE_FTT_ART_add (EE_UINT8 msg_id, EE_UINT8 * data);
void EE_FTT_ART_change (EE_UINT8 msg_id, EE_UINT8 * data);
void EE_FTT_ART_remove (EE_UINT8 msg_id);

void EE_FTT_ART_insert (EE_UINT8 id);
void EE_FTT_ART_delete (EE_UINT8 id);
EE_UINT8 EE_FTT_ARTcheck (void);

EE_UINT16 EE_FTT_Ainv (EE_UINT16 A);
EE_UINT16 EE_FTT_H (EE_UINT8 msg_pos, EE_UINT16 t);
EE_UINT8 EE_FTT_level_i (EE_UINT8 msg_pos, EE_UINT16 delta, EE_UINT16 * level_i);
EE_UINT8 EE_FTT_ART_check(EE_UINT8 * msg_pos);
#endif

/* MACRO FUNCTION section
 */
#define EE_FTT_DIV_UPPER(x,y) ((((x)-1) / (y)) +1)

/* MASK section 
 */
#define EE_MASK_FTT_OP_TYPE 0xF0
#define EE_FTT_ADD 0x00
#define EE_FTT_CHANGE 0x10
#define EE_FTT_REMOVE 0x20

#define EE_MASK_FTT_HURRY_TYPE 0x0400
#define EE_FTT_HURRY_SLAVE_ADD 0x0000

#define EE_MASK_FTT_CONF_MSG_ID 0xF000
#define EE_MASK_FTT_IND_MSG_ID 0xF800

#define EE_MASK_FTT_MSG_ID 0x07E0

#define EE_MASK_FTT_NODE_ID 0x07E0  /* Used to take the node id in activation/deactivation request*/

#define EE_MASK_FTT_SRT_PENDING 0x02
#define EE_SET_FTT_SRT_PENDING 0x02
#define EE_RESET_FTT_SRT_PENDING 0xFD
#define EE_FTT_SRT_PENDING 0x02

#define EE_MASK_FTT_MSG_ACTIVE 0x01
#define EE_FTT_MSG_ACTIVE 0x01
#define EE_SET_FTT_MSG_ACTIVE 0x01
#define EE_RESET_FTT_MSG_ACTIVE 0x00

#define EE_MASK_FTT_LP_TYPE 0x0400
#define EE_FTT_REQ_TYPE 0x0400

#define EE_FTT_TM 0x1000  
#define EE_FTT_HURRY_DATA 0xA000 
#define EE_FTT_CTRL_LP 0xE000 
#define EE_FTT_CTRL_HURRY 0xA000  
#define EE_FTT_SDATA 0x6000
#define EE_FTT_ADATA_RT 0x8000
#define EE_FTT_ADATA_RTD 0xC000
#define EE_FTT_ADATA_NRT 0xF000

#define EE_FTT_CTRL_HP_S 0xB000
#define EE_FTT_CTRL_HP_A 0xB800

#define EE_FTT_SRT_REQ 0x00
#define EE_FTT_ART_REQ 0x02

#define EE_SET_FTT_ADD_OK 0x00
#define EE_SET_FTT_NO_ADD 0x80
#define EE_FTT_SLAVE_OK 0xE0
#define EE_FTT_SLAVE_NO_ADD 0xC0

#define EE_FTT_HURRY_ART (0xA400 | EE_FTT_CAN_ID)
#define EE_FTT_TM_ID (0x1000 | EE_FTT_CAN_ID)

#define EE_FTT_AW 0
#define EE_FTT_STOP_TRANSMISSION 1

__INLINE__ void __ALWAYS_INLINE__ EE_FTT_PROTO_read_timer (void)
{
   /* Leggo il Timer1
    */
   EE_FTT_PROTO_timer = *(EE_UINT16 *)0xFE52;
}

   
   

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
 * Author:2003 Francesco Bertozzi
 * CVS: $Id: ee_slave.h,v 1.2 2006/04/08 21:15:23 pj Exp $
 */
 
#ifndef __SLAVE_H__
#define __SLAVE_H__

/* 
 * SYNCHRONOUS MESSAGES SECTION
 */
#ifdef EE_FTT_N_SYNCH
/* Structure used to submit new parameters for a synchronous message
 * in SRT.change
 */
struct EE_FTT_SPARAM_TYPE {
   EE_UINT8 per,
               dline;
}; 

/* Structure used to store synch. messages data
 * Meaning of status:
 *    -------x  0 : Message cannot transmitted
 *              1 : Message can be transmitted
 *    ------x-  0 : Message not pending
 *              1 : Message pending
 *    ----xx-- 00 : No error on message
 *             01 : Buffer overflow error 
 *             10 : Data not sent
 *    x-------  0 : Callback associated
 *              1 : Task associated
 */
struct EE_FTT_SYNCH_MSG_RAM_TYPE 
{
   EE_UINT8 per,
               dline,
               status;               
};

struct EE_FTT_SYNCH_MSG_ROM_TYPE 
{
   EE_UINT16 msg_id,
                tx_time;
                
   EE_UINT8 size,
               phase;
               
   void * call;                              
               
   EE_UINT8 * data;      
};

extern struct EE_FTT_SYNCH_MSG_RAM_TYPE * EE_FTT_SYNCH_MSG_RAM[EE_FTT_N_SYNCH];
extern const struct EE_FTT_SYNCH_MSG_ROM_TYPE * EE_FTT_SYNCH_MSG_ROM[EE_FTT_N_SYNCH];
#endif

/* 
 * ASYNCHRONOUS REAL-TIME section
 */

#ifdef EE_FTT_N_RT
/* Structure used to submit new parameters for a synchronous message
 * in ART.change
 */
struct EE_FTT_RT_PARAM_TYPE {
   EE_UINT16 dline,
                mit;
};

/* This structure is used to store sporadic data.
 */
struct EE_FTT_RT_ROM_TYPE {
   EE_UINT16 msg_id,
                tx_time;
                
   EE_UINT8 size;                               
   
   void * call;                        
   EE_UINT8 * data;
};

/* This structure is used to store variables info about real-time messages
 * Meaning of status:
 *    -------x  0 : Message downgraded
 *              1 : Message not downgraded
 *    ------x-  0 : message not pending
 *              1 : message pending
 *    ----xx-- 00 : No error on message
 *             01 : Buffer overflow error
*    x-------  0 : Callback associated
 *              1 : Task associated
 */  
struct EE_FTT_RT_RAM_TYPE {
   EE_UINT16 mit,               
                dline;
                
   EE_UINT8 status;              
};
   
extern const struct EE_FTT_RT_ROM_TYPE * EE_FTT_RT_ROM[EE_FTT_N_RT];
extern struct EE_FTT_RT_RAM_TYPE * EE_FTT_RT_RAM[EE_FTT_N_RT];
#endif

/* 
 * ASYNCHRONOUS NON REAL-TIME section
 */
/* Used to store info and data about non real-time messages (reception)
 */
#ifdef EE_FTT_NRTR
struct EE_FTT_NRTR_MSG_RAM_TYPE 
{
   EE_UINT8 first,
               last,
               tot,
               status;
};

const struct EE_FTT_NRTR_MSG_ROM_TYPE
{
   EE_UINT16 msg_id,
                length;   
   EE_UINT8 size;
   void * call;                           
   EE_UINT8 * buffer;
}; 

extern struct EE_FTT_NRTR_MSG_RAM_TYPE * EE_FTT_NRTR_RAM[EE_FTT_NRTR];
extern const struct EE_FTT_NRTR_MSG_ROM_TYPE * EE_FTT_NRTR_ROM[EE_FTT_NRTR];
#endif   

/* FIFO buffer type (transmission)
 */   
/* Used to take in track the status of the transmission data buffer
 */
#ifdef EE_FTT_NRTT                                      
struct EE_FTT_NRTT_BPAR_TYPE 
{
   EE_UINT8 first, 
               last,
               tot;
};

/* Non real-time data
 */
struct EE_FTT_NRTT_BUFF_TYPE
{
   EE_UINT16 msg_id;
   EE_UINT8 size;
   EE_UINT8 buffer[8];
};

/* Used to store info about non real-time messages (transmit)
 */
const struct EE_FTT_NRTT_MSG_ROM_TYPE
{
   EE_UINT16 msg_id;
   EE_UINT8 size;
   
   void * call;
};

extern const struct EE_FTT_NRTT_MSG_ROM_TYPE * EE_FTT_NRTT_ROM[EE_FTT_NRTT];
extern EE_UINT8 EE_FTT_NRTT_RAM[EE_FTT_NRTT];

extern struct EE_FTT_NRTT_BPAR_TYPE EE_FTT_NRTT_BPAR;
extern struct EE_FTT_NRTT_BUFF_TYPE EE_FTT_NRTT_BUFF[EE_FTT_NRTT_LENGTH];
#endif

/* CONTROL MESSAGES section
 */
struct EE_FTT_CTRL_BUFF_TYPE {
   EE_UINT16 msg_id;   
   EE_UINT8 size,
               next;   
   EE_UINT8 data[7];      
};

struct EE_FTT_CTRL_TYPE {
   EE_UINT8 head, 
               tot,
               transmitted;
};

extern struct EE_FTT_CTRL_BUFF_TYPE EE_FTT_CTRL_BUFF[EE_FTT_N_CTRL];
extern struct EE_FTT_CTRL_TYPE EE_FTT_CTRL;

/* GLOBAL SYSTEM STATUS section
 */
/* EE_FTT_status : store system status
 * EE_FTT_cont : a counter used to know witch is the actual data 
 * that we want to transmit
 */
extern EE_UINT8 EE_FTT_status;
extern EE_UINT8 EE_FTT_cont;

/* FUNCTION DECLARATION section
 */
void EE_FTT_stop_asynch (void);
#define EE_FTT_STOP_ASYNCH EE_FTT_stop_asynch

void EE_FTT_transmitter (void);
#define EE_FTT_TRANSMITTER EE_FTT_transmitter

void EE_FTT_confirm (EE_UINT8 msg_id[], EE_UINT8 result);
void EE_FTT_indication (EE_UINT8 msg_id[], EE_UINT8 len, EE_UINT8 data[]);
EE_UINT8 EE_FTT_ctrl_buf_req (EE_UINT16 msg_id);

void EE_FTT_PROTO_init_handler (void);  
void EE_FTT_PROTO_set_handler (EE_UINT16 set_rel);  
void EE_FTT_PROTO_reset_handler (void);  

EE_UINT8 EE_FTT_start (void);

#ifdef EE_FTT_N_SYNCH
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_Snotify (EE_UINT8 msg_pos, EE_UINT8 type);
void EE_FTT_SMS_consume (EE_UINT8 msg_id, EE_UINT8 * size, EE_UINT8 data[]);
void EE_FTT_SMS_produce (EE_UINT8 msg_pos, EE_UINT8 msg_data[]);
EE_UINT8 EE_FTT_SRT_add (EE_UINT8 msg_pos);
EE_UINT8 EE_FTT_SRT_change (EE_UINT8 msg_pos, struct EE_FTT_SPARAM_TYPE * param);
EE_UINT8 EE_FTT_SRT_remove (EE_UINT8 msg_pos);
EE_UINT8 EE_FTT_Ssearch (EE_UINT16 msg_id);
#endif

#ifdef EE_FTT_N_RT
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_Snotify (EE_UINT8 msg_pos, EE_UINT8 type);
EE_UINT8 EE_FTT_ART_add (EE_UINT8 msg_pos);
EE_UINT8 EE_FTT_ART_change (EE_UINT8 msg_pos, struct EE_FTT_RT_PARAM_TYPE * param);
EE_UINT8 EE_FTT_ART_remove (EE_UINT8 msg_pos);
EE_UINT8 EE_FTT_Asearch (EE_UINT16 msg_id);
EE_UINT8 EE_FTT_AMS_RECEIVE (EE_UINT8 msg_pos, EE_UINT8 * size, EE_UINT8 msg_data[]);
EE_UINT8 EE_FTT_AMS_SEND (EE_UINT8 msg_pos, EE_UINT8 msg_data[]);
#endif

#ifdef EE_FTT_NRTT
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_NRTTnotify (EE_UINT8 msg_pos, EE_UINT8 type);
EE_UINT8 EE_FTT_NRTTsearch (EE_UINT16 msg_id);
EE_UINT8 EE_FTT_NRT_SEND (EE_UINT8 msg_pos, EE_UINT8 msg_data[]);
#endif

#ifdef EE_FTT_NRTR
__INLINE__ void __ALWAYS_INLINE__ EE_FTT_NRTRnotify (EE_UINT8 msg_pos, EE_UINT8 type);
EE_UINT8 EE_FTT_NRTRsearch (EE_UINT16 msg_id);
EE_UINT8 EE_FTT_NRT_RECEIVE (EE_UINT8 msg_pos, EE_UINT8 msg_data[]);
#endif


/* MESSAGES DEFINITION section
 */
/* Synchronous messages
 */ 
#define EE_FTT_DEFINE_SYNCH_MESSAGE_TRANSMIT(id,tx_time,per,phase,dline,size,action,call) \
EE_UINT8 EE_FTT_SDATA##id[size];   \
struct EE_FTT_SYNCH_MSG_RAM_TYPE EE_FTT_SYNCH_RAM##id = { per, dline, action };   \
const struct EE_FTT_SYNCH_MSG_ROM_TYPE EE_FTT_SYNCH_ROM##id = {id, tx_time, size, phase, call, EE_FTT_SDATA##id}

#define EE_FTT_DEFINE_SYNCH_MESSAGE_RECEIVE(id,size,action,call) \
EE_UINT8 EE_FTT_SDATA##id[size];   \
struct EE_FTT_SYNCH_MSG_RAM_TYPE EE_FTT_SYNCH_RAM##id = { 0,0, action }; \
const struct EE_FTT_SYNCH_MSG_ROM_TYPE EE_FTT_SYNCH_ROM##id = {id, 0, size, 0, call, EE_FTT_SDATA##id}

/* Sporadic real-time messages
 */
#define EE_FTT_DEFINE_RT_MESSAGE_TRANSMIT(id,tx_time,mit,dline,size,action,call)   \
EE_UINT8 EE_FTT_RT_BUFFER##id[size]; \
const struct EE_FTT_RT_ROM_TYPE EE_FTT_RT_ROM##id = {id, tx_time, size, call, EE_FTT_RT_BUFFER##id};  \
struct EE_FTT_RT_RAM_TYPE EE_FTT_RT_RAM##id = {mit,dline,action}

#define EE_FTT_DEFINE_RT_MESSAGE_RECEIVE(id,size,action,call)   \
EE_UINT8 EE_FTT_RT_BUFFER##id[size]; \
const struct EE_FTT_RT_ROM_TYPE EE_FTT_RT_ROM##id = {id, 0, size, call, EE_FTT_RT_BUFFER##id};  \
struct EE_FTT_RT_RAM_TYPE EE_FTT_RT_RAM##id = {0,0,action}

/* Non real-time messages
 */
#define EE_FTT_DEFINE_NRT_MESSAGE_RECEIVE(id,size,length,action,call)   \
EE_UINT8 EE_FTT_NRTR_BUFF_DATA##id[size*length]; \
const struct EE_FTT_NRTR_MSG_ROM_TYPE EE_FTT_NRTR_MSG_ROM##id = {id, length, size, call, EE_FTT_NRTR_BUFF_DATA##id};  \
struct EE_FTT_NRTR_MSG_RAM_TYPE EE_FTT_NRTR_MSG_RAM##id = {0,0,0,action}

#define EE_FTT_DEFINE_NRT_MESSAGE_TRANSMIT(id,size,action,call)   \
const struct EE_FTT_NRTT_MSG_ROM_TYPE EE_FTT_NRTT_MSG_ROM##id = {id, size, call};   \
EE_UINT16 EE_FTT_NRTT_MSG_RAM##id = action


#define EE_FTT_INSERT_SYNCH_MSG_RAM(id) &EE_FTT_SYNCH_RAM##id
#define EE_FTT_INSERT_SYNCH_MSG_ROM(id) &EE_FTT_SYNCH_ROM##id

#define EE_FTT_INSERT_RT_MSG_ROM(id) &EE_FTT_RT_ROM##id
#define EE_FTT_INSERT_RT_MSG_RAM(id) &EE_FTT_RT_RAM##id

#define EE_FTT_INSERT_NRTR_MSG_ROM(id) &EE_FTT_NRTR_MSG_ROM##id
#define EE_FTT_INSERT_NRTR_MSG_RAM(id) &EE_FTT_NRTR_MSG_RAM##id

#define EE_FTT_INSERT_NRTT_MSG_ROM(id) &EE_FTT_NRTT_MSG_ROM##id
#define EE_FTT_INSERT_NRTT_MSG_RAM(id) 0

/* MACRO section
 */
#define EE_MASK_FTT_MSG_TYPE 0xF800
#define EE_FTT_TM 0x1000
#define EE_FTT_S 0x6000
#define EE_FTT_RT_DG 0xC000
#define EE_FTT_RT 0x8000
#define EE_FTT_CTRL_HURRY 0xA000
#define EE_FTT_CTRL_HP_S 0xB000
#define EE_FTT_CTRL_HP_A 0xB800
#define EE_FTT_CTRL_LP 0xE000
#define EE_FTT_NRT 0xF000
#define EE_FTT_RESET_MSG_TYPE 0x07FF

#define EE_MASK_FTT_HURRY_TYPE 0xFC00
#define EE_FTT_HURRY_REPLY 0xA400
#define EE_MASK_FTT_REPLY_TYPE 0xC0
#define EE_FTT_SLAVE_REPLY 0xC0

#define EE_MASK_FTT_CTRL_HURRY_TYPE 0xFC00
#define EE_FTT_CTRL_ART_REPLY 0xA400
#define EE_FTT_ART_REPLY_TYPE 0xC0

#define EE_MASK_FTT_PENDING 0x02
#define EE_SET_FTT_PENDING 0x02
#define EE_RESET_FTT_PENDING 0xFD
#define EE_FTT_PENDING 0x02

#define EE_MASK_FTT_TX_DOWNGRADED 0x10
#define EE_FTT_TX_DOWNGRADED 0x00
#define EE_SET_FTT_RT2DG 0x4000
#define EE_SET_FTT_DG2RT 0xBFFF

#define EE_MASK_FTT_MSG_PENDING 0x02
#define EE_FTT_MSG_PENDING 0x02
#define EE_SET_FTT_MSG_PENDING 0x02
#define EE_RESET_FTT_MSG_PENDING 0xFD

#define EE_MASK_FTT_ACTIVE 0x01
#define EE_SET_FTT_MSG_ACTIVE 0x01
#define EE_FTT_MSG_ACTIVE 0x01
#define EE_SET_FTT_MSG_NOT_ACTIVE 0x00

#define EE_SET_FTT_DOWNGRADE 0xFE
#define EE_SET_FTT_NOT_DOWNGRADE 0x01

#define EE_MASK_FTT_HURRY_NODE_ID 0x1F

#define EE_MASK_FTT_ACTION_TYPE 0x80
#define EE_FTT_ACTION_CALLBACK 0x00
#define EE_FTT_ACTION_TASK 0x80

#define EE_RESET_FTT_STATUS 0x80
#define EE_RESET_FTT_ERROR 0xF3
#define EE_SET_FTT_ERROR_DATA_NOT_SENT 0x04
#define EE_SET_FTT_BUFF_OVFL 0x02

#define EE_FTT_AW 0x00
#define EE_FTT_AW_CTRL 0x01
#define EE_FTT_AW_LP 0x03
#define EE_FTT_SW 0x04
#define EE_MASK_FTT_TW 0x07

#define EE_SET_FTT_AW_CTRL 0x01
#define EE_SET_FTT_AW_LP 0x02
#define EE_SET_FTT_SW 0x04
#define EE_MASK_FTT_SW 0x04
#define EE_RESET_FTT_TW 0xF8

#define EE_FTT_DATA_LOST 0x00
#define EE_FTT_DATA 0x01
#define EE_FTT_ADD_CHANGE_ACCEPTED 0x02
#define EE_FTT_MSG_DOWNGRADED 0x03
#define EE_FTT_DATA_SENT 0x04
#define EE_FTT_DATA_NOT_SENT 0x05
#define EE_FTT_MSG_ACTIVATED 0x06

/* INCLUDE INLINE FUNCTION section
 */
#include "sinline.c"

#endif

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
 * CVS: $Id: ee_master.h,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */
 
#ifndef __PSA_H__
#define __PSA_H__
/* Simbols
 */

/* User definitions
 *
 * EE_PSA_PERIODIC : If the user want to use only the periodic messages
 *    algorithm
 * EE_PSA_SPORADIC : If the user want to use only the sporadic messages
 *    algorithm
 * EE_PSA_N_PERIODIC : number of periodic messages allowed
 * EE_PSA_N_SPORADIC : number of sporadic messages allowed
 * EE_PSA_EC : the period of the elementary cycle
 * EE_PSA_X : the transmission time of a 8-bytes message
 *    used like idle time
 * EE_PSA_CAN_ID : to set the can identifier used to send 
 *    the elementary cycle
 * EE_PSA_LPW : to assign the guaranteed bandwidth to the periodic traffic
 * EE_PSA_LAW : to assign the guaranteed bandwidth to the poradic traffic
 * EE_PSA_MASTER_ID : the id of the master
 * EE_MUTEX_PERIODIC : The identifier of the mutex used in periodic 
 *    messages mutual exclusive access
 * EE_MUTEX_SPORADIC : The identifier of the mutex used in periodic 
 *    messages mutual exclusive access
 */
 
/* System definitions
 *
 * EE_PSA_TM_SIZE : size in bytes of the trigger message
 * EE_PSA_CTRL : the transmission time of the control message
 * EE_PSA_TM : the transmission time of the trigger message
 */
 
#define EE_PSA_TM_SIZE ((((EE_PSA_N_PERIODIC >> 2) +3) -1) >> 2) +1
#define EE_PSA_CTRL EE_PSA_X
#define EE_PSA_TM EE_PSA_X
#define EE_PSA_DISPATCHER (void *)((EE_psa_dispatcher)(void))
#define EE_PSA_SCHEDULER (void *)((EE_psa_time_control)(void))

/* System parameters
 *
 * pending_head : the head of the pending periodic messages
 * ready_head : the head of the periodic messages that 
                are waiting for the next activation
 * LSW_act : the actual periodic system load
 * LSW_guar : the guaranteed periodic system load
 * LAW_act : the actual sporadic system load
 * LAW_guar : the guaranteed sporadic system load
 */                 
struct EE_psa_sys_TYPE {
  EE_UINT8 pending_head;
  EE_UINT8 ready_head;
  #ifdef EE_PSA_PERIODIC
  EE_UINT16 LPW_act;
  #endif
  #ifdef EE_PSA_SPORADIC
  EE_UINT16 LAW_act;
  #endif
  EE_UINT8 lp_per, lp_spor; //usefull?
  EE_UINT8 node, node_max;
};

/* The trigger message (for the trigger message size see the documentation) */
struct EE_psa_tm_TYPE {
  EE_UINT8 id[2];
  EE_UINT8 size;
  EE_UINT8 value[EE_PSA_TM_SIZE];
};
 
/* Periodic messages parameters definition
 *
 * cont : time counter 
 * period : the message period
 * tx_time : the message transmission time
 * next : a link to the next periodic message
 * status : bitfield with the following meaning:
 *  -------x : 0 message not activated
 *             1 message activated
 *  ------x- : 0 message inserted in ready queue
 *             1 message inserted in pending queue
 *  x------- : 0 soft message
 *             1 hard message
 * (see documentation for more details)
 */
#ifdef EE_PSA_PERIODIC
struct EE_psa_periodic_TYPE {
  EE_INT16 count;
  EE_UINT16 period,
               tx_time,
               Unorm;
  EE_UINT8 next,
              status;
};  
#endif

/* Sporadic messages parameters definition
 *
 * tx_time : transmission time
 * dline : deadline of the message
 * mit : minimum interarival time
 * status : bitfield with the following meaning:
 *  -------x : 0 message not activated
 *             1 message activated
 *  ------x- : 0 message inserted in ready queue
 *             1 message inserted in pending queue
 */
#ifdef EE_PSA_SPORADIC
struct EE_psa_sporadic_TYPE {
  EE_UINT16 tx_time,
               Unorm,
               dline,
               tx_time,
               mit;
  EE_UINT8 status;
};
#endif

/* System definitions
 */
extern struct EE_psa_sys_TYPE EE_psa_sys;
extern struct EE_psa_tm_TYPE EE_psa_tm;
#ifdef EE_PSA_PERIODIC
extern struct EE_psa_periodic_TYPE EE_psa_periodic[EE_PSA_N_PERIODIC];
#endif
#ifdef EE_PSA_SPORADIC
extern struct EE_psa_sporadic_TYPE EE_psa_sporadic[EE_PSA_N_SPORADIC];
#endif

/* Functions definition
 */
void EE_psa_time_control (void);
void EE_psa_dispatcher (void);
void EE_psa_indication (EE_UINT8 *can_msg_id, EE_UINT8 size, EE_UINT8 *data);
void EE_psa_confirm (EE_UINT8 *can_msg_id, EE_UINT8 *data);
#ifdef EE_PSA_PERIODIC
void EE_psa_periodic_add (EE_UINT8 msg_id, EE_UINT8 *data);
void EE_psa_periodic_remove (EE_UINT8 msg_id);
void EE_psa_insert_ready(EE_UINT8 msg);
void EE_psa_insert_pending(EE_UINT8 msg);
void EE_psa_remove_ready(EE_UINT8 msg);
void EE_psa_remove_pending(EE_UINT8 msg);
#endif
#ifdef EE_PSA_SPORADIC
void EE_psa_sporadic_add (EE_UINT8 msg_id, EE_UINT8 *data);
void EE_psa_sporadic_remove (EE_UINT8 msg_id);
#endif
void EE_psa_start (void);

/* Masks, check, set and reset symbols
 *
 * EE_*_PSA_OVL used to check if there is an overload state in the network
 * EE_PSA_PHARD a value used to check if a deadline is an hard deadline
 * EE_RESET_PSA_PENDING it make a pending message a ready message
 * EE_MASK_PSA_REAL_ID used in periodic add to make the parameter msg_id a 
 *  real message id identifier
 * EE_MASK_PSA_QUEUE to check where is store a message (queue) 
 * EE_PSA_ACTRD a value to check if a message is an active message stored 
 *  in ready queue
 * EE_PSA_ACTPD a value to check if a message is an active message stored 
 *  in pending queue
 * EE_PSA_RESET_STATUS to reset activation and stored queue flags
 * EE_*_PSA_*OVL used to check set/reset overload state
 * EE_*_PSA_ACTIVE used to set a sporadic message active
 * EE_MASK_PSA_OVL_OP : used to check the requested operation under
 *  an overload state
 */

#define EE_MASK_PSA_OVL 0x03
#define EE_PSA_NO_OVL 0x00
#define EE_MASK_PSA_POVL 0x20
#define EE_PSA_POVL 0x20
#define EE_MASK_PSA_PTYPE 0x80
#define EE_PSA_PHARD 0x80
#define EE_SET_PSA_PHARD 0x80
#define EE_RESET_PSA_PHARD 0x7F
#define EE_RESET_PSA_PENDING 0xFD
#define EE_MASK_PSA_REAL_ID 0x7F
#define EE_MASK_PSA_QUEUE 0x03
#define EE_PSA_ACTRD 0x01
#define EE_PSA_ACTPD 0x03
#define EE_PSA_RESET_STATUS 0xFC
#define EE_RESET_PSA_POVL 0xEF
#define EE_SET_PSA_POVL 0x20
#define EE_RESET_PSA_SOVL 0xEF
#define EE_SET_PSA_SOVL 0x10
#define EE_RESET_PSA_OVL 0xCF
#define EE_MASK_PSA_ACTIVE 0x01
#define EE_SET_PSA_ACTIVE 0x01
#define EE_RESET_PSA_ACTIVE 0xFE

/* CAN frames identifier */
#define EE_MASK_PSA_CAN_TYPE 0xF1
#define EE_PSA_CAN_POVL 0x60
#define EE_PSA_CAN_SOVL 0x61
#define EE_PSA_CAN_PER 0x70
#define EE_PSA_CAN_SPOR 0x71

/* Admitted operation codes */
#define EE_MASK_PSA_CAN_OP 0xC0
#define EE_PSA_CAN_ADD 0x80
#define EE_PSA_CAN_REMOVE 0x00
#define EE_PSA_CAN_ADD_HARD 0xC0
#define EE_PSA_CAN_ADD_SOFT 0x80

#endif


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
 * CVS: $Id: initosekcom.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "com/osek/cominit.h"

/* Modes definition
 */
COMApplicationModeType EE_osekcom_validmodes[EE_OSEKCOM_N_MODE] = {EE_OSEKCOM_MODE_A};

/* ipdu definitions 
 */
/* Transmission 
 */
extern StatusType ipdu_callout(void);
EE_OSEKCOM_DEFINE_IPDU_DIRECT(VC_1,32,ipdu_callout,10,10,REVERSE);

/* Reception 
 */
EE_OSEKCOM_DEFINE_IPDU_RECEIVE(BATT_1,8,NULL,50,5,HILO_CONT);
EE_OSEKCOM_DEFINE_IPDU_RECEIVE(DRIVER_1,16,NULL,50,50,KEY_SWITCH);
EE_OSEKCOM_DEFINE_IPDU_RECEIVE(BRAKE_1,8,NULL,50,20,BRAKE);

/* Message definition 
 */
/* Transmission
 * Only IDLE message is trigger, all other messages are pending.
 */
extern void callback_txok(void);
extern void callback_txer(void);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(REVERSE,2,VC_1,0,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,DC_CURRENT_CTRL);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(DC_CURRENT_CTRL,8,VC_1,2,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,V12_POWER);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(V12_POWER,1,VC_1,10,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,BRAKE_SOL);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(BRAKE_SOL,1,VC_1,11,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,BACKUP_ALARM);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(BACKUP_ALARM,1,VC_1,12,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,WARN_LIGHT);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(WARN_LIGHT,7,VC_1,13,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,KEY_SWITCH);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(KEY_SWITCH,1,VC_1,20,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,FWD_REV);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(FWD_REV,1,VC_1,21,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,IDLE);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(IDLE,1,VC_1,22,EE_OSEKCOM_TRIGGERED,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,SHIFT_PROGRESS);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(SHIFT_PROGRESS,1,VC_1,23,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,MAIN_ACK);
EE_OSEKCOM_DEFINE_STATIC_MESSAGE(MAIN_ACK,1,VC_1,24,EE_OSEKCOM_PENDING,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL,EE_OSEKCOM_NULL);

/* Reception
 */                  
extern void callback_rxok(void);
extern void callback_rxer(void);                                                                      
EE_OSEKCOM_DEFINE_UNQUEUED_STATIC_MESSAGE(HILO_CONT,4,BATT_1,0,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,KEY_SWITCH);
EE_OSEKCOM_DEFINE_UNQUEUED_STATIC_MESSAGE(KEY_SWITCH_RUN,1,DRIVER_1,4,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,KEY_START);
EE_OSEKCOM_DEFINE_UNQUEUED_STATIC_MESSAGE(KEY_START,1,DRIVER_1,5,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,ACCEL);
EE_OSEKCOM_DEFINE_UNQUEUED_STATIC_MESSAGE(ACCEL,2,DRIVER_1,6,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,BRAKE);
EE_OSEKCOM_DEFINE_UNQUEUED_STATIC_MESSAGE(BRAKE,1,BRAKE_1,8,F_Always,NULL,EE_OSEKCOM_NO_ORDER,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_OK,EE_OSEKCOM_CB_ER,EE_OSEKCOM_CB_ER,NULL,NULL,EE_OSEKCOM_NULL);


/* Other config
 */
struct EE_osekcom_msg_RAM_TYPE * EE_osekcom_msg_RAM[EE_OSEKCOM_N_MSG] = {
  EE_osekcom_msg_RAM(HILO_CONT),
  EE_osekcom_msg_RAM(KEY_SWITCH_RUN),
  EE_osekcom_msg_RAM(KEY_START),
  EE_osekcom_msg_RAM(ACCEL),
  EE_osekcom_msg_RAM(BRAKE), 
  EE_osekcom_msg_RAM(REVERSE),      
  EE_osekcom_msg_RAM(DC_CURRENT_CTRL),                      
  EE_osekcom_msg_RAM(V12_POWER),                           
  EE_osekcom_msg_RAM(BRAKE_SOL),                   
  EE_osekcom_msg_RAM(BACKUP_ALARM),                     
  EE_osekcom_msg_RAM(WARN_LIGHT),                          
  EE_osekcom_msg_RAM(KEY_SWITCH),                          
  EE_osekcom_msg_RAM(FWD_REV),                           
  EE_osekcom_msg_RAM(IDLE),                               
  EE_osekcom_msg_RAM(SHIFT_PROGRESS),                    
  EE_osekcom_msg_RAM(MAIN_ACK)      
};                     
                        
const struct EE_osekcom_msg_ROM_TYPE * EE_osekcom_msg_ROM[EE_OSEKCOM_N_MSG] = {
  EE_osekcom_msg_ROM(HILO_CONT),
  EE_osekcom_msg_ROM(KEY_SWITCH_RUN),
  EE_osekcom_msg_ROM(KEY_START),
  EE_osekcom_msg_ROM(ACCEL),
  EE_osekcom_msg_ROM(BRAKE), 
  EE_osekcom_msg_ROM(REVERSE),      
  EE_osekcom_msg_ROM(DC_CURRENT_CTRL),                      
  EE_osekcom_msg_ROM(V12_POWER),                           
  EE_osekcom_msg_ROM(BRAKE_SOL),                   
  EE_osekcom_msg_ROM(BACKUP_ALARM),                     
  EE_osekcom_msg_ROM(WARN_LIGHT),                          
  EE_osekcom_msg_ROM(KEY_SWITCH),                          
  EE_osekcom_msg_ROM(FWD_REV),                           
  EE_osekcom_msg_ROM(IDLE),                               
  EE_osekcom_msg_ROM(SHIFT_PROGRESS),                    
  EE_osekcom_msg_ROM(MAIN_ACK)      
};

struct EE_osekcom_ipdu_RAM_TYPE * EE_osekcom_ipdu_RAM[EE_OSEKCOM_N_IPDU] = {
  EE_osekcom_ipdu_RAM(VC_1),
  EE_osekcom_ipdu_RAM(BATT_1),
  EE_osekcom_ipdu_RAM(DRIVER_1),
  EE_osekcom_ipdu_RAM(BRAKE_1)
};                     
                        
const struct EE_osekcom_ipdu_ROM_TYPE * EE_osekcom_ipdu_ROM[EE_OSEKCOM_N_IPDU] = {
  EE_osekcom_ipdu_ROM(VC_1),
  EE_osekcom_ipdu_ROM(BATT_1),
  EE_osekcom_ipdu_ROM(DRIVER_1),
  EE_osekcom_ipdu_ROM(BRAKE_1)
};                     

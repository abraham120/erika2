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

/*Definizione dei flag*/
EE_OSEKCOM_DEFINE_FLAG(data_in);
EE_TID task = 2;

/* Definizione dei messaggi */
/*RICEZIONE*/
EE_OSEKCOM_DEFINE_INTERNAL_UNQUEUED_MESSAGE(CENTRALINA1,32,F_Always,NULL,EE_OSEKCOM_T_OK,&task,CENTRALINA2);
EE_OSEKCOM_DEFINE_INTERNAL_QUEUED_MESSAGE(CENTRALINA2,32,F_Always,NULL,EE_OSEKCOM_F_OK,&data_in,2,EE_OSEKCOM_NULL);

/* TRASMISSIONE */
/* Message definition*/
EE_OSEKCOM_DEFINE_INTERNAL_MESSAGE(ABS,32,CENTRALINA1);


/* Altre configurazioni */
const struct EE_osekcom_msg_ROM_TYPE * EE_osekcom_msg_ROM[]=
  {
    EE_osekcom_msg_ROM(ABS),
    EE_osekcom_msg_ROM(CENTRALINA1),
    EE_osekcom_msg_ROM(CENTRALINA2)
  };

  struct EE_osekcom_msg_RAM_TYPE * EE_osekcom_msg_RAM[]=
    {
      EE_osekcom_msg_RAM(ABS),
      EE_osekcom_msg_RAM(CENTRALINA1),
      EE_osekcom_msg_RAM(CENTRALINA2)
    };

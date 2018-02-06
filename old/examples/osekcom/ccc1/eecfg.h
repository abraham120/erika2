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
 * Author: 2003 Paolo Gai
 * CVS: $Id: eecfg.h,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

/* Main configuration option of the kernel */

#ifdef __ST10__
#define __USR_STK_SIZE__ 40
#endif

#define THREAD_MAX 6

/* OSEK COM message configuration */
/* from V/C */
#define REVERSE 5 /* 31 */
#define DC_CURRENT_CTRL 6 /* 34 */
#define V12_POWER 7 /* 35 */
#define BRAKE_SOL 8 /* 37 */
#define BACKUP_ALARM 9 /* 38 */
#define WARN_LIGHT 10 /* 39 */
#define KEY_SWITCH 11 /* 40 */
#define FWD_REV 12 /* 44 */
#define IDLE 13 /* 46 */
#define SHIFT_PROGRESS 14 /* 48 */
#define MAIN_ACK 15 /* 53 */

/* to V/C (small) */
#define HILO_CONT 0 /* 14 from battery */
#define KEY_SWITCH_RUN 1 /* 15 from driver */
#define KEY_START 2 /* 16 from driver */
#define ACCEL 3 /* 17 from driver */
#define BRAKE 4 /* 18 from brakes */

/* OsekCOM ipdu configuration */
#define VC_1 0x00E0       /* frame id 7 standard frame, controller 0 */
#define BATT_1 0x0020  /* frame id 1 standard frame, controller 0 */
#define BRAKE_1 0x0180    /* frame id 12 standard frame, controller 0 */
#define DRIVER_1 0x0120     /* frame id 9 standard frame, controller 0 */

#define EE_MUTEX_OSEKCOM_MSG 0
#define EE_OSEKCOM_N_MSG 16 // The number of messages handled by the node

#define EE_MUTEX_OSEKCOM_IPDU 1
#define EE_OSEKCOM_N_IPDU 4 // The number of ipdu handled by the node

#define EE_OSEKCOM_N_MODE 1
#define EE_OSEKCOM_MODE_A 0
#define EE_OSEKCOM_ALARM 0
#define EE_OSEKCOM_PERIOD 1


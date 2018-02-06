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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: ee_board.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "ee_internal.h"

volatile char *ee_time_low_ptr   = (char *)(SIMSUPPORT_BASE + GET_TIME_ADDRESS_LO);
volatile char *ee_time_high_ptr  = (char *)(SIMSUPPORT_BASE + GET_TIME_ADDRESS_HI);
volatile char *ee_time_stop_ptr  = (char *)(SIMSUPPORT_BASE + STOP_TIME_ADDRESS);
volatile char *ee_time_rel_ptr   = (char *)(SIMSUPPORT_BASE + RELEASE_TIME_ADDRESS);

volatile char *ee_cycle_low_ptr  = (char *)(SIMSUPPORT_BASE + GET_CYCLE_ADDRESS_LO);
volatile char *ee_cycle_high_ptr = (char *)(SIMSUPPORT_BASE + GET_CYCLE_ADDRESS_HI);
volatile char *ee_cycle_stop_ptr = (char *)(SIMSUPPORT_BASE + STOP_CYCLE_ADDRESS);
volatile char *ee_cycle_rel_ptr  = (char *)(SIMSUPPORT_BASE + RELEASE_CYCLE_ADDRESS);

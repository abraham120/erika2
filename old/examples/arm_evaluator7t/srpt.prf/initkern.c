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
 * Author: 2001-2002 Paolo Gai, Alessandro Colantonio
 * CVS: $Id: initkern.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "ee.h"


/* ROM kernel descriptors */
EE_TYPERELDLINE th_period[PERIODIC_THREAD_MAX] = {
    0x08000000,
    0x04000000,
    0x02000000
};

const EE_TYPERELDLINE EE_th_reldline[THREAD_MAX] = {
    0x08000000,
    0x04000000,
    0x02000000,
    0x01000000
};

const EE_TYPEPRIO EE_th_ready_prio[THREAD_MAX] = {
    0x01,
    0x02,
    0x04,
    0x08
};

const EE_TYPEPRIO EE_th_dispatch_prio[THREAD_MAX] = {
    0x01,
    0x02,
    0x04,
    0x08
};

/* RAM kernel descriptors */
EE_TYPEABSDLINE EE_th_absdline[THREAD_MAX];

#if defined(__MULTI__) || defined(__WITH_STATUS__)
EE_TYPESTATUS EE_th_status[THREAD_MAX] = {
    EE_READY,
    EE_READY,
    EE_READY,
    EE_READY
};
#endif

EE_TYPENACT EE_th_nact[THREAD_MAX] = {
    0,
    0,
    0,
    0
};

EE_TID EE_th_next[THREAD_MAX] = {
    EE_NIL,
    EE_NIL,
    EE_NIL,
    EE_NIL
};

EE_TID EE_rqfirst  = EE_NIL;
EE_TID EE_stkfirst = EE_NIL;

EE_TYPEPRIO EE_sys_ceiling = 0x0000; // the ceiling of the first task

/* ROM */
const EE_TYPEPRIO EE_mutex_ceiling[MUTEX_MAX] = { 0x08 };

/* RAM */
EE_TYPEPRIO EE_mutex_oldceiling[MUTEX_MAX];

#ifdef __ENABLE_THREAD__
EE_TYPENACT EE_th_enabled[THREAD_MAX] = {
    1,
    1,
    1,
    1
};
#endif

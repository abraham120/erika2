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
 * Author: 2004 Antonio Fiaschi
 * CVS: $Id: initkern.c,v 1.2 2004/11/30 09:59:44 pj Exp $
 */

#include "erika.h"


/* ROM kernel descriptors */
ERIKA_TYPERELDLINE th_period[PERIODIC_THREAD_MAX] = {
    0x08000000,
    0x04000000,
    0x02000000
};

const ERIKA_TYPERELDLINE ERIKA_th_reldline[THREAD_MAX] = {
    0x08000000,
    0x04000000,
    0x02000000,
    0x01000000
};

const ERIKA_TYPEPRIO ERIKA_th_ready_prio[THREAD_MAX] = {
    0x01,
    0x02,
    0x04,
    0x08
};

const ERIKA_TYPEPRIO ERIKA_th_dispatch_prio[THREAD_MAX] = {
    0x01,
    0x02,
    0x04,
    0x08
};

/* RAM kernel descriptors */
ERIKA_TYPEABSDLINE ERIKA_th_absdline[THREAD_MAX];

#if defined(__MULTI__) || defined(__SEGM__) || defined(__WITH_STATUS__)
ERIKA_TYPESTATUS ERIKA_th_status[THREAD_MAX] = {
    ERIKA_READY,
    ERIKA_READY,
    ERIKA_READY,
    ERIKA_READY
};
#endif

ERIKA_TYPENACT ERIKA_th_nact[THREAD_MAX] = {
    0,
    0,
    0,
    0
};

ERIKA_TID ERIKA_th_next[THREAD_MAX] = {
    ERIKA_NIL,
    ERIKA_NIL,
    ERIKA_NIL,
    ERIKA_NIL
};

ERIKA_TID ERIKA_rqfirst  = ERIKA_NIL;
ERIKA_TID ERIKA_stkfirst = ERIKA_NIL;

ERIKA_TYPEPRIO ERIKA_sys_ceiling = 0x0000; // the ceiling of the first task

/* ROM */
const ERIKA_TYPEPRIO ERIKA_mutex_ceiling[MUTEX_MAX] = { 0x08 };

/* RAM */
ERIKA_TYPEPRIO ERIKA_mutex_oldceiling[MUTEX_MAX];

#ifdef __ENABLE_THREAD__
ERIKA_TYPENACT ERIKA_th_enabled[THREAD_MAX] = {
    1,
    1,
    1,
    1
};
#endif

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013 Bruno Morelli
 */

#ifndef EE_CAX_CONTEXT__
#define EE_CAX_CONTEXT__
#include "cpu/common/inc/ee_context.h"
extern EE_TID EE_std_endcycle_next_tid;

#ifdef __MONO__

/* With monostack, we need only the information that the task is stacked.  We
 * don't need to know which task it is, as there is no new stack to switch
 * to. */
#define EE_std_mark_tid_stacked(tid) ((EE_TID)-1)

#define EE_std_need_context_change(tid) ((tid) >= 0)

#endif /* __MONO__ */


#ifdef __MULTI__

#define EE_std_mark_tid_stacked(tid) ((tid) | (EE_TID)TID_IS_STACKED_MARK)

extern int EE_std_need_context_change(EE_TID tid);

/*TODO*/
#if 0
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID tid)
{
}
#endif
#endif /* __MULTI__ */

#endif /* EE_CAX_CONTEXT__ */

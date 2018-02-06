/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef _STATE_H_
#define _STATE_H_

#include "BswCommon.h"

#define TIMESINCEKEYON_TICK (50)    ///< Is the period of clock0 (incremented in FasterLoop as it has a 50 usec period)
extern void EcuFunctionReset(void);
extern void EcuDestructiveReset(void);

extern void EcuReset(void);
extern void MainStateSafe(void);
extern void UpdateClock(void);
extern void UpdateClock20msec(void);
extern uint32 GetClock0(void);
extern uint32 GetClock2(void);
extern uint32 GetClock3(void);
extern uint32 GetClockMsec(void);
extern boolean After(uint32 time0, uint32 period);
extern void StateTask(void);

/* Function declarations */
StdReturnType EcuCheckFuncReset(void);
void EcuClearSwFuncReset(void);
StdReturnType EcuCheckDestrReset(void);
void EcuClearSwDestrReset(void);
void EcuClearFuncReset(void);
void EcuClearDestrReset(void);
void MainState_Shutdown(void);

#endif      // _STATE_H_

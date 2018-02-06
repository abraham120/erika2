/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * CPU-dependent part of Autosar API
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#ifndef __EE_AS_CPU_H__
#define __EE_AS_CPU_H__

#ifdef __DCC__

/* In-line system calls for Diab compiler */
__asm static StatusType ActivateTask(TaskType TaskID)
{
% reg TaskID
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, TaskID
	li	r0, EE_ID_ActivateTask
	sc
}

__asm static StatusType TerminateTask(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_TerminateTask
	sc
}

__asm static StatusType ChainTask(TaskType TaskID)
{
% reg TaskID
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, TaskID
	li	r0, EE_ID_ChainTask
	sc
}

__asm static StatusType Schedule(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_Schedule
	sc
}

__asm static StatusType ForceSchedule(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_ForceSchedule
	sc
}
__asm static StatusType GetTaskID(TaskRefType TaskID)
{
% reg TaskID
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, TaskID
	li	r0, EE_ID_GetTaskID
	sc
}
__asm static StatusType GetTaskState(TaskType TaskID, TaskStateRefType State)
{
% reg TaskID, State
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, TaskID
	mr	r4, State
	li	r0, EE_ID_GetTaskState
	sc
}

__asm static void EnableAllInterrupts(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_EnableAllInterrupts
	sc
}
__asm static void DisableAllInterrupts(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_DisableAllInterrupts
	sc
}
__asm static void ResumeAllInterrupts(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_ResumeAllInterrupts
	sc
}
__asm static void SuspendAllInterrupts(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_SuspendAllInterrupts
	sc
}
__asm static void ResumeOSInterrupts(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_ResumeOSInterrupts
	sc
}
__asm static void SuspendOSInterrupts(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_SuspendOSInterrupts
	sc
}
#ifndef __OO_NO_RESOURCES__

__asm static StatusType GetResource(ResourceType ResID)
{
% reg ResID
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, ResID
	li	r0, EE_ID_GetResource
	sc
}
__asm static StatusType ReleaseResource(ResourceType ResID)
{
% reg ResID
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, ResID
	li	r0, EE_ID_ReleaseResource
	sc
}
#endif /* ! __OO_NO_RESOURCES__ */
#ifndef __OO_NO_EVENTS__

__asm static StatusType SetEvent(TaskType TaskID, EventMaskType Mask)
{
% reg TaskID, Mask
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, TaskID
	mr	r4, Mask
	li	r0, EE_ID_SetEvent
	sc
}
__asm static StatusType ClearEvent(EventMaskType Mask)
{
% reg Mask
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Mask
	li	r0, EE_ID_ClearEvent
	sc
}
__asm static StatusType GetEvent(TaskType TaskID, EventMaskRefType Event)
{
% reg TaskID, Event
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, TaskID
	mr	r4, Event
	li	r0, EE_ID_GetEvent
	sc
}
__asm static StatusType WaitEvent(EventMaskType Mask)
{
% reg Mask
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Mask
	li	r0, EE_ID_WaitEvent
	sc
}
#endif /* ! __OO_NO_EVENTS__ */
#ifndef __OO_NO_ALARMS__

__asm static void CounterTick(CounterType c)
{
% reg c
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, c
	li	r0, EE_ID_counter_tick
	sc
}
__asm static StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
% reg AlarmID, Info
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, AlarmID
	mr	r4, Info
	li	r0, EE_ID_GetAlarmBase
	sc
}
__asm static StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick)
{
% reg AlarmID, Tick
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, AlarmID
	mr	r4, Tick
	li	r0, EE_ID_GetAlarm
	sc
}
__asm static StatusType SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle)
{
% reg AlarmID, increment, cycle
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, AlarmID
	mr	r4, increment
	mr	r5, cycle
	li	r0, EE_ID_SetRelAlarm
	sc
}
__asm static StatusType SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle)
{
% reg AlarmID, start, cycle
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, AlarmID
	mr	r4, start
	mr	r5, cycle
	li	r0, EE_ID_SetAbsAlarm
	sc
}
__asm static StatusType CancelAlarm(AlarmType AlarmID)
{
% reg AlarmID
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, AlarmID
	li	r0, EE_ID_CancelAlarm
	sc
}
#endif /* ! __OO_NO_ALARMS__ */

__asm static AppModeType GetActiveApplicationMode(void)
{
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	li	r0, EE_ID_GetActiveApplicationMode
	sc
}
__asm static StatusType StartOS(AppModeType Mode)
{
% reg Mode
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Mode
	li	r0, EE_ID_StartOS
	sc
}
__asm static void ShutdownOS(StatusType Error)
{
% reg Error
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Error
	li	r0, EE_ID_ShutdownOS
	sc
}
#ifdef __OO_SEM__

__asm static StatusType WaitSem(SemRefType Sem)
{
% reg Sem
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Sem
	li	r0, EE_ID_WaitSem
	sc
}
__asm static void WaitSem(SemRefType Sem)
{
% reg Sem
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Sem
	li	r0, EE_ID_WaitSem
	sc
}
__asm static int TryWaitSem(SemRefType Sem)
{
% reg Sem
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Sem
	li	r0, EE_ID_TryWaitSem
	sc
}
__asm static StatusType PostSem(SemRefType Sem)
{
% reg Sem
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Sem
	li	r0, EE_ID_PostSem
	sc
}
__asm static int GetValueSem(SemRefType Sem)
{
% reg Sem
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, Sem
	li	r0, EE_ID_GetValueSem
	sc
}
#endif /* __OO_SEM__ */
#else /* __DCC__ */
#error "Compiler not supported"
#endif /* else __DCC__ */

#endif /* __EE_AS_CPU_H__ */

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.  ERIKA Enterprise is free software;
 * you can redistribute it and/or modify it under the terms of the
 * GPLv2 + Linking Exception license (contained in the file `ee/LICENSE').
 *
 * ERIKA Enterprise is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the license for more details.
 *
 * ###*E*### */

/*
 * Test project used to check MISRA compliance
 * Author: 2011 Bernardo  Dal Seno
 */
#include "ee_irq.h"
#include "ee.h"

#include "test/assert/inc/ee_assert.h"

#ifndef NULL
#define NULL 0
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

static volatile int xx;

#if (! defined(__MSRP__)) || (EE_CURRENTCPU == 0)
#define MY_ALARM MyAlarm
#define MY_COUNTER MainTimer
#define MY_RESOURCE MyResource

#else /* if ! __MSRP__ || EE_CURRENTCPU == 0 */
#define MY_ALARM OtherAlarm
#define MY_COUNTER OtherTimer
#define MY_RESOURCE MyOtherResource

#endif /* else if ! __MSRP__ || EE_CURRENTCPU == 0 */

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__

__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void)
{
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void)
{
  EE_hal_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void)
{
	xx = 3;
}

__INLINE__ void __ALWAYS_INLINE__ ChainTask(TaskType t)
{
	(void)ActivateTask(t);
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i)
{
	xx = 5;
#ifdef __MSRP__
	(void)EE_cpu_startos();
#endif
}

#define E_OK 0
typedef int StatusType;
__INLINE__ void __ALWAYS_INLINE__ ShutdownOS(StatusType s)
{
	xx = 10;
}

#define TICK_VAL 3

#else /* if __FP__ */

#define TICK_VAL 3U

#endif /* else if __FP__ */

DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);

void DecrIsr(void);
void FixedIntvIsr(void);

#ifdef __MSRP__
EE_TYPEBARRIER fake_barrier;
#endif /* __MSRP__ */


static void body1(void)
{
#if defined(__ALARMS__) || ((defined(__OO_BCC1__) || defined(__OO_BCC2__) \
		|| defined(__OO_ECC1__) || defined(__OO_ECC2__))	\
	&& (! defined (__OO_NO_ALARMS__)))
	TickType tt = (EE_TYPETICK)TICK_VAL;
#ifndef __FP__
	AlarmBaseType i;
	(void)GetAlarmBase(MY_ALARM, &i);
#endif /* __FP__ */

	(void)CounterTick(MY_COUNTER);
	(void)GetAlarm(MY_ALARM, &tt);
	(void)SetAbsAlarm(MY_ALARM, TICK_VAL, TICK_VAL);
	(void)SetRelAlarm(MY_ALARM, TICK_VAL, TICK_VAL);
	(void)CancelAlarm(MY_ALARM);
#endif /* __ALARMS__ */
	(void)ActivateTask(Task2);
	(void)EE_assert_and(2, 1, 1);
	(void)EE_assert_or(3, 2, 1);
#if defined(__OO_ECC2__) || defined(__OO_ECC1__)
	(void)SetEvent(Task2, MyEvent);
#endif /* __OO_EEC1__ || __OO_EEC2__ */
#ifndef __FP__
	(void)ForceSchedule();
#endif /* ! __FP__ */
	xx = 7;

#ifdef __MSRP__
	fake_barrier.value = 0U;
#endif /* __MSRP__ */

	(void)ChainTask(Task2);
}

static void body2(void)
{

#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
	EventMaskType e;
#endif

#if ((defined(__OO_BCC1__) || defined(__OO_BCC2__)		 	\
		|| defined(__OO_ECC1__) || defined(__OO_ECC2__))	\
		&& defined(__OO_SEM__))
	StatusType status;
#endif /* __OO_BCC1__ || __OO_BCC2__ */

#if ((defined(__OO_BCC1__) || defined(__OO_BCC2__)		 	\
		|| defined(__OO_ECC1__) || defined(__OO_ECC2__))	\
		&& defined(__OO_SEM__))
	SemRefType Sem=NULL;
	int my_res=0;
	my_res = GetValueSem(Sem);

#ifndef __PRIVATE_TRYWAITSEM__
	my_res = TryWaitSem(Sem);
#endif /* __PRIVATE_TRYWAITSEM__ */

#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_WAITSEM__

#ifdef __OO_EXTENDED_STATUS__
	status = WaitSem(Sem);
	status = PostSem(Sem);
#else
	WaitSem(Sem);
	PostSem(Sem);
#endif /* __OO_EXTENDED_STATUS__ */
#endif /* __PRIVATE_WAITSEM__ */
#endif /* __OO_ECC1__ || __OO_ECC2__ */

#endif /* __OO_BCC1__ || __OO_BCC2__ || __OO_ECC1__ || 
	__OO_ECC2__ && __OO_SEM__ */

#if defined(__OO_ECC2__) || defined(__OO_ECC1__)
	(void)GetEvent(Task2, &e);
	(void)WaitEvent(MyEvent);
	(void)ClearEvent(MyEvent);
#endif /* __OO_ECC2__ || __OO_ECC1__ */
	(void)Schedule();
	(void)ActivateTask(Task1);
#if ((defined(__OO_BCC1__) || defined(__OO_BCC2__)		 \
		|| defined(__OO_ECC1__) || defined(__OO_ECC2__)) \
	&& (! defined (__OO_NO_RESOURCES__)))			 \
	|| (defined(__FP__) && (! defined(__FP_NO_RESOURCE__)))
	(void)GetResource((EE_TYPERESOURCE)MY_RESOURCE);
	(void)ReleaseResource((EE_TYPERESOURCE)MY_RESOURCE);
#endif /* RESOURCES */
	(void)EE_assert_range(0, 1, 3);
	(void)EE_assert_last();
	if (xx > 1) {
		(void)ShutdownOS(E_OK);
	}
	(void)TerminateTask();
}

#if defined(__MSRP__)
extern EE_BIT EE_as_rpc_IOC[];
#endif

#if (! defined(__MSRP__)) || (EE_CURRENTCPU == 0)
TASK(Task1)
{
	body1();
}

TASK(Task2)
{
	body2();
}
#else /* if ! __MSRP__ || EE_CURRENTCPU == 0 */
TASK(Task3)
{
	body1();
	body2();
}
#endif /* else if ! __MSRP__ || EE_CURRENTCPU == 0 */

ISR2(DecrIsr)
{
	(void)ActivateTask(Task1);
}

ISR2(FixedIntvIsr)
{
	(void)ActivateTask(Task2);
}

/* MAIN function */
int main(void)
{
#if defined(__MSRP__)
	/* Dummy access just to prevent from compiler deadstripping */
	EE_as_rpc_IOC[0]=1U;
#endif

	(void)EE_assert(1, 1, EE_ASSERT_NIL);

	/* let's start the multiprogramming environment...*/
	(void)StartOS((AppModeType)OSDEFAULTAPPMODE);
	return 0;
}


#ifdef __OO_HAS_ERRORHOOK__
void ErrorHook(StatusType Error)
{
	xx = 18;
}
#endif /* __OO_HAS_ERRORHOOK__ */

#ifdef __OO_HAS_PRETASKHOOK__
void PreTaskHook(void)
{
	xx = 16;
}
#endif /* __OO_HAS_PRETASKHOOK__ */

#ifdef __OO_HAS_POSTTASKHOOK__
void PostTaskHook(void)
{
	xx = 17;
}
#endif /* __OO_HAS_POSTTASKHOOK__ */

#ifdef __OO_HAS_STARTUPHOOK__
void StartupHook(void)
{
	xx = 19;
}
#endif /* __OO_HAS_STARTUPHOOK__ */

#ifdef __OO_HAS_SHUTDOWNHOOK__
void ShutdownHook(StatusType Error)
{
	xx = 20;
}
#endif /* __OO_HAS_SHUTDOWNHOOK__ */

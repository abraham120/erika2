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

#include "ee_internal.h"
#include "ee_api.h"
#include "ee_irq.h"

#include "test/assert/inc/ee_assert.h"

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

#ifndef __EE_MEMORY_PROTECTION__
#define ISR2(f) static void f(void)
#endif


DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);

void DecrIsr(void);
void FixedIntvIsr(void);


static void body1(void)
{
#if defined(__ALARMS__) || ((defined(__OO_BCC1__) || defined(__OO_BCC2__) \
		|| defined(__OO_ECC1__) || defined(__OO_ECC2__))	\
	&& (! defined (__OO_NO_ALARMS__)))
	TickType tt = TICK_VAL;
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
	{
		EE_TYPEBARRIER fake_barrier;
		EE_e200zx_sync_barrier(&fake_barrier);
	}
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
	(void)GetResource(MY_RESOURCE);
	(void)ReleaseResource(MY_RESOURCE);
#endif /* RESOURCES */
	(void)EE_assert_range(0, 1, 3);
	(void)EE_assert_last();
	if (xx > 1) {
		(void)ShutdownOS(E_OK);
	}
	(void)TerminateTask();
}


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
#ifndef __PPCE200Z0__
	EE_e200zx_stop_fixed_intv();
#endif /* ! __PPCE200Z0__ */
}

static void init_decrementer_timer(void)
{
	EE_e200z7_register_ISR(10, &DecrIsr, (EE_UINT8)0U);
#ifndef __PPCE200Z0__
	EE_e200z7_setup_decrementer(8000000U);
#endif /* ! __PPCE200Z0__ */
}

/*
 * This function has been added just to remove some 
 * false positive flexlin errors.
 * If the three function called in "remove_false_positive"
 * are removed a cascade of false positive is generated.
 */
static void remove_false_positive(void)
{
#ifndef __PPCE200Z0__
	EE_e200zx_delay(0U);
	EE_e200z7_setup_decrementer_oneshot(0U);
	EE_e200z7_stop_decrementer();
#endif /* ! __PPCE200Z0__ */
}

static void init_fixed_timer(void)
{
	EE_e200z7_register_ISR(11, &FixedIntvIsr, (EE_UINT8)1U);
#ifndef __PPCE200Z0__
	EE_e200zx_setup_fixed_intv(64U-23U);
#endif /* ! __PPCE200Z0__ */
}

#if defined(__MSRP__)
static void fake_z0_entry(void)
{
	xx = 25;
}
#endif /* __MSRP__ */


/* MAIN function */
int main(void)
{
	(void)EE_assert(1, 1, EE_ASSERT_NIL);
	init_decrementer_timer();
	init_fixed_timer();
#if defined(__MSRP__) && (EE_CURRENTCPU == 0)
	EE_mpc5668_start_z0(&fake_z0_entry);
#endif /* __MSRP__ && EE_CURRENTCPU == 0 */
	/* let's start the multiprogramming environment...*/
	(void)StartOS(OSDEFAULTAPPMODE);
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

#ifndef __touch_kal_erika_h__
#define __touch_kal_erika_h__

#include <ee.h>
#include <touch_kal.h>
#include <touch_timer.h>

extern volatile uint32_t touch_kal_erika_time_counter;

void touch_kal_external_timer_action(void);

/* tick_duration is expressed in microseconds */
COMPILER_INLINE 
int8_t touch_kal_init(uint32_t tick_duration) 
{
	/* TODO: make use of this information to properly configure the
		 duration of the tick of the timer connected to the the
		 Counter fot the KAL tasks! */
	/* TODO: Fix all this hard-coding!!*/
	if (tick_duration != 0) {
		if (touch_timer_init(tick_duration, 40000) < 0)
			return -TOUCH_KAL_ERR_TIMER_INIT;
		touch_timer_set_isr_callback(touch_kal_external_timer_action);
		touch_timer_start(); // FIXME: start timer not by default but with touch_start!
	}
	
	return 1;
}

COMPILER_INLINE 
int8_t touch_kal_erika_set_body(void (*src)(void), void (**dst)(void)) 
{
	*dst = src;
	return 1;
}

COMPILER_INLINE 
int8_t touch_kal_erika_set_activation(TaskType tid, AlarmType aid, 
				     uint32_t offset,
				     uint32_t period) 
{
	/* FIXME: current implementation may not work w.r.t erika FP
		  need to solve the coherence in the calling sequence of
		  CancelAlarm and SetRelAlarm 
	*/
	if (offset != 0) { 
		CancelAlarm(aid);
		SetRelAlarm(aid, offset, period);
	} else {
		if (period == 0) {
			ActivateTask(tid);
		} else {
			ActivateTask(tid);
			CancelAlarm(aid);
			SetRelAlarm(aid, period, period);
		}
	}
	return 1;
}

COMPILER_INLINE 
int8_t touch_kal_erika_cancel_activation(AlarmType aid) 
{
	CancelAlarm(aid);
	return 1;
}

COMPILER_INLINE 
int8_t touch_kal_erika_mutex_wait(ResourceType res) 
{
	GetResource(res);
	return 1;
}

COMPILER_INLINE 
int8_t touch_kal_erika_mutex_signal(ResourceType res) 
{
	ReleaseResource(res);
	return 1;
}

#endif /* Header Protection */

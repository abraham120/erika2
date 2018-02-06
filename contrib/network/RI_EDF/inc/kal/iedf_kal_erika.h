/** 
* @file iedf_kal_erika.h
* @brief Erika KAL Implementation
* @author Christian Nastasi
* @author Gianluca Franchino  
* @version 0.1
* @date 2009-06-22
*/
#ifndef __iedf_kal_erika_h__
#define __iedf_kal_erika_h__

#include <ee.h>
#include <kal/iedf_kal.h>
#include <hal/iedf_timer.h>

#ifndef IEDF_HAL_BUS_FREQ
#define IEDF_HAL_BUS_FREQ 40000
#endif

extern volatile uint32_t iedf_kal_erika_time_counter;

void iedf_kal_external_timer_action(void);

/* tick_duration is expressed in microseconds */
COMPILER_INLINE 
int8_t iedf_kal_erika_init(uint32_t tick_duration) 
{
	/* TODO: make use of this information to properly configure the
		 duration of the tick of the timer connected to the the
		 Counter fot the KAL tasks! */
	/* TODO: Fix all this hard-coding!!*/
	if (tick_duration != 0) {
		#ifdef IEDF_HAL_EXTERNAL_TIMER
		/* TODO: call a user callback where the user can be notified 
			 about the kal tick_duration */
		#else
		if (iedf_timer_init(tick_duration, IEDF_HAL_BUS_FREQ) < 0)
			return -IEDF_KAL_ERR_TIMER_INIT;
		iedf_timer_set_isr_callback(iedf_kal_external_timer_action);
		iedf_timer_start();
		#endif
	}
	return 1;
}

COMPILER_INLINE uint32_t iedf_kal_get_time(void) 
{
	return iedf_kal_erika_time_counter;
}

COMPILER_INLINE 
int8_t iedf_kal_erika_set_body(void (*src)(void), void (**dst)(void)) 
{
	*dst = src;
	return 1;
}

COMPILER_INLINE 
int8_t iedf_kal_erika_set_activation(TaskType tid, AlarmType aid, 
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
int8_t iedf_kal_erika_cancel_activation(AlarmType aid) 
{
	CancelAlarm(aid);
	return 1;
}

 
COMPILER_INLINE 
int8_t iedf_kal_erika_mutex_wait(ResourceType res) 
{
	GetResource(res);
	return 1;
}

COMPILER_INLINE 
int8_t iedf_kal_erika_mutex_signal(ResourceType res) 
{
	ReleaseResource(res);
	return 1;
}

#define IEDF_KAL_TASK_ASYNC(task_id, priority)			\
static void (*IEDF_EE_TBODY_##task_id)(void) = 0;		\
TASK(IEDF_EE_TASK_##task_id)					\
{ 								\
	if (IEDF_EE_TBODY_##task_id != 0)			\
		IEDF_EE_TBODY_##task_id();			\
}

#define IEDF_KAL_TASK(task_id, priority)				\
static void (*IEDF_EE_TBODY_##task_id)(void) = 0;		\
TASK(IEDF_EE_TASK_##task_id)					\
{ 								\
	if (IEDF_EE_TBODY_##task_id != 0)			\
		IEDF_EE_TBODY_##task_id();			\
}

#define IEDF_KAL_MUTEX(mutex_id, task_id)			\

#define iedf_kal_init(tick_duration) 				\
iedf_kal_erika_init(tick_duration)				\

#define iedf_kal_set_body(task_id, task_body) 		 	\
iedf_kal_erika_set_body(task_body, &(IEDF_EE_TBODY_##task_id))	\


#define iedf_kal_set_activation(task_id, offset, period)		\
iedf_kal_erika_set_activation(IEDF_EE_TASK_##task_id, 		\
			      IEDF_EE_ALARM_##task_id,		\
			      offset, period)			\

#define iedf_kal_activate(task_id)				\
ActivateTask(IEDF_EE_TASK_##task_id)				\

#define iedf_kal_cancel_activation(task_id)			\
iedf_kal_erika_cancel_activation(IEDF_EE_ALARM_##task_id)		\


#define iedf_kal_mutex_wait(mutex_id)				\
iedf_kal_erika_mutex_wait(IEDF_EE_RESOURCE_##mutex_id)		\


#define iedf_kal_mutex_signal(mutex_id)				\
iedf_kal_erika_mutex_signal(IEDF_EE_RESOURCE_##mutex_id)		\


#endif /* Header Protection */

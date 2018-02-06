/** 
* @file uwl_kal_erika.h
* @brief Erika KAL Implementation
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_kal_erika_h__
#define __uwl_kal_erika_h__

#include <ee.h>
#include <kal/uwl_kal.h>
#include <hal/uwl_timer.h>

#ifndef UWL_HAL_BUS_FREQ
#define UWL_HAL_BUS_FREQ 40000
#endif

extern volatile uint32_t uwl_kal_erika_time_counter;

void uwl_kal_external_timer_action(void);

/* tick_duration is expressed in microseconds */
COMPILER_INLINE 
int8_t uwl_kal_erika_init(uint32_t tick_duration) 
{
	/* TODO: make use of this information to properly configure the
		 duration of the tick of the timer connected to the the
		 Counter fot the KAL tasks! */
	/* TODO: Fix all this hard-coding!!*/
	if (tick_duration != 0) {
		#ifdef UWL_HAL_EXTERNAL_TIMER
		/* TODO: call a user callback where the user can be notified 
			 about the kal tick_duration */
		#else
		if (uwl_timer_init(tick_duration, UWL_HAL_BUS_FREQ) < 0)
			return -UWL_KAL_ERR_TIMER_INIT;
		uwl_timer_set_isr_callback(uwl_kal_external_timer_action);
		uwl_timer_start();
		#endif
	}
	return 1;
}

COMPILER_INLINE uint32_t uwl_kal_get_time(void) 
{
	return uwl_kal_erika_time_counter;
}

COMPILER_INLINE 
int8_t uwl_kal_erika_set_body(void (*src)(void), void (**dst)(void)) 
{
	*dst = src;
	return 1;
}

COMPILER_INLINE 
int8_t uwl_kal_erika_set_activation(TaskType tid, AlarmType aid, 
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
int8_t uwl_kal_erika_cancel_activation(AlarmType aid) 
{
	CancelAlarm(aid);
	return 1;
}

 
COMPILER_INLINE 
int8_t uwl_kal_erika_mutex_wait(ResourceType res) 
{
	GetResource(res);
	return 1;
}

COMPILER_INLINE 
int8_t uwl_kal_erika_mutex_signal(ResourceType res) 
{
	ReleaseResource(res);
	return 1;
}

#define UWL_KAL_TASK_ASYNC(task_id, priority)			\
static void (*UWL_EE_TBODY_##task_id)(void) = 0;		\
TASK(UWL_EE_TASK_##task_id)					\
{ 								\
	if (UWL_EE_TBODY_##task_id != 0)			\
		UWL_EE_TBODY_##task_id();			\
}

#define UWL_KAL_TASK(task_id, priority)				\
static void (*UWL_EE_TBODY_##task_id)(void) = 0;		\
TASK(UWL_EE_TASK_##task_id)					\
{ 								\
	if (UWL_EE_TBODY_##task_id != 0)			\
		UWL_EE_TBODY_##task_id();			\
}

#define UWL_KAL_MUTEX(mutex_id, task_id)			\

#define uwl_kal_init(tick_duration) 				\
uwl_kal_erika_init(tick_duration)				\

#define uwl_kal_set_body(task_id, task_body) 		 	\
uwl_kal_erika_set_body(task_body, &(UWL_EE_TBODY_##task_id))	\


#define uwl_kal_set_activation(task_id, offset, period)		\
uwl_kal_erika_set_activation(UWL_EE_TASK_##task_id, 		\
			      UWL_EE_ALARM_##task_id,		\
			      offset, period)			\

#define uwl_kal_activate(task_id)				\
ActivateTask(UWL_EE_TASK_##task_id)				\

#define uwl_kal_cancel_activation(task_id)			\
uwl_kal_erika_cancel_activation(UWL_EE_ALARM_##task_id)		\


#define uwl_kal_mutex_wait(mutex_id)				\
uwl_kal_erika_mutex_wait(UWL_EE_RESOURCE_##mutex_id)		\


#define uwl_kal_mutex_signal(mutex_id)				\
uwl_kal_erika_mutex_signal(UWL_EE_RESOURCE_##mutex_id)		\


#endif /* Header Protection */

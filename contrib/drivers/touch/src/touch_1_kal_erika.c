/**
* @file touch_kal_erika.c
* @brief Erika Implementation for KAL
* @author Francesco Prosperi
* @version 0.0001
* @date 2009-07-02
*/
#include <ee.h>
#include <touch_1_kal_erika.h>

volatile uint32_t touch_1_kal_erika_time_counter = 0;

void touch_1_kal_external_timer_action(void)
{
	//touch_1_kal_erika_time_counter++;
	//CounterTick(TOUCH_COUNTER);
	ActivateTask(TASK_TOUCH_MANAGER_1);
}

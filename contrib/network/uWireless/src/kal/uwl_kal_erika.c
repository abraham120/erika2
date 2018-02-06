/** 
* @file uwl_kal_erika.c
* @brief Erika Implementation for KAL
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#include <kal/uwl_kal_erika.h>

volatile uint32_t uwl_kal_erika_time_counter = 0;

void uwl_kal_external_timer_action(void) 
{
	uwl_kal_erika_time_counter++;
	CounterTick(UWL_EE_TASK_COUNTER);                      
}

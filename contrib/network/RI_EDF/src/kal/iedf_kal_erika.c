/** 
* @file iedf_kal_erika.c
* @brief Erika Implementation for KAL
* @author Christian Nastasi 2009
* @author Gianluca Franchino 2012
* @version 0.1
* @date 2009-06-22
*/
#include <kal/iedf_kal_erika.h>

volatile uint32_t iedf_kal_erika_time_counter = 0;

void iedf_kal_external_timer_action(void) 
{
	iedf_kal_erika_time_counter++;
	CounterTick(IEDF_EE_TASK_COUNTER);                      
}

#include "ee_internal.h"

#ifdef __PIC32_ICD2__
int _ICD2RAM; /* TODO: is this still required? */
#endif

/*
 * Endcycle Next thread, Endcycle Next tos, nesting level
 */
EE_UREG EE_IRQ_nesting_level;
EE_ADDR EE_hal_endcycle_next_thread;
#ifdef __MULTI__
EE_UREG EE_hal_endcycle_next_tos;
#endif
#ifdef __IRQ_STACK_NEEDED__
EE_ADDR EE_pic32_temp_tos;
#endif

/*
 * thread_end_instance function
 */
void EE_thread_end_instance(void);

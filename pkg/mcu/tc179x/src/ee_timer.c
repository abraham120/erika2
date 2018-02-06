/* Jan Kleinsorge, 2010 */

#include "ee.h"
#include "ee_internal.h"
#include "cpu/tricore1/inc/ee_hal.h"
#include "mcu/tc179x/inc/ee_stm.h"
#include "mcu/tc179x/inc/ee_tc179xdefs.h"

#ifndef __PRIVATE_TIMEINIT__
void EE_time_init(void)
{
    register EE_FREG flags;
    flags = EE_hal_begin_nested_primitive();
    EE_tc179x_stm_init();
    EE_hal_end_nested_primitive(flags);
}
#endif


#ifndef __PRIVATE_HAL_GETTIME__
EE_TIME EE_hal_gettime(void)
{
    /* The tc179x has a 56bit counter of which we only use the lower
     * 32bits here. The STM ticks with at most the system frequency.
     * EE_time_init sets this up. By default the STM ticks at half that
     * frequency. */
    return 0xffffffff - EE_tc179x_stm_tim0.reg;
}

#endif





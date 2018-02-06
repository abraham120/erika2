/* Jan Kleinsorge, 2010 */

/* Support the programming of the General Clock Unit (GGCU) 
 *
 */

#include "ee.h"
#include "ee_internal.h"
#include "mcu/tc179x/inc/ee_scu.h"
#include "mcu/tc179x/inc/ee_wdt.h"
#include "mcu/tc179x/inc/ee_stm.h"
#include "mcu/tc179x/inc/ee_tc179xdefs.h"

#ifdef __TC1796__
#include "board/infineon_tc1796b/inc/ee_board.h"
#endif

#ifdef __TC1796__

/* Program the tc1796 GCU to PLL mode.
 *
 * The clock system should but doesn't need to be initialized.
 * Per default it runs at some pll base mode at lowered frequency.
 * This initialization here sets the CPU at its maximum frequency
 * and let's us be sure about its parameters. 
 *
 *
 * NOTE: On GNU invoked automatically (see ee_init.S)
 *
 */
void EE_tc179x_init_clock()
{
    EE_PLL_CLC clc;

    if (EE_tc179x_pll_clc.bits.BYPPIN)
        return;
    
    register EE_FREG flags;
    flags = EE_hal_begin_nested_primitive();

    clc.reg = 0;
    clc.bits.VCOBYP = 1;
    clc.bits.RESLD = 1;    
    clc.bits.KDIV = EE_TRIBOARD1796_PLL_KDIV - 1;
    clc.bits.NDIV = EE_TRIBOARD1796_PLL_NDIV - 1;
    clc.bits.PDIV = EE_TRIBOARD1796_PLL_PDIV - 1;
    clc.bits.VCOSEL = EE_TRIBOARD1796_PLL_VCOSEL;
    /* sysfs == 0: sys_freq == cpu_freq/2 */

    EE_wdt_unlock();
    EE_tc179x_pll_clc.bits.VCOBYP = 1;     /* VCO bypass */
    while(!EE_tc179x_pll_clc.bits.VCOBYP); /* Wait until we really do(!) */
    EE_tc179x_pll_clc.reg = clc.reg;       /* Reset PLL_CLC */
    EE_wdt_lock();

    while(!EE_tc179x_pll_clc.bits.LOCK);   /* Wait for phase lock */

    EE_wdt_unlock();
    EE_tc179x_pll_clc.bits.VCOBYP = 0;    /* Disable VCO bypass */
    EE_wdt_lock();

    EE_hal_end_nested_primitive(flags);
}


/* Returns the currently defined CPU clock frequency in Hz 
 * 
 * We assume 'PLL Mode' of the PLL circuit. 
 *
 * FIXME: Implement EE_tc179x_GCU_init to have a guaranteed state
 *        there.
 */
EE_UINT32 EE_tc179x_cpu_freq(void)
{

    EE_PLL_CLC clc = EE_tc179x_pll_clc_nv;
    EE_UREG k = 1 + clc.bits.KDIV;
    EE_UREG n = 1 + clc.bits.NDIV;
    EE_UREG p = 1 + clc.bits.PDIV;
    EE_UINT32 freq;

    if (clc.bits.BYPPIN) {
        freq = EE_TRIBOARD1796_OSC_FREQ_HZ;  /* Direct Drive Mode */
    } else {
        if (clc.bits.VCOBYP) {
            freq =EE_TRIBOARD1796_OSC_FREQ_HZ / (p * k); /* VCO Bypass Mode */
        } else {
            freq = (n * EE_TRIBOARD1796_OSC_FREQ_HZ) / (p * k); /* PLL Mode */
        }
    }    
    return freq;
}


/*  Returns the currently defined CPU clock frequency in Hz
 *
 */
EE_UINT32 EE_tc179x_sys_freq(void)
{
    EE_UINT32 cpuf = EE_tc179x_cpu_freq();
    EE_PLL_CLC clc = (EE_PLL_CLC)EE_tc179x_pll_clc_nv; 
    return cpuf >> (1 - clc.bits.SYSFS);
}


#else

#error Other MCU not supported.

#endif

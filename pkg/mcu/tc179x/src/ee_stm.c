/* Jan Kleinsorge, 2010 */

#include "ee_internal.h"
#include "mcu/tc179x/inc/ee_mcu.h"
#include "mcu/tc179x/inc/ee_stm.h"
#include "mcu/tc179x/inc/ee_tc179xdefs.h"

#ifdef __TC1796__


void EE_tc179x_stm_init(void)
{
    EE_STM_CLC clc;
    clc = EE_tc179x_stm_clc;
    clc.bits.DISR = 0;          /* Enable STM */
    clc.bits.RMC = 1;           /* STM freq. == System freq. / RMC */
    EE_tc179x_stm_clc = clc;
    while (clc.bits.DISS);      /* Wait for activation */
}


void EE_tc179x_stm_cmp0_init(EE_UINT8 iv, EE_UINT32 match)
{
    register EE_FREG flags;
    flags = EE_hal_begin_nested_primitive();
    
    /* Clear pending interrupts at STM */
    EE_tc179x_stm_isrr.bits.CMP0IRR = 1;
    EE_tc179x_stm_isrr.bits.CMP1IRR = 1;

    /* Clear pending interupt at SRN */
    EE_tc179x_stm_src0.bits.CLRR = 1;
    EE_tc179x_stm_src0.bits.CLRR = 1;
    
    /* Assign cmp-regs to SRN0 resp. SRN1 */
    EE_tc179x_stm_icr.bits.CMP0OS = 0;
    EE_tc179x_stm_icr.bits.CMP1OS = 1;

    /* Define compare interval register state */
    EE_STM_CMCON con = { .reg = 0 };    
    con.bits.MSTART0 = 0;
    con.bits.MSIZE0 = 31;
    EE_tc179x_stm_cmcon = con;

    /* Program service request control register */
    if (iv) {
        EE_STM_SRC0 src = { .reg = 0 };
        src.bits.SRPN = iv;   /* Priority/Interrupt vector */
        src.bits.TOS  = 0;    /* CPU handles this */
        src.bits.SRE  = 1;    /* Enable SRN */
        EE_tc179x_stm_src0.reg = src.reg; 
    }
    
    /* Prepare match register */    
    EE_tc179x_stm_cmp0.reg = match;

    /* Enable match register */
    EE_tc179x_stm_icr.bits.CMP0EN = 1;
    /* EE_tc179x_stm_icr.reg |= STM_ICR_CMP0EN_MASK; */
    /* For revisions < 5, use this: */
    /* EE_tc179x_stm_icr.reg = STM_ICR_CMP0EN_MASK | STM_ICR_CMP0OS_MASK; */

    EE_tc1_isync();

    /* NOTE: 
     * On TSIM, STM_ICR.CMP0IR always stays set irrespective of explicit
     * clearing. The internal state changes nevertheless.
     */

    EE_hal_end_nested_primitive(flags);
}


void EE_tc179x_stm_set_cmp0(EE_UINT32 match)
{
    EE_tc179x_stm_cmp0.reg = match;
}


EE_UINT32 EE_tc179x_stm_ticks_per_usec(void)
{
    EE_UINT32 sysf = EE_tc179x_sys_freq();
    EE_STM_CLC clc = EE_tc179x_stm_clc;
    EE_UINT32 stmf = sysf / clc.bits.RMC;
    return stmf / 1000000;
}


#else

#error Other MCU not supported.

#endif

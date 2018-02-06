/*******************************************************************************
* Freescale Semiconductor Inc.
* (c) Copyright 2011 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by FREESCALE in this matter are performed AS IS and without
any warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. FREESCALE neither guarantees nor will be
held liable by CUSTOMER for the success of this project.
FREESCALE DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED 
TO THE PROJECT BY FREESCALE, AND OR NAY PRODUCT RESULTING FROM FREESCALE 
SERVICES. IN NO EVENT SHALL FREESCALE BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL 
DAMAGES ARISING OUT OF THIS AGREEMENT.
CUSTOMER agrees to hold FREESCALE harmless against any and all claims demands 
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result 
of the advise or assistance supplied CUSTOMER in connection with product, 
services or goods supplied under this Agreement.
********************************************************************************
* File:             main.c
* Owner:            b08110
* Version:          1.4
* Date:             Oct-26-2011
* Classification:   General Business Information
* Brief:            pin toggle stationery for MPC5643L
********************************************************************************
* Detailed Description: 
*
*
* ------------------------------------------------------------------------------
* Test HW:  xPC564xLKIT, PPC5643L Cut3 silicon
* Target :  internal_FLASH, RAM
* Fsys:     120 MHz PLL0
* Debugger: Lauterbach Trace32. script for internal_FALSH run_from_flash.cmm
*                               script for RAM: run_from_run_vle_lsm
*
********************************************************************************
Revision History:
1.0     Apr-08-2011     b08110  Initial Version
1.1     Apr-12-2011     b08110  Fixed INTC interrupts (IVOR4 init).
                                Changed header file to Cut2 silicon.
1.2     Jul-08-2011     b08110  Modified Mode Entry sequence in order to enter
                                a different device mode along with a change
                                in device clocking.
1.3     Aug-26-2011     b08110  Corrected clk_out settings for output clock
                                (in the CGM)
1.4     Oct-26-2011     b08110  -Initialized all core registers in __start()
                                entry point - need for LockStep operation.
                                -Added Mode transition from SAFE to DRUN
                                in ClearFails().
                                -Removed call to ClearCF() after startup.
                                It is important to review critical faults 
                                and not to clear them automatically.
                                -Changed system clock frequency to 120 MHz.
*******************************************************************************/
#include <ee.h>
#include <ee_irq.h>
#include "stm.h"
#include "initHW.h"

#ifndef EE_ISR_DYNAMIC_TABLE
void STM_isr_handler(void);

ISR2(STM_isr_handler)
{
        /* perform a dummy activity */
        ActivateTask(Task1);

        /* clear request */
        mpc5643l_stm_clear_int(0);

        /* stop timer */
        mpc5643l_stm_disable();

        /* enable channel 0 to raise a new interrupt*/
        mpc5643l_stm_select_channel(0);

        /* initial counter value (equal to 0) */
        mpc5643l_stm_set_counter(0);

	/* start timer */
        mpc5643l_stm_enable();
}
#else
void STM_isr_handler(void);

void STM_isr_handler(void)
{
	register unsigned char ldok_test;

        /* perform a dummy activity */
        ActivateTask(Task1);

        /* clear request */
        mpc5643l_stm_clear_int(0);

        /* stop timer */
        mpc5643l_stm_disable();

        /* enable channel 0 to raise a new interrupt*/
        mpc5643l_stm_select_channel(0);

        /* initial counter value (equal to 0) */
        mpc5643l_stm_set_counter(0);

	/* start timer */
        mpc5643l_stm_enable();
}
#endif

static void init_stm_timer(void);

static void init_stm_timer(void)
{
        /* freeze anabled */
        mpc5643l_stm_freeze_on();

        /* set prescaler to 0x0 */
        mpc5643l_stm_set_prescaler(1);

        /* set compare register to 120000000: 1 sec supposing 120 Mhz clk */
        mpc5643l_stm_channel_cmp(0,120000000);

        /* enable channel 0 */
        mpc5643l_stm_select_channel(0);

        /* initial counter value */
        mpc5643l_stm_set_counter(0);

        /* start timer */
        mpc5643l_stm_enable();
}

/*******************************************************************************
* Global functions
*******************************************************************************/
DeclareTask(Task1);

TASK(Task1) {
	SIU.GPDO[52].R ^= 1;
	SIU.GPDO[53].R ^= 1;
	SIU.GPDO[54].R ^= 1;
	SIU.GPDO[55].R ^= 1;
	TerminateTask();
}

DeclareTask(Task2);

TASK(Task2){
	/* set stm */
	init_stm_timer();

	TerminateTask();
}

int main(void) 
{
    initHW();

#ifdef EE_ISR_DYNAMIC_TABLE
    EE_e200z7_register_ISR(30+16, STM_isr_handler, 15);
#endif

    StartOS(OSDEFAULTAPPMODE);

#ifdef __OO_STARTOS_OLD__
    while(1)
	;
#endif

    return 0;
}




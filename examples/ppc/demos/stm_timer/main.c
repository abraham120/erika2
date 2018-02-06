/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.  ERIKA Enterprise is free software;
 * you can redistribute it and/or modify it under the terms of the
 * GPLv2 + Linking Exception license (contained in the file `ee/LICENSE').
 *
 * ERIKA Enterprise is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the license for more details.
 *
 * ###*E*### */

/*
 * Example of use of the decrementer and the fixed-interval interrupts
 * Author: 2011 Bernardo  Dal Seno
 *         2012 Francesco Esposito
 */

#include <ee.h>
#include <ee_irq.h>
#include "board/axiom_mpc5674fxmb/inc/ee_board.h"
#include "ee_stm.h"

DeclareTask(Task1);

void delay(unsigned int value)
{
        volatile int i=0;
        for (i=0; i<value; i++)
                ;
}

void alert_stm(void)
{
        /* perform a dummy activity */
        ActivateTask(Task1);

        /* clear request */
        mpc5674f_stm_clear_int(0);

          /* stop timer */
        mpc5674f_stm_disable();

        /* enable channel 0 to raise a new interrupt*/
        mpc5674f_stm_select_channel(0);

        /* initial counter value (equal to 0) */
        mpc5674f_stm_set_counter(0);

        /* start timer */
        mpc5674f_stm_enable();
}

static void init_stm_timer(void)
{
        /* register isr */
        EE_e200z7_register_ISR(216, alert_stm, 15);

        /* freeze anabled */
        mpc5674f_stm_freeze_on();

        /* set prescaler to 0x0 */
        mpc5674f_stm_set_prescaler(1);

        /* set compare register to 0x400000 */
        mpc5674f_stm_channel_cmp(0,0x400000);

        /* enable channel 0 */
        mpc5674f_stm_select_channel(0);

        /* initial counter value */
        mpc5674f_stm_set_counter(0);

        /* start timer */
        mpc5674f_stm_enable();
}

TASK(Task1)
{
	delay(1000);
}

void main(void)
{
        init_stm_timer();
	StartOS(OSDEFAULTAPPMODE);
	EE_hal_enableIRQ();
	while (1) {
		/* Background loop */
	}
}

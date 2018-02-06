/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Simple test for IOC
 * Author: 2012 Francesco Esposito
 */
#include <ee.h>
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE 1U
#endif

#ifndef FALSE
#define FALSE 0U
#endif

/* assertion data and declarations */
EE_TYPEASSERTVALUE EE_assertions[27];

/* Task declarations */
DeclareTask(TaskReceive1);
DeclareTask(TaskReceive2);
DeclareTask(TaskReceive3);
DeclareTask(TaskReceive4);

/* Primitive type */
TASKParams3 dummy_data_slave, dummy_data_slave1, dummy_data_slave2;

/* Result */
static Std_ReturnType result = 0x0U;

TASK(TaskReceive1)
{
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    /* Receive IOC incoming data transmission (polling mode) */
    /* Ipotetica chiamata all'RTE sulla porta 0, item 2 */
    result = IocReceive_0(&dummy_data_slave);
    EE_assert(2, (result==IOC_E_OK), 1);
    EE_assert(3, (dummy_data_slave.c[9]==7), 2);

    result = IocReceive_0(&dummy_data_slave);
    EE_assert(4, (result==IOC_E_OK), 3);
    EE_assert(5, (dummy_data_slave.c[9]==8), 4);

    result = IocReceive_0(&dummy_data_slave);
    EE_assert(6, (result==IOC_E_OK), 5);
    EE_assert(7, (dummy_data_slave.c[9]==9), 6);

    /* Here 3 messages should be received succesfully */
    result = IocReceive_0(&dummy_data_slave);
    EE_assert(8, (result==IOC_E_NO_DATA), 7);

    result = IocReceive_0(&dummy_data_slave);
    EE_assert(9, (result==IOC_E_NO_DATA), 8);

    /* Activate task on master core to send new data */
    ActivateTask(TaskSend2);

	TerminateTask();
}

TASK(TaskReceive2)
{
    result = IocReceive_0(&dummy_data_slave);   /* Extract first element 
                                                and acknowledge "lost data" */
    EE_assert(10, (result==IOC_E_LOST_DATA && dummy_data_slave.c[9]==10), 9);

    result = IocReceive_0(&dummy_data_slave);   /* Extract second element */
    EE_assert(11, (result==IOC_E_OK && dummy_data_slave.c[9]==11), 10);

    result = IocReceive_0(&dummy_data_slave);   /* Extract 3-th */
    EE_assert(12, (result==IOC_E_OK && dummy_data_slave.c[9]==12), 11);

    result = IocReceive_0(&dummy_data_slave);   /* Extract 4-th */
    EE_assert(13, (result==IOC_E_OK && dummy_data_slave.c[9]==13), 12);

    result = IocReceive_0(&dummy_data_slave);   /* Extract 5-th */
    EE_assert(14, (result==IOC_E_OK && dummy_data_slave.c[9]==14), 13);

    result = IocReceive_0(&dummy_data_slave);   /* Get NO DATA since buffer
                                                has been emptied */
    EE_assert(15, (result==IOC_E_NO_DATA), 14);

    /* Reset buffer for new test */
    result = IocEmptyQueue_0();
    EE_assert(16, (result==IOC_E_OK), 15);

    result = IocReceive_0(&dummy_data_slave);
    EE_assert(17, (result==IOC_E_NO_DATA), 16);

    result = IocReceive_0(&dummy_data_slave);
    EE_assert(18, (result==IOC_E_NO_DATA), 17);

    /* Activate task on master core to send new data */
    ActivateTask(TaskSend3);

	TerminateTask();
}

TASK(TaskReceive3)
{
    result = IocReceiveGroup_0(&dummy_data_slave, &dummy_data_slave1,
        &dummy_data_slave2);
    EE_assert(19, (result==IOC_E_OK), 18);

    /* Activate task on master core to send new data */
    ActivateTask(TaskSend4);

	TerminateTask();
}

TASK(TaskReceive4)
{
    result = IocReceiveGroup_0(&dummy_data_slave, &dummy_data_slave1,
        &dummy_data_slave2);
    EE_assert(20, (result==IOC_E_LOST_DATA), 19);

    /* Reset buffer for new test */
    result = IocEmptyQueue_0();
    EE_assert(21, (result==IOC_E_OK), 20);

    result = IocReceiveGroup_0(&dummy_data_slave, &dummy_data_slave1,
        &dummy_data_slave2);
    EE_assert(22, (result==IOC_E_NO_DATA), 21);

    /* Activate task on master core to send new data */
    ActivateTask(TaskSend5);

	TerminateTask();
}

/*
 * MAIN TASK
 */
int main(void)
{
	/* Start Operating System */
	StartOS(OSDEFAULTAPPMODE);

	return 0;
}

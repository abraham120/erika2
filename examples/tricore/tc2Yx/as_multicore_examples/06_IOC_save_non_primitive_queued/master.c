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
 * Simple test for IOC (queued semantic & primitive data)
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
EE_TYPEASSERTVALUE EE_assertions[30];
extern EE_IOC_Buffer EE_SHARED_IDATA EE_ioc_enqueued_buffer[];
uint8 test_num=1;

/* Task declarations */
DeclareTask(TaskSend1);
DeclareTask(TaskSend2);
DeclareTask(TaskSend3);
DeclareTask(TaskSend4);
DeclareTask(TaskSend5);

/* Primitive type */
TASKParams3 dummy_data_master = {99, 66, {9,8,7,6,5,4,3,2,1,0}};
TASKParams3 dummy_data_master1 = {99, 66, {9,8,7,6,5,4,3,2,1,0}};
TASKParams3 dummy_data_master2 = {99, 66, {9,8,7,6,5,4,3,2,1,0}};

/* Result */
Std_ReturnType result = 0x0;

TASK(TaskSend1)
{
    uint8 i=0U;

    EE_assert(test_num, TRUE, EE_ASSERT_NIL);

    for (i=0; i<7; i++) {
        /* Call to generated function */
        result = IocSend_0(&dummy_data_master);

        /* Change a value just to hace something to check with the debugger */
        dummy_data_master.c[9] = dummy_data_master.c[9]+1;

        test_num++;

        if (i<5) {
            EE_assert(test_num, (result==IOC_E_OK), test_num-1);
        }
        else {
            EE_assert(test_num, (result==IOC_E_LIMIT), test_num-1);
        }
    }

    /* Test if buffer[0] has rejected a data */
    test_num++;
    EE_assert(test_num, (EE_ioc_enqueued_buffer[0].data_rejected ==
        EE_CBUFF_DATA_REJECTED), test_num-1);

    /* Reset buffer for new test */
    result = IocEmptyQueue_0();
    test_num++;
    EE_assert(test_num, (result==IOC_E_OK), test_num-1);

    /* Test if buffer[0] is available after IocEmptyQueue() */
    test_num++;
    EE_assert(test_num, (EE_ioc_enqueued_buffer[0].data_rejected ==
        EE_CBUFF_DATA_ACCEPTED), test_num-1);

    for (i=7; i<10; i++) {
        result = IocSend_0(&dummy_data_master);

        /* Change a value just to hace something to check with the debugger */
        dummy_data_master.c[9] = dummy_data_master.c[9]+1;

        test_num++;
        EE_assert(test_num, (result==IOC_E_OK), test_num-1);
    }

    /* Activate task on slave core to read data previously written */
    ActivateTask(TaskReceive1);

	TerminateTask();
}

TASK(TaskSend2)
{
    uint8 i=0U;

    /* Reset buffer for new test */
    result = IocEmptyQueue_0();
    test_num++;
    EE_assert(test_num, (result==IOC_E_OK), test_num-1);

    /* Start of another test */
    for (i=0; i<7; i++) {
        /* Call to generated function */
        result = IocSend_0(&dummy_data_master);

        /* Change a value just to hace something to check with the debugger */
        dummy_data_master.c[9] = dummy_data_master.c[9]+1;

        test_num++;

        if (i<5) {
            EE_assert(test_num, (result==IOC_E_OK), test_num-1);
        }
        else {
            EE_assert(test_num, (result==IOC_E_LIMIT), test_num-1);
        }
    }

    /* Activate task on slave core to read data previously written */
    ActivateTask(TaskReceive2);

    TerminateTask();
}

TASK(TaskSend3)
{
    /* Reset buffer for new test */
    result = IocEmptyQueue_0();
    EE_assert(23, (result==IOC_E_OK), 22);

    /* Call to generated function */
    result = IocSendGroup_0(&dummy_data_master, &dummy_data_master1,
        &dummy_data_master2);

    EE_assert(24, (result==IOC_E_OK), 23);

    /* Activate task on slave core to read data previously written */
    ActivateTask(TaskReceive3);

    TerminateTask();
}

TASK(TaskSend4)
{
    /* Call to generated function */
    result = IocSendGroup_0(&dummy_data_master, &dummy_data_master1,
        &dummy_data_master2);

    /* Call to generated function */
    result = IocSendGroup_0(&dummy_data_master, &dummy_data_master1,
        &dummy_data_master2);

    EE_assert(25, (result==IOC_E_LIMIT), 24);

    /* Activate task on slave core to read data previously written */
    ActivateTask(TaskReceive4);

    TerminateTask();
}

TASK(TaskSend5)
{
    /* Reset buffer for new test */
    result = IocEmptyQueue_0();
    EE_assert(26, (result==IOC_E_OK), 25);

    /* Write three new data (test number 27, 28, 29) */

    /* Call to generated function */
    result = IocSend_0(&dummy_data_master);
    EE_assert(27, (result==IOC_E_OK), 26);

    /* Call to generated function */
    result = IocSend_0(&dummy_data_master);
    EE_assert(28, (result==IOC_E_OK), 27);

    /*
     * Modify generated data to activate receive-callback functionality.
     * This is not normal since generated data cannot be modified, we do
     * that just to test Pull-callback functionality.
     */
    EE_ioc_enqueued_buffer[0].callback = IOC_CALLBACK_YES;

    /* Now receive callback is enabled, write new data to activate
    callback capability */

    /* Call to generated function */
    result = IocSend_0(&dummy_data_master);
    EE_assert(29, (result==IOC_E_OK), 28);

    /* On the slave core we expect a callback able to receive
    these three new data */

    EE_assert_range(0,1, 29);
    EE_assert_last();

    TerminateTask();
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType status;

  StartCore(OS_CORE_ID_1, &status);

  /* Start Operating System */
  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

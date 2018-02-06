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
EE_TYPEASSERTVALUE EE_assertions[7];

/* Task declarations */
DeclareTask(TaskReceive1);
DeclareTask(TaskReceive2);

/* Value used by assert */
#define VALUE 0

/* Primitive type */
TASKParams3 dummy_data_slave, dummy_data_slave1, dummy_data_slave2;

/* Result */
Std_ReturnType result = 0x0U;

TASK(TaskReceive1)
{
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    /* Only the last write is find, the others have been lost */
    result = IocRead_0(&dummy_data_slave);
    EE_assert(2, (result==IOC_E_OK && dummy_data_slave.c[9] == VALUE+2), 1);

    /* Activate task on master core to start new test*/
    ActivateTask(TaskSend2);

	TerminateTask();
}

TASK(TaskReceive2)
{
    /* Call to generated function */
    result = IocReadGroup_0(&dummy_data_slave, &dummy_data_slave1,
        &dummy_data_slave2);

    EE_assert(3, (result==IOC_E_OK &&
        dummy_data_slave.c[9] == VALUE), 2);
    EE_assert(4, (result==IOC_E_OK &&
        dummy_data_slave1.c[9] == VALUE+1), 3);
    EE_assert(5, (result==IOC_E_OK &&
        dummy_data_slave2.c[9] == VALUE+2), 4);

    /* Activate task on master core to start new test*/
    ActivateTask(TaskSend3);

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

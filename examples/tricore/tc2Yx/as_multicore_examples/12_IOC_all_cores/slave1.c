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

/* Value used by assert */
#define VALUE 33

/* assertion data and declarations */
EE_TYPEASSERTVALUE EE_assertions[4];

TASKParams3 dummy_slave1_receive;
TASKParams3 dummy_data_slave1 = {99, 66, {9,8,7,6,5,4,3,2,1,VALUE}};

/* Result */
Std_ReturnType result = 0x0;

/* Task declarations */
DeclareTask(TaskSlave1);

TASK(TaskSlave1)
{
    /* Send new data to the master core */
    result = IocSend_2(&dummy_data_slave1);   /* ...to master (e.g. buffer 2) */
    EE_assert(3, (result==IOC_E_OK &&
        ((TASKParams3*)EE_ioc_enqueued_buffer[2].memory)->c[9] == VALUE), 2);

    ActivateTask(master_receive1);

    EE_assert_range(0, 1, 3);
    EE_assert_last();

	TerminateTask();
}

/*
 * MAIN TASK
 */
int main(void)
{
    EE_assert(1, TRUE, EE_ASSERT_NIL);

	/* Start Operating System */
	StartOS(OSDEFAULTAPPMODE);

	return 0;
}

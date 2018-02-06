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
EE_TYPEASSERTVALUE EE_assertions[5];

/* Value used by assert */
#define VALUE 0

/* Non Primitive type */
TASKParams3 dummy_data_master_receive;
TASKParams3 dummy_data_master = {99, 66, {9,8,7,6,5,4,3,2,1,VALUE}};
TASKParams3 dummy_data_master1 = {99, 66, {9,8,7,6,5,4,3,2,1,VALUE+1}};

/* Result */
Std_ReturnType result = 0x0;

/* Task declarations */
DeclareTask(TaskSend1);
DeclareTask(master_receive1);

TASK(TaskSend1)
{
  EE_assert(1, TRUE, EE_ASSERT_NIL);

  /* Reset buffer for new test */
  result = IocSend_0(&dummy_data_master); /* ...to slave1 (e.g. buffer 0) */
  EE_assert(2, (result==IOC_E_OK &&
      ((TASKParams3*)EE_ioc_enqueued_buffer[0].memory)->c[9] == VALUE), 1);

  result = IocSend_1(&dummy_data_master1); /* ...to slave2 (e.g. buffer 1) */
  EE_assert(3, (result==IOC_E_OK &&
      ((TASKParams3*)EE_ioc_enqueued_buffer[1].memory)->c[9] == VALUE+1), 2);

  TerminateTask();
}

TASK(master_receive1)
{
    result = IocReceive_2(&dummy_data_master_receive);
    EE_assert(4, (result==IOC_E_OK &&
        dummy_data_master_receive.c[9] == 33), 3);

    EE_assert_range(0, 1, 4);
    EE_assert_last();

    TerminateTask();
}

/*
 * MAIN TASK
 */
int main(void)
{
    StatusType status_slave1;
    StatusType status_slave2;

    /* Start slave cores */
    StartCore(OS_CORE_ID_1, &status_slave1);
    StartCore(OS_CORE_ID_2, &status_slave2);

    /* Start Operating System */
    StartOS(OSDEFAULTAPPMODE);

    return 0;
}

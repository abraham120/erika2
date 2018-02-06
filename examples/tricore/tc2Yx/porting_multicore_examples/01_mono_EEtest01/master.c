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
 * Simple project to test the second core (no interaction between cores)
 * Based on porting_examples mono_EEtest05
 * Author: 2012 Errico Guidieri
 */

#include <ee.h>

DeclareTask(TaskMaster);

/* Needed to avoid compilation errors */
TASK(TaskMaster)
{
  /* The followinr reading are used to tell the LINKER to not PRUNE shared kernel data structures.
     I didn't find a better way to do that :( (No options to pass to the LINKER). */
  volatile EE_UREG fake_access;
  fake_access = EE_rn_pending[0][0];
  fake_access = EE_rn_switch[0];
  fake_access = EE_rn_first[0][0];
  fake_access = EE_rn_cpu[0];
  fake_access = EE_rn_next[0][0];
  fake_access = EE_rn_task[0];
  fake_access = EE_rn_spin[0];
}


/*
 * MAIN TASK
 */
int main(void)
{
    /* StartOS call needed to unlock the barrier for the other core */
    StatusType ev;
    StartCore(OS_CORE_ID_1, &ev);
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

#include <ee.h>
#include <ee_internal.h>
#include <ee_irq.h>
#include "test/assert/inc/ee_assert.h"
#include "../../common/test_common.h"

#define TRUE  1U
#define FALSE 0U

#define MAX_ASSERT 70

#define IRQ_LOW     0U
#define IRQ_MEDIUM  1U
#define IRQ_HIGH    2U

#define IRQ_LOW_PRIO    EE_ISR_PRI_1
#define IRQ_MEDIUM_PRIO EE_ISR_PRI_2
#define IRQ_HIGH_PRIO   EE_ISR_PRI_3

static StatusType last_error;
static unsigned int error_count;

static unsigned int low_isr_hit;
static unsigned int medium_isr_hit;
static unsigned int high_isr_hit;

static int assert_count = EE_ASSERT_NIL;
static void assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[MAX_ASSERT + 1];

DeclareTask(Task1);

TASK(Task1)
{
  /* Do not release resources and do not call Terminate Task let kernel do the
     clean-up (as another test) */
  GetResource(Resource1);

  /* Firt IRQ stack */
  test_fire_irq(IRQ_LOW);
  assert(low_isr_hit == 1U);
  assert(medium_isr_hit == 1U);
  assert(high_isr_hit == 1U);
  assert(EE_oo_get_ISR2_TID() == EE_NIL);
  assert(EE_isr2_index == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK + 1] == EE_UREG_MINUS1);
  /* Second IRQ stack */
  GetResource(ResourceA);
  test_fire_irq(IRQ_LOW);
  assert(low_isr_hit == 1U);
  ReleaseResource(ResourceA);
  assert(low_isr_hit == 2U);
  assert(medium_isr_hit == 2U);
  assert(high_isr_hit == 2U);
  assert(EE_oo_get_ISR2_TID() == EE_NIL);
  assert(EE_isr2_index == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
  /* Third IRQ Stack */
  GetResource(ResourceB);
  test_fire_irq(IRQ_LOW);
  test_fire_irq(IRQ_MEDIUM);
  test_fire_irq(IRQ_HIGH);
}

void ErrorHook(StatusType Error)
{
  /* I cache error ID here to check that Error hook is called and that the
     right error is set */

  last_error = Error;
  ++error_count;
}

ISR2(IsrLow)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif /* __OO_EXTENDED_STATUS__ */
  ACK_IRQ(IRQ_LOW);
  if (low_isr_hit == 0U) {
    assert(EE_hal_get_int_prio() == IRQ_LOW_PRIO);
    GetResource(ResourceA);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_isr2_nesting_level[EE_isr2_index] == 1U);
    assert(EE_hal_get_int_prio() == IRQ_LOW_PRIO);
    test_fire_irq(IRQ_MEDIUM);
    assert(medium_isr_hit == 1U);
    assert(high_isr_hit == 1U);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    ReleaseResource(ResourceA);
    assert(EE_hal_get_int_prio() == IRQ_LOW_PRIO);
  } else if (low_isr_hit == 1U) {
    assert(EE_hal_get_int_prio() == IRQ_LOW_PRIO);
    GetResource(ResourceB);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_hal_get_int_prio() == IRQ_HIGH_PRIO);
    test_fire_irq(IRQ_MEDIUM);
    test_fire_irq(IRQ_HIGH);
    assert(medium_isr_hit == 1U);
    assert(high_isr_hit == 1U);
  } else if (low_isr_hit == 2U) {
    assert(high_isr_hit == 3U);
    assert(medium_isr_hit == 3U);
    GetResource(ResourceA);
    GetResource(ResourceB);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_hal_get_int_prio() == IRQ_HIGH_PRIO);
    assert(EE_th_resource_last[EE_MAX_TASK] == ResourceB);
#ifdef __OO_EXTENDED_STATUS__
    /* Error two more in error_count */
    s = ReleaseResource(ResourceA);
    assert(s == E_OS_NOFUNC);
    assert(EE_hal_get_int_prio() == IRQ_HIGH_PRIO);
#endif /* __OO_EXTENDED_STATUS__ */
  }
  ++low_isr_hit;
}

ISR2(IsrMedium)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif /* __OO_EXTENDED_STATUS__ */
  ACK_IRQ(IRQ_MEDIUM);
  if (medium_isr_hit == 0U) {
    assert(low_isr_hit == 0U);
    assert(EE_hal_get_int_prio() == IRQ_MEDIUM_PRIO);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    test_fire_irq(IRQ_HIGH);
    assert(high_isr_hit == 1U);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_hal_get_int_prio() == IRQ_MEDIUM_PRIO);
  } else if (medium_isr_hit == 1U) {
    assert(low_isr_hit == 2U);
    assert(high_isr_hit == 2U);
    assert(EE_hal_get_int_prio() == IRQ_MEDIUM_PRIO);
  } else if (medium_isr_hit == 2U) {
    assert(high_isr_hit == 3U);
    assert(low_isr_hit == 2U);
    /* You should not do this but API cannot prevent
       you on doing this */
    GetResource(ResourceB);
    assert(EE_oo_get_ISR2_TID() == EE_MAX_TASK);
    assert(EE_isr2_nesting_level[EE_isr2_index] == 1U);
    assert(EE_hal_get_int_prio() == IRQ_HIGH_PRIO);
    ReleaseResource(ResourceB);
#ifdef __OO_EXTENDED_STATUS__
    /* Error two more in error_count */
    s = GetResource(ResourceA);
    assert(s == E_OS_ACCESS);
    assert(EE_hal_get_int_prio() == IRQ_MEDIUM_PRIO);
    assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
#endif /* __OO_EXTENDED_STATUS__ */
  }
  ++medium_isr_hit;
}

ISR2(IsrHigh)
{
  ACK_IRQ(IRQ_HIGH);
  if (high_isr_hit == 0U) {
    GetResource(ResourceB);
    assert(medium_isr_hit == 0U);
    assert(EE_oo_get_ISR2_TID() == (EE_MAX_TASK + 1U));
    assert(EE_isr2_nesting_level[EE_isr2_index] == 3U);
    assert(EE_hal_get_int_prio() == IRQ_HIGH_PRIO);
    ReleaseResource(ResourceB);
  } else if (high_isr_hit == 1U) {
    assert(low_isr_hit == 2U);
    assert(medium_isr_hit == 1U);
    assert(last_error == E_OS_RESOURCE);
    assert(error_count == 1U);
  } else if (high_isr_hit == 2U) {
    assert(last_error == E_OS_MISSINGEND);
    assert(error_count == 2U);
    assert(medium_isr_hit == 2U);
    assert(low_isr_hit == 2U);
  }
  ++high_isr_hit;
}

int main(int argc, char *argv[])
{
#ifdef __CORTEX_MX__
  EE_system_init();
#endif

#ifdef EE_TRICORE__
  test_setup_irq(IRQ_LOW, IsrLow, EE_TC_1_ISR_PRI);
  test_setup_irq(IRQ_MEDIUM, IsrMedium, EE_TC_2_ISR_PRI);
  test_setup_irq(IRQ_HIGH, IsrHigh, EE_TC_3_ISR_PRI);
#endif

  StartOS(OSDEFAULTAPPMODE);

  ActivateTask(Task1);

  assert(last_error == E_OS_RESOURCE);
#ifdef __OO_EXTENDED_STATUS__
  assert(error_count == 5U);
#else
  assert(error_count == 3U);
#endif /* __OO_EXTENDED_STATUS__ */
  assert(EE_th_resource_last[Task1] == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK] == EE_UREG_MINUS1);
  assert(EE_th_resource_last[EE_MAX_TASK + 1] == EE_UREG_MINUS1);

  EE_assert_range(0, 1, assert_count); 

  EE_assert_last();

  return 0;
}

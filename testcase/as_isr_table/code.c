/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/* This include must be the first one because contains defines that shall be
   generate by RT-Druid in eecfg.h */
#include "isr_define.h"
#include <ee_irq.h>
#include <ee_internal.h>
#include "test/assert/inc/ee_assert.h"
#include "../../common/test_common.h"

#define TRUE  1U
#define FALSE 0U

#define IRQ_LOW     0
#define IRQ_MEDIUM  3
#define IRQ_HIGH    5

#define IRQ_LOW_PRIORITY     EE_PPCE200ZX_0_ISR_PRI
#define IRQ_MEDIUM_PRIORITY  EE_PPCE200ZX_3_ISR_PRI
#define IRQ_HIGH_PRIORITY    EE_PPCE200ZX_5_ISR_PRI


/* defined in oil file */
#define STACK_IRQ_SIZE      512U

#define MAX_ASSERT 30

static unsigned int low_isr_hit;
static unsigned int medium_isr_hit;
static unsigned int high_isr_hit;

static unsigned int task2_hit;

static int assert_count = EE_ASSERT_NIL;

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[MAX_ASSERT + 1];

static void fire_irq(unsigned int irq)
{
  if(irq > 5U)
    return;
  /* SHOOT THE IRQ */
  test_fire_irq(irq);
  EE_e200zx_mbar();
}

static void assert(int test)
{
  EE_assert(assert_count + 1, test, assert_count);
  ++assert_count;
}

#ifdef EE_GNU__
__INLINE__ EE_ADDR __ALWAYS_INLINE__ read_stack_pointer(void) {
  register EE_ADDR ret;
  __asm volatile ("mr %0, r1" : "=r"(ret));
  return ret;
}
#else
__asm static EE_ADDR read_stack_pointer(void) {
#ifdef __DCC__
  ! "r1","r3"
#endif /* __DCC__ */
  /* PPC EABI states that sp (stack pointer) is an alias for r1 */
  /* PPC EABI States that r3 is return register so I copy sp on r3 */
  mr r3, r1
}
#endif


#ifdef __IRQ_STACK_NEEDED__
__INLINE__ void __ALWAYS_INLINE__ assert_ISR_stack(void) {
  int comparison_result;
  EE_ADDR sp_temp;
  sp_temp = read_stack_pointer();
  /* The TOS (Top of the stack is putted at the stack's biggest address */
  comparison_result =   sp_temp <= EE_e200z7_IRQ_tos.SYS_tos;
  /* STACK_IRQ_SIZE is the IRQ stack size. Cast to let me do the math */
  comparison_result &=  sp_temp >= (EE_ADDR)(
    (unsigned int)EE_e200z7_IRQ_tos.SYS_tos - STACK_IRQ_SIZE);
  assert(comparison_result);
}

__INLINE__ void __ALWAYS_INLINE__ assert_sys_stack(void) {
  int comparison_result;
  EE_ADDR sp_temp;
  sp_temp = read_stack_pointer();
  comparison_result = sp_temp >= &EE_e200zx_sys_stack;
  /* EE_SYS_STACK_SIZE is the System stack size. Is defined in eecfg.h by
     RT-Druid */
  comparison_result &=  sp_temp <= 
      &EE_e200zx_sys_stack[EE_STACK_INITP(EE_SYS_STACK_SIZE)];
  assert(comparison_result);
}
#else
#define assert_ISR_stack()  ((void)0)
#define assert_sys_stack()  ((void)0)
#endif /* __IRQ_STACK_NEEDED__ */

DeclareTask(Task1);
DeclareTask(Task2);

void IsrLow(void);
void IsrMedium(void);
void IsrHigh(void);

ISR(IsrLow)
{
  register EE_ADDR sp_temp;
  ACK_IRQ(IRQ_LOW);
  assert_ISR_stack();
  sp_temp = read_stack_pointer();
  fire_irq(IRQ_MEDIUM);
  assert(sp_temp == read_stack_pointer());
  ++low_isr_hit;
}

ISR(IsrMedium)
{
  register EE_ADDR sp_temp;
  ACK_IRQ(IRQ_MEDIUM);
  assert_ISR_stack();
  ActivateTask(Task2);
  sp_temp = read_stack_pointer();
  fire_irq(IRQ_HIGH);
  assert(sp_temp == read_stack_pointer());
  ++medium_isr_hit;
}

ISR(IsrHigh)
{
  register EE_ADDR sp_temp;
  ACK_IRQ(IRQ_HIGH);
  assert_ISR_stack();
  ++high_isr_hit;
}


TASK(Task1)
{
  register EE_ADDR sp_temp;
  assert_sys_stack();
  sp_temp = read_stack_pointer();
  fire_irq(IRQ_LOW);
  assert(sp_temp == read_stack_pointer());
  assert_sys_stack();
  assert(task2_hit == 1);
  fire_irq(IRQ_HIGH);
  assert(sp_temp == read_stack_pointer());
  assert_sys_stack();
  assert(high_isr_hit == 2);
  TerminateTask();
}

TASK(Task2) {
  register EE_ADDR sp_temp;
  assert_sys_stack();
  assert(low_isr_hit == 1);
  assert(medium_isr_hit == 1);
  assert(high_isr_hit == 1);
  ++task2_hit;
  TerminateTask();
}

#ifdef EE_ISR_DYNAMIC_TABLE
__INLINE__ void __ALWAYS_INLINE__ initialize_isr_table(void)
{
  EE_e200z7_register_ISR(EE_E200ZX_MAX_CPU_EXCP + IRQ_LOW, IsrLow,
    IRQ_LOW_PRIORITY);
  EE_e200z7_register_ISR(EE_E200ZX_MAX_CPU_EXCP + IRQ_MEDIUM, IsrMedium,
    IRQ_MEDIUM_PRIORITY);
  EE_e200z7_register_ISR(EE_E200ZX_MAX_CPU_EXCP + IRQ_HIGH, IsrHigh,
    IRQ_HIGH_PRIORITY);
}
#define INITIALIZE_ISR_TABLE()  initialize_isr_table()
#else /* EE_ISR_DYNAMIC_TABLE */
#define INITIALIZE_ISR_TABLE()  ((void)0)
#endif /* EE_ISR_DYNAMIC_TABLE */


int main(void)
{
  register EE_ADDR sp_temp;
  INITIALIZE_ISR_TABLE();
  assert_sys_stack();
  sp_temp = read_stack_pointer();
  StartOS(OSDEFAULTAPPMODE);
  assert(sp_temp == read_stack_pointer());
  EE_assert_range(0, 1, assert_count);
  EE_assert_last();

  return 0;
}

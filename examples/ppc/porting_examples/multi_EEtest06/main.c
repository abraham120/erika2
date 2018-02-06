/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Simple project to test the all the context changes; it measure the time
 * used for different types of context changes.  Multistack, Osek BCC1 kernel.
 * Author: 2010 Fabio Checconi
 */


#include <ee.h>
#include <ee_irq.h>
#include "test/assert/inc/ee_assert.h"

/* For time measurements */
#include "timing.h"

/* started: Set to 1 at the beginning of main() */
int started;

/* Used by the ISR to discriminate between different firings */
int tick_counter;

/* Used inside Task 4 to discriminate between different activations */
int t4_counter;

/* A register not restored correctly? */
int error;

/* Assertions */
EE_TYPEASSERTVALUE EE_assertions[62];
/* Final result */
EE_TYPEASSERTVALUE result;

/* Event time instants */
volatile timer_t t2_before_irq1, th_caught_irq, th_end_irq, t2_before_irq2,
t4_start, t4_finish, t2_finish, t1_before_t3, t1_before_irq3, t3_wait, t1_wait,
t3_finish, t1_before_t5, t5_finish, t1_finish;

/* Context change timing */
timer_t irq_call1,      /* IRQ servicing time                   */
irq_call2,              /* Same                                 */
irq_return,             /* From ISR to interrupted task         */
irq_new_task,           /* From ISR to newly started task       */
end_task_after_irq,     /* Exit a task started from an ISR      */
end_task_new_task1,     /* Exit a task and launch a new one     */
activate_new_task1,     /* Activate and launch a new task       */
wait_switch,            /* Wait and switch to a suspendend task */
irq_call3,              /* IRQ servicing time                   */
irq_switch,             /* From ISR to suspended task           */
end_task1,              /* Exit a task (back to the interrupted one) */
activate_new_task2,     /* Activate and launch a new task       */
end_task_new_task2,     /* Exit a task and launch a new one     */
end_task2,              /* Exit a task (back to the interrupted one) */
end_task3;              /* Exit a task (back to the interrupted one) */
/* `activate_new_task2', `end_task_new_task2', `end_task2', and `end_task3' do
 * not involve a task switch even in the multistack version.  `end_task3' does
 * not involve an explicit call to TerminateTask() even with an Osek kernel. */

/*
 * Event sequence:
 
 T2 starts
  IRQ fires; ISR activates T1
  IRQ fires; ISR activates T4
   T4 starts and terminates
 T2 terminates
 T1 starts
 T1 activates T3
  T3 starts
  T3 waits for T1
  T1 wakes T3
  T3 terminates
 T1 activates T5
  T5 starts
  T5 activates T4
  T5 terminates
  T4 starts and terminates
 T1 terminates
 IRQ fires
 IRQ fires; ISR activates T6
 T6 starts
 T6 terminates all
 
 */

/***********************
 * Auxiliary functions
 ***********************/

/* Functions that exercise the registers */
#include "dirty_regs.h"

/*
 * End the program
 */
void terminate_all(void)
{
    extern void _exit(int);
    _exit(0);
}

/*
 * IRQ enabled?
 */
asm volatile int get_IRQ_enabled(void)
{
! "r3"
    mfmsr r3
    andi. r3, r3, 0x8000
}

/*
 * Stuff used for stack checking; disable canary-related checks if DEBUG_STACK
 * is not defined
 */
#ifndef DEBUG_STACK
#define check_all_pre_stack_canaries(x,y)       0
#endif
#include <cpu/e200zx/inc/ee_debug.h>

EE_ADDR base_toses[EE_MAX_TASK+1];
int num_toses;

__INLINE__ void check_stacks(EE_TID tid, EE_TYPEASSERT ass1, EE_TYPEASSERT ass2)
{
    EE_UREG ctos, etos, rtos;
    ctos = get_current_tos_index();
    etos = get_tos_index_for_task(tid);
    rtos = get_most_likely_tos_index(base_toses, num_toses);
    EE_assert(ass1, ctos == etos, EE_ASSERT_NIL);
    EE_assert(ass2, ctos == rtos, EE_ASSERT_NIL);
}


/*
 * Wait and wake up: use sempaphores with FP and events with ECC1 (Osek)
 */
__INLINE__ void wait_for_T1(void)
{
    WaitEvent(WakeUpEvent);
}

__INLINE__ void wake_up_T3(void)
{
    SetEvent(Task3, WakeUpEvent);
}

/***********************
 * Interrupts
 ***********************/

/*
 * Raise an interrupt immediately
 */
void fire_irq(void)
{
    EE_e200z7_setup_decrementer_oneshot(1);
}

/*
 *  Fire several periodic interrupts
 */
void fire_late_irqs(void)
{
    EE_e200z7_setup_decrementer(1000000);
}

/*
 * Stop periodic interrupts
 */
void stop_interrutps(void)
{
    EE_e200z7_stop_decrementer();
}

/*
 * Interrupt handler
 */
void interrupt_handler_body(void)
{
    ++tick_counter;
    switch(tick_counter) {
    case 1:
        /* First firing */
        EE_assert(3, 1, 2);
        irq_call1 = time_diff(t2_before_irq1, th_caught_irq);
        ActivateTask(Task1);
        EE_assert(4, 1, 3);
        break;
    case 2:
        /* Second firing */
        EE_assert(6, 1, 5);
        irq_call2 = time_diff(t2_before_irq2, th_caught_irq);
        ActivateTask(Task4);
        EE_assert(7, t4_start == 0, 6);
        break;
    case 3:
        /* Third firing */
        EE_assert(58, 1, 57);
        irq_call3 = time_diff(t1_before_irq3, th_caught_irq);
        wake_up_T3();
        break;
    case 4:
        /* Fourth firing */
        EE_assert(18, error == 0, 17);
        break;
    case 5:
        /* Fifth firing */
        stop_interrutps();
        ActivateTask(Task6);
        /* Check that registers have been restored correctly by the previous
           call to the ISR */
        EE_assert(19, error == 0, 18);
        break;
    }
}

void interrupt_handler(void)
{
    th_caught_irq = get_current_time();
    error = dirty_regs(&interrupt_handler_body, 48);
    switch (tick_counter) {
    case 1:
        EE_assert(20, error == 0, EE_ASSERT_NIL);
        break;
    case 2:
        EE_assert(21, error == 0, EE_ASSERT_NIL);
        break;
    case 3:
        EE_assert(61, error == 0, EE_ASSERT_NIL);
        break;
    case 4:
        EE_assert(22, error == 0, EE_ASSERT_NIL);
        break;
    case 5:
        EE_assert(23, error == 0, EE_ASSERT_NIL);
        break;
    }
    th_end_irq = get_current_time();
}

/*
 * Low-level initialization of the interrupts
 */
void init_interrupts(void)
{
    EE_e200z7_register_ISR(10, interrupt_handler, 0);
    EE_e200z7_enableIRQ();
}

/***********************
 * Tasks
 ***********************/


/*
 * Task 1
 */
void task1_activate_body(void)
{
    timer_t t;
    t1_before_t3 = get_current_time();
    ActivateTask(Task3);
    t = get_current_time();
    wait_switch = time_diff(t3_wait, t);
 
}

void task1_body(void)
{
    timer_t t, t4;
    EE_assert(10, 1, 9);
    check_stacks(Task1, 24, 25);
    error = dirty_regs(&task1_activate_body, 11); /* Activate T3 */
    EE_assert(60, error == 0, EE_ASSERT_NIL);
    EE_assert(57, 1, 11);
    t1_before_irq3 = get_current_time();
    fire_irq(); /* Wake up T3 */
    t = get_current_time();
    end_task1 = time_diff(t3_finish, t);
    EE_assert(12, 1, 59);
    EE_assert(26, t4_start == 0, EE_ASSERT_NIL);
    t1_before_t5 = get_current_time();
    ActivateTask(Task5);
    t = get_current_time();
    end_task2 = time_diff(t4_finish, t);
    t4 = t4_start;
    end_task_new_task2 = time_diff(t5_finish, t4);
    EE_assert(15, t4 != 0, 26);
    EE_assert(16, 1, 15);
}

TASK(Task1)
{
    timer_t t;
    t = get_current_time();
    end_task_new_task1 = time_diff(t2_finish, t);
    error = dirty_regs(&task1_body, 11);
    EE_assert(27, error == 0, EE_ASSERT_NIL);
    t1_finish = get_current_time();
    //TerminateTask();
}

/*
 * Task 2
 */
void task2_body(void) {
    timer_t t, t4;
    EE_assert(2, 1, 1);
    EE_assert(28, get_IRQ_enabled(), EE_ASSERT_NIL);
    check_stacks(Task2, 29, 30);
    t2_before_irq1 = get_current_time();
    fire_irq();
    t = get_current_time();
    irq_return = time_diff(th_end_irq, t);
    EE_assert(5, 1, 4);
    EE_assert(31, t4_start == 0, EE_ASSERT_NIL);
    EE_assert(32, get_IRQ_enabled(), EE_ASSERT_NIL);
    t2_before_irq2 = get_current_time();
    fire_irq();         // The ISR launches T4
    t = get_current_time();
    end_task_after_irq = time_diff(t4_finish, t);
    t4 = t4_start;
    irq_new_task = time_diff(th_end_irq, t4);
    EE_assert(8, t4 != 0, 31);
    EE_assert(55, get_IRQ_enabled(), EE_ASSERT_NIL);
    EE_assert(9, 1, 8);
    t4_start = 0;      // Reset T4 time for another assertion
}

TASK(Task2)
{
    error = dirty_regs(&task2_body, 12);
    EE_assert(56, error == 0, EE_ASSERT_NIL);
    t2_finish = get_current_time();
    TerminateTask();
}

/*
 * Task 3
 */
void task3_body(void)
{
    timer_t t;
    EE_assert(11, 1, 10);
    EE_assert(33, get_IRQ_enabled(), EE_ASSERT_NIL);
    check_stacks(Task3, 34, 35);
    t3_wait = get_current_time();
    wait_for_T1();
    t = get_current_time();
    irq_switch = time_diff(th_end_irq, t);
    EE_assert(59, 1, 58);
}

TASK(Task3)
{
    timer_t t;
    t = get_current_time();
    activate_new_task1 = time_diff(t1_before_t3, t);
    error = dirty_regs(&task3_body, 13);
    EE_assert(36, error == 0, EE_ASSERT_NIL);
    t3_finish = get_current_time();
    TerminateTask();
}

/*
 * Task 4
 */
void task4_body(void)
{
    /* Empty */
}

TASK(Task4)
{
    t4_start = get_current_time();
    ++t4_counter;
    error = dirty_regs(&task4_body, 14);
    if (t4_counter == 1) {
        EE_assert(37, get_IRQ_enabled(), EE_ASSERT_NIL);
        check_stacks(Task4, 38, 39);
        EE_assert(40, error == 0, EE_ASSERT_NIL);
    } else {
        EE_assert(41, get_IRQ_enabled(), EE_ASSERT_NIL);
        check_stacks(Task4, 42, 43);
        EE_assert(44, error == 0, EE_ASSERT_NIL);
    }        
    t4_finish = get_current_time();
    TerminateTask();
}

/*
 * Task 5
 */
void task5_body(void)
{
    EE_assert(13, 1, 12);
    EE_assert(45, get_IRQ_enabled(), EE_ASSERT_NIL);
    check_stacks(Task5, 46, 47);
    ActivateTask(Task4);
    EE_assert(14, 1, 13);
}

TASK(Task5)
{
    timer_t t;
    t = get_current_time();
    activate_new_task2 = time_diff(t1_before_t5, t);
    error = dirty_regs(&task5_body, 12);
    EE_assert(48, error == 0, EE_ASSERT_NIL);
    t5_finish = get_current_time();
    TerminateTask();
}

/*
 * Task 6: terminate program
 */
TASK(Task6)
{
    EE_assert_range(0, 1, sizeof(EE_assertions)/sizeof(EE_TYPEASSERTVALUE)-1);
    result = EE_assert_last();
    terminate_all();
}

/*
 * MAIN TASK
 */
void main_body(void)
{
    timer_t t;
    EE_assert(1, 1, EE_ASSERT_NIL);
    EE_assert(49, ! get_IRQ_enabled(), EE_ASSERT_NIL);
    num_toses = get_base_toses(base_toses);
    init_interrupts();
    StartOS(OSDEFAULTAPPMODE);
    EE_assert(50, get_IRQ_enabled(), EE_ASSERT_NIL);
    ActivateTask(Task2);
    t = get_current_time();
    end_task3 = time_diff(t1_finish, t);
    EE_assert(17, 1, 16);
    EE_assert(51, get_IRQ_enabled(), EE_ASSERT_NIL);
    error = check_toses(base_toses, num_toses);
    EE_assert(52, 0 == error, EE_ASSERT_NIL);
    error = check_all_pre_stack_canaries(base_toses, num_toses);
    EE_assert(53, 0 == error, EE_ASSERT_NIL);
}

void test_irq_restore(void)
{
    fire_late_irqs();
    error = check_regs( 10 );
    /* Control reaches this point only in case of error. Wait for the next
     * interrupt to check the `error' variable */
    for (;;)
        ;
}

int main(void)
{
    started = 1;
    error = dirty_regs(&main_body, 10);
    EE_assert(54, error == 0, EE_ASSERT_NIL);
    test_irq_restore();
    started = 0;
    return 0;
}

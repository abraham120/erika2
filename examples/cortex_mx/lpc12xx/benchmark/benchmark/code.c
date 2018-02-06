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
 * Author: Gianluca Franchino 2011
 */
#include "bm_config.h"
//#include "cpu/cortex_mx/inc/ee_irq.h"
#include "timingtest.h"

char code_buf[80];
/*
* Interrupt handlers
*/
ISR1(isr1_handler)
{	
	timingtest_mark(TIMINGTEST_CKP_BEGIN_ISR1);
	//bm_uart_send_buffer("\r\nISR1_BEGIN", strlen("\r\nISR1_BEGIN"));
	bm_clear_isr1();
	//bm_uart_send_buffer("\r\nISR1_END", strlen("\r\nISR1_END"));
	timingtest_mark(TIMINGTEST_CKP_END_ISR1);	
}


ISR2(isr2_handler)
{	
	
	timingtest_mark(TIMINGTEST_CKP_BEGIN_ISR2);
	//bm_uart_send_buffer("\r\nISR2_BEGIN", strlen("\r\nISR2_BEGIN"));
	
	bm_clear_isr2();

	//bm_uart_send_buffer("\r\nISR2_END", strlen("\r\nISR2_END"));
	timingtest_mark(TIMINGTEST_CKP_END_ISR2);
	
}

ISR2(isr2_act_task_handler)
{	
	
	timingtest_mark(TIMINGTEST_CKP_BEGIN_ISR2_AT);
	//bm_uart_send_buffer("\r\nISR2_AT_BEGIN", strlen("\r\nISR2_AT_BEGIN"));	
	
	bm_clear_isr2_act_task();
	
	activate_task(Task1);
	
	//bm_uart_send_buffer("\r\nISR2_AT_END", strlen("\r\nISR2_AT_END"));	
	timingtest_mark(TIMINGTEST_CKP_END_ISR2_AT);
	
}

/*
* Tasks
*/
unsigned int task2_chp_begin = TIMINGTEST_CKP_BEGIN_TASK2;
unsigned int task2_chp_end = TIMINGTEST_CKP_END_TASK2;

TASK(Task1)
{
	timingtest_mark(TIMINGTEST_CKP_BEGIN_TASK1);

	//bm_uart_send_buffer("\r\nTASK1_BEGIN", strlen("\r\nTASK1_BEGIN"));
	
	task2_chp_begin = TIMINGTEST_CKP_BEGIN_TASK2;
	task2_chp_end = TIMINGTEST_CKP_END_TASK2;
	
	/*New task without preemption*/
	timingtest_mark(TIMINGTEST_CKP_BEFORE_TASK2_FROM_TASK1);
	activate_task(Task2);
	timingtest_mark(TIMINGTEST_CKP_AFTER_TASK2_FROM_TASK1);
	
	//bm_uart_send_buffer("\r\nTASK1_END", strlen("\r\nTASK1_END"));
	timingtest_mark(TIMINGTEST_CKP_END_TASK1);

	terminate_task();	
}


TASK(Task2)
{
	//timingtest_mark(TIMINGTEST_CKP_BEGIN_TASK2);
	timingtest_mark(task2_chp_begin);
	//bm_uart_send_buffer("\r\nTASK2_BEGIN", strlen("\r\nTASK2_BEGIN"));

	//bm_uart_send_buffer("\r\nTASK2_END", strlen("\r\nTASK2_END"));
	timingtest_mark(task2_chp_end);
	//timingtest_mark(TIMINGTEST_CKP_END_TASK2);
	
	terminate_task();		
}


/*
*  Task(BM_task): task implementing the benchmark.
*
* Benchmark parameters computation:
* -ISR1 Latency = TIMINGTEST_CKP_BEGIN_ISR1 - TIMINGTEST_CKP_BEFORE_ISR1;
* -ISR1 exit = TIMINGTEST_CKP_AFTER_ISR1 - TIMINGTEST_CKP_END_ISR1;
* -ISR2 Latency = TIMINGTEST_CKP_BEGIN_ISR2 - TIMINGTEST_CKP_BEFORE_ISR2; 
* -ISR2 exit = TIMINGTEST_CKP_AFTER_ISR2 - TIMINGTEST_CKP_END_ISR2;
* -New task from ISR =  TIMINGTEST_CKP_BEGIN_TASK1 - TIMINGTEST_CKP_END_ISR2_AT  
* -New task with preemption = TIMINGTEST_CKP_BEGIN_TASK2_PREE - TIMINGTEST_CKP_BEFORE_TASK2
* -New task without preemption = TIMINGTEST_CKP_AFTER_TASK2_FROM_TASK1 - TIMINGTEST_CKP_BEFORE_TASK2_FROM_TASK1
* -Task exit = TIMINGTEST_CKP_AFTER_TASK2 - TIMINGTEST_CKP_END_TASK2_PREE
* -Task (activated from IRQ) exit = TIMINGTEST_CKP_BEFORE_TASK2 - TIMINGTEST_CKP_END_TASK1 
* 
* Task priority order: BM_task < Task2 < Task1 
* (i.e. the highest priority task is Task1, the lowest one is BM_task)
* 
* TO BE DECIDED: at the moment TIMINGTEST_CKP_BEGIN_ISR2_AT, 
* TIMINGTEST_CKP_END_TASK1 and other checkpoints are not used. If necessary, 
* we could save memory removing them.
* 
* Note: "timingtest_mark(checkpoint)" is the function getting the timestamp. The timestamp 
* is stored into checkpoint. For instance, timingtest_mark(TIMINGTEST_CKP_BEFORE_ISR1) stores
* the current timestamp into TIMINGTEST_CKP_BEFORE_ISR1.
*/

unsigned int prio;

TASK(BM_task)
{

	bm_set_isr2_act_pri();

	for (;;) {  

		/*Raise ISR1 */
		timingtest_mark(TIMINGTEST_CKP_BEFORE_ISR1);
		bm_raise_isr1();
		timingtest_mark(TIMINGTEST_CKP_AFTER_ISR1);
	
		/*Raise ISR2 */
		timingtest_mark(TIMINGTEST_CKP_BEFORE_ISR2);
		bm_raise_isr2();
		timingtest_mark(TIMINGTEST_CKP_AFTER_ISR2);
	
		/*Raise ISR2 with task_activate*/
		bm_raise_isr2_act_task();

		/*New task with preemption*/
		task2_chp_begin = TIMINGTEST_CKP_BEGIN_TASK2_PREE;
		task2_chp_end = TIMINGTEST_CKP_END_TASK2_PREE;
		timingtest_mark(TIMINGTEST_CKP_BEFORE_TASK2);
		activate_task(Task2);
		timingtest_mark(TIMINGTEST_CKP_AFTER_TASK2);
		
		if (++bm_loops == BM_MAX_LOOPS) {
			bm_stop();
		}
	}
	
	terminate_task();
}


/*
* Main function
*/
int main(void)
{

	unsigned i;

	/*Initialize HW related stuff */ 
	bm_hw_init();

	/*Initialize timestamping tools */	
	timingtest_init();
#ifdef	BM_USE_UART
	print_log_header();
#endif	
	/*Initialize RTOS related stuff */
	bm_rtos_init();
	
	return 0;

  
}

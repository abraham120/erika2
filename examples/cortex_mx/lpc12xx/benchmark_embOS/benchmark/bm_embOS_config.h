/*
 * Author: Gianluca Franchino 2012
 */
#ifndef __BM_EMBOS_CONFIG_H__
#define __BM_EMBOS_CONFIG_H__

#include "RTOS.h"

#ifndef ANALISYS_RES_DIM
#define ANALISYS_RES_DIM 9 
#endif

#ifndef TIMINGTEST_NUM_RECORDS
#define TIMINGTEST_NUM_RECORDS 20
#endif


#ifndef BM_MAX_LOOPS
#define BM_MAX_LOOPS  TIMINGTEST_NUM_RECORDS
#endif


#ifdef __NO_INLINE__
#define __INLINE__ static
/* Used to declare an inline function before the actual definition */
#define __DECLARE_INLINE__ static
#else
#define __INLINE__ static __inline
/* Used to declare an inline function before the actual definition */
#define __DECLARE_INLINE__ static __inline
#endif

#define __ALWAYS_INLINE__ __attribute__((always_inline))

#define NORETURN  __attribute__ ((noreturn))

#define __ASM __asm
#define __IRQ __irq


#define activate_task(task) \
	OS_CREATETASK(&TCB ## task, #task, task,  task ## _pri, Stack ## task);

#define terminate_task() OS_TerminateTask(0)

#define TASK(Task) void Task()

#define DECLARE_TASK(Task) void Task()


#define ISR1(f)			\
void ISR1_ ## f(void);	\
void f(void)			\
{						\
	ISR1_ ## f();		\
}						\
void ISR1_ ## f(void)


#define ISR2(f)			\
void ISR2_ ## f(void);	\
void f(void)			\
{						\
	OS_EnterInterrupt(); \
	ISR2_ ## f();		\
	OS_LeaveInterrupt(); \
}						\
void ISR2_ ## f(void)

#define bm_stop() do { \
						bm_set_end(); \
						terminate_task();\
					 } while(0)



#define BM_task_pri 1
#define Task1_pri 3
#define Task2_pri 2

DECLARE_TASK(BM_task);
DECLARE_TASK(Task1);
DECLARE_TASK(Task2);

/* Task stacks */
extern OS_STACKPTR int StackBM_task[128], StackTask1[128], StackTask2[128]; 
/* Task-control-blocks */
extern OS_TASK TCBBM_task, TCBTask1, TCBTask2;
	
	
static volatile unsigned int bm_loops = 0;



__ALWAYS_INLINE__ void bm_rtos_init(void)
{
	OS_IncDI();		/* Initially disable interrupts     */
	OS_InitKern();	/* Initialize OS                    */
	//OS_InitHW();	/* Initialize Hardware for OS       */

	activate_task(BM_task); /* Create BM_Task */
	
	OS_DecRI();	/* Enable interrupts*/

	OS_Start(); /* Start multitasking */

	OS_Idle(); /* Background loop*/
}


#endif /*__BM_ERIKA_CONFIG_H__*/


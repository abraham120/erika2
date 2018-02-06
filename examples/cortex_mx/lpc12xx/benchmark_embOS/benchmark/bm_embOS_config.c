/*
 * Author: Gianluca Franchino 2011
 */
 
 #include "RTOS.h"
 
 
 /* Task stacks */
OS_STACKPTR int StackBM_task[128], StackTask1[128], StackTask2[128]; 
/* Task-control-blocks */
OS_TASK TCBBM_task, TCBTask1, TCBTask2;
	
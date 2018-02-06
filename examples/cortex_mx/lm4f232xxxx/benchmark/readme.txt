The purpose of this benchmark is to provide a measure of the performance of Erika Enterprise
with the following kernel mechanisms:

-ISR1 latency: the time elapsed from the activation of an Interrupt Service Routine of type 1 (ISR1), to the first ISR instruction. 
-ISR1 exit: the time elapsed from the last instruction of an ISR1 to the subsequent instruction of the interrupted task.
-ISR2 latency: the time elapsed from the activation of an Interrupt Service Routine of type 2 (ISR2), to the first ISR2 instruction. 
-ISR2 exit: the time elapsed from the last instruction of an ISR2  to the subsequent instruction of the interrupted task.
-New task from an ISR2: the time elapsed from the last instruction of an ISR2 to the first instruction of the new task.
-New task with preemption: the time elapsed from the first instruction necessary to active a new task to the first instruction of the new task.
-New task without preemption: the time elapsed from the first instruction necessary to active a new task to the last instruction necessary to active the new task.
-Terminate task (not activated from an ISR): the time elapsed from the last task instruction to the next instruction of the task preempted by the task just terminated.
-Terminate task (not activated from an ISR): the time elapsed from the last task instruction to the next instruction of the task preempted by the task just terminated.



The benchmark folders are organized as follows:
-Erika_Stellaris_Benchmark is the main directory. It contains this file, "readme.txt" plus the "makefile" and the following subfolders;
-benchmark: it contains the source files;
-output: it will contain, after the compilation process, all the files of the project.
-Keil_Debug_BM_Project: it contains the configuration files for the Keil IDE.
-results: it contains  which is the file with the benchmark results.
 

Follow the instruction below to compile and run the benchmark:
1)Open the cygwin shell and go in the following directory: "Testsuite/TI_Stellaris_LM4F232H5QD\bin\Erika_Stellaris_Benchmark".
2)If you want to compile and run the benchmark with the simulator provided with Keil IDE, type the following two commands:

export Debugger=ICDI
make

If you want to compile and execute the benchmark with the simulator provided with the Keil IDE, just type the make command.

After the execution of the benchmark, the obtained results are stored in the file 
BM_TI_Stellaris_LM4F232H5QD.log. This file can be found in the results folder. 


 

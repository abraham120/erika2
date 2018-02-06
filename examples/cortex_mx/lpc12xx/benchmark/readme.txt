The purpose of this benchmark is to provide a measure of the performance of Erika Enterprise
with the following kernel mechanisms:

-ISR1 latency: the time elapsed from the activation of an Interrupt Service 
Routine of type 1 (ISR1), to the first ISR instruction. 
-ISR1 exit: the time elapsed from the last instruction of an ISR1 to the 
subsequent instruction of the interrupted task.
-ISR2 latency: the time elapsed from the activation of an Interrupt Service 
Routine of type 2 (ISR2), to the first ISR2 instruction. 
-ISR2 exit: the time elapsed from the last instruction of an ISR2  to the 
subsequent instruction of the interrupted task.
-New task from an ISR2: the time elapsed from the last instruction of an ISR2 to 
the first instruction of the new task.
-New task with preemption: the time elapsed from the first instruction necessary 
to active a new task to the first instruction of the new task.
-New task without preemption: the time elapsed from the first instruction necessary 
to active a new task to the last instruction necessary to active the new task.
-Terminate task (not activated from an ISR): the time elapsed from the last task 
instruction to the next instruction of the task preempted by the task just terminated.
-Terminate task (not activated from an ISR): the time elapsed from the last task
instruction to the next instruction of the task preempted by the task just terminated.



The benchmark folders are organized as follows:
-benchmark: it contains the source files;
-output: it will contain, after the compilation process, all the files of the project.
-Keil_Debug_BM_Project: it contains the configuration files for the Keil IDE.
-results: it contains BM_NXP_LPC1227.log which is the file with the benchmark results.

Note: the folder "results" contains BM_NXP_LPC1227_HW.log and BM_NXP_LPC1227_SIM.log. 
These files reports respectively the results we obtained with the LPCXpresso board 
and with the simulator.


The benchmark can be compiled and run with three configurations:

1)Simulation: in this configuration the benchmark is compiled and run by the Keil
simulator. To launch the benchmark, open the cygwin console and type the following
command: "make Debugger=Simul".

2)ULINK2: in this configuration the benchmark is compiled and run by Keil 
through the ULINK2 debugger which has to be connected to the board. We used the 
LPCXpresso board featuring a NXP LPC1227 microcontroller  
(http://ics.nxp.com/lpcxpresso). To launch the benchmark, open the cygwin console 
and just type "make" or "make Debugger=ULINK2". 

3)ULINK2 with results sent through the UART. In this configuration the benchmark 
is compiled and run by the Keil through the ULINK2 debugger. The results of the 
benchmark are sent to the UART0 of the LPCXpresso board. To acquire the results 
use an hyperterminal such as HTerm, minicom etc..


 

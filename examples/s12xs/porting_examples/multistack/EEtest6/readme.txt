multi6

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode and semaphores.
 In this demo is shown that a task can be interrupted with a call to ready2stacked (with an activation
 of a high priority task) and resumed with a call to stkchange (if the high priority task is blocked 
 on a shared resource).
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 ee_hs12xsregs.h, eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 

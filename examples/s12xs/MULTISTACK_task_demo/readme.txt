multi_task_demo

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode and conformance class ECC1.
 In this demo two tasks are activated inside two ISRs and work with different stacks.
 There is also a separate stack for IRQs.
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 ee_hs12xsregs.h, eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 

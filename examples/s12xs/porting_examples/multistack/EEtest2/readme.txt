multi2

 Another minimal EE demo that demonstrates how to work with the MULTISTACK mode.
 In this demo two task are activated inside an ISR and work with different stacks.
 With this demo you can test the preemption mechanism with stack change starting from an interrupt. 
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 ee_hs12xsregs.h, eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 

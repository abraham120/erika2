multi4

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode with nested interrupts.
 In this demo two tasks are activated inside two ISRs and work with different stacks.
 The ISRs use another stack. With this demo you can test the ISR nesting mechanism and the behaviour of the ISR stack. 
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 ee_hs12xsregs.h, eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 

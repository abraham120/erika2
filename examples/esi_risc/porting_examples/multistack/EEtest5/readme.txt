multi5

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode and semaphores.
 In this demo two tasks are activated in the main function and work with different stacks.
 The demo is a classical producer/consumer problem implemented with two
 semaphores P and V.
 The demo is used to show the following features of ERIKA Enterprise OS: 
 - 	Multistack configuration: The Producer and the Consumer task need a
  	separate stack because they block calling the WaitSem
  	primitive. 

 - 	Separate stack for IRQs:  the OIL file allocates a
  	separate stack for ISR Type 2 by setting "IRQ_STACK = TRUE { SYS_SIZE=64;
  	};".

 - 	Semaphores: ERIKA Enterprise supports counting semaphores. The
  	demo show how to initialize the semaphores, and how to use the main
  	semaphore primitives (PostSem and WaitSem).
 
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 

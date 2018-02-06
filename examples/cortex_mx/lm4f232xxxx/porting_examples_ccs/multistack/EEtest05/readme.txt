EEtest05

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode and
 semaphores.
 In this demo two tasks are activated in the main function and work with
 different stacks.
 The demo is a classical producer/consumer problem implemented with two
 semaphores P and V.
 The demo is used to show the following features of ERIKA Enterprise OS: 
 - 	Multistack configuration: The Producer and the Consumer task need a
	separate stack because they block calling the WaitSem
	primitive. 

 - 	Separate stack for IRQs:  the OIL file allocates a
	separate stack for ISR Type 2 by setting:
	"IRQ_STACK = TRUE { SYS_SIZE=64; };".

 - 	Semaphores: ERIKA Enterprise supports counting semaphores.
	The demo show how to initialize the semaphores, and how to use the main
	semaphore primitives (PostSem and WaitSem).

 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the
            application.
"code.c": Main application file.

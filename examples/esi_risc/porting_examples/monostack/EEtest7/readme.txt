test7

 A minimal EE demo for BCC2 mode testing. Task1 is a non-preemptive task
 and Task2 can have pending activations.
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...).

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the application.
"main.c": Main application file.

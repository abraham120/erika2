multi0

 A minimal EE demo to test the compilation chain in MULTISTACK mode.
 In this first demo two task are activated and share the same stack but
 the operating system is in MULTISTACK mode.
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...) 

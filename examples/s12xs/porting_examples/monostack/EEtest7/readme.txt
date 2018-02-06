test7

 A minimal EE demo for BCC2 mode testing. Task1 is a non-preemptive task
 and Task2 can have pending activations.
 The compilation chain can start outside Eclipse environment from the Cygwin shell with the "make" 
 command inside the Debug folder of the project.
 The Debug folder can be created manually if you don't have the oil-based generator. 
 The Debug folder must contain at least the following files (suitably modified...):
 ee_hs12xsregs.h, eecfg.h, eecfg.c and the makefile (see the examples of different architectures to begin...).

The RT-DRUID project contains the following files:
"mc9s12xs128.lkf": Cosmic linker script for Freescale S12 microcontroller.  
"conf.oil": Configuration file in OSEK implementation language specific for the application.
"crtsx.S": Start-up file to initialize variables and code. 
"hs12xsregs.h": S12 Microcontroller Registers header file.
"main.c": Main application file.
"vector_s12x.c": ISR and Interrupt vector file.
"Full_Chip_Simulation.ini": Configuration file for CW debugger simulation.
"SofTec_HCS12.ini": Configuration file for CW debugger and SofTec DEMO9S12XSFAME demo board. 
"C_Layout.hwl": Scopes layout file for CW debugger.

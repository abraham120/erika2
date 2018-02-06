Resource demo

 Resource demo: A minimal EE demo for the MONOSTACK case with the SofTec DEMO9S12XSFAME demo board.
 The demo uses the following peripherals:
 LEDs;
 Buttons;;
 ADC module; 
 PIT timer;
 SCI module;

The RT-DRUID project contains the following files:
"mc9s12xs128.lkf": Cosmic linker script for Freescale S12 microcontroller.  
"conf.oil": Configuration file in OSEK implementation language specific for the application.
"crtsx.S": Start-up file to initialize variables and code. 
"hs12xsregs.h": S12 Microcontroller Registers header file.
"main.c": Main application file.
"vector_s12x.c": ISR and Interrupt vector file.
"myapp.h": Header file required by the application. 
"Full_Chip_Simulation.ini": Configuration file for CW debugger simulation.
"SofTec_HCS12.ini": Configuration file for CW debugger and SofTec DEMO9S12XSFAME demo board. 
"C_Layout.hwl": Scopes layout file for CW debugger.
 

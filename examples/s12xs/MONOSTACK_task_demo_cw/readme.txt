Task demo

 Task demo: A minimal EE demo for the MONOSTACK case with the SofTec DEMO9S12XSFAME demo board.
 The demo uses the following peripherals:
 LEDs;
 Buttons;;
 ADC module; 
 PIT timer;
 SCI module;

The RT-DRUID project contains the following Codewarrior files:
"SofTec_HCS12_linker.prm": Codewarrior linker script for Freescale S12 microcontroller.  
"conf.oil": Configuration file in OSEK implementation language specific for the application.
"Start12.c": Start-up file to initialize variables and code. 
"main.c": Main application file.
"Vectors.c": ISR and Interrupt vector file (if needed...).
"CPU12ISRs.c": ISR handlers source file (if needed...).
"CPU12ISRs.h": ISR handlers header file (if needed...).
"Full_Chip_Simulation.ini": Configuration file for CW debugger simulation.
"SofTec_HCS12.ini": Configuration file for CW debugger and SofTec DEMO9S12XSFAME demo board. 
"C_Layout.hwl": Scopes layout file for CW debugger.
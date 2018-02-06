Task demo

 Task demo: A minimal EE demo for the MONOSTACK case with the Axiom TWRS12G128 demo board.
 The demo uses the following peripherals:
 LEDs;
 Buttons;;
 ADC module; 
 TIMER0 timer;
 SCI module;

The RT-DRUID project contains the following Codewarrior files:
"Project.prm": Codewarrior linker script for Freescale S12 microcontroller.  
"conf.oil": Configuration file in OSEK implementation language specific for the application.
"Start12.c": Start-up file to initialize variables and code. 
"main.c": Main application file.
"Vectors.c": ISR and Interrupt vector file (if needed...).
"CPU12ISRs.c": ISR handlers source file (if needed...).
"CPU12ISRs.h": ISR handlers header file (if needed...).
"Full_Chip_Simulation.ini": Configuration file for CW debugger simulation.
"PE_Multilink_CyclonePro.ini": Configuration file for CW debugger and Axiom TWRS12G128 demo board. 
"C_Layout.hwl": Scopes layout file for CW debugger.
Task demo - batch mode

 Task demo: A minimal EE demo for the MONOSTACK case with the Axiom TWRS12G128 demo board.
 The demo uses the following peripherals:
 LEDs;
 Buttons;;
 ADC module; 
 TIMER0 timer;
 SCI module;

The project contains the following files:
"conf.oil":     Configuration file in OSEK implementation language specific for the application.
"src/main.c":       Main application file.
"s12g/Start12.c":    Start-up file to initialize variables and code. 
"s12g/Vectors.c":    ISR and Interrupt vector file (if needed...).
"s12g/CPU12ISRs.c":  ISR handlers source file (if needed...).
"s12g/CPU12ISRs.h":  ISR handlers header file (if needed...).
"hiwave/Full_Chip_Simulation.ini":    Configuration file for CW debugger simulation.
"hiwave/PE_Multilink_CyclonePro.ini": Configuration file for CW debugger and Axiom TWRS12G128 demo board. 
"hiwave/C_Layout.hwl": Scopes layout file for CW debugger.
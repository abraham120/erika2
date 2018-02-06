Small example of a periodic task under ERIKA Enterprise Basic
------------------------------------------------------------------
version 1.0 - 19 december 2006
Author: Paolo Gai - Mauro Marinoni
------------------------------------------------------------------

Requirements:
-------------
Microcontroller:
PIC33FFJ256MC710

Hardware:
Evidence/EmbeddedSolutions Flex rel. 1.0
Microchip Explorer16 (see below)

Software:
Erika Enterprise Basic 1.4

------------------------------------------------------------------

Notes:

This simple demo has been published in a reduced version on the
Firmware Italian Magazine in the February 2007 issue.

The demo basically has a task which is periodically activated by a
periodic alarm. The alarm is linked to a counter which is incremented
by a timer interrupt T1.

At each execution, the task turns on and off a led, to show its
periodical execution.

We also included a build.xml and a compile.bat file which can be used
to generate the source code from command line.

---

Note for Explorer16 users: 

To use the demo with the Microchip Explorer16 board, please modify the
conf.oil file by selecting the Explorer16 board using the right option
in the graphical configurator, or by modifying the conf.oil file as
follows:

		BOARD_DATA = EE_FLEX {

should be modified with 

		BOARD_DATA = MICROCHIP_EXPLORER16 {


To run the demo with the PIC24FJ128GA010, please modify the conf.oil
file by selecting the MCU with the graphical configurator, or by modifying
the conf.oil file as follows:

		MCU_DATA = PIC30 {
				MODEL = PIC33FJ256MC710;
		};
		
should be modified with

		MCU_DATA = PIC30 {
				MODEL = PIC24FJ128GA010;
		};

and comment the configuration instruction in code.c

// Primary (XT, HS, EC) Oscillator without PLL
//_FOSCSEL(FNOSC_PRI);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
//_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
//_FWDT(FWDTEN_OFF);
// Disable Code Protection
//_FGS(GCP_OFF);            							
 


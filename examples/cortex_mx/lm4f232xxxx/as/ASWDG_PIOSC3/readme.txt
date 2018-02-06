ASWDG_PIOSC3

 Simple project to test the Precision Internal Oscillator WDG driver services
 using callback and NMI without system reset.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

NOTE:	In order to use watchdog 1, we have to enable the clock to another
	module that can use the PIOSC as a clock (UART, SSI, ADC).
	http://e2e.ti.com/support/microcontrollers/
		/stellaris_arm_cortex-m3_microcontroller/f/471/t/176487.aspx
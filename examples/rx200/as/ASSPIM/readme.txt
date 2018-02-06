ASSPIM

 Simple project to to estimate the SPI Handler/Driver MINIMAL services.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

From Debug/rx200.map:

In debug mode (no optimizations):

*** Total Section Size ***

RAMDATA SECTION:  00000496 Byte(s)
ROMDATA SECTION:  00000779 Byte(s)
PROGRAM SECTION:  000040f2 Byte(s)

With optimization ( -optimize=max for ccrx):

RAMDATA SECTION:  00000496 Byte(s)
ROMDATA SECTION:  00000779 Byte(s)
PROGRAM SECTION:  00001bd6 Byte(s)

Note: to enable optimizations comment out  " EE_OPT = "DEBUG"; " in conf.oil.
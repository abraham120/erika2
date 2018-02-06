ASSPI_LBM_3

 Simple project to test the AUTOSAR SPI Handler/Driver:
 - 2 Sequence
   - Interruptible Sequence
     - 2 Jobs
       - 4 Channels 
       - 7 Channels
   - Non-Interruptible Sequence
     - 1 Job
       - 3 Channels
 - Only 2 SSI Hardware Unit
   - Loop-back Mode (MOSI and MISO connected by a physical wire )
   - Asynchronous
 - Write/AsyncTransmit/Read (IB)
   - Polling Mode ( to test internal scheduler )
 - Setup/AsyncTransmit (EB)
   - Polling Mode ( to test internal scheduler )

 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.
ASSPI_LBM_0_B

 Simple project to test the AUTOSAR SPI Handler/Driver:
 - 1 Sequence
   - 1 Job
     - 1 Channel
       - Max 3 bytes
 - 3 SCI Hardware Units
   - Loop-back Mode (MOSI and MISO connected by a physical wire )
   - 2 Units Asynchronous
   - 1 Units Synchronous
 - Write/AsyncTransmit/Read (IB)
   - Interrupt Mode
   - Polling Mode
 - Setup/AsyncTransmit (EB)
   - Interrupt Mode
   - Polling Mode
 - SyncTransmit/Read (IB)
 - Setup/SyncTransmit (EB)
   - No Source Buffer.

 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

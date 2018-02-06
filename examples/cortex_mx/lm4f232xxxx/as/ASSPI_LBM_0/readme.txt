ASSPI_LBM_0

 Simple project to test the AUTOSAR SPI Handler/Driver:
 - 1 Sequence
   - 1 Job
     - 1 Channel
       - Max 3 bytes
 - All 4 SSI Hardware Unit
   - Loop-back Mode
   - 2 Units Asynchronous
   - 2 Units Synchronous
 - Write/AsyncTransmit/Read (IB)
   - Interrupt Mode
   - Polling Mode
 - Setup/AsyncTransmit (EB)
   - Interrupt Mode
   - Polling Mode
 - Write/SyncTransmit/Read (IB)
 - Setup/SyncTransmit (EB)

 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil":	Configuration file in OSEK implementation language specific for
		the application.
"main.c":	Main application file.

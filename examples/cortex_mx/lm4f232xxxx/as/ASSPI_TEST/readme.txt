ASSPI_TEST

 Simple project to test the AUTOSAR SPI Handler/Driver:
 - 1 Sequence
   - 1 Job
     - 1 Channel
       - One Byte Only.
 - 2 SSI Hardware Modules
   - Loop-back Mode
   - 1 Unit Asynchronous
   - 1 Unit Synchronous
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

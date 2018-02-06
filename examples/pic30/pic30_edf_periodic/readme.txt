Periodic EDF task under ERIKA Enterprise Basic
------------------------------------------------------------------
version 1.0 - 17 june 2006
Author: Paolo Gai 
------------------------------------------------------------------

Requirements:
-------------
Microcontroller:
PIC33FFJ256MC710

Hardware:
Evidence/EmbeddedSolutions Flex rel. 1.0

Software:
Erika Enterprise Basic 1.4.1

------------------------------------------------------------------

Notes:

The demo shows the implementation of a simple periodic task with a
period of 0.5 seconds. The demo is very similar to the demo in the
directory pic30_Firmware_February.

Please note:
- the relative deadline specification in the OIL file
	TASK myTask { REL_DEADLINE = "0.5s"; ...
	
- the specification of the system tick, which is done in two places, 
  in the C file using
   _FOSCSEL(FNOSC_PRI);
  which specifies a 500ns timer tick, and in the OIL file with
  KERNEL_TYPE = EDF { NESTED_IRQ = TRUE; TICK_TIME = "500ns";};
  
Finally, please note that the relative deadline of a task is 
independent from the activation pattern of a task. In particular, 
to program the task as periodic with a period of 0.5s
we needed a hardware timer (in the example T1) programmed with a 
period of 25 ms using the line
	PR1   = 0xc350;
and an alarm which fires every 40 T1 interrupts using the line
	SetRelAlarm(myAlarm, 20, 20);
 



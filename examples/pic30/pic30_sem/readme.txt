Multistack and Semaphore example
------------------------------------------------------------------
version 1.1 - april 27, 2009
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

The demo is a classical producer/consumer problem implemented with two
semaphores P and V.

The demo is used to show the following features of ERIKA Enterprise
Basic:

- Multistack configuration: The Producer and the Consumer task need a
  separate stack because they block calling the WaitSem
  primitive. 

- Separate stack for IRQs:  the OIL file allocates a
  separate stack for ISR Type 2 by setting "IRQ_STACK = TRUE { SYS_SIZE=64;
  };".

- Semaphores: ERIKA Enterprise Basic supports counting semaphores. The
  demo show how to initialize the semaphores, and how to use the main
  semaphore primitives (PostSem and WaitSem).

---

Note for Explorer16 users: 

To use the demo with the Microchip Explorer16 bard, please modify the
conf.oil file by selecting the Explorer16 board using the right option
in the graphical configurator, or by modifying the conf.oil file as
follows:

		BOARD_DATA = EE_FLEX {

should be modified with 

		BOARD_DATA = MICROCHIP_EXLORER16 {

---

version 1.1 adds a second OIL file, conf_EDF.oil, that shows how the
same demo can be used with the EDF scheduler.
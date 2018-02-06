Usage of RES_SCHEDULER under ERIKA Enterprise Basic
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

This small example shows the usage of the RES_SCHEDULER resource.

The RES_SCHEDULER resource can be used to temporarily make a task
non-preemptive.

The demo is basically composed by a task which periodically flashes a
led, and by a low priority task which executes and periodically lock
RES_SCHEDULER.

The visible behavior is the following:

- LowTask is the low priority task calling the RES_SCHEDULER
  primitive. The task never ends, alternating a preemptive and a
  non-preemptive (basically it locks RES_SCHEDULER) behavior, with 50%
  duty cycle.

- HighTask is activated periodically flashing the LED.

- When LowTask is in the preemptible phase, HighTask preempts LowTask,
  and as a result the led Flashes.

- When LowTask is in the non-preemptible phase, HighTask does not
  preempt LowTask. As a result, it stores pending activations which
  are then recovered when the non-preemptible phase ends. As a result,
  the led stops flashing; at the end of the non-preemptible phase the
  led flashes rapidly (meaning HighTask is executing the pending
  activations).

---

Note for Explorer16 users: 

To use the demo with the Microchip Explorer16 bard, please modify the
conf.oil file by selecting the Explorer16 board using the right option
in the graphical configurator, or by modifying the conf.oil file as
follows:

		BOARD_DATA = EE_FLEX {

should be modified with 

		BOARD_DATA = MICROCHIP_EXLORER16 {


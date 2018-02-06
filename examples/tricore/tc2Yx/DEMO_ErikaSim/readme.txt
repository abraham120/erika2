Task demo

 Task demo: A minimal EE demo with the TriCore TC275-TE
 under lauterbach simulation environment and Infineo TriBoard
 The demo uses the following peripherals:
 *  STM Timer;
 *  DIO as output for LEDs;
 *  DIO as event input with ESR (External Service Requests) as button [Soldered by hand*];
 
The demo tests the ECC1 kernel type.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the application.
"code.c": Main application file.

* Infineon TriBoard come without buttons, but RESET button.
  We soldered a flying button connected with signal REQ1 <-> pin P15.8 on
  pin 71 of PERIPHERALS (Xx02,Xx02) connector.
  Pin P15.8 is a valid input for the ESR5 (External Request Selector 5).

  The button we soldered was connected in series with a pull-up, so it
  shortcut the pin with GND when pressed. That's imply that we configured
  EICR2.EIS1, External Input Channel Register, to generate the interrupt
  on falling edges.


EEtest02

 Another minimal EE demo that demonstrates how to work with the MULTISTACK mode.
 In this demo two tasks are activated inside an ISR and work with different
 stacks.
 With this demo you can test the preemption mechanism with stack change starting
 from an interrupt.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the
            application.
"code.c": Main application file.

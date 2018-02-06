EEtest04

 Another minimal EE demo that demostrates how to create two TASKs with different
 priorities.
 This demo can be used to test the preemption mechanism.
 In this case Task2 can't preempt Task1.
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the
            application.
"code.c": Main application file.

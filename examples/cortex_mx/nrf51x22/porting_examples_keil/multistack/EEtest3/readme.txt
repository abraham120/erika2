EEtest3

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode with
 nested interrupts.
 In this demo two tasks are activated inside two ISRs and work with different
 stacks.
 With this demo you can test the ISR nesting mechanism with stack change. 
 The compilation chain starts from the Cygwin shell with the "make" command
 inside Debug directory.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the
            application.
"code.c": Main application file.

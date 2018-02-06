EEtest6

 A minimal EE demo that demonstrates how to work with the MULTISTACK mode and
 semaphores.
 In this demo is shown that a task can be interrupted with a call to
 ready2stacked (with an activation of a high priority task) and resumed with a
 call to stkchange (if the high priority task is blocked  on a shared resource).
 The compilation chain starts from the Cygwin shell with the "make" command
 inside Debug directory.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the
            application.
"code.c": Main application file.

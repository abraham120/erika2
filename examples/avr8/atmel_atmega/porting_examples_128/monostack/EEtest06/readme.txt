EEtest06

 A minimal EE demo that demostrates how the Erika BCC1 mode works.
 This demo can be used to test Erika BCC1 files compilation, kernel start
 procedure (StartOS(...)) and task termination (EE_s12xs_terminate_task(:::)).
 The compilation chain starts from the Cygwin shell with the "make" command.

The RT-DRUID project contains the following files:
"conf.oil": Configuration file in OSEK implementation language specific for the
            application.
"code.c": Main application file.

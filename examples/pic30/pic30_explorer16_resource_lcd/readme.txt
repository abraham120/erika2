Resource usage under ERIKA Enterprise Basic
------------------------------------------------------------------
version 1.0 - 21 december 2006
Author: Paolo Gai - Mauro Marinoni
------------------------------------------------------------------

Requirements:
-------------
Microcontroller:
PIC33FFJ256MC710

Hardware:
Microchip Explorer16

Software:
Erika Enterprise Basic 1.4

------------------------------------------------------------------

Notes:

This demo shows the usage of the Resource primitives under ERIKA
Enterprise Basic.

The demo works on the Microcip Explorer 16 Evaluation board.

The idea of the demo is to have a simple program composed by two
tasks. Each task prints a number from 0 to 9 at a given row and
column.

The typical output on the 16x2 characters LCD of the Explorer16 demo
board will be the following:

X... .... .... ....
X... .... .... ....

where "X" is a number from 0 to 9, which typically changes very
rapidly, and "." is an empty character.

The access to the LCD is done in purpose in a non-atomic way, by first
selecting the row and then the column on the LCD.

The demo can be run in two modes (see the "#define" in code.c).

WITH_RESOURCES defined
----------------------

The access to the LCD is protected by using a Resource. In that case,
the usage of the resource avoids race conditions, and the output on
the LCD is the one expected. 

A typical race condition event could be:

LowTask     : GetResource myResource
LowTask     : select line 0
T1 Interrupt: Activate HighTask, which do not execute because myResource is locked
LowTask     : select column 0
LowTask     : print character ---> character printed in (0,0), CORRECT!
LowTask     : ReleaseResource myResource
HighTask    : GetResource myResource
HighTask    : select line 1
HighTask    : select column 1
HighTask    : print character ---> character printed in (1,1), CORRECT!
HighTask    : ReleaseResource myResource

In this case, the race condition is avoided because of the usage of the shared resource.


WITH_RESOURCES not defined
--------------------------

The access to the LCD is NOT protected by using a Resource. In that case,
race conditions can appear.

A typical race condition event could be:

LowTask     : select line 0
T1 Interrupt: Activate HighTask, which preempts LowTask because there are no resources locked
HighTask    : select line 1
HighTask    : select column 1
HighTask    : print character ---> character printed in (1,1), CORRECT!
LowTask     : select column 0
LowTask     : print character ---> character printed in (1,0), NOT CORRECT!


In this case, the race condition is not avoided, and a spurius
character is printed in cell (1,1).

In this case, the output on the 16x2 characters LCD of the Explorer16 demo
board will be the following:

X... .... .... ....
XX.. .... .... ....

which is not correct.

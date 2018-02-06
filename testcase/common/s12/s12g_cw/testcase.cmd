// Load the executable file
load "Debug\s12.elf" AUTOERASEANDFLASH NOPRELOADCMD NOPOSTLOADCMD NORUNAFTERLOAD
// Set a breakpoint when the execution runs out from the main function...
BS 0xC03E P E
// Start execution...
GO
// Wait the breakpoint or a similar pause
WAIT 10 ;s
STOP
// Check the assertions vector
IF EE_assertions[0]==1
printf("OK!!!")
ELSE
printf("FAILURE!!!")
ENDIF

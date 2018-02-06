These examples demonstrate the functionality of the "porting examples".
The build infrastructure is currently a little incompatible to what 
employed within the general ERIKA examples. This is mainly due to the
environment in which we ported and use ERIKA. From the 'build.mk' files,
it should be simple to set up a stand-alone makefile. 

The examples can be tested on Infineon's tsim simulator (packaged with the
HighTec GCC toolchain) and the TriBoard tc1796 (v1.4) - with the exception
of 'demo_led' which is specifially tailored for that board.
To run the examples in tsim, set __TSIM__ in the makefiles which
causes the HighTec gcc to pick a different set of CRT objects.

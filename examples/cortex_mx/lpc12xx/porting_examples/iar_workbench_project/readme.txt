Executable files built outside of IAR Embedded Workbench

Follow these steps to load and debug an executable file that was built outside
IAR Embedded Workbench, one example is projects built on the command line. 

1. Choose Project>Add Files to add the executable file (filename extension .out)
that you want to debug to the project. 

2. Set up the debugger options according to you needs. The only project options
that are meaningful to set for this kind of project are options in the General
Options and Debugger categories. Make sure to set up the general project 
options in the same way as when the executable file was built.

3. To start the debugger, select the project in the workspace window and
click the Debug button. The project can be reused whenever you rebuild your
executable file. The debugger will notice if the executable file has been 
rebuilt and ask you if you want to reload it.

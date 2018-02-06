RT-Druid and ERIKA Enterprise for Nios II
demo_2cpu
version 1.1
-----------------------------------------



Welcome to the Evidence RT-Druid and ERIKA Enterprise demo version for
Nios II!!!




This small project shows some of the main features available with
ERIKA Enterprise RTOS, and the configuration flexibility that can be
obtained using the RT-Druid Configurator for designing new software
and exploiting the power of multiprocessor Altera Nios II designs.



These are the features supported by this demo:

- specification of real-time threads that can be used to code the
  application behavior (thread*.c)

- configuration of real-time threads using the OIL configuration file,
  and their partitioning on the available CPUs

- definition of data structures local to a single CPU (see
  cpu0_startup.c)

- definition of data structures that are shared between different
  processors (see shareddata.h)

- definition of data structures that are automatically shared between
  different processors depending on the kind of resource used (see
  resourcedata.c)
  


To compile the demo, please follow these steps:

- create two system libraries, one for each cpu of the evidence_2cpu
  hardware design

- create a new RT-Druid Project

- copy all the files of this example inside the project directory

- open the properties of the project, and, in the "C/C++ Make Project"
  tab, set the build directory to "\<projectname>\Debug", where
  <projectname> is the name of the project you created

- right click on the project name in the Navigator toolbar, and choose
  "Build Project" as with typical Altera C/C++ Projects. The
  application will compile, producing two ELF binaries


  
To run the application, you have to create a multiprocessor collection
containing two debug configurations, one for each CPU. The application
will start printing a message on the consoles.  Then, press Button 1 on
the development board, and the messages printed by the threads will
appear on the console where the threads are allocated to.

You can freely move tasks from one CPU to another, without changing
the application source code: you only need to change the "CPU_ID"
assignment of each task down in this file.



Final note: When using Nios II peripherals, the developer have to
guarantee that there are notg more than one task using that
peripheral. All the tasks in this example are using the "printf"
primitive to print on the local CPU console. In this small demo,
calling printf from different tasks does not cause big problems
because threads typically do not preempt each other since they are all
activated from the same ISR.




(end of the readme.txt file)

Testcase Architecture documentation
-----------------------------------

by Paolo Gai, Jan 8, 2004

Introduction
------------

The testcase atchitecture is made to simplify the debug of a generic
EE component using an automatic tool. The paradigm of the testing
is a "black box" testing. That is, assertions are inserted into the
code OUTSIDE the component code, and the test will test the behavior
of the system seen by an external observer.

To debug a component, a set of test cases have to be produced and
verified.

Each test case is composed by:
 
- a set of tasks, resources, ..., with their properties and init values

- a sequence of calls, ISRs and assertions that constitute a
  typical execution of the test case

Definition: The test case is said to be successful if a run
of the application respects the sequence.

To check if a test case is successful, the automatic tool runs the
test case. when the test case ends (i.e., it stops at a predefined
breackpoint), the debugger (or the user) have to check that the final
assertion is verified. If it is verified, the test is passed.

This approach is slightly different from the one used by the MODISTARC
testing, that implies that the entire program execution is somehow
traced at some given testpoints, the test trace pulled out of the ECU
and compared with a given pattern. That approach will be probably
implemented in the future.


Directory structure
-------------------

- The base directory for -all- test cases is $(EEBASE)/testcase;
  $(EEBASE)/examples is used for tests included in the final
  distribution, and for initial tests.

- the test cases should work in more than one architecture
  (identified by a name A). Architecture names are chosen in the following way
  (THIS IS OBSOLETE):
  - first comes a name that identifies the BSP (that is, CPU on a given board)
  - then a name for the compiler
  - then additional informations
  For example, "e7g_rtdruid" means:
  - "e7" --> Evaluator7T
  - "g" --> gnu gcc
  - "_rtdruid" --> used in conjunction with rtdruid

- Each test on each architecture can contain more than one
  configuration (identified by a name C). There are two ways to
  specify the list of configurations: 
  - old demos: list in a makefile CONF variable; Example: "CONF=BCC1 BCC2 ECC1"
  - new demos: list of variables that can have different choices. All
    the possible combinations will be tried. 
    Example: "conf= A=b,c D=e,f" --> the combinations that will be tried
    are (A=b D=e) (A=c D=e) (A=b D=f) (A=c D=f)

- every test case T has its own directory $(EEBASE)/testcase/T

- $(EEBASE)/testcase/T contains the test case source code. The test
  case source code comes in two flavours:
  - (case 1: old tests) a set of source files that includes
    application source and configuration (.h, makefiles,...)
  - (case 2: new tests) a .c file and an OIL file named 
    $(EEBASE)/testcase/T/appl.oil

- $(EEBASE)/testcase/T/conf.in is included by makefiles inside the
  common directory that lists in the variable "worksfor" the set of
  architectures A for which the testcase should be tried. For example,
  if conf.in contains a line "worksfor = a b c", that means that
  architectures a, b, c applies to this test.  it also contains the
  specification of the typical configurations for which the test has
  been designed for.

Makefile Architecture
---------------------

- $(EEBASE)/testcase/makefile is the global makefile that is always
  called with "make ARCH=myarch". The makefile simply checks in all
  the subdirectories T the existence of the file
  $(EEBASE)/testcase/T/conf.in. If it exists, it runs on that
  directory arch_multiplexer.mk recursively.

- $(EEBASE)/testcase/common/arch_multiplexer.mk is called recursively
  on each subdirectory. it checks if the workfor variable contained
  inside conf.in contains the architecture specified in $(ARCH)
  (example: ARCH=ee, worksfor values like ee, ee1, ee_xxx match)a. if
  yes, it executes conf_multiplexer.mk recursively on the directory.

- $(EEBASE)/testcase/common/conf_multiplexer.mk parses the "conf"
  variable inside conf.in and executes a makefile rule for each
  configuration. the rule that is executed cleans, compile and
  eventually debug a given example.

- $(EEBASE)/testcase/common/THEARCH/* contains all the scripts for a
  particular THEARCH architecture. in particular, it contains a file
  arch.mk that specifies a set of variables that are the commands used
  by conf_multiplexer.mk to clean, compile and debug an example. All
  these commands are contained in makefile variables that starts with
  ARCH_MK_*

- $(EEBASE)/testcase/T/manual typically contains a set of files and
  scripts that are copied on the out directory and that are used to
  compile the test in the manual configurations.

- Ways the configurations C are passed to the test cases are the following:

  - (case 1: old tests) the configuration is passed to
    $(EEBASE)/testcase/T/manual/makefile inside the environment variable
    $(CONF). the makefile,. based on that environment variable, choses
    which are the characteristics of the application.

  - (case 2: new tests) the configuration is used to define a symbol
    that is then used to filter the appl.oil file. The appl.oil file
    contains conditional parts (#ifdefs) used to customize the
    particular OIL file.

Supported ARCHitectures:
------------------------

Here are the current existing subdirectories under the common tree:
- e7t_manual  --> Evaluator7T scripts with manual version of the source code
- e7t_rtdruid --> Evaluator7T scripts with source generated by rtdruid
- e7t_dist_src --> Evaluator7T scripts with source generated by 
		   rtdruid, with source distribution generation
- janusg_manual --> Janus scripts with manual version of the source code
- st10_manual --> st10 scripts with manual version of the source code
- triscend    --> Triscend A7 scripts

(Note: janusg do not have any script in these directories, they are
directly integrated in etc)

A typical execution
-------------------

Suppose that I type:

[pj@sam testcase]$ make ARCH=e7t

The global makefile will call arch_multiplexer.mk on all
subdirectories containing a conf.in file. 

Suppose it finds "./oo1/conf.in". arch_multiplexer.mk is called with
EXPERIMENT set to "oo1".

arch_multiplexer search in the worksfor variable specified inside
conf.in if it contains a pattern matrching e7t*. suppose yes. 
(Note: since 060902 it must be an exact match!!!)


for each matching pattern, it calls recursively conf_multiplexer.mk
with thearch=<one of the matching architectures specified in conf.in>.

conf_multiplexer examines all the possible configurations and executes
for each one the commands needed for cleaning, compiling and debugging
the target. The commands are specified in
$(EEBASE)/testcase/common/$(thearch)/arch.mk. 

Note that a separate directory is created for each configuration.

There are two cases:

- "manual" tests

  In this case, we can suppose the ./oo1 contains a manual directory
  with a makefile + configuration code, that is copied in the separate
  directory created for each configuration.

- "new tests"

  In this case, we can suppose the ./oo1 contains application code +
  appl.oil. The execution of the makefiles will:
  
  - copy all the files in ./oo1 inside the separate directory for
    the configuration.
  - filter with the GCC preprocessor appl.oil
  - call rtdruid that will parse appl.oil generating the configuration files
  - execute the makefile generated by rtdruid.
    - that makefile will generate ./oo1/out_XXX/out, with the usual compiled files in it.

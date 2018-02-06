#******************************************************************************
#                                                                             *
# License Agreement                                                           *
#                                                                             *
# Copyright (c) 2005 Altera Corporation, San Jose, California, USA.           *
# All rights reserved.                                                        *
#                                                                             *
# Permission is hereby granted, free of charge, to any person obtaining a     *
# copy of this software and associated documentation files (the "Software"),  *
# to deal in the Software without restriction, including without limitation   *
# the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
# and/or sell copies of the Software, and to permit persons to whom the       *
# Software is furnished to do so, subject to the following conditions:        *
#                                                                             *
# The above copyright notice and this permission notice shall be included in  *
# all copies or substantial portions of the Software.                         *
#                                                                             *
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
# DEALINGS IN THE SOFTWARE.                                                   *
#                                                                             *
# This agreement shall be governed in all respects by the laws of the State   *
# of California and by the laws of the United States of America.              *
#                                                                             *
# Altera does not recommend, suggest or require that this reference design    *
# file be used in conjunction or combination with any other product.          *
#******************************************************************************

#******************************************************************************
#                                                                             *
# THIS IS A LIBRARY READ-ONLY SOURCE FILE. DO NOT EDIT.                       *
#                                                                             *
#******************************************************************************

# This file provide rules and defines used to accelerate selected functions
# using the C2H tools. A list of functions to accelerate is 
# provided in the file c2h.mk in the project release/debug directory.
#
# The c2h target is c2h_build
#
# The file c2h.mk defines a list of source files to accelerate in the 
# variable C2H, e.g.:
#
# C2H_SRC = <RELATIVE PATH TO>/foo.c < RELATIVE PATH>/bar.c
#
# For each file declared in C2H_SRC, another variable is defined which lists
# the functions within that file which are to be accelerated, e.g:
#
# <RELATIVE PATH>/foo_C2H_ACCELERATORS = foo
# <RELATIVE PATH>/bar_C2H_ACCELERATORS = bar1 bar2
#
# In addition a variable is defined which lists all accelerators that are to be
# used, e.g.:
#
# <RELATIVE PATH>/foo_C2H_ENABLED_ACCELERATORS = foo
# <RELATIVE PATH>/bar_C2H_ENABLED_ACCELERATORS = bar2
# 

# Include the file c2h.mk if it exists

-include c2h.mk
-include user_c2h.mk
-include c2h_preview_switch.mk

# list of the compiler flags

C2H_FLAGS = -fno-inline

# Add the C-HAC specific C flags for all effected files

CFLAGS += $(subst $<, $(C2H_FLAGS), $(filter $<, $(C2H_SRC)))
APP_CFLAGS += $(subst $<, $(C2H_FLAGS), $(filter $<, $(C2H_SRC)))

# Command used to turn the function symbol of the .o file in C2H_SRC to WEAK 
# The linker will use the function symbol of .o file from C2H_STUBS
C2H_POST_PROCESS_CMD = $(OBJCOPY) $(foreach func, \
  $($(basename $<)_C2H_ENABLED_ACCELERATORS), --weaken-symbol $(func)) $@

# Use the C2H post process command for all affected files 
# CC_POST_PROCESS is used in gnu_rules.mk
CC_POST_PROCESS = $(subst $<, $(C2H_POST_PROCESS_CMD), $(filter $<, $(C2H_SRC)))

# Add the C2H stubs to the list of source files to process.
C2H_STUBS = $(foreach file, $(C2H_SRC),                                        \
               $(foreach func, $($(basename $(file))_C2H_ENABLED_ACCELERATORS), \
                 alt_c2h_$(func).c))

ifeq "$(origin HDL_LANGUAGE)" "undefined"
HDL_LANGUAGE = verilog
endif

C_SRCS += $(C2H_STUBS)

# Add the list of c source whith _C2H_ACCELERATOR  qualifier
C2H_SRC_ACCELERATORS = $(sort $(foreach file, $(C2H_SRC),                           \
                     $(foreach func,                                     \
                       $($(basename $(file))_C2H_ACCELERATORS), $(file))))

#List of C2H Pre-porcessed files 
C2H_PREPROC = $(foreach file,$(C2H_SRC_ACCELERATORS),                        \
                  $(OBJ_DIR)/$(strip $(subst ../,,$(basename $(file)))).c2h_pre)

# Add the HDL dependency file to the list of dependency files
DEPS += $(foreach file, $(C2H_SRC),                                          \
                  $(OBJ_DIR)/$(strip $(subst ../,,$(basename $(file)))).d)

# Rule used to generate the C-HAC HDL. A timestamp file is used to avoid updating the
# HDL file whenever there is an unrelated source file change.

C2H_TIMESTAMP = c2h_hdl-t

# Add the prop files as targets just in case the user has selected analysis.
ifeq ($(C2H_REPORT_ONLY),TRUE)
C2H_PROP = $(foreach file, $(C2H_SRC),                                        \
               $(foreach func, $($(basename $(file))_C2H_ACCELERATORS), \
                 $(APP_DIR_CORRECTED)/$(func).prop))
endif

c2h_build : $(C2H_STUBS) $(C2H_PROP)

$(C2H_PROP) : $(C2H_TIMESTAMP)

$(C2H_STUBS) : $(C2H_TIMESTAMP)
	@true

# Add c2h.mk dependency to C2H_TIMESTAMP to ensure cleaning previous C Code
ifneq "$(origin C2H_SRC)" "undefined"
ifeq ($(C2H_SRC),)
$(C2H_TIMESTAMP): c2h.mk
all:$(C2H_TIMESTAMP)
endif
endif

# Location of the .qpf file
QPF  :=$(word 1,$(wildcard $(dir $(PTF))*.qpf))

# Name of the Quartus II project remove the string ".qpf"
QPROJ=$(basename $(QPF))

# Ensure that PERL5LIB has all the required directories for chac-generate
CYGPATHEXE_U := $(shell if [ "X`which cygpath.exe 2> /dev/null`" != "X" ]; \
             then echo "cygpath -u"; else echo "echo"; fi)
PERL5LIB:=$(PERL5LIB):$(shell echo -n `$(CYGPATHEXE_U) "${QUARTUS_ROOTDIR}/sopc_builder/bin"`):$(shell echo -n `$(CYGPATHEXE_U) "${QUARTUS_ROOTDIR}/sopc_builder/bin/europa"`):$(shell echo -n `$(CYGPATHEXE_U) "${QUARTUS_ROOTDIR}/sopc_builder/bin/perl_lib"`)
export PERL5LIB

# Path to the chac-generate program
CHAC_GENERATE_PATH = $(SOPC_KIT_NIOS2)/components/altera_avalon_c_hardware_accelerator
C2H_GENERATE_PATH = $(SOPC_KIT_NIOS2)/components/altera_avalon_c_hardware_accelerator/c2h-generate

# C2H generation script
C2H_GENERATE = $(C2H_GENERATE_PATH)/c2h-generate 

# [djl 2007.01.24]
# Correct the APP_DIR path to -m type, since the IDE-generated
# makefile is now producing -l type paths, and SOPC Builder hangs when
# given a --script argument with a /cygdrive/ path.
CYGPATHEXE_M := $(shell if [ "X`which cygpath.exe 2> /dev/null`" != "X" ]; \
             then echo "cygpath -m"; else echo "echo"; fi)
APP_DIR_CORRECTED = `$(CYGPATHEXE_M) "$(APP_DIR)"`

PROJECTNAME = $(notdir $(basename $(QPROJ)))
GROUPNAME = $(notdir $(PROJECT))

# C2H global script argument
C2H_GLOBAL_ARG  = --classpath=$(C2H_GENERATE_PATH)/com.altera.c2h.jar 
C2H_GLOBAL_ARG += --classpath=$(C2H_GENERATE_PATH)/com.altera.widgets.jar 
C2H_GLOBAL_ARG += --ptf=$(PTF) 
C2H_GLOBAL_ARG += --group=$(GROUPNAME) 
C2H_GLOBAL_ARG += --qpf=$(QPROJ) 
C2H_GLOBAL_ARG += --c2h_force_recompile=$(strip $(FORCE_C2H_RECOMPILE)) 
C2H_GLOBAL_ARG += --c2h_quartus_compilation=$(strip $(C2H_QUARTUS_COMPILATION)) 
C2H_GLOBAL_ARG += --c2h_report_only=$(strip $(C2H_REPORT_ONLY)) 
C2H_GLOBAL_ARG += --flow_timestamp=$(APP_DIR_CORRECTED)/$(APP_CONFIG)/$(C2H_TIMESTAMP) 
C2H_GLOBAL_ARG += --target_cpu_name=$(strip $(C2H_TARGET_CPU)) 
C2H_GLOBAL_ARG += --chac_generate_script_location=$(CHAC_GENERATE_PATH)/chac-generate
C2H_GLOBAL_ARG += --projectname=$(PROJECTNAME)

# C2H function based script argument
C2H_ACC_ARG = $(foreach file, $(C2H_SRC),\
               $(foreach func, $($(basename $(file))_C2H_ACCELERATORS),\
               --accelerator=$(func),$(APP_DIR_CORRECTED)/$(APP_CONFIG)/$(OBJ_DIR)/$(strip $(subst ../,,$(basename $(file)))).c2h_pre,$(APP_DIR_CORRECTED)/$(APP_CONFIG)/alt_c2h_$(func).c,0$(findstring $(func),$($(basename $(file))_C2H_DCACHE_FLUSH))))

ifdef C2H_PREVIEW
C2H_PREVIEW_FLAG = --preview=$(C2H_PREVIEW)
endif

# C2H run call
C2H_RUN = $(C2H_GENERATE) $(C2H_PREVIEW_FLAG) $(C2H_GLOBAL_ARG) $(C2H_ACC_ARG)

# C2H run call info message 
ifeq ($(HDL_LANGUAGE),vhdl)
C2H_LANGUAGE  = vhdl
else
C2H_LANGUAGE  = v
endif

C2H_STUBS_HDL = $(foreach file, $(C2H_SRC),                                        \
                 $(foreach func, $($(basename $(file))_C2H_ENABLED_ACCELERATORS), \
                 $(dir $(PTF))accelerator_$(PROJECT)_$(func).$(C2H_LANGUAGE)))

C2H_RUN_MESSAGE = The Nios II C2H Compiler is generating $(notdir $(C2H_STUBS_HDL))...


# Test for existing drivers if:
# (1) The user has selected linking hardware for at least one function
# (2) The user has selected use_existing_accelerators or analyze_only,
#     neither of which generate drivers.

ifeq ($(C2H_NO_GENERATE),TRUE)
# When selecting "Use the Existing Accelerator" , check if the files exits
ifneq ($(words $(C2H_STUBS)),0)
C2H_ERROR_MESSAGE = Unable to locate all existing C2H accelerators : $(C2H_STUBS)
C2H_STUBS_TEST = test $(subst -a -f $(firstword $(C2H_STUBS)),  \
                              -f $(firstword $(C2H_STUBS)),     \
                              $(foreach stub, $(C2H_STUBS),-a -f $(stub)))
C2H_RUN = $(C2H_STUBS_TEST) || (echo $(C2H_ERROR_MESSAGE) && $(C2H_STUBS_TEST))
endif
C2H_RUN_MESSAGE = 
endif

ifeq ($(C2H_REPORT_ONLY),TRUE)
# When selecting "Analyze all accelerators" , update console message display
C2H_RUN_MESSAGE = The Nios II C2H Compiler is analyzing $(notdir $(C2H_SRC_ACCELERATORS))...
# When selecting "Use the Existing Accelerator" , check if the files exits
ifneq ($(words $(C2H_STUBS)),0)
C2H_ERROR_MESSAGE = C2H: Hardware accelerator was selected for linking with the analyze-only option, which does not update the accelerator drivers.  An existing accelerator driver was not found \(because it has not been built, or the directory was cleaned\).  Select the \"Build and Generate\" option to regenerate the accelerator drivers, or select the \"Use software implementation\" option for the accelerators that do not have drivers : $(C2H_STUBS)
C2H_STUBS_TEST = test $(subst -a -f $(firstword $(C2H_STUBS)),  \
                              -f $(firstword $(C2H_STUBS)),     \
                              $(foreach stub, $(C2H_STUBS),-a -f $(stub)))
endif
endif

ifdef C2H_STUBS_TEST
C2H_TEST = $(C2H_STUBS_TEST) || ((echo $(C2H_ERROR_MESSAGE)) && $(C2H_STUBS_TEST))
endif

ifdef ABS_BSP_INCLUDE_FILE
ifneq ($(words $(C2H_ACC_ARG)),0)
ifneq ($(C2H_REPORT_ONLY),TRUE)
BSP_TOUCH = touch $(ABS_BSP_INCLUDE_FILE)
endif
endif
endif

$(C2H_TIMESTAMP): $(C2H_PREPROC)
	@echo $(C2H_RUN_MESSAGE)
	@echo $(C2H_RUN)
	$(C2H_RUN)
	@echo $(BSP_TOUCH)
	$(BSP_TOUCH)
	@echo This is an auto-generated timestamp file for C2H_QUARTUS_COMPILATION=$(strip $(C2H_QUARTUS_COMPILATION)). > $@

# C2H preprocessor flags
C2H_FLAGS_PREPROC = -fno-inline
C2H_FLAGS_PREPROC += -D ALTERA_HARDWARE_COMPILE
C2H_FLAGS_PREPROC += -D CHAC_THIS
C2H_FLAGS_PREPROC += -D '__attribute__(x)=  '
C2H_FLAGS_PREPROC += -D '__restrict__= restrict'
C2H_FLAGS_PREPROC += -D '__builtin_va_list = int'
C2H_FLAGS_PREPROC += -D '__ULong = unsigned long'
C2H_FLAGS_PREPROC += -D '_fpos_t = long'
C2H_FLAGS_PREPROC += -D 'wint_t = char'
C2H_FLAGS_PREPROC += -D '_flock_t= int'
C2H_FLAGS_PREPROC += -D '__FILE= __SFILE'
C2H_FLAGS_PREPROC += -D '__extension__= '
C2H_FLAGS_PREPROC += -D '__prompt='
C2H_FLAGS_PREPROC += -D '__const=const'
C2H_FLAGS_PREPROC += -D '__inline__='
C2H_FLAGS_PREPROC += -MD
C2H_FLAGS_PREPROC += -E
C2H_FLAGS_PREPROC += $(CPPFLAGS) $(CFLAGS)
C2H_FLAGS_PREPROC += $(APP_CPPFLAGS) $(APP_CFLAGS)

# pre-process C2H_ACCELERATORS
$(C2H_PREPROC) : $(OBJ_DIR)/%.c2h_pre : %.c c2h.mk $(C2H_SRC_ACCELERATORS)
	$(C2H_TEST)
	@echo Compiling $(notdir $<)...
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	nios2-elf-gcc $(C2H_FLAGS_PREPROC) $< -o $@ -MF $(@:.c2h_pre=.d)

# add c2h target to all target
all:c2h_build

c2h_clean:
	$(RM) $(C2H_TIMESTAMP) $(C2H_STUBS) $(C2H_PREPROC) $(C2H_PROP)

# Add the local clean rule to the global clean rule
clean: c2h_clean

# Mark the phony rules as phony
.PHONY: c2h c2h_clean

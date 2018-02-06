#******************************************************************************
#                                                                             *
# License Agreement                                                           *
#                                                                             *
# Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
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

# This file provides the common rules which are shared between the HAL and
# uC/OS-II Makefiles. This means that it defines the "all" and "clean" rules,
# and then includes the files: gnu_rules.mk and gtf_rules.mk.
#
# gnu_rules.mk defines the rules which use the gnu tools, i.e. it defines the
# rules for compiling, archiving, and linking. gtf_rules.mk defines the rules
# for generating files which are dependent on the STF and PTF files, i.e. 
# generated_app.mk, generated_all.mk, generated.sh, alt_sys_init.c and system.h.

# Add the library source files to the source file lists

C_SRCS   += $(C_LIB_SRCS)
ASM_SRCS += $(ASM_LIB_SRCS) 

# List of makefile fragments. This is used to ensure the system is rebuilt when 
# the Makefiles change.

MAKEFILE_LIST += makefile $(SYSTEM_MAKEFILE)       \
                 $(COMPONENT_MAKEFILES)            \
                 $(GTF_GENERATED)/generated_all.mk \
                 $(GTF_GENERATED)/system.h   \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/common.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gtf_rules.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gnu_rules.mk \
				 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/system_rules.mk 

# ******************************************************************************
# *                          RULE DEFINITIONS                                  *
# ******************************************************************************

.DELETE_ON_ERROR:

# Set the name of the generated library to be based on the project name 

LIB_NAME = lib$(SYSTEM_NAME).a

# The system project generates the following output files, which are listed
# in the 'all' target:

all: proc_check $(GTF_GENERATED)/system.h crt0.o $(LIB_NAME) $(GTF_GENERATED)/generated_app.mk
all: $(GTF_GENERATED)/generated.sh
all: $(GTF_GENERATED)/generated.gdb

# When running: 'make clean' we want to delete all generated files, which is 
# what the following clean rule does. However when running: 'make clean all', 
# make doesn't realise that it needs to regenerated some of the files deleted
# by the 'clean' rule before running the 'all' rule. In particular make has
# problems with included makefiles being deleted. To avoid this, some files
# are only deleted for 'make clean' and not for 'make clean all'.

clean:
	$(RM) *.a
	find . -name '*.o' | xargs $(RM)
	$(RM) $(GTF_GENERATED)/system.h $(GTF_GENERATED)/generated.x

ifeq ($(MAKECMDGOALS),clean)
	$(RM) $(OBJ_DIR) $(GTF_GENERATED) *.d
	$(RM) $(SOPC_HOME_DIR)/install.ptf
endif

# Include the rules for making sure all the paths are Unix style

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/common.mk

# Include the component makefiles

ifneq ($(COMPONENT_MAKEFILES),)
include $(COMPONENT_MAKEFILES)
endif


proc_check:
ifeq ($(PROC),)
	@echo Error: no processor component available. 
	@echo SOPC_BUILDER_PATH may be incorrectly set in your environment.
	@echo
	@exit 1
endif

# Include the rules for building the object files and dependency files

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gnu_rules.mk

# Include the rules for generating the auto-generated files

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gtf_rules.mk

# add the linker script to the all rule

all: $(LINKER_SCRIPT)

.PHONY: all clean proc_check

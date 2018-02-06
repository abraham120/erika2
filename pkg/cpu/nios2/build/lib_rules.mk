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
# and then includes the file gnu_rules.mk.
#
# gnu_rules.mk defines the rules which use the gnu tools, i.e. it defines the
# rules for compiling, and archiving. 

# List of makefile fragments. This is used to ensure the system is rebuilt when 
# the Makefiles change.

MAKEFILE_LIST += makefile $(LIB_MAKEFILE)          \
                 $(COMPONENT_MAKEFILES)            \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/common.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gnu_rules.mk \
				 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/lib_rules.mk 

# ******************************************************************************
# *                          RULE DEFINITIONS                                  *
# ******************************************************************************

.DELETE_ON_ERROR:

# Set the name of the generated library to be based on the project name 

LIB_NAME = lib$(PROJECT).a

# The system project generates the following output files, which are listed
# in the 'all' target:

all: proc_check $(LIB_NAME)

# When running: 'make clean' we want to delete all generated files, which is 
# what the following clean rule does. 

clean:
	$(RM) *.a
	find . -name '*.o' | xargs $(RM)

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

.PHONY: all clean proc_check

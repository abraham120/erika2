#******************************************************************************
#                                                                             *
# License Agreement                                                           *
#                                                                             *
# Copyright (c) 2004-20005 Altera Corporation, San Jose, California, USA.     *
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

# This file defines some useful defines which are common to both system and
# application projects. 

# get our path converter as cygpath (for windows) or echo (no conversion on 
# unix)

CYGPATHEXE_U := $(shell if [ "X`which cygpath.exe 2> /dev/null`" != "X" ]; \
             then echo "cygpath -u"; else echo "echo"; fi)

CYGPATHEXE_M := $(shell if [ "X`which cygpath.exe 2> /dev/null`" != "X" ]; \
             then echo "cygpath -m"; else echo "echo"; fi)

# Some components need to know where the kit is installed.

SOPC_KIT_NIOS2 := $(shell echo `$(CYGPATHEXE_U) "${SOPC_KIT_NIOS2}"` )
SOPC_KIT_NIOS2_M := $(shell echo `$(CYGPATHEXE_M) "${SOPC_KIT_NIOS2}"` )

# The STF file is placed in a fixed location relative to the HAL project.

STF := $(SYSTEM_DIR)/system.stf

# Add a pre-processor flag to indicate that this is a "simulation only" build.

ifeq ($(ALT_SIM_OPTIMIZE),1)
CPPFLAGS += -DALT_SIM_OPTIMIZE
endif

# Rule used by the IDE to perform a complete rebuild. "make rebuild" is
# distinct from "make clean all" in that it can correctly regenerate and use 
# the auto-generated makefile fragments.

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: rebuild 

%.h %.tcc:
	echo make: \*\*\* [$@] File does not exist.
	echo make: \*\*\* [$@] The project may contain an out of date dependency file.
ifeq ($(PROJ_TYPE), system)
	echo make: \*\*\* [$@] Try \'Clean...\' from the Project menu for project $(SYSTEM_NAME).
else
	echo make: \*\*\* [$@] Try \'Clean...\' from the Project menu for project $(PROJECT).
endif
	exit 1

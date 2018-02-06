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

# This makefile is included into the top level makefile for system library
# projects. It is responsible for defining the rules used to build the project.
#
# In practice this file defers the rule definitions to the included file, 
# system_rules.mk. This makefile restricts itself to simply configuring some
# variables required by system_rules.mk, and including the makefile fragments
# supplied by each component.
#
# The key feature of this makefile is that it includes the auto-generated
# makefile, generated_all.mk, to obtain a list of the components to build into
# the library. This file defines four lists of components being used,
# which are combined here to form the COMPONENTS variable.
#
# COMPONENTS is then used to construct: the source search path, the include 
# search path, and a list of the makefile fragments supplied by the components 
# (which are then included).

# specify the flavour of system that's being built

SYSTEM = hal

# specify that we're a library Makefile

PROJ_TYPE = lib

# since this library is intended to be usable across all hardware
# configurations, the only components that are included are those that
# must be present in all systems, i.e. the processor and the operating
# system components

COMPONENTS += $(COMPONENTS_PROCESSOR) \
             $(COMPONENTS_OS)

# Construct the source searchpath. 

VPATH += ..

# Construct the include path based on the available components

HAL_INC_DIRS = $(wildcard $(foreach component, $(COMPONENTS), \
                           $(component)/HAL/inc $(component)/inc))

# -I$(GTF_GENERATED)  Evidence: REMOVED!!!
CPPFLAGS += -I..                      \
            $(foreach dir, $(HAL_INC_DIRS), -I$(dir))

# Construct a list of the component makefiles

COMPONENT_MAKEFILES = $(wildcard $(foreach component,$(COMPONENTS), \
                                 $(component)/HAL/src/component.mk))


# Include the rules used to build system projects

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/lib_rules.mk


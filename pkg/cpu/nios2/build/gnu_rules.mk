#******************************************************************************
#                                                                             *
# License Agreement                                                           *
#                                                                             *
# Copyright (c) 2004-2005 Altera Corporation, San Jose, California, USA.      *
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

# This file defines all the rules that use the Gnu tools, i.e. the rules used
# for compiling, archiving, linking, and generating the objdump file.
# Add a macro definition to specify the system type for conditional compiling of
# system code.

CPPFLAGS += -D__$(SYSTEM)__

# Using pipes instead of temporary files is slightly quicker.

CPPFLAGS += -pipe

# Directory in which to place the object files

OBJ_DIR := obj

# Include rules and defines used for c-hac

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/chac_rules.mk

# List of object files which are to be built. This is constructed from the input
# list of C source files (C_SRCS), C++ source files (CXX_SRCS), and assembler 
# source file (ASM_SRCS). The permitted file extensions are:
#
# .c            - for C files
# .cxx .cc .cpp - for C++ files
# .S .s         - for assembler files

OBJS = $(sort $(addprefix $(OBJ_DIR)/, $(C_SRCS:.c=.o)                        \
               $(patsubst %.cxx, %.o, $(patsubst %.cc, %.o,                   \
                                        $(patsubst %.cpp, %.o, $(CXX_SRCS)))) \
               $(patsubst %.S, %.o, $(patsubst %.s, %.o, $(ASM_SRCS)))))


# Adding ERIKA Enterprise files
EE_LIBOBJS += $(sort $(addprefix $(OBJ_DIR)/, $(C_LIBSRCS:.c=.o)            \
               $(patsubst %.S, %.o, $(patsubst %.s, %.o, $(ASM_LIBSRCS)))))

# List of dependancy files for each object file.

DEPS = $(OBJS:.o=.d)

# If no linker script definition is supplied, use the default.

ifndef LINKER_SCRIPT
ifeq ($(CUSTOM_LINKER_SCRIPT),)
LINKER_SCRIPT = $(GTF_GENERATED)/generated.x
else
LINKER_SCRIPT = $(SYSTEM_DIR)/$(CUSTOM_LINKER_SCRIPT)
endif
endif

# Pattern rules for constructing the object and dependency files that live
# in the "obj" directory.

$(OBJ_DIR)/%.o: %.c $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CC) -MD -c $(CPPFLAGS) $(CFLAGS) -o $@ $< 
	$(CC_POST_PROCESS)

$(OBJ_DIR)/%.o: %.cpp $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -MD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
	$(CXX_POST_PROCESS)

$(OBJ_DIR)/%.o: %.cc $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -MD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
	$(CXX_POST_PROCESS)

$(OBJ_DIR)/%.o: %.cxx $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -MD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
	$(CXX_POST_PROCESS)

$(OBJ_DIR)/%.o: %.S $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(AS) -MD -c $(CPPFLAGS) $(CFLAGS) $(ASFLAGS) -o $@ $<
	$(AS_POST_PROCESS)

$(OBJ_DIR)/%.o: %.s $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(AS) -MD -c $(CPPFLAGS) $(CFLAGS) $(ASFLAGS) -o $@ $<
	$(AS_POST_PROCESS)

# Pattern rules for making useful intermediate files

$(OBJ_DIR)/%.s: %.c $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CC) -S $(CPPFLAGS) $(CFLAGS) -o $@ $< 

$(OBJ_DIR)/%.s: %.cpp $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -S $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.s: %.cc $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -S $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.s: %.cxx $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -S $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.i: %.c $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CC) -E $(CPPFLAGS) $(CFLAGS) -o $@ $< 

$(OBJ_DIR)/%.i: %.cpp $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -E $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.i: %.cc $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -E $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.i: %.cxx $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<) to assembler...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -E $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<

# Pattern rules for building other object files.

%.o: %.c $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CC) -MD -c $(CPPFLAGS) $(CFLAGS) -o $@ $<
	$(CC_POST_PROCESS)

%.o: %.cpp $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -MD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
	$(CXX_POST_PROCESS)

%.o: %.cc $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -MD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
	$(CXX_POST_PROCESS)

%.o: %.cxx $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(CXX) -MD -c $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -o $@ $<
	$(CXX_POST_PROCESS)

%.o: %.S $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(AS) -MD -c $(CPPFLAGS) $(CFLAGS) $(ASFLAGS) -o $@ $<
	$(AS_POST_PROCESS)

%.o: %.s $(MAKEFILE_LIST)
	@echo Compiling $(notdir $<)...
	@mkdir -p $(dir $(basename $@))
	$(AS) -MD -c $(CPPFLAGS) $(CFLAGS) $(ASFLAGS) -o $@ $<
	$(AS_POST_PROCESS)

# Put the pwd in front of every path in the -I args because you cannot
# give two arguments to sed and one argument needs to be the -I itself

CPPFLAGS_WITH_PWD = $(subst -I,-I$(shell pwd)/,$(CPPFLAGS))

# Go through each -I in the flags and remove the pwd from directories
# which were absolute in the first place. This is detected by looking
# for a // where the two paths join or a single character followed by
# a colon and a slash in either direction.

CPPFLAGS_FOR_INCLUDES = $(foreach ARG,$(CPPFLAGS_WITH_PWD), $(shell echo $(ARG) | sed -e 's/-I\(.*\)\/\/\(.*\)/-I\/\2/' -e 's/-I\(.*\)\(.\):\([\\\/]\)\(.*\)/-I\2:\3\4/' -)) 

# Rule for putting the include directories and definitions to stdout
# This is used by the Nios II IDE C/C++ indexer

listincludedirs: $(MAKEFILE_LIST)
	echo " " | $(CC) -P -E -v -dD $(CPPFLAGS_FOR_INCLUDES) $(CFLAGS) - 

# Rule for constructing the system library.

$(LIB_NAME): $(OBJS)
	@echo Creating $@...
	$(RM) -f $@
	$(AR) $(ARFLAGS) $@ $^



# Rule for constructing the ERIKA Enterprise system library.

LDDEPS += libee.a
LIBS += -lee
LDFLAGS += -L.
libee.a: $(EE_LIBOBJS)
	@echo Creating $@...
	$(RM) -f $@
	$(AR) $(ARFLAGS) $@ $^






# After linking, we either do or dont' print out a useful report about
# memory-usage and stack-space....depending on whether this toolchain
# provides a summary-utility.
#
ifneq ($(MEM_USAGE_INFO_UTILITY),)
 SUMMARY_REPORT_COMMAND = $(MEM_USAGE_INFO_UTILITY) $(ELF)
else
 SUMMARY_REPORT_COMMAND = 
endif

# Rule for constructing the executable elf file.

$(ELF): $(OBJS) $(LINKER_SCRIPT) $(LDDEPS)
	@echo Linking $@...
	$(LD) -T'$(LINKER_SCRIPT)' $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS) 
	$(SUMMARY_REPORT_COMMAND)

# Rule for building the objdump of the executable

$(ELF).objdump: $(ELF)
	@echo Creating $@...
	$(OBJDUMP) $< > $@

# Include the dependancy files

ifneq ($(findstring clean, $(MAKECMDGOALS)),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),rebuild)
-include $(DEPS)
endif
endif
endif

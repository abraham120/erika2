# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2012  Evidence Srl
# 
# This file is part of ERIKA Enterprise.
# 
# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation, 
# (with a special exception described below).
# 
# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.
# 
# As a special exception, the copyright holders of this library give you
# permission to link this code with independent modules to produce an
# executable, regardless of the license terms of these independent
# modules, and to copy and distribute the resulting executable under
# terms of your choice, provided that you also meet, for each linked
# independent module, the terms and conditions of the license of that
# module.  An independent module is a module which is not derived from
# or based on this library.  If you modify this code, you may extend
# this exception to your version of the code, but you are not
# obligated to do so.  If you do not wish to do so, delete this
# exception statement from your version.
# 
# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.
# 
# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

# Author: 2016 Nils Scharnke
# Based on cc_cortex_iar.mk

# Select object file format
OUT_EXTENSION := out
CG_OUT_EXTENSION := $(OUT_EXTENSION)
CG_REC_EXTENSION := rec

BIN_EXTENSION := bin
HEX_EXTENSION := hex

BINDIR_CYG := /usr/bin
CG_INCLUDE_DIR := $(call short_native_path, $(COMP_DIR)/include/v800)


# Bin directories used for compilation
# BINDIR_ASM      - directory of the Assembler
# BINDIR_CC       - directory of the C compiler
# BINDIR_LINK      - directory of the C compiler used for linking

ifndef EE_ASM
EE_ASM:=$(COMP_DIR)/ccv850.exe
endif

ifndef EE_CC
EE_CC:=$(COMP_DIR)/ccv850.exe
endif

ifndef EE_LINK
EE_LINK:=$(COMP_DIR)/ccv850.exe
endif

ifndef EE_AR
EE_AR:=$(COMP_DIR)/ccv850.exe
endif

ifndef EE_REC
EE_REC:=$(COMP_DIR)/gsrec.exe
endif

#Add application file to dependencies
ifneq ($(ONLY_LIBS), TRUE)

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
OPT_LIBS += 

TARGET = $(TARGET_NAME).$(CG_OUT_EXTENSION) $(TARGET_NAME).$(CG_REC_EXTENSION) 


endif	# !ONLY_LIBS

# INCLUDE_PATH is a colon separated list of directories for source file searching

OPT_INCLUDE = $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call short_native_path,$d)))

# OPT_AR: options for library generation
OPT_AR = -archive


## OPT_CMN are common options included in all other options
OPT_CMN = -sda=none \
          -dwarf2 \
          -prepare_dispose \
          -no_callt \
          -reserve_r2 \
          -inline_prologue \
          -notda \
          -fnone \
          --unknown_pragma_warnings \
          -list  \
          -registermode=22 
          
          # -sda=none   no small data area use - modify for optimization (depends on application) 
          # -dwarf2    enable generation of DWARF debugging info 
          # -prepare_dispose   use prepare/dispose instructions 
          # -no_callt   do not use callt instructions 
          # -reserve_r2   reserve r2 for use by the user 
          # -inline_prologue   force compiler to use inline code sequences 
          # -notda   disable tiny data areas 
          # -fnone   disallow all floating-point operations 
          # --unknown_pragma_warnings   treat unknown pragmas as warnings 
          # -list   create source listing 
          # -registermode=22  number of registers used by the compiler

# define CPU
ifeq ($(call iseeopt, __RH850G3M__), yes)
OPT_CMN += -cpu=RH850G3M
else ifeq ($(call iseeopt, __RH850G3K__), yes)
OPT_CMN += -cpu=RH850G3K
else 
#$(error RH850 CPU -> CPU type either not specified or not supported! (Supported CPUs-> G3M, G3K))
endif


ifeq ($(call iseeopt, DEBUG), yes)
OPT_CMN += --debug -Odebug
else
OPT_CMN += --debug -Ogeneral -w 
endif

ifdef VERBOSE
OPT_CMN += -v
endif

## OPT_CC are the options for C compiler invocation
OPT_CC += -c $(OPT_CMN)

# Specific option from the application makefile
OPT_CC += $(CFLAGS) 


##OPT_ASM are the options for assembler invocation

OPT_ASM += -preprocess_assembly_files -passsource  -c $(OPT_CMN)

# Specific option from the application makefile
OPT_ASM += $(ASFLAGS)


##OPT_ASM are the options for assembler invocation
OPT_LINK += $(OPT_CMN) -multiple

# Specific option from the application makefile
OPT_LINK += $(LDFLAGS)

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

DEFS_ASM = $(addprefix -D, $(EEOPT) )
DEFS_CC  = $(addprefix -D, $(EEOPT) )


# Automatic dependency generation
ifeq ($(call iseeopt, NODEPS), yes)
DEPENDENCY_OPT = 
make-depend =
else # NODEPS
DEPENDENCY_OPT = -MMD
endif # NODEPS
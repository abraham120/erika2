# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2016  Evidence Srl
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

## Author: 2017,  Giuseppe Serano

##
## Compiler related options
##


## AVR Tools GNU GCC compiler

# BINDIR is the directory of assembler, linker, ... distributed with AVR Tools
BINDIR := $(call native_path,$(AVR_TOOLS))/bin

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
ALLINCPATH += \
$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))
#$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

ifndef	AVR_GCCPREFIX
AVR_GCCPREFIX = avr
endif

ifndef	EE_OBJDUMP
EE_OBJDUMP = $(BINDIR)/$(AVR_GCCPREFIX)-objdump
endif

# GNUPro compilers
ifndef	EE_LINK
EE_LINK = $(BINDIR)/$(AVR_GCCPREFIX)-gcc
endif

ifndef	EE_ASM
EE_ASM = $(BINDIR)/$(AVR_GCCPREFIX)-gcc
endif

ifndef	EE_CC
EE_CC = $(BINDIR)/$(AVR_GCCPREFIX)-gcc
endif

ifndef	EE_CXX
EE_CXX = $(BINDIR)/$(AVR_GCCPREFIX)-g++
endif

ifndef	EE_AR
EE_AR = $(BINDIR)/$(AVR_GCCPREFIX)-ar
endif

ifndef	EE_NM
EE_NM = $(BINDIR)/$(AVR_GCCPREFIX)-nm
endif

ifndef	EE_OBJCOPY
EE_OBJCOPY = $(BINDIR)/$(AVR_GCCPREFIX)-objcopy
endif

ifndef	EE_SIZE
EE_SIZE = $(BINDIR)/$(AVR_GCCPREFIX)-size
endif

################################################################################
## OPT_CC are the options for arm compiler invocation			      ##
# -mmcu=atmega128    = generate optimized code for AVR atmega128 processor     #
# -Os                 = select the optimization level			       #
#                     NOTE that -O0 can NOT be used because it not expands     #
#                     inline functions!!!!				       #
# -c                 = compile only (do not link)			       #
# -Wall		   = all compiling warning				       #
# -Winline	         = warn if a function does not expand inline           #
# -finline-functions = make all simple functions inline			       #
##-Wl                =Pass option to the linker avr-ld   		      ##
################################################################################

## OPT_CC are the options for avr compiler invocation
ifeq ($(call iseeopt, __ARDUINO_SDK__), yes)
OPT_CC += -c
ifeq ($(call iseeopt, DEBUG), yes)
OPT_CC += -g
endif
OPT_CC += -Os
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
OPT_CC += -std=gnu11
else	# __ARDUINO_SDK_CC__
OPT_CC += -w
endif	# __ARDUINO_SDK_CC__
ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)
OPT_CC += -ffunction-sections -fdata-sections
else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
OPT_CC += -fdata-sections -ffunction-sections
endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
ifneq ($(AVR8_MCU),)
OPT_CC += -mmcu=$(AVR8_MCU)
endif	# AVR8_MCU
else	# __ARDUINO_SDK__
OPT_CC = -Wall -Winline -w -c
ifeq ($(call iseeopt, __AVR8_GCC_C99__), yes)
OPT_CC += -std=gnu99
else
OPT_CC += -std=c89
endif
ifeq ($(findstring atxmega, $(AVR8_MCU)), atxmega)
EEOPT += __AVR8_GCC_OSIZE__
endif	# ATXMEGA
ifeq ($(call iseeopt, DEBUG), yes)
OPT_CC += -gdwarf-2
endif
ifeq ($(call iseeopt, __AVR8_GCC_OSIZE__), yes)
OPT_CC += -Os
endif
ifneq ($(AVR8_MCU),)
OPT_CC += -fdata-sections -ffunction-sections
OPT_CC += -Werror-implicit-function-declaration -Wmissing-prototypes
OPT_CC += -Wpointer-arith -Wstrict-prototypes -mrelax
OPT_CC += -mmcu=$(AVR8_MCU)
endif	# AVR8_MCU
endif	# __ARDUINO_SDK__
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

## OPT_CXX are the options for avr compiler invocation
ifeq ($(call iseeopt, __ARDUINO_SDK__), yes)
OPT_CXX += -c
ifeq ($(call iseeopt, DEBUG), yes)
OPT_CXX += -g
endif
OPT_CXX += -Os
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
OPT_CXX += -std=gnu++11
else	# __ARDUINO_SDK_CC__
OPT_CXX += -w
endif	# __ARDUINO_SDK_CC__
ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)
OPT_CXX += -fno-exceptions -ffunction-sections -fdata-sections
OPT_CXX += -fno-threadsafe-statics
else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
OPT_CXX += -fdata-sections -ffunction-sections -fno-exceptions
endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
ifneq ($(AVR8_MCU),)
OPT_CXX += -mmcu=$(AVR8_MCU)
endif	# AVR8_MCU
else	# __ARDUINO_SDK__
OPT_CXX = -Wall -Winline -w -c
ifeq ($(call iseeopt, __AVR8_GCC_C99__), yes)
OPT_CXX += -std=gnu99
else
OPT_CXX += -std=c89
endif
ifeq ($(call iseeopt, DEBUG), yes)
OPT_CXX += -gdwarf-2
endif
OPT_CXX += -fdata-sections -ffunction-sections
OPT_CXX += -Werror-implicit-function-declaration
OPT_CXX += -Wpointer-arith -mrelax
OPT_CXX += -mmcu=$(AVR8_MCU)
endif	# __ARDUINO_SDK__
# Specific option from the application makefile
OPT_CXX += $(CFLAGS) $(CXXFLAGS)

## OPT_ASM are the options for avr assembler invocation
# --gdwarf2     = generate dwarf2 debbugging information for each assembler line
## -x assembler-with-cpp -gdwarf2
OPT_ASM = -c -x assembler-with-cpp
ifneq ($(call iseeopt, __ARDUINO_SDK__), yes)
ifeq ($(call iseeopt, __AVR8_GCC_C99__), yes)
OPT_ASM += -std=gnu99
else
OPT_ASM += -std=c89
endif
endif	# !__ARDUINO_SDK__
ifneq ($(AVR8_MCU),)
OPT_ASM += -mrelax
ifeq ($(findstring atxmega, $(AVR8_MCU)), atxmega)
OPT_ASM += -Wa,-gdwarf2
else	# ATXMEGA
ifeq ($(call iseeopt, DEBUG), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK__), yes)
OPT_ASM += -g
else	# __ARDUINO_SDK__
OPT_ASM += -Wa,-gdwarf2
endif	# __ARDUINO_SDK__
endif	# DEBUG
endif	# ATXMEGA
OPT_ASM += -mmcu=$(AVR8_MCU)
endif	# AVR8_MCU

# OPT_AR represents the options for avr linker invocation
OPT_AR = rcs

# OPT_LINK represents the options for avr linker invocation
ifeq ($(call iseeopt, __ARDUINO_SDK__), yes)
OPT_LINK += -Os -Wl,--gc-sections
ifneq ($(AVR8_MCU),)
OPT_LINK += -mmcu=$(AVR8_MCU)
endif	# AVR8_MCU
else	# __ARDUINO_SDK__
OPT_LINK = $(LDFLAGS)
ifneq ($(AVR8_MCU),)
OPT_LINK += -Wl,--start-group -Wl,--end-group -Wl,--gc-sections
OPT_LINK += -mrelax -Wl,--relax
ifeq ($(findstring atxmega, $(AVR8_MCU)), atxmega)
OPT_LINK += -Wl,--section-start=.BOOT=0x4000
endif	# ATXMEGA
OPT_LINK += -mmcu=$(AVR8_MCU)
endif	# AVR8_MCU
endif	# __ARDUINO_SDK__

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

DEFS_ASM = $(addprefix -D,$(EEOPT))
DEFS_CC  = $(addprefix -D,$(EEOPT))
DEFS_CXX  = $(addprefix -D,$(EEOPT))

ifeq ($(call iseeopt, __BIN_DISTR), yes) 
# Note: the defines used in EEOPT to compile the library
# are already added in the eecfg.h
DEFS_ASM += -D__CONFIG_$(EELIB)__
DEFS_CC  += -D__CONFIG_$(EELIB)__
DEFS_CXX  += -D__CONFIG_$(EELIB)__
endif

# Automatic dependency generation
ifeq ($(call iseeopt, NODEPS), yes)
DEPENDENCY_OPT =
make-depend =
else	# EEOPT NODEPS
# Create dependency for all headers, and add a target for each header
DEPENDENCY_OPT = -MP -MMD -MF $(call native_path,$(subst .o,.d_tmp,$(@)))
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes)
# Dependencies on Windows need path translation and quote remotion
make-depend = sed -e 's_\\\(.\)\(.\)_/\1\2_g' \
	-e 's_\<\([a-zA-Z]\):/_/cygdrive/\l\1/_g' < $1_tmp > $1 && rm $1_tmp
else	# EEOPT __RTD_CYGWIN__
make-depend = mv $1_tmp $1
endif	# EEOPT __RTD_CYGWIN__
endif	# EEOPT NODEPS

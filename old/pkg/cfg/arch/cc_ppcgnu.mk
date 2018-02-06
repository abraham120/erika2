# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2008  Evidence Srl
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

##
## PowerPC
##

ifeq ($(findstring __MPC5XX__,$(EEALLOPT)), __MPC5XX__)
PPCCOMMON=YES
endif
ifeq ($(findstring __MPC5PROTECTED__,$(EEALLOPT)), __MPC5PROTECTED__)
PPCCOMMON=YES
endif

##
## PowerPC, common part
##

ifeq ($(PPCCOMMON),YES)

# MPC5BASE is the base directory of development environment
# it should be defined in your .bashrc
# MPC5BASE =

# BINDIR is the directory of assembler, compiler, linker...
BINDIR = $(MPC5BASE)/bin

# GNUPro compilers
ifndef EE_LINK
EE_LINK=$(QUIET)$(BINDIR)/powerpc-eabi-linux-gnu-ld
endif
ifndef EE_ASM
EE_ASM=$(QUIET)$(BINDIR)/powerpc-eabi-linux-gnu-as
endif
ifndef EE_CC
EE_CC=$(QUIET)$(BINDIR)/powerpc-eabi-linux-gnu-gcc
endif
ifndef EE_AR
EE_AR=$(QUIET)$(BINDIR)/powerpc-eabi-linux-gnu-ar
endif

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
ALLINCPATH = -I$(APPBASE) -I$(EEBASE)/pkg

## OPT_CC are the options for arm compiler invocation
# -mpowerpc         = generate optimized code for PowerPC family processor
# -O                = select the optimization level
#                     NOTE that -O0 can NOT be used because it not expands
#                     inline functions!!!!
# -mnew-mnemonics   = select mnemonics defined for PowerPC architecture
# -mbig-endian      = (optional)
# -meabi            = Embedded PowerPC system do adhere to Embedded Application
#                     Binary Interface
# -ggdb             = add debug tables for GDB
# -c                = compile only (do not link)
# -Wall             = all compiling warning
# -Winline          = warn if a function does not expand inline
# -finline-functions = make all simple functions inline
# -mregnames
OPT_CC = -mpowerpc -mnew-mnemonics -meabi -mregnames -mbig-endian\
        -O1 -Wall -Winline -c $(ALLINCPATH)
#OPT_CC = -mpowerpc -mnew-mnemonics -meabi\
#        -O2 -Wall -Winline -c $(ALLINCPATH)
ifneq ($(findstring __BIN_DISTR,$(EEALLOPT)), __BIN_DISTR)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPT_CC += -ggdb
endif
endif

## OPT_ASM are the options for asm invocation
# -mppc32           = generate optimized code for PowerPC 32-bit architecture
OPT_ASM = -mppc32

ifneq ($(findstring __BIN_DISTR,$(EEALLOPT)), __BIN_DISTR)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPT_ASM += --gstabs
endif
endif

# OPT_LINK represents the options for mpclink invocation
ifeq ($(findstring __DEFAULT_LD_SCRIPT__,$(EEOPT)) , __DEFAULT_LD_SCRIPT__)
OPT_LINK += --script=out/loc_gnu.ld -u__start
LINKDEP = out/loc_gnu.ld out/loc_mpc566evb.ld
else
OPT_LINK += 
endif

DEFS_ASM = $(addprefix -D, $(EEOPT) )
DEFS_CC  = $(addprefix -D, $(EEOPT) )

endif


##
## MPC5 Non Protected
##
ifeq ($(findstring __MPC5XX__,$(EEALLOPT)), __MPC5XX__)
# here there are the parts that are specific for the non-protected part

# (none at the moment)

endif


##
## MPC5 Protected
##
ifeq ($(findstring __MPC5PROTECTED__,$(EEALLOPT)), __MPC5PROTECTED__)
# here there are the parts that are specific for the protected part

# (none at the moment)

endif

# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2011  Evidence Srl
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
# Based on rules_cortex_generic.mk

# Enable verbose output from EE_OPT
ifeq ($(call iseeopt, VERBOSE), yes)
VERBOSE = 1
endif

# Initial definition of target all as predefined
all:

include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

ifneq ($(ONLY_LIBS), TRUE)

ifneq ($(call iseeopt, __BIN_DISTR), yes)
LIBDEP += $(ERIKALIB)
else
LIBDEP += $(EEBASE)/lib/$(ERIKALIB)
endif

endif	# ONLY_LIBS


#Includes from Compiler
INCLUDE_PATH += $(CG_INCLUDE_DIR)

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)

# Specific option from the application makefile
LIBDEP += $(LDDEPS)


include $(PKGBASE)/cfg/cfg.mk

##
# MCU
##

#####################################

# R7F701503
ifeq ($(call iseeopt, __R7F701503__), yes)

MCU_MODEL = R7F701503

ifndef MCU_LINKERSCRIPT
ifeq ($(call iseeopt, __IAR__), yes)
MCU_LINKERSCRIPT = $(call short_native_path, $(EEBASE)/pkg/mcu/renesas_r7f701503/src/iar/lnkr7f701503.icf)
endif # __IAR__
ifeq ($(call iseeopt, __GHS__), yes)
MCU_LINKERSCRIPT = $(call short_native_path, $(EEBASE)/pkg/mcu/renesas_r7f701503/src/ghs/dr7f701503.ld)
endif # __GHS__
endif # MCU_LINKERSCRIPT
MCU_STARTUP = $(STARTUP_SRCS)
TARGET_NAME = r_1503
endif	# __R7F701503__

# R7F701057
ifeq ($(call iseeopt, __R7F701057__), yes)

MCU_MODEL = R7F701057

ifndef MCU_LINKERSCRIPT
ifeq ($(call iseeopt, __IAR__), yes)
MCU_LINKERSCRIPT := $(call short_native_path, $(EEBASE)/pkg/mcu/renesas_r7f701057/src/iar/lnkr7f701057.icf)
endif # __IAR__
ifeq ($(call iseeopt, __GHS__), yes)
MCU_LINKERSCRIPT := $(call short_native_path, $(EEBASE)/pkg/mcu/renesas_r7f701057/src/ghs/dr7f701057.ld )
endif # __GHS__
endif # MCU_LINKERSCRIPT
MCU_STARTUP = $(STARTUP_SRCS)
TARGET_NAME = r_1057
endif	# __R7F701057__

# No MCU model
ifndef MCU_MODEL
$(error No known MCU model found in EE_OPT)
endif	# MCU_MODEL


EE_BOOT_SRCS := $(MCU_STARTUP)

# Boot code containing _start should stay outside of the library in
# case of normal compilation
ifeq ($(call iseeopt, __BIN_DISTR), yes)
LIBSRCS += $(EE_BOOT_SRCS)
else
SRCS += $(EE_BOOT_SRCS)
endif

# Add a custom linker script if provided by the user
LINKDEP += $(MCU_LINKERSCRIPT)

ifeq ($(call iseeopt, __NO_APP__), yes)
TARGET := $(ERIKALIB)

# we put the eecfg.c inside the library
LIBEESRCS += eecfg.c
endif

#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##

LIBEESRCS += $(EE_SRCS)
LIBEEOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(patsubst %.850, %.o, $(patsubst %.S, %.o, $(LIBEESRCS)))))))

LIBOBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(patsubst %.850, %.o, $(patsubst %.S, %.o, $(LIBSRCS)))))))

SRCS += $(APP_SRCS)
SRCS += $(EE_SRCS)

OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(patsubst %.s, %.o, \
$(patsubst %.asm, %.o, $(patsubst %.850, %.o, $(patsubst %.S, %.o, $(SRCS)))))))

# Variable used to import dependencies
ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS) 

OBJDIRS=$(sort $(dir $(ALLOBJS)))

INCLUDE_PATH += $(PKGBASE) $(call short_native_path,$(APPBASE)) . $(CG_INLCUDE_DIR)

vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.s $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)
vpath %.asm $(EE_VPATH) $(APPBASE)
vpath %.850 $(EE_VPATH) $(APPBASE)

## Compute common variables ##
COMPUTED_INCLUDE_PATH := $(OPT_INCLUDE)
COMPUTED_OPT_LINK := $(OPT_LINK)
COMPUTED_OPT_ASM := $(OPT_ASM)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_AR := $(OPT_AR)
COMPUTED_OPT_OBJDUMP := $(OPT_OBJDUMP)
COMPUTED_OPT_OBJCOPY := $(OPT_OBJCOPY)
COMPUTED_OPT_FROMELF := $(OPT_FROMELF)


ifeq ($(call iseeopt, __IAR__), yes)
COMPUTED_OPT_BIN2HEX := $(OPT_BIN2HEX)
endif	# !__IAR__ (Default compiler toolchain)

##
# Select input filename format ##
##

SOURCEFILE = $(call short_native_path,$(dir $<))\\$(notdir $<)


TARGETFILE = $(call native_path,$@)

 

## Main rules: all clean ##

.PHONY: all clean

all: make_directories $(ALL_LIBS) $(TARGET)
	@echo "************************************"
	@echo "Compilation terminated successfully!"

clean:
	@-rm -rf obj *.a *.map *.sim workspace *.htm *.$(CG_BIN_EXTENSION) \
	*.$(CG_OUT_EXTENSION) *.dnm *.dla *.dba *.rec *.map
# deps deps.pre ee_c_m0regs.h
	@echo "CLEAN";

	
	
### Target file creation ###

ifeq ($(call iseeopt, __IAR__), yes)

$(TARGET_NAME).$(CG_OBJDUMP_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "OBJDUMP";
	$(QUIET)$(EE_BIN2HEX) $(COMPUTED_OPT_OBJDUMP) \
	$(TARGET_NAME).$(CG_OUT_EXTENSION) $(TARGET_NAME).$(CG_OBJDUMP_EXTENSION)

$(TARGET_NAME).$(CG_HEX_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "BIN2HEX";
	$(QUIET)$(EE_BIN2HEX) $(COMPUTED_OPT_BIN2HEX) \
	$(TARGET_NAME).$(CG_OUT_EXTENSION) $(TARGET_NAME).$(CG_HEX_EXTENSION)
else # !__IAR__

ifeq ($(call iseeopt, __GHS__), yes)
$(TARGET_NAME).$(CG_REC_EXTENSION): $(TARGET_NAME).$(CG_OUT_EXTENSION)
	@echo "REC";
	$(QUIET)$(EE_REC) \
	$(TARGET_NAME).$(CG_OUT_EXTENSION) -o $(TARGET_NAME).$(CG_REC_EXTENSION)
else # !__GHS__
	@echo "No valid compiler defined!";
endif # __GHS__
endif # __IAR__



$(TARGET_NAME).$(CG_OUT_EXTENSION): $(OBJS) $(LINKDEP) $(LIBDEP) 
	@echo "LD";
ifeq ($(call iseeopt, __IAR__), yes)
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) -o $@ $(OBJS) \
	--config $(MCU_LINKERSCRIPT)
else	# !__IAR__
ifeq ($(call iseeopt, __GHS__), yes)
	$(QUIET)$(EE_LINK) $(COMPUTED_OPT_LINK) -o $@ $(OBJS) $(OPT_LIBS) $(subst \,/,$(LINKDEP)) \
	-map="$(TARGET_NAME).map"
endif	# __GHS__
endif	# __IAR__

### Object file creation ###

# produce the object file from assembly code in a single step
## TODO: - Only one rule for .s and .S
$(OBJDIR)/%.o: %.S
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(SOURCEFILE) \
	-o $(TARGETFILE)


$(OBJDIR)/%.o: %.s
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(DEPENDENCY_OPT) \
  $(SOURCEFILE) -o $(TARGETFILE)


$(OBJDIR)/%.o: %.asm
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(DEPENDENCY_OPT) \
  $(SOURCEFILE) -o $(TARGETFILE)
  
$(OBJDIR)/%.o: %.850
	$(VERBOSE_PRINTASM) $(EE_ASM) $(COMPUTED_OPT_ASM) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_ASM) $(DEPENDENCY_OPT) \
  $(SOURCEFILE) -o $(TARGETFILE)
  
# produce the object file from C code in a single step
$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC) $(EE_CC) $(COMPUTED_OPT_CC) \
	$(COMPUTED_INCLUDE_PATH) $(DEFS_CC) $(DEFS_ISR) $(DEPENDENCY_OPT) \
	$(SOURCEFILE) -o $(TARGETFILE)

	$(QUIET)$(call make-depend, $<, $@, $(subst .o,.d,$@))

# TODO: produce the object file from C++ code in a single step
# $(OBJDIR)/%.o: %.cpp
# $(OBJDIR)/%.o: %.cxx
# $(OBJDIR)/%.o: %.cc
# $(OBJDIR)/%.o: %.C

##
## EE Library
##

libee.a: $(LIBEEOBJS)
	@echo "AR    $(ERIKALIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) -o $@ $^

##
## Directories
##

.PHONY: make_directories

## Objects depend on directories, but they are not remade if directories change
$(ALLOBJS): | make_directories

make_directories: $(OBJDIRS)

## Directories are (re)created only when some of them don't exist already
$(OBJDIRS): 
	@echo "MAKE_DIRECTORIES"
	$(QUIET)mkdir -p $(OBJDIRS)

# the eeopt file is generated when dealing with ONLY_LIBS!
#
# this is a phony because the source code does not depend on this file
# and its content higly depends on the EEOPT variables...
#
.PHONY: generate_eeopt
generate_eeopt:
	@echo "GEN   eeopt.h"
	$(QUIET)for x in $(EEOPT); do \
		echo \#ifndef $${x}      >> eeopt.h; \
		echo \#define $${x}      >> eeopt.h; \
		echo \#endif             >> eeopt.h; \
	done;

##
## Automatic Generation of dependencies
##

dependencies=$(subst .o,.d,$(ALLOBJS))
ifneq ($(call iseeopt, NODEPS), yes) 
ifneq ($(MAKECMDGOALS),clean)
-include $(dependencies)
endif
endif

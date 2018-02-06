# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2012  Evidence Srl
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

## Makefile for Benchmark project
## Author: 2012,  Gianluca Franchino
############################################################################
#
# CORTEX M0
#
############################################################################
APPBASE := ..
OUTBASE := output
OBJDIR := ./objdir

native_path = "$(shell cygpath -w $1 | sed -e 's/\\$$//' -e 's/\\/\\\\/g')"

ifndef ARM_ROOT
    ARM_ROOT := $(shell cygpath `cygpath -ms 'D:/Keil/ARM'`)
endif

# Select object file format
CG_OUT_EXTENSION := out

BINDIR_CYG := /usr/bin

#ARM_ROOT: Keil uVision ARM Installation Root Folder.
#          Default "C:\Keil\ARM".
CG_TOOL_ROOT := $(ARM_ROOT)

CG_BIN_DIR := $(CG_TOOL_ROOT)/BIN40

CG_BINUTILS_DIR := $(CG_TOOL_ROOT)/BIN

CG_LIB_DIR := $(CG_TOOL_ROOT)/RV31/LIB

CG_INCLUDE_DIR := $(CG_TOOL_ROOT)/RV31/INC/

ifdef TMPDIR
CG_TMPDIR := $(call native_path, $(TMPDIR))
else
CG_TMPDIR := $(call native_path, .)
endif

# Bin directories used for compilation
# BINDIR_ASM      - directory of the Assembler
# BINDIR_CC       - directory of the C compiler
# BINDIR_DEP      - directory of the C compiler used for dependencies
# BINDIR_BINUTILS - directory of the binutils

BINDIR_ASM      := $(CG_BIN_DIR)
BINDIR_CC       := $(CG_BIN_DIR)
BINDIR_BINUTILS := $(CG_BINUTILS_DIR)
BINDIR_DEP      := $(CG_BIN_DIR)

ifndef ARM_ASM
ARM_ASM:=$(BINDIR_ASM)/armasm.exe
endif

ifndef KEIL_CC
ARM_CC:=$(BINDIR_CC)/armcc.exe
endif

ifndef KEIL_LINK
ARM_LINK:=$(CG_BIN_DIR)/armlink.exe
endif

ifndef KEIL_DEP
ARM_DEP:=$(BINDIR_DEP)/armcc.exe
endif

ifndef KEIL_AR
ARM_AR:=$(CG_BIN_DIR)/armar.exe
endif

ifdef VERBOSE
QUIET=
VERBOSE_DEVNULL=
else
QUIET=@
VERBOSE_DEVNULL=>/dev/null
endif

VERBOSE_PRINTCC= $(QUIET)printf "CC  $(notdir $<)\\n";
VERBOSE_PRINTASM=$(QUIET)printf "ASM  $(EXPERIMENT) $(notdir $<)\\n";

#include base_var.mk

SOURCEFILE = $(call native_path,$<)
TARGETFILE = $(call native_path,$@)

ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_1.6.0.20111119_0157\ee_files'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=

############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -O3 --apcs=interwork -W 
CFLAGS  += -DTEST_TIMING -D__BM_CORTEX_M0__ -D__LPC1227__ -D__MULTI__ 
CFLAGS  += -D__BM_EMBOS__ -DTIMINGTEST_NUM_RECORDS=30  
CFLAGS  += -D__LPC1227__ -DBM_USE_UART -DUSE_PRINT_OUT -DBM_USE_SYSTICK
CFLAGS  += --cpu=Cortex-M0 -c -D__EVAL 

CFLAGS  += -I $(call native_path, $(CG_INCLUDE_DIR)) 
CFLAGS  += -I"$(shell cygpath -w $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/inc/Drivers/include)" 
CFLAGS  += -I"$(shell cygpath -w $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/inc/CM0/DeviceSupport/NXP/LPC12xx)" 
CFLAGS  += -I"$(shell cygpath -w $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/inc/CM0/CoreSupport)"
CFLAGS  += -I"$(shell cygpath -w ../embOS/Start/Inc)"

ASFLAGS += --cpu Cortex-M0 --pd "__EVAL SETA 1" --xref --cpreproc --cpreproc_opts=-D,__CORTEX_M0__ 
ASFLAGS += --cpreproc_opts=-D,__EE_DEF_SYS_INIT__

ifdef CG_LIB_DIR
LDFLAGS  += --libpath $(call native_path, $(CG_LIB_DIR))
endif

LDFLAGS  += --userlibpath .
LDFLAGS  += --cpu Cortex-M0 --strict --summary_stderr
LDFLAGS  +=	--info summarysizes --map --xref --callgraph --symbols --info sizes
LDFLAGS  +=	--info totals --info unused --info veneers
LDFLAGS  += --scatter=template.sct --entry Reset_Handler


#ASFLAGS += -g
#CFLAGS  += -g -DOS_LIBMODE_DP -DDEBUG={1} 
#LDFLAGS += --debug
CFLAGS  += -DOS_LIBMODE_XR
#Add embOS library
#LIBS    += ../embOS/Start/Lib/osT6LDP.lib
LIBS    += ../embOS/Start/Lib/osT6LXR.lib

#
# Sources
#
############################################################################

APP_SRCS +=  code.c timingtest.c bm_embOS.c startup_LPC12xx.s bm_cortex_m0_log_header.c
APP_SRCS += $(filter-out $(EMBOS_SRC_DEL), $(subst ../, ,$(shell ls ../embOS/Start/BoardSupport/NXP/LPC122x/Setup/*.c)))

APP_SRCS += $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/CM0/DeviceSupport/NXP/LPC12xx/system_LPC12xx.c 
APP_SRCS += $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/Drivers/source/lpc12xx_iocon.c
APP_SRCS += $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/Drivers/source/lpc12xx_libcfg_default.c
APP_SRCS += $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/Drivers/source/lpc12xx_uart.c
APP_SRCS += $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/Drivers/source/lpc12xx_sysctrl.c
#Uncomment the following line if -DBM_USE_SYSTICK is not present in CFLAGS*/
#APP_SRCS += $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/libsrc/Drivers/source/lpc12xx_timer32.c

TARGET := c_m0.out

OBJS=$(addprefix $(OBJDIR)/, $(sort \
$(patsubst %.cxx, %.o, \
$(patsubst %.cc, %.o, $(patsubst %.cpp, %.o, \
$(patsubst %.C, %.o,$(CXX_SRCS)))))\
$(patsubst %.c, %.o, \
$(patsubst %.S, %.o, $(patsubst %.s, %.o, $(APP_SRCS))))))


SRCS = $(addprefix ../,$(APP_SRCS))

OBJDIRS = $(sort $(dir $(OBJS)))

vpath %.c ../
vpath %.s ../


.PHONY: all clean

all: make_directories $(TARGET)

clean:
	@-rm -rf *.lst *.a *.map *.sim *.out deps deps.pre $(OBJDIR) 	

c_m0.out: $(OBJS)
	@echo "LD";
	$(QUIET) $(ARM_LINK) $(LDFLAGS) --output $@ $(OBJS) $(LIBS) --map --list=c_m0.map
	@echo "************************************"
	@echo "EmbOS app compilation terminated successfully!"

$(OBJDIR)/%.o: %.s
	$(VERBOSE_PRINTASM) $(ARM_ASM) $(ASFLAGS) $(SOURCEFILE) -o $(TARGETFILE)

$(OBJDIR)/%.o: %.c
	$(VERBOSE_PRINTCC) $(ARM_CC) $(CFLAGS) $(SOURCEFILE) -o $(TARGETFILE)

##
## Directories
##

.PHONY: make_directories
## Objects depend on directories, but they are not remade if directories change
$(OBJS): | make_directories

make_directories: $(OBJDIRS)

## Directories are (re)created only when some of them don't exist already
$(OBJDIRS): 
	@echo "MAKE_DIRECTORIES"
	mkdir -p $(OBJDIRS)


############################################################################
#
# end
#
############################################################################

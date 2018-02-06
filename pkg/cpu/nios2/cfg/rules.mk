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

## Author: 2003- Paolo Gai
## CVS: $Id: rules.mk,v 1.8 2008/07/01 08:01:29 pj Exp $


##################################################################################
# NOTE
# This makefile is only useful to build Nios II libraries!!!
# To build a real application under Nios II, use the Altera development kit...
##################################################################################

ifneq ($(call iseeopt, __BIN_DISTR_FULL__), yes)
ifneq ($(call iseeopt, __BIN_DISTR_LIMITED__), yes)
all:
	@echo you can use this makefile only for building NIOS2 libraries!!!
endif
endif

# These flags can be set from C/C++ build property page -> nios2-elf-gcc -> General
CFLAGS = -DALT_DEBUG -O3 -g -Wall

ASFLAGS = -Wa,-gdwarf2

# These flags can be set from C/C++ build property page -> nios2-elf-ar.archiver -> General
ARFLAGS = -src

# This project
PROJECT := ee

RM := rm -rf

# eecfg.h has been generated in the current directory!
CFLAGS += -I.

# these defines depend on the Nios II Version
# please look at nios2_startup_scripts
ifndef EE_NIOS2_VERSION
$(error EE_NIOS2_VERSION not defined!)
endif

EE_NIOS2_DIR = /cygdrive/c/altera/$(EE_NIOS2_VERSION)/nios2eds
EE_SOPC_DIR = /cygdrive/c/altera/$(EE_NIOS2_VERSION)/ip/sopc_builder_ip

COMPONENTS_PROCESSOR := $(EE_NIOS2_DIR)/components/altera_nios2
COMPONENTS_OS := $(EE_NIOS2_DIR)/components/altera_hal \
		$(EE_NIOS2_DIR)/components/evidence_ee 

ifeq ($(call iseeopt, __NIOS2_SPIN_AVALON_MUTEX__), yes)
COMPONENTS += $(EE_SOPC_DIR)/altera_avalon_mutex
endif

ifeq ($(call iseeopt, __NIOS2_SPIN_AVALON_MUTEX_DIRECT__), yes)
COMPONENTS += $(EE_SOPC_DIR)/altera_avalon_mutex
endif

ifeq ($(call iseeopt, __NIOS2_IPIC_PIO__), yes)
COMPONENTS += $(EE_SOPC_DIR)/altera_avalon_pio
endif

# Include HAL library makefile
LIB_MAKEFILE := $(EE_NIOS2_DIR)/components/evidence_ee/build/lib.mk
include $(LIB_MAKEFILE)

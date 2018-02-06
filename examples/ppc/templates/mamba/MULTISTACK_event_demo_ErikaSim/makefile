# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2010  Evidence Srl
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

## Makefile for Erika PPC projects
## Author: 2010,  Bernardo  Dal Seno


# Destination directory
export OUTPUT_DIR = output

# Check the environment and use reasonable defaults
ifndef ERIKA_FILES
export ERIKA_FILES := $(abspath ../../../../..)
else
export ERIKA_FILES := $(subst \,/,$(ERIKA_FILES))
endif

# Check the environment and use reasonable defaults
ifndef RTDRUID_ECLIPSE_HOME
RTDRUID_ECLIPSE_HOME = C:/Evidence/Evidence/eclipse
RTDRUID_SCRIPT_DIR =
else
RTDRUID_ECLIPSE_HOME := $(subst \,/,$(RTDRUID_ECLIPSE_HOME))
endif

ifndef RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR=$(RTDRUID_ECLIPSE_HOME)/evidence
else
RTDRUID_SCRIPT_DIR := $(subst \,/,$(RTDRUID_SCRIPT_DIR))
endif

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, makefile eecfg.h eecfg.c)

.PHONY: all clean

all: $(RTDRUID_OUTPUT)
	$(MAKE) -C $(OUTPUT_DIR) all

clean:
	@echo cleaning...
	rm -f -r $(OUTPUT_DIR)


ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

# Run RT-Druid
$(RTDRUID_OUTPUT): conf.oil
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ;\
	export ECLIPSE_HOME ;\
	exec sh $(RTDRUID_SCRIPT_DIR)/start_ant.sh -buildfile $(RTDRUID_SCRIPT_DIR)/build.xml -Din_conf_oil=$< -Dconf_output_dir=$(OUTPUT_DIR) compile

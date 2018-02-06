# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2011  Evidence Srl
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

## Author: 2012, Errico Guidieri


# Destination directory
export OUTPUT_DIR = Output

# Check the environment and use reasonable defaults
ifndef RTDRUID_ECLIPSE_HOME
RTDRUID_ECLIPSE_HOME := C:/Evidence/eclipse
else
RTDRUID_ECLIPSE_HOME := $(subst \,/,$(RTDRUID_ECLIPSE_HOME))
endif

ifndef RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR := $(RTDRUID_ECLIPSE_HOME)/evidence
endif

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, makefile common.mk master/common.c\
master/eecfg.h master/eecfg.c master/makefile\
slave1/eecfg.h slave1/eecfg.c slave1/makefile)

.PHONY: all clean config

all: $(RTDRUID_OUTPUT)
	$(MAKE) -C $(OUTPUT_DIR)

clean:
	@echo cleaning...
	rm -f -r $(OUTPUT_DIR)

config: $(RTDRUID_OUTPUT)

# Run RT-Druid
ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

$(RTDRUID_OUTPUT): conf.oil
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)";\
	export ECLIPSE_HOME ;\
	$(RTDRUID_SCRIPT_DIR)/generate_code.sh $(RTDRUID_ECLIPSE_HOME)\
		conf.oil $(OUTPUT_DIR)

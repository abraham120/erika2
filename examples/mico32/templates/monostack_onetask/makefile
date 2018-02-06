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

## Makefile for Erika Mico32 projects
## Author: 2010,  Bernardo  Dal Seno


# Destination directory
export OUTPUT_DIR = output

# Check the environment and use reasonable defaults
ifndef RTDRUID_ECLIPSE_HOME
RTDRUID_ECLIPSE_HOME = C:/Evidence/eclipse
RTDRUID_SCRIPT_DIR =
endif
ifndef RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR=$(RTDRUID_ECLIPSE_HOME)/evidence
endif
ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif


RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, \
 makefile lattice.mk platform.mk eecfg.h eecfg.c crt0ram.S)

.PHONY: all clean

all: $(RTDRUID_OUTPUT)
	@$(MAKE) --no-print-directory -f $(OUTPUT_DIR)/makefile all
# Don't confuse people by printing the directory, as the current directory
# is not changed

clean:
	@echo cleaning...
	rm -f -r $(OUTPUT_DIR)

# If any target different from `all' or `clean' si given, try to invoke the
# generated makefile. `force' is used to force the invocation of the child
# makefile
%: $(RTDRUID_OUTPUT) force
	@$(MAKE) --no-print-directory -f $(OUTPUT_DIR)/makefile $@
# Avoid triggering the catch-all rule
.PHONY: force
force: ;
conf.oil: ;
makefile: ;

# Run RT-Druid
$(RTDRUID_OUTPUT): conf.oil
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ;\
	export ECLIPSE_HOME ;\
	exec sh $(RTDRUID_SCRIPT_DIR)/start_ant.sh -buildfile $(RTDRUID_SCRIPT_DIR)/build.xml -Din_conf_oil=$< -Dconf_output_dir=$(OUTPUT_DIR) compile

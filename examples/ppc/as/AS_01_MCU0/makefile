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

# Added to support ERIKA_FILES environmental variable
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := ${ERIKA_FILES}
endif

# AS Configuration files
CONFIGURATION_FILES = Compiler_Cfg.h Mcu_Cfg.h Mcu_Cfg.c

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, eecfg.c eecfg.h makefile)

.PHONY: all all_ext autotest autotest_ext clean

all: $(RTDRUID_OUTPUT)
	$(MAKE) -C $(OUTPUT_DIR) all

all_ext: $(RTDRUID_OUTPUT)
	EEOPT=__OO_EXTENDED_STATUS__
	$(MAKE) EXT=1 -C $(OUTPUT_DIR) all

autotest: all
	cp t32_autotest.cmm $(OUTPUT_DIR)/t32.cmm

autotest_ext: all_ext
	cp t32_autotest.cmm $(OUTPUT_DIR)/t32.cmm

clean:
	@echo cleaning...
	rm -f -r $(OUTPUT_DIR) $(CONFIGURATION_FILES) *errors*

ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

# Run RT-Druid
$(RTDRUID_OUTPUT): conf.oil $(CONFIGURATION_FILES)
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ;\
	export ECLIPSE_HOME ;\
	bash $(RTDRUID_SCRIPT_DIR)/generate_code.sh $(RTDRUID_ECLIPSE_HOME) \
		conf.oil $(OUTPUT_DIR)

$(CONFIGURATION_FILES):
	@echo "Coping configuration file: $@ from AS Contrib"
	@cp $(EEBASE)/contrib/as/arch/mpc56xx/codewarrior/config/$@ .


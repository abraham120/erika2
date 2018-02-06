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

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, eecfg.c eecfg.h makefile)

.PHONY: all all_ext autotest autotest_ext clean deep_clean_lin lin

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
	rm -f -r $(OUTPUT_DIR) *errors*

ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

# Run RT-Druid
$(RTDRUID_OUTPUT): conf.oil
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ;\
	export ECLIPSE_HOME ;\
	bash $(RTDRUID_SCRIPT_DIR)/generate_code.sh $(RTDRUID_ECLIPSE_HOME) \
		conf.oil $(OUTPUT_DIR)

# LIN compliance level; to be overridden on the command line
LIN_LEVEL ?= 4C

# LIN executable; override it if your settings are different
LIN_EXE ?= /opt/case/lin/7.10/lin

# Configuration file for LIN
LIN_CONF = erika_ppc.lnt

lin: real_errors

# Remove all LIN configuration files
deep_clean_lin: clean
	rm -rf $(HOME)/.files.lin $(HOME)/lin_*.txt $(HOME)/.rules.lnt \
	 $(HOME)/.lin.cnfg $(HOME)/.lin.lock


# Targets are listed
# Generate compilation command list
cleanup_cmds = grep -v '[-]o [^ ]\+\.src' | sed 's/printf[^;]\+;//'
$(OUTPUT_DIR)/make.list: $(RTDRUID_OUTPUT)
	@echo MAKE $(dir $@)
	@(cd $(OUTPUT_DIR)$* && make -n) | $(cleanup_cmds) > $@ \
	  || (rm -f $@; false)

# Run LIN
$(OUTPUT_DIR)/out_lin.txt: $(OUTPUT_DIR)/make.list $(LIN_CONF)
	@echo "LIN $(dir $@)"
	@rm -f $@ && cd $(OUTPUT_DIR) && \
	$(LIN_EXE) -p . -n -m make.list -L $(LIN_LEVEL) -c dcc \
	 -v 5.5.1.0 -l $(abspath $(LIN_CONF)) 2>lin.stderr >lin.stdout ; \
	test -e out_lin.txt || tail -1 lin.stdout \
	 | grep -F '0 error(s) found.' >/dev/null && touch out_lin.txt

# Compact LIN output
# The awk script may cause problem to the output format in case of long ee path
errors: $(OUTPUT_DIR)/out_lin.txt
	@echo Merging errors...
	@gawk 'BEGIN {err = 0; msg = ""} '\
	'{if ($$0 ~ /^[-a-zA-Z0-9_./]+\.([ch]|lnt)/ '\
	'|| $$0 ~ /^Error [0-9]+: /) err = 1; '\
	'if (err == 1) { if (! ($$0 ~ /^(--- .+| *_ *)$$/)) { '\
	'    gsub("^[[:space:]]+", "", $$0); msg = msg $$0 " "; '\
	'    if ($$0 ~ /\]$$/) { err = 2; } '\
	'  } else { err = 2; } }'\
	'if (err == 2) { err = 0; print msg; msg = "" } '\
	'}' $^ | sort -u > $*.tmp
	@sed 's#$(EEBASE)/##g' $*.tmp | sed '1d' > $@
	@rm -f $*.tmp
# Even more compact output: Remove EEBASE from paths and the first row that is
# the last of the out_lin.txt

# Remove deviation
real_errors: errors
	sh ./filter_misra.sh $< $@

# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
#
# Copyright (C) 2002-2011  Evidence Srl
#
# This file is part of ERIKA Enterprise.  ERIKA Enterprise is free software;
# you can redistribute it and/or modify it under the terms of the
# GPLv2 + Linking Exception license (contained in the file `ee/LICENSE').
#
# ERIKA Enterprise is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the license for more details.
#
# ###*E*### */

## Makefile for checking MISRA compliance of Erika PPC kernels
## Author: 2011,  Bernardo  Dal Seno


# LIN compliance level; to be overridden on the command line
LIN_LEVEL ?= 4C

# LIN executable; override it if your settings are different
LIN_EXE ?= /opt/case/lin/7.10/lin

# Configuration file for LIN
LIN_CONF = erika_ppc.lnt

# Destination directory (base name)
OUT_DIR_BASE = output_

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

# Added to support ERIKA_FILES environmental variable
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := ${ERIKA_FILES}
endif

# Only makefile is used in rule chaining
RTDRUID_OUTPUT_FILES = makefile

# All configurations
SP_CONFIGS = bcc1 bcc2 ecc1 ecc2 fp prot
MP_CONFIGS = mp_bcc1 mp_fp mp_ecc2

# Output files of LIN.  This list is used to trigger the chain of pattern-rules
LIN_FILES = $(addsuffix /out_lin.txt,$(addprefix $(OUT_DIR_BASE),$(SP_CONFIGS)))
LIN_FILES +=$(addsuffix /master/out_lin.txt,$(addprefix $(OUT_DIR_BASE),$(MP_CONFIGS)))
LIN_FILES +=$(addsuffix /slave/out_lin.txt,$(addprefix $(OUT_DIR_BASE),$(MP_CONFIGS)))


.PHONY: all clean clean_lin deep_clean_lin
# Do not delete intermediate files (e.g., files created by RT-Druid)
.SECONDARY:

all: real_errors.report

# Remove RT-Druid output and reports
clean:
	rm -f -r $(OUT_DIR_BASE)* errors errors.report real_errors.report

# Remove all reports
clean_lin:
	rm -f $(LIN_FILES) errors errors.report real_errors.report

# Remove all LIN configuration files
deep_clean_lin: clean_lin
	rm -rf $(HOME)/.files.lin $(HOME)/lin_*.txt $(HOME)/.rules.lnt \
	 $(HOME)/.lin.cnfg $(HOME)/.lin.lock

# Run RT-Druid
$(OUT_DIR_BASE)%/makefile: conf_%.oil
	@echo "Running RT-Druid $*..."
	@bash "$(RTDRUID_ECLIPSE_HOME)"/evidence/generate_code.sh \
	 "$(RTDRUID_ECLIPSE_HOME)" $< $(OUT_DIR_BASE)$*


# Generate compilation command list
cleanup_cmds = grep -v '[-]o [^ ]\+\.src' | sed 's/printf[^;]\+;//'
mp_make = `make $1-all -n | grep '^make '| tail -1` -n
%/shared_sym.ld:
	touch $@
$(OUT_DIR_BASE)%/master/make.list: $(OUT_DIR_BASE)%/makefile $(OUT_DIR_BASE)%/shared_sym.ld
	@echo MAKE $(dir $@)
	@(cd $(OUT_DIR_BASE)$* && $(call mp_make,CPU_MASTER)) \
	  | $(cleanup_cmds) > $@ || (rm -f $@; false)
$(OUT_DIR_BASE)%/slave/make.list: $(OUT_DIR_BASE)%/makefile $(OUT_DIR_BASE)%/shared_sym.ld
	@echo MAKE $(dir $@)
	@(cd $(OUT_DIR_BASE)$* && $(call mp_make,CPU1)) \
	  | $(cleanup_cmds) > $@ || (rm -f $@; false)

# Targets are listed, so this rule is not triggered for MP configurations
$(addsuffix /make.list,$(addprefix $(OUT_DIR_BASE),$(SP_CONFIGS))): \
  $(OUT_DIR_BASE)%/make.list: $(OUT_DIR_BASE)%/makefile
	@echo MAKE $(dir $@)
	@(cd $(OUT_DIR_BASE)$* && make -n) | $(cleanup_cmds) > $@ \
	  || (rm -f $@; false)


# Run LIN
$(OUT_DIR_BASE)%/out_lin.txt: $(OUT_DIR_BASE)%/make.list $(LIN_CONF)
	@echo "LIN $(dir $@)"
	@rm -f $@ && cd $(OUT_DIR_BASE)$* && \
	$(LIN_EXE) -p . -n -m make.list -L $(LIN_LEVEL) -c dcc \
	 -v 5.5.1.0 -l $(abspath $(LIN_CONF)) 2>lin.stderr >lin.stdout ; \
	test -e out_lin.txt || tail -1 lin.stdout \
	 | grep -F '0 error(s) found.' >/dev/null && touch out_lin.txt

# Compact LIN output
# The awk script may cause problem to the output format in case of long ee path
errors: $(LIN_FILES)
	@echo Merging errors...
	@gawk 'BEGIN {err = 0; msg = ""} '\
	'{if ($$0 ~ /^[-a-zA-Z0-9_./]+\.([ch]|lnt)/ '\
	'|| $$0 ~ /^Error [0-9]+: /) err = 1; '\
	'if (err == 1) { if (! ($$0 ~ /^(--- .+| *_ *)$$/)) { '\
	'    gsub("^[[:space:]]+", "", $$0); msg = msg $$0 " "; '\
	'    if ($$0 ~ /\]$$/) { err = 2; } '\
	'  } else { err = 2; } }'\
	'if (err == 2) { err = 0; print msg; msg = "" } '\
	'}' $^ | sort -u > $@

# Even more compact output: Remove EEBASE from paths
errors.report: errors
	 sed 's#$(EEBASE)/##g' $< > $@

# Remove deviations
real_errors.report: errors.report
	sh ./filter_misra.sh $< $@

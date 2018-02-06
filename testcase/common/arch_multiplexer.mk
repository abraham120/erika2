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

# Author: 2004 Paolo Gai

# ARCH multiplexer

include common.mk
include ../$(EXPERIMENT)/conf.in

# PURPOSE OF THIS MAKEFILE
# This makefile is called by the main makefile, once for each
# directory that contains a conf.in file.
#
# This makefile verifies if the experiment is compatible with the
# architecture(s) we are testing. If yes, it calls recursively the
# conf_multiplexer.in makefile, once for each architecture that have
# to be tested.

# variables defined from now on:
# from the main makefile:
# - ARCH       the architecture to test
# - EXPERIMENT the directory to test
# from conf.in
# - conf       the configurations of the EXPERIMENT that have to be tested
# - worksfor   the architectures for which the EXPERIMENT has been tested

#Note: the architecture must be an exact match!
archs := $(filter $(ARCH),$(worksfor))

MUX = $(EEBASE)/testcase/common/confparser/confparser_mux

.PHONY: all conf help clean

#
# All
#

all_archs := $(addprefix all_, $(archs))
all: $(all_archs)
	@echo dummy > /dev/null

define all_template
.PHONY: all_$(1)
all_$(1): $$(MUX)
	+@$$(MAKE) $$(NOPRINTDIR) -f conf_multiplexer.mk thearch=$(1) all

endef
$(foreach a,$(archs),$(eval $(call all_template,$(a))))


#
# rtdruid
#

rtdruid_archs := $(addprefix rtdruid_, $(archs))
rtdruid: $(rtdruid_archs)
	@echo dummy > /dev/null

define rtdruid_template
.PHONY: rtdruid_$(1)
rtdruid_$(1): $$(MUX)
	+@$$(MAKE) $$(NOPRINTDIR) -f conf_multiplexer.mk thearch=$(1) rtdruid

endef
$(foreach a,$(archs),$(eval $(call rtdruid_template,$(a))))



#
# dist
#

dist_archs := $(addprefix dist_, $(archs))
dist: $(dist_archs)
	@echo dummy > /dev/null

define dist_template
.PHONY: dist_$(1)
dist_$(1): $$(MUX)
	+@$$(MAKE) $$(NOPRINTDIR) -f conf_multiplexer.mk thearch=$(1) dist

endef
$(foreach a,$(archs),$(eval $(call dist_template,$(a))))


#
# conf
#

conf_archs := $(addprefix conf_, $(archs))
conf: $(conf_archs)
	@echo dummy > /dev/null

define conf_template
.PHONY: conf_$(1)
conf_$(1): $$(MUX)
	+@$$(MAKE) $$(NOPRINTDIR) -f conf_multiplexer.mk thearch=$(1) conf

endef
$(foreach a,$(archs),$(eval $(call conf_template,$(a))))






$(MUX):
	lockfile $(EEBASE)/testcase/common/confparser/confparser_make.lock
	+@$(MAKE) -C $(EEBASE)/testcase/common/confparser
	rm -f $(EEBASE)/testcase/common/confparser/confparser_make.lock

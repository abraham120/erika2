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

## Author: 2003 Paolo Gai
## CVS: $Id: rules_axiom_mpc566evb.mk,v 1.2 2006/12/21 15:38:52 pj Exp $


include $(EEBASE)/pkg/cfg/dir.mk
include $(PKGBASE)/cfg/verbose.mk
include $(PKGBASE)/cfg/compiler.mk

# OPT_LINK represents the options for armlink invocation
ifneq ($(findstring __DEFAULT_LD_SCRIPT__,$(EEOPT)) , __DEFAULT_LD_SCRIPT__)
OPT_LINK += --script=out/loc_gnu.ld -u__start
LINKDEP = out/loc_gnu.ld out/loc_mpc566evb.ld
endif

# OPT_LIBS is used to link additional libraries (e.g., for C++ support)
OPT_LIBS += -lee -L $(APPBASE)/out

include $(wildcard $(PKGBASE)/cfg/cfg.mk)

# all must be the first rule... in general, syscalls.mk adds new rules but it must be just here.
all::
include $(PKGBASE)/cfg/syscalls.mk



#
# --------------------------------------------------------------------------
#

##
## Common Rules
##

# Boot code containing _start should stay outside of the library in
# case of normal compilation
ifeq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR)
LIBSRCS += $(EE_BOOT_SRCS)
else
SRCS += $(EE_BOOT_SRCS)
endif

SRCS += $(APP_SRCS)
OBJS= $(addprefix out/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS))))

LIBSRCS += $(EE_SRCS)
LIBOBJS = $(addprefix out/, $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS))))


vpath %.elf out $(shell mkdir -p out)
vpath %.o out
vpath %.to out
vpath %.cd out
vpath %.Sd out
vpath %.td out
vpath %.c $(EE_VPATH) $(APPBASE)
vpath %.S $(EE_VPATH) $(APPBASE)
vpath %.src out

out/%.o: %.S $(EE_SYSCALLS_PREREQUISITES)
	$(VERBOSE_PRINTPRE)
	$(EE_CC) $(ALLINCPATH) $(DEFS_ASM) -E $< > out/$(notdir $(patsubst %.o,%.src,$@))
	$(VERBOSE_PRINTASM)
	$(EE_ASM) $(OPT_ASM) out/$(notdir $(patsubst %.o,%.src,$@)) -o out/$(notdir $@)

out/%.o: %.c $(EE_SYSCALLS_PREREQUISITES)
	$(VERBOSE_PRINTCC)
	$(EE_CC) $(OPT_CC) $(DEFS_CC) $< -o out/$(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(VERBOSE_PRINTASM)
	$(EE_CC) $(OPT_CC) $(DEFS_CC) $< -S -o out/$(notdir $(patsubst %.o,%.S,$@))
endif


##
## Main rules: all clean
##

.PHONY: all clean

all:: mpc566evb.elf t32

mpc566evb.elf: $(OBJS) out/libee.a $(LINKDEP)
	@echo LD
	$(EE_LINK) $(OPT_LINK) \
                     -o out/$@ $(OBJS) \
                     --start-group $(OPT_LIBS) --end-group \
                     -M > out/mpc566evb.map

clean::
	@echo CLEAN
	@-rm -rf out


##
## Locator files
##

out/loc_gnu.ld: $(PKGBASE)/board/axiom_mpc566evb/cfg/loc_gnu.ld
	@echo LOC
	@cp $(PKGBASE)/board/axiom_mpc566evb/cfg/loc_gnu.ld out

out/loc_mpc566evb.ld: cfg_evb.h
	@echo AWK
	@awk '/#define/{ print $$2 " = " $$3 ";" }' < cfg_evb.h >out/loc_mpc566evb.ld



##
## EE Library
##

out/libee.a: $(LIBOBJS)
	@echo AR  out/libee.a
	$(EE_AR) rs out/libee.a $(LIBOBJS)


##
## Automatic Generation of dependencies
##

# deps contains all the dependencies
out/deps: $(addprefix out/, $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd,$(SRCS) $(LIBSRCS))))
	@echo GEN out/deps
	@cat $(addprefix out/, \
		$(patsubst %.S,%.Sd,$(patsubst %.c,%.cd,$(SRCS) $(LIBSRCS)))) > out/deps

# generate dependencies for ARM .c files and add "file.cd" to the target
out/%.cd: %.c $(EE_SYSCALLS_PREREQUISITES)
	$(VERBOSE_PRINTDEP)
	$(EE_CC) $(OPT_CC) $(DEFS_CC) -M $< | sed "s/\($*\)\.o[ :]*/out\/\1\.o out\/$(notdir $@): /g" > $@
	@test -s $@ || rm -f $@

# generate dependencies for .S files and add "file.Sd" to the target
out/%.Sd: %.S $(EE_SYSCALLS_PREREQUISITES)
	$(VERBOSE_PRINTDEP)
	$(EE_CC) $(ALLINCPATH) $(DEFS_ASM) -M $< | sed "s/\($*\)\.o[ :]*/out\/\1\.src out\/$(notdir $@): /g" > $@
	@test -s $@ || rm -f $@


#
# --------------------------------------------------------------------------
#

# Lauterbach t32 scripts

T32_SCRIPTS = $(shell cd $(PKGBASE)/board/axiom_mpc566evb/debug/lauterbach; find . ! -type d | grep -v CVS)

T32_DIRS = $(shell cd $(PKGBASE)/board/axiom_mpc566evb/debug/lauterbach; find .  -type d | grep -v CVS)

# "touch" solves some dependency issues with make
define T32_template
out/$(1): $(PKGBASE)/board/axiom_mpc566evb/debug/lauterbach/$(1)
	@echo CP $$@
	@mkdir -p $$(addprefix out/,$$(T32_DIRS))
	@cp -a $$< $$@
	touch $$@
endef

$(foreach file,$(T32_SCRIPTS),$(eval $(call T32_template,$(file))))

t32: $(addprefix out/, $(T32_SCRIPTS))


ifndef NODEPS
ifneq ($(MAKECMDGOALS),clean)
-include out/deps
endif
endif

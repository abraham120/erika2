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

#
# Freescale PowerPc e200zX testcases
#

# The list of supported targets
ifneq ($(MCU_TARGET),$(filter $(MCU_TARGET),k2 cobra55 mamba))
$(error BAD TARGET!!! This testsuite configured for PowerPC supports these target list: cobra55, k2 or mamba. For instance: make ARCH=e200zx_diab_5_8_vle MCU_TARGET=cobra55)
else

# K2-specific filters
ifeq ($(MCU_TARGET), k2)
ifneq ($(ARCH), $(or $(filter $(ARCH), e200zx_diab_5_8_vle), $(filter $(ARCH), e200zx_hightec_4_6_4_0_vle)))
$(error BAD ARCH!!! K2 can can be tested only with ARCH=e200zx_diab_5_8_vle!!!)
endif
endif

endif

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/e200zx_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/e200zx_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/e200zx_rtdruid_global_build.xml; \
		cd tmp; java -jar $(LAUNCHER_JAR) -application org.eclipse.ant.core.antRunner >rtdruid_e200zx.log 2>&1; \
	fi );

#
# configurations
#

# e200zx_diab_5_5_1_fle
TESTLIST 		                += e200zx_diab_5_5_1_fle
OUTDIR_COMMANDS_e200zx_diab_5_5_1_fle 	= $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_diab_5_5_1_fle            	= $(call CONF_e200zx_source_template,diab_5_5_1,fle)
GLOBAL_CONF 		                +=
DIST_e200zx_diab_5_5_1_fle            	=
RTDRUID_e200zx_diab_5_5_1_fle		= $(RTDRUID_e200zx_source)
CLEAN_e200zx_diab_5_5_1_fle           	=
COMPILE_e200zx_diab_5_5_1_fle         	= $(COMPILE_e200zx_source)
DEBUG_e200zx_diab_5_5_1_fle           	= $(call DEBUG_e200zx_source_template,fle)

# e200zx_diab_5_5_1_vle
TESTLIST 		                += e200zx_diab_5_5_1_vle
OUTDIR_COMMANDS_e200zx_diab_5_5_1_vle   = $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_diab_5_5_1_vle              = $(call CONF_e200zx_source_template,diab_5_5_1,vle)
GLOBAL_CONF 		                +=
DIST_e200zx_diab_5_5_1_vle              =
RTDRUID_e200zx_diab_5_5_1_vle           = $(RTDRUID_e200zx_source)
CLEAN_e200zx_diab_5_5_1_vle             =
COMPILE_e200zx_diab_5_5_1_vle           = $(COMPILE_e200zx_source)
DEBUG_e200zx_diab_5_5_1_vle             = $(call DEBUG_e200zx_source_template,vle)

# e200zx_codewarrior_10_0_2_vle
TESTLIST 		                        += e200zx_codewarrior_10_0_2_vle
OUTDIR_COMMANDS_e200zx_codewarrior_10_0_2_vle   = $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_codewarrior_10_0_2_vle              = $(call CONF_e200zx_source_template,codewarrior_10_0_2,vle)
GLOBAL_CONF 		                        +=
DIST_e200zx_codewarrior_10_0_2_vle              =
RTDRUID_e200zx_codewarrior_10_0_2_vle           = $(RTDRUID_e200zx_source)
CLEAN_e200zx_codewarrior_10_0_2_vle             =
COMPILE_e200zx_codewarrior_10_0_2_vle           = $(COMPILE_e200zx_source)
DEBUG_e200zx_codewarrior_10_0_2_vle             = $(call DEBUG_e200zx_source_template,vle)

# e200zx_codewarrior_10_0_2_fle
TESTLIST 		                        += e200zx_codewarrior_10_0_2_fle
OUTDIR_COMMANDS_e200zx_codewarrior_10_0_2_fle   = $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_codewarrior_10_0_2_fle              = $(call CONF_e200zx_source_template,codewarrior_10_0_2,fle)
GLOBAL_CONF 		                        +=
DIST_e200zx_codewarrior_10_0_2_fle              =
RTDRUID_e200zx_codewarrior_10_0_2_fle           = $(RTDRUID_e200zx_source)
CLEAN_e200zx_codewarrior_10_0_2_fle             =
COMPILE_e200zx_codewarrior_10_0_2_fle           = $(COMPILE_e200zx_source)
DEBUG_e200zx_codewarrior_10_0_2_fle             = $(call DEBUG_e200zx_source_template,fle)

# e200zx_diab_5_8_vle
TESTLIST 		                += e200zx_diab_5_8_vle
OUTDIR_COMMANDS_e200zx_diab_5_8_vle     = $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_diab_5_8_vle                = $(call CONF_e200zx_source_template,diab_5_8,vle)
GLOBAL_CONF 		                +=
DIST_e200zx_diab_5_8_vle                =
RTDRUID_e200zx_diab_5_8_vle             = $(RTDRUID_e200zx_source)
CLEAN_e200zx_diab_5_8_vle               =
COMPILE_e200zx_diab_5_8_vle             = $(COMPILE_e200zx_source)
DEBUG_e200zx_diab_5_8_vle               = $(call DEBUG_e200zx_source_template,vle)

# e200zx_diab_5_8_fle
TESTLIST 		                += e200zx_diab_5_8_fle
OUTDIR_COMMANDS_e200zx_diab_5_8_fle     = $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_diab_5_8_fle                = $(call CONF_e200zx_source_template,diab_5_8,fle)
GLOBAL_CONF 		                +=
DIST_e200zx_diab_5_8_fle                =
RTDRUID_e200zx_diab_5_8_fle             = $(RTDRUID_e200zx_source)
CLEAN_e200zx_diab_5_8_fle               =
COMPILE_e200zx_diab_5_8_fle             = $(COMPILE_e200zx_source)
DEBUG_e200zx_diab_5_8_fle               = $(call DEBUG_e200zx_source_template,fle)

# e200zx_hightec_4_6_4_0_vle
TESTLIST					+= e200zx_hightec_4_6_4_0_vle
OUTDIR_COMMANDS_e200zx_hightec_4_6_4_0_vle	= $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_hightec_4_6_4_0_vle                = $(call CONF_e200zx_source_template,hightec_4_6_4_0,vle)
GLOBAL_CONF					+=
DIST_e200zx_hightec_4_6_4_0_vle                =
RTDRUID_e200zx_hightec_4_6_4_0_vle             = $(RTDRUID_e200zx_source)
CLEAN_e200zx_hightec_4_6_4_0_vle               =
COMPILE_e200zx_hightec_4_6_4_0_vle             = $(COMPILE_e200zx_source)
DEBUG_e200zx_hightec_4_6_4_0_vle               = $(call DEBUG_e200zx_source_template,vle)

# e200zx_gnu_fle
TESTLIST				+= e200zx_gnu_fle
OUTDIR_COMMANDS_e200zx_gnu_fle		= $(OUTDIR_COMMANDS_e200zx_source)
CONF_e200zx_gnu_fle			= $(call CONF_e200zx_source_template,gnu,fle)
GLOBAL_CONF				+=
DIST_e200zx_gnu_fle			=
RTDRUID_e200zx_gnu_fle			= $(RTDRUID_e200zx_source)
CLEAN_e200zx_gnu_fle			=
COMPILE_e200zx_gnu_fle			= $(COMPILE_e200zx_source)
DEBUG_e200zx_gnu_fle			= $(call DEBUG_e200zx_source_template,fle)

# -------------------------------------------------------------------

EE_TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(EE_TMPDIR)/e200zx_manual.lock
RTDRUID_GENERATE_LOCK = $(EE_TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(EE_TMPDIR)/dist.lock

# -------------------------------------------------------------------

OUTDIR_COMMANDS_e200zx_source = \
	( cd $@; cp -sf ../*.* .; \
	);

# -------------------------------------------------------------------
# # These are the commands used by e200zx_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
# The template receives two arguments (in any order):
# - instruction set: can be either vle or fle
# - compiler: can be either codewarrior or diab
CONF_e200zx_source_template = \
	echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -De200zx -D$(MCU_TARGET) $(e200zx_compiler_def) $(e200zx_vle_def) -o - >$(OUTDIR_PREFIX)$*/ee.oil;
e200zx_compiler_def=$(if $(filter codewarrior_10_0_2,$1 $2),-DUSE_CODEWARRIOR,$(if $(filter diab_5_5_1,$1 $2),-DUSE_DIAB,$(if $(filter diab_5_8,$1 $2),-DUSE_DIAB_5_8,$(if $(filter hightec_4_6_4_0,$1 $2),-DUSE_HIGHTEC,$(if $(filter gnu,$1 $2),-DUSE_GNU,$(error Neither "codewarrior" nor "diab" nor "hightec" nor "GNU" found in arguments of CONF_e200zx_source_template))))))
e200zx_vle_def=$(if $(filter vle,$1 $2),-DUSE_VLE,$(if $(filter fle,$1 $2),-DUSE_FLE,$(error Neither "fle" nor "vle" found in arguments of CONF_e200zx_source_template)))

# Generate the rt-druid files...
RTDRUID_e200zx_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(call native_path,$(OUTDIR_PREFIX)$*/ee.oil)\" outputdir=\"$(call native_path,$(OUTDIR_PREFIX)$*/Debug)\" /\> >> $(EE_TMPDIR)/e200zx_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!!!

COMPILE_e200zx_source = \
	+@unset EEBASE; \
	if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug >$(OUTDIR_PREFIX)$*/compile.log 2>&1; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/errors.log; fi


# The template receives one argument
# - instruction set: can be either vle or fle
DEBUG_e200zx_source_template = \
	sed -e 's:\#USE_VLE\#:$(e200zx_vle_debug):g' < e200zx/$(MCU_TARGET)/t32.cmm > $(OUTDIR_PREFIX)$*/t32.cmm; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "&count=&count+1" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo chdir $(OUTDIR_PREFIX)$* >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo "write \#1 \"$(OUTDIR_PREFIX)$*\"" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print '"Test no. "' '%Decimal' '&count' '" ("' '&failed' \
		'" errors so far)"' >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print \"$(OUTDIR_PREFIX)$*\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo do t32.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
		cp -u e200zx/$(MCU_TARGET)/t32_quit.cmm $(EE_TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK);
e200zx_vle_debug = $(if $(filter vle,$1),1,$(if $(filter fle,$1),0,$(error Neither "fle" nor "vle" found in arguments of DEBUG_e200zx_source_template)))

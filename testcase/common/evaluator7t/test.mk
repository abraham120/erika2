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
# Evaluator7T testcases
#

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/e7t_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/e7t_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/e7t_rtdruid_global_build.xml; \
		cd tmp; java -jar $(LAUNCHER_JAR) -application org.eclipse.ant.core.antRunner >rtdruid_e7t.log 2>&1; \
	fi );




#
# configurations
#


# e7t
TESTLIST += e7t
CONF_e7t             = $(CONF_e7t_source)
DIST_e7t            =
RTDRUID_e7t            = $(RTDRUID_e7t_source)
CLEAN_e7t           =
COMPILE_e7t         = $(COMPILE_e7t_source)
DEBUG_e7t           = $(DEBUG_e7t)

# e7t_dist_bin_full
#TESTLIST += e7t_dist_bin_full
#OUTDIR_COMMANDS_e7t_dist_bin_full = $(OUTDIR_COMMANDS_e7t)
#CONF_e7t_dist_bin_full             = $(CONF_e7t_binfull)
#GLOBAL_CONF += $(GLOBAL_CONF_e7t_binfull)
#DIST_e7t_dist_bin_full            =
#RTDRUID_e7t_dist_bin_full            = $(RTDRUID_e7t_binfull)
#CLEAN_e7t_dist_bin_full           =
#COMPILE_e7t_dist_bin_full         = $(COMPILE_e7t_source)
#DEBUG_e7t_dist_bin_full           = $(DEBUG_e7t)

# -------------------------------------------------------------------


EE_TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(EE_TMPDIR)/e7t_manual.lock
RTDRUID_GENERATE_LOCK = $(EE_TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(EE_TMPDIR)/dist.lock


# -------------------------------------------------------------------

OUTDIR_COMMANDS_e7t = cd $@; cp -sf ../*.* .


DEBUG_e7t = \
	@cp evaluator7t/t32.cmm $(OUTDIR_PREFIX)$*; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo chdir $(OUTDIR_PREFIX)$* >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print \"$(OUTDIR_PREFIX)$*\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo do t32.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
		cp -u evaluator7t/t32_quit.cmm $(EE_TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK); \

# -------------------------------------------------------------------


# # These are the commands used by e7t_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_e7t_source = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil;

RTDRUID_e7t_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(call native_path,$(OUTDIR_PREFIX)$*/ee.oil)\" outputdir=\"$(call native_path,$(OUTDIR_PREFIX)$*/Debug)\" /\> >> $(EE_TMPDIR)/e7t_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!

COMPILE_e7t_source = \
	+@unset EEBASE; \
	if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug >$(OUTDIR_PREFIX)$*/compile.log 2>&1; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/errors.log; fi


# -------------------------------------------------------------------

# These are the commands used by e7t_dist_bin_full

#CONF_e7t_binfull = \
#	@echo CONF $(OUTDIR_PREFIX)$*; \
#	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
#	echo \<rtdruid.Oil.DistributionBuilder inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputFile=\"`cygpath -m $(EE_TMPDIR)/bindistrfull_partial.mk`\" DistributionName=\"$(subst /,,$(EXPERIMENT))_$*\" DistributionType=\"full\"/\> >> $(EE_TMPDIR)/e7t_ant_partial.xml;


#GLOBAL_CONF_e7t_binfull = \
#	( if test e7t_dist_bin_full = $(ARCH); then \
#		cat common/rtdruid_common/script_prologue.xml tmp/e7t_ant_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
#		cp tmp/build.xml tmp/e7t_ant_global_build.xml; \
#		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner; cd ..; \
#		echo "ALL_DISTRIBUTIONS += RTDRUID" > tmp/e7t_bindistrfull.mk; \
#		cat tmp/bindistrfull_partial.mk >> tmp/e7t_bindistrfull.mk; \
#		false; \
#		make -C ${EEBASE}/dist/binary DISTFILE=${EEBASE}/testcase/tmp/e7t_bindistrfull.mk DIST=RTDRUID E7T_MOVE=Y; \
#	fi );

#RTDRUID_e7t_binfull = \
#	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
#	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`\" Signatures_file=\"`cygpath -m $(EE_E7T_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\" /\> >> $(EE_TMPDIR)/e7t_rtdruid_partial.xml;
#binDistrSignatures_file=\"`cygpath -m $(EE_E7T_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\"

# take also a look to GLOBAL_RTDRUID at the top of the file!




# -------------------------------------------------------------------

# # These are the commands used by e7t_dist_bin_lim

# CONF_e7t_binlim = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrlimited_file=\"bindistrlimited.mk\" /\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;







# #
# # Evaluator7t testcases
# #

# # e7t_rtdruid
# TESTLIST += e7t_rtdruid
# OUTDIR_COMMANDS_e7t_rtdruid = OUTDIR_COMMANDS_e7t
# CONF_e7t_rtdruid             = CONF_e7t
# DIST_e7t_rtdruid            =
# CLEAN_e7t_rtdruid           =
# COMPILE_e7t_rtdruid         = COMPILE_e7t
# DEBUG_e7t_rtdruid           = DEBUG_e7t

# # e7t_manual
# TESTLIST += e7t_manual
# OUTDIR_COMMANDS_e7t_manual  = OUTDIR_COMMANDS_e7t_manual
# CONF_e7t_manual              =
# DIST_e7t_manual             =
# CLEAN_e7t_manual            = CLEAN_e7t_manual
# COMPILE_e7t_manual          = COMPILE_e7t
# DEBUG_e7t_manual            = DEBUG_e7t

# # e7t_dist_src
# TESTLIST += e7t_dist_src
# OUTDIR_COMMANDS_e7t_dist_src = OUTDIR_COMMANDS_e7t
# CONF_e7t_dist_src             = CONF_e7t_source
# DIST_e7t_dist_src            = DIST_e7t_source
# CLEAN_e7t_dist_src           =
# COMPILE_e7t_dist_src         = COMPILE_e7t_source
# DEBUG_e7t_dist_src           = DEBUG_e7t

# # e7t_dist_bin_full
# TESTLIST += e7t_dist_bin_full
# OUTDIR_COMMANDS_e7t_dist_bin_full = OUTDIR_COMMANDS_e7t
# CONF_e7t_dist_bin_full             = CONF_e7t_binfull
# DIST_e7t_dist_bin_full            = DIST_e7t_binfull
# CLEAN_e7t_dist_bin_full           =
# COMPILE_e7t_dist_bin_full         = COMPILE_e7t_source
# DEBUG_e7t_dist_bin_full           = DEBUG_e7t

# # e7t_dist_bin_lim
# TESTLIST += e7t_dist_bin_lim
# OUTDIR_COMMANDS_e7t_dist_bin_lim = OUTDIR_COMMANDS_e7t
# CONF_e7t_dist_bin_lim             = CONF_e7t_binlim
# DIST_e7t_dist_bin_lim            = DIST_e7t_binlim
# CLEAN_e7t_dist_bin_lim           =
# COMPILE_e7t_dist_bin_lim         = COMPILE_e7t_source
# DEBUG_e7t_dist_bin_lim           = DEBUG_e7t

# # -------------------------------------------------------------------


# EE_TMPDIR = $(EEBASE)/testcase/tmp
# FILE_LOCK = $(EE_TMPDIR)/e7t_manual.lock
# RTDRUID_GENERATE_LOCK = $(EE_TMPDIR)/rtdruid_generate_lock.lock
# LOCKFILE= lockfile -1 -r-1
# DIST_LOCK = $(EE_TMPDIR)/dist.lock


# # -------------------------------------------------------------------

# # These are the commands used by e7t_rtdruid

# OUTDIR_COMMANDS_e7t = cd $@; cp -sf ../*.* .

# # This piece of commented code is to put an if to the generation code
# # in ARCH_MK_CONF

# #if test ! -e $(OUTDIR_PREFIX)$*/ee.oil; then \
# #fi;\
# #if test -n `grep $(OUTDIR_PREFIX)$*/ee.oil $(EE_TMPDIR)/rtdruid_ant_partial.xml`; then \
# #fi;

# CONF_e7t = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\"/\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;

# COMPILE_e7t = +@$(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*



# DEBUG_e7t = \
# 	@cp evaluator7t/t32.cmm $(OUTDIR_PREFIX)$*; \
# 	$(LOCKFILE) $(FILE_LOCK); \
# 		echo chdir $(OUTDIR_PREFIX)$* >> $(EE_TMPDIR)/t32_jobs.cmm; \
# 		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
# 		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
# 		echo print \"$(OUTDIR_PREFIX)$*\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
# 		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
# 		echo do t32.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
# 		cp -u evaluator7t/t32_quit.cmm $(EE_TMPDIR)/t32.cmm; \
# 	rm -f $(FILE_LOCK); \


# # -------------------------------------------------------------------

# # These are the commands used by e7t_manual

# OUTDIR_COMMANDS_e7t_manual = @cd $@; cp -sf ../*.* .; cp -sf ../manual/*.* ../manual/makefile .

# CLEAN_e7t_manual = +@$(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$* clean

# # -------------------------------------------------------------------

# # These are the commands used by e7t_dist_src

# COMPILE_e7t_source = +@$(MAKE) $(PARAMETERS) NODEPS=1 EEBASE=$(OUTDIR_PREFIX)$*/ee_RTDRUID -C $(OUTDIR_PREFIX)$*

# CONF_e7t_source = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" sourcedistr_file=\"sourcedist.mk\" /\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;

# DIST_e7t_source = \
# 	@echo DIST $(OUTDIR_PREFIX)$*; \
# 	$(LOCKFILE) $(DIST_LOCK); \
# 		make -C $(EEBASE)/dist/source DISTFILE=$(OUTDIR_PREFIX)$*/sourcedist.mk DIST=RTDRUID; \
# 		mv $(EEBASE)/dist/source/ee_RTDRUID $(OUTDIR_PREFIX)$*; \
# 	rm -rf $(DIST_LOCK)

# # -------------------------------------------------------------------

# # These are the commands used by e7t_dist_bin_full

# CONF_e7t_binfull = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrfull_file=\"bindistrfull.mk\" /\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;

# DIST_e7t_binfull = \
# 	@echo DIST $(OUTDIR_PREFIX)$*; \
# 	$(LOCKFILE) $(DIST_LOCK); \
# 		make -C $(EEBASE)/dist/binary DISTFILE=$(OUTDIR_PREFIX)$*/bindistrfull.mk DIST=RTDRUID; \
# 		mv $(EEBASE)/dist/binary/ee_RTDRUID $(OUTDIR_PREFIX)$*; \
# 		make -C $(EEBASE)/dist/binary clean; \
# 	rm -rf $(DIST_LOCK)

# # -------------------------------------------------------------------

# # These are the commands used by e7t_dist_bin_lim

# CONF_e7t_binlim = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrlimited_file=\"bindistrlimited.mk\" /\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;

# DIST_e7t_binlim = \
# 	@echo DIST $(OUTDIR_PREFIX)$*; \
# 	$(LOCKFILE) $(DIST_LOCK); \
# 		make -C $(EEBASE)/dist/binary DISTFILE=$(OUTDIR_PREFIX)$*/bindistrlimited.mk DIST=RTDRUID; \
# 		mv $(EEBASE)/dist/binary/ee_RTDRUID $(OUTDIR_PREFIX)$*; \
# 		make -C $(EEBASE)/dist/binary clean; \
# 	rm -rf $(DIST_LOCK)


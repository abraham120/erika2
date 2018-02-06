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
# Altera Nios 2 testcases
#

#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/nios2_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/nios2_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/nios2_rtdruid_global_build.xml; \
		cd tmp; java -jar $(LAUNCHER_JAR) -application org.eclipse.ant.core.antRunner >rtdruid_nios2.log 2>&1; \
	fi );




#
# configurations
#

TESTLIST += nios2
CONF_nios2             = $(CONF_nios2_source)
DIST_nios2            =
RTDRUID_nios2            = $(RTDRUID_nios2_source)
CLEAN_nios2           =
COMPILE_nios2         = $(COMPILE_nios2_source)

# nios2_dist_trace
TESTLIST += nios2_trace
OUTDIR_COMMANDS_nios2_trace = $(OUTDIR_COMMANDS_nios2)
CONF_nios2_trace             = $(CONF_nios2_source)
DIST_nios2_trace            =
RTDRUID_nios2_trace            = $(RTDRUID_nios2_source)
CLEAN_nios2_trace           =
COMPILE_nios2_trace         = $(COMPILE_nios2_source)


# -------------------------------------------------------------------


EE_TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(EE_TMPDIR)/nios2_manual.lock
RTDRUID_GENERATE_LOCK = $(EE_TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(EE_TMPDIR)/dist.lock


# -------------------------------------------------------------------

# These are the commands used by nios2_rtdruid

OUTDIR_COMMANDS_nios2 = cd $@; cp -sf ../*.* .

# This piece of commented code is to put an if to the generation code
# in ARCH_MK_CONF

#if test ! -e $(OUTDIR_PREFIX)$*/ee.oil; then \
#fi;\
#if test -n `grep $(OUTDIR_PREFIX)$*/ee.oil $(EE_TMPDIR)/rtdruid_ant_partial.xml`; then \
#fi;

# CONF_nios2 = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\"/\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;

# COMPILE_nios2 = +@$(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*



DEBUG_nios2 = \
	cp nios2/testcase.cmm $(OUTDIR_PREFIX)$*/Debug; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo chdir `cygpath -w $(OUTDIR_PREFIX)$*/Debug` >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print \"`cygpath -w $(OUTDIR_PREFIX)$*/Debug`\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo do testcase.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
		cp -u nios2/t32.cmm $(EE_TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK); \


DEBUG_nios2_trace = \
	cp nios2/testcase_trace.cmm $(OUTDIR_PREFIX)$*/Debug; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo chdir `cygpath -w $(OUTDIR_PREFIX)$*/Debug` >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print \"`cygpath -w $(OUTDIR_PREFIX)$*/Debug`\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo do testcase_trace.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
		cp -u nios2/t32.cmm $(EE_TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK); \



# -------------------------------------------------------------------


# # These are the commands used by nios2_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_nios2_source = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil;

#COMPILE_nios2_source = +$(MAKE) $(PARAMETERS) NODEPS=1 EEBASE=$(OUTDIR_PREFIX)$*/ee_RTDRUID -C $(OUTDIR_PREFIX)$*

# workaround for a bug in RT-Druid that does not generate the results in the right directory
# moreover the make version in Nios II is a 3.80. To call it we use the script mymake.sh
# we cannot use make 3.81 shipped with cygwin because it does not support windows pathnames in the directory name
# we cannot use make380 in cygwin because of the CR-LF problem
# I also had to make a symbolic link in /home in the nios2 cygwin installation
COMPILE_nios2_source = mkdir $(OUTDIR_PREFIX)$*/Debug; mv $(OUTDIR_PREFIX)$*/makefile $(OUTDIR_PREFIX)$*/Debug; mv $(OUTDIR_PREFIX)$*/default_cpu $(OUTDIR_PREFIX)$*/Debug; mv $(OUTDIR_PREFIX)$*/common.mk $(OUTDIR_PREFIX)$*/Debug; $(EEBASE)/testcase/common/nios2/mymake.sh $(PARAMETERS) NODEPS=1 EEBASE=$(OUTDIR_PREFIX)$*/ee_RTDRUID -C $(OUTDIR_PREFIX)$*/Debug

RTDRUID_nios2_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(call native_path,$(OUTDIR_PREFIX)$*/ee.oil)\" outputdir=\"$(call native_path,$(OUTDIR_PREFIX)$*)\" /\> >> $(EE_TMPDIR)/nios2_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!


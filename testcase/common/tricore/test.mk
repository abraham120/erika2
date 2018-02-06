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
# TriCore testcases
#


#
# Global scripts
#

GLOBAL_RTDRUID += \
	( if test -e tmp/tricore_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/tricore_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/tricore_rtdruid_global_build.xml; \
		cd tmp; java -jar $(LAUNCHER_JAR) -application org.eclipse.ant.core.antRunner >rtdruid_tricore.log 2>&1; \
	fi );

#
# configurations
#

# tricore_tc27x_tasking
TESTLIST                                +=  tricore_tc27x_tasking
OUTDIR_COMMANDS_tricore_tc27x_tasking   =   $(OUTDIR_COMMANDS_tricore_source)
CONF_tricore_tc27x_tasking              =   $(CONF_tricore_source)
GLOBAL_CONF                             +=
DIST_tricore_tc27x_tasking              =
RTDRUID_tricore_tc27x_tasking           =   $(RTDRUID_tricore_source)
CLEAN_tricore_tc27x_tasking             =
COMPILE_tricore_tc27x_tasking           =   $(COMPILE_tricore_source)
DEBUG_tricore_tc27x_tasking             =   $(DEBUG_tricore_tasking_source)

# tricore_tc27x_gnu
TESTLIST                                +=  tricore_tc27x_gnu
OUTDIR_COMMANDS_tricore_tc27x_gnu        =   $(OUTDIR_COMMANDS_tricore_source)
CONF_tricore_tc27x_gnu                   =   $(CONF_tricore_source)
GLOBAL_CONF                             +=
DIST_tricore_tc27x_gnu                   =
RTDRUID_tricore_tc27x_gnu                =   $(RTDRUID_tricore_source)
CLEAN_tricore_tc27x_gnu                  =
COMPILE_tricore_tc27x_gnu                =   $(COMPILE_tricore_source)
DEBUG_tricore_tc27x_gnu                  =   $(DEBUG_tricore_tasking_source)

# tricore_tc29x_gnu
TESTLIST                                +=  tricore_tc29x_gnu
OUTDIR_COMMANDS_tricore_tc29x_gnu        =   $(OUTDIR_COMMANDS_tricore_source)
CONF_tricore_tc29x_gnu                   =   $(CONF_tricore_source)
GLOBAL_CONF                             +=
DIST_tricore_tc29x_gnu                   =
RTDRUID_tricore_tc29x_gnu                =   $(RTDRUID_tricore_source)
CLEAN_tricore_tc29x_gnu                  =
COMPILE_tricore_tc29x_gnu                =   $(COMPILE_tricore_source)
DEBUG_tricore_tc29x_gnu                  =   $(DEBUG_tricore_t29x_source)

# -------------------------------------------------------------------

EE_TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(EE_TMPDIR)/tricore_manual.lock
RTDRUID_GENERATE_LOCK = $(EE_TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(EE_TMPDIR)/dist.lock
NATIVE_OUTDIR_PREFIX = $(call native_path,$(OUTDIR_PREFIX))

# -------------------------------------------------------------------

OUTDIR_COMMANDS_tricore_source = \
	( cd $@; cp -f ../*.* .; );

# -------------------------------------------------------------------
# # These are the commands used by tricore_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution

CONF_tricore_source = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil;

# Generate the rt-druid files...
RTDRUID_tricore_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(call native_path,$(OUTDIR_PREFIX)$*/ee.oil)\" outputdir=\"$(call native_path,$(OUTDIR_PREFIX)$*/Debug)\" /\> >> $(EE_TMPDIR)/tricore_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!!!

COMPILE_tricore_source = \
	+@unset EEBASE; \
	if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug >$(OUTDIR_PREFIX)$*/compile.log 2>&1; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/errors.log; fi

DEBUG_tricore_tasking_source = \
	cp tricore/t32_tc27x.cmm $(OUTDIR_PREFIX)$*/t32.cmm; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "&count=&count+1" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo chdir $(NATIVE_OUTDIR_PREFIX)$* >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo "write \#1 \"$(NATIVE_OUTDIR_PREFIX)$*\"" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print '"Test no. "' '%Decimal' '&count' '" ("' '&failed' \
		'" errors so far)"' >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print \"$(NATIVE_OUTDIR_PREFIX)$*\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo do t32.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
		cp -u tricore/t32_quit.cmm $(EE_TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK);

DEBUG_tricore_t29x_source = \
	cp tricore/t32_tc29x.cmm $(OUTDIR_PREFIX)$*/t32.cmm; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "&count=&count+1" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo chdir $(NATIVE_OUTDIR_PREFIX)$* >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo "write \#1 \"$(NATIVE_OUTDIR_PREFIX)$*\"" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select Messages >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print '"Test no. "' '%Decimal' '&count' '" ("' '&failed' \
		'" errors so far)"' >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo print \"$(NATIVE_OUTDIR_PREFIX)$*\" >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo area.select A000 >> $(EE_TMPDIR)/t32_jobs.cmm; \
		echo do t32.cmm >> $(EE_TMPDIR)/t32_jobs.cmm; \
		cp -u tricore/t32_quit.cmm $(EE_TMPDIR)/t32.cmm; \
	rm -f $(FILE_LOCK);
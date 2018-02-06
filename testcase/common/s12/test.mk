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
# Freescale S12XS testcases
#

#
# Global scripts
#


GLOBAL_RTDRUID += \
	( if test -e tmp/s12xs_rtdruid_partial.xml; then \
		cat common/rtdruid_common/script_prologue.xml tmp/s12xs_rtdruid_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
		cp tmp/build.xml tmp/s12xs_rtdruid_global_build.xml; \
		cd tmp; java -jar $(LAUNCHER_JAR) -application org.eclipse.ant.core.antRunner >rtdruid_s12xs.log 2>&1; \
	fi );


#
# configurations
#

TESTLIST += s12xs_cosmic s12xs_cw s12g128_cw s12g48_cw s12gn48_cw

# s12xs_cosmic
OUTDIR_COMMANDS_s12xs_cosmic    = $(OUTDIR_COMMANDS_s12xs_cosmic_source)
CONF_s12xs_cosmic               = $(CONF_s12_source)
GLOBAL_CONF                    +=
DIST_s12xs_cosmic               =
RTDRUID_s12xs_cosmic            = $(RTDRUID_s12_source)
CLEAN_s12xs_cosmic              =
COMPILE_s12xs_cosmic            = $(COMPILE_s12_source)
DEBUG_s12xs_cosmic              = $(DEBUG_s12xs_cosmic_source)

# s12xs_cw
OUTDIR_COMMANDS_s12xs_cw    = $(OUTDIR_COMMANDS_s12xs_cw_source)
CONF_s12xs_cw               = $(CONF_s12_source)
GLOBAL_CONF                +=
DIST_s12xs_cw               =
RTDRUID_s12xs_cw            = $(RTDRUID_s12_source)
CLEAN_s12xs_cw              =
COMPILE_s12xs_cw            = $(COMPILE_s12_source)
DEBUG_s12xs_cw              = $(DEBUG_s12xs_cw_source)

# s12g128_cw
OUTDIR_COMMANDS_s12g128_cw     = $(OUTDIR_COMMANDS_s12g128_cw_source)
CONF_s12g128_cw                = $(CONF_s12_source)
RTDRUID_s12g128_cw             = $(RTDRUID_s12_source)
COMPILE_s12g128_cw             = $(COMPILE_s12_source)
DEBUG_s12g128_cw               = $(DEBUG_s12g_cw_source)

# s12g48_cw
OUTDIR_COMMANDS_s12g48_cw     = $(OUTDIR_COMMANDS_s12g48_cw_source)
CONF_s12g48_cw                = $(CONF_s12_source)
RTDRUID_s12g48_cw             = $(RTDRUID_s12_source)
COMPILE_s12g48_cw             = $(COMPILE_s12_source)
DEBUG_s12g48_cw               = $(DEBUG_s12g_cw_source)

# s12gn48_cw
OUTDIR_COMMANDS_s12gn48_cw     = $(OUTDIR_COMMANDS_s12gn48_cw_source)
CONF_s12gn48_cw                = $(CONF_s12_source)
RTDRUID_s12gn48_cw             = $(RTDRUID_s12_source)
COMPILE_s12gn48_cw             = $(COMPILE_s12_source)
DEBUG_s12gn48_cw               = $(DEBUG_s12g_cw_source)

## s12xs_dist_bin_full
#TESTLIST                            += s12xs_dist_bin_full
#OUTDIR_COMMANDS_s12xs_dist_bin_full  = OUTDIR_COMMANDS_s12xs
#CONF_s12xs_dist_bin_full             = CONF_s12xs_binfull
#GLOBAL_CONF                         += $(GLOBAL_CONF_s12xs_binfull)
#DIST_s12xs_dist_bin_full             =
#RTDRUID_s12xs_dist_bin_full          = RTDRUID_s12xs_binfull
#CLEAN_s12xs_dist_bin_full            =
#COMPILE_s12xs_dist_bin_full          = COMPILE_s12_source
#DEBUG_s12xs_dist_bin_full            = DEBUG_s12xs

# -------------------------------------------------------------------

EE_TMPDIR = $(EEBASE)/testcase/tmp
FILE_LOCK = $(EE_TMPDIR)/s12xs_manual.lock
RTDRUID_GENERATE_LOCK = $(EE_TMPDIR)/rtdruid_generate_lock.lock
LOCKFILE= lockfile -1 -r-1
DIST_LOCK = $(EE_TMPDIR)/dist.lock

# -------------------------------------------------------------------

OUTDIR_COMMANDS_s12xs_cosmic_source = \
	( cd $@; cp -sf ../*.* .; \
	cp ../../common/s12/s12xs_cosmic/vector_s12x.c ../../common/s12/s12xs_cosmic/crtsx.S ../../common/s12/s12xs_cosmic/mc9s12xs128.lkf .; \
	cp ../../common/s12/s12xs_cosmic/Full_Chip_Simulation.ini ../../common/s12/s12xs_cosmic/C_Layout.hwl ../../common/s12/s12xs_cosmic/SofTec_HCS12.ini .; );

OUTDIR_COMMANDS_s12xs_cw_source = \
	( cd $@; cp -sf ../*.* .; \
	cp ../../common/s12/s12xs_cw/Vectors.c ../../common/s12/s12xs_cw/CPU12ISRs.c ../../common/s12/s12xs_cw/CPU12ISRs.h .; \
	cp ../../common/s12/s12xs_cw/Start12.c ../../common/s12/s12xs_cw/Full_Chip_Simulation.ini ../../common/s12/s12xs_cw/C_Layout.hwl ../../common/s12/s12xs_cw/SofTec_HCS12.ini .; );

OUTDIR_COMMANDS_s12g128_cw_source = \
	( cd $@; cp -sf ../*.* .; \
	cp ../../common/s12/s12g_cw/Vectors.c ../../common/s12/s12g_cw/CPU12ISRs.c ../../common/s12/s12g_cw/CPU12ISRs.h .; \
	cp ../../common/s12/s12g_cw/Start12.c ../../common/s12/s12g_cw/s12g128/Full_Chip_Simulation.ini ../../common/s12/s12g_cw/C_Layout.hwl ../../common/s12/s12g_cw/s12g128/PE_Multilink_CyclonePro.ini .; );

OUTDIR_COMMANDS_s12g48_cw_source = \
	( cd $@; cp -sf ../*.* .; \
	cp ../../common/s12/s12g_cw/Vectors.c ../../common/s12/s12g_cw/CPU12ISRs.c ../../common/s12/s12g_cw/CPU12ISRs.h .; \
	cp ../../common/s12/s12g_cw/Start12.c ../../common/s12/s12g_cw/s12g48/Full_Chip_Simulation.ini ../../common/s12/s12g_cw/C_Layout.hwl ../../common/s12/s12g_cw/s12g48/PE_Multilink_CyclonePro.ini .; );

OUTDIR_COMMANDS_s12gn48_cw_source = \
	( cd $@; cp -sf ../*.* .; \
	cp ../../common/s12/s12g_cw/Vectors.c ../../common/s12/s12g_cw/CPU12ISRs.c ../../common/s12/s12g_cw/CPU12ISRs.h .; \
	cp ../../common/s12/s12g_cw/Start12.c ../../common/s12/s12g_cw/s12gn48/Full_Chip_Simulation.ini ../../common/s12/s12g_cw/C_Layout.hwl ../../common/s12/s12g_cw/s12gn48/PE_Multilink_CyclonePro.ini .; );


# -------------------------------------------------------------------
# # These are the commands used by s12xs_dist_src

# this simply parses the OIL file and then raises a flag if there is need to generate a source distribution
CONF_s12_source = \
	@echo CONF $(OUTDIR_PREFIX)$*; \
	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -Ds12 -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil;

# Generate the rt-druid files...
RTDRUID_s12_source = \
	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
	echo \<rtdruid.Oil.Configurator inputfile=\"$(call native_path,$(OUTDIR_PREFIX)$*/ee.oil)\" outputdir=\"$(call native_path,$(OUTDIR_PREFIX)$*/Debug)\" /\> >> $(EE_TMPDIR)/s12xs_rtdruid_partial.xml;

# take also a look to GLOBAL_RTDRUID at the top of the file!!!

COMPILE_s12_source = \
	+@unset EEBASE; \
	if $(MAKE) $(PARAMETERS) NODEPS=1 -C $(OUTDIR_PREFIX)$*/Debug >$(OUTDIR_PREFIX)$*/compile.log 2>&1; then echo OK $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/ok.log; else echo ERROR $(EXPERIMENT) $(OUTDIR_PREFIX)$* >>$(EE_TMPDIR)/errors.log; fi

DEBUG_s12g_cw_source = \
	cp s12/s12g_cw/testcase.cmd $(OUTDIR_PREFIX)$*; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "                                     " >> $(EE_TMPDIR)/s12_jobs.cmd; \
		echo "cd `cygpath -w $(OUTDIR_PREFIX)$*`" >> $(EE_TMPDIR)/s12_jobs.cmd; \
		echo "cf testcase.cmd                      " >> $(EE_TMPDIR)/s12_jobs.cmd; \
		cp -u s12/s12.cmd $(EE_TMPDIR)/s12.cmd; \
	rm -f $(FILE_LOCK);

DEBUG_s12xs_cosmic_source = \
	cp s12/s12xs_cosmic/testcase.cmd $(OUTDIR_PREFIX)$*; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "                                     " >> $(EE_TMPDIR)/s12_jobs.cmd; \
		echo "cd `cygpath -w $(OUTDIR_PREFIX)$*`" >> $(EE_TMPDIR)/s12_jobs.cmd; \
		echo "cf testcase.cmd                      " >> $(EE_TMPDIR)/s12_jobs.cmd; \
		cp -u s12/s12.cmd $(EE_TMPDIR)/s12.cmd; \
	rm -f $(FILE_LOCK);
	
DEBUG_s12xs_cw_source = \
	cp s12/s12xs_cw/testcase.cmd $(OUTDIR_PREFIX)$*; \
	$(LOCKFILE) $(FILE_LOCK); \
		echo "                                     " >> $(EE_TMPDIR)/s12_jobs.cmd; \
		echo "cd `cygpath -w $(OUTDIR_PREFIX)$*`" >> $(EE_TMPDIR)/s12_jobs.cmd; \
		echo "cf testcase.cmd                      " >> $(EE_TMPDIR)/s12_jobs.cmd; \
		cp -u s12/s12.cmd $(EE_TMPDIR)/s12.cmd; \
	rm -f $(FILE_LOCK);


# -------------------------------------------------------------------
# These are the commands used by s12xs_dist_bin_full

#CONF_s12xs_binfull = \
#	@echo CONF $(OUTDIR_PREFIX)$*; \
#	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
#	echo \<rtdruid.Oil.DistributionBuilder inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputFile=\"`cygpath -m $(EE_TMPDIR)/bindistrfull_partial.mk`\" DistributionName=\"$(subst /,,$(EXPERIMENT))_$*\" DistributionType=\"full\"/\> >> $(EE_TMPDIR)/s12xs_ant_partial.xml;

#GLOBAL_CONF_s12xs_binfull = \
#	( if test s12xs_dist_bin_full = $(ARCH); then \
#		cat common/rtdruid_common/script_prologue.xml tmp/s12xs_ant_partial.xml common/rtdruid_common/script_epilogue.xml > tmp/build.xml; \
#		cp tmp/build.xml tmp/s12xs_ant_global_build.xml; \
#		cd tmp; java org.eclipse.core.launcher.Main -application org.eclipse.ant.core.antRunner; cd ..; \
#		echo "ALL_DISTRIBUTIONS += RTDRUID" > tmp/s12xs_bindistrfull.mk; \
#		cat tmp/bindistrfull_partial.mk >> tmp/s12xs_bindistrfull.mk; \
#		false; \
#		make -C ${EEBASE}/dist/binary DISTFILE=${EEBASE}/testcase/tmp/s12xs_bindistrfull.mk DIST=RTDRUID s12xs_MOVE=Y; \
#	fi );

#RTDRUID_s12xs_binfull = \
#	@echo RTDRUID $(OUTDIR_PREFIX)$*; \
#	echo \<rtdruid.Oil.Configurator inputfile=\"`cygpath -m $(OUTDIR_PREFIX)$*/ee.oil`\" outputdir=\"`cygpath -m $(OUTDIR_PREFIX)$*`\" Signatures_file=\"`cygpath -m $(EE_s12xs_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\" /\> >> $(EE_TMPDIR)/s12xs_rtdruid_partial.xml;
##binDistrSignatures_file=\"`cygpath -m $(EE_s12xs_IDE_BASE)/../../components/evidence_ee/ee/signature/signature.xml`\"

# take also a look to GLOBAL_RTDRUID at the top of the file!

# -------------------------------------------------------------------

# # These are the commands used by s12xs_dist_bin_lim

# CONF_s12xs_binlim = \
# 	@echo CONF $(OUTDIR_PREFIX)$*; \
# 	cat $(OUTDIR_PREFIX)$*/appl.oil | gcc -c - -E -P -I$(EEBASE)/pkg $(addprefix -D, $(shell $(DEMUX2) $*)) -D$(thearch) -o - >$(OUTDIR_PREFIX)$*/ee.oil; \
# 	echo \<rtdruid.Oil.Configurator inputfile=\"$(OUTDIR_PREFIX)$*/ee.oil\" outputdir=\"$(OUTDIR_PREFIX)$*\" bindistrlimited_file=\"bindistrlimited.mk\" /\> >> $(EE_TMPDIR)/rtdruid_ant_partial.xml;


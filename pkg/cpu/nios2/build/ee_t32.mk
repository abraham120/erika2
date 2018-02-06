#
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


# ERIKA Enterprise for Nios II
#
# Lauterback Trace32 support

#
# Trace32 Locations
#
T32_DRIVE=c:
T32_DIR=/cygdrive/c/T32



.PHONY: t32_scripts
t32_scripts:
	@echo T32 scripts

# generic .cmm files
# --------------------------
	@cp -ru $(subst \,/,$(SOPC_KIT_NIOS2))/components/evidence_ee/ee/pkg/cpu/nios2/debug/lauterbach/* .
	@chmod -R +w *

# config.t32 files for each CPU
# --------------------------
	@$(foreach cpu,$(CPU_LIST),\
		echo "\$$INCLUDE `cygpath -aw $(T32_DIR)/config.t32`"  > $($(cpu)_NAME)/config.t32; \
		echo "; Config lines added by ERIKA Enterprise"       >> $($(cpu)_NAME)/config.t32; \
		echo "; This file has been automatically generated"   >> $($(cpu)_NAME)/config.t32; \
		echo "; Do not modify"                                >> $($(cpu)_NAME)/config.t32; \
		echo "OS="                                            >> $($(cpu)_NAME)/config.t32; \
		echo "ID=T32_$($(cpu)_ID)"                            >> $($(cpu)_NAME)/config.t32; \
		echo                                                  >> $($(cpu)_NAME)/config.t32; \
		echo ";T32 Intercom"                                  >> $($(cpu)_NAME)/config.t32; \
		echo "IC=NETASSIST"                                   >> $($(cpu)_NAME)/config.t32; \
		echo "PORT=$($(cpu)_PORT)"                            >> $($(cpu)_NAME)/config.t32; \
		echo                                                  >> $($(cpu)_NAME)/config.t32; \
		echo "PBI="                                           >> $($(cpu)_NAME)/config.t32; \
		echo "CORE=$($(cpu)_ID)"                              >> $($(cpu)_NAME)/config.t32; \
		echo                                                  >> $($(cpu)_NAME)/config.t32; \
		echo ";Screen Settings:"                              >> $($(cpu)_NAME)/config.t32; \
		echo "SCREEN="                                        >> $($(cpu)_NAME)/config.t32; \
		echo "FONT=SMALL"                                     >> $($(cpu)_NAME)/config.t32; \
		echo "HEADER=ERIKA Enterprise on Nios II CPU $($(cpu)_NAME)" >> $($(cpu)_NAME)/config.t32; \
	)

# debug.bat
# --------------------------
	@echo "rem ERIKA Enterprise Debug script!"                         > debug.bat
	@echo "rem Do not modify!"                                        >> debug.bat
ifndef EE_NIOS2_JAM_FILE
	@echo "set EE_NIOS2_JAM_FILE=..\\..\\..\\fpga.jam"                >> debug.bat
else
	@echo "set EE_NIOS2_JAM_FILE=$(EE_NIOS2_JAM_FILE)"                >> debug.bat
endif
	@echo "cd `cygpath -aw .`"                                        >> debug.bat
	@echo "`cygpath -aw $(T32_DIR)`\\t32mnios.exe -c `cygpath -aw ./$(CPU_MASTER_NAME)/config.t32`" >> debug.bat
	@chmod +x debug.bat

# debugnojam.bat
# --------------------------
	@echo "rem ERIKA Enterprise Debug script!"                         > debug_nojam.bat
	@echo "rem Do not modify!"                                        >> debug_nojam.bat
	@echo "set EE_NIOS2_JAM_FILE=NOJAM"                               >> debug_nojam.bat
	@echo "cd `cygpath -aw .`"                                        >> debug_nojam.bat
	@echo "`cygpath -aw $(T32_DIR)`\\t32mnios.exe -c `cygpath -aw ./$(CPU_MASTER_NAME)/config.t32`" >> debug_nojam.bat
	@chmod +x debug_nojam.bat

# global t32.cmm
# --------------------------
	@echo "; Global Lauterbach script produced by ERIKA Enterprise"  > t32.cmm
	@echo do t32/jam                                                >> t32.cmm
	@$(foreach cpu,$(subst CPU_MASTER,,$(CPU_LIST)),\
		echo cd `cygpath -aw $($(cpu)_DIR)`                     >> t32.cmm; \
		echo os `cygpath -aw $(T32_DIR)`\\t32mnios.exe          >> t32.cmm; \
	)
	@echo cd `cygpath -aw $(CPU_MASTER_DIR)`                        >> t32.cmm
	@echo do t32                                                    >> t32.cmm

# t32.cmm files for each CPU
# --------------------------
	@$(foreach cpu,$(CPU_LIST),\
		echo "; t32.cmm generated by the ERIKA Enterprise scripts" > $($(cpu)_NAME)/t32.cmm; \
		echo "; Do not modify"                                    >> $($(cpu)_NAME)/t32.cmm; \
		echo "GLOBAL &EE_NIOS2_ELF_FILE"                          >> $($(cpu)_NAME)/t32.cmm; \
		echo "&EE_NIOS2_ELF_FILE=\"`cygpath -aw $($(cpu)_ELF)`\"" >> $($(cpu)_NAME)/t32.cmm; \
		echo "system.multicore.core $($(cpu)_ID)"                 >> $($(cpu)_NAME)/t32.cmm; \
		echo "do ../t32/debug_nojam.cmm"                          >> $($(cpu)_NAME)/t32.cmm; \
	)

# synch commands in t32.cmm
# -------------------------
# Note: the synch commands must be the last ones in the script because of the "go main" command!!!
# connect command for each CPU
	@$(foreach cpu,$(CPU_LIST),\
		echo "synch.connect $(foreach port, $(subst $(cpu),,$(CPU_LIST)), localhost:$($(port)_PORT))" >> $($(cpu)_NAME)/t32.cmm; \
	)
# synch.slaveXXX for the slaves
	@$(foreach cpu,$(subst CPU_MASTER,,$(CPU_LIST)),\
		echo "synch.SlaveGo on"                                   >> $($(cpu)_NAME)/t32.cmm; \
		echo "synch.SlaveStep on"                                 >> $($(cpu)_NAME)/t32.cmm; \
		echo "synch.SlaveBRK on"                                  >> $($(cpu)_NAME)/t32.cmm; \
	)
# synch.MasterXXX for the master
	@echo "synch.MasterGo on"                	                  >> $(CPU_MASTER_NAME)/t32.cmm
	@echo "synch.MasterStep on"                                       >> $(CPU_MASTER_NAME)/t32.cmm
	@echo "synch.MasterBRK on"                                        >> $(CPU_MASTER_NAME)/t32.cmm

# orti support for each cpu
# --------------------------
ifdef EE_ORTI_SUPPORT
	@$(foreach cpu,$(CPU_LIST),\
		echo "; ORTI SUPPORT"				                                 >> $($(cpu)_NAME)/t32.cmm; \
		echo "menu.reprogram orti"                                                       >> $($(cpu)_NAME)/t32.cmm; \
		echo "menu.reprogram `cygpath -aw $(T32_DIR)/demo/kernel/orti/ortiperf`"         >> $($(cpu)_NAME)/t32.cmm; \
		echo "task.orti system.orti"                                                     >> $($(cpu)_NAME)/t32.cmm; \
		$(T32_DIR)/demo/kernel/orti/genmenu.exe $($(cpu)_NAME)/system.orti 		 		          ; \
		mv orti.men $($(cpu)_NAME)										  ; \
	)
endif

# testcase_data.cmm
# --------------------------
# This file is generated and used only for internal automatic testcase generation only!
	@echo "; testcase_data.cmm generated for internal EE testsuite only!"      > testcase_data.cmm
	@echo "global &EE_NIOS2_JAM_FILE"                                         >> testcase_data.cmm
ifndef EE_NIOS2_JAM_FILE
	@echo "&EE_NIOS2_JAM_FILE=\"..\\..\\..\\fpga.jam\""                       >> testcase_data.cmm
else
	@echo "&EE_NIOS2_JAM_FILE=\"$(EE_NIOS2_JAM_FILE)\""                       >> testcase_data.cmm
endif
	@$(foreach cpu,$(CPU_LIST),\
		echo "global &EE_NIOS2_ELF_FILE"                                  >> testcase_data.cmm; \
		echo "&EE_NIOS2_ELF_FILE=\"`cygpath -aw $($(cpu)_ELF)`\""         >> testcase_data.cmm; \
	)


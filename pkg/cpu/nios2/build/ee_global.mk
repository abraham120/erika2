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



export EE_NM = nios2-elf-nm.exe

.PHONY: all clean

all:
	make -C $(CPU_MASTER_DIR) -f cpu.mk all
	$(EE_NM) $(CPU_MASTER_ELF) -n -t d | gawk '/EE_SHARED_DATA_/{printf "%s = 0x%x + 0x80000000;\n", substr($$3,16,length($$3)), $$1}' > shared.x
	$(EE_NM) $(CPU_MASTER_ELF) -n -t d | gawk '/EE_SHARED_CODE_/{printf "%s = 0x%x;\n", substr($$3,16,length($$3)), $$1}' >> shared.x
	$(foreach cpudir,$(CPU_DIRS), make -C $(cpudir) -f cpu.mk all ;)
	touch --reference=$(CPU_MASTER_ELF) cpu_master_date.tmp
	touch $(CPU_MASTER_ELF)
	make -C $(CPU_MASTER_DIR) -f cpu.mk EE_build_hex
	touch --reference=cpu_master_date.tmp $(CPU_MASTER_ELF)
	rm cpu_master_date.tmp
	make t32_scripts -f ./makefile

clean:
	make -C $(CPU_MASTER_DIR) -f cpu.mk clean
	$(foreach cpudir,$(CPU_DIRS), make -C $(cpudir) -f cpu.mk clean ;)

$(LOCAL_LINKER_SCRIPT): $(GENERATED_LINKER_SCRIPT)
	cp $(GENERATED_LINKER_SCRIPT) $(LOCAL_LINKER_SCRIPT)

$(LINKER_SCRIPT) : $(OBJS) $(LOCAL_LINKER_SCRIPT)
	cp $(LOCAL_LINKER_SCRIPT) $(LINKER_SCRIPT)
	$(EE_NM) $(OBJS) -n -t d | gawk '/EE_SHARED_DATA_/{printf "%s = %s + 0x80000000;\n", substr($$3,16,length($$3)), $$3}' >> $(LINKER_SCRIPT)
	$(EE_NM) $(OBJS) -n -t d | gawk '/EE_SHARED_CODE_/{printf "%s = %s;\n", substr($$3,16,length($$3)), $$3}' >> $(LINKER_SCRIPT)

# let's include the lauterbach script generation rules
include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/ee_t32.mk

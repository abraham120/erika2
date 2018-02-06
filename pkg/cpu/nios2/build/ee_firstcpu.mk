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


# This is the CPU makefile used by the FIRST CPU.
# This file is included by the cpu.mk of the first CPU only.

# Note: This rule have to stay AFTER the include of the APP_MAKEFILE because it depends on OBJS!!!

$(LINKER_SCRIPT) : $(OBJS) $(LOCAL_LINKER_SCRIPT)
	cp $(LOCAL_LINKER_SCRIPT) $(LINKER_SCRIPT)
	$(EE_NM) $(OBJS) -n -t d | gawk '/EE_SHARED_DATA_/{printf "%s = %s + 0x80000000;\n", substr($$3,16,length($$3)), $$3}' >> $(LINKER_SCRIPT)
	$(EE_NM) $(OBJS) -n -t d | gawk '/EE_SHARED_CODE_/{printf "%s = %s;\n", substr($$3,16,length($$3)), $$3}' >> $(LINKER_SCRIPT)

# This hack is needed to rebuild the hex target only if hex files are
# produced for the system. That is because the Altera code generator
# does not put an hex target when there is any onchip memory in a
# design.

# note that with test we only check that the string is not null!

EE_build_hex:
	if (test $(firstword $(shell grep hex $(GTF_GENERATED)/generated_app.mk))); then (make -C . -f cpu.mk hex;); fi

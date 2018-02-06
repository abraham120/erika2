# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
#
# Copyright (C) 2002-2013  Evidence Srl
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

## Author: 2013, Bruno Morelli

ifeq ($(call iseeopt, EE_CUBIEBOARD2__), yes)
ifneq ($(call iseeopt, __DEFAULT_LD_SCRIPT__), yes)

gcclibdir := $(shell dirname `$(EE_CC) -print-libgcc-file-name`)

TARGET += $(TARGET_NAME).bin

$(TARGET_NAME).bin: $(TARGET_NAME).elf
	@echo "************************************"
	@echo "Building $@"
	$(QUIET)$(EE_OBJCOPY) -O binary $(TARGET_NAME).elf $@ 2>/dev/null


OPT_LINK += -T gnu_cubieboard2.lds -Ttext 0x80008000
EXT_LIBS += -L$(gcclibdir) -lgcc
LINKDEP = gnu_cubieboard2.lds

EE_SRCS += pkg/board/cubieboard2/src/core_init.S
EE_SRCS += pkg/board/cubieboard2/src/crt0.S
EE_SRCS += pkg/board/cubieboard2/src/eabi_compat.c

OPT_CC +=  -fno-strict-aliasing -fno-common -msoft-float -fno-builtin -ffreestanding\
 -marm -mno-thumb-interwork -fno-stack-protector -mabi=aapcs-linux -nostdlib

OPT_CC += -DEE_ARM_PERIPHBASE=0x00A00000

gnu_cubieboard2.lds: $(PKGBASE)/board/cubieboard2/cfg/gnu_cubieboard2.lds
	@printf "LOC\n" ;
	@cp $(PKGBASE)/board/cubieboard2/cfg/gnu_cubieboard2.lds .
endif
endif

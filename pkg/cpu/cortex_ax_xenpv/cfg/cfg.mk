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

## Author: 2013 Bruno Morelli

#
# GCC compiler for ARM
#
ifeq ($(call iseeopt, EE_CORTEX_AX_XENPV__), yes)
EE_SRCS += pkg/cpu/cortex_ax_xenpv/xenpv/hyper-arm_32.S
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/ee_hal.S
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/gic.c
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/ee_cax_vtable.c
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/private_timer.c
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/ee_irqv.S
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/ee_irq_handlers.S
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/xendebug.c
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/xenincludes.c
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/xenstore.c
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/xengnttab.c

ifeq ($(call iseeopt, __OO_BCC1__), yes)
CPU_OO=YES
endif
ifeq ($(call iseeopt, __OO_BCC2__), yes)
CPU_OO=YES
endif
ifeq ($(call iseeopt, __OO_ECC1__), yes)
CPU_OO=YES
endif
ifeq ($(call iseeopt, __OO_ECC2__), yes)
CPU_OO=YES
endif

ifeq ($(CPU_OO), YES)
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/ee_oo.S
endif

#ifeq ($(call iseeopt, __MSRP__), yes)
EE_SRCS += pkg/cpu/cortex_ax_xenpv/src/ee_cax_multicore.c
#endif

endif

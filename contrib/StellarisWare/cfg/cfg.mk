# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2012  Evidence Srl
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

##
## Author:  2012,  Giuseppe Serano
##

ifneq ($(ENABLE_LIBS), TRUE)

ifeq ($(call iseeopt, __STELLARISWARE__), yes)

EEOPT += TARGET_IS_BLIZZARD_RA1
EEOPT += PART_LM4F232H5QD

INCLUDE_PATH += $(EEBASE)/contrib/StellarisWare/

ifeq ($(call iseeopt, __STELLARISWARE_DRIVER_LIB__), yes)

endif

ifeq ($(call iseeopt, __STELLARISWARE_GRAPHICS_LIB__), yes)
# GrContextFontSet 
EE_SRCS += contrib/StellarisWare/grlib/string.c
# GrContextInit
EE_SRCS += contrib/StellarisWare/grlib/context.c
# GrRectDraw
EE_SRCS += contrib/StellarisWare/grlib/rectangle.c
# g_sFontFixed6x8
EE_SRCS += contrib/StellarisWare/grlib/fonts/fontfixed6x8.c
# GrMapISO8859_1_Unicode
EE_SRCS += contrib/StellarisWare/grlib/charmap.c
# GrLineDrawH, GrLineDrawV
EE_SRCS += contrib/StellarisWare/grlib/line.c
endif

ifeq ($(call iseeopt, __STELLARISWARE_EK_LM4F232__), yes)
INCLUDE_PATH += $(EEBASE)/contrib/StellarisWare/boards/ek-lm4f232/
EE_SRCS += contrib/StellarisWare/boards/ek-lm4f232/drivers/cfal96x64x16.c
endif

endif	# __STELLARISWARE__

endif	# ENABLE_LIBS
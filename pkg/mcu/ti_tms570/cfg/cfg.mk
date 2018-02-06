# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2011  Evidence Srl
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
# Edited: 2014  Christoph Kreuzberger

ifeq ($(call iseeopt, __TMS570__), yes)

# Add Contrib Include Path
INCLUDE_PATH += $(EEBASE)/contrib/ti_tms570/include/

ifeq ($(call iseeopt, __CCS__), yes)


# Startup Code
ifndef CRT0_SRCS
CRT0_SRCS += contrib/ti_tms570/source/sys_intvecs.asm
endif	# CRT0_SRCS

# Yet necessary files from Contrib
EE_SRCS += contrib/ti_tms570/source/esm.c
EE_SRCS += contrib/ti_tms570/source/notification.c
EE_SRCS += contrib/ti_tms570/source/rti.c
EE_SRCS += contrib/ti_tms570/source/sys_core.asm
EE_SRCS += contrib/ti_tms570/source/sys_memory.asm
EE_SRCS += contrib/ti_tms570/source/sys_mpu.asm
EE_SRCS += contrib/ti_tms570/source/sys_phantom.c
EE_SRCS += contrib/ti_tms570/source/sys_pmu.asm
EE_SRCS += contrib/ti_tms570/source/sys_startup.c
EE_SRCS += contrib/ti_tms570/source/system.c
EE_SRCS += contrib/ti_tms570/source/dabort.asm


# GIO Driver
ifeq ($(or $(call iseeopt, __USE_GIO__), $(call iseeopt, __USE_LEDS__)), yes)
EE_SRCS += contrib/ti_tms570/source/gio.c
endif

# HET Driver
ifeq ($(or $(call iseeopt, __USE_HET__), $(call iseeopt, __USE_LEDS__)), yes)
EE_SRCS += contrib/ti_tms570/source/het.c
endif


# Selftest Driver
ifeq ($(call iseeopt, __USE_Selftest__), yes)
EE_SRCS += contrib/ti_tms570/source/sys_selftest.c
endif

# LIN Driver
ifeq ($(call iseeopt, __USE_LIN__), yes)
EE_SRCS += contrib/ti_tms570/source/lin.c
endif

# SPI Driver
ifeq ($(call iseeopt, __USE_SPI__), yes)
EE_SRCS += contrib/ti_tms570/source/spi.c
endif

# SCI Driver
ifeq ($(call iseeopt, __USE_SCI__), yes)
EE_SRCS += contrib/ti_tms570/source/sci.c
endif

# ADC Driver
ifeq ($(call iseeopt, __USE_ADC__), yes)
EE_SRCS += contrib/ti_tms570/source/adc.c
endif

# CAN Driver
ifeq ($(call iseeopt, __USE_CAN__), yes)
EE_SRCS += contrib/ti_tms570/source/can.c
endif


endif	# !__CCS__

ifeq ($(call iseeopt, __USE_TIMER__), yes)
#EE_SRCS += pkg/mcu/ti_tms570/src/ee_timer.c
endif


endif	# __TMS570__



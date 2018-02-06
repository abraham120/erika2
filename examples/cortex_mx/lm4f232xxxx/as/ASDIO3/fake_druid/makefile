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

### fake-druid makefile
#
# Author: 2011  Giuseppe Serano

### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1276


############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ASSERT__
EEOPT += __USE_SYSTICK__
EEOPT += __AUTOSAR_R4_0__
EEOPT += __AS_MCU_DRIVER__
EEOPT += __AS_PORT_DRIVER__
EEOPT += __AS_DIO_DRIVER__
EEOPT += __ADD_LIBS__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M4__
EEOPT += __KEIL__
EEOPT += __STELLARIS__
EEOPT += __LM4F232xxxx__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCE__
EEOPT += __DISABLE_EEOPT_DEFINES__

############################################################################
#
# Erika base directory
#
############################################################################
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)
else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_1.6.0.20111119_0157\ee_files'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=

############################################################################
#
# CORTEX M4
#
############################################################################
APPBASE := ..
OUTBASE := .

ifndef ARM_ROOT
    ARM_ROOT := $(shell cygpath `cygpath -ms 'C:\Keil\ARM'`)
endif

############################################################################
#
# Init MCU for CORTEX MX (LM4F232xxxx)
#
############################################################################
STELLARIS_MODEL           := LM4F232xxxx


############################################################################
#
# Flags
#
############################################################################
CFLAGS  +=
ASFLAGS +=
LDFLAGS +=
LDDEPS  +=
LIBS    +=

LIB_OPT  += __LIB_AUTOSAR__

############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c main.c Dio_Cfg.c Mcu_Cfg.c Port_Cfg.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

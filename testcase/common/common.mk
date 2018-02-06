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

# Author: 2011 Bernardo Dal Seno
#              Giuseppe Serano

# Common makefile

MYOS:=$(shell uname -s)

ifeq ($(findstring Linux, $(MYOS)), Linux)
# Linux: `strip' removes leading or trailing white chars
native_path = $(strip $1)
else
# Cygwin: Sed is used to remove trailing backslash and to double internal backslashes
native_path = $(shell cygpath -w $1 | sed -e 's/\\$$//' -e 's/\\/\\\\/g')
endif

ifeq ($(findstring Linux, $(MYOS)), Linux)
unix_path = $1
else
unix_path = $(shell cygpath $(shell cygpath -m -s '$1'))
endif

ifdef ERIKA_FILES

ifdef EEBASE
       $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif

EEBASE := $(call unix_path,$(ERIKA_FILES))

else # ERIKA_FILES

ifndef EEBASE
EEBASE := $(call unix_path,$(PWD)/../)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif

endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside makefiles

ifdef RTDRUID_ECLIPSE_HOME

ifdef ECLIPSE_HOME
       $(warning ECLIPSE_HOME is set, but it has been overridden by RTDRUID_ECLIPSE_HOME)
endif

ECLIPSE_HOME := $(call unix_path,$(RTDRUID_ECLIPSE_HOME))

else #RTDRUID_ECLIPSE_HOME

ifndef ECLIPSE_HOME
ECLIPSE_HOME := /opt/eclipse/
else
        $(warning The usage of ECLIPSE_HOME is deprecated. Please use RTDRUID_ECLIPSE_HOME)
endif

endif # RTDRUID_ECLIPSE_HOME
LAUNCHER_JAR := "$(call native_path,$(shell ls $(ECLIPSE_HOME)/plugins/org.eclipse.equinox.launcher_*.jar))"
# RTDRUID_ECLIPSE_HOME has fulfilled its role. Make sure it's not used inside makefiles
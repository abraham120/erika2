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
## Author: 2008 Mauro Marinoni
##         2012 Giuseppe Serano
##

ifeq ($(call iseeopt, __CORTEX_MX__), yes)

ifneq ($(ENABLE_LIBS), TRUE)

ifeq ( \
  $(or $(call iseeopt, USE_CONSOLE), $(call iseeopt, USE_CONSOLE_SERIAL)), yes \
)

##
## Application files
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/console/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/console/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/console/inc

EE_SRCS_CONSOLE_COMMON := $(addprefix \
	contrib/console/src/, \
	$(notdir $(shell ls -1 $(EEBASE)/contrib/console/src/*.c)) \
)
EE_SRCS += $(EE_SRCS_CONSOLE_COMMON)

## Check the architecture
EE_SRCS += contrib/console/src/hal/cortex_mx.c

endif	# USE_CONSOLE || USE_CONSOLE_SERIAL

endif	# ENABLE_LIBS

else	# __CORTEX_MX__

## Check the Console library selection
ifeq ($(findstring __LIB_CONSOLE__,$(LIB_OPT)),__LIB_CONSOLE__)

##
## Application files
##

#EE_SRCS += contrib/console/src/console.c
EE_SRCS_CONSOLE_COMMON := $(addprefix contrib/console/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/console/src/*.c)))
EE_SRCS += $(EE_SRCS_CONSOLE_COMMON)


## Check the architecture
ifeq ($(call iseeopt, __PIC30__), yes)
EE_SRCS += contrib/console/src/hal/pic30.c
endif

ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/console/src/hal/pic32.c
endif

ifeq ($(call iseeopt, __AVR5__), yes)
EE_SRCS += contrib/console/src/hal/avr5.c
endif

ifeq ($(call iseeopt, __AVR8__), yes)
EE_SRCS += contrib/console/src/hal/avr8.c
endif

ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/console/src/hal/mico32.c
endif

ifeq ($(call iseeopt, __MC9S12__), yes)
EE_HC12_CONSOLE=YES
endif
ifeq ($(call iseeopt, __HCS12XS__), yes)
EE_HC12_CONSOLE=YES
endif
ifeq ($(EE_HC12_CONSOLE), YES)
EE_SRCS += contrib/console/src/hal/s12.c
endif

endif

endif	# !__CORTEX_MX__

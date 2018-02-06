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
## Author: 2007 Mauro Marinoni
##         2012 Giuseppe Serano
##

## Check the Console library selection
ifeq ($(findstring __LIB_CONSOLE__,$(LIB_OPT)) , __LIB_CONSOLE__)
INCLUDE_CONSOLE = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_CONSOLE = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_CONSOLE), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __COSMIC__), yes)
ALLINCPATH += -i"$(shell cygpath -w $(EEBASE)/contrib/console/inc)"
else
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/console/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/console/inc
endif
endif
INCLUDE_PATH += $(EEBASE)/contrib/console/inc

ifeq ($(call iseeopt, __CORTEX_MX__), yes)

## Add each file individually
EE_SRCS_CONSOLE := $(addprefix \
	contrib/console/src/, \
	$(notdir $(shell ls -1 $(EEBASE)/contrib/console/src/*.c)) \
)

EE_SRCS_CONSOLE += contrib/console/src/hal/cortex_mx.c

else	# __CORTEX_MX__

## Add each file individually
#EE_SRCS_CONSOLE += contrib/console/libsrc/libconsole.c
EE_SRCS_CONSOLE +=

endif	# !__CORTEX_MX__

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_CONSOLE),)
EE_OBJS_CONSOLE := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_CONSOLE))))
LIBSRCS += $(EE_SRCS_CONSOLE)

ifeq ($(call iseeopt, __CORTEX_MX__), yes)
CONSOLELIBNAME	:= console
CONSOLELIB	:= lib$(CONSOLELIBNAME).a

$(CONSOLELIB): $(EE_OBJS_CONSOLE)
	@echo "AR  $(CONSOLELIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^
else	# __CORTEX_MX__
libconsole.a: $(EE_OBJS_CONSOLE)
	@echo $(EE_SRC_CONSOLE)
	@printf "AR  libconsole.a\n" ;
	$(QUIET)$(EE_AR) rs libconsole.a $(EE_OBJS_CONSOLE)
endif	# !__CORTEX_MX__

##
## Add the library to the linker list and list of lib files
##
ifeq ($(call iseeopt, __CORTEX_MX__), yes)
OPT_LIBS += $(CONSOLELIB)
ALL_LIBS += $(CONSOLELIB)
else	# __CORTEX_MX__
OPT_LIBS += -lconsole
ALL_LIBS += libconsole.a
endif	# !__CORTEX_MX__

endif

endif

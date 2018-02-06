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
## Author: 2010 Dario Di Stefano 
##         2012 Giuseppe Serano
##

ifeq ($(call iseeopt, __CORTEX_MX__), yes)

ifneq ($(ENABLE_LIBS), TRUE)

ifeq ($(call iseeopt, __USE_ETHERNET_ENC28J60__), yes)

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/ethernet/enc28j60/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/ethernet/enc28j60/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/ethernet/enc28j60/inc

EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60_hal_ee_cortex_mx.c

endif

endif

else	# __CORTEX_MX__

## Check the ENC28J60 library selection
ifeq ($(findstring __LIB_ENC28J60__,$(LIB_OPT)),__LIB_ENC28J60__)

##
## Application files
##

EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60.c

ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60_hal_ee_mico32.c
endif

ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/drivers/ethernet/enc28j60/src/enc28j60_hal_ee_pic32.c
endif

endif

endif	# __CORTEX_MX__
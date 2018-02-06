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

## Author: 2013 Alessandro Biondi

##Check if is the stack that we're asking for
ifeq ($(call iseeopt, __USE_NRF51422_SYSLIB__), yes)

## Check the library selection
ifeq ($(findstring __LIB_NRF51422_SYSLIB__,$(LIB_OPT)) , __LIB_NRF51422_SYSLIB__)
INCLUDE_NRF51422_SYSLIB = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_NRF51422_SYSLIB = YES
endif

endif

##
## If the library is required
##
ifeq ($(INCLUDE_NRF51422_SYSLIB), YES)


##
## Library code
##
## Add the inc path to the include pathlist
##New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51422/inc
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51422/inc/ant
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51422/inc/ant/softdevice
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51422/inc/app_common
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51422/inc/boards
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51422/inc/ext_sensors

# Common files
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/templates/system_nrf51.c
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/templates/system_nrf51422.c


ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_BUTTON__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/app_common/app_button.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_FIFO__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/app_common/app_fifo.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_GPIOTE__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/app_common/app_gpiote.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_SCHEDULER__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/app_common/app_scheduler.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_TIMER__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/app_common/app_timer.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_UART__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/app_common/app_uart.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_ANT__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ant/ant_app_timer.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_CONSOLE__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/console/console.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_ADNS2080__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/adns2080/adns2080.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_CHERRY8X16__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/cherry8x16/cherry8x16.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_DS1624__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/ds1624/ds1624.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_MPU6050__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/mpu6050/mpu6050.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_NRF6350__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/nRF6350/nRF6350.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_SDIO__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/sdio/sdio.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_SYNAPTICS_TOUCHPAD__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/ext_sensors/synaptics_touchpad/synaptics_touchpad.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_ASSERT__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/nrf_assert/nrf_assert.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_DELAY__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/nrf_delay/nrf_delay.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_ECB__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/nrf_ecb/nrf_ecb.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_NVMC__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/nrf_nvmc/nrf_nvmc.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_SIMPLE_UART__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/simple_uart/simple_uart.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_SPI_MASTER__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/spi_master/spi_master.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51422_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51422_SYSLIB_TWI_MASTER__)), yes) 
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/twi_master/twi_hw_master.c
EE_SRCS_SYSLIB += contrib/nordic/nrf51422/src/twi_master/twi_sw_master.c
endif

## If the file list is not empty, create the lib
ifneq ($(EE_SRCS_SYSLIB),)
EE_OBJS_SYSLIB := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o, $(EE_SRCS_SYSLIB))))
LIBSRCS += $(EE_SRCS_SYSLIB)

NRF51422SYSLIB := libnrf51422_syslib.a

$(NRF51422SYSLIB): $(EE_OBJS_SYSLIB)
	@echo "AR    $(NRF51422SYSLIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^
OPT_LIBS += $(NRF51422SYSLIB)
ALL_LIBS += $(NRF51422SYSLIB)

endif

endif #__USE_NRF51422_SYSLIB__


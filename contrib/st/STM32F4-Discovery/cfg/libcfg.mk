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

## Author: 2012 Carlo Caione
## Author: 2013 Mauro Marinoni

ifeq ($(call iseeopt, __STM32F4xx__), yes)

## Check the STM324F_DISCOVERY library selection
ifeq ($(findstring __LIB_STM32F4_DISCOVERY__,$(LIB_OPT)) , __LIB_STM32F4_DISCOVERY__)
INCLUDE_STM32F4_DISCOVERY = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_STM32F4_DISCOVERY = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_STM32F4_DISCOVERY), YES)

## MM: Why?!?
#EEOPT += USE_STM32F4_DISCOVERY

## MM: StdPeriph deps must be inserted by RT-Druid in the Makefile!!!
EEOPT += __USE_STM32F4XX_SPD_RCC__
EEOPT += __USE_STM32F4XX_SPD_GPIO__
# Extra, to be removed
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_BUTTONS__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_EXTI__
EEOPT += __USE_STM32F4XX_SPD_SYSCFG__
endif
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_COM__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_USART__
endif
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_AUDIO__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_DMA__
EEOPT += __USE_STM32F4XX_SPD_DAC__
EEOPT += __USE_STM32F4XX_SPD_SPI__
EEOPT += __USE_STM32F4XX_SPD_I2C__
endif
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_LCD__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_FSMC__
endif
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_ACCEL__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_SPI__
endif
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_SD__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_DMA__
EEOPT += __USE_STM32F4XX_SPD_SDIO__
endif
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_UART_DEBUG__)), yes) 
EEOPT += __USE_STM32F4XX_SPD_USART__
endif


INCLUDE_PATH += $(EEBASE)/contrib/st/STM32F4-Discovery/inc

## Add each file individually
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/stm32f4_discovery.c

ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_AUDIO__)), yes) 
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/stm32f4_discovery_audio_codec.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_LCD__)), yes) 
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/stm32f4_discovery_lcd.c
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/fonts.c
ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_LCD_LOG__)), yes) 
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/lcd_log.c
endif
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_ACCEL__)), yes) 
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/stm32f4_discovery_lis302dl.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_SD__)), yes) 
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/stm32f4_discovery_sdio_sd.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4_DISCOVERY_ALL__), $(call iseeopt, __USE_STM32F4_DISCOVERY_UART_DEBUG__)), yes) 
EE_SRCS_STM32F4_DISCOVERY += contrib/st/STM32F4-Discovery/src/stm32f4_discovery_debug.c
endif


## Make list of object files and add it to libraries global list
EE_OBJS_STM32F4_DISCOVERY := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(EE_SRCS_STM32F4_DISCOVERY))))
LIBSRCS += $(EE_SRCS_STM32F4_DISCOVERY)

STM32F4DISCOVERYLIB := libstm32f4discovery.a

$(STM32F4DISCOVERYLIB): $(EE_OBJS_STM32F4_DISCOVERY)
	@echo "AR    $(STM32F4DISCOVERYLIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^
OPT_LIBS += $(STM32F4DISCOVERYLIB)
ALL_LIBS += $(STM32F4DISCOVERYLIB)

endif	# INCLUDE_STM32F4_DISCOVERY

endif	# __STM32F4xx__

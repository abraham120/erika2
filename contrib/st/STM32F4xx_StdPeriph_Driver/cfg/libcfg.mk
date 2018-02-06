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

##Check if is a compatible microcontroller
ifeq ($(call iseeopt, __STM32F4xx__), yes)

## Check the STM32F4XX_SPD library selection
ifeq ($(call islibopt,__LIB_STM32F4XX_SPD__), yes)
INCLUDE_STM32F4XX_SPD = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_STM32F4XX_SPD = YES
endif

endif

##
## If the library is required
##
ifeq ($(INCLUDE_STM32F4XX_SPD), YES)

EEOPT += USE_STDPERIPH_DRIVER

##
## Library code
##
## Add the inc path to the include pathlist
##New include mechanism

INCLUDE_PATH += $(EEBASE)/contrib/st/CMSIS/Include
INCLUDE_PATH += $(EEBASE)/contrib/st/CMSIS/Device/STM32F4xx/Include
INCLUDE_PATH += $(EEBASE)/contrib/st/STM32F4xx_StdPeriph_Driver/inc


## Add each file individually
ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_ADC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_CAN__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_CRC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_CRYP__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_CRYP_AES__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_CRYP_DES__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_CRYP_TDES__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_DAC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_DBGMCU__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_DCMI__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_DMA__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_EXTI__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_FLASH__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_FSMC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_GPIO__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_HASH__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_HASH_MD5__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_HASH_SHA1__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_I2C__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_IWDG__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_PWR__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_RCC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_RNG__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_RTC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_SDIO__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_SPI__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_SYSCFG__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_TIM__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_USART__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_WWDG__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
endif

ifeq ($(or $(call iseeopt, __USE_STM32F4XX_SPD_ALL__), $(call iseeopt, __USE_STM32F4XX_SPD_MISC__)), yes) 
EE_SRCS_STM32F4XX_SPD += contrib/st/STM32F4xx_StdPeriph_Driver/src/misc.c
endif





## If the file list is not empty, create the stm32f4xxspd lib
ifneq ($(EE_SRCS_STM32F4XX_SPD),)
EE_OBJS_STM32F4XX_SPD := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o, $(EE_SRCS_STM32F4XX_SPD))))
LIBSRCS += $(EE_SRCS_STM32F4XX_SPD)

STM32F4XXSPDLIB := libstm32f4xxspd.a

$(STM32F4XXSPDLIB): $(EE_OBJS_STM32F4XX_SPD)
	@echo "AR    $(STM32F4XXSPDLIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^
OPT_LIBS += $(STM32F4XXSPDLIB)
ALL_LIBS += $(STM32F4XXSPDLIB)

endif

endif


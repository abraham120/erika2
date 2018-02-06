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

##
## Author:  2011,  Giuseppe Serano
##

##Check if is the stack that we're asking for
ifeq ($(call iseeopt, __AUTOSAR_R4_0__), yes)
## Check the CMSIS library selection
ifeq ($(findstring __LIB_AUTOSAR__,$(LIB_OPT)) , __LIB_AUTOSAR__)
INCLUDE_AUTOSAR = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_AUTOSAR = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_AUTOSAR), YES)

##
## Library code
##
## Add the inc path to the include pathlist
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/as/include

ifeq ($(and $(call iseeopt, __STELLARIS__), $(call iseeopt, __KEIL__)), yes)

INCLUDE_PATH += $(EEBASE)/contrib/as/arch/stellaris/keil/include
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Hardware.c

## Add each file individually
ifeq ($(call iseeopt, __AS_MCU_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Mcu.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Mcu_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Mcu_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Mcu_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_MCU_DRIVER__

ifeq ($(call iseeopt, __AS_PORT_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Port.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Port_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Port_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Port_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_PORT_DRIVER__

ifeq ($(call iseeopt, __AS_DIO_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Dio.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Dio_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Dio_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Dio_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_DIO_DRIVER__

ifeq ($(call iseeopt, __AS_SCI_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Sci.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Sci_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Sci_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Sci_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Sci_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_SCI_DRIVER__

ifeq ($(call iseeopt, __AS_GPT_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Gpt.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Gpt_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Gpt_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Gpt_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Gpt_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_GPT_DRIVER__

ifeq ($(call iseeopt, __AS_DMA_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Dma.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Dma_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Dma_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Dma_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Dma_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_DMA_DRIVER__

ifeq ($(call iseeopt, __AS_SPI_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Spi.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Spi_Irq.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Spi_Handler.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Spi_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Spi_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Spi_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_SPI_DRIVER__

ifeq ($(call iseeopt, __AS_WDG_PIOSC_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/WdgPIOsc.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Wdg_PIOscIrq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Wdg_PIOscCfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Wdg_PIOscCfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Wdg_PIOscCfg.c
endif
endif	# __NO_APP__
endif	# __AS_WDG_PIOSC_DRIVER__

ifeq ($(call iseeopt, __AS_WDG_SYSCLK_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/WdgSysClk.c
EE_SRCS_AUTOSAR += contrib/as/arch/stellaris/keil/drivers/Wdg_SysClkIrq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Wdg_SysClkCfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Wdg_SysClkCfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Wdg_SysClkCfg.c
endif
endif	# __NO_APP__
endif	# __AS_WDG_SYSCLK_DRIVER__

endif # __STELLARIS__ && __KEIL__

ifeq ($(and $(call iseeopt, EE_MPC5643L), $(call iseeopt, __CODEWARRIOR__)), yes)

INCLUDE_PATH += $(EEBASE)/contrib/as/arch/mpc56xx/codewarrior/include
EE_SRCS += contrib/as/arch/mpc56xx/codewarrior/drivers/Hardware.c

ifeq ($(call iseeopt, __AS_MCU_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/mpc56xx/codewarrior/drivers/Mcu.c
endif # __AS_MCU_DRIVER__

ifeq ($(call iseeopt, __AS_PORT_DRIVER__), yes)
EE_SRCS += contrib/as/arch/mpc56xx/codewarrior/drivers/Port.c
endif # __AS_PORT_DRIVER__

ifeq ($(call iseeopt, __AS_GPT_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/mpc56xx/codewarrior/drivers/Gpt.c
EE_SRCS_AUTOSAR += contrib/as/arch/mpc56xx/codewarrior/drivers/Gpt_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Gpt_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Gpt_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Gpt_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_GPT_DRIVER__

endif #EE_MPC5643L && __CODEWARRIOR__

ifeq ($(and $(call iseeopt, __R5F5210x__), $(call iseeopt, __CCRX__)), yes)

INCLUDE_PATH += $(EEBASE)/contrib/as/arch/rx200_5f5210x/ccrx/include

ifeq ($(call iseeopt, __AS_MCU_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Mcu.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Mcu_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Mcu_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Mcu_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_MCU_DRIVER__

ifeq ($(call iseeopt, __AS_PORT_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Port.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Port_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Port_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Port_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_PORT_DRIVER__

ifeq ($(call iseeopt, __AS_DIO_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Dio.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Dio_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Dio_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Dio_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_DIO_DRIVER__

ifeq ($(call iseeopt, __AS_SCI_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Sci.c
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Sci_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Sci_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Sci_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Sci_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_SCI_DRIVER__

ifeq ($(call iseeopt, __AS_GPT_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Gpt.c
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Gpt_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Gpt_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Gpt_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Gpt_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_GPT_DRIVER__

ifeq ($(call iseeopt, __AS_SPI_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Spi.c
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Spi_Irq.c
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Spi_Handler.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Spi_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Spi_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Spi_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_SPI_DRIVER__

ifeq ($(call iseeopt, __AS_WDG_IWDT_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Wdg_IWDT.c
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Wdg_IWDT_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Wdg_IWDT_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Wdg_IWDT_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Wdg_IWDT_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_WDG_IWDT_DRIVER__

ifeq ($(call iseeopt, __AS_WDG_PCLK_DRIVER__), yes)
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Wdg_PCLK.c
EE_SRCS_AUTOSAR += contrib/as/arch/rx200_5f5210x/ccrx/drivers/Wdg_PCLK_Irq.c
ifeq ($(call iseeopt, __NO_APP__), yes)
ifneq ($(filter %Wdg_PCLK_Cfg.c, $(APP_SRCS)),)
EE_SRCS_AUTOSAR += $(filter %Wdg_PCLK_Cfg.c, $(APP_SRCS))
else
EE_SRCS_AUTOSAR += $(OUTBASE)/Wdg_PCLK_Cfg.c
endif
endif	# __NO_APP__
endif	# __AS_WDG_PCLK_DRIVER__

endif	#__R5F5210x__ && __CCRX__

#~ ifeq ($(call iseeopt, __NO_APP__), yes)
#~ EE_SRCS_AUTOSAR += $(filter-out eecfg.c, $(APP_SRCS))
#~ endif
ifeq ($(and $(call iseeopt, __R5F5210x__), $(call iseeopt, __CCRX__)), yes)
EE_OBJS_AUTOSAR := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.obj,$(patsubst %.s,%.obj,$(EE_SRCS_AUTOSAR))))
else	# __R5F5210x__ && __CCRX__
EE_OBJS_AUTOSAR := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(EE_SRCS_AUTOSAR))))
endif	# !(__R5F5210x__ && __CCRX__)

LIBSRCS += $(EE_SRCS_AUTOSAR)

ifeq ($(and $(call iseeopt, __R5F5210x__), $(call iseeopt, __CCRX__)), yes)
AUTOSARLIB := libas.lib

$(AUTOSARLIB): $(EE_OBJS_AUTOSAR)
	@echo "AR    $(AUTOSARLIB)";
	$(QUIET) $(EE_LINK) $(COMPUTED_OPT_AR) -output=$@ $^

OPT_LIBS += -library=$(AUTOSARLIB)
ALL_LIBS += $(AUTOSARLIB)
else	#__R5F5210x__ && __CCRX__
AUTOSARLIB := libas.a

$(AUTOSARLIB): $(EE_OBJS_AUTOSAR)
	@echo "AR    $(AUTOSARLIB)";
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^

	
OPT_LIBS += $(AUTOSARLIB)
ALL_LIBS += $(AUTOSARLIB)
endif	#__R5F5210x__ && __CCRX__

endif	# INCLUDE_AUTOSAR

endif	# __AUTOSAR_R4_0__

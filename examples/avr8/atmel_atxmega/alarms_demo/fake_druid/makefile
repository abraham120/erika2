### fake-druid makefile
#
# Author: 2013  Giuseppe Serano

### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1275



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG

# TODO: Set correct EEOPT.

# MCU
EEOPT += __MCU_EXTENDED_STATUS__

# GPIO
EEOPT += __GPIO_DRIVER__
EEOPT += __GPIO_EXTENDED_STATUS__
EEOPT += __GPIO_READCHANNEL_API__
EEOPT += __GPIO_WRITECHANNEL_API__
EEOPT += __GPIO_FLIPCHANNEL_API__
EEOPT += __GPIO_ENABLENOTIF_API__

# GPT
EEOPT += __GPT_DRIVER__
EEOPT += __GPT_CHANNEL_C_0__
EEOPT += __GPT_CHANNEL_D_0__
EEOPT += __GPT_EXTENDED_STATUS__
EEOPT += __GPT_STOPTIMER_API__
EEOPT += __GPT_ENABLENOTIF_API__

# BOARD
#EEOPT += __BOARD_EXTENDED_STATUS__

# LED
#EEOPT += __LED_DRIVER__
#EEOPT += __LED_PORT_D__
#EEOPT += __LED_EXTENDED_STATUS__


############################################################################
#
# Automatic options
#
############################################################################
ifeq	($(shell uname), Linux)
EEOPT += __RTD_LINUX__
else
EEOPT += __RTD_CYGWIN__
endif
EEOPT += __HAS_TYPES_H__
EEOPT += __AVR8__
EEOPT += __ATXMEGA__
#EEOPT += __ATMEL_STK600__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __ALARMS__
EEOPT += __FP_NO_RESOURCE__
EEOPT += __ALLOW_NESTED_IRQ__
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
ifeq	($(shell uname), Linux)
EEBASE := $(strip ${ERIKA_FILES})
else
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)
endif

else # ERIKA_FILES

ifndef EEBASE
ifeq	($(shell uname), Linux)
	EEBASE := (HOME)/Evidence/eclipse/plugins/com.eu.evidence.ee_2.0.0.20121025_2010/ee_files
else
	EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_2.0.0.20121025_2010\ee_files'`)
endif
else
	$(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=


############################################################################
#
# AVR8
#
############################################################################
APPBASE := ..
OUTBASE := Debug

include $(EEBASE)/pkg/cfg/path_helper.mk
ifeq	($(shell uname), Linux)
$(eval $(call check_and_set_linux_compiler_path,AVR_TOOLS,$(HOME)/avr8-gnu-toolchain))
else
$(eval $(call check_and_set_cygwin_compiler_path,AVR_TOOLS,C:\\Program Files (x86)\\Atmel\\Atmel Toolchain\\AVR8 GCC\\Native\\3.4.2.876\\avr8-gnu-toolchain))
endif

############################################################################
#
# Init MCU for AVR (XMEGA)
#
############################################################################
AVR8_MCU := atxmega16d4

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



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c code.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

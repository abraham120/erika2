### fake-druid makefile
#
# Author: 2014  Giuseppe Serano

### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1277



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ADD_LIBS__
EEOPT += USE_CONSOLE
EEOPT += USE_CONSOLE_SERIAL


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
EEOPT += __AVR8_GCC_C99__
EEOPT += __AVR8__
EEOPT += __ATMEGA__
EEOPT += __IC_USED__
EEOPT += __TIMER_USED__
EEOPT += __TIMER0_CLK_DIV64__
EEOPT += __TIMER_0_USED__
EEOPT += __TIMER1_CLK_DIV64__
EEOPT += __TIMER_1_USED__
EEOPT += __TIMER2_CLK_DIV64__
EEOPT += __TIMER_2_USED__
EEOPT += __TIMER3_CLK_DIV64__
EEOPT += __TIMER_3_USED__
EEOPT += __XBOW_MIB5X0__
EEOPT += __LEDS_USED__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __ALARMS__
EEOPT += __FP_NO_RESOURCE__
#EEOPT += __ALLOW_NESTED_IRQ__
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
$(eval $(call check_and_set_cygwin_compiler_path,AVR_TOOLS,C:\\Program Files (x86)\\Atmel\\Atmel Toolchain\\AVR8 GCC\\Native\\3.4.2.1002\\avr8-gnu-toolch))
endif


############################################################################
#
# Init MCU for AVR (MEGA)
#
############################################################################
AVR8_MCU := atmega128

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

LIB_OPT  += __LIB_ATMEL802154__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c code.c handler.c threads.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

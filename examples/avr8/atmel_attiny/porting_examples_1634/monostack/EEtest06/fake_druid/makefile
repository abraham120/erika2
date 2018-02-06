### fake-druid makefile
#
# Author: 2017  Giuseppe Serano

### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1278



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ASSERT__
EEOPT += __OO_STARTOS_OLD__


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
EEOPT += __AVR8__
EEOPT += __ATTINY__
EEOPT += __TIMER_USED__
EEOPT += __TIMER_0_USED__
EEOPT += __TIMER0_CLK_DIV256__
EEOPT += __OO_BCC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
EEOPT += __OO_AUTOSTART_TASK__
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
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

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
$(eval $(call check_and_set_cygwin_compiler_path,AVR_TOOLS,C:\\Program Files (x86)\\Atmel\\Atmel Toolchain\\AVR8 GCC\\Native\\3.4.2.1002\\avr8-gnu-toolchain))
endif


############################################################################
#
# Init MCU for AVR (MEGA)
#
############################################################################
AVR8_MCU := attiny1634


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

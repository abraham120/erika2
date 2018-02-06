### fake-druid makefile
#
# Author: 2011  Giuseppe Serano

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
EEOPT += __ASSERT__
EEOPT += __ADD_LIBS__
EEOPT += __USE_ATMEL_CMSIS__
EEOPT += __USE_ATMEL_SAM_DEV__
EEOPT += __USE_ATMEL_SAM_DEV_ALL__

EEOPT += __USE_USER_LED__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __GNU__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M3__
EEOPT += __ATMEL_SAM3__
EEOPT += __SAM3X8E__
EEOPT += __OO_BCC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
EEOPT += __OO_AUTOSTART_TASK__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __OO_STARTOS_OLD__
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
EEBASE := ${ERIKA_FILES}
else # ERIKA_FILES

ifndef EEBASE
        EEBASE := /opt/erika/svn/ee
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))

############################################################################
#
# CORTEX MX
#
############################################################################
include $(EEBASE)/pkg/cfg/path_helper.mk
APPBASE := 
OUTBASE := Debug

$(eval $(call check_and_set_linux_compiler_path,GNU_ARM_ROOT,/opt/arm/gcc-arm-none-eabi-4_7-2013q1))

############################################################################
#
# Init MCU for STELLARIC
#
############################################################################
ATMEL_MODEL	:= SAM3X8E


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

LIB_OPT  += __LIB_ATMEL_CMSIS__
LIB_OPT  += __LIB_ATMEL_SAM_DEV__

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

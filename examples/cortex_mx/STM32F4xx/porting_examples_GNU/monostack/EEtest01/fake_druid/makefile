

############################################################################
#
# STM32F4XX_SPD Options
#
############################################################################
EEOPT += __USE_STM32F4XX_SPD__



############################################################################
#
# STM32F4_DISCOVERY Options
#
############################################################################
EEOPT += __USE_STM32F4_DISCOVERY__


EEOPT += __USE_STM32F4_DISCOVERY_LEDS__
EEOPT += __USE_STM32F4XX_SPD_GPIO__
EEOPT += __USE_STM32F4XX_SPD_RCC__
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
EEOPT += __ADD_LIBS__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __STM32__
EEOPT += __STM32F4xx__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M4__
EEOPT += __GNU__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCE__
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
        EEBASE := /Users/DeusExMachina/Documents/area_lavoro/eclipseMAC/plugins/com.eu.evidence.ee_2.3.0.N20140424_1122/ee_files
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))


############################################################################
#
# CORTEX M0
#
############################################################################
-include $(EEBASE)/pkg/cfg/path_helper.mk
APPBASE := ..
OUTBASE := Debug

$(eval $(call check_and_set_linux_compiler_path,GNU_ARM_ROOT,/Users/DeusExMachina/Documents/area_lavoro/gcc-arm-none-eabi-4_7-2013q3/))


############################################################################
#
# Init MCU for CORTEX Mx (STM32F4xx)
#
############################################################################
STM32_MODEL           := STM32F4xx


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

LIB_OPT  += __LIB_ST_CMSIS__
LIB_OPT  += __LIB_STM32F4XX_SPD__
LIB_OPT  += __LIB_STM32F4_DISCOVERY__


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

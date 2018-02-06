
# Configuration for CORTEX_MX
EEOPT += __STM32__
EEOPT += __STM32F4xx__
STM32_MODEL           := STM32F4xx


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
EEOPT += __OO_STARTOS_OLD__
EEOPT += __ADD_LIBS__
EEOPT += __USE_STM32F4XX_CMSIS__
EEOPT += __USE_STM32F4XX_SPD__
EEOPT += __USE_STM32F4XX_EVAL__
EEOPT += __USE_SYSTICK__
EEOPT += __USE_SPD_TIM__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M4__
EEOPT += __KEIL__
EEOPT += __OO_BCC2__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
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
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Users\CC\Desktop\ee'`)
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
APPBASE := 
OUTBASE := Debug

ifndef ARM_ROOT
    ARM_ROOT := $(shell cygpath `cygpath -ms 'C:\Keil\ARM'`)
endif



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

LIB_OPT  += __LIB_CMSIS__
LIB_OPT  += __LIB_SPD__
LIB_OPT  += __LIB_EVAL__


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

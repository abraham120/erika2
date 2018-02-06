### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1276



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ASSERT__
EEOPT += __ADD_LIBS__
EEOPT += __USE_LPC12XX_CMSIS_V2__
EEOPT += __USE_CMSIS_IOCON__
EEOPT += __USE_CMSIS_SYSCTRL__
EEOPT += __USE_CMSIS_GPIO__
EEOPT += __USE_CMSIS_TIMER16__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __LPCXPRESSO__
EEOPT += __LPC12xx__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M0__
EEOPT += __C_M0_IAR_J_LINK__
EEOPT += __IAR__
EEOPT += __FP__
EEOPT += __IRQ_STACK_NEEDED__
EEOPT += __MULTI__
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
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\RT-Druid\plugins\com.eu.evidence.ee_1.6.0.20111221_1001\ee_files'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=


############################################################################
#
# CORTEX M0
#
############################################################################
APPBASE := ..
OUTBASE := Output

ifndef IAR_CCDIR
    IAR_CCDIR := $(shell cygpath `cygpath -ms 'C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm'`)
endif



############################################################################
#
# Init MCU for CORTEX Mx (LPC12xx)
#
############################################################################
LPCXPRESSO_MODEL           := LPC12xx


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

### Setting Erika's variables:
# EEBASE = ../../..
# APPBASE = .
# 
# EEOPT =



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

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M0__
EEOPT += __IAR__
EEOPT += __C_M0_IAR_J_LINK__
EEOPT += __LPCXPRESSO__
EEOPT += __LPC12xx__
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
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_1.6.0.20111119_0157\ee_files'`)
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
OUTBASE := .

ifndef IAR_CCDIR
#TODO: cambiare opportunamente
#IAR_CCDIR := $(shell $(EEBASE)/pkg/cfg/arch/cc_cortex_m0_detect.sh ASM "c:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm")
    IAR_CCDIR := $(shell cygpath `cygpath -ms "c:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm"`)
endif

############################################################################
#
# Init MCU for CORTEX Mx (LPC12xx)
#
############################################################################
LPCXPRESSO_MODEL           := LPC12xx
LPCXPRESSO_LINKERSCRIPT    := lpc12xx_flash.icf
LPCXPRESSO_INCLUDE_C       := LPC12xx.h
LPCXPRESSO_INCLUDE_S       := ?
LPCXPRESSO_STARTUP       := ?

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

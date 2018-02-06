
# Configuration for CORTEX_MX
EEOPT += __NORDIC__
EEOPT += __NRF51X22__



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
EEOPT += __USE_NRF51822_SYSLIB__

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M0__
EEOPT += __KEIL__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCES__
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
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Users\Alessandro\Documenti\ee_VM\ee'`)
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

LIB_OPT += __LIB_NRF51822_SYSLIB__
OPT_CC 	+= -DBOARD_PCA10001



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

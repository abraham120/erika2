### fake-druid makefile
#
# Author: 2011  Giuseppe Serano

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
EEOPT += __ASSERT__
EEOPT += __USE_USER_LED__

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __STELLARIS__
EEOPT += __LM4F232xxxx__
EEOPT += __CORTEX_MX__
EEOPT += __CORTEX_M4__
EEOPT += __CCS__
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
# CORTEX M4
#
############################################################################
APPBASE := ..
OUTBASE := .

ifndef CCS_INSTALL_ROOT
    CCS_INSTALL_ROOT := $(shell cygpath `cygpath -ms 'C:\Programmi\Texas Instruments\ccsv4'`)
endif



############################################################################
#
# Init MCU for CORTEX Mx (LM4F232xxxx)
#
############################################################################
STELLARIS_MODEL           := LM4F232xxxx


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

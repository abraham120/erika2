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
EEOPT += NODEPS
EEOPT += __ASSERT__
EEOPT += __SEM__
EEOPT += __RSKRX210__
EEOPT += __USE_RSKRX120_USER_LED__
EEOPT += __USE_RSKRX210_OP_FREQ_SETUP__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __RX200__
EEOPT += __CCRX__
EEOPT += __R5F5210x__
EEOPT += __FP__
EEOPT += __MULTI__
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
# RENESAS RX200
#
############################################################################
APPBASE := ..
OUTBASE := .

ifndef CCRX_ROOT
    CCRX_ROOT := $(shell cygpath `cygpath -ms 'C:\Programmi\Renesas\Hew\Tools\Renesas\RX\1_2_0'`)
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
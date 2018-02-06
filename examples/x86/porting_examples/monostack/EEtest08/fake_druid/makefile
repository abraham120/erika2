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


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __X86__
EEOPT += __USE_UART__
EEOPT += __FP__
EEOPT += __MONO__
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
EEBASE := $(ERIKA_FILES)

else # ERIKA_FILES

ifndef EEBASE
    EEBASE := /srv/scratch/hoffmann/erika/ee_git
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=


############################################################################
#
# Freescale S12
#
############################################################################
APPBASE := ..
OUTBASE := Debug

############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -I. -ggdb
ASFLAGS +=
LDFLAGS +=
LDDEPS  +=
LIBS    +=



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c $(APPBASE)/code.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

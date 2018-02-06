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
EEOPT += __CODEWARRIOR__
EEOPT += CW_EVAL_VERSION


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CODEWARRIOR__
EEOPT += __HCS12XS__
EEOPT += __MC9S12XS128__
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
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse_160_old\plugins\com.eu.evidence.ee_1.6.0.20111115_1040\ee_files'`)
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

ifndef COSMIC_ASMDIR
COSMIC_ASMDIR := $(shell cygpath `cygpath -ms 'c:\Programmi\Freescale\CWS12v5.1'`)
endif
ifndef COSMIC_CCDIR
COSMIC_CCDIR := $(shell cygpath `cygpath -ms 'c:\Programmi\Freescale\CWS12v5.1'`)
endif


############################################################################
#
# Init MCU for S12 (CUSTOM)
#
############################################################################
COSMIC_MODEL           := MC9S12XS128
COSMIC_LINKERSCRIPT    := ../SofTec_HCS12_linker.prm
COSMIC_INCLUDE_H       := mc9s12xs128.h
COSMIC_INCLUDE_C       := mc9s12xs128.c


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -D__FAR_DATA
ASFLAGS += 
LDFLAGS += -addansixbi.lib
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c Start12.c $(COSMIC_INCLUDE_C) $(COSMIC_INCLUDE_S) main.c Vectors.c CPU12ISRs.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

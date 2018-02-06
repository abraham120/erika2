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
EEOPT += __S12XS_INCLUDE_REGS__
EEOPT += __CODEWARRIOR__
EEOPT += CW_EVAL_VERSION

############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __CODEWARRIOR__
EEOPT += __MC9S12__
EEOPT += __USE_SCI__
EEOPT += __USE_TIMER__
EEOPT += __MC9S12G128__
EEOPT += __TWRS12G128__
EEOPT += __USE_BUTTONS__
EEOPT += __USE_LEDS__
EEOPT += __OO_BCC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
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
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Dario\EE_svn\repos\ee\trunk\ee'`)
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
APPBASE := 
OUTBASE := Debug

ifndef S12_ASMDIR
S12_ASMDIR := $(shell cygpath `cygpath -ms 'c:\Programmi\Freescale\CWS12v5.1'`)
endif
ifndef S12_CCDIR
S12_CCDIR := $(shell cygpath `cygpath -ms 'c:\Programmi\Freescale\CWS12v5.1'`)
endif


############################################################################
#
# Init MCU for S12 (MC9S12G128)
#
############################################################################
S12_MODEL           := MC9S12G128
S12_LINKERSCRIPT    := 
S12_INCLUDE_H       := mc9s12g128.h
S12_INCLUDE_C       := mc9s12g128.c
S12_INCLUDE_S       := 


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -D__FAR_DATA -Onf
ASFLAGS += 
LDFLAGS += -addansibi.lib
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c $(S12_INCLUDE_C) $(S12_INCLUDE_S) main.c Vectors.c CPU12ISRs.c Start12.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

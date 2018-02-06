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
EEOPT += __S12XS_INCLUDE_REGS__
EEOPT += __EE_STDINT_SKIP_64BIT__
EEOPT += __ADD_LIBS__
EEOPT += USE_CONSOLE
EEOPT += USE_CONSOLE_SERIAL


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __COSMIC__
EEOPT += __HCS12XS__
EEOPT += __USE_SCI__
EEOPT += __USE_PIT__
EEOPT += __MC9S12XS128__
EEOPT += __DEMO9S12XSFAME__
EEOPT += __USE_POTENTIOMETER__
EEOPT += __USE_ADC__
EEOPT += __USE_BUTTONS__
EEOPT += __USE_LEDS__
EEOPT += __USE_LIGHT_SENSOR__
EEOPT += __OO_BCC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
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
COSMIC_ASMDIR := $(shell cygpath `cygpath -ms 'c:\Programmi\COSMIC\EVAL12X'`)
endif
ifndef COSMIC_CCDIR
COSMIC_CCDIR := $(shell cygpath `cygpath -ms 'c:\Programmi\COSMIC\EVAL12X'`)
endif


############################################################################
#
# Init MCU for S12 (CUSTOM)
#
############################################################################
COSMIC_MODEL           := MC9S12XS128
COSMIC_LINKERSCRIPT    := ../mc9s12xs128.lkf
COSMIC_INCLUDE_H       := ioxs256.h
COSMIC_INCLUDE_C       := vector_s12x.c
COSMIC_INCLUDE_S       := crtsx.S


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -l +modf +fast +nowiden +warn +sprec
ASFLAGS += -c -v -l 
LDFLAGS += -p -sa -m mapfile.map
LDDEPS  += 
LIBS    += 

LIB_OPT  += __LIB_CONSOLE__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c $(COSMIC_INCLUDE_C) $(COSMIC_INCLUDE_S) main.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

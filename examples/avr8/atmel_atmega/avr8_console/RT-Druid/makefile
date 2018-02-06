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
EEOPT += __LEDS_USED__
EEOPT += __ADD_LIBS__
EEOPT += __USE_UART__
EEOPT += USE_CONSOLE
EEOPT += USE_CONSOLE_SERIAL


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __AVR5__
EEOPT += __ATMEGA128__
EEOPT += __TIMER0_CLK_DIV32__
EEOPT += __TIMER_0_USED__
EEOPT += __TIMER1_CLK_DIV256__
EEOPT += __TIMER_1_USED__
EEOPT += __TIMER2_CLK_DIV64__
EEOPT += __TIMER_2_USED__
EEOPT += __TIMER3_CLK_DIV64__
EEOPT += __TIMER_3_USED__
EEOPT += __TIMER_USED__
EEOPT += __XBOW_MIB5X0__ 
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __ALARMS__
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
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_2.1.0.20130704_2011\ee_files'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))


############################################################################
#
# AVR 5
#
############################################################################
APP_SRCS += handler_install.S 

include $(EEBASE)/pkg/cfg/path_helper.mk
APPBASE := ..
OUTBASE := RT-Druid

$(eval $(call check_and_set_cygwin_compiler_path,AVR5_DIR,C:\programmi\AVRGCC\avrgcc))
AVR5_MODEL := atmega128



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

LIB_OPT  += __LIB_CONSOLE__


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

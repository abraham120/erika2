# these lines override the .bashrc definitions
#EEBASE = ../../..
#APPBASE = .

###
### Setting EEOPT variable:
###

EEOPT =


############################################################################
#
# User options
#
############################################################################


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __MSP430__
EEOPT += __UTMOST__
EEOPT += __MSP430_1611__
EEOPT += __MONO__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __OO_BCC2__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __USE_LEDS__
#EEOPT += __OO_NO_ALARMS__
#EEOPT += __OO_NO_RESOURCES__
#EEOPT += __OO_AUTOSTART_TASK__
EEOPT += __OO_STARTOS_OLD__

ifndef EEBASE
    EEBASE  := /extra/eclipse/plugins/com.eu.evidence.ee_1.0.0.201002181432/ee_base
endif
APPBASE := ..
OUTBASE := output



############################################################################
#
# Flags
#
############################################################################
CFLAGS  +=-g2
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += $(OUTBASE)/eecfg.c main.c



############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

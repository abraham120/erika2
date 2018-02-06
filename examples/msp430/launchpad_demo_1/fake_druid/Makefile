
# Configuration for MSP430
EEOPT += __MSP430__

ifndef EEBASE
EEBASE  := /home/steve/Evidence/eclipse/plugins/com.eu.evidence.ee_1.6.0.201101311103/ee_base
endif

APPBASE := .
OUTPUT_DIR := output




CFLAGS  += -mmcu=msp430x2012
ASFLAGS += -mmcu=msp430x2012
LDFLAGS += -mmcu=msp430x2012
#
### Setting Erika's variables:
# EEBASE = ../../..
# APPBASE = .
# 
# EEOPT =


EEOPT += __MSP430_LAUNCHPAD__
EEOPT += __USE_LEDS__
EEOPT += __USE_BUTTONS__

EEOPT += __RTD_LINUX__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCES__

CFLAGS  += -g2
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 


APP_SRCS += $(OUTPUT_DIR)/eecfg.c main.c

include $(EEBASE)/pkg/cfg/rules.mk

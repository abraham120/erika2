# # Date             : 1/18/2010
# RT-Druid version : 
#

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
EEOPT += DEBUG
EEOPT += NODEPS


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __ESI_RISC__
EEOPT += __USE_LEDS__
EEOPT += __USE_TIMERS__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCES__


############################################################################
#
# EnSilica eSi-RISC
#
############################################################################
EEBASE  := $(shell cygpath `cygpath -ms "C:\Projects\P001110\MAIN\code\ee"`)
APPBASE := 
OUTBASE := Debug

TARGET_OPTIONS := -msoc=esi3200_cycloneiiidemo -O2

############################################################################
#
# Flags
#
############################################################################
CFLAGS += $(TARGET_OPTIONS)
ASFLAGS += $(TARGET_OPTIONS)
LDFLAGS += $(TARGET_OPTIONS)
LDDEPS  += 
LIBS    += 

# Link in the lightweight startup code for a smaller final image
LDFLAGS +=  -mcrt0s



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c main.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

# ALARMS Test Makefile
# 
# by Paolo Gai 2002
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 

# Compiling options
#EEOPT = __ST10__

EEOPT = __ARM7GNU__ DEBUG __LEDS_USED__  __EVALUATOR7T__

#EEOPT = __H8__ __LCD_USED__ __PLAY_NOTE_SUPPORT__

EEOPT += __MONO__ __FP__ __ALARMS__ __FP_NO_MUTEX__

#
# --------------------------------------------------------------------------
#

# architecture independent part
APP_SRCS = code.c initkern.c

# architecture dependent part
ifeq ($(findstring __ARM7GNU__,$(EEOPT)) , __ARM7GNU__)
APP_SRCS += initarm7.c
THUMB_SRCS=
endif

ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS += initst10.c
endif

ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
APP_SRCS += inith8.c set_hand.s
endif

#
# --------------------------------------------------------------------------
#

include $(EEBASE)/config/config.mak

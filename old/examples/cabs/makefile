# CABS Test Makefile
# 
# by Paolo Gai 2001-2002
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 

# Compiling options
#EEOPT = __ST10__ 
#EEOPT = __ST10__ __ST10_OPTIMIZED__
EEOPT = __ARM7GNU__ __TIMER_1_USED__ DEBUG __LEDS_USED__ __TIMER_0_USED__ __EVALUATOR7T__
#EEOPT = __ARM7ADS__ __TIMER_1_USED__ DEBUG __LEDS_USED__ __TIMER_0_USED__
#EEOPT = __H8__ __TIMER_A_USER_FUNCTION_USED__ __LCD_USED__

EEOPT += __MONO__ __EDF__ __CABS__


#
# --------------------------------------------------------------------------
#

# architecture independent part
APP_SRCS = code.c initkern.c mycabs.c

ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS += handst10.asm irq_st10.c initst10.c
endif

ifeq ($(findstring __ARM7GNU__,$(EEOPT)) , __ARM7GNU__)
APP_SRCS += initarm7.c irq_arm7.c
THUMB_SRCS=
endif

ifeq ($(findstring __ARM7ADS__,$(EEOPT)) , __ARM7ADS__)
APP_SRCS += initarm7.c irq_arm7.c
THUMB_SRCS=
endif

ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
APP_SRCS += inith8.c irq_h8.c set_hand.s
endif

#
# --------------------------------------------------------------------------
#

include $(EEBASE)/config/config.mak

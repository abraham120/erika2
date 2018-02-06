# HARD ALARMS Test Makefile
# 
# by Bertozzi Francesco 2002
#

# Compiling options
EEOPT = __ST10___

EEOPT += __MONO__ __FP__ __HARD_ALARMS__ __FP_NO_MUTEX__

#
# --------------------------------------------------------------------------
#

# architecture independent part
APP_SRCS = code.c initkern.c

# architecture dependent part
ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS += initst10.c st10timer.asm
endif

#
# --------------------------------------------------------------------------
#

include $(EEBASE)/config/config.mak

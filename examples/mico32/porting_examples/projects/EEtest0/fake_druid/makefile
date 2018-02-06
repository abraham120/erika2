# # Date             : 3/14/2011
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


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __LM32__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCES__


############################################################################
#
# Lattice mico 32
#
############################################################################
ifndef EEBASE
    EEBASE  := ../../../../..
endif
APPBASE := ..
OUTBASE := output



############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -g2
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
# More rules for Lattice mico 32
#
############################################################################
#include $(OUTPUT_DIR)/platform.mk
PLATFORM_NAME=onchipramtimer
PLATFORM_LIB_PATH=../onchipramtimer_lib
PLATFORM_BLD_CFG=Release
#include $(OUTPUT_DIR)/lattice.mk
# Use standalone printf implementation: -D_USE_LSCC_PRINTF_
CFLAGS += -D_USE_LSCC_PRINTF_
# C library to use.
C_LIB := -lc



############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

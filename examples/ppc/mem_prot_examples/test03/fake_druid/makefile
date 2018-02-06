### Setting Erika's variables:
# EEBASE = ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1253



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += EE_ISR_DYNAMIC_TABLE


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __PPCE200ZX__
EEOPT += __MPC5674F__
EEOPT += __PPCE200Z7__
EEOPT += __DIAB__
EEOPT += __EE_MEMORY_PROTECTION__
EEOPT += __EE_USE_MMU__
EEOPT += __OO_ECC2__
EEOPT += __AS_SC4__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MULTI__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
EEOPT += __OO_NO_EVENTS__
EEOPT += __OO_AUTOSTART_TASK__


############################################################################
#
# Freescale MPC5674F, PPC E200Z7
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
CFLAGS  += -Xsmall-data=0
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c code.c app1.c app2.c trusted.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

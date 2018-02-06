### Setting Erika's variables:
# EEBASE = ../../..
# APPBASE = .
# 
# EEOPT =



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __E200ZX_EXECUTE_FROM_RAM__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __PPCE200ZX__
EEOPT += __MPC5674F__
EEOPT += __PPCE200Z7__
EEOPT += __VLE__
EEOPT += __DIAB__
EEOPT += __OO_ORTI_RUNNINGISR2__
EEOPT += __OO_ORTI_LASTERROR__
EEOPT += __OO_ORTI_SERVICETRACE__
EEOPT += __OO_ORTI_PRIORITY__
EEOPT += __OO_ORTI_RES_LOCKER_TASK__
EEOPT += __OO_ORTI_RES_ISLOCKED__
EEOPT += __OO_ORTI_STACK__
EEOPT += __OO_ORTI_ALARMTIME__
EEOPT += __OO_BCC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
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
CFLAGS  += 
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



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

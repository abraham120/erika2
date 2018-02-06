

############################################################################
#
# Makefile created by RT-Druid
# 
# Cpu 0(master)
#
############################################################################

# Include common informations
include ../common.mk

# Base dir
APPBASE ?= ../..


############################################################################
#
# EE options
#
############################################################################
EEOPT += 
EEOPT += __PPCE200Z6__
EEOPT += __VLE__
EEOPT += __DIAB__
EEOPT += __OO_ORTI_LASTERROR__
EEOPT += __OO_ORTI_SERVICETRACE__
EEOPT += __OO_ORTI_PRIORITY__
EEOPT += __OO_ORTI_RES_LOCKER_TASK__
EEOPT += __OO_ORTI_RES_ISLOCKED__
EEOPT += __OO_ORTI_STACK__
EEOPT += __OO_ORTI_ALARMTIME__
EEOPT += __RN__
EEOPT += __RN_TASK__
EEOPT += __OO_NO_ALARMS__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS +=  common.c master.c eecfg.c


############################################################################
#
# Default rules
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk


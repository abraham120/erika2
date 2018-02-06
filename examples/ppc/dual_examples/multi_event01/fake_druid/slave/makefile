

############################################################################
#
# Makefile created by RT-Druid
# 
# Cpu 1(slave)
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
EEOPT += USE_PRAGMAS
EEOPT += __PPCE200Z0__
EEOPT += __VLE__
EEOPT += __DIAB__
EEOPT += __OO_ORTI_RES_LOCKER_TASK__
EEOPT += __OO_ORTI_RES_ISLOCKED__
EEOPT += __OO_ORTI_STACK__
EEOPT += __OO_ORTI_ALARMTIME__
EEOPT += __OO_ORTI_ISR2__
EEOPT += __RN__
EEOPT += __RN_EVENT__
EEOPT += __RN_TASK__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_AUTOSTART_TASK__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS +=  slave.c eecfg.c


############################################################################
#
# Default rules
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk


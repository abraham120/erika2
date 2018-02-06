## Author: 2011 Antonio Marcello Catinella
## Check the cal library selection
ifeq ($(findstring __LIB_CAL__,$(LIB_OPT)),__LIB_CAL__)

SYS_ACTORS=art_switch.c art_led.c

include $(EEBASE)/contrib/cal/cfg/actors.mk

EE_SRCS += $(EEBASE)/contrib/cal/src/actors-rts.c
EE_SRCS += $(EEBASE)/contrib/cal/src/ee_cal.c

INCLUDE_PATH += $(EEBASE)/contrib/cal/inc

endif

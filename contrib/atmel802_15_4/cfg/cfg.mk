## Author: 2007 Antonio Romano
## CVS: $Id:


ifeq ($(findstring __LIB_ATMEL802154__,$(LIB_OPT)),__LIB_ATMEL802154__)

##
## Application files
##

ifeq ($(call iseeopt, __AT86RF230__), yes)

EE_SRCS +=      

endif

##
## Add atmel802.15.4 to the linker list of libs
##

OPT_LIBS += -lZigbEE

endif

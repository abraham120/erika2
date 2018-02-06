## Author: 2011 Riccardo Schiavi
## Check the selection


ifeq ($(findstring __LIB_TCPIP__,$(LIB_OPT)) , __LIB_TCPIP__)

##
## Application files
## 

SRCS += $(addprefix contrib/microchip/tcpip_531/libsrc/, $(notdir $(shell ls -1 $(EEBASE)/contrib/microchip/tcpip_531/libsrc/*.c | grep -v PIC32)))
SRCS += $(addprefix contrib/microchip/tcpip_531/libsrc/WiFi/, $(notdir $(shell ls -1 $(EEBASE)/contrib/microchip/tcpip_531/libsrc/WiFi/*.c)))

ifeq ($(call iseeopt, __PIC32__), yes)
SRCS += $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/*.c | grep -e PIC32)
endif


endif

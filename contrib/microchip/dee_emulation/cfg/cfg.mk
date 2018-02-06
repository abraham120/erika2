## Author: 2009 Francesco Prosperi
## Check the Touch library selection
ifeq ($(findstring __LIB_DEE_EMULATION__,$(LIB_OPT)),__LIB_DEE_EMULATION__)

##
## Application files
##

EE_SRCS += contrib/microchip/dee_emulation/src/dee_emulation_16-bit.c
EE_SRCS += contrib/microchip/dee_emulation/src/dee_emulation_flash_operations.S

endif

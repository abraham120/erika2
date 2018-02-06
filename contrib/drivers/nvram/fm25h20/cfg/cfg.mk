## Author: 2010 Christian Nastasi

## Check the FM25H20 library selection
ifeq ($(findstring __LIB_FM25H20__,$(LIB_OPT)),__LIB_FM25H20__)

##
## Application files
##

### Common library files
EE_SRCS += contrib/drivers/nvram/fm25h20/src/fm25h20.c

### Select the specific architecture files
ifeq ($(call iseeopt, __MICROCHIP_PIC32__), yes)
EE_SRCS += contrib/drivers/nvram/fm25h20/src/fm25h20_hal_ee_pic32.c
endif

endif

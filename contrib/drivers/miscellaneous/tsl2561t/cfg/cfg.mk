## Author: 2010 Christian Nastasi

## Check the FM25H20 library selection
ifeq ($(findstring __LIB_TSL2561T__,$(LIB_OPT)),__LIB_TSL2561T__)

##
## Application files
##

### Common library files
EE_SRCS += contrib/drivers/miscellaneous/tsl2561t/src/tsl2561t.c

### Select the specific architecture files
ifeq ($(call iseeopt, __MICROCHIP_PIC32__), yes)
EE_SRCS += contrib/drivers/miscellaneous/tsl2561t/src/tsl2561t_hal_ee_pic32.c
endif

ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/drivers/miscellaneous/tsl2561t/src/tsl2561t_hal_ee_mico32.c
endif

endif

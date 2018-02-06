## Author: 2010 Dario Di Stefano

## Check the library selection
ifeq ($(findstring __LIB_PCF8583__,$(LIB_OPT)),__LIB_PCF8583__)

##
## Application files
##

### Common library files
EE_SRCS += contrib/drivers/miscellaneous/pcf8583/src/pcf8583.c

endif

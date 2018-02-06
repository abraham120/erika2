## Author: 2009 Francesco Prosperi

## Check the Amazing library selection
ifeq ($(findstring __LIB_AMAZING__,$(LIB_OPT)),__LIB_AMAZING__)

##
## Application files
##

EE_SRCS += contrib/amazing/src/amazing.c

endif

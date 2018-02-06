## Author: 2010 Dario Di Stefano
## Check the selection

ifeq ($(findstring __LIB_TCPIP__,$(LIB_OPT)) , __LIB_TCPIP__)

##
## Application files
##
EE_SRCS += 

endif

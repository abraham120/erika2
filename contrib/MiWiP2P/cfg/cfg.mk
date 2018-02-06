## Author: 2009 Gianluca Franchino

## Check the MIWIP2P library selection
ifeq ($(findstring __LIB_MIWIP2P__,$(LIB_OPT)),__LIB_MIWIP2P__)

##
## Library files
##

EE_SRCS_MIWIP2P_COMMON := $(addprefix contrib/MiWiP2P/libsrc/, $(notdir $(shell ls -1 $(EEBASE)/contrib/MiWiP2P/libsrc/*.c)))
EE_SRCS += $(EE_SRCS_MIWIP2P_COMMON)

endif


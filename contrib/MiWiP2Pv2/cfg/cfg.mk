## Author: 2010 Gianluca Franchino

## Check the MIWIP2Pv2 library selection
ifeq ($(findstring __LIB_MIWIP2P_V2__,$(LIB_OPT)),__LIB_MIWIP2P_V2__)

##
## Library files
##

#EE_SRCS_MIWIP2P_COMMON := $(addprefix contrib/MiWiP2P/libsrc/, $(notdir $(shell ls -1 $(EEBASE)/contrib/MiWiP2P/libsrc/*.c)))
#EE_SRCS += $(EE_SRCS_MIWIP2P_COMMON)

#EE_SRCS += contrib/MiWiP2Pv2/libsrc/Common/radio_spi.c
EE_SRCS += contrib/MiWiP2Pv2/libsrc/Common/serv_funct.c
EE_SRCS += contrib/MiWiP2Pv2/libsrc/Common/SymbolTime.c
EE_SRCS += contrib/MiWiP2Pv2/libsrc/P2P/P2P.c
EE_SRCS += contrib/MiWiP2Pv2/libsrc/Transceivers/MRF24J40/MRF24J40.c
EE_SRCS += contrib/MiWiP2Pv2/libsrc/Transceivers/crc.c
EE_SRCS += contrib/MiWiP2Pv2/libsrc/Transceivers/security.c

endif


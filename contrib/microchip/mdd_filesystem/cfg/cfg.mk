## Author: 2011 Gianluca Franchino

## Check the mdd_filesystem library selection
ifeq ($(findstring __LIB_MDD_FILESYSTEM__,$(LIB_OPT)),__LIB_MDD_FILESYSTEM__)

##
## Library files
##

#EE_SRCS_MDD_FILESYSTEM_COMMON := $(addprefix contrib/mdd_filesystem/libsrc/, $(notdir $(shell ls -1 $(EEBASE)/contrib/microchip/mdd_filesystem/libsrc/*.c)))
#EE_SRCS += $(EE_SRCS_MDD_FILESYSTEM_COMMON)

#EE_SRCS += "contrib/mdd_filesystem/libsrc/CF-Bit transaction.c" #REMOVE the blank in the file name!
#EE_SRCS += contrib/mdd_filesystem/libsrc/CF-PMP
#EE_SRCS += "contrib/mdd_filesystem/libsrc/Interanl Flash.c" #REMOVE the blank in the file name!
EE_SRCS += contrib/microchip/mdd_filesystem/libsrc/FSIO.c
EE_SRCS += contrib/microchip/mdd_filesystem/libsrc/SD-SPI.c

endif


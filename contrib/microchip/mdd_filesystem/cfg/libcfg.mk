## Author: Gianluca Franchino 1/18/2011

## Check the MDD_FILESYSTEM library selection
ifeq ($(findstring __LIB_MDD_FILESYSTEM__,$(LIB_OPT)) , __LIB_MDD_FILESYSTEM__)
INCLUDE_MDD_FILESYSTEM = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(findstring __BUILD_ALL_LIBS__,$(EEOPT)) , __BUILD_ALL_LIBS__)
INCLUDE_MDD_FILESYSTEM = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_MDD_FILESYSTEM), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(findstring __RTD_CYGWIN__,$(EEOPT)), __RTD_CYGWIN__) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/microchip/mdd_filesystem/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/microchip/mdd_filesystem/inc
endif
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/microchip/mdd_filesystem/inc

## Add each file individually
EE_SRCS_MDD_FILESYSTEM +=

## If the file list is not empty, create the mdd_filesystem lib
ifneq ($(EE_SRCS_MDD_FILESYSTEM),)

EE_OBJS_MDD_FILESYSTEM := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_MDD_FILESYSTEM))))

LIBSRCS += $(EE_SRCS_MDD_FILESYSTEM)

libmiwip2pv2.a: $(EE_OBJS_MDD_FILESYSTEM)
    @echo $(EE_SRC_MDD_FILESYSTEM)
    @printf "AR  libmdd_fs.a\n" ;
    $(QUIET)$(EE_AR) rs libmdd_fs.a $(EE_OBJS_MDD_FILESYSTEM)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lmdd_fs
ALL_LIBS += libmdd_fs.a

endif

endif

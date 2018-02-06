## Author: Gianluca Franchino 3/11/2010

## Check the MiWiP2Pv2 library selection
ifeq ($(findstring __LIB_MIWIP2P_V2__,$(LIB_OPT)) , __LIB_MIWIP2P_V2__)
INCLUDE_MIWIP2P_V2 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_MIWIP2P_V2 = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_MIWIP2P_V2), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/MiWiP2Pv2/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/MiWiP2Pv2/inc
endif
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/MiWiP2Pv2/inc

## Add each file individually
EE_SRCS_MIWIP2P_V2 +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_MIWIP2P_V2),)

EE_OBJS_MIWIP2P := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_MIWIP2P_V2))))

LIBSRCS += $(EE_SRCS_MIWIP2P_V2)

libmiwip2pv2.a: $(EE_OBJS_MIWIP2P_V2)
    @echo $(EE_SRC_MIWIP2P_V2)
    @printf "AR  libmiwip2pv2.a\n" ;
    $(QUIET)$(EE_AR) rs libmiwip2pv2.a $(EE_OBJS_MIWIP2P_V2)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lmiwip2pv2
ALL_LIBS += libmiwip2pv2.a

endif

endif

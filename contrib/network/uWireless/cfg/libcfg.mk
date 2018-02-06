## Author: 2007 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_UWIRELESS__,$(LIB_OPT)) , __LIB_UWIRELESS__)
INCLUDE_UWIRELESS = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_UWIRELESS = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_UWIRELESS), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/network/uWireless/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/network/uWireless/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/network/uWireless/inc

## Add each file individually
#EE_SRCS_uWireless += contrib/network/libsrc/libuWireless.c
EE_SRCS_UWIRELESS +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_UWIRELESS),)

EE_OBJS_UWIRELESS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_UWIRELESS))))

LIBSRCS += $(EE_SRCS_UWIRELESS)

libuWireless.a: $(EE_OBJS_UWIRELESS)
	@echo $(EE_SRC_UWIRELESS)
	@printf "AR  libuWireless.a\n" ;
	$(QUIET)$(EE_AR) rs libuWireless.a $(EE_OBJS_UWIRELESS)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -luWireless
ALL_LIBS += libuWireless.a

endif

endif

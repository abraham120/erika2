## Author: 2007 Mauro Marinoni

## Check the CC2420 library selection
ifeq ($(findstring __LIB_CC2420__,$(LIB_OPT)) , __LIB_CC2420__)
INCLUDE_CC2420 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_CC2420 = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_CC2420), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/radio/cc2420/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/radio/cc2420/inc
endif
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/drivers/radio/cc2420/inc

## Add each file individually
#EE_SRCS_CC2420 += contrib/drivers/radio/cc2420/libsrc/libcc2420.c
EE_SRCS_CC2420 +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_CC2420),)

EE_OBJS_C2420 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_CC2420))))

LIBSRCS += $(EE_SRCS_CC2420)

libcc2420.a: $(EE_OBJS_CC2420)
	@echo $(EE_SRC_CC2420)
	@printf "AR  libcc2420.a\n" ;
	$(QUIET)$(EE_AR) rs libcc2420.a $(EE_OBJS_CC2420)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lcc2420
ALL_LIBS += libcc2420.a

endif

endif

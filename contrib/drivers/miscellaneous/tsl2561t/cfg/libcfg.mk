## Author: 2010 Christian Nastasi

## Check the FM25H20 library selection
ifeq ($(findstring __LIB_TSL2561T__,$(LIB_OPT)) , __LIB_TSL2561T__)
INCLUDE_TSL2561T = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_TSL2561T = YES
endif

## If the library is required
ifeq ($(INCLUDE_TSL2561T), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/miscellaneous/tsl2561t/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/miscellaneous/tsl2561t/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/miscellaneous/tsl2561t/inc

## Add each file individually
EE_SRCS_TSL2561T +=

## If the file list is not empty, create the library
ifneq ($(EE_SRCS_TSL2561T),)

EE_OBJS_FM25H20 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_TSL2561T))))

LIBSRCS += $(EE_SRCS_TSL2561T)

libfm25h20.a: $(EE_OBJS_TSL2561T)
	@echo $(EE_SRC_TSL2561T)
	@printf "AR  libtsl2561t.a\n" ;
	$(QUIET)$(EE_AR) rs libtsl2561t.a $(EE_OBJS_TSL2561T)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -ltsl2561t
ALL_LIBS += libtsl2561t.a

endif

endif

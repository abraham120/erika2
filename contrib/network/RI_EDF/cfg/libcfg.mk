## Author: 2007 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_IEDF__,$(LIB_OPT)) , __LIB_IEDF__)
INCLUDE_IEDF = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_IEDF = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_IEDF), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/network/RI_EDF/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/network/RI_EDF/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/network/RI_EDF/inc

## Add each file individually
#EE_SRCS_RI_EDF += contrib/network/libsrc/libiedf.c
EE_SRCS_IEDF +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_IEDF),)

EE_OBJS_IEDF := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_IEDF))))

LIBSRCS += $(EE_SRCS_IEDF)

libiedf.a: $(EE_OBJS_IEDF)
	@echo $(EE_SRC_IEDF)
	@printf "AR  libiedf.a\n" ;
	$(QUIET)$(EE_AR) rs libiedf.a $(EE_OBJS_IEDF)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -liedf
ALL_LIBS += libiedf.a

endif

endif

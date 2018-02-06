## Author: 2009 Mauro Marinoni

## Check the MRF24J40 library selection
ifeq ($(findstring __LIB_MRF24J40__,$(LIB_OPT)) , __LIB_MRF24J40__)
INCLUDE_MRF24J40 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_MRF24J40 = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_MRF24J40), YES)

##
## Library code
##



## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/radio/mrf24j40/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/radio/mrf24j40/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/radio/mrf24j40/inc

## Add each file individually
#EE_SRCS_MRF24J40 += contrib/drivers/radio/mrf24j40/libsrc/libmrf24j40.c
EE_SRCS_MRF24J40 +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_MRF24J40),)

EE_OBJS_MRF24J40 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_MRF24J40))))

LIBSRCS += $(EE_SRCS_MRF24J40)

libmrf24j40.a: $(EE_OBJS_MRF24J40)
	@echo $(EE_SRC_MRF24J40)
	@printf "AR  libmrf24j40.a\n" ;
	$(QUIET)$(EE_AR) rs libmrf24j40.a $(EE_OBJS_MRF24J40)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lmrf24j40
ALL_LIBS += libmrf24j40.a

endif

endif

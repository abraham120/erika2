## Check the Console library selection
ifeq ($(findstring __LIB_MEMORY__,$(LIB_OPT)) , __LIB_MEMORY__)
INCLUDE_MEMORY = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_MEMORY = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_MEMORY), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/memory/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/memory/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/memory/inc

## Add each file individually
#EE_SRCS_MEMORY += contrib/memory/libsrc/cqueue.c
EE_SRCS_MEMORY += contrib/memory/libsrc/list.c
EE_SRCS_MEMORY += contrib/memory/libsrc/ee_cbuffer.c

## If the file list is not empty, create the memory lib
ifneq ($(EE_SRCS_MEMORY),)
EE_OBJS_MEMORY := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_MEMORY))))
LIBSRCS += $(EE_SRCS_MEMORY)

ifneq ($(call iseeopt, __LM32__), yes) 
libmemory.a: $(EE_OBJS_MEMORY)
	@echo $(EE_SRC_MEMORY)
	@printf "AR  libmemory.a\n" ;
	$(QUIET)$(EE_AR) $(COMPUTED_OPT_AR) $@ $^

##
## Add the library to the linker list and list of lib files
##
##
## Add the library to the linker list and list of lib files
##
ifeq ($(call iseeopt, __KEIL__), yes) 
OPT_LIBS += --userlibpath $(OUTPUT_DIR)/ libmemory.a
else
OPT_LIBS += -lmemory
endif

ALL_LIBS += libmemory.a

else
$(OUTPUT_DIR)/libmemory.a: $(EE_OBJS_MEMORY)
	@echo $(EE_SRC_MEMORY)
	@printf "AR  libmemory.a\n" ;
	$(QUIET)$(EE_AR) rs $(OUTPUT_DIR)/libmemory.a $(EE_OBJS_MEMORY)

OPT_LIBS += -lmemory
ALL_LIBS += $(OUTPUT_DIR)/libmemory.a
endif



endif

endif

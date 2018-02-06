## Author: 2010 Dario Di Stefano 

## Check the PHY library selection
ifeq ($(findstring __LIB_MAC_EXTPHY__,$(LIB_OPT)) , __LIB_MAC_EXTPHY__)
INCLUDE_PHY = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_PHY = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_PHY), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/ethernet/mac_extphy/inc)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/ethernet/mac_extphy/inc/microchip)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/ethernet/mac_extphy/inc
ALLINCPATH += -I$(EEBASE)/contrib/drivers/ethernet/mac_extphy/inc/microchip
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/ethernet/mac_extphy/inc
INCLUDE_PATH += $(EEBASE)/contrib/drivers/ethernet/mac_extphy/inc/microchip

## Add each file individually
EE_SRCS_PHY +=

## If the file list is not empty, create the console lib
ifneq ($(EE_SRCS_PHY),)

EE_OBJS_PHY := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_PHY))))

LIBSRCS += $(EE_SRCS_PHY)

libphy.a: $(EE_OBJS_PHY)
	@echo $(EE_SRC_PHY)
	@printf "AR  libphy.a\n" ;
	$(QUIET)$(EE_AR) rs libphy.a $(EE_OBJS_PHY)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lphy
ALL_LIBS += libphy.a

endif

endif

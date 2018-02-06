## Author: 2009 Francesco Prosperi

#Check the Microchip EEPROM Emulation Library
ifeq ($(findstring __LIB_DEE_EMULATION__,$(LIB_OPT)) , __LIB_DEE_EMULATION__)
INCLUDE_DEE_EMULATION = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_DEE_EMULATION = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_DEE_EMULATION), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/microchip/dee_emulation/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/microchip/dee_emulation/inc
endif
#New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/microchip/dee_emulation/inc

endif

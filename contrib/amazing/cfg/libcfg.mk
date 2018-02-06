## Author: 2007 Mauro Marinoni

## Check the Console library selection
ifeq ($(findstring __LIB_AMAZING__,$(LIB_OPT)) , __LIB_AMAZING__)
INCLUDE_AMAZING = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_AMAZING = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_AMAZING), YES)

##
## Library code
##

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/amazing/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/amazing/inc
endif
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/amazing/inc

endif

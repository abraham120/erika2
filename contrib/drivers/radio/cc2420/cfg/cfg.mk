## Author: 2008 Mauro Marinoni

## Check the CC2420 library selection
ifeq ($(findstring __LIB_CC2420__,$(LIB_OPT)),__LIB_CC2420__)

##
## Application files
##

EE_SRCS += contrib/drivers/radio/cc2420/src/cc2420.c
EE_SRCS += contrib/drivers/radio/cc2420/src/cc2420_hal_ee.c
#EE_SRCS_CC2420_COMMON := $(addprefix contrib/drivers/radio/cc2420/src/, $(notdir $(shell ls -1 $(EEBASE)/contrib/drivers/radio/cc2420/src/*.c)))
#EE_SRCS += $(EE_SRCS_CC2420_COMMON)


## Potentially, check the architecture
#ifeq ($(call iseeopt, __PIC30__), yes)
## Add each file individually
#EE_SRCS += contrib/console/src/hal/pic30.c
#endif

endif

## Author: 2009 Mauro Marinoni

## Check the HV7131GP library selection
ifeq ($(findstring __LIB_HV7131GP__,$(LIB_OPT)),__LIB_HV7131GP__)

##
## Application files
##

EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp.c
ifeq ($(call iseeopt, __MICROCHIP_DSPIC30__), yes)
EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp_hal_ee_dspic.c
endif
ifeq ($(call iseeopt, __MICROCHIP_PIC32__), yes)
EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp_hal_ee_pic32.c
endif
ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/drivers/camera/hv7131gp/src/hv7131gp_hal_ee_mico32.c
endif

INCLUDE_PATH += $(EEBASE)/contrib/drivers/camera/hv7131gp/inc

endif

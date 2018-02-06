## Author: 2010 Christian Nastasi

## Check the MRF24J40 library selection
ifeq ($(findstring __LIB_MRF24J40__,$(LIB_OPT)),__LIB_MRF24J40__)

##
## Application files
##

EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40.c
ifeq ($(call iseeopt, __MICROCHIP_DSPIC30__), yes)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_dspic.c
endif
ifeq ($(call iseeopt, __MICROCHIP_PIC32__), yes)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_pic32.c
endif
ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_mico32.c
endif

ifeq ($(call iseeopt, __STM32__), yes)
EE_SRCS += contrib/drivers/radio/mrf24j40/src/mrf24j40_hal_ee_stm32.c
endif

endif

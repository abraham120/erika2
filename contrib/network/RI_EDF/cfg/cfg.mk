## Author: 2012 Gianluca Franchino

## Check the RI_EDF library selection
ifeq ($(findstring __LIB_IEDF__,$(LIB_OPT)),__LIB_IEDF__)

##
## Application files
##
#GF: Use the KAL support. It's located in uWireless folder

#GF: use iedf_debug.c instead of uwl_debug.c
#EE_SRCS += contrib/network/uWireless/src/util/uwl_debug.c

ifeq ($(findstring __LIB_CC2420__,$(LIB_OPT)),__LIB_CC2420__)
EE_SRCS += contrib/network/RI_EDF/src/hal/iedf_radio_cc2420.c
endif

ifeq ($(findstring __LIB_MRF24J40__,$(LIB_OPT)),__LIB_MRF24J40__)
EE_SRCS += contrib/network/RI_EDF/src/iedf_radio_mrf24j40.c
endif

ifneq ($(call iseeopt, IEDF_HAL_EXTERNAL_TIMER), yes)
ifeq ($(call iseeopt, __PIC30__), yes)
EE_SRCS += contrib/network/RI_EDF/src/hal/iedf_timer_dspic30.c
endif
ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/network/RI_EDF/src/hal/iedf_timer_pic32.c
endif
ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/network/RI_EDF/src/hal/iedf_timer_mico32.c
endif
endif

ifeq ($(findstring IEDF_USE_GENERIC,$(EEOPT)), IEDF_USE_GENERIC)
EE_SRCS += contrib/network/RI_EDF/src/util/iedf_util.c
EE_SRCS += contrib/network/RI_EDF/src/mac/iedf_data.c
EE_SRCS += contrib/network/RI_EDF/src/mac/iedf.c
EE_SRCS += contrib/network/RI_EDF/src/phy/iedf_phy.c
EE_SRCS += contrib/network/RI_EDF/src/kal/iedf_kal_erika.c

ifeq ($(findstring IEDF_DEBUG,$(EEOPT)), IEDF_DEBUG)
EE_SRCS += contrib/network/RI_EDF/src/util/iedf_debug.c
endif

endif

endif
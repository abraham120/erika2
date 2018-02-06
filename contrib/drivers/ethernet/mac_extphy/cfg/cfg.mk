## Author: 2010 Dario Di Stefano 

## Check the SMSC8720 library selection
ifeq ($(findstring __LIB_MAC_EXTPHY__,$(LIB_OPT)),__LIB_MAC_EXTPHY__)

##
## Application files
##

EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/phy.c
EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/eth_api.c
EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/microchip/ETHPIC32ExtPhy.c
EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/microchip/ETHPIC32IntMac.c
#EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/microchip/Tick.c
#EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/microchip/Helpers.c

ifeq ($(call iseeopt, __USE_PHY_SMSC8720__), yes)
EE_SRCS += contrib/drivers/ethernet/mac_extphy/src/microchip/ETHPIC32ExtPhySMSC8720.c
endif

endif #__LIB_EXTPHY__

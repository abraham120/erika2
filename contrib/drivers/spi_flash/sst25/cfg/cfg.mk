## Author: 2010 Dario Di Stefano

## Check the SPIFLASH library selection
ifeq ($(findstring __LIB_SPIFLASH__,$(LIB_OPT)),__LIB_SPIFLASH__)

##
## Application files
##

EE_SRCS += contrib/drivers/spi_flash/src/spi_flash_generic.c

ifeq ($(call iseeopt, __USE_SST25__), yes)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25_generic.c
endif

ifeq ($(call iseeopt, __USE_SST25LF0X0A__), yes)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25lf0x0a.c
endif

ifeq ($(call iseeopt, __USE_SST25VF016B__), yes)
ifeq ($(call iseeopt, __USE_DIAMOND__), no)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25vf016b.c
endif
endif

ifeq ($(call iseeopt, __USE_SST25VF016B__), yes)
ifeq ($(call iseeopt, __USE_DIAMOND__), yes)
EE_SRCS += contrib/drivers/spi_flash/sst25/src/sst25dvf016b.c
endif
endif

endif

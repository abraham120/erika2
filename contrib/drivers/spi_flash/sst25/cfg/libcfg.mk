## Author: 2010 Dario Di Stefano

## Check the SPIFLASH library selection
ifeq ($(findstring __LIB_SPIFLASH__,$(LIB_OPT)) , __LIB_SPIFLASH__)
INCLUDE_SPIFLASH = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_SPIFLASH = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_SPIFLASH), YES)

##
## Library code
##
## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/spi_flash/inc)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/drivers/spi_flash/sst25/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/drivers/spi_flash/inc
ALLINCPATH += -I$(EEBASE)/contrib/drivers/spi_flash/sst25/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/drivers/spi_flash/inc
INCLUDE_PATH += $(EEBASE)/contrib/drivers/spi_flash/sst25/inc

## Add each file individually
EE_SRCS_SPIFLASH +=

## If the file list is not empty, create the SPIFLASH lib
ifneq ($(EE_SRCS_SPIFLASH),)

EE_OBJS_SPIFLASH := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_SPIFLASH))))

LIBSRCS += $(EE_SRCS_SPIFLASH)

libspiflash.a: $(EE_OBJS_SPIFLASH)
	@echo $(EE_SRC_SPIFLASH)
	@printf "AR  libspiflash.a\n" ;
	$(QUIET)$(EE_AR) rs libspiflash.a $(EE_OBJS_SPIFLASH)

##
## Add the library to the linker list and list of lib files
##
OPT_LIBS += -lspiflash
ALL_LIBS += libspiflash.a

endif

endif

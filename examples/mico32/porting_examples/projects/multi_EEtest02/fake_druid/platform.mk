# Platform-specific settings
#



############################################################################
#
# Variable part, automatically generated from 'conf.oil'
#
############################################################################
PLATFORM_NAME=onchipramtimer
PLATFORM_LIB_PATH=../onchipramtimer_lib
PLATFORM_BLD_CFG=Release




############################################################################
#
# Fixed part
#
############################################################################
ifndef PLATFORM_BLD_CFG
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
PLATFORM_BLD_CFG=Debug
else
PLATFORM_BLD_CFG=Release
endif
endif

# Where these platform-dependent makefiles are located.
PLATFORM_MAKEFILES_DIR = $(addprefix $(PLATFORM_LIB_PATH),\
    $(addprefix /$(PLATFORM_NAME), /$(PLATFORM_BLD_CFG)))

# Platform library (relative path and name)
PLATFORM_LIBRARY=$(addprefix $(PLATFORM_LIB_PATH)/,\
    $(addprefix $(PLATFORM_BLD_CFG)/,\
    $(addprefix $(PLATFORM_BLD_CFG)/, lib$(PLATFORM_NAME).a)))


# Linker file
PLATFORM_LD_FILE=$(PLATFORM_MAKEFILES_DIR)/linker.ld

# Platform_rules.mk contains CPU configuration.
include $(PLATFORM_MAKEFILES_DIR)/platform_rules.mk
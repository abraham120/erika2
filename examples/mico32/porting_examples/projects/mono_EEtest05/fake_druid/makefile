# # Date             : 3/17/2010
# RT-Druid version : 
#

# these lines override the .bashrc definitions
#EEBASE = ../../..
#APPBASE = .

###
### Setting EEOPT variable:
###

EEOPT =


############################################################################
#
# User options
#
############################################################################
EEOPT += __ASSERT__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_LINUX__
EEOPT += __LM32__
EEOPT += __OO_BCC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MONO__
EEOPT += __OO_AUTOSTART_TASK__
EEOPT += __OO_STARTOS_OLD__


############################################################################
#
# Lattice mico 32
#
############################################################################
ifndef EEBASE
    EEBASE  := /extra/eclipse/plugins/com.eu.evidence.ee_1.5.1.201003031211/ee_base
endif
APPBASE := ..
OUTBASE := output

LD_FILE = $(OUTPUT_DIR)/linker.ld



############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -g2
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += $(OUTBASE)/eecfg.c $(OUTPUT_DIR)/crt0ram.S main.c dirty_regs.S


############################################################################
#
# More rules for Lattice mico 32
#
############################################################################
include $(OUTPUT_DIR)/platform.mk
include $(OUTPUT_DIR)/lattice.mk

# Remove the crt*.o files from the building process
$(LD_FILE): $(PLATFORM_LD_FILE)
	@echo "Patching linker script"
	$(QUIET) grep -v -E '^INPUT\(' $< > $@



############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk

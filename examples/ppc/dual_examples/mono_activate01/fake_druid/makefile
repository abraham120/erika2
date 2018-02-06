

############################################################################
#
# Makefile created by RT-Druid
#
############################################################################
# Current Project
PROJECT := myProject



############################################################################
#
# Master CPU
#
############################################################################
CPU_MASTER_NAME := master
CPU_MASTER_PORT := 10000
CPU_MASTER_ID   := 0
CPU_MASTER_ELF  := $(PROJECT)_master.elf
CPU_MASTER_DIR  := master



############################################################################
#
# Slave CPUs
#
############################################################################
# Slave cpu slave
CPU1_NAME := slave
CPU1_PORT := 10001
CPU1_ID   := 1
CPU1_ELF  := $(PROJECT)_slave.elf
CPU1_DIR  := slave


# List of all the slave CPU dirs
CPU_DIRS :=  $(CPU1_DIR)
# List of all CPU
CPU_LIST := CPU_MASTER  CPU1



############################################################################
#
# Orti
#
############################################################################
EE_ORTI_SUPPORT := 1


############################################################################
#
# Include common and standard makefiles ...
#
############################################################################
include common.mk

__BASE_MAKEFILE__ = yes
include $(EEBASE)/pkg/cfg/rules.mk


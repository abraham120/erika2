# Jan Kleinsorge, 2009
#
# This is a hand-crafted root-makefile for the EE compilation
# process. Should actually be auto-generated. 
#

export PLATFORM := LINUX
export EEOPT    := DEBUG VERBOSE
export PATH     := $(PATH):$(shell pwd)/util/

project_dir     := .
erika_dir       := ../../..

EVIDENCEBASE    := $(project_dir)
EEBASE          := $(erika_dir)
APPBASE         := $(project_dir)
OUTBASE         := $(project_dir)

TRICORE1_GCCDIR := $(realpath $(shell dirname $(shell which tricore-gcc))/../)

TRICORE1_MODEL   := tc1796

# __TC179x__ is currently a synonym for tc1796/tc13

EEOPT += DEBUG

EEOPT += __TRICORE_GNU__ __TRICORE1__ __TC13__ __TC1796__

# Enable when using the tsim simulator
#EEOPT += __TSIM__

EEOPT +=  __MONO__ 

EEOPT += __OO_BCC1__ __OO_EXTENDED_STATUS__ __OO_AUTOSTART_TASK__

#EEOPT += __TRAP__ __INT__

#EEOPT += __ALLOW_NESTED_IRQ__

#EEOPT += __IRQ_STACK_NEEDED__

CFLAGS  += 
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 

APP_SRCS += eecfg.c code.c

include $(EEBASE)/pkg/cfg/rules.mk

# Generic Makefile for CAL actor networks, via C, to executable
#
# Use 'make help' to view available make targets
#
#
# Modified for integration on Erika toolchain
# Author: Antonio Marcello Catinella
# Date:   2011


# Controlling if CAL_BASE variable is defined
ifndef CAL_BASE
$(error CAL_BASE variable not defined!)
endif
ifdef ACTORS_JAVA
export JAVA=$(ACTORS_JAVA)
endif

# delete the built-in suffixes to avoid surprises
.SUFFIXES:

# Default definitions of tools and directories
include $(EEBASE)/contrib/cal/cfg/definitions.mk

#
# This is a good place for project-specific definitions:
# ------------------------------------------------------

# Source directory (default is current directory)
# export srcdir=/home/me/MPEG4_SP_Decoder

# Additional libraries
# override LDLIBS += -lmylib1 -mylib2
export LDLIBS

# Additional C-files to be compiled (and included in linking)
# override C_FILES += foo.c bar.c
CAL_SRC_DIR = contrib/cal/src
SYS_ACTORS_OBJS = $(addprefix $(OBJDIR)/$(CAL_SRC_DIR)/, $(SYS_ACTORS:.c=.o))
LIBSRCS += $(addprefix $(CAL_SRC_DIR)/, $(SYS_ACTORS))

# Generate debug code
# DEBUG=Y

#
# Available CAL networks and those already elaborated/built
#
srcdir?=.
SRCDIR_ABS=$(abspath $(srcdir))
CAL_NETWORKS=$(wildcard $(srcdir)/*.nl)
AVAILABLE_MODELS=$(patsubst %.nl,%, $(notdir $(CAL_NETWORKS)))
MODEL:=$(patsubst %.nl,%, $(filter %.nl, $(APP_SRCS)))
APP_SRCS:=$(filter-out %.nl, $(APP_SRCS))

ifneq ("$(AVAILABLE_MODELS)", "")
include $(EEBASE)/contrib/cal/cfg/makemodel.mk
else
$(error There isn't any netlist file available for this project!)
endif

#
# clean: Clean all build files
#

.PHONY: clean clean-actors

clean: clean-actors

clean-actors:
	rm -f  $(MODEL).xdf $(MODEL).depend $(MODEL).timestamp $(MODEL).c\
            *.par *.xlim && rm -R cache/


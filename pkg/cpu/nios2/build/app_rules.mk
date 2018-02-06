#******************************************************************************
#                                                                             *
# License Agreement                                                           *
#                                                                             *
# Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
# All rights reserved.                                                        *
#                                                                             *
# Permission is hereby granted, free of charge, to any person obtaining a     *
# copy of this software and associated documentation files (the "Software"),  *
# to deal in the Software without restriction, including without limitation   *
# the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
# and/or sell copies of the Software, and to permit persons to whom the       *
# Software is furnished to do so, subject to the following conditions:        *
#                                                                             *
# The above copyright notice and this permission notice shall be included in  *
# all copies or substantial portions of the Software.                         *
#                                                                             *
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
# DEALINGS IN THE SOFTWARE.                                                   *
#                                                                             *
# This agreement shall be governed in all respects by the laws of the State   *
# of California and by the laws of the United States of America.              *
#                                                                             *
# Altera does not recommend, suggest or require that this reference design    *
# file be used in conjunction or combination with any other product.          *
#******************************************************************************

#******************************************************************************
#                                                                             *
# THIS IS A LIBRARY READ-ONLY SOURCE FILE. DO NOT EDIT.                       *
#                                                                             *
#******************************************************************************

# This file provides the common rules which are shared between the HAL and
# uC/OS-II Makefiles. This means that it defines the "all" and "clean" rules,
# and then includes the files: gnu_rules.mk and gtf_rules.mk.
#
# gnu_rules.mk defines the rules which use the gnu tools, i.e. it defines the
# rules for compiling, archiving, and linking. gtf_rules.mk defines the rules
# for generating files which are dependent on the STF and PTF files, i.e. 
# generated_app.mk, generated_all.mk, generated.sh, alt_sys_init.c and 
# system.h.
#
# In addition this file includes the auto-generated makefile, generated_app.mk,
# which defines all of the "post elf" build rules, for example the rules
# used to build flash programming files. The content of generated_app.mk is
# dependent upon the system configuration and is generated based on the
# settings in the associated PTF and STF files.

# List of makefile fragments used to ensure the system is rebuilt when the 
# Makefiles change.

MAKEFILE_LIST += makefile $(APP_MAKEFILE)            \
                 $(COMPONENT_MAKEFILES)              \
                 $(GTF_GENERATED)/generated_all.mk   \
                 $(GTF_GENERATED)/system.h   \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/common.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/ee_common.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/ee_firstcpu.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/ee_global.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/ee_othercpu.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gtf_rules.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gnu_rules.mk \
                 $(SOPC_KIT_NIOS2)/components/evidence_ee/build/app_rules.mk

# Work out the final output name

ifndef ELF
ifneq ($(ALT_SIM_OPTIMIZE),1)
ELF = $(PROJECT).elf
else
ELF = RUN_ON_HDL_SIMULATOR_ONLY_$(PROJECT).elf
endif
endif

# ******************************************************************************
# *                          RULE DEFINITIONS                                  *
# ******************************************************************************

.DELETE_ON_ERROR:

all: system_project $(ELF) 

ifeq ($(DO_MAKE_OBJDUMP),1)
all: $(ELF).objdump
endif

all: $(GTF_GENERATED)/generated.sh generated_app.sh

# When running: 'make clean' we want to delete all generated files, which is 
# what the following clean rule does. However when running: 'make clean all', 
# make doesn't realise that it needs to regenerated some of the files deleted
# by the 'clean' rule before running the 'all' rule. In particular make has
# problems with included makefiles being deleted. To avoid this, some files
# are only deleted for 'make clean' and not for 'make clean all'. 

clean: generated_app_clean
	$(RM) *.elf *.objdump generated_app.sh
	find . -name '*.o' | xargs $(RM)
ifeq ($(MAKECMDGOALS),clean)         
	$(RM) $(OBJ_DIR) *.d
endif

# The clean rule will only clean the current project. It will not clean the
# associated HAL system project as well. To do this, use the distclean rule.

distclean: 
	$(MAKE) clean
	$(MAKE) -C "$(SYSTEM_CONFIG_DIR)" clean

# Build the associated system library project. This will always build for
# the same configuration as is bing used for the application project, for
# example if a "debug" configuration is being used for the application,
# then a "debug" configuration will be built for the system library.

system_project:
	$(MAKE) -C "$(SYSTEM_CONFIG_DIR)"

generated_app.sh: makefile
	@echo Creating $@...
	@echo "#! /bin/sh" > $@
	@echo "#" >> $@
	@echo " " >> $@

	@echo "# DO NOT MODIFY THIS FILE" >> $@
	@echo "#" >> $@
	@echo "#   Changing this file will have subtle consequences" >> $@
	@echo "#   which will almost certainly lead to a nonfunctioning" >> $@
	@echo "#   system. If you do modify this file, be aware that your" >> $@
	@echo "#   changes will be overwritten and lost when this file" >> $@
	@echo "#   is generated again." >> $@
	@echo "#" >> $@
	@echo "# DO NOT MODIFY THIS FILE" >> $@
	@echo " " >> $@
	@echo "SYSTEM_CONFIG_DIR=$(SYSTEM_CONFIG_DIR)" >> $@

# The auto-generated makefile fragment that defines the required targets other 
# than $(ELF)

-include $(GTF_GENERATED)/generated_app.mk

# Include the rules for making sure all the paths are Unix style

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/common.mk

# Include the component makefiles

ifneq ($(COMPONENT_MAKEFILES),)
include $(COMPONENT_MAKEFILES)
endif

# Include the rules for building the object files and dependency files

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gnu_rules.mk

# Include the rules for generating the auto-generated files

include $(SOPC_KIT_NIOS2)/components/evidence_ee/build/gtf_rules.mk
# Build license reminders last.
all: license_reminders

.PHONY: all clean distclean system_project license_reminders

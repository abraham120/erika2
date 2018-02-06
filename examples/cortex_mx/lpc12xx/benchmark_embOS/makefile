# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2012  Evidence Srl
# 
# This file is part of ERIKA Enterprise.
# 
# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation, 
# (with a special exception described below).
# 
# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.
# 
# As a special exception, the copyright holders of this library give you
# permission to link this code with independent modules to produce an
# executable, regardless of the license terms of these independent
# modules, and to copy and distribute the resulting executable under
# terms of your choice, provided that you also meet, for each linked
# independent module, the terms and conditions of the license of that
# module.  An independent module is a module which is not derived from
# or based on this library.  If you modify this code, you may extend
# this exception to your version of the code, but you are not
# obligated to do so.  If you do not wish to do so, delete this
# exception statement from your version.
# 
# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.
# 
# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

## Makefile for Benchmark project
## Author: 2012,  Gianluca Franchino

#Utility Function
cygwin-path=$(shell cygpath -u -a '$1')

# Destination directory
export OUTPUT_DIR = output

arch ?= NXP_LPC1227

# Simulator Interface
#Debugger       ?= Simul
# In-Circuit Debugger Interface
Debugger       ?= ULINK2

DEBUG_PROJECT_DIR ?= Keil_Debug_BM_Project
OUTPUT_PORT ?= memory

ifeq ($(Debugger), ULINK2)

ifeq ($(OUTPUT_PORT), uart)
DEPENDENT_MAKE := uart/makefile
else
DEPENDENT_MAKE := ulink2/makefile
endif

endif

ifeq ($(Debugger), Simul)
DEPENDENT_MAKE := simul/makefile
endif

DEPENDENT_HEADERS := timingtest.h bm_config.h bm_cortex_m0_config.h bm_embOS_config.h 
DEPENDENT_SCT := template.sct

ifeq ($(Debugger), ULINK2)

ifeq ($(OUTPUT_PORT), uart)
APP_SRC :=  code.c timingtest.c bm_embOS.c bm_cortex_m0_log_header.c startup_LPC12xx.s
else
APP_SRC :=  code.c timingtest.c bm_embOS.c startup_LPC12xx.s
endif

else
APP_SRC :=  code.c timingtest.c bm_embOS.c startup_LPC12xx.s
endif


TARGET_DEPENDENT_MAKE := $(addprefix benchmark/, $(DEPENDENT_MAKE))
TARGET_DEPENDENT_SCT := $(addprefix benchmark/, $(DEPENDENT_SCT))
TARGET_DEPENDENT_HEADERS := $(addprefix benchmark/, $(DEPENDENT_HEADERS))
TARGET_SRCS := $(addprefix $(OUTPUT_DIR)/, $(APP_SRC))
TARGET_HEADERS := $(addprefix $(OUTPUT_DIR)/, $(DEPENDENT_HEADERS))


BUILD_OUT_FILE := $(OUTPUT_DIR)/c_m0.out

DEBUG_FILES :=	Debug.ini \
		$(Debugger).plg \
		$(Debugger).uvopt \
		$(Debugger).uvproj \
		$(Debugger)_$(arch).dep


DEBUG_SRC_FILE := $(OUTPUT_DIR)/$(Debugger).out

SRCS_DEBUG_FILES := $(addprefix $(DEBUG_PROJECT_DIR)/, $(DEBUG_FILES))
DEST_DEBUG_FILES := $(addprefix $(OUTPUT_DIR)/, $(DEBUG_FILES))

DEBUGGER_BIN ?= /cygdrive/c/Keil/UV4/Uv4.exe

DEBUGGER_PROJECT := $(OUTPUT_DIR)/$(Debugger).uvproj

DEBUG_DONE_FILE := $(OUTPUT_DIR)/debug_done.txt

BM_DONE_FILE := $(OUTPUT_DIR)/benchmark_done.txt

#############################################################################
#	Standard commands
#############################################################################
CD    =  @cd
MOVE  =  @mv
COPY  =  @cp
ECHO  =  @echo


.PHONY: all
all: $(BM_DONE_FILE)
	$(ECHO) ---------- END OF BENCHMARK ----------

###############################################################################
##  Local targets and rules
###############################################################################	
.PHONY: clean
clean:
	$(ECHO) cleaning...
	$(RM) -r $(OUTPUT_DIR)

#clean plus all
.PHONY: all-forced
all-forced: clean all make-dir_out

.PHONY: make-dir-out
make-dir_out: $(OUTPUT_DIR)

$(OUTPUT_DIR): 
	@echo "MAKE_DIRECTORIES"
	@mkdir -p $(OUTPUT_DIR)

$(BM_DONE_FILE): $(DEBUG_DONE_FILE)
	$(ECHO) "End of Benchmark"

$(DEBUG_DONE_FILE): $(DEBUG_SRC_FILE) $(DEST_DEBUG_FILES)
	$(ECHO) "Start debugging of Benchmark"
	@$(DEBUGGER_BIN) -j0 -d $(DEBUGGER_PROJECT)
	$(ECHO) "End debugging of Benchmark"

$(DEBUG_SRC_FILE): $(BUILD_OUT_FILE)
	$(ECHO) "Copying debug file: $@ from $<"
	$(COPY) $< $@

$(BUILD_OUT_FILE): $(TARGET_DEPENDENT_MAKE) $(TARGET_DEPENDENT_HEADERS)\
					$(TARGET_SRCS) $(TARGET_HEADERS) $(OUTPUT_DIR)/makefile\
					$(OUTPUT_DIR)/template.sct
	$(ECHO) "Building of Benchmark"
	@$(MAKE) -C $(OUTPUT_DIR) all

#############################################################################
## Copy Benchmark source files
#############################################################################
$(OUTPUT_DIR)/%.c: benchmark/%.c make-dir_out
	$(ECHO) "Copying benchmark source file: $@ from $<"
	$(COPY) $< $@

$(OUTPUT_DIR)/%.s: benchmark/%.s make-dir_out
	$(ECHO) "Copying benchmark source file: $@ from $<"
	$(COPY) $< $@
	
$(OUTPUT_DIR)/%.h: benchmark/%.h make-dir_out
	$(ECHO) "Copying benchmark header file: $@ from $<"
	$(COPY) $< $@	

$(OUTPUT_DIR)/makefile: $(TARGET_DEPENDENT_MAKE) make-dir_out
	$(ECHO) "Copying benchmark makefile: $@ from $<"
	$(COPY) $< $@

$(OUTPUT_DIR)/template.sct: $(TARGET_DEPENDENT_SCT) make-dir_out
	$(ECHO) "Copying benchmark linker script: $@ from $<"
	$(COPY) $< $@

#############################################################################
## Copy Kile Debugger related files
#############################################################################		

$(OUTPUT_DIR)/Debug.ini: $(DEBUG_PROJECT_DIR)/Debug.ini
	$(ECHO) "Copying debug file: $@ from $<"
	$(COPY) $< $(OUTPUT_DIR)
	
$(OUTPUT_DIR)/$(Debugger).%: $(DEBUG_PROJECT_DIR)/$(Debugger).%
	$(ECHO) "Copying debug file: $@ from $<"
	$(COPY) $< $(OUTPUT_DIR)
#	$(MOVE) $(OUTPUT_DIR)/$(Debugger).out $(OUTPUT_DIR)/$(Debugger).axf

$(OUTPUT_DIR)/$(Debugger)_$(arch).dep: $(DEBUG_PROJECT_DIR)/$(Debugger)_$(arch).dep
	$(ECHO) "Copying debug file: $@ from $<"
	$(COPY) $< $(OUTPUT_DIR)

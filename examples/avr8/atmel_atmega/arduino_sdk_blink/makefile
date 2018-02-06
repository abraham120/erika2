# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2016  Evidence Srl
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

## Makefile for Erika Arduino demos
## Author: 2016,  Giuseppe Serano

# Destination directory
export OUTPUT_DIR = Debug

# Check the environment and use reasonable defaults
ifndef	ARDUINO_SDK_FILES
ifeq	($(shell uname), Linux)
export	ARDUINO_SDK_FILES = $(HOME)/arduino-1.0.5-r2
else
# For Old Arduino Support
#export	ARDUINO_SDK_FILES = C:/arduino-1.0.5-r2
# For Arduino.cc.
#export	ARDUINO_SDK_FILES = C:/arduino-1.6.8
#export	ARDUINO_SDK_FILES = C:/arduino-1.6.9
export	ARDUINO_SDK_FILES = C:/arduino-1.6.10
# For Arduino.org.
#export	ARDUINO_SDK_FILES = C:/arduino-1.7.8
#export	ARDUINO_SDK_FILES = C:/arduino-1.7.9
#export	ARDUINO_SDK_FILES = C:/arduino-1.7.10
endif
endif

ifndef	AVR_TOOLS
export AVR_TOOLS = $(ARDUINO_SDK_FILES)/hardware/tools/avr
endif

ifndef	ARDUINO_COM_PORT
export	ARDUINO_COM_PORT = COM62
endif

ifndef	ARDUINO_BAUDRATE
export	ARDUINO_BAUDRATE = 115200	# ARDUINO UNO 328
#export	ARDUINO_BAUDRATE = 57600	# ARDUINO NANO 328
endif

ifndef	ARDUINO_MCU
export	ARDUINO_MCU = atmega328p
endif


ifndef	ERIKA_FILES
export ERIKA_FILES = $(abspath ../../../..)
endif

ifndef	RTDRUID_ECLIPSE_HOME
ifeq	($(shell uname), Linux)
export RTDRUID_ECLIPSE_HOME = $(HOME)/Evidence/eclipse
else
export RTDRUID_ECLIPSE_HOME = C:/Evidence/eclipse
endif
endif

ifndef	RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR = $(RTDRUID_ECLIPSE_HOME)/evidence
endif

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, makefile eecfg.h eecfg.c)

.PHONY: all clean upload

all: $(RTDRUID_OUTPUT)
	$(MAKE) -C $(OUTPUT_DIR) all

clean:
	@echo cleaning...
	@rm -f -r $(OUTPUT_DIR)

upload:	all
	@$(ARDUINO_SDK_FILES)/hardware/tools/avr/bin/avrdude \
	-C$(ARDUINO_SDK_FILES)/hardware/tools/avr/etc/avrdude.conf \
	-p$(ARDUINO_MCU) -carduino -P\\\\.\\$(ARDUINO_COM_PORT) \
	-b$(ARDUINO_BAUDRATE) -D -Uflash:w:$(OUTPUT_DIR)/arduino.hex:i


ifeq ($(RUN_RTDRUID),1)
ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

# Run RT-Druid
$(RTDRUID_OUTPUT): conf.oil
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ;\
	export ECLIPSE_HOME ;\
	exec sh $(RTDRUID_SCRIPT_DIR)/generate_code.sh $(RTDRUID_ECLIPSE_HOME) conf.oil $(OUTPUT_DIR)

else
# Simulate RT-Druid
$(RTDRUID_OUTPUT): $(OUTPUT_DIR)/% : fake_druid/%
	@echo "Substituing RT-Druid in generating $@..."
	@mkdir -p $(OUTPUT_DIR)
	@cp $< $@
endif

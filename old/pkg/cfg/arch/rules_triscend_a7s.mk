# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2008  Evidence Srl
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

## Author: 2003 Marko Bertogna
## CVS: $Id: rules_triscend_a7s.mk,v 1.2 2007/06/01 09:00:21 pj Exp $

##
## Linux makefile for GCC cross compiler 3.0
##



##
## Global paths
##

# ARM7BASE is the base directory of development environment
# it should be defined in your .bashrc
# ARM7BASE = 

# EEBASE is the base directory of the kernel
# it should be defined in your .bash_profile
# EEBASE = 

# APPBASE is the base directory of the application
APPBASE = $(CURDIR)

# BINDIR is the directory of assembler, compiler, linker...
BINDIR = $(ARM7BASE)/bin

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
ALLINCPATH = -I$(EEBASE)/include -I$(APPBASE)

# GNUPro compilers
ifndef ARM7LINK
ARM7LINK=$(BINDIR)/arm-elf-ld
endif
ifndef ARM7ASM
ARM7ASM=$(BINDIR)/arm-elf-as
endif
ifndef ARM7CC
ARM7CC=$(BINDIR)/arm-elf-gcc
endif
ARM7TCC=$(ARM7CC) -mthumb # 16-bit thumb C compiler

ifndef ARM7AR
ARM7AR=$(BINDIR)/arm-elf-ar
endif

ifndef ARM7OBJCOPY
ARM7OBJCOPY=$(BINDIR)/arm-elf-objcopy
endif

# do not display too much things...
ifndef VERBOSE
ARM7LINK:=@$(ARM7LINK)
ARM7ASM:=@$(ARM7ASM)
ARM7CC:=@$(ARM7CC)
ARM7TCC:=@$(ARM7TCC)
ARM7AR:=@$(ARM7AR)
ARM7OBJCOPY:=@$(ARM7OBJCOPY)

VERBOSE_DEVNULL=
VERBOSE_PRINTDEP=@echo DEP $<
VERBOSE_PRINTCC=@echo CC  $<
VERBOSE_PRINTTCC=@echo TCC $<
VERBOSE_PRINTCPP=@echo CPP $<
VERBOSE_PRINTASM=@echo ASM $<
VERBOSE_PRINTSRC=@echo SRC $<
VERBOSE_PRINTOBJCOPY=@echo OBJCOPY $<

else
VERBOSE_DEVNULL=>/dev/null
VERBOSE_PRINTDEP=@echo
VERBOSE_PRINTCC=@echo
VERBOSE_PRINTTCC=@echo
VERBOSE_PRINTCPP=@echo
VERBOSE_PRINTASM=@echo
VERBOSE_PRINTOBJCOPY=@echo
endif



## OPTARM7CC are the options for arm compiler invocation
# -mcpu=arm7tdmi    = generate optimized code for ARM7TDMI processor
# -mno-apcs-frame   = don't generate a stack frame APCS compliant
#                     (should be the default, anyway when specified 
#                     the compiler puts a warning in conjunction with 
#                     the use of -g)
# -O                = select the optimization level
#                     NOTE that -O0 can NOT be used because it not expands
#                     inline functions!!!!
# -ggdb             = add debug tables for GDB
# -c                = compile only (do not link)
# -mthumb-interwork = support arm/thumb interwork
# -Wall		    = all compiling warning
# -Winline	    = warn if a function does not expand inline
# -finline-functions = make all simple functions inline
OPTARM7CC = -mcpu=arm7tdmi -mthumb-interwork \
	-O1 -Wall -Winline -c $(ALLINCPATH)
#OPTARM7CC = -mcpu=arm7tdmi -mno-apcs-frame -mthumb-interwork \
#	-O2 -Wall -Winline -c $(ALLINCPATH)
ifneq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPTARM7CC += -ggdb
endif
endif

## OPTARM7TCC are the options for thumb compiler invocation
# -mcallee-super-interworking = switch to thumb mode after an arm header
OPTARM7TCC = $(OPTARM7CC) -mthumb-interwork -mcallee-super-interworking

## OPTARM7ASM are the options for asm invocation
# -marm7tdmi        = generate optimized code for ARM7TDMI processor
# -mapcs-32	    = support APCS function calling standard
# -mthumb-interwork = support arm/thumb interwork
OPTARM7ASM = -marm7tdmi -mthumb-interwork -mapcs-32

ifneq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
OPTARM7ASM += --gstabs
endif
endif

# OPTARM7LINK represents the options for armlink invocation
ifneq ($(findstring __DEFAULT_LD_SCRIPT__,$(EEOPT)) , __DEFAULT_LD_SCRIPT__)
OPTARM7LINK = --script=out/triscend_a7s.ld -u__start
LINKDEP = out/triscend_a7s.ld out/loc_triscend.ld
endif

# OPTARM7LIBS is used to link additional libraries (e.g., for C++ support)
OPTARM7LIBS = -lerika -L $(APPBASE)/out


# The line below will convert the .elf file to a Motorola S-Record file.
DMP	= $(ARM7OBJCOPY) --set-start 0x00000000 -O srec out/$*.elf out/$*.hex


# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

# we use gcc! DEFSARM7ASM += $(foreach SYM, $(EEOPT), --defsym $(SYM)=1)
DEFSARM7ASM = $(addprefix -D, $(EEOPT) _PROJECT_HEADER=\"$(FCP_PROJECT_DIR)/$(FCP_PROJECT).h\")
DEFSARM7CC  = $(addprefix -D, $(EEOPT) _PROJECT_HEADER=\"$(FCP_PROJECT_DIR)/$(FCP_PROJECT).h\")
DEFSARM7TCC = $(addprefix -D, $(EEOPT) _PROJECT_HEADER=\"$(FCP_PROJECT_DIR)/$(FCP_PROJECT).h\")




#
# HAL source
#
ARM7_VPATH = $(EEBASE)/src/arm7gnu
ARM7_SRCS = hal.S hal_thumb.S

#
# BSP source
#
ARM7_VPATH += $(EEBASE)/src/arm7gnu/triscend_a7s
ARM7_SRCS += inthand.S start.S


# FP
ifeq ($(findstring __FP__,$(EEOPT)) , __FP__)
KERN_VPATH += $(EEBASE)/src/fp
KERN_SRCS += gettime.c irq_act.c irq_sc.c \
	rq_exchg.c rq_inser.c schedule.c thact.c thendin.c thmkrdy.c

  ifneq ($(findstring __FP_NO_MUTEX__,$(EEOPT)) , __FP_NO_MUTEX__)
  KERN_SRCS += mutex.c
  endif

else
KERN_VPATH +=
KERN_SRCS +=
endif


# EDF
ifeq ($(findstring __EDF__,$(EEOPT)) , __EDF__)
KERN_VPATH += $(EEBASE)/src/edf
KERN_SRCS += gettime.c irq_act.c irq_sc.c \
	rq_exchg.c rq_inser.c schedule.c thact.c thendin.c thmkrdy.c

  ifneq ($(findstring __EDF_NO_MUTEX__,$(EEOPT)) , __EDF_NO_MUTEX__)
  KERN_SRCS += mutex.c
  endif

else
KERN_VPATH +=
KERN_SRCS +=
endif






# OO

ifeq ($(findstring __OO_BCC1__,$(EEOPT)) , __OO_BCC1__)
OO=YES
endif
ifeq ($(findstring __OO_BCC2__,$(EEOPT)) , __OO_BCC2__)
OO=YES
endif
ifeq ($(findstring __OO_ECC1__,$(EEOPT)) , __OO_ECC1__)
OO=YES
OO_ECC=YES
endif
ifeq ($(findstring __OO_ECC2__,$(EEOPT)) , __OO_ECC2__)
OO=YES
OO_ECC=YES
endif

ifeq ($(OO), YES)
KERN_VPATH += $(EEBASE)/src/oo
KERN_SRCS += activate.c schedule.c force_schedule.c terminat.c \
	     thendin.c irqendin.c tstub.c lookup.c \
             rq_exchg.c rq_first.c rq_inser.c \
             shtdown.c startos.c
             

ifneq ($(findstring __OO_NO_CHAINTASK__,$(EEOPT)) , __OO_NO_CHAINTASK__)
KERN_SRCS += chaintas.c
endif

ifneq ($(findstring __OO_NO_RESOURCES__,$(EEOPT)) , __OO_NO_RESOURCES__)
KERN_SRCS += lockres.c ulockres.c
endif


ifneq ($(findstring __OO_NO_ALARMS__,$(EEOPT)) , __OO_NO_ALARMS__)
KERN_SRCS += alcancel.c  algetbase.c  alget.c \
             alsetabs.c  alsetrel.c altick.c
endif

ifeq ($(OO_ECC) , YES)
KERN_SRCS += evclear.c evget.c evset.c evwait.c 
endif

ifeq ($(findstring __BIN_DISTR,$(EEOPT)) , __BIN_DISTR)
KERN_SRCS +=	disableallinterrupts.c     \
		enableallinterrupts.c      \
		suspendallinterrupts.c     \
		resumeallinterrupts.c      \
		suspendosinterrupts.c      \
		resumeosinterrupts.c       \
		getactiveapplicationmode.c \
		gettaskid.c                \
		gettaskstate.c
endif

ARM7_SRCS += oo.S

# irqendin.c
else
KERN_VPATH +=
KERN_SRCS +=
endif


#
# --------------------------------------------------------------------------
#

# Communication Libraries


########### COM CCCA #############
ifeq ($(findstring __COM_CCCA__,$(EEOPT)) , __COM_CCCA__) 
LIB_SRCS += com.c msgreception.c filters.c memo.c startcom.c \
	stopcom.c initmessage.c getcomapplicationmode.c \
	comerrorgetserviceid.c sendstatic.c receivestatic.c
LIB_VPATH += $(EEBASE)/src/com/com
endif

########### COM CCCB #############
ifeq ($(findstring __COM_CCCB__,$(EEOPT)) , __COM_CCCB__) 
LIB_SRCS += com.c msgreception.c filters.c memo.c startcom.c \
	stopcom.c initmessage.c getcomapplicationmode.c \
	comerrorgetserviceid.c sendstatic.c receivestatic.c \
	msgstatus.c
LIB_VPATH += $(EEBASE)/src/com/com
endif

########### COM CCC0 #############
ifeq ($(findstring __COM_CCC0__,$(EEOPT)) , __COM_CCC0__) 
LIB_SRCS += com.c msgreception.c filters.c memo.c startcom.c \
	stopcom.c initmessage.c getcomapplicationmode.c \
	comerrorgetserviceid.c sendstatic.c receivestatic.c \
	convert.c queue_TM.c dmonitor.c
LIB_VPATH += $(EEBASE)/src/com/com
endif

########### COM CCC1 #############
ifeq ($(findstring __COM_CCC1__,$(EEOPT)) , __COM_CCC1__) 
LIB_SRCS += com.c msgreception.c filters.c memo.c startcom.c \
	stopcom.c initmessage.c getcomapplicationmode.c \
	comerrorgetserviceid.c sendstatic.c receivestatic.c \
	msgstatus.c \
	convert.c queue_TM.c dmonitor.c \
	sendzero.c senddynamic.c receivedynamic.c notify_error.c \
	startperiodic.c stopperiodic.c queue_DM.c
LIB_VPATH += $(EEBASE)/src/com/com
endif

########### ISO15765 NETWORK LAYER ################
ifeq ($(findstring __ISO15765__,$(EEOPT)) , __ISO15765__)
LIB_SRCS += init_net.c request.c confirm.c monitor.c indication.c
LIB_VPATH += $(EEBASE)/src/com/iso15765
endif

########### FTT NETWORK LAYER ################
### FTT MASTER NODE ###
ifeq ($(findstring __FTT_MASTER__,$(EEOPT)) , __FTT_MASTER__)
LIB_SRCS += ART_add.c ART_change.c ART_check.c ART_remove.c \
	asynch_tx.c stop_asynch.c \
	ftt_confirm.c ftt_dispatcher.c ftt_indication.c ftt_init.c \
	ftt_set_handler.asm ftt_start.c \
	rm_scheduler.c \
	slave_add.c slave_remove.c \
	SRT_add.c SRT_change.c SRT_check.c SRT_delete.c SRT_insert.c \
	SRT_remove.c \
LIB_VPATH += $(EEBASE)/src/com/ftt/master/
endif

### FTT SLAVE NODE ###
ifeq ($(findstring __FTT_SLAVE__,$(EEOPT)) , __FTT_SLAVE__)
LIB_SRCS += activation.c \
	NRT_receive.c NRT_send.c \
	AMS_receive.c AMS_send.c \
	ART_add.c ART_change.c ART_remove.c Asearch.c \
	NRTTsearch.c NRTRsearch.c \
	buf_req.c \
	ftt_confirm.c ftt_indication.c ftt_init.c ftt_set_handler.asm \
	ftt_start.c ftt_transmitter.c \
	SMS_consume.c SMS_produce.c \
	SRT_add.c SRT_change.c SRT_remove.c Ssearch.c \
	stop_asynch.c
LIB_VPATH += $(EEBASE)/src/com/ftt/slave/
endif

############ DATA LINK LAYER ###################
ifeq ($(findstring __DLC_STANDARD__,$(EEOPT)) , __DLC_STANDARD__)
LIB_SRCS += canst10.c can_handler.c can_driver.c init_can.c 
	transmit.c irqcanst10.asm
LIB_VPATH += $(EEBASE)/src/com/dlc
endif


#
# --------------------------------------------------------------------------
#

# Libraries

ifeq ($(findstring __CABS__,$(EEOPT)) , __CABS__)
LIB_SRCS += cabs.c
LIB_VPATH += $(EEBASE)/src/cabs
endif

ifeq ($(findstring __SEM__,$(EEOPT)) , __SEM__)

ifeq ($(findstring __MONO__,$(EEOPT)) , __MONO__)
all::
	$(error Semaphores and Mono Stack HAL are not compatible!!!)
clean::
	$(error Semaphores and Mono Stack HAL are not compatible!!!)
endif

LIB_SRCS += swait.c spost.c sirqpost.c sgetvalue.c strywait.c
LIB_VPATH += $(EEBASE)/src/sem
endif

ifeq ($(findstring __ALARMS__,$(EEOPT)) , __ALARMS__)
LIB_SRCS += alcancel.c altick.c alget.c alsetabs.c alsetrel.c
LIB_VPATH += $(EEBASE)/src/alarms
endif

ifeq ($(findstring __ASSERT__,$(EEOPT)) , __ASSERT__)
LIB_SRCS += assert.c
LIB_VPATH += $(EEBASE)/src/assert
endif


#
# --------------------------------------------------------------------------
#

##
## Common Rules
##

SRCS = $(APP_SRCS)
OBJS= $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
THUMB_OBJS= $(patsubst %.c,%.to,$(THUMB_SRCS))

LIBSRCS = $(KERN_SRCS) $(LIB_SRCS)
LIBOBJS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(LIBSRCS)))
 
ifeq ($(findstring __BIN_DISTR,$(EEOPT)), __BIN_DISTR)
LIBSRCS += $(ARM7_SRCS)
else
SRCS += $(ARM7_SRCS)
endif

vpath %.elf out
vpath %.o out
vpath %.to out
vpath %.cd out
vpath %.Sd out
vpath %.td out
vpath %.c $(ARM7_VPATH) $(KERN_VPATH) $(LIB_VPATH) $(APPBASE)
vpath %.S $(ARM7_VPATH) $(KERN_VPATH) $(LIB_VPATH) $(APPBASE)
vpath %.src out

%.o: %.S
	@test -d out || mkdir out
	$(VERBOSE_PRINTCPP)
	$(ARM7CC) $(ALLINCPATH) $(DEFSARM7ASM) -E $< > out/$(notdir $(patsubst %.o,%.src,$@))
	$(VERBOSE_PRINTASM)
	$(ARM7ASM) $(OPTARM7ASM) out/$(notdir $(patsubst %.o,%.src,$@)) -o out/$(notdir $@)

%.o: %.c 
	@test -d out || mkdir out
	$(VERBOSE_PRINTCC)
	$(ARM7CC) $(OPTARM7CC) $(DEFSARM7CC) $< -o out/$(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(VERBOSE_PRINTSRC)
	$(ARM7CC) $(OPTARM7CC) $(DEFSARM7CC) $< -S -o out/$(notdir $(patsubst %.o,%.S,$@))
endif

%.to: %.c 
	@test -d out || mkdir out
	$(VERBOSE_PRINTTCC)
	$(ARM7TCC) $(OPTARM7TCC) $(DEFSARM7TCC) $< -o out/$(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(VERBOSE_PRINTSRC)
	$(ARM7TCC) $(OPTARM7TCC) $(DEFSARM7TCC) $< -S -o out/$(notdir $(patsubst %.to,%.src,$@))
endif



##
## Main rules: all clean
##

.PHONY: all clean

all:: sdram

%.elf: $(OBJS) $(THUMB_OBJS) $(LINKDEP) out/liberika.a
	@echo LD out/liberika.a $(VERBOSE_DEVNULL)
	$(ARM7LINK) $(OPTARM7LINK) \
                     -o out/$@ $(addprefix out/, $(OBJS) $(THUMB_OBJS)) \
                     --start-group $(OPTARM7LIBS) --end-group \
	             -M > out/$(@:.elf=.map)

%.hex: %.elf
	$(VERBOSE_PRINTOBJCOPY)
	$(DMP)
	$(HEX_TO_I)


# CSOC_CFG_OPTS are the normal options used for csoc config 
CSOCOPTS	+= -clk $(CLOCK) -swt 200 \
	-csl $(FCP_PROJECT_DIR)/$(FCP_PROJECT).csl -dev $(CSOC_NAME) \
	-miu $(MIU) -sdmiu $(SDMIU) -sdram $(SDRAM)

# CSOC_DWL_OPTS are the options for csoc download
CSOC_DWL_OPTS += -pgm


# Direct download to SDRAM
#
sdram: sdram.hex
	csoc config $(CSOCOPTS) -code out/sdram.hex \
	-mem $(SDRAM) \
	-out out/sdram.cfg
	csoc download $(CSOC_DWL_OPTS) out/sdram.cfg

#
# Download to flash
#
flash: flash.hex
	csoc config $(CSOCOPTS) -code out/flash.hex \
	-mem $(FLASH_DEVICE) \
	-out out/flash.cfg
	csoc download $(CSOC_DWL_OPTS) out/flash.cfg

#
# Download but do not run the users application
#	
csl: 
	csoc config $(CSOCOPTS) -nr \
	-mem $(FLASH_DEVICE) \
	-out out/csl.cfg
	csoc download $(CSOC_DWL_OPTS) out/csl.cfg

#
# Direct download to internal SRAM
#
internal: triscenda7.hex
	csoc config $(CSOCOPTS) -code out/triscenda7.hex \
	-mem none \
	-out out/internal.cfg
	csoc download $(CSOC_DWL_OPTS) out/internal.cfg


clean::
	@echo CLEAN
	@-rm -rf out

##
## EE Library
##

out/liberika.a: $(LIBOBJS)
	@echo AR  out/liberika.a
	$(ARM7AR) rs out/liberika.a $(addprefix out/,$(LIBOBJS))

##
## Locator files
##

out/triscend_a7s.ld: $(EEBASE)/etc/arm7/triscend_a7s.ld
	@test -d out || mkdir out
	@echo LOC
	@cp $(EEBASE)/etc/arm7/triscend_a7s.ld out

out/loc_triscend.ld: cfg_triscend.h
	@test -d out || mkdir out
	@echo AWK
	@awk '{ print $$2 " = " $$3 ";" }' < cfg_triscend.h >out/loc_triscend.ld

##
## Automatic Generation of dependencies
##

# deps contains all the dependencies
out/deps: $(patsubst %.S,%.Sd,$(patsubst %.c,%.cd,$(SRCS) $(LIBSRCS))) $(patsubst %.c,%.td,$(THUMB_SRCS))
	@echo GEN out/deps
	@cat $(addprefix out/, \
		$(patsubst %.S,%.Sd,$(patsubst %.c,%.cd,$(SRCS) $(LIBSRCS))) \
		$(patsubst %.c,%.td,$(THUMB_SRCS))) > out/deps

# generate dependencies for ARM .c files and add "file.cd" to the target
%.cd: %.c
	@test -d out || mkdir out
	$(VERBOSE_PRINTDEP)
	$(ARM7CC) $(OPTARM7CC) $(DEFSARM7CC) -M $< | sed "s/\($*\)\.o[ :]*/\1\.o $@: /g" > out/$@
	@test -s out/$@ || rm -f out/$@

# generate dependencies for THUMB .c files and add "file.td" to the target
%.td: %.c
	@test -d out || mkdir out
	$(VERBOSE_PRINTDEP)
	$(ARM7TCC) $(OPTARM7TCC) $(DEFSARM7TCC) -M $< | sed "s/\($*\)\.o[ :]*/\1\.o $@: /g" > out/$@
	@test -s out/$@ || rm -f out/$@

# generate dependencies for .S files and add "file.Sd" to the target
%.Sd: %.S
	@test -d out || mkdir out
	$(VERBOSE_PRINTDEP)
	$(ARM7CC) $(ALLINCPATH) $(DEFSARM7ASM) -M $< | sed "s/\($*\)\.o[ :]*/\1\.src $@: /g" > out/$@
	@test -s out/$@ || rm -f out/$@


ifdef DEPS
-include out/deps
endif

## Check default dependencies
include $(EEBASE)/config/check.mak


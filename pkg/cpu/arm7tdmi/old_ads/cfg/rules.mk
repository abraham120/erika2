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

## Author: 2001-2002 Paolo Gai, Alessandro Colantonio
## CVS: $Id: rules.mk,v 1.4 2007/06/01 09:00:21 pj Exp $



##
## Cygwin makefile for ARM Developer Suite (ADS)
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
BINDIR = $(ARM7BASE)/Bin

# uncomment the following line if you want assembly code into APPBASE/out
# and you want to debug with AXD
DEBUG = 1

# ALLINCPATH is a comma separated list of directories for source file searching
ALLINCPATH = $(shell cygpath -wsa "$(EEBASE)/include"),$(shell cygpath -wsa "$(APPBASE)")

# CodeWarrior Compilers
ARM7LINK="$(BINDIR)/armlink.exe"
ARM7ASM="$(BINDIR)/armasm.exe"
ARM7CC="$(BINDIR)/armcc.exe"
ARM7TCC="$(BINDIR)/tcc.exe"	# 16-bit thumb C compiler


## OPTARM7CC are the options for armcc invocation
## NOTE: -O2 don't work!
# -g  = add debug tables
# -O1 = select minimum optimization
# -c  = compile only (do not link)
# -j  = adds directories to the source file search path
OPTARM7CC = -O1 -c -j"$(ALLINCPATH)" -j- -apcs /interwork
ifeq ($(call iseeopt, DEBUG), yes)
OPTARM7CC += -g
endif
OPTARM7TCC = $(OPTARM7CC)

## OPTARM7ASM are the options for armasm invocation
# -g    = generate debug tables
# -i    = adds directories to the source file search path
OPTARM7ASM = -i "$(ALLINCPATH)" -apcs /interwork
ifeq ($(call iseeopt, DEBUG), yes)
OPTARM7ASM += -g
endif

# OPTARM7LINK represents the options for armlink invocation
OPTARM7LINK = 




# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...
OPTARM7CC += $(addprefix -D, $(EEOPT) )
OPTARM7TCC += $(addprefix -D, $(EEOPT) )

## NOTE: the symbol __ARM7ADS__ is useless
## NOTE: a symbol has to be always defined, so we have to know the whole symbols set
ALLSYMBOLS = DEBUG MONO MULTI FP_SCHED EDF_SCHED TIME_SUPPORT ALLOW_NESTED_IRQ \
		IRQ_STACK_NEEDED TIMER_1_USED TIMER_0_USED EXT0_USED

## WARNING!!!
## Because ADS does not accept a symbol that has the prefix '__' and
## it does not accept FP as a valid symbol, all the scheduler choice
## symbols are modified adding the '_SCHED' suffix
ifeq ($(call iseeopt, __FP__), yes)
TRUESYMBOLS = $(foreach SYM, $(subst __FP__,__FP_SCHED__,$(EEOPT)), $(subst __,,$(SYM)))
endif
ifeq ($(call iseeopt, __EDF__), yes)
TRUESYMBOLS = $(foreach SYM, $(subst __EDF__,__EDF_SCHED__,$(EEOPT)), $(subst __,,$(SYM)))
endif
FALSESYMBOLS = $(foreach SYM, $(ALLSYMBOLS), $(filter-out $(TRUESYMBOLS), $(SYM)))

OPTARM7ASM += $(foreach SYM, $(FALSESYMBOLS), -pd "$(SYM) SETL {FALSE}")
OPTARM7ASM += $(foreach SYM, $(TRUESYMBOLS), -pd "$(SYM) SETL {TRUE}")




#
# Kernel source
#
ARM7_VPATH = $(shell cygpath -wsa "$(EEBASE)/src/arm7ads")
ARM7_SRCS = drvinit.c insthand.c hal.s inthand.s start.s
OPTARM7ASM += -i "$(shell cygpath -wsa "$(EEBASE)/src/arm7ads")" # for symbols.s



# FP
ifeq ($(call iseeopt, __FP__), yes)
FP_VPATH = $(shell cygpath -wsa "$(EEBASE)/src/fp")
FP_SRCS = gettime.c irq_act.c irq_sc.c mutex.c \
	rq_exchg.c rq_inser.c schedule.c thact.c thendin.c thmkrdy.c
else
FP_VPATH =
FP_SRCS =
endif


# EDF
ifeq ($(call iseeopt, __EDF__), yes)
EDF_VPATH = $(shell cygpath -wsa "$(EEBASE)/src/edf")
EDF_SRCS = gettime.c irq_act.c irq_sc.c mutex.c \
	rq_exchg.c rq_inser.c schedule.c thact.c thendin.c thmkrdy.c
else
EDF_VPATH =
EDF_SRCS =
endif



#
# --------------------------------------------------------------------------
#

# Libraries

ifeq ($(call iseeopt, __CABS__), yes)
LIB_SRCS += cabs.c
LIB_VPATH += $(shell cygpath -wsa "$(EEBASE)/src/cabs")
endif

ifeq ($(call iseeopt, __SEM__), yes)

ifeq ($(call iseeopt, __MONO__), yes)
all::
	$(error Semaphores and Mono Stack HAL are not compatible!!!)
clean::
	$(error Semaphores and Mono Stack HAL are not compatible!!!)

endif

LIB_SRCS += swait.c spost.c sirqpost.c sgetvalue.c strywait.c
LIB_VPATH += $(shell cygpath -wsa "$(EEBASE)/src/sem")
endif

#
# --------------------------------------------------------------------------
#



##
## Common Rules
##

SRCS = $(ARM7_SRCS) $(FP_SRCS) $(EDF_SRCS) $(LIB_SRCS) $(APP_SRCS)
OBJS= $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRCS)))
THUMB_OBJS= $(patsubst %.c,%.to,$(THUMB_SRCS))

vpath %.axf out
vpath %.o out
vpath %.to out
vpath %.cd out
vpath %.sd out
vpath %.td out
vpath %.c $(ARM7_VPATH) $(FP_VPATH) $(EDF_VPATH) $(LIB_VPATH) $(APPBASE)
vpath %.s $(ARM7_VPATH) $(FP_VPATH) $(EDF_VPATH) $(LIB_VPATH) $(APPBASE)


%.o: %.c 
	@test -d out || mkdir out
	@echo
	$(ARM7CC) $(OPTARM7CC) "$<" -o "out/$(notdir $@)"

%.to: %.c 
	@test -d out || mkdir out
	@echo
	$(ARM7TCC) $(OPTARM7TCC) "$<" -o "out/$(notdir $@)"

%.o: %.s
	@test -d out || mkdir out
	@echo
	$(ARM7ASM) $(OPTARM7ASM) "$<" -o "out/$(notdir $@)"



##
## Main rules: all clean
##

.PHONY: all clean

all:: $(PROJ).axf

$(PROJ).axf: $(OBJS) $(THUMB_OBJS)
	$(ARM7LINK) -o out/$@ $(addprefix out/, $(OBJS) $(THUMB_OBJS))

clean::
	-rm -rf out



##
## Automatic Generation of dependencies
##

# deps contains all the dependencies
out/deps: $(patsubst %.s,%.sd,$(patsubst %.c,%.cd,$(SRCS)))
	cat $(addprefix out/, $(patsubst %.s,%.sd,$(patsubst %.c,%.cd,$(SRCS)))) > out/deps

# generate dependencies for .c files and add "file.cd" to the target
%.cd: %.c
	@test -d out || mkdir out
	@echo
	$(SHELL) -ec '$(ARM7CC) $(OPTARM7CC) -M "$<" \
		| sed "s/\($*\)\.o[ :]*/\1\.o $@: /g" > out/$@; \
		test -s out/$@ || rm -f out/$@'

# generate dependencies for THUMB .c files and add "file.td" to the target
%.td: %.c
	@test -d out || mkdir out
	@echo
	$(SHELL) -ec '$(ARM7TCC) $(OPTARM7TCC) -M "$<" \
		| sed "s/\($*\)\.o[ :]*/\1\.o $@: /g" > out/$@; \
		test -s out/$@ || rm -f out/$@'

# generate dependencies for .s files and add "file.sd" to the target
%.sd: %.s
	@test -d out || mkdir out
	@echo
	$(SHELL) -ec '$(ARM7ASM) $(OPTARM7ASM) "$<" -o "out/$(patsubst %.s,%.o,$(notdir $<))" -Depend out/$@t'
	test -s out/$@t && cat out/$@t | sed "s/\($*\)\.o[ :]*/\1\.o $@: /g" > out/$@
	-rm -f out/$@t
	test -s out/$@ || rm -f out/$@

-include out/deps

## Check default dependencies
include $(EEBASE)/config/check.mak

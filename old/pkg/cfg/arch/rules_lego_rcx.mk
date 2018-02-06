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

## Author: 2002 Davide Cantini
## CVS: $Id: rules_lego_rcx.mk,v 1.2 2007/06/01 09:00:21 pj Exp $

## Global paths
##

# H8BASE is the base directory of development environment
# it should be defined in your .bashrc
# H8BASE = 

# EEBASE is the base directory of the kernel
# it should be defined in your .bash_profile
# EEBASE = 

# APPBASE is the base directory of the application
APPBASE = $(CURDIR)

# BINDIR is the directory of assembler, compiler, linker...
BINDIR = $(H8BASE)/h8300-hitachi-hms/bin

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
ALLINCPATH = -I$(EEBASE)/include -I$(APPBASE)

# LOADFILE is the path of configuration file for ld command
ifeq ($(findstring __NO_ROM_DATA__, $(EEOPT)), __NO_ROM_DATA__)
LOADFILE = $(EEBASE)/etc/h8/h8cfgNRD.lds
else
LOADFILE = $(EEBASE)/etc/h8/h8cfgRD.lds
endif


# GNU compilers
H8LINK=$(BINDIR)/ld
H8ASM=$(BINDIR)/as
H8CC=$(BINDIR)/gcc
H8CPP=$(BINDIR)/gcc
H8AR=$(BINDIR)/ar

## OPTH8CC are the options for H8 gcc compiler invocation
# -O                = select the optimization level
#                     NOTE that -O0 can NOT be used because it not expands
#                     inline functions!!!!
# -c                = compile only (do not link)
# -Wall		    = all compiling warning
# -Winline	    = warn if a function does not expand inline
OPTH8CC = -O2 -Wall -Wno-unused -Winline -c $(ALLINCPATH)

# CPP: we MUST use -fno-rtti because if used the compiler generates a LOT of
# code :-(
OPTH8CPP = -O2 -Wall -Wno-unused -Winline -fno-rtti -c $(ALLINCPATH)

## OPTH8ASM are the options for H8 asm invocation
OPTH8ASM = 

# OPTH8LINK represents the options for H8 link invocation
OPTH8LINK =  -T$(LOADFILE) -u__start

# OPTH8LIBS is used to link additional libraries (e.g., for C++ support)
OPTH8LIBS = -lerika -L $(APPBASE)/out


# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...
OPTH8ASM += $(foreach SYM, $(EEOPT), --defsym $(SYM)=1)
OPTH8CC += $(addprefix -D, $(EEOPT) )
OPTH8CPP += $(addprefix -D, $(EEOPT) )



#
# Kernel source
#
H8_VPATH = $(EEBASE)/src/h8
H8_SRCS = hal.s start.s drivers.s func_d.c
ifeq ($(findstring TRIG_USED__, $(EEOPT)), TRIG_USED__)
H8_SRCS += fmath.s
else
ifeq ($(findstring FIXED_USED__, $(EEOPT)), FIXED_USED__)
H8_SRCS += fmath.s
endif
endif


OPTH8ASM += -I$(EEBASE)/src/h8 # for symbols.s
OPTH8ASM += -I$(EEBASE)/include/h8 # for handstub.s


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


#
# --------------------------------------------------------------------------
#

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

//H8_SRCS += oo.S
EEOPT += __OO__

# irqendin.c
else
KERN_VPATH +=
KERN_SRCS +=
endif


#
# --------------------------------------------------------------------------
#

# Libraries

ifeq ($(findstring __CPP__,$(EEOPT)) , __CPP__)
OPTH8LIBS += -L $(H8BASE)/lib/gcc-lib/h8300-hitachi-hms/2.95.2 -lgcc
endif

ifeq ($(findstring __LIBC__,$(EEOPT)) , __LIBC__)
ALLINCPATH += -I$(EEBASE)/include/libc
LIB_SRCS += abort.c memset.c strcmp.c
#LIB_SRCS += abort.c free.c malloc.c memset.c strcmp.c
LIB_VPATH += $(EEBASE)/src/libc/string $(EEBASE)/src/libc/stdlib
endif

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



#
# --------------------------------------------------------------------------
#

##
## Common Rules
##

SRCS = $(APP_SRCS)
OBJS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRCS))))

LIBSRCS = $(H8_SRCS) $(KERN_SRCS) $(LIB_SRCS)
LIBOBJS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(LIBSRCS))))

vpath %.o out
vpath %.srec out
vpath %.c $(H8_VPATH) $(KERN_VPATH) $(LIB_VPATH) $(APPBASE)
vpath %.s $(H8_VPATH) $(KERN_VPATH) $(LIB_VPATH) $(APPBASE)


%.o: %.s
	@test -d out || mkdir out
	@echo
	$(H8ASM) $(OPTH8ASM) $< -o out/$(notdir $@) 

%.o: %.c 
	@test -d out || mkdir out
	@echo
	$(H8CC) $(OPTH8CC) $< -o out/$(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(H8CC) $(OPTH8CC) $< -S -o out/$(notdir $(patsubst %.o,%.S,$@))
endif

%.o: %.cpp 
	@test -d out || mkdir out
	@echo
	$(H8CPP) $(OPTH8CPP) $< -o out/$(notdir $@)
ifeq ($(findstring DEBUG,$(EEOPT)) , DEBUG)
	$(H8CPP) $(OPTH8CPP) $< -S -o out/$(notdir $(patsubst %.o,%.S,$@))
endif


##
## Main rules: all clean
##

.PHONY: all clean

all:: h8.srec

h8.srec: $(OBJS) out/liberika.a
	$(H8LINK) $(OPTH8LINK) -o out/$@ -Map out/h8.map $(addprefix out/, $(OBJS)) --start-group $(OPTH8LIBS) --end-group

clean::
	-rm -rf out

##
## EE Library
##

out/liberika.a: $(LIBOBJS)
	$(H8AR) rs out/liberika.a $(addprefix out/,$(LIBOBJS))





## Check default dependencies
include $(EEBASE)/config/check.mak

## Check H8 specific dependencies and errors

##ifeq ($(findstring __PLAY_BUFFER_SUPPORT__,$(EEOPT)), __PLAY_BUFFER_SUPPORT__)
##ifeq ($(findstring __PLAY_NOTE_SUPPORT__,$(EEOPT)), __PLAY_NOTE_SUPPORT__)
##    $(error don't use __PLAY_BUFFER_SUPPORT__ and __PLAY_NOTE_SUPPORT__ together)
##endif
##endif

ifeq ($(findstring __MOTOR_B_PWM_USED__,$(EEOPT)), __MOTOR_B_PWM_USED__)
    $(error Solo i motori A e C possono essere controllati con tecnica PWM)
endif


###########################################
##### AUTO GENERATED MACRO
###########################################

# the following lines automatically add a set of symbols to the main
# EEOPT symbol

ifeq ($(findstring PWM_USED__,$(EEOPT)), PWM_USED__)
    EEOPT += __MOTOR_PWM_SUPPORT__
    EEOPT += __T81_SUPPORT__
endif

ifeq ($(findstring VP_USED__,$(EEOPT)), VP_USED__)
    EEOPT += __MOTOR_VP_SUPPORT__
endif 

ifeq ($(findstring __PLAY_BUFFER_SUPPORT__,$(EEOPT)), __PLAY_BUFFER_SUPPORT__)
EEOPT += __T80_SUPPORT__
else
ifeq ($(findstring __PLAY_NOTE_SUPPORT__,$(EEOPT)), __PLAY_NOTE_SUPPORT__)
EEOPT += __T80_SUPPORT__
endif 
endif

ifeq ($(findstring __PLAY_BUFFER_SUPPORT__,$(EEOPT)), __PLAY_BUFFER_SUPPORT__)
EEOPT += __TIMER_B_SUPPORT__
else
ifeq ($(findstring __PLAY_NOTE_SUPPORT__,$(EEOPT)), __PLAY_NOTE_SUPPORT__)
EEOPT += __TIMER_B_SUPPORT__
else
ifeq ($(findstring __MOTOR_VP_SUPPORT__,$(EEOPT)), __MOTOR_VP_SUPPORT__)
EEOPT += __TIMER_B_SUPPORT__
else
ifeq ($(findstring __TIMER_B_USER_FUNCTION_USED__,$(EEOPT)), __TIMER_B_USER_FUNCTION_USED__)
EEOPT += __TIMER_B_SUPPORT__
endif
endif
endif
endif


ifeq ($(findstring __TIMER_A_USER_FUNCTION_USED__,$(EEOPT)), __TIMER_A_USER_FUNCTION_USED__)
EEOPT += __TIMER_A_SUPPORT__
endif


ifeq ($(findstring __SF_HIGH_SPEED_TRIG_USED__,$(EEOPT)), __SF_HIGH_SPEED_TRIG_USED__)
ifneq ($(findstring __SF_TRIG_USED__,$(EEOPT)), __SF_TRIG_USED__)
EEOPT += __SF_TRIG_USED__ 
endif
endif

ifeq ($(findstring __DF_HIGH_SPEED_TRIG_USED__,$(EEOPT)), __DF_HIGH_SPEED_TRIG_USED__)
ifneq ($(findstring __DF_TRIG_USED__,$(EEOPT)), __DF_TRIG_USED__)
EEOPT += __DF_TRIG_USED__
endif
endif

ifeq ($(findstring __SF_TRIG_USED__,$(EEOPT)), __SF_TRIG_USED__)
ifneq ($(findstring __SIGNED_FIXED_USED__,$(EEOPT)), __SIGNED_FIXED_USED__)
EEOPT += __SIGNED_FIXED_USED__ 
endif
endif

ifeq ($(findstring __DF_TRIG_USED__,$(EEOPT)), __DF_TRIG_USED__)
ifneq ($(findstring __DOUBLE_FIXED_USED__,$(EEOPT)), __DOUBLE_FIXED_USED__)
EEOPT += __DOUBLE_FIXED_USED__ 
endif
endif

ifeq ($(findstring _FIXED_USED__,$(EEOPT)), _FIXED_USED__)
EEOPT += __FMATH_SUPPORT__
endif


######  END OF AUTO GENERATED MACRO  ##############

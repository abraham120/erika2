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

## Author: 2001 Paolo Gai, Enrico Bini
## CVS: $Id: rules_ertec_eva167.mk,v 1.2 2007/06/01 09:00:21 pj Exp $

# C166BASE is the base directory of development environment
# it should be defined in your .bash_profile
# C166BASE=/cygdrive/c/programmi/c166

# EEBASE is the base directory of the kernel
# it should be defined in your .bash_profile
# EEBASE=/cygdrive/d/ee

EEOPT += __LITTLE__

# APPBASE is the base directory of the application
APPBASE = $(CURDIR)

# BINDIR is the directory of assembler, compiler, linker...
BINDIR = $(C166BASE)/bin

# M166INC is the include directory for the macro assembly preprocessor
ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)

ifeq ($(findstring __MONO__,$(EEOPT)) , __MONO__)
M166INC = $(shell cygpath -wa $(EEBASE)/include/st10mono/)
endif
ifeq ($(findstring __MULTI__,$(EEOPT)) , __MULTI__)
M166INC = $(shell cygpath -wa $(EEBASE)/include/st10mono/)
endif

endif


ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
ifeq ($(findstring __MULTI__,$(EEOPT)) , __MULTI__)
M166INC = $(shell cygpath -wa $(EEBASE)/include/st10segm/)
endif
endif

export M166INC

# INCDIR is the include directory for the C compiler
# Not used!!!
# INCDIR = $(subst /,\,$(EEBASE)/include);$(APPBASE)

# TASKING Compilers and Macro processors
M166=$(BINDIR)/m166.exe
A166=$(BINDIR)/a166.exe
C166=$(BINDIR)/c166.exe
CC166=$(BINDIR)/cc166.exe

# do not display too much things...
ifndef VERBOSE
M166:=@$(M166)
A166:=@$(A166)
C166:=@$(C166)
CC166:=@$(CC166)

VERBOSE_DEVNULL=
VERBOSE_PRINTDEP=@echo DEP $<
VERBOSE_PRINTCC=@echo CC  $<
VERBOSE_PRINTCPP=@echo CPP $<
VERBOSE_PRINTASM=@echo ASM $<
VERBOSE_PRINTSRC=@echo SRC $<
VERBOSE_PRINTMACRO=@echo MACRO $<

else
VERBOSE_DEVNULL=>/dev/null
VERBOSE_PRINTDEP=@echo
VERBOSE_PRINTCC=@echo
VERBOSE_PRINTCPP=@echo
VERBOSE_PRINTASM=@echo
VERBOSE_PRINTMACRO=@echo
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



# OPTM166 are the options for m166 invocation
OPTM166 = WA\(2\)


# OPTC166 are the options for c166 invocation
# -Ac = enable character arithmetic
# -Ad = dont initialize data to zero
# -Af = pointer comparison on 14-bit
# -Ai = allow inlining
# -Ak = recognize C-language extensions
# -Al = identifiers can be 500 characters long
# -Am = use sensefully DIVL assembly instruction
# -As = __STDC__ is defined as '0'
# -Au = reduce data size
# -Aptvx = relax many strict ANSI-C checks
# -Bb = dont place NOP after each instr
# -Bd = divide not protected against interrupt
# -BE = extend sequence... boh?
# -Bi = dont place BFLDH PSW,#0F0h, #0F0h befoer RETI
# -Bm = multiply/divide not protected against interrupt
# -Bu = multiply not protected against interrupt
# -xmifp = use the C167 extensions
# -Mt = model tiny
# -c0 = allocate 0 bytes for Common Subexpressions Elimination on user stack
# -s = merge C source code with assembly
# -t = produce the total on stdout
# -Oaw = relax alias cheking
# -Ob = dont clear non-initialized data
# -OC = disable Common Subexpressions Elimination
# -Od = enable constant and copy propagation
# -OE = allocate ROM data in LDAT sections
# -Of = faster and larger code
# -Og = optimize code for expressions
# -Oh = optimize interrupt frame code
# -Oj = remove redundant code
# -Ok = reuse register contents if possible
# -Ol = fast loops. Faster and larger code for loops
# -On = allow the peephole optimizer to remove NOP
# -Oo = enable code rearranging in flow optimization
# -Op = enable jump optimizations
# -Oq = treat casting pointer to long equal to casting to a far pointer
# -Or = enable variables in registers
# -OS = optimize switch instructions
# -OT = use id when tiny or small model
# -OU = use system stack for interrupt
# -Ox = compiler performs the extra inlining
# -znocustack = suppress user stack estimation
# -zautobitastruct-4 = optimize the use of bitaddressable memory
# -zautobita-0 = dont move char in bitaddressable memory
# -gfl = incorporate information for debbugging
#OPTC166 = -I$(subst \,\\,$(shell cygpath -wa $(C166BASE)/include))  \
#          -I$(subst \,\\,$(shell cygpath -wa $(EEBASE)/include)) \
#          -I$(subst \,\\,$(shell cygpath -wa $(APPBASE)))           \
#          -BbdEimu -xmifp -c0 -s -t                                 \
#          -znocustack -zautobitastruct-4 -zautobita-0               \
#          -gfl -AcDfiklmpstuvx -OabCdEfghjklnopqrSUwx

OPTC166 = -I$(subst \,\\,$(shell cygpath -wa $(C166BASE)/include))  \
          -I$(subst \,\\,$(shell cygpath -wa $(EEBASE)/include)) \
          -I$(subst \,\\,$(shell cygpath -wa $(APPBASE)))           \
          -xmifp -OB -zautobitastruct-4 -zautobita-0 -s -g -A1 -O1


ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
  OPTC166 += -Ml -Ot -P
else
  OPTC166 += -Mt -OT
endif

# OPTA166 are the options for a166 invocation
OPTA166=PL\(60\) PW\(132\) TA\(8\) WA\(1\) EX NOM166 SN\(reg167.def\)

# OPTOUT are the options for cc166 when making .out
OPTOUT=	-cf -xmifp
ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
  OPTOUT += -Ml
else
  OPTOUT += -Mt
endif


#
# --------------------------------------------------------------------------
#

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

# check if we are compiling __EDF__ with __TIME_SUPPORT__. If not,
# the define is automatically added

ifeq ($(findstring __EDF__,$(EEOPT)) , __EDF__)
	ifeq ($(findstring __TIME_SUPPORT__,$(EEOPT)) , __TIME_SUPPORT__)
	else
		EEOPT += __TIME_SUPPORT__
	endif
endif

OPTC166 += $(addprefix -D, $(EEOPT) )


# The M166 preprocessor wants every symbol to be defined at least true or false.
# Here, we have to add to the defined symbols ore the false symbols used into
# the Assembler code :-(

OPTM166 += $(foreach d, $(EEOPT), DEF\($(d)\) )


ASMSYMBOLS = __ALLOW_NESTED_IRQ__
FALSESYMBOLS = $(foreach SYM, $(ASMSYMBOLS), $(filter-out $(EEOPT), $(SYM)))

#OPTM166 += $(foreach d, $(FALSESYMBOLS), DEF\($(d),0\) )



#
# --------------------------------------------------------------------------
#

# Objects

ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)

ifeq ($(findstring __MONO__,$(EEOPT)) , __MONO__)
ST10MONO_SRCS= $(EEBASE)/src/st10mono/start.asm  \
               $(EEBASE)/src/st10mono/main.c

ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)
	ST10MONO_SRCS+= $(EEBASE)/src/st10mono/hal_optimized.asm
else
	ST10MONO_SRCS+= $(EEBASE)/src/st10mono/hal.asm
endif

ST10MONO_VPATH=$(EEBASE)/src/st10mono
else
ST10MONO_SRCS=
ST10MONO_VPATH=
endif

ifeq ($(findstring __MULTI__,$(EEOPT)) , __MULTI__)
ST10MULT_SRCS= $(EEBASE)/src/st10mono/start.asm  \
               $(EEBASE)/src/st10mono/main.c

ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)
	ST10MULT_SRCS+= $(EEBASE)/src/st10mono/hal_optimized.asm
else
	ST10MULT_SRCS+= $(EEBASE)/src/st10mono/hal.asm
endif

ST10MULT_VPATH=$(EEBASE)/src/st10mono
else
ST10MULT_SRCS=
ST10MULT_VPATH=
endif

endif

ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
ST10SEGM_SRCS= $(EEBASE)/src/st10segm/func.asm   \
               $(EEBASE)/src/st10segm/start.asm  \
               $(EEBASE)/src/st10segm/main.c

ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)
else
	ST10SEGM_SRCS+=  $(EEBASE)/src/st10segm/nopt.asm
endif

ST10SEGM_VPATH=$(EEBASE)/src/st10segm
else
ST10SEGM_SRCS=
ST10SEGM_VPATH=
endif


ifeq ($(findstring __FP__,$(EEOPT)) , __FP__)
KERN_SRCS += $(EEBASE)/src/fp/gettime.c          \
         $(EEBASE)/src/fp/irq_act.c          \
         $(EEBASE)/src/fp/rq_exchg.c         \
         $(EEBASE)/src/fp/rq_inser.c         \
         $(EEBASE)/src/fp/schedule.c         \
         $(EEBASE)/src/fp/thact.c            \
         $(EEBASE)/src/fp/thmkrdy.c          

  ifneq ($(findstring __FP_NO_MUTEX__,$(EEOPT)) , __FP_NO_MUTEX__)
  KERN_SRCS += $(EEBASE)/src/edf/mutex.c
  endif


ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)
  OPT_SRCS += $(APPBASE)/opt/optirqsc.opt \
              $(APPBASE)/opt/optthend.opt
else
	KERN_SRCS+= $(EEBASE)/src/fp/irq_sc.c        \
		  $(EEBASE)/src/fp/thendin.c
endif

KERN_VPATH+=$(EEBASE)/src/fp

endif

ifeq ($(findstring __EDF__,$(EEOPT)) , __EDF__)
KERN_SRCS += $(EEBASE)/src/edf/gettime.c          \
           $(EEBASE)/src/edf/irq_act.c          \
           $(EEBASE)/src/edf/rq_exchg.c         \
           $(EEBASE)/src/edf/rq_inser.c         \
           $(EEBASE)/src/edf/schedule.c         \
           $(EEBASE)/src/edf/thact.c            \
           $(EEBASE)/src/edf/thmkrdy.c


  ifneq ($(findstring __EDF_NO_MUTEX__,$(EEOPT)) , __EDF_NO_MUTEX__)
  KERN_SRCS += $(EEBASE)/src/edf/mutex.c
  endif


ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)
  OPT_SRCS += $(APPBASE)/opt/optirqsc.opt \
              $(APPBASE)/opt/optthend.opt
else
	KERN_SRCS+= $(EEBASE)/src/edf/irq_sc.c \
	            $(EEBASE)/src/edf/thendin.c
endif

KERN_VPATH+=$(EEBASE)/src/edf

endif



# OO

ifeq ($(OO), YES)
KERN_VPATH += $(EEBASE)/src/oo
KERN_SRCS += activate.c schedule.c force_schedule.c terminat.c \
	     tstub.c lookup.c \
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

ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)
  OPT_SRCS += $(APPBASE)/opt/optirqsc.opt \
              $(APPBASE)/opt/optthend.opt

else
	KERN_SRCS+= $(EEBASE)/src/oo/irqendin.c \
	            $(EEBASE)/src/oo/thendin.c
endif

# aggiungere il codice particolare per OO...

# irqendin.c
else
KERN_VPATH +=
KERN_SRCS +=
endif


#
# --------------------------------------------------------------------------
#

# Libraries


#######################################
#   COMMUNICATION INTER/INTRA NODE    #
#######################################

########### COM CCCA #############
ifeq ($(findstring __COM_CCCA__,$(EEOPT)) , __COM_CCCA__) 
	LIB_SRCS += $(EEBASE)/src/com/com/filters.c 
	LIB_SRCS += $(EEBASE)/src/com/com/initmessage.c 
	LIB_SRCS += $(EEBASE)/src/com/com/memo.c 
	LIB_SRCS += $(EEBASE)/src/com/com/msgreception.c 
	LIB_SRCS += $(EEBASE)/src/com/com/shared_send.c 
	LIB_SRCS += $(EEBASE)/src/com/com/cominit.c
	LIB_SRCS += $(EEBASE)/src/com/com/startcom.c
	LIB_SRCS += $(EEBASE)/src/com/com/stopcom.c  
	LIB_SRCS += $(EEBASE)/src/com/com/sendstatic.c
	LIB_SRCS += $(EEBASE)/src/com/com/receivestatic.c
	LIB_VPATH += $(EEBASE)/src/com/com/
endif

########### COM CCCB #############
ifeq ($(findstring __COM_CCCB__,$(EEOPT)) , __COM_CCCB__) 
	LIB_SRCS += $(EEBASE)/src/com/com/filters.c 
	LIB_SRCS += $(EEBASE)/src/com/com/initmessage.c 
	LIB_SRCS += $(EEBASE)/src/com/com/memo.c 
	LIB_SRCS += $(EEBASE)/src/com/com/msgreception.c 
	LIB_SRCS += $(EEBASE)/src/com/com/msgstatus.c
	LIB_SRCS += $(EEBASE)/src/com/com/shared_send.c  
	LIB_SRCS += $(EEBASE)/src/com/com/cominit.c
	LIB_SRCS += $(EEBASE)/src/com/com/receivestatic.c
	LIB_SRCS += $(EEBASE)/src/com/com/startcom.c
	LIB_SRCS += $(EEBASE)/src/com/com/stopcom.c  
	LIB_SRCS += $(EEBASE)/src/com/com/sendstatic.c
	LIB_VPATH += $(EEBASE)/src/com/com
endif

########### COM CCC0 #############
ifeq ($(findstring __COM_CCC0__,$(EEOPT)) , __COM_CCC0__) 
	LIB_SRCS += $(EEBASE)/src/com/com/com_indication.c
	LIB_SRCS += $(EEBASE)/src/com/com/com_confirm.c
	LIB_SRCS += $(EEBASE)/src/com/com/convert.c
	LIB_SRCS += $(EEBASE)/src/com/com/filters.c 
	LIB_SRCS += $(EEBASE)/src/com/com/initmessage.c 
	LIB_SRCS += $(EEBASE)/src/com/com/memo.c 
	LIB_SRCS += $(EEBASE)/src/com/com/msgreception.c 
	LIB_SRCS += $(EEBASE)/src/com/com/hmonitor.c
	LIB_SRCS += $(EEBASE)/src/com/com/shared_send.c  
	LIB_SRCS += $(EEBASE)/src/com/com/cominit.c
	LIB_SRCS += $(EEBASE)/src/com/com/queue_TM.c
	LIB_SRCS += $(EEBASE)/src/com/com/receivestatic.c
	LIB_SRCS += $(EEBASE)/src/com/com/startcom.c
	LIB_SRCS += $(EEBASE)/src/com/com/stopcom.c  
	LIB_SRCS += $(EEBASE)/src/com/com/sendstatic.c
	LIB_SRCS += $(EEBASE)/src/com/com/tmonitor.c
	LIB_VPATH += $(EEBASE)/src/com/com
endif

########### COM CCC1 #############
ifeq ($(findstring __COM_CCC1__,$(EEOPT)) , __COM_CCC1__) 
	LIB_SRCS += $(EEBASE)/src/com/com/com_indication.c
	LIB_SRCS += $(EEBASE)/src/com/com/com_confirm.c
	LIB_SRCS += $(EEBASE)/src/com/com/convert.c
	LIB_SRCS += $(EEBASE)/src/com/com/dmonitor.c
	LIB_SRCS += $(EEBASE)/src/com/com/filters.c 
	LIB_SRCS += $(EEBASE)/src/com/com/hmonitor.c
	LIB_SRCS += $(EEBASE)/src/com/com/initmessage.c 
	LIB_SRCS += $(EEBASE)/src/com/com/memo.c 
	LIB_SRCS += $(EEBASE)/src/com/com/msgreception.c 
	LIB_SRCS += $(EEBASE)/src/com/com/msgstatus.c
	LIB_SRCS += $(EEBASE)/src/com/com/notify_error.c
	LIB_SRCS += $(EEBASE)/src/com/com/shared_send.c  
	LIB_SRCS += $(EEBASE)/src/com/com/cominit.c
	LIB_SRCS += $(EEBASE)/src/com/com/pmonitor.c
	LIB_SRCS += $(EEBASE)/src/com/com/queue_DM.c
	LIB_SRCS += $(EEBASE)/src/com/com/queue_TM.c
	LIB_SRCS += $(EEBASE)/src/com/com/queue_PM.c
	LIB_SRCS += $(EEBASE)/src/com/com/receivedynamic.c
	LIB_SRCS += $(EEBASE)/src/com/com/receivestatic.c
	LIB_SRCS += $(EEBASE)/src/com/com/senddynamic.c
	LIB_SRCS += $(EEBASE)/src/com/com/sendstatic.c 
	LIB_SRCS += $(EEBASE)/src/com/com/sendzero.c 
	LIB_SRCS += $(EEBASE)/src/com/com/startcom.c 
	LIB_SRCS += $(EEBASE)/src/com/com/startperiodic.c
	LIB_SRCS += $(EEBASE)/src/com/com/stopcom.c 
	LIB_SRCS += $(EEBASE)/src/com/com/stopperiodic.c
	LIB_SRCS += $(EEBASE)/src/com/com/tmonitor.c
	LIB_VPATH += $(EEBASE)/src/com/com
endif

########### ISO15765 NETWORK LAYER ################
ifeq ($(findstring __ISO15765__,$(EEOPT)) , __ISO15765__)
	LIB_SRCS += $(EEBASE)/src/com/iso15765/init_net.c 
	LIB_SRCS += $(EEBASE)/src/com/iso15765/request.c 
	LIB_SRCS += $(EEBASE)/src/com/iso15765/confirm.c 
	LIB_SRCS += $(EEBASE)/src/com/iso15765/monitor.c 
	LIB_SRCS += $(EEBASE)/src/com/iso15765/indication.c
	LIB_VPATH += $(EEBASE)/src/com/iso15765
endif

########### PSA NETWORK LAYER ################
### PSA MASTER NODE ###
ifeq ($(findstring __PSA_MASTER__,$(EEOPT)) , __PSA_MASTER__)
	LIB_SRCS += $(EEBASE)/src/com/psa/master/dispatcher.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/edf_sched.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_confirm.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_indication.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_init.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_padd.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_prem.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_sadd.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_srem.c
	LIB_SRCS += $(EEBASE)/src/com/psa/master/psa_start.c
	LIB_VPATH += $(EEBASE)/src/com/psa/master/
endif

### FTT SLAVE NODE ###
ifeq ($(findstring __FTT_SLAVE__,$(EEOPT)) , __FTT_SLAVE__)
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/AMS_receive.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/AMS_send.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ART_add.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ART_change.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ART_remove.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/Asearch.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/buf_req.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ftt_confirm.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ftt_indication.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ftt_init.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ftt_set_handler.asm
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ftt_start.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/ftt_transmitter.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/NRT_receive.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/NRT_send.c   
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/NRTRsearch.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/NRTTsearch.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/SMS_consume.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/SMS_produce.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/SRT_add.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/SRT_change.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/SRT_remove.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/Ssearch.c
	LIB_SRCS += $(EEBASE)/src/com/ftt/slave/stop_asynch.c
	LIB_VPATH += $(EEBASE)/src/com/ftt/slave/
endif

############ DATA LINK LAYER ###################
ifeq ($(findstring __DLC_STANDARD__,$(EEOPT)) , __DLC_STANDARD__)
	LIB_SRCS += $(EEBASE)/src/com/dlc/canst10.c
	LIB_SRCS += $(EEBASE)/src/com/dlc/can_handler.c
	LIB_SRCS += $(EEBASE)/src/com/dlc/can_driver.c
	LIB_SRCS += $(EEBASE)/src/com/dlc/init_can.c
	LIB_SRCS += $(EEBASE)/src/com/dlc/transmit.c
	LIB_SRCS += $(EEBASE)/src/com/dlc/irqcanst10.asm
	LIB_VPATH += $(EEBASE)/src/com/dlc
endif

############ REAL-TIME DATA LINK LAYER ###################
ifeq ($(findstring __RT_DLC_STANDARD__,$(EEOPT)) , __RT_DLC_STANDARD__)
	LIB_SRCS += $(EEBASE)/src/com/rtdlc/canst10.c
	LIB_SRCS += $(EEBASE)/src/com/rtdlc/can_handler.c
	LIB_SRCS += $(EEBASE)/src/com/rtdlc/can_driver.c
	LIB_SRCS += $(EEBASE)/src/com/rtdlc/init_can.c
	LIB_SRCS += $(EEBASE)/src/com/rtdlc/transmit.c
	LIB_SRCS += $(EEBASE)/src/com/rtdlc/irqcanst10.asm
	LIB_VPATH += $(EEBASE)/src/com/rtdlc
endif

#################################################################################################

ifeq ($(findstring __ASSERT__,$(EEOPT)) , __ASSERT__)
LIB_SRCS += assert.c
LIB_VPATH += $(EEBASE)/src/assert
endif

ifeq ($(findstring __CABS__,$(EEOPT)) , __CABS__)
LIB_SRCS += $(EEBASE)/src/cabs/cabs.c
LIB_VPATH += $(EEBASE)/src/cabs
endif

ifeq ($(findstring __SEM__,$(EEOPT)) , __SEM__)

ifeq ($(findstring __MONO__,$(EEOPT)) , __MONO__)
all::
	$(error Semaphores and Mono Stack HAL are not compatible!!!)
clean::
	$(error Semaphores and Mono Stack HAL are not compatible!!!)
endif

LIB_SRCS += $(EEBASE)/src/sem/swait.c \
            $(EEBASE)/src/sem/spost.c \
            $(EEBASE)/src/sem/sirqpost.c \
            $(EEBASE)/src/sem/sgetvalue.c \
            $(EEBASE)/src/sem/strywait.c
LIB_VPATH += $(EEBASE)/src/sem
endif

ifeq ($(findstring __ALARMS__,$(EEOPT)) , __ALARMS__)
LIB_SRCS += alcancel.c altick.c alget.c alsetabs.c alsetrel.c
LIB_VPATH += $(EEBASE)/src/alarms
endif

ifeq ($(findstring __HARD_ALARMS__,$(EEOPT)) , __HARD_ALARMS__)
LIB_SRCS += alcancel.c alget.c alinsert.c alsetabs.c alsetrel.c altimer.c
LIB_VPATH += $(EEBASE)/src/hard_alarms
endif

#
# --------------------------------------------------------------------------
#

# Common Rules

SRCS= $(ST10MONO_SRCS) $(ST10MULT_SRCS) $(ST10SEGM_SRCS) $(KERN_SRCS) $(LIB_SRCS) $(APP_SRCS) $(OPT_SRCS)

OBJS= $(patsubst %.c,%.obj,$(patsubst %.asm,%.obj,$(patsubst %.opt,%.obj,$(SRCS))))

LOCALOBJS=$(notdir $(OBJS))

SRCS_VPATH= $(ST10MONO_VPATH) $(ST10MULT_VPATH) $(ST10SEGM_VPATH) \
            $(KERN_VPATH) $(LIB_VPATH) $(APPBASE)

vpath %.abs out
vpath %.out out
vpath %.obj out
vpath %.src out
vpath %.opt opt
vpath %.c   $(SRCS_VPATH)
vpath %.asm $(SRCS_VPATH)

%.obj : %.src
	$(VERBOSE_PRINTASM)
	$(A166) out\\$(notdir $<) $(OPTA166) PRINT\(out\\$(notdir $(basename $<)).lst\) TO out\\$(notdir $@)

%.obj: %.opt
	$(VERBOSE_PRINTASM)
	$(A166) opt\\$(notdir $<) $(OPTA166) PRINT\(out\\$(notdir $(basename $<)).lst\) TO out\\$(notdir $@)

%.src : %.c 
	$(VERBOSE_PRINTCC)
	$(C166) $(subst \,\\,$(shell cygpath -wa $<)) $(OPTC166) -o out\\$(subst /,\\,$(notdir $@))

%.src : %.asm 
	$(VERBOSE_PRINTMACRO)
	$(M166) $(subst \,\\,$(shell cygpath -wa $<)) $(OPTM166) TO out\\$(subst /,\\,$(notdir $@))

#vpath %.s out
#
#%.s : %.asm 
#	$(C166) $(subst \,\\,$(shell cygpath -wa $<)) $(OPTC166) -E  -o out\\$(subst /,\\,$(notdir $@))
#
#%.src : %.s 
#	$(M166) out\\$(notdir $<) $(OPTM166) TO out\\$(subst /,\\,$(notdir $@))

#
# --------------------------------------------------------------------------
#

# Main rules: all clean

.PHONY :all clean

all         :: out $(OPT_SRCS) st10.abs

st10.abs : st10.out
	@echo ABS
	@$(BINDIR)/ieee166.exe out\\$< out\\$@

st10.out : $(LOCALOBJS) _st10.ilo
	@echo LINK
	$(CC166) -o out/$@ $(subst /,\\,$(addprefix out/, $(LOCALOBJS))) _st10.ilo $(OPTOUT)

clean       ::
	@echo CLEAN
	@rm -rf out

# The output directory!!!
out:
	@echo out
	@mkdir out

# --------------------------------------------------
# Optimized versions of the termination primitives

ifeq ($(findstring __ST10_OPTIMIZED__,$(EEOPT)) , __ST10_OPTIMIZED__)

$(OPT_SRCS):
	$(error Error: __ST10_OPTIMIZED__ is specified into EEOPT but $@ does not exist. Read $(EEBASE)/config/st10opt.txt for details...) 

opt:
	mkdir opt

ifeq ($(findstring __FP__,$(EEOPT)) , __FP__)
opt_srcs:
	$(C166) $(subst \,\\,$(shell cygpath -wa $(EEBASE)/src/fp/irq_sc.c)) $(OPTC166) -o opt\\optirqsc.opt
	$(C166) $(subst \,\\,$(shell cygpath -wa $(EEBASE)/src/fp/thendin.c)) $(OPTC166) -o opt\\optthend.opt
endif

ifeq ($(findstring __EDF__,$(EEOPT)) , __EDF__)
opt_srcs:
	$(C166) $(subst \,\\,$(shell cygpath -wa $(EEBASE)/src/edf/irq_sc.c)) $(OPTC166) -o opt\\optirqsc.opt
	$(C166) $(subst \,\\,$(shell cygpath -wa $(EEBASE)/src/edf/thendin.c)) $(OPTC166) -o opt\\optthend.opt
endif

ifeq ($(OO), YES)
opt_srcs:
	$(C166) $(subst \,\\,$(shell cygpath -wa $(EEBASE)/src/oo/irqendin.c)) $(OPTC166) -o opt\\optirqsc.opt
	$(C166) $(subst \,\\,$(shell cygpath -wa $(EEBASE)/src/oo/thendin.c)) $(OPTC166) -o opt\\optthend.opt
endif

st10_opt: opt opt_srcs
	@echo --------------------------------------------------------------------
	@echo
	@echo
	@echo
	@echo Now,
	@echo \(1\) remove all the assembler lines that contains R0 
	@echo from the files into the 
	@echo $(APPBASE)/opt 
	@echo directory, and 
	@echo
	@echo \(2\) substitute the last RETN or RETS with RETV...
	@echo \(Maybe some SED expert would have done a batch substitution...
	@echo ...anyone can help me?\)

else

opt:
	$(error opt target only available when __ST10_OPTIMIZED__ is specified)

endif


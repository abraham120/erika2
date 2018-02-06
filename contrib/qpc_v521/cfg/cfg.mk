# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2014  Evidence Srl
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

##QPC Version 5.2.1
## Author: 2014 Gianluca Franchino



ifeq ($(call iseeopt, __LIB_QPC_V521__), yes)

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/qpc_v521/inc)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/qpc_v521/inc/qep)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/qpc_v521/inc/qf)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/qpc_v521/inc/qs)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/qpc_v521/inc/ports/erika)"
else
ALLINCPATH += -I$(EEBASE)/contrib/qpc_v521/inc
ALLINCPATH += -I$(EEBASE)/contrib/qpc_v521/inc/qep
ALLINCPATH += -I$(EEBASE)/contrib/qpc_v521/inc/qf
ALLINCPATH += -I$(EEBASE)/contrib/qpc_v521/inc/qs
ALLINCPATH += -I$(EEBASE)/contrib/qpc_v521/inc/ports/erika

endif


INCLUDE_PATH += $(EEBASE)/contrib/qpc_v521/inc
INCLUDE_PATH += $(EEBASE)/contrib/qpc_v521/inc/qep
INCLUDE_PATH += $(EEBASE)/contrib/qpc_v521/inc/qf
INCLUDE_PATH += $(EEBASE)/contrib/qpc_v521/inc/qs
INCLUDE_PATH += $(EEBASE)/contrib/qpc_v521/inc/ports/erika

EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/ports/erika/qf_port.c

EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qep.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qfsm_dis.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qfsm_ini.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qhsm_dis.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qhsm_in.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qhsm_ini.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qhsm_top.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qmsm_dis.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qep/qmsm_ini.c


EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_ctor.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_defer.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_fifo.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_get_.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_lifo.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_sub.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_usub.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qa_usuba.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qeq_fifo.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qeq_get.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qeq_init.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qeq_lifo.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_act.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_gc.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_log2.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_new.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_pool.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_psini.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_pspub.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_pwr2.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qf_tick.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qma_ctor.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qmp_get.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qmp_init.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qmp_put.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qte_arm.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qte_ctor.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qte_ctr.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qte_darm.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qf/qte_rarm.c

ifeq ($(call iseeopt, Q_SPY), yes)
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_blk.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_byte.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_dict.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_f32.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_f64.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_mem.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_str.c
EE_SRCS_QPC_V521_ALL += $(EEBASE)/contrib/qpc_v521/src/qs/qs_u64.c
endif


EE_SRCS += $(EE_SRCS_QPC_V521_ALL)


endif #__LIB_QPC_V521__

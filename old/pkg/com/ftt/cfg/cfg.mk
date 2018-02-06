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

## Author: 2004 Paolo Gai
## CVS: $Id: cfg.mk,v 1.2 2006/11/03 11:05:21 pj Exp $


########### FTT NETWORK LAYER ################
### FTT MASTER NODE ###
ifeq ($(call iseeopt, __FTT_MASTER__), yes)
EE_SRCS += pkg/src/com/ftt/master/ART_add.c
EE_SRCS += pkg/src/com/ftt/master/ART_change.c
EE_SRCS += pkg/src/com/ftt/master/ART_check.c
EE_SRCS += pkg/src/com/ftt/master/ART_remove.c
EE_SRCS += pkg/src/com/ftt/master/asynch_tx.c
EE_SRCS += pkg/src/com/ftt/master/stop_asynch.c
EE_SRCS += pkg/src/com/ftt/master/ftt_confirm.c
EE_SRCS += pkg/src/com/ftt/master/ftt_dispatcher.c
EE_SRCS += pkg/src/com/ftt/master/ftt_indication.c
EE_SRCS += pkg/src/com/ftt/master/ftt_init.c
EE_SRCS += pkg/src/com/ftt/master/ftt_set_handler.asm
EE_SRCS += pkg/src/com/ftt/master/ftt_start.c
EE_SRCS += pkg/src/com/ftt/master/rm_scheduler.c
EE_SRCS += pkg/src/com/ftt/master/slave_add.c
EE_SRCS += pkg/src/com/ftt/master/slave_remove.c
EE_SRCS += pkg/src/com/ftt/master/SRT_add.c
EE_SRCS += pkg/src/com/ftt/master/SRT_change.c
EE_SRCS += pkg/src/com/ftt/master/SRT_check.c
EE_SRCS += pkg/src/com/ftt/master/SRT_delete.c
EE_SRCS += pkg/src/com/ftt/master/SRT_insert.c
EE_SRCS += pkg/src/com/ftt/master/SRT_remove.c
endif

### FTT SLAVE NODE ###
ifeq ($(call iseeopt, __FTT_SLAVE__), yes)
EE_SRCS += pkg/src/com/ftt/slave/activation.c
EE_SRCS += pkg/src/com/ftt/slave/NRT_receive.c
EE_SRCS += pkg/src/com/ftt/slave/NRT_send.c
EE_SRCS += pkg/src/com/ftt/slave/AMS_receive.c
EE_SRCS += pkg/src/com/ftt/slave/AMS_send.c
EE_SRCS += pkg/src/com/ftt/slave/ART_add.c
EE_SRCS += pkg/src/com/ftt/slave/ART_change.c
EE_SRCS += pkg/src/com/ftt/slave/ART_remove.c
EE_SRCS += pkg/src/com/ftt/slave/Asearch.c
EE_SRCS += pkg/src/com/ftt/slave/NRTTsearch.c
EE_SRCS += pkg/src/com/ftt/slave/NRTRsearch.c
EE_SRCS += pkg/src/com/ftt/slave/buf_req.c
EE_SRCS += pkg/src/com/ftt/slave/ftt_confirm.c
EE_SRCS += pkg/src/com/ftt/slave/ftt_indication.c
EE_SRCS += pkg/src/com/ftt/slave/ftt_init.c
EE_SRCS += pkg/src/com/ftt/slave/ftt_set_handler.asm
EE_SRCS += pkg/src/com/ftt/slave/ftt_start.c
EE_SRCS += pkg/src/com/ftt/slave/ftt_transmitter.c
EE_SRCS += pkg/src/com/ftt/slave/SMS_consume.c
EE_SRCS += pkg/src/com/ftt/slave/SMS_produce.c
EE_SRCS += pkg/src/com/ftt/slave/SRT_add.c
EE_SRCS += pkg/src/com/ftt/slave/SRT_change.c
EE_SRCS += pkg/src/com/ftt/slave/SRT_remove.c
EE_SRCS += pkg/src/com/ftt/slave/Ssearch.c
EE_SRCS += pkg/src/com/ftt/slave/stop_asynch.c
endif


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

ALL_DISTRIBUTIONS += BINARY_OO1

BINARY_OO1 = BINARY_OO1_CONF

BINARY_OO1_CONF_MAX_TASK = 4
BINARY_OO1_CONF_MAX_RESOURCE = 2
BINARY_OO1_CONF_MAX_APPMODE = 1
BINARY_OO1_CONF_MAX_ALARM = 0

BINARY_OO1_CONF = __BIN_DISTR_LIMITED__ __ALLOW_NESTED_IRQ__ __ARM7GNU__ __EVALUATOR7T__ __SAMSUNG_KS32C50100__ __MULTI__ __OO_ECC2__ __OO_HAS_STARTUPHOOK__ __OO_NO_ALARMS__ __OO_ORTI_LASTERROR__ __OO_ORTI_SERVICETRACE__ __OO_ORTI_RUNNINGISR2__ __OO_ORTI_PRIORITY__ __OO_ORTI_STACK__ __OO_EXTENDED_STATUS__ __OO_HAS_ERRORHOOK__ __OO_HAS_PRETASKHOOK__ __OO_HAS_POSTTASKHOOK__ __LCD_USED__ __LEDS_USED__ __TIMER_0_USED__ __DIP_SWITCH_USED__

# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2011  Evidence Srl
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

# Author: 2011, Bernardo  Dal Seno

# Template for in-line assembly system calls used for Diab on PPC e200.
# This file must be sourced before executing
# pkg/kernel/as/cfg/generate_syscall.sh to generate all system calls

function EE_SYSCALL_0()
{
    echo "__asm $1 $2(void)"
    echo "{"
    echo '! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"'
    echo "	li	r0, $3"
    echo "	sc"
    echo "}"
}

function EE_SYSCALL_1()
{
    echo "__asm $1 $2($3 $4)"
    echo "{"
    echo "% reg $4"
    echo '! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"'
    echo "	mr	r3, $4"
    echo "	li	r0, $5"
    echo "	sc"
    echo "}"
}

function EE_SYSCALL_2()
{
    echo "__asm $1 $2($3 $4, $5 $6)"
    echo "{"
    echo "% reg $4, $6"
    echo '! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"'
    echo "	mr	r3, $4"
    echo "	mr	r4, $6"
    echo "	li	r0, $7"
    echo "	sc"
    echo "}"
}

function EE_SYSCALL_3()
{
    echo "__asm $1 $2($3 $4, $5 $6, $7 $8)"
    echo "{"
    echo "% reg $4, $6, $8"
    echo '! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"'
    echo "	mr	r3, $4"
    echo "	mr	r4, $6"
    echo "	mr	r5, $8"
    echo "	li	r0, $9"
    echo "	sc"
    echo "}"
}

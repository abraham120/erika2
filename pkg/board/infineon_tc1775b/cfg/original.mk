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

# PJ: note: this file is not used for compilatuion,
# it was the original makefile from metrowerks codewarrior

PROJ    = dhrystone
PROJDIR = c:\program files\tasking\ctc v2.1\myprograms\benchmark\dhrystone
PRODDIR = c:\program files\tasking\ctc v2.1

INCDIR  = $(PRODDIR)\include
LIBDIR  = $(PRODDIR)\lib\$(PROTECTED)

PROTECTED=p\tc112


OPT_XVW = -tcfg infineon_triboard_tc1775b.cfg -C tc1775b -i --load_application_goto_main=true --sync_on_halt=on -a 100 -b 500 -s 26

all : "$(PROJ).elf"

"dhry_1.o" : "dhry_1.c" "dhry.h" <1098976665>
	@echo Compiling and assembling "dhry_1.c"
	@"$(PRODDIR)\bin\cctc.exe" -t -o $@ -co "dhry_1.c" -f<<EOF
	$(EMPTY) $(OPT_CC)
	EOF

"dhry_2.o" : "dhry_2.c" "dhry.h" <1098976665>
	@echo Compiling and assembling "dhry_2.c"
	@"$(PRODDIR)\bin\cctc.exe" -t -o $@ -co "dhry_2.c" -f<<EOF
	$(EMPTY) $(OPT_CC)
	EOF

"cstart.o" : "cstart.asm" <1098976665>
	@echo Assembling "cstart.asm"
	@"$(PRODDIR)\bin\cctc.exe" -o $@ -co "cstart.asm" -f<<EOF
	$(EMPTY) $(OPT_CC)
	EOF

"$(PROJ).elf" : "dhry_1.o" "dhry_2.o" "cstart.o" <1098976665>
	@echo Linking and Locating to $*.elf in ELF/DWARF 2 format
	@"$(PRODDIR)\bin\cctc.exe" -f<<EOF
	$(separate "\n" $(match .o $!))
	$(separate "\n" $(match .a $!)) $(OPT_LKLC)
	EOF

clean :
	@echo Deleting intermediate files and output files for project '$(PROJ)'.
	@$(exist "dhry_1.o" del "dhry_1.o")
	@$(exist "dhry_2.o" del "dhry_2.o")
	@$(exist "cstart.o" del "cstart.o")
	@$(exist "$(PROJ).elf" del "$(PROJ).elf")
	@$(exist "_dhrystone.lsl" del "_dhrystone.lsl")
	@$(exist "tc1775b.lsl" del "tc1775b.lsl")
	@$(exist "dhrystone.map" del "dhrystone.map")

# Copyright 1997-2004 Altium BV
# Serial#:	123456
# EDE Version:	3.5r9 (Build 138)

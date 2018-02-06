/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
/*
 * Linker script for CodeWarrior compiler, for executables running from flash
 * on CPU 0.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 *         2012 Francesco Esposito
 */
SECTIONS
{
	GROUP : {
		.boot_data LOAD(ADDR(.boot_data)): { KEEP(*(.boot_data)) }
		.boot LOAD(ADDR(.boot)): { }
	} > boot

	GROUP : {
		.text_vle (VLECODE) LOAD(ADDR(iflash)): {
			*(.text)
			*(.text_vle)
			*(.init)
			*(.fini)
			_etext_vle = . ;
		}
		.text LOAD(_etext_vle): {
			*(.text)
			*(.text_vle)
			*(.init)
			*(.fini)
			*(.ctors)
			*(.dtors)
			*(extab)
			*(extabindex)
			*(.rdata)
			*(.rodata)
			_etext = . ;
		}

		ee_smcglobalc = . ;
		ee_mcglobalc LOAD(ee_smcglobalc): { }
		ee_emcglobalc = . ;

		.sdata2 LOAD(ee_emcglobalc): {
			*(.sdata2)
			*(.sbss2)
		 }
    . = ALIGN(16);
		ee_load_ram = . ;
	} > iflash

	GROUP : {
		ee_sdata = . ;
		.data LOAD(ee_load_ram): { }

		.sram_text LOAD(ee_load_ram + ADDR(.sram_text) - ADDR(.data)): { }

		ee_smcglobald = . ;
		ee_mcglobald LOAD(ee_load_ram + ee_smcglobald - ADDR(.data)): { }
                ee_fast_mcglobald LOAD(ee_load_ram + ADDR(ee_fast_mcglobald) - ADDR(.data)): { }
		ee_emcglobald = . ;

		.sdata LOAD(ee_load_ram + ADDR(.sdata) - ADDR(.data)): { }

		ee_sbss = . ;
		.sbss : { }
                ee_fast_mcglobalu : { }
		.bss : { }
                ee_mcglobalu : { }
		ee_ebss = . ;

		ee_sstack = . ;
		.stack LOAD(ADDR(.stack)): {
			*(.stack)
			*(.ustack)
		}
		ee_estack = . ;
	} > isram
}

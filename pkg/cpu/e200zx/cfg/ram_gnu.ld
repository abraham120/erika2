/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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
 * Linker script for GNU GCC compiler, for executables running from RAM.
 * Author: 2014, Giuseppe Serano
 */

ENTRY(__start)

SECTIONS
{

	.boot : 
	{
      		*(.boot)
	} >isram

	.text : 
	{ 
		*(.text)
		*(.text.*)
		*(.init)
		*(.fini)
		*(rdata)
		*(.eini)
	} >isram

	.rodata :
	{
		*(.rodata)
		*(.rodata.*)
	} >isram

	.sdata2 :
	{
		_SDA2_BASE_ = 0x8000 ;
		*(.sdata2)
		*(.sdata2.*)
	} >isram

	.sbss2	(NOLOAD) :
	{
		ee_ssbss2 = . ;
		*(.sbss2)
		*(.sbss2.*)
		ee_esbss2 = . ;
	} >isram

	.data :
	{
		ee_load_ram = . ;
		ee_sdata = . ;
		*(.data)
		*(.data.*)
	} >isram

	.sdata :
	{
		_SDA_BASE_ = 0x8000 ;
		*(.sdata)
		*(.sdata.*)
	} >isram

	.sbss	(NOLOAD) :
	{
		ee_sbss = . ;
		*(.sbss)
		*(.sbss.*)
	} >isram

	.bss	(NOLOAD) :
	{
		*(.bss)
		*(.bss.*)
		ee_ebss = . ;
	} >isram

        .stack	(NOLOAD) :
	{
		ee_sstack = . ;
		*(.stack)
		ee_estack = . ;
	} >isram

}

/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013 Bruno Morelli
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
	erika_main_memory : ORIGIN = 0x80008000, LENGTH = 0x8000000
}

/* stacks */
EE_irq_stack_size = 4096;
EE_fiq_stack_size = 1024;
EE_svc_stack_size = 1024;
EE_abt_stack_size = 1024;
EE_stack_size = 8192;

EE_irq_stack_start = ORIGIN(erika_main_memory) + LENGTH(erika_main_memory) - EE_irq_stack_size;
EE_irq_stack_end = EE_irq_stack_start + EE_irq_stack_size;

EE_fiq_stack_start = EE_irq_stack_start - EE_fiq_stack_size;
EE_fiq_stack_end = EE_fiq_stack_start + EE_fiq_stack_size;

EE_svc_stack_start = EE_fiq_stack_start - EE_svc_stack_size;
EE_svc_stack_end = EE_svc_stack_start + EE_svc_stack_size;

EE_abt_stack_start = EE_svc_stack_start - EE_abt_stack_size;
EE_abt_stack_end = EE_abt_stack_start + EE_abt_stack_size;

EE_stack_start = EE_abt_stack_start - EE_stack_size;
EE_stack_end = EE_stack_start + EE_stack_size;


ENTRY(_start_0)
SECTIONS
{
  . = 0x80008000;
  . = ALIGN(4);
  .text : {
    *(.ee_start)
    __stack_base__ = .;
    KEEP(*(.ee_symtab))
    *(.boot_board)
    *(.crt0)
    *(.text)
    *(.text.*)
    . = ALIGN(0x100000);
    __vector_start = .;
    *(.vectors)
    . = ALIGN(0x100000);
  } > erika_main_memory

  .rodata : {
    . = ALIGN(4);
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
  } > erika_main_memory

  .data : {
    . = ALIGN(4);
    *(.data)
  } > erika_main_memory

  .got : {
    . = ALIGN(4);
    *(.got)
  } > erika_main_memory
  . = .;
  . = ALIGN(4);

  .bss : {
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > erika_main_memory

  . = ALIGN(0x4000);
  __l1_page_table__ = . ;
  . = ALIGN(0x100000);
  __vector_table__ = . ;

  .mmu_tbl : {
    /* . = ALIGN(0x100000); */
    . = ALIGN(0x4000);
    __mmu_tbl_start = .;
    *(.mmu_tbl)
      /* . = . + 0x100000; */ /* valid max size 16kb (1mb at the moment) */
      . = . + 0x4000;  /* valid max size 16kb */
    __mmu_tbl_end = .;
  } > erika_main_memory

  ee_mcglobal : {
    . = ALIGN(0x100000);
    __ee_mcglobal_start = .;
    *(ee_mcglobalc)
    *(ee_mcglobald)
    __ee_mcglobal_end = .;
  } > erika_main_memory

  . = ALIGN(4);
  _end = . ;
}



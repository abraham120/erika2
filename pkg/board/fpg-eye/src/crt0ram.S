/*
 * This file is based on the crt0ram.S provided with the Lattice Mico32
 * software, version 8.0. The heading below is taken verbatim from the original
 * file.
 *
 * Modified:
 *    2010-2011, Bernardo  Dal Seno
 *    Copyright (C) 2010-2011  Evidence Srl
 */


	
/****************************************************************************
**
**  Name: crt0ram.S
**
**  Description:
**        Implements boot-code that calls LatticeDDInit (that calls main())
**        Implements exception handlers (actually, redirectors)
**
**  $Revision: $
**
** Disclaimer:
**
**   This source code is intended as a design reference which
**   illustrates how these types of functions can be implemented.  It
**   is the user's responsibility to verify their design for
**   consistency and functionality through the use of formal
**   verification methods.  Lattice Semiconductor provides no warranty
**   regarding the use or functionality of this code.
**
** --------------------------------------------------------------------
**
**                     Lattice Semiconductor Corporation
**                     5555 NE Moore Court
**                     Hillsboro, OR 97214
**                     U.S.A
**
**                     TEL: 1-800-Lattice (USA and Canada)
**                          (503)268-8001 (other locations)
**
**                     web:   http://www.latticesemi.com
**                     email: techsupport@latticesemi.com
**
** --------------------------------------------------------------------------
**
**  Change History (Latest changes on top)
**
**  Ver    Date        Description
** --------------------------------------------------------------------------
**  3.1   Jun-18-2008  Added __MICO_NO_INTERRUPTS__ preprocessor
**                     option to exclude invoking MicoISRHandler
**                     to reduce code-size in apps that don't use
**                     interrupts
**
**  3.0   Mar-25-2008  Added Header
**
**---------------------------------------------------------------------------
*****************************************************************************/

/*
 * LatticeMico32 C startup code.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* From include/sys/signal.h */  
#define SIGINT  2   /* interrupt */
#define SIGTRAP 5   /* trace trap */
#define SIGFPE  8   /* arithmetic exception */
#define SIGSEGV 11  /* segmentation violation */

#include <cpu/mico32/inc/ee_asm_util.h>
#include <system_conf.h>

#define LED_CODE_DATAB	0xee
#define LED_CODE_INSTB	0xaa
#define LED_CODE_DIV0	0xcc
#define LED_CODE_SYSC	0x88
#define LED_CODE_BREAK	0x77
#define LED_CODE_WATCH	0x55

/* Check prerequisites for handlers */
#if defined(__LM32_VERBOSE_HANDLERS__) && \
 (! defined(SERPARIO_BASE_ADDRESS) || ! defined (UART_BASE_ADDRESS))
#error "__LM32_VERBOSE_HANDLERS__ needs both serpar and uart components"
#endif
#if defined(__LM32_NOISY_HANDLERS__) && ! defined(SERPARIO_BASE_ADDRESS)
#error "__LM32_NOISY_HANDLERS__ needs the serpar component"
#endif

/* Provide a reasonable default for handlers */
#if ! defined(__LM32_NOISY_HANDLERS__) && ! defined(__LM32_STANDARD_HANDLERS__) \
 && ! defined(__LM32_VERBOSE_HANDLERS__	)
#if defined(SERPARIO_BASE_ADDRESS) && ! defined (DEBUG)
#define __LM32_NOISY_HANDLERS__
#else
#define __LM32_STANDARD_HANDLERS__
#endif
#endif

#if SERPARIO_BASE_ADDRESS & 0x8000
#define SERPARIO_BASE_HI ((SERPARIO_BASE_ADDRESS >> 16) + 1)
#define SERPARIO_BASE_LO (0xffff0000 + (SERPARIO_BASE_ADDRESS & 0xffff))
#else
#define SERPARIO_BASE_HI (SERPARIO_BASE_ADDRESS >> 16)
#define SERPARIO_BASE_LO (SERPARIO_BASE_ADDRESS & 0xffff)
#endif


#ifdef __LM32_VERBOSE_HANDLERS__	
#define NUM_REG		36
	.macro	GENERIC_HANDLER led_code
	mv	r0, sp
	/* r0 is not 0 any more! don't use RET, MV, MVHI, NOT, MVI, NOP */
	xor	sp, sp, sp
	orhi	sp, sp, hi(_fstack-4*NUM_REG)
	ori	sp, sp, lo(_fstack-4*NUM_REG)
	sw	(sp + 4*28), r0
	xor	r0, r0, r0
	ori	r0, r0, \led_code
	bi	_dump_all_registers
	.endm

#elif defined(__LM32_NOISY_HANDLERS__)
	.macro	GENERIC_HANDLER led_code
	mvhi	r11, SERPARIO_BASE_HI
	mvi	r12, (0xffffff00 | \led_code)
1:	
	mvhi	r13, (CPU_FREQUENCY >> 18)
2:
	addi	r13, r13, -1
	bg	r13, r0, 2b
	sw	(r11 + SERPARIO_BASE_LO + 4), r12
	xori	r12, r12, 0x0100
	bi	1b
	.endm

#else /* defined __LM32_STANDARD_HANDLERS__ */
	.macro	GENERIC_HANDLER led_code
	rcsr	r7, DEBA
	addi	r7, r7, . - _reset_handler - 4
	b	r7
	nop
	nop
	nop
	nop
	nop
	.endm

#endif /* __LM32_XXXX_HANDLERS__ */


	
/* Exception handlers - Must be 32 bytes long. */
        .section    .boot, "ax", @progbits
	
        .global	_start  
_start: 
	   
        .global _reset_handler
        .type 	_reset_handler, @function
_reset_handler:
    xor     r0, r0, r0
    wcsr    IE, r0
    wcsr    IM, r0
    mvhi    r1, hi(_reset_handler)
    ori     r1, r1, lo(_reset_handler)
    wcsr    EBA, r1
    calli   _crt0
    nop
        .size	_reset_handler, .-_reset_handler
	
        .global _breakpoint_handler
        .type 	_breakpoint_handler, @function
_breakpoint_handler:
	GENERIC_HANDLER LED_CODE_BREAK
        .size   _breakpoint_handler, .-_breakpoint_handler

        .global _instruction_bus_error_handler
        .type 	_instruction_bus_error_handler, @function
_instruction_bus_error_handler:
	GENERIC_HANDLER LED_CODE_INSTB
        .size   _instruction_bus_error_handler, .-_instruction_bus_error_handler
	
        .global _watchpoint_handler
        .type 	_watchpoint_handler, @function
_watchpoint_handler:
	GENERIC_HANDLER LED_CODE_WATCH
        .size   _watchpoint_handler, .-_watchpoint_handler
	
        .global _data_bus_error_handler
        .type 	_data_bus_error_handler, @function
_data_bus_error_handler:
	GENERIC_HANDLER LED_CODE_DATAB
        .size   _data_bus_error_handler, .-_data_bus_error_handler
	
        .global _divide_by_zero_handler
        .type 	_divide_by_zero_handler, @function
_divide_by_zero_handler:
	GENERIC_HANDLER LED_CODE_DIV0
        .size   _divide_by_zero_handler, .-_divide_by_zero_handler
	
        .global _interrupt_handler
        .type 	_interrupt_handler, @function
_interrupt_handler:
    sw      (sp+0), ra
    calli   _save_all
    mvi     r1, SIGINT
#ifndef __MICO_NO_INTERRUPTS__
    calli   MicoISRHandler
#else
    wcsr    IE, r0
#endif
    bi      _restore_all_and_return
    nop
    nop
    nop
        .size   _interrupt_handler, .-_interrupt_handler
	
        .global _system_call_handler
        .type 	_system_call_handler, @function
_system_call_handler:
	GENERIC_HANDLER LED_CODE_SYSC
        .size   _system_call_handler, .-_system_call_handler
	
        .global _crt0
        .type 	_crt0, @function
_crt0:
    /* Clear r0 */
    xor     r0, r0, r0
    /* Setup stack and global pointer */
    mvhi    sp, hi(_fstack)
    ori     sp, sp, lo(_fstack)
    mvhi    gp, hi(_gp)
    ori     gp, gp, lo(_gp)

#ifdef __LM32_RELOCATE_TEXT__
    /* Relocate text */
    mvhi    r1, hi(_ftext)
    ori     r1, r1, lo(_ftext)
    mvhi    r2, hi(_ftext_rom)
    ori     r2, r2, lo(_ftext_rom)
    be      r1, r2, .L_done_text_relocation
    mvhi    r3, (_etext)
    ori     r3, r3, (_etext)
    calli   _relocate_text
.L_done_text_relocation:
#endif

#ifdef __LM32_RELOCATE_DATA__
    /* Relocate read-only data */
    mvhi    r1, hi(_frodata)
    ori     r1, r1, lo(_frodata)
    mvhi    r2, hi(_frodata_rom)
    ori     r2, r2, lo(_frodata_rom)
    be      r1, r2, .L_done_rodata_relocation
    mvhi    r3, hi(_erodata)
    ori     r3, r3, lo(_erodata)
    be      r1, r3, .L_done_rodata_relocation
    sub     r3, r3, r1
    calli   memcpy
.L_done_rodata_relocation:        
        
    /* Relocate data */
    mvhi    r1, hi(_fdata)
    ori     r1, r1, lo(_fdata)
    mvhi    r2, hi(_fdata_rom)
    ori     r2, r2, lo(_fdata_rom)
    be      r1, r2, .L_done_data_relocation
    mvhi    r3, hi(_edata)
    ori     r3, r3, lo(_edata)
    be      r1, r3, .L_done_data_relocation
    sub     r3, r3, r1
    calli   memcpy
.L_done_data_relocation:        
#endif

/* Clear BSS */
    mvhi    r1, hi(_fbss)
    ori     r1, r1, lo(_fbss)
    mvhi    r3, hi(_ebss)
    ori     r3, r3, lo(_ebss)
        .size   _crt0, .-_crt0
	
        .global .ClearBSS
        .type 	.ClearBSS, @function
.ClearBSS:
    bi      .L_enter_clear_bss
.L_clear_bss_loop:
    sw      (r1+0), r0
    addi    r1, r1, 4
.L_enter_clear_bss:
    bne      r1, r3, .L_clear_bss_loop
        .size   .ClearBSS, .-.ClearBSS
	
        .global .CallConstructor
        .type 	.CallConstructor, @function

.CallConstructor:
#ifdef __LM32_USE_CPLUSPLUS__
    /* Call C++ constructors */
    calli   _init
#endif
    /* Call main program */
    mvi     r1, 0
    mvi     r2, 0
    mvi     r3, 0
    calli   main
#ifdef __LM32_USE_CPLUSPLUS__
    calli   _fini
#endif
    /* Call exit, which doesn't return, to perform any clean up */
    calli   _exit
        .size   .CallConstructor, .-.CallConstructor

#ifdef __LM32_RELOCATE_TEXT__
	.global _relocate_text
	.type 	_relocate_text, @function
_relocate_text:
    lb      r4, (r2+0)
    addi    r2, r2, 1
    sb      (r1+0), r4
    addi    r1, r1, 1
    bne     r1, r3, _relocate_text
    ret
	.size	_relocate_text, .-_relocate_text
#endif

        .global _save_all
        .type 	_save_all, @function
    /* Save all registers onto the stack */ 
_save_all:
#ifdef MICO32_FULL_CONTEXT_SAVE_RESTORE
    addi    sp, sp, -128
#else
    addi    sp, sp, -60
#endif
    sw      (sp+4), r1
    sw      (sp+8), r2
    sw      (sp+12), r3
    sw      (sp+16), r4
    sw      (sp+20), r5
    sw      (sp+24), r6
    sw      (sp+28), r7
    sw      (sp+32), r8
    sw      (sp+36), r9
    sw      (sp+40), r10
#ifdef MICO32_FULL_CONTEXT_SAVE_RESTORE
    sw      (sp+44), r11
    sw      (sp+48), r12
    sw      (sp+52), r13
    sw      (sp+56), r14
    sw      (sp+60), r15
    sw      (sp+64), r16
    sw      (sp+68), r17
    sw      (sp+72), r18
    sw      (sp+76), r19
    sw      (sp+80), r20
    sw      (sp+84), r21
    sw      (sp+88), r22
    sw      (sp+92), r23
    sw      (sp+96), r24
    sw      (sp+100), r25
    sw      (sp+104), r26
    sw      (sp+108), r27
    sw      (sp+120), ea
    sw      (sp+124), ba
    /* ra and sp need special handling, as they have been modified */
    lw      r1, (sp+128)
    sw      (sp+116), r1
    mv      r1, sp
    addi    r1, r1, 128
    sw      (sp+112), r1
#else
    sw      (sp+52), ea
    sw      (sp+56), ba
    /* ra and sp need special handling, as they have been modified */
    lw      r1, (sp+60)
    sw      (sp+48), r1
    mv      r1, sp
    addi    r1, r1, 60
    sw      (sp+44), r1
#endif
    xor     r1, r1, r1
    wcsr    ie, r1
    ret
        .size  	_save_all, .-_save_all
	
        .global _restore_all_and_return
        .type 	_restore_all_and_return, @function
    /* Restore all registers and return from exception */
_restore_all_and_return:
    addi    r1, r0, 2
    wcsr    ie, r1
    lw      r1, (sp+4)
    lw      r2, (sp+8) 
    lw      r3, (sp+12) 
    lw      r4, (sp+16) 
    lw      r5, (sp+20) 
    lw      r6, (sp+24) 
    lw      r7, (sp+28) 
    lw      r8, (sp+32) 
    lw      r9, (sp+36) 
    lw      r10, (sp+40)
#ifdef MICO32_FULL_CONTEXT_SAVE_RESTORE
    lw      r11, (sp+44)
    lw      r12, (sp+48)
    lw      r13, (sp+52)
    lw      r14, (sp+56)
    lw      r15, (sp+60)
    lw      r16, (sp+64)
    lw      r17, (sp+68)
    lw      r18, (sp+72)
    lw      r19, (sp+76)
    lw      r20, (sp+80)
    lw      r21, (sp+84)
    lw      r22, (sp+88)
    lw      r23, (sp+92)
    lw      r24, (sp+96)
    lw      r25, (sp+100)
    lw      r26, (sp+104)
    lw      r27, (sp+108)
    lw      ra, (sp+116)
    lw      ea, (sp+120)
    lw      ba, (sp+124)
    /* Stack pointer must be restored last, in case it has been updated */
    lw      sp, (sp+112)
#else
    lw      ra, (sp+48)
    lw      ea, (sp+52)
    lw      ba, (sp+56)
    /* Stack pointer must be restored last, in case it has been updated */
    lw      sp, (sp+44)
#endif
    nop
    eret
        .size   _restore_all_and_return, .-_restore_all_and_return


#ifdef __LM32_VERBOSE_HANDLERS__

#define MICOUART_LSR_TX_RDY_MASK	0x20
#define MICOUART_LSR_RX_RDY_MASK	0x01
#define MICOUART_RXTX	0
#define MICOUART_LSR	20
#define MICOUART_LCR	12

#define REG_STR_LEN	6
        .type 	_dump_all_registers, @function
_dump_all_registers:
	/* This function is called with r0 containing the excpetion code, so
	 * don't use RET, MV, MVHI, NOT, MVI, NOP until r0 is cleared.
	 * sp is valid and its old content is stored in (sp + 4*28)
	 */
	sw	(sp + 4), r1
	or	r1, r0, r0	// mv r1, r0
	xor	r0, r0, r0
	/* r0 now cleared! */
	sw	(sp + 8), r2
	sw	(sp + 12), r3
	sw	(sp + 16), r4
	sw	(sp + 20), r5
	sw	(sp + 24), r6
	sw	(sp + 28), r7
	sw	(sp + 32), r8
	sw	(sp + 36), r9
	sw	(sp + 40), r10
	sw	(sp + 44), r11
	sw	(sp + 48), r12
	sw	(sp + 52), r13
	sw	(sp + 56), r14
	sw	(sp + 60), r15
	sw	(sp + 64), r16
	sw	(sp + 68), r17
	sw	(sp + 72), r18
	sw	(sp + 76), r19
	sw	(sp + 80), r20
	sw	(sp + 84), r21
	sw	(sp + 88), r22
	sw	(sp + 92), r23
	sw	(sp + 96), r24
	sw	(sp + 100), r25
	sw	(sp + 104), r26
	sw	(sp + 108), r27
	// sp (r28) is already there
	sw	(sp + 116), ra
	sw	(sp + 120), ea
	sw	(sp + 124), ba
	rcsr	r2, ip
	sw	(sp + 128), r2
	rcsr	r2, im
	sw	(sp + 132), r2
	rcsr	r2, ie
	sw	(sp + 136), r2
	rcsr	r2, eba
	sw	(sp + 140), r2
	rcsr	r2, cfg
	sw	(sp + 144), r2
	mv	r11, r1
	
	mvi	r2, LED_CODE_DATAB
	bne	r11, r2, 1f
	mvhi	r1, hi(_err_str_datab)
	ori	r1, r1, lo(_err_str_datab)
	bi	2f
1:	
	mvi	r2, LED_CODE_INSTB
	bne	r11, r2, 1f
	mvhi	r1, hi(_err_str_instb)
	ori	r1, r1, lo(_err_str_instb)
	bi	2f
1:	
	mvi	r2, LED_CODE_DIV0
	bne	r11, r2, 1f
	mvhi	r1, hi(_err_str_div0)
	ori	r1, r1, lo(_err_str_div0)
	bi	2f
1:	
	mvi	r2, LED_CODE_SYSC
	bne	r11, r2, 1f
	mvhi	r1, hi(_err_str_sysc)
	ori	r1, r1, lo(_err_str_sysc)
	bi	2f
1:	
	mvi	r2, LED_CODE_BREAK
	bne	r11, r2, 1f
	mvhi	r1, hi(_err_str_break)
	ori	r1, r1, lo(_err_str_break)
	bi	2f
1:	
	mvhi	r1, hi(_err_str_watch)
	ori	r1, r1, lo(_err_str_watch)
2:	
	mv	r21, r1
	mv	r22, r11
.L_dump_regs_loop:
	calli	_err_print_str

	addi	r12, sp, 4
	addi	r13, r12, 4*(NUM_REG/2)
	LOAD_ADDR r14, _err_reg_names
1:
	mv	r1, r14
	mv	r2, r12
	calli	_err_print_reg_str
	addi	r12, r12, 4
	addi	r14, r14, REG_STR_LEN
	bg	r13, r12, 1b
	
	ori	r12, r11, 0xffffff00
	LOAD_ADDR r14, SERPARIO_BASE_ADDRESS
	LOAD_ADDR r15, UART_BASE_ADDRESS
1:	
	/* Check if there is input from Uart */
	lw	r1, (r15 + MICOUART_LSR)
	andi	r1, r1, MICOUART_LSR_RX_RDY_MASK
	be	r1, r0, 2f
	/* Remove pending input */
4:
	lw	r2, (r15 + MICOUART_RXTX)
	lw	r1, (r15 + MICOUART_LSR)
	andi	r1, r1, MICOUART_LSR_RX_RDY_MASK
	bne	r1, r0, 4b
	/* Key pressed: reprint everything */
	mv	r1, r21
	mv	r11, r22
	bi	.L_dump_regs_loop
2:
	mvhi	r13, (CPU_FREQUENCY >> 18)
3:
	addi	r13, r13, -1
	bg	r13, r0, 3b
	sw	(r14 + 4), r12
	xori	r12, r12, 0x0100
	bi	1b
	.size	_dump_all_registers, .-_dump_all_registers


	/* Leaf functions can use r1-r6 freely */
	
/* _err_print_str */
	
        .type 	_err_print_str, @function
	/* r1 = pointer to string */
_err_print_str:
	LOAD_ADDR r2, UART_BASE_ADDRESS
1:	
	lbu	r4, (r1 + 0)
	be	r4, r0, 3f
	addi	r1, r1, 1
2:	
	lw	r3, (r2 + MICOUART_LSR)
	andi	r3, r3, MICOUART_LSR_TX_RDY_MASK
	be	r3, r0, 2b
	sw	(r2 + MICOUART_RXTX), r4
	bi	1b
3:	
	ret
	.size	_err_print_str, .-_err_print_str


/* _err_print_reg */
	
        .type 	_err_print_reg, @function
	/* r1 = value to print */
_err_print_reg:
	LOAD_ADDR r2, UART_BASE_ADDRESS
	mvi	r5, 28
1:	
	sru	r4, r1, r5
	andi	r4, r4, 0xf
	mvi	r6, 10
	bge	r4, r6, 4f
	addi	r4, r4, '0' // '0'-'9'
	bi	2f
4:
	addi	r4, r4, ('a'-10) // 'a'-'f'
2:	
	lw	r3, (r2 + MICOUART_LSR)
	andi	r3, r3, MICOUART_LSR_TX_RDY_MASK
	be	r3, r0, 2b
	sw	(r2 + MICOUART_RXTX), r4
	addi	r5, r5, -4
	bge	r5, r0, 1b
3:	
	ret
	.size	_err_print_reg, .-_err_print_reg



/* _err_print_reg_str */

        .type 	_err_print_reg_str, @function
	/* r1 = first description string,
	   r2 = pointer to first register value
	    */
_err_print_reg_str:
	mv	r8, ra
	mv	r9, r2
	mv	r10, r1
	calli	_err_print_str
	lw	r1, (r9 + 0)
	calli	_err_print_reg
	LOAD_ADDR r1, _err_str_spaces
	calli	_err_print_str
	addi	r1, r10, REG_STR_LEN*(NUM_REG/2)
	calli	_err_print_str
	lw	r1, (r9 + 4*(NUM_REG/2))
	calli	_err_print_reg
	LOAD_ADDR r1, _err_str_newline
	mv	ra, r8
	bi	_err_print_str
	.size	_err_print_reg_str, .-_err_print_reg_str


	.data

	.type	_err_str_datab, @object
	.balign 1
_err_str_datab:
	.string	"DATA BUS EXCEPTION\n"
	.size	_err_str_datab, .-_err_str_datab

	.type	_err_str_instb, @object
	.balign 1
_err_str_instb:
	.string	"INSTRUCTION BUS EXCEPTION\n"
	.size	_err_str_instb, .-_err_str_instb

	.type	_err_str_div0, @object
	.balign 1
_err_str_div0:
	.string	"DIVISION BY ZERO\n"
	.size	_err_str_div0, .-_err_str_div0

	.type	_err_str_sysc, @object
	.balign 1
_err_str_sysc:
	.string	"SYSTEM CALL\n"
	.size	_err_str_sysc, .-_err_str_sysc

	.type	_err_str_break, @object
	.balign 1
_err_str_break:
	.string	"BREAKPOINT\n"
	.size	_err_str_break, .-_err_str_break

	.type	_err_str_watch, @object
	.balign 1
_err_str_watch:
	.string	"WATCHPOINT\n"
	.size	_err_str_watch, .-_err_str_watch

	.type	_err_reg_names, @object
	.balign 1
_err_reg_names:
	.string	"r1:  "
	.string	"r2:  "
	.string	"r3:  "
	.string	"r4:  "
	.string	"r5:  "
	.string	"r6:  "
	.string	"r7:  "
	.string	"r8:  "
	.string	"r9:  "
	.string	"r10: "
	.string	"r11: "
	.string	"r12: "
	.string	"r13: "
	.string	"r14: "
	.string	"r15: "
	.string	"r16: "
	.string	"r17: "
	.string	"r18: "
	.string	"r19: "
	.string	"r20: "
	.string	"r21: "
	.string	"r22: "
	.string	"r23: "
	.string	"r24: "
	.string	"r25: "
	.string	"r26: "
	.string	"r27: "
	.string	"sp:  "
	.string	"ra:  "
	.string	"ea:  "
	.string	"ba:  "
	.string	"ip:  "
	.string	"im:  "
	.string	"ie:  "
	.string	"eba: "
	.string	"cfg: "
	.size	_err_reg_names, .-_err_reg_names

	.type	_err_str_newline, @object
	.balign 1
_err_str_newline:
	.string	"\n"
	.size	_err_str_newline, .-_err_str_newline

	.type	_err_str_spaces, @object
	.balign 1
_err_str_spaces:
	.string	"      "
	.size	_err_str_spaces, .-_err_str_spaces

#endif /* __LM32_VERBOSE_HANDLERS__ */

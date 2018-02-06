/* the define is needed for binary distributions */
#define __EECFG_THIS_IS_ASSEMBLER__
#include "eecfg.h"
#include "cpu/pic32/inc/ee_compiler.h"

.global EE_pic32_hal_ready2stacked
.extern EE_hal_endcycle_next_thread	

#ifdef __MULTI__

#ifdef __IRQ_STACK_NEEDED__
.global	EE_pic32_change_to_irq_tos
.global	EE_pic32_change_from_irq_tos
#endif
.global	EE_pic32_hal_stkchange
.extern	EE_pic32_system_tos
.extern	EE_pic32_active_tos
.extern EE_hal_endcycle_next_tos

.text
////////////////////////////////////////////////////////////////////////////////
//
// MACRO Actions:
//  - 1. If exiting_tos == entering_tos nothing must be done (end of macro)
//  - 2. Save registers in the current stack (exiting one)
//  - 3. Save the SP (exiting_tos) in EE_pic32_system_tos[EE_pic32_active_tos]
//  - 4. Set EE_pic32_active_tos = tos_index (index of the entering_tos)
//  - 5. Load the SP with the entering_tos in EE_pic32_system_tos[tos_index]
//  - 6. Load registers from current stack (entering one)
//
////////////////////////////////////////////////////////////////////////////////
.macro EE_CHANGE_TOS_MACRO
	lw	$t0,%gp_rel(EE_pic32_active_tos)($gp) 
	beq	$a1,$t0,2f	// if next_SP == current_SP do nothing	
	addiu   $sp,$sp,-36	// Save the context
	sw	$s8,32($sp)
	sw	$s7,28($sp)
	sw	$s6,24($sp)
	sw	$s5,20($sp)
	sw	$s4,16($sp)
	sw	$s3,12($sp)
	sw	$s2,8($sp)
	sw	$s1,4($sp)
	sw	$s0,0($sp)
	// Save Stack Pointer: EE_pic32_system_tos[EE_pic32_active_tos] = SP
	la	$t1,EE_pic32_system_tos 
	sll	$t0, $t0, 2
        addu    $t0, $t0, $t1
	sw	$sp, 0($t0)
	// Update new SP_idx: EE_pic32_active_tos = tos_index
        sw	$a1,%gp_rel(EE_pic32_active_tos)($gp)
	// Restore Stack Pointer: SP = EE_pic32_system_tos[tos_index]
	sll	$a1, $a1, 2
        addu    $a1, $a1, $t1
	lw	$sp, 0($a1)
	lw	$s8,32($sp)	// Restore the context
	lw	$s7,28($sp)
	lw	$s6,24($sp)
	lw	$s5,20($sp)
	lw	$s4,16($sp)
	lw	$s3,12($sp)
	lw	$s2,8($sp)
	lw	$s1,4($sp)
	lw	$s0,0($sp)
	addiu   $sp,$sp,36
2:
.endm
#endif // __MULTI__

////////////////////////////////////////////////////////////////////////////////
//
// MONOSTACK:
// void EE_pic32_hal_ready2stacked(EE_ADDR thread_addr);
//
// MULTISTACK:
// void EE_pic32_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index);
//
// a0 = thread_addr	-> Function pointer to the thread body to activate.
// a1 = tos_index	-> Index in EE_pic32_system_tos[] memory array 
//                         from which the SP of the entering thread
//                         (the caller) must be retrieved.
//
// Actions: 
//  - NOTE: the context is saved by the C compiler calling mechanism, the 
//          caller (exiting thread) save what it has to save and the callee 
//          (entering thread) will save what it has to (the actual call is done
//          by this function). 
//  - 1. If MULTISTACK: swap stacks of the exiting thread and the entering one
//                      (initially the entering SP is in a1)
//  - 2. Enable interrupts: the thread MUST run with enabled interrupts
//  - 3. Execute the thread: call the function pointer (initially is in a0)
//  - 4. Disable interrupts
//  - 5. Call EE_thread_end_instance: this check if there is an other threads to
//                                    be activated by setting the global
//                                    variable EE_hal_endcycle_next_thread
//  - 6. If MULTISTACK: read the SP for the new (possible) entering thread from 
//                      from the global variable EE_hal_endcycle_next_tos
//  - 7. If EE_hal_endcycle_next_thread != 0 activate it: goint to point 1.
//  - 8. If MULTISTACK: swap stacks of the entering thread and the exiting one
//  - 9. If EE_hal_endcycle_next_thread == 0: go the the stacked thread, i.e.
//                                            simply return to the stacked one
//
////////////////////////////////////////////////////////////////////////////////
.ent EE_pic32_hal_ready2stacked
EE_pic32_hal_ready2stacked:
	addiu   $sp,$sp,-4		// Save regs and take function param
	sw      $ra,0($sp)     
1:
	#ifdef __MULTI__
	EE_CHANGE_TOS_MACRO 		// Switch to the SP of the new thread
	#endif
	ei  				// enable interrupts
	jal 	$a0 			// call the thread
	di  				// disable interrupts
	jal EE_thread_end_instance 	// call the thread end instance
	#ifdef __MULTI__
	lw	$a1,%gp_rel(EE_hal_endcycle_next_tos)($gp) 
	#endif
	lw	$a0,%gp_rel(EE_hal_endcycle_next_thread)($gp) 
	bne	$a0,$0,1b		// do {activate ready} while (next != 0)
	#ifdef __MULTI__
	EE_CHANGE_TOS_MACRO
	#endif
	lw	$ra, 0($sp) 		// restore regs
	addiu	$sp,$sp,4
	jr	$ra			// return to the stacked thread
.end EE_pic32_hal_ready2stacked

#ifdef __MULTI__
////////////////////////////////////////////////////////////////////////////////
//
// MONOSTACK:
// not defined
//
// MULTISTACK: 
// void EE_pic32_hal_stkchange(EE_UREG tos_index);
//
// a0 = tos_index	-> Index in EE_pic32_system_tos[] memory array 
//                         from which the SP of the entering thread
//                         (the caller) must be retrieved.
//
// Actions: 
//  - 1. Save registers in the current stack (exiting one)
//  - 2. Save the SP (exiting_tos) in EE_pic32_system_tos[EE_pic32_active_tos]
//  - 3. Set EE_pic32_active_tos = tos_index (index of the entering_tos)
//  - 4. Load the SP with the entering_tos in EE_pic32_system_tos[tos_index]
//  - 5. Load registers from current stack (entering one)
//
////////////////////////////////////////////////////////////////////////////////
.ent EE_pic32_hal_stkchange
EE_pic32_hal_stkchange:
	addiu   $sp,$sp,-40	// Save the context
	sw	$ra,36($sp)	
	sw	$s8,32($sp)
	sw	$s7,28($sp)
	sw	$s6,24($sp)
	sw	$s5,20($sp)
	sw	$s4,16($sp)
	sw	$s3,12($sp)
	sw	$s2,8($sp)
	sw	$s1,4($sp)
	sw	$s0,0($sp)
	// Save Stack Pointer: EE_pic32_system_tos[EE_pic32_active_tos] = SP
	la	$t1,EE_pic32_system_tos 
	lw	$t0,%gp_rel(EE_pic32_active_tos)($gp) 
	sll	$t0, $t0, 2
        addu    $t0, $t0, $t1
	sw	$sp, 0($t0)
	// Update new SP_idx: EE_pic32_active_tos = tos_index
        sw	$a0,%gp_rel(EE_pic32_active_tos)($gp)
	// Restore Stack Pointer: SP = EE_pic32_system_tos[tos_index]
	sll	$a0, $a0, 2
        addu    $a0, $a0, $t1
	lw	$sp, 0($a0)
	lw	$ra,36($sp)	// Restore the context
	lw	$s8,32($sp)	
	lw	$s7,28($sp)
	lw	$s6,24($sp)
	lw	$s5,20($sp)
	lw	$s4,16($sp)
	lw	$s3,12($sp)
	lw	$s2,8($sp)
	lw	$s1,4($sp)
	lw	$s0,0($sp)
	addiu   $sp,$sp,40
	jr	$ra			// return to the caller
.end EE_pic32_hal_stkchange
#endif // __MULTI__

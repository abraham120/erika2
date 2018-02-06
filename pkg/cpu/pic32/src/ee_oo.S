#include "cpu/pic32/inc/ee_compiler.h"

.global	EE_pic32_terminate_task
.global EE_pic32_terminate_savestk
	
.text

////////////////////////////////////////////////////////////////////////////////
//
// void EE_pic32_terminate_savestk(EE_ADDR addr_store_sp, EE_ADDR realbody);
//
// a0 = addr_store_sp	-> Address where the SP has to be saved
// a1 = realbody 	-> Address of the function (tread) to be called
//
// Actions: 
//  - NOTE: Interrupt are enabled.
//  - Save the context: all the registers not preserved by the caller MUST be
//                      saved. TODO: I did it looking at the prologue the 
//                      compiler attach to ISR defined in C (making use of 
//                      __attribute__(interrupt)). Is thi ok? Maybe to mutch?
//  - Save the SP: the save the SP in memory at the address pointed by a0. 
//  - Save the a0: in case the TASK ends without calling the TerminateTask 
//                 (i.e. with a return) we have a backup to restore SP. We can
//                 save the address in a0 in a register that will be preserved
//                 by the callee (for instance t0). Does the calle save a0?
//  - Call the thread: the thread is the function pointer in a1.
//  - Restore the a0: in case the TASK ends without calling the TerminateTask
//                    we have to restore a0 and then execute here the 
//                    EE_pic32_terminate_task.
//
////////////////////////////////////////////////////////////////////////////////
.ent EE_pic32_terminate_savestk
EE_pic32_terminate_savestk:
	addiu   $sp,$sp,-92	// Save the context
	sw	$ra,84($sp)
	sw	$t9,80($sp)
	sw	$t8,76($sp)
	sw	$s0,72($sp)
	sw	$t7,68($sp)
	sw	$t6,64($sp)
	sw	$t5,60($sp)
	sw	$t4,56($sp)
	sw	$t3,52($sp)
	sw	$t2,48($sp)
	sw	$t1,44($sp)
	sw	$t0,40($sp)
	sw	$a3,36($sp)
	sw	$a2,32($sp)
	sw	$a1,28($sp)
	sw	$a0,24($sp)
	sw	$v1,20($sp)
	sw	$v0,16($sp)
	sw	$sp,0($a0)	// Save the SP
	move	$t0,$a0		// Backup: Maybe this is useless?
	jal	$a1		// Call the thread function: should not return.
	move	$a0,$t0		// Restore: Maybe this is useless?
	// NOTE: no return is done, thus the EE_pic32_terminate_task follows.
.end EE_pic32_terminate_savestk
////////////////////////////////////////////////////////////////////////////////
//
// void  EE_pic32_terminate_task(EE_ADDR addr_stored_sp);
//
// a0 = addr_stored_sp	-> Address where the SP has been saved
//
// Actions: 
//  - NOTE: Interrupt are enabled.
//  - Restore the SP: the SP is in memory at the address pointed by a0. 
//  - Restore the context: all the registers have been saved by the 
//                         EE_pic32_terminate_savestk funciton.
//  - Return to caller: make the jump return.
//
////////////////////////////////////////////////////////////////////////////////
.ent EE_pic32_terminate_task 
EE_pic32_terminate_task:
	lw	$sp,0($a0)	// Restore the SP
	lw	$ra,84($sp)	// Restore the context
	lw	$t9,80($sp)
	lw	$t8,76($sp)
	lw	$s0,72($sp)
	lw	$t7,68($sp)
	lw	$t6,64($sp)
	lw	$t5,60($sp)
	lw	$t4,56($sp)
	lw	$t3,52($sp)
	lw	$t2,48($sp)
	lw	$t1,44($sp)
	lw	$t0,40($sp)
	lw	$a3,36($sp)
	lw	$a2,32($sp)
	lw	$a1,28($sp)
	lw	$a0,24($sp)
	lw	$v1,20($sp)
	lw	$v0,16($sp)
	addiu   $sp,$sp,92
	jr 	$ra		// Return to caller
.end EE_pic32_terminate_task 

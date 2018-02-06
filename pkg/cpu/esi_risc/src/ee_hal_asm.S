/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, Pebble Bay Consulting Ltd.
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

/* Author: Steve Langstaff, Pebble Bay Consulting Ltd, 2010
 *
 */

/*
 * SUPPORT_LIBC_REENTRANCY:
 * Consult chapter 10 "Reentrancy" the newlib manual.
 * If SUPPORT_LIBC_REENTRANCY is undefined: (default)
 *		The user may use the non-reentrant library functions in one thread only.
 *		In other threads the user should use the reentrant versions (_name_r) of
 *          the library functions, after initializing a reentrancy structure for
 *          each thread. The user should pass a pointer to this structure as the
 *          extra argument for all such library functions.
 * If SUPPORT_LIBC_REENTRANCY is defined: (TODO - not yet supported)
 *   	The user may use the non-reentrant library functions in any thread.
 *		The OS will automatically create and initialise a reentrancy structure
 *      	for each thread, and automatically swap the global _impure_ptr on
 *          each context change.
 */
#ifdef	SUPPORT_LIBC_REENTRANCY
        .extern _impure_ptr
#endif

/*
 * Save all of the caller-save registers and 4 extras
 */
.global	isr_save_context
isr_save_context:
        add		sp, -((__registers__/2)+4) * (__bits__/8)

#if	__registers__ == 8
        s       (sp+[5]), r4
        s       (sp+[6]), r5
        s       (sp+[7]), r6
        s       (sp+[8]), r7
#endif

#if	__registers__ == 16
        s       (sp+[5]), r8
        s       (sp+[6]), r9
        s       (sp+[7]), r10
        s       (sp+[8]), r11
        s       (sp+[9]), r12
        s       (sp+[10]), r13
        s       (sp+[11]), r14
        s       (sp+[12]), r15
#endif

#if	__registers__ == 32
        s       (sp+[5]), r8
        s       (sp+[6]), r9
        s       (sp+[7]), r10
        s       (sp+[8]), r11
        s       (sp+[9]), r12
        s       (sp+[10]), r13
        s       (sp+[11]), r14
        s       (sp+[12]), r15
        s       (sp+[13]), r16
        s       (sp+[14]), r17
        s       (sp+[15]), r18
        s       (sp+[16]), r19
        s       (sp+[17]), r20
        s       (sp+[18]), r21
        s       (sp+[19]), r22
        s       (sp+[20]), r23
#endif

        rcsr    arg0, Thread, EPC
        s       (sp+[1]), arg0
        rcsr    arg0, Thread, ECAS
        s       (sp+[2]), arg0
        rcsr    arg0, Thread, ETC
        s       (sp+[3]), arg0

#ifdef	SUPPORT_LIBC_REENTRANCY
#if __bits__ == 16
        l       arg0, [_impure_ptr]
#else
        l       arg0, (gp+[_impure_ptr])
#endif
        s       (sp+[4]), arg0
#endif

        /* Come out of exception mode, so we can perform syscalls */
        rcsr    arg0, Thread, TC
        or      arg0, 0x2
        wcsr    Thread, TC, arg0
		ret

/*
 * Restore all of the caller-save registers and 4 extras
 */
.global isr_restore_context
isr_restore_context:

#ifdef	SUPPORT_LIBC_REENTRANCY
        l       arg0, (sp+[4])
#if __bits__ == 16
        s       [_impure_ptr], arg0
#else
        l       arg1, (gp+[_impure_ptr])
        s       (arg1), arg0
#endif
#endif

        l       arg0, (sp+[3])
        wcsr    Thread, ETC, arg0
        l       arg0, (sp+[2])
        wcsr    Thread, ECAS, arg0
        l       arg0, (sp+[1])
        wcsr    Thread, EPC, arg0

#if	__registers__ == 8
        l       r4, (sp+[5])
        l       r5, (sp+[6])
        l       r6, (sp+[7])
        l       r7, (sp+[8])
#endif

#if	__registers__ == 16
        l       r8, (sp+[5])
        l       r9, (sp+[6])
        l       r10, (sp+[7])
        l       r11, (sp+[8])
        l       r12, (sp+[9])
        l       r13, (sp+[10])
        l       r14, (sp+[11])
        l       r15, (sp+[12])
#endif

#if	__registers__ == 32
        l       r8, (sp+[5])
        l       r9, (sp+[6])
        l       r10, (sp+[7])
        l       r11, (sp+[8])
        l       r12, (sp+[9])
        l       r13, (sp+[10])
        l       r14, (sp+[11])
        l       r15, (sp+[12])
        l       r16, (sp+[13])
        l       r17, (sp+[14])
        l       r18, (sp+[15])
        l       r19, (sp+[16])
        l       r20, (sp+[17])
        l       r21, (sp+[18])
        l       r22, (sp+[19])
        l       r23, (sp+[20])
#endif

        add		sp, ((__registers__/2)+4) * (__bits__/8)

		ret

		.extern	EE_isr_high_level_handler
		.global EE_isr_low_level_handler
EE_isr_low_level_handler:
		add		sp, -(__bits__/8)
		s       (sp+[1]), ra
		call    isr_save_context
		call    EE_isr_high_level_handler
		call    isr_restore_context
		l       ra, (sp+[1])
		add		sp,  (__bits__/8)
		eret

#ifdef	__MULTI__

#ifdef __IRQ_STACK_NEEDED__

		.extern EE_isr_stack_temp

		.global EE_isr_stack_swap_and_call
EE_isr_stack_swap_and_call:
		/* arg0 - handler function to call */
		/* arg1 - top of stack to use for call */

		/* push our return address onto the stack */
		add		sp, -(__bits__/8)
		s       (sp+[1]), ra

		/* store the current sp in the global EE_isr_stack_temp */
#if __bits__ == 16
        l       arg2, [EE_isr_stack_temp]
#else
        l       arg2, (gp+[EE_isr_stack_temp])
#endif
        s       (arg2), sp

		/* swap to the new sp */
		mv		sp, arg1

		/* call the high-level handler */
		call	arg0

		/* recover the old stack pointer */
#if __bits__ == 16
        l       arg2, [EE_isr_stack_temp]
#else
        l       arg2, (gp+[EE_isr_stack_temp])
#endif
        l       sp, (arg2)

		/* recover our return address from the stack */
		l       ra, (sp+[1])
		add		sp,  (__bits__/8)
		ret
#endif

/* Pseudocode for the context change routine:

void EE_std_change_context(EE_TID tid)
     begin:
      EE_UREG tos_index = EE_std_thread_tos[tid+1];
      if (tos_index != EE_std_active_tos)
      {
          save_caller_saved_registers();
          switch_stacks(tos_index);
          restore_caller_saved_registers();
      }
      if (is_not_marked_stacked(tid)) {
          tid = EE_std_run_task_code(tid);
          goto begin;
      }
*/
		.global EE_esi_change_context
		.extern EE_std_thread_tos
		.extern EE_std_system_tos
		.extern EE_std_active_tos
EE_esi_change_context:
		/* tid comes to us in arg0 */

		/* work out EE_std_thread_tos[(tid&0x7fffffff)+1] */
		/* mask out stacked bit (MSB) */
#if	__bits__ == 16
		l			arg1, 0x8000
#elif __bits__ == 32
		l			arg1, 0
		orhi		arg1, 0x8000
#endif
		andnot		arg2, arg0, arg1

		add		arg2, 1
		/* shift to index into EE_std_thread_tos[]) */
		sl		arg2, arg2, (__bits__/16)

		/* get EE_std_thread_tos into arg1 */
#if __bits__ == 16
        l       arg1, [EE_std_thread_tos]
#else
        l       arg1, (gp+[EE_std_thread_tos])
#endif

		add		arg2, arg1, arg2

		/* get tos_index into arg1 */
		l		arg1, (arg2+[0])

		/* if (tos_index != EE_std_active_tos) */

		/* get EE_std_active_tos into arg2 */
#if __bits__ == 16
        l       arg2, ([EE_std_active_tos])
#else
        l       arg2, (gp+[EE_std_active_tos])
        l       arg2, (arg2)
#endif
		/* so now we have:
		 * tos_index in arg1
		 * EE_std_active_tos in arg2
		 */
		cmp		arg1, arg2
		be		EE_esi_change_context_switch_not_required

		/* save registers */
		/* the following is slightly wasteful of memory but easy to read! */
        add     sp, -__registers__*__bits__/8

#if	__registers__ == 8
        s       (sp+[2]), r2
		/* skip gp */
		/* skip arg0 */
        s       (sp+[5]), r5
        s       (sp+[6]), r6
        s       (sp+[7]), r7
#endif

#if	__registers__ == 16
        s       (sp+[2]), r2
        s       (sp+[3]), r3
        s       (sp+[4]), r4
        s       (sp+[5]), r5
        s       (sp+[6]), r6
		/* skip gp */
		/* skip arg0 */
        s       (sp+[9]), r9
        s       (sp+[10]), r10
        s       (sp+[11]), r11
        s       (sp+[12]), r12
        s       (sp+[13]), r13
        s       (sp+[14]), r14
        s       (sp+[15]), r15
#endif

#if	__registers__ == 32
        s       (sp+[2]), r2
        s       (sp+[3]), r3
        s       (sp+[4]), r4
        s       (sp+[5]), r5
        s       (sp+[6]), r6
        s       (sp+[7]), r7
        /* skip arg0 */
        s       (sp+[9]), r9
        s       (sp+[10]), r10
        s       (sp+[11]), r11
        s       (sp+[12]), r12
        s       (sp+[13]), r13
        s       (sp+[14]), r14
        s       (sp+[15]), r15
        s       (sp+[16]), r16
        s       (sp+[17]), r17
        s       (sp+[18]), r18
        s       (sp+[19]), r19
        s       (sp+[20]), r20
        s       (sp+[21]), r21
        s       (sp+[22]), r22
        s       (sp+[23]), r23
        s       (sp+[24]), r24
        s       (sp+[25]), r25
        s       (sp+[26]), r26
        s       (sp+[27]), r27
        s       (sp+[28]), r28
        s       (sp+[29]), r29
        s       (sp+[30]), r30
        /* skip gp */
#endif
		/* switch_stacks(tos_index) */
		/* EE_std_system_tos[EE_std_active_tos].SYS_tos = sp; */
#if __bits__ == 16
        l       arg3, [EE_std_system_tos]
#else
        l       arg3, (gp+[EE_std_system_tos])
#endif

		sl		arg2, arg2, (__bits__/16)
		add		arg2, arg3, arg2

		/* save stack pointer */
		s		(arg2+[0]), sp

		/* sp = EE_std_system_tos[tos_index].SYS_tos; */
		sl		arg2, arg1, (__bits__/16)
		add		arg2, arg3, arg2

		/* save stack pointer */
		l		sp, (arg2+[0])

		/* EE_std_active_tos = tos_index */
#if __bits__ == 16
        s       ([EE_std_active_tos]), arg1
#else
        l       arg2, (gp+[EE_std_active_tos])
        s       (arg2), arg1
#endif

		/* restore registers */

#if	__registers__ == 8
        l       r2, (sp+[2])
		/* skip gp */
		/* skip arg0 */
        l       r5, (sp+[5])
        l       r6, (sp+[6])
        l       r7, (sp+[7])
#endif

#if	__registers__ == 16
        l       r2, (sp+[2])
        l       r3, (sp+[3])
        l       r4, (sp+[4])
        l       r5, (sp+[5])
        l       r6, (sp+[6])
		/* skip gp */
		/* skip arg0 */
        l       r9, (sp+[9])
        l       r10, (sp+[10])
        l       r11, (sp+[11])
        l       r12, (sp+[12])
        l       r13, (sp+[13])
        l       r14, (sp+[14])
        l       r15, (sp+[15])
#endif

#if	__registers__ == 32
        l       r2, (sp+[2])
        l       r3, (sp+[3])
        l       r4, (sp+[4])
        l       r5, (sp+[5])
        l       r6, (sp+[6])
        l       r7, (sp+[7])
		/* skip arg0 */
        l       r9, (sp+[9])
        l       r10, (sp+[10])
        l       r11, (sp+[11])
        l       r12, (sp+[12])
        l       r13, (sp+[13])
        l       r14, (sp+[14])
        l       r15, (sp+[15])
        l       r16, (sp+[16])
        l       r17, (sp+[17])
        l       r18, (sp+[18])
        l       r19, (sp+[19])
        l       r20, (sp+[20])
        l       r21, (sp+[21])
        l       r22, (sp+[22])
        l       r23, (sp+[23])
        l       r24, (sp+[24])
        l       r25, (sp+[25])
        l       r26, (sp+[26])
        l       r27, (sp+[27])
        l       r28, (sp+[28])
        l       r29, (sp+[29])
        l       r30, (sp+[30])
        /* skip gp */
#endif
        add     sp, __registers__*__bits__/8

EE_esi_change_context_switch_not_required:
		/*
      	if (is_not_marked_stacked(tid))
      	{
        	tid = EE_std_run_task_code(tid);
          	goto begin;
      	}
      	*/
		/* mask in stacked bit (MSB) */
#if	__bits__ == 16
		l			arg1, 0x8000
#elif __bits__ == 32
		l			arg1, 0
		orhi		arg1, 0x8000
#endif
		and			arg2, arg0, arg1
		bnz			arg2, EE_esi_change_context_end
		/* mask off top bit of tid */
		andnot		arg0, arg0, arg1
		/* preserve our return address */
		add			sp, -__bits__/8
		s	      	(sp+[1]), r1
		call		EE_std_run_task_code
		l	      	r1, (sp+[1])
		add     	sp, __bits__/8
		b 			EE_esi_change_context

EE_esi_change_context_end:
		ret

#endif

/*******************************************************************************
* get_sp()
*
* Return the current value of the stack pointer
*
*******************************************************************************/
		.global		get_sp
get_sp:
		mv			arg0, sp
		ret

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)
/*******************************************************************************
* EE_hal_terminate_savestk(EE_TID tid)
*
* Save the stack prior to calling a thread entry point
*
*******************************************************************************/
		.global		EE_hal_terminate_savestk
EE_hal_terminate_savestk:
		/* arg0 - tid (thread id) */
		sl		arg0, arg0, (__bits__/16)

		/* arg1 = EE_terminate_real_th_body[tid] */
#if __bits__ == 16
        l       arg1, [EE_terminate_real_th_body]
#else
        l       arg1, (gp+[EE_terminate_real_th_body])
#endif
		add		arg1, arg0, arg1
		l		arg1, (arg1)

		/* arg2 = & EE_terminate_data[tid] */
#if __bits__ == 16
        l       arg2, [EE_terminate_data]
#else
        l       arg2, (gp+[EE_terminate_data])
#endif
		add		arg2, arg0, arg2

		/* save the registers after leaving some space for registers */
        add     sp, -__registers__*__bits__/8
		s		(arg2), sp

#if	__registers__ == 8
        s       (sp+[1]), r1
        s       (sp+[2]), r2
		/* skip gp */
		/* skip arg0 */
        s       (sp+[5]), r5
        s       (sp+[6]), r6
        s       (sp+[7]), r7
#endif

#if	__registers__ == 16
        s       (sp+[1]), r1
        s       (sp+[2]), r2
        s       (sp+[3]), r3
        s       (sp+[4]), r4
        s       (sp+[5]), r5
        s       (sp+[6]), r6
		/* skip gp */
		/* skip arg0 */
        s       (sp+[9]), r9
        s       (sp+[10]), r10
        s       (sp+[11]), r11
        s       (sp+[12]), r12
        s       (sp+[13]), r13
        s       (sp+[14]), r14
        s       (sp+[15]), r15
#endif

#if	__registers__ == 32
        s       (sp+[1]), r1
        s       (sp+[2]), r2
        s       (sp+[3]), r3
        s       (sp+[4]), r4
        s       (sp+[5]), r5
        s       (sp+[6]), r6
        s       (sp+[7]), r7
        /* skip arg0 */
        s       (sp+[9]), r9
        s       (sp+[10]), r10
        s       (sp+[11]), r11
        s       (sp+[12]), r12
        s       (sp+[13]), r13
        s       (sp+[14]), r14
        s       (sp+[15]), r15
        s       (sp+[16]), r16
        s       (sp+[17]), r17
        s       (sp+[18]), r18
        s       (sp+[19]), r19
        s       (sp+[20]), r20
        s       (sp+[21]), r21
        s       (sp+[22]), r22
        s       (sp+[23]), r23
        s       (sp+[24]), r24
        s       (sp+[25]), r25
        s       (sp+[26]), r26
        s       (sp+[27]), r27
        s       (sp+[28]), r28
        s       (sp+[29]), r29
        s       (sp+[30]), r30
        /* skip gp */
#endif

		/* call the thread body */
		call	arg1

		/* task terminated with a return */
		/* so load our return address from the stack and tidy up */
        l       r1, (sp+[1])
		add     sp, __registers__*__bits__/8
		ret

/*******************************************************************************
* EE_hal_terminate_task(EE_TID tid)
*
* Restore the stack when tidying up after calling a thread entry point
*
*******************************************************************************/
		.global		EE_hal_terminate_task
EE_hal_terminate_task:
		/* arg0 - tid (thread id) */
		sl		arg0, arg0, (__bits__/16)

		/* arg2 = & EE_terminate_data[tid] */
#if __bits__ == 16
        l       arg2, [EE_terminate_data]
#else
        l       arg2, (gp+[EE_terminate_data])
#endif
		add		arg2, arg0, arg2
		/* restore the stack pointer */
		l		sp, (arg2)

		/* restore registers */

#if	__registers__ == 8
        l       r1, (sp+[1])
        l       r2, (sp+[2])
		/* skip gp */
		/* skip arg0 */
        l       r5, (sp+[5])
        l       r6, (sp+[6])
        l       r7, (sp+[7])
#endif

#if	__registers__ == 16
        l       r1, (sp+[1])
        l       r2, (sp+[2])
        l       r3, (sp+[3])
        l       r4, (sp+[4])
        l       r5, (sp+[5])
        l       r6, (sp+[6])
		/* skip gp */
		/* skip arg0 */
        l       r9, (sp+[9])
        l       r10, (sp+[10])
        l       r11, (sp+[11])
        l       r12, (sp+[12])
        l       r13, (sp+[13])
        l       r14, (sp+[14])
        l       r15, (sp+[15])
#endif

#if	__registers__ == 32
        l       r1, (sp+[1])
        l       r2, (sp+[2])
        l       r3, (sp+[3])
        l       r4, (sp+[4])
        l       r5, (sp+[5])
        l       r6, (sp+[6])
        l       r7, (sp+[7])
		/* skip arg0 */
        l       r9, (sp+[9])
        l       r10, (sp+[10])
        l       r11, (sp+[11])
        l       r12, (sp+[12])
        l       r13, (sp+[13])
        l       r14, (sp+[14])
        l       r15, (sp+[15])
        l       r16, (sp+[16])
        l       r17, (sp+[17])
        l       r18, (sp+[18])
        l       r19, (sp+[19])
        l       r20, (sp+[20])
        l       r21, (sp+[21])
        l       r22, (sp+[22])
        l       r23, (sp+[23])
        l       r24, (sp+[24])
        l       r25, (sp+[25])
        l       r26, (sp+[26])
        l       r27, (sp+[27])
        l       r28, (sp+[28])
        l       r29, (sp+[29])
        l       r30, (sp+[30])
        /* skip gp */
#endif
        add     sp, __registers__*__bits__/8
        ret
#endif

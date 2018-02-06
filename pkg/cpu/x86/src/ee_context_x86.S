.global EE_std_change_context
.global EE_x86_thread_tos
.global EE_x86_system_tos

EE_std_change_context:
	mov 4(%esp), %eax # Get next TID from stack
	movl %eax, %ecx	  # Copy to ecx for retrieving actual ID
	and $0x7fffffff, %ecx # mask out stacked flag
	inc %ecx
	movl EE_x86_thread_tos(,%ecx,4), %ecx # get next tos index
	movl EE_x86_active_tos, %edx # get current thread index
	cmp %edx, %ecx	  # check if thread changes to itself
	je EE_std_change_context_skip  # if so: skip switch
	pushl %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	mov %esp, EE_x86_system_tos(,%edx, 4) # save stack pointer
	mov EE_x86_system_tos(,%ecx, 4), %esp # restore next stack pointer
	mov %ecx, EE_x86_active_tos	      # save current thread index
	popl %edi
	popl %esi
	popl %ebx
	popl %ebp
EE_std_change_context_skip:
	test %eax, %eax	   # If thread was stacked:
	js EE_std_change_context_bye  #  just return, restoring registers automatically
	push %eax	   # Else: call EE_std_run_task_code(tid);
	call EE_std_run_task_code # Start from the beginning
	mov %eax, 4(%esp)  # Copy next TID to stack for next interation
	jmp EE_std_change_context # see above
EE_std_change_context_bye:
	ret

#include "ee.h"

extern void EE_thread_not_terminated(void);

void EE_hal_terminate_savestk(EE_TID tid) {

    // save callee-saved registers
    asm volatile ("push %ebx; push %edi; push %esi; push %ebp");

    // --- EE_terminate_data[tid] = %esp
    asm volatile ("mov %%esp, EE_terminate_data(,%%eax,4)" : : : "memory" );

    // call actual thread body
    // EE_terminate_real_th_body[tid]();
    asm volatile ("call *EE_terminate_real_th_body(,%%eax,4)" ::: "memory" );

    // the task terminated with a return; do the usual cleanup
    // EE_thread_not_terminated();
    asm volatile ("jmp EE_thread_not_terminated");
}


void EE_hal_terminate_task(EE_TID tid) {

    // restore stack pointer:
    // %esp = EE_terminate_data[tid]
    asm volatile ("mov %0, %%esp" : : "m" (EE_terminate_data[tid]) : );

    // pop callee-saved registers
    asm volatile ("pop %ebp; pop %esi; pop %edi; pop %ebx");

    // ret...
}



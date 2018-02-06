#ifndef APP_H
#define APP_H

void discard(EE_UREG x);

EE_INT32 CallMyTaskTrustedService(EE_INT32 arg);
EE_INT32 CallMyIsrTrustedService(EE_INT32 arg);

/* This bypasses the normal trusted function mechanism */
#ifdef __DCC__
__asm EE_INT32 CallMyQuickTrustedService(EE_INT32 x)
{
% reg x
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, x
	li	r0, EE_ID_TRUSTED_MyQuickTrustedService
	sc
}
#else
#error "Compiler not supported"
#endif

#endif /* APP_H */

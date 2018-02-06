#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#define TRUE 1

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__

#define StatusType int

__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void) {
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void) {
  EE_hal_enableIRQ();
}

__INLINE__ int __ALWAYS_INLINE__ TerminateTask(void)
{
	return 0;
}

#define OSDEFAULTAPPMODE 1
__INLINE__ int __ALWAYS_INLINE__ StartOS(int i)
{
	_asm("cli");
	return 0;
}
#endif

#endif /* __APPLICATION_H__ */
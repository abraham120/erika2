#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <ee.h>
#include <ee_irq.h>
#include "shared.h"

/* just a set of constant delays */
#define BASE_DELAY 250000
#define SMALL_DELAY BASE_DELAY/16
#define MEDIUM_DELAY BASE_DELAY/8
#define LARGE_DELAY BASE_DELAY

/* define a function input parameter as global (shared among CPUs)  */
#define INTER_PROC_COMM 1
/* define a function input parameter as local (read/write by a single CPU) */
#define LOCAL_COMM 0

/*
 * Function performing a configurable delay
 */
static inline void delay(unsigned int my_delay)
{
	/* declared volatile to prevent from compiler optimization */
	volatile unsigned int cnt = 0;

	while (++cnt < my_delay)
		;
}

/*
 * Function performing shared memory set
 */
static inline void set_shared_value(int val, volatile int indata[])
{
	unsigned i;

	delay(LARGE_DELAY);
	for (i = 0; i < SHARED_LONG_LEN; ++i) {
		indata[i] = val;
	}
}

/*
 * Function performing shared memory check
 */
static inline int check_shared_value(int val, volatile int indata[])
{
	int ret = 1;
	unsigned i;

	delay(LARGE_DELAY);
	for (i = SHARED_LONG_LEN; i > 0; --i) {
		if (indata[i - 1] != val)
			ret = 0;
	}
	return ret;
}

#ifdef __MSRP__
static inline void lock_var(void)
{
	EE_mpc5668_spin_in(MY_SPINLOCK);
}

static inline void unlock_var(void)
{
	EE_mpc5668_spin_out(MY_SPINLOCK);
}
#else
static inline void lock_var(void)
{
	GetResource(shared_var2);
}

static inline void unlock_var(void)
{
	ReleaseResource(shared_var2);
}
#endif


#ifdef __MSRP__
static inline void sys_start_up(void)
{
#ifdef __E200ZX_EXECUTE_FROM_RAM__
	EE_mpc5668_start_z0((void (*)(void))0x40020000);
#else
	EE_mpc5668_start_z0((void (*)(void))0x00030000);
#endif
}
#else
static inline void sys_start_up(void)
{
	/* empty body....z0 not present, thi is a single core system */
}
#endif

#endif


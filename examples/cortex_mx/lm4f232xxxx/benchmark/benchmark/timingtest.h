/*
 * timingtest.h
 * Timing test RTOSs
 */

#ifndef __TIMING_TEST_H__
#define __TIMING_TEST_H__

#include "bm_config.h"

#include <stdio.h> 

#if ! defined(TEST_TIMING)

#define timingtest_init()
#define timingtest_mark(x)

#else /* TEST_TIMING */

#define elapsed(e1, e2) (e2-e1)

enum timingtest_checkpoint {TIMINGTEST_CKP_BEFORE_ISR1,
			TIMINGTEST_CKP_AFTER_ISR1, TIMINGTEST_CKP_BEGIN_ISR1, 
			TIMINGTEST_CKP_END_ISR1, TIMINGTEST_CKP_BEFORE_ISR2, 
			TIMINGTEST_CKP_AFTER_ISR2, TIMINGTEST_CKP_BEGIN_ISR2,
			TIMINGTEST_CKP_END_ISR2, TIMINGTEST_CKP_BEGIN_ISR2_AT, 
			TIMINGTEST_CKP_END_ISR2_AT, TIMINGTEST_CKP_BEGIN_TASK1,
			TIMINGTEST_CKP_BEFORE_TASK2_FROM_TASK1, 
			TIMINGTEST_CKP_AFTER_TASK2_FROM_TASK1, TIMINGTEST_CKP_END_TASK1,
			TIMINGTEST_CKP_BEGIN_TASK2, TIMINGTEST_CKP_END_TASK2,
			TIMINGTEST_CKP_BEFORE_TASK2, TIMINGTEST_CKP_BEGIN_TASK2_PREE, 
			TIMINGTEST_CKP_END_TASK2_PREE, TIMINGTEST_CKP_AFTER_TASK2,
			TIMINGTEST_CKP_LAST};

			
#define TIMINGTEST_NUM_CHECKPOINTS ((unsigned)TIMINGTEST_CKP_LAST)

//#define TIMINGTEST_NUM_RECORDS 50

struct timingtest_rec {
	uint32_t checkpoint[TIMINGTEST_NUM_CHECKPOINTS];
};

struct analysis_rec {
	uint32_t mean;
	uint32_t low;
	uint32_t high;
	uint32_t ticks_mean;
	uint32_t ticks_low;
	uint32_t ticks_high;
	uint32_t count;
	char str[80];
};


extern struct timingtest_rec timingtest_times[TIMINGTEST_NUM_RECORDS + 2];
extern unsigned timingtest_count[TIMINGTEST_NUM_CHECKPOINTS];

void timingtest_init(void);

void timingtest_output_and_reset(void);

extern unsigned char str_buf[80];


__INLINE__ void timingtest_mark(enum timingtest_checkpoint ckp)
{
	uint32_t t = get_time_stamp();
	timingtest_times[timingtest_count[ckp]].checkpoint[ckp] = t;
	++timingtest_count[ckp];
#if 0	
	sprintf((char*)str_buf, "\r\nckp=%d",ckp);
	bm_uart_send_buffer(str_buf, strlen(str_buf));
#endif	
	if (ckp == TIMINGTEST_CKP_LAST - 1) {
		if (timingtest_count[ckp] == TIMINGTEST_NUM_RECORDS)
			timingtest_output_and_reset();
	}
}


#endif /* TEST_TIMING */

#endif /*__TIMING_TEST_H__ */

/*
 * timingtest.c
 * Timing test for RTOSs
 */

#include "timingtest.h"
#include "bm_config.h"

#include <stdarg.h>
#include <stdio.h>

/* Bits to discard in computation */
#define TIMING_DISC  0 /*4*/
#define scale_ticks(x) ((x) >> TIMING_DISC)
#define unscale_ticks(x) ((x) << TIMING_DISC)

/*#define FIRST_RUN_COUNT (TIMINGTEST_NUM_RECORDS * 9 / 10)*/
#define FIRST_RUN_COUNT 0

/* The array has space for more records in case any checkpoint lags behind  */
struct timingtest_rec timingtest_times[TIMINGTEST_NUM_RECORDS + 2];
unsigned timingtest_count[TIMINGTEST_NUM_CHECKPOINTS];
static unsigned timingtest_first;

#ifdef RES_IN_MEMORY
struct analysis_rec analysis_res[ANALISYS_RES_DIM];
#endif

/*res_size is used by the Keil tool, see Debug.ini*/
volatile uint32_t res_size = ANALISYS_RES_DIM;

#ifndef RES_IN_MEMORY

#ifndef USE_PRINT_OUT
static void myprintf(const char* format, ...)
{
#define MAX_CHARS 128
    char str[MAX_CHARS];
	//unsigned int intst = bm_disableIRQ();
    int len;
	
    va_list args;
    va_start( args, format );
    vsnprintf(str, MAX_CHARS, format, args);
	len = strlen(str); 
    va_end( args );
	/*
	if (bm_are_IRQs_enabled(intst))
        bm_enableIRQ();
	*/	
    bm_uart_send_buffer((unsigned char*)str, len);
	
	
}

#else
//static void print_out(unsigned char* str)
void print_out(unsigned char* str)
{
#ifdef BM_USE_UART
	bm_uart_send_buffer(str, strlen(str));
#endif	
}
#endif //!USE_PRINT_OUT

#endif //!RES_IN_MEMORY

struct time_analysis {
	uint32_t low;
	uint32_t hi;
	uint32_t sum;
	uint32_t count;
};


static void init_analysis(struct time_analysis *ta)
{
	ta->low = ~0UL;
	ta->hi = 0U;
	ta->sum = 0U;
	ta->count = 0U;
	res_size = ANALISYS_RES_DIM;
}


static void analyze_item(struct time_analysis *ta, uint32_t t)
{
	t = scale_ticks(t);
	if (t < ta->low)
		ta->low = t;
	if (t > ta->hi)
		ta->hi = t;
	ta->sum += t;
	++(ta->count);
}

#ifdef USE_PRINT_OUT
unsigned char str_buf[80];
#endif

	
static void print_analysis(const char *str, const struct time_analysis *ta)
{
#ifdef RES_IN_MEMORY	
	static unsigned int res_p = 0;
#endif
	uint32_t low = ticks_to_us(unscale_ticks(ta->low));
	uint32_t hi = ticks_to_us(unscale_ticks(ta->hi));
	uint32_t mean = ticks_to_us(unscale_ticks(ta->sum / ta->count));
	
	
#ifdef RES_IN_MEMORY	 
	sprintf(analysis_res[res_p].str,"%s (%d samples):\r\n", str, ta->count);
	analysis_res[res_p].mean = mean;
	analysis_res[res_p].low = low;
	analysis_res[res_p].high = hi;
	analysis_res[res_p].ticks_mean = ta->sum / ta->count;
	analysis_res[res_p].ticks_low = ta->low;
	analysis_res[res_p].ticks_high = ta->hi;

	res_p = (res_p + 1) % ANALISYS_RES_DIM; 
#else
#ifndef USE_PRINT_OUT	
	
	myprintf("%s (%d samples):\r\n", str, ta->count);
	myprintf("  Mean:    %d.%03d usec\r\n", mean / 1000, mean % 1000);
	myprintf("  Minimum: %d.%03d usec\r\n", low / 1000, low % 1000);
	myprintf("  Maximum: %d.%03d usec\r\n", hi / 1000, hi % 1000);
	myprintf("\r\n");
	
#else

	sprintf(str_buf, "%s (%d samples):\r\n", str, ta->count);
	print_out(str_buf);
	sprintf(str_buf, "  Mean:    %u.%03u usec - %u ticks\r\n", mean / 1000, 
		mean % 1000, ta->sum / ta->count);
	print_out(str_buf);
	sprintf(str_buf, "  Minimum: %u.%03u usec - %u ticks\r\n", low /1000,
		low % 1000, ta->low);
	print_out(str_buf);
	sprintf(str_buf,"  Maximum: %u.%03u usec - %u ticks\r\n", hi / 1000, 
		hi % 1000, ta->hi);
	print_out(str_buf);
	print_out("\r\n");
	
#endif //USE_PRINT_OUT

#endif // RES_IN_MEMORY
}


void timingtest_init(void)
{
	unsigned i;
	for (i = 0; i < TIMINGTEST_NUM_CHECKPOINTS; ++i)
		timingtest_count[i] = FIRST_RUN_COUNT;
	timingtest_first = FIRST_RUN_COUNT;
}


static void timingtest_reset(void)
{
	unsigned i;
	timingtest_first = 0;
	for (i = 0; i < TIMINGTEST_NUM_CHECKPOINTS; ++i) {
		timingtest_count[i] -= TIMINGTEST_NUM_RECORDS;
		if (timingtest_count[i] > timingtest_first)
			timingtest_first = timingtest_count[i];
	}
}


void timingtest_output_and_reset(void)
{
	unsigned i;

	/* ISR1 Latency */
	struct time_analysis ISR1_latency;
	/* ISR1 exit */
	struct time_analysis ISR1_exit;
	/* ISR2 Latency */
	struct time_analysis ISR2_latency;
	/* ISR2 exit */
	struct time_analysis ISR2_exit;
	/* New task from ISR */
	struct time_analysis ISR2_new_task;
	/* New task with preemption */
	struct time_analysis new_task_pree;
	/* New task without preemption*/
	struct time_analysis new_task_no_pree;
	/* Task exit*/
	struct time_analysis task_exit;
	/* Task (activated from IRQ) exit*/
	struct time_analysis taskIRQ_exit;
	
	init_analysis(&ISR1_latency);
	init_analysis(&ISR1_exit);
	init_analysis(&ISR2_latency);
	init_analysis(&ISR2_exit);
	init_analysis(&ISR2_new_task);
	init_analysis(&new_task_pree);
	init_analysis(&new_task_no_pree);
	init_analysis(&task_exit);
	init_analysis(&taskIRQ_exit);
	
	for (i = timingtest_first; i < TIMINGTEST_NUM_RECORDS; ++i) {
		/*struct timingtest_rec *prev, *curr;
		prev = &timingtest_times[i-1];*/
		
		struct timingtest_rec *curr = &timingtest_times[i];


		analyze_item(&ISR1_latency, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_BEFORE_ISR1],
				curr->checkpoint[TIMINGTEST_CKP_BEGIN_ISR1]));
		analyze_item(&ISR1_exit, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_END_ISR1],
				curr->checkpoint[TIMINGTEST_CKP_AFTER_ISR1]));
		analyze_item(&ISR2_latency, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_BEFORE_ISR2],
			curr->checkpoint[TIMINGTEST_CKP_BEGIN_ISR2]));
		analyze_item(&ISR2_exit, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_END_ISR2],
			curr->checkpoint[TIMINGTEST_CKP_AFTER_ISR2]));
		analyze_item(&ISR2_new_task, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_END_ISR2_AT],
			curr->checkpoint[TIMINGTEST_CKP_BEGIN_TASK1]));
		analyze_item(&new_task_pree, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_BEFORE_TASK2],
			curr->checkpoint[TIMINGTEST_CKP_BEGIN_TASK2_PREE]));				
		analyze_item(&new_task_no_pree, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_BEFORE_TASK2_FROM_TASK1],
			curr->checkpoint[TIMINGTEST_CKP_AFTER_TASK2_FROM_TASK1]));
		analyze_item(&task_exit, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_END_TASK2_PREE],
			curr->checkpoint[TIMINGTEST_CKP_AFTER_TASK2]));
		analyze_item(&taskIRQ_exit, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_END_TASK1],
			curr->checkpoint[TIMINGTEST_CKP_BEFORE_TASK2]));
/*
		analyze_item(&taskIRQ_exit, 
			elapsed(curr->checkpoint[TIMINGTEST_CKP_END_TASK1],
			curr->checkpoint[TIMINGTEST_CKP_AFTER_ISR2_AT]));
*/
	}
	
	print_analysis("ISR1 Latency", &ISR1_latency);
	print_analysis("ISR1 exit", &ISR1_exit);
	print_analysis("ISR2 Latency", &ISR2_latency);
	print_analysis("ISR2 exit", &ISR2_exit);
	print_analysis("New task from ISR", &ISR2_new_task);
	print_analysis("New task with preemption", &new_task_pree);
	print_analysis("New task without preemption", &new_task_no_pree);
	print_analysis("Task (not activated from IRQ) exit", &task_exit);
	print_analysis("Task (activated from IRQ) exit", &taskIRQ_exit);
	
	timingtest_reset();
}


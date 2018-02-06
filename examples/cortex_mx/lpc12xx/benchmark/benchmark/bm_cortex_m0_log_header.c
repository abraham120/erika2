#include "timingtest.h"

#include <stdarg.h>
#include <stdio.h>



void print_log_header(void)
{

#ifdef USE_PRINT_OUT
	print_out("********************************\r\n");
	print_out("*       Erika Enterprise       *\r\n");
	sprintf(str_buf, "* SystemCoreClock: %u Hz *\r\n", SystemCoreClock);
	print_out(str_buf);
	sprintf(str_buf, "* MainClock: %u Hz       *\r\n", MainClock);
	print_out(str_buf);
	sprintf(str_buf, "* IRQ latency register: 0x%X   *\r\n", 
		LPC_SYSCON->IRQLATENCY);
	print_out(str_buf);
	
#ifdef __FP__
	print_out("* Scheduler: FP                *\r\n");
#elif defined __OO_BCC1__
	print_out("* Scheduler: OO_BCC1           *\r\n");
#else
	print_out("WARNING: unknown scheduler!!!!!\r\n");
#endif

#ifdef __MONO__
	print_out("* Stack handling: MONOSTACK    *\r\n");
#elif defined (__MULTI__)
	print_out("* Stack handling:MULTI_STACK   *\r\n");
#else
	print_out("WARNING: unknow stack handling!!!!\r\n");
#endif


	print_out("********************************\r\n");
#endif //USE_PRINT_OUT

}

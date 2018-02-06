#include "timingtest.h"

#include <stdarg.h>
#include <stdio.h>



void print_log_header(void)
{

#ifdef USE_PRINT_OUT
	print_out("********************************\r\n");
	print_out("******     embOS 3.86e    ******\r\n");
	sprintf(str_buf, "* SystemCoreClock: %u Hz *\r\n", SystemCoreClock);
	print_out(str_buf);
	sprintf(str_buf, "* MainClock: %u Hz       *\r\n", MainClock);
	print_out(str_buf);
	sprintf(str_buf, "* IRQ latency register: 0x%X   *\r\n", 
		LPC_SYSCON->IRQLATENCY);
	print_out(str_buf);
	print_out("* Scheduler: FP                *\r\n");
	print_out("* Stack handling:MULTI_STACK   *\r\n");
	print_out("********************************\r\n");
#endif //USE_PRINT_OUT

}

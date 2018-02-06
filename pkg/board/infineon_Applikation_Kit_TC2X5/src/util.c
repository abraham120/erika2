/*
 * util.c
 *
 *  Created on: Feb 3, 2014
 *      Author: Fusseneg
 */
#include "../inc/util.h"

void delay_us(unsigned long time)
{
	volatile long test;
	unsigned long i;
	test = 0;
	for (i = 0; i < time; i += 1)
	{
		test += 1;
	}
}

void delay_ms(unsigned long time)
{
	while (time--)
	{
		delay_us(1000);
	}
}

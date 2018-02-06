#include "ee.h"
#include "console_serial.h"


const EE_UINT8 char_array[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D',
						'E','F'};

/*
 * This function prints on the console the hexadecimal value of to_print
 */
void PrintChar(EE_UINT8 to_print)
{
    console_write(0, (EE_UINT8*) &char_array[(to_print & 0xF0)>>4], 1);
    console_write(0, (EE_UINT8*) &char_array[to_print & 0x0F], 1);
}


/*
 * This function prints on the console the value of to_print in decimal form
 */
void PrintDec(EE_UINT8 to_print)
{
	console_write(0, (EE_UINT8*) &char_array[to_print/10], 1);
	console_write(0, (EE_UINT8*) &char_array[to_print%10], 1);
}

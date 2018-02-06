
/* Header file. */
#include "array_update.h"

int array_update_change(unsigned char* array, unsigned int len_array, unsigned int pos,
                         unsigned char* update, unsigned int len_update)
{
	if (pos > len_array){
		return -1;
	}
	memcpy((array + pos), update, len_update);
}

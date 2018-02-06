#ifndef __NETBUFF_H__
#define __NETBUFF_H__

#include "ee.h"

typedef struct netbuff{
	EE_UINT8 *b;
	EE_UINT8 **pb;
	EE_UINT8 *free;
	EE_UINT8 nbuffs;
} NETBUFF;

void netbuff_init(struct netbuff *netb, EE_UINT8 nbuffs, EE_UINT16 buffdim);
void *netbuff_get(struct netbuff *netb, EE_UINT8 to);
void *netbuff_sequentialget(struct netbuff *netb, EE_UINT8 to);
void netbuff_release(struct netbuff *netb, void *m);


#endif

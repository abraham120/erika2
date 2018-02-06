#ifndef QUEUE_H_
#define QUEUE_H_

#include "ee.h"
#include "hal/hal_defines.h"
#include "frame_format.h"

#define ARR_SIZE 15
typedef struct 
{
	MPDU arr[ARR_SIZE];
	EE_INT8 rear,front;
}c_queue;

void initq(c_queue *p);

EE_BIT isempty(c_queue *p);

MPDU * insertq(c_queue *p);

MPDU * removeq(c_queue *p);

MPDU* getq(c_queue *p);

void insert_mac_payload_8(c_queue *p, EE_UINT8 pos, EE_UINT8 val);

void insert_mac_payload_16(c_queue *p, EE_UINT8 pos, EE_UINT16 val);

void insert_mac_payload_32(c_queue *p, EE_UINT8 pos, EE_UINT32 val);

#endif /*QUEUE_H_*/

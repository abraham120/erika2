#include "common/queue.h"

#include "common/console.h"


void initq(c_queue *p){
	
	p->front = -1;
	p->rear = -1;
	
}

EE_BIT isempty(c_queue *p)
{
	if(p->front == p->rear)
		return 1;
	else
		return 0;
}

MPDU * insertq(c_queue *p)
{
	EE_UINT8 t;
	t = (p->rear+1)%ARR_SIZE;
	if(t == p->front)
	{
		//printf("\nQueue Overflow\n");
		//ee_console_out_str("BO\n");
		
		return 0;
	}
	else
	{
		p->rear=t;
		//p->arr[p->rear]=v;
		return &(p->arr[p->rear]);
	}
}

MPDU* getq(c_queue *p)
{
	if(isempty(p))
	{
		//printf("\nQueue Underflow");
		//exit(0);
		return 0;
	}
	else
	{
		//p->front=(p->front + 1)%ARR_SIZE;
		return(&(p->arr[(p->front + 1 )%ARR_SIZE]));
	}
}


MPDU* removeq(c_queue *p)
{
	EE_UINT8 t;
	if(isempty(p))
	{
		//printf("\nQueue Underflow");
		//exit(0);
		return 0;
	}
	else
	{
		//t = p->front;
		p->front=(p->front + 1)%ARR_SIZE;
		return(&(p->arr[p->front]));
	}
}


void insert_mac_payload_8(c_queue *p, EE_UINT8 pos, EE_UINT8 val){
	MPDU* temp = getq(p);
	
	temp->data[pos] =  val;

return;

}

void insert_mac_payload_16(c_queue *p, EE_UINT8 pos, EE_UINT16 val){
	MPDU* temp = getq(p);
	temp->data[pos] =  (EE_UINT8)(val >> 8);
	temp->data[pos+1] =  (EE_UINT8)(val & 0x00FF);
}

void insert_mac_payload_32(c_queue *p, EE_UINT8 pos, EE_UINT32 val){
	MPDU* temp = getq(p);
	temp->data[pos] =  (EE_UINT8)(val >> 24);
	temp->data[pos+1] =  (EE_UINT8)(val >> 16);
	temp->data[pos+2] =  (EE_UINT8)(val >> 8);
	temp->data[pos+3] =  (EE_UINT8)(val & 0x000000FF);
}

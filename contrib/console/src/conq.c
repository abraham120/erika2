#include "conq.h"

void conq_init(conq_t *q)
{
	q->nFirstElement = 0;
	q->nLastElement = CONQ_DIMENSION-1;
	q->nElementNumber = 0;
}

void conq_flush (conq_t *q)
{
	q->nFirstElement = 0;
	q->nLastElement = CONQ_DIMENSION-1;
	q->nElementNumber = 0;
}

char conq_insert(conq_t *q, char x)
{
	if (q->nElementNumber >= CONQ_DIMENSION)
		/* Warning: queue overflow enqueue */
#ifdef	__CORTEX_MX__
		return (char)-1;
#else
		return -1;
#endif
	else {
		q->nLastElement = (q->nLastElement+1) % CONQ_DIMENSION;
		q->storage[ q->nLastElement ] = x;    
		q->nElementNumber = q->nElementNumber + 1;
	}
	
	return 0;
}

char conq_extract(conq_t *q)
{
	char x;

	if (q->nElementNumber <= 0)
		/* Warning: empty queue dequeue */
#ifdef	__CORTEX_MX__
		return (char)-1;
#else
		return -1;
#endif
	else {
		x = q->storage[ q->nFirstElement ];
		q->nFirstElement = (q->nFirstElement+1) % CONQ_DIMENSION;
		q->nElementNumber = q->nElementNumber - 1;
	}

	return(x);
}

int conq_isempty(conq_t *q)
{
	if (q->nElementNumber <= 0){
		return 1; /* TRUE */
	} else {
		return 0; /* FLSE */
	}
}

/*void conq_print(conq_t *q)
{
	int i;

	i=q->nFirstElement; 
    
	printf("Queue content:\n");
	while (i != q->nLastElement) {
		printf("%c ",q->q[i]);
		i = (i+1) % CONQ_DIMENSION;
	}
	printf("%c ",q->q[i]);
	printf("\n");
}*/

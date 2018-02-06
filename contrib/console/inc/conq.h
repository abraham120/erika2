#ifndef _CONQ_H_
#define _CONQ_H_

#ifndef CONQ_DIMENSION
#define CONQ_DIMENSION		16
#endif

typedef struct {
	/* Queue Itself */
	char		storage[CONQ_DIMENSION+1];
	/* The position of the first element */
	int		nFirstElement;
	/* The position of the last element */
	int		nLastElement;
	/* Number of the elements inside the queue */
	unsigned int	nElementNumber;
} conq_t;

void	conq_init	(conq_t *q);		/* Queue Initialization */
void	conq_flush	(conq_t *q);		/* Clean Queue Initialization */
char	conq_insert	(conq_t *q, char x);	/* Allow enqueuing op */
char	conq_extract	(conq_t *q);		/* Allow dequeuing op */
/* Retur TRUE if the Queue is empty, FALSE otherwise */
int	conq_isempty	(conq_t *q);
#if	0
/* Print the entire Queue Content */
void	conq_print	(conq_t *q);
#endif	/* 0 */

#endif


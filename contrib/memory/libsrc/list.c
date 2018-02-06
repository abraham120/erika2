/** 
* @file list.c
* @brief Generic linked list implementation.
* @author Christian Nastasi
* @date 2009-03-18
*/

#include <list.h>


/******************************************************************************/
/*                        PRIVATE internal FUNCTIONS                          */
/******************************************************************************/
/* TODO: do something better than this! O(n) */
COMPILER_INLINE uint16_t get_free_index(list_t *l)
{
	uint16_t i; 
	/* TODO: won't work when LEN >= 0xFFFE, return 0 with no space! */
	
	for (i = 0; i < l->length; i++) 
		if (l->next[i] == L_FREE)
			break;
	return i;
}


/******************************************************************************/
/*                           COMMON BASIC FUNCTIONS                           */
/******************************************************************************/
void *list_last(list_t *l) 
{
	uint16_t i;

	if (l->head == L_EOL)
		return 0;
	for (i = l->head; l->next[i] != L_EOL; i = l->next[i]) ;
	return (void *) (l->data + (i * l->data_size));
}

#define logger(l) 

#define logger_extr(l) 

/*
char str[1000];
#define logger(l) \
{\
\
	sprintf(str, \
		"*_*_* List INSERT @ %u\n: "\
		"                   cnt=%u head=%u"\
		" next[%u %u %u %u %u %u %u %u %u"\
		" %u %u %u %u %u %u %u %u %u %u %u ]", \
		__LINE__, l->count, l->head,\
		l->next[0], l->next[1], l->next[2], l->next[3], \
		l->next[4], l->next[5],\
		l->next[6], l->next[7], l->next[8], l->next[9], l->next[10],\
		l->next[11], l->next[12], l->next[13], l->next[14], \
		l->next[15], l->next[16], l->next[17], l->next[18], \
		l->next[19]);\
	uwl_debug_print(str);\
}

#define logger_extr(l) \
{\
\
	sprintf(str, \
		"*_*_* List EXTRACT @ %u\n: "\
		"                   cnt=%u head=%u"\
		" next[%u %u %u %u %u %u %u %u %u"\
		" %u %u %u %u %u %u %u %u %u %u %u ]", \
		__LINE__, l->count, l->head,\
		l->next[0], l->next[1], l->next[2], l->next[3], \
		l->next[4], l->next[5],\
		l->next[6], l->next[7], l->next[8], l->next[9], l->next[10],\
		l->next[11], l->next[12], l->next[13], l->next[14], \
		l->next[15], l->next[16], l->next[17], l->next[18], \
		l->next[19]);\
	uwl_debug_print(str);\
}
*/

void *list_push_front(list_t *l)
{
	uint16_t i;

	if (l->count == l->length) 
		return 0;
	if (l->head == L_EOL) {
		l->head = 0;
		l->next[0] = L_EOL;
		l->count++;
logger(l);
		return (void *) l->data;
	}
	i = get_free_index(l);
	l->next[i] = l->head;
	l->head = i;
	l->count++;
logger(l);
	return (void *) (l->data + (i * l->data_size));
}

void *list_push_back(list_t *l)
{
	uint16_t i;
	
	if (l->count == l->length) 
		return 0;
	if (l->head == L_EOL) {
		l->head = 0;
		l->next[0] = L_EOL;
		l->count++;
logger(l);
		return (void *) l->data;
	}
	for (i = l->head; l->next[i] != L_EOL; i = l->next[i]) ;
	l->next[i] = get_free_index(l);
	i = l->next[i];
	l->next[i] = L_EOL;
	l->count++;
logger(l);
	return (void *) (l->data + (i * l->data_size));
}

void *list_insert(list_t *l, uint16_t p)
{
	uint16_t i;

	if (p == 0)
		return list_push_front(l);
	if (p == l->count)
		return list_push_back(l);
	if (l->count == l->length || p > l->count) 
		return 0;
	for (i = l->head; p-- > 1; i = l->next[i]) ;
	p = get_free_index(l); 	/* p = new, prev(p) = i, next(p) = next(i) */
	l->next[p] = l->next[i];/* p->next(i) */
	l->next[i] = p;		/* i->p */
	l->count++;
logger(l);
	return (void *) (l->data + (p * l->data_size));
}

void *list_at(list_t *l, uint16_t p)
{
	uint16_t i;

	if (l->head == L_EOL || p >= l->count) 
		return 0;
	for (i = l->head; p-- != 0; i = l->next[i]) ;
	return (void *) (l->data + (i * l->data_size));
}

void *list_pop_front(list_t *l)
{
	uint16_t old_head = l->head;

	if (l->count == 0) 
		return 0;
	l->count--;
	l->head = l->next[old_head];
	l->next[old_head] = L_FREE;
logger_extr(l);
	return (void *) (l->data + (old_head * l->data_size));
}

void *list_pop_back(list_t *l)
{
	uint16_t i, prev_i;

	if (l->count == 0) 
		return 0;
	l->count--;
	prev_i = l->head;
	for (i = l->head; l->next[i] != L_EOL; i = l->next[i]) 
		prev_i = i;
	l->next[i] = L_FREE;
	l->next[prev_i] = L_EOL;
logger_extr(l);
	return (void *) (l->data + (i * l->data_size));
}

void *list_extract(list_t *l, uint16_t p)
{
	uint16_t i;

	if (p == 0)
		return list_pop_front(l);
	if (l->count == 0 || p >= l->count) 
		return 0;
	if (p == l->count - 1)
		return list_pop_back(l);
	for (i = l->head; p-- > 1; i = l->next[i]) ;
	p = l->next[i];		/* p = to_extract, i = prev(p), n = next(p) */
	l->next[i] = l->next[p];/* i->n */
	l->next[p] = L_FREE;	/* p = free */
	l->count--;
logger_extr(l);
	return (void *) (l->data + (p * l->data_size));
}

/******************************************************************************/
/*                             ITERATOR FUNCTIONS                             */
/******************************************************************************/
void *list_iter_at(list_t *l, uint16_t p)
{
	uint16_t i;

	if (l->head == L_EOL || p > l->count) 
		return 0;
	for (i = l->head; p-- != 0; i = l->next[i]) ;
	l->iterator = i;
	return (void *) (l->data + (i * l->data_size));
}

void *list_iter_front(list_t *l)
{
	if (l->head == L_EOL) 
		return 0;
	l->iterator = l->head;
	return (void *) (l->data + (l->iterator * l->data_size));
}

void *list_iter_next(list_t *l)
{
	l->iterator = l->next[l->iterator];
	if (l->iterator == L_EOL)
		return 0;
	return (void *) (l->data + (l->iterator * l->data_size));
}

void *list_iter_current(list_t *l)
{
	if (l->iterator == L_EOL)
		return 0;
	return (void *) (l->data + (l->iterator * l->data_size));
}

void *list_iter_extract(list_t *l)
{
	/* TODO */
	//l->count--;
	return 0;
}




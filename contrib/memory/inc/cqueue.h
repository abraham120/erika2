/** 
* @file cqueue.h
* @brief Generic circular queue implementation
* @author Christian Nastasi
* @date 2009-03-18
*/
#ifndef __cqueue_h__
#define __cqueue_h__

#include <arch/mem_compiler.h>

/** 
* @brief Circular Queue Type
*
* The implementation of the circular queue make use of the 
* <it>fill counter</it>  mechanism to solve the Full/Empty condition and 
* particualry the case with one index and a fill counter 
* (no additional variable required).
*/
typedef struct cqueue_t {
	uint16_t front;		/**< Pointer to the head of the queue.*/
	uint16_t count;		/**< Number of element in the queue. */
	uint16_t length;	/**< The length of the circular queue. */
	uint16_t data_size;	/**< The size of a queue element. */
	uint8_t *data;		/**< Pointer to the storage for the elements. */
} cqueue_t;


/** 
* @brief Static circular queue allocation
*
* Allow to create a circular queue in a static way, allocating the storage
* as an array in the global section or in the local context of a function.
* This macro also creates a \ref cqueue_t that can be used by the \c cqueue
* functions. 
* \see cqueue_clear 
* \see cqueue_is_empty
* \see cqueue_is_full 
* \see cqueue_get_size
* \see cqueue_get_length
* \see cqueue_get_datasize
* \see cqueue_first
* \see cqueue_last
* \see cqueue_push
* \see cqueue_pop
* 
* @param[out] name 	The name given to the \ref cqueue_t created.  
* @param[in] type 	The data type of the queue elements.
* @param[in] length 	The length of the queue, max number of elements.
* @param[in] attribute 	A valid compiler attribute for the data storage.
*/
#define CQUEUE_DEFINE(name, type, length, attribute)	\
static type cqueue_data_##name[length] attribute;	\
cqueue_t name = {					\
	0, 						\
	0, 						\
	length, 					\
	sizeof(type), 					\
	(uint8_t *) cqueue_data_##name			\
}; 							\

/** 
* @brief Static circular queue allocation
*
* Same to \ref CQUEUE_DEFINE, but in this case the keyword 
* \c static is used in front of \c name. 
* 
* \todo If used within a function this declare two persistent variable due to
* the bahaviour of the \c static keyword in functions. 
* 
* @param[out] name 	The name given to the \ref cqueue_t created.  
* @param[in] type 	The data type of the queue elements.
* @param[in] length 	The length of the queue, max number of elements.
* @param[in] attribute 	A valid compiler attribute for the data storage.
*/
#define CQUEUE_DEFINE_STATIC(name, type, length, attribute)	\
static type cqueue_data_##name[length] attribute;		\
static cqueue_t name = {					\
	0, 							\
	0, 							\
	length, 						\
	sizeof(type), 						\
	(uint8_t *) cqueue_data_##name				\
}; 								\

#define CQUEUE_DEFINE_EXTMEM(name, type, length, storage)	\
cqueue_t name = {						\
	0, 							\
	0, 							\
	length, 						\
	sizeof(type), 						\
	(uint8_t *) (storage)					\
}; 								\

#define CQUEUE_DEFINE_EXTMEM_STATIC(name, type, length, storage) 	\
static cqueue_t name = {						\
	0, 								\
	0, 								\
	length, 							\
	sizeof(type), 							\
	(uint8_t *) (storage)						\
}; 									\

/** 
* @brief Clear the circular queue
*
* Reset the queue indexes.
* 
* @param[in] q The circular queue
*/
COMPILER_INLINE void cqueue_clear(cqueue_t *q) 
{
	q->front = 0;
	q->count = 0;
}

/** 
* @brief Empty space check 
* 
* @param[in] q The circular queue
* 
* @return Returns 1 if queue is empty, otherwise 0
*/
COMPILER_INLINE int8_t cqueue_is_empty(cqueue_t *q)
{
	return (q->count == 0);
}

/** 
* @brief Full space check 
* 
* @param[in] q The circular queue
* 
* @return Returns 1 if queue is full, otherwise 0
*/
COMPILER_INLINE int8_t cqueue_is_full(cqueue_t *q)
{
	return (q->count == q->length);
}

/** 
* @brief Elements in queue
* 
* @param[in] q The circular queue
* 
* @return Returns the number of elements in the queue.
*/
COMPILER_INLINE uint16_t cqueue_get_size(cqueue_t *q) 
{
	return q->count;
}

/** 
* @brief Length of the queue
* 
* @param[in] q The circular queue
* 
* @return Returns the maximum number of elements available in the queue.
*/
COMPILER_INLINE uint16_t cqueue_get_length(cqueue_t *q)
{
	return q->length;
}

/** 
* @brief Element size
* 
* @param[in] q The circular queue
* 
* @return Returns the size of a queue element. 
*/
COMPILER_INLINE uint16_t cqueue_get_datasize(cqueue_t *q) 
{
	return q->data_size;
}

/** 
* @brief Get first element
*
* Get the reference to first element of the queue without removing.
* 
* @param[in] q 	The circular queue.
* 
* @return A pointer to the element or 0 if the queue is empty.
*/
COMPILER_INLINE void *cqueue_first(cqueue_t *q) 
{
	if (q->count == 0)
		return 0;
	return (void *) (q->data + (q->front * q->data_size));
}


/** 
* @brief Get last element
* 
* Gget the reference to the last element of the queue without removing.
* 
* @param[in] q 	The circular queue.
* 
* @return A pointer to the element or 0 if the queue is empty.
*/
COMPILER_INLINE void *cqueue_last(cqueue_t *q) 
{
	if (q->count == 0)
		return 0;
	return (void *) (q->data + 
	       (((q->front + q->count - 1) % q->length) * q->data_size));
}

/** 
* @brief Push in the queue
* 
* Insert an element in the circular queue if this is not full.
* The function attempt to return a reference to a free element in the queue
* in which the data has to be stored.
* 
* @param[in] q 	The circular queue.
* 
* @return A pointer to the element or 0 if the queue is full.
*/
COMPILER_INLINE void *cqueue_push(cqueue_t *q)
{
	if (q->count == q->length)
		return 0;
	return (void *) (q->data + 
	       (((q->front + (q->count)++) % q->length) * q->data_size));
}


/** 
* @brief Pop from the queue
* 
* Extract an element from the circular queue if this is not empty.
* The function attempt to return a reference to the extracted element of queue,
* in which the data are to be stored, logically removing it from the queue.
* 
* @param[in] q 	The circular queue.
* 
* @return A pointer to the element or 0 if the queue is empty.
*/
COMPILER_INLINE void *cqueue_pop(cqueue_t *q)
{
	void *p;

	if (q->count == 0)
		return 0;
	p = (void *) (q->data + (q->front * q->data_size));
	q->front = (q->front + 1) % q->length;
	q->count -= 1;
	return p;
}

/** 
* @brief Get an element at position 
* 
* Get the reference to the element of the queue at position p without removing.
* 
* @param[in] q The circular queue.
* @param[in] p The index (from 0 to N-1).
* 
* @return A pointer to the element or 0 if the queue is empty. 
*/
COMPILER_INLINE void *cqueue_at(cqueue_t *q, uint16_t p) 
{
	if (q->count == 0 || p >= q->count)
		return 0;
	return (void *) (q->data + 
	       (((q->front + p) % q->length) * q->data_size));
}

#endif /* Header Protection */

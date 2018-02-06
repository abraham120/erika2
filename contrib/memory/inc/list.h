/** 
* @file list.h
* @brief Generic linked list implementation
* @author Christian Nastasi
* @date 2009-03-18
*/
#ifndef __list_h__
#define __list_h__

#include <arch/mem_compiler.h>
#ifdef __STDIO_COMPILER_BUG__
#include <stddef.h>
void	*memcpy	(void *, const void *, size_t);
void	*memset	(void *, int , size_t);
#else
#include <string.h>
#endif

#ifdef L_EOL
#undef L_EOL
#endif
#define L_EOL 0xFFFE

#ifdef L_FREE
#undef L_FREE
#endif
#define L_FREE 0xFFFF


/** 
* @brief Linked List
*
* The implementation of the linked list 
*/
typedef struct list_t {
	uint16_t head;		/**< Pointer to the head of the list.*/
	uint16_t count;		/**< Number of element in the list. */
	uint16_t length;	/**< The length of the list. */
	uint16_t iterator;	/**< Used to perform iteration on list. */
	uint16_t data_size;	/**< The size of a list element. */
	uint8_t *data;		/**< Pointer to the array of elements. */
	uint16_t *next;		/**< Pointer to the array of next indexes. */
} list_t;

/** 
* @brief Static list allocation
*
* Allow to create a list in a static way, allocating the storage either
* as an array in the global section or in the local context of a function.
* This macro also creates a \ref list_t that can be used by the \c list
* functions. 
* \see list_clear 
* \see list_is_empty
* \see list_is_full 
* \see list_get_size
* \see list_get_length
* \see list_get_datasize
* \see list_first
* \see list_last
* \see list_insert
* \see list_push_front
* \see list_push_back
* \see list_remove
* 
* @param[out] name 	The name given to the \ref list_t created.  
* @param[in] type 	The data type of the list elements.
* @param[in] length 	The length of the list, max number of elements.
* @param[in] attribute 	A valid compiler attribute for the data storage.
*/
#define LIST_DEFINE(name, type, length, attribute)	\
static type list_data_##name[length] attribute;		\
static uint16_t list_next_indexes_##name[length];	\
list_t name = {						\
	L_EOL, 						\
	0, 						\
	length, 					\
	0, 						\
	sizeof(type), 					\
	(uint8_t *) list_data_##name,			\
	list_next_indexes_##name			\
}; 							\

/** 
* @brief Static list allocation
*
* Same to \ref LIST_DEFINE, but in this case the keyword 
* \c static is used in front of \c name. 
* 
* \todo If used within a function this declare two persistent variable due to
* the bahaviour of the \c static keyword in functions. 
* 
* @param[out] name 	The name given to the \ref list_t created.  
* @param[in] type 	The data type of the list elements.
* @param[in] length 	The length of the list, max number of elements.
* @param[in] attribute 	A valid compiler attribute for the data storage.
*/
#define LIST_DEFINE_STATIC(name, type, length, attribute)	\
static type list_data_##name[length] attribute;			\
static uint16_t list_next_indexes_##name[length];		\
static list_t name = {						\
	L_EOL, 							\
	0, 							\
	length, 						\
	0, 							\
	sizeof(type), 						\
	(uint8_t *) list_data_##name,				\
	list_next_indexes_##name				\
}; 								\

#define LIST_DEFINE_EXTMEM(name, type, length, storage)	\
static uint16_t list_next_indexes_##name[length];	\
list_t name = {						\
	L_EOL, 						\
	0, 						\
	length, 					\
	0, 						\
	sizeof(type), 					\
	(uint8_t *) (storage),				\
	list_next_indexes_##name			\
}; 							\

#define LIST_DEFINE_EXTMEM_STATIC(name, type, length, storage)	\
static uint16_t list_next_indexes_##name[length];		\
static list_t name = {						\
	L_EOL, 							\
	0, 							\
	length, 						\
	0, 							\
	sizeof(type), 						\
	(uint8_t *) (storage),					\
	list_next_indexes_##name				\
}; 								\

/** 
* @name Error Codes
* @{ */
#define LIST_EMPTY 	1	/**< Empty list. */
#define LIST_FULL 	2	/**< Full list. */
/**  @} */


/** 
* @brief Clear the list
*
* Reset the list indexes.
* 
* @param[in] l The list.
*/
COMPILER_INLINE void list_clear(list_t *l) 
{
	l->count = 0;
	l->head = L_EOL;
	l->iterator = L_EOL;
	memset(l->next, L_FREE, l->length * sizeof(uint16_t));
}

/** 
* @brief Empty space check 
* 
* @param[in] l The list
* 
* @return Returns 1 if list is empty, otherwise 0
*/
COMPILER_INLINE int8_t list_is_empty(list_t *l)
{
	return (l->count == 0);
}

/** 
* @brief Full space check 
* 
* @param[in] l The list
* 
* @return Returns 1 if list is full, otherwise 0
*/
COMPILER_INLINE int8_t list_is_full(list_t *l)
{
	return (l->count == l->length);
}

/** 
* @brief Elements in list
* 
* @param[in] l The list
* 
* @return Returns the number of elements in the list.
*/
COMPILER_INLINE uint16_t list_get_size(list_t *l) 
{
	return l->count;
}

/** 
* @brief Length of the list
* 
* @param[in] l The list
* 
* @return Returns the maximum number of elements available in the list.
*/
COMPILER_INLINE uint16_t list_get_length(list_t *l)
{
	return l->length;
}

/** 
* @brief Element size
* 
* @param[in] l The list
* 
* @return Returns the size of a list element. 
*/
COMPILER_INLINE uint16_t list_get_datasize(list_t *l) 
{
	return l->data_size;
}

/** 
* @brief Get first element
*
* Get the reference to first element of the list without removing.
* 
* @param[in] l 	The list.
* 
* @return A pointer to the element or 0 if the list is empty.
*/
COMPILER_INLINE void *list_first(list_t *l) 
{
	if (l->count == 0)
		return 0;
	return (void *) (l->data + (l->head * l->data_size));
}

/** 
* @brief Get element at position
*
* Get the reference to the element of the list at the given position 
* without removing.
* 
* @param[in] l 	The list.
* @param[in] p 	Desired position of the element.
* 
* @return A pointer to the element or 0 if the list is empty.
*/
void *list_at(list_t *l, uint16_t p);

/** 
* @brief Get last element
* 
* Gget the reference to the last element of the list without removing.
* 
* @param[in] l 	The list.
* 
* @return A pointer to the element or 0 if the list is empty.
*/
void *list_last(list_t *l);

/** 
* @brief Insertion in the list
* 
* Insert an element in the list, if this is not full, in the 
* specified position.
* The function attempt to return a reference to a free element in the list
* in which the data has to be stored.
* 
* @param[in] l 	The list.
* @param[in] p 	Desired position for the element.
* 
* @return A pointer to the element; 0 if the list is either full or the there
*	  is no element at that position.
*/
void *list_insert(list_t *l, uint16_t p);

/** 
* @brief Head insertion in the list
* 
* Same as \ref list_insert, but attempt to insert in the head position.
* 
* @param[in] l 	The list.
* 
* @return A pointer to the element or 0 if the list is full.
*/
void *list_push_front(list_t *l);

/** 
* @brief Appending to the list
* 
* Same as \ref list_insert, but attempt to append at the end of the list.
* 
* @param[in] l 	The list.
* 
* @return A pointer to the element or 0 if the list is full.
*/
void *list_push_back(list_t *l);

/** 
* @brief Insertion (after) in the list
* 
* Insert an element in the list, if this is not full, after the 
* specified position.
* The function attempt to return a reference to a free element in the list
* in which the data has to be stored.
* 
* @param[in] l 	The list.
* @param[in] p 	Position before the new element.
* 
* @return A pointer to the element; 0 if the list is either full or the there
*	  is no element at that position.
*/
COMPILER_INLINE void *list_insert_after(list_t *l, uint16_t p)
{
	if (p < l->count)
		p++;
	return list_insert(l, p);
}

/** 
* @brief Extract from the list
* 
* Extract (remove) an element from the list, if this is not empty, from the 
* specified position.
* The function attempt to return a reference to the extracted element of 
* the list in which the data are stored, removing it from the list.
* 
* @param[in] l 	The list.
* @param[in] p 	Position of the element to remove.
* 
* @return A pointer to the element or 0 if the list is empty.
*/
void *list_extract(list_t *l, uint16_t p);

/** 
* @brief Head extraction from the list
* 
* Extract (remove) the list head, if this is not empty.
* The function attempt to return a reference to the extracted element 
* in which the data are stored, removing it from the list.
* 
* @param[in] l 	The list.
* 
* @return A pointer to the element or 0 if the list is empty.
*/
void *list_pop_front(list_t *l);

/** 
* @brief End extraction from the list
* 
* Extract (remove) the last element from the list, if this is not empty.
* The function attempt to return a reference to the extracted element 
* in which the data are stored, removing it from the list.
* 
* @param[in] l 	The list.
* 
* @return A pointer to the element or 0 if the list is empty.
*/
void *list_pop_back(list_t *l);

/** 
* @brief Set iterator to head
* 
* \todo Write more
* 
* @param[in] l The list.
* 
* @return  A pointer to the head element or 0 if the list is empty.
*/
void *list_iter_front(list_t *l);

/** 
* @brief Set iterator to position
* 
* \todo Write more
* 
* @param[in] l The list.
* @param[in] p Position of the desidered element.
* 
* @return  A pointer to the pointed element or 0 if the list is empty.
*/
void *list_iter_at(list_t *l, uint16_t p);

/** 
* @brief Forward iteration
*
* Perform a forward iteration, go to the next element, 
* and attempt to get the reference to this node.
* 
* @param[in] l The list.
* 
* @return  A pointer to the element or 0 if the end of the list is reached.
*/
void *list_iter_next(list_t *l);

/** 
* @brief Get current iterator position
*
* Attempt to return a reference to the element pointer by the current iterator.
* 
* @param[in] l The list.
* 
* @return  A pointer to the element or 0 if the iterator was not valid.
*/
void *list_iter_current(list_t *l);

#endif /* Header Protection */

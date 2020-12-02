#ifndef PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUEHEAP_H
#include <stdint.h>

/**
 * @typedef priorityQueueHeap
 * @brief   Opaque heap structure.
 * 
 */
typedef struct priorityQueueHeap priorityQueueHeap;



/**
 * @typedef priorityQueueHeap_t
 * @brief   priority queue heap abstract data type interface.
 * 
 */
typedef priorityQueueHeap* priorityQueueHeap_t;

/**
 * @brief   Creates priority Queue heap container.
 * 
 * @param   buffer
 *  Storage array for the elements to be stored, must be created independently
 * @param   size
 *  Size of the array
 * @returns
 *  A priority queue heap handler
 */
priorityQueueHeap_t priorityQueueHeap_init(void* array, uint8_t size);



#endif
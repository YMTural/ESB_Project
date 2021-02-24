#ifndef PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUEHEAP_H
#include "bootcamp/debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bootcamp/task.h"
#if(DEBUG == 0)
#include <avr/interrupt.h>
#endif
#if(DEBUG == 1)
#include "bootcamp/interrupt.h"
#endif
/**
 * @typedef priorityQueueHeap
 * @brief   Opaque heap structure.
 * 
 */
typedef struct priorityQueueHeap priorityQueueHeap;


/**
 * @typedef priorityQueueHeap_t
 * @brief  Priority Queue Heap abstract data type interface.
 * 
 */
typedef priorityQueueHeap* priorityQueueHeap_t;

/**
 * @brief   Creates priority Queue heap container including a queue.
 * 
 * @param   size
 *  Size of the Priority Queue
 * @returns
 *  A priority queue heap handler
 */
priorityQueueHeap_t priorityQueueHeap_init(uint8_t maxSize, task* array);

/**
 * @brief   Adds a new task to the priority queue. Returns -1 if queue full else 0
 * 
 * @param   priorityQueueHeap
 *  The queue container where is the task is to be added
 * 
 * @param   task
 *  Task which is to be added to the queue
 *  
 */
int8_t priorityQueueHeap_add(void* priorityQueueHeap, task task);

/**
 * @brief   Returns the next task from the priority queue   
 * 
 * @param   priorityQueueHeap
 *  The queue container where is the task is to be taken
 * @param   task
 *  The task which is to be added
 * @return
 *  A task
 * 
 */
task* priorityQueueHeap_getNext(priorityQueueHeap_t priorityQueueHeap);

/**
 * @brief   Returns the next ready task from the priority queue   
 * 
 * @param   priorityQueueHeap
 *  The queue container where is the task is to be taken
 * 
 * @return
 *  A task which is ready
 * 
 */
task* priorityQueueHeap_getNextReady(void* priorityQueueHeap);

/**
 * @brief   Restores heap structure if only 1 item is missplaced
 * 
 * @param   priorityQueueHeap
 *  The queue container where is the heap structure is to be restored
 * @param   startIndex
 *  Index of the item which is missplaced (minimum index)
 */
void priorityQueueHeap_heapify(priorityQueueHeap_t priorityQueueHeap, uint8_t startIndex);

/**
 * @brief   Swaps array elements
 * 
 * @param a
 *  Index of the first item to be swapped
 * @param b
 *  Index of the second item to be swapped
 * @param priorityQueueHeap
 *  The queue container where the swap is to be taken place
 */
void priorityQueueHeap_swap(uint8_t a, uint8_t b, priorityQueueHeap_t priorityQueueHeap);


/**
 * @brief   Peeks at the n'th element of the heap
 * 
 * @param priorityQueueHeap
 *  The queue container which will be peeked at
 * @param
 *  The index which will be peeked at
 * @return
 *  The n'th task in the queue starting from 0
 */

task* priorityQueueHeap_peekAt(void* priorityQueueHeap,uint8_t n);

/**
 *  @brief Returns the current number of task in the priority queue
 * 
 *  @param
 *   The queue container whose size is to be determined
 *  @param
 *   The place of the task in the heap
 *  @return
 *   Pointer to the n'th task
 */ 

uint8_t priorityQueueHeap_size(void* priorityQueueHeap);

/**
 *  @brief Returns the capacity of the priority queue
 * 
 *  @param
 *   The queue container whose capacity is to be determined
 *  @return
 *   The capacity of the queue
 */ 
uint8_t priorityQueueHeap_capacity(void* priorityQueueHeap);

/**
 *  @brief Frees the memory allocated for the priority queue and the container
 * 
 *  @param
 *   The queue container whose memory is to be freed
 */ 
void priorityQueueHeap_free(priorityQueueHeap_t priorityQueueHeap);

/**
 *  @brief NOT FINISHED! -- Increments the priority of non periodic tasks to avoid starvation
 * 
 *  @param
 *   The queue container whose non periodic tasks are to be incremented
 * 
 */ 
//void priorityQueueHeap_incrementPriorityOfNonPeriodic(priorityQueueHeap_t priorityQueueHeap);

/**
 * @brief Deletes the item in the n'th place of the heap
 * 
 * 
 * @param
 *  The queue container
 * @param
 *  The place of the item to be deleted
 * 
 */ 


void priorityQueueHeap_deleteItem(void* priorityQueueHeap, uint8_t n);


#endif
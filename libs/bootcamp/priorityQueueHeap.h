#ifndef PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUEHEAP_H
#include "bootcamp/debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bootcamp/task.h"
/**
 * @typedef priorityQueueHeap
 * @brief   Opaque heap structure.
 * 
 */
typedef struct priorityQueueHeap priorityQueueHeap;


/**
 * @typedef TimeBasedScheduler_t
 * @brief  TimeBasedScheduler abstract data type interface.
 * 
 */
typedef priorityQueueHeap* priorityQueueHeap_t;

/**
 * @brief   Creates priority Queue heap container.
 * 
 * @param   buffer
 *  Storage array for the elements to be stored
 * @param   size
 *  Size of the array
 * @returns
 *  A priority queue heap handler
 */
priorityQueueHeap_t priorityQueueHeap_init(uint8_t maxSize);

/**
 * @brief   Adds a new task to the priority queue. Returns Error if queue full
 * 
 * @param   task
 *  Task which is to be added to the queue
 *  
 * @param   array
 *  The queue where is the task is to be added
 */
int priorityQueueHeap_add(priorityQueueHeap_t priorityQueueHeap, task task);

/**
 * @brief   Returns the next task from the priority queue   
 * 
 * @return
 *  task
 * 
 */
task* priorityQueueHeap_getNext(priorityQueueHeap_t priorityQueueHeap);

/**
 * @brief   Returns the next ready task from the priority queue   
 * 
 * @return
 *  A task which is ready
 * 
 */
task* priorityQueueHeap_getNextReady(priorityQueueHeap_t priorityQueueHeap);

/**
 * @brief   Maintains max heap structure
 * 
 * 
 */
void priorityQueueHeap_heapify(priorityQueueHeap_t priorityQueueHeap, uint8_t startIndex);

/**
 * @brief   Swaps array elements
 * 
 * 
 */
void priorityQueueHeap_swap(uint8_t a, uint8_t b, priorityQueueHeap_t priorityQueueHeap);


task* priorityQueueHeap_peekAt(priorityQueueHeap_t queue,uint8_t n);

uint8_t priorityQueueHeap_size(priorityQueueHeap_t queue);

uint8_t priorityQueueHeap_capacity(priorityQueueHeap_t queue);

void priorityQueueHeap_free(priorityQueueHeap_t queue);

void priorityQueueHeap_incrementPriorityOfNonPeriodic(priorityQueueHeap_t priorityQueueHeap);

#endif
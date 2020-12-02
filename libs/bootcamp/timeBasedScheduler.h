#ifndef TIMEBASEDSCHEDULER_H
#define TIMEBASEDSCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
/**
 * @typedef timeBasedScheduler
 * @brief   Opaque time based scheduler structure.
 * 
 */
typedef struct timeBasedScheduler timeBasedScheduler;

/**
 * @typedef TimeBasedScheduler_t
 * @brief  TimeBasedScheduler abstract data type interface.
 * 
 */
typedef timeBasedScheduler* timeBasedScheduler_t;


/**
 * @typedef priorityQueueHeap
 * @brief   Opaque heap structure.
 * 
 */
typedef struct priorityQueueHeap priorityQueueHeap;

/**
 * @typedef priorityQueueHeap_t
 * @brief  priorityQueueHeap abstract data type interface.
 * 
 */
typedef priorityQueueHeap* priorityQueueHeap_t;

/**
 * @typedef e_periodicity
 * @brief Enumeration for periodicity of a task
 * 
 */
typedef enum
{
    PERIODIC,
    NONPERIODIC,
}e_periodicity;

/**
 * @typedef e_timer
 * @brief Enumeration to select the timer which shall be used
 * 
 */
typedef enum
{
    TIMER0,
    TIMER1,
    TIMER2,
}e_timer;

/**
 * @typedef task
 * @brief   Opaque task structure.
 * 
 */
typedef struct task task;


/**
 * @brief   Creates time based scheduler container.
 * 
 * @param   maxSize
 *  Maximum size of the task queue
 * 
 * @returns
 *  A time based scheduler handle
 */
timeBasedScheduler_t timeBasedScheduler_init(uint8_t maxSize);


/**
 * @brief   Adds a new task to the schedule
 * @param   function
 *  function which is to be executed
 * @param priority
 *  priority of the process
 * @param periodic
 *  sets the periodicity of a task
 * 
 */

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, bool periodic);

/**
 * @brief   Schedules all the tasks. Will run forever. Can return error code
 * @param
 *  time based Schedule which is to be scheduled
 */
uint8_t timeBasedScheduler_schedule(timeBasedScheduler tBScheduler);

/**
 * @brief   Configures the selected timer to given intervall
 * 
 * @param timer
 *  Has either to be 1,2 or 3
 * @param intervall
 *  Number of milliseconds 
 */
void timeBasedScheduler_timer(uint8_t timer, uint16_t intervall);
/**
 * @brief   Frees the memory for the time based scheduler
 * 
 */
void timeBasedScheduler_free(timeBasedScheduler_t tbScheduler);

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
static priorityQueueHeap priorityQueueHeap_init(uint8_t maxSize);

/**
 * @brief   Adds a new task to the priority queue. Returns Error if queue full
 * 
 * @param   task
 *  Task which is to be added to the queue
 *  
 * @param   array
 *  The queue where is the task is to be added
 */
static int priorityQueueHeap_add(priorityQueueHeap_t priorityQueueHeap, task task);

/**
 * @brief   Returns the next task from the priority queue   
 * 
 * @return
 *  task
 * 
 */
static task priorityQueueHeap_getNext(priorityQueueHeap_t priorityQueueHeap);


/**
 * @brief   Maintains max heap structure
 * 
 * 
 */
static void priorityQueueHeap_heapify(priorityQueueHeap_t priorityQueueHeap, uint8_t startIndex);

/**
 * @brief   Swaps array elements
 * 
 * 
 */
static void priorityQueueHeap_swap(uint8_t a, uint8_t b, priorityQueueHeap_t priorityQueueHeap);






#endif
#ifndef TIMEBASEDSCHEDULER_H
#define TIMEBASEDSCHEDULER_H
#ifndef DEBUG
#define DEBUG 0
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bootcamp/task.h"
#if(DEBUG == 0)
#include <avr/interrupt.h>
#endif
#if(DEBUG == 1)
#include "bootcamp/interrupt.h"
#endif
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

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority);

/**
 * @brief   Adds a new periodic task to the schedule
 * @param   function
 *  function which is to be executed
 * @param priority
 *  priority of the process
 * @param periodic
 *  sets the periodicity of a task
 * 
 */

bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t period, uint16_t startTime);

/**
 * @brief   Schedules all the tasks. Will run forever. Can return error code
 * @param
 *  time based Schedule which is to be scheduled
 */
void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler, uint16_t* currentTime);

/**
 * @brief   NOT FINISHED YET! ; Configures the selected timer to given intervall
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

void priorityQueueHeap_free(priorityQueueHeap_t queue);

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
void timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler, uint16_t currentTime);

#endif
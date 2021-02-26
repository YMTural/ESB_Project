#ifndef TIMEBASEDSCHEDULER_H
#define TIMEBASEDSCHEDULER_H
#include "bootcamp/debug.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bootcamp/task.h"
#include "bootcamp/arduinoArch.h"
#if(DEBUG == 0)
#include <avr/interrupt.h>
#endif
#if(DEBUG == 1)
#include "bootcamp/interrupt.h"
#endif




#if DEBUG == 1
typedef struct  timeBasedScheduler
{
    void* queue;
    bool overflow;
    //function pointer
    uint8_t (*queueSize)(void* queue);
    uint8_t (*queueCapacity)(void* queue);
    int8_t (*queueAdd)(void* queue, task thisTask);
    task* (*queuePeekAt)(void* queue, uint8_t n);
    task* (*queueGetNextReady)(void* queue);
    void (*queueDelete)(void* queue, uint8_t n);
    uint32_t availableIDs;
    uint16_t* currentTime;

} timeBasedScheduler;

#endif

#if DEBUG == 0
/**
 * @typedef timeBasedScheduler
 * @brief   Opaque time based scheduler structure.
 * 
 */
typedef struct timeBasedScheduler timeBasedScheduler;

#endif

/**
 * @typedef TimeBasedScheduler_t
 * @brief  TimeBasedScheduler abstract data type interface.
 * 
 */
typedef timeBasedScheduler* timeBasedScheduler_t;


/**
 * @brief   Creates time based scheduler container.
 * 
 * @param   currentTime
 *  Internal timer of the scheduler
 * 
 * @param   queue
 *  A queue for the tasks
 * 
 * @param   queueSize
 *  Pointer to a queue size function
 * 
 * @param   queueCapacity
 *  Pointer to a queue capacity function
 * 
 * @param   queueAdd
 *  Pointer to a enqueue function
 * 
 * @param   queuePeekAt
 *  Pointer to a peek function which returns a pointer to the peeked task
 *
 * @param   queueGetNextReady
 *  Pointer to a dequeue function
 * 
 * @param   queueDelete
 *  Pointer to a queue remove element function
 * @returns
 *  A time based scheduler handle
 */
timeBasedScheduler_t timeBasedScheduler_init(uint16_t* currentTime, void* queue,
    uint8_t (*queueSize)(void* queue),
    uint8_t (*queueCapacity)(void* queue),
    int8_t (*queueAdd)(void* queue, task thisTask),
    task* (*queuePeekAt)(void* queue, uint8_t n),
    task* (*queueGetNextReady)(void* queue),
    void (*queueDelete)(void* queue, uint8_t n) );


/**
 * @brief
 *  Adds a new task to the schedule
 * 
 * @param tBScheduler
 *  timeBasedScheduler handle
 * @param function
 *  Pointer to a function which is to be executed
 * @param priority
 *  priority of the process
 * @param start_time
 *  Time after which the task shall be executed
 * 
 */

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void (*function)(void), uint8_t priority, uint16_t start_time);

/**
 * @brief   Adds a new periodic task to the schedule
 * 
 * @param tBScheduler
 *  timeBasedScheduler handle
 * 
 * @param function
 *  Pointer to a function which is to be executed
 * @param priority
 *  priority of the process
 * @param period
 *  Sets the period of a task in milliseconds
 * @param startTime
 *  Time after which the task shall be executed the first time
 * @param overflow
 *  Determines if the task shall be executed in an odd timer iteration
 *  
 *  
 */
//Legacy Code
bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void (*function)(void), uint8_t priority, uint16_t period, uint16_t startTime, bool overflow);

/**
 * @brief   Schedules all the tasks and executes them.
 * 
 * @param
 *  time based Schedule which is to be scheduled
 */
void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler);

/**
 * @brief   NOT FINISHED YET! || 1MS ONLY ; Configures the selected timer to given intervall
 *          
 * @param timer
 *  Has either to be 1,2 or 3
 * @param intervall
 *  Number of milliseconds 
 */
void timeBasedScheduler_timer(uint8_t timer, uint16_t intervall);

/**
 * @brief   Frees the time based scheduler
 * 
 */
void timeBasedScheduler_free(timeBasedScheduler_t tbScheduler);


/**
 *  @brief Iterates over the queue marking a Task as ready if their start time has been reached and their overflow bit matched
 * 
 *  @param tBScheduler
 *   Scheduler container
 *   
 * 
 */

bool timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler);

/**
 *  @brief Increments the internal Timer and checks for overflow
 * 
 * @param tBScheduler
 *  Time based scheduler container
 * 
 * 
 */
void timeBasedScheduler_incrementTimer(timeBasedScheduler_t tBScheduler);

/**
 * @brief
 *  Adds a tasks with a paramter to the schedule.
 * @param tBScheduler
 *  timeBasedScheduler handle
 * 
 * @param function
 *  Pointer to a function which is to be executed
 * @param priority
 *  priority of the process
 * @param period
 *  Sets the period of a task in milliseconds
 * @param start_time
 *  Time after which the task shall be executed the first time
 * @param param
 *  Parameter of the function
 */

bool timeBasedScheduler_addTaskWithParam(timeBasedScheduler_t tBScheduler, void (*function)(char*), uint8_t priority, uint16_t start_time, char* param);

/**
 * @brief
 *  Finds the smallest available id of the Scheduler
 * @param tBScheduler
 * 
 * @return
 *  Returns an unique id 
 * 
 * 
 */ 

uint8_t timeBasedScheduler_findNextAvailableId(timeBasedScheduler_t tBScheduler);

/**
 * @brief
 *  Frees the given id in the scheduler, making it availabe again.
 * @param
 *  Id to be freed
 * 
 * 
 */ 

void timeBasedScheduler_freeID(timeBasedScheduler_t tBScheduler, uint8_t n);


/**
 * @brief
 *  Adds a periodic tasks with an id to the schedule.
 * @param tBScheduler
 *  timeBasedScheduler handle
 * 
 * @param function
 *  Pointer to a function which is to be executed
 * @param priority
 *  priority of the process
 * @param period
 *  Sets the period of a task in milliseconds
 * @param start_time
 *  Time after which the task shall be executed the first time
 * 
 * @param overflow
 *  Determines if the task shall be executed in an odd timer iteration
 * 
 * 
 * @param id
 *  A unique task id 
 */

bool timeBasedScheduler_addPeriodicTaskID(timeBasedScheduler_t tBScheduler, void (*function)(void), uint8_t priority, uint16_t period, uint16_t start_time, bool overflow, uint8_t id);


/**
 * @brief
 *  Adds a periodic tasks with a paramter to the schedule.
 * @param tBScheduler
 *  timeBasedScheduler handle
 * 
 * @param function
 *  Pointer to a function which is to be executed
 * @param priority
 *  priority of the process
 * @param period
 *  Sets the period of a task in milliseconds
 * @param start_time
 *  Time after which the task shall be executed the first time
 * 
 * @param overflow
 *  Determines if the task shall be executed in an odd timer iteration
 * 
 * @param param
 *  Parameter of the function
 * 
 * @param id
 *  A unique task id 
 */

bool timeBasedScheduler_addPeriodicTaskWithParam(timeBasedScheduler_t tBScheduler, void (*function)(char*), uint8_t priority, uint16_t period, uint16_t start_time, bool overflow, char* param, uint8_t id);

/**
 * @brief
 *  Deletes the task with the given id from the scheduler.
 * @param tBScheduler
 *  timeBasedScheduler handle
 * @param id
 *  Id of the task which is to be deleted
 * 
 * 
 */

void timeBasedScheduler_deleteTask(timeBasedScheduler_t tBScheduler, uint8_t id);

/**
 * @brief
 *  Returns the Overflow state of the internal timer
 * @return
 *  Overflow state of the internal timer
 * 
 */

bool timeBasedScheduler_getOverflowBit(timeBasedScheduler_t tBScheduler);

/**
 * @brief
 *  Returns all used ids of the scheduler in a 32bit Value.
 *  If the n'th bit is not set -> the n'th id is available
 * @return
 *  All used ids
 * 
 */
uint32_t timeBasedScheduler_getUsedIDsInt(timeBasedScheduler_t tBScheduler);
#endif
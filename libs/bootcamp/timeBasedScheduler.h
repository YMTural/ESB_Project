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
 * @param   maxSize
 *  Maximum size of the task queue
 * 
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
 * @brief   Adds a new task to the schedule
 * 
 * @param   function
 *  function which is to be executed
 * @param priority
 *  priority of the process
 * @param periodic
 *  sets the periodicity of a task
 * 
 */

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void (*function)(void), uint8_t priority, uint16_t start_time);

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

bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void (*function)(void), uint8_t priority, uint16_t period, uint16_t startTime, bool overflow);

/**
 * @brief   Schedules all the tasks. Will run forever. Can return error code
 * @param
 *  time based Schedule which is to be scheduled
 */
void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler);

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


/**
 *  @brief Iterates of the queue marking all Task ready if their start time is reached
 * 
 *  @param tBScheduler
 *   Scheduler container
 *   
 * 
 */

bool timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler);

/**
 *  @brief Increments the Timer and checks for overflow
 * 
 * @param tBScheduler
 *  Time based scheduler container
 * @param currentTime
 *  Timer which is to be incremented
 * 
 * 
 */
void timeBasedScheduler_incrementTimer(timeBasedScheduler_t tBScheduler);

bool timeBasedScheduler_addTaskWithParam(timeBasedScheduler_t tBScheduler, void (*function)(char*), uint8_t priority, uint16_t start_time, char* param);

uint8_t timeBasedScheduler_findNextAvailableId(timeBasedScheduler_t tBScheduler);

void timeBasedScheduler_freeID(timeBasedScheduler_t tBScheduler, uint8_t n);

bool timeBasedScheduler_addPeriodicTaskID(timeBasedScheduler_t tBScheduler, void (*function)(void), uint8_t priority, uint16_t period, uint16_t start_time, bool overflow, uint8_t id);

bool timeBasedScheduler_addPeriodicTaskWithParam(timeBasedScheduler_t tBScheduler, void (*function)(char*), uint8_t priority, uint16_t period, uint16_t start_time, bool overflow, char* param, uint8_t id);

void timeBasedScheduler_deleteTask(timeBasedScheduler_t tBScheduler, uint8_t id);

bool timeBasedScheduler_getOverflowBit(timeBasedScheduler_t tBScheduler);

uint32_t timeBasedScheduler_getUsedIDsInt(timeBasedScheduler_t tBScheduler);
#endif
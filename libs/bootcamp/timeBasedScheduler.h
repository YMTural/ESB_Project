#ifndef TIMEBASEDSCHEDULER_H
#define TIMEBASEDSCHEDULER_H
#include "bootcamp/debug.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bootcamp/task.h"
#include "bootcamp/priorityQueueHeap.h"
#include "bootcamp/arduinoArch.h"
#if(DEBUG == 0)
#include <avr/interrupt.h>
#endif
#if(DEBUG == 1)
#include "bootcamp/interrupt.h"
#endif


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

#if DEBUG == 1
typedef struct  timeBasedScheduler
{
    priorityQueueHeap_t queue;
    uint16_t currentTime;

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

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t start_time);

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


void timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler, uint16_t currentTime);

#endif
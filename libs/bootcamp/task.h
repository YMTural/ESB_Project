#ifndef TASK
#define TASK
#include <stdint.h>
#include "bootcamp/debug.h"
/**
 * @typedef task
 * @brief   A task structure
 * 
 */
typedef struct task {

    uint8_t id;

    void (*function)(void);

    uint8_t priority;

    bool isPeriodic;
    //Period time
    uint16_t period;
    //Ready status
    bool isReady;
    //When to be executed
    uint16_t startTime;
}task;

#endif
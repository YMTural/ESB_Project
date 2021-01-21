#ifndef TASK
#define TASK
#include <stdint.h>
#include <stdbool.h>
#include "bootcamp/debug.h"
/**
 * @typedef task
 * @brief   A task structure
 * 
 */
typedef struct task {

    uint8_t id;
    union functionType{
        void (*voidfunction)(void);
        void (*charfunction)(char * param);
    }functions;
    char * param;
    uint8_t paramLength;
    uint8_t priority;

    bool isPeriodic;
    //Period time
    uint16_t period;
    //Ready status
    bool isReady;
    //When to be executed
    uint16_t startTime;
    //Overflow
    bool overflow;
}task;

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
#endif
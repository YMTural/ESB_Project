#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    SINGLE,
    MULTI,
    NONE
}cmdType;

/**
 * @typedef UART_interrupt
 * @brief   Opaque UART_interrupt structure.
 * 
 * This enables encapsulation: the internals will be implemented in the .c file
 * 
 */

typedef struct taskHandler taskHandler;


/**
 * @typedef UART_buffer_t
 * @brief  UART_buffer abstract data type interface.
 */

typedef taskHandler* taskHandler_t;


/**
 * @brief   A data transmission is initiated by
 *          enableling Interrupts 
 *           
 * @param   ubuf
 *  8 bit data which is to be transmitted
 */

taskHandler_t taskHandler_init(const char singleCommands[][9], const char multiCommands[][9]);

uint8_t taskHandler_parseNextToken(taskHandler_t taskHandler, char* readBuffer, uint8_t length);

uint8_t taskHandler_commandType(taskHandler_t taskHandler);

//Returns char to param (malloc called)!
char* taskHandler_getParam(taskHandler_t taskHandler);

uint8_t taskHandler_getCommandNumber(taskHandler_t taskHandler);

void taskHandler_reset(taskHandler_t tHandler);
#endif
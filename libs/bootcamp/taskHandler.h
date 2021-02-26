#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef CHESS_H
typedef enum
{
    SINGLE,
    MULTI,
    NONE
}cmdType;
#endif
#ifdef CHESS_H
typedef enum
{
    SINGLE,
    MULTI
}cmdType;
#endif
/**
 * @typedef taskHandler
 * @brief   Opaque taskHandler structure.
 * 
 * This enables encapsulation: the internals will be implemented in the .c file
 * 
 */

typedef struct taskHandler taskHandler;


/**
 * @typedef taskHandler_t
 * @brief  taskHandler abstract data type interface.
 */

typedef taskHandler* taskHandler_t;


/**
 * @brief
 *  Initializes the taskHandler
 * @param singleCommands
 *  Function pointer array of all commands with no paramters
 * @param multiCommands
 *  Function pointer array of all commands with parameters 
 *           
 * @returns
 *  A taskhandler handle
 */

taskHandler_t taskHandler_init(const char singleCommands[][9], const char multiCommands[][9]);


/**
 * @brief
 *  Parses the next Token in a String determining the command and its paramter.
 *  Returns 254 if there is no free memory
 *  Returns 255 if the parsed command is unknown
 *  Returns 0 if command is too short
 * @param taskHandler
 *  The taskHandler
 * @param readBuffer
 *  The String to be parsed
 * @param length
 *  Length of the String
 * @returns
 *  The length of the parsed command
 * 
 */ 
uint8_t taskHandler_parseNextToken(taskHandler_t taskHandler, char* readBuffer, uint8_t length);

/**
 * @brief
 *  Returns the type of the last parsed command
 * @return
 *  Last commandtype
 * 
 * 
 */

uint8_t taskHandler_commandType(taskHandler_t taskHandler);

//Returns char to param (malloc called)!
/**
 * @brief
 *  Retruns a pointer to the parameter of a command
 *  Must be freed after execution!
 * @param taskHandler
 *  Taskhandler
 * 
 */
char* taskHandler_getParam(taskHandler_t taskHandler);

/**
 * @brief
 *  Returns the indice of the command in the function pointer array
 * @return
 * Position in pointer array
 * 
 */
uint8_t taskHandler_getCommandNumber(taskHandler_t taskHandler);

/**
 * @brief
 *  Resets the taskHandler in its init state
 * @param taskHandler
 *  taskHandler
 * 
 */
void taskHandler_reset(taskHandler_t tHandler);
#endif
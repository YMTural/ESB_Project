#include "bootcamp/taskHandler.h"

#define NUMBEROFSINGLECOMMANDS 6

struct taskHandler{

    uint8_t size; 

    char (*singleCommands)[9];
    char (*multiCommands)[9];

    bool commandType;

    uint8_t commandNumber;
    char* param;
};

taskHandler_t taskHandler_init(const char singleCommands[][9], const char multiCommands[][9]){

    taskHandler_t tHandler = malloc(sizeof(taskHandler));

    tHandler -> singleCommands = singleCommands;
    tHandler -> multiCommands = multiCommands;

    tHandler -> commandType = NONE;


    tHandler -> param = 0;
    tHandler -> commandNumber = 255;

    return tHandler;
}

void taskHandler_reset(taskHandler_t tHandler){

    tHandler -> commandType = NONE;

    free(tHandler -> param);
    tHandler -> param = 0;
    tHandler -> commandNumber = 255;
}

bool taskHandler_determineTaskNumber(taskHandler_t tHandler, char* taskChar, uint8_t length){

    uint8_t commandNumber = 255;
    strncpy(taskChar, taskChar, length - 1);
    taskChar[length - 1] = '\0';
    char (*list)[9] = (tHandler -> commandType == SINGLE) ? tHandler -> singleCommands : tHandler -> multiCommands;

    for (uint8_t i = 0; i < NUMBEROFSINGLECOMMANDS; i++)
    {
      if(strncmp(taskChar, list[i], length - 1) == 0){
        commandNumber = i;
        break;
      }
    }    

    tHandler -> commandNumber = commandNumber;

    if(commandNumber == 255){ 
        tHandler -> commandType = NONE;
        return false;
    }

    return true;
}

uint8_t taskHandler_getNextTokenIndex(char* string, uint8_t startIndex, uint8_t length){
    uint8_t tokenLength = 0;
    for (uint8_t i = startIndex; i < length; i++)
    {
        tokenLength++;
        if(string[i + startIndex] == ' '){
            break;
        } 
    }
    return tokenLength;
}

//Return length of Token
uint8_t taskHandler_parseNextToken(taskHandler_t tHandler, char* readBuffer, uint8_t length){
    uint8_t lengthFirstPart;
    
    if(length < 2){
        taskHandler_reset(tHandler);
        return false;
    } 

    lengthFirstPart = taskHandler_getNextTokenIndex(readBuffer, 0, length);
    tHandler -> commandType = (length > lengthFirstPart) ? MULTI : SINGLE;
    if(tHandler -> commandType == SINGLE){

        taskHandler_determineTaskNumber(tHandler, readBuffer, lengthFirstPart);
    }
    else{
    
        if(taskHandler_determineTaskNumber(tHandler, readBuffer, lengthFirstPart)){
            tHandler -> param = malloc(sizeof(char) * (length - lengthFirstPart));
            if(tHandler -> param != 0){

                strncpy(tHandler -> param, readBuffer + lengthFirstPart, length - lengthFirstPart);
                tHandler -> param[length - lengthFirstPart - 1] = '\0';
            }else{

                return 254;
            }
        }else{
            return 255;
        }
    }
        
    return lengthFirstPart;
}

uint8_t taskHandler_getCommandNumber(taskHandler_t tHandler){
    return tHandler -> commandNumber;
}

uint8_t taskHandler_commandType(taskHandler_t tHandler){
    return tHandler -> commandType;
}

char* taskHandler_getParam(taskHandler_t tHandler){
    return tHandler -> param;
}

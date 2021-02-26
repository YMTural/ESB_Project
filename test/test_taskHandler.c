#include "bootcamp/taskHandler.h"
#include "bootcamp/priorityQueueHeap.h"
#include "bootcamp/interrupt.h"
#include <unity.h>
#include "bootcamp/arduinoArch.h"

const char  multiCommands[7][9] = {"echo", "led", "flash", "sine", "periodic", "kill", ""};
const char  singleCommands[7][9] = {"help", "toggle", "inc", "counter", "temp", "list", "chess"};  

void test_parseNextTokenValidMultiCmd(void){

    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);
    
    char testInput[] = {"echo 123\n"};
    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));
    TEST_ASSERT_EQUAL_UINT8(MULTI, taskHandler_commandType(tHandler));
    TEST_ASSERT_EQUAL_UINT8(0, taskHandler_getCommandNumber(tHandler));
    TEST_ASSERT_EQUAL_STRING("123", taskHandler_getParam(tHandler));

}
void test_parseNextTokenValidSingleCmd(void){

    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);
    
    char testInput[] = {"temp\n"};
    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));
    TEST_ASSERT_EQUAL_UINT8(SINGLE, taskHandler_commandType(tHandler));
    TEST_ASSERT_EQUAL_UINT8(4, taskHandler_getCommandNumber(tHandler));
    TEST_ASSERT_EQUAL_STRING(NULL, taskHandler_getParam(tHandler));

}

void test_parseNextTokenInvalidMultiCmd(void){

    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);
    
    char testInput[] = {"ec2ho 123\n"};
    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));
    TEST_ASSERT_EQUAL_UINT8(255, taskHandler_getCommandNumber(tHandler));
    TEST_ASSERT_EQUAL_STRING(NULL, taskHandler_getParam(tHandler));

}


void test_parseNextTokenInvalidSingleCmd(void){

    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);
    
    char testInput[] = {"test\n"};
    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));
    TEST_ASSERT_EQUAL_UINT8(255, taskHandler_getCommandNumber(tHandler));
    TEST_ASSERT_EQUAL_STRING(NULL, taskHandler_getParam(tHandler));

}

void test_taskHandlerReset(void){

    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);
    
    char testInput[] = {"echo 123\n"};
    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));
    taskHandler_reset(tHandler);
    TEST_ASSERT_EQUAL_UINT8(255, taskHandler_getCommandNumber(tHandler));
    TEST_ASSERT_EQUAL_STRING(NULL, taskHandler_getParam(tHandler));

}
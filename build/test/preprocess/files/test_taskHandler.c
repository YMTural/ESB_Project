#include "build/temp/_test_taskHandler.c"
#include "libs/bootcamp/arduinoArch.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
#include "libs/bootcamp/interrupt.h"
#include "libs/bootcamp/priorityQueueHeap.h"
#include "libs/bootcamp/taskHandler.h"




const char multiCommands[7][9] = {"echo", "led", "flash", "sine", "periodic", "kill", ""};

const char singleCommands[7][9] = {"help", "toggle", "inc", "counter", "temp", "list", "chess"};



void test_parseNextTokenValidMultiCmd(void){



    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);



    char testInput[] = {"echo 123\n"};

    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((MULTI)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_commandType(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_getCommandNumber(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualString((const char*)(("123")), (const char*)((taskHandler_getParam(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(18));



}

void test_parseNextTokenValidSingleCmd(void){



    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);



    char testInput[] = {"temp\n"};

    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((SINGLE)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_commandType(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((4)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_getCommandNumber(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualString((const char*)((

   ((void *)0)

   )), (const char*)((taskHandler_getParam(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(29));



}



void test_parseNextTokenInvalidMultiCmd(void){



    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);



    char testInput[] = {"ec2ho 123\n"};

    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_getCommandNumber(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualString((const char*)((

   ((void *)0)

   )), (const char*)((taskHandler_getParam(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(40));



}





void test_parseNextTokenInvalidSingleCmd(void){



    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);



    char testInput[] = {"test\n"};

    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_getCommandNumber(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualString((const char*)((

   ((void *)0)

   )), (const char*)((taskHandler_getParam(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(52));



}



void test_taskHandlerReset(void){



    taskHandler_t tHandler = taskHandler_init(singleCommands, multiCommands);



    char testInput[] = {"echo 123\n"};

    taskHandler_parseNextToken(tHandler, testInput, strlen(testInput));

    taskHandler_reset(tHandler);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((255)), (UNITY_INT)(UNITY_UINT8 )((taskHandler_getCommandNumber(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualString((const char*)((

   ((void *)0)

   )), (const char*)((taskHandler_getParam(tHandler))), (

   ((void *)0)

   ), (UNITY_UINT)(64));



}

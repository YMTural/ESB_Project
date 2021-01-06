/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_circularBuffer_init(void);
extern void test_circularBuffer_free(void);
extern void test_circularBuffer_reset(void);
extern void test_circularBuffer_capacity(void);
extern void test_circularBuffer_pushFull(void);
extern void test_circularBuffer_pushOver(void);
extern void test_circularBuffer_pushCheck(void);
extern void test_circularBuffer_readAll(void);
extern void test_circularBuffer_readCheck(void);
extern void test_circularBuffer_readEmpty(void);
extern void test_circularBuffer_sizeFillingUp(void);
extern void test_circularBuffer_sizeLooping(void);
extern void test_circularBuffer_fullEmpty(void);
extern void test_circularBuffer_fullFull(void);
extern void test_circularBuffer_empty(void);
extern void test_circularBuffer_overWriteAll(void);
extern void test_circularBuffer_overwriteCheckTwice(void);
extern void test_circularBuffer_sizeFullBuffer(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Setup (stub)=====*/
void setUp(void) {}

/*=======Teardown (stub)=====*/
void tearDown(void) {}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, int line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======Parameterized Test Wrappers=====*/

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_circularBuffer.c");
  run_test(test_circularBuffer_init, "test_circularBuffer_init", 9);
  run_test(test_circularBuffer_free, "test_circularBuffer_free", 21);
  run_test(test_circularBuffer_reset, "test_circularBuffer_reset", 39);
  run_test(test_circularBuffer_capacity, "test_circularBuffer_capacity", 63);
  run_test(test_circularBuffer_pushFull, "test_circularBuffer_pushFull", 74);
  run_test(test_circularBuffer_pushOver, "test_circularBuffer_pushOver", 88);
  run_test(test_circularBuffer_pushCheck, "test_circularBuffer_pushCheck", 105);
  run_test(test_circularBuffer_readAll, "test_circularBuffer_readAll", 123);
  run_test(test_circularBuffer_readCheck, "test_circularBuffer_readCheck", 143);
  run_test(test_circularBuffer_readEmpty, "test_circularBuffer_readEmpty", 166);
  run_test(test_circularBuffer_sizeFillingUp, "test_circularBuffer_sizeFillingUp", 189);
  run_test(test_circularBuffer_sizeLooping, "test_circularBuffer_sizeLooping", 207);
  run_test(test_circularBuffer_fullEmpty, "test_circularBuffer_fullEmpty", 236);
  run_test(test_circularBuffer_fullFull, "test_circularBuffer_fullFull", 246);
  run_test(test_circularBuffer_empty, "test_circularBuffer_empty", 263);
  run_test(test_circularBuffer_overWriteAll, "test_circularBuffer_overWriteAll", 274);
  run_test(test_circularBuffer_overwriteCheckTwice, "test_circularBuffer_overwriteCheckTwice", 293);
  run_test(test_circularBuffer_sizeFullBuffer, "test_circularBuffer_sizeFullBuffer", 317);

  return UnityEnd();
}
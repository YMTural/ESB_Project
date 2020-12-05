/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_timeBasedScheduler_init(void);
extern void test_timeBasedScheduler_addOneTask(void);
extern void test_timeBasedScheduler_addMoreThanMaxSizeTasks(void);
extern void test_timeBasedScheduler_addOnePeriodicTask(void);
extern void test_timeBasedScheduler_addOnePeriodicTaskToFull(void);
extern void test_timeBasedScheduler_schedule(void);


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
  UnityBegin("test_timeBasedScheduler.c");
  run_test(test_timeBasedScheduler_init, "test_timeBasedScheduler_init", 8);
  run_test(test_timeBasedScheduler_addOneTask, "test_timeBasedScheduler_addOneTask", 20);
  run_test(test_timeBasedScheduler_addMoreThanMaxSizeTasks, "test_timeBasedScheduler_addMoreThanMaxSizeTasks", 28);
  run_test(test_timeBasedScheduler_addOnePeriodicTask, "test_timeBasedScheduler_addOnePeriodicTask", 41);
  run_test(test_timeBasedScheduler_addOnePeriodicTaskToFull, "test_timeBasedScheduler_addOnePeriodicTaskToFull", 57);
  run_test(test_timeBasedScheduler_schedule, "test_timeBasedScheduler_schedule", 79);

  return UnityEnd();
}

#include "bootcamp/timeBasedScheduler.h"


#if DEBUG == 0
struct  timeBasedScheduler
{
    void* queue;
    bool overflow;
    //function pointer
    uint8_t (*queueSize)(void* queue);
    uint8_t (*queueCapacity)(void* queue);
    int8_t (*queueAdd)(void* queue, task thisTask);
    task* (*queuePeekAt)(void* queue, uint8_t n);
    task* (*queueGetNextReady)(void* queue);
    void (*queueDelete)(void* queue, uint8_t n);
    uint32_t availableIDs;
    uint16_t* currentTime;
};

#endif


void timeBasedScheduler_free(timeBasedScheduler_t tBScheduler){

    free(tBScheduler);
}

//Dependency Injection
timeBasedScheduler_t timeBasedScheduler_init(uint16_t* currentTime, void* queue, uint8_t (*queueSize)(void* queue),
    uint8_t (*queueCapacity)(void* queue),
    int8_t (*queueAdd)(void* queue, task thisTask),
    task* (*queuePeekAt)(void* queue, uint8_t n),
    task* (*queueGetNextReady)(void* queue),
    void (*queueDelete)(void* queue, uint8_t n) ){

    timeBasedScheduler_t tBScheduler = malloc(sizeof(timeBasedScheduler));
    tBScheduler -> overflow = false;
    tBScheduler -> queue = queue;
    tBScheduler -> queueSize = queueSize;
    tBScheduler -> queueCapacity = queueCapacity;
    tBScheduler -> queueAdd = queueAdd;
    tBScheduler -> queuePeekAt = queuePeekAt;
    tBScheduler -> queueGetNextReady = queueGetNextReady;
    tBScheduler -> queueDelete = queueDelete;
    tBScheduler -> availableIDs = 0;
    tBScheduler -> currentTime = currentTime;


    timeBasedScheduler_timer(1,1);

    sei();


    return tBScheduler;
}

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function(void), uint8_t priority, uint16_t start_time){

    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

        return false;
    }
    uint16_t startTime;
    task task;
    //Use pointer to get most accurate currentTime
    startTime = *(tBScheduler -> currentTime) + start_time;
    //If overflow occured add with flipped overflow bit
    //This prevents timer overflow scheduling errors
    if(startTime < *(tBScheduler -> currentTime)){
        task.overflow = !tBScheduler -> overflow;
    }else
    {
        task.overflow = tBScheduler ->overflow;
    }
    task.functions.voidfunction = function;
    task.param = 0;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = false;
    task.startTime = startTime;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void* function(void), uint8_t priority, uint16_t period, uint16_t startTime, bool overflow){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){
       
        return false;
    }
 
    task task;
    task.functions.voidfunction = function;
    task.param = 0;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;   
    task.isReady = false;
    task.overflow = overflow;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}
//remove param length and use strlen(param) instead, can check with param = 0 if param is set.
bool timeBasedScheduler_addPeriodicTaskWithParam(timeBasedScheduler_t tBScheduler, void* function(char*), uint8_t priority, uint16_t period, uint16_t start_time, bool overflow, char* param, uint8_t id){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

        return false;
    }
    uint16_t startTime;
    task task;
    task.id = id;
    //Use pointer to get most accurate currentTime
    startTime = *(tBScheduler -> currentTime) + start_time;
    //If overflow occured add with flipped overflow bit
    //This prevents timer overflow scheduling errors
    if(startTime < *(tBScheduler -> currentTime)){
        task.overflow = !tBScheduler -> overflow;
    }else
    {
        task.overflow = tBScheduler ->overflow;
    }
    task.functions.charfunction = function;
    task.param = param;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;   
    task.isReady = false;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

bool timeBasedScheduler_addTaskWithParam(timeBasedScheduler_t tBScheduler, void* function(char*), uint8_t priority, uint16_t start_time, char* param){

    
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

        return false;
    }
    uint16_t startTime;
    task task;
    //Use pointer to get most accurate currentTime
    startTime = (*(tBScheduler -> currentTime) + start_time);
    //If overflow occured add with flipped overflow bit
    //This prevents timer overflow scheduling errors
    if(startTime < *(tBScheduler -> currentTime)){
        task.overflow = !tBScheduler -> overflow;
    }else
    {
        task.overflow = tBScheduler ->overflow;
    }

    task.functions.charfunction = function;
    task.param = param;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = false;
    task.startTime = startTime;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

uint8_t timeBasedScheduler_findNextAvailableId(timeBasedScheduler_t tBScheduler){

    for (uint8_t i = 0; i < 32; i++)
    {
        //Check if nth bit is set
        if( !(  ((tBScheduler -> availableIDs) >> i) & 1)  ){
            tBScheduler -> availableIDs  |= (1 << i);
            return i; 
        }
    }
    return 255;
}

void timeBasedScheduler_freeID(timeBasedScheduler_t tBScheduler, uint8_t n){

    tBScheduler -> availableIDs &= (~ (1 << n));
}



bool timeBasedScheduler_addPeriodicTaskID(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t period, uint16_t start_time, bool overflow, uint8_t id){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

       
        return false;
    }
 
    task task;
    uint16_t startTime;
    //Use pointer to get most accurate currentTime
    startTime = *(tBScheduler -> currentTime) + start_time;
    //If overflow occured add with flipped overflow bit
    //This prevents timer overflow scheduling errors
    if(startTime < *(tBScheduler -> currentTime)){
        task.overflow = !tBScheduler -> overflow;
    }else
    {
        task.overflow = tBScheduler ->overflow;
    }
    task.id = id;
    task.functions.voidfunction = function;
    task.param = 0;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;   
    task.isReady = false;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

void timeBasedScheduler_timer(uint8_t timer, uint16_t intervall){


    arduinoArch_setTimer();

}

void timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler){

    for (uint8_t i = 0; i < tBScheduler->queueSize(tBScheduler->queue); i++)
    {   
        
        if ( (tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->startTime <= *(tBScheduler -> currentTime)) && ((tBScheduler -> overflow == tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->overflow)) )
        {
            tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->isReady = true;
        }
        
    }
    

}

void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler){

    uint16_t startTime;
    task nextTask;
    task* pTask;
        pTask = tBScheduler -> queueGetNextReady(tBScheduler->queue);
        if(pTask != 0){
            nextTask = *pTask;
            if(nextTask.param){
                nextTask.functions.charfunction(nextTask.param);
            }else{
                nextTask.functions.voidfunction();
            }
            if(nextTask.isPeriodic){
                UART_transmit(nextTask.id);
                //Use pointer to get most accurate currentTime
                startTime = *(tBScheduler -> currentTime) + nextTask.period;
                //If overflow occured add with flipped overflow bit
                //This prevents timer overflow scheduling errors
                if(startTime < *(tBScheduler -> currentTime)){
                    if(nextTask.param){
                        timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, nextTask.functions.charfunction, nextTask.priority, nextTask.period, startTime, !tBScheduler -> overflow, nextTask.param, nextTask.id);
                    }else
                    {
                        timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask.functions.voidfunction, nextTask.priority, nextTask.period, startTime, !tBScheduler -> overflow);
                    }
                    
                }else{
                    if(nextTask.param){
                        timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, nextTask.functions.charfunction, nextTask.priority, nextTask.period, startTime, tBScheduler -> overflow, nextTask.param, nextTask.id);
                    }else
                    {
                        timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask.functions.voidfunction, nextTask.priority, nextTask.period, startTime, tBScheduler -> overflow);    
                    }
                    
                }
                //priorityQueueHeap_incrementPriorityOfNonPeriodic(tBScheduler->queue);
            }else{
                //Free param if task is non-periodic
                free(nextTask.param);
        }
    }
}

void timBasedScheduler_deleteTask(timeBasedScheduler_t tBScheduler, uint8_t id){

    uint8_t n;
    for (uint8_t i = 0; i < tBScheduler -> queueSize(tBScheduler -> queue); i++)
    {
        if(tBScheduler -> queuePeekAt(tBScheduler -> queue, i) -> id == id){
            n = i;
            break;
        }
    }
    
    tBScheduler -> queueDelete(tBScheduler -> queue, n);
    timeBasedScheduler_freeID(tBScheduler, n);
}

void timeBasedScheduler_incrementTimer(timeBasedScheduler_t tBScheduler){

    *(tBScheduler -> currentTime) = *(tBScheduler -> currentTime) + 1;
    if (*(tBScheduler -> currentTime) < 1)
    {
       tBScheduler -> overflow = !tBScheduler -> overflow;
    }
}

bool getOverflowBit(timeBasedScheduler_t tBScheduler){

    return tBScheduler -> overflow;
}
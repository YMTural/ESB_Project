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
};

#endif


void timeBasedScheduler_free(timeBasedScheduler_t tBScheduler){

    free(tBScheduler);
}

//Dependency Injection
timeBasedScheduler_t timeBasedScheduler_init(uint8_t maxSize, void* queue, uint8_t (*queueSize)(void* queue),
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


    timeBasedScheduler_timer(1,1);

    sei();


    return tBScheduler;
}

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function(void), uint8_t priority, uint16_t start_time){

    
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

        return false;
    }
    task task;
    task.functions.voidfunction = function;
    task.paramLength = 0;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = false;
    task.startTime = start_time;
    task.overflow = tBScheduler->overflow;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void* function(void), uint8_t priority, uint16_t period, uint16_t startTime, bool overflow){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

       
        return false;
    }
 
    task task;
    task.functions.voidfunction = function;
    task.paramLength = 0;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;   
    task.isReady = false;
    task.overflow = overflow;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

bool timeBasedScheduler_addPeriodicTaskWithParam(timeBasedScheduler_t tBScheduler, void* function(char*), uint8_t priority, uint16_t period, uint16_t startTime, bool overflow, char* param, uint8_t paramLength,  uint8_t id){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

       
        return false;
    }
 
    task task;
    task.id = id;
    task.functions.charfunction = function;
    task.param = param;
    task.paramLength = paramLength;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;   
    task.isReady = false;
    task.overflow = overflow;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}
bool timeBasedScheduler_addTaskWithParam(timeBasedScheduler_t tBScheduler, void* function(char*), uint8_t priority, uint16_t start_time, char* param, uint8_t paramLength){

    
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

        return false;
    }
    task task;
    task.functions.charfunction = function;
    task.param = param;
    task.paramLength = paramLength;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = false;
    task.startTime = start_time;
    task.overflow = tBScheduler->overflow;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

uint8_t findNextAvailabeID(timeBasedScheduler_t tBScheduler){

    for (uint8_t i = 0; i < 32; i++)
    {
        //Check if nth bit is set
        if( !((tBScheduler -> availableIDs) >> i) & 1 ){
            tBScheduler -> availableIDs  |= (1 << i);
            return i; 
        }
    }
    return 255;
}

void freeID(timeBasedScheduler_t tBScheduler, uint8_t n){

    tBScheduler -> availableIDs & (~ (1 << n));
}



bool timeBasedScheduler_addPeriodicTaskID(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t period, uint16_t startTime, bool overflow, uint8_t id){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

       
        return false;
    }
 
    task task;
    task.id = id;
    task.functions.voidfunction = function;
    task.paramLength = 0;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;   
    task.isReady = false;
    task.overflow = overflow;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}

void timeBasedScheduler_timer(uint8_t timer, uint16_t intervall){


    arduinoArch_setTimer();

}

void timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler, uint16_t currentTime){

    for (uint8_t i = 0; i < tBScheduler->queueSize(tBScheduler->queue); i++)
    {   
        
        if (tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->startTime <= currentTime && ((tBScheduler -> overflow == tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->overflow) || tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->isPeriodic == false) )
        {
            tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->isReady = true;
        }
        
    }
    

}

void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler, uint16_t* currentTime){

    uint16_t startTime;
    task nextTask;
    task* pTask;
        pTask = tBScheduler -> queueGetNextReady(tBScheduler->queue);
        if(pTask != 0){
            nextTask = *pTask;
            if(nextTask.paramLength){
                nextTask.functions.charfunction(nextTask.param);
            }else{
                nextTask.functions.voidfunction();
            }
            if(nextTask.isPeriodic){
                //Use pointer to get most accurate currentTime
                startTime = *currentTime + nextTask.period;
                //If overflow occured add with flipped overflow bit
                //This prevents timer overflow scheduling errors
                if(startTime < *currentTime){
                    if(nextTask.paramLength){
                        timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, nextTask.functions.charfunction, nextTask.priority, nextTask.period, startTime, !tBScheduler -> overflow, nextTask.param, nextTask.paramLength, findNextAvailabeID(tBScheduler));
                    }else
                    {
                        timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask.functions.voidfunction, nextTask.priority, nextTask.period, startTime, !tBScheduler -> overflow);
                    }
                    
                }else{
                    if(nextTask.paramLength){
                        timeBasedScheduler_addPeriodicTaskWithParam(tBScheduler, nextTask.functions.charfunction, nextTask.priority, nextTask.period, startTime, tBScheduler -> overflow, nextTask.param, nextTask.paramLength, findNextAvailabeID(tBScheduler));
                    }else
                    {
                        timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask.functions.voidfunction, nextTask.priority, nextTask.period, startTime, tBScheduler -> overflow);    
                    }
                    
                }
                //priorityQueueHeap_incrementPriorityOfNonPeriodic(tBScheduler->queue);
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
    freeID(tBScheduler, n);
}

void timeBasedScheduler_incrementTimer(timeBasedScheduler_t tBScheduler, uint16_t* timer){

    *timer = *timer + 1;
    if (*timer < 1)
    {
       tBScheduler -> overflow = !tBScheduler -> overflow;
    }
}
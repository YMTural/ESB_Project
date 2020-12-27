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
    task* (*queueGetNextReady)(void* queue) ){

    timeBasedScheduler_t tBScheduler = malloc(sizeof(timeBasedScheduler));
    tBScheduler -> overflow = false;
    tBScheduler -> queue = queue;
    tBScheduler -> queueSize = queueSize;
    tBScheduler -> queueCapacity = queueCapacity;
    tBScheduler -> queueAdd = queueAdd;
    tBScheduler -> queuePeekAt = queuePeekAt;
    tBScheduler -> queueGetNextReady = queueGetNextReady;


    timeBasedScheduler_timer(1,1);

    sei();


    return tBScheduler;
}

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t start_time){

    
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

        return false;
    }
    task task;
    task.function = function;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = false;
    task.startTime = start_time;
    tBScheduler -> queueAdd((tBScheduler->queue), task);
    
    return true;
}
bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t period, uint16_t startTime, bool overflow){

   
    if(tBScheduler->queueSize(tBScheduler -> queue) >= tBScheduler->queueCapacity(tBScheduler -> queue)){

       
        return false;
    }
 
    task task;
    task.function = function;
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
        
        if (tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->startTime <= currentTime && (tBScheduler -> overflow == tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->overflow) )
        {

            tBScheduler -> queuePeekAt(tBScheduler -> queue, i)->isReady = true;
        }
        
    }
    

}

void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler, uint16_t* currentTime){

    uint16_t startTime;
    task* nextTask;
        nextTask = tBScheduler -> queueGetNextReady(tBScheduler->queue);
        if(nextTask != 0){

            nextTask->function();
            
            if(nextTask -> isPeriodic){
               
                //Use pointer to get most accurate currentTime
                startTime = *currentTime + nextTask ->period;
                //If overflow occured add with flipped overflow bit
                //This prevents timer overflow scheduling errors
                if(startTime < *currentTime){
                    timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask->function, nextTask->priority, nextTask ->period, startTime, !tBScheduler->overflow);
                }else{
                    timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask->function, nextTask->priority, nextTask ->period, startTime, tBScheduler->overflow);
                }
                
                //priorityQueueHeap_incrementPriorityOfNonPeriodic(tBScheduler->queue);
            }
        }
    
 
    


}

void timeBasedScheduler_incrementTimer(timeBasedScheduler_t tBScheduler, uint16_t* timer){

    *timer = *timer + 1;
    if (*timer < 1)
    {
       tBScheduler -> overflow = !tBScheduler -> overflow;
    }
    
}
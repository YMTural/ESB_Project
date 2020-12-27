#include "bootcamp/timeBasedScheduler.h"


#if DEBUG == 0
struct  timeBasedScheduler
{
    priorityQueueHeap_t queue;
    uint16_t currentTime;
};

#endif


void timeBasedScheduler_free(timeBasedScheduler_t tBScheduler){
    //free(tBScheduler->queue.prioQueue);
    free(tBScheduler);
}





timeBasedScheduler_t timeBasedScheduler_init(uint8_t maxSize){

    timeBasedScheduler_t tBScheduler = malloc(sizeof(timeBasedScheduler));

    tBScheduler -> queue = priorityQueueHeap_init(maxSize);

    timeBasedScheduler_timer(1,1);

    sei();


    return tBScheduler;
}

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t start_time){

   
    if(priorityQueueHeap_size(tBScheduler -> queue) >= priorityQueueHeap_capacity(tBScheduler -> queue)){

       
        return false;
    }
    task task;
    task.function = function;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = false;
    task.startTime = start_time;
    priorityQueueHeap_add((tBScheduler->queue), task);
    
    return true;



}
bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t period, uint16_t startTime){

   
    if(priorityQueueHeap_size(tBScheduler -> queue) >= priorityQueueHeap_capacity(tBScheduler -> queue)){

       
        return false;
    }
 
    task task;
    task.function = function;
    task.priority = priority;
    task.isPeriodic = true;
    task.period = period;
    task.startTime = startTime;
    task.isReady = false;
    priorityQueueHeap_add((tBScheduler->queue), task);
    
    return true;



}
void timeBasedScheduler_timer(uint8_t timer, uint16_t intervall){


    arduinoArch_setTimer();

}

void timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler, uint16_t currentTime){

    for (uint8_t i = 0; i < priorityQueueHeap_size(tBScheduler->queue); i++)
    {   
        
        if (priorityQueueHeap_peekAt(tBScheduler -> queue, i)->startTime <= currentTime )
        {

            priorityQueueHeap_peekAt(tBScheduler -> queue, i)->isReady = true;
        }
        
    }
    

}

void timeBasedScheduler_schedule(timeBasedScheduler_t tBScheduler, uint16_t* currentTime){

    uint16_t startTime;
    task* nextTask;
        nextTask = priorityQueueHeap_getNextReady(tBScheduler->queue);
        if(nextTask != 0){

            nextTask->function();
            
            if(nextTask -> isPeriodic){
               
                //Use pointer to get most accurate currentTime
                startTime = *currentTime + nextTask ->period;

                timeBasedScheduler_addPeriodicTask(tBScheduler, nextTask->function, nextTask->priority, nextTask ->period, startTime);
                //priorityQueueHeap_incrementPriorityOfNonPeriodic(tBScheduler->queue);
            }
        }
    
 
    


}


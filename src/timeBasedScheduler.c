#include "bootcamp/timeBasedScheduler.h"
#include <stdio.h>

#if DEBUG == 0
struct  timeBasedScheduler
{
    priorityQueueHeap_t queue;
    uint16_t currentTime;
};

#endif



struct priorityQueueHeap
{
    task* prioQueue;
    uint8_t capacity;
    uint8_t size;
    
};


priorityQueueHeap_t priorityQueueHeap_init(uint8_t maxSize){

    priorityQueueHeap_t queue = malloc(sizeof(priorityQueueHeap));
    task *array = malloc(sizeof(task)*maxSize);
    queue -> prioQueue = array;
    queue -> capacity = maxSize;
    queue -> size = 0;
    return queue;
}


void timeBasedScheduler_free(timeBasedScheduler_t tBScheduler){
    //free(tBScheduler->queue.prioQueue);
    free(tBScheduler);
}

void priorityQueueHeap_free(priorityQueueHeap_t queue){
    //free(tBScheduler->queue.prioQueue);
    free(queue->prioQueue);
    free(queue);
}
void priorityQueueHeap_swap(uint8_t a, uint8_t b, priorityQueueHeap_t priorityQueueHeap){

    task tmp;

    tmp = priorityQueueHeap->prioQueue[a];

    priorityQueueHeap->prioQueue[a] = priorityQueueHeap->prioQueue[b];

    priorityQueueHeap->prioQueue[b] = tmp;



}

task* priorityQueueHeap_peekAt(priorityQueueHeap_t queue, uint8_t n){

    if (n >= queue->size)
    {
        return NULL;
    }else{

        return &queue -> prioQueue[n];


    }
    


}


void priorityQueueHeap_heapify(priorityQueueHeap_t priorityQueueHeap, uint8_t startIndex){




    uint8_t left = 2*startIndex+1;
    uint8_t right = 2*startIndex+2;
    uint8_t max = startIndex;

    if( (left < priorityQueueHeap -> size) && (priorityQueueHeap->prioQueue[max].priority <= priorityQueueHeap->prioQueue[left].priority)){

        max = (uint8_t) left;
    }
    if( (right < priorityQueueHeap -> size) && (priorityQueueHeap->prioQueue[max].priority <= priorityQueueHeap->prioQueue[right].priority)){

        max = (uint8_t) right;
    }

    if(max != startIndex){
        
        priorityQueueHeap_swap(startIndex,max, priorityQueueHeap);
        priorityQueueHeap_heapify(priorityQueueHeap, max);
    }

}

int priorityQueueHeap_add(priorityQueueHeap_t priorityQueueHeap, task task){

    if(priorityQueueHeap -> size == priorityQueueHeap -> capacity){

        return -1;
    }

    priorityQueueHeap -> size++;

    uint8_t index = priorityQueueHeap -> size -1;
    priorityQueueHeap -> prioQueue[index] = task;
    while (index != 0 &&  priorityQueueHeap -> prioQueue[index].priority >  priorityQueueHeap -> prioQueue[(index-1)/2].priority ){
        
        priorityQueueHeap_swap(index, (index-1)/2, priorityQueueHeap);
        index = (index-1)/2;

    }
    return 0;
}

task* priorityQueueHeap_getNext(priorityQueueHeap_t priorityQueueHeap){


    if(priorityQueueHeap->size <= 0){

        //Implement error, probably should return NULL pointer
        return NULL;
    }
    if(priorityQueueHeap->size == 1){

        priorityQueueHeap->size = 0;
        return &priorityQueueHeap -> prioQueue[0];
    }
    task task = priorityQueueHeap -> prioQueue[0];
    priorityQueueHeap -> size--;
    priorityQueueHeap -> prioQueue[0] = priorityQueueHeap -> prioQueue[priorityQueueHeap->size];
    priorityQueueHeap -> prioQueue[priorityQueueHeap -> size] = task;
    priorityQueueHeap_heapify(priorityQueueHeap, 0);
    return &priorityQueueHeap -> prioQueue[priorityQueueHeap -> size];
}

task* priorityQueueHeap_getNextReady(priorityQueueHeap_t priorityQueueHeap){

    uint8_t index = 0;
    if(priorityQueueHeap->size <= 0){
         
        //Implement error, probably should return NULL pointer
        return NULL;
        
    }
    if(priorityQueueHeap->size == 1 && priorityQueueHeap -> prioQueue[0].isReady){
         
   
        priorityQueueHeap->size = 0;
        return &priorityQueueHeap -> prioQueue[0];
    }
    //Search for next ready task
    while(!(priorityQueueHeap -> prioQueue[index].isReady)){
 
        index = (index + 1) % priorityQueueHeap -> size;
    }
    task task = priorityQueueHeap -> prioQueue[index];

    priorityQueueHeap -> size--;
    priorityQueueHeap -> prioQueue[index] = priorityQueueHeap -> prioQueue[priorityQueueHeap->size];
    priorityQueueHeap -> prioQueue[priorityQueueHeap -> size] = task;
    priorityQueueHeap_heapify(priorityQueueHeap, 0);
    return &priorityQueueHeap -> prioQueue[priorityQueueHeap -> size];
}


timeBasedScheduler_t timeBasedScheduler_init(uint8_t maxSize){

    timeBasedScheduler_t tBScheduler = malloc(sizeof(timeBasedScheduler));

    tBScheduler -> queue = priorityQueueHeap_init(maxSize);

    timeBasedScheduler_timer(1,1);

    sei();


    return tBScheduler;
}

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority){

   
    if(tBScheduler->queue -> size >= tBScheduler->queue -> capacity){

       
        return false;
    }
    task task;
    task.function = function;
    task.priority = priority;
    task.isPeriodic = false;
    task.period = 0;
    task.isReady = true;
    priorityQueueHeap_add((tBScheduler->queue), task);
    
    return true;



}
bool timeBasedScheduler_addPeriodicTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, uint16_t period, uint16_t startTime){

   
    if(tBScheduler->queue -> size >= tBScheduler->queue -> capacity){

       
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

    TCNT0=0;
    //Sets CTC mode
    TCCR0A=(1<<WGM01);
    //Sets top value for output compare 
    OCR0A=250;
    //Enable interrupt for output compare 
    TIMSK0=(1<<OCIE0A);
    //Selects Prescaler 64 and start timer0
    TCCR0B=(1<<CS01)|(1<<CS00);

}

void timeBasedScheduler_markIfReady(timeBasedScheduler_t tBScheduler, uint16_t currentTime){

    for (uint8_t i = 0; i < tBScheduler->queue -> size; i++)
    {   
        if (tBScheduler->queue -> prioQueue[i].startTime <= currentTime )
        {

            tBScheduler->queue -> prioQueue[i].isReady = true;
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

            }
        }
        
 
    


}


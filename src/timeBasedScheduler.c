#include "bootcamp/timeBasedScheduler.h"

struct task
{
    uint8_t id;
    void *function;
    uint8_t priority;
    bool periodicity;
};

struct priorityQueueHeap
{
    task* prioQueue;
    uint8_t capacity;
    uint8_t size;
    
};

struct  timeBasedScheduler
{
    priorityQueueHeap queue;
};

priorityQueueHeap priorityQueueHeap_init(uint8_t maxSize){

    priorityQueueHeap queue;
    task *array = malloc(sizeof(task)*maxSize);
    queue.prioQueue = array;
    queue.capacity = maxSize;
    queue.size = 0;

    return queue;
}


void timeBasedScheduler_free(timeBasedScheduler_t tBScheduler){
    free(tBScheduler->queue.prioQueue);
    free(tBScheduler);
}

static void priorityQueueHeap_swap(uint8_t a, uint8_t b, priorityQueueHeap_t priorityQueueHeap){

    task tmp;

    tmp = priorityQueueHeap->prioQueue[a];

    priorityQueueHeap->prioQueue[a] = priorityQueueHeap->prioQueue[b];

    priorityQueueHeap->prioQueue[b] = tmp;



}

void priorityQueueHeap_heapify(priorityQueueHeap_t priorityQueueHeap, uint8_t startIndex){

    uint8_t left = 2*startIndex+1;
    uint8_t right = 2*startIndex+2;
    uint8_t max = startIndex;;

    if( (left <= priorityQueueHeap -> capacity) && (priorityQueueHeap->prioQueue[startIndex].priority < priorityQueueHeap->prioQueue[left].priority)){

        max = left;
    }
    if( (right <= priorityQueueHeap -> capacity) && (priorityQueueHeap->prioQueue[startIndex].priority < priorityQueueHeap->prioQueue[right].priority)){

        max = right;
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

task priorityQueueHeap_getNext(priorityQueueHeap_t priorityQueueHeap){


    if(priorityQueueHeap->size <= 0){

        //Implement error
        return;
    }
    if(priorityQueueHeap->size == 1){

        priorityQueueHeap->size = 0;
        return priorityQueueHeap -> prioQueue[0];
    }
    task task = priorityQueueHeap -> prioQueue[0];
    priorityQueueHeap -> size--;
    priorityQueueHeap -> prioQueue[0] = priorityQueueHeap -> prioQueue[priorityQueueHeap->size];
    priorityQueueHeap_heapify(priorityQueueHeap, 0);
    return task;
}

timeBasedScheduler_t timeBasedScheduler_init(uint8_t maxSize){

    timeBasedScheduler_t tBScheduler = malloc(sizeof(timeBasedScheduler));

    tBScheduler -> queue = priorityQueueHeap_init(maxSize);

    return tBScheduler;
}

bool timeBasedScheduler_addTask(timeBasedScheduler_t tBScheduler, void* function, uint8_t priority, bool periodic){

   
    if(tBScheduler->queue.size >= tBScheduler->queue.capacity){

        //Implement error
        return false;
    }
    task task;
    task.function = function;
    task.priority = priority;
    task.periodicity = periodic;
    priorityQueueHeap_add(&(tBScheduler->queue), task);
    
    return true;



}
#include "bootcamp/priorityQueueHeap.h"

struct priorityQueueHeap
{
    task* prioQueue;
    uint8_t capacity;
    uint8_t size;
};


priorityQueueHeap_t priorityQueueHeap_init(uint8_t maxSize, task* array){

    priorityQueueHeap_t queue = malloc(sizeof(priorityQueueHeap));
    
    //This caused a weird bug!
    //task *array = malloc(sizeof(task)*maxSize);
    queue -> prioQueue = array;
    queue -> capacity = maxSize;
    queue -> size = 0;
    return queue;
}

int8_t priorityQueueHeap_add(void* v_priorityQueueHeap, task task){

    priorityQueueHeap_t priorityQueueHeap = v_priorityQueueHeap;

    if(priorityQueueHeap -> size == priorityQueueHeap -> capacity){

        return -1;
    }

    uint8_t index = priorityQueueHeap -> size;
    priorityQueueHeap -> size++;
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
        return 0;
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

task* priorityQueueHeap_getNextReady(void* v_priorityQueueHeap){
    priorityQueueHeap_t priorityQueueHeap = v_priorityQueueHeap;
    uint8_t index = 0;
    bool found = false;
    if(priorityQueueHeap->size <= 0){
         
        //Implement error, probably should return NULL pointer
        return 0;
        
    }
    if(priorityQueueHeap->size == 1 && priorityQueueHeap -> prioQueue[0].isReady){
         
   
        priorityQueueHeap->size = 0;
        return &priorityQueueHeap -> prioQueue[0];
    }
    //Search for next ready task
    for (uint8_t i = 0; i < priorityQueueHeap_size(priorityQueueHeap); i++)
    {
        if((priorityQueueHeap -> prioQueue[i].isReady)){
            index = i;
            found = true;
            break;
        }
    }
    if(!found){
        return 0;
    }
    //No need for busy waiting, probably check here^ for sleep opportunity
    /*
    while(!(priorityQueueHeap -> prioQueue[index].isReady)){
 
        index = (index + 1) % priorityQueueHeap -> size;
    }*/

    task task = priorityQueueHeap -> prioQueue[index];

    priorityQueueHeap -> size--;
    priorityQueueHeap -> prioQueue[index] = priorityQueueHeap -> prioQueue[priorityQueueHeap->size];
    priorityQueueHeap -> prioQueue[priorityQueueHeap -> size] = task;
    priorityQueueHeap_heapify(priorityQueueHeap, index);
    return &priorityQueueHeap -> prioQueue[priorityQueueHeap -> size];
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
void priorityQueueHeap_swap(uint8_t a, uint8_t b, priorityQueueHeap_t priorityQueueHeap){

    task tmp;

    tmp = priorityQueueHeap->prioQueue[a];
    priorityQueueHeap->prioQueue[a] = priorityQueueHeap->prioQueue[b];
    priorityQueueHeap->prioQueue[b] = tmp;
}

task* priorityQueueHeap_peekAt(void* v_queue, uint8_t n){

    priorityQueueHeap_t queue = v_queue;
    if (n >= queue->size)
    {
        return 0;
    }else{

        return &queue -> prioQueue[n];
    }
}


uint8_t priorityQueueHeap_size(void* v_priorityQueueHeap){

    priorityQueueHeap_t priorityQueueHeap = v_priorityQueueHeap; 

    return priorityQueueHeap -> size;
}

uint8_t priorityQueueHeap_capacity(void* v_priorityQueueHeap){

    priorityQueueHeap_t priorityQueueHeap = v_priorityQueueHeap;

    return priorityQueueHeap -> capacity;
}

void priorityQueueHeap_free(priorityQueueHeap_t queue){

    //free(queue->prioQueue);
    free(queue);
}
/*
void priorityQueueHeap_incrementPriorityOfNonPeriodic(priorityQueueHeap_t priorityQueueHeap){

    for(uint8_t i = 0; i < priorityQueueHeap->size; i++)
    {
        if (!priorityQueueHeap -> prioQueue[i].isPeriodic && priorityQueueHeap -> prioQueue[i].priority != 255) 
        {
            priorityQueueHeap -> prioQueue[i].priority++;
        }
    }
}
*/

void priorityQueueHeap_deleteItem(void* v_priorityQueueHeap, uint8_t n){

    priorityQueueHeap_t queue = v_priorityQueueHeap;

    if (queue -> size <= n){

        return;
    }
    else{

        priorityQueueHeap_swap(n, (queue -> size) - 1, queue);
        queue -> size--;
        priorityQueueHeap_heapify(queue, n);
    }
}
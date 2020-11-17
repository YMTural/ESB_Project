#include "bootcamp/circularBuffer.h"


struct circularBuffer {

    uint8_t* startAddress;   
    uint8_t* endAddress;

    uint8_t* startIndex;
    uint8_t* endIndex;

    //To fully utilise the bufferspace
    uint8_t full;
    //Avoiding calculating it everytime it is needed
    uint8_t capacity;
};


circularBuffer_t circularBuffer_init(uint8_t* buffer, size_t size){

    circularBuffer_t cbuf = malloc(sizeof(circularBuffer));

    cbuf->startAddress = buffer;
    cbuf->endAddress = buffer + size;
    
    cbuf->startIndex = cbuf->startAddress;
    cbuf->endIndex = cbuf->startAddress;

    cbuf->full = 0;
    cbuf->capacity = size;
    
    return cbuf;
}

void circularBuffer_free(circularBuffer_t cbuf){

    free(cbuf);
}

void circularBuffer_reset(circularBuffer_t cbuf){
   
    cbuf->startIndex = 0;
    cbuf->endIndex = 0;

    for(int i = 0; i < cbuf->capacity; i++){

        *(cbuf->startAddress + i) = 0;
    }
}

void circularBuffer_overwrite(circularBuffer_t cbuf, uint8_t data){
   
    if(circularBuffer_push(cbuf, data) == -1){

        *(cbuf->startIndex) = data;
        cbuf->startIndex = cbuf->startAddress + ((cbuf->startIndex - cbuf->startAddress) + 1) % cbuf->capacity;
    }

}

int8_t circularBuffer_push(circularBuffer_t cbuf, uint8_t data){

    if(!cbuf->full){

        *(cbuf->endIndex) = data;
        //newEndpos = currentPos + 1 mod cap
        cbuf->endIndex = cbuf->startAddress + ((cbuf->endIndex - cbuf->startAddress) + 1) % cbuf->capacity;
        cbuf->full = (cbuf->startIndex == cbuf->endIndex);
        return 0;
    }
    return -1;
}

int8_t circularBuffer_read(circularBuffer_t cbuf, uint8_t* data){

    if(!circularBuffer_empty(cbuf)){
        *data = *(cbuf->startIndex);
        //newEndpos = currentPos + 1 mod cap
        cbuf->startIndex = cbuf->startAddress + ((cbuf->startIndex - cbuf->startAddress) + 1) % cbuf->capacity;
        cbuf->full = 0;
        return 0;
    }
    return -1;
}


bool circularBuffer_empty(circularBuffer_t cbuf){

    return ( (cbuf-> startIndex == cbuf->endIndex) && (!(cbuf->full)));
}

bool circularBuffer_full(circularBuffer_t cbuf){

    return cbuf->full; 

}

size_t circularBuffer_capacity(circularBuffer_t cbuf){

    return cbuf->capacity;
}

size_t circularBuffer_size(circularBuffer_t cbuf){

    size_t size = cbuf->capacity; 

    if(!cbuf->full){

        if(cbuf->startIndex <= cbuf->endIndex){
            
            size =  cbuf->endIndex - cbuf->startIndex;

        }else{
            //Looping, therefore must subtract from max size
            size = size - (cbuf->startIndex - cbuf->endIndex);
        }


    }

    return size;
}


#ifndef RINGBUFFER
#define RINGBUFFER

#include <sys/sem.h> // Semaphore stuff
#include <sys/shm.h> // Shared mem stuff

struct ringbufferTools{
    sem_t mutex;

    sem_t written;
    sem_t read;


    off_t readPos; //current position of reading 
    off_t writePos; //current position of writing

    size_t buf_size;
}


struct ringBuffer{
    struct ringbufferTools tools;
    char buffer[];
}




#endif
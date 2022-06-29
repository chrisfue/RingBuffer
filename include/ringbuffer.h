#ifndef RINGBUFFER
#define RINGBUFFER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>// Shared mem definitions and functions
#include <sys/sem.h>// Semaphore definitions and functions
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

struct ringbufferTools
{
    

    sem_t *written; //write semaphore, sem_post after writing
    sem_t  *read;   //read semaphore, sem_post after reading

    off_t readPos;  // current position of reading
    off_t writePos; // current position of writing

    size_t buf_size;
};

struct ringBuffer
{
    struct ringbufferTools tools;
    char * buffer;
};



char * getadressSpace(char * memName, int size,int * blockID);

#endif
#include <stdio.h>
#include <ringbuffer.h>

#define BUFFSIZE 20

int main(int argc, char **Argv){
    struct ringBuffer myRingBuff={0};


//remove potential old semaphores
sem_unlink("written");
sem_unlink("read");


//set semaphores for this process
myRingBuff.tools.written = sem_open("/written", O_CREAT,0660,0);
if(myRingBuff.tools.written == SEM_FAILED){
    perror("sem_open \"/written\"");
    return(EXIT_FAILURE);
}
myRingBuff.tools.read = sem_open("/read", O_CREAT,0660,0);
if(myRingBuff.tools.read == SEM_FAILED){
    perror("sem_open \"/read\"");
    return(EXIT_FAILURE);
}


myRingBuff.buffer = getadressSpace("sharedMem",BUFFSIZE);

if(myRingBuff.buffer==NULL){
    printf("Error at assigning block");
return 1;
}

while(1){
printf("%s",myRingBuff.buffer);
}

}
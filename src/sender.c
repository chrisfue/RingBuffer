
#include "ringbuffer.h"



int main(int argc, char **argv){

//buffersize from arguments:

int buffsize= strtod(argv[1],NULL);
printf("%d",buffsize);

//create ringbuffer
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




//set shared memory
myRingBuff.buffer = getadressSpace("sharedMem",buffsize);

if(myRingBuff.buffer==NULL){
    printf("Error at assigning block");
return 1;
}

//set up writing process:
char temp;
int i=0;

while(temp=getc(stdin)!=EOF){
    //increment Semaphore
sem_post(myRingBuff.tools.written);

//write to Buffer
myRingBuff.buffer[i%buffsize]=temp;

//increment write index
myRingBuff.tools.writePos++;

}



}
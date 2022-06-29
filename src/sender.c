
#include "ringbuffer.h"



int main(int argc, char **argv){


int blockID;

//buffersize from arguments:

int buffsize= strtod(argv[1],NULL);
printf("%d",buffsize);

//create ringbuffer
struct ringBuffer myRingBuff={0};


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
myRingBuff.buffer = getadressSpace("sharedMem",buffsize,&blockID);

if(myRingBuff.buffer==NULL){
    printf("Error at assigning block");
return 1;
}

//set up writing process:
char temp;
int i=0;

while(1){
    
//take over char
    temp=fgetc(stdin);

    
    //increment Semaphore
if(sem_post(myRingBuff.tools.written)!=0){
    perror("sem_post");
}
if(temp==EOF){
    //write to Buffer
myRingBuff.buffer[myRingBuff.tools.writePos%buffsize]=temp;

//increment write index
myRingBuff.tools.writePos++;
        
    //decrement Semaphore    
    if(sem_wait(myRingBuff.tools.read)!=0){
        perror("sem_wait_read");
    }
        break;

        
    }

//write to Buffer
myRingBuff.buffer[myRingBuff.tools.writePos%buffsize]=temp;

//increment write index
myRingBuff.tools.writePos++;


sem_wait(myRingBuff.tools.read);

}



//}
//printf("%s", myRingBuff.buffer);
//shmctl(blockID,IPC_RMID,NULL);




}
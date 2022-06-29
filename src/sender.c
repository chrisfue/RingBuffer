
#include "ringbuffer.h"



int main(int argc, char **argv){


int blockID;

//buffersize from arguments:

int buffsize= strtod(argv[1],NULL); //strtod for buffsize, returns 0 on failure
if(buffsize<=0){
    printf("incorrect call of function\nTry \"./receiver <buffersize>\"");
    return EXIT_FAILURE;
}

printf("Please enter text to write to Ringbuffer\n exit with CTRL+D");

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


while(1){
  int writeIndex= myRingBuff.tools.writePos%buffsize;
//take over char
    temp=fgetc(stdin);


//write to buffer (writer always has to start)
    myRingBuff.buffer[writeIndex]=temp;
    
    //increment Semaphore, so other process is not blocked by sem_wait and can read the entered char
if(sem_post(myRingBuff.tools.written)!=0){
    perror("sem_post");
}
//Condition for finishing
if(temp==EOF){
    //write to Buffer
//myRingBuff.buffer[writeIndex]=temp;

//increment write index
myRingBuff.tools.writePos++;
        
    //decrement Semaphore    
    if(sem_wait(myRingBuff.tools.read)!=0){
        perror("sem_wait_read");
    }
        break;

        
    }

//write to Buffer
//myRingBuff.buffer[myRingBuff.tools.writePos%buffsize]=temp;

//increment write index
myRingBuff.tools.writePos++;

//Wait for other process to continue
if(sem_wait(myRingBuff.tools.read)!=0){
        perror("sem_wait_read");
    }

}



//}
//printf("%s", myRingBuff.buffer);
//shmctl(blockID,IPC_RMID,NULL);




}
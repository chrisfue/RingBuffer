#include <stdio.h>
#include <ringbuffer.h>



int main(int argc, char **argv){
    struct ringBuffer myRingBuff={0};

int buffsize = strtod(argv[1],NULL); //Strtod for buffsize, returns 0 on failure
if(buffsize<=0){
    printf("incorrect call of function\nTry \"./receiver <buffersize>\"");
    return EXIT_FAILURE;
}

int blockID;




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

//access shared mem
myRingBuff.buffer = getadressSpace("sharedMem",buffsize,&blockID);

if(myRingBuff.buffer==NULL){
    printf("Error at assigning block");
return 1;
}

//read look
while(1){


int readIndex =myRingBuff.tools.readPos%buffsize;
    
   //Wait for write process to start
    if(sem_wait(myRingBuff.tools.written)!=0){
        perror("sem_wait_written");
    }
    

if((int)myRingBuff.buffer[readIndex]==EOF){
    myRingBuff.tools.readPos++;

    //increase to allow
sem_post(myRingBuff.tools.read);
        break;
    }
    
printf("%c",myRingBuff.buffer[readIndex]);
myRingBuff.tools.readPos++;
sem_post(myRingBuff.tools.read);


}

sem_unlink("/written");
sem_unlink("/read");

}
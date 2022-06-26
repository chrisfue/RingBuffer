


#include "ringbuffer.h" //my shared mem definitions and functions



char * getadressSpace(char *memName, int size){

    // 1. Get FileID:

    int blockID;
    key_t key = ftok(memName, 0); // On success, the generated key_t value is returned. - man page
    if (key == -1)                // on Failure -1 is returned.
    {
        perror("ftok failed");
    }

    blockID = shmget(key, size, 0777 | IPC_CREAT);

    // 2. Get Pointer to Mem:

    char *memPo; // Pointer to emit

    memPo = shmat(blockID, NULL, 0);
    if (memPo == (char *)(-1))
    { // shmat man page: the shared memory segment shall not be attached,
        // shmat() shall return (void *)-1, and errno shall be set to
        // indicate the error.
        perror("Shmat:");
        return NULL;
    }

    return memPo;
}





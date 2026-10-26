#include <sys/shm.h>   // for shared memory functions
#include <stdio.h>     // for printf()
#include <string.h>    // for strcpy()

int main() {
    // create shared memory segment
    int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);

    // attach shared memory to process address space
    char *data = (char*) shmat(shmid, NULL, 0);

    // write directly into shared memory
    strcpy(data, "Shared memory message");

    // read from same shared memory
    printf("Data: %s\n", data);

    return 0;
}

// shmget → creates shared memory block
// 1024 → size in bytes

// shmat → attaches memory to process
// returns pointer to shared region

// strcpy writes directly into shared space

// NO COPYING involved:
// ➤ all processes access same memory

// This is SEND BY REFERENCE



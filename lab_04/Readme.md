
# Lab 04: Inter-Process Communication Using Shared Memory

## Operating Systems Lab

**Topic:** Inter-Process Communication (IPC)  
**Technique:** System V Shared Memory  
**Language:** C  
**Operating System:** Ubuntu Linux  
**Header File:** `sys/shm.h`

---

## 1. Overview

This lab explores shared memory as a mechanism for Inter-Process Communication (IPC) in Linux. Shared memory allows multiple processes to access the same memory region, enabling efficient communication by avoiding the need to transfer each message through a pipe or message queue.

The practical demonstrates how to create a shared memory segment, attach it to a process's address space, write data into it, and read the stored data.

## 2. Learning Objectives

- Understand the role of shared memory in IPC.
- Learn how to create a shared memory segment using `shmget()`.
- Understand how `shmat()` attaches shared memory to a process.
- Write and read data using a shared memory pointer.
- Compare shared memory with pipes and message queues.

## 3. Concepts Covered

### 3.1 Shared Memory

Shared memory is an IPC technique in which multiple processes can access the same memory region. Once the memory segment is attached, processes can read and write data through pointers to that region.

Unlike pipes and message queues, shared memory does not require each message to be passed through a separate kernel-managed communication buffer. However, processes may still need synchronization mechanisms to prevent conflicting access.

### 3.2 Creating Shared Memory with `shmget()`

The `shmget()` system call creates or accesses a shared memory segment.

```c
int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
```

- `IPC_PRIVATE`: Requests a new shared memory segment.
- `1024`: Specifies the segment size in bytes.
- `0666`: Specifies read and write permissions, subject to system permissions.
- `IPC_CREAT`: Requests creation of the segment.
- `shmid`: Stores the shared memory identifier returned by the call.

### 3.3 Attaching Shared Memory with `shmat()`

The `shmat()` system call attaches the shared memory segment to the process's address space.

```c
char *data = (char *) shmat(shmid, NULL, 0);
```

- `shmid`: Identifier of the shared memory segment.
- `NULL`: Allows the operating system to choose the attachment address.
- `0`: Attaches the segment with default read/write access.
- `data`: Pointer used to access the shared memory.

### 3.4 Writing and Reading Data

The program writes a message into shared memory:

```c
strcpy(data, "Shared memory message");
```

It then reads the message from the same memory region:

```c
printf("Data: %s\n", data);
```

The pointer `data` refers to the attached shared memory. Therefore, the program writes and reads the string directly through that pointer.

### 3.5 Send-by-Reference Concept

Shared memory is commonly described as a **shared-memory communication model** rather than send-by-copy. Multiple processes can access the same underlying memory segment instead of passing separate copies of the message between processes.

This can reduce data-transfer overhead, but synchronization may be required when multiple processes access the same data concurrently.

## 4. Program Workflow

1. Include the required header files.
2. Create a shared memory segment using `shmget()`.
3. Attach the segment using `shmat()`.
4. Store a message in the shared memory.
5. Read the stored message using the same pointer.
6. Display the message using `printf()`.

### Workflow Diagram

```text
Start
  |
  v
Create Shared Memory
     (shmget)
  |
  v
Attach Memory
     (shmat)
  |
  v
Write Message
  |
  v
Read Message
  |
  v
Display Output
  |
  v
End
```

## 5. Source Code

Save the program as `shared-memory.c`.

```c
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);

    char *data = (char *) shmat(shmid, NULL, 0);

    strcpy(data, "Shared memory message");

    printf("Data: %s\n", data);

    return 0;
}
```

**Note:** This is the basic demonstration program. A complete implementation should check system-call errors, detach the memory, and remove the shared memory segment when it is no longer needed.

## 6. Compile and Run

Open the Ubuntu terminal and navigate to the lab directory.

Compile the program:

```bash
gcc -Wall -Wextra -g shared-memory.c -o shared-memory
```

Execute it:

```bash
./shared-memory
```

## 7. Expected Output

```text
Data: Shared memory message
```

The program displays the message stored in the shared memory segment.

## 8. Important System Calls

| Function | Purpose |
|---|---|
| `shmget()` | Creates or obtains a shared memory segment |
| `shmat()` | Attaches the segment to a process's address space |
| `shmdt()` | Detaches the segment from a process |
| `shmctl()` | Performs control operations, including marking a segment for removal |
| `strcpy()` | Copies a string into the destination memory |
| `printf()` | Displays the stored message |

## 9. Shared Memory vs. Pipes and Message Queues

| Feature | Pipes | Message Queues | Shared Memory |
|---|---|---|---|
| Communication model | Byte stream | Structured messages | Shared memory region |
| Data access | Through `read()` and `write()` | Through send and receive operations | Direct access through pointers |
| Data transfer | Data passes through a pipe buffer | Messages are managed by the kernel | Processes access the same memory segment |
| Synchronization | Blocking behavior can coordinate access | Send/receive operations can block | Often requires explicit synchronization |
| Typical use | Stream-based communication | Message-based communication | Efficient sharing of larger amounts of data |

## 10. Key Learnings

- Shared memory is an IPC mechanism in Linux.
- `shmget()` creates or obtains a shared memory segment.
- `shmat()` attaches the segment to the process's address space.
- A pointer provides access to the attached memory.
- Multiple processes can access the same shared memory segment.
- Shared memory can reduce data-transfer overhead.
- Synchronization is important when multiple processes access shared data concurrently.
- Shared memory resources must be managed and cleaned up appropriately.

## 11. Further Experiments

- Modify the message stored in shared memory.
- Increase or decrease the shared memory segment size.
- Create two separate processes that access the same segment.
- Observe how changes made by one process become visible to another.
- Experiment with synchronization using semaphores.
- Add error handling and proper shared memory cleanup.

## 12. Conclusion

This lab demonstrates the basic operation of System V shared memory in Linux. It covers creating a memory segment, attaching it to a process, writing a message, and reading that message through a pointer.

Shared memory is useful when processes need efficient access to common data. Unlike message-based IPC, it allows processes to work with the same underlying memory region, making synchronization and resource management important considerations.

---

**Subject:** Operating Systems  
**Lab Topic:** Inter-Process Communication Using Shared Memory


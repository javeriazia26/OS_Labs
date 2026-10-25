# Lab: Blocking and Non-Blocking Pipe Communication

## Operating Systems Lab

**Topic:** Inter-Process Communication (IPC)  
**Operating System:** Ubuntu Linux  
**Language:** C  
**Concepts:** Pipes, `read()`, `write()`, `fcntl()`, Blocking I/O, Non-Blocking I/O, Send-by-Copy

---

## 1. Overview

This lab explores how Linux handles reading and writing data through pipes. It focuses on the difference between blocking and non-blocking reads and explains how data is transferred from a process to a pipe through the operating system's kernel buffer.

The lab helps build an understanding of process synchronization, file descriptor behavior, and inter-process communication.

## 2. Learning Objectives

- Understand blocking behavior when reading from a pipe.
- Learn how non-blocking mode changes the behavior of `read()`.
- Understand the purpose of `fcntl()` and the `O_NONBLOCK` flag.
- Identify the read and write ends of a pipe.
- Understand how data is copied from user memory into the kernel's pipe buffer.

## 3. Concepts Covered

### 3.1 Blocking Read

A blocking read waits when no data is available in the pipe, provided the pipe's write end is still open. The calling process remains waiting until data becomes available or another condition ends the wait.

Example:

```c
read(fd[0], buffer, sizeof(buffer));
```

- `fd[0]`: Read end of the pipe.
- `buffer`: Memory location where the received data is stored.
- `sizeof(buffer)`: Maximum number of bytes to read, assuming `buffer` is an array in this context.
- `read()`: Attempts to retrieve data from the pipe.

**Behavior:** If the pipe is empty and a writer is still connected, the process waits until data becomes available.

### 3.2 Non-Blocking Read

Non-blocking mode allows a read operation to return without waiting when no data is available.

Example:

```c
#include <fcntl.h>

fcntl(fd[0], F_SETFL, O_NONBLOCK);
read(fd[0], buffer, sizeof(buffer));
```

- `fcntl()`: Used to change file descriptor status flags.
- `F_SETFL`: Sets file status flags.
- `O_NONBLOCK`: Enables non-blocking behavior.

**Behavior:** If the pipe is empty and its write end remains open, `read()` returns `-1` and sets `errno` to `EAGAIN` or `EWOULDBLOCK` rather than waiting.

Note: In real programs, check the return value of `fcntl()` and `read()`. When setting flags, preserve existing flags using `F_GETFL` before applying `O_NONBLOCK`.

### 3.3 Writing Data to a Pipe

The `write()` system call sends data through the write end of a pipe.

Example:

```c
write(fd[1], msg, strlen(msg) + 1);
```

- `fd[1]`: Write end of the pipe.
- `msg`: Data to send.
- `strlen(msg) + 1`: Number of bytes to write, including the terminating null character.

The operating system copies the data from the process's user-space memory into the kernel-managed pipe buffer. Another process can later read the data from that buffer.

### 3.4 Send-by-Copy

Pipe communication follows a send-by-copy model: data written by one process is copied into the kernel's pipe buffer, and a receiving process reads it into its own memory.

The processes communicate through the pipe rather than directly sharing the original user-space buffer.

## 4. Blocking vs. Non-Blocking I/O

| Feature | Blocking Read | Non-Blocking Read |
|---|---|---|
| Behavior when pipe is empty | Waits if a writer is still open | Returns immediately |
| Process execution | The calling process waits | The calling process can continue |
| Typical result when no data is available | No return until data or another condition occurs | `-1` with `errno` set to `EAGAIN` or `EWOULDBLOCK` |
| Configuration | Default pipe behavior | Enable with `O_NONBLOCK` |

## 5. Important System Calls

| Function | Purpose |
|---|---|
| `pipe()` | Creates a pipe and provides read and write file descriptors |
| `read()` | Reads data from the pipe |
| `write()` | Writes data to the pipe |
| `fcntl()` | Gets or modifies file descriptor flags |
| `strlen()` | Calculates the length of a string, excluding its null terminator |

## 6. Practical Workflow

1. Create a pipe using `pipe()`.
2. Identify the read end (`fd[0]`) and write end (`fd[1]`).
3. Use `write()` to send a message through the pipe.
4. Use `read()` to receive the message.
5. Observe blocking behavior when no data is available.
6. Enable `O_NONBLOCK` using `fcntl()` and observe the difference.
7. Compare how the process behaves in both modes.

## 7. Key Learnings

- A pipe provides a communication channel between processes.
- `fd[0]` is used for reading, while `fd[1]` is used for writing.
- A blocking read can suspend a process while waiting for data.
- Non-blocking mode allows a read operation to return immediately when data is unavailable.
- The `fcntl()` function can change a file descriptor's status flags.
- Pipe communication transfers data through a kernel-managed buffer.

## 8. Further Experiments

- Run a read operation before writing any data and observe blocking behavior.
- Enable non-blocking mode and check the return value of `read()`.
- Use `perror()` to display errors when system calls fail.
- Compare the behavior when the write end is closed.
- Experiment with different message lengths and buffer sizes.

## 9. Conclusion

This lab demonstrates how blocking and non-blocking I/O affect process behavior during pipe communication. It also explains how `read()` and `write()` interact with the kernel-managed pipe buffer and how data is transferred between processes.

These concepts are useful for understanding synchronization, process communication, and I/O behavior in Linux.

---

**Subject:** Operating Systems  
**Lab Topic:** Blocking and Non-Blocking Pipe Communication  

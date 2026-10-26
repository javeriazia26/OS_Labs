
# Lab 02: Inter-Process Communication Using System V Message Queues

**Subject:** Operating Systems  
**Topic:** Inter-Process Communication (IPC)  
**Language:** C  
**Environment:** Ubuntu Linux, GCC, and Terminal  
**Program:** [`msg_queue_demo.c`](msg_queue_demo.c) (provided by my teacher)

## Overview

This lab explores Inter-Process Communication (IPC) using System V message queues in C. Under my teacher's guidance, I studied how processes can exchange data through a message queue managed by the operating system kernel.

I practiced setting up the required environment, compiling and executing the provided program, and examining the commands used to manage message queues. This lab builds on the pipe communication concepts covered in Lab 01 and introduces another IPC mechanism with different characteristics.

The documentation covers the concepts learned, program workflow, practical commands, comparison with pipes, troubleshooting, and exercises for further practice.

## Table of Contents

- [Objectives](#objectives)
- [Concepts Covered](#concepts-covered)
- [Program Workflow](#program-workflow)
- [Pipe vs. Message Queue](#pipe-vs-message-queue)
- [Commands Used](#commands-used)
- [Troubleshooting](#troubleshooting)
- [Expected Output](#expected-output)
- [Code Observations](#code-observations)
- [Key Takeaways](#key-takeaways)
- [Experiments](#experiments)
- [Practice Exercises](#practice-exercises)

---

## Objectives

The objectives of this lab are to:

- Understand Inter-Process Communication (IPC).
- Learn how System V message queues work.
- Explore the `ftok()`, `msgget()`, `msgsnd()`, `msgrcv()`, and `msgctl()` functions.
- Understand message types and message selection.
- Practice creating, accessing, inspecting, and removing message queues.
- Compare message queues with pipes.
- Develop practical skills in compiling, executing, and troubleshooting C programs on Ubuntu.

## Concepts Covered

### 1. System V Message Queues

A message queue is an IPC mechanism managed by the operating system kernel. Processes can send messages to the queue and receive messages from it without directly sharing their ordinary process memory.

Unlike a simple byte stream, a message queue stores individual messages. Each message has a type and a data section.

### 2. Generating a Key with `ftok()`

The `ftok()` function generates a key used by processes to identify a message queue.

```c
key_t key = ftok("progfile", 65);
```

- `progfile` is the path to an existing file.
- `65` is a project identifier.
- The resulting key can be used to access the same queue from different programs, provided they generate the same key and use compatible permissions.

The file must exist and be accessible for `ftok()` to work. The generated key is not guaranteed to be globally unique, so applications should account for possible collisions.

### 3. Creating or Accessing a Queue with `msgget()`

The `msgget()` function creates a new message queue or accesses an existing one.

```c
int msgid = msgget(key, IPC_CREAT | 0666);
```

- `key` identifies the queue.
- `IPC_CREAT` requests creation if the queue does not already exist.
- `0666` specifies read and write permissions for the owner, group, and others, subject to system permission rules.
- The returned message queue ID is used in subsequent operations.

### 4. Message Structure

A System V message contains a message type followed by its data.

A typical structure looks like this:

```c
struct message {
    long mtype;
    char mtext[100];
};
```

- `mtype` is a positive integer stored as a `long`.
- `mtext` contains the actual message data.

The message type must be positive when sending a message.

### 5. Message Types

Message types allow a receiving process to select messages according to their type.

For example:

- Receiving with type `1` selects the first available message of type `1`.
- Receiving with type `2` selects the first available message of type `2`.
- Receiving with type `0` selects the first message in the queue, regardless of type.

This feature allows different categories of messages to be handled through the same queue.

### 6. Sending and Receiving Messages

Two important functions are used to exchange messages.

**`msgsnd()`** sends a message to the queue.

**`msgrcv()`** receives a message from the queue and removes it after a successful receive.

By default, `msgrcv()` blocks when no matching message is available. This behavior allows a receiving process to wait until a suitable message arrives.

### 7. Managing and Removing a Queue with `msgctl()`

The `msgctl()` function performs control operations on a message queue.

For example:

```c
msgctl(msgid, IPC_RMID, NULL);
```

The `IPC_RMID` operation removes the queue from the kernel.

System V message queues persist independently of the processes using them. They are not automatically removed merely because a program terminates, so explicit cleanup is important.

---

## Program Workflow

The provided program demonstrates message queue communication through the following steps:

1. Generates a key using the `ftok()` function, the file `progfile`, and the project identifier `65`.
2. Creates or accesses a message queue using `msgget()`.
3. Prepares a message with type `1` and the text `Hello via mailbox`.
4. Sends the message using `msgsnd()`.
5. Displays a confirmation that the message was sent.
6. Receives a message of type `1` using `msgrcv()`.
7. Displays the received message.
8. Removes the message queue using `msgctl()`.

In this demonstration, the same process sends and receives the message. This provides a straightforward introduction to the message queue API. In practical IPC applications, separate processes can use a shared key to access the same queue.

### Communication Flow

```text
        Sender
           |
           | msgsnd()
           v
   +-------------------+
   |  Kernel Message   |
   |       Queue       |
   +-------------------+
           |
           | msgrcv()
           v
        Receiver
```

## Pipe vs. Message Queue

Both pipes and message queues support inter-process communication, but they differ in how they handle data and identify communication channels.

| Feature | Pipe (Lab 01) | System V Message Queue (Lab 02) |
|---|---|---|
| Data format | Continuous stream of bytes | Individual messages |
| Communication | Commonly used for one-way communication | Processes can send and receive messages |
| Access | Pipe file descriptors must be available to the processes | Processes access the queue using its key and queue ID |
| Data selection | No message-type selection | Messages can be selected by type |
| Lifetime | Exists while its underlying pipe references remain open | Persists in the kernel until explicitly removed |
| Main interfaces | `pipe()`, `read()`, `write()` | `msgget()`, `msgsnd()`, `msgrcv()`, `msgctl()` |

**Key difference:** A pipe transfers a stream of bytes, whereas a System V message queue preserves message boundaries and supports message-type selection.

---

## Commands Used

### 1. Creating the Lab Directory

```bash
mkdir -p ~/os-labs/lab02-message-queue
cd ~/os-labs/lab02-message-queue
touch progfile
ls -l
```

| Command | Purpose |
|---|---|
| `mkdir -p` | Creates the lab directory. |
| `cd` | Moves into the lab directory. |
| `touch progfile` | Creates the file required by the example's `ftok()` call if it does not exist. |
| `ls -l` | Lists files and their details. |

**Important:** Run the program from the expected directory, or update the file path in the code accordingly.

### 2. Inspecting, Compiling, and Running the Program

```bash
head -n 3 fork-exec-wait.c
gcc -Wall -Wextra -g msg_queue_demo.c -o fork-exec-wait
./fork-exec-wait
```

- `head -n 3` displays the first three lines of the source file.
- `gcc -Wall -Wextra -g` compiles the program, enables additional warnings, and includes debugging information.
- `./msg_queue_demo` executes the compiled program.

### 3. Inspecting Message Queues

```bash
ipcs -q
```

The `ipcs -q` command lists System V message queues currently present in the kernel.

It is useful for checking whether a queue remains after a program finishes or fails.

### 4. Removing a Leftover Queue

```bash
ipcrm -q <msqid>
```

Replace `<msqid>` with the actual message queue ID displayed by `ipcs -q`.

Use this command only when you have identified the queue that needs to be removed and have permission to remove it.

---

## Troubleshooting

### 1. The Program Cannot Generate the Queue Key

**Possible cause:** The file passed to `ftok()` does not exist, is inaccessible, or the program is running from a different directory than expected.

**Solution:**

```bash
touch progfile
ls -l progfile
./fork-exec-wait
```

Ensure that the file path used in the source code resolves to the intended file.

### 2. The Program Hangs at `msgrcv()`

**Possible cause:** No message matching the requested type is available in the queue.

For example, if the program sends a message with type `2` but attempts to receive type `1`, the receive operation can block indefinitely.

**Solution:** Verify that the sent message type matches the receive operation and that `msgsnd()` completed successfully.

### 3. Message Queues Remain After Execution

**Possible cause:** The program terminated before reaching the queue-removal operation.

**Solution:**

```bash
ipcs -q
ipcrm -q <msqid>
```

Identify the correct queue ID before removing the queue.

### 4. Compilation Errors Involving `gcc`

**Possible cause:** A terminal command was accidentally placed inside the C source file.

**Solution:**

```bash
head -n 3 message-queue.c
```

Verify that the file contains C source code rather than terminal commands. Run compilation commands in the terminal.

### 5. Compiler Warnings About Message Sizes or Return Values

**Possible cause:** The program may pass an incorrect message-size argument or ignore the return values of system calls.

**Solution:** Review the warnings, verify the size of the message data, and add error checking to the relevant function calls.

---

## Expected Output

When the provided program executes successfully, the output should resemble:

```text
Message sent
Received: Hello via mailbox
```

The exact output depends on the implementation of `msg_queue_demo.c`.

---

## Code Observations

While reviewing the provided program, the following implementation details are important to understand.

### 1. Message Size

The `msgsnd()` and `msgrcv()` functions expect the size of the message data, excluding the leading `long` message-type field.

For example, if the message structure contains a text array named `mtext`, the size argument can be based on that array:

```c
sizeof(message.mtext)
```

The appropriate expression depends on the actual structure and the amount of data being sent. Passing the size of the entire structure may include the message-type field and therefore use an incorrect size.

### 2. Error Handling

System calls and related functions can fail. The program should check the return values of:

- `ftok()`
- `msgget()`
- `msgsnd()`
- `msgrcv()`
- `msgctl()`

For example:

```c
if (msgid == -1) {
    perror("msgget");
    return 1;
}
```

Appropriate error checking makes failures easier to diagnose and prevents later operations from using invalid values.

### 3. Sender and Receiver in the Same Process

The demonstration uses the same process for sending and receiving. This simplifies the example, but separate sender and receiver programs are a useful next step for understanding IPC between independent processes.

### 4. Queue Cleanup

Removing the queue after use prevents unnecessary kernel resources from remaining allocated. Programs should also handle errors so that failures during execution can be diagnosed appropriately.

---

## Key Takeaways

By studying and practicing this lab, I learned that:

- System V message queues provide a kernel-managed IPC mechanism.
- `ftok()` generates a key that can be used to identify a queue.
- `msgget()` creates or accesses a message queue.
- Each message contains a type and a data section.
- `msgsnd()` and `msgrcv()` send and receive messages.
- Message types allow receivers to select specific messages.
- `msgrcv()` can block while waiting for a matching message.
- `msgctl()` with `IPC_RMID` removes a queue.
- `ipcs -q` and `ipcrm` help inspect and manage message queues.
- Proper message sizing and error handling are important for reliable C programs.

## Experiments

The following experiments can help reinforce the concepts covered in this lab:

1. Run the program without creating `progfile` and observe how the program handles the failure.
2. Temporarily disable the queue-removal operation, execute the program, and inspect the queue using `ipcs -q`.
3. Send a message with type `2` while keeping the receive type as `1`. Observe what happens when no matching message is available.
4. Send multiple messages with different types and receive them by specifying their types.
5. Change the receive type to `0` and observe which queued message is received.
6. Correct the message-size argument and compare the behavior with the original implementation.

**Note:** Experiments that can cause the program to block should be performed in a terminal where you can safely interrupt execution.

## Practice Exercises

1. **Separate sender and receiver:** Create `sender.c` and `receiver.c` so that two independent programs use the same queue.
2. **Two-way communication:** Design a simple exchange of messages between two processes using suitable message types.
3. **User input:** Read a message from the keyboard and send it through the queue.
4. **Error handling:** Check the return values of the IPC functions and report errors using `perror()`.
5. **Multiple messages:** Send and receive five messages using a loop.

Save exercise solutions in a separate `exercises/` directory to keep the main demonstration unchanged.

---

## Conclusion

This lab introduced me to System V message queues as an IPC mechanism in Operating Systems. With the concepts taught by my teacher and practical work using the provided C program, I learned how to create a queue, send and receive messages, select messages by type, and manage queue resources.

Comparing message queues with pipes also helped me understand that different IPC mechanisms have different characteristics and use cases. These concepts provide a foundation for studying more advanced topics in process communication and synchronization.

**Next Lab:** Lab 03 — Process Creation Using `fork()`, `exec()`, and `wait()`.

---

**Documented by Javeria Zia**  
*Operating Systems — Practical Lab Series*

# Lab 06: Blocking and Non-Blocking Message Queue Communication

## Operating Systems Lab

**Topic:** Inter-Process Communication (IPC)  
**Mechanism:** System V Message Queues  
**Language:** C  
**Environment:** Ubuntu Linux  
**Concepts:** `msgsnd()`, `msgrcv()`, `IPC_NOWAIT`, Queue Capacity, Blocking I/O

---

## 1. Overview

This lab explores blocking and non-blocking message sending using System V message queues in Linux.

It demonstrates how the operating system handles messages when a queue has available capacity and what happens when the queue becomes full. The practical compares the default blocking behavior of `msgsnd()` with the non-blocking behavior enabled by `IPC_NOWAIT`.

## 2. Learning Objectives

- Understand message queue capacity and its limitations.
- Learn how `msgsnd()` sends messages to a queue.
- Observe blocking behavior when the queue is full.
- Understand the purpose of the `IPC_NOWAIT` flag.
- Handle errors returned by non-blocking message operations.
- Learn how to remove a message queue after use.

## 3. Concepts Covered

### 3.1 Blocking Message Sending

```c
msgsnd(msgid, &message, sizeof(message.msg_text), 0);
```

The final argument is `0`, so the operation uses the default blocking behavior.

- If the queue has enough space, the message is added and the sender continues.
- If the queue is full, the sender waits until space becomes available.
- If the queue is removed while the sender is waiting, the call can fail.

Blocking does not mean the receiver must be actively reading every time a message is sent. The queue can temporarily store messages.

### 3.2 Non-Blocking Message Sending

```c
msgsnd(msgid, &message,
       sizeof(message.msg_text), IPC_NOWAIT);
```

The `IPC_NOWAIT` flag prevents the sender from waiting for queue space.

If the queue is full, `msgsnd()` returns `-1` and sets `errno` to `EAGAIN`.

This allows the program to handle a full queue immediately rather than blocking.

### 3.3 Message Queue Capacity

System V message queues have operating-system-defined limits on the number and total size of queued messages.

Using `IPC_NOWAIT` does not make a queue unlimited. It only changes what happens when an operation cannot proceed immediately.

### 3.4 Message Structure

```c
struct msg_buffer {
    long msg_type;
    char msg_text[256];
};
```

- `msg_type`: Identifies the message type and must be positive when sending.
- `msg_text`: Stores the message text in a fixed-capacity array.

For `msgsnd()` and `msgrcv()`, the message-size argument excludes the leading `long msg_type` field.

## 4. Practical Workflow

1. Create a message queue using `msgget()`.
2. Prepare a message structure.
3. Send messages using `msgsnd()`.
4. In blocking mode, observe how sending pauses when the queue becomes full.
5. Allow the receiver to read messages and free queue space.
6. In non-blocking mode, use `IPC_NOWAIT` and detect `EAGAIN`.
7. Remove the queue using `msgctl()` with `IPC_RMID`.

## 5. Blocking vs. Non-Blocking Comparison

| Feature | Blocking Mode | Non-Blocking Mode |
|---|---|---|
| Flag | `0` | `IPC_NOWAIT` |
| Queue has space | Message is sent | Message is sent |
| Queue is full | Sender waits | Call returns immediately |
| Full-queue result | Waits for space or another terminating condition | `-1`, with `errno` set to `EAGAIN` |
| Sender behavior | May pause | Can continue or handle the error |
| Queue capacity | Limited | Limited |

## 6. Compile and Run

Compile the source file:

```bash
gcc -Wall -Wextra -g message-queue-blocking.c -o message-queue-blocking
```

Run blocking mode:

```bash
./message-queue-blocking blocking
```

Run non-blocking mode:

```bash
./message-queue-blocking nowait
```

## 7. Expected Behavior

### Blocking Mode

The sender submits 200 messages. The receiver waits briefly before consuming them. If the queue fills, the sender pauses until the receiver frees space.

Example progress messages:

```text
Mode: Blocking message sending
Sender: Sent 25 messages.
Sender: Sent 50 messages.
...
Receiver: Received 200 messages.
Message queue removed.
```

The exact timing and progress output depend on the system's queue limits and process scheduling.

### Non-Blocking Mode

The sender submits messages until the queue cannot accept another message.

Example:

```text
Mode: Non-blocking message sending
Queue is full; sender did not block.
Successfully sent: [system-dependent count]
Message queue removed.
```

The actual number of accepted messages varies by system configuration.

## 8. Key Learnings

- System V message queues store messages until they are received.
- A queue has finite capacity.
- Default `msgsnd()` behavior can block when the queue is full.
- `IPC_NOWAIT` makes a full-queue send fail immediately instead of waiting.
- `EAGAIN` indicates that a non-blocking send could not proceed because the queue lacked sufficient space.
- Message queues can be removed using `msgctl()` and `IPC_RMID`.

## 9. Further Experiments

- Change the message text size and observe the effect on queue capacity.
- Compare blocking and non-blocking sending.
- Change the receiver's delay in blocking mode.
- Inspect active message queues using `ipcs -q`.
- Experiment with error handling for `EAGAIN`.
- Observe the effect of removing a queue while processes are using it.

## 10. Conclusion

This lab demonstrates how System V message queues handle blocking and non-blocking message sending. It highlights the effect of finite queue capacity and explains how `IPC_NOWAIT` allows applications to respond when a queue is full.

Understanding these behaviors is useful when designing inter-process communication systems that must manage limited resources and avoid unnecessary waiting.

---

**Subject:** Operating Systems  
**Lab Topic:** Blocking and Non-Blocking Message Queue Communication

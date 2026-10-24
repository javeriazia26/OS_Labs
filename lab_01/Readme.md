

# Lab 01: Parent-Child Communication Using a Pipe

**Subject:** Operating Systems (OS)  
**Topic:** Inter-Process Communication (IPC)  
**Language:** C  
**Environment:** Ubuntu Linux, GCC, and Terminal  
**Program:** `pipe_demo.c` (provided by my teacher)

## About This Lab

This is my first practical lab for the Operating Systems (OS) subject. Under my teacher's guidance, I learned how a parent process and a child process communicate with each other using a pipe in C.

During this lab, I explored important OS concepts such as `pipe()`, `fork()`, `read()`, `write()`, and `wait()`. I also faced some errors while working with the terminal and source code, learned how to identify their causes, and documented the solutions.

I created this README to record my learning experience, the commands I used, the problems I encountered, and the concepts I understood through practical implementation.

## Table of Contents

- [Lab Objectives](#lab-objectives)
- [Concepts I Learned](#concepts-i-learned)
- [How the Program Works](#how-the-program-works)
- [Commands I Used](#commands-i-used)
- [Problems I Faced and Their Solutions](#problems-i-faced-and-their-solutions)
- [Expected Output](#expected-output)
- [What I Learned](#what-i-learned)
- [Experiments to Try](#experiments-to-try)
- [Practice Exercises](#practice-exercises)
- [Quick Troubleshooting Guide](#quick-troubleshooting-guide)

---

## Lab Objectives

The main objectives of this lab were to:

- Understand inter-process communication (IPC).
- Learn how to create a pipe using `pipe()`.
- Understand process creation using `fork()`.
- Exchange data between a parent process and a child process.
- Practice compiling and running a C program on Ubuntu.
- Learn how to identify and resolve common programming and terminal errors.

## Concepts I Learned

### 1. Inter-Process Communication (IPC)

Inter-Process Communication (IPC) refers to the mechanisms provided by an operating system that allow processes to exchange data and coordinate their activities.

In this lab, I learned how a parent process sends a message to its child process through a pipe.

### 2. Pipe

A pipe is an IPC mechanism that allows data to flow between processes. In this program, the pipe is used for one-way communication.

The `pipe()` system call creates a pipe and provides two file descriptors:

- `fd[0]`: Used to read data from the pipe.
- `fd[1]`: Used to write data into the pipe.

A pipe follows the First In, First Out (FIFO) principle, meaning data is read in the order it was written.

### 3. fork()

The `fork()` system call creates a child process from the calling process.

- In the child process, `fork()` returns `0`.
- In the parent process, it returns the child's process ID (PID).
- If process creation fails, it returns `-1`.

After `fork()` executes successfully, both processes can access the file descriptors inherited from the parent, allowing them to communicate through the same pipe.

### 4. Why Is the Pipe Created Before fork()?

I learned that the pipe must be created before calling `fork()` in this program so that the child inherits the parent's pipe file descriptors.

This allows the parent and child to use the same pipe for communication.

### 5. Closing Unused Pipe Ends

Since this program uses a pipe for one-way communication, each process closes the end it does not need.

- The parent closes the read end because it sends the message.
- The child closes the write end because it receives the message.

Closing unused pipe ends is important for proper resource management and helps ensure that readers can detect the end of the data stream when all write ends are closed.

### 6. read() and write()

These system calls are used to transfer data through the pipe.

- `write()` sends data into the pipe.
- `read()` receives data from the pipe.

A blocking `read()` waits when no data is available and the pipe is still open for writing. This allows the child to wait for the parent to send the message.

### 7. wait()

The `wait()` system call allows the parent process to wait for its child process to finish.

I learned that waiting for the child helps the parent manage process execution and prevents the child from becoming a zombie while the parent remains alive without collecting its exit status.

### 8. Null Terminator (\0)

In C, strings end with a null terminator (`\0`).

When sending a string through a pipe, the program must ensure that the receiving process has a properly terminated string before printing it with functions such as `printf()`.

### 9. Parent and Child Processes

The parent and child are separate processes with different process IDs and separate address spaces.

In this lab, the pipe provides a communication channel between them.

---

## How the Program Works

The program demonstrates communication between a parent process and a child process.

The execution follows these steps:

1. The program starts as a single process.
2. The program creates a pipe using `pipe()`.
3. It calls `fork()` to create a child process.
4. The child closes the unused write end of the pipe and waits to receive data.
5. The parent closes the unused read end and writes a message into the pipe.
6. The child reads the message and displays it on the terminal.
7. The parent waits for the child to finish.
8. Both processes terminate.

### Communication Flow

```text
       PARENT PROCESS                    CHILD PROCESS
          (Sender)                         (Receiver)

       write(fd[1])
             |
             v
       +-------------+
       |    PIPE     |
       |  FIFO Data  |
       +-------------+
             |
             v
          read(fd[0])
             |
             v
      Display the Message
```

This practical helped me understand how processes can exchange information without directly sharing their ordinary program memory.

---

## Commands I Used

During this lab, I practiced several Ubuntu terminal commands to set up the environment, inspect the source code, compile the program, and execute it.

### 1. Setting Up the Environment

First, I updated the package lists and installed the required development tools.

```bash
sudo apt update
sudo apt install build-essential gdb valgrind
gcc --version
```

**What I learned:**

- `sudo apt update` refreshes the package lists.
- `sudo apt install build-essential gdb valgrind` installs the compiler toolchain and debugging tools.
- `gcc --version` verifies that GCC is available.

### 2. Creating the Lab Directory

I created a separate directory for this lab to keep the source code and documentation organized.

```bash
mkdir -p ~/os-labs/lab01-pipe
cd ~/os-labs/lab01-pipe
```

- `mkdir -p` creates the directory if it does not already exist.
- `cd` moves into the lab directory.

### 3. Inspecting and Editing Files

I used the following commands to inspect and edit the source file.

```bash
ls
head -n 3 pipe_demo.c
cat pipe_demo.c
nano pipe_demo.c
```

| Command | Purpose |
|---|---|
| `ls` | Lists files in the current directory. |
| `head -n 3 pipe_demo.c` | Displays the first three lines of the source file. |
| `cat pipe_demo.c` | Displays the file contents. |
| `nano pipe_demo.c` | Opens the file in the Nano text editor. |

I also learned about this command while troubleshooting:

```bash
sed -i '1d' pipe_demo.c
```

It deletes the first line of the file. However, deleting a line is only appropriate when that line actually needs to be removed.

### 4. Compiling and Running the Program

After checking the source file, I compiled and executed the program.

```bash
gcc pipe_demo.c -o pipe_demo
./pipe_demo
```

- The `gcc` command compiles the C source code into an executable named `pipe_demo`.
- The `./pipe_demo` command runs the executable from the current directory.

For additional compiler warnings and debugging information, I can use:

```bash
gcc -Wall -Wextra -g pipe_demo.c -o pipe_demo
```

### 5. Useful Terminal Shortcuts

| Shortcut | Purpose |
|---|---|
| `Ctrl + Shift + C` | Copies selected terminal text. |
| `Ctrl + Shift + V` | Pastes text into the terminal. |
| `Ctrl + O` | Saves a file in Nano. |
| `Ctrl + X` | Exits Nano. |
| `Ctrl + C` | Interrupts a running program or cancels the current terminal input. |

---

## Problems I Faced and Their Solutions

While performing this lab, I encountered several practical issues. These problems helped me understand how to troubleshoot a program instead of simply rerunning commands without checking the cause.

### 1. Unable to Download the Program Provided by My Teacher

**Problem:** After changing my phone, I could not download the source files shared by my teacher.

**Solution:** I needed to obtain the files again, for example by asking my teacher or a classmate to resend them or by accessing the shared files through another available source.

**What I learned:** It is important to keep a copy of the source code on the computer where I will compile and run the program.

### 2. Setting Up the C Programming Environment

**Problem:** I needed to make sure Ubuntu had the tools required to compile and run C programs.

**Solution:** I installed the development tools and checked the compiler version.

```bash
sudo apt update
sudo apt install build-essential gdb valgrind
gcc --version
```

**What I learned:** Before running a C program, I should verify that the compiler is installed correctly.

### 3. Copying Terminal Output

**Problem:** I initially tried using `Ctrl + C` to copy terminal output, but it interrupted the running process instead.

**Solution:** I selected the required text and used `Ctrl + Shift + C` to copy it.

**What I learned:** Terminal shortcuts are different from shortcuts in many text editors and browsers.

### 4. Compilation Error: `unknown type name 'gcc'`

**Problem:** I encountered the following error:

```text
pipe_demo.c:1:1: error: unknown type name 'gcc'
    1 | gcc pipe_demo.c -o pipe_demo
```

**Cause:** I had accidentally placed the compilation command inside the C source file. GCC interpreted the terminal command as C code.

**Solution:** I checked the source file and removed the terminal commands from it. The `.c` file needed to contain C source code, while compilation commands had to be entered in the terminal.

**What I learned:** Compiler errors often help identify exactly what went wrong. Checking the line number and the contents of the file helped me understand the problem.

### 5. Removing the First Line Did Not Solve the Problem

**Problem:** After running the following command:

```bash
sed -i '1d' pipe_demo.c
```

I encountered another error:

```text
pipe_demo.c:1:1: error: expected identifier or '(' before '.' token
    1 | ./pipe_demo
```

**Cause:** The file contained terminal commands instead of C code. Removing the first line exposed another command that the compiler could not understand.

**Solution:** I inspected the file contents and corrected the source file rather than repeatedly deleting lines.

**What I learned:** Before modifying a file, I should check its actual contents using `head` or `cat`. If the source code is missing or incorrect, I should restore the proper C program.

### 6. Unexpected `.^C` in the Terminal

**Problem:** I noticed `.^C` in the terminal while troubleshooting.

**Cause:** A stray character had been entered before `Ctrl + C` was pressed.

**Solution:** I cancelled the incorrect terminal input, returned to the prompt, and entered the correct command.

**What I learned:** `Ctrl + C` interrupts execution or cancels input; it does not repair source code.

### 7. Understanding Parent and Child Execution

**Problem:** I needed to understand why a parent process should wait for its child to finish.

**Solution:** I learned that the parent can use `wait(NULL)` to wait for a child process to terminate.

```c
#include <sys/wait.h>

/* In the parent process, after creating the child: */
wait(NULL);
```

This is an illustrative snippet; it should be placed in the appropriate part of the complete program.

**What I learned:** Process synchronization helps control execution order and allows the parent to collect the child's termination status.

---

## Expected Output

When the program runs successfully, the child process receives the message sent by the parent.

```text
Child received: Hello from parent
```

The exact output depends on the message used in the source code.

---

## What I Learned

By completing this lab under my teacher's guidance and practicing it on Ubuntu, I learned:

- The purpose of inter-process communication (IPC).
- How `pipe()` creates a communication channel.
- How `fork()` creates a child process.
- How parent and child processes use inherited file descriptors.
- The difference between the read end and write end of a pipe.
- How `read()` and `write()` transfer data between processes.
- Why unused pipe ends should be closed.
- How `wait()` helps the parent manage its child process.
- How to compile and run a C program using GCC.
- How to identify and fix common source-code and terminal errors.

Most importantly, I learned that practical OS labs require both understanding the concept and knowing how to work with the development environment.


## Practice Exercises

The following exercises can help me practice the concepts covered in this lab:

1. Modify the program so that the child sends a reply to the parent using a second pipe.
2. Allow the parent to read a line from the keyboard and send it to the child for processing.
3. Send an integer through the pipe instead of a string.
4. Send multiple messages through the pipe using a loop.

I can save my solutions in a separate `exercises/` directory to keep the original lab program unchanged.

---

## Quick Troubleshooting Guide

| Problem | Possible Cause | Solution |
|---|---|---|
| `gcc: command not found` | GCC is not installed. | Run `sudo apt install build-essential`. |
| `unknown type name 'gcc'` | A terminal command was placed inside the C file. | Remove the command and restore the correct C source code. |
| `expected identifier or '('` | The source file contains invalid C syntax. | Inspect the file using `head` or `cat`. |
| `No such file or directory` | The file or directory name is incorrect. | Check the current directory using `pwd` and list files using `ls`. |
| `Permission denied` | The executable cannot be run as entered or permissions are insufficient. | Check the file and use `./pipe_demo` when appropriate. |
| Child waits for input | No data is available yet, or a pipe end remains open. | Check the parent write operation and close unused pipe ends. |
| Output order is unexpected | Parent and child execution can overlap. | Use appropriate synchronization, such as `wait()`, where required. |

---

## Conclusion

This was my first practical Operating Systems lab, in which I learned how a parent process and a child process communicate through a pipe.

With the concepts explained by my teacher and hands-on practice in Ubuntu, I gained a better understanding of process creation, IPC, file descriptors, and synchronization. Troubleshooting the errors also helped me improve my terminal skills and learn how to debug problems systematically.

I will continue building on these concepts in the upcoming OS labs, covering process management, threads, synchronization, CPU scheduling, memory management, and deadlocks.

**Next Lab:** Process Creation Using `fork()`, `exec()`, and `wait()`.

---

**Created and documented by Javeria Zia**  
*Operating Systems — Practical Lab Series*

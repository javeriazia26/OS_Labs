

# Lab 07: Process Management in Linux Using fork(), exec(), and wait()

**Subject:** Operating Systems  
**Topic:** Process Management  
**Language:** C  
**Environment:** Ubuntu Linux, GCC, and Terminal  
**Program:** `process-management.c`

## Overview

This lab explores process management in Linux using C. Under my teacher's guidance, I studied how processes are created, how a child process can execute another program, and how a parent process waits for its child to finish.

I practiced compiling and executing the program on Ubuntu Linux and observed the behavior of the parent and child processes. The program also demonstrates process-specific variables, execution delays, and checking the child's termination status.

## Table of Contents

- [Objectives](#objectives)
- [Concepts Covered](#concepts-covered)
- [Program Workflow](#program-workflow)
- [Commands Used](#commands-used)
- [Program Output](#program-output)
- [Output Explanation](#output-explanation)
- [Key Takeaways](#key-takeaways)
- [Practice Exercises](#practice-exercises)
- [Conclusion](#conclusion)

---

## Objectives

The objectives of this lab are to:

- Understand process creation using `fork()`.
- Distinguish between parent and child processes.
- Understand how processes maintain separate copies of variables.
- Learn how `execlp()` executes another program.
- Understand how `sleep()` pauses process execution.
- Learn how `wait()` synchronizes the parent with its child.
- Check process termination status using status macros.
- Practice compiling and executing C programs in Linux.

## Concepts Covered

### 1. Process Creation Using `fork()`

The `fork()` system call creates a new process called the child process.

After a successful call, both parent and child continue execution from the point where `fork()` returns.

The return value helps distinguish the processes:

- A negative value indicates failure.
- `0` indicates execution in the child process.
- A positive value in the parent represents the child's process ID (PID).

### 2. Parent and Child Processes

The parent and child execute independently after `fork()`.

In this program, the initial variable is:

```c
int x = 5;
```

The child changes its copy of `x` to `15`, while the parent changes its copy to `3`.

The output demonstrates that the changes made by one process do not modify the other process's ordinary variable.

### 3. Executing Another Program Using `execlp()`

The `execlp()` function replaces the current process image with another program.

The program uses:

```c
execlp("ls", "ls", "-l", (char *)NULL);
```

This executes the `ls -l` command, which displays files and their details in the current directory.

If `execlp()` succeeds, it does not return to the original program. If it fails, execution continues to the error-handling code.

### 4. Pausing Execution Using `sleep()`

The `sleep()` function pauses the calling process for the specified number of seconds.

```c
sleep(3);
```

In this program, the child pauses for three seconds before executing `ls -l`.

### 5. Synchronization Using `wait()`

The `wait()` system call allows the parent process to wait until one of its child processes terminates.

```c
wait(&status);
```

The program checks the return value of `wait()` before examining the child's termination status.

### 6. Checking Process Termination Status

The program uses status macros to determine how the child process ended.

- `WIFEXITED(status)` checks whether the child terminated normally.
- `WEXITSTATUS(status)` retrieves the child's exit status after normal termination.
- `WIFSIGNALED(status)` checks whether the child terminated because of a signal.
- `WTERMSIG(status)` identifies the signal that terminated the child.

In the observed execution, the child exited normally with status `0`, indicating successful completion of the executed command.

---

## Program Workflow

The program follows these steps:

1. Initializes the variable `x` to `5`.
2. Calls `fork()` to create a child process.
3. The parent changes its copy of `x` to `3`.
4. The child changes its copy of `x` to `15`.
5. The child waits for three seconds using `sleep()`.
6. The child executes `ls -l` using `execlp()`.
7. The parent waits for the child using `wait()`.
8. The parent checks and displays the child's termination status.

### Process Flow

```text
             Start
               |
         Initialize x = 5
               |
             fork()
            /      \
           /        \
      Parent        Child
        |              |
      x = 3          x = 15
        |              |
      wait()         sleep(3)
        |              |
        |           execlp()
        |              |
        |            ls -l
        |              |
        +------ Wait for child
                       |
              Check exit status
                       |
                      End
```

The exact order of printed messages may vary because parent and child processes execute independently.

---

## Commands Used

### 1. Navigate to the Lab Directory

```bash
cd ~/os-labs/lab07-process-management
```

### 2. Compile the Program

```bash
gcc process-management.c -o process-management
```

This command compiles the C source file and creates an executable named `process-management`.

For additional compiler warnings, use:

```bash
gcc -Wall -Wextra -g process-management.c -o process-management
```

### 3. Execute the Program

```bash
./process-management
```

The `./` prefix runs the executable from the current directory.

### 4. List Files in the Current Directory

The child executes:

```bash
ls -l
```

This displays the files and their details, including permissions, ownership, file sizes, and modification times.

---

## Program Output

The following output was observed during execution:

```text
Parent process: x = 3
Parent process: waiting for child...
Child process: x = 15
Child process: executing ls -l
total 20
-rwxrwxr-x 1 javeria-zia javeria-zia 16312 Oct 26 14:46 process-management
-rw-rw-r-- 1 javeria-zia javeria-zia  1238 Oct 26 14:45 process-management.c
Child exited normally with status: 0
```

File sizes, permissions, timestamps, and directory contents may differ on another system or during another execution.

## Output Explanation

### Parent Process

```text
Parent process: x = 3
Parent process: waiting for child...
```

The parent changes its copy of `x` to `3` and waits for the child process to terminate.

### Child Process

```text
Child process: x = 15
Child process: executing ls -l
```

The child changes its copy of `x` to `15`, pauses for three seconds, and then executes `ls -l`.

### Directory Listing

The `ls -l` command displays the files in the lab directory, including the compiled executable and the C source file.

### Child Termination Status

```text
Child exited normally with status: 0
```

This confirms that the child terminated normally and returned exit status `0`.

---

## Key Takeaways

Through this lab, I learned that:

- `fork()` creates a child process.
- Parent and child processes have separate copies of ordinary variables.
- `execlp()` replaces the current process image with another program.
- `sleep()` pauses the calling process.
- `wait()` allows the parent to wait for a child process to terminate.
- `WIFEXITED()` and `WEXITSTATUS()` help inspect normal termination.
- `WIFSIGNALED()` and `WTERMSIG()` help identify signal-based termination.
- `ls -l` displays detailed directory information.
- Process scheduling can affect the order of output.

## Practice Exercises

1. Change the initial value of `x` and observe the parent and child values.
2. Change the child's delay from three seconds to five seconds.
3. Replace `ls -l` with another command using `execlp()`.
4. Temporarily use an invalid command and observe how the program handles `execlp()` failure.
5. Add the child's PID and the parent's PID to the output using `getpid()` and `getppid()`.
6. Investigate how a parent can send a signal to a child using `kill()` and `SIGTERM`.

## Conclusion

This lab introduced process management in Linux through process creation, program execution, and parent-child synchronization.

By compiling and running the program, I observed how `fork()` creates separate processes, how `execlp()` runs another program in the child process, and how `wait()` allows the parent to collect the child's termination status.

These concepts provide a foundation for understanding process control and synchronization in Operating Systems.

---

**Documented by Javeria Zia**  
*Operating Systems — Practical Lab Series*

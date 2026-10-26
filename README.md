
# OS_Labs

A beginner-friendly collection of hands-on Operating Systems labs written in C for Ubuntu Linux. This repository documents my practical learning journey through core Operating Systems concepts, including process management, inter-process communication (IPC), blocking and non-blocking operations, and shared memory.

Each lab includes concept explanations, compilation and execution commands, program output, troubleshooting notes, key takeaways, and practice exercises where applicable. The programs are practiced and documented under my teacher's guidance.

## Table of Contents

- [Lab Index](#lab-index)
- [Prerequisites](#prerequisites)
- [Environment Setup](#environment-setup)
- [Basic Workflow for Every Lab](#basic-workflow-for-every-lab)
- [Essential Terminal Commands](#essential-terminal-commands)
- [Lessons Learned](#lessons-learned)
- [Repository Structure](#repository-structure)
- [Credits](#credits)

## Lab Index

| Lab | Topic | Main Concepts | Status |
|---|---|---|---|
| Lab 01 | Inter-Process Communication Using Pipes | `pipe()`, `fork()`, `read()`, `write()` | Completed |
| Lab 02 | Inter-Process Communication Using System V Message Queues | `ftok()`, `msgget()`, `msgsnd()`, `msgrcv()`, `msgctl()` | Completed |
| Lab 03 | Blocking and Non-Blocking Pipe Operations | Blocking reads, `fcntl()`, `O_NONBLOCK` | Completed |
| Lab 04 | Inter-Process Communication Using Shared Memory | `shmget()`, `shmat()`, shared memory, send-by-reference | Completed |
| Lab 05 | Message Buffers and Pipe Communication | Message structures, character buffers, `read()`, `write()` | Practiced |
| Lab 06 | Blocking and Non-Blocking System V Message Queue Operations | `msgsnd()`, `IPC_NOWAIT`, queue limits | Practiced |
| Lab 07 | Process Management in Linux | `fork()`, `execlp()`, `wait()`, process exit status | Practiced |

**Status guide:**
- **Completed:** The lab has been practiced and documented.
- **Practiced:** The program has been run or studied, and its documentation may still need finalization.
- **Planned:** The lab has not yet been completed.

## Prerequisites

Before starting these labs, make sure you have:

- Ubuntu Linux or WSL (Windows Subsystem for Linux).
- GCC compiler.
- Basic knowledge of C programming, including variables, functions, loops, and arrays.
- Basic familiarity with terminal commands.

## Environment Setup

### 1. Update Package Lists

```bash
sudo apt update
```

### 2. Install Required Tools

```bash
sudo apt install build-essential gdb valgrind
```

These packages provide the following tools:

- **build-essential:** Installs GCC, Make, and essential development tools and libraries.
- **GDB:** A debugger for identifying and troubleshooting program errors.
- **Valgrind:** Helps detect memory errors and memory leaks.

### 3. Verify the GCC Installation

```bash
gcc --version
```

If GCC is installed correctly, this command displays its version information.

## Basic Workflow for Every Lab

Follow these steps whenever you work on a lab.

### 1. Navigate to the Lab Directory

```bash
cd ~/os-labs/labXX-name
```

Replace `labXX-name` with the actual directory name of the lab.

### 2. List the Files

```bash
ls -l
```

This displays the files and their details in the current directory.

### 3. Check the Source Code

```bash
head -n 3 program.c
```

This displays the first three lines of the C source file.

### 4. Compile the Program

```bash
gcc -Wall -Wextra -g program.c -o program
```

This compiles `program.c`, enables additional compiler warnings, includes debugging information, and creates an executable named `program`.

For programs that use POSIX threads, use the `-pthread` option:

```bash
gcc -Wall -Wextra -g program.c -o program -pthread
```

### 5. Run the Program

```bash
./program
```

Observe the output and experiment with the code to understand the underlying Operating Systems concept.

## Essential Terminal Commands

| Command | Purpose |
|---|---|
| `pwd` | Displays the current working directory. |
| `ls` | Lists files and directories. |
| `cd folder` | Changes the current directory. |
| `mkdir -p path` | Creates a directory, including missing parent directories. |
| `touch file` | Creates an empty file if it does not exist. |
| `nano file.c` | Opens a file in the Nano text editor. |
| `cat file.c` | Displays the contents of a file. |
| `head -n 3 file.c` | Displays the first three lines of a file. |
| `gcc file.c -o program` | Compiles a C source file. |
| `./program` | Executes the compiled program. |
| `ipcs -q` | Lists System V message queues. |
| `ipcrm -q <msqid>` | Removes a specified System V message queue. |

### Useful Terminal Shortcuts

- **Ctrl + Shift + C:** Copy selected terminal text.
- **Ctrl + Shift + V:** Paste text into the terminal.
- **Ctrl + O:** Save a file in Nano.
- **Enter:** Confirm the filename when saving in Nano.
- **Ctrl + X:** Exit Nano.
- **Ctrl + C:** Interrupt a running terminal process.

## Lessons Learned

These are important lessons from my practical work:

1. **Keep source code and terminal commands separate.** C code belongs in `.c` files, while compilation and execution commands belong in the terminal.
2. **Read compiler errors carefully.** They often identify the file, line number, and type of error.
3. **Verify file contents when something goes wrong.** Use `cat` or `head` to inspect a source file.
4. **Understand commands before using them.** For example, `Ctrl + C` interrupts a running process.
5. **Compile and test programs.** Observe the output and investigate unexpected behavior.
6. **Understand IPC mechanisms.** Pipes, message queues, and shared memory provide different ways for processes to exchange data.
7. **Understand blocking behavior.** Blocking operations may wait for data or resources, while non-blocking operations can return without waiting.
8. **Practice troubleshooting.** Errors and unexpected results are opportunities to improve practical understanding.

## Repository Structure

```text
os-labs/
├── README.md
├── lab01-pipe/
│   ├── README.md
│   └── pipe_demo.c
├── lab02-message-queues/
│   ├── README.md
│   └── msg_queue.c
├── lab03-blocking-non-blocking/
│   ├── README.md
│   └── blocking-non-blocking.c
├── lab04-shared-memory/
│   ├── README.md
│   └── shared-memory.c
├── lab05-message-buffer/
│   ├── README.md
│   └── message-buffer.c
├── lab06-message-queue-blocking/
│   ├── README.md
│   └── message-queue-blocking.c
├── lab07-process-management/
│   ├── README.md
│   └── process-management.c
```

*Note: The structure above reflects the lab names used in this documentation. Update filenames and folder names if your local repository uses different names. Planned labs may not have source files or README files yet.*

### Lab Documentation Format

Each lab's README aims to include:

- **Overview:** What the lab demonstrates.
- **Objectives:** What the lab is intended to teach.
- **Concepts Covered:** The OS concepts and system calls studied.
- **Program Workflow:** How the program operates.
- **Commands Used:** Compilation, execution, and inspection commands.
- **Program Output:** The output observed during practice.
- **Troubleshooting:** Common errors and possible solutions.
- **Key Takeaways:** Important lessons from the lab.
- **Experiments and Exercises:** Suggestions for further practice.

## Credits

Created and documented by **Javeria Zia**.

This repository represents my practical learning journey through Operating Systems concepts using C programming and Ubuntu Linux. With my teacher's guidance, I practice programs, observe their behavior, troubleshoot errors, and document what I learn.

---

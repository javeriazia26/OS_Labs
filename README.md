
# OS_Labs

A beginner-friendly collection of hands-on Operating Systems labs written in C for Ubuntu Linux. Each lab demonstrates a core Operating Systems (OS) concept, such as process management, inter-process communication (IPC), threads, CPU scheduling, and memory management, through practical programs.

Each lab includes explanations of the concepts, compilation and execution commands, common errors, step-by-step troubleshooting, key takeaways, and exercises to reinforce learning.

## Table of Contents

- [Lab Index](#lab-index)
- [Prerequisites](#prerequisites)
- [Environment Setup](#environment-setup)
- [Basic Workflow for Every Lab](#basic-workflow-for-every-lab)
- [Essential Terminal Commands](#essential-terminal-commands)
- [Golden Rules I Learned](#golden-rules-i-learned)
- [Repository Structure](#repository-structure)
- [Credits](#credits)

## Lab Index

| Lab | Topic | Concepts Covered | Status |
|---|---|---|---|
| Lab 01 | Parent-Child Communication Using Pipes | `pipe()`, `fork()`, blocking reads, IPC | Completed |
| Lab 02 | Process Creation | `fork()`, `exec()`, `wait()` | Planned |
| Lab 03 | Threads | `pthread_create()`, `pthread_join()` | Planned |
| Lab 04 | Race Conditions | Mutexes, critical sections, synchronization | Planned |
| Lab 05 | Semaphores | Producer-Consumer Problem, synchronization | Planned |
| Lab 06 | CPU Scheduling | FCFS, SJF, Round Robin | Planned |
| Lab 07 | Memory Management | Memory allocation, page replacement algorithms | Planned |
| Lab 08 | Deadlock | Deadlock prevention, avoidance, Banker's Algorithm | Planned |

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
ls
```

This displays the files in the current directory.

### 3. Check the Source Code

```bash
head -n 3 program.c
```

This displays the first three lines of the C source file so you can verify that it contains the expected code.

### 4. Compile the Program

```bash
gcc program.c -o program
```

This compiles `program.c` and creates an executable named `program`.

For programs that use POSIX threads, compile with the `-pthread` option:

```bash
gcc program.c -o program -pthread
```

### 5. Run the Program

```bash
./program
```

Observe the output and experiment with the code to understand the underlying OS concept.

## Essential Terminal Commands

| Command | Purpose |
|---|---|
| `pwd` | Displays the current working directory. |
| `ls` | Lists files and directories. |
| `cd folder` | Changes the current directory. |
| `mkdir -p path` | Creates a directory, including any missing parent directories. |
| `nano file.c` | Opens a file in the Nano text editor. |
| `cat file.c` | Displays the contents of a file. |
| `head -n 3 file.c` | Displays the first three lines of a file. |
| `gcc file.c -o program` | Compiles a C source file into an executable. |
| `./program` | Executes the compiled program. |

### Useful Terminal Shortcuts

- **Ctrl + Shift + C:** Copy selected terminal text.
- **Ctrl + Shift + V:** Paste text into the terminal.
- **Ctrl + O:** Save a file in Nano.
- **Enter:** Confirm the filename when saving in Nano.
- **Ctrl + X:** Exit Nano.
- **Ctrl + C:** Interrupt a running terminal process.

## Golden Rules I Learned

These are some important lessons I learned while working on Operating Systems labs:

1. **Code goes inside the source file; commands go in the terminal.** Do not paste terminal commands into a C source file.
2. **Read compiler errors carefully.** They usually indicate the file, line number, and type of error.
3. **Check file contents when something goes wrong.** Use `cat` or `head` to verify that the file contains the expected code.
4. **Understand what a command does before using it.** For example, `Ctrl + C` interrupts a running process; it does not fix program errors.
5. **Compile, run, experiment, and debug.** Change the code, observe the results, and fix any errors to strengthen your understanding.
6. **Learn by experimenting.** Try different inputs and scenarios to see how operating system concepts behave in practice.

## Repository Structure

```text
os-labs/
├── README.md
├── setup/
│   └── README.md
├── lab01-pipe/
│   ├── README.md
│   └── pipe_demo.c
├── lab02-fork-exec-wait/
│   ├── README.md
│   └── process_demo.c
├── lab03-threads/
├── lab04-race-conditions/
├── lab05-semaphores/
├── lab06-cpu-scheduling/
├── lab07-memory-management/
└── lab08-deadlock/
```

*Note: This structure illustrates the planned organization. Add source files and README files as each lab is implemented.*

### Lab Documentation Format

Each lab's README follows a consistent structure:

- **Goal:** What the lab demonstrates.
- **Concepts Learned:** The OS concepts and system calls covered.
- **Commands Used:** Compilation and execution commands.
- **Hurdles and Fixes:** Common errors and their solutions.
- **Key Takeaways:** Important lessons from the lab.
- **Experiments:** Suggested modifications to the program.
- **Exercises:** Practice tasks to reinforce understanding.

## Credits

Created and documented by **Javeria Zia**.

This repository is a practical learning journey through Operating Systems concepts using C programming and Ubuntu Linux. The labs are designed to help beginners build their understanding through hands-on experimentation, debugging, and documentation.

# OS_Labs
beginner-friendly collection of hands-on Operating Systems labs written in C for Ubuntu. Each lab turns a core OS concept (processes, pipes, threads, scheduling, memory) into a program you can compile and run, with explanations of the concepts, the commands used, common errors, and step-by-step fixes.


---

## Table of Contents

- [Lab Index](#lab-index)
- [Prerequisites](#prerequisites)
- [Environment Setup](#environment-setup)
- [Basic Workflow for Every Lab](#basic-workflow-for-every-lab)
- [Essential Terminal Commands](#essential-terminal-commands)
- [Hurdles Faced So Far](#hurdles-faced-so-far)
- [Golden Rules I Learned](#golden-rules-i-learned)
- [Repository Structure](#repository-structure)
- [Credits](#credits)

---

## Lab Index

| Lab | Topic | Concepts | Status |
|-----|-------|----------|--------|
| [Lab 01](lab01-pipe/) | Parent-child communication with pipes | pipe, fork, blocking read, IPC | Done |
| Lab 02 | Process creation | fork, exec, wait | Planned |
| Lab 03 | Threads | pthread create and join | Planned |
| Lab 04 | Race conditions | mutexes, critical sections | Planned |
| Lab 05 | Semaphores | producer-consumer | Planned |
| Lab 06 | CPU scheduling | FCFS, SJF, Round Robin | Planned |
| Lab 07 | Memory management | allocation, page replacement | Planned |
| Lab 08 | Deadlock | Banker's algorithm | Planned |

---

## Prerequisites

- Ubuntu (or WSL on Windows)
- `gcc` compiler
- Basic C (variables, functions, arrays)
- Basic terminal use

---

## Environment Setup

```bash
sudo apt update
sudo apt install build-essential gdb valgrind
gcc --version
```

- `build-essential` gives `gcc`, `make`, and the C headers
- `gdb` is the debugger
- `valgrind` finds memory errors
- `gcc --version` confirms the install worked

---

## Basic Workflow for Every Lab

```bash
cd ~/os-labs/labXX-name       # go to the lab folder
ls                            # check the files are there
head -3 program.c             # make sure the file starts with real C code
gcc program.c -o program      # compile
./program                     # run
```

For thread labs, add `-pthread` when compiling.

---

## Essential Terminal Commands

| Command | Purpose |
|---------|---------|
| `pwd` | Show the current folder |
| `ls` | List files |
| `cd folder` | Move into a folder |
| `mkdir -p path` | Create a folder (and parents) |
| `nano file` | Edit a file (Ctrl + O, Enter to save, Ctrl + X to exit) |
| `cat file` | Print a file |
| `head -3 file` | Print the first 3 lines of a file |
| `gcc file.c -o name` | Compile |
| `./name` | Run a compiled program |

**Terminal shortcuts:** Ctrl + Shift + C (copy), Ctrl + Shift + V (paste). Plain Ctrl + C **stops** a running program.



## Golden Rules I Learned

1. **Code goes inside the file. Commands go in the terminal.**
2. Read the compiler error. It shows the exact file, line, and text that failed.
3. When stuck, check the file contents first with `head` or `cat`.
4. Do not use Ctrl + C to "fix" things; it only cancels.
5. Run the program, change it, break it, fix it. That is how the concepts stick.

---

## Repository Structure

```
os-labs/
├── README.md
├── setup/
│   └── README.md
├── lab01-pipe/
│   ├── README.md
│   └── pipe_demo.c
├── lab02-fork-exec-wait/
└── ...
```

Each lab README follows the same pattern: goal, concepts learned, commands used, hurdles and fixes, key takeaways, experiments, exercises.

---

## Credits
- Documentation, experiments, and write-ups by *[Javeria Zia]**.

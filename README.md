# Mini-Shell in C 🐚

## Overview
This project is a custom, lightweight Linux Shell (Command Line Interpreter) implemented entirely in C. It was developed as part of the Operating Systems course to demonstrate a deep understanding of process management, system calls, and memory handling in a POSIX environment.

Unlike using high-level wrappers like `system()` or `execvp()`, this shell manually parses the environment variables and manages the execution flow from scratch, providing a true "under the hood" look at how operating systems execute commands.

## Features
* **Dynamic Command Execution:** Supports running standard Linux commands (e.g., `ls`, `pwd`, `cat`).
* **Argument Passing:** Fully supports passing multiple arguments and flags to commands (e.g., `ls -l -a`).
* **Manual PATH Resolution:** Dynamically searches for the executable binary across all directories specified in the system's `$PATH` environment variable.
* **Process Isolation:** Safely spawns child processes for command execution without crashing the main shell environment.
* **Memory Safety:** Implements secure string tokenization and environment variable duplication to prevent segmentation faults and memory corruption.
* **Graceful Exit:** Includes a built-in `leave` command to safely terminate the shell.

## Technical Architecture
The shell operates on an infinite loop, following the classic **Read-Parse-Execute** cycle:
1. **Read:** Catches user input using `fgets()`, safely handling empty spaces and empty inputs (Fail-Fast logic).
2. **Parse:** Tokenizes the command and its arguments into an array of pointers using `strtok()`.
3. **Execute:** * Uses `fork()` to create a child process.
   * The parent process uses `wait()` to pause until the child completes its task.
   * The child process creates a local copy of the `PATH` variable, iterates through the directories, concatenates the command name, and attempts execution using `execv()`.
   * If the command is not found in any directory, the child terminates safely using `exit(1)`.

## System Calls & Libraries Used
* `fork()` - Process creation.
* `wait()` - Process synchronization.
* `execv()` - Program execution (Strictly `execv`, avoiding `execvp` to manually implement path resolution).
* `getenv()` - Environment variable retrieval.
* `strtok()`, `strcpy()`, `strcat()` - String manipulation.

## How to Compile and Run

### Prerequisites
* A Linux/Unix environment (or WSL on Windows).
* GCC Compiler installed.

### Compilation
Open your terminal and compile the code using `gcc`:
```bash
gcc -o minishell shell.c
```

### Execution
Run the compiled binary:
```bash
./minishell
```

## Usage Example
```text
Please put your command: ls -l
total 16
-rwxr-xr-x 1 user user 16384 Apr 14 10:00 minishell
-rw-r--r-- 1 user user  1500 Apr 14 09:55 shell.c

Please put your command: pwd
/home/user/projects/minishell

Please put your command: fakecommand
No such command fakecommand, please try a different command

Please put your command: leave
```

## Author
**Raz Asraf**
B.Sc. Computer Science Student | IT Support Engineer

# UNIX Shell in C++

A custom UNIX Shell built in C++ to understand the internals of command-line interpreters and strengthen UNIX system programming concepts. The shell recreates core functionalities of a UNIX shell using POSIX system calls, including process creation, command execution, file redirection, pipelines, signal handling, and built-in commands.

---

## Features

- Execute Linux commands
- Built-in commands
  - `cd`
  - `pwd`
  - `history`
  - `help`
  - `clear`
  - `exit`
- Custom commands
  - `say`
  - `display`
  - `calendar`
  - `open`
- Input redirection (`<`)
- Output redirection (`>`)
- Append redirection (`>>`)
- Pipeline support (`|`)
- Background process execution (`&`)
- Signal handling (`SIGINT`, `SIGCHLD`)
- Command history

---

## Tech Stack

- **Language:** C++
- **Platform:** Linux / UNIX
- **Concepts:** POSIX System Calls, Process Management, Inter-Process Communication (IPC)

---

## POSIX APIs Used

- `fork()`
- `execvp()`
- `waitpid()`
- `pipe()`
- `dup2()`
- `open()`
- `close()`
- `chdir()`
- `getcwd()`
- `signal()`

---

## Project Structure

```text
UNIX-Shell/
│
├── Makefile
├── README.md
├── .gitignore
│
└── src/
    ├── main.cpp
    ├── parser.cpp
    ├── parser.h
    ├── executor.cpp
    ├── executor.h
    ├── pipeline.cpp
    ├── pipeline.h
    ├── redirect.cpp
    ├── redirect.h
    ├── builtin.cpp
    ├── builtin.h
    ├── history.cpp
    ├── history.h
    ├── signals.cpp
    ├── signals.h
    ├── custom.cpp
    └── custom.h
```

---

## Build

```bash
make
```

or

```bash
g++ -Wall -Wextra -std=c++17 \
src/main.cpp \
src/parser.cpp \
src/executor.cpp \
src/pipeline.cpp \
src/redirect.cpp \
src/history.cpp \
src/builtin.cpp \
src/signals.cpp \
src/custom.cpp \
-o NeoShell
```

---

## Run

```bash
./NeoShell
```

---

## Example Commands

### Execute Commands

```bash
ls -l
pwd
mkdir Demo
```

### Built-in Commands

```bash
cd Documents
history
help
clear
```

### Redirection

```bash
ls > files.txt
cat < files.txt
echo Hello >> files.txt
```

### Pipelines

```bash
cat file.txt | grep error
ls | sort
ps aux | grep chrome
```

### Background Process

```bash
sleep 10 &
```

### Custom Commands

```bash
say Hello World
display notes.txt
calendar 7 2026
open report.pdf
```

---

## Learning Outcomes

This project provided hands-on experience with:

- UNIX Shell Architecture
- Process Creation and Management
- Inter-Process Communication using Pipes
- File Descriptor Manipulation
- Input/Output Redirection
- Signal Handling
- Command Parsing
- Modular Software Design
- POSIX System Programming

---

## Future Improvements

- Tab completion
- Environment variable expansion
- Persistent command history
- Job control (`jobs`, `fg`, `bg`)
- Command aliases
- Auto-complete using `readline`
- Support for quoted strings and escape characters
- Improved error handling

---

## License

This project is intended for educational and learning purposes.

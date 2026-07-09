# unix_shell
# UNIX Shell in C++

A simple UNIX Shell built in C++ to explore how command-line interpreters work internally. This project recreates core shell functionalities using POSIX system calls, providing hands-on experience with process management, command execution, file handling, and inter-process communication.

## Features

* Execute Linux commands
* Built-in commands:

  * `cd`
  * `pwd`
  * `history`
  * `exit`
* Process creation using `fork()`
* Command execution using `execvp()`
* Input redirection (`<`)
* Output redirection (`>`, `>>`)
* Pipeline support (`|`)
* Signal handling (`Ctrl + C`)
* Command history

## Technologies Used

* C++
* POSIX System Calls
* Linux / UNIX Environment

## Project Structure

```
Unix-Shell/
│
├── src/
│   ├── main.cpp
│   ├── parser.cpp
│   ├── parser.h
│   ├── executor.cpp
│   ├── executor.h
│   ├── builtin.cpp
│   ├── builtin.h
│   ├── history.cpp
│   ├── history.h
│   ├── redirect.cpp
│   ├── redirect.h
│   ├── pipeline.cpp
│   ├── pipeline.h
│   ├── signals.cpp
│   ├── signals.h
│   ├── custom.cpp
│   └── custom.h
│
├── Makefile
├── README.md
└── .gitignore
```

## Compilation

```bash
g++ shell.cpp -o shell
```

## Running the Shell

```bash
./shell
```

## Example Commands

```bash
pwd

ls -l

cd Desktop

cat file.txt

cat file.txt | grep hello

sort < numbers.txt

ls > output.txt

echo "Hello World" >> output.txt

history

exit
```

## Concepts Covered

* Process Management
* Command Parsing
* File Descriptors
* Input/Output Redirection
* Pipes and Inter-Process Communication
* Signal Handling
* POSIX System Programming

## Future Improvements

* Background process execution (`&`)
* Multiple pipeline support
* Environment variable expansion
* Auto-completion
* Arrow key history navigation
* Job control
* Custom shell prompt

## Learning Outcomes

Building this project provided practical experience with UNIX internals and POSIX APIs, including process creation, command execution, redirection, and signal handling. It also strengthened my understanding of how a shell interacts with the operating system to manage processes and execute user commands.

# Custom Linux Shell in C

A custom POSIX-compliant Linux command-line shell built from scratch in C.

## Features
- Dynamic prompt displaying the current working directory (`getcwd`)
- Command-line string tokenization using `strtok`
- Built-in commands: `cd` (`chdir`) and `exit`
- External binary execution using `fork`, `execvp`, and `wait`

## How to Compile & Run
```bash
gcc myshell.c -o myshell
./myshell
```

# 🐚 MiniShell using C

A **lightweight Unix-like shell application developed** in **C**, designed to execute internal and external commands while demonstrating **Linux Internals, process control, and POSIX system calls.**
This project showcases strong fundamentals in C programming, system-level programming, and operating system concepts.

---

## 🚀 Project Description

The MiniShell application simulates the basic functionality of a Unix shell by accepting user commands, parsing input, and executing them using Linux system calls.
It supports both **internal commands** and **external commands**, providing hands-on exposure to process creation, signal handling, and shell–kernel interaction.

This project was developed as part of the **Linux Internals (LI) module** in the **Embedded Systems Professional Course** at **Emertxe Information Technologies**.

---

## 🎯 Objective

The objective is to understand and use the system calls w.r.t process creation, signal handling, process synchronization, exit status, text parsing etc..

---

## ✨ Features

- Execution of external commands (**e.g., ls, wc, sleep**)
- Built-in internal commands such as **cd, pwd, and exit**
- Command-line input parsing and argument handling
- Process control using **fork(), execvp(), and waitpid()**
- Signal handling using **SIGINT and SIGCHLD**
- Stable shell behavior with proper child process management
---

## 🛠️ Technologies & Concepts Used

- **C Programming**
- **Linux Internals**
- **File I/O (fopen, fread, fwrite)**
- **POSIX System Calls**
- **Process Control (fork, exec, wait)**
- **Signal Handling**
- **Modular Programming**

---

## 🧠 How the Application Works

- The shell displays a prompt and waits for user input
- Input is parsed into commands and arguments
- Internal commands are executed within the shell process
- External commands are executed by creating child processes
- The parent process waits for child completion and handles signals
- Proper signal handling ensures clean process termination
  
---

## 📂 Project Structure

```text
MiniShell/
├── main.c
├── scan_input.c
├── cmd.c
├── header.h
└── ext_cmds.txt
```

---

## ▶️ Compilation and Execution

### Compile and run:
```bash
gcc *.c -o minishell
./minishell
```

## Learning Outcome and Impact

This project strengthened my understanding of **Linux process management, system calls, and shell–kernel interaction**.
It improved my ability to debug system-level programs and gave me confidence in writing robust **low-level C applications**.

---

## Acknowledgment

I would like to sincerely thank Anand Lokhande Sir for his guidance and clear explanation of C programming concepts, which helped me build this project with a strong logical foundation.

---

## GitHub Repository

[https://github.com/Manu-hp1/Minishell]

---

## About Me

I am an Embedded Systems Trainee at Emertxe Information Technologies, building strong fundamentals in C programming, Linux, and system-level concepts. I am passionate about writing clean code and continuously improving my technical skills.

---

## License

This project is developed for learning and educational purposes.


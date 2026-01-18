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

- MP3 files are opened in binary mode
- ID3 header and frames are parsed using file offsets
- Metadata values are extracted and displayed to the user
- For editing, selected tag frames are updated safely
- Audio data remains untouched during metadata modification
- Separate modules handle reading and editing operations

---

## 📂 Project Structure

```text
MP3-Tag-Reader/
├── main.c
├── view.c
├── view.h
├── edit.c
├── edit.h
├── version.c
├── version.h
├── type.h
└── sample.mp3

```

---

## ▶️ Compilation and Execution

### Compile and run:
```bash
gcc *.c -o mp3_tag
./mp3_tag -v sample.mp3
./mp3_tag -e sample.mp3
```

## Learning Outcome and Impact

This project strengthened my understanding of **binary file formats, metadata parsing, and structured file manipulation.**
It improved my debugging skills and confidence in working with **low-level file operations** while ensuring data integrity.

---

## Acknowledgment

I would like to sincerely thank Anand Lokhande Sir for his guidance and clear explanation of C programming concepts, which helped me build this project with a strong logical foundation.

---

## GitHub Repository

[https://github.com/Manu-hp1/MP3-Tag-Reader-and-Editor]

---

## About Me

I am an Embedded Systems Trainee at Emertxe Information Technologies, building strong fundamentals in C programming, Linux, and system-level concepts. I am passionate about writing clean code and continuously improving my technical skills.

---

## License

This project is developed for learning and educational purposes.


#ifndef MAIN_H // If not defined MAIN_H, include the following
#define MAIN_H // Define MAIN_H to prevent multiple inclusions

#include <stdio.h> // Header file for standard input and output functions like printf, scanf
#include <string.h> // Header file for string manipulation functions like strcpy, strcmp
#include <stdlib.h> // Header file for standard library functions like exit, getenv
#include <stdio_ext.h> // Header file for GNU extensions to standard I/O functions like __fpurge
#include <sys/types.h> // Header file for data types used in system calls like pid_t
#include <sys/stat.h> // Header file for data returned by the stat() function like file information
#include <fcntl.h> // Header file for file control options like open, O_RDONLY
#include <unistd.h> // Header file for POSIX operating system API functions like fork, execvp
#include <signal.h> // Header file for signal handling functions like signal, SIGINT
#include <sys/wait.h> // Header file for waiting functions like wait, waitpid


#define BUILTIN	1 // Macro for buitl-in commands
#define EXTERNAL 2 // Macro for external commands
#define NO_COMMAND 3 // Macro for neither built-in nor external commands

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct stop // Structure to store stopped process information
{
	int spid; // Stopped process ID
	char name[15]; // Stopped process name
};

/* Function to scan and process user input */
void scan_input(char *prompt, char *input_string);

/* Function to get command from input string -> ex: "ls -l" -> "ls" */
char *get_command(char *input_string);

/* Function to copy and change prompt */
void copy_change(char *prompt, char *input_string);

/* Function to check command type: BUILTIN, EXTERNAL, or NO_COMMAND */
int check_command_type(char *command);

/* Function to implement echo command */
void echo(char *input_string, int status);

/* Function to execute internal commands */
void execute_internal_commands(char *input_string);

/* Function to execute external commands */
void execute_external_commands(char *input_string);

/* Function to handle signals */
void signal_handler(int sig_num);

/* Function to extract external commands from file */
void extract_external_commands(char **external_commands);

#endif

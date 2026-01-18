#include <stdio.h> // Header file for standard input and output functions like printf, scanf
#include <stdlib.h> // Header file for standard library functions like exit, getenv
#include "header.h" // Header file for standard library functions like exit, getenv

struct stop arr[50]; // Array to store stopped processes
extern char prompt[25]; // External variable for shell prompt
extern char input_string[1024]; // External variable for input string
extern char *external_commands[155]; // External array for external commands
int status; // Variable to store status of child processes
int ind = 0; // Index for stopped processes array
pid_t pid = 0; // Variable to store process ID
char *cmd;

void copy_change(char *prompt, char *input_string) // Function to copy and change prompt
{
	if(input_string[4] != ' ') // Validate new prompt
	{
		strcpy(prompt, input_string + 4); // Update the prompt
	}
	else
	{
		printf("\033[1;91mError: \033[1;97mPS1=NEW_PROMPT\n");
	}
}

void echo(char *input_string, int status) // Function to handle special commands
{
	if (strcmp(input_string, "echo $$") == 0) // Check for "echo $$" command
	{
		printf("%d\n", getpid()); // Print process ID of the shell
	}
	else if (strcmp(input_string, "echo $?") == 0) // Check for "echo $?" command
	{
		printf("%d\n", WEXITSTATUS(status)); // Print exit status of last command
	}
	else if (strcmp(input_string, "echo $SHELL") == 0) // Check for "echo $SHELL" command
	{
		printf("%s\n", getenv("SHELL")); // Print the SHELL environment variable
	}
}

void signal_handler(int sig_num) // Function to handle signals
{
	if(sig_num == SIGINT) // Handle SIGINT (Ctrl+C)
	{
		if (pid == 0)
		{
			printf("\n");
			printf("\033[1;92m%s\033[1;97m", prompt); // Reprint the prompt
			fflush(stdout);
		}

	}
	else if (sig_num == SIGTSTP) // Handle SIGTSTP (Ctrl+Z)
	{
		if (pid == 0) // If no child process is running
		{
			printf("\n");
			printf("\033[1;92m%s\033[1;97m", prompt); // Reprint the prompt
			fflush(stdout);
		}
		else if (pid > 0) // If a child process is running
		{
			arr[ind].spid = pid; // Store the stopped process ID
			strcpy(arr[ind].name, input_string); // Store the stopped process name
			ind++; // Increment the index for stopped processes
		}
	}
	else if (sig_num == SIGCHLD) // Handle SIGCHLD (Child process status change)
	{
		waitpid(-1, &status, WNOHANG); // wait for any child process without blocking
	}

}

void execute_internal_commands(char *input_string) // Function to execute internal commands
{
	char buf[50]; // Buffer to store current working directory
	int flag = 0; // flag used to track the stopped processes

	if (strcmp( input_string, "exit") == 0) // Check for "exit" command
	{
		free(cmd);
		printf("Exiting.....");
		usleep(100000);
		printf("See..u..next..time \U0001F44B\n");
		usleep(100000);
		exit(0);
	}
	else if (strcmp( input_string, "pwd") == 0) // Check for "pwd" command
	{
		getcwd( buf, 50); // To get current working directory, works same as pwd
		printf("%s\n", buf); // Print path of curren working directory
	}
	else if (strncmp(input_string, "cd" , 2) == 0) // Check for "cd" command
	{
		chdir( input_string + 3); // To change directory

		getcwd( buf, 50); // To know whether the directory is changed or not
		printf("%s\n", buf); // Print path of curren working directory
	}
	else if (strncmp(input_string, "echo", 4) == 0) // Check for "echo" command
	{
		echo(input_string, status); // Execute echo function
	}
	else if (strcmp( input_string, "jobs") == 0) // Check for "jobs" command
	{
		for(int i = 0; i < ind; i++)
		{
			printf("%s\n", arr[i].name); // Print the names of stopped processes
		}
	}
	else if (strcmp( input_string, "fg") == 0) // Check for "fg" command
	{
		flag = ind;
		if(flag != 0)
		{
			kill(arr[ind - 1].spid, SIGCONT); // Continue the stopped process
			waitpid(arr[ind - 1].spid, &status, WUNTRACED);// Wait for the process to finish or stop
			ind--; // Decrement the index for stopped processes
		}
		else
		{
			printf("-bash: fg: current: no such job\n");
		}
	}
	else if (strcmp( input_string, "bg") == 0) // Check for "bg" command
	{
		flag = ind;
		if(flag != 0)
		{
			signal(SIGCHLD, signal_handler); // Regiter SIGCHLD handler
			kill(arr[ind - 1].spid, SIGCONT); // Continue the stopped process in the background
			ind--; // Decrement the index for stopped processes
		}
		else
		{
			printf("-bash: bg: current: no such job\n");
		}
	}
}

void execute_external_commands(char *input_string) // Function to execute external commands
{
	char *argv[50]; // Array to store command arguments
	int i = 0; // Index for argv[]
	int pi = 0, argc = 0; // pi: pipe count, argc: argument count

	argv[i] = strtok(input_string, " "); // Tokenize input string into argv[]
	while (argv[i] != NULL) // Loop through tokens
	{
		argc++; // Increment argument count
		if (strcmp(argv[i], "|") == 0) // Check for pipe symbol
		{
			pi++; // Increment pipe count
		}
		i++;
		argv[i] = strtok(NULL, " "); // Get next token
	}
	if (pi == 0) // If no pipes are present
	{
		execvp(argv[0], argv); // Execute the command
		printf("\033[1;91mexecvp failed\033[1;97m: command \"%s\" not found\n", argv[0]);
		exit(1); // Exit if execvp fails
	}
	else
	{
		int cmd_count = 0;   // Number of commands
		int cmd_start[argc]; // starting index of each command
		int pipe_count = 0;  // Number of pipes

		cmd_start[cmd_count++] = 0; // First command starts at index 1

		for (int i = 0; i < argc; i++) // Loop through arguments to find pipes
		{
			if (strcmp(argv[i], "|") == 0) // Check for pipe symbol
			{
				argv[i] = NULL;                 // Replace pipe with NULL to separate commands
				cmd_start[cmd_count++] = i + 1; // Next command starts after the pipe
				pipe_count++;                   // Increment pipe count
			}
		}
		if(cmd_count != pipe_count + 1)
		{
			printf("Invalid pipe operation\n");
			return;
		}

		int fd[2];                            // File descriptors for the pipe
		for (int i = 0; i <= pipe_count; i++) // Loop through each command
		{
			if (i != pipe_count) // Create pipe for all but the last command
			{
				if (pipe(fd) == -1) // Create the pipe
				{
					perror("Pipe failed"); // Print error message
					exit(1);               // Exit with error code
				}
			}
			int pid = fork(); // Create a new process
			if (pid > 0)      // Parent process
			{
				if (i != pipe_count) // If not last command, close write end of pipe
				{
					dup2(fd[0], 0); // Redirect stdin to read end of pipe
					close(fd[0]);   // Close read end of pipe
					close(fd[1]);   // Close write end of pipe
				}
			}
			else if (pid == 0) // Child process
			{
				if (i != pipe_count) // If not last command, set up write end of pipe
				{
					dup2(fd[1], 1); // Redirect stdout to write end of pipe
					close(fd[0]);   // Close read end of pipe
				}
				execvp(argv[cmd_start[i]], argv + cmd_start[i]); // Execute command
				printf("\033[1;91mexecvp failed\033[1;97m: command \"%s\" not found\n", argv[cmd_start[i]]);
				exit(1); // Exit if execvp fails
			}
		}

		close(fd[0]); // Close read end of pipe
		close(fd[1]); // Close write end of pipe

		for (int i = 0; i <= pipe_count; i++) // Parent waits for all children
		{
			wait(NULL); // Wait for child process to finish
		}
	}
}

void scan_input(char *prompt, char *input_string) // Function to scan and process user input
{
	signal( SIGINT, signal_handler); // Register SIGINT handler
	signal( SIGTSTP, signal_handler); // Register SIGTSTP handler
	extract_external_commands(external_commands); // Function to extract external commands
	while(1) // Infinite loop to continuously scan input
	{
		printf("\033[1;92m%s\033[1;97m", prompt); // Print the shell prompt
		scanf("%[^\n]", input_string); // Scan input string until newline
		getchar();
		if(strncmp(input_string, "PS1=", 4) == 0) // Check for prompt change command
		{
			copy_change(prompt, input_string); // Change the prompt
		}
		else
		{
			cmd = get_command(input_string); // Extract command from input string, ex: "ls -l" -> "ls"
			int type = check_command_type(cmd); // Check command type: BUILTIN, EXTERNAL, or NO_COMMANAD
			if (type == BUILTIN) //  If command is a built-in command
			{
				execute_internal_commands(input_string); // Execute the built-in command
			}
			else if (type == EXTERNAL) // If command is an external command
			{
				pid = fork(); // Create a new process
				if(pid == 0) // Child process
				{
					signal(SIGINT, SIG_DFL); // Set default SIGINT behaviour
					signal(SIGTSTP, SIG_DFL); // Set default SIGTSTP behaviour
					execute_external_commands(input_string); // Execute the external command
					exit(0); // Exit child process
				}
				else if (pid > 0) // Parent process
				{
					waitpid(pid, &status, WUNTRACED); // Wait for child process to finish or stop
				}

			}
			else
			{
				printf("Command not found!\n"); // Print error message for unknown command
			}

			memset(input_string,'\0',1025); // Clear the input string for the next iteration
		}
	}
}

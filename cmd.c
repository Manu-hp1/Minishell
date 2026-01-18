#include "header.h" // Header file for including project-specific declaration

extern char *external_commands[155]; // External array for external commands

/*List of builtin commands*/
char *builtins[] = {"echo", "jobs", "fg", "bg",  "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval", "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source","exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

char *get_command(char *input_string) // Function to extract command from input string
{
	char *command; // Variable to store the command
	int i = 0; // Index for iterating through input string
	command = malloc(10 * sizeof(char)); // Allocate memory for command
	while(input_string[i] != '\0') // Loop until end of input string
	{
		command[i] = input_string[i]; // Copy character to command
		if(input_string[i] == ' ') // Stop at first space
		{
			command[i] = '\0'; // Store the null character at end of string
			break; // Exit loop because command stored successfully
		}
		i++;
	}
	return command; // Return the extracted command
}

void extract_external_commands(char **external_commands) // Function to extract external commands from file
{
	int fd; // Create a file descriptor
	fd = open("ext_cmds.txt", O_RDONLY); // Open the file containing external command
	char *buf = malloc(10 * sizeof(char));   // buffer for one line

	char ch; // Variable to store each character
	int i = 0; // Index for buffer
	int indx = 0; // Index for external_commands array
	while(read(fd, &ch, 1) > 0) // Read file character by character
	{
		if(ch == '\n') // If newline character is encountered
		{
			buf[i] = '\0'; // Null-terminate the buffer
			external_commands[indx] = malloc(strlen(buf) + 1); // Allocate memory for the command
			strcpy(external_commands[indx++], buf); // Copy buffer to external_commands array
			i = 0; // Reset buffer index
		}
		else
		{
			buf[i++] = ch; // Store character in buffer
		}
	}
	external_commands[indx] = NULL; // Null-terminate the external_commands array
	close(fd); // Close the file descriptor
	// free(buf);
}

int check_command_type(char *command) // Function to check command type: BUILTIN, EXTERNAL, or NO_COMMAND
{
	for(int i = 0; builtins[i] != NULL; i++) // Loop through built-in commands
	{
		if(strcmp(command, builtins[i]) == 0) // Compare with input command
		{
			return BUILTIN; // Return BUILTIN if command found in built-ins
		}
	}
	for(int i = 0; external_commands[i] != NULL; i++) // Loop through external commands
	{
		if(strcmp(command, external_commands[i]) == 0) // Compare with input command
		{

			return EXTERNAL; // Return EXTERNAL if command found in external_commands
		}
	}
	return NO_COMMAND; // Return NO_COMMAND if command not found in built-ins or external_commands
}


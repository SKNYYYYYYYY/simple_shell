#include "main.h"

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 * @env: The environment variables.
 */
void execute_command(char *command, char **env)
{
	pid_t pid;
	char *full_path, *pathname;
	char **args;


	args = split_command(command);
	/*cd command to change directory*/
	if (_strcmp(args[0],"cd") == 0)
	{
		if (args[1] != NULL)
		{
			pathname = args[1];
		    if (chdir(pathname) == 0)
	            printf("%s#\n", args[1]);
		}
		else
		{
			pathname = "/home";
			chdir(pathname);
		}
	}
	
	/*Handling the exit command*/
if (strcmp(args[0], "exit") == 0) {
         handle_exit(args);
         return;
    }
    
    /*to check if the absolute path is specified i.e /bin/ls*/
	if(args[0][0] == '/' || args[0][1] == '/')
	{
		full_path = args[0];
	}
	else
	{
		full_path = find_path(command, env);
		if (full_path == NULL && _strcmp(args[0],"cd") != 0 && _strcmp(args[0],"#") != 0)
		{
			write(STDERR_FILENO, command, _strlen(command));
			write(STDERR_FILENO, ": command not found\n", 21);
			free(args);
			return;
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free(args);
		return;
	}

	if (pid == 0)
	{

		execve(full_path, args, env);
		perror("execve");
		if(full_path != args[0])/*prevents double freeing hence enables executing compiled files more than once*/
			free(full_path);
		free(args);
		exit(1);
	}
	else
	{
		wait(NULL);
		if(full_path != args[0]) /*prevents double freeing hence enables executing compiled files more than once*/
			free(full_path);
		free(args);
	}
}

void handle_exit(char **args) {
char *endptr;
long status;
    if (args[1] == NULL) {
        exit(0);
    } else {
        
        status = strtol(args[1], &endptr, 10);
        
        if (*endptr != '\0' || status < 0 || status > 255) {
            fprintf(stderr, "Exit: Invalid status\n");
            return;
        }
        
        exit((int)status);
    }
}



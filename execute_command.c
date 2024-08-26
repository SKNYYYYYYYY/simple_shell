#include "main.h"

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 * @env: The environment variables.
 */
int execute_command(char *command, char **env)
{
	pid_t pid;
	char *full_path;
	char **args;
	int status = -1;

	args = split_command(command);

	/*Handling the exit command*/
	if (_strcmp(args[0],"exit") == 0)
	{
		free(args);
		exit(EXIT_SUCCESS);
	}

	/*to check if the absolute path is specified i.e /bin/ls*/
	if(args[0][0] == '/' || args[0][1] == '/')
	{
		full_path = args[0];
	}
	else
	{
		full_path = find_path(command, env);
		if (full_path == NULL)
		{
			write(STDERR_FILENO, command, _strlen(command));
			write(STDERR_FILENO, ": command not found\n", 21);
			free(args);
			return (status);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free(args);
		return (status);
	}

	if (pid == 0)
	{
		status = execve(full_path, args, env);
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
	return (status);
}

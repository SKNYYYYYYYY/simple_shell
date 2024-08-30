#include "main.h"

/**
 * handle_cd_command - Handles the 'cd' command.
 * @args: The command arguments.
 */
void handle_cd_command(char **args)
{
	char *pathname;

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

/**
 * handle_exit_command - Handles the 'exit' command.
 * @args: The command arguments.
 */
void handle_exit_command(char **args)
{
	int status = EXIT_SUCCESS;
	int i;

	if (args[1] != NULL)
	{
		status = _atoi(args[1]);
		if (status < 0 || status > 255)
			status = EXIT_SUCCESS;
	}

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
	exit(status);
}

/**
 * get_full_path - Retrieves the full path for a command.
 * @args: The command arguments.
 * @command: The original command string.
 * @env: The environment variables.
 * Return: The full path or NULL if not found.
 */
char *get_full_path(char **args, char *command, char **env)
{
	char *full_path;

	if (args[0][0] == '/' || args[0][1] == '/')
	{
		full_path = args[0];
	}
	else
	{
		full_path = find_path(command, env);
		if (full_path == NULL && _strcmp(args[0], "cd") != 0)
		{
			write(STDERR_FILENO, command, _strlen(command));
			write(STDERR_FILENO, ": command not found\n", 21);
		}
	}
	return (full_path);
}

/**
 * free_resources - Frees allocated resources.
 * @full_path: The full path of the command.
 * @args: The command arguments.
 */
void free_resources(char *full_path, char **args)
{
	if (full_path != args[0])
		free(full_path);
	free(args);
}

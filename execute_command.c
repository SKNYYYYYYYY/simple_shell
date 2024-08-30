#include "main.h"

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 * @env: The environment variables.
 */
void execute_command(char *command, char **env)
{
	pid_t pid;
	char *full_path;
	char **args;

	args = split_command(command);
	if (*args == NULL)
		return;

	if (_strcmp(args[0], "cd") == 0)
	{
		handle_cd_command(args);
		return;
	}

	if (_strcmp(args[0], "exit") == 0)
	{
		handle_exit_command(args);
		return;
	}

	full_path = get_full_path(args, command, env);
	if (full_path == NULL)
	{
		free(args);
		return;
	}

	pid = fork();
	handle_fork(pid, full_path, args, env);
}

/**
 * handle_fork - Handles the fork and execution of a command.
 * @pid: Process ID after fork.
 * @full_path: The full path of the command.
 * @args: The command arguments.
 * @env: The environment variables.
 */
void handle_fork(pid_t pid, char *full_path, char **args, char **env)
{
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
		free_resources(full_path, args);
		exit(1);
	}
	else
	{
		wait(NULL);
		free_resources(full_path, args);
	}
}

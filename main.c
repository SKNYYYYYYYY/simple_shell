#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * print_prompt - Print the shell prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * main - Entry point of the shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 *
 * Return: Always 0
 */
int main(int argc, char **argv, char **env)
{
	char *command = NULL;
	size_t size = 0;
	ssize_t nread;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			print_prompt();
		}
		nread = getline(&command, &size, stdin);
		if (nread == -1)
		{
			free(command);
			if (feof(stdin))
			{
				exit(EXIT_SUCCESS);
			}
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (command[nread - 1] == '\n')
		{
			command[nread - 1] = '\0';
		}
		if (command[0] != '\0')
		{
			execute_command(command, env);
		}
	}
	free(command);
	return (0);
}

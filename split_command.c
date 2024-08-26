#include "main.h"

#define MAX_ARGS 100

/**
 * split_command - Splits a command into arguments.
 * @command: The command to split.
 *
 * Return: An array of arguments.
 */
char **split_command(char *command)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * MAX_ARGS);
	if (args == NULL)
		return (NULL);

	token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}

	args[i] = NULL;
	return (args);
}

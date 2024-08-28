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
	char *token, *comment_start;
	int i = 0;
	
	char command_copy[BUFFER_SIZE];
strncpy(command_copy, command, BUFFER_SIZE - 1);
command_copy[BUFFER_SIZE - 1] = '\0';
comment_start = strchr(command_copy, '#');
	comment_start = strchr(command_copy, '#');
	if (comment_start != NULL)
	{
		if (comment_start == command)
		{
			return NULL;
		}
		*comment_start = '\0'; 
	}

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

char* trim_comment(char* command) {
    char* comment_start = strchr(command, '#');
    if (comment_start != NULL) {
        *comment_start = '\0';
    }
    return command;
}
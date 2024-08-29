#include "main.h"

#define MAX_ARGS 100


/* Function to handle comments */
void comment_handler(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#')
		{
			buffer[i] = '\0';  /*Terminate the string at the first '#'*/
			break;
		}
	}
}


char **split_command(char *command)
{
	char **args;
	char *token;
	int i = 0;
	
	comment_handler(command);
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

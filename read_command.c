#include "main.h"

/**
 * read_command - Reads a command from standard input.
 *
 * Return: The command entered by the user or NULL on failure.
 */
char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = getline(&buffer, &bufsize, stdin);

	if (characters_read == -1)
	{
		free(buffer);
		return (NULL);
	}

	return (buffer);
}

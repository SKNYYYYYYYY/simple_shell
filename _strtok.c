#include "main.h"

/**
 * _strtok - Tokenizes a string
 * @str: The string to tokenize
 * @delim: The delimiter string
 * Return: A pointer to the next token or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *buffer;
	char *token;

	if (str)
		buffer = str;
	else if (!buffer)
		return (NULL);

	/*Skip leading delimiters*/
	while (*buffer && my_strchr(delim, *buffer))
		buffer++;

	if (!*buffer)
		return (NULL);

	token = buffer;

	/*Find the end of the token*/
	while (*buffer && !my_strchr(delim, *buffer))
		buffer++;

	if (*buffer)
	{
		*buffer = '\0';
		buffer++;
	}

	return (token);
}

#include "main.h"

/**
* realloc_buffer - Resizes the buffer when it runs out of space.
* @lineptr: Pointer to the buffer.
* @n: Pointer to the size of the buffer.
* @size: Current size of the buffer.
* @nread: Number of characters read so far.
*
* Return: 0 on success, -1 on failure.
*/
int realloc_buffer(char **lineptr, size_t *n, size_t size, ssize_t nread)
{
	size_t new_size = size * 2;
	char *new_ptr = malloc(new_size);
	ssize_t i;

	if (new_ptr == NULL)
		return (-1);

	for (i = 0; i < nread; i++)
		new_ptr[i] = (*lineptr)[i];

	free(*lineptr);
	*lineptr = new_ptr;
	*n = new_size;

	return (0);
}

/**
* _getline - Reads an entire line from a stream using the read system call.
* @lineptr: Pointer to the buffer that will store the line read.
* @n: Pointer to the size of the buffer.
* @stream: The file descriptor to read from.
*
* Return: The number of characters read, or -1 on failure or EOF.
*/
ssize_t _getline(char **lineptr, size_t *n, int stream)
{
	ssize_t nread = 0;
	size_t size;
	char buffer[1];

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		size = 128;
		*lineptr = malloc(size);
		if (*lineptr == NULL)
			return (-1);
		*n = size;
	}
	else
		size = *n;

	while (1)
	{
		if (read(stream, buffer, 1) <= 0)
			return (nread > 0 ? nread : -1);

		if ((size_t)nread >= size - 1)
			if (realloc_buffer(lineptr, n, size, nread) == -1)
				return (-1);

		(*lineptr)[nread++] = buffer[0];
		if (buffer[0] == '\n')
			break;
	}

	(*lineptr)[nread] = '\0';
	return (nread);
}


/**
 *  * _atoi - converts a string to an integer
 *   * @s: string to be converted
 *    *
 *     * Return: the int converted from the string
   */
int _atoi(char *s)
{
	int i = 0, d = 0, n = 0, len = 0, f = 0, digit = 0;

	while (s[len] != '\0')
		len++;


	while (i < len && f == 0)
	{
		if (s[i] == '-')
			++d;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}
	if (f == 0)
		return (0);
	return (n);
}

/**
* _isdigit - check if numbers are 0 - 9
* @c: char to be checked
*
* Return: 0 or 1
*/
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
* _puts - prints a string, followed by a new line, to stdout
* @str: string to print
*/
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str++);
	}
	_putchar('\n');
}

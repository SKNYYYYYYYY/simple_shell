#include "main.h"
#include <stdlib.h>
#include <string.h>


/**
 * _setenv - Set or modify an environment variable
 * @name: Name of the variable
 * @value: Value of the variable
 * @overwrite: Whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char **env = environ; /* Use the global environ variable */
	char *new_var;
	size_t i;
	size_t name_len = _strlen(name);
	size_t value_len = _strlen(value);

	/* Check if environment variable already exists */
	for (i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], name, name_len) == 0 &&
			env[i][name_len] == '=')
		{
			if (overwrite)
			{
				/* Replace existing variable */
				new_var = malloc(name_len + value_len + 2); /* +2 for '=' and '\0' */
				if (new_var == NULL)
				{
					return (-1);
				}
				sprintf(new_var, "%s=%s", name, value);
				free(env[i]); /* Free the old variable */
				env[i] = new_var;
				return (0);
			}
			return (0);
		}
	}

	/* Add new environment variable */
	new_var = malloc(name_len + value_len + 2); /* +2 for '=' and '\0' */
	if (new_var == NULL)
	{
		return (-1);
	}
	sprintf(new_var, "%s=%s", name, value);
	env[i] = new_var;
	env[i + 1] = NULL; /* Null-terminate the array */

	return (0);
}

/**
 * get_env_var - Retrieve the value of an environment variable
 * @name: Name of the variable
 * @env: Environment variable list
 *
 * Return: Value of the variable or NULL if not found
 */
char *get_env_var(const char *name, char **env)
{
	size_t i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], name, strlen(name)) == 0 &&
			env[i][strlen(name)] == '=')
		{
			return (env[i] + strlen(name) + 1);
		}
	}
	return (NULL);
}

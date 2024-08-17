#include "main.h"

/**
 * find_path - Finds the full path of a command.
 * @command: The command to find.
 * @env: The environment variables.
 *
 * Return: The full path of the command or NULL if not found.
 */
char *find_path(char *command, char **env)
{
	char **path_list;
	char *full_path = NULL;
	int i;

	path_list = build_path_list(env);
	if (path_list == NULL)
		return (NULL);

	for (i = 0; path_list[i]; i++)
	{
		full_path = malloc(_strlen(path_list[i]) + _strlen(command) + 2);
		if (full_path == NULL)
		{
			free_path_list(path_list);
			return (NULL);
		}

		_strcpy(full_path, path_list[i]);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free_path_list(path_list);
			return (full_path);
		}
		free(full_path);
	}
	free_path_list(path_list);
	return (NULL);
}

/**
 * build_path_list - Builds a list of directories from the PATH variable.
 * @env: The environment variables.
 *
 * Return: An array of directories or NULL on failure.
 */
char **build_path_list(char **env)
{
	char *path_var, *path_var_copy;
	char **path_list;
	int i = 0;

	path_var = get_env_var("PATH", env);
	if (path_var == NULL)
		return (NULL);

	path_var_copy = _strdup(path_var);
	if (path_var_copy == NULL)
		return (NULL);
	path_list = malloc(BUFFER_SIZE * sizeof(char *));
	if (path_list == NULL)
		return (NULL);

	path_list[i] = _strtok(path_var_copy, ":");
	while (path_list[i] != NULL)
	{
		i++;
		path_list[i] = _strtok(NULL, ":");
	}
	return (path_list);
}

/**
 * free_path_list - Frees the memory allocated for the path list.
 * @path_list: The list to free.
 */
void free_path_list(char **path_list)
{
	free(path_list);
}

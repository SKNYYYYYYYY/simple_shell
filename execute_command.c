#include "main.h"

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 * @env: The environment variables.
 */
void execute_command(char *command, char **env)
{
	pid_t pid;
	char *full_path, *pathname;
	char **args;
	int status, i, j, arg_count;
	char **new_args;
	args = split_command(command);
	
	/*cd command to change directory*/
	if (_strcmp(args[0],"cd") == 0)
	{
		if (args[1] != NULL)
		{
			pathname = args[1];
		    if (chdir(pathname) == 0)
	            printf("%s#\n", args[1]);
		}
		else
		{
			pathname = "/home";
			chdir(pathname);
		}
	}
	
	/*Handling the exit command*/
if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
{
     
    arg_count = 0;

    
    while (args[arg_count] != NULL)
        arg_count++;

 
    new_args = malloc(sizeof(char *) * (arg_count + 1));
    if (new_args == NULL)
    {
        
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    
    for (i = 0; i < arg_count; i++)
    {
        new_args[i] = strdup(args[i]);
        if (new_args[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            for ( j = 0; j < i; j++)
                free(new_args[j]);
            free(new_args);
            exit(EXIT_FAILURE);
        }
    }
    new_args[arg_count] = NULL;  

   
    status = EXIT_SUCCESS;  /* Default to 0 */
    if (new_args[1] != NULL)
    {
        status = _atoi(new_args[1]);
        if (status < 0 || status > 255)
            status = EXIT_SUCCESS;  /* Invalid status, use 0 */
    }

    
    for ( i = 0; new_args[i] != NULL; i++)
        free(new_args[i]);
    free(new_args);

    exit(status);
}
    /*to check if the absolute path is specified i.e /bin/ls*/
	if(args[0][0] == '/' || args[0][1] == '/')
	{
		full_path = args[0];
	}
	else
	{
		full_path = find_path(command, env);
		if (full_path == NULL && _strcmp(args[0],"cd") != 0)
		{
			write(STDERR_FILENO, command, _strlen(command));
			write(STDERR_FILENO, ": command not found\n", 21);
			free(args);
			return;
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		free(args);
		return;
	}

	if (pid == 0)
	{
		printf("%s\n",full_path);
		execve(full_path, args, env);
		perror("execve");
		if(full_path != args[0])/*prevents double freeing hence enables executing compiled files more than once*/
			free(full_path);
		free(args);
		exit(1);
	}
	else
	{
		wait(NULL);
		if(full_path != args[0]) /*prevents double freeing hence enables executing compiled files more than once*/
			free(full_path);
		free(args);
	}
}


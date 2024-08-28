#ifndef MAIN_H
#define MAIN_H

extern char **environ;

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Buffer size for command and environment handling */
#define BUFFER_SIZE 1024

void print_prompt(void);
char *read_command(void);
void execute_command(char *command, char **env);
char *find_path(char *command, char **env);
char **build_path_list(char **env);
void free_path_list(char **path_list);
int _setenv(const char *name, const char *value, int overwrite);
char *get_env_var(const char *name, char **env);
char **split_command(char *command);
void *_realloc(char *str);


/*standard library Functions*/
void *_realloc(char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, char *src);
int _strncmp(char *s1, const char *s2, int n);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
int _isdigit(int c);
void _puts(char *str);
int _putchar(char c);

/*Helper functions*/
char* trim_comment(char* command);

#endif /* MAIN_H */

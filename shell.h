#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>




#define BUFFER_SIZE 1024
void free_arguments(char **arguments);
char *find_command(char *command);
int execute_command(char *command, char **arguments);
void handle_exit();
void handle_env();
int simple_shell(int mode);


#endif

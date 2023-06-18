#ifndef _SHELL_H_
#define _SHELL_H8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 100
void print_prompt(void);
char *read_command(void);
void execute_command(char *command);
void handle_exit(void);
void handle_env(void);



#endif

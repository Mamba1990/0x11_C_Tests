#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 100

void print_prompt(void)
{
    printf("simple_shell$ ");
    fflush(stdout);
}

char *read_command(void)
{
	char *command;
    	command = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    	fgets(command, MAX_COMMAND_LENGTH, stdin);
    	return (command);
}

void execute_command(char *command)
{
	int status;
	pid_t pid;
    	command[strcspn(command, "\n")] = '\0';  /* Remove the newline character */
    	pid = fork();
	if (pid < 0)
       	{
        	perror("fork");
        	return;
	}
    	else if (pid == 0)
	{
        						/* Child process */
		if (execlp(command, command, NULL) == -1)
	       	{
            		printf("Command not found: %s\n", command);
           		exit(1);
        	}	
        	exit(0);
	}
    	else
       	{
        /* Parent process */
		waitpid(pid, &status, 0);
    	}
}

void handle_exit(void)
{
	exit (0);
}

void handle_env(void)
{
	extern char **environ;
	int i;
    	for (i = 0; environ[i] != NULL; i++)
       	{
        	printf("%s\n", environ[i]);
    	}
}

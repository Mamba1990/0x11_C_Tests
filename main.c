#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
int main(void)
{
	char *command;
    	while (1) 
	{
        	print_prompt();
       		command = read_command();

        if (command == NULL) 
	{
            	printf("\n");
            	handle_exit();
        }

        if (strcmp(command, "exit") == 0) 
	{
            	handle_exit();
        } 
	else if (strcmp(command, "env") == 0) 
	{
            	handle_env();
        }
       	else
       	{
            	execute_command(command);
        }

        free(command);
    }

    return 0;
}









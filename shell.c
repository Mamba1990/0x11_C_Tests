#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ; /* Declare the environ variable*/

int simple_shell(void)
{
    char *buffer;
    size_t bufsize = BUFFER_SIZE;
    ssize_t line_size;
    int status;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("$ "); /* Display prompt*/

	line_size = getline(&buffer, &bufsize, stdin);
        if (line_size == -1)
        {
            if (feof(stdin))
            {
                printf("\n"); /* Handle end of file (Ctrl+D)*/
                break;
            }
            else
            {
                perror("getline error");
                exit(EXIT_FAILURE);
            }
        }

        buffer[line_size - 1] = '\0'; /* Remove the trailing newline character*/

        /* Execute the command*/

        if (fork() == 0)
        {
            /*Child process*/
            if (execve(buffer, (char *const *)&buffer, environ) == -1) /* Pass environ to execve*/
            {
                perror("execve error");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process*/
            wait(&status); /* Wait for the child process to finish*/
        }
    }

    free(buffer);
    return (0);
}


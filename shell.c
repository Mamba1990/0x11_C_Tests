#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

extern char **environ; /* Declare the environ variable*/

void free_arguments(char **arguments)
{
    int i;

    if (arguments == NULL)
        return;

    for (i = 0; arguments[i] != NULL; i++)
        free(arguments[i]);

    free(arguments);
}

void execute_command(char *command, char **arguments)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execvp(command, arguments) == -1)
        {
            perror("execvp error");
            free_arguments(arguments);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}

int simple_shell(int mode)
{
    char *buffer;
    size_t bufsize = BUFFER_SIZE;
    ssize_t line_size;
    char *command;
    char **arguments;
    size_t arg_count;
    char *token;
    size_t arguments_size = 64;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (mode == 1)
            printf("$ "); /* Display prompt */

        line_size = getline(&buffer, &bufsize, stdin);

        if (line_size == -1)
        {
            if (feof(stdin))
            {
                printf("\n"); /* Handle end of file (Ctrl+D) */
                break;
            }
            else
            {
                perror("getline error");
                exit(EXIT_FAILURE);
            }
        }

        buffer[line_size - 1] = '\0'; /* Remove the trailing newline character */

        if (strlen(buffer) == 0)
            continue; /* Skip processing if buffer is empty */

        if (mode == 2)
            printf("%s\n", buffer); /* Print the command in non-interactive mode */

        /* Tokenize the command and arguments */
        command = strtok(buffer, " ");
        arguments = (char **)malloc((arguments_size + 1) * sizeof(char *));
        if (arguments == NULL)
        {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
        arguments[0] = command;
        arg_count = 1;
        token = strtok(NULL, " ");

        while (token != NULL)
        {
            arguments[arg_count] = strdup(token);
            if (arguments[arg_count] == NULL)
            {
                perror("strdup error");
                free_arguments(arguments);
                exit(EXIT_FAILURE);
            }
            arg_count++;

            if (arg_count >= arguments_size)
            {
                arguments_size *= 2;
                arguments = (char **)realloc(arguments, (arguments_size + 1) * sizeof(char *));
                if (arguments == NULL)
                {
                    perror("realloc error");
                    free_arguments(arguments);
                    exit(EXIT_FAILURE);
                }
            }

            token = strtok(NULL, " ");
        }

        arguments[arg_count] = NULL;

        if (strcmp(command, "exit") == 0)
            break; /* Exit the shell if the command is "exit" */

        execute_command(command, arguments);

        free_arguments(arguments);
    }

    free(buffer);
    return 0;
}


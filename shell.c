#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

extern char **environ; /* Declare the environ variable */

void free_arguments(char **arguments)
{
    int i;

    if (arguments == NULL)
        return;
    for (i = 0; arguments[i] != NULL; i++)
        free(arguments[i]);

    free(arguments);
}

int simple_shell(int mode)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t line_size;
    int status;
    char **arguments = NULL;
    char *command;
    size_t arg_count;
    char *token;
    size_t arguments_size = 64;
    char *path;
    char *full_path;
    char *path_env;
    char *path_token;

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
                    exit(EXIT_FAILURE);
                }
            }

            token = strtok(NULL, " ");
        }

        arguments[arg_count] = NULL;

        /* Check if the command is "exit" */
        if (strcmp(command, "exit") == 0)
        {
            break; /* Exit the loop if the command is "exit" */
        }

        /* Check if the command exists in the PATH before calling fork */
        path = getenv("PATH");
        if (path != NULL)
        {
            path_env = strdup(path);
            if (path_env == NULL)
            {
                perror("strdup error");
                exit(EXIT_FAILURE);
            }

            path_token = strtok(path_env, ":");
            while (path_token != NULL)
            {
                full_path = malloc(strlen(path_token) + strlen(command) + 2); /* 2 for '/' and '\0' */
                if (full_path == NULL)
                {
                    perror("malloc error");
                    exit(EXIT_FAILURE);
                }
                strcpy(full_path, path_token);
                strcat(full_path, "/");
                strcat(full_path, command);

                if (access(full_path, X_OK) == 0)
                {
                    /* Command exists in the PATH, call fork and execve */
                    if (fork() == 0)
                    {
                        /* Child process */
                        execve(full_path, arguments, environ); /* Pass environ to execve */

                        perror("execve error");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        /* Parent process */
                        wait(&status); /* Wait for the child process to finish */
                    }
                    free(full_path);
                    break; /* Exit the loop if the command is found and executed */
                }
                free(full_path);
                path_token = strtok(NULL, ":");
            }

            free(path_env);
        }
        else
        {
            /* PATH environment variable is not set */
            printf("PATH environment variable is not set. Unable to locate command.\n");
        }
    }

    free(buffer);
    return 1; /* Return 1 to indicate successful termination */
}

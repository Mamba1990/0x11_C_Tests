
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"


#define BUFF_SIZE 1024
extern char **environ; /* Declare the environ variable */
/**
 * freeArguments - frees arguments
 * @args: pointer to an array of strings 
 *
 * Return: void
 */

void freeArguments(char **args)
{
    int i;

    if (args == NULL)
        return;
    for (i = 0; args[i] != NULL; i++)
        free(args[i]);

    free(args);
}

int my_simple_shell(int mode)
{
    char *buff = NULL;
    size_t bufsize = 0;
    ssize_t lineSize;
    int status;
    char **args = NULL;
    char *cmd;
    size_t argCount;
    char *token;
    size_t arguments_size = 64;
    char *path;
    char *fullPath;
    char *pathEnv;
    char *pathToken;

    while (1)
    {
        if (mode == 1)
            printf("$ "); /* Display prompt */

        lineSize = getline(&buff, &bufsize, stdin);
        if (lineSize == -1)
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

        buff[lineSize - 1] = '\0'; /* Remove the trailing newline character */

        /* Tokenize the command and arguments */
        cmd = strtok(buff, " ");
        args = (char **)malloc((arguments_size + 1) * sizeof(char *));
        if (args == NULL)
        {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
        args[0] = cmd;
        argCount = 1;
        token = strtok(NULL, " ");

        while (token != NULL)
        {
            args[argCount] = str_dup(token);
            if (args[argCount] == NULL)
            {
                perror("strdup error");
                exit(EXIT_FAILURE);
            }
            argCount++;

            if (argCount >= arguments_size)
            {
                arguments_size *= 2;
                args = (char **)__realloc(args, (arguments_size + 1) * sizeof(char *));
                if (args == NULL)
                {
                    perror("realloc error");
                    exit(EXIT_FAILURE);
                }
            }

            token = strtok(NULL, " ");
        }

        args[argCount] = NULL;

        /* Check if the command is "exit" */
        if (str_cmp(cmd, "exit") == 0)
        {
            break; /* Exit the loop if the command is "exit" */
        }

        /* Check if the command exists in the PATH before calling fork */
        path = getenv("PATH");
        if (path != NULL)
        {
            pathEnv = strdup(path);
            if (pathEnv == NULL)
            {
                perror("strdup error");
                exit(EXIT_FAILURE);
            }

            pathToken = strtok(pathEnv, ":");
            while (pathToken != NULL)
            {
                fullPath = malloc(str_len(pathToken) + str_len(cmd) + 2); /* 2 for '/' and '\0' */
                if (fullPath == NULL)
                {
                    perror("malloc error");
                    exit(EXIT_FAILURE);
                }
                str_cpy(fullPath, pathToken);
                str_cat(fullPath, "/");
                str_cat(fullPath, cmd);

                if (access(fullPath, X_OK) == 0)
                {
                    /* Command exists in the PATH, call fork and execve */
                    if (fork() == 0)
                    {
                        /* Child process */
                        execve(fullPath, args, environ); /* Pass environ to execve */

                        perror("execve error");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        /* Parent process */
                        wait(&status); /* Wait for the child process to finish */
                    }
                    free(fullPath);
                    break; /* Exit the loop if the command is found and executed */
                }
                free(fullPath);
                pathToken = strtok(NULL, ":");
            }

            free(pathEnv);
        }
        else
        {
            /* PATH environment variable is not set */
            printf("PATH environment variable is not set. Unable to locate command.\n");
        }
    }

    free(buff);
    return 1; /* Return 1 to indicate successful termination */
}

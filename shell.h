#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
void freeArguments(char **args);
char *str_dup(const char *str);
int my_simple_shell(int mode);
int str_len(const char *s);
int str_cmp(char *s1, char *s2);
char *str_cpy(char *dest, char *src);
char *str_cat(char *dest, char *src);
void *__realloc(void *ptr, size_t size);
void _free(void *ptr);
void __free(char **ptr);
#endif

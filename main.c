#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Entry point of the program
 * @argc: The number of command-line arguments
 * @argv: An array of strings containing the arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	int i;
	int mode;

	if (argc < 1)
	{
		printf("No arguments provided.\n");
		return (1);
	}

	/* Accessing command-line arguments */
	printf("Command-line arguments:\n");
	for (i = 0; i < argc; i++)
	{
		printf("Argument %d: %s\n", i, argv[i]);
	}


	printf("Select mode:\n");
	printf("1. Interactive Mode\n");
	printf("2. Non-Interactive Mode\n");
	printf("Enter mode (1 or 2): ");
	scanf("%d", &mode);

	while (getchar() != '\n');

	if (mode == 1 || mode == 2)
	{
		my_simple_shell(mode);
	}
	else
	{
		printf("Invalid mode. Please enter 1 or 2.\n");
	}

	return (0);
}


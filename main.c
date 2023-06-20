#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int main(void)
{
    int mode;

    printf("Select mode:\n");
    printf("1. Interactive Mode\n");
    printf("2. Non-Interactive Mode\n");
    printf("Enter mode (1 or 2): ");
    scanf("%d", &mode);

    while (getchar() != '\n'); /* Clear the input buffer */

    if (mode == 1 || mode == 2)
    {
        my_simple_shell(mode);
    }
    else
    {
        printf("Invalid mode. Please enter 1 or 2.\n");
    }

    return 0;
}


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

    if (mode == 1)
    {
        /* Interactive mode */
        simple_shell(1);
    }
    else if (mode == 2)
    {
        /*  Non-interactive mode */
        simple_shell(0);
    }
    else
    {
        printf("Invalid mode. Please try again.\n");
        return 1;
    }

    return 0;
}
